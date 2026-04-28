// Problem Statement:



// Given an integer array nums, find the subarray with the largest sum and return its sum.



// Example : Leetcode Streak

// Rahul loves coding and wants to solve problems on LeetCode every day to improve his skills. Some days he solves many problems (+points), while on tough days, he struggles or skips (-points). To find his best streak, he uses Kadane’s algorithm, which helps track the highest consecutive score. Instead of checking all days manually, the algorithm smartly continues a streak or starts fresh when needed.



// Example 1:
// Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
// Output: 6
// Explanation: The subarray [4,-1,2,1] has the largest sum of 6.


// Example 2:
// Input: nums = [1]
// Output: 1
// Explanation: The subarray [1] has the largest sum 1.


// Example 3:
// Input: nums = [5, 4, 1, 7, 8]
// Output: 25
// Explanation: The subarray [5, 4, 1, 7, 8] has the largest sum of 25.


// Approach
// Using Kadane’s Algorithm :



// 1.    Kadane's Algorithm has two choices at every element :

// Add the current element to continue the current subarray.
// Start the new subarray, If the current element gives a higher value than the previous subarray sum.


// 2. It tracks the sum of the current subarray (currSum) and the highest sum found so far (maxSum).

// 3. Initialize currSum and maxSum to nums[0].

// 4. Iterate through the array, updating currSum to the maximum of:

// Starting a new subarray with nums[i], or
// Adding nums[i] to the current subarray.
// 5. Update maxSum with the larger of maxSum and currSum.

// 6. Return maxSum as the result.





// Dry Run 

// Final Answer:

// Maximum Subarray Sum = 6

// Time Complexity	Space Complexity
// O(n) 	O(1)


#include <iostream>
#include<vector>
using namespace std;
class Solution {
public:
   // ✅ KADANE'S ALGORITHM: Greedy approach to find maximum subarray sum
   // Core Idea: At each position, decide whether to extend the current subarray
   //            or start a fresh one (whichever gives maximum value)
   int maxSubArray(vector<int>& nums) {
       
       // 🔴 LINE 1: Initialize currSum with first element
       // ═══════════════════════════════════════════════════════════════════
       // WHAT: currSum tracks the maximum sum of subarray ENDING AT current position
       // WHY: We need a baseline. If we start with 0, negative numbers break logic
       //      Example: [-5,-2] should return -2, not 0
       // IF REMOVED: Would treat -5 as valid start, fail on all-negative arrays
       // EDGE CASE: Works for single element [5] because currSum = maxSum = 5
       int currSum = nums[0];   // Initialize current subarray sum
       
       // 🔴 LINE 2: Initialize maxSum with first element
       // ═══════════════════════════════════════════════════════════════════
       // WHAT: Stores the best answer found so far
       // WHY: We need to compare against something. nums[0] is the safest minimum
       // IF REMOVED: Would fail to track any maximum
       int maxSum = nums[0];    // Initialize maximum subarray sum
      
       // 🔴 LOOP: Two-choice decision at each element
       // ═══════════════════════════════════════════════════════════════════
       // Iterate through the array starting from the second element
       for (int i = 1; i < nums.size(); i++) {
           
           // 🔴 LINE 3: The HEART of Kadane's algorithm - make the decision
           // ═══════════════════════════════════════════════════════════════
           // WHAT: Chooses between two options:
           //       Option A: currSum + nums[i]  (extend existing subarray)
           //       Option B: nums[i]            (start fresh subarray)
           // WHY: If previous sum + current < current alone, previous subarray is dead weight
           //
           // STEP-BY-STEP DRY RUN on [-2, 1, -3, 4]:
           // ─────────────────────────────────────────
           // i=1, nums[1]=1:
           //   currSum = max(-2 + 1, 1) = max(-1, 1) = 1 ✓ (start fresh)
           //   maxSum = max(-2, 1) = 1
           //
           // i=2, nums[2]=-3:
           //   currSum = max(1 + (-3), -3) = max(-2, -3) = -2 ✓ (keep previous)
           //   maxSum = max(1, -2) = 1
           //
           // i=3, nums[3]=4:
           //   currSum = max(-2 + 4, 4) = max(2, 4) = 4 ✓ (start fresh)
           //   maxSum = max(1, 4) = 4
           //
           // Continuing this gives us 6 (which is max of [4,-1,2,1])
           //
           // IF REMOVED: Algorithm becomes broken - no decision point
           // 
           // EDGE CASES HANDLED:
           // ✓ All negative: Returns least negative (e.g., [-5,-2] → -2)
           // ✓ All positive: Returns sum of all (e.g., [1,2,3] → 6)
           // ✓ Mixed: Correctly skips negative subarrays
           currSum = max(currSum + nums[i], nums[i]);  // Two-choice: extend or restart
           
           // 🔴 LINE 4: Update global maximum after each decision
           // ═══════════════════════════════════════════════════════════════
           // WHAT: Keeps track of the BEST answer seen anywhere
           // WHY: currSum only represents ending at position i, not overall best
           //      We need to record whenever we find something better globally
           // IF REMOVED: maxSum stays at nums[0], misses all optimal subarrays
           //             Example: [-5,10] would return -5 instead of 10
           // TIME THIS EXECUTES: Every iteration (n times)
           maxSum = max(maxSum, currSum);  // Update global maximum
       }
      
       return maxSum;  // ✅ Return the best sum found during entire array traversal
   }
};


int main() {
   // Test case: Define an array of integers
   vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  
   Solution solution;  // Create an instance of the Solution class
   int result = solution.maxSubArray(nums);  // Call the maxSubArray function to find the max sum
  
   // Output the result
   cout << "The maximum subarray sum is: " << result << endl;
  
   return 0;  // Return 0 to indicate successful execution
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
   • Dynamic Programming / Greedy Algorithm
   • Contiguous Subarray Optimization
   • Single-pass traversal problem

📌 Key Characteristics to Identify:
   ✓ Find MAXIMUM/MINIMUM of contiguous elements
   ✓ ENTIRE array must be checked (no subset choice)
   ✓ Subarray must be contiguous (consecutive elements)
   ✓ Single array, single operation

🔑 Constraints That Matter:
   • Input can have negative, zero, and positive integers
   • At least 1 element guaranteed
   • Must return a number (not empty subarray allowed)
   • Linear time solution expected

❌ What This Problem IS NOT:
   • NOT subsequence (elements can be non-contiguous)
   • NOT longest subarray (we want maximum SUM, not length)
   • NOT subset selection (we can't skip elements in middle)

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 2️⃣  PATTERN RECOGNITION - How to Spot This in Future Interviews
└─────────────────────────────────────────────────────────────────────────────────

🎨 DSA Pattern Used: GREEDY + DYNAMIC PROGRAMMING

Where Kadane's Algorithm Appears:
┌────────────────────────────────────────────────────────────────┐
│ EXACT MATCHES (Use Kadane Directly):                          │
│ • Maximum subarray sum                                         │
│ • Maximum product subarray                                     │
│ • House Robber III variations                                  │
│                                                                │
│ PATTERN VARIATIONS (Modify Kadane):                           │
│ • Maximum circular subarray sum                               │
│ • Subarray with K distinct elements                           │
│ • Stock trading (Best Day to Buy/Sell)                        │
│ • Minimum subarray sum                                        │
│                                                                │
│ SIMILAR CONCEPTS (Related patterns):                          │
│ • Two pointers (sliding window)                               │
│ • Prefix sum (range queries)                                  │
│ • DP on arrays                                                │
└────────────────────────────────────────────────────────────────┘

🔍 Signals to Recognize This Pattern:
   Signal #1: "Find max/min SUM of CONTIGUOUS elements"
   Signal #2: "Need to compare subarray choices at each position"
   Signal #3: "Optimal decision depends on ONLY previous position"
   Signal #4: Problem asks for ONE scalar answer (not indices)

🧠 One-Line Memory Trick:
   "At each position, GREEDILY decide: keep growing or START FRESH"

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 3️⃣  APPROACH BREAKDOWN - Interview Style Evolution
└─────────────────────────────────────────────────────────────────────────────────

APPROACH 1: BRUTE FORCE (Show this first, then optimize)
═══════════════════════════════════════════════════════════════════════════════
Time: O(n²)  |  Space: O(1)

Logic:
  • Try every possible starting position (i=0 to n-1)
  • For each start, try every possible ending position (j=i to n-1)
  • Calculate sum for each subarray [i...j]
  • Keep track of maximum

Code Idea:
  int maxSum = INT_MIN;
  for (int i = 0; i < nums.size(); i++) {
      int currSum = 0;
      for (int j = i; j < nums.size(); j++) {
          currSum += nums[j];
          maxSum = max(maxSum, currSum);
      }
  }
  return maxSum;

Problem: Too slow for large arrays! Need faster solution.

────────────────────────────────────────────────────────────────────────────────

APPROACH 2: SLIGHTLY BETTER (Prefix Sums)
═══════════════════════════════════════════════════════════════════════════════
Time: O(n²) with preprocessing  |  Space: O(n)

Logic:
  • Precompute prefix sums
  • Use formula: sum(i,j) = prefix[j+1] - prefix[i]
  • Still O(n²) pairs to check

Problem: Still O(n²)! Can we do better?

────────────────────────────────────────────────────────────────────────────────

APPROACH 3: OPTIMAL - KADANE'S ALGORITHM ⭐⭐⭐
═══════════════════════════════════════════════════════════════════════════════
Time: O(n)  |  Space: O(1)

Key Insight: "At each position, we only care about TWO choices"
  • Do we EXTEND the previous subarray with current element?
  • Or do we START FRESH from current element?

WHY THIS APPROACH IS CHOSEN:
  ✓ Single pass through array
  ✓ Only track 2 variables (currSum, maxSum)
  ✓ O(1) space complexity
  ✓ Greedy: local optimal choice leads to global optimum
  ✓ Provably optimal (can't do better than O(n))

The "Greedy" Part:
  At each step, we make the locally best decision (extend or restart)
  and this magically gives the globally optimal answer.

Why Greedy Works Here:
  • Problem has "optimal substructure": answer contains optimal sub-solutions
  • Making best local choice doesn't block other choices
  • Example: If [4,-1,2,1] is optimal ending at i, taking [4,-1,2] is part of
    the optimal solution for smaller array

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 4️⃣  INTUITION BUILDING - Simple Explanation
└─────────────────────────────────────────────────────────────────────────────────

🎬 Thought Experiment - The Shopkeeper's Profit:

Imagine a shopkeeper tracking daily profit:
  Day 1: -$2 (loss)
  Day 2: +$1 (small gain)
  Day 3: -$3 (big loss)
  Day 4: +$4 (good recovery)
  Day 5: -$1 (small loss)
  Day 6: +$2 (gain)
  Day 7: +$1 (gain)
  Day 8: -$5 (big loss)
  Day 9: +$4 (recovery)

Question: "What's the best consecutive period to highlight to investors?"

Kadane's Insight: 
  • Start tracking from Day 1
  • Day 1-3: Running sum = -2, 1, -3 (not looking good)
  • Day 4: Should we trust the previous sum? -3 + 4 = 1? Or start fresh? 4!
    RESTART because 4 alone is better than carrying the -3 burden
  • Days 4-7: Running sum = 4, 3, 5, 6 (nice growth)
  • Day 8: -5 is heavy, so we'd consider dropping days if we continued
  • Day 9: +4, worth tracking

BEST PERIOD: Days 4-7 with profit $6

The Trick: "Don't carry dead weight - restart when burden gets too heavy"

───────────────────────────────────────────────────────────────────────────────

🧩 The Core Idea in 2 Sentences:

1. Keep running total of subarray sum ENDING at current position
2. At each position, GREEDILY choose: "Does adding current element beat 
   starting fresh? If not, forget the past and restart"

═══════════════════════════════════════════════════════════════════════════════

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 5️⃣  HOW TO RECALL LATER - Memory Anchors
└─────────────────────────────────────────────────────────────────────────────────

When You See a LeetCode Problem, Ask Yourself:

❓ Question 1: "Are we looking for CONTIGUOUS elements?"
   If YES → Could be Kadane

❓ Question 2: "Are we comparing SUM/PRODUCT/COUNT at each position?"
   If YES → Likely Kadane

❓ Question 3: "Do I only care about ENDING AT current position, 
                not starting before?"
   If YES → Definitely Kadane

───────────────────────────────────────────────────────────────────────────────

🎯 2-3 Key Signals to Identify:

   Signal 1: "Find maximum/minimum SUM"
   Signal 2: "Subarray must be CONTIGUOUS"
   Signal 3: Only 2 DP states matter (ending here vs starting here)

───────────────────────────────────────────────────────────────────────────────

📌 One-Line Mnemonic:
   "CARRY or RESTART - local choice, global answer"

   Every iteration: Is carrying the past worth it? If not, dump it.

───────────────────────────────────────────────────────────────────────────────

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 6️⃣  COMMON MISTAKES - Where Beginners Fail
└─────────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 1: Initializing maxSum to 0
   Wrong: int maxSum = 0;
   Problem: For array [-5, -2], returns 0 instead of -2
   Fix: Use INT_MIN or nums[0]
   Lesson: Negative-only arrays are valid inputs

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 2: Updating maxSum BEFORE updating currSum
   Wrong: 
      maxSum = max(maxSum, currSum);
      currSum = max(currSum + nums[i], nums[i]);
   Problem: Uses stale currSum value
   Fix: Update currSum first, THEN maxSum
   Lesson: Order matters in DP - state must be updated before comparison

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 3: Starting loop from i=0 instead of i=1
   Wrong: for (int i = 0; i < nums.size(); i++)
   Problem: currSum is already nums[0], recalculate wastes iteration
   Fix: Start from i=1
   Lesson: Initialization is part of the algorithm

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 4: Using addition instead of max()
   Wrong: currSum = currSum + nums[i];  (missing the max decision!)
   Problem: Never restarts, treats all subarrays equally
   Example: [-5, 10] would give -5+10=5 instead of 10
   Fix: currSum = max(currSum + nums[i], nums[i]);
   Lesson: This is THE core decision of algorithm

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 5: Confusing "subarray ending here" vs "best subarray overall"
   Common Error: Thinking currSum is the answer
   Wrong: return currSum;
   Problem: currSum only represents ENDING at last position, not overall best
   Example: [5, 1, -10, 1] → currSum=-8 but maxSum=5
   Fix: return maxSum;
   Lesson: Maintain TWO separate state variables for different meanings

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 6: Forgetting about edge cases during explanation
   Problem: In interview, explaining only happy path
   Missing: Single element, all negatives, all positives, zeros
   Fix: Always trace through edge cases mentally
   Lesson: Robustness matters in interviews

───────────────────────────────────────────────────────────────────────────────

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 7️⃣  COMPLEXITY ANALYSIS - Deep Dive
└─────────────────────────────────────────────────────────────────────────────────

⏱️  TIME COMPLEXITY: O(n)

Analysis:
  • Initialization: O(1) - just assign nums[0]
  • Loop: Runs exactly (n-1) times
    - Each iteration: O(1) operations
      → max(currSum + nums[i], nums[i]) = O(1)
      → max(maxSum, currSum) = O(1)
  • Return: O(1)
  
  Total: O(1) + O(n) + O(1) = O(n) ✓

Why Linear Time is Optimal:
  • We MUST examine every element at least once
  • Each element could potentially be the answer (in all-positive case)
  • No data structure can help us skip checking elements
  • Lower bound is Ω(n), so O(n) is optimal

Comparison:
  Brute Force:   O(n²)  ← check all pairs of (i, j)
  Prefix Sum:    O(n²)  ← still check all pairs
  Kadane:        O(n)   ← linear single pass ✓

───────────────────────────────────────────────────────────────────────────────

🧠 SPACE COMPLEXITY: O(1)

Analysis:
  • currSum: 1 integer
  • maxSum: 1 integer
  • Loop variable i: 1 integer
  • No additional data structures used
  • No recursion (no call stack)
  
  Total: O(1) constant space ✓

Space Advantages:
  ✓ Can handle very large arrays
  ✓ Suitable for embedded systems, IoT
  ✓ In-place algorithm (doesn't modify input)

───────────────────────────────────────────────────────────────────────────────

🎯 Why This Complexity is Great:
  • Linear time: You cannot do better (must see each element)
  • Constant space: Optimal space efficiency
  • Single pass: Cache-friendly, practical

───────────────────────────────────────────────────────────────────────────────

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 8️⃣  ALTERNATIVE APPROACHES - Only Explanation (No Code)
└─────────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 1: DIVIDE AND CONQUER
─────────────────────────────────────────────────────────────────────────────
Time: O(n log n)  |  Space: O(log n) [recursion stack]

Idea:
  • Split array into left and right halves
  • Recursively find max subarray in each half
  • Find max subarray that CROSSES the middle
  • Return maximum of all three cases

Why Use This:
  ✓ Great interview teaching tool (show understanding of recursion)
  ✓ Parallelizable (can split work across processors)
  ✗ Slower than Kadane (O(n log n) vs O(n))
  ✗ Uses extra space for recursion

When to Choose: Teaching context, or when you need parallelization

───────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 2: DYNAMIC PROGRAMMING (Formal DP Approach)
─────────────────────────────────────────────────────────────────────────────
Time: O(n)  |  Space: O(n)

Idea:
  • Define DP state: dp[i] = maximum sum of subarray ending at index i
  • Recurrence: dp[i] = max(nums[i], dp[i-1] + nums[i])
  • Answer: max(dp[0...n-1])
  • Maintain dp array instead of single variable

Why Use This:
  ✓ More formal DP structure (good for explaining to interviewers)
  ✓ Easier to extend to variants (e.g., maximum product)
  ✗ Uses O(n) extra space (Kadane uses O(1))
  ✓ But same O(n) time

Optimization:
  Notice we only need dp[i-1] for each step → optimize to Kadane!

───────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 3: PREFIX SUM + HASH SET/MAP
─────────────────────────────────────────────────────────────────────────────
Time: O(n²) basic, O(n) advanced  |  Space: O(n)

Idea:
  • Build prefix sum array
  • For each pair of indices (i,j), calculate sum as prefix[j]-prefix[i]
  • Basic version: Check all pairs (O(n²))
  • Advanced: Use hash map to track seen prefix sums

Why NOT Use This:
  ✗ Slower or equal to Kadane
  ✗ More space
  ✓ But useful for other problems (subarray sum to target K)

When to Consider: If problem adds constraint like "sum must equal K"

───────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 4: MAXIMUM CIRCULAR SUBARRAY (Variant)
─────────────────────────────────────────────────────────────────────────────
Time: O(n)  |  Space: O(1)

Idea:
  • Run Kadane once for max subarray (non-circular)
  • Find total sum of array
  • Find MINIMUM subarray (using modified Kadane)
  • Circular max = total - minimum
  • Handle edge case: if all negative, return max subarray

Why Study This:
  ✓ Shows deep understanding of Kadane
  ✓ Common variant in interviews
  ✓ Real-world: Circular buffer problems

───────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 5: MAXIMUM PRODUCT SUBARRAY (Variant)
─────────────────────────────────────────────────────────────────────────────
Time: O(n)  |  Space: O(1)

Idea:
  • Can't simply use max for products (negatives flip signs!)
  • Track both maximum AND minimum ending at each position
  • minSum helps because negative × negative = positive
  • State: (maxProduct, minProduct)

Why Different from Sum:
  ✗ Kadane directly won't work for products
  ✓ Need to track BOTH max and min
  ✓ Common interview follow-up question

───────────────────────────────────────────────────────────────────────────────

RECOMMENDATION FOR INTERVIEWS:
  1. Start with Kadane's algorithm (easiest, O(n) + O(1))
  2. Mention brute force as warm-up (shows thinking process)
  3. If asked for alternatives, explain Divide & Conquer
  4. If time, mention variants (circular, product, minimum)
  5. Always discuss space-time tradeoffs

*/

/*
═══════════════════════════════════════════════════════════════════════════════════
                              QUICK REFERENCE CARD
═══════════════════════════════════════════════════════════════════════════════════

ALGORITHM: Kadane's Algorithm (Greedy)
PROBLEM: Maximum Subarray Sum
TIME: O(n) - Optimal
SPACE: O(1) - Optimal

CORE IDEA:
  currSum = max(currSum + nums[i], nums[i])  // Extend or restart?
  maxSum = max(maxSum, currSum)               // Track global best

KEY VARIABLES:
  currSum → Best sum ENDING at position i
  maxSum  → Best sum FOUND SO FAR

INIT: Both = nums[0]
LOOP: i = 1 to n-1
RETURN: maxSum

WHEN TO USE:
  ✓ Maximum sum of contiguous subarray
  ✓ Minimum sum of contiguous subarray
  ✓ Maximum product of contiguous subarray
  ✓ Best buying/selling stock price

EDGE CASES TO CHECK:
  ✓ Single element: [5]
  ✓ All negative: [-5, -2]
  ✓ All positive: [1, 2, 3]
  ✓ Mixed: [-2, 1, -3, 4, -1, 2, 1, -5, 4]

═══════════════════════════════════════════════════════════════════════════════════
*/


