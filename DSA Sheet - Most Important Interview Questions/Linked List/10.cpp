#include <iostream>
using namespace std;

/*
    Problem represented by this file:
    - Each linked list stores a non-negative integer in reverse digit order.
      Example: 2 -> 4 -> 3 represents 342.
    - We need to return a new linked list representing the sum, also in reverse order.
      Example: (2 -> 4 -> 3) + (5 -> 6 -> 4) = 342 + 465 = 807,
      so the answer is 7 -> 0 -> 8.
*/
struct ListNode {
    // Stores one digit of the number.
    // Why needed: each node represents exactly one decimal place.
    // If removed, the list could not store the numeric digit at this position.
    int val;

    // Points to the next less-significant/more-significant digit depending on traversal.
    // In this problem, moving next means moving from ones place to tens, hundreds, etc.
    // If removed, nodes would not form a linked list.
    ListNode *next;

    // Default constructor: creates a node with digit 0 and no next node.
    // Edge case support: useful for dummy nodes or empty initialization.
    ListNode() : val(0), next(nullptr) {}

    // Constructor for a single isolated node.
    // Why needed: lets us easily create result nodes like new ListNode(sum % 10).
    ListNode(int x) : val(x), next(nullptr) {}

    // Constructor for a node that already points to another node.
    // Why needed: convenient when manually building test lists.
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    /*
        Function goal:
        - Add two numbers stored as reverse-order linked lists.
        - Return the head of a newly created linked list containing the answer.

        Pattern used:
        - Linked list traversal + elementary-school addition with carry.

        Why reverse order helps:
        - We naturally add from least significant digit to most significant digit.
        - Since the head is the ones digit, we can process from head to tail directly.
    */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        /*
            dummyHead is a placeholder node before the real answer.

            What it does:
            - Gives us a stable node before the result list starts.
            - The final answer begins at dummyHead->next.

            Why necessary:
            - Without a dummy node, we would need special handling for the first result node.
            - That usually creates extra if/else logic and more chances for bugs.

            What breaks if removed:
            - curr would have no safe initial node to attach new nodes to.
            - We would need to separately track whether the result list is empty.

            Space note:
            - This one extra node is O(1) auxiliary space.
        */
        ListNode* dummyHead = new ListNode(0);

        /*
            curr always points to the last node in the result list built so far.

            What it does:
            - Allows us to append each newly computed digit in O(1) time.

            Why necessary:
            - If we did not keep a tail pointer, appending might require traversing
              the result list again and again, causing O(n^2) behavior.

            What breaks if removed:
            - We would lose the place where the next result digit should be attached.
        */
        ListNode* curr = dummyHead;

        /*
            temp1 and temp2 are traversal pointers.

            What they do:
            - Walk through l1 and l2 without changing the original head pointers.

            Why necessary:
            - We need to read every digit from both lists.
            - Keeping l1 and l2 unchanged is cleaner and useful if the caller still
              needs the original list heads.

            What breaks if removed:
            - We would either mutate/use l1 and l2 directly, or have no way to move
              through the lists safely.
        */
        ListNode* temp1 = l1;
        ListNode* temp2 = l2;

        /*
            carry stores the overflow from adding two digits.

            Example:
            - 8 + 7 = 15, result digit is 5 and carry is 1.

            Why necessary:
            - Addition depends on the carry from the previous lower digit.

            What breaks if removed:
            - Sums like 9 -> 9 plus 1 would incorrectly become 0 -> 9
              instead of 0 -> 0 -> 1.
        */
        int carry = 0;

        /*
            Continue while at least one list still has digits.

            What it does:
            - Handles lists of equal length and unequal length.

            Why OR is necessary:
            - If one number has more digits, those remaining digits still need to be
              copied into the sum with carry applied.

            What breaks if changed to AND:
            - Example: 9 -> 9 plus 1 would stop after the first pair and miss the
              second 9.

            Edge cases handled here:
            - l1 longer than l2.
            - l2 longer than l1.
            - one list being NULL, if the platform allows it.
        */
        while (temp1 != NULL || temp2 != NULL) {
            /*
                Start this digit's sum with the carry from the previous position.

                Dry run example: l1 = 2 -> 4 -> 3, l2 = 5 -> 6 -> 4
                Iteration 1:
                - carry = 0, sum starts as 0.
                - add 2 and 5, sum becomes 7.
                - result digit is 7, carry remains 0.

                Why necessary:
                - Carry affects the next digit exactly like manual addition.

                What breaks if removed:
                - Overflow from the previous digit would be ignored.
            */
            int sum = carry;

            /*
                If temp1 exists, add its current digit and move to the next digit.

                What it does:
                - Reads one digit from the first number.

                Why the if check is necessary:
                - The lists may have different lengths.
                - If temp1 is NULL, temp1->val would crash.

                What breaks if temp1 = temp1->next is removed:
                - Infinite loop when temp1 is not NULL, because we would keep
                  reading the same node forever.
            */
            if (temp1) {
                sum += temp1->val;
                temp1 = temp1->next;
            }

            /*
                If temp2 exists, add its current digit and move to the next digit.

                Same reasoning as temp1:
                - Protects against NULL access.
                - Supports unequal-length input lists.
                - Advances traversal so the loop eventually finishes.

                Dry run continuation:
                Iteration 2 for 2 -> 4 -> 3 and 5 -> 6 -> 4:
                - sum starts with carry 0.
                - add 4 and 6, sum = 10.
                - result digit = 0, carry = 1.
            */
            if (temp2) {
                sum += temp2->val;
                temp2 = temp2->next;
            }

            /*
                Compute carry for the next digit.

                What it does:
                - sum / 10 extracts overflow beyond one decimal digit.
                - Since input digits are 0 to 9 and carry is at most 1,
                  carry will be either 0 or 1.

                Why necessary:
                - Needed for cases like 4 + 6 = 10 or 9 + 9 + 1 = 19.

                What breaks if removed:
                - The next higher digit would not receive the overflow.
            */
            carry = sum / 10;

            /*
                Create the result digit using sum % 10.

                What it does:
                - Keeps only the current ones-place digit of sum.
                - Appends that digit to the result list.

                Why modulo is necessary:
                - A list node must store a single digit, not values like 10, 15, or 19.

                What breaks if sum is stored directly:
                - The result list would violate the problem's digit-per-node rule.

                Dry run continuation:
                - Iteration 1: sum = 7, append 7.
                - Iteration 2: sum = 10, append 0, carry = 1.
                - Iteration 3: sum starts 1, add 3 and 4 => 8, append 8.
                Final result: 7 -> 0 -> 8.
            */
            curr->next = new ListNode(sum % 10);

            /*
                Move curr to the node just appended.

                Why necessary:
                - The next result digit must be attached after this new node.

                What breaks if removed:
                - Every new digit would overwrite dummyHead->next or attach at the
                  wrong place, losing previously created result nodes.
            */
            curr = curr->next;
        }

        /*
            If carry still remains, append it as a final new digit.

            What it handles:
            - Final overflow after processing all input nodes.

            Example:
            - 9 -> 9 represents 99.
            - 1 represents 1.
            - 99 + 1 = 100, so result should be 0 -> 0 -> 1.
            - The final 1 comes from this block.

            What breaks if removed:
            - Any addition that creates one extra digit at the end would be wrong.

            Edge case handled:
            - Both lists end, but carry is still 1.
        */
        if (carry) {
            curr->next = new ListNode(carry);
        }

        /*
            Return the real result head.

            Why dummyHead->next:
            - dummyHead is not part of the answer; it was only a helper.

            What breaks if returning dummyHead:
            - The answer would incorrectly start with an extra 0 node.

            Complexity:
            - Let n be length of l1 and m be length of l2.
            - Time: O(max(n, m)), because each node is visited once.
            - Space: O(max(n, m)) for the new result list.
              Auxiliary space, ignoring the output list, is O(1).
        */
        return dummyHead->next;
    }
};

int main() {
    /*
        Empty main for local compilation.

        Why it exists:
        - Online judges usually call Solution::addTwoNumbers directly.
        - In a local C++ file, main allows the program to compile as a complete executable.

        Edge case note:
        - No test cases are built here, so this file defines the solution but does not
          demonstrate runtime behavior by itself.
    */
    
    return 0;
}

/*
    ### 1. Problem Understanding

    - Type of problem:
      Linked list arithmetic / simulation problem.

    - What is being asked:
      Add two non-negative integers where each digit is stored in a linked list node.
      The digits are reversed, so the head node is the ones place.

    - Key constraints/clues:
      1. "Digits are stored in reverse order" means we can add from head to tail.
      2. "Each node contains a single digit" means every result node must store sum % 10.
      3. Lists may have different lengths, so traversal must continue while either list exists.
      4. A final carry may create an extra node.


    ### 2. Pattern Recognition

    - DSA pattern used:
      Linked list traversal + carry propagation.

    - How to recognize this pattern later:
      If a problem says numbers are represented digit-by-digit and asks for addition,
      multiplication, or incrementing, think "manual arithmetic with carry".

    - Why linked list matters:
      Since random access is not available, we process nodes sequentially with pointers.


    ### 3. Approach Breakdown (Interview Style)

    - Brute force idea:
      Convert both linked lists into integers, add them, then convert the sum back to
      a linked list.

      Problem with brute force:
      The numbers may be too large for int, long long, or even built-in numeric types.

    - Better approach:
      Store digits in arrays or strings, then perform addition.

      Problem with this:
      Extra storage is unnecessary because the linked lists already give digits in the
      correct order for addition.

    - Optimal approach:
      Traverse both lists together, add corresponding digits plus carry, create one
      result node per digit, and append a final carry if needed.

      Why this is chosen:
      It visits each node once, avoids integer overflow, and uses only constant extra
      working space apart from the required output list.


    ### 4. Intuition Building

    - Core idea:
      This is exactly how we add numbers on paper, starting from the rightmost digit.
      The only difference is that the linked list is already reversed, so the "rightmost"
      digit is conveniently at the head.

    - Trick/insight:
      Do not try to rebuild the full number. Just add digit by digit and carry forward
      the overflow.


    ### 5. How to Recall Later

    - Key signal 1:
      Digits are stored in reverse order.

    - Key signal 2:
      Need to add two numbers represented by linked lists.

    - Key signal 3:
      Carry can remain after both lists end.

    - One-line memory trick:
      "Walk both lists like paper addition: digit = sum % 10, carry = sum / 10."


    ### 6. Common Mistakes

    - Forgetting to handle different length lists.
    - Using while (l1 && l2) instead of while (l1 || l2).
    - Forgetting the final carry node.
    - Returning dummyHead instead of dummyHead->next.
    - Storing sum directly instead of sum % 10.
    - Moving curr before attaching the new node.
    - Trying to convert the whole list into an integer and causing overflow.


    ### 7. Complexity Analysis

    - Time complexity:
      O(max(n, m)), where n is the length of l1 and m is the length of l2.
      Reason: each node from both lists is visited at most once.

    - Space complexity:
      O(max(n, m)) for the returned linked list.
      If the output list is not counted as extra space, auxiliary space is O(1)
      because only a few pointers and integer variables are used.


    ### 8. Alternative Approaches

    - Convert to numbers:
      Simple to imagine but unsafe for very large inputs because of integer overflow.

    - Use stacks:
      Useful if digits are stored in forward order, for example 3 -> 4 -> 2 represents
      342. Stacks let us process from the least significant digit.

    - Reverse both lists first:
      Also useful for forward-order digit problems, but unnecessary here because the
      input is already in reverse order.

    - Recursion:
      Can simulate traversal, but carry management becomes less direct and recursion
      adds call stack overhead.
*/
