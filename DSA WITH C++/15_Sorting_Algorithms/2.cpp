#include <iostream>
using namespace std;
void bubbleSort(int arr[],int n){//o(n^2)
    for (int i = 0; i < n-1; i++)
    {
        bool isSwap=false;
        for (int j = 0; j < n-i-1; j++)
        {
            if (arr[j]>arr[j+1])
            {
                swap(arr[j],arr[j+1]);
                isSwap=true;
            }
            
        }
        if (!isSwap)
        {
            return;
        }
        
        
    }
    
}
void printArr(int arr[],int n){
    for (int i = 0; i < n; i++)
    {
        cout<< arr[i]<<" ";
    }
    cout<<endl;
}
int main() {
    int arr1[]={1,2,7,9,17};
    int n=5;
    bubbleSort(arr1,n);
    printArr(arr1,n);
    return 0;
}