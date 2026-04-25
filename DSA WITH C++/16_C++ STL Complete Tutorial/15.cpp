#include <iostream>
#include <set> // multiset is inside <set>
using namespace std;

int main() {
    multiset<int> ms;

    ms.insert(10);
    ms.insert(5);
    ms.insert(20);
    ms.insert(10); // duplicate allowed

    cout << "Multiset contents (sorted, duplicates allowed):\n";
    for (auto val : ms) {
        cout << val << " ";
    }
    cout << endl;

    // Count occurrences
    cout << "Count of 10: " << ms.count(10) << endl;

    return 0;
}
