#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
                st.push(s[i]);
            } else {
                if (st.empty()) return false;

                if ((st.top() == '(' && s[i] == ')') ||
                    (st.top() == '{' && s[i] == '}') ||
                    (st.top() == '[' && s[i] == ']')) {
                    st.pop();
                } else {
                    return false;
                }
            }
        }
        return st.empty();
    }
};

// ✅ main function for testing
int main() {
    Solution solution;

    string s1 = "()[]{}";
    string s2 = "(]";
    string s3 = "({[]})";
    string s4 = "(((";

    cout << s1 << " → " << (solution.isValid(s1) ? "Valid" : "Invalid") << endl;
    cout << s2 << " → " << (solution.isValid(s2) ? "Valid" : "Invalid") << endl;
    cout << s3 << " → " << (solution.isValid(s3) ? "Valid" : "Invalid") << endl;
    cout << s4 << " → " << (solution.isValid(s4) ? "Valid" : "Invalid") << endl;

    return 0;
}
