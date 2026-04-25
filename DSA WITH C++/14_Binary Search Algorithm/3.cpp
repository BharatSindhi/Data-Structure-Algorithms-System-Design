#include <iostream>
using namespace std;

// Mock of the guess API for local testing
// Change `picked_number` to simulate the system's chosen number.
int picked_number = 42;
int guess(int num) {
    if (num > picked_number) return -1;
    if (num < picked_number) return 1;
    return 0;
}

// Solution class using binary search
class Solution {
public:
    int guessNumber(int n) {
        int first = 1, last = n;
        while (first <= last) {
            int mid = first + (last - first) / 2;
            int res = guess(mid);
            if (res == 0)
                return mid;
            else if (res == -1)
                last = mid - 1;
            else
                first = mid + 1;
        }
        return -1; // This line will never be reached if input is valid
    }
};

// Driver code for testing
int main() {
    Solution sol;
    int n = 100;
    cout << "Picked Number: " << sol.guessNumber(n) << endl;
    return 0;
}
