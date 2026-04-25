#include <iostream>
using namespace std;

int main() {
    int n = 5; // You can change this or take input
    for (int i = 0; i < n; i++) {
        char ch = 'A'; // Reset ch for every row

        // Print leading spaces
        for (int j = 0; j < i; j++) {
            cout << " ";
        }

        // Print pattern
        for (int j = 0; j < n - i; j++) {
            cout << ch ; // Print character and row number
            ch++; // Move to next character
        }

        cout << endl;
    }

    return 0;
}
