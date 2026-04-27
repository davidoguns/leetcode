use std::cell::RefCell;
use std::rc::Rc;

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

pub struct Solution;

impl Solution {
    pub fn inorder_traversal(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        match root {
            Some(root) => {
                let mut v = Vec::<i32>::new();
                if let Some(left) = &root.borrow().left {
                    for item in Solution::inorder_traversal(Some(left.clone())) {
                        v.push(item);
                    }
                }
                v.push(root.borrow().val);
                if let Some(right) = &root.borrow().right {
                    for item in Solution::inorder_traversal(Some(right.clone())) {
                        v.push(item);
                    }
                }
                v
            }
            None => Vec::<i32>::default(),
        }
    }
}

fn main() {}

#[cfg(test)]
pub mod test {
    use crate::{Solution, TreeNode};
    use std::cell::RefCell;
    use std::rc::Rc;

    #[test]
    pub fn test_traversal() {
        let root_node = Rc::new(RefCell::new(TreeNode {
            val: 5,
            left: Some(Rc::new(RefCell::new(TreeNode {
                val: 3,
                left: None,
                right: None,
            }))),
            right: None,
        }));
        assert_eq!(
            vec![3, 5],
            Solution::inorder_traversal(Some(root_node.clone()))
        );
        assert_ne!(
            vec![5, 3],
            Solution::inorder_traversal(Some(root_node.clone()))
        );
        assert_ne!(
            vec![3, 5, 8],
            Solution::inorder_traversal(Some(root_node.clone()))
        );

        let root_node_2 = Rc::new(RefCell::new(TreeNode {
            val: 2,
            left: Some(Rc::new(RefCell::new(TreeNode {
                val: 6,
                left: None,
                right: Some(Rc::new(RefCell::new(TreeNode {
                    val: 8,
                    left: None,
                    right: None,
                }))),
            }))),
            right: Some(Rc::new(RefCell::new(TreeNode {
                val: 10,
                left: None,
                right: None,
            }))),
        })); 
        assert_eq!(
            vec![6, 8, 2, 10],
            Solution::inorder_traversal(Some(root_node_2.clone()))
        );
    }
}
