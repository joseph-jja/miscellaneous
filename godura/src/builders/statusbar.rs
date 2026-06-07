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

        let status_buff = get_status_buffer(&app).unwrap();
        let buffer = get_text_buffer(&app).unwrap();
        let mut iter = buffer.start_iter();
        let mark = buffer.create_mark(Some("position_mark"), &iter, false);
        buffer.connect_changed(move |buffer| {
            println!("Changed made");
            if let Some(mark) = buffer.mark("position_mark") {
                let mut iter = buffer.end_iter();
                buffer.move_mark(&mark, &iter);
                let line = iter.line();
                let column = iter.line_offset();

                let fmt_position = format!("Line: {}  Column: {}", line, column);
                let position = fmt_position.as_str();
                println!("Mark found {:?}", position);
                status_buff.set_text(&position);
            }
        });

        /*buffer.connect_notify(Some("cursor-position"), |buffer, _| {
            // Get the updated character offset (0-indexed from the start)
            let cursor_pos = buffer.property::<i32>("cursor-position");
            
            // Convert the character offset to a TextIter if you need to calculate line/column numbers
            let mut iter = buffer.iter_at_offset(cursor_pos);
            let line = iter.line();
            let column = iter.line_offset();
            let fmt_position = format!("Line: {}  Column: {}", line, column);
            let position = fmt_position.as_str();
            status_buff.set_text(&position);
            //println!("Cursor moved to Offset: {}, Line: {}, Column: {}", cursor_pos, line, col);
        });*/
    }
}
