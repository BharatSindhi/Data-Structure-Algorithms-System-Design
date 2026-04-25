#include <iostream>
using namespace std;

int main() {
    int n = 5;
    for (int i = 0; i < n; i++) {
        // Print leading spaces
        for (int j = 0; j < n - i - 1; j++) {
            cout << " ";
        }

        // Print decreasing numbers from i to 1
        for (int j = i + 1; j > 1; j--) {
            cout << j - 1;
        }

        // Print increasing numbers from 1 to i
        for (int j = 1; j <= i; j++) {
            cout << j;
        }

        cout << endl;
    }

    return 0;
}
