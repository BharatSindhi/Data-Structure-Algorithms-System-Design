#include <iostream>
using namespace std;

class Person {
public:
    string name;
    int age;

    Person(string name, int age) {
        this->name = name;
        this->age = age;
    }
};

class Student : public Person {
public:
    int roll;

    // Constructor for Student that also initializes Person
    Student(string name, int age, int roll) : Person(name, age) {
        this->roll = roll;
    }

    void display() {
        cout << "Name: " << name << ", Age: " << age << ", Roll: " << roll << endl;
    }
};

int main() {
    Student s1("Bharat", 20, 101);
    s1.display();

    return 0;
}
