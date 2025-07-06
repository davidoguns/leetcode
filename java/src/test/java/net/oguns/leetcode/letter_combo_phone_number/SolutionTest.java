package net.oguns.leetcode.letter_combo_phone_number;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;
import net.oguns.leetcode.letter_combo_phone_number.Solution;

public class SolutionTest {
    @Test
    public void testSolution() {
        Solution s = new Solution();
        s.letterCombinations("23").stream().forEach(combo -> System.out.println("Item: " + combo));
    }
}
