pub fn is_match(s: String, p: String) -> bool {
    let regex_tokens = get_regex_tokens(p);
    let vec = to_vec(&mut s.chars());
    match_regex(0, &vec, 0, &regex_tokens)
}

fn match_regex(curr_ch_index: usize, chars: &Vec<char>, curr_token_index: usize, tokens: &Vec<(char, bool)>) -> bool {
    if let Some(char) = chars.get(curr_ch_index) {
        if let Some(token) = tokens.get(curr_token_index) {
            //here we have both a token and a character to examine
            if token.0 == *char || token.0 == '.' {
                if token.1 { //zero or many
                    //we match if either we advance the token on the same character OR
                    //we continue consuming the characters until the tokens don't match
                    match_regex(curr_ch_index+1, &chars, curr_token_index, &tokens) ||
                    match_regex(curr_ch_index, &chars, curr_token_index+1, &tokens)
                } else { //just one char matching one token with no repeat
                    //advance both current character and current token and continue matching
                    match_regex(curr_ch_index+1, &chars, curr_token_index+1, &tokens)
                }
            } else {
                //if the character doesn't match, it doesn't matter if it's a zero-many as well
                //continue while advancing the regex token, not the character
                if token.1 {
                    //advance token, not character
                    match_regex(curr_ch_index, &chars, curr_token_index+1, &tokens)
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
        if let Some(token) = tokens.get(curr_token_index) {
            if token.1 {
                //matching *, so we can say we match so far and move forward
                //advance token to match as long as they are zero-or-many
                match_regex(curr_ch_index, &chars, curr_token_index+1, &tokens)
            } else {
                false
            }
        }
        else {
            true
        }
    }
}

fn to_vec(char_itr: &mut dyn Iterator<Item = char>) -> Vec<char> {
    let mut vreturn = Vec::<char>::new();
    while let Some(char) = char_itr.next() {
        vreturn.push(char);
    }
    vreturn
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
