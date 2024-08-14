package net.oguns.leetcode.kth_smallest_bst;

import java.util.Stack;

import net.oguns.TreeNode;


class Solution {
    //helper function does the actual in order traversal.
    //It returns true (ending traversal) when kth node in order is traversed
    //If it returns true, it'll write the actual value inside num[] which is
    //just an output parameter
    private boolean kthSmallestHelper(TreeNode current, int k[], int num[]) {
        boolean found = false;
        if (current.left() != null) {
             found = kthSmallestHelper(current.left(), k, num);
            if (found) return true;
        }
        if ((--k[0]) == 0) {
            //this is the node to return
            num[0] = current.val();
            return true;
        }
        if (current.right() != null) {
            found = kthSmallestHelper(current.right(), k, num);
            if (found) return true;
        }
        return false;
    }
    public int kthSmallestRecurse(TreeNode root, int k) {
        int num[] = new int[]{0};
        int karr[] = new int[]{k};
        if (kthSmallestHelper(root, karr, num)) {
            return num[0];
        }
        throw new RuntimeException("Could not find kth smallest.");
    }

    //same traversal using a stack 
    public int kthSmallest(TreeNode root, int k) {
        Stack<TreeNode> nodeStack = new Stack<>();
        if (root == null) {
            throw new RuntimeException("Could not find kth smallest.");
        }
        TreeNode currentNode = root;
        //this is an "iterative" in order traversal
        while (currentNode != null || !nodeStack.isEmpty()) {
            while (currentNode != null)  {
                nodeStack.push(currentNode);
                currentNode = currentNode.left();
            }
            //process "this" node (pull it off stack)
            currentNode = nodeStack.pop();
            if (--k == 0) {
                return currentNode.val();
            }
            currentNode = currentNode.right();
        }
        throw new RuntimeException("Could not find kth smallest.");
    }
}
