//#include <come.h>

struct sA {
    int a;
    char* b;
};

int fun()
{
    return 1;
}

union uA {
    int a
    char* b;
    int** c;
};

enum eA {
    kA, kB, kC
};

typedef int tType;

struct sB {
    int a;
    char* b;
    struct sB* c;
};

int main()
{
    int a = 1;
    a + 1;
    int lambda() { return 1 };

    struct sA b;
    b;

    union uA c;
    c;

    tType d;
    d;

    eA e;
    e;

    sB f;
    f;

