/*
════════════════════════════════════════════════════════════════════════════════
                              MERGE SORT ALGORITHM
════════════════════════════════════════════════════════════════════════════════

PROBLEM STATEMENT:
─────────────────
Sort an integer array using the Merge Sort algorithm.

REAL-WORLD ANALOGY:
──────────────────
Imagine you have a pile of unsorted papers. Instead of comparing every paper to
every other paper, you:
  1. Split the pile into smaller piles (divide)
  2. Sort each small pile (conquer)
  3. Merge the sorted piles back together (combine)

This is MUCH more efficient than trying to sort the original huge pile!

KEY PROPERTIES OF MERGE SORT:
─────────────────────────────
✓ Divide-and-Conquer algorithm
✓ STABLE sort (preserves order of equal elements)
✓ O(n log n) in BEST, AVERAGE, and WORST cases (guaranteed!)
✓ Requires O(n) extra space (not in-place)
✓ Works great for linked lists and external sorting

════════════════════════════════════════════════════════════════════════════════
*/

#include <iostream>
#include <vector>
using namespace std;

// ╔════════════════════════════════════════════════════════════════════════════╗
// ║                          PHASE 1: MERGE FUNCTION                          ║
// ║   Purpose: Combine two sorted subarrays into one sorted array            ║
// ╚════════════════════════════════════════════════════════════════════════════╝

void merge(vector<int>& array, int low, int mid, int high) {
    // 🔴 WHAT: Calculate sizes of the two halves
    // ─────────────────────────────────────────────────────────────────────
    // WHAT: n1 = number of elements in LEFT subarray [low...mid]
    //       n2 = number of elements in RIGHT subarray [mid+1...high]
    // WHY: We need to know how many elements to create temporary arrays for
    // FORMULA: n1 = mid - low + 1  (inclusive on both ends)
    //          n2 = high - mid     (mid+1 to high, so high - (mid+1) + 1 = high - mid)
    // EDGE CASE: When subarrays are size 1: n1=1, n2=0 or n1=0, n2=1
    int n1 = mid - low + 1;
    int n2 = high - mid;
    
    // 🔴 WHAT: Create temporary arrays to hold the two halves
    // ─────────────────────────────────────────────────────────────────────
    // WHY: We need separate arrays to safely compare and merge without
    //      overwriting data in the original array during the process
    // IF REMOVED: We'd overwrite array elements before comparing them,
    //             corrupting the sorting process
    // MEMORY: Creates O(n1 + n2) = O(n) temporary storage
    vector<int> left_part(n1), right_part(n2);

    // 🔴 WHAT: Copy left half of array into left_part
    // ─────────────────────────────────────────────────────────────────────
    // WHY: We need a snapshot of the data to safely manipulate
    // LOOP: Copies elements from array[low] to array[mid] into left_part
    // TIME: O(n1) - iterates through all n1 elements
    for (int i = 0; i < n1; ++i)
        left_part[i] = array[low + i];
    
    // 🔴 WHAT: Copy right half of array into right_part
    // ─────────────────────────────────────────────────────────────────────
    // WHY: Separate copy ensures we don't lose data during merge
    // STARTING POINT: mid + 1 (the element right after mid)
    // TIME: O(n2) - iterates through all n2 elements
    for (int i = 0; i < n2; ++i)
        right_part[i] = array[mid + 1 + i];

    // ════════════════════════════════════════════════════════════════════════
    // PHASE 1: Initialize merge pointers and start merging
    // ════════════════════════════════════════════════════════════════════════
    
    // 🔴 WHAT: Initialize three pointers
    // ─────────────────────────────────────────────────────────────────────
    // p1: Points to current position in left_part (starts at 0)
    // p2: Points to current position in right_part (starts at 0)
    // write_ind: Points to current position where we write in original array
    //            (starts at low, the beginning of the merge range)
    // WHY: We use these to traverse and merge the two sorted arrays
    int p1 = 0, p2 = 0, write_ind = low;
    
    // 🔴 WHAT: CORE MERGE LOGIC - Compare and pick smaller element
    // ─────────────────────────────────────────────────────────────────────
    // LOOP CONDITION: Continue while BOTH arrays have unmerged elements
    // IF REMOVED: We'd miss comparing elements from both arrays
    //
    // DRY RUN on two sorted arrays [1, 3, 5] and [2, 4, 6]:
    // ─────────────────────────────────────────────────────────────────
    // Step 1: p1=0, p2=0, write_ind=low
    //   Compare: left_part[0]=1 vs right_part[0]=2
    //   1 <= 2 → Write 1, p1++
    //   Result: array[low] = 1, p1=1, p2=0
    //
    // Step 2: p1=1, p2=0, write_ind=low+1
    //   Compare: left_part[1]=3 vs right_part[0]=2
    //   3 > 2 → Write 2, p2++
    //   Result: array[low+1] = 2, p1=1, p2=1
    //
    // Step 3: p1=1, p2=1, write_ind=low+2
    //   Compare: left_part[1]=3 vs right_part[1]=4
    //   3 <= 4 → Write 3, p1++
    //   Result: array[low+2] = 3, p1=2, p2=1
    //
    // Step 4: p1=2, p2=1, write_ind=low+3
    //   Compare: left_part[2]=5 vs right_part[1]=4
    //   5 > 4 → Write 4, p2++
    //   Result: array[low+3] = 4, p1=2, p2=2
    //
    // Step 5: p1=2, p2=2, write_ind=low+4
    //   Compare: left_part[2]=5 vs right_part[2]=6
    //   5 <= 6 → Write 5, p1++
    //   Result: array[low+4] = 5, p1=3, p2=2
    //
    // Loop exits because p1==n1 (3), then we copy remaining from right_part
    // Final: array[low+5] = 6
    // FINAL RESULT: [1, 2, 3, 4, 5, 6] ✓ SORTED!
    //
    // STABILITY: Using <= instead of < preserves order of equal elements
    //            (left array elements come before right array elements
    //             when values are equal)
    //
    // EDGE CASES HANDLED:
    // ✓ One array larger than other (handled by while loops below)
    // ✓ Arrays of size 1 (loop runs n1-1 and n2-1 times)
    // ✓ Duplicate elements (uses <= for stability)
    while (p1 < n1 && p2 < n2) {
        if (left_part[p1] <= right_part[p2]) {
            // 🔴 LEFT element is smaller or equal → take from left
            // WHY <=: Ensures STABILITY (equal elements maintain relative order)
            array[write_ind] = left_part[p1++];
        } else {
            // 🔴 RIGHT element is smaller → take from right
            array[write_ind] = right_part[p2++];
        }
        ++write_ind;  // 🔴 Move write position forward after each merge
    }

    // ════════════════════════════════════════════════════════════════════════
    // PHASE 2: Copy remaining elements (only ONE of these loops will execute)
    // ════════════════════════════════════════════════════════════════════════
    
    // 🔴 WHAT: Copy any remaining elements from left_part
    // ─────────────────────────────────────────────────────────────────────
    // WHEN: Executes only if left_part had more elements than right_part
    // WHY: These remaining elements are already sorted, just need copying
    // IF REMOVED: Some elements from left_part would be lost/not included
    // EXAMPLE: Merging [5,6,7] and [1,2]
    //          After comparison loop: p1=2, p2=2
    //          left_part[2]=7 still needs to be written
    while (p1 < n1)
        array[write_ind++] = left_part[p1++];

    // 🔴 WHAT: Copy any remaining elements from right_part
    // ─────────────────────────────────────────────────────────────────────
    // WHEN: Executes only if right_part had more elements than left_part
    // WHY: These remaining elements are already sorted, just need copying
    // IF REMOVED: Some elements from right_part would be lost/not included
    // EXAMPLE: Merging [1,2] and [5,6,7]
    //          After comparison loop: p1=2, p2=2
    //          right_part[2]=7 still needs to be written
    while (p2 < n2)
        array[write_ind++] = right_part[p2++];
    
    // 🔴 END OF MERGE: Two sorted subarrays successfully merged into one
}

// ╔════════════════════════════════════════════════════════════════════════════╗
// ║                    PHASE 2: DIVIDE AND CONQUER FUNCTION                   ║
// ║   Purpose: Recursively divide array and trigger merges                   ║
// ╚════════════════════════════════════════════════════════════════════════════╝

void merge_sort(vector<int>& array, int low, int high) {
    // 🔴 WHAT: BASE CASE - check if array needs sorting
    // ─────────────────────────────────────────────────────────────────────
    // IF REMOVED: Function would recurse indefinitely, causing stack overflow!
    // CONDITION: low >= high means 0 or 1 element (already sorted)
    // WHY: An array with 1 or 0 elements is trivially sorted
    // WHEN TRUE: Returns immediately without further recursion
    if (low >= high)
        return;

    // 🔴 WHAT: Calculate midpoint for dividing the array
    // ─────────────────────────────────────────────────────────────────────
    // FORMULA: mid = low + (high - low) / 2  (avoids integer overflow!)
    // WHY NOT: mid = (low + high) / 2
    //          Because low + high could overflow for very large indices
    // SAFER: Using (high - low) / 2 prevents overflow
    // RESULT: Divides array roughly in half
    // EXAMPLE: array [0...9], low=0, high=9
    //          mid = 0 + (9-0)/2 = 4
    //          Creates split: [0...4] and [5...9]
    int mid = low + (high - low) / 2;
    
    // 🔴 WHAT: RECURSIVE CALL - Sort left half
    // ─────────────────────────────────────────────────────────────────────
    // RANGE: array[low] to array[mid]
    // WHY: Divide-and-conquer: solve smaller subproblem
    // RECURSION TREE: Keeps dividing until base case (low >= high)
    merge_sort(array, low, mid);
    
    // 🔴 WHAT: RECURSIVE CALL - Sort right half
    // ─────────────────────────────────────────────────────────────────────
    // RANGE: array[mid+1] to array[high]
    // WHY: Sort the other half independently
    // INDEPENDENCE: Left and right sorts don't affect each other
    merge_sort(array, mid + 1, high);
    
    // 🔴 WHAT: MERGE - Combine two sorted halves
    // ─────────────────────────────────────────────────────────────────────
    // ORDER MATTERS: Must merge AFTER both recursive calls complete!
    // IF REMOVED: Sorted halves never combined → array remains unsorted
    // IF CALLED BEFORE RECURSION: Would merge unsorted data
    // POST-ORDER: This merge happens in post-order traversal
    merge(array, low, mid, high);
}

class Solution {
public:
    // 🔴 WHAT: Wrapper function for user-friendly interface
    // ─────────────────────────────────────────────────────────────────────
    // WHY: Users call this; we handle index calculations internally
    // CONVERTS: From 1-based intuition to 0-based array indexing
    vector<int> sortArray(vector<int>& nums) {
        merge_sort(nums, 0, nums.size() - 1);  // Call merge sort on entire array
        return nums;
    }
};

int main() {
    return 0;
}

/* 
╔════════════════════════════════════════════════════════════════════════════════╗
║               COMPREHENSIVE ANALYSIS - INTERVIEW PREPARATION                   ║
╚════════════════════════════════════════════════════════════════════════════════╝
*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 1️⃣  PROBLEM UNDERSTANDING
└─────────────────────────────────────────────────────────────────────────────────

🎯 Problem Type:
   • Divide-and-Conquer Algorithm
   • Sorting Problem
   • Recursive Algorithm
   • Comparison-based Sorting

📌 Key Characteristics:
   ✓ Must sort array in ascending/descending order
   ✓ Elements can be any comparable type
   ✓ Can have duplicates
   ✓ No constraint on input size

🔑 Core Constraints:
   • Input: An unsorted array of integers
   • Output: The same array sorted
   • Method: Must maintain stability (equal elements keep relative order)
   • No in-place requirement (can use extra space)
   • Guaranteed O(n log n) expected

❌ What This Problem IS NOT:
   • NOT about finding specific elements
   • NOT about searching
   • NOT about in-place sorting requirement
   • NOT about minimizing space at all costs

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 2️⃣  PATTERN RECOGNITION - Divide-and-Conquer
└─────────────────────────────────────────────────────────────────────────────────

🎨 DSA Pattern Used: DIVIDE-AND-CONQUER

Where Merge Sort Pattern Appears:
┌────────────────────────────────────────────────────────────────┐
│ SORTING (Direct Applications):                                │
│ • Sorting arrays/lists                                        │
│ • Sorting linked lists                                        │
│ • External sorting (files larger than memory)                │
│                                                                │
│ DIVIDE-AND-CONQUER (Related Problems):                        │
│ • Quick Sort (variation)                                      │
│ • Finding inversions in array                                 │
│ • Merge sort variations (K-way merge)                         │
│ • Counting inversions                                         │
│                                                                │
│ SIMILAR PROBLEMS:                                             │
│ • Merge K sorted lists                                        │
│ • Merge sorted arrays                                         │
│ • External merge sort                                         │
└────────────────────────────────────────────────────────────────┘

🔍 Signals to Recognize Divide-and-Conquer:
   Signal #1: "Divide the problem into INDEPENDENT subproblems"
   Signal #2: "Solve each subproblem RECURSIVELY"
   Signal #3: "COMBINE solutions to get final answer"
   Signal #4: "Have a clear BASE CASE for recursion"

Pattern Structure:
   1. DIVIDE: Split problem into smaller identical subproblems
   2. CONQUER: Solve subproblems recursively
   3. COMBINE: Merge solutions to solve original problem

🧠 Memory Trick:
   "DIVIDE the problem RECURSIVELY until tiny → CONQUER tiny problems 
    → COMBINE results back up"

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 3️⃣  APPROACH BREAKDOWN - Interview Style Evolution
└─────────────────────────────────────────────────────────────────────────────────

APPROACH 1: BRUTE FORCE - Bubble Sort
═══════════════════════════════════════════════════════════════════════════════
Time: O(n²)  |  Space: O(1)

Logic:
  • Compare adjacent elements
  • Swap if out of order
  • Repeat n times

Problem: TOO SLOW for large arrays!
  Example: 1 million elements → 1 trillion comparisons

────────────────────────────────────────────────────────────────────────────────

APPROACH 2: IMPROVED - Quick Sort
═══════════════════════════════════════════════════════════════════════════════
Time: O(n log n) average, O(n²) worst  |  Space: O(log n)

Logic:
  • Pick pivot element
  • Partition around pivot
  • Recursively sort left and right

Better than Bubble, but:
  ✗ Worst case O(n²) (when pivot is always smallest/largest)
  ✗ Not stable (doesn't preserve equal element order)

────────────────────────────────────────────────────────────────────────────────

APPROACH 3: OPTIMAL - MERGE SORT ⭐⭐⭐
═══════════════════════════════════════════════════════════════════════════════
Time: O(n log n) GUARANTEED  |  Space: O(n)

Logic:
  1. DIVIDE: Split array in half recursively
  2. CONQUER: Sort each half independently
  3. COMBINE: Merge two sorted halves

WHY THIS APPROACH IS CHOSEN:
  ✓ GUARANTEED O(n log n) in best, average, AND worst case
  ✓ STABLE sort (preserves order of equal elements)
  ✓ Predictable performance (no worst-case collapse)
  ✓ Works perfectly for linked lists
  ✓ Great for external sorting (files, streams)
  ✗ Requires O(n) extra space (trade-off worth it!)

Key Insight:
  Merging two sorted arrays is EASY:
  • Compare heads of both arrays
  • Take smaller one
  • Move forward
  • Result: perfectly sorted merged array

This insight makes Merge Sort elegant!

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 4️⃣  INTUITION BUILDING - Simple Explanation
└─────────────────────────────────────────────────────────────────────────────────

🎬 Thought Experiment - The Library Sorting Problem:

You have 1000 unsorted books on the floor. How do you sort them efficiently?

Inefficient Way (Bubble Sort):
  • Go through all books, find the smallest, put it first
  • Repeat 1000 times → 1,000,000+ operations!

Smart Way (Merge Sort):
  1️⃣  DIVIDE: Split books into two piles of 500 each
      └─→ Repeat: Split each pile into two piles of 250 each
      └─→ Repeat: Keep splitting until you have individual books
      └─→ Stop: Single books are "sorted"

  2️⃣  MERGE: Take two piles, interleave sorted books
      • Compare front books from each pile
      • Take the smaller book first
      • Move to next book in that pile
      • Repeat until one pile exhausted
      • Copy remaining books from other pile
      └─→ Result: Two piles merged into one sorted pile

  3️⃣  REPEAT MERGING: Work your way back up
      • Merge adjacent sorted piles
      • Soon you have two sorted piles of 500 each
      • Final merge: 1000 books perfectly sorted!

Why Merge Sort Wins:
  • Splitting: O(log n) levels (keep cutting in half)
  • At each level: O(n) work (merging all n elements)
  • Total: O(n log n) ✓

Core Idea:
  "Split until trivial, then smartly combine back"

The "Trick":
  The MERGE operation is the secret sauce:
  Two sorted arrays merging in O(n) time is beautiful!

═══════════════════════════════════════════════════════════════════════════════

Recursion Tree for [3, 1, 4, 1, 5, 9, 2, 6]:
                                                                                    
                    [3, 1, 4, 1, 5, 9, 2, 6] ← LEVEL 0 (1 problem)
                         /                    \\
                 [3, 1, 4, 1]          [5, 9, 2, 6] ← LEVEL 1 (2 problems)
                  /          \\            /        \\
            [3, 1]     [4, 1]        [5, 9]     [2, 6] ← LEVEL 2 (4 problems)
            /    \\     /    \\        /   \\     /   \\
          [3]  [1]   [4]  [1]      [5]  [9]   [2]  [6] ← LEVEL 3 (8 problems - base case)
          
          [1,3]    [1,4]         [5,9]    [2,6] ← MERGE step 1
              \     /                 \    /
              [1,1,3,4]              [2,5,6,9]  ← MERGE step 2
                     \                   /
                    [1,1,2,3,4,5,6,9]   ← FINAL (sorted!)

Recursion Depth: log(8) = 3 levels
Work at each level: 8 comparisons/merges = O(n)
Total: 3 × 8 = 24 operations ≈ O(n log n) ✓

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 5️⃣  HOW TO RECALL LATER - Memory Anchors
└─────────────────────────────────────────────────────────────────────────────────

When You See a Sorting Problem, Ask Yourself:

❓ Question 1: "Do I need GUARANTEED O(n log n) performance?"
   If YES → Consider Merge Sort
   (Quick Sort might hit O(n²) in worst case)

❓ Question 2: "Must the sort be STABLE?
   (preserve order of equal elements)"
   If YES → Merge Sort is perfect
   (Quick Sort and Heap Sort are unstable)

❓ Question 3: "Is space NOT a constraint?"
   If YES → Merge Sort is ideal
   (Can use extra O(n) space without worry)

───────────────────────────────────────────────────────────────────────────────

🎯 2-3 Key Signals to Identify Merge Sort:

   Signal 1: "Guarantee O(n log n) required"
   Signal 2: "Stability matters (equal elements keep order)"
   Signal 3: "Recursive divide-and-conquer approach"

───────────────────────────────────────────────────────────────────────────────

📌 One-Line Mnemonic:
   "SPLIT HALF, SORT HALVES, MERGE SORTED HALVES"

   Every recursion: split in half → conquer → merge
   Keep doing until array is sorted!

───────────────────────────────────────────────────────────────────────────────

Comparison with Other Sorts:
┌──────────────┬─────────────┬───────────┬─────────────┬──────────────┐
│ Algorithm    │ Best Case   │ Avg Case  │ Worst Case  │ Stable? Space│
├──────────────┼─────────────┼───────────┼─────────────┼──────────────┤
│ Bubble Sort  │ O(n)        │ O(n²)     │ O(n²)       │ Yes  O(1)   │
│ Quick Sort   │ O(n log n)  │ O(n log n)│ O(n²)       │ No   O(log n)│
│ Merge Sort   │ O(n log n)  │ O(n log n)│ O(n log n)  │ Yes  O(n)   │
│ Heap Sort    │ O(n log n)  │ O(n log n)│ O(n log n)  │ No   O(1)   │
│ Insertion    │ O(n)        │ O(n²)     │ O(n²)       │ Yes  O(1)   │
└──────────────┴─────────────┴───────────┴─────────────┴──────────────┘

Merge Sort shines when:
  ✓ Guaranteed performance is needed
  ✓ Stability is required
  ✓ Space is available
  ✓ Sorting linked lists
  ✓ External sorting (huge files)

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 6️⃣  COMMON MISTAKES - Where Beginners Fail
└─────────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 1: Forgetting the BASE CASE
   Wrong: 
     void merge_sort(vector<int>& array, int low, int high) {
         int mid = low + (high - low) / 2;
         merge_sort(array, low, mid);        // ← Infinite recursion!
         merge_sort(array, mid + 1, high);
     }
   Problem: Function recurses forever → STACK OVERFLOW
   Fix: Always check if (low >= high) return;
   Lesson: Every recursive function MUST have a base case

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 2: Calculating midpoint unsafely
   Wrong: int mid = (low + high) / 2;
   Problem: For very large indices, low + high overflows!
            Example: low=2B, high=2B → sum=4B > INT_MAX
   Fix: int mid = low + (high - low) / 2;
   Lesson: This is a famous bug; always use this formula

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 3: Not using <= in merge (using <)
   Wrong: if (left_part[p1] < right_part[p2])
   Problem: Loses STABILITY! Equal elements change relative order
            Example: [3a, 3b] might become [3b, 3a]
   Fix: if (left_part[p1] <= right_part[p2])
   Lesson: Stability matters; use <= to pick from left on ties

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 4: Forgetting to copy remaining elements
   Wrong:
     while (p1 < n1 && p2 < n2) { ... merge ... }
     // Missing: while (p1 < n1) array[write_ind++] = left_part[p1++];
     // Missing: while (p2 < n2) array[write_ind++] = right_part[p2++];
   Problem: Some elements are never written back → MISSING DATA
            Example: Merging [5,6,7] and [1,2] loses 5,6,7!
   Fix: Add both while loops to copy remaining
   Lesson: After merge loop, exactly one cleanup loop executes

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 5: Wrong array range in recursion
   Wrong: merge_sort(array, low, mid) instead of merge_sort(array, low, mid-1)
   Problem: Elements get processed twice or skipped
            Infinite recursion or incorrect sort
   Fix: Ensure ranges are non-overlapping:
        Left:  [low...mid]
        Right: [mid+1...high]
   Lesson: Check that all elements are covered exactly once

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 6: Creating temp arrays INSIDE the merge, outside the loop
   Common Pattern Error: Allocating too many temp arrays
   Better: Allocate once per merge call (as shown in code)
   Lesson: Minimize allocations in hot loops

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 7: Merging in wrong order
   Wrong: merge() called BEFORE recursive merge_sort() calls
   Problem: Tries to merge unsorted halves → garbage output
   Fix: Recursively sort first, THEN merge
   Lesson: Post-order traversal: conquer children, then combine

───────────────────────────────────────────────────────────────────────────────

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 7️⃣  COMPLEXITY ANALYSIS - Deep Dive
└─────────────────────────────────────────────────────────────────────────────────

⏱️  TIME COMPLEXITY: O(n log n) GUARANTEED

Analysis:

1. RECURSION DEPTH:
   • Keep dividing array in half until size 1
   • n → n/2 → n/4 → ... → 1
   • Number of levels = log₂(n) = O(log n)

2. WORK AT EACH LEVEL:
   • Level 0: 1 merge operation on n elements = O(n)
   • Level 1: 2 merge operations on n/2 each = 2 × O(n/2) = O(n)
   • Level 2: 4 merge operations on n/4 each = 4 × O(n/4) = O(n)
   • ...
   • Level k: 2^k merges on n/2^k each = 2^k × O(n/2^k) = O(n)
   
   KEY INSIGHT: Every level does exactly O(n) work!

3. TOTAL TIME:
   Total = (# of levels) × (work per level)
   Total = O(log n) × O(n)
   Total = O(n log n) ✓

Why O(n log n) is GUARANTEED:
  • Same number of levels regardless of input (always log n)
  • Same work per level regardless of values (always n)
  • No worst case collapse like Quick Sort

Comparison:
  Bubble Sort:   O(n²)       ← 1 million elements = 1 trillion ops
  Quick Sort:    O(n²) worst ← might hit this with bad luck
  Merge Sort:    O(n log n)  ← 1 million = ~20 million ops ✓

───────────────────────────────────────────────────────────────────────────────

🧠 SPACE COMPLEXITY: O(n)

Analysis:

1. TEMPORARY ARRAYS:
   • In merge(): Create left_part (size n1) and right_part (size n2)
   • For each merge: Allocates n1 + n2 = O(n) temporary space
   • But only during one merge call at a time
   • After merge, temp arrays are freed (local scope)

2. RECURSION STACK:
   • Recursion depth: O(log n) levels
   • Each level adds stack frame: O(1) per frame
   • Total stack space: O(log n)

3. TOTAL SPACE:
   Temporary arrays: O(n) (only one merge active at a time)
   Call stack: O(log n)
   Total: O(n) + O(log n) = O(n) ✓

Why O(n) Space is Worth It:
  • O(n log n) sorting that's GUARANTEED and STABLE
  • Extra space is reasonable trade-off
  • Can't do guaranteed O(n log n) with O(1) space

Alternative Space Analysis:
  • In-place sorting (Heap Sort): O(n log n) time, O(1) space
  • But: Heap Sort is unstable, harder to implement on linked lists

Auxiliary Space Only:
  If counting only NEW space (not the array itself):
  • Temporary: O(n) 
  • Recursion: O(log n)
  • Total auxiliary: O(n) still

───────────────────────────────────────────────────────────────────────────────

Example Complexity Calculation:
Array size: 8 elements [3,1,4,1,5,9,2,6]

Level 0: 1 merge of 8 elements = 8 comparisons
Level 1: 2 merges of 4 elements each = 8 comparisons
Level 2: 4 merges of 2 elements each = 8 comparisons
Level 3: 8 merges of 1 element each = 0 comparisons (base case)

Total: 24 comparisons
Formula: n × log₂(n) = 8 × 3 = 24 ✓

For 1,000,000 elements:
  1,000,000 × log₂(1,000,000) ≈ 1,000,000 × 20 = 20,000,000 operations
  Compare to: 1,000,000² = 1,000,000,000,000 (Bubble Sort!) 

That's 50,000× faster! 🚀

───────────────────────────────────────────────────────────────────────────────

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 8️⃣  ALTERNATIVE APPROACHES - Only Explanation (No Code)
└─────────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 1: QUICK SORT
─────────────────────────────────────────────────────────────────────────────
Time: O(n log n) average, O(n²) worst  |  Space: O(log n)

Idea:
  • Pick a "pivot" element
  • Partition array: elements < pivot on left, >= pivot on right
  • Recursively sort left and right partitions
  • No explicit merge needed (partition IS the order)

Why Use This:
  ✓ Faster in practice (better cache locality)
  ✓ O(1) extra space (in-place partitioning)
  ✓ Often has good constants
  ✗ Worst case O(n²) (if pivot always smallest/largest)
  ✗ Not stable (equal elements change relative order)
  ✗ Unpredictable performance

When to Choose:
  • General-purpose sorting (std::sort uses it internally)
  • When space is critical
  • Average case performance is good enough

───────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 2: HEAP SORT
─────────────────────────────────────────────────────────────────────────────
Time: O(n log n) guaranteed  |  Space: O(1)

Idea:
  • Build max-heap from array
  • Repeatedly extract max element, place at end
  • Shrink heap and repeat until sorted
  • Uses heap property: parent >= children

Why Use This:
  ✓ O(n log n) guaranteed (like Merge Sort)
  ✓ O(1) space (in-place, no temporary arrays)
  ✓ Don't need stable sort
  ✗ Slower in practice (poor cache locality)
  ✗ Unstable
  ✗ Harder to understand than Merge Sort

When to Choose:
  • Need guaranteed O(n log n) with O(1) space
  • Sorting in embedded systems (memory limited)
  • When stability not required

───────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 3: INSERTION SORT
─────────────────────────────────────────────────────────────────────────────
Time: O(n²) average  |  Space: O(1)

Idea:
  • Start from second element
  • Insert each element into sorted portion (left side)
  • Shift larger elements right to make space

Why Use This:
  ✓ Simple to implement and understand
  ✓ O(1) space (in-place)
  ✓ O(n) best case (already sorted)
  ✓ Stable
  ✓ Good for nearly sorted data
  ✗ O(n²) average case (too slow)

When to Choose:
  • Small arrays (n < 50)
  • Nearly sorted arrays
  • Educational purposes
  • Embedded systems with extreme memory constraints

───────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 4: COUNTING SORT
─────────────────────────────────────────────────────────────────────────────
Time: O(n + k)  |  Space: O(k)  where k = range of integers

Idea:
  • Count frequency of each element
  • Reconstruct array based on counts
  • Don't compare elements at all!

Why Use This:
  ✓ Faster than O(n log n) for small integer ranges
  ✓ Linear time: O(n + k)
  ✓ Stable (if implemented carefully)
  ✗ Only works for integers or discrete values
  ✗ Wasteful if k >> n (e.g., range [1 to 1M] but only 10 elements)

When to Choose:
  • Sorting integers with limited range
  • Radix Sort (uses Counting Sort internally)
  • When elements are repeated frequently

───────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 5: MERGE SORT on LINKED LISTS
─────────────────────────────────────────────────────────────────────────────
Time: O(n log n)  |  Space: O(log n) [recursion stack only, no temp arrays!]

Idea:
  • Same merge sort logic
  • But operate on linked list nodes instead of array indices
  • Use slow/fast pointers to find middle
  • Merge by adjusting node pointers, no array allocation

Why Use This:
  ✓ O(n log n) guaranteed
  ✓ O(log n) space (no temporary arrays needed!)
  ✓ Stable
  ✓ Only sorting algorithm suitable for linked lists
  ✗ Slightly more complex code

When to Choose:
  • Sorting linked lists (THE algorithm)
  • When you want O(n log n) with minimal space on linked data

───────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 6: HYBRID APPROACH (Timsort)
─────────────────────────────────────────────────────────────────────────────
Time: O(n log n) average, O(n) best  |  Space: O(n)

Idea:
  • Use insertion sort on small "runs" (< 64 elements)
  • Merge the sorted runs (like Merge Sort)
  • Adaptive: exploits existing sorted sequences

Why Use This:
  ✓ Best practical performance (used in Python, Java!)
  ✓ Excellent on partially sorted data
  ✓ Stable
  ✗ Complex to implement
  ✗ O(n) space still

When to Choose:
  • Production-grade sorting library
  • Unknown data patterns (adaptive algorithm)

───────────────────────────────────────────────────────────────────────────────

INTERVIEW RECOMMENDATION FRAMEWORK:

"What should I use?"

  1. Quick Sort?
     • Best general purpose
     • Practical choice for most cases
     • Only use if O(n²) worst case acceptable

  2. Merge Sort?
     • Need GUARANTEED O(n log n)
     • Stability is required
     • Sorting linked lists (MUST USE THIS)
     • Space available

  3. Heap Sort?
     • Need guaranteed O(n log n) with O(1) space
     • Stability not required

  4. Insertion Sort?
     • Small arrays
     • Nearly sorted data
     • Space is critical

  5. Counting Sort?
     • Integer range is small
     • Want better than O(n log n)

Default: Quick Sort (99% of the time)
Exception: Merge Sort if any of above conditions met

*/

/*
═══════════════════════════════════════════════════════════════════════════════════
                              QUICK REFERENCE CARD
═══════════════════════════════════════════════════════════════════════════════════

ALGORITHM: Merge Sort (Divide-and-Conquer)
PROBLEM: Sort an array
TIME: O(n log n) - GUARANTEED
SPACE: O(n) - Temporary arrays + O(log n) recursion stack

PATTERN:
  merge_sort(array, low, high):
    1. IF low >= high: RETURN (base case)
    2. mid = low + (high - low) / 2
    3. merge_sort(left half)      [DIVIDE]
    4. merge_sort(right half)     [CONQUER]
    5. merge(two sorted halves)   [COMBINE]

  merge(array, low, mid, high):
    1. Create temp arrays for left and right halves
    2. Copy data from array to temp arrays
    3. Compare and merge back to original array (smaller element first)
    4. Copy any remaining elements

KEY POINTS:
  ✓ Must have base case (low >= high)
  ✓ Calculate mid safely: low + (high - low) / 2
  ✓ Use <= in comparison (for stability)
  ✓ Don't forget copy remaining elements loops
  ✓ Always merge AFTER recursive calls (post-order)

STABILITY: YES (uses <= not <)
IN-PLACE: NO (uses O(n) temporary space)
BEST CASE: O(n log n) [always same structure]
AVERAGE CASE: O(n log n)
WORST CASE: O(n log n) [guaranteed!]

WHEN TO USE:
  ✓ Need guaranteed O(n log n)
  ✓ Must be stable
  ✓ Sorting linked lists
  ✓ External sorting
  ✗ Space is critical (use Heap Sort instead)
  ✗ Already nearly sorted (use Insertion Sort)

COMMON BUGS:
  ✗ No base case → stack overflow
  ✗ Using (low + high) / 2 → integer overflow
  ✗ Using < instead of <= → loses stability
  ✗ Forgetting copy remaining elements → data loss
  ✗ Merging before recursion → unsorted data

═══════════════════════════════════════════════════════════════════════════════════
*/