#include <iostream>
#include <vector>
using namespace std;

int majorityElement(vector<int>& nums) {
    int n = nums.size();  // ✅ Fixed missing semicolon

    for (int val : nums) {
        int freq = 0;
        for (int ele : nums) {
            if (ele == val) {
                freq++;
            }
        }
        if (freq > n / 2) {
            return val;
        }
    }
    return -1; // ✅ In case no majority element exists (shouldn't happen if guaranteed)
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
