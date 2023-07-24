//yikes..forget the prompt for this one
pub fn get_order_vec(tasks: Vec<Vec<i32>>) -> Vec<i32> {
    get_order(tasks.into_iter().map(|v| { (*v.get(0).unwrap(), *v.get(1).unwrap()) }).collect::<Vec<(i32, i32)>>())
}

pub fn get_order(_tasks: Vec<(i32, i32)>) -> Vec<i32> {
    vec![]
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_get_order() {
        assert_eq!(vec![0, 2, 3, 1], get_order(vec![(1, 2), (2, 4), (3, 2), (4, 1)]));
        assert_eq!(vec![4, 3, 2, 0, 1], get_order(vec![(7, 10), (7, 12), (7, 5), (7, 4), (7, 2)]));
    }

    fn test_get_order_vec() {
        assert_eq!(vec![0, 2, 3, 1], get_order_vec(vec![vec![1, 2], vec![2, 4], vec![3, 2], vec![4, 1]]));
        assert_eq!(vec![4, 3, 2, 0, 1], get_order_vec(vec![vec![7, 10], vec![7, 12], vec![7, 5], vec![7, 4], vec![7, 2]]));
    }
}
