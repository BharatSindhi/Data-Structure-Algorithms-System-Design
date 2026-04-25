#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    // Printing and popping s
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    // Create another stack
    stack<int> s2;
    s2.push(10);
    s2.push(20);

    // Swap stacks
    s.swap(s2);

    cout << "s size: " << s.size() << endl;
    cout << "s2 size: " << s2.size() << endl;

    return 0;
}
