#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    set<vector<int>> s; // optional for uniqueness

    void getAllCombinations(vector<int>& candidates, int idx, int target,
                            vector<vector<int>>& ans, vector<int>& combin) {
        if (target == 0) {
            if (s.find(combin) == s.end()) {
                ans.push_back(combin);
                s.insert(combin);
            }
            return;
        }
        if (idx >= (int)candidates.size() || target < 0)
            return;

        // include current element
        combin.push_back(candidates[idx]);
        getAllCombinations(candidates, idx, target - candidates[idx], ans, combin);
        combin.pop_back();

        // move to next element
        getAllCombinations(candidates, idx + 1, target, ans, combin);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> combin;
        getAllCombinations(candidates, 0, target, ans, combin);
        return ans;
    }
};

int main() {
    Solution sol;

    // Example input
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;

    vector<vector<int>> result = sol.combinationSum(candidates, target);

    cout << "Combinations that sum to " << target << ":\n";
    for (auto& comb : result) {
        cout << "[ ";
        for (int num : comb) cout << num << " ";
        cout << "]\n";
    }

    return 0;
}
