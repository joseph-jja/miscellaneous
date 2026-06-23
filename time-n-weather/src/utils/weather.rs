pub mod weather {

    use std::path::PathBuf;

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

        let mut output_filename = PathBuf::new();
        output_filename.push("/");
        output_filename.push("tmp");
        output_filename.push("hourlyForecast.json");
        let filename: String =  output_filename.to_string_lossy().into_owned();
        
        println!("We got some results {:?} for file {:?}", results, output_filename);
        write_outfile(&filename, &results);
    }
}
