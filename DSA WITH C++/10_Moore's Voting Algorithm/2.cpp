#include <iostream>
#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    int n = nums.size();
    vector<int> res;
    int i=0,j=n-1;
    while (i<j)
    {
        int pair=nums[i]+nums[j];

        if (pair>target)
        {
            j--;
        }else if (pair<target)
        {
            i++;
        }else{
            res.push_back(i);
            res.push_back(j);
            return res;
        }
        
        
    }
    
    
   
    return res; // return empty if no match
}

int main() {
    vector<int> nums = {2, 6, 7, 15};
    int target = 8;

    vector<int> result = twoSum(nums, target);

    if (!result.empty()) {
        cout << "Indices: " << result[0] << ", " << result[1] << endl;
    } else {
        cout << "No two numbers found with the given target." << endl;
    }

    return 0;
}
 