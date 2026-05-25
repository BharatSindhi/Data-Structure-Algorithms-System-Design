#include <iostream>
#include <stack>
using namespace std;

/*
    Problem this code solves:
    Implement a Queue (FIFO: First In, First Out) using only Stacks (LIFO: Last In, First Out).

    Core idea:
    - s1 is used for incoming elements.
    - s2 is used for outgoing/front elements.
    - When s2 is empty, we pour all elements from s1 into s2.
      This reverses their order, so the oldest pushed element comes on top of s2.

    Small dry run:
    push(10), push(20), push(30)
        s1 top -> 30, 20, 10
        s2 empty

    pop()
        s2 is empty, so move all s1 elements into s2:
        s2 top -> 10, 20, 30
        Now pop top of s2 = 10, which is the correct queue front.

    Complexity:
    - push: O(1)
    - pop: Amortized O(1), worst-case O(n) when transfer happens
    - peek: Amortized O(1), worst-case O(n) when transfer happens
    - empty: O(1)
    - Space: O(n), because all queue elements are stored across two stacks
*/
class MyQueue {
public:

    // s1 stores newly pushed elements.
    // Why needed: It lets push(x) stay O(1), because stack push is constant time.
    // If removed: We would have no place to store new elements before they are reordered.
    stack<int> s1;

    // s2 stores elements in queue-removal order.
    // Why needed: Its top represents the current queue front after elements are transferred from s1.
    // If removed: pop() and peek() could not return the oldest element efficiently using only one stack.
    stack<int> s2;

    // Constructor for initializing the queue object.
    // Here, no manual work is needed because both stacks are automatically empty when created.
    // If removed: Object creation like MyQueue q; would fail unless another constructor was available.
    MyQueue() {

    }

    // Adds a new element at the back/rear of the queue.
    // Queue behavior required: newer elements should leave after older elements.
    // We push into s1 because s1 acts as the "input stack".
    // Dry run:
    // push(10) -> s1: [10]
    // push(20) -> s1: [10, 20] where 20 is on top
    // The order looks reversed inside s1, but it will be fixed when moved to s2.
    // If this line is removed: The queue would never store the inserted value.
    // Edge case: Pushing into an empty queue works naturally.
    // Time: O(1), Space: O(1) extra for this operation.
    void push(int x) {
        s1.push(x);
    }

    // Removes and returns the front element of the queue.
    // Important assumption/missed edge case:
    // This code assumes pop() is called only when the queue is not empty.
    // If both s1 and s2 are empty, s2.top() would be invalid and may crash/produce undefined behavior.
    int pop() {

        // Move elements only if s2 is empty
        // Why only when s2 is empty?
        // Because if s2 already has elements, its top is already the correct queue front.
        // Moving again too early would mix newer elements before older ones and break FIFO order.
        //
        // Example:
        // push(1), push(2), pop()
        // After first transfer: s2 top is 1, then 2.
        // If we push(3), s1 has 3 while s2 still has 2.
        // Next pop must return 2, not 3, so we must NOT transfer s1 yet.
        //
        // If this if-block is removed:
        // s2 may be empty, and then s2.top() below would be invalid.
        if (s2.empty()) {

            // Transfer every element from s1 to s2.
            // What it does: Reverses the stack order.
            // Why necessary: Queue needs the oldest element first, while s1 has the newest element on top.
            //
            // Dry run:
            // s1 top -> 30, 20, 10
            // Move 30: s2 top -> 30
            // Move 20: s2 top -> 20, 30
            // Move 10: s2 top -> 10, 20, 30
            // Now 10, the oldest element, is on top and can be popped first.
            //
            // If this loop is removed:
            // Elements in s1 would never become available for pop()/peek().
            // Time: O(n) for this transfer, but each element moves from s1 to s2 at most once.
            while (!s1.empty()) {
                // Copy the current newest item from s1 onto s2.
                // This is one half of the "reverse the order" operation.
                // If removed: s1.pop() would delete values without saving them.
                s2.push(s1.top());

                // Remove the copied item from s1.
                // Why needed: Prevents duplicates and allows the loop to progress.
                // If removed: Infinite loop, because s1 would never become empty.
                s1.pop();
            }
        }

        // At this point, s2.top() is the queue front.
        // Why: Either s2 already had older elements, or we just transferred s1 into it.
        // If removed: We would lose the value after popping and could not return it.
        int ans = s2.top();

        // Remove the front element from the queue.
        // If removed: pop() would return the same front again and again, so queue state would be wrong.
        s2.pop();

        // Return the removed front element.
        // If removed: pop() would not give the caller the value they asked for.
        return ans;
    }

    // Returns the front element without removing it.
    // Same missed edge case as pop():
    // If peek() is called on an empty queue, s2.top() is invalid.
    int peek() {

        // If s2 is empty, there is no ready-to-read front element.
        // So we transfer from s1 to s2 to expose the oldest inserted value.
        // If removed: peek() after only push() calls would access an empty s2.
        if (s2.empty()) {

            // Same transfer logic as pop(), but we do not remove the answer afterward.
            // Dry run:
            // push(5), push(6)
            // s1 top -> 6, 5
            // transfer -> s2 top -> 5, 6
            // peek() returns 5, and both values remain in the queue.
            // Time: O(n) only when transfer happens; amortized O(1) overall.
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }

        // Return the current front without popping it.
        // If replaced with s1.top(), it would return the newest element, which is stack behavior, not queue behavior.
        return s2.top();
    }

    // Checks whether the queue has no elements.
    // Why both stacks?
    // Some elements may be waiting in s1, while older elements may be ready in s2.
    // The queue is empty only when BOTH are empty.
    //
    // Example:
    // push(1), push(2), pop()
    // s1 may be empty, but s2 may still contain 2.
    // So checking only s1.empty() would wrongly say the queue is empty.
    //
    // If removed: Caller cannot safely know whether pop()/peek() is valid.
    // Time: O(1), Space: O(1).
    bool empty() {
        return s1.empty() && s2.empty();
    }
};
int main() {
    
    return 0;
}

/*
    ### 1. 🧠 Problem Understanding

    - Type of problem:
      This is a data structure design problem. You are asked to simulate one data structure
      (Queue) using another data structure (Stack).

    - Queue rule:
      FIFO = First In, First Out.
      The element inserted earliest must be removed first.

    - Stack rule:
      LIFO = Last In, First Out.
      The element inserted latest is removed first.

    - Key constraint/clue:
      Because stacks reverse order, using one stack directly gives the wrong removal order.
      The clue is: "Implement Queue using Stacks" means we need to reverse the order somehow.

    - Edge cases:
      1. Empty queue: empty() handles it correctly.
      2. pop()/peek() on empty queue: this implementation does not guard against it.
      3. Multiple pushes before pop: handled by transferring s1 to s2.
      4. Push after some pops: handled because new values wait in s1 until s2 becomes empty.


    ### 2. 🔍 Pattern Recognition

    - Pattern used:
      Two-stack simulation / data structure transformation.

    - How to recognize it:
      If a problem asks you to implement FIFO behavior using LIFO tools, think:
      "Can I use one stack for input and another stack to reverse the order for output?"

    - Common signal:
      You need to process elements in the opposite order from how the available structure naturally gives them.


    ### 3. ⚡ Approach Breakdown (Interview Style)

    - Brute force idea:
      On every push, move elements around so that the front is always on top.
      This can make push O(n), while pop becomes O(1).

    - Better approach:
      Use two stacks:
      s1 for pushes, s2 for pops/peeks.
      Transfer only when s2 becomes empty.

    - Optimal approach:
      The current implementation.
      It avoids unnecessary movement. Each element is pushed into s1 once, moved to s2 once,
      and popped from s2 once. That is why operations are amortized O(1).


    ### 4. 🧩 Intuition Building

    Think of s1 as a pile where new people enter a line, but the order is backward.
    When it is time to serve and s2 is empty, we flip the whole pile into s2.
    That flip makes the oldest person come to the top.

    The trick:
    Do not flip every time. Flip only when needed.
    If s2 still has older elements, they must be served before anything newer in s1.


    ### 5. 🔁 How to Recall Later

    - Signal 1:
      "Queue using stack" means FIFO from LIFO, so think "reverse using another stack."

    - Signal 2:
      If new elements should wait behind older elements, keep them in an input stack.

    - Signal 3:
      If output stack has elements, never disturb it; its top is already the correct front.

    - Memory trick:
      "Push to inbox, pop from outbox; refill outbox only when empty."


    ### 6. ⚠️ Common Mistakes

    - Moving s1 to s2 on every pop even when s2 is not empty.
      This breaks FIFO order when new elements were pushed after a previous transfer.

    - Checking only one stack in empty().
      The queue can have elements in either s1 or s2.

    - Forgetting to pop from s1 during transfer.
      That causes an infinite loop.

    - Calling pop() or peek() when the queue is empty.
      This implementation does not protect against that case.

    - Thinking pop is always O(n).
      Worst-case pop can be O(n), but amortized over many operations it is O(1).


    ### 7. 📊 Complexity Analysis

    - push(x):
      Time O(1), because it only pushes into s1.
      Extra space O(1) per operation.

    - pop():
      Worst-case O(n), when s2 is empty and all elements must move from s1 to s2.
      Amortized O(1), because each element is transferred only once.

    - peek():
      Worst-case O(n), for the same transfer reason.
      Amortized O(1).

    - empty():
      Time O(1), because it only checks two stack states.

    - Total space:
      O(n), where n is the number of elements stored in the queue.


    ### 8. 🔄 Alternative Approaches

    - Costly push approach:
      Keep the front element always on top of one stack by rearranging elements during every push.
      Then pop is O(1), but push becomes O(n).

    - Recursive one-stack approach:
      Use recursion to reach the bottom of a stack for pop/peek.
      This simulates queue behavior but uses call stack space and is less clean.

    - Built-in queue:
      In real C++ work, use std::queue<int> if the interview specifically does not restrict you.
      Here, the purpose is to understand how queue behavior can be built from stack behavior.
*/
