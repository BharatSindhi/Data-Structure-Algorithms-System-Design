#include <iostream>
using namespace std;

int main() {
    pair<int, int> p1 = {1, 3};
    pair<int, pair<char, int>> p2 = {1, {'k', 3}};

    cout << p1.first << endl;           // 1
    cout << p2.second.first << endl;    // k
    return 0;
}
