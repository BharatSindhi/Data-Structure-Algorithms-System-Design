#include <iostream>
// Includes input/output utilities.
// This file does not currently print anything, but <iostream> is commonly kept
// for main(), cout/cin, or quick local testing.
// If removed from this exact program, it would still compile because no iostream
// object is used; however, adding cout/cin later would break without it.
// Complexity impact: none at runtime.
#include <vector>
// Includes the vector container used by the function parameter vector<int>& gain.
// If removed, the compiler would not know what vector<int> means.
// Complexity impact: none directly; vector gives O(1) indexed access and compact storage.
using namespace std;
// Lets us write vector instead of std::vector.
// If removed, every standard library name would need the std:: prefix.
// In interviews, using std:: explicitly is often cleaner, but this does not affect logic.

class Solution {
// LeetCode expects solutions to be wrapped inside a class named Solution.
// If this class is removed or renamed, LeetCode's judge will not find largestAltitude().
public:
    int largestAltitude(vector<int>& gain) {
        // Problem type:
        // We are given net altitude changes between consecutive points.
        // Starting altitude is always 0.
        // We must return the highest altitude reached at any point.
        //
        // Example for dry run:
        // gain = {-5, 1, 5, 0, -7}
        // Start altitude = 0
        // After -5 => -5
        // After +1 => -4
        // After +5 => 1
        // After +0 => 1
        // After -7 => -6
        // Highest altitude seen = 1
        //
        // Pattern:
        // This is a Prefix Sum problem because every current altitude depends on
        // the sum of all gains seen so far.
        //
        // Time complexity of the function: O(n), where n = gain.size(),
        // because we scan the gain array exactly once.
        // Space complexity: O(1), because we only store two integer variables.

        int prev=0;
        // prev stores the current altitude after applying gains one by one.
        // It starts at 0 because the biker starts at altitude 0 before any gain.
        //
        // Why necessary:
        // To know the altitude at the current point, we need the running sum of gains.
        //
        // What breaks if removed:
        // We would not know the current altitude, so we could not compare it with
        // the best altitude found so far.
        //
        // Dry run:
        // gain = {-5, 1, 5}
        // initially prev = 0
        // after -5: prev = -5
        // after +1: prev = -4
        // after +5: prev = 1
        //
        // Edge case handled:
        // If gain is empty, altitude never changes and prev remains 0.

        int max=0;
        // max stores the highest altitude found so far.
        // It starts at 0 because the starting altitude itself is a valid altitude.
        //
        // Why necessary:
        // The highest point might be the starting point, especially if all gains are negative.
        //
        // What breaks if initialized incorrectly:
        // If max started from a very negative value, the answer would still often work,
        // but starting from 0 directly captures the problem's rule that altitude begins at 0.
        // If this variable is removed, we could not remember the best altitude after moving on.
        //
        // Dry run:
        // gain = {-3, -2}
        // altitudes: 0, -3, -5
        // max should stay 0, because the starting point is highest.
        //
        // Note:
        // The name max shadows the common std::max function name. It works here,
        // but in larger codebases a name like highest would be clearer.

        for(auto x : gain){
            // Iterate through each altitude change in gain.
            //
            // What x means:
            // x is the change from the previous point to the next point.
            // Positive x means going up; negative x means going down; zero means no change.
            //
            // Why necessary:
            // We must process every gain to compute every altitude reached.
            //
            // What breaks if removed:
            // No gains would be applied, so the function would always return 0.
            //
            // Dry run with gain = {-5, 1, 5, 0, -7}:
            // loop 1: x = -5
            // loop 2: x = 1
            // loop 3: x = 5
            // loop 4: x = 0
            // loop 5: x = -7
            //
            // Edge cases handled:
            // - Empty gain vector: loop runs 0 times and returns starting altitude 0.
            // - All negative gains: max remains 0.
            // - Zero gains: altitude stays the same and comparison still works.

            prev+=x;
            // Update current altitude by adding the current gain to the previous altitude.
            // This is the prefix sum step.
            //
            // Why necessary:
            // Altitude after i moves = gain[0] + gain[1] + ... + gain[i].
            //
            // What breaks if removed:
            // prev would stay 0 forever, so max would never reflect real altitudes.
            //
            // Dry run:
            // gain = {-5, 1, 5}
            // before loop: prev = 0
            // x = -5 => prev = 0 + (-5) = -5
            // x = 1  => prev = -5 + 1 = -4
            // x = 5  => prev = -4 + 5 = 1
            //
            // Edge case note:
            // If gain values or array size were extremely large, int overflow could happen.
            // LeetCode constraints for this problem are small enough that int is safe.

            if(prev>max) max=prev;
            // If the current altitude is higher than every altitude seen before,
            // update max to this new highest altitude.
            //
            // Why necessary:
            // The answer is not the final altitude; it is the highest altitude at any point.
            //
            // What breaks if removed:
            // max would remain 0, missing cases where altitude becomes positive.
            // Example: gain = {-1, 5}
            // altitudes: 0, -1, 4
            // correct answer = 4, but without this check we would return 0.
            //
            // Dry run:
            // gain = {-5, 1, 5, 0, -7}
            // start: prev = 0, max = 0
            // x = -5 => prev = -5, max stays 0
            // x = 1  => prev = -4, max stays 0
            // x = 5  => prev = 1,  max becomes 1
            // x = 0  => prev = 1,  max stays 1
            // x = -7 => prev = -6, max stays 1
            //
            // Beginner mistake:
            // Returning final altitude instead of tracking the maximum altitude seen.
        }
        return max;
        // Return the highest altitude encountered, including the starting altitude 0.
        //
        // Why necessary:
        // This is the value the problem asks for.
        //
        // What breaks if removed:
        // A non-void function must return an int; compilation would fail or behavior would be invalid.
        //
        // Final dry run result:
        // gain = {-5, 1, 5, 0, -7}
        // highest altitude = 1
        // return 1
    }
};

int main() {
    // Empty main for local compilation.
    // LeetCode does not use this main(); it creates a Solution object internally
    // and calls largestAltitude() with test cases.
    //
    // If removed in a normal local C++ program, linking may fail because the
    // program needs an entry point. On LeetCode, main is not required.
    
    return 0;
    // Signals successful program termination for local runs.
    // Does not affect the LeetCode solution method.
}

/*
### 1. Problem Understanding

- This is an array/running-sum problem.
- You are given gain[i], where each value tells how much altitude changes after one road segment.
- The starting altitude is 0.
- The goal is to find the maximum altitude reached at any time, not just the final altitude.
- Key clue: each altitude depends on all previous gains, which suggests prefix sum.

### 2. Pattern Recognition

- DSA pattern used: Prefix Sum / Running Sum.
- Recognize it when:
  - You need the cumulative value up to each index.
  - The current state depends on the previous state plus the current element.
  - The problem asks for max/min over all cumulative values.

### 3. Approach Breakdown (Interview Style)

- Brute force idea:
  - For every point, recompute altitude by summing all gains from the beginning.
  - This takes O(n^2) time because many sums are repeated.

- Better approach:
  - Build a prefix sum array containing altitude after each step.
  - Then find the maximum in that prefix array.
  - This takes O(n) time and O(n) space.

- Optimal approach:
  - Do not store all altitudes.
  - Keep only current altitude and highest altitude seen so far.
  - This takes O(n) time and O(1) space, so it is chosen here.

### 4. Intuition Building

- Imagine walking on hills.
- You do not need to remember every previous height if you only care about the highest one.
- At each move:
  - update where you are now,
  - ask, "Is this the highest I have ever been?"
- The trick is remembering that the starting altitude 0 also counts.

### 5. How to Recall Later

- Key signal 1: "net gain" or "change" values are given instead of direct values.
- Key signal 2: You need the best value reached along the way.
- Key signal 3: Current value = previous value + current change.
- Memory trick: "Changes need a running total; highest needs a running max."

### 6. Common Mistakes

- Forgetting to include starting altitude 0.
- Returning final altitude instead of highest altitude.
- Initializing max to gain[0], which can fail when all gains are negative.
- Creating an unnecessary prefix array when only the maximum is needed.
- Overthinking the problem as sorting, searching, or dynamic programming.

### 7. Complexity Analysis

- Time complexity: O(n)
  - Each gain value is processed exactly once.

- Space complexity: O(1)
  - Only prev and max are stored, regardless of input size.

### 8. Alternative Approaches

- Prefix array approach:
  - Create an array where prefix[i] stores altitude after i moves.
  - Then return the maximum value in that array.
  - Easier to visualize, but uses extra O(n) space.

- In-place transformation approach:
  - Convert gain into cumulative altitude values directly.
  - Then find the maximum.
  - Saves a new array but modifies the input, which is often unnecessary and risky.

- Standard library approach:
  - Use functions like partial_sum to compute cumulative values.
  - Good for concise code, but less beginner-friendly in interviews.
*/
