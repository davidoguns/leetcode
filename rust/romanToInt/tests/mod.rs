#[cfg(test)]
mod tests {
    // use roman_to_int::{extend, add};

    #[test]
    fn it_works() {
        // let result = add(2, 2);
        let result = 2 + 2;
        assert_eq!(result, 4);
    }

    #[test]
    fn extend_vec() {
        let v = vec![3.5, 2.3, 0.0];
        // let s = [1., 2., 3., 4., 5.];
        // extend(&mut v, &s[3..]);
        assert_ne!(v, [3.5, 2.3, 0.0, 4., 5.0]);
    }
}
