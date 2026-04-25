#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};

    // Forward iteration using auto
    for (auto it = vec.begin(); it != vec.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    // Reverse iteration using auto
    for (auto rit = vec.rbegin(); rit != vec.rend(); rit++) {
        cout << *rit << " ";
    }
    cout << endl;

    return 0;
}
