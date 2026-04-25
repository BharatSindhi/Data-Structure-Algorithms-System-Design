#include <stdio.h>
#include <stdbool.h>  // Include for 'bool', 'true', and 'false'

int main() {
    int n;
    bool prime = true;

    printf("Enter the number: ");
    scanf("%d", &n);

    if (n <= 1) {
        prime = false;
    } else {
        for (int i = 2; i <= n / 2; i++) {
            if (n % i == 0) {
                prime = false;
                break;
            }
        }
    }

    if (prime) {
        printf("%d is a prime number.\n", n);
    } else {
        printf("%d is not a prime number.\n", n);
    }

    return 0;
}
