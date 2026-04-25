#include <iostream>
#include <string>
#include <cctype> // for tolower, isalnum
using namespace std;

// Function to check if a character is alphanumeric
bool isAlphaNum(char ch) {
    return (ch >= '0' && ch <= '9') || (tolower(ch) >= 'a' && tolower(ch) <= 'z');
}

// Function to check if a string is a palindrome
bool isPalindrome(string s) {
    int st = 0, end = s.length() - 1;
    while (st < end) {
        // Skip non-alphanumeric characters
        if (!isAlphaNum(s[st])) {
            st++;
            continue;
        }
        if (!isAlphaNum(s[end])) {
            end--;
            continue;
        }
        // Compare characters ignoring case
        if (tolower(s[st]) != tolower(s[end])) {
            return false;
        }
        st++;
        end--;
    }
    return true;
}

int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input); // read full line including spaces

    if (isPalindrome(input)) {
        cout << "The string is a palindrome." << endl;
    } else {
        cout << "The string is not a palindrome." << endl;
    }

    return 0;
}
