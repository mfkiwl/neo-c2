#include <stdio.h>

void fun(int a, int b) 
{
    puts("version1");
}

void fun(int a, int b)
{
    inherit(a, b);
    puts("version 2");
}

void fun(int a, int b)
{
    inherit(a, b);
    printf("a %d b %d\n", a, b);
}

int main(int argc, char** argv)
{
    fun(1, 2);

    return 0;
}
