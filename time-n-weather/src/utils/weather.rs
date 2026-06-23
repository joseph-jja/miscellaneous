pub mod weather {

    use std::path::PathBuf;

    use serde::{Deserialize, Serialize};
    use serde_json::Value;

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

        let results = make_api_request(&endpoint);

        let mut output_filename = PathBuf::new();
        output_filename.push("/");
        output_filename.push("tmp");
        output_filename.push("forecast.json");

        //println!("We got some results {:?} for file {:?}", results, output_filename);
        let filename: String = output_filename.to_string_lossy().into_owned();
        write_outfile(&filename, &results);

        let parsed: Value =
            serde_json::from_str(&results.as_str()).expect("Should have forecast data!");
        if let Some(forecast_url) = parsed
            .get("properties")
            .and_then(|d| d.get("forecastHourly"))
        {
            let forecast = forecast_url.to_string().replace('"', "");

            // Print the dynamic object
            println!("Found url: {:?}", forecast);

            let hourly_forcast = make_api_request(&forecast);

            let mut forecast_filename = PathBuf::new();
            forecast_filename.push("/");
            forecast_filename.push("tmp");
            forecast_filename.push("hourlyForecast.json");
            let forecast_name: String = forecast_filename.to_string_lossy().into_owned();
            write_outfile(&forecast_name, &hourly_forcast);

            // TODO parse out first 4
        }
    }
}
