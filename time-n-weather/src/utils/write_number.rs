pub mod number {

    use crate::utils::numbers::numbers::{ 
        write_zero,
        write_one,
        write_two,
        write_three,
        write_four,
        write_five,
        write_six,
        write_seven,
        write_eight,
        write_nine
    };

    pub fn write(x: u16, y: u16, num: u16) {
        match num {
            0 => write_zero(x, y),
            1 => write_one(x, y),
            2 => write_two(x, y),
            3 => write_three(x, y),
            4 => write_four(x, y),
            5 => write_five(x, y),
            6 => write_six(x, y),
            7 => write_seven(x, y),
            8 => write_eight(x, y),
            9 => write_nine(x, y),
            _ => println!("Something else!"),
        }
    }
}
