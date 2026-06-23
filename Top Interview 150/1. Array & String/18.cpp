#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int totalGas = 0;
        int totalCost = 0;

        int start = 0;
        int currGas = 0;

        for (int i = 0; i < gas.size(); i++) {
            totalGas += gas[i];
            totalCost += cost[i];

            currGas += gas[i] - cost[i];

            if (currGas < 0) {
                start = i + 1;
                currGas = 0;
            }
        }

        if (totalGas < totalCost)
            return -1;

        return start;
    }
};
int main() {
    
    return 0;
}