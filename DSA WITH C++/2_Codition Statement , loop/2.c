#include <stdio.h>

int main() {
    int i = 0;
    int n = 10;
    int odd = 0;  // Initialize variable

    while (i < n) {
        if (i % 2 != 0) {  // Check if i is odd
            odd += i;
        }
        i++;
    }

    printf("Sum of odd numbers less than %d is %d\n", n, odd);

    return 0;
}
