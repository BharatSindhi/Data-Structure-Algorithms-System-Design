#include <iostream>
#include <vector>
#include <algorithm> // for reverse()
using namespace std;

void reverseVector(vector<int>& vec) {
    reverse(vec.begin(), vec.end());
}

int main() {
    vector<int> vec = {10, 20, 30, 40, 50};
    
    reverseVector(vec);

    cout << "Reversed vector: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
