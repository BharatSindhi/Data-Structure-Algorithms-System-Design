// Problem Statement:



// Given an integer array nums, find the subarray with the largest sum and return its sum.



// Example : Leetcode Streak

// Rahul loves coding and wants to solve problems on LeetCode every day to improve his skills. Some days he solves many problems (+points), while on tough days, he struggles or skips (-points). To find his best streak, he uses Kadane’s algorithm, which helps track the highest consecutive score. Instead of checking all days manually, the algorithm smartly continues a streak or starts fresh when needed.



// Example 1:
// Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
// Output: 6
// Explanation: The subarray [4,-1,2,1] has the largest sum of 6.


// Example 2:
// Input: nums = [1]
// Output: 1
// Explanation: The subarray [1] has the largest sum 1.


// Example 3:
// Input: nums = [5, 4, 1, 7, 8]
// Output: 25
// Explanation: The subarray [5, 4, 1, 7, 8] has the largest sum of 25.


// Approach
// Using Kadane’s Algorithm :



// 1.    Kadane's Algorithm has two choices at every element :

// Add the current element to continue the current subarray.
// Start the new subarray, If the current element gives a higher value than the previous subarray sum.


// 2. It tracks the sum of the current subarray (currSum) and the highest sum found so far (maxSum).

// 3. Initialize currSum and maxSum to nums[0].

// 4. Iterate through the array, updating currSum to the maximum of:

// Starting a new subarray with nums[i], or
// Adding nums[i] to the current subarray.
// 5. Update maxSum with the larger of maxSum and currSum.

// 6. Return maxSum as the result.





// Dry Run 

// Final Answer:

// Maximum Subarray Sum = 6

// Time Complexity	Space Complexity
// O(n) 	O(1)


#include <iostream>
#include<vector>
using namespace std;
class Solution {
public:
   // Function to find the maximum subarray sum
   int maxSubArray(vector<int>& nums) {
       int currSum = nums[0];   // Initialize the current subarray sum with the first element
       int maxSum = nums[0];    // Initialize the maximum subarray sum with the first element
      
       // Iterate through the array starting from the second element
       for (int i = 1; i < nums.size(); i++) {
           currSum = max(currSum + nums[i], nums[i]);  // Update current subarray sum: either extend or start fresh
           maxSum = max(maxSum, currSum);  // Update maxSum with the larger value between the current maxSum and currSum
       }
      
       return maxSum;  // Return the maximum subarray sum found
   }
};


int main() {
   // Test case: Define an array of integers
   vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  
   Solution solution;  // Create an instance of the Solution class
   int result = solution.maxSubArray(nums);  // Call the maxSubArray function to find the max sum
  
   // Output the result
   cout << "The maximum subarray sum is: " << result << endl;
  
   return 0;  // Return 0 to indicate successful execution
}


