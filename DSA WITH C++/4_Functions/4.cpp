#include <iostream>
using namespace std;
 
int digitSum(int n){
    int ds=0;

    while (n>0)
    {
        int ld=n%10;
        n=n/10;
        ds+=ld;
    }
    return ds;
}
int main() {
    cout<<"sum of the digit :"<<digitSum(123)<<endl;
    return 0;
}