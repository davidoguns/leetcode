#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

//https://leetcode.com/problems/perfect-squares/
class Solution {
public:
    int numSquares(int n) {
        //first generate the squares less than sqrt(n)
        int start_sqrt = floor(sqrt(n));
        vector<int> squares_desc;
        for (int idx = start_sqrt; idx > 0; --idx) {
            squares_desc.push_back(idx * idx);
        }
        //start index of squares to consider, remaining value, distance from root (tree-level)
        queue<tuple<size_t, int, int>> q;
        q.push(make_tuple(0, n, 1));
        while (!q.empty()) {
            auto const tupl = q.front();
            q.pop();
            size_t const start_sq_idx = get<0>(tupl);
            int const remaining_value = get<1>(tupl);
            int const dist_from_root = get<2>(tupl);
            for (size_t idx = start_sq_idx; idx < squares_desc.size(); ++idx) {
                int r_val_next = remaining_value - squares_desc[idx];
                if (r_val_next == 0) {
                    return dist_from_root;
                } else if (r_val_next < 0) {
                    // subtracted too far, this node cannot be a part of the path...
                } else {
                    //normal descending...but start idx has to be after this one
                    q.push(make_tuple(idx, r_val_next, dist_from_root+1));
                }
            } 
        }
        return -1; //this actually should never occur since subtracting 1 will always get us there
    }
};

int main(int argc, char *argv[]) {
    cout << "Hello leetcode!" << endl;
    Solution s;
    cout << "Solution: " << s.numSquares(100) << endl;
    cout << "Solution: " << s.numSquares(12) << endl;
    cout << "Solution: " << s.numSquares(13) << endl;
    return 0;
}
