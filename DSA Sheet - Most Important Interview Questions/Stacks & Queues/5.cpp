// Headers needed for this solution:
// - iostream: used by main / standard input-output utilities.
// - unordered_map: stores frequency of each character in average O(1) time.
// - queue: stores indices of characters that were unique when first seen.
// If unordered_map is removed, we cannot know whether a character became repeated.
// If queue is removed, we lose the order of possible first-unique candidates.
#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
public:
    // Problem: return the index of the first non-repeating character in string s.
    //
    // Example dry run target:
    // s = "leetcode"
    // Expected answer = 0, because 'l' appears once and is the earliest unique char.
    //
    // High-level idea:
    // 1. Count how many times every character appears while scanning left to right.
    // 2. Push an index into the queue when its character is seen for the first time.
    // 3. Keep removing queue front indices whose characters are no longer unique.
    //
    // Why queue?
    // The first unique character must be the earliest valid candidate, and queues
    // naturally preserve first-in-first-out order.
    int firstUniqChar(string s) {
        // m[ch] = frequency of character ch seen so far.
        // This is necessary because uniqueness depends on count, not just position.
        // If removed, the code cannot tell whether q.front() is still unique later.
        // Edge note: unordered_map works for any char values present in the string.
        // Space: O(k), where k is the number of distinct characters in s.
        unordered_map<char, int> m;

        // q stores indices of characters that were unique at the moment they were added.
        // Some indices may become invalid later if the same character appears again.
        // The while loop below lazily removes those invalid indices.
        // If this queue is removed, we would need another scan to find the earliest
        // unique character.
        // Space: O(n) in the worst case, when all characters are initially unique.
        queue<int> q;

        // Scan every character once from left to right.
        // Why left to right? Because the answer asks for the first unique character,
        // so order matters.
        // If this loop is removed, no frequencies or candidates are built.
        // Time: O(n) total for the loop body plus amortized queue cleanup.
        for (int i = 0; i < s.size(); i++) {
            // Increase the frequency of the current character.
            //
            // Dry run for s = "leetcode":
            // i=0, s[i]='l' -> m['l'] becomes 1
            // i=1, s[i]='e' -> m['e'] becomes 1
            // i=2, s[i]='e' -> m['e'] becomes 2
            //
            // Why needed?
            // This line is what detects whether a character is unique or repeated.
            //
            // If removed:
            // m[s[i]] would stay 0, no character would be recognized correctly,
            // and repeated characters could be returned as unique.
            m[s[i]]++;

            // If this is the first time we have seen s[i], it is a possible answer.
            // We push its index, not the character, because the problem asks for index.
            //
            // Dry run for "leetcode":
            // i=0 ('l'): count is 1 -> push 0, q = [0]
            // i=1 ('e'): count is 1 -> push 1, q = [0, 1]
            // i=2 ('e'): count is 2 -> do not push, because 'e' is not unique anymore
            //
            // If this block is removed:
            // q stays empty, and the function will always return -1.
            //
            // Edge handled:
            // Repeated characters are not pushed again after their first occurrence.
            if (m[s[i]] == 1) {
                q.push(i);
            }

            // Remove invalid candidates from the front of the queue.
            //
            // Important idea:
            // q may contain old indices whose characters were unique earlier but
            // became repeated later. Only the front matters for "first" unique.
            //
            // Condition breakdown:
            // !q.empty()       -> prevents accessing q.front() when queue has no items.
            // m[s[q.front()]] > 1 -> front character is repeated, so it cannot be answer.
            //
            // Dry run for "leetcode":
            // After i=2 ('e'), q = [0, 1].
            // q.front() = 0 -> s[0] = 'l', m['l'] = 1, so do not pop.
            // 'e' at index 1 is invalid, but it is behind 'l', so it does not matter yet.
            //
            // Dry run for "aabb":
            // i=0: 'a' count 1, q=[0], front 'a' unique
            // i=1: 'a' count 2, q=[0], front 'a' repeated -> pop, q=[]
            // i=2: 'b' count 1, q=[2], front 'b' unique
            // i=3: 'b' count 2, q=[2], front 'b' repeated -> pop, q=[]
            //
            // If this while loop is removed:
            // The queue front could point to a repeated character, causing a wrong answer.
            // Example: s = "aabb" would return 0 instead of -1.
            //
            // Why while, not if?
            // Multiple old front candidates may have become invalid, so we keep popping
            // until the front is either unique or the queue becomes empty.
            //
            // Amortized complexity:
            // Each index is pushed once and popped at most once, so total queue work is O(n).
            while (!q.empty() && m[s[q.front()]] > 1) {
                q.pop();
            }
        }

        // After the scan:
        // - If q is empty, every candidate became repeated, so no unique character exists.
        // - Otherwise, q.front() is the earliest index whose character frequency is 1.
        //
        // Dry run:
        // s = "leetcode" -> q.front() is 0 -> return 0.
        // s = "loveleetcode" -> final q.front() is 2 -> return 2 ('v').
        // s = "aabb" -> q is empty -> return -1.
        // s = "" -> loop never runs, q is empty -> return -1.
        //
        // If this line is changed incorrectly:
        // Returning q.front() without checking empty would crash/undefined behavior
        // for strings with no unique character or for an empty string.
        return q.empty() ? -1 : q.front();
    }
};
int main() {
    // Empty main because this file currently defines the solution class only.
    // Removing main may be fine on online judges that instantiate Solution directly,
    // but in a standalone C++ file, a main function is needed for linking.
    
    return 0;
}

/*
### 1. 🧠 Problem Understanding

This is a string + ordering problem.
Given a string, find the index of the first character that appears exactly once.

Key constraints/clues:
- "First" means order matters.
- "Non-repeating" means frequency matters.
- We need the index, so storing positions is useful.
- Empty string or all repeated characters should return -1.

Small example:
s = "loveleetcode"
Frequencies:
l -> 2, o -> 2, v -> 1, e -> 4, t -> 1, c -> 1, d -> 1
The first unique character from left to right is 'v' at index 2.

### 2. 🔍 Pattern Recognition

Pattern used: Hash Map + Queue.

How to recognize it:
- You need frequency/count information -> think hash map.
- You need the earliest valid item after updates -> think queue.
- Some earlier candidates can become invalid later -> use lazy deletion from queue front.

This pattern often appears in:
- First non-repeating character in a stream.
- Maintaining first valid candidate while processing data left to right.
- Problems where old candidates expire or become invalid.

### 3. ⚡ Approach Breakdown (Interview Style)

Brute force idea:
- For every character, scan the whole string to count how many times it appears.
- Return the first index whose count is 1.
- Time: O(n^2), Space: O(1).
- Problem: too slow for large strings.

Better approach:
- First pass: count frequencies of all characters.
- Second pass: return first index with frequency 1.
- Time: O(n), Space: O(k).
- This is simple and often best for a fixed complete string.

Optimal approach used here:
- Process the string once.
- Keep counts in unordered_map.
- Keep possible first-unique indices in a queue.
- Remove repeated candidates from the queue front as soon as they become invalid.
- Time: O(n), Space: O(n).
- This approach is especially useful if characters arrive like a stream.

### 4. 🧩 Intuition Building

Think of the queue as a waiting line of characters that are "still hoping" to be
the first unique character.

When a character appears for the first time, it joins the line.
When a character appears again, it loses eligibility.
The front of the line is always checked because only the earliest candidate can
be the answer.

The trick:
Do not try to clean the whole queue every time.
Only clean from the front, because later invalid candidates do not matter until
they reach the front.

### 5. 🔁 How to Recall Later

Signals:
- Need "first" valid item.
- Validity can change after later input.
- Need counts/frequencies.

Memory trick:
"Count with map, preserve order with queue, pop until front is honest."

### 6. ⚠️ Common Mistakes

- Returning the first character that appears once during the scan without checking
  whether it repeats later.
- Forgetting to check q.empty() before q.front().
- Using if instead of while when removing invalid front candidates.
- Pushing repeated characters into the queue again.
- Returning the character instead of its index.
- Assuming queue only contains valid indices; it may contain stale candidates behind
  the current front.

### 7. 📊 Complexity Analysis

Time Complexity: O(n)
- The for loop visits every character once.
- Each index is pushed into the queue at most once.
- Each index is popped from the queue at most once.
- unordered_map operations are average O(1).

Space Complexity: O(n)
- The queue can store up to n indices if all characters are unique while scanning.
- The unordered_map stores up to k distinct characters, where k <= n.
- Overall space is O(n).

### 8. 🔄 Alternative Approaches

1. Two-pass frequency array/map:
   Count all characters first, then scan again to find the first frequency-1
   character. This is simpler for normal string input and also O(n).

2. Fixed-size array instead of unordered_map:
   If the input is guaranteed to be lowercase English letters, use an array of
   size 26. This reduces overhead and keeps space O(1).

3. Store first index and count together:
   Track each character's count and first index, then find the minimum first index
   among characters with count 1. Useful when character set is limited.

4. Pure queue stream solution:
   If characters arrive one by one and you must report the first unique character
   after each arrival, this exact map + queue approach is a strong fit.
*/
