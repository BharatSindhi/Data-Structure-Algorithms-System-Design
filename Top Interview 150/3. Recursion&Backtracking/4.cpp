#include <iostream>
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
        if (idx >= candidates.size() || target < 0)
            return;

        // include current element
        combin.push_back(candidates[idx]);
        getAllCombinations(candidates, idx, target - candidates[idx], ans,
                           combin);
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
    
    return 0;
}