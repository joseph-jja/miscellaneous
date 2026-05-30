pub mod textarea {

    use crate::gtk;
    use gtk::prelude::*;

    pub const width: i32 = 600;
    pub const height: i32 = 400;

    pub fn build_text_area() -> gtk::ScrolledWindow {
        let buffer = gtk::TextBuffer::new(None);

        // 2. Create the TextView widget and assign the buffer
        let text_view = gtk::TextView::with_buffer(&buffer);
        //text_view.set_monospace(true); // Useful for code-like text
        text_view.set_wrap_mode(gtk::WrapMode::Word);

        // 3. Wrap it in a ScrolledWindow to allow scrolling
        let scrolled_window = gtk::ScrolledWindow::builder()
            .hscrollbar_policy(gtk4::PolicyType::Automatic) // Show horizontal bar if needed
            .vscrollbar_policy(gtk4::PolicyType::Automatic) // Show vertical bar if needed
            .min_content_height(height) // Enforce a starting size
            .min_content_width(width)
            .hexpand(true)
            .vexpand(true)
            .child(&text_view)
            .build();

        return scrolled_window;
    }
}
