#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    // Printing and popping queue
    while (!q.empty()) {
        cout << q.front() << " ";  // use front() instead of top()
        q.pop();
    }
    cout << endl;

    queue<int> q2;
    q2.push(10);
    q2.push(20);

    // Swapping queues
    q.swap(q2);

    cout << "q size: " << q.size() << endl;
    cout << "q2 size: " << q2.size() << endl;

    return 0;
}
