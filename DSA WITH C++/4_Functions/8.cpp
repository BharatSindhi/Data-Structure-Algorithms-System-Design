#include <iostream>
using namespace std;

int fibo(int n) {
    if (n == 0 || n == 1)
        return n;
    else
        return fibo(n - 1) + fibo(n - 2);
}

int main() {
    int N;
    cout << "Enter how many Fibonacci numbers you want: ";
    cin >> N;

    cout << "Fibonacci Series: ";
    for (int i = 0; i < N; i++) {
        cout << fibo(i) << " ";
    }
    cout << endl;

    return 0;
}
