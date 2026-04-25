#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> m; 
        m[0] = 1;  // Base case: empty subarray sum
        int sum = 0, count = 0;

        for (int num : nums) {
            sum += num;

            // Check if there exists a prefix sum that gives sum-k
            if (m.find(sum - k) != m.end()) {
                count += m[sum - k];
            }

            // Store/update frequency of current prefix sum
            m[sum]++;
        }

        return count;
    }
};

int main() {
    Solution sol;

    // Example input
    vector<int> nums = {1, 2, 3};
    int k = 3;

    int result = sol.subarraySum(nums, k);

    cout << "Number of subarrays with sum = " << k << " is: " << result << endl;

    return 0;
}
