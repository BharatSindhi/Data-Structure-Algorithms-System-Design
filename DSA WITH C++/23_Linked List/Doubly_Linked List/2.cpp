#include <iostream>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node(int _val) {
        val = _val;
        prev = NULL;
        next = NULL;
        child = NULL;
    }
};

class Solution {
public:
    Node* flatten(Node* head) {
        if (head == NULL) return NULL;

        Node* curr = head;
        while (curr != NULL) {
            if (curr->child != NULL) {
                Node* next = curr->next; // Save next node

                // Recursively flatten the child
                Node* childHead = flatten(curr->child);
                curr->next = childHead;
                childHead->prev = curr;
                curr->child = NULL;

                // Move to the end of the flattened child list
                Node* tail = childHead;
                while (tail->next != NULL) {
                    tail = tail->next;
                }

                // Connect tail to the saved next node
                if (next != NULL) {
                    tail->next = next;
                    next->prev = tail;
                }
            }
            curr = curr->next;
        }
        return head;
    }
};

// Utility function to print flattened list
void printList(Node* head) {
    while (head != NULL) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

// Example to test flattening
int main() {
    // Level 1: 1 - 2 - 3 - 4
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->prev = head;
    head->next->next = new Node(3);
    head->next->next->prev = head->next;
    head->next->next->next = new Node(4);
    head->next->next->next->prev = head->next->next;

    // Level 2: 3 -> 5 - 6
    Node* child = new Node(5);
    child->next = new Node(6);
    child->next->prev = child;
    head->next->next->child = child; // 3 -> child

    Solution sol;
    Node* flat = sol.flatten(head);

    cout << "Flattened list: ";
    printList(flat);

    return 0;
}
