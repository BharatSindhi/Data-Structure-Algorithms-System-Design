#include <iostream>
// Includes input/output utilities.
// This file does not currently print anything, but <iostream> is often kept
// for local testing with cout/cin inside main().
// If removed from this exact file, the pivotIndex logic still works because no
// iostream object is used; local print-based debugging would need it.
// Runtime complexity impact: none.
#include <vector>
// Includes the vector container used by vector<int>& nums.
// If removed, the compiler will not understand vector<int>.
// Why this matters for the problem: the input is an indexed list of numbers,
// and vector gives O(1) access to nums[i].
// Runtime complexity impact: none by itself.
using namespace std;
// Lets us write vector instead of std::vector.
// If removed, the code would need std::vector<int>& nums.
// This does not change the algorithm, only the naming convenience.

class Solution {
// LeetCode expects a class named Solution.
// If this class wrapper is removed or renamed, LeetCode's judge will not find
// the method in the expected format.
public:
    int pivotIndex(vector<int>& nums) {
        // Goal:
        // Find the first index i where:
        // sum of elements before i == sum of elements after i
        //
        // Example:
        // nums = {1, 7, 3, 6, 5, 6}
        // At index 3, value = 6
        // left side  = 1 + 7 + 3 = 11
        // right side = 5 + 6 = 11
        // So pivot index = 3.
        //
        // Pattern:
        // This is a Prefix Sum problem.
        // Instead of recomputing left and right sums for every index, we keep
        // a running leftSum and derive rightSum from totalSum.
        //
        // Function complexity:
        // Time: O(n), because we scan the array twice.
        // Space: O(1), because we only store a few integers.

        int totalSum = 0;
        // totalSum stores the sum of the entire array.
        //
        // Why necessary:
        // To know the right-side sum at index i without looping again, we use:
        // rightSum = totalSum - leftSum - nums[i]
        //
        // What breaks if removed:
        // We would either be unable to calculate rightSum efficiently, or we
        // would need a nested loop / suffix array.
        //
        // Dry run setup:
        // nums = {1, 7, 3, 6, 5, 6}
        // After the first loop, totalSum should become 28.
        //
        // Edge case:
        // For nums = {2, 1, -1}, totalSum = 2.
        // Negative numbers are handled naturally because sums can increase or decrease.

        // Step 1: Find total sum
        for(int num : nums){
            // Visit every element once and add it to totalSum.
            //
            // Why necessary:
            // We need the full array sum before testing any pivot, because each
            // rightSum depends on the full total.
            //
            // What breaks if this loop is removed:
            // totalSum remains 0, so rightSum calculations become wrong.
            // Example: nums = {1, 7, 3, 6, 5, 6}
            // At i = 3, rightSum would be 0 - 11 - 6 = -17 instead of 11.
            //
            // Dry run:
            // Start totalSum = 0
            // add 1  -> totalSum = 1
            // add 7  -> totalSum = 8
            // add 3  -> totalSum = 11
            // add 6  -> totalSum = 17
            // add 5  -> totalSum = 22
            // add 6  -> totalSum = 28
            //
            // Edge cases handled:
            // - Empty vector: loop runs zero times and totalSum stays 0.
            // - All negative values: totalSum correctly becomes negative.
            // - Mixed positive/negative: normal integer addition still works.
            totalSum += num;
            // Add the current number into the total.
            //
            // If removed:
            // totalSum never changes, so every rightSum is based on the wrong total.
        }

        int leftSum = 0;
        // leftSum stores the sum of all elements strictly to the left of the
        // current index i.
        //
        // Why it starts at 0:
        // At index 0, there are no elements on the left, so leftSum must be 0.
        //
        // What breaks if initialized incorrectly:
        // If leftSum starts with nums[0], index 0 would incorrectly count itself
        // as part of the left side.
        //
        // Dry run:
        // nums = {1, 7, 3, 6, 5, 6}
        // before i = 0, leftSum = 0
        // before i = 1, leftSum = 1
        // before i = 2, leftSum = 8
        // before i = 3, leftSum = 11
        //
        // Edge case:
        // A pivot at index 0 is handled because leftSum correctly starts as 0.

        // Step 2: Traverse array
        for(int i = 0; i < nums.size(); i++){
            // Try each index as a possible pivot, from left to right.
            //
            // Why left to right:
            // The problem asks for the leftmost pivot index. Returning as soon
            // as we find a match gives the smallest valid index.
            //
            // What breaks if this loop is removed:
            // No index is checked, so the function could never find a pivot.
            //
            // Dry run for nums = {1, 7, 3, 6, 5, 6}:
            // i = 0 -> test value 1
            // i = 1 -> test value 7
            // i = 2 -> test value 3
            // i = 3 -> test value 6, pivot found
            //
            // Edge cases handled:
            // - Single element: left sum = 0 and right sum = 0, so index 0 is returned.
            // - Pivot at the last index: right sum becomes 0 and can match leftSum.

            int rightSum = totalSum - leftSum - nums[i];
            // Calculate the sum of all elements strictly to the right of i.
            //
            // Formula:
            // totalSum = leftSum + nums[i] + rightSum
            // So:
            // rightSum = totalSum - leftSum - nums[i]
            //
            // Why necessary:
            // It avoids recomputing the right side with another loop.
            // This is the main optimization.
            //
            // What breaks if nums[i] is not subtracted:
            // The pivot element would be counted as part of the right side,
            // which violates the definition of pivot index.
            //
            // Dry run:
            // nums = {1, 7, 3, 6, 5, 6}, totalSum = 28
            // i = 0: leftSum = 0,  rightSum = 28 - 0  - 1 = 27
            // i = 1: leftSum = 1,  rightSum = 28 - 1  - 7 = 20
            // i = 2: leftSum = 8,  rightSum = 28 - 8  - 3 = 17
            // i = 3: leftSum = 11, rightSum = 28 - 11 - 6 = 11
            //
            // Edge case:
            // At the last index, rightSum becomes 0 because there are no elements
            // to the right.

            // Check pivot condition
            if(leftSum == rightSum){
                // If both sides are equal, the current index is a pivot index.
                //
                // Why necessary:
                // This is the exact condition the problem asks us to find.
                //
                // Why return immediately:
                // Since we scan from left to right, the first valid pivot is the
                // leftmost pivot.
                //
                // What breaks if removed:
                // The algorithm would never report a valid pivot and would always
                // continue until returning -1.
                //
                // Dry run:
                // At i = 3 for {1, 7, 3, 6, 5, 6}:
                // leftSum = 11 and rightSum = 11
                // condition is true, so return 3.
                //
                // Edge cases handled:
                // - nums = {0}: leftSum = 0, rightSum = 0, return 0.
                // - nums = {2, 1, -1}: at i = 0, leftSum = 0, rightSum = 0, return 0.
                return i;
                // Return the current index because it satisfies the pivot condition.
                //
                // If this return is removed:
                // The code might continue and miss the required leftmost pivot.
            }

            // Update left sum
            leftSum += nums[i];
            // Move nums[i] from the "current pivot element" into the left side
            // before checking the next index.
            //
            // Why necessary:
            // When i increases by 1, the old nums[i] becomes part of the left side.
            //
            // What breaks if removed:
            // leftSum would stay 0 forever, so only pivots with left sum 0 would
            // have a chance to be detected.
            //
            // Dry run:
            // nums = {1, 7, 3, 6, 5, 6}
            // after i = 0: leftSum = 0 + 1 = 1
            // after i = 1: leftSum = 1 + 7 = 8
            // after i = 2: leftSum = 8 + 3 = 11
            // before i = 3, leftSum is correctly 11.
            //
            // Edge case:
            // Negative values are handled correctly because adding a negative
            // decreases leftSum, which is exactly what the math requires.
        }

        return -1;
        // If no index made leftSum equal rightSum, there is no pivot index.
        //
        // Why necessary:
        // The problem requires returning -1 when no pivot exists.
        //
        // What breaks if removed:
        // A non-void function may fail to return a value on some paths, causing
        // compilation warnings and undefined behavior.
        //
        // Dry run with no pivot:
        // nums = {1, 2, 3}
        // totalSum = 6
        // i = 0: leftSum = 0, rightSum = 5
        // i = 1: leftSum = 1, rightSum = 3
        // i = 2: leftSum = 3, rightSum = 0
        // no match, return -1.
    }
};

int main() {
    // Empty main for local compilation.
    // LeetCode does not use this main(); it creates Solution internally and
    // calls pivotIndex() with hidden test cases.
    //
    // If removed in a normal local C++ program, linking may fail because the
    // program needs an entry point. On LeetCode, main is not required.
    
    return 0;
    // Signals successful local program termination.
    // This does not affect the LeetCode solution method.
}

/*
### 1. 🧠 Problem Understanding

* This is an array balance / prefix sum problem.
* We need an index where the sum on the left equals the sum on the right.
* The pivot element itself is excluded from both sums.
* The answer must be the leftmost valid pivot index.
* Key constraints/clues:
  * We only need sums, not the actual subarrays.
  * The phrase "left sum equals right sum" strongly hints at prefix sums.
  * Negative numbers may exist, so two-pointer or sorting ideas are not appropriate.

### 2. 🔍 Pattern Recognition

* DSA pattern used: Prefix Sum / Running Sum.
* Future recognition signals:
  * The problem asks about sums to the left/right of each index.
  * Recomputing each side from scratch would repeat work.
  * A running value can summarize everything before the current index.
* Here, totalSum gives the whole array, and leftSum gives the prefix before i.
  From those two values, rightSum can be calculated instantly.

### 3. ⚡ Approach Breakdown (Interview Style)

* Brute force idea:
  * For every index i, loop left to calculate left sum.
  * Loop right to calculate right sum.
  * Compare them.
  * Time: O(n^2), because every index may scan many elements again.

* Better approach:
  * Build prefix and suffix arrays.
  * prefix[i] can store sum before or up to i.
  * suffix[i] can store sum after or from i.
  * Then compare left and right sums for every index.
  * Time: O(n), Space: O(n).

* Optimal approach:
  * First compute totalSum.
  * Walk through the array while maintaining leftSum.
  * For each index, calculate rightSum = totalSum - leftSum - nums[i].
  * If leftSum == rightSum, return i.
  * Time: O(n), Space: O(1).
  * This is chosen because it avoids extra arrays and avoids repeated summing.

### 4. 🧩 Intuition Building

* Imagine the whole array sum as one pile.
* At each index, split the pile into three parts:
  * everything on the left,
  * the current number,
  * everything on the right.
* If left and right are equal, the current index balances the array.
* The trick is this equation:
  * totalSum = leftSum + nums[i] + rightSum
  * rightSum = totalSum - leftSum - nums[i]
* So once totalSum is known, one running leftSum is enough.

### 5. 🔁 How to Recall Later

* Signal 1: The problem asks for an index that balances left and right.
* Signal 2: You see repeated "sum before index" and "sum after index" checks.
* Signal 3: The current element should not be included in either side.
* Memory trick: "Whole sum minus left minus current gives right."

### 6. ⚠️ Common Mistakes

* Including nums[i] in the left or right sum.
* Updating leftSum before checking the pivot condition.
* Forgetting that index 0 can be a pivot when the right side sums to 0.
* Forgetting that the last index can be a pivot when the left side sums to 0.
* Continuing after finding a pivot, which may lose the required leftmost answer.
* Using nested loops and getting O(n^2) when O(n) is possible.
* Assuming all numbers are positive; negative numbers are allowed in many pivot-sum problems.

### 7. 📊 Complexity Analysis

* Time complexity: O(n)
  * First loop computes totalSum in O(n).
  * Second loop checks each index once in O(n).
  * O(n) + O(n) = O(2n), which simplifies to O(n).

* Space complexity: O(1)
  * totalSum, leftSum, rightSum, and i use constant extra space.
  * No extra array is created.

### 8. 🔄 Alternative Approaches

* Brute force:
  * Calculate left and right sums separately for every index.
  * Simple to understand, but too slow for large arrays.

* Prefix array:
  * Store cumulative sums in an array, then derive left/right sums from it.
  * Easier to visualize, but uses O(n) extra space.

* Prefix and suffix arrays:
  * Store left sums and right sums separately.
  * Very explicit, but more memory than needed.

* Algebraic variant:
  * A pivot exists when leftSum == totalSum - leftSum - nums[i].
  * Rearranged: 2 * leftSum + nums[i] == totalSum.
  * This is mathematically equivalent, but the rightSum formula is more beginner-friendly.
*/
