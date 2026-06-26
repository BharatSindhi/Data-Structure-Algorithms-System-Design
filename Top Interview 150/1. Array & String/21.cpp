#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
       if (numRows == 1) return s;  // Special case when there's only one row

        vector<string> ans(numRows);  // Vector to hold rows of characters
        int i = 0;  // Track the current row
        bool goingDown = false;  // Direction flag

        // Iterate through each character in the input string
        for (char ch : s) {
            ans[i] += ch;  // Add the character to the current row

            // If we reach the top or bottom row, switch direction
            if (i == 0 || i == numRows - 1) 
                goingDown = !goingDown;

            // Move up or down based on the current direction
            i += goingDown ? 1 : -1;
        }

        // Concatenate all rows to form the final result
        string zigzag = "";
        for (string& row : ans) {
            zigzag += row;
        }

        return zigzag;
    }
};


int main() {
    
    return 0;
}