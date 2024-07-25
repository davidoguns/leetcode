#include <iostream>
#include <vector>

using namespace std;

/**
 * Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode *head, int n) {
        //out of bounds, '1' from the end is the last element, 0 isn't anything
        if (n == 0) {
            return head;
        }
        vector<ListNode *> nodevec;
        for (ListNode *curr = head; curr != nullptr; curr = curr->next) {
            nodevec.push_back(curr);
        }
       
        //removing something not in list
        if (n > nodevec.size()) {
            return head;
        }

        ListNode *to_delete = nodevec[nodevec.size()-n];
        ListNode *new_next = to_delete->next;

        //not sure if leetcode cares for this
        delete to_delete;
        ListNode *prev = nullptr;
        if (nodevec.size() != n) {
            prev = nodevec[(nodevec.size()-n-1)];
            prev->next = new_next;
        }
        if (prev != nullptr) {
            return head;
        } else {
            return new_next;
        }
        
    }
};

void print_list(ListNode *node) {
    while (node != nullptr) {
        cout << "[" << node->val << "]";
        node = node->next;
    }
}

int main(int argc, char *argv[]) {
    Solution s;

    ListNode *list = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    s.removeNthFromEnd(list, 2);
    cout << "List: "; print_list(list); cout << endl;
    return 0;
}
