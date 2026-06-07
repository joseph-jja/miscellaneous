pub mod statusbar {

    use gtk::prelude::*;
    use gtk::{Application, TextBuffer, TextView, WrapMode};
    use gtk4 as gtk;

    use crate::utils::utilities::utilities::{get_text_buffer, get_status_buffer};

    pub fn create_status_bar() -> TextView {
        let buffer = TextBuffer::builder().build();

        let text_view = TextView::with_buffer(&buffer);
        //text_view.set_monospace(true); // Useful for code-like text
        text_view.set_wrap_mode(WrapMode::Word);
        // set name
        text_view.set_widget_name("status_bar_buffer");

        return text_view;
    }

    pub fn attach_text_position(app: &Application) {

        let status_buff = get_status_buffer(&app);
        let buffer = get_status_buffer(&app);
       
        let mut iter = buffer.start_iter();
        let mark = buffer.create_mark(Some("position_mark"), &iter, false);
        buffer.connect_mark_set(move |buffer, _location, mark| {
            if let Some(mark) = buffer.mark("position_mark") {
                let mut iter = buffer.end_iter();
                let line = iter.line();
                let column = iter.line_offset();

                let position = format!("Line: {}  Column: {}", line, column);
                // Update your UI here
                //println!("Cursor moved to Line: {}, Column: {}", line, column);
            }
        });
    }
}
