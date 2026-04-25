#include <iostream>
#include <string>
#include <cctype> // for tolower, isalnum
#include<vector>
using namespace std;
class Solution {
public:
    int compress(std::vector<char>& chars) {
        int idx = 0;
        int n = chars.size();

        for (int i = 0; i < n; i++) {
            char ch = chars[i];
            int count = 0;

            // Count consecutive occurrences of chars[i]
            while (i < n && chars[i] == ch) {
                count++;
                i++;
            }

            // Store character
            chars[idx++] = ch;

            // Store count if more than 1
            if (count > 1) {
                string str = to_string(count);
                for (char dig : str) {
                    chars[idx++] = dig;
                }
            }

            i--; // adjust index since outer loop will also increment
        }

        chars.resize(idx); // trim unused characters
        return idx;
    }
};

// Driver code
int main() {
    Solution sol;

    // Example input
    vector<char> chars = {'a','a','b','b','c','c','c'};

    cout << "Original: ";
    for (char c : chars) cout << c << " ";
    cout << "\n";

    int newLength = sol.compress(chars);

    cout << "Compressed: ";
    for (char c : chars) cout << c << " ";
    cout << "\nNew Length: " << newLength << "\n";

    return 0;
}
