pub mod numbers {

    use crate::utils::terminal::terminal::draw_box_at_location;

    // width and height in C the default was 5x7
    // then in C preprocessor direcives would override
    // not in the mood to use rust macro for this just yet
    // width and height in this case 11x15
    const CLOCK_FONT_WIDTH: u16 = 11;
    const CLOCK_FONT_HEIGHT: u16 = 15;

    pub fn write_zero(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 1;
        let height: u16 = CLOCK_FONT_HEIGHT - 1;

        let mut xp: u16 = x;
        let mut yp: u16 = y;

        // draw top and bottom of 0
        xp += 1;
        for _ in 0..width -1 {
            draw_box_at_location(xp, yp);
            draw_box_at_location(xp, yp + height);
            xp += 1;
        }

        yp += 1;
        for _ in 0..height - 1 {
            xp = x;
            draw_box_at_location(xp, yp);
            xp += width;
            draw_box_at_location(xp, yp);
            yp += 1;
        }
    }

    pub fn write_one(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH-1;
        let height: u16 = CLOCK_FONT_HEIGHT - 1;

        let mut xp: u16 = x;
        let mut yp: u16 = y;

        // move to the left width 
        xp += width;
        for _ in 0..height {
            draw_box_at_location(xp, yp);
            yp += 1;
        }
        // one more block needed
        draw_box_at_location(xp, yp);
    }

    pub fn write_two(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH;
        let height: u16 = CLOCK_FONT_HEIGHT -1;

        let mut xp: u16 = x;
        let mut yp: u16 = y;

        let top: u16 = yp;
        let middle: u16 = y + (height / 2);
        let bottom: u16 = y + height;

       draw_box_at_location(xp, top);
        xp += 1;
        for _ in 0..width - 2 {
            draw_box_at_location(xp, top);
            draw_box_at_location(xp, middle);
            draw_box_at_location(xp, bottom);
            xp += 1;
        }
        draw_box_at_location(xp, bottom);
 
        xp = x + width - 1;
        yp = top + 1;
        for _ in 0..middle - 3 {
            draw_box_at_location(xp, yp);
            yp += 1;
        }

        xp = x;
        yp = middle + 1;
        for _ in middle..height +1 {
            draw_box_at_location(xp, yp);
            yp += 1;
        }
    }
    
    pub fn write_three(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH;
        let height: u16 = CLOCK_FONT_HEIGHT;

        let mut xp: u16 = x;
        let mut yp: u16 = y;

        let top: u16 = yp;
        let middle: u16 = y + (height / 2);
        let bottom: u16 = y + height;

       xp = x;
       draw_box_at_location(xp, top);
       draw_box_at_location(xp, bottom);
       xp += 1;
        for _ in 0..width - 2 {
            draw_box_at_location(xp, top);
            draw_box_at_location(xp, middle);
            draw_box_at_location(xp, bottom);
            xp += 1;
        }
 
        xp = x + width - 1;
        yp = top + 1;
        for _ in 0..middle - 3 {
            draw_box_at_location(xp, yp);
            yp += 1;
        }

        xp = x + width - 1;
        yp = middle + 1;
        for _ in middle..height +1 {
            draw_box_at_location(xp, yp);
            yp += 1;
        }
    }

    pub fn write_four(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;

        let mut xp: u16 = x;
        let mut yp: u16 = y;

        let middle: u16 = y + (height / 2);

        // draw left
        xp = x;
        yp = y;
        for _ in 0..middle - 1 {
            draw_box_at_location(xp, yp);
            yp += 1;
        }

        // draw middle 
        xp = x + 1;
        yp = middle + 1;
        for _ in 0..width  {
            draw_box_at_location(xp, yp);
            xp += 1;
        }

        // draw right
        xp = x + width;
        yp = y;
        for _ in 0..height {
            draw_box_at_location(xp, yp);
            yp += 1;
        }
        draw_box_at_location(xp, yp);
        draw_box_at_location(xp, yp);
    }

    pub fn write_five(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH;
        let height: u16 = CLOCK_FONT_HEIGHT;

        let mut xp: u16 = x;
        let mut yp: u16 = y;

        let top: u16 = yp;
        let middle: u16 = y + (height / 2);
        let bottom: u16 = y + height;

        draw_box_at_location(xp, bottom);
        xp += 1;
        for _ in 0..width - 2 {
            draw_box_at_location(xp, top);
            draw_box_at_location(xp, middle);
            draw_box_at_location(xp, bottom);
            xp += 1;
        }
       draw_box_at_location(xp, top);
 
        xp = x;
        yp = top + 1;
        for _ in 0..middle - 3 {
            draw_box_at_location(xp, yp);
            yp += 1;
        }

        xp = x + width - 1;
        yp = middle + 1;
        for _ in middle..height +1 {
            draw_box_at_location(xp, yp);
            yp += 1;
        }
    }

    pub fn write_six(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;

        let mut xp: u16 = x;
        let mut yp: u16 = y;

        draw_box_at_location(xp, yp);

        for _ in 0..width {
            xp += 1;
            draw_box_at_location(xp, yp);
        }
        xp += 1;
        draw_box_at_location(xp, yp);

        for _ in 0..height {
            xp = x;
            yp += 1;
            draw_box_at_location(xp, yp);
        }

        xp = x;
        yp += 1;
        draw_box_at_location(xp, yp);

        for _ in 0..width {
            xp += 1;
            draw_box_at_location(xp, yp);
        }
        xp += 1;
        draw_box_at_location(xp, yp);

        for _ in 0..height {
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

        for _ in 0..width {
            xp += 1;
            draw_box_at_location(xp, yp);
        }
        xp += 1;
        draw_box_at_location(xp, yp);
    }

    pub fn write_seven(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;

        let mut xp: u16 = x;
        let mut yp: u16 = y;

        draw_box_at_location(xp, yp);

        for _ in 0..width {
            xp += 1;
            draw_box_at_location(xp, yp);
        }
        xp += 1;
        draw_box_at_location(xp, yp);

        xp = x;
        xp += width;
        xp += 1;
        for _ in 0..height {
            yp += 1;
            draw_box_at_location(xp, yp);
        }

        xp = x;
        yp += 1;
        xp += width;
        xp += 1;
        draw_box_at_location(xp, yp);
    }

    pub fn write_eight(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;

        let mut xp: u16 = x;
        let mut yp: u16 = y;

        draw_box_at_location(xp, yp);

        for _ in 0..width {
            xp += 1;
            draw_box_at_location(xp, yp);
        }
        xp += 1;
        draw_box_at_location(xp, yp);

        for _ in 0..height {
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

        for _ in 0..width {
            xp += 1;
            draw_box_at_location(xp, yp);
        }
        xp += 1;
        draw_box_at_location(xp, yp);

        for _ in 0..height {
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

        for _ in 0..width {
            xp += 1;
            draw_box_at_location(xp, yp);
        }
        xp += 1;
        draw_box_at_location(xp, yp);
    }

    pub fn write_nine(x: u16, y: u16) {
        let width: u16 = CLOCK_FONT_WIDTH - 2;
        let height: u16 = CLOCK_FONT_HEIGHT - 2;

        let mut xp: u16 = x;
        let mut yp: u16 = y;

        draw_box_at_location(xp, yp);

        for _ in 0..width {
            xp += 1;
            draw_box_at_location(xp, yp);
        }
        xp += 1;
        draw_box_at_location(xp, yp);

        for _ in 0..height {
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

        for _ in 0..width {
            xp += 1;
            draw_box_at_location(xp, yp);
        }
        xp += 1;
        draw_box_at_location(xp, yp);

        xp = x;
        xp += width;
        xp += 1;
        for _ in 0..height {
            yp += 1;
            draw_box_at_location(xp, yp);
        }

        xp = x;
        yp += 1;
        draw_box_at_location(xp, yp);

        for _ in 0..width {
            xp += 1;
            draw_box_at_location(xp, yp);
        }
        xp += 1;
        draw_box_at_location(xp, yp);
    }
}
