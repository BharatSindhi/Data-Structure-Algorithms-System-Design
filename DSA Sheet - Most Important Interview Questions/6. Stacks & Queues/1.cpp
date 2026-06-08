#include <iostream>
#include <queue>
using namespace std;

// Problem: Implement a Stack (LIFO: Last In, First Out) using only Queue operations.
// Important idea:
// - A normal queue is FIFO: the first inserted element comes out first.
// - A stack is LIFO: the last inserted element comes out first.
// - This code forces q1.front() to always store the current stack top.
// - Because of that invariant, pop() and top() become simple O(1) operations.
class MyStack {
public:
   // q1 is the "main" queue.
   // Invariant after every push:
   // q1.front() is the newest pushed element, so it behaves like stack top.
   //
   // Example stack from top to bottom: [3, 2, 1]
   // q1 front to back will also be:   [3, 2, 1]
   //
   // If q1 did not maintain this order, top() and pop() would return the wrong element.
   queue<int> q1;

   // q2 is a temporary helper queue used only during push().
   // Why needed?
   // - C++ queue lets us insert at the back and remove from the front.
   // - To put a new element at the front of q1, we first move old elements away.
   //
   // Space note:
   // - q2 may temporarily hold all existing elements, so extra space is O(n).
   queue<int> q2;

    // Constructor initializes an empty stack.
    // q1 and q2 are already empty by default because they are queue objects.
    // Removing this constructor would still work here, because no custom setup is needed.
    MyStack() {
        
    }
    
    void push(int x) {
        // Goal of push(x):
        // Make x the first element of q1 so that q1.front() becomes the stack top.
        //
        // Dry run before push(3):
        // Current logical stack top -> bottom: [2, 1]
        // q1 front -> back:                  [2, 1]
        // q2:                                []

        // Step 1: Move every old element from q1 into q2.
        // This temporarily empties q1 so the new element can be inserted first.
        //
        // Dry run:
        // Move 2: q1 = [1], q2 = [2]
        // Move 1: q1 = [],  q2 = [2, 1]
        //
        // Why necessary?
        // If we directly did q1.push(x), q1 would become [2, 1, 3],
        // and q1.front() would still be 2, not the newly pushed 3.
        //
        // What breaks if removed?
        // The data structure would behave like a queue, not a stack.
        //
        // Edge case:
        // If q1 is empty, this loop simply does nothing, which correctly handles
        // pushing the first element.
        while(!q1.empty()){
            // Read the oldest/front element of q1 before removing it.
            // Without front(), we would not know which value to preserve.
            q2.push(q1.front());

            // Remove that value from q1 after copying it to q2.
            // Without pop(), the loop would never end because q1 would stay non-empty.
            q1.pop();
        }

        // Step 2: Insert the new value into empty q1.
        //
        // Dry run:
        // q1 = [3], q2 = [2, 1]
        //
        // Why necessary?
        // This places the newest element at q1.front(), making it the stack top.
        //
        // What breaks if removed?
        // The pushed value would be lost completely.
        q1.push(x);

        // Step 3: Move all old elements back behind the new element.
        //
        // Dry run:
        // Move 2: q1 = [3, 2], q2 = [1]
        // Move 1: q1 = [3, 2, 1], q2 = []
        //
        // Now q1.front() is 3, which matches stack behavior.
        //
        // What breaks if removed?
        // All previous stack elements would remain in q2 and become unreachable
        // by pop(), top(), and empty(), because those methods only use q1.
        while(!q2.empty()){
            // Preserve the old elements in their existing order behind x.
            q1.push(q2.front());

            // Remove each transferred element from q2 so the helper queue becomes empty.
            // If removed, this loop would be infinite.
            q2.pop();
        }

        // Complexity of push:
        // If there are n elements already in the stack:
        // - First loop moves n elements from q1 to q2.
        // - Second loop moves n elements from q2 back to q1.
        // Time: O(n)
        // Extra Space: O(n) temporarily in q2.
    }
    
    int pop() {
        // Because push() keeps the newest element at q1.front(),
        // popping a stack is the same as removing q1.front().
        //
        // Dry run with q1 = [3, 2, 1]:
        // ans = 3
        // q1 after pop = [2, 1]
        // return 3
        //
        // Why store in ans?
        // Once q1.pop() is called, the front element is removed and cannot be accessed.
        //
        // Edge case missed:
        // If pop() is called on an empty stack, q1.front() is invalid behavior.
        // Online judges like LeetCode usually guarantee pop() is called only when non-empty.
        int ans=q1.front();

        // Remove the current top from the stack.
        // If this line is removed, pop() would return the top but not actually delete it.
        q1.pop();

        // Return the removed stack top.
        return ans;

        // Complexity:
        // Time: O(1), because the top is already at q1.front().
        // Space: O(1), only one integer variable is used.
    }
    
    int top() {
        // Return the current stack top without removing it.
        //
        // Dry run with q1 = [3, 2, 1]:
        // q1.front() is 3, so top() returns 3.
        // q1 remains [3, 2, 1].
        //
        // What breaks if push() did not reorder elements?
        // q1.front() would be the oldest element, not the newest.
        //
        // Edge case missed:
        // Calling top() on an empty stack is invalid.
        //
        // Complexity:
        // Time: O(1)
        // Space: O(1)
        return q1.front();
    }
    
    bool empty() {
        // The real stack contents are always stored in q1 after each operation.
        // q2 is only temporary and should be empty outside push().
        //
        // Therefore, checking q1.empty() is enough.
        //
        // Dry run:
        // q1 = []        -> empty() returns true
        // q1 = [2, 1]    -> empty() returns false
        //
        // What breaks if we checked q2 instead?
        // q2 is normally empty, so the stack would look empty even when q1 has data.
        //
        // Complexity:
        // Time: O(1)
        // Space: O(1)
        return q1.empty();
    }
};


int main() {
    // Create a MyStack object dynamically.
    // This is similar to how many online judges instantiate the class.
    MyStack* obj = new MyStack();

    // Push 1 onto the stack.
    // Current stack: [1]
    obj->push(1);

    // top() returns 1 without removing it.
    // Current stack is still: [1]
    int param_3 = obj->top();

    // pop() returns 1 and removes it.
    // Current stack becomes: []
    int param_2 = obj->pop();

    // empty() returns true because the stack has no elements now.
    bool param_4 = obj->empty();

    // Free the dynamically allocated object.
    // If this line is removed in a larger program, it may cause a memory leak.
    delete obj;

    // End the program successfully.
    return 0;
}

/*
### 1. 🧠 Problem Understanding

This is a stack-design problem: implement stack operations using queue data structures.

Stack behavior:
- push(x): add x to the top
- pop(): remove and return the top
- top(): return the top without removing
- empty(): check if stack has no elements

Key clue:
- A stack needs LIFO order.
- A queue naturally gives FIFO order.
- So the main challenge is reversing or rearranging queue order to simulate stack behavior.

Constraint usually assumed in this problem:
- Only queue operations should be used: push to back, pop from front, front, empty, size.
- pop() and top() are usually called only when the stack is non-empty.

### 2. 🔍 Pattern Recognition

Pattern used: Data structure simulation / stack using queues.

How to recognize it:
- The problem asks to implement one data structure using another.
- The main issue is a mismatch in removal order:
  stack = newest first, queue = oldest first.
- You need to maintain an invariant that makes future operations easy.

Here, the invariant is:
q1.front() is always the current stack top.

### 3. ⚡ Approach Breakdown (Interview Style)

Brute force idea:
- Store elements in a queue normally.
- During pop(), rotate the queue until the last pushed element comes to the front.
- This makes push() cheap but pop() expensive.

Better approach:
- Use two queues.
- During push(), move old elements away, insert the new element first, then move old elements back.
- This makes q1.front() always the stack top.

Optimal approach chosen here:
- Costly push, cheap pop/top.
- push(): O(n)
- pop(): O(1)
- top(): O(1)
- empty(): O(1)

Why choose this?
- It makes top() and pop() very simple because the newest element is always ready at the front.

### 4. 🧩 Intuition Building

Think of q1 as a line where only the front person can leave.
But a stack needs the newest person to leave first.

So whenever a new person arrives, we rebuild the line:
1. Move everyone aside into q2.
2. Put the new person first in q1.
3. Put everyone else behind them again.

The trick:
Do the reordering at push time so that pop and top become easy later.

### 5. 🔁 How to Recall Later

Key signals:
- "Implement Stack using Queues"
- LIFO needs to be simulated using FIFO
- Need newest element at the front of a queue

Memory trick:
"New stack top must become queue front."

### 6. ⚠️ Common Mistakes

- Directly pushing into q1 and expecting stack behavior.
- Forgetting to move old elements back from q2 to q1.
- Checking q2.empty() instead of q1.empty().
- Calling front() on an empty queue.
- Thinking push is O(1), even though it moves all existing elements twice.

### 7. 📊 Complexity Analysis

Let n be the number of elements currently in the stack.

push(x):
- Moves n elements from q1 to q2.
- Pushes x into q1.
- Moves n elements back from q2 to q1.
- Time: O(n)
- Extra Space: O(n)

pop():
- Removes q1.front().
- Time: O(1)
- Extra Space: O(1)

top():
- Reads q1.front().
- Time: O(1)
- Extra Space: O(1)

empty():
- Checks q1.empty().
- Time: O(1)
- Extra Space: O(1)

### 8. 🔄 Alternative Approaches

1. Costly pop approach:
Push elements normally into one queue.
When pop() is called, rotate the first n - 1 elements to the back.
The last remaining front element is the stack top, so remove it.
This gives push O(1), pop O(n), top may also need extra handling.

2. One queue approach:
Push x into the queue, then rotate all previous elements behind it.
Example:
Before push(3): [2, 1]
After push 3:   [2, 1, 3]
Rotate old two: [3, 2, 1]
This also makes q.front() the stack top, but uses only one queue.

3. Use an actual stack:
This is the natural solution in real projects, but it does not satisfy the interview constraint
when the problem specifically asks for queues.
*/
