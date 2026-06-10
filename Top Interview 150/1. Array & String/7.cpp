#include <iostream>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
         int count = 0;
        int i = s.length() - 1;

        // Skip trailing spaces
        while (i >= 0 && s[i] == ' ') {
            i--;
        }

        // Count the length of the last word
        while (i >= 0 && s[i] != ' ') {
            count++;
            i--;
        }

        return count;
    }
};

int main() {
    
    return 0;
}