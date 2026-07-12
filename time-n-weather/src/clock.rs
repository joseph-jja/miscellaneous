use serde::{Deserialize, Serialize};
use std::process;
use time::OffsetDateTime;

pub mod utils;
use crate::utils::utils::utils::{
    current_latitude,
    current_longitude, 
    open_weathermap_api_key, 
    read_in_file
};

use crate::utils::open_weather::open_weather::{ get_open_weather_data, write_ow_data_to_screen};
use crate::utils::weather::weather::{get_weather_data, write_data_to_screen};

use crate::utils::terminal::terminal::{
    clear_terminal, 
    destroy_terminal, 
    flush_stdout, 
    init_terminal, 
    sleep_terminal, 
    write_text_at,
    update_color
};

use crate::utils::numbers::numbers::{ get_offset, write_colon};
use crate::utils::write_number::number;

use crate::utils::network::iface::get_interfaces;

#[derive(Serialize, Deserialize)]
struct ConfigData {
    key: String,
    latitude: f32,
    longitude: f32,
}

const MINUTE: i32 = 60;
const RELOAD_WEATHER_API_DATA: i32 = 30 * MINUTE; // 30 minutes update
const RELOAD_OPEN_WEATHER_API_DATA: i32 = 60 * MINUTE; // one hour update
const SLEEP_TIME: i32 = 1; // in seconds
const SLEEP_TIME_U64: u64 = 1; // easier than converting
const MAX_SLEEP_I_VALUE: i32 = 120 * MINUTE;

fn write_time() {
    if let Ok(now) = OffsetDateTime::now_local() {
        let hour = u16::from(now.hour());
        let minute = u16::from(now.minute());

        let hour_big: u16 = get_offset(0, 2);
        let hour_small: u16 = get_offset(1, 2);

        let minute_big: u16 = 5 + get_offset(2, 2);
        let minute_small: u16 = 5 + get_offset(3, 2);

        let mut ampm: &str = "am";

        if hour < 10 {
            number::write(hour_big, 2, 0);
            number::write(hour_small, 2, hour);
        } else if hour > 12 {
            ampm = "pm";
            let twelve_hour: u16 = hour - 12;
            let hour_hundred: u16 = twelve_hour / 10;
            let hour_ten: u16 = twelve_hour - hour_hundred * 10;
            number::write(hour_big, 2, hour_hundred);
            number::write(hour_small, 2, hour_ten);
        } else {
            ampm = "pm";
            let hour_hundred: u16 = hour / 10;
            let hour_ten: u16 = hour - hour_hundred * 10;
            number::write(hour_big, 2, hour_hundred);
            number::write(hour_small, 2, hour_ten);
        }

        // 15 => 5 and 10 ?
        write_colon(hour_small + 11 + 3, 2 + 5);
        write_colon(hour_small + 11 + 3, 2 + 10);

        if minute < 10 {
            number::write(minute_big, 2, 0);
            number::write(minute_small, 2, minute);
        } else {
            let minute_hundred: u16 = minute / 10;
            let minute_ten: u16 = minute - minute_hundred * 10;
            number::write(minute_big, 2, minute_hundred);
            number::write(minute_small, 2, minute_ten);
        }

        let right_offset: u16 = 7 + get_offset(4, 2);

        let formatted_date = format!(
            "{:?}, {:?} {:?}, {:?}",
            now.weekday(),
            now.month(),
            now.day(),
            now.year()
        );
        write_text_at(right_offset, 3, &formatted_date.as_str());
        write_text_at(right_offset, 5, &ampm);
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

    let mut i: i32 = 0;
    init_terminal();
    // TODO need to add in control-C kill app functionality
    // for now testing we just run loop 120 times which should be about 2 minutes
    // ideally we would have endless loop until control-C
    while i < 120 {
        // get the weather data first time and then
        // 30 minuntes
        if i == 0 || i == RELOAD_WEATHER_API_DATA {
            get_weather_data();
        }
        // then every 60 minutes
        if i == 0 || i == RELOAD_OPEN_WEATHER_API_DATA {
            get_open_weather_data();
        }

        clear_terminal();
        write_time();

        let x_offset: u16 = 7 + get_offset(4, 2);
        write_data_to_screen(x_offset, 8);

        let net_ifaces: String = get_interfaces();
        write_text_at(x_offset, 15, &net_ifaces);

        write_ow_data_to_screen(10, 15 + 2 + 2);
        if i == 0 {
            get_weather_data();
        }

        flush_stdout();
        sleep_terminal(SLEEP_TIME_U64);
        i = i + SLEEP_TIME;
        if i > MAX_SLEEP_I_VALUE {
            i = 0;
        }
        update_color();
    }
    destroy_terminal();
}
