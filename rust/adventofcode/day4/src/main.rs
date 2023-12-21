use std::collections::{HashSet, LinkedList};

struct Card {
    id: u32,
    winning_numbers: HashSet<u32>,
    drawn_numbers: LinkedList<u32>
}

fn load_cards_from_file(filename: &str) -> Option<Vec<Card>> {
    use std::fs::File;
    use std::io::prelude::*;
    use regex::Regex;

    let mut cards = Vec::<Card>::new();

    match File::open(filename) {
        Ok(mut file) => {
            //match the whole line, use captures for each part
            // let line_regex = Regex::new(r"^Card\s+(\d+):\s((\d+)\s+)+\|((\d+)\s+)$").unwrap();
            let line_regex = Regex::new(r"^Card\s+(\d+):\s+(.*)\s+\|\s+(.*)$").unwrap();
            let mut contents = String::new();
            match file.read_to_string(&mut contents) {
                Ok(_) => {
                    for (line_num, line) in contents.lines().enumerate() {
                        if let Some(captures) = line_regex.captures(line) {
                            if captures.len() != 4 {
                                eprintln!("Line number {} does not have the right number of capture groups!", line_num+1);
                                continue;
                            }
                            let id:u32 = captures.get(1).unwrap().as_str().parse().expect("Could not parse card ID");
                            let winning_numbers_str = captures.get(2).unwrap().as_str();
                            let mut winning_numbers = HashSet::<u32>::new();
                            for num in winning_numbers_str.split_whitespace() {
                                winning_numbers.insert(num.parse().expect("Winning number can't be parsed as a number."));
                            }

                            let  drawn_numbers_str = captures.get(3).unwrap().as_str();
                            let mut drawn_numbers = LinkedList::<u32>::new();
                            for num in drawn_numbers_str.split_whitespace() {
                                drawn_numbers.push_back(num.parse().expect("Drawn number can't be parsed as a number."));
                            }
                            cards.push(Card {id, winning_numbers, drawn_numbers});
                        }
                        else {
                            eprintln!("Line number {} does not match expected pattern!", line_num+1);
                            continue;
                        }
                    }
                    Some(cards)
                },
                Err(e) => {
                    eprintln!("Failed to read file to string: {e}");
                    None
                }
            }
        },
        Err(e) => {
            eprintln!("Failed to open file: {e}");
            None
        }
    }
}

fn get_powers_from_cards(cards: &Vec<Card>) -> Vec<u32> {
    let mut powers = Vec::<u32>::new();
    for card in cards {
        let mut num_winning = 0u32;
        for drawn_number in card.drawn_numbers.iter() {
            if card.winning_numbers.contains(&drawn_number) {
                num_winning += 1;
            }
        }
        let power = if num_winning > 0 { 1 << (num_winning-1) } else { 0 };
        println!("Power of card {} is {}", card.id, power);
        powers.push(power);
    }
    powers
}

fn main() {
    if let Some(cards) = load_cards_from_file("cards.in") {
        let powers = get_powers_from_cards(&cards);
        let mut sum_of_powers = 0u32;
        for power in powers {
            sum_of_powers += power;
        }

        println!("Sum of powers from all cards is: {sum_of_powers}");
    }
}
