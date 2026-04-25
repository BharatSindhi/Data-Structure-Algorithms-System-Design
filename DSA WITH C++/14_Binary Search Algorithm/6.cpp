#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int st = 0, end = nums.size() - 1;

        while (st < end) {
            int mid = st + (end - st) / 2;

            // Ensure mid is even
            if (mid % 2 == 1) {
                mid--;
            }

            // If the pair is valid, move to the right
            if (nums[mid] == nums[mid + 1]) {
                st = mid + 2;
            } else {
                // Unique element is on the left half (including mid)
                end = mid;
            }
        }

        // st == end will point to the single element
        return nums[st];
    }
};

// Example usage
int main() {
    Solution sol;
    vector<int> nums = {1, 1, 2, 3, 3, 4, 4, 8, 8};
    cout << "Single non-duplicate element: " << sol.singleNonDuplicate(nums) << endl;
    return 0;
}
