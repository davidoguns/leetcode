
pub fn longest_common_prefix(strs: &[&str]) -> String {
    if let Some(first_string) = strs.get(0) {
        let mut split_off_idx = first_string.chars().count();
        'string_iteration: for s in strs.iter().skip(1) {
            let mut char_idx: usize = 0;
            let mut first_string_citr = first_string.chars().into_iter();
            for character in s.chars() {
                //don't compare more characters than the current longest match
                if char_idx > split_off_idx {
                    continue 'string_iteration;
                }
                //if there is a next character in the current longest match
                if let Some(nth_char) = first_string_citr.next() {
                    if nth_char != character {
                        split_off_idx = char_idx;
                        continue 'string_iteration;
                    }
                }
                char_idx += 1;
            }
            //if current string was fully iterated over, and is shorter
            //than the prior match, then shorten the match
            if char_idx < split_off_idx {
                split_off_idx = char_idx;
            }
        }
        first_string.chars().into_iter().take(split_off_idx).collect()
    }
    else { 
        "".to_string()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_prefixes() {
        assert_eq!("a", longest_common_prefix(&["ab", "a"]));
        assert_eq!("a", longest_common_prefix(&["a", "ab"]));
        assert_eq!("ab", longest_common_prefix(&["abcd", "ab", "abdcdef"]));
        assert_eq!("abcd", longest_common_prefix(&["abcd", "abcd", "abcd"]));
        assert_eq!("", longest_common_prefix(&["abcd", "bc", "abdcdef"]));
        assert_eq!("", longest_common_prefix(&["abdcdef", "abdcf", ""]));
    }
}
