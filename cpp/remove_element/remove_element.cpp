#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//https://leetcode.com/problems/remove-element/
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int num_removed = 0;
        int backscan_index = 0;
        //start from the back, and swap values into the back index
        for (int index = nums.size()-1; index >= 0; --index) {
            if (nums[index] != val) {
                //look for occurence of a value to remove using backscan
                while (backscan_index < index) {
                    if (nums[backscan_index] == val) {
                        nums[backscan_index] = nums[index];
                        ++num_removed;
                        ++backscan_index;
                        break;
                    }
                    ++backscan_index;
                }
            } else {
                //if we find the value already in the back, count it as removed as well
                ++num_removed;
            }
        }
        return nums.size() - num_removed;
    }
};

void show_vector(const vector<int>& vec) {
    cout << "[";
    for_each(vec.begin(), vec.end(), [](const int &item) { cout << item << ", "; });
    cout << "]" << endl;
}

int main(int argc, char *argv[]) {
    Solution s;
    vector<int> nums1{2, 2, 3, 4, 3, 6};
    vector<int> nums2{7, 8, 7, 10, 11, 12};
    vector<int> nums3{3, 2, 2, 3};

    cout << "Solution 1: " << s.removeElement(nums1, 3) << endl;
    show_vector(nums1);
    cout << "Solution 2: " << s.removeElement(nums2, 7) << endl;
    show_vector(nums2);
    cout << "Solution 3: " << s.removeElement(nums3, 3) << endl;
    show_vector(nums3);

    return 0;
}
