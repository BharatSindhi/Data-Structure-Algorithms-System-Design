#include <iostream>
#include <map> // for multimap
using namespace std;

int main() {
    multimap<string, int> mm;

    // Inserting values (duplicate keys allowed)
    mm.insert({"tv", 100});
    mm.insert({"laptop", 100});
    mm.insert({"headphone", 50});
    mm.insert({"tv", 200}); // duplicate key

    cout << "Multimap contents (sorted by key):\n";
    for (auto item : mm) {
        cout << item.first << " => " << item.second << endl;
    }

    return 0;
}
