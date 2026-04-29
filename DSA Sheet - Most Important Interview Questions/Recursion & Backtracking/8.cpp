#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Recursive helper to generate all unique subsets.
    //
    // Parameters:
    // nums   -> sorted input array
    // ans    -> current subset being built
    // i      -> current index where we decide include/exclude
    // result -> stores all completed unique subsets
    //
    // Pattern:
    // Recursion + Backtracking + Duplicate Skipping.
    //
    // Time Complexity:
    // O(2^n * n) in the worst case:
    // - There can be up to 2^n subsets.
    // - Copying ans into result can take O(n) per subset.
    //
    // Space Complexity:
    // O(n) recursion depth, not counting output.
    // Output itself can store O(2^n * n) values.
    void helper(vector<int>& nums, vector<int>& ans, int i, vector<vector<int>>& result) {
        // WHAT:
        // Base case: if i reaches nums.size(), all decisions for the array are done.
        //
        // WHY:
        // A subset is formed only after we have decided for every element whether
        // to include it or exclude it.
        //
        // IF REMOVED:
        // Recursion would continue beyond the array bounds and access invalid indices.
        //
        // DRY RUN:
        // nums = [1,2,2]
        // If ans = [1,2] and i = 3, there are no more elements to decide.
        // So [1,2] is pushed into result.
        //
        // EDGE CASE:
        // If nums is empty, i == nums.size() immediately, so result gets one subset:
        // the empty subset [].
        if (i == nums.size()) {
            // WHAT:
            // Store the current subset in result.
            //
            // WHY:
            // ans is one complete path in the recursion decision tree.
            //
            // IF REMOVED:
            // The algorithm would explore choices but never save any subset.
            //
            // IMPORTANT:
            // push_back copies ans at this moment. Later backtracking changes ans,
            // but the saved subset inside result remains safe.
            result.push_back(ans);

            // WHAT:
            // Stop this recursion branch after saving the subset.
            //
            // WHY:
            // There are no more choices after the last index.
            //
            // IF REMOVED:
            // Execution would continue and try to access nums[i], causing an error.
            return;
        }

        // include nums[i]
        // WHAT:
        // Choose the current number nums[i] and add it to the current subset.
        //
        // WHY:
        // For every element, one recursive branch represents "include this element".
        //
        // IF REMOVED:
        // We would miss all subsets that contain nums[i] at this position.
        //
        // DRY RUN:
        // nums = [1,2,2], i = 0, ans = []
        // push nums[0] = 1, so ans becomes [1].
        ans.push_back(nums[i]);

        // WHAT:
        // Recurse to the next index after including nums[i].
        //
        // WHY:
        // Once nums[i] is chosen, the next decision must be made for i + 1.
        //
        // IF REMOVED:
        // The include branch would stop early and never produce complete subsets.
        //
        // DRY RUN:
        // After choosing 1 from [1,2,2], call helper with i = 1 to decide about
        // the first 2.
        helper(nums, ans, i + 1, result);

        // exclude nums[i] and skip duplicates
        // WHAT:
        // Backtrack: remove nums[i] from ans to undo the include choice.
        //
        // WHY:
        // The same ans vector is reused for many recursion paths.
        // Before exploring the exclude branch, we must restore ans to its previous state.
        //
        // IF REMOVED:
        // Exclude branches would accidentally still contain nums[i].
        // Example: after including 1, the "exclude 1" branch would wrongly keep 1.
        //
        // DRY RUN:
        // If ans was [1,2], pop_back makes it [1] again before trying the path
        // where the current 2 is excluded.
        ans.pop_back();

        // WHAT:
        // Skip over duplicate values before taking the exclude branch.
        //
        // WHY:
        // This prevents generating the same subset multiple times.
        //
        // CORE IDEA:
        // If nums[i] == nums[i + 1] and we choose to exclude nums[i], then excluding
        // only the first copy but allowing the second copy to start the same choice
        // can create duplicate subsets.
        //
        // IF REMOVED:
        // Duplicate subsets appear.
        // Example: nums = [1,2,2]
        // Without this loop, the subset [1,2] can be formed by:
        // - include first 2, exclude second 2
        // - exclude first 2, include second 2
        //
        // WHY SORTING IS REQUIRED BEFORE THIS:
        // Duplicate values must be next to each other for nums[i] == nums[i + 1]
        // to detect and skip them.
        //
        // DRY RUN:
        // nums = [1,2,2]
        // Suppose i = 1 and we are excluding nums[1] = 2.
        // nums[1] == nums[2], so i increments from 1 to 2.
        // Then the recursive exclude call goes to i + 1 = 3, skipping both 2s.
        while (i + 1 < nums.size() && nums[i] == nums[i + 1]) {
            // WHAT:
            // Move i forward across equal adjacent values.
            //
            // WHY:
            // The exclude branch means "do not use this value at this decision level";
            // for duplicates, that means skip every copy of the same value.
            //
            // IF REMOVED:
            // The while loop would never progress, causing an infinite loop.
            i++;
        }

        // WHAT:
        // Recurse after excluding nums[i] and all equal duplicates beside it.
        //
        // WHY:
        // This explores the branch where the current value is not part of the subset.
        //
        // IF REMOVED:
        // We would only generate subsets from include choices and miss subsets like
        // [] or [2] when earlier values are excluded.
        //
        // DRY RUN for nums = [1,2,2]:
        // Start ans = [], i = 0.
        // Include path creates subsets beginning with 1.
        // After pop, exclude 1 and call helper(i = 1), creating subsets without 1.
        helper(nums, ans, i + 1, result);
    }

    // Main function that returns all unique subsets of nums.
    //
    // Example:
    // nums = [1,2,2]
    // result can be:
    // [], [1], [1,2], [1,2,2], [2], [2,2]
    //
    // Exact order depends on recursion order, but duplicates should not appear.
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        // WHAT:
        // Sort the array so duplicate values become adjacent.
        //
        // WHY:
        // The duplicate-skipping loop depends on equal elements being side by side.
        //
        // IF REMOVED:
        // Duplicate detection becomes unreliable.
        // Example: [2,1,2] has duplicate 2s separated, so nums[i] == nums[i+1]
        // may not catch them.
        //
        // COST:
        // Sorting takes O(n log n) time.
        sort(nums.begin(), nums.end()); // sort to group duplicates

        // WHAT:
        // result stores every unique subset.
        //
        // WHY:
        // The function must return all generated subsets, not just print them.
        //
        // IF REMOVED:
        // There would be no container to collect answers.
        //
        // SPACE:
        // Output space can be O(2^n * n) in the worst case.
        vector<vector<int>> result;

        // WHAT:
        // ans stores the subset currently being built along one recursion path.
        //
        // WHY:
        // Backtracking needs a temporary working subset.
        //
        // IF REMOVED:
        // The helper would not know which elements are currently selected.
        //
        // SPACE:
        // ans can grow up to size n, so O(n) auxiliary space.
        vector<int> ans;

        // WHAT:
        // Start recursion from index 0 with an empty subset.
        //
        // WHY:
        // Every subset is built by making include/exclude decisions from left to right.
        //
        // IF REMOVED:
        // No subsets would be generated; result would remain empty.
        //
        // DRY RUN SUMMARY for [1,2,2]:
        // Include 1:
        //   Include first 2:
        //     Include second 2 -> [1,2,2]
        //     Exclude second 2 -> [1,2]
        //   Exclude first 2 and skip duplicate -> [1]
        // Exclude 1:
        //   Include first 2:
        //     Include second 2 -> [2,2]
        //     Exclude second 2 -> [2]
        //   Exclude first 2 and skip duplicate -> []
        helper(nums, ans, 0, result);

        // WHAT:
        // Return all unique subsets.
        //
        // WHY:
        // This is the required output of the problem.
        //
        // IF REMOVED:
        // The function would not return the computed answer.
        return result;
    }
};


int main() {
    // This main function is currently empty.
    //
    // WHAT:
    // It allows the file to compile as a standalone C++ program.
    //
    // WHY:
    // Many online judges call Solution::subsetsWithDup directly, so main is often
    // not needed for judge execution.
    //
    // IF YOU WANT TO TEST MANUALLY:
    // You could create a vector like {1,2,2}, call subsetsWithDup, and print result.
    // No test code is added here because the instruction is to only add comments.

    // WHAT:
    // Return 0 to indicate successful program execution.
    return 0;
}

/*
================================================================================
### 1. 🧠 Problem Understanding
================================================================================

What type of problem is this?
- This is a combinatorics generation problem.
- Specifically, it generates the power set: all possible subsets.
- The twist is that nums may contain duplicates, but result must not contain
  duplicate subsets.

Key constraints/clues:
- "All subsets" usually hints recursion/backtracking or bit manipulation.
- "May contain duplicates" means we need a duplicate-handling rule.
- Output size is exponential, so O(2^n) behavior is expected.
- Order of subsets is usually not important unless explicitly stated.

Example:
- nums = [1,2,2]
- Unique subsets are:
  [], [1], [2], [1,2], [2,2], [1,2,2]
- Duplicate [2] or [1,2] should not appear twice.
*/

/*
================================================================================
### 2. 🔍 Pattern Recognition
================================================================================

DSA pattern used:
- Recursion + Backtracking.
- Duplicate skipping after sorting.

How to recognize this pattern:
- The problem asks for "all combinations", "all subsets", "all possibilities",
  or "generate every valid answer".
- At each element, you have a choice:
  include it or exclude it.
- You need to build a temporary answer and undo choices after recursion.
- Duplicates in input require sorting or a visited/skip rule.

Future signal:
- If a problem says "return all unique ..." and input can contain duplicates,
  think: sort first, then skip duplicates carefully.
*/

/*
================================================================================
### 3. ⚡ Approach Breakdown (Interview Style)
================================================================================

Brute force idea:
- Generate all 2^n subsets using include/exclude recursion.
- Store each subset in a set to automatically remove duplicates.
- This is simple but less efficient because set insertion compares vectors and
  adds extra memory overhead.

Better approach:
- Sort nums first.
- During recursion, when excluding a value, skip all adjacent duplicates.
- This avoids creating duplicate subsets in the first place.

Optimal approach used here:
- Sort + backtracking + duplicate skip.
- Sorting groups equal values.
- Include branch allows taking duplicates when needed, such as [2,2].
- Exclude branch skips duplicate copies to avoid repeated subsets.

Why this one is chosen:
- It avoids the extra set.
- It is clean and interview-friendly.
- It directly explains why duplicates do not appear.
*/

/*
================================================================================
### 4. 🧩 Intuition Building
================================================================================

Core idea in simple terms:
- For each number, ask:
  "Do I take this number or leave it?"
- That creates a decision tree.
- When duplicate numbers exist, leaving one copy and then taking an identical
  later copy can create the same subset again.

The trick/insight:
- Sort first.
- When you choose to exclude a value, exclude all its duplicate copies at that
  same decision level.

Why include branch does not skip duplicates immediately:
- Because subsets like [2,2] are valid.
- We only skip duplicates in the exclude branch to avoid starting the same choice
  again from an identical value.
*/

/*
================================================================================
### 5. 🔁 How to Recall Later
================================================================================

Key signals:
- "Generate all subsets."
- "Input may contain duplicates."
- "Return unique subsets."

One-line memory trick:
- "Sort duplicates together; when saying no to a value, say no to all its twins."

Recall formula:
- Include current.
- Backtrack.
- Skip duplicates.
- Exclude current group.
*/

/*
================================================================================
### 6. ⚠️ Common Mistakes
================================================================================

Where beginners go wrong:
- Forgetting to sort before skipping duplicates.
- Skipping duplicates in the include branch and accidentally missing [2,2].
- Forgetting ans.pop_back(), causing elements to leak into other branches.
- Pushing ans into result before reaching the base case in this version's logic.
- Using a set unnecessarily and making the solution heavier.
- Not understanding that result.push_back(ans) copies the current subset.

Edge cases handled:
- Empty input: returns [[]].
- All unique elements: behaves like normal subset generation.
- All duplicate elements, such as [2,2,2]: returns [], [2], [2,2], [2,2,2].
- Single element: returns [] and [element].

Edge cases to be aware of:
- Very large n creates huge output because subsets grow exponentially.
- This is not a bug; it is inherent to the problem.
*/

/*
================================================================================
### 7. 📊 Complexity Analysis
================================================================================

Time Complexity:
- Sorting: O(n log n).
- Backtracking: O(2^n) recursive subset choices in the no-duplicate worst case.
- Copying each subset into result can take up to O(n).
- Overall worst-case time: O(n log n + 2^n * n).
- Usually simplified as O(2^n * n), because output generation dominates.

Space Complexity:
- Recursion depth: O(n).
- Temporary ans vector: O(n).
- Output result: O(2^n * n) in the worst case.

Auxiliary space excluding output:
- O(n).

Important interview note:
- You cannot do better than exponential output size because the problem asks you
  to return all subsets.
*/

/*
================================================================================
### 8. 🔄 Alternative Approaches
================================================================================

1. Bitmasking:
- Use numbers from 0 to 2^n - 1.
- Each bit decides whether to include an element.
- For duplicates, you still need a set or a duplicate-handling strategy.
- Good for unique elements, less elegant for duplicate handling.

2. Backtracking with a for-loop:
- Another common style builds subsets by choosing the next element inside a loop.
- At each recursion level, skip nums[j] when j > start and nums[j] == nums[j - 1].
- This is often the most popular LeetCode style for Subsets II.

3. Generate all then use set:
- Generate every subset without caring about duplicates.
- Insert each subset into a set.
- Easier to reason about initially, but uses more memory and does extra work.

4. Iterative subset expansion:
- Start with [[]].
- For each number, append it to existing subsets.
- With duplicates, only extend subsets created in the previous duplicate step.
- Efficient but slightly trickier to explain than recursive backtracking.
*/
