package net.oguns.practice.max_level;

import java.util.LinkedList;
import java.util.Queue;

import net.oguns.TreeNode;

class Solution {
    public int maxLevel(TreeNode root) {
        Queue<TreeNode> nodeQueue = new LinkedList<TreeNode>();
        if (root == null) throw new RuntimeException("Tree is null, there is no max level");
        int currentLevel = 0;
        int maxLevel = 0;
        int childrenAddedOnThisLevel = 1;
        int childrenAddedOnMaxLevel = 1;
        nodeQueue.add(root);
        while (!nodeQueue.isEmpty()) {
            //go through each child "added" from prior level, and add it's children to track
            //then check if it's a new max level
            int childrenAddedOnNextLevel = 0;
            for (int i = 0; i < childrenAddedOnThisLevel; ++i) {
                TreeNode child = nodeQueue.poll();
                if (child.left() != null) {
                    ++childrenAddedOnNextLevel;
                    nodeQueue.add(child.left());
                }
                if (child.right() != null) {
                    ++childrenAddedOnNextLevel;
                    nodeQueue.add(child.right());
                }
            }
            if (childrenAddedOnThisLevel > childrenAddedOnMaxLevel) {
                maxLevel = currentLevel;
            }
            ++currentLevel;
            childrenAddedOnThisLevel = childrenAddedOnNextLevel;
        }
        return maxLevel;
    }
}
