pub fn generate_parenthesis(n: i32) -> Vec<String> {
    let mut ret = Vec::<String>::new();
    generate_parens(0, 0, n, "".to_owned(), &mut ret);
    ret
}

pub fn generate_parens(
    n_open: i32,
    n_closed: i32,
    n_max: i32,
    current_string: String,
    output: &mut Vec<String>,
) {
    //if we have reached the string length limit, we've generated a solution
    if current_string.len() as i32 == n_max * 2 {
        output.push(current_string);
    } else {
        //if we can open a parens, open it and continue generating
        if n_open < n_max {
            generate_parens(
                n_open + 1,
                n_closed,
                n_max,
                format!("{}(", current_string),
                output,
            );
        }
        //if we can close a parens, close it and continue generating 
        if n_closed < n_open {
            generate_parens(
                n_open,
                n_closed + 1,
                n_max,
                format!("{})", current_string),
                output,
            );
        }
    }
}

fn main() {
    println!("Parentheses combinations: {:?}", generate_parenthesis(3));
}

#[cfg(test)]
pub mod test {
    use crate::generate_parenthesis;
    #[test]
    pub fn test_gen_parens() {
        assert_eq!(vec!["(())", "()()"], generate_parenthesis(2));
        assert_eq!(
            vec!["((()))", "(()())", "(())()", "()(())", "()()()"],
            generate_parenthesis(3)
        );
        assert_eq!(
            vec![
                "(((())))", "((()()))", "((())())", "((()))()", "(()(()))", "(()()())", "(()())()",
                "(())(())", "(())()()", "()((()))", "()(()())", "()(())()", "()()(())", "()()()()"
            ],
            generate_parenthesis(4)
        );
    }
}
