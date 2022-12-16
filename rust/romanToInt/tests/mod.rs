#[cfg(test)]
mod tests {
    use roman_to_int::roman_to_int;
    use roman_to_int::roman_digit_to_int;

    #[test]
    fn invalid_roman_numbers() {
        assert_eq!(true, roman_to_int("2#$^%&&").is_err());
        assert_eq!(true, roman_to_int("not_a_roman").is_err());
        assert_eq!(true, roman_to_int("-").is_err());
    }

    #[test]
    fn invalid_digits() {
        assert_eq!(None, roman_digit_to_int(&'\n'));
        assert_eq!(None, roman_digit_to_int(&'p'));
        assert_eq!(None, roman_digit_to_int(&'-'));
    }

    #[test]
    fn valid_digits() {
        assert_eq!(Some(1), roman_digit_to_int(&'i'));
        assert_eq!(Some(1), roman_digit_to_int(&'I'));
        assert_eq!(Some(5), roman_digit_to_int(&'v'));
        assert_eq!(Some(5), roman_digit_to_int(&'V'));
        assert_eq!(Some(10), roman_digit_to_int(&'x'));
        assert_eq!(Some(10), roman_digit_to_int(&'X'));
        assert_eq!(Some(50), roman_digit_to_int(&'l'));
        assert_eq!(Some(50), roman_digit_to_int(&'L'));
        assert_eq!(Some(100), roman_digit_to_int(&'c'));
        assert_eq!(Some(100), roman_digit_to_int(&'C'));
        assert_eq!(Some(500), roman_digit_to_int(&'d'));
        assert_eq!(Some(500), roman_digit_to_int(&'D'));
        assert_eq!(Some(1000), roman_digit_to_int(&'m'));
        assert_eq!(Some(1000), roman_digit_to_int(&'M'));
    }

    #[test]
    fn valid_entire_numbers() {
        assert_eq!(Ok(0), roman_to_int(""));
        assert_eq!(Ok(1), roman_to_int("I"));
        assert_eq!(Ok(1), roman_to_int("i"));
        assert_eq!(Ok(4), roman_to_int("IV"));
        assert_eq!(Ok(14), roman_to_int("xiv"));
        assert_eq!(Ok(2002), roman_to_int("MMII"));
        assert_eq!(Ok(2112), roman_to_int("MMCXII"));
    }
}
