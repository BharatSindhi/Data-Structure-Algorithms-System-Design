#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res = "";
        if (strs.empty()) return res;

        for (int i = 0; i < strs[0].size(); i++) {
            char c = strs[0][i];
            for (auto &s : strs) {
                // Check if i exceeds the string length OR characters don't match
                if (i >= s.size() || s[i] != c) {
                    return res;
                }
            }
            res += c;
        }
        return res;
    }
}; 
int main() {
    // your code here
    return 0;
}