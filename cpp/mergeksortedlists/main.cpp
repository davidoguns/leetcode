#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>
#include <optional>

using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

void print_list(ListNode * const list) {
    ListNode *current = list;
    while (current != nullptr) {
        cout << "Item: " << current->val << endl;
        current = current->next;
    }
}

optional<ListNode *> get_min(vector<ListNode*>& lists) {
    optional<ListNode *> min_value{};
    vector<ListNode *>::iterator selected = lists.end();
    // for_each(lists.begin(), lists.end(), [&min_value](ListNode *& node) {
    for (auto list_itr = lists.begin(); list_itr != lists.end(); list_itr++) {
        auto node = *list_itr;
        if (node == nullptr) {
            continue;
        }
        if (!min_value.has_value()) {
            min_value = node;
            selected = vector<ListNode*>::iterator{list_itr};
        }
        else if ((*min_value)->val > node->val) {
            min_value = node;
            selected = vector<ListNode*>::iterator{list_itr};
        }
    }
    //advance what was selected, if any
    if (selected != lists.end()) {
        (*selected) = (*selected)->next;
    }
    return min_value;
}

//https://leetcode.com/problems/merge-k-sorted-lists/
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<ListNode*> heads{lists};
        ListNode *head{nullptr};
        ListNode *prev{nullptr};
        optional<ListNode *> min{};

        while ((min = get_min(heads)).has_value()) {
            if (prev == nullptr) {
                head = prev = *min;
                head->next = nullptr;
            }
            else {
                prev->next = *min;
                (*min)->next = nullptr;
                prev = prev->next;
            }
        }
        return head;
    }
};

int main(int argc, char *argv[]) {
    //basic programs don't need to call delete, just let the OS clean up when the process dies
    vector<ListNode*> lists1 = vector<ListNode*>{
        new ListNode{1, new ListNode{4, new ListNode{5}}},
        new ListNode{1, new ListNode{3, new ListNode{4}}},
        new ListNode{2, new ListNode{6}}};

    Solution s;
    print_list(s.mergeKLists(lists1));
}
