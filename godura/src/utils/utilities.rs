pub mod utilities {

  use crate::gtk;
  use gtk::prelude::*;

  pub fn find_widget_by_name(parent: &gtk::Widget, name: &str) -> Option<gtk::Widget> {
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
}
