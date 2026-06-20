#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int res = 0;     // number of jumps
        int l = 0;       // left boundary of the current jump range
        int r = 0;       // right boundary (farthest we can reach in current jump)

        while (r < nums.size() - 1) {  // stop when we can reach or exceed the last index
            int farthest = 0;

            // Explore all indices within the current jump range [l, r]
            for (int i = l; i <= r; i++) {
                farthest = max(farthest, i + nums[i]);
            }

            // Move the window to the next jump range
            l = r + 1;
            r = farthest;
            res++;
        }

        return res;
    }
};


int main() {
    
    return 0;
}