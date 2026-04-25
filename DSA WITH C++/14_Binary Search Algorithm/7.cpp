#include <iostream>
#include <vector>
using namespace std;

bool isValid(vector<int> &arr, int n, int m, int maxAllowPages) {
    int stu = 1, pages = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxAllowPages) return false;

        if (pages + arr[i] <= maxAllowPages) {
            pages += arr[i];
        } else {
            stu++;
            pages = arr[i];
        }
    }
    return stu <= m;
}

int allocateBook(vector<int> &arr, int n, int m) {
    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];

    int st = 0, end = sum;
    int ans = -1;
    while (st <= end) {
        int mid = st + (end - st) / 2;
        if (isValid(arr, n, m, mid)) {
            ans = mid;
            end = mid - 1;
        } else {
            st = mid + 1;
        }
    }
    return ans;
}

int main() {
    vector<int> arr = {2, 1, 3, 4};
    int n = 4, m = 2;

    cout << allocateBook(arr, n, m) << endl;
    return 0;
}
