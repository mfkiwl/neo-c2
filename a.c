#include <stdlib.h>
#include <stdio.h>

int main()
{
    int a[3];

    int* b = a;

    b[0] = 123;

    printf("%d\n", b[0]);

    return 0;
}
