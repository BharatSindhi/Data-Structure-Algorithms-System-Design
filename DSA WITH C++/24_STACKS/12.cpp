#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, -1);
        stack<int> s;

        // Traverse the array twice (for circular nature)
        for (int i = 2 * n - 1; i >= 0; i--) {
            while (!s.empty() && nums[s.top()] <= nums[i % n]) {
                s.pop();
            }
            if (i < n) { // Only fill answers for first n elements
                ans[i] = s.empty() ? -1 : nums[s.top()];
            }
            s.push(i % n);
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 1};
    vector<int> result = sol.nextGreaterElements(nums);

    cout << "Next Greater Elements: ";
    for (int x : result) cout << x << " ";
    cout << endl;

    return 0;
}
