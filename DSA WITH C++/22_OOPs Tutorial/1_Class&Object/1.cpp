#include <iostream>
using namespace std;

class Teacher {
public:   // <-- make members public
    // Properties / Attributes
    string name;
    string dept;
    string subject;
    double salary;

    // methods / member functions
    void changeDept(string newDept) {
        dept = newDept;
    }
};

int main() {
    Teacher t1;
    t1.name = "bharat";
    t1.subject = "python";
    t1.dept = "cs";
    t1.salary = 50000;

    cout << t1.name << endl;
    return 0;
}
