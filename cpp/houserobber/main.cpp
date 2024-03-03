#include <iostream>
#include <algorithm>
#include <tuple>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// https://leetcode.com/problems/house-robber-iii/submissions/1193059080/
class Solution {
public:
    int rob(TreeNode* root) {
        auto sums = get_both_sums(root);
        return std::max(get<0>(sums), get<1>(sums));
    }

    // return tuple that says what the maximum value of a subtree is if
    // it is included get<0>(node) or isn't included get<1>(node)
    tuple<int, int> get_both_sums(TreeNode *node) {
        if (node == nullptr) {
            return std::move(tuple{0, 0});
        }
        else {
            tuple<int, int> both_sums_left = get_both_sums(node->left);
            tuple<int, int> both_sums_right = get_both_sums(node->right);

            //now we have a few combinations to care about:
            //1 - this is included, only check the max value when adding each 
            //    child nodes sums when not included, however low
            int included_max = node->val + get<1>(both_sums_left) + get<1>(both_sums_right);
            //2 - this node is NOT included, so we have to take the maximums of either child
            int not_included_max = std::max(get<0>(both_sums_right), get<1>(both_sums_right)) +
                            std::max(get<0>(both_sums_left), get<1>(both_sums_left));
            return std::move(tuple{included_max, not_included_max});
        }
    }
};

int main(int argc, char *argv[]) {
    Solution s;

    cout << "Solution: " << s.rob(nullptr) << endl;
    cout << "Solution: " << s.rob(new TreeNode{3, new TreeNode{2, nullptr, new TreeNode{3}}, new TreeNode{3, nullptr, new TreeNode{1}}}) << endl;
    return 0;
}
