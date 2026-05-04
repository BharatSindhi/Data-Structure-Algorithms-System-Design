#include <iostream>
#include <vector>
using namespace std;

// This solution answers the M-Coloring Problem:
// Can we color all vertices of an undirected graph using at most m colors
// so that no two directly connected vertices have the same color?
//
// DSA category:
// - Recursion + Backtracking
// - Constraint satisfaction problem
//
// Important representation note:
// - edges is given as an edge list: {{u, v}, ...}
// - The code converts it into an adjacency matrix adj[v][v].
// - adj[i][j] == 1 means there is an edge between vertex i and vertex j.
//
// Overall dry run idea for a small example:
// v = 3, edges = {{0, 1}, {1, 2}}, m = 2
// Graph: 0 -- 1 -- 2
// Try coloring node 0 with color 0 -> safe.
// Try coloring node 1 with color 0 -> not safe because node 0 has color 0.
// Try coloring node 1 with color 1 -> safe.
// Try coloring node 2 with color 0 -> safe because node 1 has color 1.
// All nodes colored, so answer is true.
class Solution {
public:

    bool issafetoassign(int node, int col, vector<vector<int>> &adj, vector<int> &color, int v) {
        // Check every possible neighbor k of the current node.
        // What this does:
        // - Loops through all vertices from 0 to v - 1.
        // - If k is connected to node and k already has the same color,
        //   then assigning col to node violates the graph-coloring rule.
        //
        // Why this is necessary:
        // - The main constraint is: adjacent vertices cannot share a color.
        // - Before placing a color, we must verify that it does not conflict
        //   with already-colored neighbors.
        //
        // What would break if this loop is removed:
        // - The algorithm would assign colors blindly.
        // - It might return true for invalid colorings where connected nodes
        //   have the same color.
        //
        // Small dry run:
        // Suppose node = 1, col = 0, and color = {0, -1, -1}.
        // If adj[1][0] == 1, then node 1 is connected to node 0.
        // Since color[0] == 0, assigning color 0 to node 1 is unsafe.
        for(int k = 0; k < v; k++) {
            // adj[node][k] == 1 checks whether k is a neighbor of node.
            // color[k] == col checks whether that neighbor already has
            // the color we are trying to assign.
            //
            // Why both conditions are needed:
            // - Same color is only a problem when there is an edge.
            // - Non-adjacent vertices are allowed to have the same color.
            //
            // If this condition is removed:
            // - We would not detect conflicts, and invalid answers could pass.
            if(adj[node][k] == 1 && color[k] == col) {
                // Conflict found, so this color cannot be assigned to node.
                // Returning false immediately prunes this branch of recursion.
                //
                // If this return is removed:
                // - The function may continue and incorrectly say the color is safe.
                return false;
            }
        }
        // No adjacent vertex has the same color, so this assignment is valid.
        //
        // Edge cases handled here:
        // - Isolated vertex: no adj[node][k] == 1, so every color is safe.
        // - Partially colored graph: uncolored neighbors have color -1,
        //   so they will not conflict with colors 0 to m - 1.
        return true;
    }

    bool fnc(int node, vector<vector<int>> &adj, int m, vector<int> &color, int v) {
        // Base case:
        // If node == v, it means we successfully assigned colors to
        // vertices 0 through v - 1.
        //
        // Why this is necessary:
        // - Recursion needs a stopping point.
        // - Reaching this line means every previous assignment was safe.
        //
        // What would break if removed:
        // - The recursion would keep calling fnc(node + 1, ...)
        //   beyond the valid vertex range and eventually access invalid memory.
        //
        // Dry run:
        // For v = 3, after coloring node 0, node 1, and node 2,
        // the next call is fnc(3, ...). Since 3 == v, return true.
        if(node == v) return true;

        // Try each color from 0 to m - 1 for the current node.
        //
        // Why colors start at 0:
        // - Color labels are arbitrary.
        // - With m colors, using 0 to m - 1 is convenient for indexing/thinking.
        //
        // What would break if this loop is removed:
        // - No color would ever be tried, so the function could never build
        //   a valid coloring.
        //
        // Dry run:
        // If m = 3, the function tries color 0, then 1, then 2.
        // The first safe color is tentatively chosen and recursion continues.
        for(int col = 0; col < m; col++) {
            // Before assigning col to node, verify it does not clash with
            // already-colored adjacent vertices.
            //
            // This is the constraint check step of backtracking.
            //
            // If this check is removed:
            // - The recursion would explore invalid states and could return
            //   true even when the graph is not legally colorable.
            if(issafetoassign(node, col, adj, color, v)) {
                // Choose:
                // Temporarily assign this safe color to the current node.
                //
                // Why this is necessary:
                // - The next recursive calls need to know that this node
                //   is already colored.
                //
                // If this line is removed:
                // - Future nodes would not see this node's color, so conflicts
                //   against this node would never be detected.
                color[node] = col;

                // Explore:
                // Move to the next vertex and try to color the rest of the graph.
                //
                // Why node + 1:
                // - This solution colors vertices in order: 0, 1, 2, ...
                //
                // If this recursive call is removed:
                // - The function would only color the current node and never
                //   verify whether the remaining graph can be colored.
                //
                // Dry run:
                // After setting color[0] = 0, call fnc(1, ...).
                // If that eventually colors all nodes, the true result bubbles up.
                if(fnc(node + 1, adj, m, color, v)) return true;

                // Un-choose / Backtrack:
                // The chosen color did not lead to a full valid coloring,
                // so reset this node and try the next color.
                //
                // Why this is necessary:
                // - Backtracking must clean up the current decision before
                //   exploring another decision.
                //
                // What would break if removed:
                // - A failed color would remain in color[node].
                // - Later attempts could be polluted by stale assignments,
                //   causing wrong conflict checks.
                color[node] = -1;
            }
        }

        // If no color from 0 to m - 1 works for this node, then this path fails.
        //
        // This tells the previous recursive call:
        // "Your earlier color choice led to a dead end; try another color."
        //
        // Edge case:
        // - If m == 0 and v > 0, the for loop never runs, so this returns false.
        return false;
    }

    bool graphColoring(int v, vector<vector<int>> &edges, int m) {
        
        // Convert the edge list into an adjacency matrix.
        //
        // What this does:
        // - Creates a v x v matrix initialized with 0.
        // - Later, adj[u][w] = 1 means u and w are connected.
        //
        // Why this is necessary:
        // - issafetoassign needs quick access to whether two vertices are adjacent.
        //
        // What would break if removed:
        // - The safety check would not know which vertices are connected.
        //
        // Space impact:
        // - This uses O(v^2) extra space.
        vector<vector<int>> adj(v, vector<int>(v, 0));

        // Build the undirected graph.
        //
        // Each edge e contains two vertices:
        // - e[0] is one endpoint
        // - e[1] is the other endpoint
        //
        // Dry run:
        // edges = {{0, 1}, {1, 2}}
        // After processing {0, 1}: adj[0][1] = 1 and adj[1][0] = 1.
        // After processing {1, 2}: adj[1][2] = 1 and adj[2][1] = 1.
        //
        // Edge cases missed:
        // - If an edge has invalid vertex indexes, this code may access
        //   out-of-bounds memory.
        // - If an edge vector has fewer than 2 elements, e[1] is invalid.
        for(auto &e : edges){
            // Extract the first endpoint of the edge.
            // If this line is removed, we cannot mark the edge in adj.
            int u = e[0];
            // Extract the second endpoint of the edge.
            // If this line is removed, we cannot complete the connection.
            int w = e[1];
            // Mark u connected to w.
            // Needed because adjacency matrix answers: "Is u connected to w?"
            adj[u][w] = 1;
            // Mark w connected to u because the graph is undirected.
            //
            // If this line is removed:
            // - The graph becomes one-directional in the matrix.
            // - Some conflicts may be missed depending on node order.
            adj[w][u] = 1;
        }

        // color[i] stores the assigned color of vertex i.
        // -1 means "not colored yet".
        //
        // Why -1:
        // - Valid colors are 0 to m - 1.
        // - So -1 is a clean marker that cannot be confused with a real color.
        //
        // If this initialization is removed:
        // - The algorithm would not know which vertices are uncolored.
        vector<int> color(v, -1);

        // Start recursive coloring from vertex 0.
        //
        // Return value:
        // - true if the graph can be colored using m colors.
        // - false otherwise.
        //
        // Edge case:
        // - If v == 0, fnc(0, ...) immediately returns true because node == v.
        return fnc(0, adj, m, color, v);
    }
};
int main() {
    
    return 0;
}

/*
### 1. Problem Understanding

This is a graph coloring / constraint satisfaction problem.
The task is to decide whether all v vertices can be colored using at most m
colors such that no two adjacent vertices have the same color.

Key constraints and clues:
- The input has vertices and edges, so it is a graph problem.
- The phrase "no adjacent vertices share the same color" signals constraints.
- We are asked whether a valid assignment exists, not how many assignments exist.
- Trying choices and undoing them is a strong clue for backtracking.

### 2. Pattern Recognition

Pattern used: Recursion + Backtracking.

How to recognize this in future:
- You need to assign one value from many choices to each item.
- A choice may become invalid because of earlier choices.
- If a choice fails later, you must undo it and try another choice.
- Keywords often include: generate, assign, arrange, color, place, valid configuration.

### 3. Approach Breakdown (Interview Style)

Brute force idea:
- Try every possible color assignment for all vertices.
- With v vertices and m colors, there are m^v possible assignments.
- After creating each full assignment, check whether it is valid.

Better approach:
- Still try possible assignments, but check validity while building the answer.
- If a color creates an immediate conflict, skip that branch early.

Optimal approach used here:
- Backtracking with pruning.
- Color one vertex at a time.
- Before assigning a color, check whether it conflicts with colored neighbors.
- If a path fails, undo the choice and try the next color.

Why this one is chosen:
- The problem is NP-complete in general, so we cannot expect a simple polynomial
  solution for all graphs.
- Backtracking is the standard interview-friendly way to search the solution
  space while pruning bad choices early.

### 4. Intuition Building

Think of coloring a map.
Pick one region, choose a color, then move to the next region.
Before coloring a region, look at its already-colored neighbors.
If any neighbor has that color, do not use it.
If all colors fail for a region, the previous region probably made a bad choice,
so go back and try a different color there.

The trick:
- Do not wait until the whole graph is colored to find mistakes.
- Detect conflicts immediately and stop exploring that branch.

### 5. How to Recall Later

Key signals:
- "Can we assign colors/values?"
- "Adjacent/related items cannot have the same value."
- "Find whether at least one valid assignment exists."

One-line memory trick:
Color, check neighbors, recurse, undo if stuck.

### 6. Common Mistakes

- Forgetting to backtrack with color[node] = -1.
- Checking all vertices for same color instead of only adjacent vertices.
- Forgetting that an undirected edge must be stored both ways.
- Using colors 1 to m in one place and 0 to m - 1 in another.
- Not handling disconnected graphs; this code handles them because it still
  processes every vertex from 0 to v - 1.
- Assuming greedy coloring is always enough; greedy can fail depending on order.

### 7. Complexity Analysis

Time Complexity:
- Worst case: O(m^v * v).
- There are up to m choices for each of v vertices, giving m^v recursive states.
- For each attempted color, issafetoassign scans v possible neighbors.
- Building the adjacency matrix takes O(v^2 + E), where E is number of edges.
- The exponential backtracking cost dominates.

Space Complexity:
- O(v^2) for the adjacency matrix.
- O(v) for the color array.
- O(v) recursion stack depth.
- Overall: O(v^2).

### 8. Alternative Approaches

1. Adjacency list instead of adjacency matrix:
   Store only actual neighbors. The safety check scans neighbors of node instead
   of all v vertices. This is usually better for sparse graphs.

2. Greedy coloring:
   Assign the first available color to each vertex. Fast, but not guaranteed to
   find a valid coloring even when one exists.

3. Bitmask optimization:
   Use bitsets or masks to track unavailable colors for faster checks. Useful
   for tighter competitive-programming constraints.

4. Graph-specific shortcuts:
   Some special graphs are easier. For example, checking whether a graph is
   2-colorable can be solved with BFS/DFS bipartite checking.
*/
