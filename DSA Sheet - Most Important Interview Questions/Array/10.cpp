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
// Includes input/output support.
// What it does: Allows the program to use cout for printing triplets in main().
// Why needed: Without this header, cout may not be recognized by the compiler.
// If removed: The printing part in main() can fail to compile.
// Complexity impact: None on algorithmic time/space complexity.
#include<vector>
// Includes the vector container.
// What it does: Allows dynamic arrays like vector<int> and vector<vector<int>>.
// Why needed: The input array and answer list are both stored using vectors.
// If removed: vector would be undefined, so the solution cannot compile.
// Complexity impact: result may store up to O(k) triplets, where k is the number of valid answers.
#include<algorithm>
// Includes common algorithms such as sort().
// What it does: Gives access to std::sort, which arranges nums in nondecreasing order.
// Why needed: Sorting is the key step that makes duplicate skipping and two pointers possible.
// If removed: sort(nums.begin(), nums.end()) would fail to compile.
// Complexity impact: sort costs O(n log n), but the later O(n^2) scan dominates overall.
using namespace std;
// Allows writing vector, cout, sort directly instead of std::vector, std::cout, std::sort.
// If removed: The logic still works, but every standard-library name must be prefixed with std::.


class Solution {
public:
   vector<vector<int>> threeSum(vector<int>& nums) {
       // Function goal:
       // Return every unique triplet [a, b, c] from nums such that a + b + c == 0.
       //
       // Important interview thought:
       // Instead of checking all i, j, k combinations in O(n^3), we sort the array,
       // fix one value nums[i], and solve the remaining part as a 2Sum problem
       // using two pointers in O(n).
       //
       // Small dry run input:
       // nums = [-1, 0, 1, 2, -1, -4]
       // After sorting: [-4, -1, -1, 0, 1, 2]
       // i = 0 -> nums[i] = -4, target = 4, left/right try pairs but no pair sums to 4.
       // i = 1 -> nums[i] = -1, target = 1, pairs (-1,2) and (0,1) give valid triplets.
       // i = 2 -> nums[i] = -1 is skipped because it duplicates nums[1].
       // Final answer: [-1,-1,2] and [-1,0,1].
       vector<vector<int>> result;
       // Stores all unique valid triplets.
       // Why needed: We must return all answers, not just count them.
       // If removed: There is nowhere to collect triplets before returning.
       // Edge case: If no triplet exists, result remains empty and returns [].
       // Space: O(k), where k is the number of unique triplets stored.
       int n = nums.size();
       // Saves array size so we do not repeatedly call nums.size().
       // Why needed: The loops and pointer bounds depend on n.
       // If removed: We could still call nums.size() directly, but this keeps the code clearer.
       // Edge cases handled:
       // n < 3 -> the for loop condition i < n - 2 fails, so result stays empty.
       sort(nums.begin(), nums.end()); // Step 1: Sort the array
       // What it does: Rearranges nums in ascending order.
       // Why necessary:
       // 1. Duplicates become adjacent, so they can be skipped easily.
       // 2. Two-pointer movement becomes meaningful:
       //    - moving left rightward increases the pair sum,
       //    - moving right leftward decreases the pair sum.
       // If removed:
       // The duplicate-skipping checks would be unreliable, and the two-pointer logic
       // would no longer know which direction makes the sum larger or smaller.
       // Dry run:
       // [-1, 0, 1, 2, -1, -4] becomes [-4, -1, -1, 0, 1, 2].
       // Time: O(n log n). Extra space depends on sort implementation, usually O(log n) recursion.
       for (int i = 0; i < n - 2; i++) {
           // Fix nums[i] as the first number of the triplet.
           // Why i < n - 2:
           // A triplet needs two more elements after i, so i can only go up to n - 3.
           // If this bound is wrong:
           // We may either miss valid triplets or access invalid pointer ranges.
           // Dry run:
           // sorted nums = [-4, -1, -1, 0, 1, 2]
           // i visits 0, 1, 2, 3. For each i, left and right search the suffix after i.
           // Step 2: Skip duplicate values for the current number
           if (i > 0 && nums[i] == nums[i - 1]) continue;
           // What it does: Avoids using the same fixed value more than once.
           // Why necessary:
           // If nums[i] is the same as nums[i - 1], then all triplets starting with
           // this value were already considered in the previous iteration.
           // If removed:
           // Duplicate triplets can appear in result.
           // Example:
           // sorted [-4, -1, -1, 0, 1, 2]
           // i = 1 and i = 2 both have nums[i] = -1.
           // Without this continue, [-1, 0, 1] could be found more than once.
           // Edge case handled: arrays with many repeated values, like [0,0,0,0].


           int target = -nums[i]; // We need two numbers that sum to -nums[i]
           // Converts 3Sum into 2Sum:
           // nums[i] + nums[left] + nums[right] == 0
           // becomes nums[left] + nums[right] == -nums[i].
           // Why needed: This lets the inner loop focus only on finding a pair.
           // If removed: We would have to repeatedly compare the full three-number sum.
           // Dry run:
           // If nums[i] = -1, target = 1.
           // Now we search for two numbers whose sum is 1, such as -1 + 2 or 0 + 1.
           int left = i + 1, right = n - 1;
           // left starts immediately after i, right starts at the last index.
           // Why needed:
           // 1. Ensures i, left, and right are different indices.
           // 2. Searches only elements after i, preventing reused combinations in different orders.
           // If left started at 0, nums[i] could be reused or triplets could repeat in different order.
           // If right were not n - 1, we might miss larger values needed to balance the sum.
           // Dry run:
           // For i = 1 in [-4,-1,-1,0,1,2], left = 2, right = 5.


           // Step 3: Two-pointer approach
           while (left < right) {
               // Continue while there are two different elements available.
               // Why left < right:
               // A valid triplet requires distinct indices, so left and right cannot meet or cross.
               // If changed to left <= right:
               // The same element could be used twice when left == right.
               // Example:
               // nums[i] = -2 and nums[left] = 1 at the same index would incorrectly form [-2,1,1].
               int sum = nums[left] + nums[right];
               // Current pair sum for the two unfixed elements.
               // Why needed: Compare this pair sum against target.
               // If removed: The algorithm cannot decide whether it found a triplet or which pointer to move.
               // Dry run:
               // i = 1, nums[i] = -1, target = 1
               // left = 2 -> nums[left] = -1, right = 5 -> nums[right] = 2
               // sum = 1, so [-1,-1,2] is valid.


               if (sum == target) {
                   // Pair matches the needed target, so nums[i] + nums[left] + nums[right] == 0.
                   // This is the success condition for one unique triplet.
                   // Found a valid triplet
                   result.push_back({nums[i], nums[left], nums[right]});
                   // Adds the triplet to the answer.
                   // Why safe to add directly:
                   // Because sorting plus duplicate skipping prevents repeated triplets.
                   // If removed: Valid answers would be discovered but never returned.
                   // Dry run:
                   // nums[i] = -1, nums[left] = -1, nums[right] = 2 -> store [-1,-1,2].
                   // Edge case:
                   // For [0,0,0], stores [0,0,0] once.


                   // Step 4: Skip duplicates for left and right pointers
                   while (left < right && nums[left] == nums[left + 1]) left++;
                   // Skips repeated values on the left side after a valid triplet is found.
                   // Why necessary:
                   // If the next left value is identical, it would create the same triplet again.
                   // If removed:
                   // Inputs like [-2,0,0,2,2] may produce duplicate [-2,0,2].
                   // Dry run:
                   // sorted [-2,0,0,2,2]
                   // after finding [-2,0,2], left points at first 0.
                   // This loop moves left past duplicate 0 values before the final left++.
                   // Edge case handled: multiple duplicate middle values.
                   while (left < right && nums[right] == nums[right - 1]) right--;
                   // Skips repeated values on the right side after a valid triplet is found.
                   // Why necessary:
                   // Reusing an equal right value would create the same value-triplet.
                   // If removed:
                   // Duplicate answers can appear when the array has repeated large values.
                   // Dry run:
                   // sorted [-2,0,0,2,2]
                   // after finding [-2,0,2], right points at last 2.
                   // This loop moves right leftward across duplicate 2 values.
                   // Edge case handled: repeated positive values at the end.


                   left++;
                   // Moves left to the next new candidate after recording a valid triplet.
                   // Why needed:
                   // The current pair has already been used, so we must search for another pair.
                   // If removed:
                   // The loop could get stuck on the same left/right values forever.
                   right--;
                   // Moves right to the next new candidate after recording a valid triplet.
                   // Why needed:
                   // Both pointers must move after a match because keeping either one can repeat work.
                   // If removed:
                   // The loop may repeat the same pair or fail to progress correctly.
               } else if (sum < target) {
                   // Current pair sum is too small.
                   // Because the array is sorted, increasing left is the only way to try a larger pair sum.
                   left++; // Need a larger sum
                   // If removed or if right-- were used instead:
                   // The sum would stay too small or become even smaller, causing missed answers.
                   // Dry run:
                   // target = 4, pair (-1,2) gives sum = 1.
                   // Move left rightward to try a bigger left value.
               } else {
                   // Current pair sum is too large.
                   // Because the array is sorted, decreasing right is the direct way to try a smaller pair sum.
                   right--; // Need a smaller sum
                   // If removed or if left++ were used instead:
                   // The sum may become even larger, and valid answers can be skipped.
                   // Dry run:
                   // target = 1, pair (1,2) gives sum = 3.
                   // Move right leftward to reduce the sum.
               }
           }
       }


       return result;
       // Returns all unique triplets found.
       // Edge cases:
       // 1. nums has fewer than 3 elements -> returns empty vector.
       // 2. all positives or all negatives -> no zero-sum triplet, returns empty vector.
       // 3. many duplicates -> duplicate skipping keeps answers unique.
       //
       // Time complexity:
       // Sorting is O(n log n), outer loop is O(n), inner two-pointer scan is O(n) per fixed i.
       // Total: O(n^2), because O(n^2) dominates O(n log n).
       //
       // Space complexity:
       // O(k) for the returned triplets, where k is the number of valid unique triplets.
       // Ignoring output storage, the algorithm uses O(1) extra variables
       // plus possible O(log n) internal recursion space from sort.
   }
};


int main() {
   // Driver code for testing the threeSum function with a sample input.
   // In online judges like LeetCode, main() is usually not required;
   // they call threeSum() directly.
   Solution sol;
   // Creates an object of Solution so we can call sol.threeSum(nums).
   vector<int> nums = {-1, 0, 1, 2, -1, -4};
   // Sample input.
   // Expected unique triplets after sorting and processing:
   // [-1, -1, 2]
   // [-1, 0, 1]
   vector<vector<int>> res = sol.threeSum(nums);
   // Calls the algorithm and stores the returned list of triplets.


   for (auto triplet : res) {
       // Iterates over each triplet in the answer.
       // If res is empty, this loop simply does not run.
       for (int num : triplet) {
           // Prints each number inside the current triplet.
           cout << num << " ";
       }
       cout << endl;
       // Moves to the next line after printing one triplet.
   }


   return 0;
   // Indicates successful program completion.
}

// ---------------------------------------------------------------------------
// 1. Problem Understanding
// ---------------------------------------------------------------------------
// Type of problem:
// This is a "find unique combinations that satisfy a sum condition" problem.
// More specifically, it is the classic 3Sum problem.
//
// Key constraints/clues:
// 1. Need triplets, not pairs -> likely fix one element and solve 2Sum on the rest.
// 2. Sum must be exactly 0 -> compare against the negative of the fixed value.
// 3. Solution set must not contain duplicates -> sorting is a strong clue.
// 4. Medium difficulty and array-based -> often expects O(n^2), not O(n^3).
//
// Edge cases to think about:
// 1. nums.size() < 3 -> impossible to form a triplet.
// 2. all numbers are positive -> no sum can be 0.
// 3. all numbers are negative -> no sum can be 0.
// 4. many duplicates like [0,0,0,0] -> answer should be only [[0,0,0]].
// 5. no valid triplet like [0,1,1] -> return empty result.

// ---------------------------------------------------------------------------
// 2. Pattern Recognition
// ---------------------------------------------------------------------------
// DSA pattern used:
// Sorting + Two Pointers.
//
// How to recognize this pattern in future:
// 1. The problem asks for pairs/triplets with a target sum.
// 2. The answer must avoid duplicates.
// 3. Order of elements in the answer does not matter.
// 4. You can sort the array without losing the meaning of the problem.
//
// Mental signal:
// "If I sort, can I move one pointer to increase the sum and another pointer to decrease it?"

// ---------------------------------------------------------------------------
// 3. Approach Breakdown (Interview Style)
// ---------------------------------------------------------------------------
// Brute force idea:
// Try every i, j, k combination using three nested loops.
// Check whether nums[i] + nums[j] + nums[k] == 0.
// To avoid duplicates, store sorted triplets in a set.
// Time: O(n^3 log k) or worse depending on set operations.
// Space: O(k) for unique answers.
//
// Better approach:
// Fix one number nums[i], then use a hash set to find whether another number
// exists to complete the triplet.
// This can reduce searching to around O(n^2), but duplicate handling becomes
// more delicate and usually needs a set of triplets.
// Space: O(n) or O(k), depending on implementation.
//
// Optimal approach:
// Sort the array.
// Fix nums[i].
// Use left and right pointers to find pairs that sum to -nums[i].
// Skip duplicates while scanning.
// Time: O(n^2).
// Extra space: O(1), ignoring output.
//
// Why this one is chosen:
// It gives the expected O(n^2) time and handles duplicates cleanly without
// needing a set for final answers.

// ---------------------------------------------------------------------------
// 4. Intuition Building
// ---------------------------------------------------------------------------
// Core idea:
// Pick one number and ask:
// "What two numbers are needed to cancel this number and make the total zero?"
//
// Example:
// If the fixed number is -1, the other two numbers must sum to 1.
// In a sorted array, if the two-pointer sum is too small, move left rightward.
// If the sum is too large, move right leftward.
//
// Trick/insight:
// Sorting turns random movement into controlled movement.
// left++ means "try a bigger value."
// right-- means "try a smaller value."
// This is why we can avoid checking every pair manually.

// ---------------------------------------------------------------------------
// 5. How to Recall Later
// ---------------------------------------------------------------------------
// Key signals:
// 1. "Find all unique triplets."
// 2. "Sum equals target/zero."
// 3. "No duplicate triplets."
//
// One-line memory trick:
// Sort, fix one number, then two-pointer the remaining target.

// ---------------------------------------------------------------------------
// 6. Common Mistakes
// ---------------------------------------------------------------------------
// 1. Forgetting to sort before using two pointers.
// 2. Not skipping duplicate fixed values nums[i].
// 3. Skipping duplicates before storing the valid triplet instead of after.
// 4. Moving only one pointer after finding a valid triplet, which can repeat work.
// 5. Using left <= right and accidentally reusing the same element.
// 6. Returning duplicate triplets because duplicate values were not handled.
// 7. Thinking O(n^3) is acceptable for typical 3Sum constraints.

// ---------------------------------------------------------------------------
// 7. Complexity Analysis
// ---------------------------------------------------------------------------
// Time complexity:
// sort(nums) costs O(n log n).
// The outer loop runs O(n) times.
// For each fixed i, left and right together scan the remaining array in O(n).
// Total time = O(n log n) + O(n^2) = O(n^2).
//
// Space complexity:
// The result itself takes O(k), where k is the number of valid triplets.
// Apart from the output, the algorithm uses only a few variables:
// n, i, target, left, right, sum.
// So auxiliary space is O(1), ignoring sort's internal implementation.

// ---------------------------------------------------------------------------
// 8. Alternative Approaches
// ---------------------------------------------------------------------------
// 1. Three nested loops:
// Simple but slow. Good for understanding the problem, bad for interviews
// unless constraints are tiny.
//
// 2. Hashing after fixing one number:
// Fix nums[i], then solve 2Sum using a hash set for the remaining elements.
// This can be O(n^2), but avoiding duplicate triplets usually requires extra
// care or a set of vectors.
//
// 3. General kSum recursion:
// Sort the array and recursively reduce kSum to 2Sum.
// Useful when the problem asks for 4Sum, kSum, or multiple target sizes.
