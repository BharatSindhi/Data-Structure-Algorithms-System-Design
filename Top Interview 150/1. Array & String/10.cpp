#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int l=0;
        int r=0;

        while(r<nums.size()){
            int count=1;
            while(r+1<nums.size() && nums[r] == nums[r+1]){
                r++;
                count++;
            }
            int cnums=min(2,count);
            for(int i=0;i<cnums;i++){
                nums[l]=nums[r];
                l++;
            }
            r++;
        }
        return l;
    }
};

int main() {
    
    return 0;
}