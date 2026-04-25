// # Intuition
// If there is a cycle in the linked list, then two pointers moving at different speeds will eventually meet inside the cycle.
// If there is no cycle, the faster pointer will reach the end (NULL) first.
// # Approach
// Use two pointers:

// Slow pointer moves one step at a time.

// Fast pointer moves two steps at a time.

// Traverse the list while ensuring fast and fast->next are not NULL.

// If at any point, slow == fast, it means both pointers met inside a cycle → return true.

// If the fast pointer reaches NULL, the list has no cycle → return false.
// # Complexity
// - Time complexity:
// O(n)
// - Space complexity:
// O(1)
// # Code
// ```cpp []
// /**
//  * Definition for singly-linked list.
//  * struct ListNode {
//  *     int val;
//  *     ListNode *next;
//  *     ListNode(int x) : val(x), next(NULL) {}
//  * };
//  */
// class Solution {
// public:
//     bool hasCycle(ListNode* head) {
//         ListNode* slow = head;
//         ListNode* fast = head;

//         while (fast != NULL && fast->next != NULL) {
//             slow = slow->next;
//             fast = fast->next->next;
//             if (slow == fast)
//                 return true;
//         }
//         return false;
//     }
// };
// ```


#include <iostream>  // for std::cout, std::endl

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;          // move by 1
            fast = fast->next->next;    // move by 2
            if (slow == fast) {
                return true;            // cycle detected
            }
        }
        return false;                   // no cycle
    }
};

int main() {
    // Example 1: Linked list with cycle
    ListNode* head1 = new ListNode(3);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(0);
    head1->next->next->next = new ListNode(-4);

    // Create a cycle (last node points back to second node)
    head1->next->next->next->next = head1->next;

    Solution sol;
    if (sol.hasCycle(head1)) {
        std::cout << "Cycle detected in list 1" << std::endl;
    } else {
        std::cout << "No cycle in list 1" << std::endl;
    }

    // Example 2: Linked list without cycle
    ListNode* head2 = new ListNode(1);
    head2->next = new ListNode(2);

    if (sol.hasCycle(head2)) {
        std::cout << "Cycle detected in list 2" << std::endl;
    } else {
        std::cout << "No cycle in list 2" << std::endl;
    }

    // Cleanup (avoid memory leaks for non-cyclic list)
    delete head2->next;
    delete head2;

    return 0;
}
