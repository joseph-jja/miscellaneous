pub mod textarea {

    use gtk::prelude::*;
    use gtk::{PolicyType, ScrolledWindow, TextBuffer, TextView, WrapMode};
    use gtk4 as gtk;

    use crate::utils::utilities::utilities::get_status_buffer;

    pub const DEFAULT_WIDTH: i32 = 600;
    pub const DEFAULT_HEIGHT: i32 = 400;

    pub fn build_text_area() -> ScrolledWindow {
        let buffer = TextBuffer::builder().build();

        let mut iter = buffer.start_iter();
        let mark = buffer.create_mark(Some("position_mark"), &iter, false);
        buffer.connect_mark_set(move |buffer, _location, mark| {
            //let status_buff = get_status_buffer
            if let Some(mark) = buffer.mark("position_mark") {
                let mut iter = buffer.end_iter();
                let line = iter.line();
                let column = iter.line_offset();
        
                // Update your UI here
                println!("Cursor moved to Line: {}, Column: {}", line, column);
            }
        });

        // 2. Create the TextView widget and assign the buffer
        let text_view = TextView::with_buffer(&buffer);
        //text_view.set_monospace(true); // Useful for code-like text
        text_view.set_wrap_mode(WrapMode::Word);
        // set name
        text_view.set_widget_name("main_text_buffer");

        // 3. Wrap it in a ScrolledWindow to allow scrolling
        let scrolled_window = ScrolledWindow::builder()
            .hscrollbar_policy(PolicyType::Automatic) // Show horizontal bar if needed
            .vscrollbar_policy(PolicyType::Automatic) // Show vertical bar if needed
            .min_content_height(DEFAULT_HEIGHT) // Enforce a starting size
            .min_content_width(DEFAULT_WIDTH)
            .hexpand(true)
            .vexpand(true)
            .child(&text_view)
            .build();

        return scrolled_window;
    }
}
