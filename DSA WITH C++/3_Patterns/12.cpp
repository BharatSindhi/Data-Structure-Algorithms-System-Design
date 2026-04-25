#include <iostream>
using namespace std;

int main()
{
    int n = 5;
    char Ch = 'A';

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j > 0; j--)
        {
            cout << Ch << " ";
            Ch++;
        }
        cout << endl;
    }

    return 0;
}