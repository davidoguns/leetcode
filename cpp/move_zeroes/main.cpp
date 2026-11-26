#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// https://leetcode.com/problems/move-zeroes/
class Solution {
public:
    //not the fastest with the rotates, but clean and clear
    void moveZeroes(vector<int>& nums) {
        for (int idx = 0; idx < nums.size(); ++idx) {
            if (nums[idx] == 0) {
                //find the next non-zero rotate it up to here; if there isn't one, we're done
                auto first_non_zero = std::find_if(nums.begin() + idx + 1, nums.end(), [](auto& num) { return num != 0; });
                if (first_non_zero != nums.end()) {
                    std::rotate(nums.begin() + idx, first_non_zero, nums.end());
                } else {
                    return;
                }
            }
        }
    }
};

template <class T>
string string_print_list(const vector<T> &vec) {
    stringstream ss;
    ss << "[";
    for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
        ss << *itr;
        if ((itr + 1) != vec.end()) {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

//dumping this abstract utility function here that
//should have been used for so many other problems
template <class T>
string string_print_list_list(const vector<vector<T>> &vec) {
    stringstream ss;
    ss << "[";
    for (auto itr = vec.begin(); itr != vec.end(); ++itr) {
        ss << string_print_list(*itr);
        if ((itr + 1) != vec.end()) {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

int main(int argc, char** argv) {
    Solution s;
    vector<int> v1{0, 0, 1};
    s.moveZeroes(v1);
    cout << "Zeroes moved: " << string_print_list(v1) << endl;

    return 0;
}
