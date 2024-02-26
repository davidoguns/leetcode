#include <iostream>
/**
 * Definition for singly-linked list.
 * https://leetcode.com/problems/add-two-numbers/submissions/1186296449/
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = nullptr;
        ListNode *result = nullptr;
        bool carry_one = false;
        while (l1 != nullptr || l2 != nullptr) {
            int digit = carry_one ? 1 : 0;
            if (l1 != nullptr) {
                digit += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                digit += l2->val;
                l2 = l2->next;
            }
            if (digit > 9) {
                carry_one = true;
                digit -= 10;
            } else {
                carry_one = false;
            }
            
            //now insert in list, might be the first
            if (result == nullptr) {
                head = result = new ListNode{digit, nullptr};
            } else {
                result->next = new ListNode{digit, nullptr};
                result = result->next;
            }
        }
        if (carry_one) {
            result->next = new ListNode{1, nullptr};
        }
        if (result == nullptr) {
            result = new ListNode{0, nullptr};
        }
        return head;
    }
};

void print_list(ListNode const  *head) {
    //we'll just use head to iterate as well
    
    while (head != nullptr) {
        std::cout << head->val;
        head = head->next;
    }
}

int main(int argc, char* argv[]) { 
    using namespace std;
    //not going to worry about deletes because end of program cleans everything up
    
    ListNode *number1 = new ListNode{2, new ListNode{4, new ListNode{3, nullptr}}};
    ListNode *number2 = new ListNode{5, new ListNode{6, new ListNode{4, nullptr}}};

    cout << "Adding numbers ";
    print_list(number1);
    cout << " and ";
    print_list(number2);
    cout << "." << endl << "  Result: ";

    Solution s;
    ListNode *solution = s.addTwoNumbers(number1, number2);
    print_list(solution);
    cout << endl;

    return 0;
}
