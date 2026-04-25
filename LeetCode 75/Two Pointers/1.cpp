#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int j = 0; // position for next non-zero

        // Step 1: Move all non-zero elements forward
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] != 0) {
                nums[j] = nums[i];
                j++;
            }
        }

        // Step 2: Fill remaining positions with zero
        while(j < nums.size()) {
            nums[j] = 0;
            j++;
        }
    }
};
int main() {
    
    return 0;
}