#include <iostream>
#include <climits> // for INT_MIN
using namespace std;

int getMaxSum(int mat[][3], int row, int cols) {
    int maxSum = INT_MIN;  // handle negative numbers too
    for (int i = 0; i < row; i++) {
        int rowSum = 0;
        for (int j = 0; j < cols; j++) {
             rowSum += mat[i][j];
        }
        maxSum = max(maxSum, rowSum);
    }
    return maxSum;
}

int main() {
    int matrix[3][3] = {{1,2,30}, {3,5,6}, {7,8,9}};
    int rows = 3;
    int columns = 3;

    cout << "Maximum row sum = " << getMaxSum(matrix, rows, columns) << endl;

    return 0;
}
