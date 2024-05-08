#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

//https://leetcode.com/problems/search-in-rotated-sorted-array/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size()-1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums.at(mid) == target) {
                return mid;
            }
            bool left_rotated = nums.at(left) > nums.at(mid);
            bool right_rotated = nums.at(mid) > nums.at(right);
            bool either_rotated = left_rotated || right_rotated;
            //both left and right cannot both be true, assertion needed
            //this invalidates an array that simply isn't sort-rotated, and is unsorted in the
            //search location
            assert(!either_rotated || !(left_rotated && right_rotated));
            
            if (!either_rotated) {
                if (target < nums.at(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            else { //means one or the other side is rotated
                //either the left side is rotated and we know it's on the right
                //or the right side is rotated and we know it's not on the left
                //these two conditions means "go right" and the others mean "go left"
                if (left_rotated) {
                    if (target > nums.at(mid) && target <= nums.at(right)) {
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                } else { //implicit right rotated, assertion
                    if (target >= nums.at(left) && target < nums.at(mid)) {
                        right = mid - 1;
                    } else {
                        left = mid + 1;
                    }
                }
            }
        }
        return -1;
    }
};

int main(int argc, char *argv[]) {
    Solution s;
    vector v1{3, 5, 1};
    // vector v2{5, 6, 7, 8, 9, 10, 1, 2, 3, 4};
    vector v3{4, 5, 6, 7, 8, 1, 2, 3};
    vector v4{7, 8, 1, 2, 3, 4, 5, 6};
    cout << "Search result index: " << s.search(v1, 3) << endl;
    // cout << "Search result index: " << s.search(v2, 8) << endl;
    cout << "Search result index: " << s.search(v3, 8) << endl;
    cout << "Search result index: " << s.search(v4, 2) << endl;
    return 0;
}
