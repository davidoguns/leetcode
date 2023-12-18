use std::fs::File;
use std::vec::Vec;
use std::rc::Rc;
use std::collections::LinkedList;
use std::io::prelude::*;
use std::fmt;

pub enum Color {
    RED = 1,
    GREEN = 2,
    BLUE = 3,
}

impl fmt::Display for Color {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Color::RED => write!(f, "RED"),
            Color::GREEN => write!(f, "GREEN"),
            Color::BLUE => write!(f, "BLUE"),
        }
    }
}

pub struct ColorLimitOrColorOutcome {
    count: u32,
    color: Color
}
pub type Limit = ColorLimitOrColorOutcome;
pub type ColorOutcome = ColorLimitOrColorOutcome;

pub struct GameReveal {
    color_outcomes: LinkedList<ColorOutcome>,
}

pub struct Game {
    game_id: u32,
    power: u32,
    reveals: LinkedList<GameReveal>
}

fn validate_game(limits: &[Limit], outcome: &Game) -> bool {
    for limit in limits {
        for reveal in &outcome.reveals {
            for color_outcome in reveal.color_outcomes.iter() {
                let color_matches = match limit.color  {
                    Color::RED => matches!(color_outcome.color, Color::RED),
                    Color::BLUE => matches!(color_outcome.color, Color::BLUE),
                    Color::GREEN => matches!(color_outcome.color, Color::GREEN),
                };
                if color_matches && (limit.count < color_outcome.count) {
                    // eprintln!("Invalid {}:{} for game ID: {}", color_outcome.color, color_outcome.count, outcome.game_id);
                    return false;
                }
            }
        }
   }
    true
}

//unlike day 1's solution, we're going to separate the load/parse of the 
//input into it's own function. Not that it's necessary because it's trivial
//enough, but hey, we're learning some Rust here and want to run into problems
//and get a solid understanding while doing easy stuff, repeatedly.
// TODO: std::io::Error is not the only error that can occur. Those + parsing can occur.
//       for now, I'm letting parsing error's panic. Will revist.
// Due to the structure of how part 1 was solved, part 2 is more easily done here, or 
// at least most of the work
fn load_game_outcomes_from_file(filename: &str) -> Result<Vec<Rc<Game>>, std::io::Error> {
    let mut outcomes = Vec::<Rc<Game>>::new();
    match File::open(filename) {
        Ok(mut file) => {
            let mut contents = String::new();
            match file.read_to_string(&mut contents) {
                Ok(_) => {
                    for line in contents.trim().lines() {
                        let (game_id_token, game_outcomes) = line.split_once(":").expect("Game ID split failed");
                        let (mut min_red, mut min_green, mut min_blue) = (u32::MIN, u32::MIN, u32::MIN);
                        let id_text = game_id_token.split_once(" ").expect("Game ID value split failed").1;
                        let id = id_text.parse::<u32>().expect("Failed to parse game ID into number");
                        let mut reveal_list = LinkedList::<GameReveal>::new();
                        let reveal_split = game_outcomes.split(";");
                        for reveal in reveal_split {
                            let mut color_outcome_list = LinkedList::<ColorOutcome>::new();
                            for color_and_count_texts in reveal.split(",") {
                                let (count_text, color_word) = color_and_count_texts.trim().split_once(" ")
                                    .expect("Failed to split count and color token");
                                let count = count_text.parse::<u32>().expect("Failed to parse count for color");
                                color_outcome_list.push_back(ColorOutcome { 
                                    count,
                                    color: match color_word {
                                        _ if color_word == "red" => {
                                            min_red = u32::max(min_red, count);
                                            Color::RED
                                        },
                                        _ if color_word == "green" => {
                                            min_green = u32::max(min_green, count);
                                            Color::GREEN
                                        },
                                        _ if color_word == "blue" => {
                                            min_blue = u32::max(min_blue, count);
                                            Color::BLUE
                                        },
                                        _ => panic!("Unrecognized color word!")
                                    }
                                });
                            }
                            reveal_list.push_back(GameReveal {color_outcomes: color_outcome_list});
                        }
                        outcomes.push(Rc::new(Game {
                            game_id: id,
                            reveals: reveal_list,
                            power: min_red * min_green * min_blue
                        }));
                    }
                    Result::Ok(outcomes)
                },
                Err(e) => { 
                    Err(e)
                }
            }
            
        },
        Err(e) => {
            Err(e)
        }
    }
}

fn main() {
    let game_limits = [
        Limit {
            color: Color::RED,
            count: 12,
        },
        Limit {
            color: Color::GREEN,
            count: 13,
        },
        Limit {
            color: Color::BLUE,
            count: 14,
        },
    ];

    let mut valid_games = Vec::<Rc<Game>>::new();
    if let Ok(games) = load_game_outcomes_from_file("game_outcomes.in") {
        let mut game_power_sum = 0u32;
        for game_outcome in games {
            game_power_sum += game_outcome.power;
            println!("Game ID {}, has power: {}", game_outcome.game_id, game_outcome.power);
            if validate_game(&game_limits, &game_outcome) {
                println!("Game ID was valid: {}", game_outcome.game_id);
                valid_games.push(game_outcome);
            }
        }

        //sum up valid game IDs
        let mut game_id_sum = 0u32;
        for game_outcome in valid_games {
            game_id_sum += game_outcome.game_id;
        }

        println!("Game ID sum: {game_id_sum}");
        println!("Game power sum: {game_power_sum}");
    }
    else {
        println!("Could not load game outcomes from file");
    }
}

mod test {
    #![cfg(test)]
    use crate::{Limit, Color, ColorOutcome, Game, GameReveal, validate_game};
    use std::collections::LinkedList;

    #[test]
    pub fn test_validate_game() {
        let game_limits = [
            Limit {
                color: Color::RED,
                count: 2,
            },
            Limit {
                color: Color::GREEN,
                count: 2,
            },
            Limit {
                color: Color::BLUE,
                count: 3,
            },
        ];

        let mut color_outcome_list = LinkedList::<ColorOutcome>::new();
        color_outcome_list.push_back(ColorOutcome {
            color: Color::RED,
            count: 2
        });
        color_outcome_list.push_back(ColorOutcome {
            color: Color::GREEN,
            count: 2
        });
        color_outcome_list.push_back(ColorOutcome {
            color: Color::BLUE,
            count: 3
        });

        let mut game_reveal_list = LinkedList::<GameReveal>::new();
        game_reveal_list.push_back(GameReveal {
            color_outcomes: color_outcome_list
        });

        let game_outcome_1 = Game {
            game_id: 1,
            reveals: game_reveal_list,
            power: 0
        };

        assert_eq!(true, validate_game(&game_limits, &game_outcome_1));
    }
}
