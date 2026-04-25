#include <iostream>
using namespace std;

class Parent{
public:
    void getInfo(){
        cout<<"parent class";
    }

    virtual void hello(){
        cout<<"hello from virtual\n";
    }
};

class Child : public Parent{
public:
    void getInfo(){
        cout<<"child class";
    }
    void hello(){
        cout<<"hello from chlid\n";
    }
};

int main() {
    Child c1;
    c1.getInfo();
    c1.hello();
    Parent p1;
    p1.getInfo();
    return 0;
}