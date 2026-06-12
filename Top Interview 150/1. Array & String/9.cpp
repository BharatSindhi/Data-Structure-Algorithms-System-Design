#include <iostream>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size();
        int m = needle.size();

        if(m == 0) return 0;              // empty needle
        if(n < m) return -1;              // impossible case
        if(haystack == needle) return 0;  // exact match

        for(int i = 0; i <= n - m; i++){  // only go until valid window
            if(haystack.substr(i, m) == needle){
                return i;
            }
        }
        return -1;
    }
};


int main() {
    
    return 0;
}