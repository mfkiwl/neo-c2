#include <stdio.h>

typedef int (*fNativeFun)(int a, int b);

int fun(int a, int b)
{
    return a + b;
}

int main()
{
    fNativeFun a = fun;
    
    printf("%d\n", a(1,2));
    
    return 0;
}

