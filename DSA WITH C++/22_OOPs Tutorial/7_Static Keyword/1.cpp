#include <iostream>
using namespace std;

// (1) Static inside a function
void fun() {
    static int x = 0;   // static local variable (retains value)
    cout << "fun() x : " << x << endl;
    x++;
}

// (2) Class with both normal and static members
class A {
public:
    int y;              // non-static → separate for each object
    static int x;       // static → shared across all objects

    void setY(int val) {
        y = val;
    }

    void show() {
        cout << "Object's y = " << y << ", Shared x = " << x << endl;
    }

    static void incX() {   // static function → can access only static members
        x++;
    }
};
int A::x = 100;  // definition of static member outside class

// (3) File-scope static variable
static int g = 50;

// (3) File-scope static function
static void helper() {
    cout << "Inside static helper()\n";
}

int main() {
    // --- Function static ---
    fun();
    fun();
    fun();

    cout << "---------------------" << endl;

    // --- Class static vs non-static ---
    A obj1, obj2;

    obj1.setY(10);
    obj2.setY(20);

    cout << "Before incX():\n";
    obj1.show();  // y=10, x=100
    obj2.show();  // y=20, x=100 (same x!)

    A::incX(); // increment shared static x

    cout << "After incX():\n";
    obj1.show();  // y=10, x=101
    obj2.show();  // y=20, x=101

    cout << "---------------------" << endl;

    // --- File-scope static ---
    cout << "g = " << g << endl;
    helper();

    return 0;
}
