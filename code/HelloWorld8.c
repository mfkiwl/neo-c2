#include <stdio.h>

int main(int argc, char** argv)
{
    int a = 1;
    auto fun = int lambda(__current__* parent, int b, int c) {
        *parent.a = 4;
        return (*parent.a + b + c);
    }

    auto fun2 = int lambda(int x, int y) {
        y = 1;
        return x;
    }

    printf("%d\n", fun(__stack__, 1, 2));
    printf("a %d\n", a);
}
