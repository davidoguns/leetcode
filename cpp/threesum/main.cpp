#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>

using std::vector;
using std::set;
using std::tuple;
using std::get;

// https://leetcode.com/problems/3sum/
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<tuple<int, int, int>> result_set;
        vector<vector<int>> result;
        if (nums.size() < 3) {
            return result;
        }
        // O(nlogn) sort
        std::sort(nums.begin(), nums.end());
        int i = 0;

        while ((i < nums.size()-2) && nums[i] <= 0) {
            int current_ival = nums[i];
            int left = i + 1;
            int right = nums.size() - 1;

            // zero in on the next two numbers that when added to the nums[i] == 0
            while (left < right) {
                int other_sum = nums[left] + nums[right];
                int diff = current_ival + other_sum;
                if (diff == 0) {
                    //we are sitting on a triplet, add it to result set for de-dup
                    result_set.insert(std::make_tuple(current_ival, nums[left], nums[right]));
                    ++left;
                    --right;
                } else if (diff < 0) {
                    //means we need to advance left
                    ++left;
                } else if (diff > 0) {
                    //means we need to pull back from the right
                    --right;
                }
            }

            //advance i to the next "different" starting number in order to help de-dup
            //technically this is not necessary since we are adding to set, but it skips iterations
            do {
                i++;
            } while ((i < nums.size()-2) && nums[i] == current_ival);
        }

        //unpack result_set into result structure
        std::for_each(result_set.begin(), result_set.end(), [&result](auto const& tpl) {
            result.push_back(vector{get<0>(tpl), get<1>(tpl), get<2>(tpl)});
        });

        return result;
    }
};

int main(int argc, char** argv) {
    vector v{-1, 0, 1, 2, -1, -4};
    Solution s;
    vector<vector<int>> r = s.threeSum(v);
    vector v2{0, 0, 0};
    vector<vector<int>> r2 = s.threeSum(v2);
    vector v3{1,2,0,1,0,0,0,0};
    vector<vector<int>> r3 = s.threeSum(v3);
    return 0;
}
