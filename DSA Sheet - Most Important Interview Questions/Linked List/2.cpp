#include <iostream>
using namespace std;


//  * Definition for singly-linked list.
// This structure represents one node in a singly linked list.
// Each node stores an integer value and a pointer to the next node.
// Because this is a singly linked list, every node can only move forward
// through the `next` pointer; there is no direct pointer to the previous node.
  struct ListNode {
      // Stores the actual data value of the current node.
      int val;

      // Points to the next node in the list.
      // If this is the last node, `next` is nullptr.
      ListNode *next;

      // Default constructor:
      // Creates a node with value 0 and no next node.
      // This is useful when a platform or test harness creates empty/default nodes.
      ListNode() : val(0), next(nullptr) {}

      // Constructor with only a value:
      // Creates a node containing `x`, and marks it as the end of a list
      // by setting `next` to nullptr.
      ListNode(int x) : val(x), next(nullptr) {}

      // Constructor with value and next pointer:
      // Creates a node containing `x` and links it directly to another node.
      // This is useful for building lists quickly.
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:
    // Reverses a singly linked list in-place and returns the new head.
    // Time Complexity: O(n), because each node is visited exactly once.
    // Space Complexity: O(1), because only three pointer variables are used,
    // regardless of the number of nodes.
    ListNode* reverseList(ListNode* head) {
        // `prev` will point to the already reversed part of the list.
        // Initially, no nodes have been reversed, so it starts as NULL.
        // After the first node is processed, that node's next should point
        // to NULL because it becomes the tail of the reversed list.
        ListNode* prev=NULL;

        // `curr` points to the node currently being processed.
        // It starts at `head`, the first node of the original list.
        // If `head` is NULL, the list is empty and the while loop will not run.
        ListNode* curr=head;

        // `next` temporarily stores the next node before changing curr->next.
        // This is necessary because once curr->next is reversed, the original
        // forward link would be lost without saving it first.
        ListNode* next=NULL;

        // Iterate until every node has been processed.
        // Loop invariant:
        // - `prev` is the head of the reversed portion.
        // - `curr` is the first node of the remaining unreversed portion.
        // - nodes before `curr` already point backward correctly.
        while(curr != NULL){
            // Save the next node before modifying the current node's link.
            // Without this line, changing curr->next would disconnect the rest
            // of the original list and we would not know where to continue.
            next=curr->next;

            // Reverse the pointer of the current node.
            // Instead of pointing to the next node in the original list,
            // it now points to the previous node in the reversed list.
            curr->next=prev;

            // Move `prev` forward to the current node.
            // The reversed part now starts at `curr`.
            prev=curr;

            // Move `curr` forward to the saved next node.
            // This continues traversal through the original list.
            curr=next;
        }

        // When the loop ends, `curr` is NULL, meaning the original list is fully processed.
        // `prev` points to the last node of the original list, which is now the new head.
        // Edge cases:
        // - Empty list: head is NULL, loop does not run, returns NULL.
        // - Single-node list: node points to NULL again, returns the same node.
        return prev;
    }
};
int main() {
    // Empty main function.
    // The reverseList function is usually tested by an online judge or external test code.
    
    return 0;
}

// ------------------------------------------------------------
// Overall Explanation of the Approach
// ------------------------------------------------------------
// This code reverses a singly linked list using an iterative three-pointer method.
// The three pointers are:
// 1. `prev` - tracks the reversed part of the list.
// 2. `curr` - tracks the current node being processed.
// 3. `next` - temporarily stores the next node so the remaining list is not lost.
//
// For every node, the algorithm:
// 1. Stores the original next node in `next`.
// 2. Changes curr->next so it points backward to `prev`.
// 3. Moves `prev` to `curr`.
// 4. Moves `curr` to `next`.
//
// Once `curr` becomes NULL, all links have been reversed and `prev` is the new head.
//
// Optimality:
// This is the best and most commonly used approach for reversing a singly linked list.
// It is optimal because it visits each node once and uses constant extra memory.
//
// Complexity:
// Time Complexity: O(n), where n is the number of nodes in the list.
// Space Complexity: O(1), because no extra list, array, stack, or recursion is used.
//
// Pros:
// - Very efficient in both time and space.
// - Reverses the list in-place without creating new nodes.
// - Correctly handles empty lists and single-node lists.
// - Avoids recursion, so there is no risk of stack overflow for very large lists.
//
// Cons:
// - Pointer manipulation can be confusing for beginners.
// - The original list order is destroyed because the reversal happens in-place.
// - If the input list has a cycle, this loop would not terminate.
//
// Suggested Alternative Approaches:
// - Recursive reversal:
//   This can be elegant and shorter, but it uses O(n) call stack space.
//   It may also cause stack overflow for very long linked lists.
//
// - Stack-based reversal:
//   Push all nodes or values onto a stack and rebuild the links/order.
//   This is easier to understand, but it needs O(n) extra memory.
//
// - Create a new reversed list:
//   Build new nodes in reverse order instead of changing the original list.
//   This preserves the original list but requires O(n) extra memory.
