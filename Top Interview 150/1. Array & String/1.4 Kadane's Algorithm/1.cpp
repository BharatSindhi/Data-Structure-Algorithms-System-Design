#include <iostream>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n=nums.size();
        int currSum=0;
        int maxiSum=nums[0];
        for(int i=0;i<n;i++){
            currSum+=nums[i];
            maxiSum=max(maxiSum,currSum);
            if(currSum<0){
                currSum=0;
            }
        }
        return maxiSum;
    }
};

int main() {
    
    return 0;
}


