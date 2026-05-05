#include <iostream>
using namespace std;

// Definition for singly-linked list.
// What this block does:
// - Creates the node structure used to build a singly linked list.
// - Each node stores one integer value and one pointer to the next node.
//
// Why this is necessary:
// - The middleNode function receives and returns ListNode pointers.
// - Without this struct definition, C++ does not know what ListNode means.
//
// What would break if removed:
// - The compiler/IntelliSense would report "ListNode is undefined".
// - The slow and fast pointer declarations would also fail because their type is unknown.
struct ListNode {
    // Stores the actual data inside the node.
    // Example: in list 1 -> 2 -> 3, the first node has val = 1.
    int val;

    // Points to the next node in the list.
    // If this is the last node, next is nullptr.
    ListNode *next;

    // Default constructor:
    // Creates a node with value 0 and no next node.
    // Useful when a node is created without immediately passing data.
    ListNode() : val(0), next(nullptr) {}

    // Constructor with value:
    // Creates a node containing x and points next to nullptr.
    // If this constructor were removed, creating ListNode(5) would fail.
    ListNode(int x) : val(x), next(nullptr) {}

    // Constructor with value and next pointer:
    // Creates a node containing x and directly connects it to another node.
    // Useful for quickly linking nodes together.
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // Problem:
    // - Given the head of a singly linked list, return the middle node.
    // - If there are two middle nodes, return the second middle node.
    //
    // DSA pattern used:
    // - Slow and fast pointers, also called the tortoise and hare technique.
    //
    // Why this pattern works:
    // - slow moves 1 step at a time.
    // - fast moves 2 steps at a time.
    // - By the time fast reaches the end, slow has covered half the distance.
    ListNode* middleNode(ListNode* head) {
        // slow starts at the head of the linked list.
        //
        // What it does:
        // - slow will eventually point to the middle node.
        //
        // Why this is necessary:
        // - We need one pointer that moves at half the speed of fast.
        //
        // What would break if removed:
        // - There would be no pointer tracking the middle position.
        //
        // Edge case:
        // - If head has only one node, slow starts at that node and is returned.
        ListNode* slow = head;

        // fast also starts at the head.
        //
        // What it does:
        // - fast checks how far we can move through the list.
        //
        // Why this is necessary:
        // - Its 2-step movement tells us when slow has reached the middle.
        //
        // What would break if removed:
        // - We would need another way to know when half the list has been crossed.
        //
        // Dry-run idea:
        // - In 1 -> 2 -> 3 -> 4 -> 5, fast moves 1 to 3 to 5 while slow moves 1 to 2 to 3.
        ListNode* fast= head;

        // Continue while fast can safely move ahead.
        //
        // What the condition checks:
        // - fast != NULL means fast is still pointing to a valid node.
        // - fast->next != NULL means fast has at least one more node after it.
        //
        // Why both checks are necessary:
        // - fast moves two steps using fast->next->next.
        // - If fast is NULL, accessing fast->next would crash.
        // - If fast->next is NULL, moving two steps is no longer possible.
        //
        // What would break if this condition were wrong:
        // - Removing fast != NULL can cause a null pointer access.
        // - Removing fast->next != NULL can also make fast->next->next unsafe.
        //
        // Edge cases handled:
        // - 1 node: loop does not run, returns head.
        // - 2 nodes: loop runs once, returns second node.
        // - Odd length: returns exact middle.
        // - Even length: returns second middle, as required by LeetCode-style problem.
        while(fast !=NULL && fast->next !=NULL){
            // Move slow by one node.
            //
            // What it does:
            // - Advances the middle tracker one step.
            //
            // Why this is necessary:
            // - Since fast moves twice as quickly, slow naturally lands at half the distance.
            //
            // What would break if removed:
            // - slow would stay at the head, so the function would return the wrong node for lists longer than 1.
            //
            // Dry run on 1 -> 2 -> 3 -> 4 -> 5:
            // - Start: slow = 1, fast = 1
            // - After 1st loop: slow = 2, fast = 3
            // - After 2nd loop: slow = 3, fast = 5
            // - Loop stops, answer = 3
            slow=slow->next;

            // Move fast by two nodes.
            //
            // What it does:
            // - Advances fast twice as far as slow.
            //
            // Why this is necessary:
            // - This creates the 2:1 speed ratio that makes slow reach the middle.
            //
            // What would break if removed or changed to one step:
            // - slow and fast would move at the same speed.
            // - slow would reach the end instead of the middle.
            //
            // Dry run on even list 1 -> 2 -> 3 -> 4:
            // - Start: slow = 1, fast = 1
            // - After 1st loop: slow = 2, fast = 3
            // - After 2nd loop: slow = 3, fast = NULL
            // - Loop stops, answer = 3, which is the second middle.
            fast=fast->next->next;
        }

        // Return the node slow is pointing to.
        //
        // Why this is correct:
        // - When fast reaches the end, slow has moved half as many steps.
        //
        // What would break if removed:
        // - The function would not return the required ListNode pointer.
        //
        // Complexity:
        // - Time: O(n), because fast scans through the list once.
        // - Space: O(1), because only two extra pointers are used.
        //
        // Edge case missed:
        // - If head is NULL, this code returns NULL safely.
        // - Some platforms guarantee the list is non-empty, but this implementation still behaves safely for an empty list.
        return slow;
    }
};

int main() {
    // Empty main function.
    // This file mainly contains the Solution class for an online judge style problem.
    // Removing main may be fine on LeetCode, but local compilation usually needs a main function.
    return 0;
}

/*
### 1. 🧠 Problem Understanding

* What type of problem is this?
  - This is a linked list traversal problem.
  - More specifically, it asks us to find a position-based node without using array indexing.

* What are key constraints/clues?
  - A linked list does not allow direct access like arr[n / 2].
  - We only have the head pointer.
  - We need the middle node.
  - If there are two middle nodes, the expected answer is the second middle node.
  - A one-pass solution is possible because the problem only asks for the middle, not for all node positions.

### 2. 🔍 Pattern Recognition

* Which DSA pattern is used?
  - Slow and fast pointers.
  - This is also called the tortoise and hare pattern.

* How can I recognize this pattern in future problems?
  - The problem involves a linked list.
  - You need to find a middle point, cycle, meeting point, or relative position.
  - You want to avoid counting all nodes first if a one-pass pointer technique can solve it.
  - One pointer moving faster than another gives useful information about structure or distance.

### 3. ⚡ Approach Breakdown (Interview Style)

* Brute force idea
  - First traverse the linked list and count the number of nodes.
  - Suppose the length is n.
  - Then traverse again until index n / 2.
  - Return that node.
  - This works, but it needs two passes.

* Better approach
  - Store all node addresses in a vector.
  - Return nodes[size / 2].
  - This gives easy indexing but uses O(n) extra space.

* Optimal approach (why this one is chosen)
  - Use two pointers: slow and fast.
  - slow moves one step.
  - fast moves two steps.
  - When fast reaches the end, slow is at the middle.
  - This uses one pass and constant extra space, so it is optimal.

### 4. 🧩 Intuition Building

* Explain the core idea in simple terms
  - Imagine two runners starting at the same point.
  - One runner moves twice as fast as the other.
  - When the faster runner reaches the finish line, the slower runner is halfway there.
  - In this problem, the slower runner's position is the middle node.

* What is the “trick” or insight?
  - You do not need the length of the linked list.
  - The fast pointer reaching the end indirectly tells you that slow has reached the middle.

### 5. 🔁 How to Recall Later

* 2–3 key signals to identify this problem again
  - "Find the middle of a linked list."
  - "Return the second middle in an even-length list."
  - "Do it in one pass" or "use constant extra space."

* One-line memory trick
  - "Fast runs twice; slow lands in the middle."

### 6. ⚠️ Common Mistakes

* Where beginners go wrong
  - Forgetting to check fast and fast->next before doing fast->next->next.
  - Moving both slow and fast by one step, which makes slow reach the end instead of the middle.
  - Returning fast instead of slow.
  - Thinking even-length lists should return the first middle when the problem asks for the second middle.
  - Commenting out the ListNode struct in local files, which makes ListNode undefined.

### 7. 📊 Complexity Analysis

* Time Complexity: O(n)
  - fast moves through the linked list two nodes at a time.
  - Even though it jumps two steps, the total work is still proportional to the number of nodes.
  - Each loop does constant work.

* Space Complexity: O(1)
  - The algorithm only uses two pointer variables: slow and fast.
  - It does not create an array, vector, map, or extra linked list.

### 8. 🔄 Alternative Approaches

* Count length first
  - Traverse the list once to count nodes.
  - Traverse again to the n / 2-th node.
  - This uses O(1) space but takes two passes.

* Store nodes in a vector
  - Push every node pointer into a vector.
  - Return the node at index size / 2.
  - This is easy to understand but uses O(n) extra space.

* Recursive counting
  - Recursively visit nodes and use the length to identify the middle.
  - This is usually unnecessary and uses call stack space.
*/
