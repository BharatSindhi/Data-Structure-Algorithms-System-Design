#include <iostream>
using namespace std;

class Print{

public:
    void Show(int x){
        cout <<"int : "<<x<<endl;
    }

    void Show(char ch){
        cout<<"char :"<<ch<<endl;
    }
};

int main() {
    Print p1;
    p1.Show(4);
    return 0;
}