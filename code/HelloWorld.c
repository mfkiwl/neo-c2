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

/*
string xsprintf(char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    char* tmp;
    int len = vasprintf(&tmp, msg, args);
    va_end(args);

    if(len < 0) {
        fprintf(stderr, "can't get heap memory. Heap memory number is %d. xsprintf len %d\n", gNumMemAlloc, len);

        exit(2);
    }

    return dummy_heap tmp;
}
*/

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

/*
struct sGenericsData<T>
{
    T data;
    T data2;
};
*/

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
