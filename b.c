#include <stdio.h>

struct sB {
    char mName[128];
    int mIndex;
    char* mType;
};

struct sA {
    int a;
    struct sB g[128];
    int b;
    int c;

    int d;

    struct sA* mParent;
    struct sA* mNext;
};

int main()
{
    printf("sA %lu\n", sizeof(struct sA));

    return 0;
}
