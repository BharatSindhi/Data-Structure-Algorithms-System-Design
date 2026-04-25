#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Solution {
public:
    // Iterative O(n^2) checker:
    // Map each value (0..n*n-1) to its coordinates, then ensure consecutive values
    // are a valid knight move and that grid[0][0] == 0.
    bool checkValidGrid(const vector<vector<int>>& grid) {
        int n = (int)grid.size();
        if (n == 0) return true;

        // Quick start check: requirement (from your earlier version) that (0,0) == 0
        if (grid[0][0] != 0) return false;

        int total = n * n;
        vector<pair<int,int>> pos(total, make_pair(-1, -1));
        vector<char> seen(total, 0);

        // fill position array and detect invalid values / duplicates
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int val = grid[i][j];
                if (val < 0 || val >= total) return false;     // out of valid range
                if (seen[val]) return false;                   // duplicate value
                seen[val] = 1;
                pos[val] = make_pair(i, j);
            }
        }

        // ensure pos[0] is (0,0) (extra safety)
        if (pos[0].first != 0 || pos[0].second != 0) return false;

        // check each consecutive pair is a knight move
        for (int k = 0; k + 1 < total; ++k) {
            int r1 = pos[k].first, c1 = pos[k].second;
            int r2 = pos[k+1].first, c2 = pos[k+1].second;
            int dr = r1 - r2; if (dr < 0) dr = -dr;
            int dc = c1 - c2; if (dc < 0) dc = -dc;
            if (!((dr == 1 && dc == 2) || (dr == 2 && dc == 1))) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cout << "Enter grid size n: ";
    if (!(cin >> n)) return 0;
    if (n <= 0) {
        cout << "Invalid grid size\n";
        return 0;
    }

    vector<vector<int>> grid(n, vector<int>(n));
    cout << "Enter the grid values (" << n * n << " numbers):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    Solution sol;
    if (sol.checkValidGrid(grid)) {
        cout << "The grid represents a valid knight's tour.\n";
    } else {
        cout << "The grid is NOT a valid knight's tour.\n";
    }

    return 0;
}
