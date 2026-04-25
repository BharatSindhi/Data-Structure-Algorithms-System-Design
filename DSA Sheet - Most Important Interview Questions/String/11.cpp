// 🔹 What is Rabin–Karp?

// The Rabin–Karp algorithm is used to search for a pattern string (P) inside a text string (T).

// 👉 Instead of comparing characters one by one every time, it:

// Converts strings into hash values
// Compares hash values first (fast)
// Only if hashes match → does actual string comparison
// 🔹 Idea (Core Concept)
// Calculate hash of pattern P
// Take first window of text (same length as P), calculate hash
// Slide window one step at a time:
// Recalculate hash using rolling hash
// If hash matches → check characters
// 🔹 Why is it efficient?

// Because:

// Hash comparison is O(1)
// Avoids unnecessary character comparisons
// 🔹 Rolling Hash Concept

// Instead of recalculating hash every time:

// New Hash
// =
// (
// Old Hash
// −
// leading char
// )
// ×
// 𝑏
// 𝑎
// 𝑠
// 𝑒
// +
// new char
// New Hash=(Old Hash−leading char)×base+new char

// This makes sliding window fast 🚀

// 🔹 Example

// Text = "ABCCDDAEFG"
// Pattern = "CDD"

// Steps:
// Hash("CDD") → compute
// Compare with "ABC" → no match
// Slide → "BCC" → no match
// Slide → "CCD" → no match
// Slide → "CDD" → hash match ✅ → verify → FOUND
// 🔹 Algorithm Steps
// Compute hash of pattern
// Compute hash of first window of text
// Loop through text:
// Compare hash
// If equal → verify characters
// Update hash using rolling hash
// 🔹 C++ Implementation (Interview Ready)


#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<int> rabinKarp(string text, string pattern) {
        int n = text.size();
        int m = pattern.size();
        
        const int base = 256;   // number of characters
        const int mod = 1e9 + 7;
        
        long long patternHash = 0, textHash = 0;
        long long power = 1;
        
        // Calculate power = base^(m-1)
        for (int i = 0; i < m - 1; i++)
            power = (power * base) % mod;
        
        // Initial hash values
        for (int i = 0; i < m; i++) {
            patternHash = (patternHash * base + pattern[i]) % mod;
            textHash = (textHash * base + text[i]) % mod;
        }
        
        vector<int> result;
        
        for (int i = 0; i <= n - m; i++) {
            // Check hash match
            if (patternHash == textHash) {
                // Verify characters
                if (text.substr(i, m) == pattern)
                    result.push_back(i);
            }
            
            // Rolling hash update
            if (i < n - m) {
                textHash = (textHash - text[i] * power % mod + mod) % mod;
                textHash = (textHash * base + text[i + m]) % mod;
            }
        }
        
        return result;
    }
};

// 🔹 Time Complexity
// Case	Complexity
// Best Case	O(n + m)
// Average	O(n + m)
// Worst Case	O(n × m) (hash collisions)
// 🔹 When to Use?

// Use Rabin-Karp when:

// Multiple pattern matching
// Plagiarism detection
// DNA sequence matching
// String search in large data
// 🔹 Key Insight (Important for Interviews)

// 👉 “We compare hashes first, not strings”

// 👉 “Rolling hash avoids recomputation”

// 👉 “Collision possible → so verify”

// 🔹 Comparison with Other Algorithms
// Algorithm	Idea
// Brute Force	Compare all substrings
// KMP	Use LPS (pattern preprocessing)
// Rabin-Karp	Use hashing
// 🔹 Simple Intuition

// Think like:

// “Instead of checking full strings every time, I compare their fingerprints (hash).”