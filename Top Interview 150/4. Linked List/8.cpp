#include <iostream>
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

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {

        if(head == NULL || head->next == NULL || k == 0)
            return head;

        // Step 1: Find length and tail
        ListNode* tail = head;
        int len = 1;

        while(tail->next != NULL) {
            tail = tail->next;
            len++;
        }

        // Step 2: Reduce unnecessary rotations
        k = k % len;

        if(k == 0)
            return head;

        // Step 3: Make circular list
        tail->next = head;

        // Step 4: Find new last node
        int steps = len - k - 1;

        ListNode* newLastNode = head;

        while(steps--) {
            newLastNode = newLastNode->next;
        }

        // Step 5: New head
        ListNode* newHead = newLastNode->next;

        // Step 6: Break the circle
        newLastNode->next = NULL;

        return newHead;
    }
};

int main() {
    
    return 0;
}