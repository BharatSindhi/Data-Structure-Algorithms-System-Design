#include <iostream>
// Provides basic input/output support.
// What it does: Makes standard C++ I/O available.
// Why needed: This file currently has an empty main(), but most C++ templates include iostream.
// If removed: The current code may still compile if no I/O is used, but any cout/cin test code would fail.
// Complexity impact: None.
#include <map>
// Provides the map container.
// What it does: Stores requirements as index -> required inversion count.
// Why needed: We need to quickly know whether a prefix ending at index i has a fixed inversion requirement.
// If removed: map<int,int> would be undefined and the code would not compile.
// Complexity impact: map lookup is O(log r), where r is the number of requirements.
#include <vector>
// Provides the vector container.
// What it does: Stores the requirements input as vector<vector<int>>.
// Why needed: The function signature receives requirements in vector form.
// If removed: vector would be undefined and the code would not compile.
// Complexity impact: Storing requirements takes O(r) space.
using namespace std;
// Lets us write map, vector, and other standard-library names without std::.
// If removed: The logic still works, but names must be written as std::map, std::vector, etc.

class Solution {
public:
    int dp[300][401];int mod=1e9+7;
    // dp[i][cnt] memoizes the number of ways to build the permutation from state (i, cnt).
    //
    // Meaning of state:
    // i   = the next value/index being inserted into the growing permutation.
    // cnt = current inversion count for the prefix built so far.
    //
    // Why size [300][401]:
    // n can go up to around 300 in this style of problem, and the inversion requirement
    // is capped at 400, so cnt values beyond 400 are not useful.
    //
    // mod = 1e9 + 7 is used because the number of valid permutations can be very large.
    //
    // If dp is removed:
    // The same recursive states would be recomputed many times, causing exponential time.
    //
    // If mod is removed:
    // sum can overflow int/long long for large n.
    //
    // Important note:
    // This code uses memset later, so a normal standalone compile usually needs <cstring>.
    // That is not added here because the request is to only add comments.
   int  solve(int i,int n,map<int,int>&m,int cnt)
    {
        // Recursive DP function.
        //
        // Big picture:
        // We build a permutation prefix step by step.
        // At step i, we insert the next largest value into a prefix of size i.
        // Inserting this new largest value can add between 0 and i new inversions,
        // so the next inversion count can range from cnt to cnt + i.
        //
        // Example of the transition:
        // Suppose i = 2 and current prefix length is 2.
        // Current inversion count cnt = 0.
        // Inserting value 2 into a length-2 prefix can add:
        // 0 inversions if placed at the end,
        // 1 inversion if placed between the two old values,
        // 2 inversions if placed at the front.
        // So possible next counts are 0, 1, 2.
        //
        // Dry run idea for n = 3, no requirements:
        // solve(1,3,cnt=0)
        // i = 1: j ranges 0..1
        //   j = 0 -> solve(2,3,0)
        //   j = 1 -> solve(2,3,1)
        // i = 2 then each state expands by adding 0..2 inversions.
        // Base i == 3 counts one completed permutation path.
        if(i==n)
            return 1;
        // Base case:
        // If i == n, all values have been inserted and a full valid permutation path is formed.
        //
        // Why return 1:
        // This branch represents exactly one way to complete the construction.
        //
        // If removed:
        // Recursion would continue past the valid length and access invalid dp states.
        //
        // Edge case handled:
        // Once all requirements have already been checked during earlier steps,
        // reaching i == n means this path is valid.
        if(cnt>400)
            return 0;
        // Pruning invalid states.
        //
        // What it does:
        // If inversion count exceeds 400, stop exploring this branch.
        //
        // Why necessary:
        // dp only has columns 0..400, and the problem constraints usually cap
        // required inversion counts at 400.
        //
        // If removed:
        // dp[i][cnt] could access out-of-bounds memory when cnt > 400.
        //
        // Edge case handled:
        // Very inversion-heavy branches are safely discarded.
       if(dp[i][cnt]!=-1)
           return dp[i][cnt];
       // Memoization check.
       //
       // What it does:
       // If we already solved state (i, cnt), reuse the stored answer.
       //
       // Why necessary:
       // Many different insertion paths can lead to the same (i, cnt).
       // Without memoization, recursion would repeat the same work again and again.
       //
       // If removed:
       // The solution becomes much slower, close to exploring all permutations.
       //
       // Complexity impact:
       // Memoization reduces states to at most n * 401.
       
      
        int sum=0;
        // Accumulates the number of valid ways from the current state.
        //
        // Why needed:
        // Each possible next inversion count j represents a different insertion choice.
        // We add the number of valid completions from all allowed choices.
        //
        // If removed:
        // There would be no variable to collect answers across recursive branches.
        for(int j=cnt;j<=cnt+i;j++)
        {
            // Try every possible next inversion count after inserting the next largest value.
            //
            // Why range cnt to cnt + i:
            // At step i, the new value can create 0, 1, 2, ..., i new inversions.
            // Therefore:
            // newCount = cnt + addedInversions
            // so j ranges from cnt to cnt + i.
            //
            // Dry run:
            // If cnt = 1 and i = 3, then j can be:
            // 1, 2, 3, 4
            // meaning the insertion added 0, 1, 2, or 3 inversions.
            //
            // If this loop is removed:
            // The function would not explore insertion choices, so it could not count permutations.
            
           
        
        
        if(m.find(i)!=m.end())
        {
            // Check whether the prefix ending at index i has a required inversion count.
            //
            // What m stores:
            // m[index] = exact number of inversions required for prefix nums[0..index].
            //
            // Why check here:
            // After choosing j, we know the inversion count for the prefix up to i.
            // This is the exact moment to validate the requirement for index i.
            //
            // If removed:
            // The algorithm would count permutations that violate given requirements.
            if(j!=m[i])
                continue;
            // If a requirement exists and j does not match it, skip this branch.
            //
            // Why necessary:
            // A prefix with the wrong inversion count can never become valid later,
            // because requirements apply to that exact prefix.
            //
            // If removed:
            // Invalid branches would be included in the final count.
            //
            // Dry run:
            // If requirement says prefix index 2 must have 1 inversion,
            // then while i == 2, only j == 1 is allowed.
        }
            
            
         sum= (sum%mod+  solve(i+1,n,m,j)%mod)%mod;
         // Recurse to the next insertion step using j as the new inversion count.
         //
         // What it does:
         // Counts all valid completions after choosing this next inversion count.
         //
         // Why modulo is used:
         // The number of valid permutations can be huge, so we keep it within mod.
         //
         // If removed:
         // This branch would not contribute to the answer, so the count would be too small.
         //
         // Dry run:
         // For n = 3 and no requirements:
         // solve(1,3,0) adds answers from solve(2,3,0) and solve(2,3,1).
         //
         // Complexity:
         // Each state loops over up to i + 1 choices, bounded by O(n).
            
            
        } 
        return dp[i][cnt]=sum;
        // Store and return the answer for state (i, cnt).
        //
        // Why needed:
        // Future calls to the same state can return instantly using dp[i][cnt].
        //
        // If removed:
        // The answer might still be correct, but runtime becomes much worse.
        //
        // Space:
        // dp table stores O(n * 401) integer states.
            
        
    }
    
    
    
    int numberOfPermutations(int n, vector<vector<int>>& requirements) {
        // Main function called by the judge.
        //
        // Problem interpretation:
        // Count how many permutations of [0, 1, ..., n - 1] satisfy all prefix
        // inversion-count requirements.
        //
        // A requirement [end, cnt] means:
        // The prefix ending at index end must have exactly cnt inversions.
        //
        // Example:
        // n = 3, requirement [2, 1]
        // We need full permutations of [0,1,2] with exactly 1 inversion.
        // Valid examples include [0,2,1] and [1,0,2].
        map<int,int>m;
        // Converts requirements into a lookup table: prefix index -> required inversions.
        //
        // Why needed:
        // During recursion, when we reach index i, we can quickly check if i has a rule.
        //
        // If removed:
        // We would need to scan the whole requirements vector at every recursive state.
        memset(dp,-1,sizeof(dp));
        // Initializes all dp states to -1, meaning "not computed yet."
        //
        // Why necessary:
        // Memoization needs a marker to distinguish unknown states from computed answers.
        //
        // If removed:
        // dp contains garbage values, so the memoization check can return wrong answers.
        //
        // Note:
        // Standalone C++ normally requires #include <cstring> for memset.
        // The include is not added here because only comments are being added.
        for(int i=0;i<requirements.size();i++)
        {
          // Read each requirement pair.
          //
          // requirements[i][0] = prefix ending index.
          // requirements[i][1] = required inversion count for that prefix.
          m[requirements[i][0]]=requirements[i][1];
          // Store the requirement in the map.
          //
          // Why needed:
          // Later, solve() can check m.find(currentIndex) to know whether a restriction exists.
          //
          // If removed:
          // The recursion would ignore all requirements and count too many permutations.
          //
          // Edge case:
          // If duplicate requirements for the same index are present, this overwrites the older one.
          // The code assumes input is valid or does not contain conflicting duplicates.
        }
        
        if(m.find(0)!=m.end() && m[0]!=0)
            return 0;
        // Handles the prefix of length 1.
        //
        // Why index 0 must have 0 inversions:
        // A single element can never form an inversion because an inversion needs two positions.
        //
        // If requirement [0, x] exists with x != 0:
        // It is impossible, so return 0 immediately.
        //
        // If this check is removed:
        // The recursion starts from solve(1, n, 0), meaning it assumes prefix 0 has 0 inversions.
        // A bad requirement like [0,1] might not be rejected correctly.
    
        
        
       return  solve(1,n,m,0);
       // Start recursion after the first element is placed.
       //
       // Why i = 1:
       // Prefix index 0 has exactly one element and exactly 0 inversions.
       // The next step is to insert/build for index 1.
       //
       // Why cnt = 0:
       // One element has zero inversions.
       //
       // If changed:
       // Starting at the wrong i or cnt would count invalid construction states.
       //
       // Overall time:
       // There are about n * 401 DP states.
       // Each state loops over up to O(n) possible added inversion counts.
       // So worst-case time is O(n * 401 * n), often written as O(n^2 * 400).
       //
       // Overall space:
       // O(n * 401) for dp, O(r) for map, and O(n) recursion stack depth.
    }
};

int main() {
    // Empty driver.
    // In coding platforms, the judge creates Solution and calls numberOfPermutations().
    
    return 0;
    // Successful program termination.
}

// ---------------------------------------------------------------------------
// 1. Problem Understanding
// ---------------------------------------------------------------------------
// Type of problem:
// This is a counting problem on permutations with prefix inversion constraints.
// Because the answer asks "how many ways", and choices overlap heavily, it is
// naturally a Dynamic Programming problem.
//
// Key constraints/clues:
// 1. We count permutations, not construct just one permutation.
// 2. Requirements are about prefixes and inversion counts.
// 3. Inversion counts are capped around 400, which makes cnt a valid DP dimension.
// 4. The result can be huge, so modulo 1e9 + 7 is required.
//
// Edge cases:
// 1. Requirement at index 0 must be 0.
// 2. cnt > 400 is invalid for this dp table.
// 3. No requirements means count all permutations under the dp limit.
// 4. Conflicting duplicate requirements are not explicitly handled.

// ---------------------------------------------------------------------------
// 2. Pattern Recognition
// ---------------------------------------------------------------------------
// DSA pattern used:
// Dynamic Programming with recursion + memoization.
//
// More specific pattern:
// Count permutations by inserting the next largest element and tracking
// inversion count.
//
// How to recognize this pattern later:
// 1. The problem talks about permutations and inversions.
// 2. You need counts for prefixes.
// 3. Adding a new largest element changes inversion count by a controlled range.
// 4. The same state can be described by "where am I?" and "how many inversions so far?"
//
// State recognition:
// dp[i][cnt] means:
// "Number of ways after building up to step i with cnt inversions so far."

// ---------------------------------------------------------------------------
// 3. Approach Breakdown (Interview Style)
// ---------------------------------------------------------------------------
// Brute force idea:
// Generate every permutation of [0, 1, ..., n - 1].
// For each permutation, compute inversion counts for required prefixes.
// Count the ones that satisfy all requirements.
// This is O(n! * n^2), which is far too slow.
//
// Better approach:
// Use recursion to build permutations step by step.
// Track the current inversion count and stop branches that violate requirements.
// This is better conceptually, but still repeats many identical states.
//
// Optimal approach used here:
// Use DP memoization on (i, cnt).
// At each step, try all possible new inversion counts created by inserting
// the next largest value.
// Check prefix requirements immediately when their index is reached.
//
// Why this one is chosen:
// It avoids generating actual permutations and only counts states that matter:
// current index and current inversion count.

// ---------------------------------------------------------------------------
// 4. Intuition Building
// ---------------------------------------------------------------------------
// Core idea:
// Do not think of building the exact permutation first.
// Think of building the inversion count.
//
// When inserting the next largest number into a prefix of size i:
// 1. Put it at the end -> adds 0 inversions.
// 2. Move it one step left -> adds 1 inversion.
// 3. Put it at the front -> adds i inversions.
//
// Trick/insight:
// The new largest value has a predictable effect on inversions.
// That lets us count possible inversion totals without storing the full permutation.

// ---------------------------------------------------------------------------
// 5. How to Recall Later
// ---------------------------------------------------------------------------
// Key signals:
// 1. "Permutation" plus "inversion count".
// 2. "Prefix must have exactly x inversions."
// 3. Small inversion limit like 400.
//
// One-line memory trick:
// Insert the next largest number; it can add 0 to i inversions.

// ---------------------------------------------------------------------------
// 6. Common Mistakes
// ---------------------------------------------------------------------------
// 1. Trying to generate all permutations.
// 2. Forgetting that index 0 can only have 0 inversions.
// 3. Not pruning cnt > 400 before indexing dp.
// 4. Checking requirements at the wrong step.
// 5. Missing modulo operations during summation.
// 6. Forgetting to initialize dp to -1.
// 7. Confusing "inserting value i" with "placing at array index i".

// ---------------------------------------------------------------------------
// 7. Complexity Analysis
// ---------------------------------------------------------------------------
// Time complexity:
// dp has at most n * 401 states.
// Each state tries up to i + 1 choices, which is O(n) in the worst case.
// map lookup costs O(log r).
// Worst-case time is O(n * 401 * n * log r).
// Since 401 is a fixed cap, this is often simplified to O(n^2 log r).
//
// Space complexity:
// dp table uses O(n * 401).
// map uses O(r), where r is the number of requirements.
// recursion stack can grow to O(n).
// Total auxiliary space: O(n * 401 + r + n).

// ---------------------------------------------------------------------------
// 8. Alternative Approaches
// ---------------------------------------------------------------------------
// 1. Bottom-up DP:
// Build dp iteratively from smaller prefixes to larger prefixes.
// This avoids recursion stack and can be easier to optimize.
//
// 2. Prefix-sum optimized DP:
// The transition sums over a range of previous counts.
// With prefix sums, some inversion-count DP variants can reduce transition cost.
//
// 3. Brute force permutation checking:
// Useful only for very tiny n or for testing correctness of the DP.
//
// 4. Backtracking with pruning:
// Build actual permutations and stop when a prefix violates a requirement.
// Easier to visualize, but still too slow for large n.
