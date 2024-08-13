package net.oguns;

public record TreeNode(int val, TreeNode left, TreeNode right) { 
    public static TreeNode leaf(int val) {
        return new TreeNode(val, null, null);
    }
}
