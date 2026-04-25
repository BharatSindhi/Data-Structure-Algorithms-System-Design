#include <iostream>
#include <set>      // used to avoid duplicate combinations when candidates may lead to repeats
#include <vector>
using namespace std;

class Solution {
public:
    // This set stores combinations that have already been added to the answer.
    // It is not part of the core recursion logic, but it prevents duplicates
    // when the input or recursion order could otherwise generate the same list twice.
    set<vector<int>> s;

    void getAllCombinations(vector<int>& candidates, int idx, int target,
                            vector<vector<int>>& ans, vector<int>& combin) {
        // Base case: exact match found.
        // When target reaches 0, combin holds a valid combination.
        if (target == 0) {
            // Check the set to avoid duplicates in the result.
            // Removing this would allow repeated combinations when same numbers appear in different orders.
            if (s.find(combin) == s.end()) {
                ans.push_back(combin);
                s.insert(combin);
            }
            return;
        }

        // If we've exhausted candidates or overshot the target, stop exploring this branch.
        // Without this guard, the recursion would continue indefinitely or push negative targets.
        if (idx >= candidates.size() || target < 0)
            return;

        // Include the current element and continue exploring with the same index.
        // This allows repeated use of a candidate, which is required by the problem.
        combin.push_back(candidates[idx]);
        getAllCombinations(candidates, idx, target - candidates[idx], ans,
                           combin);

        // Backtrack by removing the last added element.
        // If this pop is removed, the combination list would grow incorrectly and subsequent branches would be wrong.
        combin.pop_back();

        // Exclude the current element and move to the next index.
        // This explores combinations that do not use candidates[idx].
        getAllCombinations(candidates, idx + 1, target, ans, combin);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;   // store final result combinations
        vector<int> combin;       // current combination under construction

        // Start recursive exploration from index 0 and the full target.
        getAllCombinations(candidates, 0, target, ans, combin);
        return ans;
    }
};

int main() {
    
    return 0;
}

/*
### 1. 🧠 Problem Understanding

* What type of problem is this?
  - This is a recursion/backtracking problem where we need to build all combinations summing to a target.
  - It is also a subset sum variant where numbers can be reused.

* What are key constraints/clues?
  - You can reuse candidates multiple times.
  - The combination order does not matter for the final answer.
  - The output should contain unique combinations only.
  - Search must stop when the target is reached or exceeded.

### 2. 🔍 Pattern Recognition

* Which DSA pattern is used?
  - Backtracking / recursive exploration.

* How can I recognize this pattern in future problems?
  - The problem asks for combinations or subsets that satisfy a condition.
  - There is a choice at each step to include or skip an element.
  - Reusing the same candidate is allowed, leading to recursion that keeps the same index.

### 3. ⚡ Approach Breakdown (Interview Style)

* Brute force idea
  - Generate all possible subsequences and filter those that sum to target.
  - This would be extremely inefficient with exponential combinations.

* Better approach
  - Use recursion to build combinations and prune paths when the sum exceeds the target.
  - This avoids exploring impossible branches.

* Optimal approach (why this one is chosen)
  - Backtracking directly constructs valid combinations and prunes early.
  - It avoids generating all permutations by keeping candidates in order and eliminating duplicates.

### 4. 🧩 Intuition Building

* Explain the core idea in simple terms
  - Choose a number, subtract it from the target, and keep building until the target becomes zero.
  - If the target becomes negative or no candidates remain, backtrack.
  - Each recursion branch represents a decision to take or skip a candidate.

* What is the “trick” or insight?
  - The key is allowing repeated use of the same candidate by recursing with the same index.
  - Backtracking ensures we undo choices so the next branch starts clean.

### 5. 🔁 How to Recall Later

* 2–3 key signals to identify this problem again
  - "combination sum" or "choose numbers that add up to target."
  - "Use candidates unlimited times."
  - "Return all unique combinations."

* One-line memory trick
  - "Pick or skip each candidate, reuse when needed, and backtrack after trying it."

### 6. ⚠️ Common Mistakes

* Where beginners go wrong
  - Forgetting to backtrack after recursion, leaving stale values in the combination.
  - Moving to the next index too soon, which prevents reuse of the current candidate.
  - Not pruning when target < 0, causing unnecessary recursion.
  - Forgetting to eliminate duplicate combinations in the final answer.

### 7. 📊 Complexity Analysis

* Time Complexity: O(2^n) in the worst case
  - The recursion explores include/exclude choices for each candidate.
  - Pruning when target < 0 reduces some branches, but the structure is still exponential in general.

* Space Complexity: O(n)
  - The recursion stack depth is bounded by the number of candidates or the target divided by the smallest candidate.
  - The current combination vector also uses O(n) space in the worst case.

### 8. 🔄 Alternative Approaches

* Sorting + deduping before recursion
  - Sort candidates and skip duplicates during recursion instead of using a set.
  - This can simplify duplicate handling.

* Dynamic programming subset-sum style
  - Use DP to count or build combinations, but it can be harder to produce unique combinations.

* Using a boolean visited table for combination uniqueness
  - Track used numbers in a branch, but this is only useful for non-repeating combination variants.
*/