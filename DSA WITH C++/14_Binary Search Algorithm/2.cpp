#include <iostream>
#include <vector>
using namespace std;

int bs(vector<int> arr, int tar ,int s ,int e) {
    while (s<=e)
    {
        int mid=s+(e-s)/2;
        if (tar>arr[mid])
        {
            return bs(arr,tar,mid+1,e);
        }else if (tar<arr[mid])
        {
             return bs(arr,tar,s,mid-1);
        }else
        {
            return mid;
        }
    }
    return -1;
    
}

int main() {
    vector<int> arr1 = {-1, 0, 3, 4, 5, 6, 9, 12};
    int tar1 = 12;
    int st=0,end=arr1.size();
    cout << "Element at index: " << bs(arr1, tar1,st,end) << endl;

    return 0;
}
