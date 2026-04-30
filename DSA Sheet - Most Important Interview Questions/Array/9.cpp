// Problem Statement:



// Given an array nums with n objects colored red, white, or blue, sort them in place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

// We will use the integers 0 , 1 , and 2 to represent the color red, white, and blue, respectively.

// You must solve this problem without using the library's sort function.



// Example: Toy Sorting

// In a cheerful playroom, kids played all day with Red Cars, White Teddy Bears, and Blue Balls, leaving the toy box in a huge mess. The next morning, they struggled to find their favorite toys. Seeing this, the caretaker had a clever idea—instead of using extra bins, they neatly arranged the toys inside the same box. Red Cars first, Teddy Bears in the middle, and Blue Balls at the end—all sorted in no time! The kids were thrilled, and from that day on, keeping the toy box tidy became a fun and easy habit!



// Example 1:
// Input: nums = [2,0,2,1,1,0]
// Output: [0,0,1,1,2,2]


// Example 2:
// Input: nums = [2,0,1]
// Output: [0, 1, 2]

// DSA
// DSA Sheet

// Topic Difficulty
// Medium
// Microsoft
// Amazon
// MakeMyTrip
// Asked by Companies
// Sort array of 0s, 1s & 2s
// Practice Here
// Go to LeetCode
// Topics
// Click to see

// Problem Statement:



// Given an array nums with n objects colored red, white, or blue, sort them in place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

// We will use the integers 0 , 1 , and 2 to represent the color red, white, and blue, respectively.

// You must solve this problem without using the library's sort function.



// Example: Toy Sorting

// In a cheerful playroom, kids played all day with Red Cars, White Teddy Bears, and Blue Balls, leaving the toy box in a huge mess. The next morning, they struggled to find their favorite toys. Seeing this, the caretaker had a clever idea—instead of using extra bins, they neatly arranged the toys inside the same box. Red Cars first, Teddy Bears in the middle, and Blue Balls at the end—all sorted in no time! The kids were thrilled, and from that day on, keeping the toy box tidy became a fun and easy habit!



// Example 1:
// Input: nums = [2,0,2,1,1,0]
// Output: [0,0,1,1,2,2]


// Example 2:
// Input: nums = [2,0,1]
// Output: [0, 1, 2]
// Method

// Time Complexity

// Space Complexity

// Better

// O(n)

// O(1)

// Best

// O(n)

// O(1)

// Method

// Better

// Best
// Approach
// Using Dutch National Flag Algorithm :



// Using three pointers:  low, mid, and high. We sort the array, where all 0s are at the front, 1s are in the middle, and 2s are at the end. This avoids extra space and ensures optimal efficiency.



// 1. Initialize low = 0, mid = 0, and high = n - 1.

// 2. Traverse the array while mid <= high:

// If nums[mid] == 0, swap with nums[low] and increment both low and mid.
// If nums[mid] == 1, just move mid forward.
// If nums[mid] == 2, swap with nums[high] and decrement high (don't move mid yet).
// 3. Stop when mid > high. The array is now sorted in-place.

// Method Image 27
// Method Image 28
// Method Image 29
// Method Image 30
// Method Image 31
// Method Image 32
// Time Complexity	Space Complexity
// O(n) 	O(1)


#include <iostream>
#include<vector>
using namespace std;



class Solution {
public:
   void sortColors(vector<int>& nums) {
       // Dutch National Flag algorithm.
       // What this function does:
       // It sorts an array containing only 0s, 1s, and 2s in-place.
       //
       // Why this algorithm is useful:
       // Since there are only 3 possible values, we do not need comparison sorting.
       // We can divide the array into 4 conceptual regions:
       // 1. [0 ... low-1]       -> confirmed 0s
       // 2. [low ... mid-1]     -> confirmed 1s
       // 3. [mid ... high]      -> unknown elements still to process
       // 4. [high+1 ... n-1]    -> confirmed 2s
       //
       // Edge cases handled:
       // - Empty array: high becomes -1, so while (mid <= high) is false.
       // - Single element: loop runs once if needed and leaves it correct.
       // - Already sorted array: pointers simply move through it.
       // - Reverse-like array such as [2,2,1,0,0]: swaps place values correctly.
       // - All same values: still O(n), no extra memory.
       //
       // Edge case missed by the problem assumption:
       // - If nums contains values other than 0, 1, or 2, this code treats them
       //   like 2 because they fall into the final else block.
       int low = 0, mid = 0, high = nums.size() - 1;
       // low:
       // Points to the position where the next 0 should be placed.
       // If removed, we would not know the boundary of the 0-region.
       //
       // mid:
       // Scans the unknown part of the array.
       // If removed, we would not know which element is currently being classified.
       //
       // high:
       // Points to the position where the next 2 should be placed.
       // If removed, we would not know the boundary of the 2-region.
       //
       // Example start for nums = [2,0,2,1,1,0]:
       // low = 0, mid = 0, high = 5
       // unknown region is the whole array: index 0 to 5.


       // Traverse the array until mid pointer crosses high
       while (mid <= high) {
           // Why mid <= high:
           // We continue only while there are unknown elements.
           // Once mid crosses high, every index belongs to one of the confirmed regions.
           //
           // If this loop condition is removed:
           // The algorithm would either not process the array or could run forever.
           //
           // Complexity note:
           // Each iteration either increases mid or decreases high.
           // So every element is processed at most a constant number of times -> O(n).
           if (nums[mid] == 0) {
               // Swap 0 to the front
               // What is happening:
               // nums[mid] is 0, so it belongs in the front 0-region.
               // We swap it with nums[low], the first position not yet confirmed as 0.
               //
               // Why increment both low and mid after the swap:
               // - The value placed at nums[low] is definitely 0.
               // - The value moved to nums[mid] came from the 1-region
               //   or from the same position, so it is already safe to skip.
               //
               // What would break if swap is removed:
               // 0s found later would stay in the middle/end instead of moving forward.
               //
               // What would break if low++ is removed:
               // The next 0 would overwrite/swap with the same boundary again,
               // and the confirmed 0-region would not grow.
               //
               // What would break if mid++ is removed:
               // The loop could keep checking the same already-processed 0.
               //
               // Dry run piece:
               // nums = [0,2,1], low = 0, mid = 0, high = 2
               // nums[mid] == 0 -> swap nums[0] with nums[0]
               // low = 1, mid = 1
               // Now [0] is confirmed as the 0-region.
               swap(nums[low], nums[mid]);
               low++;
               mid++;
           } else if (nums[mid] == 1) {
               // Leave 1 in the middle
               // What is happening:
               // nums[mid] is 1, and 1s belong between 0s and 2s.
               // Since all positions before mid are already organized,
               // we simply move mid forward.
               //
               // Why no swap is needed:
               // A 1 is already in the correct middle region relative to the
               // processed left side.
               //
               // What would break if mid++ is removed:
               // The loop would get stuck forever on the same 1.
               //
               // Dry run piece:
               // nums = [0,1,2], low = 1, mid = 1, high = 2
               // nums[mid] == 1 -> mid becomes 2
               // Now [low ... mid-1] contains confirmed 1s.
               mid++;
           } else {
               // Swap 2 to the end
               // What is happening:
               // nums[mid] is 2, so it belongs in the end 2-region.
               // We swap it with nums[high], the last unknown position.
               //
               // Why high-- after the swap:
               // The 2 moved to nums[high] is now confirmed in its final region.
               //
               // Why mid is NOT incremented here:
               // The element swapped from nums[high] into nums[mid] is unknown.
               // It could be 0, 1, or 2, so we must inspect nums[mid] again.
               //
               // What would break if mid++ is added here:
               // We might skip an unprocessed 0 that was swapped from the end.
               // Example: [1,2,0]
               // If 2 swaps with 0 and mid moves ahead, the 0 may remain after 1.
               //
               // What would break if high-- is removed:
               // The confirmed 2-region would not grow and repeated swaps could happen.
               //
               // Dry run piece:
               // nums = [2,0,1], low = 0, mid = 0, high = 2
               // nums[mid] == 2 -> swap nums[0] and nums[2] -> [1,0,2]
               // high = 1, mid stays 0 because nums[0] is newly swapped and unknown.
               swap(nums[mid], nums[high]);
               high--;
           }
       }
       // At this point mid > high.
       // That means there are no unknown elements left.
       // Final invariant:
       // - indexes before low are 0
       // - indexes from low to high boundary already passed are 1
       // - indexes after high are 2
       //
       // Full dry run for nums = [2,0,2,1,1,0]:
       // Start: low=0, mid=0, high=5, nums=[2,0,2,1,1,0]
       // 1. nums[mid]=2 -> swap mid/high: [0,0,2,1,1,2], high=4, mid=0
       // 2. nums[mid]=0 -> swap low/mid:  [0,0,2,1,1,2], low=1, mid=1
       // 3. nums[mid]=0 -> swap low/mid:  [0,0,2,1,1,2], low=2, mid=2
       // 4. nums[mid]=2 -> swap mid/high: [0,0,1,1,2,2], high=3, mid=2
       // 5. nums[mid]=1 -> mid=3
       // 6. nums[mid]=1 -> mid=4
       // Stop because mid=4 > high=3.
       //
       // Time Complexity: O(n)
       // Reason: mid and high move in one direction, so the array is scanned once.
       //
       // Space Complexity: O(1)
       // Reason: sorting happens in-place using only three integer pointers.
   }
};


int main() {
   // Test input used for demonstration.
   // It contains mixed 0s, 1s, and 2s so every branch of sortColors can run.
   // If this line is removed, there is no array to sort in this sample program.
   vector<int> nums = {2, 0, 2, 1, 1, 0};

   // Create an object of Solution so we can call the member function sortColors.
   // If this line is removed, sol.sortColors(nums) will not compile.
   Solution sol;

   // Sort the array in-place.
   // Important: sortColors does not return a new array; it modifies nums directly.
   // If this line is removed, the output remains the original unsorted array.
   sol.sortColors(nums);


   // Print the sorted array
   for (int num : nums) {
       // Prints each element after sorting.
       // For the sample input, the expected printed order is: 0 0 1 1 2 2
       cout << num << " ";
   }
   // Print a newline after all values for cleaner output.
   cout << endl;


   // return 0 tells the operating system that the program ended successfully.
   // If omitted in modern C++, main still returns 0 implicitly, but writing it
   // keeps the exit status explicit for beginners.
   return 0;
}


// ### 1. 🧠 Problem Understanding
//
// - This is an in-place array partitioning / sorting problem.
// - The array contains only three possible values: 0, 1, and 2.
// - The required order is fixed: all 0s first, then all 1s, then all 2s.
// - The key clue is: "without using the library's sort function."
// - Another key clue is that there are only 3 distinct categories, so we can
//   classify elements instead of doing general comparison-based sorting.
//
//
// ### 2. 🔍 Pattern Recognition
//
// - Pattern used: Dutch National Flag / three-pointer partitioning.
// - Recognize it when:
//   - The array has a small fixed set of categories.
//   - You need in-place rearrangement.
//   - You need all elements of one type first, another type second, and another last.
// - This is similar to partitioning around a pivot in quicksort, but with
//   three groups instead of two.
//
//
// ### 3. ⚡ Approach Breakdown (Interview Style)
//
// - Brute force idea:
//   Use normal sorting.
//   Time: O(n log n), Space: depends on sort implementation.
//   Problem: The prompt disallows library sort and we can do better.
//
// - Better approach:
//   Count how many 0s, 1s, and 2s exist, then overwrite the array.
//   Time: O(n), Space: O(1).
//   Good, but it needs two passes over the array.
//
// - Optimal approach:
//   Dutch National Flag algorithm.
//   Time: O(n), Space: O(1), one pass.
//   Chosen because it sorts in-place while classifying each element directly.
//
//
// ### 4. 🧩 Intuition Building
//
// - Think of the array as having three buckets inside itself.
// - low grows the 0-bucket from the left.
// - high grows the 2-bucket from the right.
// - mid scans the unknown region and decides where each element belongs.
// - The trick is: when a 2 is swapped with nums[high], do not move mid,
//   because the incoming element has not been checked yet.
//
//
// ### 5. 🔁 How to Recall Later
//
// - Signal 1: Array contains only 0, 1, and 2.
// - Signal 2: Need sorted/grouped order in-place.
// - Signal 3: Asked for O(n) without using sort.
// - Memory trick: "0 goes low, 2 goes high, 1 lets mid fly."
//
//
// ### 6. ⚠️ Common Mistakes
//
// - Incrementing mid after swapping a 2 with high.
//   This can skip an unknown value brought from the right side.
// - Using while (mid < high) instead of while (mid <= high).
//   This may leave the last unknown element unprocessed.
// - Forgetting to increment low after placing a 0.
// - Thinking the final else handles only 2 even if invalid values exist.
//   The problem guarantees only 0, 1, and 2, so this is acceptable here.
//
//
// ### 7. 📊 Complexity Analysis
//
// - Time Complexity: O(n)
//   Each step either moves mid forward or high backward.
//   No element causes more than constant work.
//
// - Space Complexity: O(1)
//   The algorithm uses only low, mid, and high.
//   No extra array, map, or sorting structure is created.
//
//
// ### 8. 🔄 Alternative Approaches
//
// - Counting approach:
//   First count the number of 0s, 1s, and 2s.
//   Then rewrite the array with that many 0s, followed by 1s, followed by 2s.
//   This is simple and still O(n), but it usually needs two passes.
//
// - General sorting:
//   Sort the array using a sorting algorithm.
//   This works, but it is less optimal because comparison sorting is usually
//   O(n log n), and the problem specifically asks not to use library sort.
//
// - Stable partitioning:
//   Partition 0s first and then partition 1s from 2s.
//   This is more complicated than needed because the problem does not require
//   stability, only correct grouping.


