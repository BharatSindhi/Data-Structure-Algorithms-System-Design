#include <iostream>
using namespace std;

void printIntersection(int arr1[], int n1, int arr2[], int n2) {
    cout << "Intersection: ";
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (arr1[i] == arr2[j]) {
                cout << arr1[i] << " ";
                break; // Prevent duplicates
            }
        }
    }
    cout << endl;
}

int main() {
    int arr1[] = {1, 2, 4, 5, 6};
    int arr2[] = {2, 3, 5, 7};

    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    printIntersection(arr1, n1, arr2, n2);

    return 0;
}
