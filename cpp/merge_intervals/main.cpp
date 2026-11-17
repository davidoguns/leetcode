#include <algorithm>
#include <iostream>
#include <pstl/glue_algorithm_defs.h>
#include <vector>

using namespace std;



void print_solution(vector<vector<int>> const &solution) {
    using namespace std;
    cout << "{";
    for_each(solution.begin(), solution.end(), [](auto i) {
        cout << "[";
        for_each(i.begin(), i.end(), [](auto j) {
            cout << j << ",";
        });
        cout << "], ";
    });
    cout << "}" << endl;
}

// in progress: current thought is this overall modeling-approach doesn't work
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            vector<vector<int>> v;
            vector<int> empty;
            v.push_back(empty);
            return v;
        }

        auto fn_ranges_overlap = [](vector<int> const& r1, vector<int> const& r2) -> bool {
            //we are overlapping if we are "not" non-overlapping
            return (!(r1[0] > r2[1] || r1[1] < r2[0]));
        };
        auto fn_merge_ranges = [](vector<int> &out, vector<int> const& r1, vector<int> const& r2) {
            //assumption is that the ranges absolutely overlap, otherwise this logic
            //can't be correct. It'll expand the range to both, and everything inbetwee
            int begin = std::min<int>(r1[0], r2[0]);
            int end = std::max<int>(r1[1], r2[1]);
            //writing this function like this to allow &out usage to overlap with the same
            //vector reference as either r1 or r2 and still work correctly. We are successively calling
            //and updating -> merging range
            out[0] = begin;
            out[1] = end;
        };

        vector<vector<int>> result;
        vector<vector<int>> inputCpy(intervals);
        std::sort(inputCpy.begin(), inputCpy.end(), [](auto &r1, auto r2) { return r1[0] < r2[0]; });

        cout << "input cpy size: " << inputCpy.size() << endl;
        auto intervalItr = inputCpy.begin();
        while (intervalItr != inputCpy.end()) {
            vector<int> r1 = *intervalItr;
            cout << " looking at range: (" << r1[0] << ", " << r1[1] << ")" << endl;
            //initialize what we're going to get as just this interval
            vector<int> r_merged{r1};
            //we are going to "merge in" all elements to the right, erasing them from the vector as we go
            auto eraseItr = intervalItr + 1;
            while (eraseItr != inputCpy.end()) {
                vector<int> r2 = *eraseItr;
                cout << "looking if overlap with: (" << r2[0] << ", " << r2[1] << ")" << endl;
                if (fn_ranges_overlap(r_merged, r2)) {
                    cout << "found overlap with: (" << r2[0] << ", " << r2[1] << ")" << endl;
                    fn_merge_ranges(r_merged, r_merged, r2);
                    cout << "merged range: (" << r2[0] << ", " << r2[1] << ")" << endl;
                    //advance based on the erase
                    eraseItr = inputCpy.erase(eraseItr);
                } else {
                    eraseItr++;
                }
            }
            result.push_back(r_merged);
            //test: can we advance the iterator that defintely wasn't erased?
            intervalItr++;
        }
        return result;
    }
};

int main(int argc, char** argv) {
    /*
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    auto itr = v.begin();
    while ((itr = std::find_if(++itr, v.end(), [](int i) { return i % 3 == 0; })) != v.end()) {
        cout << "find if iteration: " << *itr << endl;
    }
    */
    Solution s;

    vector<vector<int>> intervals1;
    vector<int> a1 = {1, 3}, a2 = {2, 6}, a3 = {8, 10}, a4 = {15, 18};
    intervals1.push_back(a1);
    intervals1.push_back(a2);
    intervals1.push_back(a3);
    intervals1.push_back(a4);
    cout << "Solution: ";
    print_solution(s.merge(intervals1));
    cout << endl;

    vector<vector<int>> intervals2;
    vector<int> b1 = {1, 4}, b2 = {0, 2}, b3 = {3, 5};
    intervals2.push_back(b1);
    intervals2.push_back(b2);
    intervals2.push_back(b3);
    cout << "Solution: ";
    print_solution(s.merge(intervals2));
    cout << endl;

    return 0;
}
