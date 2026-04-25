#include <iostream>
using namespace std;

int main() {
    int a=10;
    int*ptr =&a;
    int** prt1=&ptr;

    cout<<&ptr<<endl;
    cout<<prt1<<endl;
    return 0;
}