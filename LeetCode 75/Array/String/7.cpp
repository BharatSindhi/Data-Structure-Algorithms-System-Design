// Notes:
// - Given an integer array nums
// -  return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].
// -  The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
// -  You must write an algorithm that runs in O(n) time and without using the division operation.

 
//  Input: nums = [1,2,3,4]
// Output: [24,12,8,6]

// Approch:
// - the bruth force approch is preseat element later value product but tle
// - the best solutions is prefix & suffix
// - 

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 1);
        int prefix = 1;

        // Left pass
        for (int i = 0; i < n; i++) {
            ans[i] = prefix;
            prefix *= nums[i];
        }

        // Right pass
        int postfix = 1;
        for (int i = n - 1; i >= 0; i--) {
            ans[i] *= postfix;
            postfix *= nums[i];
        }

        return ans;
    }
};


int main() {
    // your code here
    return 0;
}