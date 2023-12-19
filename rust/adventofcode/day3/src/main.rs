use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;

pub struct PartsData {
    data: Vec<char>,
    columns: usize,
    rows: usize,
}

//this is a raw (x, y) location, and may or may not be valid with respect
//to the loaded parts data. It may be too far left (negative values), it may
//be beyond the right edge in terms of an x value > columns, or it may below
//below the botton or above the top in terms of row
type Location = (i32, i32);
//valid part number locations have valid Locations with respect
//to parts data, but we aren't going crazy with OOP modeling/validation
//on that issue since we will want to represent invalid Location as data
//and check explicitly. Getting a bit lazy using tuples here instead of named 
//fields.
//0 is the value of the number
//1 is the location of the first digit of the number
//2 is the length of characters for the entire number
type PartNumberLocation = (u32, Location, usize);

impl PartsData {
    pub fn get_adjacent_cells(&self, part_num_loc: &PartNumberLocation) -> Vec<Location> {
        let mut adjacent_vec = Vec::<Location>::new();

        //start with the left-most digit, above, below, to the left, diagonal up and down
        let diag_upper_left: Location = (part_num_loc.1.0 - 1, part_num_loc.1.1 - 1);
        if let Some(_) = self.get_index(&diag_upper_left) {
            adjacent_vec.push(diag_upper_left);
        }
        let diag_lower_left: Location = (part_num_loc.1.0 - 1, part_num_loc.1.1 + 1);
        if let Some(_) = self.get_index(&diag_lower_left) {
            adjacent_vec.push(diag_lower_left);
        }
        let left: Location = (part_num_loc.1.0 - 1, part_num_loc.1.1);
        if let Some(_) = self.get_index(&left) {
            adjacent_vec.push(left);
        }

       //iterate through the characters handling above and below
        for shift in 0..(part_num_loc.2) {
            let above: Location = (part_num_loc.1.0 + (shift as i32), part_num_loc.1.1 - 1);
            if let Some(_) = self.get_index(&above) {
                adjacent_vec.push(above);
            }
            let below: Location = (part_num_loc.1.0 + (shift as i32), part_num_loc.1.1 + 1);
            if let Some(_) = self.get_index(&below) {
                adjacent_vec.push(below);
            }
        }

        //start with the right-most digit, above, below, to the right, diagonal up and down
        let diag_upper_right: Location = (part_num_loc.1.0 + part_num_loc.2 as i32, part_num_loc.1.1 - 1);
        if let Some(_) = self.get_index(&diag_upper_right) {
            adjacent_vec.push(diag_upper_right);
        }
        let diag_lower_right: Location = (part_num_loc.1.0 + part_num_loc.2 as i32, part_num_loc.1.1 + 1);
        if let Some(_) = self.get_index(&diag_lower_right) {
            adjacent_vec.push(diag_lower_right);
        }
        let right: Location = (part_num_loc.1.0 + part_num_loc.2 as i32, part_num_loc.1.1);
        if let Some(_) = self.get_index(&right) {
            adjacent_vec.push(right);
        }

        adjacent_vec 
    }

    //ends up unused?
    pub fn get_index(&self, location: &Location) -> Option<usize> {
        if location.1 > 0 && location.1 < self.rows.try_into().unwrap() &&
            location.0 > 0 && location.0 < self.columns.try_into().unwrap() {
            return Some(location.0 as usize + (location.1 as usize * self.columns))
        }
        None
    }
    
    //must call this method on the first character, reading left to right
    pub fn get_entire_part_num(&self, first_ch: char, ch_itr: &mut dyn Iterator<Item = char>, loc: &mut Location)
        -> PartNumberLocation {
        //we need a copy at the first character, because loc will still be used to track
        //as we move character by character reading the entire number
        let part_num_loc = loc.clone();
        // println!("Part num starts at {}, {}", part_num_loc.0, part_num_loc.1);
        let mut value: u32 = first_ch.to_digit(10).expect("Should be a digit");
        let mut length = 1usize;
        while let Some(ch) = ch_itr.next() {
            if ch.is_digit(10) {
                // println!("Value is {value}");
                value = (value * 10) + ch.to_digit(10).expect("Should be a digit");
                length += 1;
                loc.0 += 1;
            } else {
                //number 
                loc.0 += 1;
                break;
            }
        }
        // println!("Part num starts at {}, {}", part_num_loc.0, part_num_loc.1);
        // println!("Part value and length {}, {}", value, length);
        (value, part_num_loc, length)
    }
}

pub fn load_parts_data_from_file(filename: &str) -> Option<(PartsData, Vec<PartNumberLocation>)> {
    match File::open(filename) {
        Ok(mut file) => {
            let mut contents = String::new();
            match file.read_to_string(&mut contents) {
                Ok(_) => {
                    let mut parts_data = PartsData {
                        columns: contents.lines().next()
                            .expect("Could not read first line to determine colums")
                            .len(),
                        rows: contents.lines().count(),
                        data: Vec::<char>::new()
                    };
                    parts_data.data.reserve_exact(parts_data.rows * parts_data.columns);
                    let mut parts_number_locations = Vec::<PartNumberLocation>::new();

                    let mut loc = (0i32, 0i32); //track location as we iterate characters
                    for line in contents.lines() {
                        //insert all characters into this structure
                        for ch in line.chars() {
                            parts_data.data.push(ch);
                        }
                        //second pass, find number (could do it in one pass, but simple)
                        let mut ch_itr = line.chars();
                        loc.0 = 0;
                        while let Some(ch) = ch_itr.next() {
                            if ch.is_digit(10) {
                                let pdl = parts_data.get_entire_part_num(ch, &mut ch_itr, &mut loc);
                               parts_number_locations.push(pdl);
                            }
                            loc.0 += 1;
                        }
                        loc.1 += 1; //increment the row we're tracking
                    }
                    Some((parts_data, parts_number_locations))
                }
                Err(e) => {
                    eprintln!("Error reading file: {e}");
                    None
                }
            }
        },
        Err(e) => {
            eprintln!("Error opening file: {e}");
            None
        }
    }
}

pub fn identify_parts_numbers(data: (PartsData, Vec<PartNumberLocation>)) -> Vec<u32> {
    let mut valid_part_numbers = Vec::<u32>::new();
    'part_num_loop:
    for pnl in data.1 {
            println!("Getting adjacent cells for: {}", pnl.0);
        for adjacent_location in data.0.get_adjacent_cells(&pnl) {
            if let Some(ch) = data.0.data.get(
                        adjacent_location.0 as usize + adjacent_location.1 as usize * data.0.columns) {
                if !ch.is_digit(10) && *ch != '.' {
                    println!("Valid part number: {}; located at ({}, {})", pnl.0, pnl.1.0, pnl.1.1);
                    valid_part_numbers.push(pnl.0);
                    continue 'part_num_loop;
                } else {
                    // println!("Not a valid part number: {}", pnl.0);
                }
            } else {
                panic!("Access out of bounds?")
            }
        }
    }
    valid_part_numbers
}

fn main() {
    if let Some(data) = load_parts_data_from_file("parts.in") {
        let parts_numbers = identify_parts_numbers(data);
        let mut sum = 0u32;
        for part_number in parts_numbers {
            sum += part_number;
        }

        println!("Sum of all parts numbers is: {sum}");
    } else {
        eprintln!("Could not load parts data from file!");
    }
}
