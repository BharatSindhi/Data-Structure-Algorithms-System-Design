// Notes:
// - Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix.
// - This matrix has the following properties:
// - Integers in each row are sorted in ascending from left to right.
// - Integers in each column are sorted in ascending from top to bottom.

// Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
// Output: true

// Approch:
// - bruth force approch used 2 for loop and check if target is equal to matrix then return true
// - better approch is binear search 



#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n=matrix[0].size();
        int m=matrix.size();
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(matrix[i][j]==target){
                    return true;
                }
            }
            
        }
        return false;

    }
};

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n=matrix[0].size();
        int m=matrix.size();
        int r=0;int c=n-1;
        while(r<m && c>=0){
            if(target==matrix[r][c]){
                return true;
            }else if(target<matrix[r][c]){
                c--;
            }else{
                r++;
            }
        }
        return false;

    }
};

int main() {
    // your code here
    return 0;
}