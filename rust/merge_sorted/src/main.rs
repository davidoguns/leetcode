#[warn(unused)]

struct Solution {}

impl Solution {
    pub fn merge(nums1: &mut Vec<i32>, m: i32, nums2: &mut Vec<i32>, n: i32) {
        let m: usize = usize::try_from(m).expect(format!("Cannot convert m[={m}] into usize").as_str());
        let n: usize = usize::try_from(n).expect(format!("Cannot convert n[={n}] into usize").as_str());
        let mut dest_idx: usize = 0;
        let mut nums2_idx: usize = 0;
        let mut nums1_drained: usize = 0;
        //Shift all elements at idx and beyond right by 1.
        //Loses a value at the end of the vector. Then insert
        //value at idx.
        let fn_shift_insert = |val: i32, idx: usize, shift_len: usize, vec: &mut Vec<i32>| {
            let shift_rng = idx..(idx+shift_len);
            vec.copy_within(shift_rng, idx+1);
            vec[idx] = val;
        };
        loop {
            if nums1_drained >= m {
                //means everything left in nums2 goes into nums1
                //so we fill from where dest_idx is now to the end
                for idx in nums2_idx..n {
                    nums1[dest_idx] = nums2[idx];
                    dest_idx += 1;
                }
                break; //this is a finishing operation
            }
            if nums2_idx >= n {
                //means we've drained all of the 2nd array into the first
                //and there's no more work to do
                break;
            }
            //core logic, compare what's next in either nums1 and nums2
            if nums2[nums2_idx] < nums1[dest_idx] {
                fn_shift_insert(nums2[nums2_idx], dest_idx, m - nums1_drained, nums1);
                nums2_idx += 1;
            } else {
                nums1_drained += 1;
            }
            dest_idx += 1;
        }
    }
}

fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
pub mod test {
    use std::vec;
    use crate::Solution;

    #[test]
    pub fn test_sort_1() {
        let mut v1 = vec![1, 2, 3, 0, 0, 0];
        let mut v2 = vec![2, 5, 6];
        Solution::merge(&mut v1, 3, &mut v2, 3);
        assert_eq!(vec![1, 2, 2, 3, 5, 6], v1);
    }

    #[test]
    pub fn test_sort_2() {
        let mut v1 = vec![2, 0];
        let mut v2 = vec![1];
        Solution::merge(&mut v1, 1, &mut v2, 1);
        assert_eq!(vec![1, 2], v1);
    }
}
