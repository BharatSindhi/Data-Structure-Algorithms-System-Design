// Problem Statement :



// Given a non-empty array of integer nums, every element appears twice except for one. Find that single one.You must implement a solution with a linear runtime complexity and use only constant extra space.



// Example : The Mystery of the Extra Guest

// Rahul’s birthday party had a special rule—every friend came with their brother, both having the same name. As guests arrived, Rahul wrote down each name and crossed it off when the brother arrived. In the end, one name remained—the guest without a brother! For example, in [4,1,2,1,2], after canceling pairs, 4 was alone. This simple trick helped Rahul find the extra guest easily!



// Example 1:
// Input: nums = [2, 2, 1]
// Output: 1


// Example 2:
// Input: nums = [4,1,2,1,2]
// Output: 4


// Example 3:
// Input: nums = [1]
// Output: 1


// Approach
// Using Xor Operator :



// By XORing all the elements, duplicate elements cancel out each other, and the remaining element is our unique element.



// 1. Understand XOR Basics

// a ^ a = 0 (same numbers cancel out)
// 0 ^ a = a (XOR with zero keeps the number unchanged.)
// 2. Initialize XOR Variable

// Start with xorResult = 0 to hold the running XOR.
// 3. Iterate and XOR All Elements

// Traverse the array and do xor for all the elements with xorResult.
// Duplicates cancel out, and only the unique element is left.
// 4. Return the Result

// After the loop, xorResult holds the non-repeating number.

#include <iostream>
#include<vector>
using namespace std;
class Solution {
public:
   int singleNumber(vector<int>& nums)
   {
       // Record the length of the array once.
       // This is required so the for-loop knows how many elements to process.
       // If this line is removed, the loop boundary would be undefined.
       int n = nums.size();

       // Initialize the XOR accumulator to zero.
       // Starting with 0 is important because 0 ^ x == x.
       // Without this, xorResult would be uninitialized and the output incorrect.
       int xorResult = 0;

       // Traverse all numbers exactly once in O(n) time.
       // Duplicate entries cancel each other due to XOR properties.
       for (int i = 0; i < n; i++) {
           xorResult ^= nums[i];
       }

       // After processing all elements, the unmatched number remains.
       return xorResult;
   }
};


int main() {
   // Test case: all elements appear twice except 4
   vector<int> nums = {2, 3, 5, 4, 5, 3, 2};


   Solution sol;
   int result = sol.singleNumber(nums);


   cout << "Single number is: " << result << endl;


   return 0;
}

/*
### 1. 🧠 Problem Understanding

* What type of problem is this?
  - Find the unique element in an array when every other element appears exactly twice.
  - This is a bit manipulation and array traversal problem.

* What are key constraints/clues?
  - Linear runtime is required (O(n)).
  - Constant extra space is required (O(1)).
  - There is exactly one element that does not have a duplicate.
  - The array is non-empty.

### 2. 🔍 Pattern Recognition

* Which DSA pattern is used?
  - Bit manipulation using XOR.

* How can I recognize this pattern in future problems?
  - The problem says "every element appears twice except one" or "find the single number."
  - It asks for O(n) time and O(1) space.
  - If duplicates cancel out and only one value remains, XOR is usually the answer.

### 3. ⚡ Approach Breakdown (Interview Style)

* Brute force idea
  - Compare each number with every other number to find the one with no match.
  - This is O(n^2) and too slow for large arrays.

* Better approach
  - Sort the array and then scan in pairs.
  - This is O(n log n) and may use extra space depending on the sort.

* Optimal approach (why this one is chosen)
  - XOR all elements in one pass.
  - Duplicate values cancel to zero, leaving the single number.
  - This meets both the time and space constraints.

### 4. 🧩 Intuition Building

* Explain the core idea in simple terms
  - Imagine crossing out matching pairs in a guest list.
  - XOR does the same thing mathematically: pairs disappear, and the odd one out stays.

* What is the “trick” or insight?
  - Use XOR to automatically remove duplicates instead of counting or sorting.

### 5. 🔁 How to Recall Later

* 2–3 key signals to identify this problem again
  - "every element appears twice except one."
  - "find the unique element."
  - "constant extra space required."

* One-line memory trick
  - "XOR removes pairs, so only the lonely number remains."

### 6. ⚠️ Common Mistakes

* Where beginners go wrong
  - Forgetting to initialize xorResult to 0.
  - Using a hash map and breaking the O(1) space requirement.
  - Assuming the single number is positive or non-zero.
  - Using this method when duplicates do not appear exactly twice.

### 7. 📊 Complexity Analysis

* Time Complexity: O(n)
  - We scan the array once and do a constant-time XOR per element.

* Space Complexity: O(1)
  - Only two extra variables are used: `n` and `xorResult`.
  - No additional arrays or maps are allocated.

### 8. 🔄 Alternative Approaches

* Sorting and scanning
  - Sort the array and then compare adjacent elements to find the unique one.
  - Time becomes O(n log n).

* Frequency counting with a hash map
  - Count occurrences, then return the value with count 1.
  - This uses extra space O(n).

* Using a set to track seen values
  - Add unseen values and remove duplicates.
  - This also uses extra space and is unnecessary here.
*/