#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxProfit = 0;
        int bestBuy = prices[0];

        for (int i = 1; i < prices.size(); i++) {
            maxProfit = max(maxProfit, prices[i] - bestBuy);
            bestBuy = min(bestBuy, prices[i]); // keep updating minimum so far
        }

        return maxProfit;
    }
};

int main() {
    Solution sol;

    // Example input
    vector<int> prices = {7, 1, 5, 3, 6, 4};

    // Call maxProfit
    int result = sol.maxProfit(prices);

    // Print result
    cout << "Maximum Profit: " << result << endl;

    return 0;
}
