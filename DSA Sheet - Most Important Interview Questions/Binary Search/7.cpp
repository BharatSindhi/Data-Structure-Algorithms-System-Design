#include <iostream>
#include <vector>
using namespace std;

int main() {
    class Solution {
public:
   double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
       int n1=nums1.size();
       int n2=nums2.size();
       if(n1>n2) return findMedianSortedArrays(nums2,nums1);
      
       int low=0;
       int high=n1;
       while(low<=high)
       {
           int i1=(low+high)/2;
           int i2=(n1+n2+1)/2-i1;
           int max1=(i1==0)?INT_MIN:nums1[i1-1];
           int max2=(i2==0)?INT_MIN:nums2[i2-1];
           int min1=(i1==n1)?INT_MAX:nums1[i1];
           int min2=(i2==n2)?INT_MAX:nums2[i2];


           if(max1<=min2 && max2<=min1)
           {
              int n=n1+n2;
              if(n%2==0)
              return ((double)max(max1,max2) + (double)min(min1,min2))/2.0;
              else
              return (double)max(max1,max2);
           }
           else if(min1<max2)
           low=i1+1;
           else
           high=i1-1;
       }
       return 0.0;
   }
};



    return 0;
}