use std::fs::File;
use std::io::prelude::*;

fn main() {
    let words_to_digit = [
        ("one", 1u32),
        ("two", 2u32),
        ("three", 3u32),
        ("four", 4u32),
        ("five", 5u32),
        ("six", 6u32),
        ("seven", 7u32),
        ("eight", 8u32),
        ("nine", 9u32),
        ("zero", 0u32),
    ];

    // program written to do the processing while it reads the file.
    match File::open("data.in") {
        Ok(mut file) => {
            let mut contents = String::new();
            if let Ok(_size_read) = file.read_to_string(&mut contents) {
                contents = contents.trim().to_owned();
                let mut running_sum = 0u32;
                for (linenum, line) in contents.lines().enumerate() {
                    let mut first_digit = Option::<u32>::None;
                    let mut second_digit = Option::<u32>::None;
                    let mut char_enum_itr = line.chars().enumerate().into_iter();
                    while let Some(char_tupl) = char_enum_itr.next() {
                        let (char_position, ch) = char_tupl;
                        if ch.is_digit(10) {
                            match first_digit {
                                Some(_x) => {
                                    //already acquired first digit, always replace second
                                    //actually this isn't clear: what if there is only one
                                    //digit in the line? Do we ignore the entire line? Is
                                    //it zero? If it is zero, is the first digit still the
                                    //tens in terms of magnitude?
                                    second_digit = ch.to_digit(10);
                                },
                                None => {
                                    first_digit = ch.to_digit(10);
                                }
                            }
                        } else {
                            let mut word_digit = Option::None;
                            //now check if we have a word spelling out digit
                            for entry in words_to_digit {
                                let split_string = line.split_at(char_position).1;
                                if split_string.starts_with(entry.0) {
                                    word_digit = Some(entry.1);
                                    //we can skip examining the characters that follow once we've
                                    //identified a numerical word
                                    for _i in 1..entry.0.chars().count() {
                                        char_enum_itr.next();
                                    }
                                    break;
                                }
                            } 
                            if let Some(digit) = word_digit {
                                match first_digit {
                                    Some(_x) => {
                                        //already acquired first digit, always replace second
                                        //actually this isn't clear: what if there is only one
                                        //digit in the line? Do we ignore the entire line? Is
                                        //it zero? If it is zero, is the first digit still the
                                        //tens in terms of magnitude?
                                        second_digit = Some(digit);
                                    },
                                    None => {
                                        first_digit = Some(digit);
                                    }
                                }
                            }
                        }
                    }

                    if first_digit.is_some() && second_digit.is_none() {
                        second_digit = Some(first_digit.unwrap());
                    }

                    if first_digit.is_some() && second_digit.is_some() {
                        running_sum += 10 * first_digit.unwrap() + second_digit.unwrap();
                    } else {
                        eprintln!("Line {} does not have two digits specified!", linenum+1);
                    }
                }
                println!("Running sum for the file is: {}", running_sum);
            } else { 
                eprintln!("File contents could not be read. Probably not UTF-8");
            }
        },
        Err(e) => {
            eprintln!("Failed to open file: {}", e);
        }
    }
}
