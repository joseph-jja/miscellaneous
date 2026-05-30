pub mod textarea {

    use crate::gtk;
    use gtk::prelude::*;

    pub fn create_gtk_buffer() -> gtk::TextBuffer {
        // 1. Create a TextBuffer to hold the content
        // don't need return but my thing
        return gtk::TextBuffer::new(None);
    }

    pub fn build_text_area(buffer: &gtk::TextBuffer) -> gtk::ScrolledWindow {
        // 2. Create the TextView widget and assign the buffer
        let text_view = gtk::TextView::with_buffer(buffer);
        //text_view.set_monospace(true); // Useful for code-like text
        text_view.set_wrap_mode(gtk::WrapMode::Word);

        // 3. Wrap it in a ScrolledWindow to allow scrolling
        let scrolled_window = gtk::ScrolledWindow::builder()
            .child(&text_view)
            .hscrollbar_policy(gtk::PolicyType::Never) // Disable horizontal scroll
            .vscrollbar_policy(gtk::PolicyType::Automatic)
            .hexpand(true)
            .vexpand(true)
            .build();

        return scrolled_window;
    }
}
