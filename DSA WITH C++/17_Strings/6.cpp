#include <iostream>
#include <vector>
#include <algorithm> // for swap
using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
        int st = 0;
        int end = s.size() - 1;
        while (st < end) {
            swap(s[st++], s[end--]);
        }
    }
};

int main() {
    // Example input
    vector<char> s = {'h', 'e', 'l', 'l', 'o'};
    
    Solution obj;
    obj.reverseString(s);
    
    // Print reversed string
    for (char c : s) {
        cout << c;
    }
    cout << endl;

    return 0;
}
