#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // PROBLEM: Find ALL unique combinations from 'candidates' that sum to 'target'
    // CONSTRAINT: Each element in candidates can be used AT MOST ONCE
    // KEY: Array may contain duplicates, but result should have UNIQUE combinations
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        // STEP 1: SORT THE ARRAY
        // WHAT: Rearrange elements in ascending order
        // WHY: Essential for two reasons:
        //      1. Identify duplicates easily (adjacent equal elements)
        //      2. Enable early termination (if current > target, all future > target)
        // BREAK IF REMOVED: Can't skip duplicates efficiently, can't prune early
        // EXAMPLE: [10,1,2,7,6,1,5] → [1,1,2,5,6,7,10]
        //          Duplicates (two 1's) are now adjacent, easy to skip
        sort(candidates.begin(), candidates.end());
        
        // WHAT: Will store final answer (all valid combinations)
        // WHY: Need to return all found combinations
        // EDGE CASE: Empty vector if no combinations found (e.g., target=5, candidates=[10,20])
        vector<vector<int>> result;
        
        // WHAT: Temporary vector to build CURRENT combination
        // WHY: As we explore, we build combinations here, then backtrack
        // ANALOGY: Like a notepad - write numbers, when done recording a path,
        //          erase the last number and try another path
        vector<int> pair;
        
        // START RECURSION: From index 0, trying to reach 'target'
        // WHAT: Launch DFS (Depth-First Search) backtracking exploration
        // WHY: Need to explore ALL possible paths to all combinations
        // PATTERN: Backtracking = DFS + state management + undo changes (pop_back)
        findCandidates(0, target, candidates, pair, result);
        
        return result;
    }

    // RECURSIVE HELPER FUNCTION
    // PARAMETERS:
    //   ind       = starting index (to avoid using same element twice)
    //   target    = remaining sum needed
    //   candidates = original array
    //   pair      = current combination being built
    //   result    = all valid combinations found so far
    void findCandidates(int ind, int target, vector<int>& candidates,
                        vector<int>& pair, vector<vector<int>>& result) {
        
        // BASE CASE: Found a valid combination!
        // WHAT: If remaining target is 0, we've successfully summed to target
        // WHY: This is our success condition - save this combination and stop exploring
        // BREAK IF REMOVED: Would continue exploring even after finding valid combo
        // DRY RUN on candidates=[1,1,2,5,6,7], target=8:
        //      When target=0: pair might be [1,2,5], add to result
        //      Return to let other paths be explored
        if (target == 0) {
            result.push_back(pair);  // SAVE the found combination
            return;  // STOP exploring this path (can't add more positives)
        }

        // LOOP: Try each element starting from 'ind' as the next candidate
        // WHAT: Iterate through remaining elements to pick next number
        // WHY: Explore all possibilities - each element could be next in combination
        // RANGE: Start from 'ind' (not 0) to avoid revisiting elements
        // EDGE CASE: If ind >= candidates.size(), loop doesn't execute (base case hit)
        for (int i = ind; i < candidates.size(); i++) {
            
            // DUPLICATE SKIPPING CONDITION
            // WHAT: Skip this element if it's same as previous AND not the first choice
            // WHY: Prevent DUPLICATE combinations
            // CONDITION: (i > ind) ensures we only skip if this isn't first element tried
            //            For example, if we have [1, 1, 2]:
            //            - When i=1 (first 1): i > ind is false (1 > 0 is false), process it
            //            - When i=2 (second 1): i > ind is true (2 > 0 is true) AND it's same
            //              as i-1, SKIP it (otherwise we'd get duplicate combinations)
            // BREAK IF REMOVED: Get duplicate combinations
            // EXAMPLE: candidates=[1,1,2], target=3
            //          Without this check: [1,2], [1,2] (DUPLICATE!)
            //          With this check: [1,2] (ONLY ONCE)
            if (i > ind && candidates[i] == candidates[i - 1]) {
                continue;  // Skip this duplicate element
            }

            // PRUNING CONDITION (Optimization)
            // WHAT: If current element exceeds remaining target, stop loop
            // WHY: Since array is SORTED, if candidates[i] > target, ALL future 
            //      candidates[i+1], candidates[i+2]... will also exceed target
            // BREAK IF REMOVED: Still works correctly, but slower (checks unnecessary elements)
            // EXAMPLE: candidates=[1,2,5,10,15], target=3
            //          When i=3 (value 10): 10 > 3, BREAK
            //          No need to check 15 (we know it's also > 3)
            if (candidates[i] > target) {
                break;  // No point checking further (all are larger)
            }

            // CHOOSE: Add current element to combination
            // WHAT: Include candidates[i] in our current path
            // WHY: We're exploring "what if we pick this element?"
            pair.push_back(candidates[i]);

            // EXPLORE: Recursively find more elements to complete combination
            // WHAT: Make recursive call with:
            //       - ind = i+1 (NEXT index, can't reuse current element)
            //       - target = target - candidates[i] (reduce remaining sum)
            //       - same candidates array
            //       - same pair (being built)
            //       - same result (accumulating answers)
            // WHY: This is DEPTH-FIRST exploration - go deep into one path first
            // KEY INSIGHT: i+1 ensures each element used AT MOST ONCE (not i, but i+1)
            // DIFFERENCE FROM COMBINATION_SUM_I: 
            //       CombinationSum1 uses 'i' (can reuse same element)
            //       CombinationSum2 uses 'i+1' (can't reuse)
            // DRY RUN on candidates=[1,1,2], target=3, starting at (0, 3):
            //       i=0, candidates[0]=1: pair=[1], recurse(1, 2)
            //           i=1, candidates[1]=1: pair=[1,1], recurse(2, 1)
            //               i=2, candidates[2]=2: 2>1, break
            //               return (target never reached)
            //           i=2, candidates[2]=2: pair=[1,2], recurse(3, 0)
            //               target=0, save [1,2], return
            //       i=1, candidates[1]=1: SKIP (duplicate: i > ind && candidates[1]==candidates[0])
            //       i=2, candidates[2]=2: pair=[2], recurse(3, 1)
            //           i=3, out of bounds, loop ends
            //           target!=0, return
            // RESULT: [[1,2]]
            findCandidates(i + 1, target - candidates[i], candidates, pair, result);

            // UNCHOOSE: Remove the element (BACKTRACK)
            // WHAT: Pop the last element from pair
            // WHY: CRITICAL for backtracking! After exploring all paths WITH this element,
            //      we need to remove it to try other elements at same level
            // ANALOGY: "Undo your move before trying a different move"
            // BREAK IF REMOVED: All combinations would have all elements (wrong answer!)
            // PATTERN: Every pair.push_back() MUST have corresponding pair.pop_back()
            // EXECUTION TRACE:
            //      Entered with pair=[1,2]
            //      Made recursive call
            //      Returned from recursive call
            //      Now pair=[1,2], pop_back()
            //      Now pair=[1], ready for next iteration
            pair.pop_back();
        }
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
  - Backtracking / Recursion problem
  - Combination generation with constraints
  - Real-world app: Finding all valid paths, generating candidates, constraint satisfaction

PROBLEM STATEMENT:
  Given an array 'candidates' and an integer 'target', find ALL unique combinations 
  where the combined sum equals target. Each element in candidates can be used 
  AT MOST ONCE. Candidates array may contain duplicates.

KEY CONSTRAINTS & CLUES:
  ✓ "ALL unique combinations" = Exhaustive search + avoid duplicates
  ✓ "Each used AT MOST ONCE" = Can't reuse same element (unlike CombinationSum1)
  ✓ "May contain duplicates" = Need to skip duplicate choices
  ✓ "Sum to target" = Early termination when target exceeded
  
EXAMPLE:
  Input: candidates = [10,1,2,7,6,1,5], target = 8
  Output: [
            [1,1,6],
            [1,2,5],
            [1,7],
            [2,6]
          ]
  
  Note: [1,1,6] appears ONCE (not twice despite two 1's in input)

================================================================================

2. 🔍 PATTERN RECOGNITION
================================================================================
DSA PATTERN USED:
  → BACKTRACKING + DFS (Depth-First Search)
  → Also called: "Decision Tree Exploration" or "Search with State Restoration"

CORE PATTERN:
  1. Choose (try adding current element)
  2. Explore (recurse with updated state)
  3. Unchoose (remove element, try next option)

RECOGNIZING THIS IN FUTURE PROBLEMS:
  
  1️⃣ SIGNAL: "Find ALL combinations/permutations/subsets with certain property"
     Keywords: "all solutions", "all possible", "generate all", "every combination"
     → Think: Backtracking needed
  
  2️⃣ SIGNAL: "Each element used AT MOST ONCE"
     Keywords: "use once", "no reuse", "each element in", "no duplicates"
     → Think: Move to next index (i+1, not i)
  
  3️⃣ SIGNAL: "Avoid duplicate solutions"
     Keywords: "unique", "no duplicate combinations", "no repeats"
     → Think: Sort + skip adjacent duplicates
  
  4️⃣ SIGNAL: "Array has duplicates but results shouldn't"
     Keywords: "array may contain duplicates", "unique results"
     → Think: Sort first, then skip duplicates during recursion

COMPARISON TABLE:
  ┌─────────────────┬──────────────┬──────────────┬─────────────────┐
  │ Problem         │ Reuse Element│ Handle Dups  │ Index Parameter │
  ├─────────────────┼──────────────┼──────────────┼─────────────────┤
  │ CombinationSum1 │ Can reuse    │ Not needed   │ i (same index)  │
  │ CombinationSum2 │ Use once     │ Must skip    │ i+1 (next)      │
  │ Permutations    │ Use once     │ Must skip    │ Used/unused set │
  │ Subsets         │ Use once     │ Must skip    │ i+1 (next)      │
  └─────────────────┴──────────────┴──────────────┴─────────────────┘

================================================================================

3. ⚡ APPROACH BREAKDOWN (INTERVIEW STYLE)
================================================================================

APPROACH 1: BRUTE FORCE (Generate ALL, then filter)
────────────────────────────────────────────────────
- Generate all possible subsets of candidates (2^n subsets)
- For each subset, check if sum == target
- Filter to get only valid ones
- Remove duplicates afterward

Pseudo-code:
  for each subset in powerset(candidates):
    if sum(subset) == target:
      if subset not in result:  // Check for duplicates
        result.add(subset)

Time: O(2^n) to generate all subsets + O(n) to check each = O(n * 2^n)
Space: O(2^n) for storing all subsets

Problem: 
  - Too slow for larger arrays
  - Generates many invalid combinations (sum != target)
  - Post-processing to remove duplicates is inefficient

Example: candidates=[1,1,2], target=3
  Subsets: [], [1], [1], [2], [1,1], [1,2], [1,2], [1,1,2]
  Valid sums: [1,2], [1,2] (duplicate!) [1,1,1] doesn't exist
  After filtering: [1,2]


APPROACH 2: RECURSION WITH PRUNING (Better!)
──────────────────────────────────────────────
- Use recursion to explore only VALID paths
- At each level, only pick elements that:
  * Haven't been used yet (index management)
  * Don't exceed remaining target (pruning)
  * Aren't duplicates of previous choice at same level
- Don't generate invalid combinations (no need to filter later)

Key Improvements:
  ✓ Sort array first (enables duplicate skipping + pruning)
  ✓ Skip adjacent duplicates (avoids duplicate combinations)
  ✓ Early break when element > target (prune invalid branches)
  ✓ Move to next index (prevents element reuse)

Time: O(2^k) where k = number of valid combinations found
      (Much better than 2^n when many combinations are invalid)
Space: O(k * avg_length) for storing valid combinations + O(h) recursion stack
      (where h = height of recursion tree, roughly target/min_element)


APPROACH 3: OPTIMAL (THIS SOLUTION - WHY IT'S CHOSEN)
──────────────────────────────────────────────────────
This IS Approach 2 - it's already optimal because:

✓ Time Complexity: O(2^k) where k = valid combinations
  - Best case: Only one combination exists → O(n) time to find it
  - Average case: Multiple valid combinations → O(2^k)
  - Worst case: Many combinations (e.g., target=100, candidates=[1,1,1...])
    Still bounded by actual solutions, not all subsets

✓ Space Complexity: O(k * avg_len) + O(h)
  - Must store results (can't be avoided)
  - Recursion depth bounded by target, not array size

✓ No wasted computation:
  - Don't explore paths that exceed target (pruning)
  - Don't generate then filter (filtering happens during recursion)
  - Don't create duplicate combinations (skipped at source)

WHY NOT IMPROVE FURTHER:
  - Can't avoid exploring ALL valid paths (must find them all)
  - Sorting is necessary (can't skip duplicates without it)
  - Backtracking is the natural pattern for this problem class

================================================================================

4. 🧩 INTUITION BUILDING
================================================================================

CORE IDEA (Explain in Simple Terms):
────────────────────────────────────
Imagine you're picking numbers from a box to reach a target sum:

TARGET = 8, Candidates = [1, 1, 2, 5, 6, 7]

Decision Tree (visualized as choices):
                                    (start: need 8)
                            /     |      |      |       |        \
                        pick 1  skip   pick 2  skip   pick 5    skip 6...
                           |    dup    |       dup    |          (no more)
                        (need 7)      (need 6)       (need 3)
                      /    |     \    /    \       /
                    pick 1 skip  pick 2   skip... pick 2 skip
                      |    dup     |              |     (rest)
                    (need 6)     (need 4)      (need 1)
                    ... continues until target=0 or target < 0 or no elements left

At each step:
  1. Try picking each remaining element
  2. If picking an element leads to valid solution, remember it
  3. Undo the pick (backtrack) and try next element
  4. If picking element > remaining target, stop trying elements (pruning)

THE "TRICK" OR KEY INSIGHTS:
───────────────────────────

🎯 INSIGHT 1: "Each element can be used ONCE"
  - After picking element at index i, continue from index i+1
  - NOT from index i (that would allow reuse)

🎯 INSIGHT 2: "Skip duplicate combinations"
  - If two elements are same value, pick only FIRST one at each level
  - If we pick both 1's at same level, we'd get same combination twice
  - Sort first, then: if (i > ind && arr[i] == arr[i-1]) skip

🎯 INSIGHT 3: "Prune invalid branches early"
  - If element > remaining target, all future elements (sorted) also > target
  - Break loop instead of checking each one

🎯 INSIGHT 4: "Backtracking saves state"
  - Instead of creating new vector at each step, reuse same vector
  - Push before recursing, pop after returning
  - This is MUCH more efficient than copying vectors

THE MENTAL MODEL:
─────────────────
Think of it as:

  THE RECURSION TREE:
  ```
  We're building a decision tree where:
  - Each NODE represents state (current combination, remaining target)
  - Each BRANCH represents trying a different element
  - LEAF NODES are solutions (when target = 0) or dead ends
  - We DFS traverse this tree, backtracking to try other branches
  ```

  THE BACKTRACKING PATTERN (Choose-Explore-Unchoose):
  ```
  function findPath(currentState):
    if currentState is solution:
      save solution
      return
    
    for each option:
      if option is valid:
        CHOOSE:  apply option to state
        EXPLORE: recurse with new state
        UNCHOOSE: undo option from state
  ```

================================================================================

5. 🔁 HOW TO RECALL LATER
================================================================================

KEY SIGNALS TO IDENTIFY THIS PROBLEM TYPE AGAIN:
─────────────────────────────────────────────

  1️⃣ "Find ALL combinations that sum to target"
     → Immediately think: Backtracking + sorted array + duplicate handling

  2️⃣ "Each element used AT MOST ONCE"
     → Immediately think: Use i+1 in recursive call, NOT i

  3️⃣ "Array has duplicates, result must be unique"
     → Immediately think: Sort + skip adjacent duplicates


ONE-LINE MEMORY TRICKS:
──────────────────────

🎯 MAIN TRICK:
  "Sort, skip duplicates with (i > ind), use i+1 for no reuse, backtrack with pop_back()"

OR SIMPLER:
  "DFS + Sort + Skip Dups + i+1 + Backtrack = CombinationSum2"

OR EVEN SIMPLER:
  "Like CombinationSum1, but with i+1 and duplicate skipping"

TRIGGER PHRASES (when you see these, use this approach):
  ⚡ "all unique combinations"
  ⚡ "each element at most once"
  ⚡ "no duplicates in result"
  ⚡ "backtracking problem"

================================================================================

6. ⚠️ COMMON MISTAKES
================================================================================

MISTAKE 1: Using 'i' instead of 'i+1' in recursive call
──────────────────────────────────────────────────────
❌ WRONG:
  findCandidates(i, target - candidates[i], ...);  // Same index!

  Result: Elements can be reused multiple times
  Example: candidates=[1], target=3
    Would allow: [1,1,1] (reused same 1 three times) ❌

✓ CORRECT:
  findCandidates(i + 1, target - candidates[i], ...);  // Next index

  Result: Each element used at most once
  Example: candidates=[1,1,1], target=3
    Would allow: [1,1,1] (used three different 1's) ✓

WHY: Index is like a bookmark - start from i means "this element available",
     start from i+1 means "this element already taken, move forward"


MISTAKE 2: Not skipping duplicates
───────────────────────────────────
❌ WRONG (without duplicate skipping):
  for (int i = ind; i < n; i++) {
    // No check for duplicates
    pair.push_back(candidates[i]);
    findCandidates(i + 1, ...);
    pair.pop_back();
  }

  Result: Duplicate combinations in output
  Example: candidates=[1,1,2], target=3
    Output: [[1,1,1], [1,2], [1,2]] ← [1,2] appears twice!

✓ CORRECT:
  for (int i = ind; i < n; i++) {
    if (i > ind && candidates[i] == candidates[i-1]) continue;  // Skip duplicate
    pair.push_back(candidates[i]);
    findCandidates(i + 1, ...);
    pair.pop_back();
  }

  Result: Only unique combinations
  Output: [[1,2]] ← No duplicates!

WHY: Condition (i > ind) is crucial:
  - i=ind (first element at this level): i > ind is false, never skip
  - i>ind (subsequent elements): if same as previous, skip (avoid duplicate choice)


MISTAKE 3: Forgetting pair.pop_back() or putting it in wrong place
──────────────────────────────────────────────────────────────────
❌ WRONG (forgetting pop):
  for (int i = ind; i < n; i++) {
    pair.push_back(candidates[i]);
    findCandidates(i + 1, target - candidates[i], ...);
    // NO pop_back() ← BUG!
  }

  Result: All combinations contain all tried elements
  Example: candidates=[1,2], target=3
    When found [1,2]:
      - Don't pop the 2
      - Back in loop, next iteration tries 2 again
      - pair = [1,2,2,...]
    Output: Wrong!

❌ WRONG (pop in wrong place):
  for (int i = ind; i < n; i++) {
    pair.pop_back();  // Pop BEFORE push? ← BUG!
    pair.push_back(candidates[i]);
    findCandidates(i + 1, ...);
  }

✓ CORRECT:
  for (int i = ind; i < n; i++) {
    pair.push_back(candidates[i]);      // Add
    findCandidates(i + 1, ...);         // Explore
    pair.pop_back();                    // Remove (UNDO)
  }

WHY: Pattern is Choose-Explore-Unchoose:
  1. Add to pair
  2. Recurse and explore all combinations WITH this element
  3. When recursion returns, REMOVE the element
  4. Loop to next element


MISTAKE 4: Not sorting the array
─────────────────────────────────
❌ WRONG:
  // Missing: sort(candidates.begin(), candidates.end());
  vector<int> pair;
  findCandidates(0, target, candidates, pair, result);

  Problem 1: Can't skip duplicates (they're not adjacent)
    candidates = [10,1,1,2], with duplicates far apart
    If checking candidates[i] == candidates[i-1], won't catch distant duplicates
  
  Problem 2: Can't prune early
    candidates = [10,1,5,20] (unsorted)
    When seeing 10 > target (5), we break
    But 1 < target, so we could still have solutions! Pruned too early.

✓ CORRECT:
  sort(candidates.begin(), candidates.end());  // [1,1,2,5,10,20]
  vector<int> pair;
  findCandidates(0, target, candidates, pair, result);

  Now: Duplicates adjacent, can skip with candidates[i] == candidates[i-1]
       After sorted, if candidates[i] > target, all future are also > target

WHY: Sorting enables both key optimizations:
  - Duplicate detection (adjacent equal elements)
  - Early termination (monotonic increasing = no surprises after large element)


MISTAKE 5: Not handling base case (target == 0)
───────────────────────────────────────────────
❌ WRONG:
  void findCandidates(...) {
    // No check for target == 0
    for (int i = ind; i < n; i++) {
      ...
    }
  }

  Result: Never save valid combinations!
  Example: For target=2, never save when we reach it
  Output: [] (empty, no combinations found!)

✓ CORRECT:
  void findCandidates(...) {
    if (target == 0) {
      result.push_back(pair);
      return;
    }
    for (int i = ind; i < n; i++) {
      ...
    }
  }

WHY: Base case is SUCCESS condition:
  - When target becomes 0, we've found valid combination
  - Must save it before stopping exploration
  - Return prevents exploring further (can't add positive to 0 and stay at 0)


MISTAKE 6: Not handling empty/invalid input
───────────────────────────────────────────
❌ RISKY (doesn't handle):
  vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    // What if candidates is empty?
    // What if target is negative?
    sort(candidates.begin(), candidates.end());
    ...
  }

✓ SAFER:
  vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    
    // Edge case 1: Empty candidates
    if (candidates.empty()) return result;  // Return empty result
    
    // Edge case 2: Negative target (impossible to reach with positive numbers)
    if (target < 0) return result;
    
    // Edge case 3: target is 0 (edge case, depends on problem statement)
    
    sort(candidates.begin(), candidates.end());
    vector<int> pair;
    findCandidates(0, target, candidates, pair, result);
    return result;
  }

EDGE CASES TO HANDLE:
  ✓ candidates = [] (empty array)
  ✓ target = 0 (no sum needed, might include empty combination)
  ✓ target < 0 (impossible if all candidates > 0)
  ✓ All candidates > target (no valid combination)
  ✓ Negative numbers in candidates (valid, complicates logic)

================================================================================

7. 📊 COMPLEXITY ANALYSIS
================================================================================

TIME COMPLEXITY: O(2^n * k)
──────────────────────────

Breakdown:
  - In worst case, explore all subsets = 2^n possibilities
  - For each subset found, copy to result = O(k) where k = combination length
  - Total: O(2^n * k)

More Precise Analysis:
  - Actual runtime ≠ 2^n when pruning:
    * Skip duplicates: reduce exploration
    * Break on candidates[i] > target: reduce exploration
    * Only explore valid paths: reduce exploration
  
  - Real complexity = O(C * k) where C = number of valid combinations found
    * If target is large and array is small: C ≈ 2^n
    * If target is small or candidates are large: C << 2^n (pruning helps)
    * If many duplicates: C << 2^n (duplicate skipping helps)

Example Scenarios:

  1️⃣ Best Case: O(n log n)
     candidates = [100,200,300], target = 10
     - Sorting: O(n log n)
     - Loop: first element 100 > 10, break immediately
     - Result: O(n log n)

  2️⃣ Average Case: O(2^k * k)
     candidates = [1,2,3...10], target = 20
     - Many valid combinations possible
     - Some pruning helps, but still explores most branches
     - k = typical combination length = 3-5

  3️⃣ Worst Case: O(2^n * n)
     candidates = [1,1,1,1...], target = n
     - Every subset is valid (sum to any target)
     - All 2^n subsets must be explored
     - Average combination length ≈ n/2
     - Total: 2^n subsets * n/2 length = O(2^n * n)

SPACE COMPLEXITY: O(n + h + k*m)
────────────────────────────────

Components:
  1. Sorting space: O(n) or O(log n) depending on sort implementation
     - C++ std::sort is introsort (hybrid): O(log n) extra space worst case
     - But often stated as O(n) to be safe

  2. Recursion stack depth: O(h)
     - h = height of recursion tree ≤ n (each recursion goes deeper)
     - More practically: h ≈ target / (smallest element)
     - For target=20, min element=1: h=20
     - For target=20, min element=5: h=4

  3. Result storage: O(k * m)
     - k = number of valid combinations found
     - m = average length of each combination
     - Must store all results (can't be avoided)

Total Space: O(sort + recursion + results) = O(n + h + k*m)

Since results can't be avoided and dominate:
  Practical: O(k * m) for storing results + O(h) for recursion
  Where k can be up to 2^n in worst case

COMPARISON:
───────────
┌─────────────────┬──────────────────┬──────────────────────┐
│ Operation       │ Time             │ Space                │
├─────────────────┼──────────────────┼──────────────────────┤
│ Sort            │ O(n log n)       │ O(log n) to O(n)     │
│ DFS exploration │ O(2^k) to O(2^n) │ O(h) recursion       │
│ Store results   │ O(k*m) copying   │ O(k*m) storage       │
│ Total           │ O(2^k * k)       │ O(n + h + k*m)       │
└─────────────────┴──────────────────┴──────────────────────┘

================================================================================

8. 🔄 ALTERNATIVE APPROACHES
================================================================================

APPROACH A: ITERATIVE BACKTRACKING (Using explicit stack)
──────────────────────────────────────────────────────────
Idea: Instead of recursion, use iterative approach with explicit stack

How it works:
  1. Use a stack to store states: (currentIndex, remainingTarget, currentPath)
  2. Loop while stack is not empty
  3. Pop state from stack
  4. If remainingTarget == 0, save path to results
  5. For each valid next element, push new state onto stack

Pseudo-code:
  stack.push({0, target, []})
  while (!stack.empty()):
    (ind, remaining, path) = stack.pop()
    if remaining == 0:
      result.add(path)
      continue
    for i from ind to n:
      if skip conditions: continue
      newPath = path + [candidates[i]]
      stack.push({i+1, remaining - candidates[i], newPath})

Complexity:
  - Time: Same O(2^k * k) as recursive (just different execution style)
  - Space: O(k * m) for stack + O(k*m) for results = O(k*m)
           (same as recursive's O(h + k*m), since explicit stack can be larger)

Pros:
  ✓ Avoids recursive function call overhead
  ✓ Some prefer iterative (easier to debug in some cases)
  ✓ No stack overflow risk for very deep recursion

Cons:
  ✗ More complex code (manage stack manually)
  ✗ Often slower in practice (function call overhead negligible compared to algorithm work)
  ✗ Harder to understand (recursion is more natural for tree exploration)

When to use: When recursion depth is known to exceed compiler limits
             (very deep trees), or when explicit control flow is crucial


APPROACH B: DYNAMIC PROGRAMMING (Subset Sum variant)
──────────────────────────────────────────────────────
Idea: Use DP to build combinations bottom-up

How it works:
  1. dp[i][j] = all combinations of first i elements that sum to j
  2. For each element: combine previous combinations with current element
  3. Skip duplicates during DP table construction

Pseudo-code:
  dp = map of target -> list of combinations
  dp[0] = [[]]  // Empty combination sums to 0
  
  for each element in sorted candidates:
    for each target in dp (in reverse to avoid using same element twice):
      if target + element is valid:
        dp[target + element] = dp[target + element] + dp[target] with element added

Complexity:
  - Time: O(target * k * m) where k = combinations
  - Space: O(target * k * m) for DP table

Pros:
  ✓ Might have better cache locality
  ✓ Can visualize DP table for small examples

Cons:
  ✗ SLOWER than backtracking in practice
  ✗ Requires more space (store all intermediate combinations)
  ✗ Harder to understand and implement correctly
  ✗ Index management for duplicates becomes convoluted

When to use: Rarely - backtracking is superior for this problem


APPROACH C: BIT MANIPULATION (Generate subsets via bitmask)
────────────────────────────────────────────────────────────
Idea: For each number 0 to 2^n-1, bit positions indicate which elements to include

How it works:
  1. For each mask from 0 to 2^n - 1:
  2. Convert mask to subset (bit i set = include candidates[i])
  3. Calculate sum of subset
  4. If sum == target, check if duplicate, then add to result

Pseudo-code:
  set<vector<int>> unique_combs;  // Use set to handle duplicates
  
  for int mask = 0 to (1 << n) - 1:
    vector<int> comb;
    int sum = 0
    for int i = 0 to n-1:
      if (mask & (1 << i)):
        comb.push_back(candidates[i])
        sum += candidates[i]
    
    if sum == target:
      sort(comb)  // For duplicate detection
      unique_combs.insert(comb)
  
  result = convert set to vector

Complexity:
  - Time: O(2^n) subsets to generate + O(n log n) per subset to sort + O(log k) set insertion
         = O(2^n * n log n) overall
  - Space: O(k*m) for set of unique combinations

Pros:
  ✓ Simple concept (iterate through all bitmasks)
  ✓ No recursion (might appeal to some)

Cons:
  ✗ MUCH SLOWER: generates ALL 2^n subsets (no pruning!)
  ✗ Requires set/hash for duplicate removal (extra overhead)
  ✗ Sorting each combination for set comparison (waste)
  ✗ Only works for n ≤ ~20 (2^20 = 1 million, 2^30 = too large)

When to use: Only when n is very small (< 15) AND you can't use backtracking


APPROACH D: CONSTRAINT SATISFACTION (CSP solver)
─────────────────────────────────────────────────
Idea: Model as CSP: Choose x₁, x₂, ... from candidates such that Σxᵢ = target

Uses: Generic CSP solver libraries

Complexity:
  - Time: Depends on CSP solver (could be exponential, could be optimized)
  - Space: O(solver overhead)

Pros:
  ✓ Leverage powerful solver libraries
  ✓ Easy to add more constraints later

Cons:
  ✗ OVERKILL for this problem
  ✗ Overhead of solver machinery
  ✗ Slower than backtracking for simple problem
  ✗ Learning curve for CSP solvers

When to use: Only if problem becomes much more complex (many constraints)


COMPARISON OF APPROACHES:
═════════════════════════

┌──────────────────┬─────────────────────┬─────────────────┬──────────────┐
│ Approach         │ Time Complexity     │ Space (w/o res) │ Difficulty   │
├──────────────────┼─────────────────────┼─────────────────┼──────────────┤
│ Backtracking     │ O(2^k * k) optimal  │ O(h)            │ ★★★ Medium   │
│ Iterative Stack  │ O(2^k * k)          │ O(k*m)          │ ★★★★ Hard    │
│ DP Approach      │ O(target * k * m)   │ O(target * k*m) │ ★★★★ Hard    │
│ Bitmask Subset   │ O(2^n * n log n)    │ O(n log n) sort │ ★★ Easy      │
│ CSP Solver       │ Variable            │ Variable        │ ★★★★★ V.Hard│
└──────────────────┴─────────────────────┴─────────────────┴──────────────┘

RECOMMENDED: 
  → Use BACKTRACKING (Recursive approach in solution)
  → It's optimal, clean, and efficient for this problem class

================================================================================
                            END OF ANALYSIS
================================================================================
*/