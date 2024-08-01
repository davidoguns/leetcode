package net.oguns.practice.max_level;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.Test;

import net.oguns.PrintUtils;
import net.oguns.TreeNode;

public class SolutionTest {
    @Test
    public void testSolution() {
        Solution s = new Solution();
        assertEquals(0, s.maxLevel(new TreeNode(5, null, null)));
        TreeNode t2 = new TreeNode(5,
            new TreeNode(4, null, null),
            new TreeNode(8, null, null));
        assertEquals(1, s.maxLevel(t2));
        PrintUtils.printTreeLevels(t2);
        assertThrows(RuntimeException.class, () -> {
            assertEquals(1, s.maxLevel(null));
        });
    }
}

