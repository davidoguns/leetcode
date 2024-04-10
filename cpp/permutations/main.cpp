#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

//https://leetcode.com/problems/permutations
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

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if (nums.size() == 1 || nums.empty()) {
            return vector<vector<int>>{nums};
        }
        vector<vector<int>> result;
        result.reserve(factorial(nums.size()));
        list<size_t> prefix;
        list<size_t> rest;
        for (size_t idx = 0; idx < nums.size(); ++idx) {
            rest.push_back(idx);
        }

        permute(nums, prefix, rest, result);
        return result;
    }

    int factorial(uint n) {
        if (n <= 1) {
            return 1;
        }
        else {
            return n * factorial(n-1);
        }
    }

    void permute(const vector<int>& nums, const list<size_t>& prefix, const list<size_t> &rest, vector<vector<int>> &result) {
        if (rest.size() == 1 || rest.size() == 0) {
            result.push_back(std::move(resolve_indices(nums, prefix, rest)));
        }
        else {
            //need to copy prefix for this local call frame
            list<size_t> local_prefix(prefix);
            list<size_t> local_rest(rest);
            //rotate through rest indices, it'll stay constant size at the end of loop iterations
            for (size_t start_idx = 0; start_idx < rest.size(); ++start_idx) {
                local_prefix.push_back(local_rest.front());
                local_rest.pop_front();

                permute(nums, local_prefix, local_rest, result);

                local_rest.push_back(local_prefix.back());
                local_prefix.pop_back(); // vector<T>::rend() not compatible type for erase
            }
        }
    }

    vector<int> resolve_indices(const vector<int>& nums, const list<size_t>& prefix, const list<size_t>& suffix) {
        vector<int> result;
        result.reserve(prefix.size() + suffix.size());
        for_each(prefix.begin(), prefix.end(), [&nums, &result](auto const &idx) {
            result.push_back(nums[idx]);
        });
        for_each(suffix.begin(), suffix.end(), [&nums, &result](auto const &idx) {
            result.push_back(nums[idx]);
        });
        return std::move(result);
    }
};

int main(int argc, char *argv[]) {
    Solution s;
    vector<int> input1{1, 2, 3};
    print_solution(s.permute(input1));
    vector<int> input2{4, 5, 6};
    print_solution(s.permute(input2));
    vector<int> input3{6};
    print_solution(s.permute(input3));
    return 0;
}
