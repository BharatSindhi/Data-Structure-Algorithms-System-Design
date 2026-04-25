#include <iostream>
using namespace std;

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head) return nullptr;

        ListNode* temp = head;
        int cnt = 0;

        // Step 1: Check if we have k nodes
        while (cnt < k && temp != nullptr) {
            temp = temp->next;
            cnt++;
        }

        if (cnt < k) return head; // not enough nodes

        // Step 2: Reverse first k nodes
        ListNode* prevNode = reverseKGroup(temp, k); // recursive call for next group
        ListNode* curr = head;

        while (cnt--) {
            ListNode* nextNode = curr->next;
            curr->next = prevNode;
            prevNode = curr;
            curr = nextNode;
        }

        // Step 3: Return new head (after reversing)
        return prevNode;
    }
};

// Helper function to print list
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    // Example: 1 -> 2 -> 3 -> 4 -> 5, k = 2
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    int k = 2;
    Solution sol;
    ListNode* newHead = sol.reverseKGroup(head, k);

    printList(newHead);  // Output: 2 1 4 3 5

    return 0;
}
