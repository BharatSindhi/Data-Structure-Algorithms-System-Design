#include <iostream>
using namespace std;

void printNum(int n){
    if (n==1)
    {
        cout<<"1\n";
        return;
    }

    cout<<n<<" ";
    printNum(n-1);
    
}
int main() {
    printNum(5);
    return 0;
}