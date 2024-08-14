package net.oguns.leetcode.kth_largest_in_array;

import java.util.Arrays;
import java.util.PriorityQueue;

//https://leetcode.com/problems/kth-largest-element-in-an-array/
class Solution {
    public int findKthLargest(int[] nums, int k) {
        final PriorityQueue<Integer> smallestNumbersMaxQ = new PriorityQueue<>((a, b) -> a - b);
        Arrays.stream(nums).forEach(num -> {
            if (smallestNumbersMaxQ.size() < k ||
                smallestNumbersMaxQ.peek() < num) {
                smallestNumbersMaxQ.add(num);
            }
            //if we've added a number in our smalle
            if (smallestNumbersMaxQ.size() > k) {
                smallestNumbersMaxQ.poll();
            }
        });
        return smallestNumbersMaxQ.peek();
    }
}
