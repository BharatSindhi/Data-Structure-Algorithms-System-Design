#include <iostream>
// unordered_map is needed because each old node must quickly point us to its copied node.
// If this include is removed, unordered_map<Node*, Node*> will not compile.
#include <unordered_map>
using namespace std;


// Definition for a Node.
// This problem is about a linked list where every node has:
// 1. next   -> the usual pointer to the next node
// 2. random -> a pointer to any node in the list, or NULL
//
// Because random can point forward, backward, to itself, or to NULL, copying only next pointers
// is not enough. We need a way to preserve the exact relationships between original nodes.
class Node {
public:
    // Stores the data value of the node.
    int val;
    // Points to the next node in the normal linked-list chain.
    Node* next;
    // Points to any node in the list, possibly NULL.
    Node* random;
    
    // Constructor creates a fresh node with the same value but no connections yet.
    // This is important because copied nodes must be separate objects, not aliases
    // of the original nodes. If we reused old nodes, we would not be making a deep copy.
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        // Edge case: empty list.
        // What it does: if there is no original node, there is nothing to copy.
        // Why needed: prevents accessing head->val when head is NULL.
        // If removed: an empty input would cause a runtime crash / undefined behavior.
        // Dry run: head = NULL -> return NULL immediately.
        // Complexity impact: O(1).
        if (head == NULL) return NULL;

        // Hash map from original node address to copied node address.
        // What it does: m[oldNode] gives the clone of oldNode.
        // Why needed: random pointers refer to original nodes, so we need to translate
        // each original random target into the corresponding copied random target.
        // If removed: we could copy next links, but random links would be hard to assign
        // without repeatedly searching the list, causing O(n^2), or we might accidentally
        // point copied nodes back into the original list.
        // Dry run example:
        // Original: A(1) -> B(2), A.random = B, B.random = A
        // Map after creating copies: m[A] = A', m[B] = B'
        // Then A'.random = m[A.random] = m[B] = B'
        // Space: O(n), because every original node gets one map entry.
        unordered_map<Node*, Node*> m;

        // Step 1: Create the head of the new list
        // What it does: creates the first copied node using head's value.
        // Why needed: we need a starting point for the copied list.
        // If removed: there would be no new list head to return or attach later nodes to.
        // Dry run: if original head is A(1), newHead becomes A'(1).
        Node* newHead = new Node(head->val);
        // What it does: records that original head maps to copied head.
        // Why needed: if any random pointer points to the original head, this lets us
        // connect that random pointer to newHead.
        // If removed: random links targeting head would fail or become incorrect.
        // Dry run: B.random = A, so later B'.random = m[A] = A'.
        m[head] = newHead;

        // oldTemp starts from the second original node because head is already copied.
        // If this started at head, head would be duplicated twice.
        Node* oldTemp = head->next;
        // newTemp tracks the last node in the copied list so new nodes can be attached.
        // If removed, we would lose the place where the next copied node should connect.
        Node* newTemp = newHead;

        // Step 2: Copy next pointers and map old to new nodes
        // This loop copies the normal linked-list chain.
        // It does NOT assign random pointers yet, because a random pointer may target
        // a node that has not been copied at the exact moment we first see it.
        //
        // Dry run with A(1) -> B(2) -> C(3):
        // Before loop: newHead = A', oldTemp = B, newTemp = A'
        // Iteration 1: create B', map B -> B', attach A'.next = B'
        // Iteration 2: create C', map C -> C', attach B'.next = C'
        // After loop: copied next chain is A' -> B' -> C'
        //
        // Edge cases:
        // - Single node: oldTemp is NULL, loop is skipped, newHead alone is valid.
        // - Random cycles do not matter here because we only walk next pointers.
        //
        // Time: O(n), one pass over nodes after head.
        while (oldTemp != NULL) {
            // Create a separate copied node with the same value as the current original node.
            // If removed, the copied list would miss this node.
            Node* copyNode = new Node(oldTemp->val);
            // Store old -> new relationship for later random pointer assignment.
            // If removed, random pointers targeting oldTemp could not be translated.
            m[oldTemp] = copyNode;
            // Link the previous copied node to this newly copied node.
            // If removed, copied nodes would exist but the copied next chain would be broken.
            newTemp->next = copyNode;

            // Move copied-list pointer forward to the node just attached.
            // If removed, every next node would keep getting attached after the same node,
            // corrupting the copied chain.
            newTemp = newTemp->next;
            // Move original-list pointer forward so the loop progresses.
            // If removed, this becomes an infinite loop on the same oldTemp.
            oldTemp = oldTemp->next;
        }

        // Step 3: Copy random pointers using the map
        // Reset both pointers to the starts of their lists.
        // Why needed: after Step 2, oldTemp is NULL and newTemp is at the copied tail.
        // If not reset, we could not walk both lists in parallel to assign random pointers.
        oldTemp = head;
        newTemp = newHead;

        // Second pass: assign random pointers in the copied list.
        //
        // Key idea:
        // - oldTemp is the current original node.
        // - newTemp is its copied node.
        // - oldTemp->random is an original node.
        // - m[oldTemp->random] is the copied version of that random target.
        //
        // Dry run with A -> B -> C:
        // A.random = C, B.random = A, C.random = NULL
        // At A/A': A'.random = m[C] = C'
        // At B/B': B'.random = m[A] = A'
        // At C/C': C'.random = NULL
        //
        // Edge cases handled:
        // - random = NULL
        // - random points to itself
        // - random points backward or forward
        // - random pointers form cycles
        //
        // Time: O(n), one more pass.
        while (oldTemp != NULL) {
            // If the original random pointer is not NULL, connect the copied node's random
            // pointer to the copied version of that target.
            // If this condition was removed and we directly used m[oldTemp->random],
            // NULL could be inserted as a key in the map unnecessarily.
            if (oldTemp->random != NULL)
                // Translate original random target into copied random target.
                // If replaced with newTemp->random = oldTemp->random, the copied list
                // would point back into the original list, which is a shallow copy bug.
                newTemp->random = m[oldTemp->random];
            else
                // Preserve NULL random pointers.
                // If removed, random could accidentally remain uninitialized in other styles
                // of construction. Here the constructor already sets NULL, but this line makes
                // the intended behavior explicit and safe.
                newTemp->random = NULL;

            // Move both lists forward together.
            // This parallel movement works because Step 2 copied the next chain in same order.
            oldTemp = oldTemp->next;
            newTemp = newTemp->next;
        }

        // Return the head of the completely independent copied list.
        // If we returned head instead, we would return the original list, not the copy.
        // Overall complexity:
        // Time: O(n), because we do two linear passes over the linked list.
        // Space: O(n), because the hash map stores one old->new entry per node.
        // Note: The copied nodes themselves are required output space; the extra auxiliary
        // space used by the algorithm is the unordered_map.
        return newHead;
    }
};

int main() {
    // No test case is built here. On coding platforms like LeetCode, the judge creates
    // linked lists and calls copyRandomList directly.
    // Edge case missed by this local main: it does not verify the clone behavior.
    
    return 0;
}

/*
### 1. 🧠 Problem Understanding

This is a deep-copy linked list problem with an extra random pointer.

Each node has two relationships:
1. next relationship: normal linked list order.
2. random relationship: arbitrary connection to any node or NULL.

The main clue is that random can point anywhere. That means we cannot simply copy nodes
one by one and assign random immediately unless we can find the copied version of each
random target.

Key constraints / clues:
- Need a deep copy: copied nodes must be new nodes, not original nodes.
- random may point forward, backward, to itself, or to NULL.
- random links can create cycles even if next links do not.

### 2. 🔍 Pattern Recognition

Pattern used: Hash Map / Object Mapping.

We map every original node to its copied node:
original node address -> copied node address

Recognize this pattern when:
- You must clone a structure with arbitrary pointers.
- A node can reference another node that may be copied earlier or later.
- You need to preserve relationships, not just values.

Common examples:
- Clone Graph
- Copy List with Random Pointer
- Deep copy objects with references

### 3. ⚡ Approach Breakdown (Interview Style)

Brute force idea:
- First copy the normal next list.
- For every original node's random pointer, search the original list to find the random
  target's position, then move to the same position in the copied list.
- Time: O(n^2), because each random assignment may require a full scan.
- Space: O(1) extra, but too slow for large inputs.

Better approach:
- Use a hash map from original node to copied node.
- First pass creates all copied nodes and fills the map.
- Second pass assigns random pointers using the map.
- Time: O(n), Space: O(n).

Optimal approach:
- There is also an O(1) extra-space interweaving approach:
  insert each copied node directly after its original node, assign random using
  old->random->next, then separate the two lists.
- This code chooses the hash-map approach because it is simpler, safer, and easier to
  explain in interviews.

### 4. 🧩 Intuition Building

Think of every original node and copied node as two versions of the same person:
- Original A has clone A'
- Original B has clone B'

If A.random points to B, then A'.random must point to B'.

The trick is: before fixing random pointers, first build a dictionary that answers:
"Given this original node, where is its clone?"

Once that dictionary exists, random pointer assignment becomes direct.

### 5. 🔁 How to Recall Later

Key signals:
1. The problem says "deep copy" or "clone".
2. Nodes contain extra/arbitrary pointers.
3. A pointer can refer to a node that is not simply the next node.

One-line memory trick:
"Clone all nodes first, remember old-to-new, then translate pointers."

### 6. ⚠️ Common Mistakes

- Assigning newTemp->random = oldTemp->random, which points the copied list back into
  the original list.
- Trying to assign random pointers before all copied nodes exist.
- Forgetting the empty-list case.
- Forgetting that random can point to NULL.
- Creating copied nodes but not connecting next pointers correctly.
- Returning the original head instead of newHead.

### 7. 📊 Complexity Analysis

Time Complexity: O(n)
- First pass copies all nodes and next pointers.
- Second pass assigns all random pointers.
- Each unordered_map lookup is average O(1).

Space Complexity: O(n)
- The map stores one entry for each original node.
- The copied list itself is required output space, so the extra auxiliary space is O(n).

### 8. 🔄 Alternative Approaches

1. Interweaving / weaving approach:
- Insert each copied node immediately after its original node.
- Example: A -> B -> C becomes A -> A' -> B -> B' -> C -> C'
- Then A'.random can be set using A.random->next.
- Finally separate original and copied lists.
- Time: O(n), Extra Space: O(1).
- More memory efficient but trickier to implement correctly.

2. Recursive DFS with memoization:
- Treat the linked list as a graph where next and random are edges.
- Recursively clone each node and store old-to-new in a map.
- Time: O(n), Space: O(n).
- Very similar to Clone Graph, but recursion may use call-stack space and can be less
  comfortable for beginners in C++.
*/
