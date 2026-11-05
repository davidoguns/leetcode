#include <iostream>

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
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        return isSymmetric(root->left, root->right);
    }

    bool isSymmetric(TreeNode* left, TreeNode* right) {
        // if left and right are the same node, there's actually a probem
        // this check is really meant to check if both are nullptr.
        if (left == right ) return true;
        if (left == nullptr) return false;
        if (right == nullptr) return false;
        //now we know both are at least non-null nodes with values
        return (left->val == right->val
                && isSymmetric(left->right, right->left)
                && isSymmetric(left->left, right->right));
    } 
};

int main(int argc, char** argv) {
    using std::cout;
    using std::endl;
    Solution s;
    
    cout << "IsSymmetric: " << s.isSymmetric(nullptr) << endl;
    cout << "IsSymmetric: " << s.isSymmetric(new TreeNode(5)) << endl;
    cout << "IsSymmetric: " << s.isSymmetric(new TreeNode(5, new TreeNode(4), new TreeNode(6))) << endl;
    cout << "IsSymmetric: " << s.isSymmetric(new TreeNode(5, new TreeNode(5), new TreeNode(5))) << endl;
    return 0;
}
