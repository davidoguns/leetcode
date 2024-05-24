#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <cstdint>

using namespace std;

//https://leetcode.com/problems/group-anagrams
class Solution {
        struct HashFunction {
            size_t operator()(string const & node) const {
                static std::hash<string> hash{};
                return hash(node);
            }
        };
        struct EqualsFunction {
            bool operator()(string const & lhs, string const & rhs) const {
                return lhs == rhs;
            }
        };
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        //O(logNchars)
        auto to_hash = [](string const &str) {
            vector<int> freq_map(26, 0); // {size_t, initial_value}
            // O(nChars)
            for_each(str.begin(), str.end(), [&freq_map](auto const& ch) {
                size_t ch_index = size_t(ch)-size_t('a');
                freq_map[ch_index] = freq_map[ch_index] + 1;
            });
            //now build string in order
            string result;
            // O(26 * log(n_chars)) ; log(n_chars) is number of times a resize might occur
            for(int ch_index = 0; ch_index < 26; ++ch_index) {
                char ch = char(ch_index + size_t('a'));
                if (freq_map[ch_index] != 0) {
                    result.append(1, ch);
                    result.append(to_string(freq_map[ch_index]));
                } 
            }
            return std::move(result);
        };
        unordered_multimap<string, string> termset;
        unordered_set<string> keyset;

        // O(Nstrs * log(nchars))
        for (auto const &str:strs) {
            auto key = to_hash(str);
            keyset.insert(key);
            termset.insert(make_pair(key, str));
        }
        // O(Nstrs)
        for (auto const &key:keyset) {
            auto range = termset.equal_range(key);
            vector<string> anagrams;
            for_each(range.first, range.second, [&anagrams](auto &entry) {
                anagrams.push_back(entry.second); 
            });
            result.push_back(std::move(anagrams));
        }
        return std::move(result);
    }

    //below approach has an integer overflow problem if strings are long and the rolling multiplication
    //results grow too large. A larger number multiplication capability could address the issue. Or would
    //need to somehow clamp the rolling hash calculation
    vector<vector<string>> groupAnagrams_faster(vector<string>& strs) {
        // actually 27 numbers here, the extra doesn't matter
        uint32_t const primes[] = { 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109,};
        vector<vector<string>> result;
        auto to_hash = [&primes](string const &str) {
            // static auto h = std::hash<uint32_t>();
            int64_t value = 1;
            for (char c:str) {
                value *= primes[size_t(c) - size_t('a')]; //use ASCII value of 'a' as 0, rest follows
            }
            return value;
        };
        unordered_multimap<int64_t, string> termset;
        unordered_set<int64_t> keyset;

        for (auto const &str:strs) {
            auto key = to_hash(str);
            keyset.insert(key);
            termset.insert(make_pair(key, str));
        }
        for (auto const &key:keyset) {
            auto range = termset.equal_range(key);
            vector<string> anagrams;
            for_each(range.first, range.second, [&anagrams](auto &entry) {
                anagrams.push_back(entry.second); 
            });
            result.push_back(std::move(anagrams));
        }

        return std::move(result);
    }
};

void print_solution(vector<vector<string>> const &output) {
    for_each(output.begin(), output.end(), [](auto &group){
        cout << "{";
        for_each(group.begin(), group.end(), [](auto &str){
            cout << "["<< str << "]";
        });
        cout << "}";
    });
}

int main(int argc, char *argv[]) {
    Solution s;
    vector<string> input = {"eat","tea","tan","ate","nat","bat"};
    print_solution(s.groupAnagrams(input));
    cout << endl;
    print_solution(s.groupAnagrams_faster(input));
    cout << endl;
    return 0;
}
