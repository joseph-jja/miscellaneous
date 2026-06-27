pub mod weather {

    use std::path::PathBuf;

    use serde::{Deserialize, Serialize};
    use serde_json::Value;

    use crate::utils::utils::utils::current_latitude;
    use crate::utils::utils::utils::current_longitude;
    use crate::utils::utils::utils::make_api_request;
    use crate::utils::utils::utils::write_outfile;

    const API_HOSTNAME: &str = "https://api.weather.gov";

    #[derive(Serialize, Deserialize, Clone, Copy, Default, Debug)]
    struct HourlyForecastData {
        startTime: String,
        endTime: String,
        temperature: String,
        temperatureUnit: String,
        windSpeed: String,
        windDirection: String
    };

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
        let filename: String =  output_filename.to_string_lossy().into_owned();
        let _ = write_outfile(&filename, &results);

        let parsed: Value = serde_json::from_str(&results.as_str()).expect("Should have forecast data!");
        if let Some(forecast_url) = parsed.get("properties").and_then(|d| d.get("forecastHourly")) {

            let forecast = forecast_url.to_string().replace('"', "");

            // Print the dynamic object
            println!("Found url: {:?}", forecast);
            
            let hourly_forcast = make_api_request(&forecast);
            
            let mut forecast_filename = PathBuf::new();
            forecast_filename.push("/");
            forecast_filename.push("tmp");
            forecast_filename.push("hourlyForecast.json");
            let forecast_name: String =  forecast_filename.to_string_lossy().into_owned();
            let _ = write_outfile(&forecast_name, &hourly_forcast);

            let hourly_data: Value = serde_json::from_str(&hourly_forcast.as_str()).expect("Should have hourly forecast data!");

            let mut four_hour_forecast: [HourlyForecastData; 4] = [HourlyForecastData::default(); 4];
            if let Some(periods) = hourly_data.get("properties").and_then(|d| d.get("periods")) { 
                for index in 0..4 {
                    let Some(a_period) = periods.get(&index.as_str()) {
                        let hour_data: HourlyForecastData = serde_json::from_str(a_period.as_str()).expect("Could not parse hourly forcast line!");
                        four_hour_forecast[index] = hour_data;
                    }
                }
            }

            // TODO parse out first 4 
            // startTime, endTime, (in 2026-06-29T08:00:00-07:00 => out 08:00:00)
            // temperature, temperatureUnit
            // windSpeed, windDirection
            /*
            {
                "number": 156,
                "name": "",
                "startTime": "2026-06-29T08:00:00-07:00",
                "endTime": "2026-06-29T09:00:00-07:00",
                "isDaytime": true,
                "temperature": 57,
                "temperatureUnit": "F",
                "temperatureTrend": null,
                "probabilityOfPrecipitation": {
                    "unitCode": "wmoUnit:percent",
                    "value": 0
                },
                "dewpoint": {
                    "unitCode": "wmoUnit:degC",
                    "value": 11.666666666666666
                },
                "relativeHumidity": {
                    "unitCode": "wmoUnit:percent",
                    "value": 86
                },
                "windSpeed": "5 mph",
                "windDirection": "SW",
                "icon": "https://api.weather.gov/icons/land/day/sct?size=small",
                "shortForecast": "Mostly Sunny",
                "detailedForecast": ""
            }*/
        }
    }
}
