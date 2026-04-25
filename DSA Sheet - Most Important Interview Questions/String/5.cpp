#include <iostream>
using namespace std;

class Solution {
public:
    bool isFreqSame(int freq1[], int freq2[]) {
        for (int i = 0; i < 26; i++) {
            if (freq1[i] != freq2[i]) {
                return false;
            }
        }
        return true;
    }

    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) return false;

        int freq[26] = {0};
        for (char c : s1) {
            freq[c - 'a']++;
        }

        int windSize = s1.length();

        for (int i = 0; i <= s2.length() - windSize; i++) {
            int windFreq[26] = {0};
            for (int j = i; j < i + windSize; j++) {
                windFreq[s2[j] - 'a']++;
            }
            if (isFreqSame(freq, windFreq)) {
                return true;
            }
        }
        return false;
    }
};


int main() {
    // your code here
    return 0;
}