package net.oguns.leetcode.letter_combo_phone_number;

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

class Solution {
    Map<Character, String> digitToLetters = new HashMap<>() {{
        put('2', "abc");
        put('3', "def");
        put('4', "ghi");
        put('5', "jkl");
        put('6', "mno");
        put('7', "pqrs");
        put('8', "tuv");
        put('9', "wxyz");
    }};
    public List<String> letterCombinations(String digits) {
        List<String> working = new LinkedList<>();
        List<String> nextStep = new LinkedList<>();
        Iterator<Integer> charItr = digits.chars().iterator();
        while (charItr.hasNext()) {
            char ch = (char)charItr.next().intValue();
            String nextLetters = digitToLetters.get(ch);
            nextStep = new LinkedList<>();
            if (working.isEmpty()) {
                //first one just populates
                Iterator<Integer> nextCharItr = nextLetters.chars().iterator();
                while (nextCharItr.hasNext()) {
                    char nextCh = (char)nextCharItr.next().intValue();
                    nextStep.add(String.valueOf(nextCh));
                }
            } else {
                //we need to amend each item with working, with each character in next step
                for(String prior_content:working) {
                    Iterator<Integer> nextCharItr = nextLetters.chars().iterator();
                    while (nextCharItr.hasNext()) {
                        char nextCh = (char)nextCharItr.next().intValue();
                        nextStep.add(prior_content + nextCh);
                    }
                }
            }
            working = nextStep; 
        }
        return working;
    }
}
