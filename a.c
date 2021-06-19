#include <stdarg.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    ovec_value[0] = 1;
    printf("%d\n", ovec_value[0]);

    return 0;
}
