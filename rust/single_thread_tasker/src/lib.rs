
pub fn get_order_vec(tasks: Vec<Vec<i32>>) -> Vec<i32> {
    get_order(tasks.into_iter().map(|v| { (*v.get(0).unwrap(), *v.get(1).unwrap()) }).collect::<Vec<(i32, i32)>>())
}

pub fn get_order(_tasks: Vec<(i32, i32)>) -> Vec<i32> {
    unimplemented!()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_order() {

    }
}
