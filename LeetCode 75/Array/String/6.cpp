#include <iostream>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        int n = s.length();
        string ans = "";
        
        for (int i = 0; i < n; i++) {
            
            // skip spaces
            if (s[i] == ' ') continue;
            
            string word = "";
            
            // take full word
            while (i < n && s[i] != ' ') {
                word += s[i];
                i++;
            }
            
            // reverse word back
            reverse(word.begin(), word.end());
            
            // add to answer
            if (!ans.empty()) ans += " ";
            ans += word;
        }
        
        return ans;
    }
};

int main() {
    // your code here
    return 0;
}