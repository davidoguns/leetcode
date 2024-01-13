pub fn is_match(s: String, p: String) -> bool {
    let mut char_itr = s.chars().into_iter();
    let regex_tokens = get_regex_tokens(p);
    let mut regex_tokens_itr = regex_tokens.iter();
    match_regex(char_itr.next(), &mut char_itr, regex_tokens_itr.next(), &mut regex_tokens_itr)
}

fn match_regex(curr_ch: Option<char>, mut char_itr: &mut dyn Iterator<Item = char>, curr_token: Option<&(char, bool)>, mut token_itr: &mut dyn Iterator<Item = &(char, bool)>) -> bool {
    if let Some(char) = curr_ch {
        if let Some(token) = curr_token {
            let (_token_char, _token_repeat) = token;
            //here we have both a token and a character to examine
            if token.0 == char || token.0 == '.' {
                if token.1 { //zero or many
                    //we match if either we advance the token on the same character OR
                    //we continue consuming the characters until the tokens don't match
                    match_regex(curr_ch, &mut char_itr, token_itr.next(), &mut token_itr) ||
                    match_regex(char_itr.next(), &mut char_itr, curr_token, &mut token_itr)
                    // match_regex(char_itr.next(), &mut char_itr, curr_token, &mut token_itr) ||
                    // match_regex(curr_ch, &mut char_itr, token_itr.next(), &mut token_itr)
                } else { //just one char matching one token with no repeat
                    //advance both current character and current token and continue matching
                    match_regex(char_itr.next(), &mut char_itr, token_itr.next(), &mut token_itr)
                }
            } else {
                //if the character doesn't match, it doesn't matter if it's a zero-many as well
                //continue while advancing the regex token, not the character
                if token.1 {
                    //advance token, not character
                    match_regex(curr_ch, &mut char_itr, token_itr.next(), &mut token_itr)
                }
                else {
                    return false
                }
            }
        } else {
            //if there's still characters left in the input, but no regex token to use to consume
            //then we have a non-match condition
            return false
        }
    }
    else {
        //no more characters left, but there are regex tokens left. This is OK  for a 
        //positive match if the tokens being looked are * 
        if let Some(token) = curr_token {
            if token.1 {
                //matching *, so we can say we match so far and move forward
                //advance token to match as long as they are zero-or-many
                match_regex(curr_ch, &mut char_itr, token_itr.next(), &mut token_itr)
            } else {
                false
            }
        }
        else {
            true
        }
    }
}

fn get_regex_tokens(p: String) ->Vec<(char, bool)> {
    let mut vreturn = Vec::<(char, bool)>::new();
    let mut regex_char_itr = p.chars().into_iter().peekable();
    while let Some(token_char) = regex_char_itr.next() {
        if token_char == '*' {
            continue;
        }
        //peek to next char to see if we're matching indef
        vreturn.push((token_char, regex_char_itr.peek().is_some_and(|&c| c == '*')));
    }
    vreturn
}

fn main() {
}

#[cfg(test)]
mod test {
    use crate::{get_regex_tokens, is_match};

    #[test]
    pub fn test_regex_match() {
        assert_eq!(true, is_match("aaa".to_owned(), "a*a".to_owned()));
        assert_eq!(true, is_match("abc".to_owned(), "abc".to_owned()));
        assert_eq!(false, is_match("abc".to_owned(), "abcd".to_owned()));
        assert_eq!(true, is_match("abc".to_owned(), "abc*".to_owned()));
        assert_eq!(true, is_match("abcd".to_owned(), "ab*cd".to_owned()));
        assert_eq!(true, is_match("abcd".to_owned(), "ab*c*d*".to_owned()));
    }
    
    #[test]
    pub fn test_regex_tokenization() {
        let tokens = get_regex_tokens("a*bcd.*rfasd*".to_owned());
        assert_eq!(vec![('a', true), ('b', false), ('c', false), ('d', false), ('.', true),
                        ('r', false), ('f', false), ('a', false), ('s', false), ('d', true)], tokens);
        for token in tokens {
            eprintln!("Token: {},{}", token.0, token.1);
        }
        assert_eq!(vec![('a', true), ('a', false)], get_regex_tokens("a*a".to_owned()));
    }
}
