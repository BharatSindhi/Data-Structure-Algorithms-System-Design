#include <iostream>
using namespace std;


//  * Definition for singly-linked list.
// This struct defines one node in a singly linked list.
//
// What each node stores:
// - val: the integer value inside the node.
// - next: pointer/address of the next node.
//
// Why this is necessary:
// - A linked list is made of separate nodes connected by pointers.
// - Unlike arrays, linked-list elements are not stored next to each other in memory.
//
// What would break if next did not exist:
// - We could store values, but we could not connect nodes into a list.
// - mergeTwoLists would have no way to move from one node to the next.
//
// Edge cases represented by this structure:
// - next == nullptr means this node is the last node.
// - A list head can itself be nullptr, meaning the list is empty.
struct ListNode {
    int val;
    ListNode *next;

    // Default constructor:
    // Creates a node with value 0 and no next node.
    //
    // Why nullptr matters:
    // - It prevents next from pointing to garbage memory.
    // - A clean null pointer safely marks the end of a list.
    ListNode() : val(0), next(nullptr) {}

    // Constructor for a single node with value x.
    //
    // Dry run:
    // - ListNode node(5) creates: 5 -> null
    //
    // What would break if next were not initialized:
    // - Traversal could accidentally follow an invalid memory address.
    ListNode(int x) : val(x), next(nullptr) {}

    // Constructor for a node with both value and next pointer.
    //
    // Dry run:
    // - If next points to node 7, ListNode(3, next) creates: 3 -> 7 -> ...
    //
    // Why useful:
    // - Lets us connect nodes at creation time.
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    /*
        Problem solved by this function:
        Merge two sorted singly linked lists into one sorted linked list.

        Important assumption:
        - list1 and list2 are already sorted in non-decreasing order.
        - The code reuses the original nodes; it does not create new nodes.

        Core recursive idea:
        - The smaller head node must become the head of the merged list.
        - After choosing that head, recursively merge the rest.

        Example:
        - list1: 1 -> 2 -> 4
        - list2: 1 -> 3 -> 4
        - merged: 1 -> 1 -> 2 -> 3 -> 4 -> 4

        Why recursion fits:
        - A linked list is naturally recursive:
          head + merged(rest of list).

        Time complexity:
        - O(n + m), where n and m are the lengths of list1 and list2.
        - Each recursive call permanently chooses one node.

        Space complexity:
        - O(n + m) recursion stack in the worst case.
        - Auxiliary data structures are not used, but recursive calls still consume stack space.
    */
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        /*
            Base case: if either list is empty, return the other list.

            What this does:
            - If list1 is nullptr, no nodes remain in list1, so the answer is list2.
            - If list2 is nullptr, no nodes remain in list2, so the answer is list1.

            Why necessary:
            - Recursion needs a stopping point.
            - Once one sorted list is exhausted, the remaining nodes in the other list
              are already sorted and can be attached directly.

            What would break if removed:
            - The next lines would access list1->val or list2->val even when one pointer is null.
            - That would cause a crash/undefined behavior.
            - Recursion would also have no clean termination condition.

            Dry run:
            - list1: nullptr
            - list2: 3 -> 5 -> 7
            - Return list2 directly because there is nothing to compare.

            Edge cases handled:
            - Both lists empty: list1 == nullptr is true, so return list2, which is nullptr.
            - One list empty: return the non-empty list.
        */
        if (list1 == nullptr || list2 == nullptr) {
            /*
                Ternary return:
                - If list1 is empty, return list2.
                - Otherwise list2 must be empty, so return list1.

                Why this specific step is necessary:
                - It preserves all remaining nodes without copying them.

                What would break if removed:
                - The merged list would lose the remaining tail of the non-empty list.

                Complexity:
                - O(1), because it only returns a pointer.
            */
            return list1 == nullptr ? list2 : list1;
        }

        /*
            Compare the current head values.

            What this does:
            - Decides which node should come first in the merged list.
            - Because both lists are sorted, the smaller head is the smallest available node overall.

            Why <= instead of <:
            - If values are equal, choosing list1 first keeps nodes from list1 before equal nodes
              from list2. This makes the merge stable with respect to the two input lists.

            What would break if removed:
            - We would not know which head should be attached first.
            - The final list could become unsorted.

            Dry run:
            - list1 head = 1, list2 head = 3
            - 1 <= 3, so list1's head must be first.
        */
        if (list1->val <= list2->val) {
            /*
                Choose list1's current node as the next node in the merged list.

                What this does:
                - Keeps list1 as the head.
                - Sets list1->next to the result of merging:
                  list1's remaining nodes with all of list2.

                Why necessary:
                - After choosing list1's head, the rest of the answer must be built from
                  list1->next and list2.

                What would break if removed:
                - list1 would remain connected to its old next node only.
                - Nodes from list2 might never be inserted into the correct position.

                Step-by-step dry run:
                - list1: 1 -> 2 -> 4
                - list2: 1 -> 3 -> 4
                - Since 1 <= 1, choose the first list1 node.
                - Now solve smaller problem:
                  merge(2 -> 4, 1 -> 3 -> 4)
                - Whatever that returns becomes list1->next.

                Recursion pattern:
                - Choose one node.
                - Ask recursion to solve the smaller remaining problem.
                - Attach the solved smaller problem behind the chosen node.
            */
            list1->next = mergeTwoLists(list1->next, list2);

            /*
                Return list1 as the head of this merged sub-list.

                Why necessary:
                - The caller needs to know which node is the first node after merging.

                What would break if removed:
                - The chosen node would not be passed back up the recursion chain.

                Dry run continuation:
                - If recursive call returns 1 -> 2 -> 3 -> 4 -> 4,
                  returning list1 gives:
                  1 -> 1 -> 2 -> 3 -> 4 -> 4
            */
            return list1;
        } else {
            /*
                Choose list2's current node as the next node in the merged list.

                What this does:
                - Keeps list2 as the head.
                - Sets list2->next to the result of merging:
                  all of list1 with list2's remaining nodes.

                Why necessary:
                - If list2->val is smaller, it must appear before list1->val in the merged list.

                What would break if removed:
                - Smaller nodes from list2 could be skipped or placed after larger nodes.
                - The merged output might not stay sorted.

                Step-by-step dry run:
                - Suppose current list1: 2 -> 4
                - Suppose current list2: 1 -> 3 -> 4
                - Since 2 <= 1 is false, choose list2's 1.
                - Now solve smaller problem:
                  merge(2 -> 4, 3 -> 4)
                - Whatever that returns becomes list2->next.
            */
            list2->next = mergeTwoLists(list1, list2->next);

            /*
                Return list2 as the head of this merged sub-list.

                Why necessary:
                - list2 is the smaller current node, so it must be the front of this part.

                What would break if removed:
                - The recursion would fail to connect the chosen node to the final answer.
            */
            return list2;
        }
    }
};

int main() {
    
    return 0;
}

/*
================================================================================
1. 🧠 Problem Understanding
================================================================================

What type of problem is this?
- This is a linked list merging problem.
- More specifically, it merges two sorted linked lists into one sorted linked list.

Key constraints/clues:
- Both input lists are already sorted.
- Nodes are connected through next pointers.
- Either list may be empty.
- We only need to rearrange next pointers; new nodes are not required.
- Because the lists are singly linked, we can only move forward.

Important edge cases:
- list1 is empty.
- list2 is empty.
- Both lists are empty.
- Lists have duplicate values.
- One list is much longer than the other.
- All values in one list are smaller than all values in the other.


================================================================================
2. 🔍 Pattern Recognition
================================================================================

DSA pattern used:
- Two-pointer merge pattern.
- Recursive linked list processing.

How to recognize this pattern in future problems:
- You are given two sorted sequences.
- You need one sorted result.
- At each step, the smaller current element should be chosen.
- For linked lists, "move pointer forward" often means using node->next.

Classic related problems:
- Merge two sorted arrays.
- Merge k sorted lists.
- Merge sort on linked lists.
- Intersection-style problems where two list pointers move forward.


================================================================================
3. ⚡ Approach Breakdown (Interview Style)
================================================================================

Brute force idea:
- Copy all values from both linked lists into an array.
- Sort the array.
- Build a new linked list from the sorted values.
- Time: O((n + m) log(n + m)).
- Space: O(n + m).
- Problem: This ignores the fact that the input lists are already sorted.

Better approach:
- Use two pointers, one for each list.
- Repeatedly pick the smaller current node and attach it to the answer.
- This can be done iteratively using a dummy node.
- Time: O(n + m), Space: O(1) extra if we ignore the output links.

Optimal approach used here:
- Recursive two-pointer merge.
- Compare list1->val and list2->val.
- Choose the smaller head.
- Recursively merge the rest.
- Time: O(n + m).
- Space: O(n + m) because of recursion stack.

Why this one is chosen:
- The code is short and directly expresses the recursive structure of linked lists.
- Each call solves a smaller version of the same problem.
- It reuses existing nodes, so no extra linked-list nodes are created.


================================================================================
4. 🧩 Intuition Building
================================================================================

Core idea in simple terms:
- Imagine the first node of each list as the only two candidates that can come next.
- Since both lists are sorted, the smaller head must be the smallest remaining node.
- Pick it, then solve the same problem for the remaining nodes.

The trick or insight:
- You never need to search the whole list.
- The correct next node is always one of the two current heads.
- After choosing one head, the rest is just the same merge problem again.

Small dry run:
- list1: 1 -> 2 -> 4
- list2: 1 -> 3 -> 4

Steps:
- Compare 1 and 1: choose list1's 1.
- Compare 2 and 1: choose list2's 1.
- Compare 2 and 3: choose 2.
- Compare 4 and 3: choose 3.
- Compare 4 and 4: choose list1's 4.
- list1 is empty, attach remaining list2's 4.
- Result: 1 -> 1 -> 2 -> 3 -> 4 -> 4.


================================================================================
5. 🔁 How to Recall Later
================================================================================

Key signals:
- Two sorted lists are given.
- Need one sorted list.
- Only the current heads need comparison.

One-line memory trick:
- Pick smaller head, merge the rest.

Recursive template to remember:
- If one list is empty, return the other.
- If list1 head is smaller, list1->next = merge(list1->next, list2), return list1.
- Otherwise, list2->next = merge(list1, list2->next), return list2.


================================================================================
6. ⚠️ Common Mistakes
================================================================================

Where beginners go wrong:
- Forgetting the null base case before accessing list1->val or list2->val.
- Creating unnecessary new nodes when the problem allows reusing nodes.
- Returning list1->next or list2->next instead of returning the chosen head.
- Forgetting to attach the recursive result to next.
- Using < instead of <= and accidentally changing stability for equal values.
- Thinking the recursive solution is O(1) space; recursion uses stack space.
- Losing the remaining tail when one list becomes empty.


================================================================================
7. 📊 Complexity Analysis
================================================================================

Time complexity:
- Let n be the length of list1 and m be the length of list2.
- Each recursive call chooses exactly one node from either list1 or list2.
- At most n + m nodes are processed.
- Time: O(n + m).

Space complexity:
- No extra arrays, hash maps, or new linked-list nodes are used.
- However, recursion creates function calls on the call stack.
- Worst-case stack depth: O(n + m).
- Space: O(n + m) for this recursive version.

Note:
- An iterative dummy-node version can reduce auxiliary space to O(1).


================================================================================
8. 🔄 Alternative Approaches
================================================================================

Alternative 1: Iterative merge with dummy node
- Create a dummy node to simplify tail handling.
- Use a tail pointer to attach the smaller node each time.
- Time is O(n + m).
- Extra space is O(1).
- This is often preferred in production when recursion depth could be large.

Alternative 2: Copy values into array and sort
- Store all values from both lists.
- Sort them.
- Build a new linked list.
- Easy to understand but inefficient because it ignores that lists are already sorted.

Alternative 3: Priority queue
- Put current nodes into a min-heap.
- Useful for merging k sorted lists.
- Overkill for exactly two lists because a simple comparison is enough.

Alternative 4: Merge by creating new nodes
- Instead of rewiring existing nodes, allocate a new node for each selected value.
- Keeps original lists unchanged.
- Uses O(n + m) extra node space.
*/
