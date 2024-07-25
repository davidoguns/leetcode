#include <iostream>
#include <ostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        if (k > nums.size()) {
            return -1;
        }
        //O(N) to build this. For optimized PQs O(1) insertion occurs
        //but may be O(logN). Numerical data should be O(1)
        priority_queue<int> numspq(nums.begin(), nums.end());

        //remove K elements
        for (size_t i = 1; i < k; ++i) {
            //O(log N)
            numspq.pop();
        }

        return numspq.top();;
    }
};

int main(int argc, char *argv[]) {
    Solution s;
    vector<int> vec1{3, 2, 1, 5, 6, 4};
    cout << "Kth largest: " << s.findKthLargest(vec1, 2) << endl;
    vector<int> vec2{3, 2, 3, 1, 2, 4, 5, 5, 6};
    cout << "Kth largest: " << s.findKthLargest(vec2, 4) << endl;
    return 0;
}
