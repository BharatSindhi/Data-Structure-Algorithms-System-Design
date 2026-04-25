#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int majorityElement(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end()); // Sort to group same elements
    int freq = 1;
    int ans = nums[0];

    for (int i = 1; i < n; i++) {
        if (nums[i] == nums[i - 1]) {
            freq++;
        } else {
            freq = 1;
        }

        if (freq > n / 2) {
            return nums[i];
        }
    }

    // Handle case if first element is majority
    if (freq > n / 2) return ans;

    return -1; // No majority element found
}

int main() {
    vector<int> nums = {2, 2, 1, 1, 1, 2, 2};  // Majority element is 2
    int result = majorityElement(nums);
    
    if (result != -1)
        cout << "Majority Element: " << result << endl;
    else
        cout << "No majority element found." << endl;

    return 0;
}
