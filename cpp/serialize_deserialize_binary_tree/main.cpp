#include <iostream>
#include <sstream>
#include <string>

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

// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
class Codec {
    // Going to serialize using nested parentheses to define nodes
    //and the nesting of node structure will follow
    //each node is "(value,left,right)"
    //example nesting of a node with a left child, no right is:
    //  (5,(3,,),)

public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream ss(std::ostringstream::ate);
        serialize(root, ss);
        return std::move(ss.str()); 
    }

    void serialize(TreeNode* root, ostringstream &ss) {
        if (root == nullptr) return;
        ss << "(";
        ss << root->val;
        ss << ",";
        ss << serialize(root->left);
        ss << ",";
        ss << serialize(root->right);
        ss << ")";
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        size_t ch_index = 0;
        return buildTree(data, ch_index); 
    }

    TreeNode *buildTree(string &data, size_t &ch_index) {
        if (ch_index >= data.length()) {
            return nullptr; //should only happen if we have empty string
        }

        char ch = data.at(ch_index);
        if (ch == '(') { //new node, expect (value,left,right)
            TreeNode *node = new TreeNode();
            char vchar = data.at(++ch_index);
            bool neg = false;
            if (vchar == '-') {
                neg = true;
                vchar = data.at(++ch_index);
            }
            while (vchar >= '0' && vchar <= '9') {
                node->val *= 10;
                node->val += int(vchar) - int('0');
                vchar = data.at(++ch_index);
            }
            if (neg) {
                node->val *= -1;
            }
            ch_index++; //pluck off comma
            node->left = buildTree(data, ch_index);
            ch_index++; //pluck off comma
            node->right = buildTree(data, ch_index);
            ch_index++; //pluck off end parens
            return node;
        } else if (ch == ',' || ch == ')') { //no value, no node
            return nullptr;
        }

        //this is actually an error case, not throwing to see if it speeds up execution
        return nullptr;
    }
};

void inorder_print(TreeNode *node) {
    if (node != nullptr) {
        inorder_print(node->left);
        cout << node->val << ", ";
        inorder_print(node->right);
    }
}

int main(int argc, char *argv[]) {
    Codec ser, deser;
    TreeNode *root = nullptr;
    TreeNode* ans = deser.deserialize(ser.serialize(root));

    TreeNode *t1 = new TreeNode(5, new TreeNode(2, nullptr, new TreeNode(4)), new TreeNode(6));
    cout << "serialized: " << ser.serialize(t1) << endl;
    cout << "deserialized: ";
    inorder_print(deser.deserialize(ser.serialize(t1)));
    cout << endl;
    return 0;
}
