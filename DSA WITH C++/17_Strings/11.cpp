#include <iostream>
#include <string>
#include <cctype> // for tolower, isalnum
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        string ans = "";

        // Step 1: reverse the entire string
        reverse(s.begin(), s.end());

        // Step 2: process each word
        for (int i = 0; i < n; i++) {
            if (s[i] == ' ') continue; // skip extra spaces

            string word = "";
            while (i < n && s[i] != ' ') {
                word += s[i];
                i++;
            }

            // reverse the word back
            reverse(word.begin(), word.end());

            // append to answer
            if (!ans.empty()) ans += " ";
            ans += word;
        }

        return ans;
    }
};

int main() {
    Solution sol;

    // Test cases
    string s1 = "  hello   world!  ";
    string s2 = "the sky is blue";
    string s3 = "   a   good   example  ";

    cout << "Input: \"" << s1 << "\"\n";
    cout << "Output: \"" << sol.reverseWords(s1) << "\"\n\n";

    cout << "Input: \"" << s2 << "\"\n";
    cout << "Output: \"" << sol.reverseWords(s2) << "\"\n\n";

    cout << "Input: \"" << s3 << "\"\n";
    cout << "Output: \"" << sol.reverseWords(s3) << "\"\n";

    return 0;
}
