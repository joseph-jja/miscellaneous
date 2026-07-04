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
        return (KELVIN_TO_FAHRENHEIT_MULTIPLIER * kelvin_in - KELVIN_CONST)
            .round()
            .to_string();
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
        }
        //let weather: String  = parsed.get("weather").unwrap().to_string();
        //let main: String = parsed.get("main").unwrap().to_string();
        //let wind: String = parsed.get("wind").unwrap().to_string();
        //let clouds: String = parsed.get("clouds").unwrap().to_string();
        
        //println!("We got some results {:?}", results);
    }
}
