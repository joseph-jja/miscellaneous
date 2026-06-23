use serde::{Deserialize, Serialize};
use std::process;
use time::OffsetDateTime;

pub mod utils;
use crate::utils::utils::utils::current_latitude;
use crate::utils::utils::utils::current_longitude;
use crate::utils::utils::utils::open_weathermap_api_key;
use crate::utils::utils::utils::read_in_file;

use crate::utils::open_weather::open_weather::get_open_weather_data;
use crate::utils::weather::weather::get_weather_data;

use crate::utils::terminal::terminal::destroy_terminal;
use crate::utils::terminal::terminal::draw_box_at_location;
use crate::utils::terminal::terminal::flush_stdout;
use crate::utils::terminal::terminal::init_terminal;
use crate::utils::terminal::terminal::clear_terminal;
use crate::utils::terminal::terminal::sleep_terminal;
use crate::utils::terminal::terminal::write_text_at;

use crate::utils::numbers::numbers::get_offset;
use crate::utils::write_number::number;

#[derive(Serialize, Deserialize)]
struct ConfigData {
    key: String,
    latitude: f32,
    longitude: f32,
}

fn write_time() {
    if let Ok(now) = OffsetDateTime::now_local() {
        let hour = u16::from(now.hour());
        let minute = u16::from(now.minute());

       let hour_big: u16 = get_offset(0, 2);
       let hour_small: u16 = get_offset(1, 2);

       let minute_big: u16 = 5 + get_offset(2, 2);
       let minute_small: u16 = 5 + get_offset(3, 2);
        
        if hour < 10 {
            number::write(hour_big, 2, 0);
            number::write(hour_small, 2, hour);
        } else {
            let hour_hundred: u16 = hour / 10;
            let hour_ten: u16 = (hour - (hour_hundred * 10));
            number::write(hour_big, 2, hour_hundred);
            number::write(hour_small, 2, hour_ten);
        }

        if minute < 10 {
            number::write(minute_big, 2, 0);
            number::write(minute_small, 2, minute);
        } else {
            let minute_hundred: u16 = minute / 10;
            let minute_ten: u16 = (minute - (minute_hundred * 10));
            number::write(minute_big, 2, minute_hundred);
            number::write(minute_small, 2, minute_ten);
        }

        let formatted_date = format!("{:?}i, {:?} {:?}, {:?}", now.weekday(), now.month(), now.day(), now.year());
        write_text_at(2, 20, formatted_date);
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

    init_terminal();
    clear_terminal();
    write_time();   
    flush_stdout();
    sleep_terminal(10);
    destroy_terminal();
    
    /*println!(
        "Config file latitude: {:?} and longitude: {:?}",
        config_json.latitude, config_json.longitude
    );*/

    //get_weather_data();
    //get_open_weather_data();
}
