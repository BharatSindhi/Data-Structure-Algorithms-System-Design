#include <iostream>
using namespace std;

int binaryToDec(int biNum){
    int ans=0,pow=1  ;

    while (biNum >0)
    {
       int rem = biNum%10;
       ans+=rem*pow;

       biNum/=10;
       pow*=2;
    }
    
    return ans;

}
int main() {
    cout<<"binary to decemial : "<<binaryToDec(1010)<<endl;    
    return 0;
}