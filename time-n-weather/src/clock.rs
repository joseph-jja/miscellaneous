use serde::{Deserialize, Serialize};
use std::process;
use time::OffsetDateTime;

pub mod utils;
use crate::utils::utils::utils::read_in_file;
use crate::utils::utils::utils::write_outfile;
use crate::utils::utils::utils::current_latitude;

#[derive(Serialize, Deserialize)]
struct ConfigData {
    key: String,
    latitude: f32,
    longitude: f32,
}

fn write_time() {
    if let Ok(now) = OffsetDateTime::now_local() {
        let hour = now.hour();
        let minute = now.minute();

        println!("Current time is {:02}:{:02}", hour, minute);
    }
}

fn main() {
    let args: Vec<String> = std::env::args().collect();

    if args.len() < 1 {
        println!("Insufficient arguments!  Need a JSON configuration file!");
        process::exit(1);
    }

    let config_filename: String = args[1].clone();
    let config_file_data: String = read_in_file(&config_filename);
    let config_json: ConfigData =
        serde_json::from_str(config_file_data.as_str()).expect("Could not parse JSON file!");

    /*{
        let mut latitude = current_latitude().write().unwrap();
        utils::current_latitude.clear();
        utils::current_latitude.push_str(&configJSON.latitude);
    }
    {
        let mut longitude = current_longitude().write().unwrap();
        current_longitude.clear();
        current_longitude.push_str(&configJSON.longitude);
    }
    {
        let mut api_key = open_weathermap_api_key().write().unwrap();
        open_weathermap_api_key.clear();
        open_weathermap_api_key.push_str(&configFileData.key);
    }*/

    println!("Config file latitude: {:?}", config_json.latitude);

    write_time();
}
