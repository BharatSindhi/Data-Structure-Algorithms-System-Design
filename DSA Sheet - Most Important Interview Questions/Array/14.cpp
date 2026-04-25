// Problem Statement :



// Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals and return an array of the non-overlapping intervals that cover all the intervals in the input.



// Example 1:
// Input: intervals = [[1, 3], [2, 6], [8, 10], [15, 18]]
// Output: [[1, 6], [8, 10], [15, 18]]
// Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].


// Example 2:
// Input: intervals = [[1,4],[4,5]]
// Output: [[1, 5]]
// Explanation: Intervals [1,4] and [4,5] are considered overlapping.
// Method Image 37

// Approach
// Using Sorting And Greedy :



// By sorting intervals by start time, we ensure an ordered merging process. As we iterate, overlapping intervals are merged by adjusting their end times, while non-overlapping ones are added separately. This approach efficiently consolidates overlapping intervals into a final merged list.



// 1. Sort the intervals:

// The provided list of intervals should be sorted in ascending order according to their start values.
// This facilitates the efficient merging of overlapping intervals and the sequential processing of intervals.
// 2. Initialize Result Storage:

// Create a list to store the merged intervals.
// Add the first interval to this list as a starting point.
// 3. Iterate Through the Intervals:

// One by one, go through the remaining intervals.
// Compare each interval to the result list's final merged interval.
// 4. Check for Overlapping Intervals:

// Merge them by updating the end time of the last merged interval if the start of the current interval falls inside the range of the last merged interval (i.e., overlap exists).
// Add the current interval to the result list separately if the intervals do not overlap.
// 5. Return the Merged Intervals:

// Convert the result list into a 2D array format and return it as the final merged intervals.
// Time Complexity	Space Complexity
// O(nlog(n))	O(1)

#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
   std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
       int n = intervals.size();
      
       // Sort intervals based on start time
       std::sort(intervals.begin(), intervals.end());


       // Result list to store merged intervals
       std::vector<std::vector<int>> result;
       result.push_back(intervals[0]);


       // Iterate through remaining intervals
       for (int i = 1; i < n; i++) {
           std::vector<int>& lastInterval = result.back();


           // Check for overlap and merge if necessary
           if (lastInterval[1] >= intervals[i][0]) {
               lastInterval[1] = std::max(lastInterval[1], intervals[i][1]);
           } else {
               result.push_back(intervals[i]);
           }
       }


       return result;
   }
};


int main() {
    
    return 0;
}