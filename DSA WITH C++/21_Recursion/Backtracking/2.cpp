#include <iostream>
#include <vector>
#include <algorithm> // for swap
using namespace std;

class Solution {
public:
    void getPerms(vector<int>& nums, int idx, vector<vector<int>>& ans) {
        if (idx == nums.size()) {
            ans.push_back(nums); // store current permutation
            return;
        }

        for (int i = idx; i < nums.size(); i++) {
            swap(nums[idx], nums[i]);          // choose
            getPerms(nums, idx + 1, ans);      // explore
            swap(nums[idx], nums[i]);          // un-choose (backtrack)
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        getPerms(nums, 0, ans);
        return ans;
    }
};

int main() {
    // Example input
    vector<int> nums = {1, 2, 3};

    Solution sol;
    vector<vector<int>> result = sol.permute(nums);

    // Print all permutations
    cout << "Permutations are:\n";
    for (auto &perm : result) {
        cout << "[ ";
        for (int num : perm) {
            cout << num << " ";
        }
        cout << "]\n";
    }

    return 0;
}
