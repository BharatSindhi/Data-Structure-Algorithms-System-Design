#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0;
        int right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target < nums[mid]) {
               right = mid - 1;
            } else if (target > nums[mid]) {
                left = mid + 1;
            } else {
                return mid;
            }
        }
        return left;
    }
};
int main() {
    // your code here
    return 0;
}