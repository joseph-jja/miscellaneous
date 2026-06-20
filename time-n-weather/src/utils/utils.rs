pub mod utils {

    use std::io;
    use std::fs::{read_to_string, write};
    use std::sync::{OnceLock, RwLock};

    pub fn current_latitude() -> &'static RwLock<String> {
        static STRING_LOCK: OnceLock<RwLock<String>> = OnceLock::new();
        STRING_LOCK.get_or_init(|| RwLock::new(String::from("")))
    }

    pub fn current_longitude() -> &'static RwLock<String> {
        static STRING_LOCK: OnceLock<RwLock<String>> = OnceLock::new();
        STRING_LOCK.get_or_init(|| RwLock::new(String::from("")))
    }

    pub fn open_weathermap_api_key() -> &'static RwLock<String> {
        static STRING_LOCK: OnceLock<RwLock<String>> = OnceLock::new();
        STRING_LOCK.get_or_init(|| RwLock::new(String::from("")))
    }

    pub fn read_in_file(filename: &String) -> String {
        let contents = read_to_string(filename).expect("Could not read file specified!");

        //println!("Open file {:?}", filename);

        return contents;
    }

    pub fn write_outfile(filename: &String, filedata: &String) -> Result<(), io::Error> {
        println!("Saving file {:?}", filename);

        write(filename, filedata)?;
        Ok(())
    }

    #[tokio::main]
    pub async fn make_api_request(api_endpoint: &String)  -> String {

        // 1. Send the GET request
        let response = reqwest::get(api_endpoint).await.expect("Fetch of data failed");

        // 2. Check if the request was successful
        if response.status().is_success() {
            // 3. Parse the body text
            let body = response.text().await.expect("Get body content failed!");
            println!("Response body:\n{}", body);
            return body;
        } else {
            println!("Server returned error: {}", response.status());
        }
         return String::from("");
    }
}
