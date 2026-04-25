#include <iostream>
using namespace std;

int uniqueNum(int arr[], int n) {
    if (n == 0) return 0;

    int index = 1;  // Position to place next unique element

    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[index - 1]) {
            arr[index] = arr[i];
            index++;
        }
    }

    return index; // Number of unique elements
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 4, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int uniqueCount = uniqueNum(arr, n);

    cout << "Unique elements count: " << uniqueCount << endl;
    cout << "Unique elements: ";
    for (int i = 0; i < uniqueCount; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
