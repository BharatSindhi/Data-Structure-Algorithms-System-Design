#include <iostream>
#include <utility> // for pair
using namespace std;

pair<int,int> linearSearch(int mat[][3], int row, int cols, int key) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < cols; j++) {
            if (mat[i][j] == key) {
                return {i, j}; // return position
            }
        }
    }
    return {-1, -1}; // not found
}

int main() {
    int matrix[4][3] = {{1,2,3}, {4,5,6}, {7,8,9}, {10,11,12}};
    int rows = 4, columns = 3;

    pair<int,int> pos = linearSearch(matrix, rows, columns, 8);

    if (pos.first != -1)
        cout << "Found at (" << pos.first << ", " << pos.second << ")" << endl;
    else
        cout << "Not found" << endl;

    return 0;
}
