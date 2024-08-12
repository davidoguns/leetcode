package net.oguns.leetcode.min_size_subarray_sum;

class Solution {
    //https://leetcode.com/problems/minimum-size-subarray-sum/
    public int minSubArrayLen(int target, int[] nums) {
        if (target == 0) return 0; //sum of zero needs a zero length array? Sure, I'll go with that
        int frontIdx = 0;
        int spanLength = 0;
        int queueSum = 0; //track the total sum of every item in the queue
        boolean targetFound = false;
        int minLength = Integer.MAX_VALUE;

        for (int idx = 0; idx < nums.length; ++idx) {
            int num = nums[idx];
            spanLength += 1;
            if (num == target) {
                //this is just a logical "optimization" that skips work. Why care about the rest of the
                //array when 1 is the smallest possible subarray length
                return 1;
            }
            queueSum += num;
            if (queueSum >= target) {
                targetFound = true;
                //now we need to shrink queue while staying above the target and capture the size of it (local minimum)
                //also noting, that how much we "shrink" the queue by allows is to SKIP in our outermost loop progression
                
                while (spanLength > 0 && (queueSum - nums[frontIdx]) >= target) {
                    queueSum -= nums[frontIdx++];
                    spanLength -= 1;
                }
                //we now know rearview queue is as small as possible so it's size is a min length
                if (minLength > spanLength) {
                    minLength = spanLength;
                }
            }
        }
        //if nothing adds up to to the target, the return will be Integer.MAX_VALUE
        //easy enough to check and do something else if necessary
        if (targetFound) {
            return minLength;
        }
        return 0;
    }
}
