pub fn build_array(target: Vec<i32>, n: i32) -> Vec<String> {
    //https://leetcode.com/problems/build-an-array-with-stack-operations
    //Don't need a stack at all. Silly problem description is more prescriptive
    let mut ret = Vec::<String>::new();
    let mut pos = 0u8;
    for digit in 1..=n {
        if pos == target.len() as u8 {
            break;
        }
        let target_digit = target.get(pos as usize).unwrap();
        ret.push("Push".to_string());
        if *target_digit == digit {
            pos += 1;
        } else {
            ret.push("Pop".to_string());
        }
    }

    ret
}

pub fn my_atoi(s: String) -> i32 {
    //https://leetcode.com/problems/string-to-integer-atoi
    let mut ch_itr = s.chars().peekable();
    //trim leading whitespace
    while ch_itr.next_if(|ch| ch.is_whitespace()).is_some() { }

    let is_positive = match ch_itr.next_if(|ch| *ch == '+' || *ch == '-') {
        Some(sign) => sign == '+',
        None => true
    };

    let mut value = 0i64;
    while ch_itr.peek().is_some_and(|ch| ch.is_ascii_digit()) {
        let digit = ch_itr.next().unwrap();
        value = value.saturating_mul(10);
        value = value.saturating_add(digit.to_digit(10).unwrap() as i64);
    }
    if !is_positive {
        value *= -1;
    }
    value.clamp(i32::MIN as i64, i32::MAX as i64) as i32
}

pub fn divide(dividend: i32, divisor: i32) -> i32 {
    let is_positive = (dividend.is_positive() && divisor.is_positive()) || 
        (dividend.is_negative() && divisor.is_negative());

    let mut abs_divd = dividend;
    //we need to flip the divisor if subtracting by it will diverge from zero
    let abs_divs = if is_positive { divisor } else { -divisor };
    let pred = 
        if abs_divd > 0 {
            |x| x > 0
        } else {
            |x| x < 0
        };

    let mut count = 0i32;
    while pred(abs_divd) {
        count = count.saturating_add(1);
        abs_divd -= abs_divs;
    }
    //check if we've subtraced once too far
    if abs_divd != 0 {
        count -= 1;
    }
    if !is_positive {
        count = -count
    }
    count
}

fn main() {
    let arr = build_array(vec![1, 3], 3);
    dbg!(arr);
}

#[cfg(test)]
pub mod test {
    use crate::{build_array, my_atoi, divide};

    #[test]
    pub fn test_build_array_with_stack() {
        let arr = build_array(vec![1, 3], 3);
        assert_eq!(vec!["Push".to_string(), "Push".to_string(), "Pop".to_string(), "Push".to_string()], arr);
    }

    #[test]
    pub fn test_my_atoi() {
        assert_eq!(32i32, my_atoi("32".to_string()));
        assert_eq!(62i32, my_atoi("0062".to_string()));
        assert_eq!(-32i32, my_atoi("-0032".to_string()));
        assert_eq!(-32i32, my_atoi("   -0032 ".to_string()));
        assert_eq!(-8192i32, my_atoi("  -8192af ".to_string()));
        assert_eq!(-2147483648, my_atoi("-91283472332".to_string()));
    }

    #[test]
    pub fn test_divide() {
        assert_eq!(5, divide(50, 10));
        assert_eq!(3, divide(10, 3));
        assert_eq!(2147483647, divide(-2147483648, -1));
    }
}
