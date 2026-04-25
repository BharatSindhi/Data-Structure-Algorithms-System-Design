// Problem Statement :



// You are given a 0-indexed 2D integer matrix of size n*n with values in the range [1, n²]. Each integer appears exactly once except a, which appears twice, and b, which is missing. The task is to find the repeating and missing numbers a and b, respectively.

// Return a 0-indexed integer array ‘ans’ of size 2, where ans[0] is equal to a and ans[1] is equal to b.



// Example 1:
// Input: grid = [[1, 3], [2, 2]]
// Output: [2,4]
// Explanation: Number 2 is repeated and number 4 is missing, so the answer is [2, 4].


// Example 2:
// Input: grid = [[9,1,7], [8,9,2], [3,4,6]]
// Output: [9,5]
// Explanation: Number 9 is repeated and number 5 is missing, so the answer is [9, 5].

// Approach
// Using Math-based Approach :



// By using math, we create two equations using the actual and expected sum and sum of squares. Solving these equations, we find the missing and repeating numbers.



// 1. Numbers in the matrix range from 1 to n². One number is repeating, and one number is missing.

// 2. Calculate:

//         expectedSum = n² * (n² + 1) / 2

//         expectedSquareSum = n² * (n² + 1) * (2n² + 1) / 6

// 3. Traverse the matrix to get

//         actualSum: Sum of all the numbers in a grid.

//         actualSquareSum: Sum of squares of all the numbers in a grid.

// 4. Let

//         diff = actualSum - expectedSum

//         diff = a - b

//         squareDiff = actualSquareSum - expectedSquareSum

//         squareDiff = a² - b²

// 5. Use:

//         squareDiff = a² - b² = (a+b)(a-b)

//         sum_ab = squareDiff / diff

//         = (a+b)(a-b)/(a-b)

//         = (a+b)



//       Solve:

//         a = (diff + sum_ab) / 2

//         b = (sum_ab - diff) / 2



// 6.    At the end we return [a, b]

// Time Complexity	Space Complexity
// O(n^2)	O(1)

#include <iostream>
#include<vector>
using namespace std;


class Solution {
public:
   vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
       // Initialize variables to store running sums from the grid
       // Using 'long long' to prevent integer overflow when calculating sums of large numbers
       long long actualSum = 0, actualSquareSum = 0;
       long long n = grid.size();  // n x n grid dimension
       long long N = n * n;        // Total number of elements in grid


       // STEP 1: Traverse the grid and calculate actual sum and sum of squares
       // Why? We need the real totals to compare with expected values
       // What breaks if removed? We'd have no actual data to work with - the entire solution fails
       // Example dry run: For grid [[1,2],[1,4]], actualSum = 1+2+1+4 = 8, actualSquareSum = 1+4+1+16 = 22
       for (int i = 0; i < n; ++i) {
           for (int j = 0; j < n; ++j) {
               int num = grid[i][j];
               actualSum += num;  // Add each element to get total sum
               actualSquareSum += (long long)num * num;  // Add square of each element
               // Note: Casting to long long prevents overflow before multiplication
           }
       }


       // STEP 2: Calculate expected sum if all numbers 1 to N² appeared exactly once
       // Formula: Sum of first n natural numbers = n * (n + 1) / 2
       // Why? This is the reference point - deviation from this reveals the missing/repeated numbers
       // What breaks if removed? We can't establish baseline to find differences
       // Example: For 2x2 grid (N=4), expectedSum = 4*5/2 = 10
       long long expectedSum = (N * (N + 1)) / 2;


       // STEP 3: Calculate expected sum of squares using the formula: Σ(k²) = n(n+1)(2n+1)/6
       // Why? This creates a second equation to solve for 2 unknowns (repeated and missing numbers)
       // What breaks if removed? We'd only have 1 equation (sum difference) but 2 unknowns - system unsolvable
       // Example: For N=4, expectedSquareSum = 4*5*9/6 = 30
       // Insight: Using two independent equations allows us to uniquely identify both 'a' and 'b'
       long long expectedSquareSum = (N * (N + 1) * (2 * N + 1)) / 6;


       // STEP 4: Calculate the difference between actual and expected sums
       // EQUATION 1: sumDifference = a - b (where 'a' is repeated, 'b' is missing)
       // Why? When we add all numbers: actualSum includes 'a' twice and lacks 'b' once
       // So: actualSum - expectedSum = a + a - b - 0 = 2a - (a+b) = a - b
       // What breaks if removed? We lose the first equation needed to solve the system
       // Example dry run: For [[1,2],[1,4]], actualSum=8, expectedSum=10, sumDifference = 8-10 = -2 = (1-3)
       long long sumDifference = actualSum - expectedSum;


       // STEP 5: Calculate difference between actual and expected sum of squares
       // EQUATION 2 (KEY INSIGHT): squareSumDifference = a² - b² = (a-b)(a+b)
       // Why? Similar logic: actualSquareSum includes a² twice and lacks b² once
       // So: actualSquareSum - expectedSquareSum = a² + a² - b² - 0 = 2a² - (a²+b²) = a² - b²
       // What breaks if removed? We lose the second equation - can't solve for 2 unknowns with 1 equation
       // This is the MATHEMATICAL TRICK: We use algebraic factorization a²-b² = (a-b)(a+b) to create:
       // (a+b) = squareSumDifference / (a-b)
       // Example dry run: For [[1,2],[1,4]], actualSquareSum=22, expectedSquareSum=30
       // squareSumDifference = 22-30 = -8 = (1²-3²) = (1-9) = -8 ✓
       long long squareSumDifference = actualSquareSum - expectedSquareSum;


       // STEP 6: Calculate sum_ab = a + b using the factorization
       // Mathematical derivation:
       // We have: a² - b² = (a-b)(a+b) = squareSumDifference
       // We know: (a-b) = sumDifference
       // Therefore: (a+b) = squareSumDifference / sumDifference
       // Why? This gives us the SECOND piece of information needed
       // Now we have TWO equations:
       //   (1) a - b = sumDifference
       //   (2) a + b = sum_ab
       // What breaks if removed? We can't calculate both 'a' and 'b'
       // Example: sum_ab = -8 / -2 = 4 = (1+3) ✓
       long long sum_ab = squareSumDifference / sumDifference;


       // STEP 7: Solve the system of 2 equations for 2 unknowns
       // System:
       //   (1) a - b = sumDifference
       //   (2) a + b = sum_ab
       // Adding both equations: 2a = (sum_ab + sumDifference), so a = (sum_ab + sumDifference) / 2
       // Subtracting (1) from (2): 2b = (sum_ab - sumDifference), so b = (sum_ab - sumDifference) / 2
       // Why this approach? Standard elimination method from linear algebra - guaranteed to work
       // What breaks if removed? We'd have no values for repeated and missing
       // Example dry run:
       // a = (4 + (-2)) / 2 = 2/2 = 1 ✓ (repeated number)
       // b = (4 - (-2)) / 2 = 6/2 = 3 ✓ (missing number)
       // Edge case handled: Integer division works fine here because sum_ab and sumDifference
       // have the same parity (both even or both odd) - mathematically guaranteed
       int repeated = (sum_ab + sumDifference) / 2;
       int missing = (sum_ab - sumDifference) / 2;


       // Return the results in required format: [repeated, missing] = [a, b]
       return {repeated, missing};
   }
};


int main() {
   // Example: 1 is repeated, 3 is missing
   vector<vector<int>> grid = {
       {1, 2},
       {1, 4}
   };


   Solution sol;
   vector<int> result = sol.findMissingAndRepeatedValues(grid);


   cout << "Repeated: " << result[0] << ", Missing: " << result[1] << endl;


   return 0;
}


/*
================================================================================
🧠 PROBLEM UNDERSTANDING
================================================================================

PROBLEM TYPE: Array Problem - Find Missing and Repeating Elements

KEY CONSTRAINTS & CLUES:
1. 2D grid (n×n) contains numbers from 1 to n²
2. Each number appears exactly once EXCEPT:
   - One number 'a' appears exactly TWICE
   - One number 'b' is MISSING (appears zero times)
3. Must find both 'a' (repeated) and 'b' (missing) simultaneously

CORE INSIGHT: This is not just about finding differences - it's about using TWO 
pieces of information (sum and sum of squares) to solve for TWO unknowns (a and b).


================================================================================
🔍 PATTERN RECOGNITION
================================================================================

DSA PATTERN: Mathematical/Algebraic Approach (specifically, System of Equations)

PATTERN RECOGNITION CLUES:
✓ Multiple unknowns to find (2 unknowns: repeated and missing)
✓ Need 2 independent equations (sum and sum of squares)
✓ Problem involves comparing actual vs. expected values
✓ Algebraic relationships hint at factorization (a² - b² = (a-b)(a+b))

HOW TO RECOGNIZE THIS PATTERN IN FUTURE:
- When you need to find "both missing AND repeating" elements → System of equations
- When one property (like sum) isn't enough → Create second property (sum of squares)
- When you see formulas like Σn or Σn² → Mathematical approach is likely optimal

SIMILAR PROBLEMS:
- Find duplicate in array (single element version)
- Find all missing numbers (multiple missing)
- Find first repeating element


================================================================================
⚡ APPROACH BREAKDOWN (Interview Style)
================================================================================

BRUTE FORCE (O(n²) space, but with extra memory):
-------
Use a HashSet/Map to track which numbers we've seen:
- Traverse grid and mark each number
- If we see it again → it's the repeated number
- After traversal, check which number 1 to n² is missing
Problem: Needs O(n²) extra space for the set

---

BETTER APPROACH (O(n) space with array):
-------
Use a frequency array of size n²+1:
- Count occurrences of each number
- Number with count = 2 is repeated
- Number with count = 0 is missing
Problem: Still needs O(n²) space - not truly "better"

---

OPTIMAL APPROACH (O(1) space) ✓ CHOSEN:
-------
Use mathematics with sum and sum of squares:

Why this is optimal:
1. No extra space beyond a few variables
2. Time complexity still O(n²) due to traversal, but this is minimum required
3. Clever use of algebra eliminates need for data structures
4. Shows interview readiness - demonstrates mathematical thinking

Mathematical elegance:
- We create 2 equations from 2 properties (sum, sum of squares)
- Solve system algebraically using factorization: a² - b² = (a-b)(a+b)
- Each operation is O(1)


================================================================================
🧩 INTUITION BUILDING
================================================================================

CORE IDEA IN SIMPLE TERMS:
"Imagine a ledger that should have entries 1 to n² each appearing once. 
When one number appears twice and another is missing, the ledger's 
TOTAL changes (sum difference). But also, the TOTAL OF SQUARES changes 
in a specific way we can exploit!"

THE TRICK / INSIGHT:
The KEY insight is factorization: a² - b² = (a - b)(a + b)

Why does this matter?
- We have ONE equation from sum: (a - b) = sumDifference
- We have another from squares: (a² - b²) = squareSumDifference
- But notice: (a² - b²) = (a-b) × (a+b)
- So: (a+b) = squareSumDifference / (a-b)
- Now we have TWO pieces: (a-b) and (a+b)
- Standard algebra solves it: a = ((a+b) + (a-b))/2, b = ((a+b) - (a-b))/2

MENTAL MODEL:
Think of it as a SYSTEM OF EQUATIONS:
  Equation 1: a - b = X     (from sum)
  Equation 2: a + b = Y     (derived from sum of squares)
  
  Add them: 2a = X + Y → a = (X+Y)/2
  Subtract: 2b = Y - X → b = (Y-X)/2


================================================================================
🔁 HOW TO RECALL LATER
================================================================================

2-3 KEY SIGNALS TO IDENTIFY THIS PROBLEM AGAIN:
1. "Find BOTH a repeating AND a missing number" (plural = multiple unknowns)
2. Can't use brute force due to space constraints (O(1) space required)
3. Numbers are from 1 to n² (specific range suggests mathematical approach)

ONE-LINE MEMORY TRICK:
"Sum gives a-b, sum-of-squares gives a+b, algebra solves both!"

FORMULA SHORTCUT:
If stuck, remember these two:
  • expectedSum = n(n+1)/2
  • expectedSquareSum = n(n+1)(2n+1)/6
  • Once you have differences, use: a = (sumDiff + sqDiff/sumDiff)/2


================================================================================
⚠️ COMMON MISTAKES
================================================================================

MISTAKE 1: Not using long long
❌ Using int causes integer overflow when calculating squares
✓ Use 'long long' for sum and sum of squares

MISTAKE 2: Forgetting why we need sum of squares
❌ Many beginners try to solve with just sum (only 1 equation for 2 unknowns)
✓ Must have 2 independent equations for 2 unknowns

MISTAKE 3: Getting confused with algebraic manipulation
❌ Trying to solve without understanding factorization a² - b² = (a-b)(a+b)
✓ Practice this factorization until it's second nature

MISTAKE 4: Not considering negative differences
❌ The repeated number might be smaller than missing (sumDifference can be negative)
✓ The algorithm handles this naturally; no special casing needed

MISTAKE 5: Integer division concerns
❌ Worrying that (sum_ab + sumDifference)/2 might not be integer
✓ Mathematically guaranteed to be integer (parity is same)

MISTAKE 6: Traversing grid multiple times
❌ Some optimize by calculating expected values first, then traversing
✓ The order doesn't matter - just makes sure you traverse exactly once


================================================================================
📊 COMPLEXITY ANALYSIS
================================================================================

TIME COMPLEXITY: O(n²)
┌─ Nested loop through entire grid: for(int i < n) for(int j < n)
│  └─ Each cell visited exactly once: n × n = n² operations
└─ All other operations (math): O(1)
   └─ Sum calculations, formula calculations: constant time

Total: O(n²)

SPACE COMPLEXITY: O(1) 
┌─ Only storing constant variables: actualSum, actualSquareSum, n, N, etc.
└─ No data structures that scale with input size
   └─ Not counting input grid (it's given)

Why not O(n) or O(n²)?
- We don't use HashSet (would be O(n²) space)
- We don't use array for frequency (would be O(n²) space)
- Only a handful of long/int variables


================================================================================
🔄 ALTERNATIVE APPROACHES
================================================================================

APPROACH 1: HashSet Method
- Use Set to store seen numbers
- Find duplicate when we encounter second occurrence
- After traversal, find missing from range [1, n²]
Time: O(n²), Space: O(n²) ❌ Extra space - not optimal

---

APPROACH 2: Frequency Array
- Create array freq[n²+1]
- Increment freq[num] for each grid element
- Find element with freq=2 (repeated) and freq=0 (missing)
Time: O(n²), Space: O(n²) ❌ Same issue - not optimal

---

APPROACH 3: Sorting + Comparison
- Flatten grid into array and sort
- Compare with expected sequence
- Find where the duplicate is and where gap is
Time: O(n² log n²) = O(n² log n) ❌ Slower due to sorting

---

APPROACH 4: XOR Method (for single missing/duplicate)
- XOR all numbers to eliminate duplicates
- XOR with 1 to n² range
- Works for simpler variants, but harder to adapt to this specific problem
Time: O(n²), Space: O(1) ✓ Could work, but less intuitive
Reason not chosen: Less general; mathematical approach teaches more

---

APPROACH 5: Mathematical (CHOSEN) ✓ BEST
- Use sum and sum of squares
- Derive system of equations
- Solve algebraically
Time: O(n²), Space: O(1) ✓✓✓ Optimal all around

Advantages:
✓ Minimal space usage
✓ No complex data structures
✓ Shows mathematical thinking
✓ Demonstrates understanding of algebra
✓ Scales perfectly
✓ Interview favorite


================================================================================
VISUAL DRY RUN EXAMPLE
================================================================================

Given grid: [[1, 2], [1, 4]]
Expected: [1, 2, 3, 4]
Actual: [1, 2, 1, 4]

Repeated = 1, Missing = 3

Step 1: Calculate sums
  actualSum = 1 + 2 + 1 + 4 = 8
  actualSquareSum = 1 + 4 + 1 + 16 = 22

Step 2: Calculate expected values
  n = 2, N = 4
  expectedSum = 4×5/2 = 10
  expectedSquareSum = 4×5×9/6 = 30

Step 3: Find differences
  sumDifference = 8 - 10 = -2        (this is a - b = 1 - 3 = -2) ✓
  squareSumDifference = 22 - 30 = -8 (this is a² - b² = 1 - 9 = -8) ✓

Step 4: Calculate sum_ab
  sum_ab = -8 / -2 = 4               (this is a + b = 1 + 3 = 4) ✓

Step 5: Solve for a and b
  a = (4 + (-2)) / 2 = 2/2 = 1       ✓ Repeated
  b = (4 - (-2)) / 2 = 6/2 = 3       ✓ Missing

Return: [1, 3]

================================================================================
*/ 




