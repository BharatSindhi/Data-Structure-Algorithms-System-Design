#include <iostream>
#include <list>
using namespace std;

class StackList {
    list<int> ll;

public:
    void push(int val) {
        ll.push_front(val); // ✅ add element at front
    }

    void pop() {
        if (!ll.empty())    // ✅ avoid popping from empty list
            ll.pop_front();
    }

    int top() {
        if (!ll.empty())    // ✅ avoid accessing empty list
            return ll.front();
        else
            return -1;      // optional error indicator
    }

    bool empty() {
        return ll.empty();  // ✅ simpler way
    }
};

int main() {
    StackList s;

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
