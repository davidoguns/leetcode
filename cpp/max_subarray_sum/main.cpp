#include <iostream>
#include <vector>

using namespace std;
 
// https://leetcode.com/problems/maximum-subarray/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) return 0;
        int max_sum = nums[0];
        int max_current = nums[0];
        for (size_t start = 1; start < nums.size(); ++start) {
            max_current = max(nums[start], max_current + nums[start]);
            if (max_current > max_sum) {
                max_sum = max_current;
            }
        }
        return max_sum;
    }
};

int main(int argc, char *argv[]) {
    Solution s;
    vector<int> input1{-2,1,-3,4,-1,2,1,-5,4};
    cout << "Maximum sum: " << s.maxSubArray(input1) << endl;

    return 0;
}

