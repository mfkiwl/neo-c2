
#include <stdio.h>

struct sA
{
    int b;
    char c;
    char d;
};

int main()
{
    printf("sA %lu\n", sizeof(struct sA));
    return 0;
}



