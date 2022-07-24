// program to add two numbers

#include <stdio.h>

void main(){
    int a, b, c;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    c = a + b;
    printf("Sum of %d and %d is %d\n", a, b, c);
}