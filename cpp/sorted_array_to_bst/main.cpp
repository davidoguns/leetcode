#include <vector>

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

// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
class Solution {
private:
    //core functionality is implemented via helper function
    //that caries the logic recursively, with a different signature
    TreeNode* sortedArrayToBST(
            vector<int>& nums,
            int index,
            int min_idx,
            int max_idx) {
        if (nums.empty() || !(index >= min_idx && index < max_idx)) {
            return nullptr;
        }
        else {
            TreeNode *node  = new TreeNode(nums[index],
                    sortedArrayToBST(nums, (min_idx + index) / 2, min_idx, index),
                    sortedArrayToBST(nums, (max_idx + index) / 2, index + 1, max_idx));
            return node;
        }
    }

public:
    //must be height balanced
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBST(nums, nums.size() / 2, 0, nums.size());
    }
};

int main(int argc, char **argv) {
    Solution s;
    vector<int> v1{-10, -3, 0, 5, 9};
    TreeNode *bst = s.sortedArrayToBST(v1);

    return 0;
}

