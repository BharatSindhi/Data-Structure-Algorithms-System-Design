#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int left = 0;
        int zero_count = 0;
        int max_len = 0;

        for (int right = 0; right < nums.size(); right++) {
            if (nums[right] == 0) {
                zero_count++;
            }

            // shrink window if zeros exceed k
            while (zero_count > k) {
                if (nums[left] == 0) {
                    zero_count--;
                }
                left++;
            }

            max_len = max(max_len, right - left + 1);
        }

        return max_len;
    }
};


int main() {
    
    return 0;
}