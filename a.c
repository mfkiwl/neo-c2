#include <stdio.h>

extern void fun(int a, int b);
extern override void fun(int a, int b);
extern override void fun(int a, int b);

void fun(int a, int b) version 1
{
    puts("version1");
}

void fun(int a, int b) version 2
{
    inherit(a, b);
    puts("version 2");
}

void fun(int a, int b)
{
    inherit(a, b);
    puts("verion 3");
    printf("a %d b %d\n", a, b);
}

int main(int argc, char** argv)
{
    fun(1, 2);

    return 0;
}
