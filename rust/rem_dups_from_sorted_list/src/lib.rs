// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        #![allow(dead_code)]
        ListNode { next: None, val }
    }
}

//https://leetcode.com/problems/remove-duplicates-from-sorted-list/
pub struct Solution;

impl Solution {
    pub fn delete_duplicates(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        match head {
            Some(head) => Some(Box::new(ListNode {
                val: head.val,
                next: Self::delete_dups(&head, &head.next),
            })),
            None => None,
        }
    }

    pub fn delete_dups(
        prev: &Box<ListNode>,
        head: &Option<Box<ListNode>>,
    ) -> Option<Box<ListNode>> {
        match head {
            Some(head) if head.val == prev.val => Self::delete_dups(head, &head.next),
            Some(head) => Some(Box::new(ListNode {
                val: head.val,
                next: Self::delete_dups(head, &head.next),
            })),
            None => None,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    pub fn to_vec(head: &Option<Box<ListNode>>) -> Vec<i32> {
        match head {
            Some(head) => {
                let mut v: Vec<i32> = Vec::new();
                let mut cur = Some(head);
                while let Some(cur_node) = cur {
                    v.push(cur_node.val);
                    cur = cur_node.next.as_ref();
                }
                v
            }
            None => Vec::new(),
        }
    }

    #[test]
    fn test_solution() {
        #[rustfmt::skip]
        let list_with_dups_1 = Some(Box::new(ListNode {val: 3,
            next: Some(Box::new(ListNode { val: 5,
                next: Some(Box::new(ListNode { val: 7,
                    next: None,
                }))
            }))
        }));
        #[rustfmt::skip]
        let list_with_dups_2 = Some(Box::new(ListNode {val: 3,
            next: Some(Box::new(ListNode {val: 5,
                next: Some(Box::new(ListNode {val: 7,
                    next: Some(Box::new(ListNode {val: 7,
                        next: None}))
                }))
            }))
        }));

        assert_eq!(
            vec!(3, 5, 7),
            to_vec(&Solution::delete_duplicates(list_with_dups_1))
        );
        assert_eq!(
            vec!(3, 5, 7),
            to_vec(&Solution::delete_duplicates(list_with_dups_2))
        );
    }
}
