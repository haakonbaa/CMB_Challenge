#include <stdio.h>

int main(void) {
    int a, b;
    //printf("Enter the values of a and b: ");
    if (scanf("%d%d", &a, &b) == 2) {
        printf("a=%d b=%d\n", a, b);
    }
    return 0;
}