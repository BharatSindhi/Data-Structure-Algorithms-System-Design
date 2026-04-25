#include <iostream>
#include <vector>
using namespace std;

class Stack {
    vector<int> v;

public:
    void push(int val) {
        v.push_back(val);
    }

    void pop() {
        if (!v.empty()) v.pop_back();
    }

    int top() {
        if (!v.empty()) return v[v.size() - 1];
        return -1; // optional: return -1 if empty
    }

    bool empty() {
        return v.size() == 0;
    }
};

int main() {
    Stack s;

    s.push(10);
    s.push(20);
    s.push(30);

    while(!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    return 0;
}
