#include <iostream>
using namespace std;

string isPrime(int n) {
    if (n <= 1) return "Non prime"; // 0 and 1 are not prime
    if (n == 2) return "Prime";     // 2 is prime

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return "Non prime";
        }
    }
    return "Prime";
}

int main() {
    int m = 85;
    cout << isPrime(m) << endl;
    return 0;
}
