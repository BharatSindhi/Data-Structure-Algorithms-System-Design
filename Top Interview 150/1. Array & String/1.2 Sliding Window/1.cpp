#include <iostream>
using namespace std;
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();

        int l = 0;
        int currWindowSum = 0;
        int result = INT_MAX;

        for (int r = 0; r < n; r++) {
            // Expand the window by adding the current element
            currWindowSum += nums[r];

            // Shrink the window while the sum is at least the target
            while (currWindowSum >= target) {
                result = min(result, r - l + 1);

                currWindowSum -= nums[l];
                l++;
            }
        }

        return (result == INT_MAX) ? 0 : result;
    }
};


int main() {
    // your code here
    return 0;
}