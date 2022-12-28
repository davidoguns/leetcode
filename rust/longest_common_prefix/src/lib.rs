pub fn longest_common_prefix(strs: &[&str]) -> String {
    if let Some(first_string) = strs.get(0) {
        let mut split_off_idx = first_string.chars().count();
        'string_iteration: for (string_index, s) in strs.iter().enumerate() {
            match string_index {
                0 => { }
                _ => {
                    for character_index_tuple in s.chars().enumerate() {
                        if character_index_tuple.0 > split_off_idx {
                            continue 'string_iteration;
                        }
                        if let Some(nth_char) = first_string.chars().nth(character_index_tuple.0) {
                            if nth_char != character_index_tuple.1 {
                                split_off_idx = character_index_tuple.0;
                                continue 'string_iteration;
                            }
                        }
                    }
                    if s.chars().count() < split_off_idx {
                        split_off_idx = s.chars().count();
                    }
                }
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
