#include <iostream>
// We need <vector> because the input array is represented as vector<int>.
// If this include is removed, vector<int> will not be recognized by the compiler.
#include <vector>
using namespace std;

class Solution {
public:
    /*
        Problem: Remove all occurrences of val from nums in-place.

        Important interview detail:
        - We do NOT need to physically erase elements from the vector.
        - We only need to move the elements we want to keep into the first k positions.
        - The function returns k, the count of valid elements after removal.

        Small dry run:
        nums = [3, 2, 2, 3], val = 3
        We want the front of nums to become [2, 2, _, _] and return 2.
    */
    int removeElement(vector<int>& nums, int val) {
        // n stores the original size of nums.
        // Why needed: the loop must scan every original element exactly once.
        // If removed: we would either need to call nums.size() directly in the loop
        // or we would not know how many elements to inspect.
        // Edge case: if nums is empty, n becomes 0 and the loop never runs.
        // Complexity impact: reading size is O(1), so this does not change total time.
        int n=nums.size();

        // count is the "write pointer".
        // It marks the next index where a value NOT equal to val should be placed.
        // It also becomes the final answer: the number of elements kept.
        // If removed: we would not know where to write the next valid element,
        // and we could not return the new logical length.
        //
        // Dry run idea:
        // nums = [3, 2, 2, 3], val = 3
        // count starts at 0 because no valid elements have been kept yet.
        //
        // Edge cases handled:
        // - All elements equal val: count stays 0.
        // - No elements equal val: count eventually becomes nums.size().
        // Space: this single integer is O(1) extra space.
        int count=0;

        // Scan every element from left to right using i as the "read pointer".
        // Why needed: every element must be checked to decide whether it should stay.
        // If this loop is removed: no removal/compaction work happens.
        //
        // Pattern:
        // - i reads from the original array.
        // - count writes only the elements we want to keep.
        //
        // Time complexity: O(n), because each element is visited once.
        for(int i=0;i<n;i++){
            // Keep only elements that are different from val.
            // Why needed: this is the actual filtering condition.
            // If removed: every element would be copied, including the value we are
            // supposed to remove.
            //
            // Dry run with nums = [3, 2, 2, 3], val = 3:
            // i = 0 -> nums[0] = 3, condition false, skip it.
            // i = 1 -> nums[1] = 2, condition true, keep it.
            // i = 2 -> nums[2] = 2, condition true, keep it.
            // i = 3 -> nums[3] = 3, condition false, skip it.
            //
            // Edge cases:
            // - Negative numbers work because comparison is value-based.
            // - Duplicates work because each element is checked independently.
            if(nums[i]!=val){
                // Move the valid element to the next available front position.
                // This compacts the array in-place.
                // Why needed: the first count positions must contain the kept values.
                // If removed: count might increase, but nums would not be rearranged,
                // so the returned length would not match the correct front segment.
                //
                // Dry run:
                // nums = [3, 2, 2, 3], val = 3
                // i = 1, count = 0 -> nums[0] = nums[1] -> [2, 2, 2, 3]
                // i = 2, count = 1 -> nums[1] = nums[2] -> [2, 2, 2, 3]
                //
                // Note:
                // Sometimes count == i, meaning the element is already in the right
                // place. The assignment is still safe and keeps the code simple.
                nums[count]=nums[i];

                // Move the write pointer forward after storing one valid element.
                // Why needed: the next kept element must go into the next index.
                // If removed: every valid element would overwrite nums[0], and the
                // final count would be wrong.
                //
                // Continuing dry run:
                // after keeping first 2, count becomes 1.
                // after keeping second 2, count becomes 2.
                count++;
            }
        }

        // count is the number of elements not equal to val.
        // The problem expects us to return this new logical length k.
        // If removed: the caller would not know how many front elements are valid.
        //
        // Final dry run result:
        // nums front segment = [2, 2], count = 2, return 2.
        //
        // Overall complexity:
        // Time: O(n), one pass over nums.
        // Space: O(1), only n, count, and i are used.
        return count;
    }
};


int main() {
    // Empty main is only here so this file can compile as a standalone C++ program.
    // The actual LeetCode-style solution is inside Solution::removeElement.
    
    return 0;
}

/*
### 1. Problem Understanding

Type of problem:
- This is an array in-place modification / filtering problem.
- We are asked to remove a target value from an array without using another array.

Key constraints/clues:
- "In-place" means modify nums directly.
- "Return k" means only the first k elements matter after the function finishes.
- The order of remaining elements is often allowed to change in this LeetCode problem,
  but this implementation keeps their relative order.
- Elements after index k - 1 do not matter.

### 2. Pattern Recognition

DSA pattern used:
- Two pointers, specifically read pointer + write pointer.

How to recognize it later:
- You need to keep some elements and discard others.
- You must do it inside the same array.
- The answer is the length of the compacted valid prefix.

### 3. Approach Breakdown (Interview Style)

Brute force idea:
- For every occurrence of val, erase it from the vector and shift later elements left.
- This is simple, but repeated shifting can make it O(n^2).

Better approach:
- Create a new vector and push only elements not equal to val.
- This is O(n) time but uses O(n) extra space, so it violates the in-place spirit.

Optimal approach:
- Use one pointer i to read every element.
- Use another pointer count to write only valid elements.
- This is chosen because it is O(n) time and O(1) extra space.

### 4. Intuition Building

Core idea:
- Think of the front part of nums as a "clean zone".
- Every time we find a number that should stay, we place it at the end of the clean zone.
- Values equal to val are simply ignored.

Trick/insight:
- We do not need to delete anything.
- We only need to overwrite the front of the array with the elements that survive.

### 5. How to Recall Later

Key signals:
- "Remove elements in-place"
- "Return the new length"
- "Remaining elements after k do not matter"

One-line memory trick:
- Read everything, write only what survives.

### 6. Common Mistakes

- Trying to actually erase elements while looping, which causes shifting and index bugs.
- Returning nums.size() instead of count.
- Incrementing count even when nums[i] == val.
- Thinking the whole vector must be cleaned; only the first count elements matter.
- Forgetting the empty array case, where the correct answer is 0.

### 7. Complexity Analysis

Time complexity:
- O(n), because each element is checked once.

Space complexity:
- O(1), because no extra array is created.
- Only a few integer variables are used.

### 8. Alternative Approaches

- Erase-based approach:
  Remove val using vector erase operations. Easy to understand, but inefficient because
  erasing from the middle shifts elements.

- Extra array approach:
  Store all non-val elements in another vector, then copy them back. Clear but not
  constant space.

- Two-end pointer approach:
  When nums[i] == val, replace it with the last unchecked element and reduce the
  effective array size. This can be faster when val appears often, but it does not
  preserve order.
*/
