pub mod files {

    use std::fs;
    use std::io;
    use std::sync::{OnceLock, RwLock};

    use gtk::prelude::*;
    use gtk4 as gtk;

    const FILE_HAS_CHANGED: &str = "file changed";
    const FILE_HAS_NOT_CHANGED: &str = "no change";

    fn file_changedindicator() -> &'static RwLock<String> {
        static STRING_LOCK: OnceLock<RwLock<String>> = OnceLock::new();
        STRING_LOCK.get_or_init(|| RwLock::new(String::from(FILE_HAS_NOT_CHANGED)))
    }

    pub fn has_buffer_changed() -> bool {
        {
            let file_change = file_changedindicator().read().unwrap();
            if file_change.as_str() == FILE_HAS_CHANGED {
                return true;
            }
        }
        return false;
    }

    pub fn reset_buffer_change() {
        {
            let mut file_change = file_changedindicator().write().unwrap();
            file_change.clear();
            file_change.push_str(FILE_HAS_CHANGED);
        }
    }

    pub fn set_buffer_change_event(buffer: &gtk::TextBuffer) {
        let is_user_action = std::rc::Rc::new(std::cell::Cell::new(false));

        // Track when user interaction starts
        let user_act_begin_clone = is_user_action.clone();
        buffer.connect_begin_user_action(move |_| {
            user_act_begin_clone.set(true);
        });

        // Track when user interaction ends
        let user_act_end_clone = is_user_action.clone();
        buffer.connect_end_user_action(move |_| {
            user_act_end_clone.set(false);
        });

        // Watch for changes
        buffer.connect_changed(move |_| {
            if is_user_action.get() {
                {
                    let mut file_change = file_changedindicator().write().unwrap();
                    file_change.clear();
                    file_change.push_str(FILE_HAS_CHANGED);
                }
            }
        });
    }

    pub fn read_in_file(filename: &String) -> String {
        // This returns a Result<String, io::Error>
        let contents =
            fs::read_to_string(filename).expect("Should have been able to read the file");

        println!("Open file {:?}", filename);

        return contents;
    }

    pub fn write_outfile(filename: &String, filedata: &String) -> Result<(), io::Error> {
        println!("Saving file {:?}", filename);
        fs::write(filename, filedata)?;
        Ok(())
    }
}
