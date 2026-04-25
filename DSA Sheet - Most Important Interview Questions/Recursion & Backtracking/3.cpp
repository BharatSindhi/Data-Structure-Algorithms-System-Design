/*
================================================================================
PROBLEM: Palindrome Partitioning (LeetCode 131)
================================================================================

GIVEN: A string s
TASK: Find ALL possible ways to partition the string such that each partition
      is a palindrome (reads the same forwards and backwards)
      
EXAMPLE:
  Input: s = "nitin"
  Output: [["n","i","t","i","n"], ["nitin"], ...]
          All partitions where each part is a palindrome

APPROACH: Backtracking with Recursion
  • Try each possible first partition
  • If it's a palindrome, recurse on the remaining string
  • When string is empty, add the complete partition to result
  • Backtrack by removing the last partition and try next option

TIME: O(N * 2^N) - exponential due to all possible partitions
SPACE: O(N) - recursion depth + result storage
================================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // ========== HELPER FUNCTION: Check if string is palindrome ==========
    // WHAT: Returns true if string reads the same forwards and backwards
    // WHY: We only partition strings where each part is a palindrome
    // COMPLEXITY: O(n) where n is length of string s
    bool isPPalin(string s){
        string s2=s;                           // Create a copy of original string
        reverse(s2.begin(),s2.end());          // Reverse the copy (O(n) operation)
        return s==s2;                          // Compare original with reversed
                                               // If equal, it's a palindrome
                                               // Examples: "aba" == "aba" ✓, "ab" != "ba" ✗
    }
    // ========== RECURSIVE BACKTRACKING FUNCTION ==========
    // PARAMETERS:
    //   s           : Remaining string to be partitioned (shrinks as we recurse)
    //   partitions  : Current partition being built (grows as we add palindromes)
    //   ans         : Reference to result vector (stores all valid partitions)
    //
    // IDEA: Recursively try each possible first partition from remaining string.
    //       If it's a palindrome, recurse on the rest. When string is exhausted,
    //       we've found a complete valid partition.
    
    void getAllParts(string s, vector<string> partitions ,vector<vector<string>> &ans){
        // ---- BASE CASE: String is completely partitioned ----
        if(s.size()==0){
            // WHAT: We've successfully partitioned the entire string
            // WHY: When s is empty, 'partitions' contains a complete valid partition
            // EXAMPLE: If original="aba" and we partitioned it as ["a","b","a"]
            //          or ["aba"], s would be empty now
            ans.push_back(partitions);        // Save this complete partition to result
            return;                           // Backtrack: stop exploring this path
        }
        
        // ---- RECURSIVE CASE: Try each possible first partition ----
        // DRY RUN Example: s="nitin", partitions=[], ans=[]
        // i=0: part="n"   (palindrome ✓) → recurse with "itin"
        // i=1: part="ni"  (not palindrome ✗) → skip
        // i=2: part="nit" (not palindrome ✗) → skip
        // i=3: part="niti" (not palindrome ✗) → skip
        // i=4: part="nitin" (palindrome ✓) → recurse with ""
        
        for(int i=0;i<s.size();i++){         // Try each possible length of first partition
            string part=s.substr(0,i+1);     // Extract first (i+1) characters as candidate partition
                                             // substr(pos, len): starts at pos, takes len characters
                                             // substr(0, 1) = first char
                                             // substr(0, 2) = first two chars, etc.

            if(isPPalin(part)){              // Check if this candidate is a palindrome
                // If yes, it's a valid partition piece. Proceed with recursion.
                
                partitions.push_back(part);  // ADD: Include this partition piece in current path
                                             // This is the KEY STEP of backtracking
                                             // We're committing to this choice
                
                // RECURSE: Now partition the REMAINING string
                // s.substr(i+1) removes the first (i+1) characters we just used
                // Example: s="nitin", i=0 → s.substr(1)="itin"
                //          s="itin",  i=3 → s.substr(4)="" (empty, base case)
                getAllParts(s.substr(i+1),partitions,ans);
                
                partitions.pop_back();       // REMOVE: Backtrack this choice!
                                             // WHY: To try the NEXT partition option
                                             // This is critical for exploring ALL possibilities
                                             // EXAMPLE of importance:
                                             //   After exploring "[n,itin]", we remove "n"
                                             //   Then try "[ni,...]", "[nit,...]", etc.
                                             // IF REMOVED: Would only explore first path, missing solutions!
            }
        }
    }
    // ========== MAIN ENTRY POINT ==========
    vector<vector<string>> partition(string s) {
        // WHAT: Initialize data structures and start the backtracking process
        vector<vector<string>> ans;        // Will store all valid palindrome partitions
        vector<string> partitions;         // Current partition being built (modified during recursion)

        // CALL: Start backtracking from the beginning of string with empty partition
        getAllParts(s, partitions, ans);   // s = full string, partitions = empty initially
        return ans;                        // Return all valid partitions found
    }
};

int main() {
    // Example usage:
    // Solution sol;
    // vector<vector<string>> result = sol.partition("nitin");
    // Result would contain all ways to partition "nitin" into palindromes
    
    return 0;
}


/*
================================================================================
                        🧠 PROBLEM UNDERSTANDING
================================================================================

PROBLEM TYPE:
  → Combinatorial Search / Generate All Partitions
  → Finding ALL valid ways to partition a string with constraints
  → Classic "Backtracking" problem

CONSTRAINTS & CLUES:
  ✓ Must find ALL valid partitions (not just one)
  ✓ Each partition must satisfy palindrome property
  ✓ Order matters (maintain sequence from left to right)
  ✓ Can have overlapping subproblems (e.g., "aa" can be ["aa"] or ["a","a"])
  
KEY OBSERVATIONS:
  1. "Find ALL possible ways" → indicates backtracking/recursion needed
  2. Constraint per partition (palindrome check) → filter at each step
  3. String partitioning → reduce problem by removing processed part
  4. No ordering/sorting needed → just explore all possibilities


================================================================================
                        🔍 PATTERN RECOGNITION
================================================================================

DSA PATTERN: BACKTRACKING (Specifically: Recursive Partitioning)

Core Elements of Backtracking Present:
  1. CHOICE: What first partition to pick (1 char? 2 chars? etc.)
  2. CONSTRAINT: That partition must be a palindrome
  3. EXPLORE: Recursively solve the remaining problem
  4. BACKTRACK: Undo the choice and try next option (pop_back)

HOW TO RECOGNIZE THIS PATTERN:
  Key signals in problem statement:
    • "Find ALL combinations/permutations/partitions"
    • "Find all ways to..." 
    • "Generate all valid..."
    • Multiple solutions required, not just one
    • Constraint that filters options

When to use BACKTRACKING:
  • Combinatorial problems (combinations, permutations, subsets)
  • Puzzle solving (Sudoku, N-Queens, maze)
  • Partitioning/grouping problems
  • When brute force explore all paths is acceptable

Why not use other patterns:
  • NOT dynamic programming: DP finds optimal solution; we want ALL
  • NOT greedy: No local optimal choice applies here
  • NOT divide-and-conquer: We don't merge solutions, we explore all


================================================================================
                    ⚡ APPROACH BREAKDOWN (Interview Style)
================================================================================

1️⃣ BRUTE FORCE: (Generates all partitions, filters invalid ones)
   ────────────────────────────────────────────────────────
   Idea:
     • Generate ALL possible partitions of string (exponential number)
     • For each partition, check if all parts are palindromes
     • Keep only valid partitions
   
   Why it's inefficient:
     ✗ Generates partitions that don't satisfy constraint
     ✗ Wastes time checking invalid paths
     ✗ More computation than needed
   
   Time: O(2^N * N) Space: O(N)
     2^N partitions, each takes O(N) to check all parts


2️⃣ BETTER APPROACH: (Prune early, but no memoization)
   ──────────────────────────────────────────────
   Idea:
     • At each step, try first partition of length 1, 2, 3, ...
     • CHECK IF PALINDROME immediately
     • Only recurse if palindrome (prune invalid branches early!)
     • This is our current solution
   
   Why it's better:
     ✓ Prunes non-palindrome partitions early
     ✓ Never explores invalid branches
     ✓ Reduces unnecessary computation
     ✗ Still O(N * 2^N) worst case
   
   Time: O(N * 2^N) Space: O(N)
     Prunes aggressively but still explores all valid combinations


3️⃣ OPTIMAL APPROACH: (Add memoization for palindrome check) ⭐
   ───────────────────────────────────────────────────────
   Idea:
     • Use dynamic programming table to check palindromes in O(1)
     • Pre-compute isPalindrome[i][j] for all substrings
     • Use the same backtracking, but with O(1) palindrome lookups
   
   Why this is optimal:
     ✓ Early pruning (same as approach 2)
     ✓ Palindrome checks are O(1) instead of O(N)
     ✓ Cannot do better: must explore all 2^N partitions
   
   Time: O(N^2 + N * 2^N) → O(N * 2^N) with preprocessing
   Space: O(N^2 + N)
     N^2 for DP table, N for recursion
   
   OUR CURRENT SOLUTION is "Better Approach" (good enough for interview)
   Add DP table for optimal solution (advanced optimization)


================================================================================
                        🧩 INTUITION BUILDING
================================================================================

THE CORE IDEA IN SIMPLE TERMS:
──────────────────────────────

Imagine you have a word "nitin" and you want to break it into parts where
each part reads the same forwards and backwards.

HOW DO YOU THINK ABOUT IT?
  
  Step 1: Pick the FIRST partition
    • Could take just "n" (1 letter)
    • Could take "ni" (2 letters) - but it's not a palindrome, skip
    • Could take "nit" (3 letters) - not palindrome, skip
    • Could take "niti" (4 letters) - not palindrome, skip
    • Could take "nitin" (5 letters) - it IS a palindrome!
  
  Step 2: For each VALID first partition, solve the REST
    • Took "n", now partition "itin"
    • Took "nitin", now partition "" (empty - done!)
  
  Step 3: COMBINE all solutions
    • From "n" → partition "itin" → get solutions like ["n","i","t","i","n"]
    • From "nitin" → partition "" → get solution ["nitin"]

THE "TRICK" OR INSIGHT:
──────────────────────

REDUCE THE PROBLEM:
  Instead of thinking "partition all at once," think:
    "What if I pick the FIRST valid partition, then solve what's left?"
  
  This transforms an impossible problem into a solvable recursive one:
    • Partition("nitin") 
      = ["n"] + Partition("itin")
      + ["nitin"] + Partition("")
  
BACKTRACKING IS ABOUT UNDOING:
  The magic line: partitions.pop_back()
  
  This allows us to try different FIRST partitions:
    ✓ Try "n" as first, explore all results
    ✓ Undo that choice (remove "n")
    ✓ Try "nitin" as first, explore all results
  
  Without pop_back(), we'd only get results for first valid partition!


================================================================================
                        🔁 HOW TO RECALL THIS LATER
================================================================================

⚡ KEY SIGNALS (Identify this problem):
   1. "Find ALL..." or "Find every..." → backtracking needed
   2. String PARTITIONING → split into parts
   3. Constraint per part (palindrome, digit sum, etc.) → filter at each step
   4. Multiple solutions, not optimization → not DP/greedy

🧠 MEMORY TRICK:
   "ALL Partitions? Backtrack!"
   
   When you see "find all partitions/combinations/subsets" → immediately
   think BACKTRACKING with CHOICE-EXPLORE-BACKTRACK pattern.

PATTERN TO REMEMBER:
   Backtracking Template:
   1. Base Case: When to stop (string empty)
   2. Loop: For each possible CHOICE
   3. Prune: Check if choice is VALID
   4. Explore: RECURSE on reduced problem
   5. Backtrack: UNDO choice for next iteration

TAG LINE:
   "For all-solutions problems, explore-then-undo with backtracking!"


================================================================================
                        ⚠️ COMMON MISTAKES
================================================================================

❌ MISTAKE 1: Forgetting to BACKTRACK (pop_back)
   ────────────────────────────────────────────
   Code:
     if(isPPalin(part)){
         partitions.push_back(part);
         getAllParts(s.substr(i+1), partitions, ans);
         // partitions.pop_back();  ← MISSING!
     }
   
   PROBLEM:
     Without pop_back(), after exploring "n", we move to "ni" but "n" is
     still in partitions. Now we're building ["n", "ni", ...] instead of
     just ["ni", ...]. This mixes solutions!
   
   RESULT: Completely wrong answers, invalid partitions
   
   FIX: Always pop_back() before trying next option


❌ MISTAKE 2: Using WRONG substring indices
   ─────────────────────────────────────────
   Code:
     string part = s.substr(0, i);        // ← Takes only i chars, not i+1
     getAllParts(s.substr(i), partitions, ans);
   
   PROBLEM: Off-by-one error
     For i=0: part = "" (empty), getAllParts(s, ...) (infinite loop!)
     For i=1: part = first char, getAllParts(s.substr(1), ...) (correct)
   
   FIX: Use substr(0, i+1) for taking i+1 characters from start


❌ MISTAKE 3: Not checking palindrome BEFORE recursing
   ────────────────────────────────────────────────
   Code:
     for(int i=0; i<s.size(); i++){
         string part = s.substr(0, i+1);
         partitions.push_back(part);           // Push without checking!
         getAllParts(s.substr(i+1), partitions, ans);
         partitions.pop_back();
     }
   
   PROBLEM:
     You'd add non-palindromes to solution. Also wastes recursion on
     branches that can't lead to valid solutions.
   
   FIX: Check if(isPPalin(part)) before push_back


❌ MISTAKE 4: Using pass-by-reference for 'partitions'
   ──────────────────────────────────────────────────
   Code:
     void getAllParts(string s, vector<string>& partitions, ...)
                                 ↑ reference instead of copy
   
   PROBLEM:
     If partitions is passed by reference, ALL recursive calls share
     the SAME vector. You can't have separate partition paths!
   
   RESULT:
     Solutions would be intertwined and wrong
   
   FIX: Pass partitions by VALUE (copy), not by reference
       Our code is CORRECT: vector<string> partitions (no &)


❌ MISTAKE 5: Misunderstanding the recursion termination
   ─────────────────────────────────────────────────────
   Code:
     if(s.size() == 0) {
         ans.push_back(partitions);
     }
     // Missing return statement
   
   PROBLEM:
     Without return, code continues and tries to partition empty string
     in the for loop, causing unnecessary iterations
   
   FIX: Add return after pushing to ans


❌ MISTAKE 6: Creating palindrome check inefficiently
   ─────────────────────────────────────────────────
   Code:
     bool isPPalin(string s) {
         // Doing reverse every time for same strings
         string s2 = s;
         reverse(s2.begin(), s2.end());
         return s == s2;
     }
   
   PROBLEM:
     This works but is inefficient. For "nitin", we might check "nit"
     multiple times across different recursive paths.
   
   OPTIMIZATION: Use DP table (2D array) to store palindrome results
                 Pre-compute in O(N^2), lookup in O(1)


❌ MISTAKE 7: Off-by-one in palindrome check
   ──────────────────────────────────────────
   Code:
     bool isPPalin(string s) {
         for(int i = 0; i < s.size()/2; i++) {
             if(s[i] != s[s.size() - i]) {  // ← WRONG INDEX
                 return false;
             }
         }
         return true;
     }
   
   PROBLEM: s.size() - i is out of bounds or wrong
     If s="abc" (size=3), for i=0: compare s[0] and s[3] (out of bounds!)
   
   FIX: Use s.size() - 1 - i
        if(s[i] != s[s.size() - 1 - i])


================================================================================
                        📊 COMPLEXITY ANALYSIS
================================================================================

TIME COMPLEXITY: O(N * 2^N)
─────────────────────────
Reasoning:

  Part 1: How many partitions are there?
    • For string of length N, there are at most 2^(N-1) partitions
    • Example: "abc" → ["abc"], ["ab","c"], ["a","bc"], ["a","b","c"]
    •           That's 2^2 = 4 partitions
    • Why 2^(N-1)? At each position between characters, we can choose
      to split or not split. With N characters, there are N-1 positions.
      Each position: 2 choices → 2^(N-1) partitions
  
  Part 2: For each partition, how much work?
    • We store the partition in ans: O(N) to push all pieces
    • Creating substring s.substr(i+1): O(N) in worst case
    • Palindrome check isPPalin: O(N)
    • So per partition attempt: O(N)
  
  Part 3: Total
    • Number of valid palindrome partitions: at most 2^N
    • Work per partition: O(N)
    • Total: O(N * 2^N)

Example:
  For "aaa": all partitions are palindromes
    ["aaa"], ["a","aa"], ["aa","a"], ["a","a","a"]
    That's 4 = 2^(3-1), and we process each: 3 * 4 = 12 work


SPACE COMPLEXITY: O(N)
──────────────────────
Reasoning:

  Part 1: Recursion call stack depth
    • Each recursive call takes one more character
    • Maximum depth: N (when we take one character at a time)
    • Recursion stack space: O(N)
  
  Part 2: Partition vector (not counted in space complexity of algorithm)
    • Current partition being built: at most N characters split into pieces
    • But this is modified in-place with push/pop
    • Used space at any point: O(N)
  
  Part 3: Result array
    • This stores all answers (not part of algorithm space complexity)
    • Counts as output space, not algorithm space
  
  Part 4: Substrings created
    • Each s.substr(i+1) creates a new string: O(N)
    • But only one at a time (not all simultaneously)
    • Space: O(N)
  
  TOTAL: O(N) space excluding output

Why not O(2^N) for storing all partitions?
  • The result array does store all partitions (output size)
  • But we don't count output space in complexity analysis
  • Only intermediate/working space: O(N)


================================================================================
                    🔄 ALTERNATIVE APPROACHES
================================================================================

ALTERNATIVE 1: Iterative Solution with Stack
──────────────────────────────────────────────
Instead of recursion, use an explicit stack to simulate the call stack:
  • Stack stores: (remaining_string, current_partition)
  • Pop from stack, try all partitions, push new states
  • Continue until stack is empty

Pros:
  ✓ Avoids recursion depth issues (stack overflow risk)
  ✓ Easier to debug with explicit state
  
Cons:
  ✗ More complex code to write
  ✗ Manual stack management
  ✗ Same time/space complexity
  ✗ Recursion is cleaner for this problem


ALTERNATIVE 2: Using Dynamic Programming for Palindrome Check
──────────────────────────────────────────────────────────────
Pre-compute which substrings are palindromes:

  1. Create DP[i][j] = true if s[i...j] is palindrome (O(N^2))
  2. Use this table to check palindromes in O(1)
  3. Same backtracking, but faster palindrome lookups
  
Improvement:
  Time: O(N^2) preprocessing + O(N * 2^N) = O(N * 2^N)
  But with MUCH smaller constant due to O(1) palindrome checks
  
When to use:
  • When string is very long
  • When palindrome check is bottleneck
  • In production code for optimization


ALTERNATIVE 3: Backtracking with Memoization (Not directly applicable)
────────────────────────────────────────────────────────────────
Traditional DP memoization won't help here because:
  • We need ALL solutions, not optimal solution
  • The partition path matters (order of partitions)
  • Different partition paths count as different solutions
  
Memoization works only when: subproblems have one optimal answer
Here: subproblem "partition 'itin'" has multiple valid answers


ALTERNATIVE 4: BFS / Queue-Based Approach
───────────────────────────────────────────
Use BFS with queue instead of DFS with recursion:
  • Queue stores (remaining_string, current_partition)
  • Process level by level
  • Add solutions when string is empty

Pros:
  ✓ Level-by-level processing (might be clearer)
  
Cons:
  ✗ More complex than recursion
  ✗ Same complexity
  ✗ Not typical for this problem


BEST PRACTICE:
───────────────
Use the recursive backtracking approach (our solution) for interviews.
It's elegant, standard, and shows good understanding of backtracking.

For optimization:
  • Add DP table for palindrome check (if string is very long)
  • Otherwise, current solution is clear and efficient enough


================================================================================
*/