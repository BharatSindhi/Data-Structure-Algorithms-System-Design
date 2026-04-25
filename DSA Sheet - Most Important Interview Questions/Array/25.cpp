// Notes:
// - You are given an array of integers nums
// - there is a sliding window of size k
// - which is moving from the very left of the array to the very right. 
// - You can only see the k numbers in the window
// -  Each time the sliding window moves right by one position.

// Return the max sliding window.


// Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
// Output: [3,3,5,5,6,7]
// Explanation: 
// Window position                Max
// ---------------               -----
// [1  3  -1] -3  5  3  6  7       3
//  1 [3  -1  -3] 5  3  6  7       3
//  1  3 [-1  -3  5] 3  6  7       5
//  1  3  -1 [-3  5  3] 6  7       5
//  1  3  -1  -3 [5  3  6] 7       6
//  1  3  -1  -3  5 [3  6  7]      7
 
 
//  Approch:
//  - the bruth force approch is used 3 for loop and create vector res and add max value 
//  - the better approch is two pointer and create vector res and add max value 
//  - best approch is sliding window and iterative and create and vector res and add max vaule 

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;   // stores indices
        vector<int> res;

        // Step 1: Process first window
        for (int i = 0; i < k; i++) {
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
        }

        // Step 2: Process remaining elements
        for (int i = k; i < nums.size(); i++) {

            // Store result of previous window
            res.push_back(nums[dq.front()]);

            // Remove elements out of window
            while (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }

            // Remove smaller elements
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }

            dq.push_back(i);
        }

        // Add result for last window
        res.push_back(nums[dq.front()]);

        return res;
    }
};
int main() {
    // your code here
    return 0;
}