#include <algorithm>
#include <iostream>

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
    TreeNode* deleteNode(TreeNode *root, int key) {
        if (root != nullptr) {
            if (root->val == key) {
                //found, now we need to replace with one of it's children
                //either the greatest value node in the left subtree,
                //or the lowest value node in the right subtree
                //let's decide on the largest value in the left substree
                if (root->left == nullptr) {
                    //if entire left subtree isn't there, the new root is the entire right subtree
                    //which might also be null (works fine)
                    return root->right;
                } else {
                    TreeNode **reparent_child = &root->left;
                    // start by going to the immediate left child
                    TreeNode *child = root->left;
                    // now traverse to the furthest right
                    while (child->right != nullptr) {
                        reparent_child = &child->right;
                        child = child->right;
                    }
                    //child is the node with a value that needs to take
                    //the place of the deleted node
                    root->val = child->val;
                    //deleted node's left is now linked the new child of what was moved up
                    (*reparent_child) = child->left;
                    //can free memory of child now, presumptive ownership of memory
                    delete child;
                    return root;
                }
            } else if(root->val > key) {
                root->left = deleteNode(root->left, key);
            } else {
                root->right = deleteNode(root->right, key);
            }
        }
        return root;
    }
};

void inorder_print(TreeNode *root) {
    if (root) {
        inorder_print(root->left);
        cout << root->val << ", ";
        inorder_print(root->right);
    }
}

int main(int argc, char *argv[]) {
    Solution s;
    TreeNode *root = new TreeNode(5, new TreeNode{3, new TreeNode{2}, new TreeNode{4}}, new TreeNode{6, nullptr, new TreeNode{7}});
    cout << "Before delete: ";
    inorder_print(root);
    cout << endl << "after delete: ";
    inorder_print(s.deleteNode(root, 3));
}
