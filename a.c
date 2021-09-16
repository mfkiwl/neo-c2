#include <stdio.h>


void (*sigset(int, void (*)(int)))(int);


int main()
{
    printf("%p\n", sigset);
}
