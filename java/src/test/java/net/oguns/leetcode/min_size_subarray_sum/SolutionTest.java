package net.oguns.leetcode.min_size_subarray_sum;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

public class SolutionTest {
    @Test
    public void testSolution() {
        Solution s = new Solution();
        assertEquals(3, s.minSubArrayLen(15, new int[]{1, 1, 1, 5, 0, 2, 10, 3}));
        assertEquals(2, s.minSubArrayLen(7, new int[]{2,3,1,2,4,3}));
        assertEquals(1, s.minSubArrayLen(4, new int[]{1,4,4}));
        assertEquals(0, s.minSubArrayLen(11, new int[]{1,1,1,1,1,1,1,1}));
        assertEquals(1, s.minSubArrayLen(1, new int[]{1,1,1,1,7}));
        assertEquals(3, s.minSubArrayLen(11, new int[]{1,2,3,4,5}));
    }
}
