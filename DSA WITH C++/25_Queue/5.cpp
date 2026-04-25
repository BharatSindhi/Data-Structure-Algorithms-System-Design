#include <iostream>
#include <queue>
using namespace std;

class MyStack {
public:
    queue<int> q1, q2;

    MyStack() {}

    void push(int x) {
        // Step 1: Move all elements from q1 to q2
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }

        // Step 2: Push new element into q1
        q1.push(x);

        // Step 3: Move everything back from q2 to q1
        while (!q2.empty()) {
            q1.push(q2.front());
            q2.pop();
        }
    }

    int pop() {
        if (q1.empty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        int topElement = q1.front();
        q1.pop();
        return topElement;
    }

    int top() {
        if (q1.empty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return q1.front();
    }

    bool empty() {
        return q1.empty();
    }
};

int main() {
    MyStack st;

    st.push(10);
    st.push(20);
    st.push(30);

    cout << "Top element: " << st.top() << endl;  // 30
    cout << "Pop element: " << st.pop() << endl;  // 30
    cout << "Top element now: " << st.top() << endl;  // 20
    cout << "Is empty? " << (st.empty() ? "Yes" : "No") << endl;

    st.pop();
    st.pop();
    cout << "Is empty after popping all? " << (st.empty() ? "Yes" : "No") << endl;

    return 0;
}
