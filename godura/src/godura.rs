
use gtk4 as gtk;
use gtk::prelude::*;
use gtk::{Application, ApplicationWindow};
use gtk::gio; 

struct MainWindow {
    app: Application,
    window: ApplicationWindow,
    buffer: TextBuffer,
    position: Text
}


fn main() {
   
   let args: Vec<String> = std::env::args().collect();

   if args.len() > 0 {
       println!("Got args {} {}!", args.len(), args[0])
   }  

   let app = Application::builder().application_id(APP_ID)
        .flags(gio::ApplicationFlags::HANDLES_OPEN)
        .build();

    let buffer: gtk::TextBuffer = textarea::create_gtk_buffer();

   // Ensure your main window is created/presented here if needed
    app.connect_activate(move |app| {
        build_window(app, &buffer);
    });

    let windows = app.windows();

    let mut main_window: gtk::ApplicationWindow;
    println!("Wind {:?}", app);
    for window in windows {
        if let Ok(app_window) = window.downcast::<gtk::ApplicationWindow>() {
            println!("Window found with title: {:?}", app_window.title());
            main_window = app_window;
        }
    }

    // 2. Connect the "open" signal
    /*let buff_clone = buffer.clone();
    app.connect_open(|app, files, _hint| {
        build_window(app, &buff_clone);
        println!("Received {} file(s) to open:", files.len());
        for file in files {
            if let Some(path) = file.path() {
                println!("- Opening: {:?}", path);
                let path_string: String = path.to_string_lossy().into_owned();
                let text_data: String = read_in_file(&path_string);
                if let Some(window) = app.active_window() {
                    if let Some(view) = window.child() {
                        println!("Got data and view {:?}", view);
                    }
                }
            }
        }
        println!("Now here, reactivate?");
    });*/

    //app.connect_activate(|_app| {
        // Fallback UI initialization if no files were explicitly requested
    //});

//   let text = scroll_textarea.child().and_downcast::<gtk4::TextView>();
            //text.buffer().set_text(text_data);
        //}*/
       
        // Present the window
    //});

    app.run_with_args(&std::env::args().collect::<Vec<String>>());

    println!("App Start {}", APP_ID)
}
