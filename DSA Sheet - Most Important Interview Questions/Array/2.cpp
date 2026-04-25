#include <iostream>
#include<vector>
using namespace std;
class Solution {
public:
    // PROBLEM: Given an array of stock prices, find max profit from one buy-sell transaction
    // CONSTRAINT: Must buy BEFORE selling (buy on day i, sell on day j where i < j)
    // KEY INSIGHT: For each price, we need the minimum price seen BEFORE it
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        
        // WHAT: Store the cheapest price seen so far (best buying opportunity)
        // WHY: To calculate profit when we sell at current price: profit = currentPrice - bestBuyPrice
        // BREAK IF REMOVED: We'd lose track of minimum, can't compare with current price efficiently
        // EDGE CASE HANDLED: If prices empty (n=0), this doesn't initialize, but that's invalid input
        int bestBuy = prices[0];
        
        // WHAT: Track the maximum profit found so far
        // WHY: We need to return the best profit across ALL possible transactions
        // BREAK IF REMOVED: We'd only return last transaction's profit, not the maximum
        // EDGE CASE: Starts at 0 (no transaction = 0 profit, handles decreasing prices)
        int profit = 0;

        // LOOP LOGIC:
        // - Start from index 1 (can't buy and sell on same day)
        // - For each price, consider it as a SELLING point
        // - Calculate profit if we sell at this price using the best buying price found so far
        // - Update bestBuy if current price is cheaper than what we've seen
        // - Update profit if this transaction beats our previous best
        for (int i = 1; i < n; i++) {
            // DRY RUN on prices = [7, 1, 5, 3, 6, 4]:
            // i=1: price=1, bestBuy=min(7,1)=1, profit=max(0, 1-7)=0
            // i=2: price=5, bestBuy=min(1,5)=1, profit=max(0, 5-1)=4
            // i=3: price=3, bestBuy=min(1,3)=1, profit=max(4, 3-1)=4
            // i=4: price=6, bestBuy=min(1,6)=1, profit=max(4, 6-1)=5
            // i=5: price=4, bestBuy=min(1,4)=1, profit=max(5, 4-1)=5
            // RESULT: 5 (buy at 1, sell at 6)
            
            // WHAT: Update the minimum price seen so far
            // WHY: We always want to compare with the CHEAPEST price before current
            // BREAK IF REMOVED: bestBuy stays constant, won't find truly minimum price
            // EDGE CASE: min() handles equal prices correctly (doesn't matter which 1 we use)
            bestBuy = min(bestBuy, prices[i]);

            // WHAT: Calculate profit if we sell at current price with best buying price
            // WHY: Check if this sell point gives us a better profit than before
            // BREAK IF REMOVED: We'd never update profit, always return 0
            // FORMULA: profit = sellingPrice - buyingPrice (buy low, sell high)
            // EDGE CASE: If current price < bestBuy, profit is negative, max() keeps previous
            profit = max(profit, prices[i] - bestBuy);
        }
        return profit;
    }
};

int main() {
    // your code here
    return 0;
}

/*
================================================================================
                    COMPREHENSIVE PROBLEM ANALYSIS
================================================================================

1. 🧠 PROBLEM UNDERSTANDING
================================================================================
TYPE: 
  - Array optimization problem
  - Single-pass greedy algorithm
  - Real-world application: Stock trading

PROBLEM STATEMENT:
  Given an array where prices[i] = stock price on day i, find the maximum 
  profit you can achieve with ONE buy-sell transaction (you must buy BEFORE sell).

KEY CONSTRAINTS & CLUES:
  - "ONE transaction" = Buy once, sell once, then DONE
  - "Buy BEFORE sell" = prices[i] must come before prices[j] where i < j
  - Prices can be NEGATIVE, ZERO, or positive numbers (edge case: all decreasing)
  - Must maximize profit OR return 0 if profit impossible (can't sell at loss)
  - Single pass opportunity = No nested loops needed

================================================================================

2. 🔍 PATTERN RECOGNITION
================================================================================
DSA PATTERN USED: 
  → "Track Minimum While Traversing" or "State Machine with Single Pass"
  → NOT Dynamic Programming (DP not needed here)
  → NOT Two Pointer or Sliding Window (those are for constraints on window size)
  → This is GREEDY + State Tracking

HOW TO RECOGNIZE THIS PATTERN IN FUTURE PROBLEMS:
  
  1️⃣ SIGNAL: "Find maximum/minimum profit/difference from pairs (i,j) where i < j"
     → Keyword: "before", "prior", "preceding", "left of"
  
  2️⃣ SIGNAL: "Single pass through array" or "Can't look ahead"
     → You need to track the BEST PREVIOUS STATE while moving forward
  
  3️⃣ SIGNAL: "Compare current element with best element seen so far"
     → Use a variable to store the best state, update it as you traverse
  
  Recognition in future: If problem asks for "maximum/minimum profit from 
  any pair where i < j", ask: "Can I track the minimum left of current 
  position?" → If YES, use this pattern!

================================================================================

3. ⚡ APPROACH BREAKDOWN (INTERVIEW STYLE)
================================================================================

APPROACH 1: BRUTE FORCE (What most beginners think)
────────────────────────────────────────────────
- For every price as buying point:
  - For every price AFTER it as selling point:
    - Calculate profit, track maximum
- Time: O(n²) - Two nested loops
- Space: O(1)
- Problem: TOO SLOW for large inputs, wastes comparisons

  Example: prices = [7, 1, 5]
  - Buy at 7: check sell at 1 (loss -6), 5 (loss -2) → worst = -2
  - Buy at 1: check sell at 5 (profit +4) → best = 4
  - Buy at 5: no future sells → skip
  Result: 4 ✓ (correct but inefficient)


APPROACH 2: BETTER (Optimization insight)
──────────────────────────────────────────
- Insight: "I don't need to check every buy-sell pair!"
- Instead: "At each selling price, I just need the MINIMUM buy price 
  seen BEFORE it"
- This reduces nested loop to single loop!
- Time: O(n) - One pass
- Space: O(1)
- Key insight: "Minimum to the left can be tracked as we go"


APPROACH 3: OPTIMAL (THE SOLUTION)
──────────────────────────────────
- THIS IS THE BETTER APPROACH (already optimal)
- Single pass through array:
  1. Track minimum price seen so far (best buying price)
  2. For each current price (potential selling price):
     - Calculate profit using best buy price
     - Update best buy if current is cheaper
     - Update max profit if this transaction is better
- Time: O(n) - Single loop, O(1) operations per iteration
- Space: O(1) - Only two variables (bestBuy, profit)

WHY THIS IS CHOSEN:
  → Linear time complexity (can't do better than O(n))
  → Constant space (optimal space usage)
  → Single pass (cache-friendly, practical)
  → Easy to extend to other similar problems

================================================================================

4. 🧩 INTUITION BUILDING
================================================================================

CORE IDEA (Explain in Simple Terms):
────────────────────────────────────
Imagine you're looking at stock prices day by day:
  Day 1: Price = $7  (best buy so far: $7)
  Day 2: Price = $1  (best buy so far: $1) ← Update! This is cheaper
  Day 3: Price = $5  (best buy so far: $1) ← Don't update, already have $1
         Profit if sell today: $5 - $1 = $4 ← New best profit!
  Day 4: Price = $3  (best buy so far: $1)
         Profit if sell today: $3 - $1 = $2 ← Keep previous best ($4)
  Day 5: Price = $6  (best buy so far: $1)
         Profit if sell today: $6 - $1 = $5 ← New best profit!

THE "TRICK" OR KEY INSIGHT:
───────────────────────────
❌ WRONG WAY: Check every possible buy-sell pair = O(n²) combinations
✓ CORRECT WAY: "At each selling price, only care about minimum buy price 
               BEFORE it, which I can track as I go"

This insight transforms O(n²) → O(n) by observing:
  - You don't need to store all prices, just the minimum seen so far
  - When you see a new price, you instantly know if it's a good sell point
  - If you find a new minimum, future sells can only benefit from it

THE MENTAL MODEL:
─────────────────
Think of it as running two "pointers" mentally:
  - LEFT pointer: "What's the cheapest I could have bought so far?" (minimum)
  - RIGHT pointer: "What price can I sell at today?" (current)
  - Profit = RIGHT - LEFT

As you move RIGHT forward, you update what you know about LEFT to always be 
the absolute minimum you've seen.

================================================================================

5. 🔁 HOW TO RECALL LATER
================================================================================

KEY SIGNALS TO IDENTIFY THIS PROBLEM AGAIN:
─────────────────────────────────────────

  1️⃣ "Max profit from buying once and selling once"
     → Think: Need minimum before each position

  2️⃣ "Compare element with best element BEFORE it"
     → Think: Single pass, track best so far

  3️⃣ "Order matters (i must come before j)"
     → Think: Can't compare randomly, must be sequential


ONE-LINE MEMORY TRICK:
──────────────────────
"Track minimum while finding maximum profit"

Or: "For each sell price, buy at the cheapest price you've seen so far"

Or: "One pass problem: maintain best-buy-so-far while calculating sell-profit"

================================================================================

6. ⚠️ COMMON MISTAKES
================================================================================

MISTAKE 1: Initializing with wrong values
───────────────────────────────────────────
❌ WRONG:
    int bestBuy = INT_MAX;  // Too high
    int profit = INT_MIN;   // Can cause overflow issues

✓ CORRECT:
    int bestBuy = prices[0];  // Actual first price
    int profit = 0;           // No profit initially (base case)

WHY: INT_MAX causes issues when comparing. prices[0] is real and safe.


MISTAKE 2: Starting loop from index 0
──────────────────────────────────────
❌ WRONG:
    for (int i = 0; i < n; i++) {  // Can't sell on day 0 if you buy day 0
        bestBuy = min(bestBuy, prices[i]);
        profit = max(profit, prices[i] - bestBuy);
    }

✓ CORRECT:
    for (int i = 1; i < n; i++) {  // Start from day 1 (after buy on day 0)

WHY: Can't buy and sell on the SAME day. Must be different days.


MISTAKE 3: Not handling decreasing array
──────────────────────────────────────────
❌ Thinking: "What if prices only go down? My code will break!"

✓ REALITY: Code handles it perfectly!
    prices = [7, 6, 5, 4, 3]
    - bestBuy keeps updating to smaller values
    - profit stays 0 (because prices[i] - bestBuy is always ≤ 0)
    - Returns 0 (correct: can't profit if all prices fall)


MISTAKE 4: Not updating bestBuy BEFORE calculating profit
──────────────────────────────────────────────────────────
❌ WRONG ORDER:
    profit = max(profit, prices[i] - bestBuy);  // Use old bestBuy
    bestBuy = min(bestBuy, prices[i]);           // Update after

✓ CORRECT ORDER:
    bestBuy = min(bestBuy, prices[i]);           // Update first
    profit = max(profit, prices[i] - bestBuy);   // Use updated value

WHY: Order doesn't actually matter for correctness here (you're comparing with
PREVIOUS prices), but doing update FIRST is cleaner and matches intuition:
"See if current price is cheapest, then calculate profit with that knowledge"


MISTAKE 5: Trying to track both buy and sell day separately
──────────────────────────────────────────────────────────────
❌ OVER-COMPLICATION:
    int buyDay = 0;
    int sellDay = 0;
    for (int i = 1; i < n; i++) {
        // Track both days... unnecessary complexity
    }

✓ SIMPLE:
    int bestBuy = prices[0];  // We don't need the DAY, just the PRICE
    profit = max(profit, prices[i] - bestBuy);

WHY: Problem asks for "maximum profit", not "which days to buy/sell"
If you only need profit, don't store unnecessary info.


MISTAKE 6: Using floating point instead of integer
─────────────────────────────────────────────────
❌ WRONG:
    double bestBuy = prices[0];
    double profit = 0.0;

✓ CORRECT:
    int bestBuy = prices[0];
    int profit = 0;

WHY: Prices are integers. Using double causes precision issues and 
unnecessary overhead.

================================================================================

7. 📊 COMPLEXITY ANALYSIS
================================================================================

TIME COMPLEXITY: O(n)
─────────────────────
Reasoning:
  - Loop runs from i = 1 to i = n-1: exactly (n-1) iterations
  - Inside loop:
    * bestBuy = min(bestBuy, prices[i])  → O(1) comparison
    * profit = max(profit, prices[i] - bestBuy) → O(1) arithmetic
  - Total: O(n) × O(1) = O(n)

Analysis by input size:
  - prices = [1, 2]       → 1 iteration → O(1)
  - prices = [1, 2, 3]    → 2 iterations → O(n)
  - prices = [1...1000]   → 999 iterations → O(n)

This is OPTIMAL for this problem because:
  - You must look at every price at least once (lower bound = O(n))
  - Our solution does exactly that, nothing more
  - Can't do better than O(n)


SPACE COMPLEXITY: O(1)
──────────────────────
Reasoning:
  - bestBuy: single integer variable → O(1)
  - profit: single integer variable → O(1)
  - No arrays, vectors, or data structures created → O(1)
  - Recursion depth: none → O(1)
  - Total extra space: O(1)

Notes:
  - Input vector prices[]: Not counted (given as input)
  - If you need to MODIFY the array or return multiple values, space may change


SPACE vs TIME TRADEOFF:
─────────────────────
Could we optimize space further? NO ✗
  - We already use O(1) space (minimum possible)
  - Can't optimize time further either: O(n) is lower bound

Could we trade space for time? No benefit here
  - We're already O(n) time with O(1) space (best possible)
  - Adding hash maps or other structures would hurt, not help

================================================================================

8. 🔄 ALTERNATIVE APPROACHES
================================================================================

APPROACH A: DYNAMIC PROGRAMMING (Not optimal for this problem)
──────────────────────────────────────────────────────────────
Idea: Use DP table to store "max profit if we sold at day i"

How it works:
  - dp[i] = maximum profit if we sell at day i
  - For each day i: dp[i] = max(prices[i] - min_price_before_i)
  - Answer: max(dp[0], dp[1], ..., dp[n-1])

Complexity:
  - Time: O(n) (same as greedy)
  - Space: O(n) (need DP array, worse than greedy)

Why NOT use this:
  - Creates O(n) space when O(1) sufficient
  - More complex to write and understand
  - Not faster than greedy approach
  
When to use: If problem requires showing "all possible profits" or building
on DP table for multi-transaction variants.


APPROACH B: PREFIX ARRAY (Another alternative)
───────────────────────────────────────────────
Idea: Pre-compute prefix minimum, then compare each price with it

How it works:
  1. Create prefix_min[] where prefix_min[i] = minimum price from 0 to i
  2. For each i, profit[i] = prices[i] - prefix_min[i]
  3. Return max(profit[])

Complexity:
  - Time: O(n) for prefix + O(n) for max = O(n)
  - Space: O(n) for prefix array

Why NOT use this:
  - Uses extra O(n) space (wasteful)
  - Two separate passes instead of single optimized pass
  - Harder to extend or modify logic

When to use: Educational purpose, or when you need to work with multiple
solutions (e.g., "profit at each day" for visualization).


APPROACH C: DIVIDE & CONQUER (Overthinking)
────────────────────────────────────────────
Idea: Split array, find max profit in left & right, combine

How it works:
  - Split array at middle
  - Recursively find max profit in left half
  - Recursively find max profit in right half
  - Find max profit across split (buy in left, sell in right)

Complexity:
  - Time: O(n log n) - worse than greedy!
  - Space: O(log n) - recursion stack

Why NOT use this:
  - Slower than greedy approach
  - Over-engineered for simple problem
  - Harder to implement and debug

When to use: Problems where elements in left half and right half are truly
independent (this problem, they're NOT).


APPROACH D: SEGMENT TREE (Total Overkill)
──────────────────────────────────────────
Idea: Build segment tree to query minimum in any range in O(log n)

This is WAY overengineered for single-pass problem.
- Time: O(n log n) build + O(n log n) queries = O(n log n)
- Space: O(n) for tree structure

When to use: If problem requires "multiple queries" on different arrays
(this isn't that problem).


WHY GREEDY IS BEST:
═══════════════════
✓ Time: O(n) - optimal
✓ Space: O(1) - optimal
✓ Simple: Just 5 lines of code
✓ Fast in practice: Cache-friendly, minimal operations
✓ Elegant: Directly maps problem logic to code

Lesson: Not all problems need complex algorithms. Look for simplest
approach that solves in optimal complexity. Greedy + Single Pass 
wins here!

================================================================================
                            END OF ANALYSIS
================================================================================
*/