package net.oguns;

import java.util.LinkedList;
import java.util.Queue;

public final class PrintUtils {
    public static void printTreeLevels(TreeNode root) {
        Queue<TreeNode> nodeQueue = new LinkedList<>();

        if (root == null) return;
        
        int numNodesOnLevel = 1;
        nodeQueue.add(root);
        while (!nodeQueue.isEmpty()) {
            int numChildrenAdded = 0;
            for (int i = 0; i < numNodesOnLevel; ++i) {
                TreeNode node = nodeQueue.poll();
                System.out.print("{" + node.val() + "}");
                if (node.left() != null) {
                    ++numChildrenAdded;
                    nodeQueue.add(node.left());
                }
                if (node.right() != null) {
                    ++numChildrenAdded;
                    nodeQueue.add(node.right());
                }
            }
            System.out.println("; level size = " + numNodesOnLevel);
            numNodesOnLevel = numChildrenAdded;
        }

    }
}
