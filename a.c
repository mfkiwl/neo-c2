#include <stdio.h>

struct sA
{
    char a;
    long b[3];
    char c;
};

struct sB
{
    struct sA a;
    char c;
    int b;
};

int main()
{
    puts("RIGHT");
    printf("sA %lu\n", sizeof(struct sA));
    printf("sB %lu\n", sizeof(struct sB));
    return 0;
}



