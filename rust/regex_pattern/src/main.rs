pub fn is_match(s: String, p: String) -> bool {
    let char_itr = s.chars().into_iter();
    let regex_tokens = get_regex_tokens(p);
    unimplemented!()
}

fn get_regex_tokens(p: String) ->Vec<(char, bool)> {
    let mut vreturn = Vec::<(char, bool)>::new();
    let mut regex_char_itr = p.chars().into_iter().peekable();
    while let Some(token_char) = regex_char_itr.next() {
        if token_char == '*' {
            continue;
        }
        vreturn.push((token_char, regex_char_itr.peek().is_some_and(|&c| c == '*')));
    }
    vreturn
}

fn main() {
}

#[cfg(test)]
mod test {
    use crate::get_regex_tokens;
    
    #[test]
    pub fn test_regex_tokenization() {
        let tokens = get_regex_tokens("a*bcd.*rfasd*".to_owned());
        assert_eq!(vec![('a', true), ('b', false), ('c', false), ('d', false), ('.', true),
                        ('r', false), ('f', false), ('a', false), ('s', false), ('d', true)], tokens);
        for token in tokens {
            eprintln!("Token: {},{}", token.0, token.1);
        }
    }
}
