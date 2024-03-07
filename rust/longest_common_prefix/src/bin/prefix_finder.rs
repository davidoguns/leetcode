use std::io::{self, Write};
use longest_common_prefix::longest_common_prefix;

fn main() -> ! {
    let mut buffer = String::new();
    loop {
        println!("Enter a comma delimited string to find the longest common prefix for: ");
        io::stdout().flush().unwrap();
        match io::stdin().read_line(&mut buffer) {
            Ok(_) => {
                let trimmed = buffer.trim();
                if String::from("q").eq_ignore_ascii_case(trimmed) ||
                    String::from("quit").eq_ignore_ascii_case(trimmed) {
                    std::process::exit(0);
                }
                else {
                    let input: Vec<&str> = trimmed.split(',').collect();
                    let lcp = longest_common_prefix(&input);

                    println!("Longest common prefix is: {}", lcp);
                }
            },
            Err(e) => {
                println!("Error reading line: {}", e);
            }
        }
        buffer.clear();
    }
}
