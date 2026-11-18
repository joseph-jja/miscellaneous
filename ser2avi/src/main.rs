use anyhow::{Context, Result};
use clap::Parser;
use opencv::core::{Mat, Rect, Size, CV_8UC1, CV_8UC3, CV_16UC1};
use opencv::imgproc;
use opencv::prelude::*;
use opencv::videoio::VideoWriter;
use ser_io::SerFile;
use std::path::PathBuf;

#[derive(Parser, Debug)]
#[command(author, version, about = "CLI tool to read SER files, debayer, center, crop, and export as an AVI video.")]
struct Args {
    /// Path to input SER file
    #[arg(short, long)]
    input: PathBuf,

    /// Path to output AVI file
    #[arg(short, long)]
    output: PathBuf,

    /// Crop width and height for output video (e.g. 512)
    #[arg(short, long, default_value_t = 512)]
    crop_size: i32,

    /// Pixel brightness threshold (0-255) for object centroid detection
    #[arg(short, long, default_value_t = 100)]
    threshold: u8,
}

fn main() -> Result<()> {
    let args = Args::parse();

    // 1. Open and parse the SER file header using ser-io
    let input_path_str = args.input.to_str().context("Invalid input file path encoding")?;
    let mut ser = SerFile::open(input_path_str).context("Failed to open input SER file")?;

    let width = ser.header.image_width as i32;
    let height = ser.header.image_height as i32;
    let frame_count = ser.header.frame_count as usize;
    let color_id = ser.header.color_id;
    let bits_per_pixel = ser.header.pixel_depth_per_plane;

    println!(
        "SER File Loaded: {}x{}, Frames: {}, Color ID: {:?}, Bits/Pixel: {}",
        width, height, frame_count, color_id, bits_per_pixel
    );

    // 2. Initialize OpenCV VideoWriter for AVI output (MJPEG Codec)
    let fourcc = VideoWriter::fourcc('M', 'J', 'P', 'G')?;
    let fps = 30.0;
    let output_size = Size::new(args.crop_size, args.crop_size);
    let mut video_writer = VideoWriter::new(
        args.output.to_str().unwrap(),
        fourcc,
        fps,
        output_size,
        true, // is_color
    ).context("Failed to initialize OpenCV VideoWriter")?;

    if !video_writer.is_opened()? {
        anyhow::bail!("VideoWriter failed to open output file");
    }

    // 3. Iterate over frames
    for i in 0..frame_count {
        print!("\rProcessing frame {}/{}", i + 1, frame_count);
        std::io::Write::flush(&mut std::io::stdout())?;

        let raw_bytes = ser.read_frame(i).context("Failed to read frame from SER file")?;
        
        let is_16bit = bits_per_pixel > 8;

        // Wrap raw buffer into an OpenCV Mat safely based on bit depth
        let src_mat = if is_16bit {
            let u16_slice: &[u16] = unsafe {
                std::slice::from_raw_parts(
                    raw_bytes.as_ptr() as *const u16,
                    raw_bytes.len() / 2,
                )
            };
            Mat::new_rows_cols_with_data(height, width, u16_slice)?.try_clone()?
        } else {
            Mat::new_rows_cols_with_data(height, width, raw_bytes.as_slice())?.try_clone()?
        };

        // Convert 16-bit to 8-bit for standard processing & video output if necessary
        let mut mat_8u = Mat::default();
        if is_16bit {
            src_mat.convert_to(&mut mat_8u, CV_8UC1, 1.0 / 256.0, 0.0)?;
        } else {
            mat_8u = src_mat;
        }

        // 4. Debayer frame by matching the ColorId enum debug string representation
        let mut bgr_mat = Mat::default();
        let color_id_str = format!("{:?}", color_id).to_uppercase();
        let bayer_code = if color_id_str.contains("RGGB") {
            imgproc::COLOR_BayerRG2BGR
        } else if color_id_str.contains("GRBG") {
            imgproc::COLOR_BayerGR2BGR
        } else if color_id_str.contains("GBRG") {
            imgproc::COLOR_BayerGB2BGR
        } else if color_id_str.contains("BGGR") {
            imgproc::COLOR_BayerBG2BGR
        } else {
            imgproc::COLOR_GRAY2BGR
        };
        
        imgproc::cvt_color(&mat_8u, &mut bgr_mat, bayer_code, 0)?;

        // 5. Identify celestial body center using thresholding and image moments
        let mut gray_for_centroid = Mat::default();
        imgproc::cvt_color(&bgr_mat, &mut gray_for_centroid, imgproc::COLOR_BGR2GRAY, 0)?;

        let mut thresh_mat = Mat::default();
        imgproc::threshold(&gray_for_centroid, &mut thresh_mat, args.threshold as f64, 255.0, imgproc::THRESH_BINARY)?;

        let moments = imgproc::moments(&thresh_mat, false)?;
        let (center_x, center_y) = if moments.m00 > 0.0 {
            ((moments.m10 / moments.m00) as i32, (moments.m01 / moments.m00) as i32)
        } else {
            (width / 2, height / 2) // Fallback to frame center if nothing found
        };

        // 6. Safe Crop and Center with Black Padding for Out-of-Bounds Edges
        let half_crop = args.crop_size / 2;
        let start_x = center_x - half_crop;
        let start_y = center_y - half_crop;

        let mut roi_x = start_x;
        let mut roi_y = start_y;
        let mut roi_w = args.crop_size;
        let mut roi_h = args.crop_size;

        let mut pad_left = 0;
        let mut pad_top = 0;

        if start_x < 0 {
            pad_left = -start_x;
            roi_x = 0;
            roi_w -= pad_left;
        }
        if start_y < 0 {
            pad_top = -start_y;
            roi_y = 0;
            roi_h -= pad_top;
        }
        if roi_x + roi_w > width {
            roi_w = width - roi_x;
        }
        if roi_y + roi_h > height {
            roi_h = height - roi_y;
        }

        let mut final_frame = Mat::zeros(args.crop_size, args.crop_size, CV_8UC3)?.to_mat()?;

        if roi_w > 0 && roi_h > 0 {
            let valid_roi = Rect::new(roi_x, roi_y, roi_w, roi_h);
            let cropped_mat = Mat::roi(&bgr_mat, valid_roi)?;
            
            let mut destination_roi = Mat::roi_mut(
                &mut final_frame, 
                Rect::new(pad_left, pad_top, roi_w, roi_h)
            )?;
            cropped_mat.copy_to(&mut destination_roi)?;
        }

        // 7. Write frame to AVI
        video_writer.write(&final_frame)?;
    }

    println!("\nProcessing complete! Output saved to: {:?}", args.output);
    Ok(())
}
