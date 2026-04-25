#include <iostream>
#include <vector>
using namespace std;

int linearSearch(vector<int>& vec, int x) {
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        if (vec[i] == x) {
            return i;
        }
    }
    return -1; // element not found
}

int main() {
    vector<int> vec = {10, 20, 30, 40, 50};
    int x = 40;
    int index = linearSearch(vec, x);

    if (index != -1)
        cout << "Element found at index " << index << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
