#include <stdio.h>

int main() {
    int a = 10, b = 5;
    int result;

    // 1. Arithmetic Operators
    printf("Arithmetic Operators:\n");
    printf("a + b = %d\n", a + b);
    printf("a - b = %d\n", a - b);
    printf("a * b = %d\n", a * b);
    printf("a / b = %d\n", a / b);
    printf("a %% b = %d\n\n", a % b); // use %% to print %

    // 2. Relational Operators
    printf("Relational Operators:\n");
    printf("a == b: %d\n", a == b);
    printf("a != b: %d\n", a != b);
    printf("a > b : %d\n", a > b);
    printf("a < b : %d\n", a < b);
    printf("a >= b: %d\n", a >= b);
    printf("a <= b: %d\n\n", a <= b);

    // 3. Logical Operators
    printf("Logical Operators:\n");
    printf("(a > b) && (b > 0): %d\n", (a > b) && (b > 0));
    printf("(a < b) || (b > 0): %d\n", (a < b) || (b > 0));
    printf("!(a == b): %d\n\n", !(a == b));

    // 4. Bitwise Operators
    printf("Bitwise Operators:\n");
    printf("a & b = %d\n", a & b);  // AND
    printf("a | b = %d\n", a | b);  // OR
    printf("a ^ b = %d\n", a ^ b);  // XOR
    printf("~a = %d\n", ~a);        // NOT
    printf("a << 1 = %d\n", a << 1); // Left shift
    printf("a >> 1 = %d\n\n", a >> 1); // Right shift

    // 5. Assignment Operators
    printf("Assignment Operators:\n");
    result = a;
    result += b; printf("a += b: %d\n", result);
    result -= b; printf("a -= b: %d\n", result);
    result *= b; printf("a *= b: %d\n", result);
    result /= b; printf("a /= b: %d\n", result);
    result %= b; printf("a %%= b: %d\n\n", result);

    // 6. Unary Operators
    printf("Unary Operators:\n");
    int x = 10;
    printf("x = %d\n", x);
    printf("++x = %d\n", ++x); // pre-increment
    printf("x++ = %d\n", x++); // post-increment
    printf("--x = %d\n", --x); // pre-decrement
    printf("x-- = %d\n\n", x--); // post-decrement

    // 7. Ternary Operator
    printf("Ternary Operator:\n");
    int max = (a > b) ? a : b;
    printf("Max of a and b = %d\n\n", max);

    // 8. Special Operators
    printf("Special Operators:\n");
    printf("Size of int: %lu bytes\n", sizeof(int));
    int y = (a = 5, b = 10, a + b); // Comma operator
    printf("Value of y (comma operator): %d\n", y);

    return 0;
}
