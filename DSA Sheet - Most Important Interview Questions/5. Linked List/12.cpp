#include <iostream>
using namespace std;


// Basic singly linked list node.
// What it does: stores one value and a pointer to the next node.
// Why needed: a linked list is made by chaining these nodes through next pointers.
// If removed: the Solution code would not know what a ListNode is, so it would not compile.
struct ListNode {
    int val;
    ListNode *next;

    // Default constructor: creates a node with value 0 and no next node.
    // Edge case helped: useful when a node is created without passing any data.
    ListNode() : val(0), next(nullptr) {}

    // Constructor with value only: creates a single standalone node.
    // Example: ListNode(5) creates 5 -> null.
    ListNode(int x) : val(x), next(nullptr) {}

    // Constructor with value and next pointer: creates a node already linked to another node.
    // Example: ListNode(5, node2) creates 5 -> node2.
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    // Problem: reverse a linked list in groups of exactly k nodes.
    // Pattern: recursion + linked-list pointer reversal.
    // Example:
    // Input:  1 -> 2 -> 3 -> 4 -> 5, k = 2
    // Output: 2 -> 1 -> 4 -> 3 -> 5
    // The last node 5 stays unchanged because it is not part of a full group of 2.
    ListNode* reverseKGroup(ListNode* head, int k) {
        // If the list is empty, there is nothing to reverse.
        // Why needed: prevents dereferencing null pointers later.
        // If removed: temp would become nullptr anyway, but this direct base case makes the recursion stop cleanly.
        // Edge case handled: head == nullptr.
        if (!head) return nullptr;

        // temp is used only to scan ahead and check whether the current group has k nodes.
        // We do not move head here because head must remain at the start of the group to reverse it later.
        ListNode* temp = head;

        // cnt counts how many nodes exist in the current group.
        // It also becomes the number of pointer reversals to perform after confirming the group is complete.
        int cnt = 0;

        // Step 1: Check if we have k nodes.
        // What this does:
        // - Moves temp forward at most k times.
        // - Counts how many nodes are available from head.
        //
        // Why necessary:
        // - The problem requires reversing only complete groups of k.
        // - If fewer than k nodes remain, they must stay in original order.
        //
        // What breaks if removed:
        // - The code would reverse even incomplete final groups.
        // - For example, 1 -> 2 -> 3 -> 4 -> 5 with k = 3 might incorrectly reverse 4 -> 5.
        //
        // Small dry run for head = 1 -> 2 -> 3 -> 4 -> 5, k = 2:
        // - cnt = 0, temp = 1
        // - move to 2, cnt = 1
        // - move to 3, cnt = 2
        // Now temp points to the first node after this group, which is 3.
        while (cnt < k && temp != nullptr) {
            // Move temp one node forward to count the current node.
            temp = temp->next;

            // Record that one more node exists in this group.
            cnt++;
        }

        // If fewer than k nodes are found, keep this remaining part unchanged.
        // Why necessary: incomplete groups should not be reversed.
        // If removed: the leftover nodes would be reversed, violating the problem requirement.
        //
        // Dry run edge example:
        // Current remaining list = 5, k = 2
        // cnt becomes 1, which is less than 2, so return 5 unchanged.
        //
        // Edge case handled: list length is not a multiple of k.
        if (cnt < k) return head; // not enough nodes

        // Step 2: Reverse the first k nodes.
        //
        // Important recursive idea:
        // Before reversing the current group, solve the rest of the list first.
        // temp currently points to the node after the current k-group.
        //
        // For 1 -> 2 -> 3 -> 4 -> 5, k = 2:
        // - Current group is 1 -> 2
        // - temp points to 3
        // - reverseKGroup(3, 2) returns the already processed tail: 4 -> 3 -> 5
        //
        // prevNode will become the "tail connection" for the reversed current group.
        // If this line is removed:
        // - The reversed current group would not correctly connect to the processed remaining list.
        // - We could lose access to nodes after the first group.
        ListNode* prevNode = reverseKGroup(temp, k); // recursive call for next group

        // curr starts at the original head of this group.
        // During reversal, curr walks through exactly k nodes.
        ListNode* curr = head;

        // Reverse exactly k links.
        //
        // Dry run for current group 1 -> 2 and prevNode = 4 -> 3 -> 5:
        // Iteration 1:
        // - nextNode = 2
        // - 1->next = 4
        // - prevNode = 1 -> 4 -> 3 -> 5
        // - curr = 2
        //
        // Iteration 2:
        // - nextNode = 3
        // - 2->next = 1
        // - prevNode = 2 -> 1 -> 4 -> 3 -> 5
        // - curr = 3
        //
        // After k iterations, prevNode is the new head of this reversed group.
        //
        // What breaks if this loop is removed:
        // - No actual reversal happens.
        //
        // Why cnt-- works:
        // - cnt was confirmed to be exactly k here, so this loop runs k times.
        while (cnt--) {
            // Save the next node before changing curr->next.
            // If removed: after rewiring curr->next, we would lose the rest of the current group.
            ListNode* nextNode = curr->next;

            // Reverse the pointer: current node now points to the already processed part.
            // This is the core linked-list reversal operation.
            // If removed: nodes would not reverse or reconnect correctly.
            curr->next = prevNode;

            // Move prevNode forward.
            // prevNode always represents the head of the partially reversed list.
            prevNode = curr;

            // Move curr to the next original node so the loop can continue reversing.
            curr = nextNode;
        }

        // Step 3: Return new head after reversing this group.
        // For group 1 -> 2, prevNode now points to 2, so 2 is returned.
        // If we returned head instead, we would return the old head 1, which is now the tail of this group.
        return prevNode;
    }
};

int main() {
    // No test driver is written here.
    // The Solution class is ready to be used by an online judge like LeetCode.
    
    return 0;
}

/*
### 1. 🧠 Problem Understanding

This is a linked-list transformation problem.
You are given the head of a singly linked list and an integer k.
The goal is to reverse nodes in groups of exactly k.

Key constraints/clues:
- It is a singly linked list, so you cannot move backward.
- Reversal must happen by changing pointers, not by swapping values.
- If the final group has fewer than k nodes, it must remain unchanged.
- The code assumes k > 0. If k == 0 or k < 0, this implementation can recurse forever.

### 2. 🔍 Pattern Recognition

Pattern used:
- Linked list reversal
- Recursion
- Process fixed-size chunks/groups

How to recognize this later:
- The problem says "reverse every k nodes" or "process linked list in groups".
- You need to keep leftover nodes unchanged.
- You repeatedly need to reverse a local section and connect it to the rest.

### 3. ⚡ Approach Breakdown (Interview Style)

Brute force idea:
- Copy all node values into an array.
- Reverse values in every group of k.
- Write values back into the linked list.
- This is easier but often rejected because it changes values, not node links, and uses extra memory.

Better approach:
- Iteratively reverse every k nodes using pointer manipulation.
- Use a dummy node and carefully connect each reversed group.
- This avoids recursion stack space but has more pointer bookkeeping.

Optimal approach used here:
- Recursively solve the list after the current group.
- Reverse the current k nodes and point its tail to the already processed rest.
- This is clean and interview-friendly, but uses recursion stack space.

### 4. 🧩 Intuition Building

Think of the list as blocks of size k.
First check whether the current block is complete.
If it is complete, trust recursion to fix the blocks after it.
Then reverse the current block and attach it to the fixed tail.

The trick:
- `temp` finds the start of the next block.
- `prevNode` stores the head of the already reversed remaining list.
- Each reversed node points to `prevNode`, so connection happens during reversal itself.

### 5. 🔁 How to Recall Later

Key signals:
- "Reverse nodes in k-group"
- "Leave remaining nodes as-is"
- "Linked list + fixed-size groups"

One-line memory trick:
Check k nodes, recurse on the rest, reverse current k into the returned tail.

### 6. ⚠️ Common Mistakes

- Forgetting to check whether k nodes exist before reversing.
- Losing the next node by changing `curr->next` before saving it.
- Returning the old head instead of the new head after reversal.
- Not connecting the reversed group to the already processed remaining list.
- Missing the k <= 0 edge case.
- Underestimating recursion stack space.

### 7. 📊 Complexity Analysis

Time Complexity: O(n)
- Each node is visited a constant number of times.
- The scan counts nodes group by group.
- The reversal also touches each node once.

Space Complexity: O(n / k) recursion stack
- One recursive call is made per complete group.
- In the worst practical case, k = 1, so the recursion depth becomes O(n).
- No extra data structure is used for storing nodes.

### 8. 🔄 Alternative Approaches

1. Iterative dummy-node approach:
Use a dummy node before head, repeatedly find each kth node, reverse that group, and reconnect the previous group to the new group head.
This gives O(n) time and O(1) extra space, but pointer handling is more complex.

2. Stack-based approach:
Push k nodes onto a stack, then pop them to reverse the group.
This is easier to reason about but uses O(k) extra space.

3. Array/value approach:
Store values in an array, reverse values in chunks, and write them back.
This is simple but does not truly reverse nodes and uses O(n) extra space.
*/
