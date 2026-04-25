#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() = 0; // pure virtual function
};

class Circle : public Shape {
public:
    void draw() override { // overriding base class function
        cout << "Drawing a circle\n";
    }
};

int main() {
    Circle c1;
    c1.draw(); // call the overridden function
    return 0;
}
