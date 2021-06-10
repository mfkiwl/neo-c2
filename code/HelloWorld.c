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
    char%* msg = dummy_heap calloc(len, sizeof(char));

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

int vasprintf(char **strp, const char *fmt, va_list ap);

string xsprintf(char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    char* tmp;
    int len = vasprintf(&tmp, msg, args);
    va_end(args);

    return dummy_heap tmp;
}

static void funA()
{
    static int xxx = 1;
    printf("%d\n", xxx);
    xxx++;
}

int funB(int x, int y)
{
    return x + y;
}

void int_show(int self)
{
    printf("int_show %d\n", self);
}

struct sData2 {
    int value1;
    int value2;
};

sData2*% sData2(int value1, int value2)
{
    sData2*% self = new sData2;

    self.value1 = value1;
    self.value2 = value2;

    return self;
}

void sData2_finalize(sData2* self)
{
    printf("finalize %d %d\n", self.value1, self.value2);
}

void sData2_show(sData2* self)
{
    printf("show %d %d\n", self.value1, self.value2);
}

struct GenericsType<T, T2> 
{
    T item;
    T2 item2;
};

void fun(GenericsType<int, bool>* data)
{
    int a = 1;
}

void funX()
{
}

impl GenericsType<T,T2>
{
    void fun(GenericsType<T,T2>* self)
    {
        printf("%d %s\n", self.item, self.item2);
    }

    int fun2(GenericsType<T,T2>* self)
    {
        return self.item + 1;
    }

    int fun3(GenericsType<T,T2>* self) {
        GenericsType<int, char*>*% data = new GenericsType<int, char*>;

        data.item = 1;

        return self.fun2() + data.fun2();
    }

    int fun4(GenericsType<T,T2>* self) {
        T i = 1;
        T j = 2;
        return i + j;
    }
}

struct Data <T>
{
    T a;
    T b;
};

struct Data2<T,T2>
{
    T a;
    T2 b;
};

impl Data2<T,T2>
{
    int fun(Data2<T,T2>* self) {
        return 2;
    }
}

impl Data <T>
{
    int fun(Data<T>* self,int a, int b) {
        return a+b;
    }

    int fun2(Data<T>* self, int a, int b) {
        Data2<T, char*>*% c = new Data2<int, char*>;
        return c.fun();
    }
}

struct sData3<T>
{
    T data;
    T data2;
};

impl sData3<T>
{
    int fun(sData3<T>* self, T data)
    {
        self.data = data;

        return self.data;
    }
}

impl Data<T>
{
    void finalize(Data<T>* self) {
        xassert("Data finalizer", true);
    }
}

struct sData3<T>
{
    T data;
    T data2;
};

struct sDataX <T>
{
    T data;
};

impl sData3<T>
{
    int fun(sData3<T>* self, T data)
    {
        T data2 = data;
        sDataX<T>*% x = new sDataX<T>;

        xassert("generics test", data2 == 123);

        x.data = data;

        xassert("generics test", x.data == 123);

        self.data = data;

        xassert("generics test", self.data == 123);

        return x.data;
    }
}

struct GData<T>
{
    T data;
};

impl GData<T>
{
    GData<T>*% initialize(GData<T>*% self)
    {
        self.data = 123;

        return self;
    }

    void fun(GData<T>* self, char* a)
    {
    }
    void fun2(GData<T>* self, char*% a)
    {
    }
}

inline void inline_funX(char* a)
{
    puts(a);
}

inline void inline_funX2(char*% a)
{
    puts(a);
}

void normal_fun(char* a)
{
    puts(a);
}

void normal_fun2(char*% a)
{
    puts(a);
}

char*% get_char()
{
    return new char[123];
}

enum AAA
  {
    kA,
    kB = kA + 1,
    kC
};

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

    int ab = 1;

    ab++;

    xassert("operator test", ab == 2);

    int ac = 2;

    xassert("operator test2", ac % 3 == 2);

    xassert("operator test3", true && true);

    xassert("operator test4", false || true);

    char* ad = null;

    xassert("operator test5", ad == null);

    xassert("operator test5", !false);

    int ii=0;
    while(ii < 5) {
        printf("%d\n", ii);
        ii++;
    }

    for(int jj=0; jj<5; jj++) {
        printf("%d\n", jj);
    }

    {
        int a = 123;
        printf("%d\n", a);
    }
    {
        int a = 234;
        printf("%d\n", a);
    }

    switch(2) {
        case 1:
            puts("AAA");
            break;

        case 2:
            puts("BBB");
            break;
    }

    int kk = 0;

test_label:
    printf("kk %d\n", kk);
    kk++;
    if(kk < 5) {
        goto test_label;
    }


    xassert("conditional operator", 1 == 1 ? true: false);

    int bd = 2;
    int bf = 2;
    xassert("conditional operator", ((bd == 2) ? bf : 0) == 2);

    xassert("complement operator", (0x01 ^ 0xFF) == 0xFE);

    xassert("func name", strcmp(__func__, "main") == 0);

    int bg = 3;

    xassert("++", bg++ == 3);
    xassert("++", bg == 4);

    int bh = 4;

    xassert("--", bh-- == 4);
    xassert("--", bh == 3);

    xassert("--", --bh == 2);

    int bi = 5;

    bi += 4;

    xassert("+=", bi == 9);

    int bj = 4;
    bj *= 4;

    xassert("*=", bj == 16);
    xassert("++", ++bj == 17);
    xassert("++", bj == 17);

    int array[128];
    int* ppp = array;

    ppp++;

    xassert("pointer sub test", ppp - array == 1);

    int*% value = new int;

    *value = 123

    printf("value %d\n", *value);

    char*% value2 = string("ABC");

    printf("%s\n", value2);

    sData2*% data = new sData2;

    data.value1 = 111;
    data.value2 = 222;

    data.show();

    3.show();

    sData2*% data2 = sData2(123, 345);

    data2.show();

    GenericsType<int, char*>*% data4 = new GenericsType<int, char*>;

    data4.item = 123;
    data4.item2 = "aaa";

    xassert("generics type", data4.item == 123 && strcmp(data4.item2, "aaa") == 0);

    data4.fun();

    xassert("generics method call", data4.fun2() == 124);

    xassert("generics method call2", data4.fun3() == 126);

    xassert("generics method call3", data4.fun4() == 3);

    Data<int>*% axz = new Data<int>;

    xassert("generics method call4", axz.fun2(1,2) == 2);

    sData3<int>*% xyi = new sData3<int>;

    xassert("generics mthod call5", xyi.fun(123) == 123);

    GData<int>*% xvi = new GData<int>.initialize();

    xassert("xvi", xvi.data == 123);

    xvi.fun(new char[123]);
    xvi.fun2(new char[123]);

    char*% xy = new char[123];

    xvi.fun(xy);
    xvi.fun2(xy);

    xvi.fun(get_char());
    xvi.fun2(get_char());

    normal_fun(new char[123]);
    normal_fun2(new char[123]);

    char*% azizi = new char[123];

    normal_fun(azizi);
    normal_fun2(azizi);

    normal_fun(get_char());
    normal_fun2(get_char());

    char*% bzizi = new char[123];
    char*% czizi = bzizi;
    normal_fun2(czizi);

    inline_funX(new char[123]);
    inline_funX2(new char[123]);

    inline_funX(get_char());
    inline_funX2(get_char());

    char*% aazizizizizzizi = new char[123];
    inline_funX(aazizizizizzizi);

    char*% bbziziizizizizizzi = new char[123];
    inline_funX2(bbziziizizizizizzi);

    int abibibibibi[3];

    int* bbibibibibib = abibibibibi;

    bbibibibibib[0] = 123;

    xassert("pointer test", bbibibibibib[0] == 123);

    var lam = int lambda(int x, int y) { return x + y };

    xassert("lambda test", lam(1, 2) = 3);


    return 0;
}

