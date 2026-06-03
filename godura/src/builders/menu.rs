pub mod menubar {

    use std::sync::{OnceLock, RwLock};

    use gtk::prelude::*;
    use gtk::{gio, Application, FileDialog, PopoverMenuBar};
    use gtk4 as gtk;

    use crate::utils::files::files::{read_in_file, write_outfile};
    use crate::utils::utilities::utilities::get_text_buffer;

    pub fn current_filename_string() -> &'static RwLock<String> {
        static STRING_LOCK: OnceLock<RwLock<String>> = OnceLock::new();
        STRING_LOCK.get_or_init(|| RwLock::new(String::from("")))
    }

    fn create_file_open_dialog(app: &Application) {
        let file_dialog = FileDialog::builder()
            .title("Select a File")
            .modal(true)
            .build();

        if let Some(window) = app.active_window() {
            let app_clone = app.clone();
            file_dialog.open(Some(&window), gio::Cancellable::NONE, move |result| {
                // Evaluate the operation within the callback closure
                match result {
                    Ok(file) => {
                        let filename = file.path().unwrap().to_string_lossy().into_owned();
                        if let Some(buffer) = get_text_buffer(&app_clone) {
                            println!("User selected file: {:?}", filename);
                            let text_data: String = read_in_file(&filename);
                            buffer.set_text(&text_data);
                            {
                                let mut open_filename = current_filename_string().write().unwrap();
                                open_filename.clear();
                                open_filename.push_str(&filename);
                            }
                        }
                    }
                    Err(err) => {
                        println!("Dialog dismissed or failed: {:?}", err);
                    }
                }
            });
        }
    }

    fn save_file(app: &Application) {
        if let Some(buffer) = get_text_buffer(&app) {
            let (start, end) = buffer.bounds();
            let filetext = String::from(buffer.text(&start, &end, false));
            {
                let filename = current_filename_string().read().unwrap();
                if filename.len() > 0 {
                    let _ = write_outfile(&filename, &filetext);
                }
            }
        }
    }

    fn create_save_as_dialog(app: &Application) {
        let file_dialog = FileDialog::builder()
            .title("Select a File")
            .modal(true)
            .build();

        if let Some(window) = app.active_window() {
            let app_clone = app.clone();
            file_dialog.save(Some(&window), gio::Cancellable::NONE, move |result| {
                // Evaluate the operation within the callback closure
                match result {
                    Ok(file) => {
                        let filename = file.path().unwrap().to_string_lossy().into_owned();
                        {
                            let mut open_filename = current_filename_string().write().unwrap();
                            open_filename.clear();
                            open_filename.push_str(&filename);
                        }
                        if let Some(buffer) = get_text_buffer(&app_clone) {
                            save_file(&app_clone);
                        }
                    }
                    Err(err) => {
                        println!("Dialog dismissed or failed: {:?}", err);
                    }
                }
            });
        }
    }

    pub fn create_menu(app: &Application) -> PopoverMenuBar {
        let file_menu = gio::Menu::new();
        file_menu.append(Some("New"), Some("app.New"));
        file_menu.append(Some("New Window"), Some("app.NewWindow"));
        file_menu.append(Some("Open..."), Some("app.Open"));
        file_menu.append(Some("Save"), Some("app.Save"));
        file_menu.append(Some("Save As..."), Some("app.SaveAs"));
        file_menu.append(Some("Quit"), Some("app.Quit"));

        let edit_menu = gio::Menu::new();
        edit_menu.append(Some("Undo"), Some("app.Undo"));
        edit_menu.append(Some("Redo"), Some("app.Redo"));
        edit_menu.append(Some("Cut"), Some("app.Cut"));
        edit_menu.append(Some("Copy"), Some("app.Copy"));
        edit_menu.append(Some("Paste"), Some("app.Paste"));

        let search_menu = gio::Menu::new();
        search_menu.append(Some("Find"), Some("app.Find"));
        search_menu.append(Some("Replace"), Some("app.Replace"));
        search_menu.append(Some("Replace All"), Some("app.ReplaceAll"));

        let menubar_menu = gio::Menu::new();
        menubar_menu.append_submenu(Some("File"), &file_menu);
        menubar_menu.append_submenu(Some("Edit"), &edit_menu);
        menubar_menu.append_submenu(Some("Search"), &search_menu);

        let open_app_clone = app.clone();
        let open_action = gio::SimpleAction::new("Open", None);
        open_action.connect_activate(move |_, _| {
            create_file_open_dialog(&open_app_clone);
        });
        app.add_action(&open_action);

        let saveas_app_clone = app.clone();
        let saveas_action = gio::SimpleAction::new("SaveAs", None);
        saveas_action.connect_activate(move |_, _| {
            create_save_as_dialog(&saveas_app_clone);
        });
        app.add_action(&saveas_action);

        let save_app_clone = app.clone();
        let save_action = gio::SimpleAction::new("Save", None);
        save_action.connect_activate(move |_, _| {
            save_file(&save_app_clone);
        });
        app.add_action(&save_action);

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
}
