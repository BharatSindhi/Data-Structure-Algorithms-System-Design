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
   // Function to calculate the maximum water that can be stored
   int maxArea(vector<int>& height) {
       int n = height.size();
       int maxWater = 0;
       int left= 0, right = n - 1; // Two pointers


       // Loop until the two pointers meet
       while (left <right) {
           int wid = right - left;  // Width between the lines
           int minHeight = min(height[left], height[right]); // Container height is min of two lines
           maxWater = max(maxWater, wid * minHeight); // Update max water if current area is larger


           // Move the pointer pointing to the shorter line inward
           if (height[left] < height[right])
               left++;
           else
               right--;
       }
       return maxWater;
   }
};


int main() {
   Solution sol;
   vector<int> height = {1,8,6,2,5,4,8,3,7};  // Input array representing heights
   int result = sol.maxArea(height); // Call the function
   cout << "Maximum water that can be stored: " << result << endl;
   return 0;
}

