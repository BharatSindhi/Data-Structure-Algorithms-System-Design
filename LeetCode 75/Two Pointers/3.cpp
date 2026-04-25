#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int left = 0;
        int right = n - 1;

        int maxareas = 0;

        while (left < right) {
            int width = right - left;
            int h = min(height[left], height[right]);

            int curr = width * h;
            maxareas = max(maxareas, curr);

            // Move the smaller height pointer
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return maxareas;
    }
};

int main() {
    // your code here
    return 0;
}