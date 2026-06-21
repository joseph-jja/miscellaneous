pub mod terminal {

use crossterm::{
    cursor::{MoveTo, Hide, Show},
    execute,
    queue,
    style::Print,
    terminal::{Clear, ClearType, EnterAlternateScreen, LeaveAlternateScreen, disable_raw_mode, enable_raw_mode},
};
use std::io::{stdout, Write};

pub fn init_terminal() {

  let mut stdout = stdout();
    enable_raw_mode()?;
    execute!(stdout, EnterAlternateScreen, Hide)?;

      queue!(stdout, Clear(ClearType::All), MoveTo(0, 0))?;

  queue!(
        stdout,
        Print("Welcome to Crossterm!\r\n"),
        Print("=====================\r\n"),
        MoveTo(0, 4),
        Print("This text is drawn at a specific coordinate.")
    )?;

    // 4. Render everything to the screen at once
    stdout.flush()?;

    // Pause briefly to view output before restoring terminal state
    std::thread::sleep(std::time::Duration::from_secs(3));

    // 5. Clean up terminal state before exiting
    execute!(stdout, Show, LeaveAlternateScreen)?;
    disable_raw_mode()?;
}

  pub fn destro_terminal() {
    disable_raw_mode()?;
  }
}
