pub struct Solution;

impl Solution {
    pub fn longest_palindrome(s: String) -> String {
        let s_chars: Vec<char> = s.chars().collect();
        if s.is_empty() || s.len() == 1usize { return s };

        let (mut lp_start, mut lp_end) = (0usize, 1usize);
       
        //start iteration on the second letter and look for odd length panlindromes
        for (ch_index, _ch) in s_chars.iter().enumerate().skip(1) {
            // println!("ch_index = {}", ch_index);
            let (mut lps, mut lpe) = (ch_index, ch_index); // this is definitely a palindrome
            while s_chars.get(lps).unwrap() == s_chars.get(lpe).unwrap() {
                if (lpe - lps) + 1 > (lp_end - lp_start) {
                    lp_end = lpe + 1;
                    lp_start = lps;
                }
                if lps == 0 || lpe == s.len()-1 {
                    break;
                }
                lps -= 1;
                lpe += 1;
            }
        }
        
        // println!("midway lp_start = {}; lp_end = {}", lp_start, lp_end);
         
        for (ch_index, _ch) in s_chars.iter().enumerate().skip(1) {
            let (mut lps, mut lpe) = (ch_index - 1, ch_index);
            // check if initial adjacent characters are the same
            if s_chars.get(lps).unwrap() != s_chars.get(lpe).unwrap() {
                continue;
            }

            if 3 > (lp_end - lp_start) {
                lp_end = lpe + 1;
                lp_start = lps;
            }  

            while s_chars.get(lps).unwrap() == s_chars.get(lpe).unwrap() {
                if (lpe - lps) + 1 > (lp_end - lp_start) {
                    lp_end = lpe + 1;
                    lp_start = lps;
                }
                if lps == 0 || lpe == s.len()-1 {
                    break;
                }
                lps -= 1;
                lpe += 1;
            }
        }
        // println!("lp_start = {}; lp_end = {}", lp_start, lp_end);
        String::from(s.get(lp_start..lp_end).unwrap())
    }
}

fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
pub mod test {
    use crate::Solution;

    #[test]
    pub fn test_longest_palindrome() {
        assert_eq!("aaaa", Solution::longest_palindrome(String::from("aaaa")));
        assert_eq!("ccc", Solution::longest_palindrome(String::from("ccc")));
        assert_eq!("bab", Solution::longest_palindrome(String::from("babad")));
        assert_eq!("abcba", Solution::longest_palindrome(String::from("babcbad")));
        assert_eq!("bb", Solution::longest_palindrome(String::from("cbbd")));
    }
}
