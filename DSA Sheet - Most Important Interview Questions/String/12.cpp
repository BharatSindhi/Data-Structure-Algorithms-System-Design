#include <iostream>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        int n = s.size();
        string word = "";
        string res = "";
        
        for(int i = 0; i < n; i++) {
            
            // Skip spaces
            while(i < n && s[i] == ' ') i++;
            
            word = "";
            
            // Build word
            while(i < n && s[i] != ' ') {
                word += s[i];
                i++;
            }
            
            // Reverse word back
            reverse(word.begin(), word.end());
            
            // Add to result
            if(word.size() > 0) {
                if(res.size() > 0) res += " ";
                res += word;
            }
        }
        
        return res;
    }
};

    
int main() {
    // your code here
    return 0;
}