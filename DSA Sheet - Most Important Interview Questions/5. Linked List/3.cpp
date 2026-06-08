/*
================================================================================
PROBLEM: Linked List Cycle Detection
================================================================================

Goal:
  Given the head of a singly linked list, determine whether the linked list has
  a cycle.

Cycle meaning:
  A cycle exists if some node's next pointer points back to an earlier node
  instead of eventually reaching NULL.

Example with cycle:
  1 -> 2 -> 3 -> 4
       ^         |
       |_________|

Example without cycle:
  1 -> 2 -> 3 -> 4 -> NULL

Core idea:
  Use two pointers:
    - slow moves 1 step at a time.
    - fast moves 2 steps at a time.

  If a cycle exists, fast will eventually "lap" slow and both pointers will
  meet at the same node. If there is no cycle, fast will reach NULL.

Pattern:
  Floyd's Cycle Detection Algorithm, also called the tortoise and hare method.
================================================================================
*/

#include <iostream>
using namespace std;


// Definition for singly-linked list.
// What this struct represents:
//   A node in a singly linked list. Each node stores:
//     1. val  -> the integer data
//     2. next -> pointer to the next node
//
// Why it is necessary:
//   The cycle detection algorithm works by following next pointers from node to node.
//
// What would break if removed:
//   ListNode would be undefined, so hasCycle(ListNode *head) could not compile.
struct ListNode {
    int val;                                  // Stores the node's value.
                                              // The cycle algorithm does not use val; it only follows pointers.
                                              // If removed, this exact constructor would break because it initializes val.

    ListNode *next;                           // Stores the address of the next node.
                                              // This is the most important field for cycle detection.
                                              // If removed, we could not traverse the linked list or detect cycles.

    ListNode(int x) : val(x), next(NULL) {}   // Constructor: creates a node with value x and no next node initially.
                                              // Setting next to NULL is important because a new standalone node should
                                              // not accidentally point to garbage memory.
};

class Solution {
public:
    /*
    Function: hasCycle

    What it does:
      Returns true if the linked list contains a cycle, otherwise returns false.

    Why this approach is necessary:
      We want to detect a cycle without modifying the list and without using
      extra memory like a hash set. Slow/fast pointers give O(1) extra space.

    What would break if the function were removed:
      There would be no API to solve the problem.

    Step-by-step dry run, no cycle:
      List: 1 -> 2 -> 3 -> 4 -> NULL

      Start:
        slow = 1, fast = 1

      Iteration 1:
        slow = 2
        fast = 3
        slow != fast

      Iteration 2:
        slow = 3
        fast moves from 3 to NULL through 4
        loop stops because fast == NULL

      Return false.

    Step-by-step dry run, with cycle:
      List: 1 -> 2 -> 3 -> 4 -> 2 ...

      Start:
        slow = 1, fast = 1

      Iteration 1:
        slow = 2
        fast = 3

      Iteration 2:
        slow = 3
        fast = 2    because fast jumps 3 -> 4 -> 2

      Iteration 3:
        slow = 4
        fast = 4    because fast jumps 2 -> 3 -> 4

      slow == fast, so return true.

    Edge cases handled:
      - Empty list: head == NULL, loop never runs, returns false.
      - One node without cycle: fast->next == NULL, loop never runs, returns false.
      - One node pointing to itself: fast and fast->next are not NULL, both move
        back to the same node, returns true.
      - Two-node cycle: fast eventually meets slow.

    Complexity:
      Time  : O(N), because each pointer moves through the list at most a linear
              number of steps before either meeting or reaching NULL.
      Space : O(1), because only two pointer variables are used.
    */
    bool hasCycle(ListNode *head) {
        ListNode* slow =head;                  // Slow pointer starts at the head and moves one node per loop.
                                              // Why necessary: it gives the fast pointer something to catch.
                                              // If removed, we would have no reference pointer for detecting a meeting.

        ListNode* fast=head;                   // Fast pointer also starts at the head but moves two nodes per loop.
                                              // Why necessary: the speed difference is what guarantees a meeting in a cycle.
                                              // If removed, we could not use Floyd's cycle detection.

        // Continue only while fast can safely move two steps.
        // Why both checks are necessary:
        //   fast != NULL prevents dereferencing a NULL pointer.
        //   fast->next != NULL prevents accessing fast->next->next when fast->next is NULL.
        //
        // What would break if this condition were weakened:
        //   The code could crash on lists with 0, 1, or even-length non-cyclic nodes.
        while(fast != NULL && fast->next!=NULL){
              slow=slow->next;                // Move slow by one step.
                                              // Why necessary: slow represents normal traversal speed.
                                              // If removed, slow would stay at head and the meeting logic would be wrong.

              fast=fast->next->next;          // Move fast by two steps.
                                              // Why necessary: fast must gain one node on slow per iteration inside a cycle.
                                              // If changed to one step, slow and fast would move together and give false positives.

              // If both pointers point to the same node, there must be a cycle.
              // Why:
              //   In a non-cyclic list, fast reaches NULL and cannot come back.
              //   In a cyclic list, fast loops around and eventually catches slow.
              if(slow==fast){
                return true;                  // Cycle found.
                                              // If removed, the loop might continue forever inside a cyclic list.
              }
        }

        // If the loop ended, fast reached the end of the list.
        // That can only happen when there is no cycle.
        return false;
    }
};

int main() {
    // Placeholder main for local compilation.
    // Online judges usually call Solution::hasCycle directly.
    return 0;
}

/*
================================================================================
1. 🧠 Problem Understanding
================================================================================

What type of problem is this?
  This is a linked-list pointer traversal problem. More specifically, it asks
  whether traversal from head eventually reaches NULL or gets trapped in a loop.

Key constraints/clues:
  - The list is singly linked, so we can only move forward using next.
  - We only need true/false, not the cycle length or starting node.
  - The list may be empty.
  - A cycle means NULL is never reached.
  - The ideal solution should not modify node values or next pointers.

Think like a problem solver:
  If a list has no cycle, every forward move gets closer to NULL.
  If a list has a cycle, once you enter the cycle, you keep visiting nodes
  forever. So the challenge is detecting "forever" without actually looping
  forever.

================================================================================
2. 🔍 Pattern Recognition
================================================================================

DSA pattern used:
  Floyd's Cycle Detection Algorithm, also known as slow and fast pointers.

How to recognize this pattern in future problems:
  Look for:
    1. A linked list or sequence where movement is one-directional.
    2. A question about cycle, loop, repetition, or meeting.
    3. A need for O(1) extra space.

Common problems using this pattern:
  - Detect cycle in linked list.
  - Find the starting node of a cycle.
  - Find middle of a linked list.
  - Happy Number cycle detection.
  - Duplicate number in an array modeled as pointer jumps.

================================================================================
3. ⚡ Approach Breakdown (Interview Style)
================================================================================

Brute force idea:
  For every node, start again from head and see if that node is visited again.

  Problem:
    This is inefficient and awkward. It can become O(N^2), and it still needs
    careful handling to avoid infinite loops.

Better approach:
  Store visited node addresses in a hash set.

  Process:
    Traverse the list.
    If the current node is already in the set, there is a cycle.
    If current becomes NULL, there is no cycle.

  Complexity:
    Time O(N), Space O(N).

Optimal approach:
  Use slow and fast pointers.

  Why optimal:
    It detects the cycle in O(N) time and O(1) extra space. Since we may need to
    inspect many nodes to know whether a cycle exists, O(N) time is expected.
    Reducing extra space from O(N) to O(1) is the main win.

================================================================================
4. 🧩 Intuition Building
================================================================================

Core idea in simple terms:
  Imagine two runners on a track. One runs slowly, one runs twice as fast.

  If the path is a straight road:
    The fast runner reaches the end first. No cycle.

  If the path is a circular track:
    The fast runner must eventually catch the slow runner. Cycle exists.

The trick:
  Do not try to remember every node. Instead, use relative speed.

Why meeting proves a cycle:
  In a normal list, pointers only move forward and eventually hit NULL.
  There is no way for fast to come back and meet slow unless nodes repeat.

================================================================================
5. 🔁 How to Recall Later
================================================================================

Key signals:
  1. Linked list has a possible loop.
  2. Need to detect repetition without extra memory.
  3. Problem asks true/false about cycle existence.

One-line memory trick:
  "If fast can lap slow, there is a loop."

================================================================================
6. ⚠️ Common Mistakes
================================================================================

1. Checking only fast != NULL:
   Then fast->next->next can crash when fast->next is NULL.

2. Moving fast by only one step:
   If both pointers move at the same speed from the same start, they remain
   together and the logic becomes meaningless.

3. Comparing node values instead of node addresses:
   Two different nodes can store the same val. A cycle is about pointers, so
   compare slow == fast, not slow->val == fast->val.

4. Returning false too early:
   You can only conclude no cycle when fast reaches NULL or fast->next reaches
   NULL.

5. Modifying the list:
   Marking nodes by changing values or breaking links can destroy input data and
   is not acceptable in most interviews.

================================================================================
7. 📊 Complexity Analysis
================================================================================

Time complexity:
  O(N)

Reason:
  - In a non-cyclic list, fast reaches NULL after about N/2 loop iterations.
  - In a cyclic list, once both pointers are inside the cycle, fast gains one
    node per iteration on slow and must eventually meet it.
  - Therefore, the total number of pointer moves is linear in the number of
    nodes.

Space complexity:
  O(1)

Reason:
  Only two pointer variables, slow and fast, are used. No hash set, array, or
  recursion stack grows with input size.

================================================================================
8. 🔄 Alternative Approaches
================================================================================

Hash set approach:
  Store every visited node address. If a node appears again, return true.
  This is simple and very readable, but uses O(N) extra memory.

Temporary modification approach:
  Mark visited nodes by changing their next pointers or values. This can detect
  repetition, but it damages the list and is usually rejected unless explicitly
  allowed.

Node count limit approach:
  If the list length were known in advance, traversing more than that many steps
  would imply a cycle. In real linked-list cycle problems, the length is usually
  unknown, so this is not practical.

Floyd's algorithm:
  The best interview choice for this problem because it is clean, fast, and uses
  constant extra space.
================================================================================
*/
