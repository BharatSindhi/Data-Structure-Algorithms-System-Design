#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    string longestPrefix(string s) {
        int n = s.size();
        vector<int> p(n, 0);

        for(int i = 1; i < n; i++){
            int j = p[i - 1];

            while(j > 0 && s[i] != s[j]){
                j = p[j - 1];  // ✅ correct fallback
            }

            if(s[i] == s[j]){
                j++;
            }

            p[i] = j;
        }

        return s.substr(0, p[n - 1]);  // ✅ return string
    }
};

int main() {
    
    return 0;
}