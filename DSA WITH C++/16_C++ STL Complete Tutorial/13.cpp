#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s;

    s.insert(10);
    s.insert(5);
    s.insert(20);
    s.insert(10); // duplicate ignored

    cout << "Set contents (sorted, no duplicates):\n";
    for (auto val : s) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
