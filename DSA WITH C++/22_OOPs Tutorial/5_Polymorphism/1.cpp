#include <iostream>
using namespace std;

class Student{
    public:
        string name;

    Student(){
        cout<< "non-paramertersized\n";
    }
    Student(string name){
        this->name=name;
        cout<<"paramaterized";
    }
};

int main() {
    Student s1;
    return 0;
}