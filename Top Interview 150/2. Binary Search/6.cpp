#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n=nums.size();
        int l=0;
        int r=n-1;
        int ans=INT_MAX;
        while(l<=r){
            int mid=l+(r-l)/2;
            if(nums[l]<=nums[mid]){
                ans=min(ans,nums[l]);
                l=mid+1;
            }else{
                r=mid-1;
                ans=min(ans,nums[mid]);
            }
        }
        return ans;
    }
};


int main() {
    
    return 0;
}