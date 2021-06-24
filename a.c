
#include <stdio.h>

struct sA
{
    int a;
    short b;
    char d;
    int e;
};

/*
struct sA
{
    int a[30];
    char b;
    int c[3];
    double d[3];
    float h[3];
};
*/

int main()
{
    puts("RIGHT");
    printf("sA %lu\n", sizeof(struct sA));
    return 0;
}



