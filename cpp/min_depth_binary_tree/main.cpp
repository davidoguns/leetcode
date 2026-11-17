#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

/*
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
        int minDepth(TreeNode* root) {
            if (root == nullptr) return 0;
            bool levelHasLeaf = false;
            int depth = 1;
            queue<tuple<TreeNode*, int>> q;
            q.push(make_tuple(root, 1));

            while (!q.empty()) {
                tuple<TreeNode*, int> front = q.front();
                q.pop();
                TreeNode *node = get<0>(front);
                int nodeDepth = get<1>(front);
                
                if (nodeDepth != depth) {
                    //just arrived at this depth, did the last level have a leaf?
                    if (levelHasLeaf) {
                        //if so, we're done. return early
                        return depth;
                    }
                    //otherwise, we're still looking
                    depth = nodeDepth;
                }

                if (node->left == nullptr && node->right == nullptr) {
                    levelHasLeaf = true;
                }

                //add available children
                if (node->right != nullptr) {
                    q.push(make_tuple(node->right, depth + 1));
                }
                if (node->left != nullptr) {
                    q.push(make_tuple(node->left, depth + 1));
                }
            }
            return depth;
        }
};

int main(int argc, char ** argv) {
    Solution s;
    TreeNode *t1 = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
    cout << "Min depth: " << s.minDepth(t1) << endl;

    return 0;
}
