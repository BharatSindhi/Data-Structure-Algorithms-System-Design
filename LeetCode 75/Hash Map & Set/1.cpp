#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {

        unordered_set<int> s1(nums1.begin(), nums1.end());
        unordered_set<int> s2(nums2.begin(), nums2.end());

        vector<int> first;
        vector<int> second;

        // Elements present in nums1 but not in nums2
        for (int x : s1) {
            if (s2.find(x) == s2.end()) {
                first.push_back(x);
            }
        }

        // Elements present in nums2 but not in nums1
        for (int x : s2) {
            if (s1.find(x) == s1.end()) {
                second.push_back(x);
            }
        }

        return {first, second};
    }
};
int main() {
    
    return 0;
}