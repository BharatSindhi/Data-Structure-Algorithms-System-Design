#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, int> m;

    // Correct insertion
    m["tv"] = 100;
    m["laptop"] = 100;
    m["headphone"] = 50;

    // Correct iteration
    for (auto item : m) {
        cout << item.first << " => " << item.second << endl;
    }
    if (m.find("headphone")!=m.end())
    {
        cout<<"found\n";
    }else{
        cout<<"not found\n";
    }
    
    return 0;
}
