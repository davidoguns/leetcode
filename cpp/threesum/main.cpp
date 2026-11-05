#include <iostream>
#include <vector>
#include <tuple>
#include <set>

using std::vector;
using std::set;
using std::tuple;

// https://leetcode.com/problems/3sum/
class Solution {
public:
    tuple<int,int,int> getSortedTuple(int i, int j, int k) {
        using std::make_tuple;
        if (i <= j && j <= k) {
            return make_tuple(i, j, k);
        } else if (i <= k && k <= j) {
            return make_tuple(i, k, j);
        } else if (j <= i && i <= k) {
            return make_tuple(j, i, k);
        } else if (j <= k && k <= i) {
            return make_tuple(j, k, i);
        } else if (k <= i && i <= j) {
            return make_tuple(k, i, j);
        } else if (k <= j && j <= i) {
            return make_tuple(k, j, i);
        } else {
            std::exit(1);
        }
        // result_set.insert(std::make_tuple(i, j, k));
        // result_set.insert(std::make_tuple(i, k, j));
        // result_set.insert(std::make_tuple(j, i, k));
        // result_set.insert(std::make_tuple(j, k, i));
        // result_set.insert(std::make_tuple(k, i, j));
        // result_set.insert(std::make_tuple(k, j, i));
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        set<tuple<int, int, int>> result_set;
        vector<vector<int>> result;
        if (nums.size() < 3) {
            return result;
        }
        for (int i = 0; i < (nums.size()-2); ++i) {
            for (int j = i+1; j < (nums.size()-1); ++j) {
                for (int k = j+1; k < (nums.size()); ++k) {
                    if ((nums[i] + nums[j] + nums[k]) == 0) {
                        tuple<int, int, int> result_tuple = getSortedTuple(nums[i], nums[j], nums[k]);
                        //ignore if we've seen this triplet
                        if (result_set.find(result_tuple) == result_set.end()) {
                            result.push_back(vector{nums[i], nums[j], nums[k]});
                            result_set.insert(result_tuple);
                        }
                    }
                }
            }
        }

        return result;
    }
};

int main(int argc, char** argv) {
    using std::cout;
    using std::endl;
    cout << "Hello leetcode" << endl;

    vector v(20, 3);
    Solution s;
    vector<vector<int>> r = s.threeSum(v);
    return 0;
}
