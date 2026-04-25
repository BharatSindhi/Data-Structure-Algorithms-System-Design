#include <iostream>
#include <vector>
using namespace std;

void helper(vector<vector<int>> &mat, int r, int c, string path, vector<string> &ans)
{
    int n = mat.size();

    // Out of bounds or blocked or already visited
    if (r < 0 || c < 0 || r >= n || c >= n || mat[r][c] == 0 || mat[r][c] == -1)
    {
        return;
    }

    // Reached destination
    if (r == n - 1 && c == n - 1)
    {
        ans.push_back(path);
        return;
    }

    // Mark as visited
    mat[r][c] = -1;

    // Explore all 4 directions
    helper(mat, r + 1, c, path + 'D', ans); // Down
    helper(mat, r - 1, c, path + 'U', ans); // Up
    helper(mat, r, c - 1, path + 'L', ans); // Left
    helper(mat, r, c + 1, path + 'R', ans); // Right

    // Backtrack
    mat[r][c] = 1;
}

vector<string> findPath(vector<vector<int>> &mat)
{
    int n = mat.size();
    vector<string> ans;
    string path = "";

    if (mat[0][0] == 0)
        return ans; // Start blocked
    helper(mat, 0, 0, path, ans);

    return ans;
}

int main()
{
    vector<vector<int>> mat = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}};

    vector<string> ans = findPath(mat);

    if (ans.empty())
    {
        cout << "No path found" << endl;
    }
    else
    {
        for (string path : ans)
        {
            cout << path << endl;
        }
    }

    return 0;
}
