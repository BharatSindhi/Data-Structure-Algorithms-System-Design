#include <iostream>
using namespace std;

int main() {
    int largeARR[5]={10,5,6,4,2};
    int n=5;
    int index=0;
    int large=largeARR[0];
    for (int  i = 0; i < n; i++)
    {
       if (largeARR[i]>large)
       {
         large=largeARR[i];
         index=i;
       }
       large=max(largeARR[i],large);
    }
    cout<<"largeest ="<<large<<"at index"<<index<<endl;
    return 0;
}