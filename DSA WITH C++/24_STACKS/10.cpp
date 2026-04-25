#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class MinStack {
public:
    stack<long long int> s;
    long long int minVal;

    MinStack() {}

    void push(int val) {
        if (s.empty()) {
            s.push(val);
            minVal = val;
        } else {
            if (val < minVal) {
                s.push(2LL * val - minVal); // store encoded value
                minVal = val;
            } else {
                s.push(val);
            }
        }
    }

    void pop() {
        if (s.empty()) return;
        if (s.top() < minVal) {
            minVal = 2LL * minVal - s.top(); // decode previous min
        }
        s.pop();
    }

    int top() {
        if (s.empty()) return -1;
        if (s.top() < minVal) {
            return (int)minVal;
        }
        return (int)s.top();
    }

    int getMin() {
        return (int)minVal;
    }
};

int main() {
    MinStack st;
    st.push(5);
    st.push(3);
    st.push(7);

    cout << "Current Min: " << st.getMin() << endl; // 3
    cout << "Top: " << st.top() << endl;            // 7

    st.pop();
    cout << "After pop, Top: " << st.top() << endl; // 3
    cout << "Current Min: " << st.getMin() << endl; // 3

    st.pop();
    cout << "After pop, Min: " << st.getMin() << endl; // 5

    return 0;
}
