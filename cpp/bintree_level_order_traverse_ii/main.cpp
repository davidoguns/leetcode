#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

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
    void levelOrder(TreeNode* node, size_t level, vector<vector<int>> &result) {
        if (node != nullptr) {
            if (level == result.size()) {
                //push in a new vector for space
                result.push_back(std::move(vector<int>{}));
            }
            result[level].push_back(node->val);
            levelOrder(node->left, level + 1, result);
            levelOrder(node->right, level + 1, result);
        }
    }

    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        levelOrder(root, 0, result);
        return result;
    }

    vector<vector<int>> levelOrderBottom2(TreeNode* root) {
        if (root == nullptr) {
            return vector<vector<int>>{};
        }
        vector<vector<int>> result;
        queue<tuple<TreeNode*, int>> q;
        q.push({root, 0});
        int current_level = -1; 
        while (!q.empty()) {
            auto node_tuple = q.front();
            q.pop();
            TreeNode *node = get<0>(node_tuple);
            int level = get<1>(node_tuple);
            if (current_level != level) {
                // new level, means new array in result
                result.push_back(vector<int>{});
                ++current_level;
            }
            result.back().push_back(node->val);
            if (node->left) {
                q.push({node->left, level+1});
            }
            if (node->right) {
                q.push({node->right, level+1});
            }
        }
        return result;
    }
};

int main(int argc, char *argv[]) {
    TreeNode *tree1 = new TreeNode{3, new TreeNode{9}, new TreeNode{20, new TreeNode{15}, new TreeNode{7}}};
    Solution s;
    print_solution(s.levelOrderBottom(tree1));

    return 0;
}
