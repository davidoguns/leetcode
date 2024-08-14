package net.oguns.leetcode.kth_largest_in_array;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

public class SolutionTest {
    @Test
    public void testSolution() {
        Solution s = new Solution();
        assertEquals(5, s.findKthLargest(new int[]{3,2,1,5,6,4}, 2));
    }
}
