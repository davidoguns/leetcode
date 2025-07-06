#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        bool carried = true;
        for (auto digit_itr = digits.rbegin(); carried && digit_itr != digits.rend(); ++digit_itr) {
            ++(*digit_itr);
            if (*digit_itr == 10) {
                *digit_itr = 0;
            }
            else {
                carried = false;
            }
        }
        if (carried) {
            //means we carried past the most significant digit
            vector<int> newCapacity;
            newCapacity.push_back(1);
            newCapacity.insert(newCapacity.end(), digits.begin(), digits.end());
            return std::move(newCapacity); //rvo?
        }
        return digits;
    }
};

void show_vector(const vector<int>& vec) {
    cout << "[";
    for_each(vec.begin(), vec.end(), [](const int &item) { cout << item << ", "; });
    cout << "]" << endl;
}

int main(int argc, char *argv[]) {
    Solution s;
    vector<int> nums1{5, 4, 3};
    vector<int> nums2{9, 9, 9};
    vector<int> nums3{1, 2, 3};

    show_vector(s.plusOne(nums1));
    show_vector(s.plusOne(nums2));
    show_vector(s.plusOne(nums3));

    return 0;
}
