#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Solution {
  public:
    queue<int> reverseFirstK(queue<int> q, int k) {
        // Goal: reverse only the first k elements of the queue, while keeping
        // the remaining n-k elements in their original relative order.
        //
        // Example dry run:
        // q = [1, 2, 3, 4, 5], k = 3
        // Expected answer = [3, 2, 1, 4, 5]
        //
        // Why pass queue by value?
        // This function receives a copy of the queue, modifies that copy, and
        // returns it. The original caller's queue is not changed directly.

        // Store the original queue size before we start popping elements.
        // What it does: n becomes the total number of elements in q.
        // Why needed: after popping the first k elements, q.size() changes, so
        // we need the original size to know how many elements should remain
        // behind the reversed part.
        // If removed: we would not know how many non-reversed elements must be
        // rotated back to the rear later.
        // Dry run: q = [1,2,3,4,5], so n = 5.
        // Edge case: if q is empty, n = 0. This code assumes k is valid; if
        // k > n, q.front() later would be invalid.
        int n=q.size();

        // Calculate how many elements should NOT be reversed.
        // What it does: remaing = number of elements after the first k.
        // Why needed: after we push the reversed first k elements to the back,
        // the untouched elements are temporarily at the front. We rotate exactly
        // this many elements to the back so the reversed block comes first.
        // If removed: the final queue order would be wrong; for example after
        // reversing first 3 in [1,2,3,4,5], we would get [4,5,3,2,1] instead of
        // [3,2,1,4,5].
        // Dry run: n = 5, k = 3, so remaing = 2 for elements [4,5].
        // Edge cases:
        // - k == n: remaing = 0, no rotation needed.
        // - k == 0: remaing = n, but the first while(k--) becomes dangerous
        //   because k-- with k = 0 evaluates to 0 first, so it does not enter;
        //   rotation then cycles the whole queue and returns the same order.
        // - k > n: remaing becomes negative and popping too many elements breaks.
        int remaing =n-k;
        
        // Stack is used because it reverses order by LIFO behavior.
        // What it does: st will temporarily hold the first k queue elements.
        // Why needed: queue is FIFO, so it cannot directly reverse its front
        // elements. Stack gives us Last-In-First-Out order.
        // If removed: we would need another way, such as recursion or deque, to
        // reverse the first k elements.
        // Dry run after pushing 1,2,3: stack top is 3, then 2, then 1.
        // Space complexity: stack stores k elements, so O(k) extra space.
        stack<int>st;
        
        // Move the first k queue elements into the stack.
        // What it does:
        // - q.front() reads the current front element.
        // - st.push(...) saves it in the stack.
        // - q.pop() removes it from the queue.
        // - k-- decreases k after each iteration.
        // Why needed: extracting exactly the first k elements separates the
        // portion we want to reverse from the untouched suffix.
        // If removed: nothing would be reversed because the stack would stay
        // empty.
        // Dry run:
        // start q = [1,2,3,4,5], k = 3
        // iteration 1: push 1, q = [2,3,4,5], stack = [1]
        // iteration 2: push 2, q = [3,4,5], stack top sequence = 2,1
        // iteration 3: push 3, q = [4,5], stack top sequence = 3,2,1
        // Edge case missed: if k is greater than q.size(), q.front() is called
        // on an empty queue, which is undefined behavior.
        // Time cost: this loop runs k times, so O(k).
        while(k--){
            st.push(q.front());
            q.pop();
        }
        
        // Pop from stack and append back to queue.
        // What it does: because stack pops last inserted first, the original
        // first k elements are appended in reversed order.
        // Why needed: this is the actual reversal step.
        // If removed: the first k elements would be lost from the queue.
        // Dry run:
        // before loop: q = [4,5], stack top sequence = 3,2,1
        // pop 3 -> q = [4,5,3]
        // pop 2 -> q = [4,5,3,2]
        // pop 1 -> q = [4,5,3,2,1]
        // Notice the queue is not final yet; [4,5] must be rotated behind
        // [3,2,1].
        // Time cost: this loop runs k times, so O(k).
        while(!st.empty()){
            q.push(st.top());
            st.pop();
        }

        // Rotate the remaining original n-k elements to the back.
        // What it does: moves the front element to the rear exactly remaing
        // times.
        // Why needed: after the stack step, the untouched suffix [4,5] is still
        // at the front, giving [4,5,3,2,1]. Rotating it produces
        // [3,2,1,4,5].
        // If removed: the reversed block would appear after the untouched
        // elements, which violates the problem requirement.
        // Dry run:
        // before loop: q = [4,5,3,2,1], remaing = 2
        // iteration 1: move 4 to back -> [5,3,2,1,4]
        // iteration 2: move 5 to back -> [3,2,1,4,5]
        // Edge cases:
        // - remaing = 0: no rotation; full queue reversed.
        // - remaing < 0 when k > n: in C++, non-zero negative values are true,
        //   so this can become an infinite loop while also accessing invalid
        //   queue state earlier. Valid input must guarantee 0 <= k <= n.
        // Time cost: this loop runs n-k times, so O(n-k).
        while(remaing){
            q.push(q.front());
            q.pop();
        }

        // Return the transformed queue.
        // What it does: gives the caller the queue with first k elements reversed.
        // Why needed: q is local to this function because it was passed by value.
        // If removed: the function would not return the computed answer.
        // Dry run result: [3,2,1,4,5].
        // Overall complexity:
        // - Time: O(k) + O(k) + O(n-k) = O(n+k), which simplifies to O(n)
        //   because k <= n for valid inputs.
        // - Extra space: O(k) for the stack.
        return q;
    }
};
int main() {

    return 0;
}

/*
### 1. Problem Understanding

What type of problem is this?
- This is a queue transformation problem.
- We are asked to reverse only a prefix of the queue, not the entire queue.

Key constraints/clues:
- Queue allows access only from the front for removal and the back for insertion.
- Reversing order suggests a stack because stack naturally gives LIFO order.
- The suffix after the first k elements must keep its original order.
- Valid input should satisfy 0 <= k <= queue size. This code depends on that.

### 2. Pattern Recognition

DSA pattern used:
- Stack + Queue simulation.
- Use an auxiliary stack to reverse a fixed number of front elements.
- Use queue rotation to restore the untouched suffix position.

How to recognize this pattern later:
- The problem says "reverse first k elements" or "reverse a part of a queue".
- You need to reverse order, but the data structure is FIFO.
- You are allowed to use extra space.
- You need partial reversal plus preservation of remaining order.

### 3. Approach Breakdown (Interview Style)

Brute force idea:
- Copy all queue elements into an array/vector.
- Reverse the first k positions.
- Rebuild the queue.
- Time: O(n), Space: O(n).

Better approach:
- Use a stack only for the first k elements.
- This avoids storing the entire queue separately.
- Time: O(n), Space: O(k).

Optimal approach chosen here:
- Push first k queue elements into a stack.
- Pop stack elements back into the queue, giving reversed order.
- Rotate the remaining n-k elements to the back.
- This is optimal for queue operations because every relevant element is moved a
  constant number of times.

### 4. Intuition Building

Core idea:
- A queue remembers arrival order: first in, first out.
- A stack reverses order: last in, first out.
- So, if we temporarily put the first k queue elements into a stack, they come
  back reversed.

The trick:
- After appending reversed elements, they are at the back of the queue.
- The untouched elements are still at the front.
- Rotate the untouched elements to the back so the reversed k elements become
  the new front.

Example:
- Start: [1,2,3,4,5], k = 3
- Stack first k: stack top is 3,2,1 and queue is [4,5]
- Push stack back: [4,5,3,2,1]
- Rotate remaining 2 elements: [3,2,1,4,5]

### 5. How to Recall Later

Key signals:
- "Reverse first k elements of a queue"
- "Preserve order of remaining elements"
- "Queue cannot reverse directly"

One-line memory trick:
- "Stack reverses the first k, queue rotation fixes their position."

### 6. Common Mistakes

- Forgetting to rotate the remaining n-k elements.
- Using q.size() after popping, then losing the original size.
- Not handling invalid k values such as k > n.
- Thinking stack reversal alone gives the final answer; it only gives
  [remaining elements][reversed k elements], so rotation is still required.
- Off-by-one errors while processing exactly k elements.

### 7. Complexity Analysis

Time Complexity:
- First loop pushes k elements into the stack: O(k).
- Second loop pops k elements back into the queue: O(k).
- Third loop rotates n-k elements: O(n-k).
- Total = O(k + k + n-k) = O(n+k), which is O(n) when k <= n.

Space Complexity:
- The stack stores exactly k elements.
- Extra space = O(k).
- The queue itself is input/output storage and is not counted as extra
  auxiliary space.

### 8. Alternative Approaches

1. Array/vector approach:
- Move all queue elements into a vector.
- Reverse the first k elements using reverse().
- Push everything back into a queue.
- Simple to understand, but uses O(n) extra space.

2. Recursion approach:
- Recursively pop k elements from the queue and push them back while unwinding.
- This can reverse the first k elements without an explicit stack, but recursion
  still uses O(k) call stack space.

3. Deque approach:
- A deque allows insertion/removal at both ends.
- You could manipulate the first k elements more flexibly, but if the problem
  specifically asks for queue operations, stack + queue is the expected pattern.
*/
