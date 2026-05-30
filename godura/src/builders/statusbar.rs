pub mod statusbar {


    use gtk4 as gtk;
    use gtk::prelude::*;
    use gtk::{
        TextBuffer,
        TextView
    };
    
    pub fn create_status_bar() {

        let buffer = TextBuffer::builder().build();

        let text_view = TextView::with_buffer(&buffer);
        //text_view.set_monospace(true); // Useful for code-like text
        text_view.set_wrap_mode(WrapMode::Word);
        // set name 
        text_view.set_widget_name("status_bar_buffer");

        return text_view;
    }
}
