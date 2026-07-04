pub mod open_weather {

    use crate::utils::utils::utils::current_latitude;
    use crate::utils::utils::utils::current_longitude;
    use crate::utils::utils::utils::make_api_request;
    use crate::utils::utils::utils::open_weathermap_api_key;

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
        //println!("We got some results {:?}", results);
    }
}
