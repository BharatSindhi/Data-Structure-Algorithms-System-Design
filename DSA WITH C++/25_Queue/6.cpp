#include <iostream>
#include <stack>
using namespace std;

class MyQueue {
public:
    stack<int> s1, s2;

    MyQueue() {}

    void push(int x) {
        // Move all elements from s1 to s2
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }

        // Push new element into s1
        s1.push(x);

        // Move all elements back from s2 to s1
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
    }

    int pop() {
        int ans = s1.top();
        s1.pop();
        return ans;
    }

    int peek() {
        return s1.top();
    }

    bool empty() {
        return s1.empty();
    }
};

int main() {
    MyQueue q;
    q.push(1);
    q.push(2);
    q.push(3);

    cout << "Front element: " << q.peek() << endl;  // Output: 1
    cout << "Popped: " << q.pop() << endl;          // Output: 1
    cout << "Front element now: " << q.peek() << endl; // Output: 2
    cout << "Is queue empty? " << (q.empty() ? "Yes" : "No") << endl; // Output: No

    return 0;
}
