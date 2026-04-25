#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
using namespace std;

class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        vector<int> ans;
        unordered_set<int> s;

        int n = grid.size();
        int a = -1, b = -1;
        long long expSum = 0, actualSum = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                actualSum += grid[i][j];

                if (s.find(grid[i][j]) != s.end()) {
                    a = grid[i][j]; // repeated number
                }
                s.insert(grid[i][j]);
            }
        }

        expSum = 1LL * (n * n) * (n * n + 1) / 2;
        b = expSum + a - actualSum; // missing number
        ans.push_back(a);
        ans.push_back(b);

        return ans;
    }
};

int main() {
    // Example input
    int n;
    cout << "Enter grid size n: ";
    cin >> n;

    vector<vector<int>> grid(n, vector<int>(n));
    cout << "Enter the " << n*n << " numbers in the grid:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    Solution sol;
    vector<int> result = sol.findMissingAndRepeatedValues(grid);

    cout << "Repeated number: " << result[0] << "\n";
    cout << "Missing number: " << result[1] << "\n";

    return 0;
}
