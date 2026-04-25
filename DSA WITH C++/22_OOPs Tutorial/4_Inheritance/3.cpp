#include <iostream>
using namespace std;

class Sports {
public:
    string game;
};

class Academics {
public:
    int marks;
};

class Student : public Sports, public Academics {   // Multiple
public:
    string name;
    void display() {
        cout << "Name: " << name << ", Game: " << game << ", Marks: " << marks << endl;
    }
};

int main() {
    Student s;
    s.name = "Bharat";
    s.game = "Cricket";
    s.marks = 90;
    s.display();
}
 