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
       // Dutch National Flag algorithm
       int low = 0, mid = 0, high = nums.size() - 1;


       // Traverse the array until mid pointer crosses high
       while (mid <= high) {
           if (nums[mid] == 0) {
               // Swap 0 to the front
               swap(nums[low], nums[mid]);
               low++;
               mid++;
           } else if (nums[mid] == 1) {
               // Leave 1 in the middle
               mid++;
           } else {
               // Swap 2 to the end
               swap(nums[mid], nums[high]);
               high--;
           }
       }
   }
};


int main() {
   vector<int> nums = {2, 0, 2, 1, 1, 0};
   Solution sol;
   sol.sortColors(nums);


   // Print the sorted array
   for (int num : nums) {
       cout << num << " ";
   }
   cout << endl;


   return 0;
}


