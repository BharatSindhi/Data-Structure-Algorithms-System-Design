#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> m;
        queue<int> q;

        for (int i = 0; i < s.size(); i++) {
            m[s[i]]++;

            // If this is the first occurrence, push its index
            if (m[s[i]] == 1) {
                q.push(i);
            }

            // Remove non-unique characters from the front
            while (!q.empty() && m[s[q.front()]] > 1) {
                q.pop();
            }
        }

        // If queue is empty, no unique character
        return q.empty() ? -1 : q.front();
    }
};

int main() {
    Solution sol;
    string s = "loveleetcode";

    int index = sol.firstUniqChar(s);
    if (index != -1)
        cout << "First unique character: '" << s[index] << "' at index " << index << endl;
    else
        cout << "No unique character found." << endl;

    return 0;
}
