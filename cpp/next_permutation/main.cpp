#include <iostream>
#include <iterator>
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
        if (std::is_sorted(nums.rbegin(), nums.rend())) {
            std::reverse(nums.begin(), nums.end());
        } else {
            //first part is finding the first two adjacent digits from the "right", scanning to the right,
            //that descend. In 12345, the 4 and 5 read 5 and 4, and are descending. They need to be swapped.
            //In this simple case, 12345 becomes 12354, which is the next number; but it isn't everything
            //Take 4893. Doing this first part gets us to 4983. Which is later lexicographically, but isn't 
            //next because it isn't the smallest. What then need to happen is the rest of the digits need
            //to be sorted in ascending order to ensure it's the minimum value.
            
            // auto numsItr = nums.begin();
            // while (numsItr != nums.end() && (numsItr+1) != nums.end()) {
            //     int smallestIndexAfter = -1; //retaining -1 means nothing after this digit is smaller
            //     auto swapTarget = std::find_if(numsItr+1, nums.end(), [&](auto const &num) { num < *numsItr; });
            //
            // }

            auto numsRevItr = nums.rbegin();
            decltype(numsRevItr) numsRevItrNext = nums.rbegin();
            while (numsRevItr != nums.rend() && (numsRevItr+1) != nums.rend()) {
                numsRevItrNext = numsRevItr+1;
                if (numsRevItrNext != nums.rend()) {
                    if (*numsRevItr > *numsRevItrNext) {
                        //swap the numbers
                        int tmpNum = *numsRevItr;
                        *numsRevItr = *numsRevItrNext;
                        *numsRevItrNext = tmpNum;
                        //exit the loop as well
                        break;
                    }
                } else {
                    //done with loop b/c we've reached the start
                    //I think this handles the special case a normal
                    break;
                }
                ++numsRevItr;
            }
            //from numsRevItr to the actual end, we need to sort. We need to do
            //some conversions so we can use std::sort which requires equivalent
            
            //the location of the iterator (exclusive), and the range towards
            //the natural end of the vector needs to be sorted
            if (numsRevItr != nums.rbegin()) {
                std::sort(nums.rbegin(), numsRevItrNext, std::greater<int>());
            }
        }
    }
};

template <class T>
void print_list(const vector<T> &vec)
{
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
