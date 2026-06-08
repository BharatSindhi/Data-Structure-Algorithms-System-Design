#include <iostream>
using namespace std;

// Basic singly linked list node.
// Each node stores:
// 1. val  -> the data
// 2. next -> address of the next node
//
// This structure is necessary because the problem is about rearranging links,
// not moving array elements by index. In a linked list, we can only move forward
// through next pointers.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    // Problem: Rotate a singly linked list to the right by k places.
    //
    // Example:
    // head = 1 -> 2 -> 3 -> 4 -> 5, k = 2
    //
    // Right rotation by 1:
    // 5 -> 1 -> 2 -> 3 -> 4
    //
    // Right rotation by 2:
    // 4 -> 5 -> 1 -> 2 -> 3
    //
    // Final answer:
    // 4 -> 5 -> 1 -> 2 -> 3
    //
    // Core idea:
    // Instead of rotating one step at a time, connect tail to head to form a
    // circle, then cut the circle at the correct point.
    ListNode* rotateRight(ListNode* head, int k) {

        // Edge cases:
        // 1. head == NULL:
        //    Empty list. There is nothing to rotate.
        //
        // 2. head->next == NULL:
        //    Only one node. Any number of rotations gives the same list.
        //
        // 3. k == 0:
        //    Zero rotations means the list should stay unchanged.
        //
        // Why this is necessary:
        // If head is NULL and we try to access head->next later, the program
        // will crash because we are dereferencing a null pointer.
        //
        // What would break if removed:
        // - Empty list input would break at "head->next" or while finding tail.
        // - Single-node list would still work logically, but extra circular
        //   linking would be unnecessary and easier to mishandle.
        //
        // Dry run:
        // head = NULL, k = 3 -> return NULL immediately.
        // head = 7, k = 10 -> return 7 immediately.
        //
        // Complexity of this check: O(1) time, O(1) space.
        if(head == NULL || head->next == NULL || k == 0)
            return head;

        // Step 1: Find length and tail
        //
        // tail starts at head because we need to walk to the last node.
        // len starts at 1 because head itself is already counted.
        //
        // Why this is necessary:
        // We need the list length to reduce k using modulo, and we need the tail
        // to later connect tail->next back to head.
        //
        // What would break if removed:
        // Without len, large k values like 2000000000 would cause unnecessary
        // work or wrong cut position.
        // Without tail, we cannot form the circular list efficiently.
        //
        // Dry run for 1 -> 2 -> 3 -> 4 -> 5:
        // tail = node 1, len = 1 initially.
        ListNode* tail = head;
        int len = 1;

        // Move tail until it reaches the last node.
        //
        // Condition tail->next != NULL means:
        // "Stop when the current node has no next node."
        //
        // Dry run:
        // List: 1 -> 2 -> 3 -> 4 -> 5
        // Start: tail = 1, len = 1
        // Iteration 1: tail = 2, len = 2
        // Iteration 2: tail = 3, len = 3
        // Iteration 3: tail = 4, len = 4
        // Iteration 4: tail = 5, len = 5
        // Stop because tail->next is NULL.
        //
        // What would break if removed:
        // len would remain 1 and tail would remain head, so all later math and
        // links would be wrong for lists longer than one node.
        //
        // Complexity of this loop: O(n) time, O(1) space.
        while(tail->next != NULL) {
            tail = tail->next;
            len++;
        }

        // Step 2: Reduce unnecessary rotations
        //
        // Rotating a list by its length gives the original list.
        // Therefore only k % len rotations matter.
        //
        // Example:
        // len = 5, k = 7
        // Rotating by 5 changes nothing, so k = 7 behaves like k = 2.
        //
        // Why this is necessary:
        // It handles huge k values efficiently and gives the correct split point.
        //
        // What would break if removed:
        // steps = len - k - 1 could become negative when k > len.
        // Example: len = 5, k = 7 -> steps = 5 - 7 - 1 = -3,
        // which makes no sense for moving forward in a linked list.
        //
        // Edge cases handled:
        // - k equal to len
        // - k greater than len
        // - very large k
        //
        // Complexity: O(1) time, O(1) space.
        k = k % len;

        // If k becomes 0 after modulo, the list remains unchanged.
        //
        // Example:
        // 1 -> 2 -> 3 -> 4 -> 5, k = 5
        // k % len = 5 % 5 = 0
        // Answer is still 1 -> 2 -> 3 -> 4 -> 5.
        //
        // Why this is necessary:
        // Avoids making a temporary cycle when no rotation is needed.
        //
        // What would break if removed:
        // The algorithm may still produce the same list if the later steps are
        // carefully executed, but it would do unnecessary pointer changes and
        // increase the chance of circular-list mistakes.
        //
        // Complexity: O(1) time, O(1) space.
        if(k == 0)
            return head;

        // Step 3: Make circular list
        //
        // Connect the last node back to the first node.
        //
        // Before:
        // 1 -> 2 -> 3 -> 4 -> 5 -> NULL
        //
        // After:
        // 1 -> 2 -> 3 -> 4 -> 5
        // ^                   |
        // |___________________|
        //
        // Why this is necessary:
        // Rotation means the last k nodes move to the front. By making the list
        // circular, we can choose a new head and then break the circle after the
        // new last node.
        //
        // What would break if removed:
        // newHead could still point to the correct node, but the old tail would
        // not connect to the old head, so the rotated list would lose nodes.
        //
        // Example if removed:
        // For 1 -> 2 -> 3 -> 4 -> 5, k = 2,
        // newHead would be 4, but 5 would still point to NULL instead of 1.
        // Result would become 4 -> 5 only, losing 1 -> 2 -> 3.
        //
        // Important warning:
        // Once this line runs, the list has a cycle. We must break it later using
        // newLastNode->next = NULL.
        //
        // Complexity: O(1) time, O(1) space.
        tail->next = head;

        // Step 4: Find new last node
        //
        // After rotating right by k:
        // - The new head is the (len - k)-th node using 0-based movement from head.
        // - The new last node is one node before the new head.
        //
        // Therefore, from head, move len - k - 1 steps to reach newLastNode.
        //
        // Example:
        // List: 1 -> 2 -> 3 -> 4 -> 5, len = 5, k = 2
        // New list should be: 4 -> 5 -> 1 -> 2 -> 3
        // New head = 4
        // New last node = 3
        //
        // steps = len - k - 1 = 5 - 2 - 1 = 2
        // Start at 1:
        // step 1 -> 2
        // step 2 -> 3
        // So newLastNode = 3.
        //
        // What would break if formula is wrong:
        // - If we used len - k, we would land on the new head instead of the
        //   new last node.
        // - If we forgot -1, the final cut would happen one node too late.
        int steps = len - k - 1;

        // Start from old head and move "steps" times to find the node that will
        // become the last node after rotation.
        //
        // Why this is necessary:
        // We need the exact node where the circular list should be broken.
        //
        // Dry run:
        // head = 1, len = 5, k = 2, steps = 2
        // newLastNode starts at 1.
        ListNode* newLastNode = head;

        // Move forward until newLastNode reaches the cut point.
        //
        // Dry run continued:
        // steps = 2:
        // Iteration 1: newLastNode = 2, steps becomes 1
        // Iteration 2: newLastNode = 3, steps becomes 0
        // Stop. newLastNode is 3.
        //
        // What would break if removed:
        // newLastNode would stay as head. The new head would become head->next,
        // which is only correct for very specific cases and wrong in general.
        //
        // Complexity of this loop: O(n) in the worst case, O(1) extra space.
        while(steps--) {
            newLastNode = newLastNode->next;
        }

        // Step 5: New head
        //
        // The node after newLastNode becomes the first node of the rotated list.
        //
        // Dry run:
        // newLastNode = 3
        // newHead = newLastNode->next = 4
        //
        // Current circular structure:
        // 1 -> 2 -> 3 -> 4 -> 5 -> 1 ...
        //
        // If newHead is 4, then rotated traversal should be:
        // 4 -> 5 -> 1 -> 2 -> 3
        //
        // Why this is necessary:
        // The function must return the new first node of the rotated list.
        //
        // What would break if removed:
        // We would not know what pointer to return after cutting the circle.
        //
        // Complexity: O(1) time, O(1) space.
        ListNode* newHead = newLastNode->next;

        // Step 6: Break the circle
        //
        // Make newLastNode the actual last node by setting its next to NULL.
        //
        // Dry run:
        // Before cut:
        // 4 -> 5 -> 1 -> 2 -> 3 -> 4 -> ...
        //
        // After newLastNode->next = NULL where newLastNode = 3:
        // 4 -> 5 -> 1 -> 2 -> 3 -> NULL
        //
        // Why this is necessary:
        // Linked lists must end at NULL. Since we created a cycle earlier, we
        // must break it to avoid infinite traversal.
        //
        // What would break if removed:
        // The returned list would be circular. Any print, search, or delete
        // function that expects NULL termination could run forever.
        //
        // Edge case handled:
        // This cut works for all k values after k %= len, as long as k != 0.
        //
        // Complexity: O(1) time, O(1) space.
        newLastNode->next = NULL;

        // Return the first node of the rotated list.
        //
        // Final dry run result:
        // Input:  1 -> 2 -> 3 -> 4 -> 5, k = 2
        // Output: 4 -> 5 -> 1 -> 2 -> 3
        //
        // Overall complexity:
        // Time: O(n)
        // - One pass to find length and tail.
        // - One partial pass to find the new last node.
        //
        // Space: O(1)
        // - Only a few pointers and integers are used.
        return newHead;
    }
};
int main() {
    
    return 0;
}

/*
================================================================================
1. Problem Understanding
================================================================================

What type of problem is this?
- This is a linked list rearrangement problem.
- The goal is not to change node values, but to change next pointers.

What are key constraints/clues?
- It is a singly linked list, so we can only move forward.
- k can be larger than the length of the list.
- Rotating by the list length gives the same list.
- Empty list, one-node list, and k = 0 should return the original head.

================================================================================
2. Pattern Recognition
================================================================================

Which DSA pattern is used?
- Linked list pointer manipulation.
- Circular linked list trick.
- Modulo reduction.

How can I recognize this pattern in future problems?
- If the last part of a linked list needs to move to the front, think about
  temporarily connecting tail to head.
- If an operation repeats every n steps, think about modulo.
- If the problem asks for "rotate", "shift", or "move last k nodes to front",
  this pattern is a strong candidate.

================================================================================
3. Approach Breakdown (Interview Style)
================================================================================

Brute force idea:
- Rotate the list one step at a time.
- For each rotation, find the last node, detach it, and place it before head.
- Time complexity: O(k * n), too slow when k is large.

Better approach:
- First calculate the length.
- Reduce k using k % len.
- Find the split point and rearrange links once.

Optimal approach:
- Find length and tail in one pass.
- Convert the list into a circle using tail->next = head.
- Find the new last node at position len - k - 1.
- Break the circle after the new last node.
- Time complexity: O(n), space complexity: O(1).

Why this one is chosen:
- It touches each node at most a small constant number of times.
- It avoids repeated rotations.
- It only changes links, so it is memory efficient.

================================================================================
4. Intuition Building
================================================================================

Core idea in simple terms:
- Imagine the linked list as a chain.
- Rotating right means cutting the chain near the end and moving that ending
  piece to the front.
- Making the chain circular lets us choose any node as the new start.
- Once we choose the new start, we cut the circle just before it.

The trick or insight:
- Right rotation by k means the new head is len - k nodes from the original head.
- The new last node is one node before that.
- So we move len - k - 1 steps to find where to cut.

================================================================================
5. How to Recall Later
================================================================================

Key signals:
- "Rotate linked list"
- "k may be greater than length"
- "Move last k nodes to front"

One-line memory trick:
- Make it a circle, walk len - k - 1 steps, cut the circle.

================================================================================
6. Common Mistakes
================================================================================

Where beginners go wrong:
- Forgetting k = k % len.
- Not handling empty list before using head->next.
- Confusing the new head with the new last node.
- Moving len - k steps instead of len - k - 1 steps.
- Creating a circular list but forgetting to break it.
- Trying to swap values instead of changing links.

================================================================================
7. Complexity Analysis
================================================================================

Time Complexity: O(n)
- Finding the tail and length takes O(n).
- Finding the new last node takes at most O(n).
- Other operations are O(1).
- Total is O(n), not O(2n), because constants are ignored.

Space Complexity: O(1)
- No extra array, stack, recursion, or hash map is used.
- Only a few variables are created: tail, len, steps, newLastNode, newHead.

================================================================================
8. Alternative Approaches
================================================================================

1. Rotate one by one:
- Move the last node to the front k times.
- Easy to understand but inefficient.
- Time: O(k * n).

2. Two-pointer gap method:
- After reducing k, keep a gap of k nodes between two pointers.
- Move both until the fast pointer reaches the tail.
- The slow pointer will land at the new last node.
- Also O(n) time and O(1) space.

3. Copy values into an array:
- Store all node values in an array, rotate the array, then write values back.
- Easier for array thinkers, but it changes values instead of links.
- Uses O(n) extra space and is not the clean linked-list solution.
*/
