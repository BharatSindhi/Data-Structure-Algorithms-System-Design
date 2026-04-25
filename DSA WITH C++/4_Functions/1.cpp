#include <iostream>
using namespace std;

int min(int a, int b) {
    if (a < b)
        return a;
    else
        return b;
}

int main() {
    cout << "Min number: " << min(2, 4) << endl;
    return 0;
}
