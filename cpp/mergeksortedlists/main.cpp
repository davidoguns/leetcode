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

ListNode* merge_lists(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr && list2 == nullptr) {
        return nullptr;
    }
    else if (list2 == nullptr) {
        return list1;
    }
    else if (list1 == nullptr) {
        return list2;
    }
    else {
        if (list1->val < list2->val) {
            list1->next = merge_lists(list1->next, list2);
            return list1;
        }
        else {
            list2->next = merge_lists(list1, list2->next);
            return list2;
        }
    }
}

//https://leetcode.com/problems/merge-k-sorted-lists/
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        else if (lists.size() == 1) {
            return lists[0];
        }
        else {
            auto list_itr = lists.begin();
            ListNode * curr_list = *list_itr;
            list_itr++;
            while (list_itr != lists.end()) {
                curr_list = merge_lists(curr_list, *list_itr);
                list_itr++;
            }
            return curr_list;
        }
    }
};

int main(int argc, char *argv[]) {
    //basic programs don't need to call delete, just let the OS clean up when the process dies
    vector<ListNode*> lists1 = vector<ListNode*>{
        new ListNode{1, new ListNode{4, new ListNode{5}}},
        new ListNode{1, new ListNode{3, new ListNode{4}}},
        new ListNode{2, new ListNode{6}}};
    vector<ListNode*> lists2 = vector<ListNode*>{
        new ListNode{1, new ListNode{4, new ListNode{5}}},
        new ListNode{1, new ListNode{3, new ListNode{4}}},
        new ListNode{2, new ListNode{6}}};

    Solution s;
    cout << "First list" << endl;
    print_list(s.mergeKLists(lists1));
    cout << "Second list" << endl;
    print_list(merge_lists(merge_lists(lists2[0], lists2[1]), lists2[2]));
}
