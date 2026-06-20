use serde::{Deserialize, Serialize};
use std::process;
use time::OffsetDateTime;

pub mod utils;
use crate::utils::utils::utils::read_in_file;
use crate::utils::utils::utils::current_latitude;
use crate::utils::utils::utils::current_longitude;
use crate::utils::utils::utils::open_weathermap_api_key;

use crate::utils::weather::weather::get_weather_data;

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

    // store these in rw lockable variables as they will be accessed by 2 APIs to get the data 
    // we are going to save and eventually parse
    {
        let lat_temp: String = config_json.latitude.to_string();
        let borrowed_str: &str = &lat_temp; 
        let mut latitude = current_latitude().write().unwrap();
        latitude.clear();
        latitude.push_str(borrowed_str);
    }
    {
        let long_temp: String = config_json.longitude.to_string();
        let borrowed_str: &str = &long_temp; 
        let mut longitude = current_longitude().write().unwrap();
        longitude.clear();
        longitude.push_str(borrowed_str);
    }
    {
        let key_temp: &str = &config_json.key; 
        let mut api_key = open_weathermap_api_key().write().unwrap();
        api_key.clear();
        api_key.push_str(key_temp);
    }

    println!("Config file latitude: {:?} and longitude: {:?}", config_json.latitude, config_json.longitude);

    write_time();
    get_weather_data();
}
