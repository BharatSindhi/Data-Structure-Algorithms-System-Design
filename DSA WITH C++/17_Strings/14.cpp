#include <iostream>
#include <string>
#include <cctype> // for tolower, isalnum
using namespace std;

class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        // If concatenation in both orders isn't the same, no gcd string exists
        if (str1 + str2 != str2 + str1) {
            return "";
        } else {
            // gcd of lengths gives the length of gcd string
            return str1.substr(0, gcd((int)str1.length(), (int)str2.length()));
        }
    }
};

int main() {
    Solution sol;

    // Example test cases
    string str1 = "ABCABC";
    string str2 = "ABC";

    cout << "GCD of \"" << str1 << "\" and \"" << str2 << "\" is: \""
         << sol.gcdOfStrings(str1, str2) << "\"" << endl;

    str1 = "ABABAB";
    str2 = "ABAB";
    cout << "GCD of \"" << str1 << "\" and \"" << str2 << "\" is: \""
         << sol.gcdOfStrings(str1, str2) << "\"" << endl;

    str1 = "LEET";
    str2 = "CODE";
    cout << "GCD of \"" << str1 << "\" and \"" << str2 << "\" is: \""
         << sol.gcdOfStrings(str1, str2) << "\"" << endl;

    return 0;
}
