#include <iostream>
using namespace std;

// This file solves the classic "Flatten a Multilevel Doubly Linked List" problem.
// Goal: convert a doubly linked list where each node may have a child list into
// one single-level doubly linked list using depth-first order.
//
// Example shape:
// 1 <-> 2 <-> 3
//       |
//       7 <-> 8
//
// Flattened output:
// 1 <-> 2 <-> 7 <-> 8 <-> 3

   
class Node {
public:
    // Stores the node's actual data value.
    // If removed, the list would still have links, but it would not represent
    // meaningful problem data.
    int val;

    // Points to the previous node in the doubly linked list.
    // This is necessary because the final answer must support backward traversal.
    // If this is not maintained, the list may look correct only in the forward direction.
    Node* prev;

    // Points to the next node on the same level, and later to the next node in
    // the flattened order.
    // If removed, we could not walk through the list from left to right.
    Node* next;

    // Points to a nested child doubly linked list.
    // During flattening, child nodes are moved into the main next chain, so every
    // child pointer should become NULL in the final answer.
    Node* child;
};


class Solution {
public:
    Node* flatten(Node* head) {
        // Edge case: empty list.
        // What this does: returns NULL when there is no node to flatten.
        // Why necessary: recursive calls may also receive NULL for empty child lists.
        // What breaks if removed: later pointer access on NULL would crash.
        // Dry run: head = NULL -> return NULL immediately.
        // Handles: empty top-level list and empty recursive child input.
        if(head == NULL){
            return NULL;
        }

        // curr walks through the current list level.
        // Why necessary: we need a moving pointer while preserving head so we can
        // return the start of the flattened list at the end.
        // What breaks if removed: using head as the iterator would lose the original start.
        // Dry run: for 1 <-> 2 <-> 3, curr starts at node 1.
        Node* curr=head;

        // Traverse nodes until the end of the current/partially flattened chain.
        // Pattern: DFS recursion + linked list splicing.
        // Why necessary: every node must be checked for a child pointer.
        // What breaks if removed: no child list would ever be flattened.
        // Complexity note: every node is visited, but the inner tail-search loop
        // can make this specific implementation slower on deeply nested inputs.
        while(curr != NULL){
            // If curr has a child, that child list must be inserted immediately
            // after curr before curr's original next node.
            // Dry run:
            // - Suppose 1 <-> 2 <-> 3 and 2 has child 7 <-> 8.
            // - curr = 1 has no child, so move on.
            // - curr = 2 has a child, so splice 7 <-> 8 between 2 and 3.
            // Handles: nodes with no child by skipping this block.
            if(curr->child != NULL){
                // Save curr's original next before overwriting curr->next.
                // Why necessary: after curr->next points to the child list, the
                // old next chain would otherwise be lost.
                // What breaks if removed: nodes after curr on the same level
                // become detached from the final list.
                // Dry run: at node 2, next stores node 3.
                Node* next = curr->next;

                // Recursively flatten the child list and attach its head after curr.
                // Why necessary: the child list may contain deeper child lists.
                // What breaks if removed: deeper nested nodes could remain unflattened.
                // Dry run: 2->child is 7 <-> 8, so 2->next becomes flattened child head 7.
                curr->next=flatten(curr->child);

                // Fix the backward pointer from the child head to curr.
                // Why necessary: the output must be a valid doubly linked list.
                // What breaks if removed: forward traversal may work, but backward
                // traversal from the child head would be incorrect.
                // Dry run: set 7->prev = 2.
                // Safe here because curr->child was non-NULL, so a valid child
                // list should return a non-NULL head.
                curr->next->prev=curr;

                // Remove the child pointer because the child list is now part of
                // the main flattened next chain.
                // What breaks if removed: the final structure would still be multilevel.
                // Dry run: node 2's child pointer becomes NULL after 7 is linked by next.
                curr->child = NULL;

                // Move curr to the tail of the newly inserted flattened child list.
                // Why necessary: the saved original next list must be reattached
                // after the child tail, not after the child head.
                // What breaks if removed: we would not know where to connect node 3.
                // Dry run: from 2 -> 7 -> 8, stop at 8 because 8->next is NULL.
                // Complexity warning: this tail search can revisit nodes in some
                // nested shapes, so a helper that returns the tail is more efficient.
                while(curr->next != NULL){
                    curr=curr->next;
                }

                // If there was an original next node, attach it after the child tail.
                // Edge case: if next is NULL, the flattened child list simply becomes the tail.
                if(next != NULL){
                    // Connect child tail to the saved original next chain.
                    // What breaks if removed: original next nodes are lost from the output.
                    // Dry run: set 8->next = 3.
                    curr->next=next;

                    // Fix the backward pointer from the original next node to the child tail.
                    // What breaks if removed: 3->prev may still point to 2 instead of 8.
                    // Dry run: set 3->prev = 8.
                    next->prev=curr;
                }
            }

            // Move to the next node in the flattened chain.
            // Why necessary: prevents an infinite loop and continues processing.
            // Dry run:
            // - After node 1, curr moves to 2.
            // - After splicing 2's child, curr has moved to child tail 8, then
            //   this line moves curr to saved next node 3.
            // Edge case: if curr is the final tail, curr becomes NULL and loop ends.
            curr=curr->next;
        }

        // Return the original head, which still points to the start of the now
        // flattened list.
        // What breaks if removed: caller would not receive the flattened list head.
        // Dry run output: 1 <-> 2 <-> 7 <-> 8 <-> 3, and head still points to 1.
        return head;
    }
};

int main() {
    // No test driver is written here.
    // The online judge/interviewer usually builds the list and calls Solution::flatten.
    // Edge case missed by this file: it does not verify output or construct sample inputs.
    
    return 0;
}

/*
===============================================================================
1. Problem Understanding
===============================================================================

- Type of problem:
  - Linked list pointer manipulation.
  - More specifically, flattening a multilevel doubly linked list.

- Key constraints/clues:
  - Each node has next, prev, and child pointers.
  - The required order is depth-first: current node, then child chain, then
    original next chain.
  - The final list must be a single-level doubly linked list.
  - All child pointers should become NULL.

===============================================================================
2. Pattern Recognition
===============================================================================

- Pattern used:
  - DFS recursion + linked list splicing.

- How to recognize this pattern in future:
  - The structure has "next" plus "child" pointers, like a list mixed with a tree.
  - The problem asks to process nested levels before continuing sideways.
  - Words like "flatten", "multilevel", "child list", and "depth-first order"
    strongly suggest DFS.

===============================================================================
3. Approach Breakdown (Interview Style)
===============================================================================

- Brute force idea:
  - Traverse all nodes in DFS order, store them in a vector, then reconnect all
    next and prev pointers afterward.
  - Simple, but uses O(n) extra space.

- Better approach:
  - Use recursion to flatten each child list and splice it into the current list.
  - This avoids a vector, but uses recursion stack space.

- Optimal approach:
  - Use DFS with a helper that returns the tail of the flattened list, or use an
    explicit stack.
  - Returning the tail avoids repeatedly scanning to the end of each child list.
  - That gives strict O(n) time because each node is processed a constant number
    of times.

===============================================================================
4. Intuition Building
===============================================================================

- Core idea:
  - When a node has a child, insert the entire child list immediately after that
    node, then continue with the old next nodes.

- Trick/insight:
  - Save next, flatten child, attach child after curr, find child tail, reconnect
    saved next.

===============================================================================
5. How to Recall Later
===============================================================================

- Key signals:
  - Node has next and child pointers.
  - Output must be one linear linked list.
  - Child list must come before the original next list.

- One-line memory trick:
  - "Save next, flatten child, splice child, find tail, restore next."

===============================================================================
6. Common Mistakes
===============================================================================

- Forgetting to save curr->next before overwriting it.
- Forgetting to set the child head's prev pointer.
- Forgetting to set the saved next node's prev pointer to the child tail.
- Forgetting to set curr->child = NULL.
- Moving curr incorrectly after splicing and skipping nodes.
- Assuming forward links are enough even when prev links are broken.

===============================================================================
7. Complexity Analysis
===============================================================================

- Time complexity:
  - Simple/balanced cases: O(n), where n is the total number of nodes.
  - This implementation can degrade toward O(n^2) on heavily nested inputs
    because it repeatedly searches for the tail with while(curr->next != NULL).

- Space complexity:
  - O(d) recursion stack, where d is the maximum child nesting depth.
  - No extra vector or hash table proportional to n is used.

===============================================================================
8. Alternative Approaches
===============================================================================

- Iterative stack:
  - Use a stack to remember original next nodes whenever a child is found.
  - Process the child first, then pop the saved next node when the child chain ends.
  - Avoids recursive call stack, but still uses stack space.

- Recursive helper returning tail:
  - Write a helper that flattens a list and returns its tail.
  - This removes repeated tail scanning and gives clean O(n) time.

- Vector reconstruction:
  - DFS collect nodes into an array, then reconnect pointers in order.
  - Very beginner-friendly, but uses O(n) extra space and is less pointer-focused.
*/
