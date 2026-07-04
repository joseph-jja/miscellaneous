pub mod open_weather {

    use serde_json::Value;

    use crate::utils::utils::utils::current_latitude;
    use crate::utils::utils::utils::current_longitude;
    use crate::utils::utils::utils::make_api_request;
    use crate::utils::utils::utils::open_weathermap_api_key;
    use crate::utils::utils::utils::LINE_ENDING;

    use crate::utils::utils::utils::write_temp_file;

    const RELOAD: i32 = 1000 * 60 * 60;
    const API_HOSTNAME: &str = "https://api.openweathermap.org";

    const KELVIN_TO_FAHRENHEIT_MULTIPLIER: f64 = 9.0 / 5.0;
    const KELVIN_CONST: f64 = 459.67;

    fn to_fahrenheit(kelvin_in: f64) -> String {
        let mut result: String (KELVIN_TO_FAHRENHEIT_MULTIPLIER * kelvin_in - KELVIN_CONST)
            .round()
            .to_string();
        result.push_str("F");
        return result;
    }

    pub fn get_open_weather_data() {
        let mut endpoint: String = String::from(API_HOSTNAME);
        endpoint.push_str("/data/2.5/weather?lat=");

        {
            let latitude = current_latitude().read().unwrap();
            let borrowed_str: &str = &latitude;
            endpoint.push_str(borrowed_str);
        }

        endpoint.push_str("&lon=");

        {
            let latitude = current_longitude().read().unwrap();
            let borrowed_str: &str = &latitude;
            endpoint.push_str(borrowed_str);
        }

        endpoint.push_str("&APPID=");

        {
            let api_key = open_weathermap_api_key().read().unwrap();
            let borrowed_str: &str = &api_key;
            endpoint.push_str(borrowed_str);
        }

        let results = make_api_request(&endpoint); //.expect("Got weather data!");
        write_temp_file("openweather.json", &results);

        let parsed: Value =
            serde_json::from_str(&results.as_str()).expect("Should have open weather data!");

        let mut output_data: String = String::from("");

        if let Some(main_section) = parsed.get("main") {
            let temp: String = main_section.get("temp").unwrap().to_string();
            let temp_value_F: String = to_fahrenheit(temp.parse().unwrap());
            output_data.push_str("Current: ");
            output_data.push_str(&temp_value_F);
            
            let temp_min: String = main_section.get("temp_min").unwrap().to_string();
            let temp__min_value_F: String = to_fahrenheit(temp_min.parse().unwrap());
            let temp_max: String = main_section.get("temp_max").unwrap().to_string();
            let temp__max_value_F: String = to_fahrenheit(temp_max.parse().unwrap());
            output_data.push_str("    High/Low: ");
            output_data.push_str(&temp__min_value_F);
            output_data.push_str("/");
            output_data.push_str(&temp__max_value_F);
            output_data.push_str(LINE_ENDING);

            let humidity: String = main_section.get("humidity").unwrap().to_string();
            output_data.push_str("Humidity: ");
            output_data.push_str(&humidity);
        }

        output_data.push_str("    Clouds: ");
        if let Some(clouds) = parsed.get("clouds").and_then(|d| d.get("all")) {
            output_data.push_str(&clouds.to_string());
        } else {
            output_data.push_str("0");
        }
        output_data.push_str("%");
        
        output_data.push_str("    Rain: ");
        if let Some(rain) = parsed.get("rain") {
            if let Some(one_hr) = rain.get("1h") {
                output_data.push_str(&one_hr.to_string());
            } else {
                output_data.push_str("0");
            }
        } else {
            output_data.push_str("0");
        }
        output_data.push_str(LINE_ENDING);

        if let Some(weather) = parsed.get("weather") {
            if let Some(main_title) = weather.get("main") { 
                output_data.push_str(&main_title.to_string());
    
                if let Some(description) = weather.get("description") {
                    output_data.push_str(": ");
                    output_data.push_str(&description.to_string());
                }
                output_data.push_str(LINE_ENDING);
            }
        }

        if let Some(wind) = parsed.get("wind") {
            let wind_speed = wind.get("speed").unwrap().to_string();
            output_data.push_str("Wind Speed: ");
            output_data.push_str(&wind_speed);
            
            let wind_direction = wind.get("deg").unwrap().to_string();
            output_data.push_str("    Wind Direction: ");
            output_data.push_str(&wind_direction);

            let wind_gust = wind.get("gust").unwrap().to_string();
            output_data.push_str("    Wind Gust: ");
            output_data.push_str(&wind_gust);

            output_data.push_str(LINE_ENDING);
        }

        //println!("We got some results {:?}", results);
        write_temp_file("details.txt", &output_data);
    }
}
