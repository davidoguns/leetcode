#include <iostream>
#include <vector>

using namespace std;

//https://leetcode.com/problems/jump-game/
class Solution {
public:
    bool canJump(vector<int>& nums) {
        //keep track of a "high water" mark that is the highest index we can "check" for
        //if it equal to the length (or higher than), then we can jump to the end
        size_t high_limit = nums[0];
        //mark the last index we added a high jump limit from,
        //this can only go up and should be less than high limit
        size_t curr_mark = 0;
        while (curr_mark <= high_limit && curr_mark < nums.size()) {
            size_t new_limit = curr_mark + nums[curr_mark];
            if (new_limit > high_limit) {
                //found a new higher limit
                high_limit = new_limit;
            }
            ++curr_mark;
        }
        return high_limit >= (nums.size()-1);
    }
};

int main(int argc, char *argv[]) {
    Solution s;
    vector<int> jumpvec{2, 3, 1, 1, 4}; 
    cout << "Can jump? " << s.canJump(jumpvec) << endl;
    vector<int> jumpvec2{3, 2, 1, 0, 4}; 
    cout << "Can jump? " << s.canJump(jumpvec2) << endl;
    return 0;
}
