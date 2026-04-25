#include <iostream>
#include<vector>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        
        int col0 = 1;

        // Step 1: mark rows and columns
        for(int i = 0; i < n; i++){
            if(matrix[i][0] == 0) col0 = 0;
            
            for(int j = 1; j < m; j++){
                if(matrix[i][j] == 0){
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // Step 2: update matrix
        for(int i = 1; i < n; i++){
            for(int j = 1; j < m; j++){
                if(matrix[i][0] == 0 || matrix[0][j] == 0){
                    matrix[i][j] = 0;
                }
            }
        }

        // Step 3: first row
        if(matrix[0][0] == 0){
            for(int j = 0; j < m; j++)
                matrix[0][j] = 0;
        }

        // Step 4: first column
        if(col0 == 0){
            for(int i = 0; i < n; i++)
                matrix[i][0] = 0;
        }
    }
};

int main() {
    // your code here
    return 0;
}