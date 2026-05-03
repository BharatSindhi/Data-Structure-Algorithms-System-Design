#include <iostream>
using namespace std;


/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int st = 1;
        int end = n;

        while (st <= end) {
            int mid = st + (end - st) / 2;

            int res = guess(mid);

            if (res == 0) {
                return mid;   // correct answer
            }
            else if (res == -1) {
                end = mid - 1;   // go left
            }
            else {
                st = mid + 1;    // go right
            }
        }
        return -1; // should never reach here
    }
};

int main() {
    
    return 0;
}
