#include <iostream>
#include<vector>
using namespace std;

int main() {
    vector<int>vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.emplace_back(4);

    vec.pop_back();
    cout<<vec.size()<<endl;
    cout<<vec.capacity()<<endl;

    cout<<"val at inx 2 "<<vec[2]<<" or "<<vec.at(2)<<endl;
    cout<<"front "<<vec.front()<<endl;
    cout<<"back "<<vec.back()<<endl;
    vec.insert(vec.begin()+2,0);
    // vec.erase(vec.begin()+1, vec.end()+2);
    for(int val : vec){
        cout<<val;
    }


    return 0;
}