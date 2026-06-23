pub mod weather {

    use crate::utils::utils::utils::current_latitude;
    use crate::utils::utils::utils::current_longitude;
    use crate::utils::utils::utils::make_api_request;
    use crate::utils::utils::utils::write_outfile;

    const RELOAD: i32 = 1000 * 60 * 60;
    const API_HOSTNAME: &str = "https://api.weather.gov";

    pub fn get_weather_data() {
        let mut endpoint: String = String::from(API_HOSTNAME);
        endpoint.push_str("/points/");

        {
            let latitude = current_latitude().read().unwrap();
            let borrowed_str: &str = &latitude;
            endpoint.push_str(borrowed_str);
        }

        endpoint.push_str(",");

        {
            let latitude = current_longitude().read().unwrap();
            let borrowed_str: &str = &latitude;
            endpoint.push_str(borrowed_str);
        }

        let results = make_api_request(&endpoint); //.expect("Got weather data!");
        println!("We got some results {:?}", results);
        let output_filename: String = String.from("/tmp/hourlyForecast.json"); 
        write_outfile(output_filename, &results);
    }
}
