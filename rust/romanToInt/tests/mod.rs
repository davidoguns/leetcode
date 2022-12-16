#[cfg(test)]
mod tests {
    use roman_to_int::roman_to_int;

    #[test]
    fn not_a_roman() {
        assert_eq!(true, roman_to_int("not_a_roman").is_err());
        assert_eq!(true, roman_to_int("-").is_err());
    }

    #[test]
    fn valid_values() {
        assert_eq!(Ok(0), roman_to_int(""));
        assert_eq!(Ok(1), roman_to_int("I"));
        assert_eq!(Ok(4), roman_to_int("IV"));
    }
}
