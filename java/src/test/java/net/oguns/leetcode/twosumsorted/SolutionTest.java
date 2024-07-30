package net.oguns.leetcode.twosumsorted;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.Test;

public class SolutionTest {
    @Test
    public void testSolution() {
        Solution s = new Solution();
        assertArrayEquals(new int[]{0, 1}, s.twoSum(new int[]{2, 7, 11, 15}, 9));
        assertArrayEquals(new int[]{0, 2}, s.twoSum(new int[]{2, 3, 4}, 6));
        assertArrayEquals(new int[]{0, 1}, s.twoSum(new int[]{-1, 0}, -1));
        assertThrows(RuntimeException.class, () -> {
            assertArrayEquals(new int[]{0, 1}, s.twoSum(new int[]{2, 7, 11, 15}, 10));
        });
    }
}
