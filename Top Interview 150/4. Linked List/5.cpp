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
    ListNode* reverseBetween(ListNode* head, int left, int right) {

        if(head == NULL || left == right) {
            return head;
        }

        ListNode* prev = NULL;
        ListNode* curr = head;

        // Move curr to left position
        while(left > 1) {
            prev = curr;
            curr = curr->next;

            left--;
            right--;
        }

        // Store connections
        ListNode* connection = prev;
        ListNode* tail = curr;

        // Reverse nodes
        while(right > 0) {
            ListNode* temp = curr->next;

            curr->next = prev;
            prev = curr;
            curr = temp;

            right--;
        }

        // Connect first part
        if(connection != NULL) {
            connection->next = prev;
        } else {
            head = prev;
        }

        // Connect last part
        tail->next = curr;

        return head;
    }
};

int main() {
    
    return 0;
}