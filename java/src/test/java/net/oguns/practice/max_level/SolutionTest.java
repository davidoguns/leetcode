package net.oguns.practice.max_level;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import org.junit.jupiter.api.Test;

public class SolutionTest {
    @Test
    public void testSolution() {
        Solution s = new Solution();
        assertEquals(0, s.maxLevel(new Solution.TreeNode(5, null, null)));
        assertEquals(1, s.maxLevel(new Solution.TreeNode(5,
            new Solution.TreeNode(4, null, null),
            new Solution.TreeNode(8, null, null))));
        assertThrows(RuntimeException.class, () -> {
            assertEquals(1, s.maxLevel(null));
        });
    }
}

