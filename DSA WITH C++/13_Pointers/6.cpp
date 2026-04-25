#include <iostream>
using namespace std;
void change(int &b){
    b=20;
}
int main() {
    int a=10;
    change(a);

    cout<<"inside main fnx  :  "<<a<<endl;
    return 0;
}

// passs by alias 