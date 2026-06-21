pub mod numbers {

    use crate::utils::terminal::terminal::draw_box_at_location;

    // width and height in C the default was 5x7
    // then in C preprocessor direcives would override
    // not in the mood to use rust macro for this just yet
    // width and height in this case 11x15
    const CLOCK_FONT_WIDTH: u16 = 11;
    const CLOCK_FONT_HEIGHT: u16 = 15;

    pub fn write_zero(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;

        let mut xp: u16 = x;
        let mut yp: u16 = y;

        let mut i: i8;

        draw_box_at_location(xp, yp);
        for i in 0..width {
            xp += 1;
            draw_box_at_location(xp, yp);
        }
        xp += 1;
        draw_box_at_location(xp, yp);
        
        for i in 0..height {
            xp = x;
            yp += 1;
            draw_box_at_location(xp, yp);
            xp += width;
            xp += 1;
            draw_box_at_location(xp, yp);
        }

        xp = x;
        yp += 1;
        draw_box_at_location(xp, yp);
        for i in 0..width {
            xp += 1;
            draw_box_at_location(xp, yp);
        }
        xp += 1;
        draw_box_at_location(xp, yp);
    }

    pub fn write_one(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_two(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_three(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_four(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_five(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_six(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_seven(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_eight(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_nine(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;
    }
}
