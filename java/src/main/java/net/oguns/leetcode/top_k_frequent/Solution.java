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

            frequencyMap.compute(num, (key, v) -> {
                if (v == null) return 1;
                return v + 1;
            });
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
