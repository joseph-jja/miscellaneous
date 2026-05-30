use gtk::gio;
use gtk::prelude::*;
use gtk::{Application, ApplicationWindow, Text, TextBuffer};
use gtk4 as gtk;

pub mod builders;
use crate::builders::menu;
use crate::builders::scrollarea;

const APP_ID: &str = "Godura";

fn build_window(app: &Application) {
    // menu bar and scroll text area
    let menu_bar = menu::menubar::create_menu(app);
    let scroll_textarea = scrollarea::textarea::build_text_area();

    let main_box = gtk4::Box::builder()
        .orientation(gtk4::Orientation::Vertical)
        .spacing(10)
        .hexpand(true) // Expand horizontally to fill window
        .vexpand(true) // Expand vertically to fill window
        .build();

    // Create a layout and add the menubar to the window
    let box_layout = gtk4::Box::new(gtk4::Orientation::Vertical, 0);
    box_layout.append(&menu_bar);

    main_box.append(&box_layout);
    main_box.append(&scroll_textarea);

    let window = ApplicationWindow::builder()
        .application(app)
        .title(APP_ID)
        .default_width(scrollarea::textarea::DEFAULT_WIDTH)
        .default_height(scrollarea::textarea::DEFAULT_HEIGHT)
        .build();

    window.set_child(Some(&main_box));

    window.present();
}

fn main() {
    let args: Vec<String> = std::env::args().collect();

    if args.len() > 0 {
        println!("Got args {} {}!", args.len(), args[0])
    }

    let app = Application::builder()
        .application_id(APP_ID)
        .flags(gio::ApplicationFlags::HANDLES_OPEN)
        .build();


    let windows = app.windows();
    let mut main_window: gtk::ApplicationWindow;
    for window in windows {
        if let Ok(app_window) = window.downcast::<gtk::ApplicationWindow>() {
            println!("Window found with title: {:?}", app_window.title());
            main_window = app_window;
        }
    }

    // 2. Connect the "open" signal
    app.connect_open(|app, files, _hint| {
        build_window(app);
        println!("Received {} file(s) to open:", files.len());
        for file in files {
            if let Some(path) = file.path() {
                println!("- Opening: {:?}", path);
                let path_string: String = path.to_string_lossy().into_owned();
                //let text_data: String = read_in_file(&path_string);
                if let Some(window) = app.active_window() {
                    if let Some(view) = window.child() {
                        println!("Got data and view {:?}", view);
                    }
                }
            }
        }
        println!("Now here, reactivate?");
        //app.connect_activate(build_window);
    });

    app.connect_activate(build_window);
    
    app.run_with_args(&std::env::args().collect::<Vec<String>>());

    println!("App Start {}", APP_ID);
}
