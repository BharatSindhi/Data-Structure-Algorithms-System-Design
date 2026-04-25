// Approach
// Binary Search on Answer :



// To stop cows from getting too close and fighting, we need to spread them out as much as possible across the stalls.

// By sorting the stall positions, we can try different gaps and see what works.

// Using binary search, we test each possible gap and check if all cows can be placed with that spacing.

// The biggest distance that still allows all cows to fit becomes our final answer.



// 1. Sort the stall positions

// We sort the array so that cows can be arranged in increasing order of stall places for easy distance comparisons.


// 2. Define the search space for minimum distance

// The smallest possible distance between any two cows is 1, stalls[n - 1] - stalls[0], is the longest distance that can exist between any two cows.
// 3. Use binary search to find the maximum possible minimum distance

// Instead of using the stall positions, we conduct a binary search on the distance value (mid).
// We determine if it is feasible to arrange every cow so that the distance between each pair is at least mid.
// 4. Validate each distance using a helper function

// Place the first cow in the first stall to begin.
// Traverse the stalls and place the next cow only if it's at least mid units away from the last placed cow.
// The existing distance is appropriate if we can arrange all of the cows in this manner.
// 5. Adjust search range based on validation

// If it is feasible to place every cow, Store the distance as a possible solution and look for a higher number (low = mid + 1) .
// If it isn't possible, reduce the search space (high = mid - 1).
// 6. Return the largest valid distance

// When low > high, the loop is terminated, and the result is the most recent valid distance calculated.


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
bool isValid(vector<int>& stalls, int cows, int minDistance)
{
   int totalStalls = stalls.size();
   int cowsPlaced = 1;
   int currentIndex = 1;
   int lastPlacedIndex = 0;


   while (currentIndex < totalStalls && cowsPlaced < cows)
   {
       if (stalls[currentIndex] - stalls[lastPlacedIndex] >= minDistance) {
           cowsPlaced++;
           lastPlacedIndex = currentIndex;
       }
       currentIndex++;
   }
   return (cowsPlaced == cows);
   }


int aggressiveCows(vector<int>& stalls, int cows)
{
   int totalStalls = stalls.size();
   sort(stalls.begin(), stalls.end());


   int low = 1;
   int high = stalls[totalStalls - 1] - stalls[0];
   int maxMinDistance = 1;


   while (low <= high)
   {
       int mid = (low + high) / 2;


       if (isValid(stalls, cows, mid)) {
           maxMinDistance = mid;
           low = mid + 1;
       } else {
           high = mid - 1;
       }
   }
   return maxMinDistance;
 }
};




int main() {
    // your code here
    return 0;
}