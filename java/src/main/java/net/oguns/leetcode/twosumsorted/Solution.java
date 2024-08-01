package net.oguns.leetcode.twosumsorted;

// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/
class Solution {
    public int[] twoSum(int[] nums, int target) {
        for (int i = 0; i < nums.length; ++i) {
            int to_match = target - nums[i];
            int left = i + 1;
            int right = nums.length;
            int found = java.util.Arrays.binarySearch(nums, left, right, to_match);
            if (found > 0) {
                return new int[]{i, found};
            }
        }
        throw new RuntimeException("Couldn't find a matching twoSum!");
    }
}
