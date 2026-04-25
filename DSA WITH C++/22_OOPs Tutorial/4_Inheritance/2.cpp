#include <iostream>
using namespace std;

class Person {
public:
    string name;
};

class Student : public Person {
public:
    int roll;
};

class Graduate : public Student {   // Multilevel
public:
    string degree;
    void display() {
        cout << "Name: " << name << ", Roll: " << roll << ", Degree: " << degree << endl;
    }
};

int main() {
    Graduate g;
    g.name = "Bharat";
    g.roll = 101;
    g.degree = "B.Tech";
    g.display();
}
