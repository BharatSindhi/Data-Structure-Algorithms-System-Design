#include <iostream>
#include <climits>
using namespace std;

int getMaxColSum(int mat[][3], int row, int cols) {
    int maxSum = INT_MIN;  
    for (int col = 0; col < cols; col++) {
        int colSum = 0;
        for (int r = 0; r < row; r++) {
            colSum += mat[r][col];   // ✅ correct: row first, then column
        }
        maxSum = max(maxSum, colSum);
    }
    return maxSum;
}

int main() {
    int matrix[3][3] = {{1,2,30}, {3,5,6}, {7,8,9}};
    int rows = 3;
    int columns = 3;

    cout << "Maximum column sum = " << getMaxColSum(matrix, rows, columns) << endl;

    return 0;
}
