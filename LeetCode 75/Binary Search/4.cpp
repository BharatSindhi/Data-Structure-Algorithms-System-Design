#include <iostream>
#include <vector>
using namespace std;

// This solution solves "Koko Eating Bananas".
// Big idea: the answer is not an index in an array; the answer is a number
// called "eating speed". Because speeds have a monotonic behavior
// (slow speeds may fail, fast speeds pass), we can binary search the answer.
class Solution {
public:

    // canEat checks whether speed k is enough to finish all piles within h hours.
    //
    // Why this helper is necessary:
    // Binary search needs a yes/no test for a guessed answer.
    // Here the guessed answer is k bananas per hour.
    //
    // If this function were removed:
    // minEatingSpeed would have no clean way to decide whether mid is valid,
    // and the binary search direction would become unclear.
    //
    // Dry run example:
    // piles = [3, 6, 7, 11], h = 8, k = 4
    // pile 3  -> ceil(3 / 4)  = 1 hour
    // pile 6  -> ceil(6 / 4)  = 2 hours
    // pile 7  -> ceil(7 / 4)  = 2 hours
    // pile 11 -> ceil(11 / 4) = 3 hours
    // total = 1 + 2 + 2 + 3 = 8, so k = 4 works.
    //
    // Edge cases:
    // - k = 1 means eating as slowly as possible.
    // - k >= max pile means each pile takes at most 1 hour.
    // - large piles can make total hours big, so hours is long long.
    //
    // Complexity of this helper:
    // Time: O(n), because we inspect every pile once in the worst case.
    // Space: O(1), because we only store the running total.
    bool canEat(vector<int>& piles, int h, int k) {

        // hours stores the total hours needed at speed k.
        // long long is used to avoid overflow when piles are large and many.
        // If this line were removed, we could not accumulate the required time.
        long long hours = 0;

        // Visit each pile and compute how many full hours Koko needs for it.
        // If this loop were removed, the function would not actually check all piles.
        for (int pile : piles) {

            // ceil(pile / k)
            // This computes ceil(pile / k) using integer arithmetic.
            //
            // Why ceil is needed:
            // Koko can only work on one pile in an hour. Even if a pile has
            // leftover bananas after division, that leftover still costs
            // one extra hour.
            //
            // Formula:
            // ceil(a / b) = (a + b - 1) / b for positive integers.
            //
            // Dry run:
            // pile = 7, k = 4
            // (7 + 4 - 1) / 4 = 10 / 4 = 2 hours
            // Without ceil logic, 7 / 4 would become 1, which is wrong.
            //
            // If this line were removed:
            // hours would never increase, so the function would incorrectly
            // say almost every speed works.
            hours += (pile + k - 1) / k;

            // optimization
            // If we already exceeded h, speed k cannot be valid.
            // Returning early avoids unnecessary work on the remaining piles.
            //
            // If this block were removed:
            // the final answer would still be correct, but the helper might
            // do extra work, especially on large inputs.
            //
            // Dry run:
            // piles = [100, 100, 100], h = 2, k = 1
            // after first pile, hours = 100 > 2, so we can fail immediately.
            if (hours > h)
                return false;
        }

        // If total hours is within the allowed h, speed k is feasible.
        // This also covers the exact-fit case, like total hours == h.
        // If this were removed, the helper would not return a result
        // for successful or exactly successful speeds.
        return hours <= h;
    }

    // minEatingSpeed returns the minimum integer speed k such that Koko can
    // finish all piles within h hours.
    //
    // This is binary search on the answer:
    // - Search space is speed, not array positions.
    // - low and high represent the smallest and largest possible speeds.
    //
    // Overall complexity:
    // Time: O(n log m), where n = number of piles and m = max pile size.
    // Space: O(1), ignoring the input array.
    int minEatingSpeed(vector<int>& piles, int h) {

        // Minimum possible speed is 1 banana/hour.
        // Speed 0 is invalid because Koko would never eat anything.
        // If this were removed or set to 0, division by zero could happen.
        int low = 1;

        // Maximum necessary speed is the largest pile size.
        // At this speed, every pile can be finished in at most one hour.
        //
        // Why this upper bound works:
        // Eating faster than the largest pile is never useful, because Koko
        // cannot eat from more than one pile in the same hour.
        //
        // If this line were removed:
        // we would not know the right boundary for binary search.
        //
        // Note:
        // In standard C++, max_element requires #include <algorithm>.
        // The logic is correct, but that header is needed for compilation.
        int high = *max_element(piles.begin(), piles.end());

        // ans stores the best valid speed found so far.
        // Start with high because high is always a safe candidate.
        // If this line were removed, we might lose the current best answer
        // while continuing to search for a smaller one.
        int ans = high;

        // Binary search over all possible eating speeds from low to high.
        //
        // Dry run with piles = [3, 6, 7, 11], h = 8:
        // low = 1, high = 11
        // mid = 6 -> works, ans = 6, search smaller speeds
        // mid = 3 -> fails, search larger speeds
        // mid = 4 -> works, ans = 4, search smaller speeds
        // loop ends, answer = 4
        //
        // If this loop were removed:
        // the function would just return high, which is valid but not minimal.
        while (low <= high) {

            // Pick the middle speed safely.
            // low + (high - low) / 2 avoids potential overflow compared
            // with (low + high) / 2.
            //
            // If this line were removed:
            // there would be no guessed speed to test.
            int mid = low + (high - low) / 2;

            // Check whether this guessed speed can finish within h hours.
            //
            // Monotonic property:
            // If mid works, every speed greater than mid also works.
            // If mid fails, every speed smaller than mid also fails.
            if (canEat(piles, h, mid)) {

                // mid is valid, so record it as a possible answer.
                // We still continue because there may be a smaller valid speed.
                // If this were removed, we could lose the minimum valid speed.
                ans = mid;

                // try smaller speed
                // Since mid works, move left to find an even smaller speed.
                // If this were changed to low = mid + 1, we would search
                // in the wrong direction and likely miss the minimum.
                high = mid - 1;

            } else {

                // increase speed
                // mid is too slow, so all speeds <= mid are impossible.
                // Move right to try faster speeds.
                // If this were removed, the loop might never make progress
                // after a failing mid.
                low = mid + 1;
            }
        }

        // ans is the smallest speed that passed canEat.
        // Edge case:
        // If h equals piles.size(), the answer becomes max pile, because
        // each pile must be finished in exactly one hour.
        return ans;
    }
};


int main() {
    
    // Empty main because LeetCode creates Solution and calls minEatingSpeed.
    // In a local test, you could create a vector and call the method here.
    return 0;
}

/*
### 1. Problem Understanding

- This is a "minimum possible value that satisfies a condition" problem.
- Koko must eat all banana piles within h hours.
- She chooses one integer speed k, meaning k bananas per hour.
- The goal is not just any working k, but the smallest working k.
- Key clue: If a speed works, all larger speeds also work. That creates a searchable yes/no boundary.

### 2. Pattern Recognition

- Pattern used: Binary Search on Answer.
- We are not searching for an element inside piles.
- We are searching over the range of possible answers: k from 1 to max(piles).
- Recognize this pattern when:
  - The problem asks for "minimum maximum", "smallest possible", or "least value".
  - You can write a helper that answers: "Can this guessed value work?"
  - The answer space is monotonic: false false false true true true.

### 3. Approach Breakdown (Interview Style)

- Brute force idea:
  Try every speed from 1 to max(piles), compute required hours, and return the first valid speed.
  Time: O(n * maxPile), which is too slow when pile values are large.

- Better approach:
  Notice that speeds form a sorted answer space by feasibility.
  Slow speeds fail, fast speeds pass.

- Optimal approach:
  Binary search the speed range [1, maxPile].
  For each mid speed, calculate total hours.
  If mid works, try smaller speeds.
  If mid fails, try larger speeds.

### 4. Intuition Building

- Imagine turning a speed knob.
- At very low speed, Koko cannot finish in time.
- At high speed, she can finish.
- We need the first speed where the answer changes from "cannot finish" to "can finish".
- The trick is converting "minimum valid speed" into a yes/no boundary search.

### 5. How to Recall Later

- Signal 1: The problem asks for the minimum integer value that makes a task possible.
- Signal 2: You can test a guessed answer with a helper function.
- Signal 3: Increasing the guessed value never makes the result worse.
- Memory trick: "Guess speed, test hours, shrink toward the first valid speed."

### 6. Common Mistakes

- Using normal division pile / k instead of ceiling division.
- Forgetting that leftover bananas still require one full hour.
- Searching array indices instead of searching possible speeds.
- Moving the binary search boundary in the wrong direction.
- Returning mid directly instead of tracking ans.
- Forgetting #include <algorithm> for max_element in local C++ compilation.
- Using int for hours when constraints can make the total large.

### 7. Complexity Analysis

- Let n be piles.size().
- Let m be max(piles).
- canEat takes O(n) time because it may inspect every pile.
- Binary search checks O(log m) possible speeds.
- Total time complexity: O(n log m).
- Extra space complexity: O(1), because only a few variables are used.

### 8. Alternative Approaches

- Linear search:
  Try k = 1, 2, 3, ... until one works.
  Simple but too slow for large pile sizes.

- Sorting:
  Sorting piles does not help much because the cost for a speed still depends
  on every pile. It would add unnecessary O(n log n) work.

- Prefix sums:
  Not useful here because each pile contributes ceil(pile / k), and k changes
  during the search. Prefix sums do not directly speed up those ceiling values.
*/
