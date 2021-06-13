#include <stdlib.h>

char*% fun()
{
    return new char[128];
}


int main(int argc, char** argv)
{
    var a = new char[128];
    var b = nomove a;

    var c = nomove fun();

    return 0;
}
