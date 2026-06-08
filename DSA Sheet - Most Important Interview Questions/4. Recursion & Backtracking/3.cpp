/*
================================================================================
PROBLEM: Palindrome Partitioning (LeetCode 131)
================================================================================

Goal:
  Given a string s, return every possible way to split it so that every chosen
  piece is a palindrome.

Example:
  s = "aab"

  Valid partitions:
    ["a", "a", "b"]   -> every single character is a palindrome
    ["aa", "b"]       -> "aa" and "b" are palindromes

  Invalid partition:
    ["aab"]           -> "aab" is not a palindrome

Core idea:
  At every index, choose a prefix of the remaining string.
  If that prefix is a palindrome, keep it and recursively solve the rest.
  After recursion returns, undo the choice so the next prefix can be tried.

Pattern:
  Backtracking / DFS over all possible string partitions.
================================================================================
*/

#include <algorithm> // Needed for reverse().
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    /*
    Helper: checks whether the complete string s is a palindrome.

    What it does:
      Makes a reversed copy of s and compares it with the original.

    Why it is necessary:
      In palindrome partitioning, every selected piece must be valid before we
      recurse. This helper is the "valid choice?" filter.

    What would break if removed:
      getAllParts() would not know which prefixes are legal. It would either
      include non-palindrome pieces or need another palindrome-checking method.

    Dry run:
      s = "aba"
        s2 = "aba"
        reverse(s2) keeps it "aba"
        s == s2, so return true

      s = "ab"
        s2 = "ab"
        reverse(s2) makes it "ba"
        s != s2, so return false

    Edge cases:
      - Single character like "x": true.
      - Empty string "": true mathematically, although this function is only
        called with non-empty prefixes in this code.
      - Case-sensitive: "Aa" is not considered a palindrome.

    Complexity:
      Time  : O(k), where k is the length of s, because reversing/comparing
              touches the characters.
      Space : O(k), because s2 is a copied string.
    */
    bool isPPalin(string s){
        string s2=s;                           // Copy the substring so the original remains available for comparison.
                                               // If removed, there is no separate reversed version to compare against.

        reverse(s2.begin(),s2.end());          // Reverse only the copied string.
                                               // If removed, s2 always equals s, so every string would look like a palindrome.

        return s==s2;                          // Return true only when original and reversed strings match.
                                               // If removed, the helper cannot tell recursion whether this prefix is valid.
    }

    /*
    Recursive backtracking function.

    Parameters:
      s          -> the remaining suffix still waiting to be partitioned
      partitions -> the current path, meaning palindrome pieces chosen so far
      ans        -> the final list of all valid partition paths

    Mental model:
      "From the remaining string, try every possible prefix. If the prefix is a
      palindrome, lock it in temporarily and solve the rest."

    Why partitions is passed by value here:
      Each recursive call receives its own copy of the current path. The code
      still calls pop_back() after recursion, which is harmless here and also
      matches the standard backtracking template. If partitions were passed by
      reference, that pop_back() would become essential because all calls would
      share the same vector.

    Dry run for s = "aab":

      getAllParts("aab", [], ans)
        i = 0, part = "a" palindrome
          partitions = ["a"]
          getAllParts("ab", ["a"], ans)
            i = 0, part = "a" palindrome
              partitions = ["a", "a"]
              getAllParts("b", ["a", "a"], ans)
                i = 0, part = "b" palindrome
                  partitions = ["a", "a", "b"]
                  getAllParts("", ["a", "a", "b"], ans)
                    s is empty, save ["a", "a", "b"]
            i = 1, part = "ab" not palindrome, skip
        i = 1, part = "aa" palindrome
          partitions = ["aa"]
          getAllParts("b", ["aa"], ans)
            saves ["aa", "b"]
        i = 2, part = "aab" not palindrome, skip

      Final ans = [["a","a","b"], ["aa","b"]]

    Edge cases:
      - Empty input string: base case pushes an empty partition [].
      - All characters different, like "abc": only ["a","b","c"] is valid.
      - All characters same, like "aaa": many valid partitions, worst case.
      - Long strings: exponential output size can become large.

    Complexity:
      Time  : O(N * 2^N) commonly stated for this style of solution, because
              there are exponentially many split patterns and each path/prefix
              work can cost up to O(N). With repeated substr/copy/reverse, the
              constant factor is higher.
      Space : O(N) auxiliary recursion depth, excluding the output. Because
              this implementation passes strings/vectors by value and creates
              substrings, temporary copying can add extra overhead along paths.
              The answer itself can require O(N * 2^N) output space.
    */
    void getAllParts(string s, vector<string> partitions ,vector<vector<string>> &ans){
        // Base case: no characters remain, so the current path covers the whole original string.
        if(s.size()==0){
            // Why necessary:
            //   This is the moment a full valid partition has been built.
            // What would break if removed:
            //   Valid answers would never be stored, so partition() would return an empty result.
            // Example:
            //   original "aa" -> choose "aa" -> remaining s becomes "" -> save ["aa"].
            ans.push_back(partitions);

            // Why necessary:
            //   Stop this branch after saving the complete partition.
            // What would break if removed:
            //   The for loop below has no useful work for an empty string, but returning makes the
            //   base case explicit and prevents accidental future code from running on completed paths.
            return;
        }

        // Try every possible prefix of the current remaining string.
        // If s = "aab", prefixes tried are "a", then "aa", then "aab".
        for(int i=0;i<s.size();i++){
            // Candidate piece is the prefix ending at index i.
            // Why i+1:
            //   substr(0, length) needs a length, not an ending index.
            //   For i = 0 we want length 1, for i = 1 we want length 2, etc.
            // What would break if changed/removed:
            //   Wrong substring bounds can skip characters, create empty pieces, or cause infinite recursion.
            string part=s.substr(0,i+1);

            // Only palindrome prefixes are allowed into the current partition.
            // Why necessary:
            //   This prunes invalid branches early.
            // What would break if removed:
            //   Non-palindrome pieces like "ab" could appear in the answer.
            if(isPPalin(part)){
                // Choose: add the valid palindrome prefix to the current path.
                // Example:
                //   s = "aab", part = "aa" -> partitions becomes ["aa"].
                // What would break if removed:
                //   The recursive call would solve the suffix, but the chosen prefix would be missing
                //   from the final saved partition.
                partitions.push_back(part);

                // Explore: recursively partition the remaining suffix after the chosen prefix.
                // Example:
                //   s = "aab", i = 1, part = "aa" -> s.substr(2) is "b".
                // Why necessary:
                //   The problem reduces from "partition the whole string" to "partition what is left."
                // What would break if removed:
                //   The algorithm would only choose one piece and never complete multi-piece answers.
                getAllParts(s.substr(i+1),partitions,ans);

                // Undo: remove the last chosen prefix before trying the next prefix.
                // In this exact code partitions is passed by value, so each call has its own copy.
                // Still, this line keeps the local path correct for the next loop iteration.
                // If partitions were passed by reference, removing this line would mix choices from
                // different branches and produce wrong partitions.
                partitions.pop_back();
            }
        }
    }

    /*
    Public entry point expected by LeetCode.

    What it does:
      Creates the result containers, starts DFS/backtracking, and returns all
      valid palindrome partitions.

    What would break if removed:
      There would be no clean function for the judge/user to call.
    */
    vector<vector<string>> partition(string s) {
        // ans stores every complete valid partition found by the recursion.
        // Output can be large: for a string like "aaaa", many split patterns are valid.
        vector<vector<string>> ans;

        // partitions stores the current path being built.
        // It starts empty because no prefix has been chosen yet.
        vector<string> partitions;

        // Start from the full string.
        // Example:
        //   partition("aab") begins with getAllParts("aab", [], ans).
        getAllParts(s, partitions, ans);

        // Return all collected paths.
        // If s = "aab", returns [["a","a","b"], ["aa","b"]].
        return ans;
    }
};

int main() {
    // This main is only a placeholder.
    // LeetCode directly calls Solution::partition(), so no manual input/output is needed here.
    // If this line were removed in a normal local C++ program, linking could fail because the
    // executable would have no entry point. On LeetCode, main is provided by the platform.
    return 0;
}

/*
================================================================================
1. 🧠 Problem Understanding
================================================================================

What type of problem is this?
  This is a "generate all valid answers" problem. More specifically, it is a
  string partitioning problem with a validity constraint on each chosen piece.

What are the key constraints/clues?
  - The phrase "all possible ways" is the biggest clue.
  - Each piece must satisfy a local condition: it must be a palindrome.
  - The original order of characters cannot change.
  - We are not asked for the minimum number of cuts or the best partition; we
    are asked to list every valid partition.

Small example:
  s = "aba"

  Possible split patterns:
    "a" | "b" | "a"  -> valid
    "a" | "ba"       -> invalid because "ba" is not palindrome
    "ab" | "a"       -> invalid because "ab" is not palindrome
    "aba"            -> valid

  Answer:
    [["a","b","a"], ["aba"]]

================================================================================
2. 🔍 Pattern Recognition
================================================================================

Pattern used:
  Backtracking / DFS recursion.

Why this pattern fits:
  Backtracking is used when we need to build answers step by step, explore a
  choice, and then undo that choice to explore another possibility.

How to recognize this pattern later:
  Look for these signals:
    1. "Find all..."
    2. "Generate all..."
    3. "All possible partitions/combinations/subsets/permutations"
    4. A condition that each partial choice must satisfy

Backtracking template:
  1. If the current state is complete, save it.
  2. Loop through all choices.
  3. Skip invalid choices.
  4. Choose one option.
  5. Recurse.
  6. Undo the choice.

================================================================================
3. ⚡ Approach Breakdown (Interview Style)
================================================================================

Brute force idea:
  Generate every possible way to place cuts between characters, then check each
  complete partition at the end.

  Problem:
    This wastes work because it builds many partitions that contain obvious
    non-palindrome pieces.

Better approach:
  While building the partition, check each chosen prefix immediately. Recurse
  only when the prefix is a palindrome.

  Benefit:
    Invalid branches are pruned early. For example, from "aab", the prefix
    "aab" is rejected immediately.

Optimal approach:
  Use the same backtracking idea, but precompute palindrome information with DP:
    dp[i][j] = whether s[i...j] is a palindrome.

  Why chosen in many optimized solutions:
    It changes palindrome checking from O(length) to O(1), while still exploring
    all valid partitions.

  Why this code is still interview-worthy:
    It clearly shows the main backtracking idea. The DP palindrome table is an
    optimization, not the core insight.

================================================================================
4. 🧩 Intuition Building
================================================================================

Core idea in simple terms:
  Do not try to split the whole string in one thought. Decide the first piece,
  then let recursion handle the rest.

For s = "aab":
  First piece can be:
    "a"   -> valid, now solve "ab"
    "aa"  -> valid, now solve "b"
    "aab" -> invalid, skip

The trick:
  A complete answer is just a sequence of locally valid palindrome choices that
  consumes the whole string.

Why backtracking feels natural:
  You are asking:
    "What if I choose this prefix?"
  Then after exploring:
    "Okay, undo that and try a longer prefix."

================================================================================
5. 🔁 How to Recall Later
================================================================================

Key signals:
  1. Need all answers, not just one answer.
  2. Need to split a string into pieces.
  3. Each piece has a condition, such as palindrome.

One-line memory trick:
  "All valid splits means choose a prefix, recurse on the suffix, then undo."

================================================================================
6. ⚠️ Common Mistakes
================================================================================

1. Forgetting the base case:
   If you do not save the path when s becomes empty, you lose complete answers.

2. Checking palindrome too late:
   If you recurse before checking, you waste time exploring invalid partitions.

3. Off-by-one errors in substr:
   substr(0, i+1) means "take the first i+1 characters."
   substr(i+1) means "skip the chosen prefix and keep the rest."

4. Forgetting to undo the choice:
   In standard reference-based backtracking, missing pop_back() causes branches
   to leak into each other. In this code, partitions is copied, but pop_back()
   still keeps the local loop state clean and matches the normal pattern.

5. Confusing this with palindrome partitioning minimum cuts:
   This problem asks for all partitions. Minimum cuts is an optimization problem
   and usually uses dynamic programming differently.

6. Ignoring output size:
   Even the best algorithm can be exponential because the number of valid
   answers itself can be exponential.

================================================================================
7. 📊 Complexity Analysis
================================================================================

Time complexity:
  O(N * 2^N), commonly stated for palindrome partition generation.

Reason:
  - There are N - 1 possible cut positions between characters.
  - Each position can be "cut" or "not cut", so there can be up to 2^(N-1)
    partition patterns.
  - For each path, copying/storing/checking pieces can cost up to O(N).

Important practical note:
  This exact implementation also creates substring copies and reverses strings
  during palindrome checks, so it has extra copying overhead. The exponential
  nature remains the main cost.

Space complexity:
  O(N) auxiliary space excluding the output.

Reason:
  - Maximum recursion depth is N when choosing one character at a time.
  - The current partition path can contain at most N pieces.

Output space:
  O(N * 2^N) in the worst case, because all partitions may need to be returned.
  Example: for "aaaa", every split pattern is valid.

================================================================================
8. 🔄 Alternative Approaches
================================================================================

Alternative 1: Backtracking with index instead of substring
  Instead of passing the remaining substring, pass a start index into the
  original string. This avoids repeatedly creating new suffix strings.

Alternative 2: DP precomputation for palindrome checks
  Build a table where dp[i][j] says whether s[i...j] is a palindrome. Then the
  recursion can check validity in O(1).

Alternative 3: Iterative DFS using a stack
  Simulate recursion manually with a stack that stores the current index and
  current partition. This avoids recursive calls but is usually more verbose.

Alternative 4: BFS using a queue
  Build partitions level by level. This also works, but DFS/backtracking is
  more common and cleaner for interviews.

Best interview answer:
  Start with recursive backtracking. If asked to optimize, mention DP
  precomputation for palindrome checks and index-based recursion to reduce
  copying.
================================================================================
*/
