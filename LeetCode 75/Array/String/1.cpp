// notes:
// - You are given two strings word1 and word2.
// - Merge the strings by adding letters in alternating order, starting with word1.
// -  append the additional letters onto the end of the merged string.
// -  Return the merged string.

// Input: word1 = "abc", word2 = "pqr"
// Output: "apbqcr"


// approch :
// - best aprroch is used two pointer approch and strated at 0 ans step by step used the  value and store the 
// - 
 


#include <iostream>
using namespace std;

class Solution {
public:
    string mergeAlternately(string word1, string word2) {

        int i = 0;
        int j = 0;

        string ans = "";

        while(i < word1.size() && j < word2.size())
        {
            ans += word1[i];
            ans += word2[j];

            i++;
            j++;
        }

        while(i < word1.size())
        {
            ans += word1[i];
            i++;
        }

        while(j < word2.size())
        {
            ans += word2[j];
            j++;
        }

        return ans;
    }
};

int main() {
    
    return 0;
}