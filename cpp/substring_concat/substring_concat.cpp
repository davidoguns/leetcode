#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

template <class T>
void print_list(const vector<T> &vec)
{
  for(const T &i:vec)
  {
    cout << i << endl;
  }
}

// https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ret;
        if (words.empty()) {
            return vector<int>{}; //no words to find
        }
        if ((words.at(0).length() * words.size()) > s.length()) {
            return vector<int>{}; //string is too small to contain all substrings even once
        }
        //now we can work
        vector<bool> word_matches;
        size_t num_words = words.size();
        size_t word_length = words.at(0).length();
        const size_t last_possible_start = s.length() - (word_length * num_words);

        for (size_t start_char_index = 0; start_char_index < last_possible_start; ++start_char_index) {
            vector<string> word_candidates;

            //build words first
            for (size_t wc_index = 0; wc_index < num_words; ++wc_index) {
                word_candidates.push_back(s.substr(start_char_index + (wc_index * word_length), word_length));
            }
            // cout << "Word candidates: (" << start_char_index << ")" << endl;
            // print_list(word_candidates);

            //naive first, removing from array isn't too efficient, but honestly not bad if it's a small collection
            //mathematically, I'm looking for word_candidates with 1 to 1 relationship with words, but they aren't sets
            //native implementation just removes from word candidates individually
            size_t words_matched = 0;
            for_each(words.begin(), words.end(), [&words_matched, &word_candidates](string const &word) {
                auto itr = std::find(word_candidates.begin(), word_candidates.end(), word);
                if (itr != word_candidates.end()) {
                    ++words_matched;
                    //remove instance (could have duplicate word)
                    word_candidates.erase(itr);
                }
            });
            if (word_candidates.empty()) {
                ret.push_back(start_char_index);
            }
        }

       return std::move(ret);
    }
};

int main(int argc, char* argv[]) {
    Solution s;
    vector<string> words = vector{string{"foo"}, string{"bar"}};
    string str{"barfoothefoobarman"};
    cout << "Solution #1" << endl;
    print_list(s.findSubstring(str, words));

    vector<string> words2 = vector{string{"foo"}, string{"bar"}, string{"the"}};
    cout << "Solution #2" << endl;
    print_list(s.findSubstring("barfoofoobarthefoobarman", words2));

    vector<string> words3 = vector{string{"word"}, string{"good"}, string{"best"}, string{"good"}};
    cout << "Solution #3" << endl;
    print_list(s.findSubstring("wordgoodgoodgoodbestword", words3));
}
