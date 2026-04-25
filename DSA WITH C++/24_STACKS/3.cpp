#include <iostream>
#include <stack>  // include stack library
using namespace std;

int main() {
    // Declare a stack of integers
    stack<int> s;

    // --- Push elements onto the stack ---
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);

    cout << "Stack size after pushing: " << s.size() << endl;
    cout << "Top element: " << s.top() << endl; // top = 40

    // --- Pop one element ---
    s.pop();
    cout << "After one pop, top element: " << s.top() << endl; // top = 30
    cout << "Stack size now: " << s.size() << endl;

    // --- Check if stack is empty ---
    if (s.empty())
        cout << "Stack is empty!" << endl;
    else
        cout << "Stack is not empty!" << endl;

    // --- Display and remove all elements ---
    cout << "Popping all elements: ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    // --- Final check ---
    cout << "Stack empty status: " << (s.empty() ? "Yes" : "No") << endl;

    return 0;
}
