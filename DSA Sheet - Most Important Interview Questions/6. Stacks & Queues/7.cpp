#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        int time = 0;

        for (int c = 0; c < tickets.size(); c++) {
            if (c <= k) {
                time += min(tickets[c], tickets[k]);
            } else {
                time += min(tickets[c], tickets[k] - 1);
            }
        }

        return time;
    }
};
int main() {
    
    return 0;
}