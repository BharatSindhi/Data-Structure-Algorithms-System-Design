#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    unordered_set<int> us;

    us.insert(10);
    us.insert(5);
    us.insert(20);
    us.insert(10); // duplicate ignored

    cout << "Unordered_set contents (no order, no duplicates):\n";
    for (auto val : us) {
        cout << val << " ";
    }
    cout << endl;

    // Check existence
    if (us.find(10) != us.end())
        cout << "10 is in the set\n";
    else
        cout << "10 is not in the set\n";

    return 0;
}
