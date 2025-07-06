package net.oguns.leetcode.same_tree;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

import net.oguns.TreeNode;

public class SolutionTest {
    @Test
    public void testSolution() {
        Solution s = new Solution();
        assertTrue(s.isSameTree(null, null));
        assertTrue(s.isSameTree(TreeNode.leaf(5), TreeNode.leaf(5)));
        assertFalse(s.isSameTree(TreeNode.leaf(6), TreeNode.leaf(5)));
        TreeNode t1 = new TreeNode(3, null, new TreeNode(4));
        TreeNode t2 = new TreeNode(3, new TreeNode(4), null);
        assertFalse(s.isSameTree(t1, t2));
        TreeNode t3 = new TreeNode(3, new TreeNode(4), new TreeNode(4, null, new TreeNode(8)));
        TreeNode t4 = new TreeNode(3, new TreeNode(4), new TreeNode(4, null, new TreeNode(8)));
        assertTrue(s.isSameTree(t3, t4));
    }
}
