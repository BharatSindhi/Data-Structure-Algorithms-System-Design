// 	Notes:
// 	- There is an integer array nums sorted in ascending order (with distinct values).
// 	- Prior to being passed to your function, nums is possibly left rotated at an unknown index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be left rotated by 3 indices and become [4,5,6,7,0,1,2].
// 	- Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
// 	- You must write an algorithm with O(log n) runtime complexity.

// Input: nums = [4,5,6,7,0,1,2], target = 0
// Output: 4

// Approch:
// - the bruth force approch direct search and return an index and also if not found return -1
// - the best approch is binary search and also match the time complexity and also but problem is nums are not complted sorted and also how to return index 
// Pattern Recognition

// Whenever you see:

// sorted array + rotated

// Think:

// ⭐ Modified Binary Search

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n=nums.size();
        int st=0;
        int end=n-1;

        while(st<=end){
            int mid=st+(end-st)/2;
            if(nums[mid]==target){
                return mid;
            }
            if(nums[st]<=nums[mid]){ // left sorted
                if(nums[st]<=target && target<=nums[mid]){
                    end=mid-1;
                }else{
                    st=mid+1;
                }
            }else{//right sorted
                if(nums[mid]<=target && target<=nums[end]){
                    st=mid+1;
                }else{
                    end=mid-1;
                }
            }
        }
        return -1;
    }
};

int main() {
    
    return 0;
}