#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, string> m = {
        {10, "A"}, {20, "B"}, {30, "C"}, {40, "D"}
    };

    auto lb = m.lower_bound(25);
    auto ub = m.upper_bound(25);

    if (lb != m.end())
        cout << "Lower bound key: " << lb->first << " value: " << lb->second << endl;

    if (ub != m.end())
        cout << "Upper bound key: " << ub->first << " value: " << ub->second << endl;

    return 0;
}
