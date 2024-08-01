package net.oguns.leetcode.top_k_frequent;

import java.util.Arrays;
import java.util.HashMap;
import java.util.PriorityQueue;

//https://leetcode.com/problems/top-k-frequent-elements/
class Solution {
    public int[] topKFrequent(int[] nums, int k) {
        record ValueFrequency(int count, int value) implements Comparable<ValueFrequency> {
			@Override
			public int compareTo(ValueFrequency o) {
                //compare just counts
                return o.count() - count();
			}
        };
        final HashMap<Integer, Integer> frequencyMap = new HashMap<>();
        Arrays.stream(nums).forEach(num -> {
            Integer currentCount = frequencyMap.get(num);
            if (currentCount == null) { //means it's 0 occurrences so far, this is the first
                frequencyMap.put(num, 1);
            } else {
                frequencyMap.put(num, currentCount + 1);
            }
        });
        PriorityQueue<ValueFrequency> pq = new PriorityQueue<>();
        frequencyMap.forEach((value, count) -> {
            //N different numbers, logN insertion
            pq.add(new ValueFrequency(count, value));
        });
        int results[] = new int[k];
        for (int i = 0; i < k && !pq.isEmpty(); ++i) {
            results[i] = pq.poll().value();
        }
        return results;
    }
}
