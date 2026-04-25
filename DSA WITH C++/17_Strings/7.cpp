#include <iostream>
#include <string>
#include <cctype> // for tolower, isalnum
using namespace std;

class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int i = 0, j = 0;
        int n1 = word1.size();
        int n2 = word2.size();
        string ans = "";

        while (i < n1 && j < n2) {
            ans += word1[i++];
            ans += word2[j++];
        }

        while (i < n1) {
            ans += word1[i++];
        }

        while (j < n2) {
            ans += word2[j++];
        }

        return ans;
    }
};

int main() {
    Solution sol;
    string word1, word2;

    cout << "Enter first word: ";
    cin >> word1;
    cout << "Enter second word: ";
    cin >> word2;

    string result = sol.mergeAlternately(word1, word2);
    cout << "Merged string: " << result << endl;

    return 0;
}
