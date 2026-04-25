// # Intuition
// We use a stack to keep track of previous stock prices and their corresponding span.
// If today’s price is higher or equal to the previous one, that means the stock span extends backward.
// # Approach
// For every new price:

// Pop all smaller or equal prices from the stack and accumulate their spans.

// Push the current price and total span back into the stack.

// Return the span for the current day.
// # Complexity
// - Time complexity:
// O(1) amortized per call (each price is pushed and popped at most once).
// - Space complexity:
// O(n) for the stack.
// # Code
// ```cpp []
// #include <bits/stdc++.h>
// using namespace std;

// class StockSpanner {
// public:
//     stack<pair<int,int>> st; // {price, span}

//     StockSpanner() {}

//     int next(int price) {
//         int span = 1;
//         // Pop smaller or equal prices and add their spans
//         while (!st.empty() && st.top().first <= price) {
//             span += st.top().second;
//             st.pop();
//         }
//         st.push({price, span});
//         return span;
//     }
// };

// /**
//  * Example usage:
//  * StockSpanner* obj = new StockSpanner();
//  * cout << obj->next(100) << endl;
//  * cout << obj->next(80) << endl;
//  * cout << obj->next(60) << endl;
//  * cout << obj->next(70) << endl;
//  * cout << obj->next(60) << endl;
//  * cout << obj->next(75) << endl;
//  * cout << obj->next(85) << endl;
//  */

// ```


#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    
    vector<int> price={100,80,60,70,60,75,85};
    vector<int> ans(price.size(),0);
    stack<int>s;

    for (int i = 0; i < price.size(); i++)
    {
        while (s.size()>0 && price[s.top()<= price[i]])
        {
            s.pop();
        }
        if (s.empty())
        {
            ans[i]=i+1;
        }else{
            ans[i]=i-s.top();
        }
        
        s.push(i);
    }
    for(int val : ans){
        cout<<val<<" ";
    }
    cout<<endl;

    return 0;
}