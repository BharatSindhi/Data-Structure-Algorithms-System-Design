#include <iostream>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int maxVowels(string s, int k) {
        int maxVowels = 0;
        int windowVowels = 0;

        // Define set of vowels
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

        // Step 1: Count vowels in the first window of size k
        for (int i = 0; i < k; i++) {
            if (vowels.count(s[i])) windowVowels++;
        }

        maxVowels = windowVowels;

        // Step 2: Slide the window
        for (int i = k; i < s.length(); i++) {
            if (vowels.count(s[i])) windowVowels++;         // Add new char if vowel
            if (vowels.count(s[i - k])) windowVowels--;     // Remove char going out
            maxVowels = max(maxVowels, windowVowels);
        }

        return maxVowels;
    }
};

int main() {
    
    return 0;
}