
/*
================================================================================
PROBLEM: Merge Two Sorted Arrays In-Place
(LeetCode 88 - Merge Sorted Array)
================================================================================

APPROACH: Two-Pointer Technique from Back-to-Front (Optimal)

WHY: We have empty space at the end of nums1, so we fill it from the back.
This avoids overwriting unprocessed elements.

TIME: O(m + n) - single pass through both arrays
SPACE: O(1) - no extra space used, merging happens in-place
================================================================================
*/

#include <iostream>
#include<vector>
using namespace std;

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
   // ---- INITIALIZATION ----
   // nums1 has size m+n but only first m elements are filled
   // nums2 has size n and all elements are filled
   // The remaining n positions in nums1 are for us to fill
   
   int size = m + n;                    // Total size of merged array
   int index = size - 1;                // Pointer to the LAST position in nums1 (where we'll place largest elements)
                                        // WHY: By filling from back, we don't overwrite unprocessed elements from nums1
                                        
   int i = m - 1;                       // Pointer to LAST ACTUAL element in nums1 (before empty space)
                                        // WHY: Start from the last filled position so we can compare
                                        
   int j = n - 1;                       // Pointer to LAST element in nums2
                                        // WHY: We want to compare the largest unprocessed elements


   // ---- MAIN MERGE LOGIC ----
   // DRY RUN with example: nums1=[1,2,3,0,0,0] (m=3), nums2=[2,5,6] (n=3)
   // Initial: i=2(nums1[2]=3), j=2(nums2[2]=6), index=5
   // Step 1: 6 > 3, so nums1[5]=6, j=1, index=4
   // Step 2: 5 > 3, so nums1[4]=5, j=0, index=3
   // Step 3: 2 <= 3, so nums1[3]=2 (from nums1), i=1, index=2
   // Step 4: 2 <= 1? No, so nums1[2]=2 (from nums2), j=-1, index=1
   // Now j < 0, loop ends. nums1 = [1,2,2,2,5,6] ✓
   
   while (i >= 0 && j >= 0) {           // Continue while both arrays have elements to process
       // WHAT: Pick the LARGER element from nums1[i] or nums2[j]
       // WHY: Placing largest element at the end ensures correct sorted order
       // KEY INSIGHT: We're placing the "winner" at position index and moving it out of consideration
       
       if (nums1[i] <= nums2[j]) {      // If nums2's current element is LARGER or equal
           nums1[index--] = nums2[j--]; // Place nums2[j] at nums1[index], move both pointers left
           // WHY <= (not <): Stable merge - when equal, prefer nums2 (though doesn't matter for this problem)
           // IF REMOVED: Would place smaller elements first at the end, breaking sorted order
       } else {                         // If nums1's current element is LARGER
           nums1[index--] = nums1[i--]; // Place nums1[i] at nums1[index], move both pointers left
           // IF REMOVED: Would place from wrong array, losing elements or creating duplicates
       }
   }
   // After this loop: All elements from BOTH arrays are compared and placed, OR one array is exhausted


   // ---- HANDLE REMAINING ELEMENTS ----
   // IMPORTANT: We only need to handle remaining nums2 elements!
   // WHY: If nums1 has remaining elements, they're ALREADY IN PLACE (no need to move)
   // WHY: If nums2 has remaining elements, they're SMALLER than all remaining nums1 elements
   //      and must be placed in the correct positions
   
   // DRY RUN: If nums1=[1,2,3,0,0,0], nums2=[0,0.5,6] after first loop:
   // The 0 and 0.5 from nums2 might not be processed. This loop handles them.
   
   while (j >= 0) {                     // While nums2 still has unprocessed elements
       nums1[index--] = nums2[j--];     // Copy remaining nums2 elements to nums1
       // IF REMOVED: Remaining nums2 elements would be lost! Array wouldn't be merged completely.
   }
   // After this loop: nums1 is fully sorted and merged
}


int main() {
   // ---- TEST CASE ----
   // Given: Two sorted arrays where nums1 has extra space
   // nums1 = [1, 2, 3, _, _, _] with m=3 filled elements
   // nums2 = [2, 5, 6] with n=3 elements
   // Expected output: [1, 2, 2, 3, 5, 6]
   
   vector<int> nums1 = {1, 2, 3, 0, 0, 0};  // Extra space reserved for merging (0s are placeholders)
   int m = 3;                                // Count of actual elements in nums1
   vector<int> nums2 = {2, 5, 6};            // Sorted array to merge
   int n = 3;                                // Count of elements in nums2

   // Call the optimized merge function
   merge(nums1, m, nums2, n);

   // Print the merged array
   cout << "Merged array: ";
   for (int num : nums1) {
       cout << num << " ";  // Output: 1 2 2 3 5 6
   }
   cout << endl;

   return 0;
}


/*
================================================================================
                        🧠 PROBLEM UNDERSTANDING
================================================================================

PROBLEM TYPE:
  → Array Manipulation / In-Place Merging
  → Classic "two sorted array" problem with a twist: merge in the given space

CONSTRAINTS & CLUES:
  ✓ nums1 is given with extra space (total size = m + n)
  ✓ Only first m elements are filled in nums1
  ✓ Both arrays are sorted in non-decreasing order
  ✓ Must merge IN-PLACE (no extra array allowed for optimal solution)
  ✓ The constraint "merge in-place" is THE KEY INSIGHT
  
KEY OBSERVATION:
  Most people try to merge from LEFT (like merging in merge-sort), but that
  requires shifting elements RIGHT. This is inefficient!
  
  SMART IDEA: Merge from RIGHT instead! The empty space is at the END,
  so fill from back to front. No shifting needed!


================================================================================
                        🔍 PATTERN RECOGNITION
================================================================================

DSA PATTERN: TWO-POINTER TECHNIQUE (Specific variant: Merge from Back)

HOW TO RECOGNIZE THIS PATTERN:
  1. You see "two sorted arrays" or "two sorted lists"
  2. You need to combine/merge them maintaining order
  3. The first array has extra space (RED FLAG: merge from back!)
  4. Constraint: "in-place" or "O(1) space"

WHEN TO USE TWO-POINTER:
  • Comparing elements from two sequences
  • Merging sorted structures
  • Finding pairs/triplets with specific properties
  • Validating palindromes or symmetric problems

VARIANT - MERGE FROM BACK:
  • When you have EXTRA SPACE at the end of first array
  • Fill from LARGEST to SMALLEST (backwards)
  • Avoids overwriting unprocessed elements


================================================================================
                    ⚡ APPROACH BREAKDOWN (Interview Style)
================================================================================

1️⃣ BRUTE FORCE APPROACH: (Bad - O(n log n))
   ─────────────────────────────
   • Concatenate both arrays: nums1 + nums2
   • Sort the combined array using quicksort/mergesort
   • Copy back to nums1
   
   WHY IT'S BAD:
   ✗ Time: O(n log n) - sorting dominates
   ✗ Space: O(m + n) - extra array needed
   ✗ Ignores the fact that arrays are already sorted!
   
   CODE IDEA:
     for each element in nums2:
         add to nums1
     sort(nums1)

2️⃣ BETTER APPROACH: (Good - O(m + n), but uses extra space)
   ───────────────────────────────
   • Create a temporary array to store result
   • Use two pointers (i, j) starting from the BEGINNING
   • Compare nums1[i] and nums2[j], pick smaller one
   • Copy to temporary array
   
   WHY IT'S BETTER:
   ✓ Time: O(m + n) - single pass, leverages sorted property
   ✓ Simpler logic than back-merge
   ✗ Space: O(m + n) - extra array needed
   
   CODE IDEA:
     temp = new array of size m+n
     i = 0, j = 0, k = 0
     while i < m and j < n:
         if nums1[i] <= nums2[j]:
             temp[k++] = nums1[i++]
         else:
             temp[k++] = nums2[j++]
     copy remaining elements
     copy temp back to nums1

3️⃣ OPTIMAL APPROACH: (Best - O(m + n), O(1) space) ⭐⭐⭐
   ────────────────────────────────────────────────
   • Use TWO-POINTER from the BACK
   • Start from: i = m-1, j = n-1, index = m+n-1
   • Compare nums1[i] and nums2[j], place LARGER one at nums1[index]
   • Move that pointer backward
   • Handle remaining elements from nums2 (if any)
   
   WHY THIS IS OPTIMAL:
   ✓ Time: O(m + n) - single pass through both arrays
   ✓ Space: O(1) - merge happens in-place, using existing space in nums1
   ✓ Leverages empty space at end of nums1
   ✓ No shifting elements needed
   ✓ Elegant and efficient
   
   THIS IS THE SOLUTION WE IMPLEMENTED!


================================================================================
                        🧩 INTUITION BUILDING
================================================================================

THE CORE IDEA IN SIMPLE TERMS:
──────────────────────────────

Imagine you have two sorted stacks of cards on a table:

    Stack A (nums1): [1, 2, 3, _, _, _]    (has empty slots)
    Stack B (nums2): [2, 5, 6]
    
Your goal: Merge them into Stack A in sorted order.

NAIVE APPROACH (Merging from Front):
    Pick from A or B, put in Stack A, BUT need to shift everything right!
    Complicated, slow, error-prone.

SMART APPROACH (Merging from Back):
    ✓ Look at the LAST card in A (3) and LAST card in B (6)
    ✓ Take the BIGGER one (6), put in empty last slot
    ✓ Now that card is done, look at next-to-last cards
    ✓ Repeat: 5 > 3, place 5, then look at 2 and 3...
    ✓ Result: [1, 2, 2, 3, 5, 6] ✓
    
THE "TRICK" OR INSIGHT:
──────────────────────

Most problems ask you to fill from FRONT. This one cleverly gives you 
EXTRA SPACE at the END (constraint: merge in-place).

The MOMENT you realize "there's empty space at the end," the solution
is to FILL FROM BACK.

This transforms a potentially O(m*n) problem (with shifting) into O(m+n)!


================================================================================
                        🔁 HOW TO RECALL THIS LATER
================================================================================

⚡ KEY SIGNALS (Identify this problem):
   1. Two sorted arrays → merge them
   2. First array has EXTRA SPACE or is LARGER than content
   3. Constraint: In-place OR O(1) space

🧠 MEMORY TRICK (The Core Essence):
   "When merging sorted arrays and you have EXTRA SPACE at the END,
    merge BACKWARDS to AVOID SHIFTING."
    
   Acronym: BEAM
   B - backward/back
   E - extra space
   A - arrays (sorted)
   M - merge

📝 PATTERN TO REMEMBER:
   Two sorted + extra space + in-place → Two-pointer from BACK


================================================================================
                        ⚠️ COMMON MISTAKES
================================================================================

❌ MISTAKE 1: Merging from LEFT (like merge-sort)
   ──────────────────────────────────────────────
   Code:
     int index = 0;  // ← Starting from front
     while (i < m && j < n) {
         if (nums1[i] <= nums2[j]) {
             nums1[index++] = nums1[i++];  // ← OVERWRITES elements!
         }
     }
   
   PROBLEM: You'll overwrite nums1[i] before processing it!
            If nums1 = [1, 2, 3, 0, 0, 0] and you place at index 0
            at the same time nums1[0] isn't processed yet, DATA LOSS!
   
   FIX: Start from the BACK instead (what we did)


❌ MISTAKE 2: Forgetting to handle remaining nums2 elements
   ────────────────────────────────────────────────────────
   Code:
    //  while (i >= 0 && j >= 0) { /* merge */
     // No second while loop for remaining nums2!
   
// //    PROBLEM: If nums2 has smaller elements, they won't be placed!
// //             Example: nums1=[1,0,0], nums2=[0,1] after first loop,
// //             remaining 0 from nums2 is lost
   
// //    FIX: Add second while loop:
// //         while (j >= 0) { nums1[index--] = nums2[j--]; }


// // ❌ MISTAKE 3: Not understanding why we DON'T need to handle nums1 remainder
// //    ──────────────────────────────────────────────────────────────────────
// //    Code:
// //      while (i >= 0 && j >= 0) { /* merge */ }
// //      while (i >= 0) { nums1[index--] = nums1[i--]; }  // ← Unnecessary!
// //      while (j >= 0) { nums1[index--] = nums2[j--]; }
   
// //    PROBLEM: The second while loop is UNNECESSARY because remaining nums1
// //             elements are already in their correct positions (we fill from
// //             back, so they naturally end up in correct spots)
   
// //    FIX: Only handle remaining nums2:
// //         while (j >= 0) { nums1[index--] = nums2[j--]; }


// // ❌ MISTAKE 4: Using < instead of <=
// //    ──────────────────────────────────
// //    Code:
// //      if (nums1[i] < nums2[j]) {  // Strict inequality
   
// //    PROBLEM: Not a bug for this problem, but < vs <= matters for stability
// //             Using < means when equal, we pick from nums1 first (still sorted)
// //             Using <= means when equal, we pick from nums2 first (also valid)
            
// //    FIX: Either works here, but <= is conventional for stable merging


// // ❌ MISTAKE 5: Off-by-one errors with pointers
// //    ───────────────────────────────────────────
// //    Code:
// //      int index = size;  // ← WRONG! Should be size - 1
// //      int i = m;         // ← WRONG! Should be m - 1
   
// //    PROBLEM: Arrays are 0-indexed. If size=6, last valid index is 5!
   
// //    FIX: Start from size-1, m-1, n-1


// // ================================================================================
// //                         📊 COMPLEXITY ANALYSIS
// // ================================================================================

// TIME COMPLEXITY: O(m + n)
// ───────────────────────
// Reasoning:
//   • We iterate through nums1 (m elements) and nums2 (n elements) exactly once
//   • Each element is processed: compared once, then placed once
//   • Total operations: m + n comparisons, m + n placements
//   • No nested loops, no recursion
//   • Therefore: O(m + n) linear time

// Example:
//   m=3, n=3 → 3+3=6 operations (best, worst, average case all same)
//   m=1000, n=1000 → 2000 operations


// SPACE COMPLEXITY: O(1)
// ─────────────────────
// Reasoning:
//   • We only use three pointers: i, j, index
//   • Pointers are just integers (constant space)
//   • No extra arrays, no recursion stack, no data structures
//   • We modify nums1 in-place
//   • No additional space grows with input size
//   • Therefore: O(1) constant space

// Comparison with alternatives:
//   • Brute force (sort): O(n log n) time, O(n) space
//   • Better approach (extra array): O(n) time, O(n) space ← Extra space!
//   • Our optimal approach: O(n) time, O(1) space ← BEST!


// WHY THIS IS OPTIMAL:
//   ✓ O(m+n) is the lower bound (must touch every element)
//   ✓ O(1) space is best possible (in-place constraint)
//   ✓ Cannot do better than this solution


// ================================================================================
//                     🔄 ALTERNATIVE APPROACHES
// ================================================================================

// ALTERNATIVE 1: Three-Pointer from Front (with temporary array)
// ───────────────────────────────────────────────────────────────
// Approach:
//   1. Create temp array of size m+n
//   2. Use three pointers: i (nums1), j (nums2), k (temp)
//   3. Compare nums1[i] and nums2[j], place smaller in temp[k]
//   4. Copy temp back to nums1

// Pros:
//   ✓ Simpler logic to understand
//   ✓ More similar to classic merge-sort merging
//   ✓ Easier to debug
  
// Cons:
//   ✗ Requires O(m+n) extra space
//   ✗ Extra copying pass (temp → nums1)
//   ✗ Not optimal for this problem

// Time: O(m+n) Space: O(m+n) ← Worse space complexity


// ALTERNATIVE 2: Recursive Two-Pointer from Back
// ────────────────────────────────────────────────
// Approach:
//   1. Create recursive function merge(i, j, k)
//   2. Base case: if i < 0, copy remaining nums2; if j < 0, return (already in place)
//   3. Recursive: compare nums1[i] and nums2[j], place at nums1[k], recurse

// Pros:
//   ✓ Elegant, shows understanding of recursion
//   ✓ Still O(1) space (recursive stack is O(m+n) but represents indices only)
  
// Cons:
//   ✗ Recursion overhead
//   ✗ Harder to understand for interviews
//   ✗ Stack depth of m+n might cause issues on very large arrays
//   ✗ Not faster than iterative version

// Time: O(m+n) Space: O(m+n) (call stack) ← Worse space


// ALTERNATIVE 3: Insertion at Position (Very Inefficient)
// ────────────────────────────────────────────────────────
// Approach:
//   For each element in nums2:
//     Find correct position in nums1 using binary search
//     Insert (shift elements right)

// Pros:
//   ✓ Conceptually simple
  
// Cons:
//   ✗ O(m*n) time due to shifting
//   ✗ Very inefficient
//   ✗ No advantage over our solution

// Time: O(m*n) Space: O(1)


// BEST PRACTICE:
// ──────────────
// Use the two-pointer from back approach (our solution).
// It's the optimal, elegant, and interview-favorite solution.

// In an interview, mention the alternatives but explain why back-merging is best:
// "We could use extra space and merge from front, but this array already 
// provides space at the end, so we use it! Merge from back to avoid shifting."

// ================================================================================
// */