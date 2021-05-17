int puts(const char* msg);
int printf(const char *format, ...);

typedef long size_t;

size_t strlen(const char *s);

void *calloc(size_t nmemb, size_t size);
void free(void *ptr);

int strcmp(const char* s1, const char* s2);

void exit(int status);

typedef char*% string;

char *strcpy(char *dest, const char *src);

char *strncpy(char *dest, const char *src, size_t n);

int strcmp(const char *s1, const char *s2);

void xassert(const char* msg, bool exp)
{
    printf(msg);
    printf("...");

    if(exp) {
        puts("ok");
    }
    else {
        puts("false");
        exit(2);
    }
}

string string(char* str)
{
    int len = strlen(str) + 1;
    char%* msg = new char[len];

    strncpy(msg, str, len);

    return msg;
}

string string2(char* str) 
{
    return string(str);
}

inline void inline_fun() 
{
    puts("HELLO WORLD");
}

inline void inline_fun2(char* msg)
{
    puts(msg);
}


inline void inline_fun3(int x, int y)
{
    printf("%d\n", x + y);
}

inline int inline_fun4(int x, int y)
{
    return x + y;
}

inline int inline_fun5(int x, int y)
{
    return inline_fun4(x, y);
}

inline string string3(char* msg)
{
    return string(msg);
}

struct sData
{
    int a;
    int b;
};

struct sUndefinedStruct;

struct sUndefinedStruct2 {
    struct sUndefinedStruct* data;
};

struct sUndefinedStruct {
    int data;
    int data2;
};

struct sAnonymousStruct {
    struct { int a; int b; } data;
};

enum eEnum { kEnumA, kEnumB, kEnumC };

enum { kEnumD, kEnumE, kEnumF };

enum eEnum2 { kEnumG, kEnumH, kEnumI } AAA;

enum { kEnumJ, kEnumK, kEnumL } BBB;

union uData {
    int data1;
    long data2;

    struct { int a; long b; long c; } data3;
} gUnionData;

int gGlobalArray[3];
int gGlobalArray2[3][3];

int gGlobalArray3[3] = {
    1,2,3
};

int gGlobalArray4[3][2] = {
    1,2, 3,4, 5,6
};

int gGlobalArray5[2][3][4] = {
    1,2,3,4, 5,6,7,8, 9,10,11,12,
    13,14,15,16, 17,18,19,20, 21,22,23,24
};

char gGlobalString[] = "ABC";

char* gGlobalArray6[3] = { "AAA", "BBB", "CCC" };

char gGlobalArray7[4] = { "ABC" };

char gGlobalArray8[4] = "ABC";

/*
struct sGenericsData<T>
{
    T data;
    T data2;
};
*/

int vasprintf(char **strp, const char *fmt, va_list ap);

string xsprintf(char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    char* tmp;
    int len = vasprintf(&tmp, msg, args);
    va_end(args);

/*
    if(len < 0) {
        fprintf(stderr, "can't get heap memory. Heap memory number is %d. xsprintf len %d\n", gNumMemAlloc, len);

        exit(2);
    }
*/

    return dummy_heap tmp;
}

void funA()
{
    static int xxx = 1;
    printf("%d\n", xxx);
    xxx++;
}

int funB(int x, int y)
{
    return x + y;
}

int main()
{
    printf("HELLO WORLD\n");

    xassert("assert test", true);
    xassert("exp test", 1 < 2);
    xassert("exp2 test", 2 > 1);
    xassert("exp3 test", 1 >= 1);
    xassert("exp4 test", 1 <= 1);
    xassert("exp5 test", 1 == 1);
    xassert("exp6 test", 1 != 2);
    xassert("exp7 test", 1+1 == 2);
    xassert("exp8 test", 1-1 == 0);
    xassert("exp9 test", 1*2 == 2);
    xassert("exp10 test", 2/2 == 1);
    xassert("exp11 test", 3%2 == 1);

    int a = 1 + 1;

    xassert("var test", a == 2);

    xassert("long test", 1L + 1L == 2L);

    xassert("auto cast test", 1L + 1 == 2);

    string b = string("ABC");

    xassert("string test", strcmp(b, "ABC") == 0);

    xassert("string test2", strcmp(string("DEF"), "DEF") == 0);

    xassert("string test3", strcmp(string2("GHI"), "GHI") == 0);

    inline_fun();

    inline_fun2("HELLO HELLO");

    inline_fun3(1,2);

    xassert("inline function test", inline_fun4(1, 2) == 3);

    xassert("inline function test2", inline_fun5(1, 2) == 3);

    xassert("inline function test3", strcmp(string3("GHI"), "GHI") == 0);

    sData c;

    c.a = 1;

    xassert("structore test", c.a == 1);


    sUndefinedStruct d;

    d.data = 111;

    xassert("undefined struct test1", d.data == 111);

    sUndefinedStruct2 e;

    struct { int a; int b; } f;

    struct AnonymousStruct { int a } g;

    sAnonymousStruct h;

    xassert("enum test", kEnumA == 0);
    xassert("enum test2", kEnumD == 0);
    xassert("enum test3", kEnumG == 0);
    xassert("enum test4", kEnumJ == 0);

    enum ENUMENUM { kEnumX, kEnumY, kEnumZ } i;
    enum { kEnumX2, kEnumY2, kEnumZ2 } j;

    xassert("enum test5", kEnumX == 0);
    xassert("enum test6", kEnumX2 == 0);

    const int k = 1;

    xassert("constant test", k == 1);

    xassert("sizeof test", sizeof(long long int) == 8);

    uData l;

    l.data1 = 111;

    xassert("union test", l.data1 == 111);

    l.data2 = 222;

    xassert("union test2", l.data2 == 222);

    xassert("union test3", l.data1 != 111);

    gUnionData.data1 = 123;

    xassert("union test4", gUnionData.data1 == 123);

    int m[5];

    m[0] = 123;

    xassert("array test", m[0] == 123);

    int n[5][5];

    n[1][2] = 123;

    xassert("array test2", n[1][2] == 123);

    int o[5][5][5];

    o[1][2][3] = 123;

    xassert("array test3", o[1][2][3] == 123);

    int p[5][5][5][5];

    int q = 123;

    int* r = &q;

    xassert("pointer test", *r == 123);

    int s[5][5];

    int* t = &s[1][0];

    *t = 123;

    xassert("pointer test2", s[1][0] == 123);

    int u[5][5];

    u[1][0] = 123;

    int* v = u[1];

    *v = 234;

    xassert("pointer test3", u[1][0] == 234);

    int w[5] = { 1,2,3,4,5 };

    xassert("array test4", w[1] == 2);

    int x[3][2] = { 1,2, 3,4, 5,6 };

    xassert("array test5", x[2][0] == 5);
    xassert("array test6", x[1][1] == 4);

    int y[2][3][2] = { 1,2, 3,4, 5,6
                     , 7,8, 9,10, 11,12 };

    xassert("array test7", y[0][1][0] == 3);
    xassert("array test8", y[1][2][1] == 12);

    gGlobalArray[1] = 2;

    xassert("global array", gGlobalArray[1] == 2);

    gGlobalArray2[1][1] = 2;

    xassert("global array2", gGlobalArray2[1][1] == 2);

    xassert("global array3", gGlobalArray3[0] == 1);

    xassert("global array4", gGlobalArray4[2][1] == 6);

    xassert("global array5", gGlobalArray5[1][2][0] == 21);

    int len = 5;

    int z[len];

    z[3] = 1;

    xassert("array test9", z[3] == 1);

    xassert("global variable test", strcmp(gGlobalString, "ABC") == 0);

    xassert("global variable test2", strcmp(gGlobalArray6[1], "BBB") == 0);

    char* aa[3] = { "AAA", "BBB", "CCC" };

    xassert("array test9", strcmp(aa[0], "AAA") == 0);

    xassert("global variable test3", strcmp(gGlobalArray7, "ABC") == 0);

    xassert("global variable test3", strcmp(gGlobalArray8, "ABC") == 0);

    char str[4] = "ABC";

    xassert("array test10", strcmp(str, "ABC") == 0);

    char str2[4] = { 'A', 'B', 'C', '\0' };

    xassert("array test11", strcmp(str2, "ABC") == 0);

    char str3[4] = { "ABC" };

    xassert("array test12", strcmp(str3, "ABC") == 0);

    char* msx = "MSX";
    puts(xsprintf("%s", msx));


    funA();
    funA();

    int (*fun)(int, int) = funB;

    xassert("fun pointer test", fun(1, 2) == 3);


/*
    sGenericsData<int> data;
*/

/*
    int d = 0;
    int e = 1;

    int f = e / d;
*/

    return 0;
}
