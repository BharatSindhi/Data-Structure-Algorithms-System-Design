#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<string, int> um;

    // Inserting values (duplicate keys overwrite previous value)
    um["tv"] = 100;
    um["laptop"] = 100;
    um["headphone"] = 50;
    um["tv"] = 200; // overwrites old value for "tv"

    cout << "Unordered_map contents (random order):\n";
    for (auto item : um) {
        cout << item.first << " => " << item.second << endl;
    }

    return 0;
}
