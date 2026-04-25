#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    // VALIDATION HELPER: Checks if placing digit 'dig' at (row, col) violates Sudoku rules
    // Why needed? Before placing any digit, we must ensure it doesn't violate 3 constraints:
    //   1. No duplicate in the same row
    //   2. No duplicate in the same column
    //   3. No duplicate in the 3x3 sub-grid
    // What breaks if removed? We'd place invalid digits and never find valid solution
    // This is the CONSTRAINT CHECKER that enables valid backtracking
    bool isSafe(vector<vector<char>>& board, int row, int col, char dig) {

        // CONSTRAINT 1: Row validation
        // Why? Sudoku rule: Each row must contain digits 1-9 with no repeats
        // Dry run: If placing '5' at (0,0), check if '5' exists anywhere in row 0
        // What breaks if removed? We could place duplicate digits in same row
        // Edge case: Empty cell '.' doesn't cause false alarm - only real digits matter
        for(int j = 0; j < 9; j++) {
            if(board[row][j] == dig) return false;  // Found digit already in row
        }

        // CONSTRAINT 2: Column validation
        // Why? Sudoku rule: Each column must contain digits 1-9 with no repeats
        // Dry run: If placing '5' at (0,0), check if '5' exists anywhere in column 0
        // What breaks if removed? We could place duplicate digits in same column
        for(int i = 0; i < 9; i++) {
            if(board[i][col] == dig) return false;  // Found digit already in column
        }

        // CONSTRAINT 3: 3x3 Sub-grid validation (THE TRICKY PART)
        // Why? Sudoku rule: Each 3x3 box must contain digits 1-9 with no repeats
        // Key insight: Finding which 3x3 box a cell belongs to
        // Formula: sr = (row/3)*3 determines start row of 3x3 box
        //          sc = (col/3)*3 determines start column of 3x3 box
        // Dry run: Position (5,7) belongs to box starting at (3,6)
        //          row/3 = 5/3 = 1 (integer div) → 1*3 = 3 ✓
        //          col/3 = 7/3 = 2 (integer div) → 2*3 = 6 ✓
        // What breaks if removed? 3x3 constraint violated - incomplete validation
        // Edge case: This handles all 9 boxes uniformly with one formula
        int sr = (row / 3) * 3;  // Starting row of 3x3 box
        int sc = (col / 3) * 3;  // Starting column of 3x3 box

        // Check all 9 cells in this 3x3 box
        for(int i = sr; i < sr + 3; i++) {
            for(int j = sc; j < sc + 3; j++) {
                if(board[i][j] == dig) return false;  // Found digit in 3x3 box
            }
        }

        // If all 3 constraints passed, digit placement is valid
        return true;
    }

    // CORE BACKTRACKING FUNCTION: Recursively fills empty cells to solve Sudoku
    // Strategy: Process cells left-to-right, top-to-bottom. For each empty cell, try digits 1-9.
    //           If a digit works, recurse. If recursion fails, backtrack and try next digit.
    // Time per level: O(9) to try digits, multiplied by depth (81 cells max)
    bool helper(vector<vector<char>>& board, int row, int col) {
        
        // BASE CASE: Successfully processed all 81 cells
        // Why? row==9 means we've filled all 9 rows. Puzzle is complete!
        // Dry run: After filling cell (8,8), next call gets row=9, returns true
        // What breaks if removed? Infinite recursion - no termination condition
        if(row == 9) return true;

        // CALCULATE NEXT CELL POSITION (moving left-to-right, then down)
        // Why? We need systematic traversal: (0,0)→(0,1)→...→(0,8)→(1,0)→...
        // Dry run: At (0,7), nextCol=8. At (0,8), nextCol becomes 9→increment row, reset col to 0
        // What breaks if removed? No forward progression - would revisit same cells
        // Edge case: When col reaches 9, wrap to next row starting at col 0
        int nextRow = row, nextCol = col + 1;  // Default: move right
        if(nextCol == 9) {
            nextRow = row + 1;  // End of row: move to next row
            nextCol = 0;        // Reset to first column
        }

        // SKIP PRE-FILLED CELLS: If cell already has digit, skip to next cell
        // Why? Pre-filled cells (given clues) cannot be changed - they're fixed constraints
        // Dry run: If board[0][0]='5' (given), skip it. Check board[0][1] instead.
        // What breaks if removed? We'd try overwriting given clues with backtracking
        // Edge case: Pre-filled cells are marked with digits '1'-'9', not '.'
        if(board[row][col] != '.') {
            // Move to next cell without trying any digits
            return helper(board, nextRow, nextCol);
        }

        // BACKTRACKING LOOP: Try each digit 1-9 at this empty cell
        // Why? Exhaustive search with pruning - try all possibilities, keep valid ones
        // Dry run: At cell (0,0), try '1', '2',...,'9' until one leads to solution
        // What breaks if removed? We'd never attempt to fill the cell
        for(char dig = '1'; dig <= '9'; dig++) {
            
            // CHECK IF DIGIT IS VALID at this position
            // Why? Before committing to a digit, verify it doesn't violate Sudoku rules
            // What breaks if removed? We'd place invalid digits leading to dead ends
            if(isSafe(board, row, col, dig)) {
                
                // PLACE DIGIT (CHOOSE)
                // Why? Commit to this digit and explore consequences recursively
                // Dry run: Place '1' at (0,0), then recursively fill (0,1)
                // What breaks if removed? No state change - backtracking won't explore this path
                board[row][col] = dig;

                // RECURSE TO NEXT CELL (EXPLORE)
                // Why? If this digit is valid, try to fill remaining cells
                // What breaks if removed? No exploration - we'd never proceed forward
                // If recursion succeeds, we found a complete solution!
                if(helper(board, nextRow, nextCol)) {
                    return true;  // Solution found! Return true to propagate up
                }

                // BACKTRACK: Undo the digit and try next one (UNCHOOSE)
                // Why? This digit led to failure downstream. Reset and try alternative.
                // Dry run: '1' didn't work at (0,0). Restore to '.', try '2' next.
                // What breaks if removed? We'd keep invalid digit and never try alternatives
                // This is CRITICAL: Backtracking means undoing changes when path fails
                board[row][col] = '.';  // Restore to empty state
            }
        }

        // NO VALID DIGIT FOUND: All 1-9 failed at this position
        // Why? This means current configuration is unsolvable. Parent must backtrack.
        // Dry run: At some cell, all digits lead to contradictions. Return false to parent.
        // What breaks if removed? We'd not signal failure to parent
        return false;  // Failure: backtrack to previous cell
    }

    // PUBLIC INTERFACE: Starts the Sudoku solving process
    // Why? This is the entry point. We start from cell (0,0) and begin filling.
    // What breaks if removed? No way to start the algorithm
    void solveSudoku(vector<vector<char>>& board) {
        helper(board, 0, 0);  // Begin backtracking from top-left corner
    }
};

int main() {
    // Example: Solve a Sudoku puzzle
    // (Typically you'd read board from input or use a test case)
    
    return 0;
}


/*
================================================================================
🧠 PROBLEM UNDERSTANDING
================================================================================

PROBLEM TYPE: Constraint Satisfaction Problem (CSP) + Backtracking

KEY CHARACTERISTICS:
1. Sudoku board: 9×9 grid divided into 9 regions of 3×3
2. Given: Some cells pre-filled with digits 1-9 (clues)
3. Goal: Fill empty cells (marked '.') with digits 1-9
4. Constraints: 3 rules that must be satisfied simultaneously
   - Each row must contain digits 1-9 exactly once
   - Each column must contain digits 1-9 exactly once
   - Each 3×3 sub-grid must contain digits 1-9 exactly once

KEY CLUES & CONSTRAINTS:
✓ Multiple constraints to satisfy (not just one rule)
✓ Some cells are fixed (pre-filled) - cannot change
✓ Must try multiple options and abandon dead ends
✓ Need to explore ALL possibilities systematically
✓ State changes must be reversible (for backtracking)

WHY THIS IS HARD:
- Large search space: Theoretically 9^(81-givens) possibilities
- Multiple constraints create complex dependencies
- Need intelligent pruning (isSafe) to avoid explosion


================================================================================
🔍 PATTERN RECOGNITION
================================================================================

DSA PATTERN: BACKTRACKING with CONSTRAINT SATISFACTION

BACKTRACKING ESSENCE:
"Depth-first exploration of search tree with pruning. When a path fails,
undo changes and explore alternative paths."

KEY COMPONENTS ALWAYS PRESENT IN BACKTRACKING:
1. Base Case: When to stop (here: row == 9, all cells filled)
2. State Selection: Choose next cell to fill (here: left-to-right, top-to-bottom)
3. Constraint Validation: Check if choice is valid (here: isSafe function)
4. Recursive Exploration: Try valid choices and recurse (here: helper call)
5. Backtrack on Failure: Undo state when path fails (here: restore '.')
6. Return valid solution or false (here: true = found, false = impossible)

HOW TO RECOGNIZE THIS PATTERN:
✓ "Fill empty cells/positions" problems
✓ Multiple constraints that must ALL be satisfied
✓ Need to try different values and backtrack on failure
✓ Can validate partial solutions against constraints
✓ Solution requires systematic exploration with pruning

SIMILAR PROBLEMS (Use same pattern):
- N-Queens problem (place queens, avoid attacks)
- Crossword puzzle solver (fill words respecting constraints)
- Graph coloring (assign colors, no adjacent same color)
- Word break (partition string into valid words)
- Rat in maze (find path from start to end)
- Permutations/Combinations (generate all, filtering with conditions)

DIFFERENT FROM:
- DP (optimal substructure with memoization) ≠ Backtracking
- BFS/DFS on graphs (traverse existing structure) ≠ Generate + Test
- Greedy (local optimum) ≠ Exhaustive search with backtrack


================================================================================
⚡ APPROACH BREAKDOWN (Interview Style)
================================================================================

APPROACH 1: BRUTE FORCE (Not Practical)
---
Try all possible number combinations:
- Generate all 9^81 possible boards
- For each, check if it satisfies all Sudoku constraints
- Return the first valid one

Time: O(9^81) - exponentially huge!
Space: O(9^81) - impossible to store
Problem: INTRACTABLE - 9^81 ≈ 10^77 combinations
Why not chosen: Computers cannot explore this many in reasonable time


APPROACH 2: SMARTER BRUTE FORCE - Generate valid numbers only
---
Optimization: Only place valid digits (checked by isSafe)
Instead of: Try all 81 positions with all 9 digits
Do: Try only valid digits at each position (prune invalid early)

Time: O(9! × 9^(81-clues)) with pruning - still huge but manageable
Space: O(depth) = O(81) for recursion stack
Problem: Still tries many dead-end paths
Why not ideal: Doesn't exploit constraint propagation


APPROACH 3: BACKTRACKING WITH CONSTRAINT VALIDATION (CHOSEN) ✓
---
Strategy:
1. Process cells systematically (left-to-right, top-to-bottom)
2. For each empty cell, try digits 1-9
3. Before trying, validate with isSafe (check row/column/3×3 box)
4. If valid, place and recurse to next cell
5. If recursion succeeds, great! Return true
6. If recursion fails, backtrack: restore to '.' and try next digit
7. If all digits fail, return false (signal parent to backtrack)

Time: O(9^m) where m = number of empty cells (typically 40-60 in puzzles)
       With pruning: Often much faster in practice (~O(3^m) or better)
Space: O(m) for recursion depth
Advantage: 
✓ Pruning eliminates invalid branches early
✓ Systematic exploration guarantees solution if it exists
✓ Clean, elegant recursive structure
✓ Easy to understand and debug

Why this is optimal:
✓ No wasteful storage (unlike generating all boards)
✓ Constraint validation prunes ~95% of search space
✓ Backtracking avoids dead-ends efficiently
✓ Works for all valid Sudoku puzzles (guaranteed solvable)
✓ Standard solution for CSP problems


================================================================================
🧩 INTUITION BUILDING
================================================================================

THE CORE IDEA (In Simple Terms):
"Imagine you're filling a Sudoku puzzle. You look at an empty cell and
try digits 1-9 one by one. For each digit:
  - You check if it breaks any Sudoku rules
  - If valid, you pencil it in and move to the next empty cell
  - You continue recursively until either:
    a) You fill all cells successfully (you won!)
    b) You reach a dead-end (no valid digit works)
  - When you hit a dead-end, you erase your last guess and try the next number
  - You keep erasing and trying until you find a complete solution"

THE TRICK / INSIGHT:
---
Key insight 1: CONSTRAINT PRUNING
Don't try invalid digits - use isSafe to filter early.
If digit violates even ONE rule (row/column/box), skip it entirely.
This cuts the search space by ~90%+

Key insight 2: SYSTEMATIC ORDERING
Process cells in a fixed order (left-to-right, top-to-bottom).
This creates a consistent recursion tree and prevents redundant exploration.

Key insight 3: STATE REVERSIBILITY
Backtracking ONLY works if you can undo changes.
That's why we restore board[row][col] = '.' after each failed attempt.
Without this undo, we'd corrupt the board state.

Key insight 4: DEPTH-FIRST WITH EARLY TERMINATION
We don't explore ALL possibilities.
As soon as we find ONE valid solution (return true propagates up),
we STOP and return immediately.
Other solutions are ignored.

MENTAL MODEL:
Think of the search as a tree:

                        (0,0)
                    /    |    \
                  1/     2|     \9
                  /       |       \
             (0,1)-try   (0,1)-try (0,1)-try
            /  |  \      /  |  \    /  |  \
           ..  ..  ..   ..  ..  .. ..  ..  ..

We do Depth-First traversal:
- Go deep (recurse) first
- When path fails, backtrack to sibling
- Try next alternative
- First successful path wins


================================================================================
🔁 HOW TO RECALL LATER
================================================================================

2-3 KEY SIGNALS TO IDENTIFY THIS PATTERN:
1. "Fill empty/missing positions" + "Multiple constraints" 
   → Backtracking CSP
2. "Try different values" + "Can validate/check constraints"
   → Backtracking CSP
3. "No greedy choice works" + "Need exhaustive search"
   → Backtracking CSP

ONE-LINE MEMORY TRICK:
"Try, Check, Recurse, Undo - that's the backtracking dance!"

FORMULA TO REMEMBER:
```
boolean backtrack(state):
    if isComplete(state):           // Base case
        return true
    
    for each choice in choices:
        if isValid(state, choice):
            makeChoice(state, choice)      // Choose
            if backtrack(newState):         // Explore
                return true
            undoChoice(state, choice)       // Unchoose (Backtrack)
    
    return false
```

FOR SUDOKU SPECIFICALLY:
- 3 constraints to check: row, column, 3×3 box
- Formula for 3×3 box start: (position/3)*3
- Always process in order to avoid revisiting cells
- Restore to '.' when backtracking (not to any other value)


================================================================================
⚠️ COMMON MISTAKES
================================================================================

MISTAKE 1: Forgetting to backtrack
❌ After recursive call returns false, forget to restore board[row][col] = '.'
   Result: Board remains corrupted, next iteration tries invalid starting state
✓ Always restore state immediately after failed recursion

---

MISTAKE 2: Wrong cell ordering
❌ Jump around randomly instead of processing left-to-right, top-to-bottom
   Result: Revisit cells, explore redundantly, inefficient
✓ Use consistent order: row by row, column by column

---

MISTAKE 3: Modifying given cells
❌ If board[row][col] != '.', don't skip it - try to modify
   Result: Change given clues, violate puzzle constraints
✓ Check if(board[row][col] != '.') and skip immediately

---

MISTAKE 4: Incomplete constraint checking
❌ Only check row, forget column or 3×3 box
   Result: "Solution" violates Sudoku rules
✓ Check ALL 3 constraints before placing digit

---

MISTAKE 5: Incorrect 3×3 box calculation
❌ Use box_row = row/3, box_col = col/3 without multiplying by 3
   Result: Wrong 3×3 region checked
✓ Use sr = (row/3)*3, sc = (col/3)*3 to get top-left corner

---

MISTAKE 6: Not returning immediately on success
❌ Continue exploring even after finding a valid solution
   Result: Inefficient, exploring unnecessary branches
✓ Return true immediately when recursion succeeds

---

MISTAKE 7: Base case confusion
❌ Check if(col == 9) instead of if(row == 9)
   Result: Terminate too early, don't fill all cells
✓ Base case is row == 9 (completed all 9 rows)

---

MISTAKE 8: Trying to fill already-filled cells with loops
❌ Even when cell is pre-filled, try loop and backtrack
   Result: Wastes time, might corrupt given clues
✓ Skip immediately with: if(board[row][col] != '.') return helper(...)


================================================================================
📊 COMPLEXITY ANALYSIS
================================================================================

TIME COMPLEXITY: O(9^(number of empty cells)) with pruning
┌─ In worst case (empty board): O(9^81)
│  └─ But impossible in practice - pruning reduces drastically
│
├─ In typical puzzles (40-60 empty cells with constraints):
│  └─ O(3^m) to O(4^m) where m = empty cells
│     └─ Pruning cuts possibilities by ~75-90% at each level
│
└─ isSafe check per digit: O(9+9+9) = O(27) = O(1) constant work
   └─ Check 9 cells in row + 9 in column + 9 in 3×3 box

Why not exponential in theory?
- Most modern Sudoku puzzles have unique solutions
- Constraint propagation eliminates most branches
- Early backtracking prevents deep dead-ends
- Average case much better than worst case

SPACE COMPLEXITY: O(m) where m = number of empty cells
┌─ Recursion stack depth: At most 81 (one for each cell)
│  └─ Each recursive call uses O(1) local variables
│  └─ Total: O(81) = O(1) space
│
└─ Board itself: O(81) = O(1) for 9×9 fixed-size grid
   └─ Not counted as auxiliary space since it's input

Total auxiliary space: O(81) = O(1) - constant!

WHY EFFICIENT:
✓ No extra data structures (no HashMaps, arrays beyond input)
✓ Recursion stack is limited to 81 depth
✓ isSafe does constant-time validation
✓ Only stores integer variables


================================================================================
🔄 ALTERNATIVE APPROACHES
================================================================================

APPROACH A: Backtracking with Candidate Lists (Optimized)
---
Maintain for each cell: set of possible valid digits
Before recursing, narrow down candidates based on constraints
Choose cell with fewest candidates (most constrained variable heuristic)

Advantage:
- Faster convergence by prioritizing constrained cells
- Fewer backtrack steps in practice
Disadvantage:
- More complex code
- Maintaining candidate sets takes extra space/time
Better for: Large or hard puzzles
Worse for: Small or easy puzzles


APPROACH B: Constraint Propagation + Backtracking
---
When placing digit in cell:
- Remove that digit from all cells in same row/column/3×3 box
- If any cell has no candidates left → contradiction → backtrack
- Continue until placement is consistent

Advantage:
- Detects contradictions early
- Reduces search tree significantly
Disadvantage:
- More code to maintain candidate lists
- Overhead of updating candidates
Better for: Very hard puzzles
Worse for: Easy puzzles (overhead > benefit)


APPROACH C: Brute Force with Random Restarts
---
Randomly try digits, backtrack on failure
If no solution after N backtracks, restart with fresh random sequence

Advantage:
- Can find different solutions (if puzzle has multiple)
Disadvantage:
- Not guaranteed to find unique solution quickly
- May explore same regions multiple times
Better for: Finding ALL solutions (not just one)
Worse for: Finding first solution efficiently


APPROACH D: Integer Linear Programming (ILP)
---
Model Sudoku as optimization problem:
- Variables: x[i][j][k] = 1 if cell (i,j) has digit k
- Constraints: Linear inequalities for row/column/box rules
- Use ILP solver (but overkill for Sudoku)

Advantage:
- General-purpose (works for variants)
- Can solve in polynomial time for some formulations
Disadvantage:
- Overkill for standard Sudoku
- Slower than backtracking
- Requires external library
Better for: Research or variants
Worse for: Standard Sudoku solving


APPROACH E: Genetic Algorithm / Simulated Annealing
---
Generate random solutions, iteratively improve
Not guaranteed optimal, probabilistic search

Advantage:
- Can escape local optima
Disadvantage:
- Doesn't guarantee correct solution
- Much slower than backtracking
- Overkill for Sudoku
Better for: Very hard optimization problems
Worse for: Sudoku (guaranteed solution with backtracking)


WHY BACKTRACKING IS CHOSEN:
✓ Guaranteed to find solution if it exists
✓ Efficient with constraint pruning
✓ Simple, elegant code
✓ Optimal space usage
✓ Industry standard for CSP problems
✓ Scales well to typical puzzles


================================================================================
VISUAL DRY RUN EXAMPLE
================================================================================

Simplified 4×4 example (instead of 9×9) with 2×2 boxes:

Initial state:
  . 1 | . 2
  . . | . .
  ----+----
  2 . | . .
  . . | 1 .

(Note: '.' = empty, digits = given)

STEP 1: Start at (0,0)
  Try '1': Check row 0: has '1' already → invalid
  Try '2': Check row 0: has '2' already → invalid
  Try '3': Check row 0: OK, col 0: OK, box: OK → PLACE '3'
  
  Current: 3 1 | . 2 → Recurse to (0,2)

STEP 2: Now at (0,2)
  Try '1': Check row 0: has '1' → invalid
  Try '2': Check row 0: has '2' → invalid
  Try '3': Check row 0: has '3' → invalid
  Try '4': Check row 0: OK, col 2: OK, box: OK → PLACE '4'
  
  Current: 3 1 | 4 2 → Recurse to (1,0)

STEP 3: Now at (1,0) (all row 0 filled, move to row 1)
  Try '1': Check row 1: OK, col 0: has '3','2' OK, box: has '3','1' OK
           Check box: (0,0)-(1,1) contains '3','1' OK → PLACE '1'
           
           (Assume after several steps, we reach contradiction)

...LATER: BACKTRACKING HAPPENS...

  At some cell, all 4 digits fail.
  Return false to parent.
  Parent backtracks: restore previous cell to '.'
  Parent tries next digit (if any) or backtracks further.

EVENTUAL SOLUTION:
  (After all backtracking and exploration)
  3 1 | 4 2
  4 2 | 3 1
  ----+----
  2 4 | 1 3
  1 3 | 2 4

All constraints satisfied! Return true from top level.


================================================================================
KEY TAKEAWAYS
================================================================================

1. BACKTRACKING = Try + Check + Recurse + Undo
2. CONSTRAINT VALIDATION is critical (prunes 90%+ of tree)
3. SYSTEMATIC ORDERING prevents redundancy
4. STATE REVERSIBILITY enables backtracking
5. EARLY TERMINATION on success is efficient
6. This pattern applies to ALL constraint satisfaction problems
7. Time complexity is exponential but pruning makes it practical
8. Space complexity is linear in problem size (recursion depth)

*/