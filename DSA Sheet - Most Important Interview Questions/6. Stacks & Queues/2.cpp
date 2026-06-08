#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

/*
Problem represented by this code:
- For every element in nums1, find its "next greater element" inside nums2.
- "Next greater" means the first number to the right of that element in nums2
  that is strictly greater than it.

Important assumption from the standard problem:
- nums1 is a subset of nums2.
- Values are unique in nums2.
  This matters because unordered_map<int, int> uses the value itself as the key.

Core example:
nums1 = [4, 1, 2]
nums2 = [1, 3, 4, 2]

Next greater values in nums2:
1 -> 3, because 3 is the first greater value to the right of 1.
3 -> 4, because 4 is the first greater value to the right of 3.
4 -> -1, because nothing greater exists to its right.
2 -> -1, because nothing exists to its right.

Answer for nums1:
4 -> -1
1 -> 3
2 -> -1
result = [-1, 3, -1]

High-level pattern:
- Use a monotonic decreasing stack while scanning nums2 from right to left.
- The stack stores possible "next greater" candidates for elements on the left.
*/
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        /*
        m stores the final lookup table:
        key   = an element from nums2
        value = that element's next greater element, or -1 if none exists.

        Why this is necessary:
        - We first solve the next greater question for every element in nums2.
        - Then each nums1 answer becomes a fast O(1) map lookup.

        What would break if removed:
        - We would have no saved relationship like 1 -> 3 or 4 -> -1.
        - For every nums1 value, we might need to search nums2 again, causing
          a slower brute force solution.

        Edge case handled:
        - If nums1 is empty, this map may still be built, but result remains empty.

        Space:
        - O(n), where n = nums2.size(), because one mapping is stored per nums2 value.
        */
        unordered_map<int, int> m; // map each number to its next greater element

        /*
        s is a monotonic decreasing stack.

        Meaning of the invariant:
        - While scanning from right to left, the stack keeps only useful elements
          that are greater candidates for future elements on the left.
        - Smaller or blocked values are removed before the current answer is chosen.

        Why a stack:
        - We only care about the nearest useful greater element to the right.
        - The top of the stack gives the closest valid candidate after removing
          smaller or equal values.

        What would break if removed:
        - We would lose the ability to skip useless right-side elements efficiently.
        - The solution would likely become O(n^2).

        Space:
        - O(n) in the worst case, for example nums2 = [4, 3, 2, 1].
        */
        stack<int> s;

        // Process nums2 from right to left
        /*
        We scan from right to left because "next greater" always lives on the right.

        At index i:
        - Everything already processed is to the right of nums2[i].
        - Therefore the stack contains candidates that could be the next greater
          element for nums2[i].

        Dry run with nums2 = [1, 3, 4, 2]:

        Start: stack = []

        i = 3, nums2[i] = 2
        - stack empty, so next greater of 2 is -1
        - push 2
        - stack top -> bottom: [2]

        i = 2, nums2[i] = 4
        - pop 2 because 2 <= 4
        - stack empty, so next greater of 4 is -1
        - push 4
        - stack: [4]

        i = 1, nums2[i] = 3
        - top 4 is greater than 3, so next greater of 3 is 4
        - push 3
        - stack: [3, 4]

        i = 0, nums2[i] = 1
        - top 3 is greater than 1, so next greater of 1 is 3
        - push 1
        - stack: [1, 3, 4]

        Final map:
        2 -> -1, 4 -> -1, 3 -> 4, 1 -> 3

        What would break if direction were left to right:
        - The right-side future values would not be known yet for the current element.
        - A left-to-right solution is possible, but it needs a different stack idea:
          keep unresolved previous elements and resolve them when a greater value appears.

        Time:
        - The for-loop visits each nums2 element once.
        */
        for (int i = nums2.size() - 1; i >= 0; i--) {
            /*
            Remove every element that cannot be the next greater element for nums2[i].

            Why pop while s.top() <= nums2[i]?
            - If s.top() is smaller than nums2[i], it is not greater, so it cannot answer.
            - If s.top() is equal to nums2[i], it is still not strictly greater.
            - Also, any smaller/equal value behind the current value becomes useless for
              future elements on the left, because nums2[i] is closer and at least as large.

            Small dry run:
            nums2 = [2, 1, 3]
            scanning right to left:
            - see 3: stack [], map[3] = -1, push 3
            - see 1: top 3 > 1, map[1] = 3, push 1; stack [1, 3]
            - see 2: top 1 <= 2, pop 1 because it cannot be next greater for 2
                     top 3 > 2, map[2] = 3

            What would break if this while-loop is removed:
            - A smaller element could incorrectly be treated as "next greater".
            - Example: nums2 = [2, 1, 3]
              Without popping 1, answer for 2 would become 1, which is wrong.

            Why while, not if:
            - Multiple smaller/equal elements may need removal.
            - Example: nums2 = [5, 1, 2, 3]
              For 5, several smaller elements may sit above the true answer or above empty.

            Edge cases handled:
            - Empty stack is checked before s.top(), preventing invalid access.
            - Equal values are popped, which matches "strictly greater".

            Complexity:
            - Although this loop is nested, each element is pushed once and popped at most once.
            - Total stack work across the whole for-loop is O(n), not O(n^2).
            */
            while (!s.empty() && s.top() <= nums2[i]) {
                s.pop();
            }

            // If stack is empty -> no greater element
            /*
            After removing useless candidates:
            - If the stack is empty, no greater element exists to the right.

            Why:
            - All right-side values were either absent or popped because they were
              smaller/equal and therefore not valid.

            What would break if this check is removed:
            - Accessing s.top() on an empty stack would be undefined behavior.

            Dry run:
            nums2 = [4, 2]
            - see 2: stack empty -> m[2] = -1
            - see 4: pop 2, stack empty -> m[4] = -1

            Edge case:
            - The last element of nums2 always gets -1 because nothing is to its right.
            */
            if (s.empty())
                m[nums2[i]] = -1;
            else
                /*
                If the stack is not empty, s.top() is the nearest useful greater value.

                Why s.top() is correct:
                - Smaller/equal elements have been removed.
                - Remaining top is the closest candidate among the useful right-side elements.

                What would break if we stored some other stack value:
                - We might choose a greater element that is farther away, not the next one.

                Dry run:
                nums2 = [1, 3, 4, 2]
                For nums2[i] = 3, stack top is 4, so m[3] = 4.
                */
                m[nums2[i]] = s.top();

            // Push current element into stack
            /*
            Push the current number so it can become a next greater candidate
            for elements further left.

            Why necessary:
            - Future iterations process elements to the left of nums2[i].
            - Those elements may need nums2[i] as their next greater answer.

            What would break if removed:
            - Current values would never be considered for earlier elements.
            - Example: nums2 = [1, 3]
              If 3 is not pushed, 1 would incorrectly get -1 instead of 3.

            Dry run continuation:
            nums2 = [1, 3, 4, 2]
            After mapping 3 -> 4, push 3 so it can answer 1 -> 3.

            Complexity:
            - Each nums2 element is pushed exactly once.
            */
            s.push(nums2[i]);
        }

        // Build answer for nums1
        /*
        result will store answers in the same order as nums1.

        Why a separate result vector:
        - nums1 asks only for selected elements from nums2.
        - The output must follow nums1 order, not nums2 order.

        Edge case:
        - If nums1 is empty, result stays empty and is returned.

        Space:
        - O(k), where k = nums1.size(), for the output vector.
        */
        vector<int> result;
        /*
        For each number requested in nums1, fetch its precomputed next greater value.

        Why this is efficient:
        - The expensive work was done once for nums2.
        - Each lookup is average O(1) using unordered_map.

        What would break if m[num] is not available:
        - In the standard problem, nums1 is guaranteed to be a subset of nums2.
        - If that guarantee is missing, m[num] would insert a default value 0,
          which would be wrong. A defensive version would use find().

        Dry run:
        nums1 = [4, 1, 2]
        map contains:
        4 -> -1
        1 -> 3
        2 -> -1
        result becomes [-1, 3, -1].

        Complexity:
        - O(k) average time, where k = nums1.size().
        */
        for (int num : nums1) {
            /*
            Append the answer for this nums1 value.

            Why push_back:
            - It preserves the same order as nums1.

            What would break if removed:
            - The returned result would miss this element's answer.
            */
            result.push_back(m[num]);
        }

        /*
        Return the completed answer vector.

        Complexity summary for the full function:
        Let n = nums2.size() and k = nums1.size().
        - Build map using monotonic stack: O(n)
        - Build result using map lookups: O(k)
        - Total time: O(n + k)
        - Extra space: O(n + k), counting map, stack, and output.
        */
        return result;
    }
};

int main() {
    /*
    Empty main function.

    Why it exists:
    - It allows this file to compile as a standalone C++ program.
    - Online judges usually call Solution::nextGreaterElement directly and do not
      require custom main logic.

    What would break if removed:
    - In a normal local compile as an executable, the linker may fail because it
      cannot find the program entry point.
    */
    
    return 0;
}

/*
### 1. 🧠 Problem Understanding

This is an array query problem using a stack.

For each value in nums1, we must find the first strictly greater value appearing
to its right in nums2.

Key constraints/clues:
- nums1 is usually a subset of nums2.
- nums2 values are usually unique.
- "Next greater" means nearest greater value on the right, not just any greater value.
- The phrase "to the right" suggests direction matters.
- The need to repeatedly find a nearby greater value suggests a stack can help.

### 2. 🔍 Pattern Recognition

Pattern used:
- Monotonic stack.

More specifically:
- Scan from right to left.
- Maintain a decreasing stack of useful candidates.
- Pop elements that are smaller or equal because they cannot be the next greater answer.

How to recognize this pattern later:
- The problem asks for "next greater", "next smaller", "previous greater", or
  "previous smaller".
- You need nearest greater/smaller element, not sorted order.
- Brute force compares each element with many elements on one side.
- You can discard elements permanently once they become useless.

### 3. ⚡ Approach Breakdown (Interview Style)

Brute force idea:
- For each num in nums1, find its index in nums2.
- Scan to the right until a greater element is found.
- If none is found, answer is -1.
- Time can be O(k * n), or O(n^2)-like in the worst case.

Better approach:
- Precompute the next greater answer for every element in nums2.
- Then answer nums1 queries using a hash map.

Optimal approach:
- Use a monotonic stack to compute all next greater values in O(n).
- Use unordered_map to answer each nums1 query in average O(1).
- Chosen because each element is pushed once and popped once, avoiding repeated scans.

### 4. 🧩 Intuition Building

Think of scanning nums2 from right to left.
For the current number, only numbers on its right can be answers.

But not all right-side numbers are useful:
- If a number is smaller than the current number, it cannot be the current answer.
- It also cannot help earlier elements if the current number is closer and bigger.

The trick:
- Keep only useful candidates in a stack.
- Before answering current element, remove all candidates that are too small.
- The stack top then becomes the nearest greater candidate.

### 5. 🔁 How to Recall Later

Key signals:
- "Next greater element"
- "First greater value to the right"
- Need answers for many elements from another array

One-line memory trick:
"For next greater on the right, scan right to left and pop smaller blockers."

### 6. ⚠️ Common Mistakes

- Using < instead of <= in the pop condition when the problem requires strictly greater.
- Forgetting to check s.empty() before calling s.top().
- Thinking the nested while-loop makes the algorithm O(n^2).
- Forgetting that each element is popped at most once.
- Returning answers in nums2 order instead of nums1 order.
- Using m[num] when nums1 may contain values not present in nums2.
- Assuming this works with duplicate nums2 values without modification.

### 7. 📊 Complexity Analysis

Let:
- n = nums2.size()
- k = nums1.size()

Time:
- Each nums2 element is pushed once: O(n).
- Each nums2 element is popped at most once: O(n).
- Each nums1 lookup is average O(1), so all lookups cost O(k).
- Total time: O(n + k).

Space:
- unordered_map stores up to n answers: O(n).
- stack stores up to n elements in the worst case: O(n).
- result stores k answers: O(k).
- Total extra space: O(n + k), or O(n) auxiliary space if output is not counted.

### 8. 🔄 Alternative Approaches

1. Brute force:
For each nums1 element, locate it in nums2, then scan right until a greater
element appears. Simple but slow for large inputs.

2. Left-to-right monotonic stack:
Scan nums2 from left to right and keep unresolved elements in a decreasing stack.
When the current value is greater than the stack top, it resolves that previous
value's answer. This is also O(n), but the mental model is "resolve old elements"
instead of "query right-side candidates".

3. Precompute index map plus brute scan:
Use a map to find each nums1 element's index in nums2 quickly, then scan right.
This improves finding the start position but still has slow repeated right scans.
*/
