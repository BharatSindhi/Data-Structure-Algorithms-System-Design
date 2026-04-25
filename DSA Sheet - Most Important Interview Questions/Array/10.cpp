// Problem Statement :



// Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

// Notice that the solution set must not contain duplicate triplets.



// The Chef’s Secret: Crafting the Perfect Balanced Recipe

// As a head chef, you're given a challenge to find three ingredients whose combined taste equals zero. To solve this efficiently, your sous chef Alex suggests sorting the ingredients first. Then, using a structured approach, you pick each ingredient as a base and apply the two-pointer technique to find a balanced trio. To avoid duplicate recipes, you skip repeated ingredients. After testing all combinations, you compile a list of unique dishes.





// Example 1:
// Input: nums = [-1, 0, 1, 2, -1, -4]
// Output: [[-1,-1,2],[-1,0,1]]

// Explanation:
// nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
// nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
// nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
// The distinct triplets are [-1,0,1] and [-1,-1,2].
// Notice that the order of the output and the order of the triplets do not matter.


// Example 2:
// Input: nums = [0, 1, 1]
// Output: []

// Explanation: The only possible triplet does not sum up to 0.


// Example 3:
// Input: nums = [0, 0, 0]
// Output: [[0,0,0]]

// Explanation: The only possible triplet sums up to 0.

// DSA
// DSA Sheet

// Topic Difficulty
// Medium
// Adobe
// Amazon
// Microsoft
// +4
// Asked by Companies
// 3Sum
// Practice Here
// Go to LeetCode
// Topics
// Click to see
// Video Thumbnail
// Problem Statement :



// Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

// Notice that the solution set must not contain duplicate triplets.



// The Chef’s Secret: Crafting the Perfect Balanced Recipe

// As a head chef, you're given a challenge to find three ingredients whose combined taste equals zero. To solve this efficiently, your sous chef Alex suggests sorting the ingredients first. Then, using a structured approach, you pick each ingredient as a base and apply the two-pointer technique to find a balanced trio. To avoid duplicate recipes, you skip repeated ingredients. After testing all combinations, you compile a list of unique dishes.





// Example 1:
// Input: nums = [-1, 0, 1, 2, -1, -4]
// Output: [[-1,-1,2],[-1,0,1]]

// Explanation:
// nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
// nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
// nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
// The distinct triplets are [-1,0,1] and [-1,-1,2].
// Notice that the order of the output and the order of the triplets do not matter.


// Example 2:
// Input: nums = [0, 1, 1]
// Output: []

// Explanation: The only possible triplet does not sum up to 0.


// Example 3:
// Input: nums = [0, 0, 0]
// Output: [[0,0,0]]

// Explanation: The only possible triplet sums up to 0.
// Method Image 25
// Method Image 26
// Method

// Time Complexity

// Space Complexity

// Naive

// O(n^3 (log(k))

// O(k)

// Better

// O(n²log(k))

// O(k)

// Best

// O(n^2)

// O(1)

// Method

// Naive

// Better

// Best
// Approach
// Using Two Pointers :



// By Sorting the array, we fix one number. Then, we use two pointers to find two other numbers that, together, sum to zero. Sorting allows us to skip duplicates efficiently and use the two-pointer method to reduce time complexity.



// 1. Sort the array to simplify duplicate handling and enable the two-pointer technique.

// 2. Loop through the array from index 0 to n - 3 (because for triplets, we need 3 numbers and after n-3, there won’t be enough numbers.) Treat each nums[i] as the first element of the triplet.

// 3. Skip duplicates for nums[i] to avoid repeating the same triplet structure.

// 4. Use two pointers (left = i + 1, right = n - 1) to find two numbers such that nums[i] + nums[left] + nums[right] == 0.

// 5. Check the sum:

// If it matches, store the triplet and move both pointers while skipping duplicates.
// If the sum is too small, increment left.
// If it's too large, decrement right.
// 6. Collect all valid triplets directly into the result list—no need for a set.

// 7. Return the result after checking all valid combinations.

// Time Complexity	Space Complexity
// O(n^2)	O(1)



#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;


class Solution {
public:
   vector<vector<int>> threeSum(vector<int>& nums) {
       vector<vector<int>> result;
       int n = nums.size();
       sort(nums.begin(), nums.end()); // Step 1: Sort the array
       for (int i = 0; i < n - 2; i++) {
           // Step 2: Skip duplicate values for the current number
           if (i > 0 && nums[i] == nums[i - 1]) continue;


           int target = -nums[i]; // We need two numbers that sum to -nums[i]
           int left = i + 1, right = n - 1;


           // Step 3: Two-pointer approach
           while (left < right) {
               int sum = nums[left] + nums[right];


               if (sum == target) {
                   // Found a valid triplet
                   result.push_back({nums[i], nums[left], nums[right]});


                   // Step 4: Skip duplicates for left and right pointers
                   while (left < right && nums[left] == nums[left + 1]) left++;
                   while (left < right && nums[right] == nums[right - 1]) right--;


                   left++;
                   right--;
               } else if (sum < target) {
                   left++; // Need a larger sum
               } else {
                   right--; // Need a smaller sum
               }
           }
       }


       return result;
   }
};


int main() {
   Solution sol;
   vector<int> nums = {-1, 0, 1, 2, -1, -4};
   vector<vector<int>> res = sol.threeSum(nums);


   for (auto triplet : res) {
       for (int num : triplet) {
           cout << num << " ";
       }
       cout << endl;
   }


   return 0;
}
