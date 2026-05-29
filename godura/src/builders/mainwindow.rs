

fn build_window(app: &Application, buffer: &gtk::TextBuffer) {

    // Create a new ApplicationWindow tied to the application
    let window = ApplicationWindow::builder()
        .application(app)
        .title(APP_ID)
        .default_width(600)
        .default_height(400)
        .build();

    // menu bar and scroll text area
    let menu_bar = create_menu(app);
    let buffer2: gtk::TextBuffer = textarea::create_gtk_buffer();
    let scroll_textarea = textarea::build_text_area(&buffer2);

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
    
    window.set_child(Some(&main_box));

    window.present();
}
