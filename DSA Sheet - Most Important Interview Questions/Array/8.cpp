// Problem Statement :



// You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the i th line are (i, 0) and (i, height[i]).

// Find two lines that together with the x-axis form a container, such that the container contains the most water.

// Return the maximum amount of water a container can store.



// Notice that you may not slant the container.



// Example : Stick Height

// Arjun saw that water collected between wooden sticks of different sizes. He wanted to find two sticks that could hold the most water. He noticed that the amount of water depended on the distance between the sticks and the shorter stick's height. To find the best pair, he and his friend started at opposite ends and moved inward, always shifting the shorter stick. This smart trick helped them find the biggest water container—just like solving the Container with Most Water problem in coding!



// Example1:
// Input: height = [1, 8, 6, 2, 5, 4, 8, 3, 7]
// Output: 49
// Explanation: The above vertical lines are represented by an array [1, 8, 6, 2, 5, 4, 8, 3, 7]. In this case, the maximum area of water (blue section) the container can contain is 49.


// Example 2:
// Input: height = [1, 1]
// Output: 1


// Approach
// Using Two Pointers :



// We are using two pointers (left=0, right=n-1) to find the maximum area between two lines by always moving the pointer at the shorter height to potentially get a taller line and a larger area.



// 1. Initialize Two Pointers:

// Start with one pointer at the beginning (left=0) and the other at the end (right=n-1) of the array.
// 2. Calculate the Area:

// For each pair of lines, compute the area as width × min(height[left], height[right]).
// 3. Update the Maximum Area:

// Track the largest area found during the iteration.
// 4. Move the Pointer with Smaller Height:

// To potentially increase the area, shift the pointer pointing to the shorter line inward.
// 5. Repeat the Process until the two pointers meet, and then return the maxArea. 



// Time Complexity	Space Complexity
// O(n) 	O(1)


#include <iostream>
#include<vector>
using namespace std;


class Solution {
public:
   // Function to calculate the maximum water that can be stored.
   //
   // Problem in one line:
   // Choose two vertical lines so that:
   //   water = distance_between_lines * shorter_line_height
   //
   // Why shorter_line_height?
   // Water spills from the shorter boundary, so the taller line cannot increase
   // the usable height unless the shorter side also becomes taller.
   //
   // Pattern used:
   // Two pointers from opposite ends.
   //
   // Time Complexity:
   // O(n), because each pointer moves inward at most n times total.
   //
   // Space Complexity:
   // O(1), because only a few integer variables are used.
   int maxArea(vector<int>& height) {
       // WHAT:
       // n stores the number of vertical lines.
       //
       // WHY:
       // We need n to place the right pointer at the last valid index: n - 1.
       //
       // IF REMOVED:
       // We would not know where the right boundary starts unless we repeatedly
       // call height.size(). The algorithm still needs this size information.
       //
       // EDGE CASE:
       // If n == 2, left = 0 and right = 1, so exactly one container is checked.
       // The original LeetCode problem guarantees at least 2 heights.
       int n = height.size();

       // WHAT:
       // maxWater stores the best area found so far.
       //
       // WHY:
       // Each pair of lines gives one candidate area. We need a variable to
       // remember the largest candidate seen during the scan.
       //
       // IF REMOVED:
       // We would calculate areas but lose the answer after moving pointers.
       //
       // WHY INITIALIZE TO 0:
       // Area cannot be negative because width and height are non-negative.
       int maxWater = 0;

       // WHAT:
       // left starts at the first line and right starts at the last line.
       //
       // WHY:
       // Starting with the widest possible container gives the best initial
       // width. Then we try to improve the limiting height by moving inward.
       //
       // IF REMOVED:
       // The two-pointer strategy cannot begin because we need two boundaries.
       //
       // DRY RUN START for height = [1, 8, 6, 2, 5, 4, 8, 3, 7]:
       // left = 0, right = 8
       // width = 8, minHeight = min(1, 7) = 1, area = 8
       // maxWater becomes 8.
       int left= 0, right = n - 1; // Two pointers


       // Loop until the two pointers meet.
       //
       // WHAT:
       // Every iteration checks one possible container: height[left] with
       // height[right].
       //
       // WHY left < right:
       // A container needs two different lines. If left == right, width becomes
       // 0, so no water can be stored.
       //
       // IF REMOVED:
       // The algorithm would either check no pairs or risk invalid pointer
       // movement. This loop is the core traversal.
       while (left <right) {
           // WHAT:
           // wid is the horizontal distance between the two selected lines.
           //
           // WHY:
           // Container area depends on width. Farther lines can hold more water
           // if the height is good enough.
           //
           // IF REMOVED:
           // We could not compute area = width * height.
           //
           // DRY RUN:
           // For left = 1 and right = 8:
           // wid = 8 - 1 = 7.
           int wid = right - left;  // Width between the lines

           // WHAT:
           // minHeight picks the shorter of the two boundary lines.
           //
           // WHY:
           // Water level is limited by the shorter line. The taller line above
           // that level does not help because water would overflow the shorter side.
           //
           // IF REMOVED:
           // Using max(height[left], height[right]) would overestimate water.
           // Example: [1, 100] can store only 1 * 1 = 1, not 1 * 100.
           //
           // DRY RUN:
           // For height[1] = 8 and height[8] = 7:
           // minHeight = 7.
           int minHeight = min(height[left], height[right]); // Container height is min of two lines

           // WHAT:
           // Calculate current area and keep it only if it is better than the
           // best answer so far.
           //
           // WHY:
           // The final answer is the maximum over all useful pairs considered.
           //
           // IF REMOVED:
           // maxWater would stay 0 and the function would return the wrong answer.
           //
           // DRY RUN:
           // height = [1,8,6,2,5,4,8,3,7]
           // left=0, right=8: width=8, minHeight=1, area=8, maxWater=8
           // move left to 1
           // left=1, right=8: width=7, minHeight=7, area=49, maxWater=49
           //
           // EDGE CASE:
           // If all heights are 0, every area is 0 and maxWater correctly stays 0.
           maxWater = max(maxWater, wid * minHeight); // Update max water if current area is larger


           // Move the pointer pointing to the shorter line inward.
           //
           // CORE INTUITION:
           // The width will always shrink when we move a pointer.
           // So the only possible way to get a larger area is to find a taller
           // shorter boundary.
           //
           // WHY MOVE THE SHORTER SIDE:
           // Suppose height[left] < height[right].
           // Current water is limited by height[left].
           // If we move right inward instead, width decreases while the limiting
           // height is still at most height[left], so area cannot improve because
           // the same short left wall is still there.
           //
           // IF THIS DECISION IS REMOVED:
           // We lose the greedy pruning that makes the solution O(n).
           // Checking all pairs would become O(n^2).
           //
           // DRY RUN CONTINUED:
           // [1,8,6,2,5,4,8,3,7]
           // left=0(1), right=8(7): left is shorter, so left++.
           // left=1(8), right=8(7): right is shorter, so right--.
           // left=1(8), right=7(3): right is shorter, so right--.
           // This keeps searching for a better shorter wall while width shrinks.
           if (height[left] < height[right])
               // WHAT:
               // Move left one step inward because left height is the limiting wall.
               //
               // WHY:
               // A taller line on the left may increase minHeight enough to beat
               // the loss in width.
               //
               // IF REMOVED:
               // left would never move in this case, causing an infinite loop.
               left++;
           else
               // WHAT:
               // Move right one step inward when right height is less than or equal
               // to left height.
               //
               // WHY:
               // The right side is the limiting wall, or both are equal. In either
               // case, moving one limiting side is safe.
               //
               // IF REMOVED:
               // right would never move in this case, causing an infinite loop.
               //
               // EDGE CASE:
               // When heights are equal, moving either pointer is acceptable.
               // This code moves right in the equal case.
               right--;
       }

       // WHAT:
       // Return the largest area found across all checked pointer pairs.
       //
       // WHY:
       // maxWater is the accumulated best answer.
       //
       // IF REMOVED:
       // The function would not provide a result to the caller.
       //
       // FINAL DRY RUN RESULT:
       // For [1,8,6,2,5,4,8,3,7], maxWater becomes 49 from lines at indices
       // 1 and 8: width = 7, height = min(8,7) = 7, area = 49.
       return maxWater;
   }
};


int main() {
   // WHAT:
   // Create an object of Solution so we can call maxArea.
   //
   // WHY:
   // maxArea is a member function inside the Solution class.
   Solution sol;

   // WHAT:
   // Sample input where each value represents the height of one vertical line.
   //
   // WHY:
   // This is the classic example for Container With Most Water.
   //
   // EXPECTED:
   // The best pair is height[1] = 8 and height[8] = 7.
   // width = 8 - 1 = 7
   // water = 7 * min(8, 7) = 49
   vector<int> height = {1,8,6,2,5,4,8,3,7};  // Input array representing heights

   // WHAT:
   // Call the function and store the answer.
   //
   // WHY:
   // Separating calculation from printing makes the result easy to inspect.
   int result = sol.maxArea(height); // Call the function

   // WHAT:
   // Print the maximum water that can be stored.
   //
   // IF REMOVED:
   // The program would still compute the result but would not show it.
   cout << "Maximum water that can be stored: " << result << endl;

   // WHAT:
   // Return 0 to indicate successful program execution.
   return 0;
}

/*
================================================================================
### 1. 🧠 Problem Understanding
================================================================================

What type of problem is this?
- This is an array optimization problem.
- We must choose two indices i and j to maximize:
      area = (j - i) * min(height[i], height[j])
- It is not asking for all pairs, only the best pair.

Key constraints/clues:
- The container cannot be slanted, so height is limited by the shorter line.
- Width depends on distance between indices.
- We need maximize a formula involving two positions.
- A brute force pair check is possible, but likely too slow for large n.

Important observation:
- Moving inward always decreases width.
- Therefore, we should only move a pointer when it gives us a chance to improve
  the limiting height.
*/

/*
================================================================================
### 2. 🔍 Pattern Recognition
================================================================================

DSA pattern used:
- Two Pointers.

Why two pointers?
- We are choosing two elements from an array.
- The answer depends on both ends: width and shorter height.
- Starting from the widest possible pair gives a strong greedy starting point.

How to recognize this pattern in future problems:
- Problem asks for a pair in a sorted-like/index-based structure.
- You can start from two extremes and safely discard one side.
- There is a rule that tells you which pointer to move.
- You want better than O(n^2) pair checking.

Signal phrase:
- "Find two lines/elements/indices that maximize or satisfy something."
*/

/*
================================================================================
### 3. ⚡ Approach Breakdown (Interview Style)
================================================================================

Brute force idea:
- Try every pair (i, j).
- Calculate:
      width = j - i
      height = min(height[i], height[j])
      area = width * height
- Track maximum area.
- Time: O(n^2)
- Space: O(1)
- Problem: Too slow when n is large.

Better approach:
- Notice that the shorter wall is always the bottleneck.
- Start with maximum width using left = 0 and right = n - 1.
- Calculate area.
- Move the pointer at the shorter line inward.

Optimal approach:
- Two pointers.
- Each step discards one boundary that cannot produce a better answer with the
  current opposite boundary.
- Time: O(n)
- Space: O(1)

Why this one is chosen:
- It checks only useful candidates.
- It keeps the best width initially and searches for better height as width
  shrinks.
*/

/*
================================================================================
### 4. 🧩 Intuition Building
================================================================================

Core idea in simple terms:
- Imagine two sticks holding water.
- The shorter stick decides how high the water can rise.
- If you move the taller stick, the width gets smaller while the same shorter
  stick still limits the water.
- That cannot help.
- So move the shorter stick and hope to find a taller one.

The trick/insight:
- Do not try all pairs.
- At each step, safely eliminate the shorter side because it is the bottleneck.

Small dry run:
height = [1, 8, 6, 2, 5, 4, 8, 3, 7]

left=0, right=8:
- width = 8
- minHeight = min(1,7) = 1
- area = 8
- maxWater = 8
- move left because 1 < 7

left=1, right=8:
- width = 7
- minHeight = min(8,7) = 7
- area = 49
- maxWater = 49
- move right because 7 is shorter

The algorithm continues, but no later area beats 49.
*/

/*
================================================================================
### 5. 🔁 How to Recall Later
================================================================================

Key signals:
- Two boundary problem.
- Area depends on width and smaller height.
- Moving one pointer decreases width, so pointer movement must be meaningful.

Memory trick:
- "Move the smaller wall, because the taller wall is not the problem."

Another quick recall:
- Width shrinks anyway, so search for a taller bottleneck.
*/

/*
================================================================================
### 6. ⚠️ Common Mistakes
================================================================================

Beginner mistakes:
- Moving the taller pointer instead of the shorter pointer.
- Thinking taller height always means more water, forgetting min(height[i], height[j]).
- Using nested loops and getting O(n^2), then timing out.
- Calculating width as right - left + 1. The correct width is right - left
  because indices represent x-coordinates.
- Forgetting to update maxWater before moving a pointer.
- Using only height[left] or height[right] instead of the minimum of both.

Edge cases handled:
- Two elements: only one possible container.
- Equal heights: moving either pointer is fine; this code moves right.
- Zero heights: area becomes 0 where a boundary height is 0.
- Increasing heights: left pointer keeps moving because left is usually shorter.
- Decreasing heights: right pointer keeps moving because right is usually shorter.

Edge case missed by the function:
- Empty array or one-element array is not explicitly handled.
- The original problem normally guarantees at least two elements.
*/

/*
================================================================================
### 7. 📊 Complexity Analysis
================================================================================

Time Complexity: O(n)
- left starts at 0.
- right starts at n - 1.
- In every loop iteration, either left increases or right decreases.
- No pointer ever moves backward.
- Therefore, there can be at most n - 1 meaningful moves.

Space Complexity: O(1)
- Variables used:
      n
      maxWater
      left
      right
      wid
      minHeight
- No extra array, map, stack, queue, or recursion is used.

Why this is optimal:
- Any algorithm must inspect enough heights to know which pair can form the
  answer.
- The two-pointer approach does this in a single pass.
*/

/*
================================================================================
### 8. 🔄 Alternative Approaches
================================================================================

1. Brute Force:
- Check every pair of lines.
- Very easy to understand.
- Time O(n^2), space O(1).
- Good first explanation in interviews, but not the final solution.

2. Sorting-based thinking:
- Sorting heights destroys original indices.
- Since width depends on original positions, sorting is not a clean fit.
- Usually not recommended for this problem.

3. Precomputed max arrays:
- You might think of storing maximum height to the left/right.
- But the answer depends on exact pair distance, not just nearest max height.
- This becomes more complex than needed and does not beat two pointers.

4. Two Pointers:
- Best practical and interview solution.
- Uses the bottleneck insight.
- Time O(n), space O(1).
*/

