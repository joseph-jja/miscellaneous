pub mod weather {

    use crate::utils::utils::utils::current_latitude;
    use crate::utils::utils::utils::current_longitude;
    use crate::utils::utils::utils::make_api_request;

    const RELOAD: int = 1000 * 60 * 60;
    const API_HOSTNAME: String = "https://api.weather.gov";

    //DISCOVER_ENDPOINT = (latitude, longitude) => `/points/${latitude},${longitude}`;

    pub fn get_weather_data() {
        let endpoint: String = API_HOSTNAME;
        endpoint.push_str("/points/");

        {
            let latitude = current_latitude().read().unwrap();
            let borrowed_str: &str = &latitude;
            endpoint.push_str(borrowed_str);
        }
        {
            let mut latitude = current_longitude().read().unwrap();
            let borrowed_str: &str = &latitude;
            endpoint.push_str(borrowed_str);
        }
    }
}
