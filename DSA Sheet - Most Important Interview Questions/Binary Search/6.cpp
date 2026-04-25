// Approach
// Optimized Time Allocation using Binary Search :



// If there is only 1 painter (i.e., k = 1), then that painter must paint all the boards, so the total time will be the sum of the array.
// If there are n painters (i.e., k = n), then each painter can take one board, and the time taken will be the maximum board length.
// So, the valid time range lies between maxValue and totalSum.
// Now, we apply binary search in this range to find the minimum time required to paint all boards using k painters


// 1.Establish the parameters of the search:

// Go through the array to find:
// maxVal: the largest board (at least this amount must be painted by a painter).
// totalSum: the sum of all the boards (the longest time if a single painter handles it all).
// 2. Apply binary search within maxVal and totalSum

// To determine the least amount of time needed, experiment with different values between maxVal and totalSum.


// 3.Verify the correctness of each mid-value:

// Use isValid() to check if we can split the task among k painters without going over mid for each estimated time (mid).


// 4. Adjust the range based on the result:

// If mid works, store it and try a lower value (high = mid - 1) .
// If its fails, Increase the range (low = mid + 1) to give yourself more time .


// 5. Return the best time found:

// The result will contain the least amount of time that satisfies all requirements after the loop is finished.
// Method Image 642
// Method Image 643
// Method Image 644
// Method Image 645
// Time Complexity	Space Complexity
// O(n*log(sum - max))	O(1)


#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
// isValid function to check if it's possible to paint within maxAllowedTime
bool isValid(vector<int>& arr, int painters, int maxAllowedTime)
{
       int requiredPainters = 1;
       int currentTime = 0;
       for (int i = 0; i < arr.size(); i++) {
           if (arr[i] > maxAllowedTime) {
               return false; // One board exceeds allowed time
           }
           if (currentTime + arr[i] <= maxAllowedTime) {
               currentTime += arr[i];
           } else {
               requiredPainters++;
               currentTime = arr[i];
           }
       }
       return (requiredPainters <= painters);
}


int minTime(vector<int>& arr, int k) {
       int n = arr.size();
       int maxVal = arr[0];
       int totalSum = arr[0];


       for (int i = 1; i < n; i++) {
           maxVal = max(maxVal, arr[i]);
           totalSum += arr[i];
       }
       int low = maxVal;
       int high = totalSum;
       int result = -1;
       while (low <= high) {
           int mid = low + (high - low) / 2;
           if (isValid(arr, k, mid)) {
               result = mid;
               high = mid - 1;
           } else {
               low = mid + 1;
           }
       }
       return result;
   }
};


int main() {
    
    return 0;
}