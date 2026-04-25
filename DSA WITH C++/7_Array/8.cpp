#include <iostream>
using namespace std;

void swapMaxAndMin(int arr[], int n) {
    int maxIdx = 0;
    int minIdx = 0;

    // Find indices of max and min elements
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[maxIdx]) {
            maxIdx = i;
        }
        if (arr[i] < arr[minIdx]) {
            minIdx = i;
        }
    }

    // Swap max and min
    int temp = arr[maxIdx];
    arr[maxIdx] = arr[minIdx];
    arr[minIdx] = temp;

    // Print updated array
    cout << "Array after swapping max and min: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    swapMaxAndMin(arr, n);

    return 0;
}
