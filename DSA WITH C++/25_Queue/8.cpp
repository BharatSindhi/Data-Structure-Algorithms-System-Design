#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;  // stores indices
        vector<int> res;

        // Process first window
        for (int i = 0; i < k; i++) {
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
        }

        // Process the rest of the array
        for (int i = k; i < nums.size(); i++) {
            // Push current window's max
            res.push_back(nums[dq.front()]);

            // Remove elements out of the window
            while (!dq.empty() && dq.front() <= i - k)
                dq.pop_front();

            // Remove smaller elements
            while (!dq.empty() && nums[dq.back()] <= nums[i])
                dq.pop_back();

            dq.push_back(i);
        }

        // Push the max of the last window
        res.push_back(nums[dq.front()]);

        return res;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    
    vector<int> ans = sol.maxSlidingWindow(nums, k);

    cout << "Maximums of each window: ";
    for (int num : ans) cout << num << " ";
    cout << endl;

    return 0;
}
