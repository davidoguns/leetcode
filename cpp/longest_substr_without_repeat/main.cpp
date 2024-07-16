#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//https://leetcode.com/problems/longest-substring-without-repeating-characters/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        //store a "set" of indices of when a character was last seen in the current "run"
        //-1 means it hasn't been seen, anything else means it has, and that is the index.
        //We need to keep track of the index because it prevents us from having to go back
        //too far once a double is found. We only need to revert back to the prior occurence
        //of a doubled character.
        //we can do this in a small sized vector (128) because characters in s are limited
        //entirely under ASCII character rules
        vector<int16_t> chset(128, -1);

        int start_index = 0;
        int max_length = 0;
        int curr_length = 0;
        for (size_t curr_idx = 0; curr_idx < s.length(); ++curr_idx) {
            char ch = s.at(curr_idx);
            if (chset.at(size_t(ch)) == -1) {
                curr_length++;
                chset[size_t(ch)] = curr_idx;
            } else {
                curr_idx = chset.at(size_t(ch)) + 1;
                chset = vector<int16_t>(128, -1);
                //reset to next character
                chset[size_t(s.at(curr_idx))] = curr_idx;
                //reset tracking length
                if (max_length < curr_length) {
                    max_length = curr_length;
                }
                curr_length = 1;
            }
        }
        if (curr_length > max_length) {
            max_length = curr_length;
        }

        return max_length;
    }
};

int main(int argc, char *argv[]) {
    Solution s;

    cout << "Length: " << s.lengthOfLongestSubstring("abcabcbb") << endl;
    cout << "Length: " << s.lengthOfLongestSubstring("bbbbb") << endl;
    cout << "Length: " << s.lengthOfLongestSubstring("pwwkew") << endl;
    return 0;
}
