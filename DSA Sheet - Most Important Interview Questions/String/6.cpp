#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int compress(vector<char>& chars) {
        int idx=0;
        int n=chars.size();
        for(int i=0;i<n;i++){
            char ch=chars[i];
            int count=0;
            while(i<n && chars[i]==ch){
                count++;i++;
            }
            if(count == 1){
                chars[idx++]=ch;
            }else{
                chars[idx++]=ch;
                string str=to_string(count);
                for(char dig:str){
                    chars[idx++]=dig;

                }
            }
            i--;

        }
        chars.resize(idx);
        return idx;
    }
};


class Solution {
public:
   int compress(vector<char>& chars) {
       chars.push_back('~');
       int n=chars.size();
       int i=0;
       int j=1;
       int count=1;
       while(j<n)
       {
           if(chars[j]==chars[j-1])
           count++;
           else
           {
             chars[i]=chars[j-1];
             i++;
             if(count>=2)
             {
                 string len=to_string(count);
                 for(auto x:len)
                 {
                   chars[i]=x;
                   i++;
                 }
                 count=1;
             }
           }
           j++;
       }
       return i;
   }
};


int main() {
    // your code here
    return 0;
}