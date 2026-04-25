#include <iostream>
using namespace std;

int singleNum(int arr[], int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result ^= arr[i];  // XOR logic
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Single number is: " << singleNum(arr, n) << endl;
    return 0;
}
