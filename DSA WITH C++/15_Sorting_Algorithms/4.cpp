 #include <iostream>
using namespace std;

void insertionSort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int curr=arr[i];
        int pre=i-1;
        while (pre>=0&&arr[pre]>curr)
        {
            arr[pre+1]=arr[pre];
            pre--;
        }
        arr[pre+1]=curr;
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
    insertionSort(arr1, n);
    cout << "After Sorting: ";
    printArr(arr1, n);
    return 0;
}
