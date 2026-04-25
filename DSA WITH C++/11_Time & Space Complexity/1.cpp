#include <iostream>
using namespace std;

int main() {
    // common time complexities o(1)
    int n;
    cin>>n;
    int  ans=n*(n+1)/2;

    // o(n)
    int fact=1;
    for (int i = 0; i < n; i++)
    {
        fact *= i;
    }
    int arr[]={1,5,7,6};
    int currSum=0 , ans=INT_MIN;
    for (int i = 2; i < n; i++)
    {
        currSum+=arr[i];
        ans=max(currSum,ans);
        currSum=currSum<0?0:currSum;
    }
    
    // o(n^2) & o(n^3)
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (arr[j]>arr[j+1])
            {
                swap(arr[j],arr[j+1]);
            }
            
        }
        
    }
    
    // o(logn)
    int s=0 , e=n-1;
    int target=5;
    while (s<=e)
    {
        int mid=s+(e-s)/2;
        if (arr[mid]<target)
        {
            s=mid+1;
        }else if (arr[mid]>target)
        {
            e=mid-1;
        }else{
            return mid;
        }  
    }
    
// o(nlogn) -> sorting -> quicksort -> gready 


    return 0;
}