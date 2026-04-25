#include <iostream>
using namespace std;
void pritDidits(int n){
    int count=0;
    while (n!=0)
    {
        int digit=n%10;
        count++;
        n=n/10;
    }
    cout<<count<<endl;
}
int main() {
    int n=3594;
    pritDidits(n);
    return 0;
}