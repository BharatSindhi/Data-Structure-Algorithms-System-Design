#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {

        unordered_map<int, int> freq;

        // Count occurrences
        for (int num : arr) {
            freq[num]++;
        }

        unordered_set<int> seen;

        // Check whether frequencies are unique
        for (auto &p : freq) {

            if (seen.count(p.second)) {
                return false;
            }

            seen.insert(p.second);
        }

        return true;
    }
};

int main() {
    
    return 0;
}