use gtk4 as gtk;
use gtk::gio;
use gtk::prelude::*;
use gtk::{Application, ApplicationWindow, Text, TextBuffer};

pub mod builders;
use crate::builders::scrollarea;
use crate::builders::menu;

const APP_ID: &str = "Godura";

struct MainWindow {
    window: ApplicationWindow,
    buffer: TextBuffer,
    position: Text,
}

fn build_window(app: &Application) { //-> MainWindow {

    // Create a new ApplicationWindow tied to the application
    let main_refs: MainWindow = MainWindow {
        window: ApplicationWindow::builder()
            .application(app)
            .title(APP_ID)
            .default_width(600)
            .default_height(400)
            .build(),
        buffer: scrollarea::textarea::create_gtk_buffer(),
        position: Text::new()
    };
        
    // menu bar and scroll text area
    let menu_bar = menu::menubar::create_menu(app, &main_refs.window);
    let scroll_textarea = scrollarea::textarea::build_text_area(main_refs.buffer);

    let main_box = gtk4::Box::builder()
        .orientation(gtk4::Orientation::Vertical)
        .spacing(6)
        .hexpand(true)  // Expand horizontally to fill window
        .vexpand(true)  // Expand vertically to fill window
        .build();
        
    // Create a layout and add the menubar to the window
    let box_layout = gtk4::Box::new(gtk4::Orientation::Vertical, 0);
    box_layout.append(&menu_bar);
    
    main_box.append(&box_layout);
    main_box.append(&scroll_textarea);
    
    main_refs.window.set_child(Some(&main_box));

    main_refs.window.present();

    //return main_refs.clone();
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
    
    //let mut main_refs: MainWindow;
    app.connect_activate(move |app| {
            //let main_refs: MainWindow = 
                build_window(&app);
    });

    //println!("Got {:?}", main_refs.window);

    // Ensure your main window is created/presented here if needed
    /*app.connect_activate(move |app| {
        build_window(app, &buffer);
    });

    let windows = app.windows();

    let mut main_window: gtk::ApplicationWindow;
    println!("Wind {:?}", app);
    for window in windows {
        if let Ok(app_window) = window.downcast::<gtk::ApplicationWindow>() {
            println!("Window found with title: {:?}", app_window.title());
            main_window = app_window;
        }
    }*/

    // 2. Connect the "open" signal
    /*let buff_clone = buffer.clone();
    app.connect_open(|app, files, _hint| {
        build_window(app, &buff_clone);
        println!("Received {} file(s) to open:", files.len());
        for file in files {
            if let Some(path) = file.path() {
                println!("- Opening: {:?}", path);
                let path_string: String = path.to_string_lossy().into_owned();
                let text_data: String = read_in_file(&path_string);
                if let Some(window) = app.active_window() {
                    if let Some(view) = window.child() {
                        println!("Got data and view {:?}", view);
                    }
                }
            }
        }
        println!("Now here, reactivate?");
    });*/

    //app.connect_activate(|_app| {
    // Fallback UI initialization if no files were explicitly requested
    //});

    //   let text = scroll_textarea.child().and_downcast::<gtk4::TextView>();
    //text.buffer().set_text(text_data);
    //}*/
    // Present the window
    //});

    app.run(); //_with_args(&std::env::args().collect::<Vec<String>>());

    println!("App Start {}", APP_ID);
}
