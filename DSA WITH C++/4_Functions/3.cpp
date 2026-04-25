#include <iostream>
using namespace std;

int fact(int n){
    if (n==0 || n==1)
    {
        return 1;
    }else{
        return n*fact(n-1);
    }
    
}

int factS(int n){
    int fact=1;

    for (int i = 0; i < n; i++)
    {
        fact*=i;
    }
    return fact;
    
    
}
int main() {
    cout<<"fact of the number"<<fact(5)<<endl;
    return 0;
}