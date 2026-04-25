#include <iostream>
using namespace std;

class Teacher {
public:   // <-- make members public
    // Properties / Attributes
private:
    double salary;

public :
    string name;
    string dept;
    string subject;
 

    // methods / member functions
    void changeDept(string newDept) {
        dept = newDept;
    }
    //setter
    void setSalary(double s){
        salary = s;
    }
    //getter
    double getSalary(){
        return salary;
    }
};

int main() {
    Teacher t1;
    t1.name = "bharat";
    t1.subject = "python";
    t1.dept = "cs";
    // t1.salary = 50000;
    t1.setSalary(25000);
    cout<<t1.name<<endl;
    cout<<t1.getSalary()<<endl;
    cout << t1.name << endl;
    return 0;
}
