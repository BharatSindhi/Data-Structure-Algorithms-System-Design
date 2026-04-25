#include <iostream>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int n=s.size();
        int l=0;
        int r=n-1;
        while(l<r){
            if(!isalnum(s[l])){
                l++;
            }else if(!isalnum(s[r])){
                r--;
            }else if(tolower(s[l])==tolower(s[r])){
                l++;
                r--;
            }else{
                return false;
            }
        }
                return true;
    }
};

int main() {
    // your code here
    return 0;
}