#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

class Solution {
public:
    // https://leetcode.com/problems/next-permutation/
    void nextPermutation(vector<int>& nums) {
        //special case at the start: all the digits are sorted in descending order
        //if this is the case, then the "next" permutation is actually the first in
        //lexicographical order. 5,4,3,2,1 -> 1,2,3,4,5
        if (std::is_sorted(nums.begin(), nums.end(), std::greater<int>())) {
            std::reverse(nums.begin(), nums.end());
        } else {
            for (int firstNumIdx = 0; firstNumIdx < nums.size(); ++firstNumIdx) {
                int firstNum = nums[firstNumIdx];
                int nextLargestNumInRestIdx = -1; //index of the next largest number to the right
                for (int nextLargestScanIdx = firstNumIdx+1; nextLargestScanIdx < nums.size(); ++nextLargestScanIdx) {
                    //we need to hone on a number that's larger, but minimally so over the current digit
                    if (nums[nextLargestScanIdx] > firstNum && (nextLargestNumInRestIdx == -1 ||
                            (nums[nextLargestScanIdx] - nums[firstNumIdx]) > nums[nextLargestNumInRestIdx] - nums[firstNumIdx])) {
                        nextLargestNumInRestIdx = nextLargestScanIdx; //store index
                    }
                }

                if (nextLargestNumInRestIdx != -1) {
                    //we need to swap this number with the current one
                    int tmp = nums[nextLargestNumInRestIdx];
                    nums[nextLargestNumInRestIdx] = nums[firstNumIdx];
                    nums[firstNumIdx] = tmp;
                    //then sort the rest ascending
                    std::sort(nums.begin()+nextLargestNumInRestIdx, nums.end());
                    //and break out of the loop, we're done
                    break;
                } else { 
                    //means there are no larger numbers to the right
                    //if the numbers to the right are sorted descending...we have a problem
                    //and shouldn't have ended up here?

                }
           }
        }
    }
};

template <class T>
void print_list(const vector<T> &vec) {
    for(const T &i:vec)
    {
        cout << "[" << i << "]";
    }
}

int main(int argc, char** argv) {
    Solution s;

    vector v4{1, 3, 2};
    cout << "Next lexicographical: " << endl;
    print_list(v4);
    s.nextPermutation(v4);
    cout << endl;
    print_list(v4);
    cout << endl;

    vector v1{1, 2, 3, 4, 5};
    cout << endl;
    cout << "Next lexicographical: " << endl;
    print_list(v1);
    s.nextPermutation(v1);
    cout << endl;
    print_list(v1);
    cout << endl;

    vector v3{5, 4, 3, 2, 1};
    cout << endl;
    cout << "Next lexicographical: " << endl;
    print_list(v3);
    cout << endl;
    s.nextPermutation(v3);
    print_list(v3);
    cout << endl;

    vector v2{4, 8, 9, 3};
    cout << endl;
    cout << "Next lexicographical: " << endl;
    print_list(v2);
    s.nextPermutation(v2);
    cout << endl;
    print_list(v2);
    cout << endl;

    return 0;
}
