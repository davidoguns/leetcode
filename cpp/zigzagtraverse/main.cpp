#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <tuple>
#include <deque>

using namespace std;

/**
 * Definition for a binary tree node.
 */
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        typedef tuple<TreeNode *, unsigned int> NodeAndLevel;
        vector<vector<int>> results;
        queue<NodeAndLevel> q;
        int last_level = 0;
        deque<int> nodes_on_level;

        if (root == nullptr) {
            return {};
        }

        q.push({root, 0});
        while (!q.empty()) {
            auto nodeAndLevel = q.front();
            TreeNode *node = get<0>(nodeAndLevel);
            unsigned int node_level = get<1>(nodeAndLevel);

            if (node->left != nullptr) q.push({node->left, node_level+1});
            if (node->right != nullptr) q.push({node->right, node_level+1});

            if (last_level != node_level) {
                //drain into results
                vector<int> result_level;
                result_level.reserve(nodes_on_level.size());
                for_each(nodes_on_level.begin(), nodes_on_level.end(), [&result_level](auto val) {
                    result_level.push_back(val);
                });
                nodes_on_level.clear();
                results.push_back(std::move(result_level));
            }
            if (node_level % 2 == 0) {
                nodes_on_level.push_back(node->val);
            } else {
                nodes_on_level.push_front(node->val);
            }
            last_level = node_level;
            q.pop();
        }
        if (!nodes_on_level.empty()) {
            vector<int> result_level;
            result_level.reserve(nodes_on_level.size());
            for_each(nodes_on_level.begin(), nodes_on_level.end(), [&result_level](auto val) {
                result_level.push_back(val);
            });
            results.push_back(std::move(result_level));
        }

        return std::move(results);
    }
};

int main(int argc, char *argv[]) {
    Solution s;

    cout << "Solution: " << endl;

    print_solution(s.zigzagLevelOrder(new TreeNode{3, new TreeNode{9}, new TreeNode{20, new TreeNode{15}, new TreeNode{7}}}));
}
