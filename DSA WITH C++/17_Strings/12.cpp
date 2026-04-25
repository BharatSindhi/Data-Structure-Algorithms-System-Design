#include <iostream>
#include <string>
#include <cctype> // for tolower, isalnum
using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0;

        // Iterate through both strings
        while (i < s.length() && j < t.length()) {
            if (s[i] == t[j]) {
                i++;  // Move pointer for 's' if characters match
            }
            j++;  // Always move pointer for 't'
        }

        // If 'i' reaches the length of 's', all characters were matched
        return (i == s.length());
    }
};

int main() {
    Solution sol;

    // Test cases
    string s1 = "abc", t1 = "ahbgdc";
    string s2 = "axc", t2 = "ahbgdc";
    string s3 = "", t3 = "ahbgdc";   // empty string is always a subsequence
    string s4 = "abc", t4 = "abc";   // exact match

    cout << "Is \"" << s1 << "\" a subsequence of \"" << t1 << "\"? "
         << (sol.isSubsequence(s1, t1) ? "true" : "false") << endl;

    cout << "Is \"" << s2 << "\" a subsequence of \"" << t2 << "\"? "
         << (sol.isSubsequence(s2, t2) ? "true" : "false") << endl;

    cout << "Is \"" << s3 << "\" a subsequence of \"" << t3 << "\"? "
         << (sol.isSubsequence(s3, t3) ? "true" : "false") << endl;

    cout << "Is \"" << s4 << "\" a subsequence of \"" << t4 << "\"? "
         << (sol.isSubsequence(s4, t4) ? "true" : "false") << endl;

    return 0;
}
