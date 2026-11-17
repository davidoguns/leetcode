#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

template <class T>
void print_solution(vector<vector<T>> const &solution) {
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

template <class T>
void print_list(const vector<T> &vec) {
    for(const T &i:vec)
    {
        cout << "[" << i << "]";
    }
}

// https://leetcode.com/problems/subsets-ii
// this variant requires de-duping
class Solution {
    public:
        //observed pattern on whiteboard:
        //when adding a number to the power set, we are going to do the same as we did
        //with normal power set generation with exceptions:
        // 1) if the prior added subset contains the number we are adding, do NOT consider it 
        // 2) For each number to build with, look at the list of "prior adds" completed with that number as if
        //    those numbers were in the set. What this looks like with example:
        //
        //    Powerset contains: { (), (1), (1,2), 2) } and we are considering adding a '2'
        //    Normal building would result in: { (), (1), (1,2), (2), (2), (1,2), (2,2), (1,2,2) }
        // We can see that (1,2), and (2) are now duplicative. Why? Because they already had a "2"
        // in them. 
        //    Correctly de-duped powerset is: { (), (1), (1,2), (2), (2, 2), (1,2,2) }
        // Instead of removing duplicates, we will not add them in the normal pass, 
        // knowing that 2 already added those two sets; and this is true no matter how many times 2 is
        // added. We only "build" by considering what was last added via the number the most recent
        // time. In this case the prior sets added by '2' were {(2), (1, 2)} and thus would add:
        // {(2,2), (1,2,2)} on top of 'only' {(), (1)}
        vector<vector<int>> subsets(vector<int>& nums) {
            //powersets size are 2^N for number of elements. We know we will fill since
            //there is no de-duping given the inputs are unique.
            //we could "right size" this with a reservation for optimization
            vector<vector<int>> results{};
            map<int, vector<vector<int>>> prior_add_map;
            vector<int> empty_set;
            results.push_back(empty_set);

            for (int const& num : nums) {
                cout << "input num: " << num << endl;
                //new sets to add at the end of this iteration
                vector<vector<int>> new_sets_to_add;

                for (auto existingResultsItr = results.begin(); existingResultsItr != results.end(); ++existingResultsItr) {
                    auto existingSet = *existingResultsItr;
                    //is there a way to optimize this check? Prior adds must not be an actual set so building one
                    //is extra work. This optimization is more worth it if we're adding the same number a lot
                    bool containsNum = false;
                    std::for_each(existingSet.begin(), existingSet.end(),[&](auto &n) { if (num == n) containsNum = true; });

                    if (containsNum) continue; //skip, otherwise, do the normal powerset add

                    //copy it, and add the current number
                    vector<int> newset;
                    //we need exactly one over the size of what we're adding to
                    newset.reserve(existingSet.size() + 1);
                    //add the previous set
                    newset.insert(newset.begin(), existingSet.begin(), existingSet.end());
                    //add new element
                    newset.push_back(num);
                    new_sets_to_add.push_back(newset);
                }

                vector<vector<int>> new_sets_to_add_from_prior;
                //now that we've safely added what won't generate duplicates
                //check what the prior adds for this number were, if there are any
                //reference to the set of previous adds from this number, if we've seen it before
                auto add_set_itr = prior_add_map.find(num);
                vector<vector<int>> new_prior_add_set;
                if (add_set_itr != prior_add_map.end()) {
                    cout << "seeing " << num << " again. Prior add:";
                    print_solution(add_set_itr->second);
                    cout << endl;
                    for (auto priorSetItr = add_set_itr->second.begin(); priorSetItr != add_set_itr->second.end(); ++priorSetItr) {
                        auto priorSet = *priorSetItr;
                        vector<int> newset;
                        newset.reserve(priorSet.size() + 1);
                        //add the previous set
                        newset.insert(newset.begin(), priorSet.begin(), priorSet.end());
                        //add new, duplicative element
                        newset.push_back(num);
                        //add to the sets to add
                        new_sets_to_add_from_prior.push_back(newset);
                    }
                    results.insert(results.end(), new_sets_to_add_from_prior.begin(), new_sets_to_add_from_prior.end());
                    prior_add_map[num] = new_sets_to_add_from_prior;
                } else {
                    //and now ensure this is the newest consideration if the number is added again
                    prior_add_map.insert(make_pair(num, new_sets_to_add));
                    //add to results
                    results.insert(results.end(), new_sets_to_add.begin(), new_sets_to_add.end());
                }
            }
            return results;
        }
};

int main(int argc, char** argv) {
    Solution s;

    // vector v1{1, 2, 3, 4};
    // auto r1 = s.subsets(v1);
    // cout << "Solution: ";
    // print_solution(r1);
    // cout << endl;
    //
    // vector v2{1, 2, 3, 4, 4};
    // auto r2 = s.subsets(v2);
    // cout << "Solution: ";
    // print_solution(r2);
    // cout << endl;
    //
    // vector v3{1, 2, 2};
    // auto r3 = s.subsets(v3);
    // cout << "Solution: ";
    // print_solution(r3);
    // cout << endl;
    //
    // vector v4{5, 5, 5, 5, 5};
    // auto r4 = s.subsets(v4);
    // cout << "Solution: ";
    // print_solution(r4);
    // cout << endl;

    vector v5{4, 4, 4, 1, 4};
    auto r5 = s.subsets(v5);
    cout << "Solution: ";
    print_solution(r5);
    cout << endl;

    return 0;
}
