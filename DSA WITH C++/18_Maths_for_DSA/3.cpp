#include <iostream>
#include <cmath>   // for log10
using namespace std;

void printDigits(int n) {
    int count = 0;
    while (n != 0) {
        int digit = n % 10;   // extract last digit
        cout << digit << endl;
        n = n / 10;
        count++;              // increment digit count
    }
    cout << "Count (from loop) = " << count << endl;
}

int main() {
    int n = 3594;
    printDigits(n);

    // Using log10 formula for digit count
    cout << "Count (using log10) = " << int(log10(n) + 1) << endl;

    return 0;
}
