use serde::{Deserialize, Serialize};
use std::io;
use std::process;
use time::OffsetDateTime;

use utils::{
    current_latitude, current_longitude, open_weathermap_api_key, read_in_file, write_file,
};

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

    let configFilename: String = args[1].clone();
    let configFileData: String = read_in_file(&configFilename);
    let configJSON: ConfigData =
        serde_json::from_str(configFileData.as_str()).expect("Could not parse JSON file!");

    {
        let mut latitude = current_latitude().write().unwrap();
        current_latitude.clear();
        current_latitude.push_str(&configJSON.latitude);
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
    }

    println!("Config file latitude: {:?}", configJSON.latitude);

    write_time();
}
