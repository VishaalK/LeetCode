#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

/**
 * Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // single element list
        if (!head || !head->next) {
            return head;
        }
        
        ListNode* rest = reverseList(head->next);
        ListNode* runner = rest;
        while (runner->next) {
            runner = runner->next;
        }
        runner->next = head;
        head->next = nullptr;

        return rest;
    }
};

ListNode* arrayToList(const vector<int>& A) {
    if (!A.size()) {
        return nullptr;
    }

    ListNode* ret = new ListNode(A.front());
    ListNode* run = ret;
    for (int i = 1; i < A.size(); i++) {
        run->next = new ListNode(A[i]);
        run = run->next;
    }
    return ret;
}

void printList(ListNode* head) {
    if (!head) {
        return;
    }

    cout << "sup" << endl;
    cout << head->val << " ";
    
    printList(head->next);
}

int main() {
    auto ans = Solution().reverseList(arrayToList(vector<int> {1,2}));
    printList(ans);
    cout << endl;
}