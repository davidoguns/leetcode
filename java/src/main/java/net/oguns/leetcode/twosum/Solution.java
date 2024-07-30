package net.oguns.leetcode.twosum;

//https://leetcode.com/problems/two-sum/
class Solution {
    public int[] twoSum(int[] nums, int target) {
        for (int i = 0; i < nums.length; ++i) {
            int to_match = target - nums[i];
            for (int j = i + 1; j < nums.length; ++j) {
                if (nums[j] == to_match) return new int[]{i, j};
            }
        }
        throw new RuntimeException("Couldn't find a matching twoSum!");
    }
}
