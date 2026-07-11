pub mod terminal {

    use crossterm::{
        cursor::{Hide, MoveTo, Show},
        execute, queue,
        style::{Print, PrintStyledContent, Stylize, ContentStyle, Color},
        terminal::{
            Clear, ClearType, EnterAlternateScreen, LeaveAlternateScreen, disable_raw_mode,
            enable_raw_mode,
        },
    };
    use std::io::{Write, stdout};
    use std::sync::{OnceLock, RwLock};

    fn current_color() -> &'static RwLock<i8> {
        static COLOR_LOCK: OnceLock<RwLock<i8>> = OnceLock::new();
        COLOR_LOCK.get_or_init(|| RwLock::new(0))
    }

    pub fn update_color() {

         let mut color: i8 = 0;
        {
            let color_lock_read = current_color().read().unwrap();
            color = *color_lock_read;
        }

        {
            let mut color_lock_write = current_color().write().unwrap();
            *color_lock_write = if color >= 6 { 0 } else { color + 1 };
        }
    }
    
    fn get_color() -> Color {

        let mut color: i8 = 0;
        {
            let color_lock_read = current_color().read().unwrap();
            color = *color_lock_read;
        }

        return match color {
            0 => Color::Magenta,
            1 => Color::Red,
            2 => Color::Blue,
            3 => Color::Yellow,
            4 => Color::Green,
            5 => Color::Cyan,
            6 => Color::White,
            _ => Color::Magenta
        };
    }
    
    pub fn init_terminal() {
        let mut stdout = stdout();

        enable_raw_mode().expect("Error setting raw mode");
        execute!(stdout, EnterAlternateScreen, Hide).expect("Failed to execute");

        queue!(stdout, Clear(ClearType::All), MoveTo(0, 0)).expect("Move failed");

        queue!(
            stdout,
            PrintStyledContent("Welcome to Crossterm!\r\n".magenta()),
            PrintStyledContent("=====================\r\n".magenta()),
            MoveTo(10, 4),
            PrintStyledContent("If you are seeing this drawn at x=10, y=4 and underlined it works!".magenta())
        )
        .expect("Print failed");

        for x in 0..67 {
            queue!(stdout, MoveTo(10 + x, 5), PrintStyledContent("█".magenta()))
                .expect("Write failed");
        }

        // 4. Render everything to the screen at once
        stdout.flush().expect("Flush failed");

        // Pause briefly to view output before restoring terminal state
        std::thread::sleep(std::time::Duration::from_secs(3));

        // 5. Clean up terminal state before exiting
        execute!(stdout, Show, LeaveAlternateScreen).expect("Failed to execute again");
    }

    pub fn clear_terminal() {
        let mut stdout = stdout();

        enable_raw_mode().expect("Error setting raw mode");
        execute!(stdout, EnterAlternateScreen, Hide).expect("Failed to execute");

        queue!(stdout, Clear(ClearType::All), MoveTo(0, 0)).expect("Move failed");
    }

    pub fn write_text_at(x: u16, y: u16, msg: &str) {
        let mut stdout = stdout();

        let current_color: Color = get_color();

        let style = ContentStyle::new().
            with(current_color);
        
        let content = style.apply(&msg);
        
        queue!(stdout, MoveTo(x, y), PrintStyledContent(content)).expect("Print failed in write_text");
    }

    // future will take color
    pub fn draw_box_at_location(x: u16, y: u16) {

        write_text_at(x, y, "█");
    }

    pub fn sleep_terminal(x: u64) {
        std::thread::sleep(std::time::Duration::from_secs(x));
    }

    pub fn flush_stdout() {
        let mut stdout = stdout();
        stdout.flush().expect("Flush failed");
    }

    pub fn destroy_terminal() {
        disable_raw_mode().expect("Failed to disable raw mode");
    }
}
