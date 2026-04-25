#include <iostream>
#include<vector>
using namespace std;
class Solution {
public:
    // Recursive binary search
    int binSearch(vector<int>& nums, int target, int st, int end) {
        if (st <= end) {
            int mid = st + (end - st) / 2;

            if (nums[mid] == target) 
                return mid;
            else if (nums[mid] < target) 
                return binSearch(nums, target, mid + 1, end);
            else 
                return binSearch(nums, target, st, mid - 1);
        }
        return -1; // target not found
    }

    int search(vector<int>& nums, int target) {
        int st = 0, end = nums.size() - 1;
        return binSearch(nums, target, st, end);
    }
};

int main() {
    Solution sol;
    vector<int> nums = {-10, -3, 0, 5, 9, 12, 17};
    int target;

    cout << "Enter target: ";
    cin >> target;

    int index = sol.search(nums, target);
    if (index != -1) {
        cout << "Target found at index " << index << endl;
    } else {
        cout << "Target not found" << endl;
    }

    return 0;
}
