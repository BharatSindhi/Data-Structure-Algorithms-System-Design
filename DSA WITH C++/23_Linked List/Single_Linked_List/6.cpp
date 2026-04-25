#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    // Function to detect the start of cycle (if any)
    ListNode* detectCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        // Step 1: Detect cycle using Floyd’s algorithm
        while (fast && fast->next) {
            slow = slow->next;       // move 1 step
            fast = fast->next->next; // move 2 steps
            if (slow == fast) {
                // Step 2: Find entry point of the cycle
                slow = head;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow; // start of cycle
            }
        }
        return nullptr; // no cycle
    }

    // Function to remove the cycle if present
    void removeCycle(ListNode* head) {
        ListNode* cycleStart = detectCycle(head);
        if (!cycleStart) return; // no cycle

        // Traverse the cycle until the node before cycleStart
        ListNode* temp = cycleStart;
        while (temp->next != cycleStart) {
            temp = temp->next;
        }
        temp->next = nullptr; // break the cycle
    }
};

// Helper function to create a linked list
ListNode* createList(int arr[], int n) {
    if (n == 0) return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* temp = head;
    for (int i = 1; i < n; i++) {
        temp->next = new ListNode(arr[i]);
        temp = temp->next;
    }
    return head;
}

// Function to print list (limited to avoid infinite loop if cycle exists)
void printList(ListNode* head, int limit = 15) {
    int count = 0;
    while (head != nullptr && count < limit) {
        cout << head->val << " -> ";
        head = head->next;
        count++;
    }
    if (head != nullptr) cout << "(cycle continues...)";
    else cout << "NULL";
    cout << endl;
}

int main() {
    Solution sol;

    // ---------- Test Case 1: List with a cycle ----------
    int arr1[] = {1, 2, 3, 4, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    ListNode* head1 = createList(arr1, n1);

    // Create cycle: link last node (5) -> node(3)
    head1->next->next->next->next->next = head1->next->next; // 5->3

    cout << "List 1 (with cycle): ";
    printList(head1); // will stop after 15 nodes to avoid infinite loop

    ListNode* cycleStart1 = sol.detectCycle(head1);
    if (cycleStart1)
        cout << "Cycle detected at node with value: " << cycleStart1->val << endl;
    else
        cout << "No cycle detected." << endl;

    // Remove the cycle
    sol.removeCycle(head1);

    cout << "List 1 after removing cycle: ";
    printList(head1); // now it should print normally and end with NULL

    cout << endl;

    // ---------- Test Case 2: List without a cycle ----------
    int arr2[] = {10, 20, 30, 40};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    ListNode* head2 = createList(arr2, n2);

    cout << "List 2 (no cycle): ";
    printList(head2);

    ListNode* cycleStart2 = sol.detectCycle(head2);
    if (cycleStart2)
        cout << "Cycle detected at node with value: " << cycleStart2->val << endl;
    else
        cout << "No cycle detected." << endl;

    // Try removing cycle (should do nothing)
    sol.removeCycle(head2);

    cout << "List 2 after removeCycle call: ";
    printList(head2);

    return 0;
}
