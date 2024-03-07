#[warn(dead_code)]
struct Solution;
// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/  
impl Solution {
    pub fn search_range(nums: Vec<i32>, target: i32) -> Vec<i32> {
        if let Some(found) = Self::binary_search(target, &nums) {
            let (mut lower, mut upper) = (found, found);
            upper += nums.get(found as usize..).unwrap().windows(2)
                .take_while(|x| (*x).first() == (*x).get(1)).count() as i32;
            lower -= nums.get(0..=found as usize).unwrap().windows(2).rev()
                .take_while(|x| (*x).first() == (*x).get(1)).count() as i32;
            
            // Rust seemed to have cleaned this code up a lot
            // I would want to ensure the performance and and story from .rev()
            // isn't too bad
            // let (mut lower_i, mut upper_i) = (found, found);
            // while lower_i > 0 {
            //     lower_i -= 1;
            //     if *nums.get((lower_i) as usize).unwrap() == target {
            //         lower = lower_i;
            //     }
            // }
            //
            // while upper_i < nums.len() as i32 - 1 {
            //     upper_i += 1;
            //     if *nums.get((upper_i) as usize).unwrap() == target {
            //         upper = upper_i;
            //     }
            // }
            return vec![lower, upper]
        }
        vec![-1, -1] //not sure what the return is here
    }

    pub fn binary_search(target: i32, nums: &Vec<i32>) -> Option<i32> {
        let mut min_index = 0;
        let mut max_index = nums.len() as i32;

        if max_index == 0 {
            return None;
        }

        while (max_index - min_index) > 1 {
            let mid_index = min_index + ((max_index - min_index) / 2);
            let mid_value = *nums.get(mid_index as usize).expect("Array out of bounds error");

            if mid_value == target {
                return Some(mid_index)
            } else if mid_value > target {
                max_index = mid_index;
            } else {
                min_index = mid_index + 1;
            }
        }
        if *nums.get(min_index as usize).expect("Array out of bounds error") == target {
            return Some(min_index)
        }

        None
    }
}

fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
pub mod test {
    use crate::Solution;

    #[test]
    pub fn test_solution() {
        assert_eq!(vec![3, 4], Solution::search_range(vec![5,7,7,8,8,10], 8));
        assert_eq!(vec![-1, -1], Solution::search_range(vec![5,7,7,8,8,10], 6));
        assert_eq!(vec![-1, -1], Solution::search_range(vec![], 0));
        assert_eq!(vec![0, 0], Solution::search_range(vec![1], 1));
    }
    
    #[test]
    pub fn test_binary_search() {
        assert_eq!(Some(3), Solution::binary_search(4, &vec![2, 3, 3, 4, 5, 8, 18]));
        assert_eq!(Some(0), Solution::binary_search(2, &vec![2, 3, 3, 4, 5, 8, 18]));
        assert_eq!(Some(5), Solution::binary_search(8, &vec![2, 3, 3, 4, 5, 8, 18]));
        assert_eq!(None, Solution::binary_search(6, &vec![2, 3, 3, 4, 5, 8, 18]));
        assert_eq!(Some(0), Solution::binary_search(-32, &vec![-32, -14, -3, 2, 3, 3, 4, 5, 8, 18]));
    }
}
