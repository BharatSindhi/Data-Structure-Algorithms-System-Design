#include <iostream>
#include<vector>
using namespace std;

int main() {
    vector<int>vec={1,2,3,4,5,6};
    cout<<"vector with being : "<<*(vec.begin())<<endl;
    cout<<"vector with being : "<<*(vec.end())<<endl;
    return 0;
}