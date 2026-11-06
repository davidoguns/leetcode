#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>
#include <cmath>

using std::vector;
using std::optional;

// https://leetcode.com/problems/3sum-closest/ 
class Solution {
    int threeSumClosest(vector<int>& nums, int target) {
        if (nums.size() < 2) std::exit(1); //there aren't three indices to look at
        int closest_sum = nums[0] + nums[1] + nums[2];
        // O(nlogn) sort
        std::sort(nums.begin(), nums.end());
        // set up three pointers. Left and right bounds are going to 'creep in'
        // Early exit is hitting the target dead on
       
        for (int i = 0; i < (nums.size() - 2); ++i) {
            if (i > 0 && nums[i] == nums[i-1]) continue;
            int left = i + 1;
            int right = nums.size()-1;

            while (left < right) {
                int current_sum = nums[i] + nums[left] + nums[right];

                if (current_sum == target) return current_sum;

                if (abs(target - current_sum) < abs(target - closest_sum)) {
                    closest_sum = current_sum;
                }

                if (current_sum < target) {
                    ++left;
                } else {
                    --right;
                }
            }
        }

        //shouldn't need to exercise the optional
        return closest_sum;
    }
public:
};

int main(int argc, char** argv) {
    using std::cout;
    using std::endl;

    vector v{-1, 0, 1, 2, -1, -4};
    vector v2{4,0,5,-5,3,3,0,-4,-5};
    vector v3{-4,2,2,3,3,3};
    vector v4{-1,2,1,-4};
    Solution s;
    // cout << "Closest sum: " << s.threeSumClosest(v, 2) << endl;
    // cout << "Closest sum: " << s.threeSumClosest(v, -7) << endl;
    cout << "Closest sum: " << s.threeSumClosest(v4, 0) << endl;
    return 0;
}
