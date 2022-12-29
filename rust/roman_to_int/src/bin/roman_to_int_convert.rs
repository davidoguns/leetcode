use std::io::{self, Write};
use roman_to_int::roman_to_int;

fn main() -> ! {
    let mut buffer = String::new();
    loop {
        print!("Enter a Roman numeral: ");
        io::stdout().flush().unwrap();
        match io::stdin().read_line(&mut buffer) {
            Ok(_) => {
                let trimmed = buffer.trim().to_uppercase();
                if String::from("q").eq_ignore_ascii_case(&trimmed) ||
                    String::from("quit").eq_ignore_ascii_case(&trimmed) {
                    std::process::exit(0);
                }
                else {
                    match roman_to_int(&trimmed) {
                        Ok(value) => {
                            println!("Value of Roman numeral is: {}", value);
                        },
                        Err(_) => {
                            println!("Input is not a valid Roman numeral!");
                        }
                    }
                }
            },
            Err(e) => {
                println!("Error reading line: {}", e);
            }
        }
        buffer.clear();
    }
}
