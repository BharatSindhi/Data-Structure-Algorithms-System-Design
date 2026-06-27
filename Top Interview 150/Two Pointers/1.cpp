#include <iostream>
using namespace std;
class Solution {
public:
    bool isPalindrome(string s) {
        int l = 0;
        int r = s.size() - 1;

        while (l < r) {
            // Skip non-alphanumeric characters
            while (l < r && !isalnum(s[l])) {
                l++;
            }

            while (l < r && !isalnum(s[r])) {
                r--;
            }

            // Compare characters (case-insensitive)
            if (tolower(s[l]) != tolower(s[r])) {
                return false;
            }

            l++;
            r--;
        }

        return true;
    }
};
int main() {
    
    return 0;
}