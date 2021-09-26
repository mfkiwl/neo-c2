#include <stdio.h>
#include <stdlib.h>

int main()
{
    system("cpp -I code -U__GNUC__ -DNEOC_GC code/HelloWorld9.c  > code/HelloWorld9.c.i");

    return 0;
}
