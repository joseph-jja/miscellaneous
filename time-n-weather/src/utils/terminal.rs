pub mod terminal {

    use crossterm::{
        cursor::{MoveTo, Hide, Show},
        execute,
        queue,
        style::{self, Stylize, Print, PrintStyledContent},
        terminal::{Clear, ClearType, EnterAlternateScreen, LeaveAlternateScreen, disable_raw_mode, enable_raw_mode},
    };
    use std::io::{stdout, Write};
    
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
            Print("This text is drawn at a specific coordinate.")
        ).expect("Print failed");

        for x in 0..45 {
            queue!(stdout, MoveTo(10 + x, 5), PrintStyledContent( "█".magenta())).expect("Write failed");
        }
        
        // 4. Render everything to the screen at once
        stdout.flush().expect("Flush failed");
        
        // Pause briefly to view output before restoring terminal state
        std::thread::sleep(std::time::Duration::from_secs(3));
        
        // 5. Clean up terminal state before exiting
        execute!(stdout, Show, LeaveAlternateScreen).expect("Failed to execute again");
    }

    // future will take color
    pub fn draw_box_at_location(x: u16, y: u16) {

        let mut stdout = stdout();

        queue!(stdout, MoveTo(x, y), PrintStyledContent( "█".magenta())).expect("Write failed");
    }

    pub fn flush_stdout() {
        let mut stdout = stdout();
        stdout.flush().expect("Flush failed");
    }

    pub fn destroy_terminal() {
        disable_raw_mode().expect("Failed to disable raw mode");
    }
}





