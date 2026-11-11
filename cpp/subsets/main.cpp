#include <cmath>
#include <vector>

using namespace std;

class Solution {
    public:
        vector<vector<int>> subsets(vector<int>& nums) {
            //powersets size are 2^N for number of elements. We know we will fill since
            //there is no de-duping given the inputs are unique.
            //we could "right size" this with a reservation for optimization
            vector<vector<int>> results{};
            vector<int> empty_set;
            results.push_back(empty_set);
            //for each element, take what's already in the list, and add the new number to the list
            int num_added = 1;
            for (int const& num : nums) {
                vector<vector<int>> new_sets_to_add;
                for(auto priorSetItr = results.begin(); priorSetItr != results.end(); ++priorSetItr) {
                    auto priorSet = *priorSetItr;
                    //copy it, and add the current number
                    vector<int> newset;
                    //we need exactly one over the size of what we're adding to
                    newset.reserve(priorSet.size() + 1);
                    //add the previous set
                    newset.insert(newset.begin(), priorSet.begin(), priorSet.end());
                    //add new element
                    newset.push_back(num);
                    new_sets_to_add.push_back(newset);
                }
                results.insert(results.end(), new_sets_to_add.begin(), new_sets_to_add.end());
            }
            return results;
        }
};

int main(int argc, char** argv) {
    Solution s;
    vector v1{1, 2, 3, 4};
    auto r1 = s.subsets(v1);

    return 0;
}
