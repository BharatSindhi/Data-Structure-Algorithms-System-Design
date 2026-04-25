#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    vector<int> arr = {6, 8, 0, 1, 3};
    stack<int> s;
    vector<int> ans(arr.size(), -1);  // initialize ans with -1

    for (int i = arr.size() - 1; i >= 0; i--) {
        while (!s.empty() && s.top() <= arr[i]) {
            s.pop();
        }
        if (!s.empty()) {
            ans[i] = s.top();
        }
        s.push(arr[i]);
    }

    for (int val : ans) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
