pub mod utilities {

    use gtk4 as gtk;
    use gtk::prelude::*;
    use gtk::{  
        Application,
        Widget,
        TextView,
        TextBuffer
    };

  pub fn find_widget_by_name(parent: &Widget, name: &str) -> Option<Widget> {
      // Check if the current widget matches the name
      if parent.widget_name() == name {
          return Some(parent.clone());
      }
  
      // Traverse children recursively
      let mut iter = parent.first_child();
      while let Some(child) = iter {
          if let Some(found) = find_widget_by_name(&child, name) {
              return Some(found);
          }
          iter = child.next_sibling();
      }
      None
  }

  pub fn get_text_buffer(app: &Application) -> Option<TextBuffer> {

    if let Some(window) = app.active_window() { 
        let app_widget: Widget = window.upcast::<Widget>();
        if let Some(text_widget) = find_widget_by_name(&app_widget, "main_text_buffer") {
            let text_view = text_widget.downcast::<gtk::TextView>()
                .expect("The widget was not a TextView");
            
            let buffer = text_view.buffer();
            return Some(buffer);
        }
    }
    return None;
  }
}
