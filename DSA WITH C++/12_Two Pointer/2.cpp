#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int left = 0;
        int right = n - 1;
        int res = 0;

        while (left < right) {
            int h = min(height[left], height[right]);
            int area = h * (right - left);
            res = max(res, area);

            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return res;
    }
};

int main() {
    Solution sol;

    // Example input
    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};

    // Call maxArea
    int result = sol.maxArea(height);

    // Print result
    cout << "Maximum Water Container Area: " << result << endl;

    return 0;
}
