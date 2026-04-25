#include <iostream>
using namespace std;

int revNum(int arr[],int n){
     int left=0;
    int rigth=n-1;

    while (left < rigth)
    {
        swap(arr[left],arr[rigth]);
        left++;
        rigth--;
    }
    
}
int main() {
    int arr[5]={10,20,30,40,50};
    int n=sizeof(arr)/sizeof(arr[0]);

    revNum(arr,n);

    for (int  i = 0; i < n; i++)
    {
        cout<<arr[i]<<" ";
    }
    

    cout<<endl;
    
    return 0;
}