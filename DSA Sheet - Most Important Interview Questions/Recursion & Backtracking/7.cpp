#include <iostream>
#include <vector>
using namespace std;

/*
════════════════════════════════════════════════════════════════════════════════
                    KNIGHT'S TOUR VALIDATION - BACKTRACKING
════════════════════════════════════════════════════════════════════════════════

PROBLEM STATEMENT:
─────────────────
Given an n×n grid where each cell contains a number, validate whether the grid
represents a valid Knight's Tour. A valid tour means:
  1. Each cell contains a unique number from 0 to n²-1
  2. Starting from position (0,0) with value 0
  3. Each consecutive number is reachable from the previous by a knight's move
  4. All numbers form a continuous sequence (0, 1, 2, ..., n²-1)

Knight Move Rules:
  • A knight moves in an "L" shape: 2 squares in one direction, 1 in perpendicular
  • 8 possible moves: (±2,±1) and (±1,±2)

REAL-WORLD ANALOGY:
──────────────────
Imagine a medieval knight on a chessboard who must visit every square exactly
once using only knight moves. We're given a completed path (grid with numbers
1-64 or 1-n²). We need to verify if this path is actually valid—that each
consecutive square is reachable by a legal knight move.

KEY PROPERTIES:
───────────────
✓ Backtracking algorithm (recursive with path exploration)
✓ Validation problem (not construction)
✓ Path verification with constraint checking
✓ Uses DFS (depth-first search) through the path
✓ Early termination on invalid path detection

EXAMPLES:
─────────
Example 1: Valid 5×5 Knight's Tour
  Grid[0][0] = 0, Grid[r1][c1] = 1 (knight move away), etc.
  Result: TRUE

Example 2: Invalid Knight's Tour
  Grid[0][0] = 0, but Grid[1][1] = 1 (knight CANNOT reach 1,1 from 0,0)
  Result: FALSE

════════════════════════════════════════════════════════════════════════════════
*/

class Solution {
public:
    // 🔴 WHAT: Recursive validation function for knight's tour
    // ──────────────────────────────────────────────────────────────────────────
    // PURPOSE: Check if we can visit all n²-1 values sequentially using knight moves
    //
    // PARAMETERS:
    //   grid   → The input grid with numbers representing knight's path
    //   r, c   → Current position (row, column)
    //   n      → Grid dimension (n×n)
    //   expVal → Expected value at current position (0, 1, 2, ..., n²-1)
    //
    // RETURNS: true if valid knight's tour from this point, false otherwise
    bool isValid(vector<vector<int>>& grid, int r, int c, int n, int expVal) {
        
        // 🔴 BOUNDARY CHECK + VALUE VALIDATION
        // ──────────────────────────────────────────────────────────────────────────
        // WHAT: Check three conditions:
        //   1. r < 0 || c < 0 → Position is out of bounds (top/left)
        //   2. r >= n || c >= n → Position is out of bounds (bottom/right)
        //   3. grid[r][c] != expVal → Current cell doesn't have expected value
        //
        // WHY: We need ALL three conditions to be valid:
        //   • Must be within grid boundaries (else invalid move)
        //   • Must have the exact expected sequential value
        //
        // IF REMOVED: We'd process invalid positions or mismatched values,
        //             leading to false positives
        //
        // EDGE CASES:
        //   • Position (0,0): Should have grid[0][0] = 0 (starting value)
        //   • Boundary positions: Must still follow knight move pattern
        //   • Out-of-bounds knight moves: Many moves from edges go out-of-bounds
        if (r < 0 || c < 0 || r >= n || c >= n || grid[r][c] != expVal) {
            return false;
        }
        
        // 🔴 SUCCESS CONDITION - REACHED END OF TOUR
        // ──────────────────────────────────────────────────────────────────────────
        // WHAT: Check if we've successfully visited all cells
        // FORMULA: n*n - 1 is the last value in a complete tour
        //          (0, 1, 2, ..., n²-1 → total n² values)
        //
        // WHY: If current value equals the last expected value, we've completed
        //      the entire knight's tour successfully!
        //
        // IF REMOVED: We'd continue recursing even after success,
        //             wasting computation
        //
        // EXAMPLE: For 5×5 grid (n=5):
        //   n*n - 1 = 25 - 1 = 24
        //   So we need to visit values 0 through 24
        if (expVal == n * n - 1) {
            return true;  // ✅ Valid tour found!
        }

        // 🔴 DEFINE ALL POSSIBLE KNIGHT MOVES
        // ──────────────────────────────────────────────────────────────────────────
        // WHAT: 8 possible moves a knight can make from any position
        // COORDINATES: (row_offset, col_offset)
        //
        // Visual representation:
        //   (-2,+1)   (-2,-1)     Knight positions relative to center
        //   (-1,+2)            (-1,-2)
        //          [Knight]
        //   (+1,+2)            (+1,-2)
        //   (+2,+1)   (+2,-1)
        //
        // WHY: We need all 8 moves to check every possible next position
        //
        // NOTATION: {dr, dc} means move by dr rows and dc columns
        // Total combinations: 2 choices for row (±2 or ±1)
        //                    × 2 choices for col offset
        //                    × 2 choices for signs
        //                    = 8 total unique moves
        vector<pair<int, int>> moves = {
            {-2, +1}, {-2, -1}, {-1, -2}, {+1, -2},
            {+2, -1}, {+2, +1}, {+1, +2}, {-1, +2}
        };

        // 🔴 TRY EACH POSSIBLE KNIGHT MOVE (BACKTRACKING)
        // ──────────────────────────────────────────────────────────────────────────
        // WHAT: For each of the 8 possible knight moves, recursively check if the
        //       next position has the expected sequential value
        //
        // LOOP EXPLANATION:
        //   auto [dr, dc] → Structured binding: unpacks pair into dr and dc
        //   r + dr, c + dc → New position after applying knight move
        //   expVal + 1 → Next expected value in the sequence
        //
        // WHY BACKTRACKING: We try each move independently. If one succeeds,
        //                   return true (tour is valid). If all fail, return false.
        //
        // DRY RUN on 5×5 grid, starting at (0,0) expecting value 0:
        // ────────────────────────────────────────────────────────
        // Step 1: At (0,0), expVal = 0
        //   Check: grid[0][0] == 0? ✓
        //   Check: Is 0 == 24 (n²-1)? ✗ Continue...
        //
        // Step 2: Try move 1: {-2,+1} → position (-2,+1)
        //   Check: -2 < 0? YES → Return false (out of bounds)
        //   Backtrack to next move
        //
        // Step 3: Try move 2: {-2,-1} → position (-2,-1)
        //   Check: Out of bounds → Return false
        //   Backtrack to next move
        //
        // Step 4: Try move 3: {-1,-2} → position (-1,-2)
        //   Check: Out of bounds → Return false
        //   Backtrack to next move
        //
        // Step 5: Try move 4: {+1,-2} → position (1,-2)
        //   Check: -2 < 0? YES → Return false
        //   Backtrack to next move
        //
        // Step 6: Try move 5: {+2,-1} → position (2,-1)
        //   Check: -1 < 0? YES → Return false
        //   Backtrack to next move
        //
        // Step 7: Try move 6: {+2,+1} → position (2,+1)
        //   Check: 0 ≤ 2 < n? ✓, 0 ≤ 1 < n? ✓
        //   Check: grid[2][1] == 1 (expected)? 
        //   If YES → Recurse with (2,1) and expVal=1
        //   If NO → Return false, try next move
        //
        // If any recursion returns true, entire call returns true
        // If all 8 moves return false, this position is invalid
        //
        // KEY INSIGHT: This is a depth-first search (DFS) through the tour path!
        // We go as deep as possible (visiting sequential numbers) before backtracking.
        //
        // TIME AT THIS STEP: For each position, we try max 8 moves
        //                    Each move is O(1) lookup
        for (auto [dr, dc] : moves) {
            if (isValid(grid, r + dr, c + dc, n, expVal + 1)) {
                return true;  // Found valid continuation of tour
            }
        }
        
        // 🔴 ALL MOVES FAILED - THIS PATH IS INVALID
        // ──────────────────────────────────────────────────────────────────────────
        // WHAT: If we reach here, none of the 8 knight moves led to a valid tour
        // WHY: The current position doesn't have a valid next position matching
        //      the expected sequential value
        return false;
    }

    // 🔴 WHAT: Public wrapper function to initiate validation
    // ──────────────────────────────────────────────────────────────────────────
    // PURPOSE: Start the knight's tour validation from the beginning
    //
    // WHY: Provides clean interface:
    //   • User doesn't need to know about helper function
    //   • Hardcodes starting values: position (0,0) and expected value 0
    //   • Extracts grid size using grid.size()
    //
    // ASSUMPTIONS:
    //   • Tour must start at (0,0)
    //   • First value must be 0
    //   • Grid is square (n×n)
    bool checkValidGrid(vector<vector<int>>& grid) {
        // 🔴 START VALIDATION: Begin at (0,0) expecting value 0
        // WHY (0,0): Knight's tour always starts at top-left corner
        // WHY 0: First value in the sequence is always 0
        // grid.size(): Assumes square grid (n×n)
        return isValid(grid, 0, 0, grid.size(), 0);
    }
};

int main() {
    // your code here
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
   • Path Validation Problem
   • Constraint Satisfaction (backtracking)
   • Graph traversal verification
   • Sequential validation

📌 Key Characteristics:
   ✓ Input: 2D grid with pre-filled numbers
   ✓ Must verify, NOT construct the path
   ✓ Specific movement constraints (knight moves only)
   ✓ Sequential value requirement (0, 1, 2, ...)
   ✓ Fixed starting point: (0,0) with value 0

🔑 Core Constraints:
   • All cells from 0 to n²-1 must be visited exactly once
   • Tour must start at (0,0) with value 0
   • Each step must follow a legal knight move (L-shape)
   • Values must be in strictly sequential order
   • Grid is always square (n×n)

❌ What This Problem IS NOT:
   • NOT about finding the knight's tour (construction)
   • NOT about finding optimal or longest path
   • NOT about counting tours
   • NOT about permutations or combinations

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 2️⃣  PATTERN RECOGNITION - Backtracking + DFS
└─────────────────────────────────────────────────────────────────────────────────

🎨 DSA Patterns Used:
   1. BACKTRACKING: Try each possibility, undo if invalid
   2. DEPTH-FIRST SEARCH (DFS): Explore path sequentially to end
   3. RECURSIVE VALIDATION: Process sequential values recursively

Where This Pattern Appears:
┌────────────────────────────────────────────────────────────────┐
│ EXACT MATCHES (Same pattern):                                 │
│ • Knight's tour validation                                    │
│ • Hamiltonian path verification                               │
│ • Route validation in graphs                                  │
│                                                                │
│ RELATED PROBLEMS (Similar approach):                          │
│ • N-Queens solver                                             │
│ • Sudoku solver                                               │
│ • Word search in grid                                         │
│ • Rat in maze                                                 │
│ • Graph cycle detection                                       │
│                                                                │
│ VARIATIONS (Different constraints):                           │
│ • Verify if path visits all cells                            │
│ • Validate tour with forbidden cells                         │
│ • Check if specific order is valid                           │
└────────────────────────────────────────────────────────────────┘

🔍 Signals to Recognize This Pattern:
   Signal #1: "Validate a pre-made path/tour"
   Signal #2: "Check if sequence follows movement rules"
   Signal #3: "Each position should have specific value/property"
   Signal #4: "Need to verify constraints at each step"

🧠 Memory Trick:
   "VERIFY THE TOUR: Check each position is reachable by VALID MOVE 
    and has SEQUENTIAL VALUE"

Key Difference from Construction:
   Construction: Generate a valid tour (HARD, needs optimization)
   Validation: Check if given tour is valid (EASIER, just verify)

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 3️⃣  APPROACH BREAKDOWN - Interview Style Evolution
└─────────────────────────────────────────────────────────────────────────────────

APPROACH 1: NAIVE/BRUTE FORCE
═══════════════════════════════════════════════════════════════════════════════
Time: O(n⁴) or worse  |  Space: O(1)

Logic:
  • Check all cells contain 0 to n²-1 (sort and verify)
  • Check if starting cell (0,0) has value 0
  • For each consecutive pair (i, i+1), find their positions
  • Check if positions are knight-move apart
  • Repeat for all n² pairs

Problem:
  ✗ Very inefficient: must search grid for each value
  ✗ No early termination: even one error check takes long

────────────────────────────────────────────────────────────────────────────────

APPROACH 2: BETTER - Indexed Lookup
═══════════════════════════════════════════════════════════════════════════════
Time: O(n²)  |  Space: O(n²)

Logic:
  • Build position map: value → (row, col)
  • For each value 0 to n²-1:
    • Get position of value i and i+1 from map
    • Check if they differ by a knight move
  • Return true if all consecutive pairs are valid knight moves

Better because:
  ✓ O(n²) lookup instead of searching
  ✓ Can return early on first invalid pair

Still not ideal:
  ✗ Requires extra O(n²) space for position map
  ✗ Must verify all pairs even if earlier pair invalid

────────────────────────────────────────────────────────────────────────────────

APPROACH 3: OPTIMAL - BACKTRACKING/DFS ⭐⭐⭐ (USED IN CODE)
═══════════════════════════════════════════════════════════════════════════════
Time: O(8^n²) worst, but typically much faster  |  Space: O(n²) recursion

Logic:
  • Start at (0,0) expecting value 0
  • For each position, check:
    1. Within bounds
    2. Has correct sequential value
    3. Is last value? Return true
  • Try all 8 knight moves to next position
  • Recursively verify from new position
  • Backtrack on any failure

WHY THIS APPROACH IS CHOSEN:
  ✓ Natural recursive structure matches the problem
  ✓ Early termination: stops as soon as path invalid
  ✓ Follows the path sequentially (0→1→2→...→n²-1)
  ✓ Elegant: directly checks constraints
  ✓ No extra data structures needed (no position map)
  ✓ No scanning for values (just validate what's there)

Key Advantage:
  The moment you find a position where no valid next position exists,
  you immediately return false. No need to check beyond that point.

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 4️⃣  INTUITION BUILDING - Simple Explanation
└─────────────────────────────────────────────────────────────────────────────────

🎬 Thought Experiment - The Treasure Hunt:

Imagine a treasure map with clues numbered 0-24 on a 5×5 grid.
You start at position (0,0) and find clue #0.
Next you must move to where clue #1 is, following knight movement rules only.
Then find clue #2 from there (again, knight move only).
Continue until you reach clue #24.

Question: "Is this a valid treasure hunt path?"

Simple Approach (NAIVE):
  • Check if (0,0) has clue 0 ✓
  • Search entire grid for clue 1 (scan all 25 cells)
  • Check if position of clue 1 is knight-move away from (0,0)
  • Search entire grid for clue 2 (scan all 25 cells again)
  • Check if knight-move away from clue 1
  • Repeat... SO MUCH SEARCHING!

Smart Approach (BACKTRACKING):
  • At position (0,0) with clue 0, ask: "Where should clue 1 be?"
  • Try moving as a knight in 8 directions
  • At each direction, check: "Is there clue 1?"
  • If yes → recursively check clue 2 from there
  • If no → try next direction (backtrack)
  • If any direction succeeds → path is valid!
  • If all 8 directions fail → this path is invalid

Why Backtracking Wins:
  • Follows the path in order (0→1→2→...)
  • Each position tells you exactly what value to expect next
  • Fail fast: stop as soon as you can't find expected next clue
  • No searching: just look at predetermined next positions

═══════════════════════════════════════════════════════════════════════════════

Visual Example: 5×5 Knight's Tour Validation

Grid:
  [0]  [ ]  [ ]  [1]  [ ]
  [ ]  [ ]  [ ]  [ ]  [ ]
  [ ]  [ ]  [ ]  [ ]  [ ]
  [ ]  [ ]  [ ]  [ ]  [ ]
  [ ]  [2]  [ ]  [ ]  [ ]

Validation Process:
  
  Step 1: Check (0,0)
    Value: 0 ✓
    Is this the last value (24)? No → Continue
    Try 8 knight moves:
      (-2,1): Out of bounds
      (-2,-1): Out of bounds
      (-1,-2): Out of bounds
      (1,-2): Out of bounds
      (2,-1): Out of bounds
      (2,1): Position (2,1) - check value
      (1,2): Position (1,2) - check value
      (-1,2): Out of bounds
  
  Step 2: Try move to (2,1)
    Check: grid[2][1] == 1? If YES → Recurse with expVal=1
           If NO → Return false (backtrack)
  
  Step 3: At (2,1) expecting value 1
    Value: 1 ✓
    Is this last value? No → Continue
    Try 8 moves from (2,1) looking for value 2
    ...and so on

Core Idea:
  "Follow the sequential path. At each step, verify it's reachable by 
   knight move. If you reach the end (n²-1), path is valid. If you get 
   stuck (no next valid position), path is invalid."

The "Trick" / Key Insight:
  Instead of searching grid for each value, FOLLOW THE TOUR FORWARD.
  Each position (after validation) tells you what the NEXT value should be.
  Just recursively follow until you either:
    1. Reach the end → Valid! ✓
    2. Can't proceed → Invalid! ✗

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 5️⃣  HOW TO RECALL LATER - Memory Anchors
└─────────────────────────────────────────────────────────────────────────────────

When You See a Grid Problem, Ask Yourself:

❓ Question 1: "Do I need to VERIFY or CONSTRUCT?"
   If VERIFY → Check this approach
   If CONSTRUCT → Need different algorithm

❓ Question 2: "Is the path already laid out (with numbers/values)?"
   If YES → Validate by following it
   If NO → Need to build the path

❓ Question 3: "Do movements follow specific rules (knight, rook, etc.)?"
   If YES → Recursive checking of legal moves
   If NO → Different validation

───────────────────────────────────────────────────────────────────────────────

🎯 2-3 Key Signals to Identify:

   Signal 1: "Given a path, validate if it's correct"
   Signal 2: "Sequential numbering (0, 1, 2, ...n²-1)"
   Signal 3: "Movement constraints (knight moves, specific rules)"

───────────────────────────────────────────────────────────────────────────────

📌 One-Line Mnemonic:
   "FOLLOW THE TOUR SEQUENTIALLY USING RECURSIVE KNIGHT MOVES"

   At each step:
   - Check if you're at the right position with right value
   - Reach end? Valid! Can't proceed? Invalid!

───────────────────────────────────────────────────────────────────────────────

When to Use Backtracking for Validation:
  ✓ Path/tour is pre-made (given as input)
  ✓ Values are sequential (0, 1, 2, ...)
  ✓ Movement rules are defined (knight moves)
  ✓ You need to verify in order
  ✗ When you need to construct the path (use different algorithm)
  ✗ When asking "count how many valid tours" (counting problem)

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 6️⃣  COMMON MISTAKES - Where Beginners Fail
└─────────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 1: Checking grid[r][c] exists AFTER accessing it
   Wrong: 
     if (grid[r][c] != expVal || r < 0 || c < 0 || r >= n || c >= n)
   Problem: Accesses grid[r][c] BEFORE checking bounds!
            If r=-1 or c=-1, this is out-of-bounds access (crash!)
   Fix: Check bounds FIRST:
     if (r < 0 || c < 0 || r >= n || c >= n || grid[r][c] != expVal)
   Lesson: Always check bounds before array access (short-circuit evaluation)

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 2: Forgetting the base case (reaching n²-1)
   Wrong:
     bool isValid(...) {
       if (r < 0 || ...) return false;  // Missing: if (expVal == n*n-1) return true
       ...
     }
   Problem: Never returns true! Keeps recursing unnecessarily
            Even valid tours are marked invalid
   Fix: Add base case: if (expVal == n*n - 1) return true;
   Lesson: Recursive functions NEED termination conditions

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 3: Wrong base case condition
   Wrong: if (expVal == n * n)  // Off-by-one error!
   Problem: Should be n²-1, not n²
            Last valid value is n²-1, not n²
            Example: 5×5 grid, values 0-24 (that's 25 values), last is 24 = 5²-1
   Fix: if (expVal == n * n - 1) return true;
   Lesson: Array indices: 0 to n²-1 (total n² elements)

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 4: Comparing move positions incorrectly
   Wrong: if (r + dr < 0 || c + dc < 0 || ...) // Using + instead of checking result
   Problem: Confusing what to check
   Correct approach: Store result, then check:
     int nr = r + dr, nc = c + dc;
     if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == expVal + 1)
   Lesson: Clarify intermediate variables for readability

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 5: Incorrect knight move definitions
   Wrong: moves = {{2,1}, {1,2}, ...}  // Missing negative moves!
   Problem: Knight can move in BOTH directions (±2, ±1)
            Only having {2,1} misses {-2,-1}, {-2,+1}, etc.
            Grid becomes unreachable from most positions!
   Fix: Include all 8: ±2 in one direction, ±1 in other
   Lesson: Think about symmetry: knight can go forward/backward, left/right

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 6: Not returning false after all moves fail
   Wrong:
     for (auto [dr, dc] : moves) {
       if (isValid(...)) return true;
     }
     // Missing: return false here!
   Problem: Falls through, implicitly returns random value or 0
   Fix: Explicitly return false after loop
   Lesson: All code paths should return value for bool functions

───────────────────────────────────────────────────────────────────────────────

❌ MISTAKE 7: Confusing validation with construction
   Wrong: Trying to FIND a valid knight's tour in the code
   Problem: This code only VALIDATES, it doesn't build tours
            If given invalid grid, it returns false (correct)
            But you can't use this to CONSTRUCT a tour
   Fix: Understand problem scope: verify vs construct vs count
   Lesson: Read problem carefully. This one is "validate given path"

───────────────────────────────────────────────────────────────────────────────

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 7️⃣  COMPLEXITY ANALYSIS - Deep Dive
└─────────────────────────────────────────────────────────────────────────────────

⏱️  TIME COMPLEXITY: O(8^(n²)) worst case, but typically O(n²)

Analysis:

THEORETICAL WORST CASE:
  • At each cell, try up to 8 moves
  • Can recurse up to n² cells deep (for a complete tour)
  • Worst case: 8 choices × 8 choices × ... × 8 choices (n² times)
  • = O(8^(n²))

BUT IN PRACTICE (for valid grids):
  • Valid grid: Path is predetermined, follow sequential values
  • Each position has EXACTLY ONE next position (deterministic)
  • No branching needed, just linear traversal
  • Time: O(n²) to verify all n² positions
  
TYPICAL CASES:
  • Invalid grid: Fails quickly when:
    - Expected value not found
    - Value in wrong place
    - Not reachable by knight move
  • Most recursion branches fail immediately
  • Average: O(n²) with small constant (like 8)

Example: 5×5 grid (25 cells)
  • Need to verify 25 sequential values
  • Each verification: check bounds (O(1)), check value (O(1))
  • Total: 25 × (1 + 1 + 8 tries × ~1 match) ≈ O(25) = O(n²)

Why Not Always O(8^(n²)):
  • Early termination: fail at first invalid position
  • Most next positions out-of-bounds: fail immediately
  • Most values don't match: fail immediately
  • Typically only 1-2 valid moves per position, not 8

───────────────────────────────────────────────────────────────────────────────

🧠 SPACE COMPLEXITY: O(n²)

Analysis:

RECURSION CALL STACK:
  • Maximum recursion depth: n² (one for each cell in tour)
  • Each call frame: O(1) local variables (r, c, n, expVal)
  • Stack space: n² call frames × O(1) per frame = O(n²)

NO ADDITIONAL DATA STRUCTURES:
  • Moves vector: O(1) (always 8 elements, constant)
  • No visited array: validation doesn't need tracking
  • No memoization: each path computed once

TOTAL SPACE:
  • Recursion stack: O(n²)
  • Local variables: O(1)
  • Input grid: O(n²) (not counted as extra space)
  • Total: O(n²) ✓

Space Optimization Opportunity:
  Could use iterative approach instead of recursion to avoid stack space,
  but would need explicit position stack (still O(n²)) or other tracking.

───────────────────────────────────────────────────────────────────────────────

Example Trace - Time Complexity:

5×5 Knight's Tour Validation:
  
  Position (0,0), expVal=0:
    Check bounds: ✓ O(1)
    Check grid[0][0]==0: ✓ O(1)
    Check if 0==24: ✗ O(1)
    Try 8 moves: O(1) per attempt
      Move 1-5: Out of bounds, fail immediately
      Move 6: Valid, found grid[2][1]==1, recurse
  
  Position (2,1), expVal=1:
    Check bounds: ✓ O(1)
    Check grid[2][1]==1: ✓ O(1)
    Check if 1==24: ✗ O(1)
    Try 8 moves: Look for value 2
      ...continue...
  
  Each cell: ~8 operations
  Total cells: 25 (for 5×5)
  Total: 25 × 8 ≈ O(n²) typically

───────────────────────────────────────────────────────────────────────────────

*/

/*
┌─────────────────────────────────────────────────────────────────────────────────
│ 8️⃣  ALTERNATIVE APPROACHES - Only Explanation (No Code)
└─────────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 1: POSITION MAP APPROACH
─────────────────────────────────────────────────────────────────────────────
Time: O(n²)  |  Space: O(n²)

Idea:
  • Create map: value → (row, col)
  • For value i from 0 to n²-2:
    • Get position of value i: (r1, c1)
    • Get position of value i+1: (r2, c2)
    • Check if (r2,c2) is knight move away from (r1,c1)
    • If not: return false
  • If all pairs valid: return true

Why Use This:
  ✓ Straightforward logic: check consecutive pairs
  ✓ Direct access to positions (O(1) lookup)
  ✗ Uses extra O(n²) space for position map
  ✗ Must check all n² pairs (no early termination advantage)
  ✗ Less elegant than recursive approach

When to Choose:
  • If you're more comfortable with iterative code
  • If you want explicit pair checking

───────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 2: SIMULATION APPROACH
─────────────────────────────────────────────────────────────────────────────
Time: O(n²)  |  Space: O(n²)

Idea:
  • Start at (0,0), read value, should be 0
  • Use value as index to find next position in grid
    (if value is i, find position of i+1, move there)
  • Repeat until value is n²-1
  • Track visited positions to ensure no revisiting

Why Use This:
  ✓ Simulation feels like "following the tour"
  ✓ Can detect if revisiting same position
  ✗ Still O(n²) lookup to find next position
  ✗ More complex than necessary for this validation

When to Choose:
  • If problem asks to "follow the path" explicitly
  • If there are additional constraints like forbidden cells

───────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 3: GRAPH-BASED VALIDATION
─────────────────────────────────────────────────────────────────────────────
Time: O(n² + edges)  |  Space: O(n²)

Idea:
  • Build graph: nodes = grid positions, edges = valid knight moves
  • Check if sequence of numbers represents a path in this graph
  • Verify consecutive positions are connected by edges

Why Use This:
  ✓ Generalized approach (works for any movement rules)
  ✓ Can reuse graph algorithms
  ✗ Over-engineered for this simple problem
  ✗ Slower than necessary (building full graph is expensive)

When to Choose:
  • If you need to solve similar problems with different movement rules
  • If graph already exists for other purposes

───────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 4: FORWARD VALIDATION (Different Order)
─────────────────────────────────────────────────────────────────────────────
Time: O(n²)  |  Space: O(n²)

Idea:
  • Instead of following 0→1→2→..., go in reverse: (n²-1)→...→1→0
  • Start from position of n²-1 (last value)
  • Check if each value is reachable by knight move to previous value

Why Use This:
  ✓ Sometimes easier to understand "coming from" vs "going to"
  ✗ Same complexity, no real advantage
  ✗ Slightly confusing (reverse traversal)

When to Choose:
  • If you're debugging and forward approach seems wrong
  • Educational: understand bidirectional validation

───────────────────────────────────────────────────────────────────────────────

ALTERNATIVE 5: HYBRID - EARLY VALIDATION
─────────────────────────────────────────────────────────────────────────────
Time: O(n²)  |  Space: O(n²)

Idea:
  • First pass: verify grid contains 0, 1, 2, ..., n²-1 exactly once
  • Second pass: verify consecutive values are knight moves apart

Why Use This:
  ✓ Separates concerns (existence check vs movement check)
  ✓ Clear two-phase approach
  ✗ Slower: requires two passes instead of one
  ✗ More code than necessary

When to Choose:
  • If requirements explicitly ask for validation in phases
  • If you want to report WHAT failed (missing value vs invalid move)

───────────────────────────────────────────────────────────────────────────────

COMPARISON TABLE:

┌─────────────────────┬───────────┬───────────┬──────────────────┐
│ Approach            │ Time      │ Space     │ Best For         │
├─────────────────────┼───────────┼───────────┼──────────────────┤
│ Backtracking (used) │ O(8^n²)ᵃ  │ O(n²)     │ Interview code   │
│ Position Map        │ O(n²)     │ O(n²)     │ Explicit pairs   │
│ Simulation          │ O(n²)     │ O(n²)     │ Value following  │
│ Graph-based         │ O(n²+E)   │ O(n²+E)   │ Different rules  │
│ Reverse             │ O(n²)     │ O(n²)     │ Debugging        │
│ Hybrid              │ O(2n²)    │ O(n²)     │ Phase reporting  │
└─────────────────────┴───────────┴───────────┴──────────────────┘
ᵃ Theoretical worst case; typically O(n²) for valid/invalid grids

RECOMMENDATION:
  Use Backtracking (current approach) for interviews:
    ✓ Elegant recursive solution
    ✓ Natural problem decomposition
    ✓ Shows understanding of backtracking pattern
    ✓ Efficient in practice
    ✓ Easy to explain and code

*/

/*
═══════════════════════════════════════════════════════════════════════════════════
                              QUICK REFERENCE CARD
═══════════════════════════════════════════════════════════════════════════════════

ALGORITHM: Knight's Tour Validation (Backtracking + DFS)
PROBLEM: Validate if grid represents valid knight's tour
TIME: O(8^(n²)) worst, O(n²) typical
SPACE: O(n²) recursion stack

KNIGHT MOVES: 8 total
  L-shape: 2 units in one direction, 1 unit perpendicular
  {(-2,+1), (-2,-1), (-1,-2), (+1,-2), (+2,-1), (+2,+1), (+1,+2), (-1,+2)}

ALGORITHM STRUCTURE:
  isValid(r, c, expectedValue):
    1. IF out of bounds → return false
    2. IF value != expectedValue → return false
    3. IF expectedValue == n²-1 → return true (success!)
    4. FOR each of 8 knight moves:
       IF isValid(next_position, expectedValue+1) → return true
    5. return false (no valid continuation)

KEY POINTS:
  ✓ Start at (0,0) with expected value 0
  ✓ Check bounds BEFORE accessing array
  ✓ Recursive: follow path 0→1→2→...→n²-1
  ✓ Early termination on invalid value
  ✓ Each position validates exactly once

EDGE CASES:
  ✓ Out of bounds knight moves (many from edges)
  ✓ Wrong values in cells (immediate failure)
  ✓ Missing values (path breaks)
  ✓ 1×1 grid (only value 0, should return true)
  ✓ 2×2 grid (knight can't visit all 4 cells)

WHEN TO USE:
  ✓ Validate pre-made knight's tour
  ✓ Verify any sequential path with movement constraints
  ✓ Need recursive backtracking demonstration
  ✗ Construct knight's tour (different algorithm)
  ✗ Count valid tours (different approach)

COMMON BUGS:
  ✗ Access array before bounds check → crash
  ✗ Forget base case (success condition) → infinite/wrong result
  ✗ Off-by-one: n*n instead of n*n-1 → wrong condition
  ✗ Incomplete knight moves → unreachable cells
  ✗ Don't return false after trying all moves

INTERVIEW TIPS:
  1. Explain: "Follow the path sequentially, verify each step"
  2. Clarify: "This validates, doesn't construct"
  3. Optimize: "Early termination on invalid value"
  4. Complexity: "O(n²) typical, O(8^n²) worst case"
  5. Edge cases: "Out of bounds moves, wrong values"

═══════════════════════════════════════════════════════════════════════════════════
*/