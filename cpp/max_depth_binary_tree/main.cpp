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
        int maxDepth(TreeNode* root) {
            queue<tuple<TreeNode*, int>> q;
            int max_depth = 0;
            if (root != nullptr) {
                q.push(make_tuple(root, 1));
            }

            while (!q.empty()) {
                auto front = q.front();
                q.pop();
                TreeNode *node = get<0>(front);
                int depth = get<1>(front);

                if (depth > max_depth) {
                    max_depth = depth;
                }

                if (node->left != nullptr) {
                    q.push(make_tuple(node->left, depth + 1));
                }
                if (node->right != nullptr) {
                    q.push(make_tuple(node->right, depth + 1));
                }
            }

            return max_depth;
        }
};

int main(int argc, char ** argv) {
    Solution s;
    TreeNode *t1 = new TreeNode(3, new TreeNode(9), new TreeNode(20, new TreeNode(15), new TreeNode(7)));
    cout << "Max depth: " << s.maxDepth(t1) << endl;

    return 0;
}
