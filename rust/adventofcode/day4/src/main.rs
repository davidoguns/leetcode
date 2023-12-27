use std::collections::{HashSet, LinkedList};

struct Card {
    #[warn(dead_code)]
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
                            //Use a simpler strategy to capture whitespace separated numbers. This
                            //also prevents us from having to use any sort of trim()
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

fn get_winning_card_count(cards: &[Card]) -> Vec<u32> {
    let mut winning_counts = Vec::<u32>::new();
    for card in cards {
        let mut num_winning = 0u32;
        for drawn_number in card.drawn_numbers.iter() {
            if card.winning_numbers.contains(&drawn_number) {
                num_winning += 1;
            }
        }
        winning_counts.push(num_winning);
    }
    winning_counts
}

fn calculate_scratchcard_count(cards: &[Card], winning_counts: &[u32]) -> Vec<u32> {
    let mut scratchcards = vec![0; cards.len()];
    for (card_index, winning_count) in winning_counts.iter().enumerate() {
        let scratchcard_bonus = *scratchcards.get(card_index).expect("This can't happen");
        let increment_range = (card_index+1)..(std::cmp::min((card_index+1) + *winning_count as usize, cards.len()));
        for rolling_index in increment_range {
            if let Some(bonus_card) = scratchcards.get_mut(rolling_index) {
                *bonus_card += 1 + scratchcard_bonus;
            } else {
                panic!("Out of bounds access? {rolling_index}, {}", scratchcards.len());
            }
        }
    }
    scratchcards
}

fn calculate_scratchcard_score(scratchcard_counts: &[u32]) -> u32 {
    let mut score = 0u32;
    let mut scratchcard_count_itr = scratchcard_counts.iter();
    while let Some(scratchcard_count) = scratchcard_count_itr.next() {
        score += 1 + scratchcard_count;
    }
    score
}

fn main() {
    // if let Some(cards) = load_cards_from_file("cards.in") {
    if let Some(cards) = load_cards_from_file("cards.in") {
        let winning_counts = get_winning_card_count(&cards);
        let mut sum_of_powers = 0u32;
        for count in &winning_counts {
            sum_of_powers += if *count > 0 { 1 << (*count-1) } else { 0 };
        }
        println!("Sum of powers from all cards is: {sum_of_powers}");

        let scratchcard_counts = calculate_scratchcard_count(&cards, &winning_counts);
        let scratchcard_score: u32 = calculate_scratchcard_score(&scratchcard_counts);

        println!("Scratchcard score is: {scratchcard_score}");
    }
}
