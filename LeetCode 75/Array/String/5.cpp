#include <iostream>
using namespace std;

class Solution {
public:

    bool isVowel(char ch) {
        return (ch == 'a' || ch == 'A' ||
                ch == 'e' || ch == 'E' ||
                ch == 'i' || ch == 'I' ||
                ch == 'o' || ch == 'O' ||
                ch == 'u' || ch == 'U');
    }

    string reverseVowels(string s) {
        int left = 0;
        int right = s.size() - 1;

        while (left < right) {

            if (isVowel(s[left]) && isVowel(s[right])) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
            else if (!isVowel(s[left])) {
                left++;
            }
            else {
                right--;
            }
        }

        return s;
    }
};
int main() {
    // your code here
    return 0;
}