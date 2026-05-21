// https://leetcode.com/problems/swap-nodes-in-pairs/
// Definition for singly-linked list.
#[derive(PartialEq, Eq, Clone, Debug)]
pub struct ListNode {
  pub val: i32,
  pub next: Option<Box<ListNode>>
}

impl ListNode {
  #[inline]
  fn new(val: i32) -> Self {
    ListNode {
      next: None,
      val
    }
  }
}

struct Solution;

impl Solution {
    pub fn _swap_pairs(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        return todo!();
        if let Some(curr_head) = &head {
            if let Some(next) = &curr_head.next {
                //save this because we are recursing there
                let next_next = next.next;
                next.next = Self::_swap_pairs(next_next);
                // next.next = Some(curr_head);
            }
        }
        head
    }
}

fn main() {
    println!("Hello, leetcode!");
}

#[cfg(test)]
mod test {
    use crate::Solution;

    #[test]
    pub fn test_swap_pairs() {

    }

}
