#include <stdio.h>

int main() {
    int n = 10;
    int even = 0;  // Initialize the sum variable

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {  // Check if the number is even
            even += i;
        }
    }

    
    printf("Sum of even numbers less than %d is %d\n", n, even);

    return 0;
}
