#include <stdio.h>


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x, y;
    scanf("%d", &x);
    scanf("%d", &y);
    swap(&x, &y);
    printf("%d, %d\n", x, y);
    return 0;
}