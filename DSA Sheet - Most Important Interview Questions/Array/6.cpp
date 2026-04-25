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
   // Helper function for exponentiation by squaring
   double helper(double x, long long n) {
       if (n == 0) return 1; // Base case: x^0 = 1
       double temp = helper(x, n / 2); // Recursively calculate x^(n/2)
       temp *= temp; // Square the result
       return (n % 2 == 0) ? temp : temp * x; // If odd exponent, multiply by x once more
   }


   double myPow(double x, int n) {
       long long exp = abs((long long)n); // Handle negative exponent safely
       double result = helper(x, exp); // Get power using helper
       return (n < 0) ? 1.0 / result : result; // If exponent was negative, return reciprocal
   }
};


int main() {
   Solution sol;
   double x = 2.0;   // Dummy input: base
   int n = 10;       // Dummy input: exponent
   cout << sol.myPow(x, n) << endl; // Output: 1024
   return 0;
}
