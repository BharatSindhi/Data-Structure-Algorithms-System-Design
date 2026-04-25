#include <iostream>
using namespace std;

int sumArr(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int proArr(int arr[], int n) {
    int product = 1;  // ✅ Start from 1, not 0
    for (int i = 0; i < n; i++) {
        product *= arr[i];
    }
    return product;
}

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);

    int sum = sumArr(arr, n);
    int product = proArr(arr, n);

    cout << "Sum of array: " << sum << endl;
    cout << "Product of array: " << product << endl;

    return 0;
}
