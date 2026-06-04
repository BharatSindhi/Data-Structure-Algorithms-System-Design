#include <iostream>
// <iostream> is included for standard input/output support.
// This file does not currently print anything, so removing this line would not break
// the merge logic itself, but it could break future cout/cin usage in main().

#include <vector>
// <vector> is necessary because the function uses vector<int>.
// If this line is removed, the compiler will not know what vector means.

using namespace std;
// Allows writing vector instead of std::vector.
// If removed, every standard library name would need the std:: prefix.

class Solution {
public:
    /*
        Problem: Merge Sorted Array

        Given:
        - nums1 has size m + n.
        - The first m values of nums1 are sorted real values.
        - The last n slots of nums1 are empty placeholders, usually 0.
        - nums2 has n sorted values.

        Goal:
        - Merge nums2 into nums1 so nums1 becomes one sorted array.
        - Do it in-place inside nums1.

        Key idea:
        - Fill nums1 from the back, not from the front.
        - Why? The back has empty space, so writing there does not overwrite
          unprocessed nums1 values.
    */
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // Total number of final elements after merging both arrays.
        // Example: nums1 = [1,2,3,0,0,0], m = 3 and nums2 = [2,5,6], n = 3
        // size = 6, so the final valid indexes are 0 to 5.
        // If this line is removed, we cannot know the last valid position in nums1.
        int size = m + n;

        // index points to the position where the next largest element should be placed.
        // We start from size - 1 because sorted merging from the end places larger
        // values first.
        //
        // Dry run setup:
        // nums1 = [1,2,3,0,0,0], nums2 = [2,5,6]
        // m = 3, n = 3
        // index = 5, i = 2, j = 2
        //
        // If this line is removed, nums1[index] cannot be assigned safely.
        int index = size - 1; // Position to insert at in nums1

        // i points to the last real element in nums1, not the placeholder zeros.
        // For m = 3, the real elements are indexes 0, 1, 2, so i = 2.
        // If m = 0, i becomes -1, correctly meaning nums1 has no real values.
        //
        // If this line is removed, we cannot compare nums1's remaining values.
        int i = m - 1;        // Last index of actual elements in nums1

        // j points to the last element in nums2.
        // For n = 3, nums2 indexes are 0, 1, 2, so j = 2.
        // If n = 0, j becomes -1, correctly meaning nums2 is empty.
        //
        // If this line is removed, we cannot compare nums2's remaining values.
        int j = n - 1;        // Last index of nums2

        // Merge both arrays starting from the back
        // This loop runs while both arrays still have unmerged elements.
        //
        // Why compare from the back?
        // - nums1 and nums2 are already sorted in non-decreasing order.
        // - Therefore, the largest remaining value must be either nums1[i] or nums2[j].
        // - We place that largest value at nums1[index], then move backward.
        //
        // If this loop is removed, no comparison-based merging happens and nums1
        // would remain mostly unchanged or incomplete.
        //
        // Edge cases handled:
        // - Duplicate values: <= sends nums2[j] first when values are equal, still sorted.
        // - nums1 has no real values: i = -1, loop is skipped, nums2 is copied later.
        // - nums2 is empty: j = -1, loop is skipped, nums1 is already correct.
        while (i >= 0 && j >= 0) {
            // Compare the largest remaining value in nums1 with the largest remaining
            // value in nums2.
            //
            // Dry run:
            // nums1 = [1,2,3,0,0,0], nums2 = [2,5,6]
            // i = 2 -> nums1[i] = 3
            // j = 2 -> nums2[j] = 6
            // 3 <= 6 is true, so 6 goes to nums1[5].
            //
            // Why <=?
            // - If nums2[j] is greater or equal, placing nums2[j] at the end is valid.
            // - For equal values, either choice keeps the array sorted.
            //
            // If this condition is removed or reversed incorrectly, the merge may place
            // smaller values after larger values and break sorted order.
            if (nums1[i] <= nums2[j]) {
                // nums2[j] is the largest remaining value, so place it at nums1[index].
                // Then move both index and j one step left.
                //
                // Example step 1:
                // before: nums1 = [1,2,3,0,0,0], index = 5, j = 2
                // write nums2[2] = 6 at nums1[5]
                // after:  nums1 = [1,2,3,0,0,6], index = 4, j = 1
                //
                // If this assignment is removed, nums2's larger elements would never be
                // inserted into nums1.
                nums1[index--] = nums2[j--];
            } else {
                // nums1[i] is larger, so keep it by moving it to the current back slot.
                // Then move both index and i one step left.
                //
                // Continuing dry run after placing 6 and 5:
                // nums1 = [1,2,3,0,5,6], nums2 = [2,5,6]
                // i = 2 -> 3, j = 0 -> 2, index = 3
                // 3 > 2, so place 3 at nums1[3].
                // nums1 becomes [1,2,3,3,5,6], then i moves to 1.
                //
                // Notice this does not lose data because nums1[3] was a placeholder.
                // If we merged from the front instead, we might overwrite nums1[0..m-1]
                // before using them.
                nums1[index--] = nums1[i--];
            }
        }

        // If any elements left in nums2, copy them over
        // At this point, at least one array is exhausted.
        //
        // If nums2 still has values, they must be the smallest remaining values, so they
        // belong at the front positions of nums1.
        //
        // Dry run continuation:
        // nums1 = [1,2,3,3,5,6], nums2 = [2,5,6]
        // i = 1 -> nums1[i] = 2
        // j = 0 -> nums2[j] = 2
        // index = 2
        // Since nums1[i] <= nums2[j], copy nums2[0] into nums1[2].
        // nums1 = [1,2,2,3,5,6], j = -1, done.
        //
        // Why only copy leftover nums2?
        // - If nums1 has leftovers, they are already in the correct front positions.
        // - If nums2 has leftovers, they are not yet in nums1 and must be copied.
        //
        // If this loop is removed, cases like:
        // nums1 = [4,5,6,0,0,0], nums2 = [1,2,3]
        // would fail because [1,2,3] must be copied into the front.
        while (j >= 0) {
            // Copy each remaining nums2 value into nums1 from right to left.
            //
            // Edge case example:
            // nums1 = [0], m = 0, nums2 = [1], n = 1
            // main loop is skipped because i = -1.
            // this loop copies 1 into nums1[0].
            //
            // If this assignment is removed, nums2 leftovers disappear.
            nums1[index--] = nums2[j--];
        }

        /*
            Final dry run summary for:
            nums1 = [1,2,3,0,0,0], m = 3
            nums2 = [2,5,6], n = 3

            Start:
            index = 5, i = 2, j = 2

            Compare 3 and 6 -> place 6 at index 5
            nums1 = [1,2,3,0,0,6]

            Compare 3 and 5 -> place 5 at index 4
            nums1 = [1,2,3,0,5,6]

            Compare 3 and 2 -> place 3 at index 3
            nums1 = [1,2,3,3,5,6]

            Compare 2 and 2 -> place nums2's 2 at index 2
            nums1 = [1,2,2,3,5,6]

            nums2 is exhausted, so stop.
            Final nums1 = [1,2,2,3,5,6]

            Time Complexity:
            O(m + n), because each element is moved or checked at most once.

            Space Complexity:
            O(1), because the merge happens inside nums1 without creating another array.
        */
    }
};

int main() {
    // Empty main function.
    // The Solution class is intended to be tested by an online judge like LeetCode.
    // Removing main() may be fine on LeetCode, but in a normal local C++ program the
    // linker usually needs a main function as the program entry point.
    
    return 0;
    // Program exits successfully.
}

/*
    ### 1. 🧠 Problem Understanding

    - This is an array merging problem.
    - More specifically, it is the "merge two sorted arrays in-place" problem.
    - nums1 already has enough extra space at the end to store nums2.
    - Key constraint/clue: both arrays are sorted.
    - Another key clue: nums1 has length m + n, but only the first m values are real.

    What this tells us:
    - Since both arrays are sorted, we should not need to sort again.
    - Since nums1 has empty space at the end, we can safely fill from the back.

    ### 2. 🔍 Pattern Recognition

    Pattern used:
    - Two pointers
    - In-place merge
    - Reverse traversal

    How to recognize this later:
    - You are given two sorted arrays/lists.
    - You need to combine them while preserving sorted order.
    - One structure has enough empty space to hold the final answer.
    - Overwriting from the front would destroy values you still need.

    Signal phrase:
    - "Merge sorted arrays in-place" usually means compare from the end.

    ### 3. ⚡ Approach Breakdown (Interview Style)

    Brute force idea:
    - Copy nums2 into the empty part of nums1.
    - Sort nums1.
    - Time: O((m + n) log(m + n))
    - Space: depends on sorting implementation.

    Better approach:
    - Use an extra array.
    - Compare from the front of nums1 and nums2.
    - Push the smaller value into the extra array.
    - Copy the result back to nums1.
    - Time: O(m + n)
    - Space: O(m + n)

    Optimal approach:
    - Use three pointers from the back.
    - Compare nums1[i] and nums2[j].
    - Put the larger one at nums1[index].
    - Move the corresponding pointer left.
    - Time: O(m + n)
    - Space: O(1)

    Why this one is chosen:
    - It uses the sorted property.
    - It uses the extra space already available in nums1.
    - It avoids extra memory.

    ### 4. 🧩 Intuition Building

    Core idea:
    - The largest remaining element should go to the last available position.
    - Because nums1 has empty slots at the end, the back is the safest place to write.

    The trick:
    - Do not start from the front.
    - Starting from the front can overwrite nums1 values before they are compared.
    - Starting from the back protects unprocessed data.

    Simple mental model:
    - Imagine filling boxes from right to left.
    - Each time, choose the bigger item from the two array endings.

    ### 5. 🔁 How to Recall Later

    Key signals:
    - Two sorted arrays.
    - Need one sorted merged result.
    - First array has extra empty space at the end.

    One-line memory trick:
    - "When nums1 has empty space at the back, merge from the back."

    ### 6. ⚠️ Common Mistakes

    - Starting from the front and overwriting useful nums1 values.
    - Forgetting to copy leftover nums2 values.
    - Trying to copy leftover nums1 values even though they are already in place.
    - Using nums1.size() without understanding that only first m values are real.
    - Treating placeholder zeros as real values.
    - Mishandling m = 0 or n = 0.

    ### 7. 📊 Complexity Analysis

    Time Complexity:
    - O(m + n)
    - Each pointer only moves left.
    - Every element is considered at most once.

    Space Complexity:
    - O(1)
    - No extra array is created.
    - Only integer pointer variables are used.

    ### 8. 🔄 Alternative Approaches

    1. Copy and sort:
       - Put all nums2 values into nums1's empty slots.
       - Sort nums1.
       - Very simple, but slower than necessary.

    2. Extra result array:
       - Use two pointers from the front.
       - Store merged values in a new array.
       - Copy back into nums1.
       - Easier to reason about, but uses O(m + n) extra space.

    3. Insert one by one:
       - Insert every nums2 element into its correct position in nums1.
       - This causes many shifts.
       - Usually O(m * n) or close to O((m + n)^2), so it is inefficient.
*/
