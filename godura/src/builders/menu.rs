pub mod menubar {

    use gtk4 as gtk;
    use gtk::prelude::*;
    use gtk::{
        gio,
        Application,
        ApplicationWindow,
        FileDialog,
        PopoverMenuBar,
    };
    use crate::utils::utilities::utilities::get_text_buffer;
    use crate::utils::files::files::read_in_file;
    
    pub fn create_file_dialog(window: &ApplicationWindow) {

        let dialog = FileDialog::builder()
            .title("Select a File")
            .modal(true)
            .build();

        dialog.open(Some(window), gio::Cancellable::NONE, move |result| {
            match result {
                Ok(file) => {
                    // file is a gio::File object
                    if let Some(path) = file.path() {
                        if let Some(buffer) = get_text_buffer(&window) {
                            println!("Selected file path: {:?}", path);
                        }
                    }
                }
                Err(err) => {
                    println!("Dialog cancelled or closed: {}", err);
                }
            }
        });
    }

    pub fn create_menu(app: &Application) -> PopoverMenuBar {
        let file_menu = gio::Menu::new();
        file_menu.append(Some("New..."), Some("app.New"));
        file_menu.append(Some("Open..."), Some("app.Open"));
        file_menu.append(Some("Save"), Some("app.Save"));
        file_menu.append(Some("Save As..."), Some("app.SaveAs"));
        file_menu.append(Some("Quit"), Some("app.Quit"));

        let edit_menu = gio::Menu::new();
        edit_menu.append(Some("Cut"), Some("app.New"));
        edit_menu.append(Some("Copy"), Some("app.Open"));
        edit_menu.append(Some("Paste"), Some("app.Save"));

        let search_menu = gio::Menu::new();

        let menubar_menu = gio::Menu::new();
        menubar_menu.append_submenu(Some("File"), &file_menu);
        menubar_menu.append_submenu(Some("Edit"), &edit_menu);
        menubar_menu.append_submenu(Some("Search"), &search_menu);

        if let Some(window) = app.active_window() { 
            let win = window.clone();
            let open_action = gio::SimpleAction::new("Open", None);
            open_action.connect_activate(move |_ ,_| {
                create_file_dialog(&win);
            });
            app.add_action(&open_action);
        }
        
        //let save_action = gio::SimpleAction::new("Save", None);
        //let saveas_action = gio::SimpleAction::new("Save As...", None);

        let app_clone = app.clone();
        let quit_action = gio::SimpleAction::new("Quit", None);
        quit_action.connect_activate(move |_, _| {
            app_clone.quit();
        });
        // Add to application or window
        app.add_action(&quit_action);

        // 3. Create the PopoverMenuBar from the MenuModel
        let menu_model: gio::MenuModel = menubar_menu.into();
        let menu_bar = PopoverMenuBar::from_model(Some(&menu_model));

        return menu_bar;
    }

    /* fn open_file_dialog(window: &Window) {
        let dialog = FileDialog::builder()
            .title("Open File")
            .modal(true)
            .build();

        // Use open_future for an async/await flow
        dialog.open(Some(window), None::<&gio::Cancellable>, move |result| {
            if let Ok(file) = result {
                let path = file.path().expect("Failed to get path");
                println!("Selected file: {:?}", path);
            }
        });
    }*/
}
