#include <iostream>
using namespace std;

// Basic singly linked list node definition.
// Each node stores one value and one pointer to the next node.
// Why necessary: reverseBetween works by rewiring these next pointers.
// If next did not exist, the nodes would not form a linked list and reversal would be impossible.
  struct ListNode {
      int val;
      ListNode *next;
      // Default constructor creates a node with value 0 and no next node.
      ListNode() : val(0), next(nullptr) {}
      // Constructor for creating a single isolated node with value x.
      ListNode(int x) : val(x), next(nullptr) {}
      // Constructor for creating a node that already points to another node.
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 

class Solution {
public:
    // Problem: Reverse only the nodes from position left to position right in a singly linked list.
    // Positions are 1-based, so left = 1 means the head node.
    //
    // Example:
    // head: 1 -> 2 -> 3 -> 4 -> 5, left = 2, right = 4
    // reverse nodes 2, 3, 4 only
    // result: 1 -> 4 -> 3 -> 2 -> 5
    //
    // Pattern used: in-place linked list reversal with boundary reconnection.
    // Time complexity: O(n), because we move through the list at most once.
    // Space complexity: O(1), because only a fixed number of pointers are used.
    ListNode* reverseBetween(ListNode* head, int left, int right) {

        // Edge case 1: empty list.
        // If head is NULL, there are no nodes to reverse.
        //
        // Edge case 2: left == right.
        // If both positions are the same, the reversal range has exactly one node.
        // Reversing one node changes nothing, so we can return immediately.
        //
        // Why necessary:
        // - Without head == NULL check, curr->next later could dereference NULL.
        // - Without left == right check, the later pointer reversal would still work for many cases,
        //   but it does unnecessary work and can make reasoning about a one-node segment harder.
        //
        // Dry run:
        // head = NULL, left = 1, right = 1 -> return NULL.
        // head = 7, left = 1, right = 1 -> return 7 unchanged.
        if(head == NULL || left == right) {
            return head;
        }

        // prev will track the node just before curr while we walk to the left position.
        // Initially there is no node before head, so prev is NULL.
        //
        // During reversal, prev will also become the previous node in the reversed part.
        // This reuse is common in linked list problems: the meaning of a pointer can evolve by phase.
        //
        // If this is removed:
        // We lose the ability to reconnect the part before left to the new head of the reversed segment.
        ListNode* prev = NULL;

        // curr starts at head and will move until it reaches the left-th node.
        // Later, curr is the pointer to the current node being reversed.
        //
        // If this is removed:
        // We would have no pointer with which to traverse or reverse the list.
        ListNode* curr = head;

        // Move curr to left position
        // Goal of this loop:
        // Move curr to the first node that must be reversed.
        // Move prev to the node immediately before that reversal segment.
        //
        // We decrement both left and right because once curr moves forward,
        // the remaining number of nodes to reverse shrinks relative to curr.
        //
        // Dry run for 1 -> 2 -> 3 -> 4 -> 5, left = 2, right = 4:
        // Start: prev = NULL, curr = 1, left = 2, right = 4
        // Iteration 1:
        //   prev = 1
        //   curr = 2
        //   left = 1
        //   right = 3
        // Stop because curr is now at position 2, the start of the segment.
        //
        // What would break if this loop is removed:
        // The algorithm would always start reversing from head, even when left > 1.
        //
        // Edge case handled:
        // If left = 1, the loop does not run, so curr stays at head and prev stays NULL.
        //
        // Edge case missed by this code:
        // It assumes left and right are valid positions within the list.
        // If left is greater than list length, curr can become NULL and curr->next later will crash.
        while(left > 1) {
            // Move prev one step forward so it trails curr.
            prev = curr;
            // Move curr one step forward toward the left-th node.
            curr = curr->next;

            // One less step remains before reaching the left boundary.
            left--;
            // Since curr moved forward, the number of nodes still to reverse also decreases.
            right--;
        }

        // Store connections
        // connection stores the node before the reversed segment.
        // For left > 1, this is the node that must point to the new head of the reversed part.
        // For left == 1, connection is NULL because the reversed segment starts at head.
        //
        // Example left = 2:
        // 1 -> 2 -> 3 -> 4 -> 5
        // connection = 1
        //
        // If this is removed:
        // After reversing 2 -> 3 -> 4 into 4 -> 3 -> 2,
        // node 1 would not know where to point.
        ListNode* connection = prev;

        // tail stores the first node of the segment before reversal.
        // After reversal, this same node becomes the tail of the reversed segment.
        //
        // Example:
        // Before reversal segment: 2 -> 3 -> 4
        // After reversal segment:  4 -> 3 -> 2
        // tail = 2, and later tail->next must connect to node 5.
        //
        // If this is removed:
        // We would lose the node that must connect the reversed segment to the remaining suffix.
        ListNode* tail = curr;

        // Reverse nodes
        // This loop reverses exactly right nodes starting from curr.
        // Remember: right was reduced while moving to left.
        // So now right means "how many nodes are in the target segment."
        //
        // For original left = 2, right = 4:
        // After the first loop, right = 3.
        // That means reverse 3 nodes: 2, 3, and 4.
        //
        // Core reversal idea:
        // Save next node, reverse current node's next pointer, then advance prev and curr.
        //
        // Dry run on 1 -> 2 -> 3 -> 4 -> 5, left = 2, right = 4:
        // Before loop:
        //   connection = 1, tail = 2, prev = 1, curr = 2, right = 3
        //
        // Iteration 1:
        //   temp = 3
        //   2->next = 1
        //   prev = 2
        //   curr = 3
        //   right = 2
        //
        // Iteration 2:
        //   temp = 4
        //   3->next = 2
        //   prev = 3
        //   curr = 4
        //   right = 1
        //
        // Iteration 3:
        //   temp = 5
        //   4->next = 3
        //   prev = 4
        //   curr = 5
        //   right = 0
        //
        // Now prev points to the new head of the reversed segment, node 4.
        // curr points to the first node after the reversed segment, node 5.
        //
        // Temporary issue during reversal:
        // 2 points back to 1, which creates a backward link inside the list.
        // This is fixed later by reconnecting connection->next and tail->next.
        //
        // What would break if temp is not used:
        // Once curr->next is changed, we lose access to the rest of the list.
        while(right > 0) {
            // Save the next node before changing curr->next.
            // This prevents losing the remainder of the list.
            ListNode* temp = curr->next;

            // Reverse the direction of the current link.
            // Instead of curr pointing forward, it points to the previous node.
            curr->next = prev;
            // Move prev forward; prev becomes the head of the reversed part built so far.
            prev = curr;
            // Move curr forward using the saved pointer.
            curr = temp;

            // One node from the target segment has been reversed.
            right--;
        }

        // Connect first part
        // If connection is not NULL, the reversal started somewhere after head.
        // The node before the segment must now point to prev, the new head of the reversed segment.
        //
        // Example:
        // connection = 1, prev = 4
        // Set 1->next = 4.
        //
        // If this block is removed:
        // The prefix before left would still point to the old segment head,
        // which became the tail after reversal, causing an incorrect or cyclic structure.
        if(connection != NULL) {
            connection->next = prev;
        } else {
            // If connection is NULL, the reversed segment started at the original head.
            // Therefore the list's head itself must change to prev.
            //
            // Example:
            // 1 -> 2 -> 3, left = 1, right = 2
            // After reversal, head should be 2, not 1.
            //
            // If this assignment is removed:
            // The function would return the old head, even though it is no longer first.
            head = prev;
        }

        // Connect last part
        // tail was the first node of the segment before reversal.
        // After reversal, it is the last node of the reversed segment.
        // It must point to curr, the first node after the reversed segment.
        //
        // Example:
        // tail = 2, curr = 5
        // Set 2->next = 5.
        //
        // If this is removed:
        // The reversed segment would not connect to the suffix of the list.
        // In many cases it may also leave a cycle, such as 1 <-> 2 during intermediate reversal.
        //
        // Edge cases handled:
        // - If right was the last position, curr is NULL, so tail->next = NULL correctly ends the list.
        // - If left is 1, tail still correctly becomes the last node of the reversed prefix.
        tail->next = curr;

        // Return the possibly updated head.
        // If left > 1, head is unchanged.
        // If left == 1, head was updated to the new front of the list.
        return head;
    }
};
int main() {
    
    return 0;
}

/*
### 1. 🧠 Problem Understanding

This is a linked list pointer manipulation problem.
The task is to reverse only a continuous section of a singly linked list, from position left to position right.

Key constraints and clues:
- The list is singly linked, so we cannot move backward.
- The reversal must happen between two positions, not necessarily the entire list.
- The best solution should usually be in-place, because linked list nodes can be rewired with pointers.
- Positions are 1-based, so careful boundary handling is important.

### 2. 🔍 Pattern Recognition

Pattern used: in-place linked list reversal with boundary reconnection.

Recognize this pattern when:
- The problem asks to reverse nodes, not values.
- The data structure is a singly linked list.
- You need to modify only a portion of the list.
- The words "between", "from m to n", "sublist", or "range" appear.

### 3. ⚡ Approach Breakdown (Interview Style)

Brute force idea:
- Copy all node values into an array.
- Reverse the values from left to right inside the array.
- Write values back into the linked list.
- This is easier, but it changes values instead of rewiring nodes and uses O(n) extra space.

Better approach:
- Traverse to the left position.
- Reverse the selected segment by changing next pointers.
- Reconnect the prefix and suffix afterward.

Optimal approach:
- Use a few pointers: prev, curr, connection, tail, and temp.
- Reverse the target segment in-place.
- This is chosen because it runs in O(n) time and O(1) extra space.

### 4. 🧩 Intuition Building

Think of the list as three parts:
1. Prefix before left
2. Middle segment from left to right
3. Suffix after right

The middle is reversed like a normal linked list reversal.
The trick is remembering the two open ends:
- connection remembers where the prefix ends.
- tail remembers where the reversed segment will end.

After reversing, attach:
- prefix -> new middle head
- new middle tail -> suffix

### 5. 🔁 How to Recall Later

Key signals:
- "Reverse linked list from position left to right"
- "Do it in one pass" or "in-place"
- "Singly linked list sublist reversal"

One-line memory trick:
Reach left, save both borders, reverse the middle, reconnect both ends.

### 6. ⚠️ Common Mistakes

- Forgetting to save curr->next before reversing curr->next.
- Not handling left = 1, where the head changes.
- Forgetting to connect the tail of the reversed segment to the suffix.
- Off-by-one errors because positions are 1-based.
- Assuming curr is always valid when the input positions may be invalid.
- Creating a cycle by reversing links but not reconnecting correctly afterward.

### 7. 📊 Complexity Analysis

Time complexity: O(n)
- In the worst case, we walk through nodes before left and then reverse nodes up to right.
- Each relevant node is visited a constant number of times.

Space complexity: O(1)
- No extra list, array, stack, or recursion is used.
- Only a fixed number of pointer variables are stored.

### 8. 🔄 Alternative Approaches

1. Value swapping:
   Store values in an array, reverse the selected range, and write them back.
   Easier to understand, but not ideal because it changes values rather than node links and uses O(n) space.

2. Dummy node approach:
   Create a dummy node before head to simplify the left = 1 case.
   This often makes the code cleaner because there is always a node before the reversal segment.

3. Head insertion within the sublist:
   Keep inserting nodes from the sublist after connection.
   This is another O(n), O(1) method and is popular in interviews, but can feel less intuitive at first.
*/
