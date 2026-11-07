#include <iostream>

using std::cout;
using std::endl;

/**
 * Definition for singly-linked list.
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
        ListNode* swapPairs(ListNode* head) {
            ListNode* newHead = nullptr;
            ListNode* pairFirst = head;

            if (pairFirst != nullptr) {
                //verify we have at least a pair of nodes to swap
                ListNode* pairSecond = pairFirst->next;
                ListNode* nextPair = nullptr;
                if (pairSecond != nullptr) {
                    //here: verified that we have a pair
                    //grab hold of next pair before we mess with current pointers
                    nextPair = pairSecond->next;
                    //if this is the first pair, newHead will be null 
                    ////mark the second part of first pair as the new head to return
                    if (newHead == nullptr) {
                        newHead = pairSecond;
                    }
                    //now swap
                    pairSecond->next = pairFirst;
                    pairFirst->next = swapPairs(nextPair);
                }
                pairFirst = nextPair; //whether or not this is a pair depends on if it's null
            }

            return newHead == nullptr ? head : newHead;
        }
};

int main(int argc, char** argv) {
    cout << "Hello swap nodes" << endl;
    return 0;
}

