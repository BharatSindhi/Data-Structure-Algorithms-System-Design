#include <iostream>
using namespace std;

// Function to check if a number is prime
bool isPrime(int n) {
    if (n < 2) return false;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }

    return true;
}

// WAF: Print all prime numbers from 2 to N
void printPrimesUpToN(int N) {
    for (int i = 2; i <= N; i++) {
        if (isPrime(i)) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main() {
    int N;
    cout << "Enter value of N: ";
    cin >> N;

    cout << "Prime numbers from 2 to " << N << " are: ";
    printPrimesUpToN(N);

    return 0;
}
