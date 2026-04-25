// Problem Statement :


// Given an array ‘nums’ of size n, return the majority element.

// As we have already discussed above, the majority element is the element that appears more than [n / 2] times. If no such element exists, then return -1.



// Example 1:
// Input: nums = [3,2,3]
// Output: 3


// Example 2:
// Input: nums = [2,2,1,1,1,2,2]
// Output: 2

// Approach
// Using Boyer-Moore Voting Algorithm :


// Moore’s Voting Algorithm works by canceling out different elements against each other. Since the majority element appears more than half the time, it survives this cancellation and becomes the final candidate. We then verify if it's truly the majority element or not.



// 1. Make the first element (nums[0]) the majority candidate, and its count = 1.

// 2. Iterate over the Array to Find a Possible Candidate

//         Iterate the array:

// Increase the count of the candidate and the current element match
// If it doesn’t match, decrease the count
// If the count becomes zero, update the current element as the new candidate and reset the count to 1.
// 3. Check if the Candidate is Majority element or not

// After identifying a candidate, traverse the array and count its frequency.
// Return it as the majority if it occurs more than n/2 times. Return -1 otherwise.


#include <iostream>
#include<vector>
using namespace std;

// Solution class containing the majorityElement function
class Solution {
public:
   int majorityElement(vector<int>& nums) {
       int n = nums.size();
       // Initialize count to 1 for the first element
       // count = 1 because we're starting with nums[0] as candidate
       // This will track how much the current candidate "dominates" others
       int count = 1;
       // Assume the first element as majority candidate
       // WHY: We'll replace this if another element appears more frequently
       // WHAT BREAKS: If we don't start with a candidate, we can't compare elements
       int majority = nums[0];

       // ==========================================
       // PHASE 1: CANCELLATION PHASE
       // Goal: Find a POSSIBLE candidate (not verified yet)
       // Key Insight: Majority element survives all cancellations
       // ==========================================
       // Start from index 1 (skipping the first element we already picked)
       // WHY: We already picked nums[0] as initial candidate
       for (int i = 1; i < n; i++) {
           // DRY RUN on [2, 2, 1, 1, 2, 2, 2]:
           // i=1: nums[1]=2 == majority(2)? YES → count=2
           // i=2: nums[2]=1 == majority(2)? NO → count=1
           // i=3: nums[3]=1 == majority(2)? NO → count=0 → majority=1, count=1
           // i=4: nums[4]=2 == majority(1)? NO → count=0 → majority=2, count=1
           // i=5: nums[5]=2 == majority(2)? YES → count=2
           // i=6: nums[6]=2 == majority(2)? YES → count=3
           // Candidate: 2 (will be verified in Phase 2)
           
           if (nums[i] == majority) {
               // If current element matches candidate, increase confidence in this candidate
               // WHY: We found an element matching our candidate
               // WHAT BREAKS: If we don't increment, we lose track of candidate strength
               count++;     // Same as candidate? increase count
           } else {
               // If current element is different, decrease confidence in candidate
               // WHY: This is the "cancellation" - one majority vote cancels one non-majority vote
               // If majority element appears >n/2 times, it survives all cancellations
               count--;     // Different element? decrease count
               
               // When count reaches 0, current candidate is no longer viable
               // WHY: count=0 means candidate and non-matching elements balance out
               // We need a NEW candidate to continue
               if (count == 0) {
                   // INSIGHT: Replace candidate with current element
                   // WHY: If count becomes 0, current element might be the majority
                   // EDGE CASE: This handles arrays where no element >n/2 exists
                   majority = nums[i];  // Change candidate
                   count = 1;            // Reset count for new candidate
               }
           }
       }


       // ==========================================
       // PHASE 2: VERIFICATION PHASE (CRUCIAL!)
       // Goal: Confirm the candidate is ACTUALLY majority
       // WHY: Boyer-Moore only guarantees a possible candidate, not a verified one
       // ==========================================
       // IMPORTANT: Reset count to 0 for verification
       // WHY: We need a fresh count, not the leftover count from Phase 1
       // WHAT BREAKS: If we use the old count, verification will be wrong
       count = 0;
       
       // Count actual occurrences of the candidate
       // WHY: We need to verify if candidate appears > n/2 times
       // DRY RUN: For [2, 2, 1, 1, 2, 2, 2] with majority=2
       //   Total 2s: 5 times
       //   n/2 = 7/2 = 3
       //   5 > 3? YES → Return 2
       for (int i = 0; i < n; i++) {
           // Count every occurrence of the candidate
           // WHY: We must verify the candidate actually appears >n/2 times
           // EDGE CASE: If no element appears >n/2 times, count will be ≤ n/2
           if (nums[i] == majority)
               count++;
       }
       
       // FINAL CHECK: Is candidate truly the majority?
       // WHY: Integer division n/2 ensures we check for STRICTLY MORE than half
       // EDGE CASE: In array [1, 2], no element appears >1 time, so return -1
       // Example: n=7, n/2=3, need count>3 (i.e., count≥4) for majority
       if (count > n / 2)
           return majority;      // Candidate is verified majority
       else
           return -1;            // No majority element exists
   }
};


int main() {
   // Test case 1: Majority element exists [2, 2, 1, 1, 2, 2, 2]
   // Majority: 2 (appears 5 times, 5 > 7/2 = 3)
   vector<int> nums = {2, 2, 1, 1, 2, 2, 2};

   // Create object and call the method
   Solution sol;
   int result = sol.majorityElement(nums);

   // Print result
   if (result != -1)
       cout << "Majority element is: " << result << endl;
   else
       cout << "No majority element found." << endl;

   return 0;
}


/*
╔════════════════════════════════════════════════════════════════════════════╗
║                 🧠 PROBLEM UNDERSTANDING                                  ║
╚════════════════════════════════════════════════════════════════════════════╝

📌 PROBLEM TYPE:
   • Frequency-based problem (which element appears most?)
   • Constraint-based problem (element appears > n/2 times)
   • Can be solved with multiple approaches (hash map, sorting, voting)

🔑 KEY CONSTRAINTS & CLUES:
   1. Majority element appears STRICTLY MORE than n/2 times
      → In [1,2,3,3,3]: majority=3 (3 times > 5/2=2.5, so >2.5 means ≥3)
   2. At most ONE element can be majority (can't have two elements each >n/2)
   3. If no element appears >n/2 times → return -1
   4. Array can be unsorted
   5. Elements can be negative, zero, positive

⚠️ CONSTRAINT THAT UNLOCKS OPTIMAL SOLUTION:
   → "More than n/2 times" means if you pair every majority element with 
     every non-majority element, majorities will outnumber non-majorities
   → This is the KEY insight for Boyer-Moore cancellation!


╔════════════════════════════════════════════════════════════════════════════╗
║                 🔍 PATTERN RECOGNITION                                    ║
╚════════════════════════════════════════════════════════════════════════════╝

🎯 PATTERN USED:
   • Boyer-Moore Voting Algorithm (also called Moore's Voting Algorithm)
   • Two-phase approach: Find candidate → Verify candidate

🔎 HOW TO RECOGNIZE THIS PATTERN:
   1. "Find majority element" (>n/2 times)
   2. "Find element that dominates" the array
   3. "Find the peak element in frequency"
   4. When you see "more than half" or ">n/2" or ">length/2"
   5. When a hash map solution works but seems "overkill"

💡 SIMILAR PROBLEMS:
   • Find single number (appear once, others twice) → XOR trick
   • Find k elements that appear >n/k times → Advanced Boyer-Moore
   • Find missing number → Math or XOR
   • Majority element in 2D matrix → Multiple voting passes


╔════════════════════════════════════════════════════════════════════════════╗
║              ⚡ APPROACH BREAKDOWN (Interview Style)                       ║
╚════════════════════════════════════════════════════════════════════════════╝

🔴 BRUTE FORCE: Count all frequencies (HashMap/Counting)
   • Algorithm:
     1. Use hash map to count each element's frequency
     2. Iterate hash map and find element with count > n/2
   • Time: O(n) - one pass to count, one pass through hash map
   • Space: O(n) - hash map stores all unique elements
   • DRAWBACK: Uses O(n) extra space

🟡 BETTER: Sort and check middle element
   • Algorithm:
     1. Sort the array
     2. After sorting, majority element MUST be at position n/2 (middle)
     3. Verify it's actually the majority
   • Why: If element appears >n/2 times, even in sorted array, it will cover middle
   • Time: O(n log n) - sorting dominates
   • Space: O(1) - if sorting is in-place
   • DRAWBACK: Slower than optimal due to sorting

🟢 OPTIMAL: Boyer-Moore Voting Algorithm (RECOMMENDED)
   • Algorithm:
     1. Phase 1: Find a candidate by canceling opposite votes
     2. Phase 2: Verify candidate is truly majority
   • Time: O(n) - two passes, no sorting
   • Space: O(1) - only using count and majority variables
   • WHY CHOSEN:
     ✓ Best time complexity (O(n))
     ✓ Best space complexity (O(1))
     ✓ Elegant logic based on mathematical property
     ✓ Shows advanced problem-solving thinking (favorite in interviews)


╔════════════════════════════════════════════════════════════════════════════╗
║                 🧩 INTUITION BUILDING                                      ║
╚════════════════════════════════════════════════════════════════════════════╝

💭 SIMPLE EXPLANATION:
   Imagine you have a voting room where people vote for candidates.
   When two different candidates meet, they CANCEL each other's vote.
   At the end, who's left standing?
   → The candidate who appears MORE than half the time will survive!

🎬 CONCRETE EXAMPLE:
   Array: [2, 2, 1, 1, 2, 2, 2]
   
   Voting process:
   • Start: Candidate = 2, Strength = 1
   • See 2: Strength = 2 (2 votes for candidate)
   • See 1: Strength = 1 (1 cancels with 2)
   • See 1: Strength = 0 (1 cancels again) → Replace candidate with 1
   • See 2: Strength = 0 (2 cancels with 1) → Replace candidate with 2
   • See 2: Strength = 1 (2 strengthens vote)
   • See 2: Strength = 2 (2 strengthens vote)
   
   Verification: Count 2s = 5, n/2 = 3, 5 > 3? YES → 2 is majority ✓

🎯 THE TRICK / INSIGHT:
   "If an element appears MORE than n/2 times, pairing it with all other
    different elements will still leave leftover majority elements."
   
   Mathematical insight:
   • If x appears > n/2 times, it appears more than (n - count_x) times
   • So when paired with all non-x elements, x has surplus
   • This surplus remains even after all cancellations

✨ WHY IT WORKS:
   Count acts as a "balance scale":
   • When you see majority element: scale tips towards it (count++)
   • When you see other element: scale tips towards other (count--)
   • But majority element is heavy enough to dominate in the end!


╔════════════════════════════════════════════════════════════════════════════╗
║                 🔁 HOW TO RECALL LATER                                     ║
╚════════════════════════════════════════════════════════════════════════════╝

🎯 MEMORY TRIGGER #1: "More than half" Pattern
   When you see: "find element that appears more than n/2 times"
   Think: "Boyer-Moore!" → Two phases: find then verify

🎯 MEMORY TRIGGER #2: The Cancellation Technique
   When you see: "cancel out" or "pair and eliminate"
   Think: "This might be voting algorithm" → Check if frequency >n/2

🎯 MEMORY TRIGGER #3: Space-Time Trade-off
   When you want: O(n) time with O(1) space (not hash map)
   Think: "I can't store everything, so I track strength instead"

📝 ONE-LINE MEMORY TRICK:
   "Majority element = the strongest candidate that survives voting cancellation"
   → Phase 1: Find it, Phase 2: Verify it

🔑 ESSENTIAL CHECKLIST:
   ☑ Phase 1: Find candidate (no verification)
   ☑ Phase 2: Verify candidate (count actual occurrences)
   ☑ Return -1 if no majority (EDGE CASE!)


╔════════════════════════════════════════════════════════════════════════════╗
║                 ⚠️ COMMON MISTAKES                                         ║
╚════════════════════════════════════════════════════════════════════════════╝

❌ MISTAKE 1: Skipping Phase 2 Verification
   ❌ WRONG: Return candidate after Phase 1
   ❌ WHY: Phase 1 finds A possible candidate, not THE majority
   ✅ CORRECT: Always verify in Phase 2
   
   Example: [1, 2, 3, 4, 5]
   • Phase 1 might give candidate=5, but 5 appears only 1 time (<5/2)
   • Without Phase 2, you'd return 5 (WRONG!)
   • With Phase 2, you return -1 (CORRECT!)

❌ MISTAKE 2: Forgetting to Reset Count in Phase 2
   ❌ WRONG: Use count from Phase 1 to verify
   ❌ WHY: count from Phase 1 is meaningless for verification
   ✅ CORRECT: Set count = 0 before Phase 2

❌ MISTAKE 3: Wrong Comparison for Majority (≥ vs >)
   ❌ WRONG: if (count >= n/2)
   ❌ WHY: Need STRICTLY MORE than n/2, not equal
   ✅ CORRECT: if (count > n/2)
   
   Example: n=4, n/2=2, you need count>2 (i.e., count≥3)

❌ MISTAKE 4: Not Handling Empty Array
   ❌ WRONG: Access nums[0] without checking if array is empty
   ✅ CORRECT: Add guard: if (n == 0) return -1;

❌ MISTAKE 5: Confusing "Majority" with "Plurality"
   ❌ WRONG: Thinking majority = most frequent element
   ❌ WHY: Majority has specific definition: > n/2
   ✅ CORRECT: Most frequent ≠ majority. Example: [1,1,2,2,3]
              1 and 2 are tied (most frequent) but neither is majority

❌ MISTAKE 6: Off-by-one in Loop
   ❌ WRONG: for (int i = 0; i < n; i++) in Phase 1
   ❌ WHY: We already initialized majority = nums[0], start from i=1
   ✅ CORRECT: for (int i = 1; i < n; i++) in Phase 1

❌ MISTAKE 7: Not Handling Negative Numbers
   ✅ CORRECT: Boyer-Moore works with ANY values (negative, zero, positive)
   Example: [-1, -1, -1, 0, 0] → majority = -1


╔════════════════════════════════════════════════════════════════════════════╗
║                 📊 COMPLEXITY ANALYSIS                                     ║
╚════════════════════════════════════════════════════════════════════════════╝

⏱️ TIME COMPLEXITY: O(n) + O(n) = O(n)
   • Phase 1: O(n) - single pass through array to find candidate
   • Phase 2: O(n) - single pass through array to count occurrences
   • Total: O(n) - linear time, which is OPTIMAL (must see all elements at least once)
   
   Why linear is optimal:
   • You must examine every element at least once to find majority
   • Impossible to do better than O(n)

💾 SPACE COMPLEXITY: O(1) - Constant Space
   • Variables used: n (size), count (frequency), majority (current candidate)
   • No hash map, no sorting, no recursive stack
   • Only 2-3 integer variables regardless of input size
   • This is OPTIMAL for this problem!

📊 COMPARISON TABLE:
   ┌─────────────────────┬──────────┬─────────────┬──────────────┐
   │ Approach            │ Time     │ Space       │ Best For     │
   ├─────────────────────┼──────────┼─────────────┼──────────────┤
   │ Hash Map            │ O(n)     │ O(n)        │ Unknown k    │
   │ Sorting             │ O(n log) │ O(1)*       │ Simple Logic │
   │ Boyer-Moore (Used)  │ O(n)     │ O(1) ✓      │ Interviews   │
   │ Binary Search Tree  │ O(n log) │ O(n)        │ Streaming    │
   └─────────────────────┴──────────┴─────────────┴──────────────┘
   * If in-place sorting is allowed

🎯 WHY BOYER-MOORE IS BEST:
   ✓ Time: Matches hash map O(n) but wins on space
   ✓ Space: Better than hash map O(n) and sorting input
   ✓ Elegance: Shows deep mathematical understanding
   ✓ Interview Appeal: Demonstrates advanced algorithmic thinking


╔════════════════════════════════════════════════════════════════════════════╗
║                 🔄 ALTERNATIVE APPROACHES                                  ║
╚════════════════════════════════════════════════════════════════════════════╝

🟠 ALTERNATIVE 1: Hash Map / Frequency Counter
   How it works:
   • Use unordered_map<int, int> to count each element
   • Iterate map and find element with count > n/2
   • Return that element or -1
   
   Pros: Easy to understand, generalizes to k-majority (>n/k)
   Cons: O(n) space, not optimal for single majority problem
   When to use: When you need to find k majority elements
   
   Code sketch:
   unordered_map<int, int> freq;
   for(auto x : nums) freq[x]++;
   for(auto& p : freq) {
       if(p.second > n/2) return p.first;
   }
   return -1;

🟠 ALTERNATIVE 2: Sorting Approach
   How it works:
   • Sort the array
   • After sort, majority element MUST be at index n/2
   • Verify by counting
   
   Why it works: If element appears >n/2 times, it must cover the middle!
   Mathematical proof:
   - In sorted array: all occurrences of element are consecutive
   - If element appears k times where k > n/2:
     - It occupies positions from some i to i+k-1
     - These positions MUST include position n/2
   
   Pros: Simple logic, works predictably
   Cons: O(n log n) time, destructive (modifies input)
   When to use: When simplicity matters more than time
   
   Code sketch:
   sort(nums.begin(), nums.end());
   int candidate = nums[n/2];
   int count = 0;
   for(auto x : nums) if(x == candidate) count++;
   return count > n/2 ? candidate : -1;

🟠 ALTERNATIVE 3: Random Pick Approach
   How it works:
   • Randomly pick an element from array
   • Count its frequency
   • If count > n/2, return it; else repeat
   • Probability: Each random pick has P(majority) > 0.5
   • Expected iterations: < 2
   
   Pros: Expected O(n) time, O(1) space
   Cons: Probabilistic (not deterministic), slower in practice
   When to use: Streaming data where you can't store all elements
   
   Code sketch:
   srand(time(0));
   while(true) {
       int candidate = nums[rand() % n];
       int count = 0;
       for(auto x : nums) if(x == candidate) count++;
       if(count > n/2) return candidate;
   }

🟠 ALTERNATIVE 4: Bit Manipulation (For advanced)
   How it works:
   • Process each bit position (0 to 31 for 32-bit integers)
   • For each bit: count how many numbers have that bit set
   • If count > n/2, that bit is set in majority element
   • Reconstruct majority element bit by bit
   
   Time: O(32 * n) = O(n), Space: O(1)
   
   Code sketch:
   int result = 0;
   for(int i = 0; i < 32; i++) {
       int count = 0;
       for(auto x : nums) {
           if((x >> i) & 1) count++;
       }
       if(count > n/2) {
           result |= (1 << i);
       }
   }
   return result;

📊 WHEN TO USE EACH:
   • Hash Map: Unknown frequency threshold, need k-majority
   • Sorting: Simple logic needed, input can be modified
   • Random: Streaming data, element arrives one-by-one
   • Bit Manipulation: Advanced problem, need practice
   • Boyer-Moore: Interview question, want to impress (DEFAULT CHOICE)


╔════════════════════════════════════════════════════════════════════════════╗
║                     🎓 FINAL TAKEAWAYS                                     ║
╚════════════════════════════════════════════════════════════════════════════╝

1️⃣ BIGGEST INSIGHT:
   "The 'more than n/2' constraint is MAGICAL. It means majority element
    survives ALL pairing/cancellation. This unlocks the O(n) O(1) solution."

2️⃣ INTERVIEW STRATEGY:
   • Start with hash map (safe, shows understanding)
   • Then mention sorting (simple optimization)
   • Finally reveal Boyer-Moore (wow factor!)
   • Bonus: Explain bit manipulation for extra points

3️⃣ PATTERN FOR SIMILAR PROBLEMS:
   • k majority elements (appears > n/k): Use modified Boyer-Moore
   • Single number (others appear twice): Use XOR
   • Frequency dominance: Think cancellation/pairing

4️⃣ KEY LINES TO REMEMBER:
   • count = 1, majority = nums[0] (initialization)
   • count--, if(count==0) majority=nums[i] (cancellation)
   • count = 0 (reset before verification) ← CRITICAL!
   • count > n/2 (STRICTLY greater, not equal)

5️⃣ TESTING CHECKLIST:
   ✓ [3, 2, 3] → expect 3
   ✓ [2, 2, 1, 1, 1, 2, 2] → expect 2
   ✓ [1] → expect 1
   ✓ [1, 2] → expect -1 (no majority)
   ✓ [2, 2, 2, 1, 1] → expect 2
   ✓ Negative numbers: [-1, -1, 0] → expect -1

╚════════════════════════════════════════════════════════════════════════════╝
*/
