#include <iostream>
using namespace std;
#include<vector>
int main() {
    vector<int>vec={10,20,30,40,50};

        // cout<<vec[0]<<endl;
        // cout<<vec[1]<<endl;
        // cout<<vec[2]<<endl;
        // cout<<vec[3]<<endl;
        // cout<<vec[4]<<endl;

        for(int i:vec){  //for each loop
            cout<<i<<endl;
        }

    return 0;
}