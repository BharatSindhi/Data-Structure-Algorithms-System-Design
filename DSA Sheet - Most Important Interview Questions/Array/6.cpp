// Problem Statement :



// We are given two variables x and n. Implement pow(x, n), which calculates x raised to the power n (i.e., x^n)



// Example 1:
// Input: x = 2.00000, n = 10
// Output: 1024.00000


// Example 2:
// Input: x = 2.10000, n = 3
// Output: 9.26100


// Example 3:
// Input: x = 2.00000, n = -2
// Output: 0.25000
// Method Image 158

// Approach
// Exponentiation by Squaring Using Recursion :



// We need to compute x^n, and instead of multiplying x by itself n times, we break it down to smaller parts using the following approach:

// 1. Even Exponent (n is even) :

//     We can express x^n as (x^{n/2})^2. This reduces the problem to finding x^{n/2}, which we then square to get x^n.  

// 2. Odd Exponent (n is odd):

//     For odd n, we split it as x^n = x * x^{n-1}. Now, we can compute x^{n-1} as (x^{(n-1)/2})^2 and multiply by x.

//     By repeatedly halving the exponent, we drastically reduce the number of multiplications, making this approach much more efficient than directly multiplying x by itself n times.

// The base case is reached when n == 0 and returns 1.
// Negative Exponent: If n is negative, compute the result for -n and take the reciprocal.
// Divide and Conquer: Recursively compute x^(n/2). If n is even, square the result. If odd, multiply by x once more.
// Return: Reciprocal the result for negative n; otherwise, return the computed value.
// Time Complexity	Space Complexity
// O(logn) 	O(logn)



#include <iostream>
#include<vector>
using namespace std;



class Solution {
public:
   /* 
    * HELPER FUNCTION: Exponentiation by Squaring (Recursive)
    * 
    * Core Idea: Instead of multiplying x by itself n times (O(n) multiplications),
    * we use divide-and-conquer to reduce exponent by half each time.
    * 
    * Mathematical Insight:
    * - If n is even: x^n = (x^{n/2})^2
    * - If n is odd:  x^n = x * x^{n-1} = x * (x^{n/2})^2
    * 
    * Time Complexity: O(log n) - we divide n by 2 each recursive call
    * Space Complexity: O(log n) - recursion depth is log(n)
    * 
    * WHY THIS APPROACH?
    * - Brute force (multiply n times) = O(n) → Too slow for large n (e.g., n = 2^31 - 1)
    * - Squaring approach = O(log n) → Optimal ✓
    */
   double helper(double x, long long n) {
       // BASE CASE: Mathematical property - any number to power 0 is 1
       // This stops recursion and is the foundation for building up the answer
       // WHY NEEDED: Without this, recursion would never terminate
       if (n == 0) return 1;
       
       // RECURSIVE STEP: Divide problem into smaller subproblem
       // Calculate x^(n/2) recursively
       // Integer division automatically handles both even and odd cases
       // Example: n=10 → n/2=5, n=5 → n/2=2, n=2 → n/2=1, n=1 → n/2=0 (stops)
       double temp = helper(x, n / 2);
       
       // SQUARING: This is the "squaring" in exponentiation by squaring
       // For even exponent: x^n = (x^{n/2})^2, so we square temp
       // For odd exponent: temp contains x^{(n-1)/2}, squaring gives x^{n-1}
       // WHAT BREAKS WITHOUT THIS: We lose the multiplicative structure; result becomes x^{n/2} instead of x^n
       temp *= temp;
       
       // HANDLE ODD EXPONENT: If original exponent n was odd, multiply by x once more
       // Why? Because:
       // - If n is odd: x^n = x * x^{n-1}
       // - We computed x^{(n-1)/2} and squared it to get x^{n-1}
       // - So we need one extra multiplication by x
       // 
       // Example dry run: x=2, n=3
       // - helper(2, 3): temp = helper(2, 1) → temp *= temp (now 2^0 = 1 squared = 1)
       //   - Then n%2 == 1 (odd), so return 1 * 2 = 2
       // - Back in helper(2, 3): temp = 2, temp *= temp → temp = 4
       //   - Then n%2 == 1, so return 4 * 2 = 8 ✓ (which is 2^3)
       return (n % 2 == 0) ? temp : temp * x;
   }


   double myPow(double x, int n) {
       // CRITICAL: Convert to long long BEFORE taking absolute value
       // WHY? Integer n can be as low as -2^31 = -2147483648
       // abs(-2147483648) would overflow int range [-2^31, 2^31-1]
       // By converting to long long first, we safely handle the minimum int value
       // WHAT BREAKS: If we call abs(n) on int directly, integer overflow occurs → wrong result
       long long exp = abs((long long)n);
       
       // Call helper function to compute x^|n|
       // Helper uses divide-and-conquer to efficiently compute the power
       double result = helper(x, exp);
       
       // Handle negative exponent using reciprocal property:
       // x^(-n) = 1 / x^n
       // WHY NEEDED: We converted negative exponent to positive to handle overflow,
       // now we need to apply the mathematical transformation
       // WHAT BREAKS WITHOUT THIS: For negative n, we'd return x^|n| instead of 1/x^|n|
       // 
       // DRY RUN: x=2, n=-2
       // - exp = 2, result = helper(2, 2) = 4
       // - n < 0, so return 1.0/4 = 0.25 ✓ (which is 2^(-2))
       return (n < 0) ? 1.0 / result : result;
   }
};


int main() {
   Solution sol;
   double x = 2.0;   // Base of the exponentiation
   int n = 10;       // Exponent
   cout << sol.myPow(x, n) << endl; // Output: 1024 (which is 2^10)
   return 0;
}


/*
================================================================================
                    🧠 PROBLEM UNDERSTANDING
================================================================================

PROBLEM TYPE: Divide and Conquer / Exponentiation Algorithm

KEY CONSTRAINTS & CLUES:
  1. x: double precision float (can be positive, negative, or fractional)
  2. n: integer in range [-2^31, 2^31 - 1] (includes extreme negative values)
  3. Special cases:
     - x^0 = 1 (always, even if x=0)
     - Negative exponent: x^(-n) = 1/x^n
     - Negative base: (-2)^3 = -8 (odd power), (-2)^2 = 4 (even power)
  4. TRAP: abs(-2147483648) overflows int → Must convert to long long first

HIDDEN INSIGHT:
  The problem looks like "multiply x by itself n times", but that's a TRAP.
  Real challenge: How to do it efficiently when n can be 2 billion?


================================================================================
                    🔍 PATTERN RECOGNITION
================================================================================

PATTERN USED: Exponentiation by Squaring (Binary Exponentiation)

MATHEMATICAL FOUNDATION:
  x^n = {
    (x^{n/2})^2        if n is even
    x * (x^{n/2})^2    if n is odd
  }

RECOGNITION SIGNALS:
  1. Problem asks for x^n where n is LARGE (usually n > 10^6)
  2. Direct approach (multiply n times) would be O(n) → Too slow
  3. Answer requires LOGARITHMIC complexity hint
  4. Often combined with: recursion, modular arithmetic, matrix power

HOW TO RECOGNIZE IN FUTURE PROBLEMS:
  ✓ "Calculate power efficiently" → Exponentiation by Squaring
  ✓ "Compute (a^n) % MOD" → Exponentiation by Squaring + Modulo
  ✓ "Matrix^n" → Exponentiation by Squaring (on matrices)
  ✓ Any problem saying "n can be up to 10^9" with power involved → This pattern


================================================================================
                    ⚡ APPROACH BREAKDOWN (Interview Style)
================================================================================

APPROACH 1: BRUTE FORCE (❌ Wrong Answer on Large Test Cases)
  ─────────────────────────────────────────────────────────────
  Idea: Multiply x by itself n times
  
  double result = 1;
  for (int i = 0; i < n; i++) {
      result *= x;
  }
  return result;
  
  Time: O(n)
  Space: O(1)
  
  PROBLEM: If n = 2^31 - 1, we do 2 billion multiplications → TLE ❌


APPROACH 2: BETTER - Recursion Without Optimization (⚠️ Not Optimal)
  ─────────────────────────────────────────────────────────────────
  Idea: x^n = x * x^(n-1)
  
  if (n == 0) return 1;
  return x * helper(x, n-1);
  
  Time: O(n)
  Space: O(n) - recursion stack
  
  PROBLEM: Same as brute force! O(n) is still too slow


APPROACH 3: OPTIMAL ✓ (Exponentiation by Squaring)
  ─────────────────────────────────────────────────
  Idea: Use the binary structure of the exponent
  
  Observation: Instead of reducing exponent by 1, reduce by HALF
  - x^10 = (x^5)^2
  - x^5 = x * (x^2)^2 = x * x^4
  - x^4 = (x^2)^2
  - x^2 = (x^1)^2
  - x^1 = x * (x^0)^2 = x * 1 = x
  - x^0 = 1 (base case)
  
  See how we reduce 10 → 5 → 2 → 1 → 0 in just 4 steps (vs 10 steps in brute force)
  
  Time: O(log n) - Reduce exponent by half each time
  Space: O(log n) - Recursion depth
  
  WHY THIS ONE?
  ✓ Handles large n efficiently
  ✓ Uses divide-and-conquer structure
  ✓ Works with modular arithmetic (important for competitive programming)
  ✓ Can be converted to iterative (space: O(1)) if needed


================================================================================
                    🧩 INTUITION BUILDING
================================================================================

THE CORE IDEA (Simple Terms):
  ─────────────────────────────
  Instead of multiplying x by itself one at a time (like stacking 10 books),
  we're SMART about it:
  
  For x^10:
    NAIVE: x * x * x * x * x * x * x * x * x * x (10 multiplications)
    SMART: (((x^2)^2)^2) * x (4 multiplications + smart reuse)
  
  The KEY is recognizing that:
    - x^even = (x^{half})^2
    - x^odd = x * (x^{half-1})^2


THE "TRICK" OR INSIGHT:
  ─────────────────────
  When n is even: We can square the half-power
  When n is odd: We multiply by x and then square the half-power
  
  This way, we turn O(n) multiplications into O(log n) multiplications!
  
  EXAMPLE:
    2^10 = (2^5)^2 = (2 * 2^4)^2 = (2 * (2^2)^2)^2 = ... ✓
    
  How many steps? Count the halvings: 10 → 5 → 2 → 1 → 0 = log2(10) ≈ 4 steps


WHY DOES SQUARING WORK?
  ────────────────────
  Mathematical property: (a^b)^c = a^(b*c)
  
  So if we compute x^(n/2) and square it:
    (x^{n/2})^2 = x^(n/2 * 2) = x^n ✓


================================================================================
                    🔁 HOW TO RECALL LATER
================================================================================

3 KEY SIGNALS TO IDENTIFY THIS PROBLEM:
  1. "Calculate x^n" where n is LARGE (> 10^6)
  2. Time limit is strict (O(n) won't pass)
  3. Exponent n involves NEGATIVE values or overflow concerns

ONE-LINE MEMORY TRICK:
  ─────────────────────
  "Power is about HALVING the exponent, not multiplying x"
  
  Or: "Binary structure of exponent → log(n) complexity"
  
  Visual: Each level of recursion squares the previous result
  
  Recursion tree for x^10:
       helper(x, 10)
           ↓
       helper(x, 5)
           ↓
       helper(x, 2)
           ↓
       helper(x, 1)
           ↓
       helper(x, 0) → returns 1


================================================================================
                    ⚠️ COMMON MISTAKES
================================================================================

MISTAKE 1: Using abs(n) directly on int
  ─────────────────────────────────────
  long long exp = abs(n);  // ❌ WRONG
  
  WHY IT FAILS:
    - n can be -2147483648 (most negative 32-bit int)
    - abs(-2147483648) overflows int range
    - Result is undefined behavior or -2147483648 again (most systems)
  
  FIX:
    long long exp = abs((long long)n);  // ✓ CORRECT
    - Convert to long long FIRST, then take abs
    - long long range is large enough to hold the absolute value


MISTAKE 2: Forgetting the base case (n == 0)
  ────────────────────────────────────────
  Forgetting: if (n == 0) return 1;
  
  WHY IT FAILS:
    - Recursion never stops
    - Stack overflow
    - Infinite recursion
  
  Also, mathematically x^0 = 1 for ANY x (except 0^0 edge case, but n=0 here)


MISTAKE 3: Not handling negative exponent correctly
  ──────────────────────────────────────────────────
  Forgetting: return (n < 0) ? 1.0 / result : result;
  
  WHY IT FAILS:
    - myPow(2, -2) would return 4 instead of 0.25
    - Mathematical definition: x^(-n) = 1/x^n
  
  Example:
    myPow(2, -2):
      Without reciprocal: returns 2^2 = 4 ❌
      With reciprocal: returns 1/4 = 0.25 ✓


MISTAKE 4: Forgetting to handle odd exponent in helper
  ────────────────────────────────────────────────────
  Wrong:
    return temp;  // Missing: n%2 == 0 check
  
  WHY IT FAILS:
    myPow(2, 3):
      - helper(2, 3) calls helper(2, 1) → temp = 1
      - temp *= temp → temp = 1
      - return temp (missing n%2 check) ❌ Returns 1 instead of 2
      - Should return temp * x = 1 * 2 = 2 ✓
  
  The odd exponent handling is CRITICAL


MISTAKE 5: Integer overflow with n
  ────────────────────────────────
  int exp = n;  // ❌ For n = -2^31, this is dangerous
  
  WHY IT FAILS:
    - Although -2^31 fits in int, operations on it can overflow
    - Better practice: use long long throughout


================================================================================
                    📊 COMPLEXITY ANALYSIS
================================================================================

TIME COMPLEXITY: O(log n)
  ────────────────────────
  REASONING:
    - Each recursive call reduces n by half (n → n/2 → n/4 → ... → 1 → 0)
    - Number of halvings until reaching 0 = log₂(n)
    - At each level: O(1) work (one multiplication, one squaring, one check)
    - Total: log₂(n) levels × O(1) work = O(log n)
  
  EXAMPLE: n = 10
    10 → 5 → 2 → 1 → 0 (4 steps, and log₂(10) ≈ 3.32)
    Each step involves one squaring and possibly one multiplication


SPACE COMPLEXITY: O(log n)
  ────────────────────────
  REASONING:
    - Recursion depth = number of times we can halve n
    - Maximum recursion depth = log₂(n)
    - Each recursive call uses constant space (one temp variable, function parameters)
    - Total stack space = log₂(n) levels × O(1) per level = O(log n)
  
  EXAMPLE: n = 10
    Call stack depth: helper(x,10) → helper(x,5) → helper(x,2) → helper(x,1) → helper(x,0)
    That's 5 frames = log₂(10) rounded up


DETAILED BREAKDOWN:

  Operation          Count           Complexity
  ─────────────────────────────────────────────
  Recursive calls    log(n)          Each halves n
  Multiplications    ≤ 2*log(n)      1-2 per level
  Comparisons        log(n)          n%2 checks
  ─────────────────────────────────────────────
  Total Time         O(log n)


================================================================================
                    🔄 ALTERNATIVE APPROACHES
================================================================================

ALTERNATIVE 1: Iterative Exponentiation by Squaring (Binary Lifting)
  ──────────────────────────────────────────────────────────────────
  
  IDEA:
    Instead of recursion, use a loop and process exponent bits from LSB to MSB
    
  COMPLEXITY:
    Time: O(log n)
    Space: O(1) - NO recursion stack! ✓
  
  HOW IT WORKS:
    Process binary representation of n
    Example: n = 10 = 1010₂
    
    Start: result = 1, base = x
    - Bit 0 (rightmost) = 0: Don't multiply, base = base²
    - Bit 1 = 1: Multiply, result *= base, base = base²
    - Bit 2 = 0: Don't multiply, base = base²
    - Bit 3 = 1: Multiply, result *= base
    
  ADVANTAGE OVER RECURSIVE:
    ✓ Space: O(log n) → O(1) (no call stack)
    ✓ Faster in practice (no function call overhead)
    ✓ Better for systems with limited stack memory
  
  DISADVANTAGE:
    ✗ Slightly harder to understand and implement
    ✗ More error-prone with bit manipulation


ALTERNATIVE 2: Memoization (Only useful if computing multiple powers)
  ────────────────────────────────────────────────────────────────────
  
  IDEA:
    Cache results of helper(x, n) to avoid recalculation
    
  WHEN TO USE:
    If you're computing power(x, n) MULTIPLE times with same x and different n
    Not beneficial for single call
  
  COMPLEXITY:
    Time: O(log n) for first call, then cached results
    Space: O(log n) - cache size


ALTERNATIVE 3: Mathematics - Using Logarithms
  ────────────────────────────────────────────
  
  IDEA:
    x^n = e^(n * ln(x))
  
  PROBLEM:
    ✗ Floating-point precision errors
    ✗ Cannot handle negative base correctly
    ✗ Not suitable for exact results
    ✗ Bad for competitive programming
  
  CONCLUSION: Avoid for interview


WHY EXPONENTIATION BY SQUARING IS BEST FOR THIS PROBLEM:
  1. O(log n) time - Fast enough for large n
  2. O(log n) space - Acceptable in most systems
  3. Clean and elegant
  4. Mathematically correct
  5. Handles all edge cases naturally
  6. Extends well to matrix power, modular arithmetic, etc.


================================================================================
                    DRY RUN EXAMPLES
================================================================================

EXAMPLE 1: x = 2.0, n = 10
  ──────────────────────────
  myPow(2.0, 10):
    exp = 10
    result = helper(2.0, 10)
    
    helper(2.0, 10):
      n = 10 (even)
      temp = helper(2.0, 5)
      
      helper(2.0, 5):
        n = 5 (odd)
        temp = helper(2.0, 2)
        
        helper(2.0, 2):
          n = 2 (even)
          temp = helper(2.0, 1)
          
          helper(2.0, 1):
            n = 1 (odd)
            temp = helper(2.0, 0)
            
            helper(2.0, 0):
              BASE CASE: return 1
            
            temp = 1
            temp *= temp → temp = 1
            n % 2 = 1 (odd), return 1 * 2 = 2
          
          temp = 2
          temp *= temp → temp = 4
          n % 2 = 0 (even), return 4
        
        temp = 4
        temp *= temp → temp = 16
        n % 2 = 1 (odd), return 16 * 2 = 32
      
      temp = 32
      temp *= temp → temp = 1024
      n % 2 = 0 (even), return 1024
    
    result = 1024
    n >= 0, return 1024 ✓


EXAMPLE 2: x = 2.0, n = -2
  ──────────────────────────
  myPow(2.0, -2):
    exp = abs(-2) = 2
    result = helper(2.0, 2)
    
    helper(2.0, 2):
      n = 2 (even)
      temp = helper(2.0, 1)
      
      helper(2.0, 1):
        n = 1 (odd)
        temp = helper(2.0, 0) = 1
        temp *= temp → 1
        return 1 * 2 = 2
      
      temp = 2
      temp *= temp → 4
      return 4
    
    result = 4
    n < 0, return 1.0 / 4 = 0.25 ✓


EXAMPLE 3: x = 0.5, n = 3
  ────────────────────────
  myPow(0.5, 3):
    exp = 3
    result = helper(0.5, 3)
    
    helper(0.5, 3):
      n = 3 (odd)
      temp = helper(0.5, 1)
      
      helper(0.5, 1):
        n = 1 (odd)
        temp = helper(0.5, 0) = 1
        temp *= temp → 1
        return 1 * 0.5 = 0.5
      
      temp = 0.5
      temp *= temp → 0.25
      return 0.25 * 0.5 = 0.125
    
    result = 0.125
    n >= 0, return 0.125 ✓ (which is 0.5^3)


================================================================================
                    EDGE CASES HANDLED
================================================================================

1. x^0:
   - Input: any x, n = 0
   - Base case returns 1 ✓
   - Correct even for x = 0 (0^0 = 1 by convention in most systems)

2. Negative Exponent:
   - Input: x = 2, n = -3
   - abs converts to positive, then 1/result ✓

3. Negative Base:
   - Input: x = -2, n = 3
   - Multiplications handle sign correctly ✓

4. Fractional Base:
   - Input: x = 0.5, n = 10
   - Floating-point multiplications work correctly ✓

5. Extreme Negative Exponent:
   - Input: x = 2, n = -2147483648
   - Conversion to long long prevents overflow ✓

6. Base = 1:
   - Input: x = 1, n = anything
   - Result is always 1 (which is correct) ✓

7. Base = 0 (except n = 0):
   - Input: x = 0, n = 5
   - Result is 0 (all multiplications by 0) ✓

8. Base = -1:
   - Input: x = -1, n = 4
   - Result is 1 ✓
   - Input: x = -1, n = 5
   - Result is -1 ✓


================================================================================
                    INTERVIEW TALKING POINTS
================================================================================

When explaining this solution:

1. START WITH THE PROBLEM:
   "We need to compute x^n efficiently, where n can be up to 2 billion"
   
2. IDENTIFY THE NAIVE APPROACH:
   "The obvious approach is to multiply x by itself n times, but that's O(n) - 
   too slow for large n"
   
3. INTRODUCE THE KEY INSIGHT:
   "We can use the mathematical property: x^n = (x^{n/2})^2
    This allows us to reduce the exponent exponentially (by half each time)"
   
4. EXPLAIN THE STRATEGY:
   "We recursively compute half the power and square it. 
    For odd exponents, we multiply by x one additional time"
   
5. HIGHLIGHT THE IMPLEMENTATION DETAILS:
   "Converting n to long long before abs() is critical to avoid overflow"
   "For negative exponents, we take the reciprocal of the result"
   
6. STATE THE COMPLEXITY:
   "Time: O(log n) - we halve the exponent each level
    Space: O(log n) - recursion depth"
   
7. MENTION ALTERNATIVES:
   "This can also be done iteratively using bit manipulation for O(1) space"
================================================================================
*/
