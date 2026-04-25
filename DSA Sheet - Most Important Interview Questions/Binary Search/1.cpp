// notes:
// - You are given an integer mountain array arr of length n where the values increase to a peak element and then decrease.
// - Return the index of the peak element.
// - Your task is to solve it in O(log(n)) time complexity.


// Input: arr = [0,1,0]
// Output: 1


// approch:
// - the bruth force approch is return an maximum index of the arr but not got an good time complexity 
// - the best approch is that is binary search that match the time complexity 


#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int low = 0;
        int high = arr.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] < arr[mid + 1]) {
                low = mid + 1;   // move right
            } else {
                high = mid;      // peak is here or left
            }
        }

        return low; // or high (both same)
    }
};


int main() {
    
    return 0;
}