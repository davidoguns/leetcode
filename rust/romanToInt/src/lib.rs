use thiserror::Error;

#[derive(Error, Debug, PartialEq, Eq)]
pub enum ConversionError {
    #[error("Invalid characters in Roman numeral string")]
    InvalidRomanNumber,
}

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
                if let Some(next_value) = roman_digit_to_int(next_char) {
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
        'I' => Some(1),
        'V' => Some(5),
        'X' => Some(10),
        'L' => Some(50),
        'C' => Some(100),
        'D' => Some(500),
        'M' => Some(1000),
        _ => None
    }
}
