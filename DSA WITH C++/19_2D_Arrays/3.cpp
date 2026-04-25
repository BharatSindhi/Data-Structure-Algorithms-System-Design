#include <iostream>
using namespace std;
bool linerarSearch(int mat[][3],int row , int cols , int key){
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (mat[i][j]==key)
            {
                return true;
            }
            
        }
        
    }
    
}
int main() {
    int matrix[4][3]={{1,2,3},{4,5,6},{7,8,9},{10,11,12}};
    int rows=4;
    int columns=3;
    cout<<linerarSearch(matrix,rows,columns,8);
    return 0;
}   