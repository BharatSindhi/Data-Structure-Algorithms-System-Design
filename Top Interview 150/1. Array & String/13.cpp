#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
           int max_index = 0;  // This will store the farthest index we can reach
        
        // Iterate through the array
        for (int i = 0; i < nums.size(); i++) {
            // If the current index exceeds the maximum index we can reach, return false
            if (i > max_index) {
                return false;
            }
            
            // Update the maximum index we can reach from this position
            max_index = max(max_index, i + nums[i]);
        }
        
        // If we reach here, it means we can reach the end
        return true;
    }
};

int main() {
    
    return 0;
}