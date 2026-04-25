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

class Teacher : public Person {   // Both inherit from Person
public:
    string subject;
};

int main() {
    Student s;
    s.name = "Bharat";
    s.roll = 101;

    Teacher t;
    t.name = "Ravi";
    t.subject = "Maths";

    cout << "Student -> " << s.name << " Roll: " << s.roll << endl;
    cout << "Teacher -> " << t.name << " Subject: " << t.subject << endl;
}
