#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm> // reverse, next_permutation, max, min, swap, max_element, min_element, binary_search
using namespace std;

int main() {
    // ===== Unordered_set Example =====
    unordered_set<int> us = {10, 5, 20, 10}; // duplicate ignored
    cout << "Unordered_set contents (no order, no duplicates): ";
    for (auto val : us) cout << val << " ";
    cout << "\n";

    // Check existence
    if (us.find(10) != us.end())
        cout << "10 is in the set\n";
    else
        cout << "10 is not in the set\n";

    // ===== Reverse =====
    vector<int> v = {1, 2, 3, 4, 5};
    cout << "\nOriginal vector: ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    reverse(v.begin(), v.end());
    cout << "After reverse: ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // ===== Next Permutation =====
    vector<int> p = {1, 2, 3};
    cout << "\nOriginal permutation: ";
    for (int x : p) cout << x << " ";
    cout << "\n";

    if (next_permutation(p.begin(), p.end())) {
        cout << "Next permutation: ";
        for (int x : p) cout << x << " ";
        cout << "\n";
    } else {
        cout << "No next permutation (already largest)\n";
    }

    // ===== Swap =====
    int a = 10, b = 20;
    cout << "\nBefore swap: a = " << a << ", b = " << b << "\n";
    swap(a, b);
    cout << "After swap:  a = " << a << ", b = " << b << "\n";

    // ===== Max / Min Functions =====
    cout << "\nMax of 15 and 42: " << max(15, 42) << "\n";
    cout << "Min of 15 and 42: " << min(15, 42) << "\n";

    // ===== Max & Min Element in a vector =====
    vector<int> nums = {10, 5, 20, 15, 25};
    auto maxIt = max_element(nums.begin(), nums.end());
    auto minIt = min_element(nums.begin(), nums.end());
    cout << "\nMax element in nums: " << *maxIt << "\n";
    cout << "Min element in nums: " << *minIt << "\n";

    // ===== Binary Search =====
    sort(nums.begin(), nums.end()); // required for binary_search
    int target = 15;
    if (binary_search(nums.begin(), nums.end(), target))
        cout << target << " found in nums\n";
    else
        cout << target << " not found in nums\n";

    // ===== Count Set Bits =====
    unsigned int num = 29; // binary: 11101 -> 4 set bits
    cout << "\nNumber of set bits in " << num << ": " 
         << __builtin_popcount(num) << "\n";
    cout << "Number of set bits in long long 29: " 
         << __builtin_popcountll(29) << "\n";

    return 0;
}
