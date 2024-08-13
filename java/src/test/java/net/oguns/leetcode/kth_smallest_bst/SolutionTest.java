package net.oguns.leetcode.kth_smallest_bst;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

import net.oguns.TreeNode;

public class SolutionTest {
    @Test
    public void testSolution() {
        Solution s = new Solution();
        TreeNode root = new TreeNode(4, new TreeNode(3, new TreeNode(1, TreeNode.leaf(0), TreeNode.leaf(2)), null), TreeNode.leaf(5));
        assertEquals(2, s.kthSmallest(root, 3));
    }
}
