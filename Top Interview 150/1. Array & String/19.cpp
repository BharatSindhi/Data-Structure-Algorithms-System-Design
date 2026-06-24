#include <iostream>
using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        // Map values to symbols sorted in descending order
        const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        const string symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        
        string roman = "";
        
        // Loop through all values
        for (int i = 0; i < 13; ++i) {
            // Keep appending the symbol while num is greater than or equal to the current value
            while (num >= values[i]) {
                roman += symbols[i];
                num -= values[i];
            }
        }
        
        return roman;
    }
};


int main() {
    
    return 0;
}