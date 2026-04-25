#include <iostream>
using namespace std;
#include<vector>
int main() {
    vector<int>vec;

    cout<<"size ="<<vec.size()<<endl;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    cout<<"size ="<<vec.size()<<endl;
    vec.pop_back();
    cout<<"size ="<<vec.size()<<endl;

    cout<<vec.front()<<endl;

    cout<<vec.back()<<endl;

    cout<<vec.at(0)<<endl;


    for(int i:vec){  //for each loop
            cout<<i<<endl;
        }


    return 0;
}