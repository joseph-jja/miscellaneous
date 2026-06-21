pub mod numbers {

    use crate::utils::terminal::terminal::draw_box_at_location;

    // width and height in this case 5x7
    const CLOCK_FONT_WIDTH: i16 = 5;
    const CLOCK_FONT_HEIGHT: i16 = 7;

    pub fn write_zero(x: i16, y: i16) {
        let width: i16 = CLOCK_FONT_WIDTH - 2;
        let height: i16 = CLOCK_FONT_HEIGHT - 2;

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

    pub fn write_one(x: i16, y: i16) {
        let width: i16 = CLOCK_FONT_WIDTH - 2;
        let height: i16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_two(x: i16, y: i16) {
        let width: i16 = CLOCK_FONT_WIDTH - 2;
        let height: i16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_three(x: i16, y: i16) {
        let width: i16 = CLOCK_FONT_WIDTH - 2;
        let height: i16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_four(x: i16, y: i16) {
        let width: i16 = CLOCK_FONT_WIDTH - 2;
        let height: i16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_five(x: i16, y: i16) {
        let width: i16 = CLOCK_FONT_WIDTH - 2;
        let height: i16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_six(x: i16, y: i16) {
        let width: i16 = CLOCK_FONT_WIDTH - 2;
        let height: i16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_seven(x: i16, y: i16) {
        let width: i16 = CLOCK_FONT_WIDTH - 2;
        let height: i16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_eight(x: i16, y: i16) {
        let width: i16 = CLOCK_FONT_WIDTH - 2;
        let height: i16 = CLOCK_FONT_HEIGHT - 2;
    }

    pub fn write_nine(x: i16, y: i16) {
        let width: i16 = CLOCK_FONT_WIDTH - 2;
        let height: i16 = CLOCK_FONT_HEIGHT - 2;
    }
}
