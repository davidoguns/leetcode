use std::collections::HashMap;

//https://leetcode.com/problems/climbing-stairs/
pub struct Solution;

impl Solution {
    pub fn climb_stairs(n: i32) -> i32 {
        let mut memo = HashMap::<i32,i32>::new();
        memo.insert(0, 0);
        memo.insert(1, 1);
        memo.insert(2, 2);
        Self::_climb_stairs(n, &mut memo)
    }

    pub fn _climb_stairs(n: i32, mut memo: &mut HashMap<i32, i32>) -> i32 {
        if memo.contains_key(&n) {
            return *memo.get(&n).unwrap();
        } else {
            let n1 = Self::_climb_stairs(n-1, &mut memo);
            memo.insert(n-1, n1);
            let n2 = Self::_climb_stairs(n-2, &mut memo);
            memo.insert(n-2, n2);
            return n1 + n2;
        }
    }
}

fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    pub fn test_climb_stairs() {
        assert_eq!(Solution::climb_stairs(3), 3);
    }
}
