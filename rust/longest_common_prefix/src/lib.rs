pub fn longest_common_prefix(strings: &[&str]) -> String {
    if strings.len() == 0 { return "".to_string(); }
    let mut match_vec = Vec::<(usize, char)>::new();
    'string_itr: for (string_index, s) in strings.iter().enumerate() {
        match string_index {
            0 => {
                //first string the match is entire string
                s.chars().enumerate().for_each(|(idx, ch)| {
                    match_vec.push((idx, ch));
                });
                println!("match vec for first: {}", s);
            }
            _ => {
                let mut schars_itr = s.chars().into_iter();
                for ch_tup in &match_vec {
                    if let Some(schar) = schars_itr.next() {
                        if schar != (*ch_tup).1 {
                            _ = match_vec.split_off((*ch_tup).0);
                            continue 'string_itr;
                        }
                    }
                    else {
                        continue 'string_itr;
                    }
                }
            }
        }

        if match_vec.is_empty() {
            break;
        }
    }

    match_vec.into_iter().map(|(_, ch)| { ch }).collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_prefixes() {
        assert_eq!("ab", longest_common_prefix(&["abcd", "ab", "abdcdef"]));
        assert_eq!("", longest_common_prefix(&["abcd", "bc", "abdcdef"]));
    }
}
