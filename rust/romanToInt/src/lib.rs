pub(crate) fn add(left: usize, right: usize) -> usize {
    left + right
}

pub(crate) fn extend(vec: &mut Vec<f64>, slice: &[f64]) {
    for elt in slice {
        vec.push(*elt);
    }
}

pub fn do_stuff() {
    let x = add(4, 6);
    let mut v = vec![3., 54., 5.];
    extend(&mut v, &[10., 10., x as f64]);
}

#[cfg(test)]
mod tests {
    use crate::add;
    use crate::extend;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }

    #[test]
    fn extend_vec() {
        let mut v = vec![3.5, 2.3, 0.0];
        let s = [1., 2., 3., 4., 5.];
        extend(&mut v, &s[3..]);
        assert_eq!(v, [3.5, 2.3, 0.0, 4., 5.0]);
    }
}
