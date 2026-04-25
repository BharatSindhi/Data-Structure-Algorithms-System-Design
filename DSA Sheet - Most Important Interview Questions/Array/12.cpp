#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    bool searchInRow(vector<vector<int>>& matrix, int target, int row) {
        int n = matrix[0].size();
        int st = 0, end = n - 1;

        while (st <= end) {
            int mid = st + (end - st) / 2;
            if (target == matrix[row][mid]) {
                return true;
            } else if (target > matrix[row][mid]) {
                st = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        return false; // important
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int startRow = 0, endRow = m - 1;

        while (startRow <= endRow) {
            int midRow = startRow + (endRow - startRow) / 2;

            if (target >= matrix[midRow][0] && target <= matrix[midRow][n - 1]) {
                return searchInRow(matrix, target, midRow);
            } else if (target > matrix[midRow][n - 1]) {
                startRow = midRow + 1;
            } else {
                endRow = midRow - 1;
            }
        }
        return false;
    }
};
int main() {
    
    return 0;
}





// 🔍 Problem: Search a 2D Matrix
// Matrix Properties

// Each row is sorted

// First element of each row is greater than the last element of the previous row

// So logically, the matrix behaves like a sorted 1D array, but we solve it cleanly using two binary searches.

// 🧠 High-Level Idea

// Instead of directly searching all elements:

// 1️⃣ Binary search on rows → find the possible row
// 2️⃣ Binary search inside that row → find the target

// This keeps the logic simple, safe, and interview-friendly.

// 🧩 Code Structure Overview

// You have two functions:

// searchMatrix()   → decides the correct row
// searchInRow()   → searches inside that row

// 🔹 Function 1: searchInRow(...)
// Purpose

// Perform binary search inside a single row

// Code
// bool searchInRow(vector<vector<int>>& matrix, int target, int row) {
//     int n = matrix[0].size();
//     int st = 0, end = n - 1;

//     while (st <= end) {
//         int mid = st + (end - st) / 2;

//         if (target == matrix[row][mid]) {
//             return true;
//         } 
//         else if (target > matrix[row][mid]) {
//             st = mid + 1;
//         } 
//         else {
//             end = mid - 1;
//         }
//     }
//     return false;
// }

// Explanation (Step-by-Step)
// Variable	Meaning
// row	Fixed row to search
// st	Starting column
// end	Ending column
// mid	Middle column

// 👉 This is a standard binary search on one row.

// 🔹 Function 2: searchMatrix(...)
// Purpose

// Find which row may contain the target

// Code
// bool searchMatrix(vector<vector<int>>& matrix, int target) {
//     int m = matrix.size(), n = matrix[0].size();
//     int startRow = 0, endRow = m - 1;

//     while (startRow <= endRow) {
//         int midRow = startRow + (endRow - startRow) / 2;

//         if (target >= matrix[midRow][0] && target <= matrix[midRow][n - 1]) {
//             return searchInRow(matrix, target, midRow);
//         } 
//         else if (target > matrix[midRow][n - 1]) {
//             startRow = midRow + 1;
//         } 
//         else {
//             endRow = midRow - 1;
//         }
//     }
//     return false;
// }

// Explanation (Step-by-Step)
// Variable	Meaning
// startRow	First row
// endRow	Last row
// midRow	Middle row
// Key Condition
// if (target >= matrix[midRow][0] &&
//     target <= matrix[midRow][n - 1])


// 👉 This checks whether target can exist in this row.

// 🧪 DRY RUN (MOST IMPORTANT 🔥)
// Input
// matrix = {
//   {1, 3, 5, 7},
//   {10, 11, 16, 20},
//   {23, 30, 34, 60}
// }
// target = 16

// 🔁 Step 1: Binary Search on Rows
// startRow	endRow	midRow	Row Range	Decision
// 0	2	1	10 → 20	target in range

// ➡ Call searchInRow(matrix, 16, 1)

// 🔁 Step 2: Binary Search in Row 1

// Row = [10, 11, 16, 20]

// st	end	mid	value	Action
// 0	3	1	11	move right
// 2	3	2	16	✅ found
// ✅ Final Output
// true

// ⏱ Time & Space Complexity
// Time Complexity

// Row search → O(log m)

// Column search → O(log n)

// Total: O(log m + log n)

// Space Complexity

// O(1) (no extra memory)

// 🧠 Why This Approach Is Good

// ✔ Very readable
// ✔ Easy to debug
// ✔ Easy to explain in exams
// ✔ Safer than flattening logic

// 🧠 One-Line Interview Explanation

// “I first binary-search the row where the target can exist, then perform binary search inside that row.”