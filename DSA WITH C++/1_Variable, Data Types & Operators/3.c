// Type Casting

#include <stdio.h>

int main() {
    char str = 'A'; // Use single quotes for characters
    int value = str; // Implicit casting from char to int

    printf("%d\n", value); // Will print ASCII value of 'A' (65)

    double price = 10.21; // Missing semicolon fixed
    int newprice = (int)price; // Explicit casting

    printf("%d\n", newprice); // Will print 10

    return 0;
}
