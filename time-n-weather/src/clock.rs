use std::fs::{read_to_string, write};
use std::io;
use std::process;
use serde::{Deserialize, Serialize};
use chrono::{Local};

#[derive(Serialize, Deserialize)]
struct ConfigData {
    key: String, 
    latitude: f32,
    longitude: f32
}

fn read_in_file(filename: &String) -> String {

        let contents = read_to_string(filename).expect("Could not read file specified!");

        //println!("Open file {:?}", filename);

        return contents;
    }

fn write_outfile(filename: &String, filedata: &String) -> Result<(), io::Error> {

        println!("Saving file {:?}", filename);

        write(filename, filedata)?;
        Ok(())
}

fn write_time() {

    let now_local = Local::now();
    let hour = now_local.hour();
    let minutes = now_local.minute();
    println!("Local time: {}:{}", hour, minutes);
}

fn main() {

    let args: Vec<String> = std::env::args().collect();

    if args.len() < 1 {
        println!("Insufficient arguments!  Need a JSON configuration file!");
        process::exit(1);
    }

    let configFilename: String = args[1].clone();
    let configFileData: String = read_in_file(&configFilename);
    let configJSON: ConfigData = serde_json::from_str(configFileData.as_str())
                .expect("Could not parse JSON file!");

    println!("Config file latitude: {:?}", configJSON.latitude);

    write_time();    
}
