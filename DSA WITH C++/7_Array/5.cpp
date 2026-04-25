#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x;
    cout << "Enter the element to search: ";
    cin >> x;

    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            cout << "Element found at index: " << i << endl;
            return 0;
        }
    }

    cout << "Element not found." << endl;
    return 0;
}
