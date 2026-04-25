#include <iostream>
#include <climits>  // for INT_MAX and INT_MIN
using namespace std;

class Solution {
public:
    int reverse(int x) {
        int revNum = 0;
        while (x != 0) {
            int digit = x % 10;

            // Check for overflow before multiplying by 10
            if (revNum > INT_MAX / 10 || revNum < INT_MIN / 10) {
                return 0;
            }

            revNum = revNum * 10 + digit;
            x = x / 10;
        }
        return revNum;
    }
};

int main() {
    Solution sol;
    int x;

    cout << "Enter an integer: ";
    cin >> x;

    int result = sol.reverse(x);
    cout << "Reversed integer: " << result << endl;

    return 0;
}
