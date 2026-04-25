#include <iostream>
using namespace std;

class Account {
public:
    string accountId;
    string userName;
    string branch;

private:
    double balance;
    string password;

public:
    // Default (non-parameterized) Constructor
    Account() {
        branch = "Bank of India";
        cout << "Default constructor called" << endl;
    }

    // Parameterized Constructor
    Account(string acc, string u, string b) {
        accountId = acc;
        userName = u;
        branch = b; 
        cout << "Parameterized constructor called" << endl;
    }

    // Copy Constructor
    Account(const Account &obj) {
        accountId = obj.accountId;
        userName = obj.userName;
        branch   = obj.branch;
        cout << "Copy constructor called" << endl;
    }

    ~Account(){
            cout<<"Hi, I delete data ";
            
    }
};

int main() {
    Account u1("ukj55", "sahil", "BOB");   // Parameterized constructor
    cout << "Account ID: " << u1.accountId << endl;
    cout << "User Name: " << u1.userName << endl;
    cout << "Branch: " << u1.branch << endl;

    cout << endl;

    Account u2 = u1;   // Copy constructor
    cout << "Account ID: " << u2.accountId << endl;
    cout << "User Name: " << u2.userName << endl;
    cout << "Branch: " << u2.branch << endl;

    return 0;
}
