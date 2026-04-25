#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 1);
        
        // First pass: calculate prefix product for each index
        for (int i = 1; i < n; ++i) {
            res[i] = res[i - 1] * nums[i - 1];
        }
        
        // Second pass: multiply with suffix product
        int suffix = 1;
        for (int i = n - 1; i >= 0; --i) {
            res[i] *= suffix;
            suffix *= nums[i];
        }

        return res;
    }
};

int main() {
    Solution sol;

    // Example input
    vector<int> nums = {1, 2, 3, 4};

    // Call productExceptSelf
    vector<int> result = sol.productExceptSelf(nums);

    // Print result
    cout << "Product Except Self: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
