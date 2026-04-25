#include <iostream>
#include <queue>
#include<vector>
using namespace std;

int main() {
    priority_queue<int,vector<int>,greater<int>> q;
    q.push(1);
    q.push(2);
    q.push(3);

    // Printing and popping queue
    while (!q.empty()) {
        cout << q.top() << " ";  // use front() instead of top()
        q.pop();
    }
    cout << endl;
    return 0;
}
