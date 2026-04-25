#include <iostream>
using namespace std;
bool isAramstrong(int n){
    int copyN=n;
    int sumOfCubes=0;
    while (n!=0)
    {
        int dig=n%10;
        sumOfCubes+=(dig*dig*dig);
        n=n/10;

    }
    return sumOfCubes==copyN;
}
int main() {
    int n=153;
    if (isAramstrong(n))
    {
        cout<<"is an armstong number\n";
    }else{
        cout<<"not an armstong number\n";
    }
    
    return 0;
}