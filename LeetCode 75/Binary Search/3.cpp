#include <iostream>
#include <vector>
using namespace std;

// This solution solves LeetCode 162: Find Peak Element.
// A peak element is an index i such that nums[i] is greater than its neighbors.
// For boundary elements, we imagine nums[-1] = -infinity and nums[n] = -infinity.
// Because of that imaginary -infinity outside the array, at least one peak always exists.
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        
        // left marks the start of the current search space.
        // Why needed:
        // We do not need to scan the whole array; binary search repeatedly shrinks
        // the possible region where a peak must exist.
        // If removed:
        // We would not know the left boundary of the remaining valid answer range.
        // Edge case:
        // For a single element array, left starts at 0 and is already the answer.
        int left = 0;

        // right marks the end of the current search space.
        // nums.size() - 1 gives the last valid index.
        // Why needed:
        // A peak index must be inside [0, nums.size() - 1].
        // If removed:
        // The algorithm would not know where the searchable range ends.
        // Edge case handled:
        // nums = [5] -> right = 0, so while(left < right) is false and 0 is returned.
        // Edge case missed by this code:
        // If nums is empty, nums.size() - 1 underflows because size() is unsigned.
        // LeetCode guarantees nums has at least one element, so this is acceptable there.
        int right = nums.size() - 1;

        // Continue until the search space collapses to exactly one index.
        // Why left < right:
        // As long as there are at least two candidates, we can compare mid with mid + 1.
        // If changed to left <= right:
        // mid + 1 could go out of bounds when left == right.
        // Invariant:
        // At every step, there is at least one peak inside the current [left, right] range.
        while(left < right){

            // Calculate the middle index safely.
            // left + (right - left) / 2 avoids possible integer overflow that can happen
            // with (left + right) / 2 in very large arrays.
            // If removed:
            // We cannot split the search space into halves.
            // Dry run example nums = [1, 2, 3, 1]:
            // left = 0, right = 3 -> mid = 1.
            int mid = left + (right - left) / 2;

            // Increasing slope
            // Compare nums[mid] with its right neighbor.
            // If nums[mid] < nums[mid + 1], we are moving upward from mid to mid + 1.
            // Why this means search right:
            // On an upward slope, a peak must exist on the right side.
            // It may be nums[mid + 1], or a later element before the slope eventually drops,
            // or the last element if the array keeps increasing.
            // If this check is removed:
            // We cannot know which half still guarantees a peak.
            // Dry run example nums = [1, 2, 3, 1]:
            // mid = 1, nums[1] = 2, nums[2] = 3.
            // Since 2 < 3, move left to mid + 1 = 2.
            // Remaining search space is [2, 3], which still contains peak index 2.
            if(nums[mid] < nums[mid + 1]){
                // Discard mid and everything left of it.
                // Why mid itself cannot be the answer here:
                // nums[mid] is smaller than nums[mid + 1], so mid is not greater than
                // its right neighbor and cannot be a peak.
                // If changed to left = mid:
                // The loop could get stuck when right = mid + 1 because mid would repeat.
                left = mid + 1;
            }
            // Decreasing slope
            // Otherwise nums[mid] > nums[mid + 1] for the standard problem constraints
            // where adjacent elements are not equal.
            // Why search left including mid:
            // If the slope goes down after mid, then nums[mid] may itself be a peak,
            // or there must be some peak to its left.
            // If this block is removed:
            // The algorithm would never handle decreasing slopes like [3, 2, 1].
            // Dry run example nums = [1, 2, 3, 1] after the first move:
            // left = 2, right = 3, mid = 2.
            // nums[2] = 3, nums[3] = 1, so search [2, 2] by setting right = mid.
            else{
                // Keep mid because it can still be a valid peak.
                // If changed to right = mid - 1:
                // We might accidentally discard the actual peak at mid.
                // Example: nums = [1, 3, 2], mid = 1 is the peak.
                right = mid;
            }
        }

        // When left == right, the search space has one index left.
        // Because the invariant says a peak always exists in [left, right],
        // this final index must be a peak.
        // Dry run completion for nums = [1, 2, 3, 1]:
        // left = 2, right = 2, loop stops, return 2.
        // Time complexity:
        // O(log n), because each iteration discards about half of the remaining range.
        // Space complexity:
        // O(1), because only a few integer variables are used.
        return left;
    }
};

int main() {
    
    return 0;
}

/*
1. Problem Understanding

- Type of problem:
  This is an array search problem where we need to find any peak element.
  We do not need the maximum element; we only need an index whose value is greater
  than its immediate neighbors.

- Key constraints/clues:
  The important clue is that nums[-1] and nums[n] are treated as -infinity.
  This guarantees at least one peak.
  Another key clue from the original problem is usually nums[i] != nums[i + 1],
  which means every adjacent comparison clearly forms either an increasing slope
  or a decreasing slope.

2. Pattern Recognition

- Pattern used:
  Binary Search on Answer / Binary Search on Slope.

- How to recognize it later:
  Use this pattern when the problem asks for a local point, such as a peak,
  valley, minimum in rotated array, or boundary, and comparing neighbors tells
  you which side still contains an answer.

3. Approach Breakdown (Interview Style)

- Brute force idea:
  Check every index and test whether it is greater than its neighbors.
  This takes O(n) time.

- Better approach:
  Notice that if nums[mid] < nums[mid + 1], the array is rising at mid, so a peak
  must exist on the right. If nums[mid] > nums[mid + 1], a peak must exist on the
  left side including mid.

- Optimal approach:
  Use binary search to repeatedly move toward a side that is guaranteed to contain
  a peak. This gives O(log n) time and O(1) space.

4. Intuition Building

- Core idea:
  Imagine walking on hills. If the ground rises to your right, keep walking right
  because you will eventually reach a top. If the ground falls to your right,
  then where you are might already be a top, or there is a top behind you.

- Trick / insight:
  You do not need to know where the maximum element is. You only need to know
  which half must contain some peak. Neighbor comparison gives that direction.

5. How to Recall Later

- Signal 1:
  The problem asks for "any peak", not necessarily the highest value.

- Signal 2:
  You are allowed to compare nums[mid] with nums[mid + 1].

- Signal 3:
  The outside of the array is treated like -infinity, guaranteeing a peak.

- One-line memory trick:
  "If slope goes up, peak is right; if slope goes down, peak is left including mid."

6. Common Mistakes

- Using left <= right, which can make nums[mid + 1] go out of bounds.

- Doing right = mid - 1 in the decreasing case, which can discard mid even though
  mid may be the peak.

- Thinking this finds the maximum element. It finds a peak, not necessarily the
  global maximum.

- Forgetting that the problem constraints guarantee a non-empty array and usually
  no equal adjacent elements.

7. Complexity Analysis

- Time Complexity:
  O(log n), because each comparison removes roughly half of the search space.

- Space Complexity:
  O(1), because the algorithm uses only left, right, and mid regardless of input size.

8. Alternative Approaches

- Linear scan:
  Check each element against its neighbors and return the first peak found.
  This is simpler but takes O(n) time.

- Find global maximum:
  The maximum element is always a peak under the boundary rule, but finding it
  by scanning also takes O(n) time.

- Recursive binary search:
  Same slope-based idea can be written recursively, but it uses O(log n) call
  stack space, so the iterative version is usually cleaner.
*/
