package net.oguns.leetcode.twosumsorted;

// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/
class Solution {
    public int[] twoSum(int[] nums, int target) {
        for (int i = 0; i < nums.length; ++i) {
            int to_match = target - nums[i];
            int left = i + 1;
            int right = nums.length - 1;
            while (left <= right) {
                int mid = left + ((right - left) / 2);
                if (nums[mid] == to_match) return new int[]{i, mid};
                if (to_match < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
        }
        throw new RuntimeException("Couldn't find a matching twoSum!");
    }
}
