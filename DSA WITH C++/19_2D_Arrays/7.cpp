#include <iostream>
using namespace std;
int diagonalSum(int mat[][3],int n){
    int sum=0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i==j)
            {
                sum+=mat[i][j];
            }else if (j==n-i-1)
            {
                sum+=mat[i][j];
            }
            
            
        }
        
    }
    return sum;
}

int diagonalSum(int mat[][3], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += mat[i][i];             // primary diagonal
        if (i != n - i - 1)           // avoid double counting center
            sum += mat[i][n - i - 1]; // secondary diagonal
    }
    return sum;
}


int main() {
    int matrix[3][3] = {{1,2,30}, {3,5,6}, {7,8,9}};
    int n=3;    
    cout<<diagonalSum(matrix,n)<<endl;
    cout<<diagonalSum(matrix,n)<<endl;

    return 0;
}