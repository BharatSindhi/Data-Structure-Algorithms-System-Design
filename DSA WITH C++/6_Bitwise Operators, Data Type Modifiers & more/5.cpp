#include <iostream>
using namespace std;

int revNum(int n) {
    int newResNum = 0;
    while (n > 0) {
        int ld = n % 10;           // last digit
        newResNum = newResNum * 10 + ld;  // build reversed number
        n = n / 10;                // remove last digit
    }
    return newResNum;
}

int main() {
    int num = 123;
    cout << revNum(num) << endl;  // Output: 321
    return 0;
}
