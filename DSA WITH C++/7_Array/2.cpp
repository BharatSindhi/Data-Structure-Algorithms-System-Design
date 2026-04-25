#include <iostream>
using namespace std;

int main() {
    int smallArr[5]={10,5,6,4,2};
    int n=5;
    int index=0;
    int small=smallArr[0];
    for (int  i = 0; i < n; i++)
    {
       if (smallArr[i]<small)
       {
         small=smallArr[i];
         index=i;
       }
        small=min(smallArr[i],small);

    }
    cout<<"smallest ="<<small<<"at index"<<index<<endl;
    return 0;
}