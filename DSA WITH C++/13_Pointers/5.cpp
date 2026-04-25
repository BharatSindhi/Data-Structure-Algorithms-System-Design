#include <iostream>
using namespace std;
void change(int* ptr){
    *ptr=20;
}
int main() {
    int a=10;
    change(&a);

    cout<<"inside main fnx  :  "<<a<<endl;
    return 0;
}

// pass by refer