
// Node definition for a singly linked list.
// Each node stores one integer value and a pointer to the next node.
// This shape matters because, unlike arrays, we cannot directly access the
// middle or compare mirrored positions by index. We must walk through pointers.
struct ListNode {
    int val;
    ListNode *next;

    // Default constructor: creates a node with value 0 and no next node.
    // If next were not initialized to nullptr, traversals could follow garbage
    // memory and crash.
    ListNode() : val(0), next(nullptr) {}

    // Constructor for a single standalone node.
    // Example: ListNode(5) creates 5 -> null.
    ListNode(int x) : val(x), next(nullptr) {}

    // Constructor for linking a new node to an existing next node.
    // Example: ListNode(1, node2) creates 1 -> node2.
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    bool isPalindrome(ListNode* head) {

        // Empty list or single node
        // What: Handles the smallest linked lists immediately.
        // Why: A list with 0 or 1 node reads the same forward and backward.
        // If removed: The algorithm would still often work for a single node,
        // but it would do unnecessary pointer work. For an empty list, later
        // pointer use could become risky in modified versions of this code.
        // Dry run:
        //   head = null       -> true
        //   head = [7]        -> true
        // Edge cases handled: empty list, one-node list.
        // Complexity for this branch: O(1) time, O(1) space.
        if(head == nullptr || head->next == nullptr)
            return true;

        // slow moves one step at a time.
        // fast moves two steps at a time.
        // Why: When fast reaches the end, slow is at the middle.
        // If either pointer initialization is removed, we cannot locate the
        // middle in one pass.
        // Example: 1 -> 2 -> 2 -> 1
        //   start: slow=1, fast=1
        //   after 1 loop: slow=2(first), fast=2(second)
        //   after 2 loops: slow=2(second), fast=null
        // Now slow points to the start of the second half.
        ListNode* slow = head;
        ListNode* fast = head;

        // Find middle
        // What: Advances slow by 1 and fast by 2 until fast reaches the end.
        // Why: This is the fast/slow pointer pattern for finding the middle of
        // a linked list without knowing its length.
        // If removed: slow would stay at head, so the code would reverse the
        // whole list and compare incorrectly.
        // Dry run on even length: 1 -> 2 -> 2 -> 1
        //   loop 1: slow=2(first), fast=2(second)
        //   loop 2: slow=2(second), fast=null
        //   result: slow starts second half.
        // Dry run on odd length: 1 -> 2 -> 3 -> 2 -> 1
        //   loop 1: slow=2, fast=3
        //   loop 2: slow=3, fast=1(last)
        //   result: slow is at the exact middle.
        // Edge cases handled: even length and odd length lists.
        // Time spent here: O(n), because fast visits about n/2 nodes.
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }

        // Odd length -> skip middle node
        // What: If fast is not null, the list has odd length and slow is on the
        // middle node, so we move slow one step forward.
        // Why: The middle element does not need to match anything in a
        // palindrome. Example: in 1 -> 2 -> 3 -> 2 -> 1, the 3 is ignored.
        // If removed: The comparison would include the middle node against the
        // first half, causing false negatives for valid odd-length palindromes.
        // Dry run:
        //   1 -> 2 -> 3 -> 2 -> 1
        //   after middle search: slow=3, fast=1
        //   fast != null, so slow moves to 2(second half start)
        // Edge case handled: odd-length lists.
        // Edge case not needed for even length: fast is null, so slow already
        // points to the second half.
        if(fast != nullptr){
            slow = slow->next;
        }

        // Reverse second half
        // prev will become the head of the reversed second half.
        // Why reverse? Singly linked lists cannot move backward, so reversing
        // the second half lets us compare left-to-right on both halves.
        // If prev is not initialized to nullptr, the reversed tail may point to
        // garbage instead of ending cleanly.
        // Example before reverse:
        //   first half: 1 -> 2
        //   second half from slow: 2 -> 1
        // Example after reverse:
        //   prev: 1 -> 2
        // Now prev can be compared with head node by node.
        ListNode* prev = nullptr;

        // What: Standard iterative linked-list reversal.
        // Why: Each node's next pointer is redirected to the previous node.
        // If removed: second half remains in original order, so comparison would
        // compare first node with middle-side node instead of last node.
        // Dry run on slow = 2 -> 1:
        //   iteration 1:
        //     temp = 1
        //     slow->next = null       gives 2 -> null
        //     prev = 2
        //     slow = 1
        //   iteration 2:
        //     temp = null
        //     slow->next = 2          gives 1 -> 2 -> null
        //     prev = 1
        //     slow = null
        //   reversed second half is prev = 1 -> 2.
        // Edge cases handled: second half of length 1 or more.
        // Time: O(n/2), Space: O(1).
        while(slow){
            // Save the next node before breaking the original link.
            // If removed: once slow->next is changed, we lose access to the
            // rest of the list.
            ListNode* temp = slow->next;

            // Reverse the pointer direction for the current node.
            // If removed: no reversal happens, and prev cannot become the
            // mirrored half needed for palindrome comparison.
            slow->next = prev;

            // Move prev forward to the newly reversed node.
            // If removed: prev would never grow, so the reversed list would be
            // lost or incomplete.
            prev = slow;

            // Continue with the original next node saved in temp.
            // If removed: the loop would not progress correctly.
            slow = temp;
        }

        // Compare first half and reversed second half
        // What: Walk through the reversed second half and the original first
        // half together.
        // Why: For a palindrome, the first node must equal the last node, the
        // second node must equal the second-last node, and so on.
        // Why loop on prev only: prev has length floor(n/2), which is exactly
        // the number of pairs we need to compare.
        // If changed to while(head): odd/even cases could over-compare extra
        // first-half or middle nodes.
        // Dry run on 1 -> 2 -> 2 -> 1:
        //   after reverse: prev = 1 -> 2, head = 1 -> 2 -> 2 -> 1
        //   compare 1 and 1 -> ok
        //   compare 2 and 2 -> ok
        //   prev becomes null -> true
        // Dry run on 1 -> 2:
        //   after reverse: prev = 2, head = 1
        //   compare 2 and 1 -> false
        // Edge case handled: mismatch can return immediately.
        while(prev){
            // If any mirrored pair differs, the list is not a palindrome.
            // If this check is removed, every list with length >= 2 would return
            // true after traversal, even 1 -> 2 -> 3.
            if(prev->val != head->val){
                return false;
            }

            // Move to the next mirrored pair.
            // If these moves are removed, the loop would either compare the
            // same nodes forever or fail to inspect all pairs.
            prev = prev->next;
            head = head->next;
        }

        // All mirrored pairs matched.
        // Therefore the linked list is a palindrome.
        // Overall time complexity: O(n)
        //   middle search O(n/2) + reverse O(n/2) + compare O(n/2) = O(n).
        // Overall space complexity: O(1)
        //   only a few pointers are used; no array/stack/recursion.
        // Note: This solution mutates the list by reversing the second half and
        // does not restore it. Some interviewers may ask you to restore it after
        // comparison if the original list must remain unchanged.
        return true;
    }
};

/*
### 1. 🧠 Problem Understanding

This is a linked-list palindrome problem.

A palindrome means the sequence of values reads the same forward and backward:
  1 -> 2 -> 2 -> 1 is a palindrome.
  1 -> 2 -> 3 is not.

Key constraints/clues:
  - It is a singly linked list, so we cannot move backward.
  - Random access by index is not available.
  - The optimal target is usually O(n) time and O(1) extra space.
  - Empty and single-node lists are automatically palindromes.

### 2. 🔍 Pattern Recognition

Pattern used:
  - Fast and slow pointers to find the middle.
  - In-place linked-list reversal.
  - Two-pointer comparison after reversing the second half.

How to recognize it later:
  - The problem asks about symmetry in a singly linked list.
  - You need to compare the start with the end, but there is no backward pointer.
  - You see a clue like "O(1) extra space" or "do not use an array/stack".

### 3. ⚡ Approach Breakdown (Interview Style)

Brute force idea:
  - Copy all node values into an array.
  - Use two indices, one from the start and one from the end.
  - Easy, but costs O(n) extra space.

Better approach:
  - Use a stack for the first half or all nodes.
  - Compare while traversing the rest.
  - Still uses O(n) extra space in common versions.

Optimal approach:
  - Find the middle with slow/fast pointers.
  - Skip the middle node if the length is odd.
  - Reverse the second half.
  - Compare the first half with the reversed second half.
  - Chosen because it gives O(n) time and O(1) extra space.

### 4. 🧩 Intuition Building

Core idea:
  A palindrome requires mirrored values to match. In an array, comparing mirrors
  is easy because we can access both ends. In a singly linked list, the "end"
  is hard to move backward from, so we reverse the second half and turn the
  problem into a normal forward comparison.

The trick:
  Do not reverse the whole list. Only reverse the second half. Then the start of
  the list and the start of the reversed half represent mirrored positions.

### 5. 🔁 How to Recall Later

Key signals:
  - "Palindrome" + "linked list".
  - Need to compare first half with second half.
  - O(1) extra space is expected.

Memory trick:
  Find middle, flip second half, compare pair by pair.

### 6. ⚠️ Common Mistakes

Beginners often:
  - Forget to skip the middle node in odd-length lists.
  - Lose the rest of the list while reversing because they do not save temp.
  - Compare while head is not null instead of while the reversed half is not null.
  - Think slow always points to the exact start of the second half, which is only
    true for even lengths before the odd-length adjustment.
  - Forget that this implementation changes the original list structure.

### 7. 📊 Complexity Analysis

Time complexity: O(n)
  - Finding the middle takes O(n).
  - Reversing the second half takes O(n/2).
  - Comparing halves takes O(n/2).
  - Constants are ignored, so total time is O(n).

Space complexity: O(1)
  - The algorithm uses only pointer variables: slow, fast, prev, temp, and head.
  - It does not allocate an array, stack, or recursive call stack.

### 8. 🔄 Alternative Approaches

Array approach:
  Store all values in a vector, then compare from both ends. This is simple and
  beginner-friendly, but it uses O(n) extra space.

Stack approach:
  Push values into a stack, then traverse again and compare with stack top.
  This also uses O(n) extra space.

Recursive approach:
  Use recursion to reach the end, then compare while the call stack unwinds.
  Elegant, but it uses O(n) stack space and can be harder to reason about.

Restore-after-check approach:
  Use the same optimal method, but reverse the second half again after comparison
  to restore the original linked list. This is useful when the input list must
  remain unchanged.
*/
