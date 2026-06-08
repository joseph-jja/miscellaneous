pub mod statusbar {

    use gtk::glib;
    use gtk::prelude::*;
    use gtk::{Application, TextBuffer, TextView, WrapMode};
    use gtk4 as gtk;
    use std::sync::mpsc;

    use crate::utils::utilities::utilities::{get_status_buffer, get_text_buffer};

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
        let buffer = get_text_buffer(&app).unwrap();
        let status_buff = get_status_buffer(&app).unwrap();

        let (sender, receiver) = mpsc::channel::<String>();

        glib::idle_add_local(glib::clone!(
            #[strong]
            status_buff,
            move || {
                // Check if a message has arrived without blocking the UI thread loop
                while let Ok(fmt_position) = receiver.try_recv() {
                    status_buff.set_text(&fmt_position);
                }
                // Return ControlFlow::Continue to keep this background receiver check active
                glib::ControlFlow::Continue
            }
        ));

        buffer.connect_notify(Some("cursor-position"), move |buffer, _| {
            // Get the updated character offset (0-indexed from the start)
            let cursor_pos = buffer.property::<i32>("cursor-position");

            // Convert the character offset to a TextIter if you need to calculate line/column numbers
            let iter = buffer.iter_at_offset(cursor_pos);
            let line = iter.line();
            let column = iter.line_offset();
            let fmt_position = format!("Line: {}  Column: {}", line, column);

            //println!("Cursor moved to Line: {}, Column: {}", line, column);
            let _ = sender.send(fmt_position);
        });
    }
}
