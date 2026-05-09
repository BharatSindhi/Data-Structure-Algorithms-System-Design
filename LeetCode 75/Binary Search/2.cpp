#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Problem: For every spell, count how many potions form a pair whose product is at least success.
    // Type: "count elements >= some threshold" after sorting, which is a classic binary search clue.
    // If this function were removed, LeetCode would have no implementation to call.
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        // Sort potions so we can binary search the first potion strong enough for each spell.
        // Why needed: without sorted order, lower_bound cannot correctly find the threshold position.
        // What breaks if removed: lower_bound on an unsorted vector gives meaningless results.
        // Dry run setup: spells = [5, 1, 3], potions = [1, 2, 3, 4, 5], success = 7.
        // After sorting, potions stays [1, 2, 3, 4, 5].
        // Edge cases: duplicates are kept, which is correct because each potion counts separately.
        // Cost: O(m log m), where m = potions.size().
        sort(potions.begin(),potions.end());

        // res stores the answer for each spell in the same order as the input spells.
        // Why needed: each spell can have a different number of successful potions.
        // What breaks if removed: there would be nowhere to collect per-spell answers.
        // Space: O(n) for n spells, because the output itself has n answers.
        vector<int> res;

        // Process each spell independently.
        // Why this loop: the threshold potion strength depends on the current spell value.
        // What breaks if removed: we would only solve zero spells and return an empty answer.
        // Dry run:
        // spell = 5 -> need potion >= ceil(7 / 5) = 2 -> potions [2,3,4,5] work -> count 4.
        // spell = 1 -> need potion >= ceil(7 / 1) = 7 -> none work -> count 0.
        // spell = 3 -> need potion >= ceil(7 / 3) = 3 -> potions [3,4,5] work -> count 3.
        // Final result for this example: [4, 0, 3].
        // Total loop cost: n iterations, each doing O(log m) binary search.
        for(int spell: spells){
            // Compute the minimum potion value needed for this spell:
            // spell * potion >= success  =>  potion >= success / spell.
            // Because potion must be an integer, we need ceil(success / spell).
            // Formula (success + spell - 1) / spell gives integer ceiling division for positive values.
            // Why needed: it converts a multiplication condition into a searchable threshold.
            // What breaks if removed/replaced with success / spell: normal division floors the value.
            // Example: success = 7, spell = 3.
            // success / spell = 2, but 3 * 2 = 6, which is not successful.
            // ceil(7 / 3) = 3, and 3 * 3 = 9, which is successful.
            // Edge cases handled: avoids checking spell * potion directly, which can overflow int.
            // Edge case assumed by LeetCode: spell values are positive, so division by zero is not an issue.
            long potion_needed=(success+spell-1)/spell;

            // Find the first potion whose value is >= potion_needed.
            // lower_bound works because potions is sorted.
            // Why needed: every potion from this iterator to the end will also be strong enough.
            // What breaks if removed: we would need to scan all potions for each spell, causing O(n*m).
            // Dry run: potions = [1,2,3,4,5], potion_needed = 3.
            // lower_bound points to value 3, the first potion that can succeed.
            // Edge cases:
            // - If all potions are too small, it == potions.end(), count becomes 0.
            // - If all potions are strong enough, it == potions.begin(), count becomes potions.size().
            // - If duplicates exist, lower_bound finds the first valid duplicate, so all valid copies count.
            auto it = lower_bound(potions.begin(),potions.end(),potion_needed);

            // Number of successful potions = elements from first valid potion to the end.
            // potions.end() - it works because vector iterators support random-access subtraction.
            // Why needed: converts the binary-search position into the required count.
            // What breaks if removed: this spell's answer would never be added to res.
            // Dry run:
            // potions = [1,2,3,4,5], it at value 3 -> end - it = 3 elements: [3,4,5].
            // Edge cases:
            // - it == end -> 0.
            // - it == begin -> m.
            // Complexity of this subtraction is O(1).
            res.push_back(potions.end()-it);
        }

        // Return answers in the same order as spells.
        // Why needed: the caller expects one count per original spell.
        // What breaks if removed: the function would not return the computed result.
        // Overall complexity:
        // Time = O(m log m + n log m), sorting potions once plus binary searching for each spell.
        // Space = O(n) for res, ignoring sort's internal implementation details.
        return res;
    }
};

int main() {
    
    return 0;
}

/*
### 1. 🧠 Problem Understanding

This is a counting problem with a hidden threshold.
For each spell, we need to count potions where:

    spell * potion >= success

Key constraints/clues:
- There are many spells and many potions, so checking every pair can be too slow.
- The condition asks for "how many values are at least enough."
- Potions can be sorted without changing the answer, because we only count potions, not their original order.
- Products can be large, so using long long / long-style arithmetic is important.

Small example:
spells = [5, 1, 3], potions = [1, 2, 3, 4, 5], success = 7
- spell 5 needs potion >= 2, so 4 potions work.
- spell 1 needs potion >= 7, so 0 potions work.
- spell 3 needs potion >= 3, so 3 potions work.
Answer: [4, 0, 3]

### 2. 🔍 Pattern Recognition

Pattern used: Sorting + Binary Search.

How to recognize it:
- The problem asks for a count of elements satisfying >=, <=, or some threshold condition.
- One array can be sorted.
- For each element in another array, you need to find the first valid position.
- Phrases like "successful pairs", "at least", "minimum required", and "count how many" often point here.

### 3. ⚡ Approach Breakdown (Interview Style)

Brute force idea:
- For every spell, try every potion.
- Count pairs where spell * potion >= success.
- Time: O(n * m), which may be too slow.

Better approach:
- Sort potions.
- For each spell, still think in terms of a required minimum potion.
- Use binary search instead of scanning all potions.

Optimal approach used here:
- Sort potions once.
- For each spell, compute potion_needed = ceil(success / spell).
- Use lower_bound to find the first potion >= potion_needed.
- All potions after that index are successful.
- This is chosen because it reduces each spell's work from O(m) to O(log m).

### 4. 🧩 Intuition Building

Core idea:
Instead of multiplying the spell with every potion, ask:

    "What is the smallest potion that would make this spell successful?"

Once potions are sorted, the answer becomes easy:
- Find the first potion that is strong enough.
- Everything to its right is also strong enough.

The trick:
Convert:

    spell * potion >= success

into:

    potion >= ceil(success / spell)

Then binary search that threshold.

### 5. 🔁 How to Recall Later

Key signals:
- Need to count pairs from two arrays.
- Condition is based on a product or sum reaching a target.
- One side can be sorted, and "first valid element" gives the count.

One-line memory trick:
Sort one array, turn the condition into a threshold, then binary search the first valid value.

### 6. ⚠️ Common Mistakes

- Using normal division success / spell instead of ceiling division.
  Example: 7 / 3 gives 2, but potion 2 fails because 3 * 2 = 6.

- Forgetting to sort potions before using lower_bound.
  lower_bound only works correctly on sorted ranges.

- Counting only one matching potion instead of all potions from the found index to the end.

- Multiplying spell * potion using int and risking overflow.
  This solution avoids direct multiplication during checks by using a required threshold.

- Using upper_bound instead of lower_bound.
  We need the first value >= potion_needed, not the first value > potion_needed.

### 7. 📊 Complexity Analysis

Let:
- n = number of spells
- m = number of potions

Sorting potions:
- O(m log m)

For each spell:
- Compute required potion in O(1).
- Binary search potions in O(log m).

Total time:
- O(m log m + n log m)

Space:
- O(n) for the result vector.
- Sorting may use extra internal stack/helper space depending on the C++ implementation.

### 8. 🔄 Alternative Approaches

1. Brute force:
   Check every spell-potion pair directly.
   Simple, but too slow for large inputs.

2. Sort potions + manual binary search:
   Same idea as lower_bound, but write the binary search yourself.
   Useful in interviews if the interviewer asks you to implement binary search manually.

3. Sort spells too with two pointers:
   You can sort spells with their original indices and move through potions in a coordinated way.
   This can work, but it is more complex because answers must be restored to original spell order.
   The lower_bound approach is cleaner and less error-prone.
*/
