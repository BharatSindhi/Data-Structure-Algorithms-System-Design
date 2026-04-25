#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
   // Function to count inversions in the array.
  int merge(vector<int>&arr,int low,int mid,int high)
  {
       int n1=mid-low+1;
       int n2=high-mid;
       vector<int> left(n1);
       vector<int> right(n2);
      
       for(int i=0;i<n1;i++)
       {
           left[i]=arr[low+i];
       }
       for(int i=0;i<n2;i++)
       {
           right[i]=arr[mid+1+i];
       }
      
       int k=low;
       int i=0;
       int j=0;
       int count=0;
       while(i<n1 && j<n2)
       {
           if(left[i]>right[j])
           {
               count+=(n1-i);
               arr[k++]=right[j++];
           }
           else
           arr[k++]=left[i++];
       }
      
       while(i<n1)
       {
           arr[k++]=left[i++];
       }
      
       while(j<n2)
       {
           arr[k++]=right[j++];
       }
       return count;
}
int mergeSort(vector<int>&arr,int low,int high)
{
       int count=0;
       if(low<high)
       {
           int mid=(low+high)/2;
           count+=mergeSort(arr,low,mid);
           count+=mergeSort(arr,mid+1,high);
           count+=merge(arr,low,mid,high);
       }
       return count;
}
int inversionCount(vector<int> &arr) {
       int n=arr.size();
       return mergeSort(arr,0,n-1);
}
};



int main() {
    // your code here
    return 0;
}