#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int st = 1, end = arr.size() - 2;  // Avoid boundary issues
        while (st <= end) {
            int mid = st + (end - st) / 2;
            if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
                return mid;
            } else if (arr[mid] > arr[mid - 1]) {
                st = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        return -1;  // Should not reach here if input is valid mountain array
    }
};

int main() {
    Solution solution;
    vector<int> arr = {0, 2, 4, 6, 5, 3, 1};  // Example mountain array
    int peakIndex = solution.peakIndexInMountainArray(arr);

    if (peakIndex != -1) {
        cout << "Peak found at index: " << peakIndex << endl;
    } else {
        cout << "Peak not found." << endl;
    }

    return 0;
}
