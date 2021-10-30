#include <stdio.h>

extern int fun(char* str) version 1;

int fun(char* str) version 2
{
    int n = inherit(str);

    return n + 1;
}

int fun(char* str) version 3
{
    int n = inherit(str);

    return n + 1;
}

int fun(char* str) version 1
{
    puts(str);
    return 1;
}

int main()
{
    if(fun("HELLO MIXIN-LAYERS") == 3) {
        puts("OK");
    }
    int len = 35;
    len = (len + 3) & ~3;
    
    printf("len %d\n", len);

    return 0;
}

