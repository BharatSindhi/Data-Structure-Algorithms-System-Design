#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int low = 0, mid = 0, high = nums.size() - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums[low++], nums[mid++]);
            } else if (nums[mid] == 1) {
                mid++;
            } else { // nums[mid] == 2
                swap(nums[mid], nums[high--]);
            }
        }
    }
};

int main() {
    Solution sol;

    vector<int> nums = {2, 0, 2, 1, 1, 0};

    cout << "Original array: ";
    for (int num : nums)
        cout << num << " ";
    cout << endl;

    sol.sortColors(nums);

    cout << "Sorted array: ";
    for (int num : nums)
        cout << num << " ";
    cout << endl;

    return 0;
}
