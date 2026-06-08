#include <iostream>
using namespace std;


// Definition for singly-linked list.
// This structure represents one node of a singly linked list.
// Each node stores:
// 1. val  -> the data value
// 2. next -> address of the next node
//
// Why this is necessary:
// A linked list is not stored in continuous memory like an array, so every node
// must explicitly remember where the next node is.
//
// What would break if next did not exist:
// We could not move from one node to another, so cycle detection would be impossible.
struct ListNode {
    int val;
    ListNode *next;

    // Constructor initializes the node value and sets next to NULL.
    // Setting next to NULL is important because a newly created node should not
    // accidentally point to garbage memory.
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    /*
        Problem solved by this function:
        Given the head of a linked list, return the node where the cycle begins.
        If the linked list has no cycle, return NULL.

        Important edge cases:
        1. Empty list: head == NULL
        2. Single node with no cycle: head->next == NULL
        3. Single node pointing to itself
        4. Cycle starts at head
        5. Cycle starts somewhere in the middle
        6. Long list with no cycle

        High-level idea:
        Use Floyd's Cycle Detection Algorithm:
        - slow moves 1 step at a time.
        - fast moves 2 steps at a time.
        - If there is a cycle, fast will eventually meet slow inside the cycle.
        - After they meet, move slow back to head.
        - Move both slow and fast 1 step at a time.
        - The node where they meet again is the start of the cycle.

        Time Complexity: O(n)
        Each pointer walks through at most a linear number of nodes.

        Space Complexity: O(1)
        Only a few pointer variables and one boolean are used.
    */
    ListNode *detectCycle(ListNode *head) {
        // slow starts at head and moves one node per iteration.
        // Why needed:
        // It acts as the slower runner in Floyd's algorithm.
        // What breaks if removed:
        // We lose the reference needed to compare with fast and detect a meeting point.
        ListNode *slow=head;

        // fast also starts at head but moves two nodes per iteration.
        // Why needed:
        // The speed difference guarantees that if a cycle exists, fast will catch slow.
        // What breaks if removed:
        // We cannot detect the cycle in O(1) space using the two-pointer technique.
        ListNode *fast=head;

        // This flag records whether slow and fast actually met inside a cycle.
        // Why needed:
        // The loop can stop either because a cycle was found or because fast reached NULL.
        // What breaks if removed:
        // We might incorrectly run the second phase even when the list has no cycle.
        bool isCycle=false;

        // Continue while fast can safely move two steps.
        // Why both checks are necessary:
        // fast != NULL prevents accessing fast->next when fast itself is NULL.
        // fast->next != NULL prevents accessing fast->next->next when fast->next is NULL.
        //
        // Edge cases handled here:
        // - Empty list: fast == NULL, loop does not run.
        // - One-node list without cycle: fast->next == NULL, loop does not run.
        // - No-cycle list of any length: fast eventually reaches NULL.
        while(fast!=NULL && fast->next != NULL){
            // Move slow by one step.
            // Dry run example with cycle:
            // 3 -> 2 -> 0 -> -4
            //      ^         |
            //      |_________|
            //
            // Initially slow = 3.
            // After 1st loop slow = 2.
            // After 2nd loop slow = 0.
            // After 3rd loop slow = -4.
            slow=slow->next;

            // Move fast by two steps.
            // In the same example:
            // Initially fast = 3.
            // After 1st loop fast = 0.
            // After 2nd loop fast = 2.
            // After 3rd loop fast = -4.
            //
            // Why two steps:
            // The relative speed is 1 node per iteration, so inside a cycle fast closes
            // the gap with slow one node at a time and must eventually meet it.
            fast=fast->next->next;

            // If both pointers point to the same node, a cycle exists.
            // Why pointer comparison, not value comparison:
            // Different nodes can store the same val, so values are not reliable.
            // We need to know whether they are literally the same memory node.
            if(slow==fast){
            // Mark that a cycle has been found.
            // What breaks if removed:
            // After breaking out of the loop, the code would not know why the loop ended.
            isCycle=true;

            // Stop the first phase as soon as a meeting point is found.
            // Why needed:
            // Continuing is unnecessary; one meeting point is enough to find the cycle start.
            break;
            }
        }

        // If no meeting happened, there is no cycle.
        // This covers all acyclic lists, including empty and single-node lists.
        // What breaks if removed:
        // The next phase would try to move pointers until they meet, but in a no-cycle
        // list fast may be NULL, causing invalid pointer access or wrong behavior.
        if(!isCycle){
            return NULL;
        }

        // Reset slow to the head while fast stays at the meeting point.
        //
        // Why this works:
        // Let:
        // - L = distance from head to cycle start
        // - C = cycle length
        // - x = distance from cycle start to meeting point
        //
        // When slow and fast meet:
        // slow traveled L + x
        // fast traveled 2(L + x)
        // The extra distance traveled by fast is L + x, and it must be a multiple of C.
        // So L + x = kC, meaning L = kC - x.
        //
        // From the meeting point, moving kC - x steps lands exactly at the cycle start.
        // From head, moving L steps also lands exactly at the cycle start.
        // Therefore, moving both one step at a time makes them meet at the cycle entry.
        slow=head;

        // Second phase: find the cycle starting node.
        //
        // Dry run on 3 -> 2 -> 0 -> -4 -> back to 2:
        // First phase meeting happens at -4.
        // Reset slow to head:
        // slow = 3, fast = -4
        // Step 1: slow = 2, fast = 2
        // They meet at node 2, which is the cycle start.
        //
        // Edge cases:
        // - If cycle starts at head, slow=head and fast may already line up after moving
        //   through the math; this loop still returns head correctly.
        // - If one node points to itself, slow and fast meet in phase 1, slow resets to
        //   head, and the loop condition is already false, so head is returned.
        while(slow!=fast){
            // Move slow one step from the head side.
            slow=slow->next;

            // Move fast one step from the meeting point side.
            // Why one step now, not two:
            // The distance relationship proved above only works when both pointers move
            // at the same speed in phase 2.
            fast=fast->next;
        }

        // slow and fast now point to the first node of the cycle.
        // Returning either pointer is correct because slow == fast here.
        return slow;
    }
};

int main() {

    return 0;
}

/*
    ### 1. 🧠 Problem Understanding

    This is a linked list cycle entry problem.
    The task is not only to check whether a cycle exists, but also to find the exact
    node where the cycle begins.

    Key constraints/clues:
    - The structure is a singly linked list, so we can only move forward.
    - There may be a cycle, so normal traversal can become infinite.
    - Interview versions usually ask for O(1) extra space, which hints that a hash set
      is acceptable as a brute force idea but not the optimal solution.

    ### 2. 🔍 Pattern Recognition

    Pattern used: Fast and Slow Pointers / Floyd's Cycle Detection.

    Recognize it when:
    - A linked list may contain a cycle.
    - You need to detect repetition without extra memory.
    - The problem talks about two speeds, cycle, loop, duplicate path, or circular movement.

    ### 3. ⚡ Approach Breakdown (Interview Style)

    Brute force idea:
    Store every visited node address in a hash set.
    If a node appears again, that node is the cycle start.
    Time: O(n), Space: O(n).

    Better approach:
    Use slow and fast pointers to detect whether a cycle exists.
    This avoids storing visited nodes.

    Optimal approach:
    Floyd's algorithm with two phases:
    1. Detect meeting point inside the cycle.
    2. Reset one pointer to head and move both one step at a time to find cycle start.
    This is chosen because it gives O(n) time and O(1) space.

    ### 4. 🧩 Intuition Building

    Imagine two runners on a circular track.
    If one runner is faster, then once both are inside the circle, the faster runner must
    eventually catch the slower runner.

    The trick:
    The first meeting point is not necessarily the cycle start, but it contains enough
    distance information. Resetting one pointer to head balances the distances so both
    pointers meet exactly at the cycle entry.

    ### 5. 🔁 How to Recall Later

    Key signals:
    - Linked list has a possible cycle.
    - Need O(1) extra space.
    - Need the first node of the cycle, not just true/false.

    One-line memory trick:
    "Meet inside the loop, reset one to start, walk together to the entry."

    ### 6. ⚠️ Common Mistakes

    - Comparing node values instead of node addresses.
    - Forgetting to check fast != NULL and fast->next != NULL.
    - Returning the first meeting point instead of the cycle start.
    - Moving fast two steps in the second phase.
    - Not handling empty lists or one-node lists.

    ### 7. 📊 Complexity Analysis

    Time Complexity: O(n)
    In phase 1, slow and fast traverse a linear number of nodes before either finding a
    meeting point or reaching the end. In phase 2, both pointers again move at most a
    linear number of steps to reach the cycle start.

    Space Complexity: O(1)
    The algorithm uses only slow, fast, and isCycle. It does not allocate any data
    structure proportional to the list size.

    ### 8. 🔄 Alternative Approaches

    1. Hash set:
       Store visited node addresses. The first repeated node is the cycle start.
       Easier to understand, but uses O(n) extra space.

    2. Modify nodes temporarily:
       Mark visited nodes by changing their next pointers or values.
       This is usually not acceptable because it mutates the input list and can destroy
       the original structure.

    3. Cycle length method:
       First detect a cycle, then calculate the cycle length. Move one pointer cycleLength
       steps ahead from head, then move both pointers together. They meet at the cycle
       start. This is also O(n) time and O(1) space, but Floyd's reset method is shorter.
*/
