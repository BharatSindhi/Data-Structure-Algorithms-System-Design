#include <iostream>
#include <vector>
#include <algorithm>
// <algorithm> is needed because the code uses sort(ans.begin(), ans.end()).
// If this include is removed, many compilers will fail because sort is undefined.
using namespace std;


class Solution {
  public:
  
    void helper(vector<vector<int>>& maze, int r, int c, string path,
                vector<string>& ans, vector<vector<bool>> &vis) {
        // This helper function performs DFS + backtracking from cell (r, c).
        //
        // What each parameter means:
        // - maze: the n x n grid where 1 means open cell and 0 means blocked cell.
        // - r, c: current row and column of the rat.
        // - path: directions taken so far, such as "DRR".
        // - ans: stores every valid complete path from source to destination.
        // - vis: marks cells already used in the current path to avoid cycles.
        //
        // Why path is passed by value:
        // Each recursive branch gets its own copy of the current path.
        // If path were shared carelessly, one branch's moves could affect another branch.
        //
        // Why ans and vis are passed by reference:
        // ans must collect results across all recursive calls.
        // vis must reflect the current path state while recursion goes deeper.
        
        int n = maze.size();
        // n is the size of the square maze.
        // The problem assumes an n x n matrix, so rows and columns both use n.
        // If this line is removed, the boundary checks below cannot know maze limits.

        if (r < 0 || c < 0 || r >= n || c >= n || maze[r][c] == 0 || vis[r][c]) {
            // Base rejection case.
            //
            // What this checks:
            // - r < 0 or c < 0: moved outside the top/left boundary.
            // - r >= n or c >= n: moved outside the bottom/right boundary.
            // - maze[r][c] == 0: current cell is blocked.
            // - vis[r][c]: current cell is already part of this path.
            //
            // Why this is necessary:
            // Recursion tries all 4 directions, including invalid moves.
            // This guard safely stops invalid branches.
            //
            // What would break if removed:
            // - Out-of-bound moves could crash the program.
            // - Blocked cells could be included in paths.
            // - Without vis checking, recursion could loop forever between cells.
            //
            // Dry run example:
            // maze = [[1,1],
            //         [0,1]]
            // From (0,0), trying Up gives r=-1.
            // This condition catches it and returns immediately.
            return;
        }

        if (r == n - 1 && c == n - 1) {
            // Success base case.
            //
            // What this means:
            // The rat has reached the destination cell in the bottom-right corner.
            //
            // Why push path:
            // path contains exactly the moves taken from (0,0) to (n-1,n-1).
            //
            // What would break if ans.push_back(path) is removed:
            // The algorithm may find valid paths but would never store them.
            //
            // What would break if return is removed:
            // The code would continue exploring after reaching the destination,
            // which could add unnecessary moves and possibly create invalid paths.
            //
            // Dry run example:
            // maze = [[1,1],
            //         [1,1]]
            // path = "DR" means (0,0) -> Down -> Right.
            // At (1,1), this condition stores "DR".
            ans.push_back(path);
            return;
        }

        vis[r][c] = true;
        // Mark the current cell as visited for the current recursion path.
        //
        // Why this is necessary:
        // It prevents cycles like moving Right and then immediately Left forever.
        //
        // What would break if removed:
        // In an open maze, recursion could revisit the same cells repeatedly,
        // causing infinite recursion or duplicate/invalid paths.
        //
        // Important backtracking idea:
        // This mark is temporary. It applies only to the current path being explored.

        helper(maze, r + 1, c, path + 'D', ans, vis); // Down
        // Try moving Down.
        // r + 1 means one row lower, same column.
        // path + 'D' records this choice in the path string.
        //
        // What would break if removed:
        // Any valid path requiring a Down move from this cell would be missed.
        helper(maze, r - 1, c, path + 'U', ans, vis); // Up
        // Try moving Up.
        // r - 1 means one row higher, same column.
        //
        // What would break if removed:
        // Valid paths that require moving upward through a different route
        // would not be discovered.
        helper(maze, r, c - 1, path + 'L', ans, vis); // Left
        // Try moving Left.
        // c - 1 means same row, one column left.
        //
        // What would break if removed:
        // Paths that move left to bypass a wall would be missed.
        helper(maze, r, c + 1, path + 'R', ans, vis); // Right
        // Try moving Right.
        // c + 1 means same row, one column right.
        //
        // What would break if removed:
        // Any path requiring a right move from this cell would be missed.
        //
        // Mini dry run on a 2 x 2 all-open maze:
        // maze = [[1,1],
        //         [1,1]]
        // Start at (0,0), path = "".
        // Try Down -> (1,0), path = "D".
        // From (1,0), Right -> (1,1), path = "DR", store "DR".
        // Backtrack to (0,0), then try Right -> (0,1), path = "R".
        // From (0,1), Down -> (1,1), path = "RD", store "RD".
        // Final ans before sorting: ["DR", "RD"].

        vis[r][c] = false;
        // Backtracking step: unmark the current cell before returning.
        //
        // Why this is the key insight:
        // The current path is done exploring from this cell, so other paths
        // should be allowed to use this cell again.
        //
        // What would break if removed:
        // A cell visited by one path would remain blocked for all later paths,
        // causing the algorithm to miss valid answers.
        //
        // Think of it as:
        // "I used this cell for my current route. Now I am undoing that choice
        // so another route can try it too."
    }

    vector<string> ratInMaze(vector<vector<int>>& maze) {
        // Main function that prepares data structures and starts backtracking.
        //
        // It returns all valid paths from top-left to bottom-right.
        // Each path is represented as a string of moves: D, U, L, R.
        int n = maze.size();
        // Store maze size.
        // If this line is removed, we cannot build the visited matrix of size n x n.
        vector<string> ans;
        // ans stores all complete valid paths.
        // If this line is removed, there is nowhere to collect the results.

        if (maze[0][0] == 0) return ans;
        // If the starting cell is blocked, the rat cannot even begin.
        //
        // Why return ans:
        // ans is empty, so this correctly means "no paths exist."
        //
        // What would break if removed:
        // helper would immediately reject the start cell anyway, but this early
        // return avoids unnecessary setup and makes the start-blocked case clear.
        //
        // Edge case handled:
        // maze = [[0]] or any maze with maze[0][0] == 0 returns empty.
        //
        // Edge case missed:
        // If maze itself is empty, maze[0][0] would crash.
        // Most Rat in a Maze problems guarantee n >= 1.

        vector<vector<bool>> vis(n, vector<bool>(n, false));
        // Create an n x n visited matrix initialized to false.
        //
        // Why needed:
        // It tracks which cells are already part of the current path.
        //
        // What would break if removed:
        // The helper could not prevent cycles safely.
        //
        // Space complexity:
        // This matrix uses O(n^2) extra space.

        helper(maze, 0, 0, "", ans, vis);
        // Start DFS from the top-left cell (0,0) with an empty path.
        //
        // Why this is necessary:
        // This is the entry point that explores every possible route.
        //
        // What would break if removed:
        // ans would always remain empty, even when valid paths exist.

        sort(ans.begin(), ans.end());  // 🔥 IMPORTANT FIX

        // Sort all path strings lexicographically.
        //
        // Why this is needed:
        // Many platforms expect the answer in dictionary order.
        // The DFS order here is D, U, L, R, which does not automatically guarantee
        // the final order expected by every judge after complex branching.
        //
        // What would break if removed:
        // The set of paths may be correct, but the output order may mismatch
        // judge expectations if they compare ordered lists.
        //
        // Complexity:
        // If there are P valid paths and average path length is L,
        // sorting costs O(P log P * L) because string comparisons can inspect chars.

        return ans;
        // Return all valid sorted paths.
        // If this line is removed, the function would not return the computed answer.
    }
};
int main() {
    // Empty driver.
    // The actual algorithm is inside Solution::ratInMaze.
    // Online judges usually call ratInMaze directly, so main does not need test code.
    
    return 0;
}


// ### 1. 🧠 Problem Understanding
//
// - This is a grid path-finding problem.
// - A rat starts at the top-left cell (0,0) and must reach the bottom-right cell.
// - The rat can move in four directions: Down, Up, Left, and Right.
// - Cells with value 1 are open; cells with value 0 are blocked.
// - The task is not just to find one path, but to find all valid paths.
// - Key clue: "all paths" usually points toward recursion/backtracking.
// - Key constraint clue: because movement is possible in 4 directions, cycles are possible,
//   so we need a visited matrix.
//
//
// ### 2. 🔍 Pattern Recognition
//
// - Pattern used: DFS + Backtracking.
// - DFS because we go deep along one route before trying another route.
// - Backtracking because after exploring one route, we undo the visited mark
//   so other routes can reuse that cell.
//
// Recognize this pattern when:
// - You need to generate all possible answers.
// - You make a choice, explore it, then undo the choice.
// - The problem has words like paths, combinations, permutations, maze, explore,
//   all possible ways, or valid arrangements.
//
//
// ### 3. ⚡ Approach Breakdown (Interview Style)
//
// - Brute force idea:
//   Try every possible sequence of moves blindly.
//   Problem: This can go out of bounds, hit blocked cells, and loop forever.
//
// - Better approach:
//   Use DFS and stop invalid branches with boundary, blocked-cell, and visited checks.
//   This avoids exploring impossible paths deeply.
//
// - Optimal approach:
//   DFS + backtracking with a visited matrix.
//   This is chosen because we must list all valid paths, not just check if one exists.
//   Backtracking ensures every valid path gets a fair chance.
//
//
// ### 4. 🧩 Intuition Building
//
// - Imagine walking through the maze with a pencil.
// - When you step into a cell, mark it so you do not step into it again
//   in the same route.
// - Try all possible directions from there.
// - When all directions are done, erase your mark and go back.
// - The trick is the erase step: vis[r][c] = false.
//   Without it, one route would permanently block cells for other routes.
//
//
// ### 5. 🔁 How to Recall Later
//
// - Signal 1: Find all paths in a grid.
// - Signal 2: Need to avoid revisiting cells in the current path.
// - Signal 3: Need to undo choices after recursion.
// - Memory trick: "Mark, move, return, unmark."
//
//
// ### 6. ⚠️ Common Mistakes
//
// - Forgetting to unmark visited cells during backtracking.
// - Not checking boundaries before accessing maze[r][c].
// - Not checking blocked cells.
// - Not using visited, causing infinite recursion.
// - Assuming only Down and Right moves are needed when the problem allows 4 directions.
// - Forgetting to sort answers if the judge expects lexicographic order.
// - Not handling blocked starting cell.
// - Not considering that an empty maze would crash with maze[0][0].
//
//
// ### 7. 📊 Complexity Analysis
//
// - Let n be the maze dimension.
// - There are n^2 cells.
// - From each cell, the recursion can try up to 4 directions.
// - Because visited prevents revisiting a cell in the same path, each path length
//   is at most n^2.
//
// Time Complexity:
// - Worst-case path exploration is exponential.
// - A common upper bound is O(4^(n^2)) for trying directions across cells.
// - With visited restrictions, the practical branching is reduced, but still exponential
//   because the number of simple paths in a grid can be very large.
// - Sorting adds O(P log P * L), where P is number of valid paths and L is path length.
//
// Space Complexity:
// - O(n^2) for the visited matrix.
// - O(n^2) recursion depth in the worst case for one path.
// - O(P * L) for storing all valid answer strings.
//
//
// ### 8. 🔄 Alternative Approaches
//
// - BFS:
//   Can find shortest paths, but this problem asks for all paths.
//   BFS would need to store full paths in the queue, often using more memory.
//
// - DFS without a visited matrix:
//   Works only if movement is restricted in a way that prevents cycles.
//   Here 4-direction movement creates cycles, so visited is necessary.
//
// - Dynamic programming:
//   Useful for counting paths when movement is limited, such as only Right and Down.
//   Not ideal here because the task is to print all paths and movement has cycles.
//
// - Direction arrays:
//   Instead of writing four helper calls manually, we could store row/column changes
//   and direction characters in arrays. This makes the code shorter, but the logic
//   is the same DFS + backtracking idea.
