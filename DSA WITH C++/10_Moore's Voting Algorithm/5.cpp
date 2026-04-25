#include <iostream>
#include <vector>
using namespace std;

int majorityElement(vector<int>& nums) {
    int ans = 0;
    int freq = 0;

    for (int i = 0; i < nums.size(); i++) {
        if (freq == 0) {
            ans = nums[i];
            freq = 1;
        } else if (nums[i] == ans) {
            freq++;
        } else {
            freq--;
        }
    }

    // Optional verification step
    int count = 0;
    for (int num : nums) {
        if (num == ans) count++;
    }

    return (count > nums.size() / 2) ? ans : -1;
}

int main() {
    vector<int> nums = {2, 2, 1, 1, 1, 2, 2};
    
    int result = majorityElement(nums);

    if (result != -1)
        cout << "Majority Element: " << result << endl;
    else
        cout << "No majority element found." << endl;

    return 0;
}
