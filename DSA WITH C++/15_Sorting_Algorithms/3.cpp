#include <iostream>
using namespace std;

void selectSort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int smallIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[smallIndex]) {
                smallIndex = j;
            }
        }
        swap(arr[i], arr[smallIndex]);
    }
}

void printArr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr1[] = {4, 5, 3, 1, 2};
    int n = 5;
    cout << "Before Sorting: ";
    printArr(arr1, n);
    selectSort(arr1, n);
    cout << "After Sorting: ";
    printArr(arr1, n);
    return 0;
}
