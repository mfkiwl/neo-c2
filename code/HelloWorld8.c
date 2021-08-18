#include <stdio.h>

void three_times(void* parent, void (*fun)(void* parent))
{
    int i;
    for(i=0; i<3; i++) {
        fun(parent);
    }
}

int main(int argc, char** argv)
{
    int a = 1;
    auto fun = int lambda(__current__* parent, int b, int c) {
        *parent.a = 4;
        return (*parent.a + b + c);
    }

    printf("%d\n", fun(__stack__, 1, 2));
    printf("a %d\n", a);

    three_times(__stack__, void lambda(__current__* parent) {
        puts("HELLO LAMBDA");
        printf("a %d\n", *parent.a);
    });
}
