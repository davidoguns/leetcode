#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

// https://leetcode.com/problems/3sum/
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
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
                // cout << "Examining triplet: (" << current_ival << ", " << nums[left] << "," << nums[right] << ")" << endl;
                // cout << "Examining triplet idx: (" << i << ", " << left << "," << right << ")" << endl;
                int other_sum = nums[left] + nums[right];
                int diff = current_ival + other_sum;
                if (diff == 0) {
                    //we are sitting on a triplet, add it to results
                    cout << "Adding triplet: (" << current_ival << ", " << nums[left] << ", " << nums[right] << ")" << endl;
                    result.push_back(vector{current_ival, nums[left], nums[right]});
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

            //advance i to the next "different" starting number in order to de-dup
            do {
                i++;
            } while ((i < nums.size()-2) && nums[i] == current_ival);
        }

        return result;
    }
};

int main(int argc, char** argv) {
    // vector v{-1, 0, 1, 2, -1, -4};
    Solution s;
    // vector<vector<int>> r = s.threeSum(v);
    // vector v2{0, 0, 0};
    // vector<vector<int>> r2 = s.threeSum(v2);
    vector v3{1,2,0,1,0,0,0,0};
    vector<vector<int>> r3 = s.threeSum(v3);
    return 0;
}
