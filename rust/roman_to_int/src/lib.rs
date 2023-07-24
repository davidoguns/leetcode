use thiserror::Error;

#[derive(Error, Debug, PartialEq, Eq)]
pub enum ConversionError {
    #[error("Invalid characters in Roman numeral string")]
    InvalidRomanNumber,
}

/** 
 * https://leetcode.com/problems/roman-to-integer/
 *
 * Incompleteness here is that there is no actual checking that the Roman numeral
 * digits are being used in proper order. It accepts input like "IIMM" and thinks
 * it's 2000, when it's really invalid.
 */
pub fn roman_to_int(input: &str) -> Result<i32, ConversionError> {
    let mut cumulation: i32 = 0;
    let mut skip = false;
    let character_vec: Vec<char> = input.chars().collect();

    for (index, c) in character_vec.iter().enumerate() {
        if skip { skip = false; continue };
        let mut to_add: i32;
        if let Some(value) = roman_digit_to_int(&c) {
            to_add = value;
            if let Some(next_char) = character_vec.get(index+1) {
                if let Some(next_value) = roman_digit_to_int(&next_char) {
                    if next_value > value { //unspecific generalization of prefixes
                        to_add = next_value - value;
                        skip = true;
                    }
                }
                else {
                    return Err(ConversionError::InvalidRomanNumber)
                }
            }
        }
        else {
            return Err(ConversionError::InvalidRomanNumber)
        }
        cumulation += to_add;
    }
    Ok(cumulation)
}

pub fn roman_digit_to_int(digit: &char) -> Option<i32> {
    match digit {
        'I' | 'i' => Some(1),
        'V' | 'v' => Some(5),
        'X' | 'x' => Some(10),
        'L' | 'l' => Some(50),
        'C' | 'c' => Some(100),
        'D' | 'd' => Some(500),
        'M' | 'm' => Some(1000),
        _ => None
    }
}
