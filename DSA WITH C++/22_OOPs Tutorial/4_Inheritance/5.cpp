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

class Teacher : public Person {
public:
    string subject;
};

class TA : public Student, public Teacher {   // Hybrid (Multiple + Hierarchical)
public:
    void display() {
        cout << "Name: " << Student::name   // Resolve ambiguity
             << ", Roll: " << roll 
             << ", Subject: " << subject << endl;
    }
};

int main() {
    TA ta;
    ta.Student::name = "Bharat";  // Need scope resolution because both Student and Teacher inherit Person
    ta.roll = 101;
    ta.subject = "AI";

    ta.display();
}
