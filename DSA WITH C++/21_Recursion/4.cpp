#include <iostream>
using namespace std;

class Solution {
public:
    // Naive recursive approach (O(2^n))
    int fibRecursive(int n) {
        if (n == 0 || n == 1) {
            return n;
        }
        return fibRecursive(n - 1) + fibRecursive(n - 2);
    }

    // Iterative DP approach (O(n), O(1) space)
    int fibIterative(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;

        int prev2 = 0, prev1 = 1, curr;
        for (int i = 2; i <= n; i++) {
            curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};

int main() {
    Solution sol;
    int n;

    cout << "Enter n: ";
    cin >> n;

    cout << "Fibonacci using Recursion: " << sol.fibRecursive(n) << endl;
    cout << "Fibonacci using Iteration (DP): " << sol.fibIterative(n) << endl;

    return 0;
}
