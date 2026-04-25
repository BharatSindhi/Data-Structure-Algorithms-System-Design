#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class MinStack {
public:
    stack<pair<int, int>> s;

    MinStack() {}

    void push(int val) {
        if (s.empty()) {
            s.push({val, val});
        } else {
            int minVal = min(val, s.top().second);
            s.push({val, minVal});
        }
    }

    void pop() {
        s.pop();
    }

    int top() {
        return s.top().first;
    }

    int getMin() {
        return s.top().second; // ✅ fixed: use .second, not .second without parentheses
    }
};

int main() {
    MinStack st;

    st.push(3);
    st.push(5);
    cout << "Min: " << st.getMin() << endl;  // 3

    st.push(2);
    st.push(1);
    cout << "Min: " << st.getMin() << endl;  // 1

    st.pop();
    cout << "Top: " << st.top() << endl;     // 2
    cout << "Min: " << st.getMin() << endl;  // 2

    return 0;
}
