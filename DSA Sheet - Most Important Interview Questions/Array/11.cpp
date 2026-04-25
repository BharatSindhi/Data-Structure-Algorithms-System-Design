// Problem Statement :



// Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:

// 0 <= a, b, c, d < n
// a, b ,c, and d are distinct.
// nums[a] + nums[b] + nums[c] + nums[d] == target


// You may return the answer in any order.



// Fair Expense Splitting: The Four-Sum Road Trip Challenge

// The Road Trip Expense Challenge involves selecting exactly four people whose contributions sum up to the total expense. By sorting the list, we efficiently find valid groups using a two-pointer approach. We iterate through pairs while avoiding duplicates, adjusting pointers to balance the sum. The valid combinations ensure fair cost-sharing. This method applies to expense splitting, financial planning, data analysis, and gaming strategies.



// Example 1:
// Input: nums = [1, 0, -1, 0, -2, 2], target = 0
// Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]


// Example 2:
// Input: nums = [2, 2, 2, 2, 2], target = 8
// Output: [[2, 2, 2, 2]]


// Approach
// Using 2 Loops and Two Pointers :



// First, we fix the first two elements using two nested loops. Then, the problem reduces to a two-pointer search for the remaining sum of the other two elements.  



// 1.    Sort the array to handle duplicates more easily and to enable efficient searching.

// 2.    Use two nested loops:

// Traverse the array i from 0 to n - 3
// Traverse the array j from i + 1 to n - 2
//              These loops fix the first two numbers in the quadruplet.

// 3.    Calculate the remainingTarget = target - nums[i] - nums[j].

// 4.    Apply the two-pointer technique to find the remaining two numbers:

// Initialize left = j + 1, right = n - 1.
// While left < right:
// If nums[left] + nums[right] < remainingTarget, left++ .
// If nums[left] + nums[right] > remainingTarget, right-- .
// If nums[left] + nums[right] == remainingTarget, store the quadruplet [nums[i], nums[j], nums[left], nums[right]] and move both pointers while skipping duplicates.
// 5.    Skip duplicate values for i, j, left, and right to ensure each quadruplet is unique.

// 6.    Return the list of unique quadruplets.

// Time Complexity	Space Complexity
// O(n^3)	O(1)




#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;


class Solution {
public:
   vector<vector<int>> fourSum(vector<int>& nums, int target) {
       int n = nums.size();
       vector<vector<int>> result;
       sort(nums.begin(), nums.end()); // Sort the array to apply two-pointer efficiently


       // Loop for the first number
       for (int first = 0; first < n - 3; first++) {
           if (first > 0 && nums[first] == nums[first - 1]) continue; // Skip duplicates


           // Loop for the second number
           for (int second = first + 1; second < n - 2; second++) {
               if (second > first + 1 && nums[second] == nums[second - 1]) continue; // Skip duplicates


               long long remainingTarget = (long long)target - nums[first] - nums[second];
               int left = second + 1, right = n - 1;


               // Two-pointer for the remaining two numbers
               while (left < right) {
                   int sum = nums[left] + nums[right];


                   if (sum < remainingTarget) {
                       left++; // Need a bigger sum
                   } else if (sum > remainingTarget) {
                       right--; // Need a smaller sum
                   } else {
                       // Found a valid quadruplet
                       result.push_back({nums[first], nums[second], nums[left], nums[right]});


                       // Skip duplicates for left and right
                       int prevLeft = nums[left], prevRight = nums[right];
                       while (left < right && nums[left] == prevLeft) left++;
                       while (left < right && nums[right] == prevRight) right--;
                   }
               }
           }
       }
       return result;
   }
};


// Main function
int main() {
   Solution sol;
   vector<int> nums = {1, 0, -1, 0, -2, 2};
   int target = 0;


   vector<vector<int>> result = sol.fourSum(nums, target);


   cout << "Quadruplets summing to " << target << ":";
   for (auto& quad : result) {
       for (int num : quad)
           cout << num << " ";
       cout << endl;
   }


   return 0;
}
