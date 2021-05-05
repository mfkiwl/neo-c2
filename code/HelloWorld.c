
int puts(const char* msg);
int printf(const char *format, ...);

void exit(int status);

/*
typedef string char*%;

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

    int a = 1;
    a = 2;

    int b = a + 1;

    return 0;
}
