#include <neo-c2.h>

struct sObj {
    int a;
    int b;
};

int main()
{
    sObj* obj = new (GC) sObj;

    obj.a = 1;
    obj.b = 2;

    xassert("gc test", obj.a == 1 && obj.b == 2);

    return 0;
}
