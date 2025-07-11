package net.oguns.leetcode.same_tree;

import net.oguns.TreeNode;

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public boolean isSameTree(TreeNode p, TreeNode q) {
        if (p == null && q == null) return true;
        else if (p != null && q != null) { 
            return p.val == q.val
                        && isSameTree(p.left, q.left)
                        && isSameTree(p.right, q.right);
        } else {
            return false;
        }
    }
}
