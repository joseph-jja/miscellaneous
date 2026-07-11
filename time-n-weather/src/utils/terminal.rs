pub mod terminal {

    use crossterm::{
        cursor::{Hide, MoveTo, Show},
        execute, queue,
        style::{Print, PrintStyledContent, Stylize},
        terminal::{
            Clear, ClearType, EnterAlternateScreen, LeaveAlternateScreen, disable_raw_mode,
            enable_raw_mode,
        },
    };
    use std::io::{Write, stdout};
    use std::sync::{OnceLock, RwLock};

    fn current_color() -> &'static RwLock<String> {
        static STRING_LOCK: OnceLock<RwLock<String>> = OnceLock::new();
        STRING_LOCK.get_or_init(|| RwLock::new(String::from("")))
    }
    
    pub fn init_terminal() {
        let mut stdout = stdout();

        enable_raw_mode().expect("Error setting raw mode");
        execute!(stdout, EnterAlternateScreen, Hide).expect("Failed to execute");

        queue!(stdout, Clear(ClearType::All), MoveTo(0, 0)).expect("Move failed");

        queue!(
            stdout,
            Print("Welcome to Crossterm!\r\n"),
            Print("=====================\r\n"),
            MoveTo(10, 4),
            Print("If you are seeing this drawn at x=10, y=4 and underlined it works!")
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

        queue!(stdout, MoveTo(x, y), Print(&msg)).expect("Print failed in write_text");
    }

    // future will take color
    pub fn draw_box_at_location(x: u16, y: u16) {
        let mut stdout = stdout();

        queue!(stdout, MoveTo(x, y), PrintStyledContent("█".magenta())).expect("Write failed");
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
