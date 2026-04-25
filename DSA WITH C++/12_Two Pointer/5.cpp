#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end()); // Sort the array
        int left = 0;
        int right = nums.size() - 1;
        int count = 0;

        while (left < right) {
            int currentSum = nums[left] + nums[right];
            if (currentSum == k) {
                count++;
                left++;
                right--;
            } else if (currentSum < k) {
                left++;
            } else {
                right--;
            }
        }

        return count;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3, 4};
    int k = 5;
    cout << "Max Operations: " << sol.maxOperations(nums, k) << endl;
    return 0;
}
