#include <stdio.h>

int main() {
    int n;
    printf("Enter the number: ");
    scanf("%d", &n);

    int sum = 0;

    for (int i = 0; i < n; i++) {
        if (i % 3 == 0) {
            sum += i;
        }
    }

    printf("Sum of numbers divisible by 3 less than %d is: %d\n", n, sum);
    
    return 0;
}
