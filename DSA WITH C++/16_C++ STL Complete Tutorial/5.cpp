#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
    deque<int> d;

    d.emplace_back(1);     // add 1 at the end
    d.push_back(2);        // add 2 at the end
    d.push_front(3);       // add 3 at the front
    d.push_front(5);       // add 5 at the front

    for (int val : d) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
