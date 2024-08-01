package net.oguns.leetcode.top_k_frequent;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;

import org.junit.jupiter.api.Test;

public class SolutionTest {
    @Test
    public void testSolution() {
        Solution s = new Solution();
        assertArrayEquals(new int[]{1, 2}, s.topKFrequent(new int[]{1, 1, 1, 2, 2, 3}, 2));
        assertArrayEquals(new int[]{1}, s.topKFrequent(new int[]{1}, 1));
    }
}
