#include <iostream>
using namespace std;

class Student {
public:
    string name;
    string enroll;
    double* cgpaPtr;  // dynamic memory

    // Parameterized constructor
    Student(string name, string enroll, double cgpa) {
        this->name = name;
        this->enroll = enroll;
        cgpaPtr = new double;   // allocate memory
        *cgpaPtr = cgpa;        // assign value
    }

    // Copy constructor (deep copy)
    Student(const Student &obj) {
        this->name = obj.name;
        this->enroll = obj.enroll;
        cgpaPtr = new double;   // allocate new memory
        *cgpaPtr = *(obj.cgpaPtr);  // copy value
    }

    // Destructor (to free memory)
    ~Student() {
        delete cgpaPtr; // memory leak
    }

    void getInfo() {
        cout << "name: " << name << endl;
        cout << "enroll: " << enroll << endl;
        cout << "cgpa: " << *cgpaPtr << endl;
    }
};

int main() {
    Student s1("bharat", "50", 7.0);

    Student s2(s1);  // deep copy constructor called
    s2.getInfo();
    *(s2.cgpaPtr)=8.0;
    s2.getInfo();

    return 0;
}
