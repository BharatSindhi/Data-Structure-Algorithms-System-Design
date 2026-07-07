#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
          int start = 0, end = nums.size() - 1;
        int startIdx = -1, endIdx = -1;

        // First binary search to find the start index of the target
        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] == target) {
                startIdx = mid;
                end = mid - 1; // Continue searching in the left half
            } else if (nums[mid] > target) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }

        start = 0;
        end = nums.size() - 1;

        // Second binary search to find the end index of the target
        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] == target) {
                endIdx = mid;
                start = mid + 1; // Continue searching in the right half
            } else if (nums[mid] > target) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }

        return {startIdx, endIdx};
    }
};
int main() {
    // your code here
    return 0;
}