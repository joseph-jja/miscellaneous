pub mod utils {

    use std::fs::{read_to_string, write};
    use std::io;
    use std::path::PathBuf;
    use std::sync::{OnceLock, RwLock};

    const USER_AGENT: &str = "Nozilla/1.0 (console; pios x86_32 ) AppleWebKit/537.36 (KHTML, like Gecko but not) xpi/100.1.1";

    #[cfg(windows)]
    pub const LINE_ENDING: &str = "\r\n";

    #[cfg(not(windows))]
    pub const LINE_ENDING: &str = "\n";

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
    pub async fn make_api_request(api_endpoint: &String) -> String {
        let client = reqwest::Client::new();

        // 1. Send the GET request
        let response = client
            .get(api_endpoint)
            .header("User-Agent", USER_AGENT)
            .header("Accept", "application/json")
            .send()
            .await
            .expect("Fetch of data failed");

        // 2. Check if the request was successful
        if response.status().is_success() {
            // 3. Parse the body text
            let body = response.text().await.expect("Get body content failed!");
            //println!("Response body:\n{}", body);
            return body;
        } else {
            println!("Server returned error: {}", response.status());
        }
        return String::from("");
    }

    pub fn format_date(input_in: &String) -> String {
        let input_work: String = input_in
            .split("T")
            .nth(1)
            .clone()
            .unwrap_or(&input_in)
            .to_string();
        let input_out: String = input_work
            .split("-")
            .nth(0)
            .clone()
            .unwrap_or(&input_work)
            .to_string();
        return input_out;
    }

    pub fn write_temp_file(filename: &String, data: &String) {
        let mut output_filename = PathBuf::new();
        output_filename.push("/");
        output_filename.push("tmp");
        output_filename.push(filename);
        let output_name: String = output_filename.to_string_lossy().into_owned();
        let _ = write_outfile(&output_name, &data);
    }
}
