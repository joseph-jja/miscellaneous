pub mod files {

    use std::fs;
    use std::io;

    pub fn read_in_file(filename: &String) -> String {
        // This returns a Result<String, io::Error>
        let contents =
            fs::read_to_string(filename).expect("Should have been able to read the file");

        return contents;
    }

    pub fn write_outfile(filename: &String, filedata: &String) -> Result<(), io::Error> {
        fs::write(filename, filedata)?;
        Ok(())
    }
}
