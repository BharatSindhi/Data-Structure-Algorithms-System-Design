/*
    ======= N-QUEENS PROBLEM - BACKTRACKING SOLUTION =======
    Problem: Place N queens on an N×N chessboard such that no two queens attack each other.
    - Two queens attack if they are in the same row, column, or diagonal.
    - Since we place one queen per row, row conflicts are automatically handled.
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // ===== CONSTRAINT CHECKING FUNCTION =====
    // Purpose: Validate if placing a queen at board[row][col] is safe
    // Why: Pruning invalid paths early saves computation in backtracking
    bool isSafe(vector<string> &board, int row, int col, int n) {
        
        // ===== CHECK COLUMN ATTACK =====
        // Check if any queen exists in the same column ABOVE current position
        // Why: We only check above (i < row) because we place queens row-by-row from top
        //      No queens below the current row exist yet
        // What breaks if removed: Queens in same column would be allowed, violating N-Queens rule
        // Time: O(n) - worst case checking entire column
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') return false;
        }

        // ===== CHECK LEFT DIAGONAL ATTACK =====
        // Check upper-left diagonal (row decreases, col decreases)
        // Direction: (-1, -1) from current position
        // Why: Queens on same diagonal attack each other
        // What breaks if removed: Diagonal attacks would be missed
        // Dry run (4×4, placing at row=2, col=1):
        //   - Check (1,0) → (0,-1 STOP) - no queens found = safe for this diagonal
        // Edge case: Works correctly at board edges (i>=0 && j>=0 prevents overflow)
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }

        // ===== CHECK RIGHT DIAGONAL ATTACK =====
        // Check upper-right diagonal (row decreases, col increases)
        // Direction: (-1, +1) from current position
        // Why: Completes diagonal attack checking (both diagonals from any queen)
        // What breaks if removed: Right diagonal attacks would be missed
        // Dry run (4×4, placing at row=2, col=2):
        //   - Check (1,3) → (0,4 STOP out of bounds) - safe
        // Edge case: j < n prevents going beyond board boundary
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }

        // ===== RETURN TRUE IF ALL CHECKS PASS =====
        // This position is safe to place a queen
        return true;
    }

    // ===== RECURSIVE BACKTRACKING FUNCTION =====
    // Purpose: Explore all possible queen placements using backtracking
    // Parameters:
    //   - board: current state of the chessboard
    //   - row: current row we're trying to place a queen in (0 to n-1)
    //   - n: size of the board
    //   - ans: stores all valid complete solutions
    void nQueens(vector<string>& board, int row, int n, vector<vector<string>> &ans) {
        
        // ===== BASE CASE: ALL QUEENS PLACED =====
        // When row == n, we've successfully placed all n queens (one per row)
        // Why: This is our success condition - a valid solution found
        // What breaks if removed: Function would continue recursing beyond valid solutions
        if (row == n) {
            ans.push_back(board);  // Add complete solution to results
            return;
        }

        // ===== TRY PLACING QUEEN IN EACH COLUMN OF CURRENT ROW =====
        // Why: Since we place one queen per row, we only vary the column
        // This ensures no two queens in same row (automatically satisfied)
        for (int j = 0; j < n; j++) {
            
            // ===== CHECK IF POSITION IS VALID BEFORE EXPLORING =====
            // Why: Pruning - don't explore invalid branches (backtracking key principle)
            // What breaks if removed: Invalid placements explored, wasting time
            // Dry run (n=4, row=1, trying col=1):
            //   - isSafe checks: column ✓, left-diag ✓, right-diag ✓ → proceed
            if (isSafe(board, row, j, n)) {
                
                // ===== PLACE QUEEN =====
                // Mark current position with 'Q' (choose step in backtracking)
                // Why: Explore this path by placing queen here
                board[row][j] = 'Q';
                
                // ===== RECURSE TO NEXT ROW =====
                // Try placing a queen in row+1 (explore deeper)
                // Why: Build solution incrementally, row by row
                nQueens(board, row + 1, n, ans);
                
                // ===== BACKTRACK: REMOVE QUEEN =====
                // Undo the placement by marking position back to '.'
                // Why: Explore other columns in this row (unchoose step)
                // What breaks if removed: Only first valid solution found, others missed
                // Critical for generating ALL solutions (not just one)
                board[row][j] = '.';
                
                // ===== EXECUTION FLOW AFTER BACKTRACK =====
                // After returning from recursion, we loop to next column (j++)
                // This tries all columns in current row before returning to parent call
            }
        }
        // ===== IMPLICIT BACKTRACKING ON RETURN =====
        // When for loop ends, function returns to parent
        // Parent continues its own loop with next column
    }

    // ===== MAIN SOLVER FUNCTION =====
    // Purpose: Initialize board and start backtracking
    vector<vector<string>> solveNQueens(int n) {
        
        // ===== INITIALIZE BOARD =====
        // Create n×n board filled with '.' (empty squares)
        // Why: Use '.' for empty, 'Q' for queen (visual representation)
        // Time complexity of initialization: O(n²)
        vector<string> board(n, string(n, '.'));
        
        // ===== RESULT CONTAINER =====
        // Each element is one complete valid solution
        // Each solution is a vector of strings (board representation)
        vector<vector<string>> ans;
        
        // ===== START BACKTRACKING FROM ROW 0 =====
        // Why: Begin search from first row, place one queen per row
        nQueens(board, 0, n, ans);
        
        // ===== RETURN ALL VALID SOLUTIONS =====
        // Example for n=4: returns 2 solutions
        // Example for n=1: returns 1 solution ["Q"]
        return ans;
    }
};

// ===== DRIVER CODE =====
int main() {
    // Test case examples would go here
    // Example: 
    //   Solution sol;
    //   auto results = sol.solveNQueens(4);
    //   // Results contains all 2 valid solutions for 4-queens
    
    return 0;
}


/*
═══════════════════════════════════════════════════════════════════════════════

                        🧠 PROBLEM UNDERSTANDING

═══════════════════════════════════════════════════════════════════════════════

**Type of Problem:**
- Classic BACKTRACKING / CONSTRAINT SATISFACTION problem
- NOT a search/sort problem - no ordering involved
- NOT a DP problem - no overlapping subproblems

**Key Constraints & Clues:**
1. Place N queens on N×N board
2. No two queens can attack each other (classic chess rule)
3. Attack rule: same row, column, or diagonal
4. We need to find ALL valid solutions (not just one)
5. The constraint that we have exactly N queens on N×N board means one queen per row

**Why Backtracking?**
- Greedy won't work: local choices don't lead to global optimum
- DP won't work: no overlapping subproblems between different placements
- Backtracking fits: explore all possibilities, prune invalid branches


═══════════════════════════════════════════════════════════════════════════════

                        🔍 PATTERN RECOGNITION

═══════════════════════════════════════════════════════════════════════════════

**DSA Pattern:** BACKTRACKING with CONSTRAINT CHECKING
                |
                +-- Decision Tree Exploration
                +-- Constraint Validation (isSafe function)
                +-- State Restoration (crucial for generating all solutions)

**Backtracking Template Used:**
```
def backtrack(solution, choices):
    if solution is complete:
        save solution
        return
    
    for each choice in choices:
        if choice is valid:
            make choice          [CHOOSE]
            backtrack(deeper)    [EXPLORE]
            undo choice          [UNCHOOSE]
```

**How to Recognize This Pattern in Future Problems:**
1. ✓ Problem asks for "all" or "count" of valid solutions (not just one)
2. ✓ Constraints must be satisfied (can't be violated)
3. ✓ State needs to be explored exhaustively
4. ✓ Invalid states can be pruned early
5. ✓ Previous choices affect future choices

**Real-World Examples of Same Pattern:**
- Sudoku solver
- Word ladder (finding all paths)
- Permutations/Combinations
- Maze with multiple exits
- Scheduling conflicts


═══════════════════════════════════════════════════════════════════════════════

                    ⚡ APPROACH BREAKDOWN (Interview Style)

═══════════════════════════════════════════════════════════════════════════════

**BRUTE FORCE APPROACH:**
- Try every possible position on the board: n² positions
- For each position, try placing a queen and recursively solve rest
- No pruning, no constraint checking
- Time: O((n²)^n) - exponential explosion
- Why it's bad: Explores many impossible branches

```
Example (n=4): Try all 4^4 = 256 placements, most invalid
```

**BETTER APPROACH (What this code does):**
- One queen per row constraint reduces search space
- Check constraints BEFORE recursing (pruning)
- Remove queen when backtracking to explore alternatives

Time: O(N! × N) - still exponential but much better
- At row 0: n choices
- At row 1: ~(n-1) choices (many pruned)
- At row 2: ~(n-2) choices
- ... and so on

**WHY THIS APPROACH IS CHOSEN:**
1. Early pruning eliminates invalid branches
2. One queen per row naturally divides problem (row-by-row)
3. isSafe() is O(n) check vs. waiting for full board evaluation
4. Simple to understand and implement
5. Generates ALL solutions efficiently (better than brute force)

**Can we do better?**
- Some optimizations: use bit manipulation, column/diagonal tracking sets
- But conceptually this is the right approach for N-Queens
- Those are constant factor improvements


═══════════════════════════════════════════════════════════════════════════════

                        🧩 INTUITION BUILDING

═══════════════════════════════════════════════════════════════════════════════

**Core Idea in Simple Terms:**
"I'm placing queens one row at a time. Before I place a queen, I check if it's safe 
(no conflicts with already placed queens). If safe, I place it and move to next row. 
If I reach the end, I found a solution! If stuck, I backtrack and try next column."

**DRY RUN on n=4 (simplified - first solution found):**

```
Step 1: Place queen at (0, 0)
  Board:
  Q . . .
  . . . .
  . . . .
  . . . .

Step 2: Try row=1
  - (1,0)? No, same column as (0,0) ✗
  - (1,1)? No, diagonal from (0,0) ✗
  - (1,2)? Yes! isSafe=true ✓ Place queen
  Board:
  Q . . .
  . . Q .
  . . . .
  . . . .

Step 3: Try row=2
  - (2,0)? No, column conflict ✗
  - (2,1)? No, column conflict ✗
  - (2,2)? No, column conflict + diagonal ✗
  - (2,3)? Yes! Place queen
  Board:
  Q . . .
  . . Q .
  . . . Q
  . . . .

Step 4: Try row=3
  - (3,0)? No, column conflict ✗
  - (3,1)? Yes! Place queen
  Board:
  Q . . .
  . . Q .
  . . . Q
  . Q . .

Step 5: row == n (4), SOLUTION FOUND! Save it.

Step 6: Backtrack from row=3
  - Try (3,2)? No...
  [Continue exploring other branches]
```

**The "Trick" or Key Insight:**
The critical insight is **state restoration via backtracking**. Without removing 
the queen (board[row][j] = '.'), we'd only find the first solution. By undoing 
each choice, we explore alternative branches and find ALL solutions.

Without backtracking:
```
nQueens(0)
├─ Place (0,0) → nQueens(1)
│  └─ Place (1,2) → nQueens(2)
│     └─ ... → finds 1st solution only
```

With backtracking:
```
nQueens(0)
├─ Place (0,0) → nQueens(1)
│  ├─ Place (1,2) → nQueens(2) → ... → find solution
│  ├─ Undo (1,2)
│  ├─ Place (1,3) → nQueens(2) → ... → find another solution
│  └─ Undo (1,3)
└─ Undo (0,0)
├─ Place (0,1) → ... [explore all starting positions]
```


═══════════════════════════════════════════════════════════════════════════════

                        🔁 HOW TO RECALL LATER

═══════════════════════════════════════════════════════════════════════════════

**2-3 Key Signals to Identify This Problem:**
1. **"Place N non-attacking items"** → N-Queens or variant
2. **"Find ALL solutions"** → Backtracking needed
3. **"Constraint-based placement"** → Check constraints before exploring

**One-Line Memory Trick:**
*"One queen per row, check column+diagonals, backtrack if stuck, record all successes."*

**Keyword Spotting:**
- "Place", "arrange", "schedule" (placement problem)
- "All", "count", "enumerate" (find all solutions)
- "No two", "non-attacking", "conflict" (constraints)
- "Board", "grid", "grid-like structure"


═══════════════════════════════════════════════════════════════════════════════

                        ⚠️ COMMON MISTAKES

═══════════════════════════════════════════════════════════════════════════════

**Mistake 1: Forgetting to Backtrack**
```cpp
// ❌ WRONG: Not undoing the placement
for (int j = 0; j < n; j++) {
    if (isSafe(board, row, j, n)) {
        board[row][j] = 'Q';
        nQueens(board, row + 1, n, ans);
        // Missing: board[row][j] = '.';  ← CRITICAL!
    }
}
// Result: Only finds 1 solution, not all
```

**Mistake 2: Checking Same-Row Conflicts**
```cpp
// ❌ Redundant and confusing
for (int j = 0; j < n; j++) {
    if (board[row][j] == 'Q') return false;  // Not needed!
}
// Why it's wrong: We place exactly one queen per row
// No same-row conflicts possible with our algorithm
```

**Mistake 3: Wrong Diagonal Direction**
```cpp
// ❌ WRONG: Checking upper-right incorrectly
for (int i = row + 1, j = col + 1; i < n && j < n; i++, j++) {
    if (board[i][j] == 'Q') return false;
}
// Why it's wrong: We never check below current row
// Queens below don't exist yet!
```

**Mistake 4: Using Sets for Row Tracking**
```cpp
// ❌ Unnecessary complexity
unordered_set<int> rows, cols, diags;
// We don't need row tracking since we place one queen per row
// Complicates code and slower than column-only checks
```

**Mistake 5: Not Initializing Board Properly**
```cpp
// ❌ WRONG: Uninitialized board
vector<string> board(n);  // What's in each string?
// Result: Unpredictable behavior, crashes

// ✓ CORRECT:
vector<string> board(n, string(n, '.'));  // Each string has n dots
```


═══════════════════════════════════════════════════════════════════════════════

                        📊 COMPLEXITY ANALYSIS

═══════════════════════════════════════════════════════════════════════════════

**TIME COMPLEXITY: O(N! × N)**

Explanation:
- Row 0: N possible placements (all need to check, but ~1 succeeds)
- Row 1: ~(N-1) valid placements (constraints prune many)
- Row 2: ~(N-2) valid placements
- ...
- Row N-1: ~1 valid placement

Multiplying: N × (N-1) × (N-2) × ... × 1 = N! at most
Each placement requires O(N) isSafe() check
Total: O(N! × N)

For N=4: 4! × 4 = 24 × 4 = 96 operations (approximate)
For N=8: 8! × 8 = 40320 × 8 = 322,560 operations

Note: Actual runtime is better due to aggressive pruning in middle rows

**SPACE COMPLEXITY: O(N² × S)**

Where:
- N² = board representation (each solution is N×N strings)
- S = number of solutions stored
- Recursion depth: O(N) call stack

For N=4: 4 solutions × 4×4 board = ~100 characters
For N=8: 92 solutions × 8×8 board = ~6000 characters

Recursion stack: O(N) - we go N levels deep

**Breakdown by Component:**
```
Board initialization: O(N²) - one time
isSafe() checks:
  - Column check: O(N)
  - Left diagonal: O(N)
  - Right diagonal: O(N)
  Total per call: O(N)

Recursive calls: O(N! × N) times isSafe is called
Storing solution: O(N²) per solution

Total Space: O(N² × number_of_solutions)
```


═══════════════════════════════════════════════════════════════════════════════

                        🔄 ALTERNATIVE APPROACHES

═══════════════════════════════════════════════════════════════════════════════

**APPROACH 1: Using Sets for Column/Diagonal Tracking**

Idea: Instead of checking entire column/diagonal each time, maintain sets of 
occupied columns, diagonals, and anti-diagonals.

Pros:
- isSafe() becomes O(1) instead of O(N)
- Total time becomes O(N!) instead of O(N! × N)
- Faster for large N

Cons:
- More memory (three sets to maintain)
- More complex code
- Requires understanding coordinate transformation

Implementation sketch:
```
cols, diag1, diag2 = sets to track occupied
For each placement:
  - Check if col in cols, (row-col) in diag1, (row+col) in diag2
  - Add to sets when placing, remove when backtracking
```

**APPROACH 2: Bit Manipulation**

Idea: Use bitmasks to represent occupied columns and diagonals instead of sets.

Pros:
- O(1) checking and updating
- Less memory than sets
- Extremely fast

Cons:
- Requires understanding bitwise operations
- Hard to read code
- Limited to small N (N ≤ 32 or 64 depending on CPU)

Example:
```
col_mask |= (1 << j)  // Mark column j as occupied
isSafe = !(col_mask & (1 << j))  // Check if column j is free
```

**APPROACH 3: Column-First (instead of Row-First)**

Idea: Place queens by column instead of by row.

Pros:
- Conceptually flexible
- Can start from any row
- Some problems naturally fit this better

Cons:
- More complex logic
- No real advantage for N-Queens

**APPROACH 4: Dynamic Programming with Memoization**

Can we use DP? No, because:
- No overlapping subproblems
  (Different board states don't share solutions)
- Each path is independent
- Memoization wouldn't help

Example why: Solving for row=3 with different configurations above 
doesn't have overlapping results.

**APPROACH 5: Randomized/Heuristic Approach**

Idea: Use simulated annealing or genetic algorithms for "a" solution.

Pros:
- Finds solutions faster for very large N
- Scalable to N > 100

Cons:
- Doesn't find ALL solutions
- Non-deterministic results
- Overkill for standard N-Queens

When to use: When N is huge (1000+) and you only need one solution


═══════════════════════════════════════════════════════════════════════════════
*/