#include <iostream>
using namespace std;
void pritDidits(int n){
    int sum=0;
    while (n!=0)
    {
        int digit=n%10;
        sum+=digit;
        n=n/10;
    }
    cout<<sum<<endl;
}
int main() {
    int n=3568;
    pritDidits(n);
    return 0;
}