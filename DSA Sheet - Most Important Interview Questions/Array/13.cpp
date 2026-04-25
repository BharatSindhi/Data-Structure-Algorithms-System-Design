// Problem Statement :



// Given an array of integers nums, find the next permutation of nums.

// The replacement must be in place and use only constant extra memory.



// A permutation of an array of integers is an arrangement of its members into a sequence or linear order.

// For example, for arr = [1, 2, 3], the following are all the permutations of arr: [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1].



// The next permutation of an array of integers is the next lexicographically greater permutation of its integers. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such an arrangement is not possible, the array must be rearranged in the lowest possible order (i.e., sorted in ascending order).



// For example, the next permutation of arr = [1,2,3] is [1,3,2].
// Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
// While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographically larger rearrangement.


// Example 1:
// Input: nums = [1, 2, 3]
// Output: [1, 3, 2]


// Example 2:
// Input: nums = [3, 2, 1]
// Output: [1, 2, 3]


// Example 3:
// Input: nums = [1, 1, 5]
// Output: [1, 5, 1]


// DSA
// DSA Sheet

// Topic Difficulty
// Medium
// Uber
// Goldman Sachs
// Adobe
// Asked by Companies
// Next Permutation
// Practice Here
// Go to LeetCode
// Topics
// Click to see
// Video Thumbnail
// Problem Statement :



// Given an array of integers nums, find the next permutation of nums.

// The replacement must be in place and use only constant extra memory.



// A permutation of an array of integers is an arrangement of its members into a sequence or linear order.

// For example, for arr = [1, 2, 3], the following are all the permutations of arr: [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1].



// The next permutation of an array of integers is the next lexicographically greater permutation of its integers. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such an arrangement is not possible, the array must be rearranged in the lowest possible order (i.e., sorted in ascending order).



// For example, the next permutation of arr = [1,2,3] is [1,3,2].
// Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
// While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographically larger rearrangement.


// Example 1:
// Input: nums = [1, 2, 3]
// Output: [1, 3, 2]


// Example 2:
// Input: nums = [3, 2, 1]
// Output: [1, 2, 3]


// Example 3:
// Input: nums = [1, 1, 5]
// Output: [1, 5, 1]
// Method Image 33
// Method Image 34
// Method Image 35
// Method Image 36
// Method

// Time Complexity

// Space Complexity

// Naive

// O(n*n!)

// O(n!) + O(n)

// Best

// O(n)

// O(1)

// Method

// Naive

// Best
// Approach
// Efficient In-Place Next Permutation Algorithm :



// The idea is to find the first decreasing element from the right, swap it with the smallest larger element on its right, and then reverse the remaining right part to get the next lexicographical permutation efficiently. This ensures minimal change while maintaining order.



// 1.    Locate the Rightmost Decreasing Element:

// Go from right to left through the array.
// Determine which index i is the first one where nums[i] < nums[i + 1].
// This indicates the point at which the sequence needs to be changed because the order breaks.
// 2.    Locate the Next Bigger Component to Exchange:

// Navigate back towards i from the rightmost element if such an index i is found.
// Identify the smallest number greater than nums[i] and swap them.
// This ensures that we get the next larger lexicographical order.
// 3.    Reverse the Right Part (Suffix) After the Swap:

// Since the right part of nums[i] was in descending order, swapping alone won’t give the next permutation.
// Reverse the portion of the array starting from i + 1 to the end.
// This step ensures that the sequence remains the next smallest possible lexicographical order.
// Time Complexity	Space Complexity
// O(n) 	O(1)

#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
private:
   void swap(vector<int>& nums, int i, int j) {
       int temp = nums[i];
       nums[i] = nums[j];
       nums[j] = temp;
   }
   void reverse(vector<int>& nums, int start, int end) {
       while (start < end) {
           swap(nums, start, end);
           start++;
           end--;
       }
   }


public:
   void nextPermutation(vector<int>& nums) {
       int n = nums.size();
       int index = -1;


       // Step 1: Find the first decreasing element from the right
       for (int i = n - 2; i >= 0; i--) {
           if (nums[i] < nums[i + 1]) {
               index = i;
               break;
           }
       }
       // Step 2: Find the next greater element to swap with nums[index]
       if (index != -1) { // If such an element is found
           for (int i = n - 1; i > index; i--) {
               if (nums[i] > nums[index]) {
                   swap(nums, i, index);
                   break;
               }
           }
       }
       // Step 3: Reverse the suffix (right part of the array)
       reverse(nums, index + 1, n - 1);
   }
};





int main() {
    
    return 0;
}