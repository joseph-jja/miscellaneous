pub mod weather {

    use serde::{Deserialize, Serialize};
    use serde_json::Value;

    use crate::utils::utils::utils::current_latitude;
    use crate::utils::utils::utils::current_longitude;
    use crate::utils::utils::utils::format_date;
    use crate::utils::utils::utils::make_api_request;
    use crate::utils::utils::utils::write_temp_file;
    use crate::utils::utils::utils::read_temp_file;
    use crate::utils::utils::utils::LINE_ENDING;

    use crate::utils::terminal::terminal::write_text_at;

    const API_HOSTNAME: &str = "https://api.weather.gov";

    const HOURLY_FILENAME: &str = "hourly.txt";

    #[derive(Serialize, Deserialize, Default, Debug)]
    struct HourlyForecastData {
        start_time: String,
        end_time: String,
        temperature: String,
        temperature_unit: String,
        wind_speed: String,
        wind_direction: String,
    }

    fn get_main_weather_url() -> String {
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
        return endpoint;
    }

    pub fn get_weather_data() {
        // get the endpoint to call
        let endpoint: String = get_main_weather_url();

        // call api
        let results = make_api_request(&endpoint);

        // write to temp file
        write_temp_file(&String::from("forecast.json"), &results);

        // The data comes back as an object that has properties.period[]
        // and we need to parse out first 4 items of the array and get these values
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

        let parsed: Value =
            serde_json::from_str(&results.as_str()).expect("Should have forecast data!");

        if let Some(forecast_url) = parsed
            .get("properties")
            .and_then(|d| d.get("forecastHourly"))
        {
            let forecast = forecast_url.to_string().replace('"', "");

            // Print the dynamic object
            //println!("Found url: {:?}", forecast);

            let hourly_forcast = make_api_request(&forecast);

            write_temp_file(&String::from("hourlyForecast.json"), &hourly_forcast);

            let hourly_data: Value = serde_json::from_str(&hourly_forcast.as_str())
                .expect("Should have hourly forecast data!");

            let mut generated: String = String::from("");
            //     results.push_str(date + time);
            if let Some(generated_at) = hourly_data
                .get("properties")
                .and_then(|d| d.get("generatedAt"))
            {
                let generated_work: String =
                    generated_at.to_string().replace('"', "").replace("T", " ");
                generated.push_str(&generated_work);
            }

            let mut four_hour_forecast: Vec<HourlyForecastData> = Vec::new();
            if let Some(periods) = hourly_data.get("properties").and_then(|d| d.get("periods")) {
                if let Some(array) = periods.as_array() {
                    for (index, item) in array.iter().enumerate() {
                        if index < 4 {
                            //println!("We got a line of data {:?}", item);
                            let start_time: String =
                                format_date(&String::from(item["startTime"].to_string()));

                            let end_time: String =
                                format_date(&String::from(item["endTime"].to_string()));

                            four_hour_forecast.push(HourlyForecastData {
                                start_time: start_time,
                                end_time: end_time,
                                temperature: item["temperature"].to_string(),
                                temperature_unit: item["temperatureUnit"].to_string(),
                                wind_speed: item["windSpeed"].to_string(),
                                wind_direction: item["windDirection"].to_string(),
                            });
                        } else {
                            break;
                        }
                    }
                }
            }
            //println!("We got me some data {:?}", four_hour_forecast);

            // details =>  (${startTime}-${endTime}): ${period.temperature}${period.temperatureUnit} / ${period.windSpeed} ${period.windDirection} ${os.EOL}`;
            // then add in last updated date and time
            // details => `Last Updated: ${formattedDate} @ ${formattedTime}`;
            let mut hourly_results: String = String::from("Hourly:");
            hourly_results.push_str(LINE_ENDING);
            for item in four_hour_forecast {
                hourly_results.push_str(&item.start_time);
                hourly_results.push_str("-");
                hourly_results.push_str(&item.end_time);
                hourly_results.push_str(": ");
                hourly_results.push_str(&item.temperature);
                hourly_results.push_str(&item.temperature_unit.replace("\"", ""));
                hourly_results.push_str(" / ");
                hourly_results.push_str(&item.wind_speed.replace("\"", ""));
                hourly_results.push_str(" ");
                hourly_results.push_str(&item.wind_direction.replace("\"", ""));
                hourly_results.push_str(LINE_ENDING);
            }
            hourly_results.push_str("Last Updated (GMT):");
            hourly_results.push_str(&generated);
            hourly_results.push_str(LINE_ENDING);
            //println!("Got generated date {:?}", generated);
            //     results.push_str(os.EOL);  // TODO fix this
            write_temp_file(HOURLY_FILENAME, &hourly_results);
            //println!("We got me some data {:?}", results);
        }
    }

    pub fn write_data_to_screen(x: u16, y: u16) {
       // read in hourly file and then write to screen at x
       // y increases x is fixed
       // we write 5 lines
       let data: String = read_temp_file(HOURLY_FILENAME);

       let mut xx: u16 = x; 
       let mut yy: u16 = y; 
       let mut i: u16 = 0;
       
       for line in data.lines() {
           //println!("{:?}", line);
           if i == 1 { 
               xx = x + 4;
           } 
           if i == 5 {
               xx = x;
           }
           write_text_at(xx, yy, line);
           i = i + 1;
           yy = y + i;
       }
    }
}
