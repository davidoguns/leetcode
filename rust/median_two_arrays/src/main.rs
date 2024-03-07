
pub fn find_median_sorted_arrays(nums1: Vec<i32>, nums2: Vec<i32>) -> f64 {
    //early tests if either are empty
    if nums1.is_empty() && nums2.is_empty() {
        panic!("Both lists are empty, no result");
    }
    else if nums1.is_empty() { //implicitly, nums2 is not empty
        //median of just nums2
        return ez_median(nums2);
    }
    else if nums2.is_empty() {
        //median of just nums1
        return ez_median(nums1);
    }
    //no we know that neither is empty
    let mut nums1_itr = nums1.iter().peekable();
    let mut nums2_itr = nums2.iter().peekable();
    let mut last_num = *nums1.first().unwrap();
    let mut prev_num = Option::<i32>::None;
    for _i in 0..(((nums1.len()+nums2.len())/2)+1) {
        if nums1_itr.peek().is_some_and(|n| 
            nums2_itr.peek().is_none() || nums2_itr.peek().unwrap() >= n) {
            prev_num = Option::<i32>::Some(last_num);
            last_num = *nums1_itr.next().unwrap();
        } else {
            prev_num = Option::<i32>::Some(last_num);
            last_num = *nums2_itr.next().unwrap();
        }
    }
    
    //if we iterated an odd number of times we need the next number
    //and take an average, this is why the return is a float
    if (nums1.len()+nums2.len()) % 2 == 0 {
        return (last_num + prev_num.unwrap()) as f64 / 2f64;
    }

    last_num as f64
}

fn ez_median(nums: Vec<i32>) -> f64 {
    if nums.len() == 1 {
        *nums.first().unwrap() as f64
    } else if nums.len() % 2 == 0 {
        (*nums.get(nums.len()/2).unwrap() + *nums.get((nums.len()/2)-1).unwrap()) as f64 / 2f64
    } else {
        *nums.get(nums.len()/2).unwrap() as f64
    }
}

fn main() {
    println!("Median is: {}",
        find_median_sorted_arrays(vec![], vec![1]));
    println!("Median is: {}",
        find_median_sorted_arrays(vec![1, 3], vec![2]));
    println!("Median is: {}",
        find_median_sorted_arrays(vec![1], vec![2]));
}
