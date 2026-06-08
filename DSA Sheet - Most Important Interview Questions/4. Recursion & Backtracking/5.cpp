#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    /*
        isSafe answers one question:
        "Can we place digit dig at board[row][col] without breaking Sudoku rules?"

        Why this helper is necessary:
        - Backtracking tries many possible digits.
        - Without a validation step, the recursion would blindly place invalid digits.
        - That would create boards with duplicate values in rows, columns, or 3x3 boxes.

        What would break if this function were removed:
        - helper() would have no way to prune bad choices early.
        - The algorithm could return an invalid Sudoku board or waste huge time exploring impossible states.

        Edge cases handled:
        - Empty cells are stored as '.', and they do not equal any digit '1' to '9'.
        - Works for all 9 sub-boxes using the same formula.

        Complexity of this helper:
        - Row check: 9 cells
        - Column check: 9 cells
        - Box check: 9 cells
        - Total: O(27), which is O(1) because Sudoku size is fixed at 9x9.
    */
    bool isSafe(vector<vector<char>>& board, int row, int col, char dig) {

        /*
            Check the entire current row.

            What this does:
            - Scans columns 0 to 8 in the same row.
            - If dig already exists, placing it again would violate Sudoku's row rule.

            Why necessary:
            - Every digit can appear at most once in each row.

            What breaks if removed:
            - Example: row already has '5', and we place another '5' in the same row.
            - The algorithm may later think the board is solved even though the row is invalid.

            Dry run:
            - Suppose row = 0, col = 2, dig = '4'.
            - Loop checks board[0][0], board[0][1], ..., board[0][8].
            - If any one of them is '4', return false immediately.

            Edge case:
            - If cells contain '.', the comparison board[row][j] == dig is false.
        */
        for(int j = 0; j < 9; j++) {
            if(board[row][j] == dig) return false;
        }

        /*
            Check the entire current column.

            What this does:
            - Scans rows 0 to 8 in the same column.
            - If dig already exists, placing it again would violate Sudoku's column rule.

            Why necessary:
            - Every digit can appear at most once in each column.

            What breaks if removed:
            - Two equal digits could appear vertically in the same column.

            Dry run:
            - Suppose row = 3, col = 5, dig = '7'.
            - Loop checks board[0][5], board[1][5], ..., board[8][5].
            - If board[6][5] is already '7', return false.
        */
        for(int i = 0; i < 9; i++) {
            if(board[i][col] == dig) return false;
        }

        /*
            Find the starting cell of the 3x3 sub-grid that contains (row, col).

            What this does:
            - Integer division groups rows as 0-2, 3-5, 6-8.
            - Multiplying by 3 gives the top row of that group.
            - The same idea applies to columns.

            Why necessary:
            - Sudoku also requires each 3x3 box to have no duplicate digits.
            - To check the box, we first need its top-left coordinate.

            What breaks if removed:
            - We would not know which 3x3 box to scan.
            - The algorithm could allow duplicates inside a box.

            Dry run:
            - If row = 5 and col = 7:
              sr = (5 / 3) * 3 = 1 * 3 = 3
              sc = (7 / 3) * 3 = 2 * 3 = 6
            - So the 3x3 box starts at (3, 6).

            Common mistake:
            - Using row / 3 alone gives the box number, not the starting row.
        */
        int sr = (row / 3) * 3;
        int sc = (col / 3) * 3;

        /*
            Check the 3x3 box.

            What this does:
            - Scans rows sr to sr + 2 and columns sc to sc + 2.
            - If dig already exists in that box, placement is invalid.

            Why necessary:
            - A digit can appear at most once in each 3x3 Sudoku region.

            What breaks if removed:
            - A board could satisfy row and column rules but still fail box rules.

            Dry run:
            - For sr = 3, sc = 6, this scans:
              (3,6) (3,7) (3,8)
              (4,6) (4,7) (4,8)
              (5,6) (5,7) (5,8)
        */
        for(int i = sr; i < sr + 3; i++) {
            for(int j = sc; j < sc + 3; j++) {
                if(board[i][j] == dig) return false;
            }
        }

        /*
            If row, column, and 3x3 box checks all passed, the digit is safe.

            What breaks if removed:
            - The caller would never know that a valid placement exists.
            - In C++, missing a return in a non-void function causes undefined behavior.
        */
        return true;
    }

    /*
        helper is the core recursive backtracking function.

        Meaning of parameters:
        - board: current Sudoku state, modified in place.
        - row, col: the current cell being processed.

        Big idea:
        - Move cell by cell from left to right, top to bottom.
        - If a cell is already filled, skip it.
        - If a cell is empty, try digits '1' through '9'.
        - Keep a digit only if it eventually leads to a complete solution.
        - If a digit leads to a dead end, undo it and try the next digit.

        What would break without this function:
        - solveSudoku() would have no recursive engine to explore possibilities.

        Complexity:
        - If m cells are empty, the worst case tries up to 9 choices per empty cell.
        - Time: O(9^m) in theory, with strong pruning from isSafe.
        - Space: O(m) recursion depth, at most O(81), which is constant for a fixed 9x9 board.
    */
    bool helper(vector<vector<char>>& board, int row, int col) {
        
        /*
            Base case: row == 9 means we moved past the last row.

            What this does:
            - Signals that all cells from row 0 to row 8 have been processed successfully.

            Why necessary:
            - Recursion must have a stopping condition.
            - This is the success condition for the whole puzzle.

            What breaks if removed:
            - The function would keep trying to access invalid rows after row 8.
            - That can cause out-of-bounds access or infinite-style recursion behavior.

            Dry run:
            - After processing (8,8), next cell becomes (9,0).
            - row == 9 returns true, meaning the board is solved.
        */
        if(row == 9) return true;

        /*
            Compute the next cell in row-major order.

            What this does:
            - Normally moves one column to the right.
            - If we pass column 8, move to the next row and reset column to 0.

            Why necessary:
            - The recursion needs a predictable way to visit every cell exactly once.

            What breaks if removed:
            - We would either stay on the same cell forever or skip cells incorrectly.

            Dry run:
            - Current (0, 0) -> next (0, 1)
            - Current (0, 8) -> nextCol becomes 9, so next is (1, 0)

            Edge case handled:
            - End of a row is handled by wrapping to the next row.
        */
        int nextRow = row, nextCol = col + 1;
        if(nextCol == 9) {
            nextRow = row + 1;
            nextCol = 0;
        }

        /*
            Skip cells that are already filled in the original or current board.

            What this does:
            - If board[row][col] is not '.', it is already a digit.
            - We do not change it; we simply solve the rest of the board.

            Why necessary:
            - Given Sudoku clues are fixed and must never be overwritten.

            What breaks if removed:
            - The algorithm would try to replace pre-filled clues.
            - That would destroy the puzzle constraints.

            Dry run:
            - If board[0][0] = '5', helper does not try '1' to '9' there.
            - It directly calls helper(board, 0, 1).

            Edge case:
            - If the initial board already has all cells filled, this keeps skipping until row == 9.
        */
        if(board[row][col] != '.') {
            return helper(board, nextRow, nextCol);
        }

        /*
            Try every possible digit for the empty cell.

            What this does:
            - Attempts '1', then '2', ..., up to '9'.
            - Each digit represents one branch in the recursion tree.

            Why necessary:
            - At an empty Sudoku cell, we do not know the correct digit in advance.
            - Trying all valid candidates guarantees we find a solution if one exists.

            What breaks if removed:
            - Empty cells would never be filled.

            Dry run:
            - At an empty cell (0, 2), the loop tries:
              dig = '1', then '2', then '3', ... until '9'.
        */
        for(char dig = '1'; dig <= '9'; dig++) {
            
            /*
                Prune invalid choices before recursing.

                What this does:
                - Calls isSafe to check row, column, and box constraints.

                Why necessary:
                - This prevents exploring branches that are already impossible.

                What breaks if removed:
                - The recursion would place illegal digits and explode into many useless states.

                Dry run:
                - If dig = '5' but row already contains '5', isSafe returns false.
                - The code skips placement and tries the next digit.
            */
            if(isSafe(board, row, col, dig)) {
                
                /*
                    Choose: place the digit temporarily.

                    What this does:
                    - Writes dig into the current empty cell.

                    Why necessary:
                    - The recursive call must see this updated board state.

                    What breaks if removed:
                    - helper would recurse without changing anything.
                    - The algorithm would not make progress toward a solved board.

                    Dry run:
                    - If board[0][2] is '.', and dig is '4', it becomes board[0][2] = '4'.
                */
                board[row][col] = dig;

                /*
                    Explore: recursively solve the remaining cells.

                    What this does:
                    - Moves to the next cell using the board after placing dig.

                    Why necessary:
                    - A digit is only truly correct if it allows the rest of the board to be solved.

                    What breaks if removed:
                    - The algorithm would place one digit but never continue solving.

                    Dry run:
                    - Place '4' at (0,2), then solve from (0,3).
                    - If all future cells can be solved, the recursive call returns true.
                */
                if(helper(board, nextRow, nextCol)) {
                    /*
                        Success propagation.

                        What this does:
                        - Once a complete valid solution is found, return true all the way up.

                        Why necessary:
                        - We only need one solved Sudoku board.

                        What breaks if removed:
                        - The algorithm might continue searching and undo a valid solution.
                    */
                    return true;
                }

                /*
                    Unchoose: backtrack by restoring the cell to empty.

                    What this does:
                    - Removes the digit that led to a failed future state.

                    Why necessary:
                    - The next digit must be tested on a clean board.

                    What breaks if removed:
                    - The board would keep failed guesses.
                    - Later candidates would be tested against a corrupted state.

                    Dry run:
                    - Put '4' at (0,2), but later no digit works at another cell.
                    - Return here, reset board[0][2] to '.', then try '5'.

                    This line is the heart of backtracking.
                */
                board[row][col] = '.';
            }
        }

        /*
            All digits failed for this empty cell.

            What this does:
            - Tells the previous recursive call that its earlier choice was wrong.

            Why necessary:
            - Failure must move backward so previous cells can try different digits.

            What breaks if removed:
            - The caller would not get a reliable failure signal.

            Dry run:
            - At cell (4,6), none of '1' to '9' is safe.
            - Return false so the previous placed digit can be undone.
        */
        return false;
    }

    /*
        Public entry point for solving the Sudoku.

        What this does:
        - Starts the recursive search from the top-left cell (0,0).

        Why necessary:
        - Users of the Solution class call solveSudoku(), not helper() directly.

        What breaks if removed:
        - There would be no clean public function matching the usual problem interface.

        Edge case:
        - If the board is already solved and valid, helper skips all cells and returns true.
        - This code does not separately report invalid or unsolvable boards; it assumes the
          input follows the standard Sudoku problem format.
    */
    void solveSudoku(vector<vector<char>>& board) {
        helper(board, 0, 0);
    }
};

int main() {
    // Empty driver. Online judges usually call Solution::solveSudoku directly.
    
    return 0;
}


/*
================================================================================
1. 🧠 Problem Understanding
================================================================================

What type of problem is this?
- This is a constraint satisfaction problem solved using backtracking.
- We must fill missing values while obeying multiple rules at the same time.

What are the key constraints/clues?
- The board is fixed size: 9x9.
- Empty cells are represented by '.'.
- Valid digits are characters '1' to '9', not integers 1 to 9.
- A digit cannot repeat in the same row.
- A digit cannot repeat in the same column.
- A digit cannot repeat in the same 3x3 box.
- Given cells must not be changed.

Important missed/assumed edge cases:
- The code assumes board has exactly 9 rows and 9 columns.
- The code assumes the input puzzle is valid according to the problem statement.
- The code does not return whether solving failed; solveSudoku ignores helper's boolean result.


================================================================================
2. 🔍 Pattern Recognition
================================================================================

Pattern used:
- Backtracking / DFS on choices / Constraint Satisfaction.

How to recognize this pattern later:
- You are asked to fill empty positions.
- Each position has multiple possible choices.
- A partial choice can be checked for validity.
- If a choice later fails, you need to undo it.
- The problem asks for one valid arrangement or all valid arrangements.

Similar problems:
- N-Queens
- Rat in a Maze
- Crossword solver
- Graph coloring
- Word search
- Generate valid parentheses
- Permutations with constraints


================================================================================
3. ⚡ Approach Breakdown (Interview Style)
================================================================================

Brute force idea:
- Try every digit in every empty cell without checking early.
- After filling the whole board, verify whether the final board is valid.
- This is extremely slow because it explores many obviously invalid boards.

Better approach:
- While filling the board, check whether the current digit is valid.
- If it violates row, column, or box rules, skip it immediately.
- This is much faster because invalid branches are pruned early.

Optimal approach used here:
- Use recursive backtracking with isSafe validation.
- Place a digit only if it is currently valid.
- Recurse to solve the rest.
- If the future fails, undo the digit and try another.

Why this approach is chosen:
- It is simple.
- It uses very little extra space.
- It guarantees a solution if one exists.
- It matches the natural "try, erase, try again" way humans solve Sudoku.


================================================================================
4. 🧩 Intuition Building
================================================================================

Core idea in simple terms:
- Treat each empty cell like a decision point.
- At each decision point, try numbers 1 to 9.
- If a number breaks a Sudoku rule, reject it immediately.
- If it looks valid, place it and move forward.
- If you later get stuck, come back and erase the previous guess.

The trick or insight:
- Do not wait until the board is full to check validity.
- Check validity before every placement.
- This turns a huge blind search into a much smaller guided search.

Mini dry run:
- Suppose an empty cell is at (0,2).
- Try '1': row already has '1', reject.
- Try '2': column already has '2', reject.
- Try '3': box already has '3', reject.
- Try '4': row, column, and box are safe, place '4'.
- Continue to the next cell.
- If a later cell has no valid digit, erase '4' and try the next option.


================================================================================
5. 🔁 How to Recall Later
================================================================================

Key signals:
- "Fill the blanks" with constraints.
- "Try all possibilities" but reject invalid partial states.
- "Undo the last choice" when stuck.

One-line memory trick:
- Try, check, place, recurse, erase.

Sudoku-specific recall:
- Check 3 things: row, column, box.
- Box start formula: (index / 3) * 3.
- Backtracking line: board[row][col] = '.';


================================================================================
6. ⚠️ Common Mistakes
================================================================================

Beginner mistakes:
- Forgetting to reset the cell to '.' after a failed recursive call.
- Checking only row and column but forgetting the 3x3 box.
- Calculating the 3x3 box start incorrectly.
- Trying to modify cells that were already filled.
- Returning false too early after the first invalid digit.
- Not returning true immediately after a solution is found.
- Confusing character digits '1' to '9' with integer digits 1 to 9.
- Forgetting that solveSudoku modifies the board in place.


================================================================================
7. 📊 Complexity Analysis
================================================================================

Time complexity:
- Let m be the number of empty cells.
- In the worst case, each empty cell can try up to 9 digits.
- Worst-case time: O(9^m).
- Each isSafe call checks 27 cells, which is O(1) for a fixed 9x9 board.
- Practical runtime is much better because invalid choices are pruned early.

Space complexity:
- The board is modified in place.
- The recursion stack can go as deep as the number of cells processed.
- Auxiliary space: O(m), at most O(81).
- Since Sudoku size is fixed, this is often described as O(1) auxiliary space.


================================================================================
8. 🔄 Alternative Approaches
================================================================================

Alternative 1: Choose the most constrained empty cell first
- Instead of scanning left to right, pick the empty cell with the fewest valid digits.
- This often reduces backtracking dramatically.
- It is faster for hard puzzles but requires extra logic.

Alternative 2: Use row/column/box hash sets
- Maintain sets or boolean arrays for used digits.
- isSafe becomes O(1) without scanning 27 cells.
- This improves constant factors but adds bookkeeping.

Alternative 3: Bitmask optimization
- Represent used digits in rows, columns, and boxes using bits.
- Very fast and memory efficient.
- Less beginner-friendly but common in optimized solutions.

Alternative 4: Constraint propagation
- After placing a digit, update possible candidates for related cells.
- Detect contradictions earlier.
- More complex but powerful for difficult Sudoku variants.

Alternative 5: Exact cover / Algorithm X
- Model Sudoku as an exact cover problem.
- Use Donald Knuth's Dancing Links algorithm.
- Very elegant and fast, but much more advanced than standard interview backtracking.
*/
