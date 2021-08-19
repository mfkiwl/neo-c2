#include <stdio.h>
#include <stdlib.h>

void int::times(int n, void* parent, void (*fun)(void* parent))
{
    int i;
    for(i=0; i<n; i++) {
        fun(parent);
    }
}

struct sStruct<T>
{
    T a;
    T b;
};

impl sStruct<T>
{
    void fun(sStruct<T>* self, T xxx, void* parent, void (*fun)(void* parent, T a)) {
        fun(parent, xxx);
    }
}

int main(int argc, char** argv)
{
    int a = 1;
/*
    auto fun = int lambda(__current__* parent, int b, int c) {
        *parent.a = 4;
        return (*parent.a + b + c);
    }

    printf("%d\n", fun(__stack__, 1, 2));
    printf("a %d\n", a);

    times(3, __stack__, void lambda(__current__* parent) {
        puts("HELLO LAMBDA");
        printf("a %p\n", parent.a);
    });
*/

    3.times() {
        puts("HELLO METHOD BLOCK");
        printf("a %d\n", *parent.a);
    }

    sStruct<int>*% data = new sStruct<int>;
    data.fun(123, __stack__, void lambda(__current__* parent, int a) {
        printf("%d\n", a);
    });
    data.fun(123) {
        puts("HELLO GENERICS METHOD BLOCK");
        printf("%d\n", it);
    }
}

