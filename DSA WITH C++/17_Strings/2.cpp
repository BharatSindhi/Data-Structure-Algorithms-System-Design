#include <iostream>
using namespace std;

int main() {
    char str[10];
    cout<<"enter char array : ";
    // cin>>str;
    cin.getline(str,10,'$');
    cout<<"output : "<<str<<endl;

    for(char ch : str){
        cout<<ch<<" ";
    }
    cout<<endl;
    return 0;
} 