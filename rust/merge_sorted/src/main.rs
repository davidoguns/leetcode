#[warn(unused)]
struct Solution {}

impl Solution {
    pub fn merge(nums1: &mut Vec<i32>, m: i32, nums2: &mut Vec<i32>, n: i32) {
        let m: usize = usize::try_from(m).expect(format!("Cannot convert m[={m}] into usize").as_str());
        let n: usize = usize::try_from(n).expect(format!("Cannot convert n[={n}] into usize").as_str());
        let mut dest_idx: usize = 0;
        let mut nums2_idx: usize = 0;
        let mut nums1_idx: usize = 0;
        loop {
            if nums1_idx >= m {
                //means everything left in nums2 goes into nums1
                for idx in nums2_idx..n {
                    nums1.insert(dest_idx, *nums2.get(idx).unwrap());
                    dest_idx += 1;
                }
                break; //this is a finishing operation
            }
            if nums2_idx >= n {
                //means we've drained all of the 2nd array into the first
                //and there's no more work to do
                break;
            }
            
            println!("dest_idx={dest_idx}; nums2_idx={nums2_idx}");
            if nums2.get(nums2_idx).unwrap() < nums1.get(dest_idx).unwrap() {
                nums1.insert(dest_idx, *nums2.get(nums2_idx).unwrap());
                nums2_idx += 1;
            } else {
                nums1_idx += 1;
            }
            dest_idx += 1;
        } 
        nums1.resize(m+n, 0);
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
    pub fn test_sort() {
        let mut v1 = vec![1, 2, 3, 0, 0, 0];
        let mut v2 = vec![2, 5, 6];
        Solution::merge(&mut v1, 3, &mut v2, 3);
        assert_eq!(vec![1, 2, 2, 3, 5, 6], v1);
    }
}
