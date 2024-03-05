#include <algorithm>
#include <iostream>
#include <limits>
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

class Solution {
public:
    // https://leetcode.com/problems/binary-tree-maximum-path-sum/description/
    int maxPathSum(TreeNode* root) {
        auto treemax = maxSum(root);
        return max(get<0>(treemax), get<1>(treemax));
    }

    //each return will be two values, 0 will be the max path that is 'connected';
    //meaning it can be continued by the parent and connected through the traversal
    //1 will be the max path of a node in isolation. We have to track them separately,
    //because it's possible a single node (path size of 1) may be the max path, but
    //its parent devalues it from being connected anywhere else positively.
    tuple<int64_t, int64_t> maxSum(TreeNode *node) {
        if (node != nullptr) {
            auto maxLeft = maxSum(node->left);
            auto maxRight = maxSum(node->right);
            //so now let's make a decision...max disconnected values
            //are one of max left or right values, or this value + left + right's connected
            auto maxDisc = max(max(get<1>(maxLeft), get<1>(maxRight)), 
                                node->val + get<0>(maxLeft) + get<0>(maxRight));
            auto maxChildren = max(get<0>(maxLeft), get<0>(maxRight));
            maxDisc = max(maxDisc, maxChildren);
            //max connected values are the max between:
            //  1 -- this value alone
            //  2 -- this value + left's connected
            //  3 -- this value + right's connected
            auto maxConnected = max<int64_t>(node->val, max(get<0>(maxLeft) + node->val, get<0>(maxRight) + node->val));
            return std::move(tuple{maxConnected, maxDisc});
        }
        return std::move(tuple{std::numeric_limits<int>::min(), std::numeric_limits<int>::min()});
    }
};

int main(int argc, char *argv[]) {
    Solution s;
    TreeNode *root = new TreeNode(-10, new TreeNode{9}, new TreeNode{20, new TreeNode{15}, new TreeNode{7}});
    TreeNode *root2 = new TreeNode(1, new TreeNode{-2}, nullptr);
    TreeNode *root3 = new TreeNode(-2, nullptr, new TreeNode{1});
    cout << "Max path sum: " << s.maxPathSum(root) << endl;
    cout << "Max path sum: " << s.maxPathSum(root2) << endl;
    cout << "Max path sum: " << s.maxPathSum(root3) << endl;
    return 0;
}
