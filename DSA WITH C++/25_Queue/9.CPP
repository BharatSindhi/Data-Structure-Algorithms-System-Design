#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int totGas = 0, totCost = 0;
        int start = 0, currGas = 0;

        for (int i = 0; i < gas.size(); i++) {
            totGas += gas[i];
            totCost += cost[i];
            currGas += (gas[i] - cost[i]);

            // If we run out of gas at station i, reset start
            if (currGas < 0) {
                start = i + 1;
                currGas = 0;
            }
        }

        return (totGas < totCost) ? -1 : start;
    }
};

int main() {
    Solution sol;
    vector<int> gas = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 1, 2};

    int start = sol.canCompleteCircuit(gas, cost);
    if (start == -1)
        cout << "No solution possible.\n";
    else
        cout << "Start at gas station: " << start << endl;

    return 0;
}
