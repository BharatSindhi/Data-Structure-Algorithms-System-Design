#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& mat, int tar) {
        int m = mat.size(), n = mat[0].size();
        int r = 0, c = n - 1; // start from top-right corner

        while (r < m && c >= 0) {
            if (tar == mat[r][c]) {
                return true;
            } else if (tar < mat[r][c]) {
                c--; // move left
            } else {
                r++; // move down
            }
        }
        return false;
    }
};

int main() {
    Solution sol;

    // Example matrix
    vector<vector<int>> matrix = {
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };

    int target;
    cout << "Enter target value: ";
    cin >> target;

    bool found = sol.searchMatrix(matrix, target);
    if (found)
        cout << "Target " << target << " found in matrix ✅" << endl;
    else
        cout << "Target " << target << " NOT found in matrix ❌" << endl;

    return 0;
}


