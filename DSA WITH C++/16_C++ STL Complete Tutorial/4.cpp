#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main() {
    list<int> l;

    l.emplace_back(1);     // add 1 at the end
    l.push_back(2);        // add 2 at the end
    l.push_front(3);       // add 3 at the front
    l.push_front(5);       // add 5 at the front

    for (int val : l) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
