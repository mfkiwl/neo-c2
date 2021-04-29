
int puts(const char* msg);
int printf(const char *format, ...);

void exit(int status);

void xassert(const char* msg, bool exp)
{
/*
    printf(msg);

    if(exp) {
        puts("ok");
    }
    else {
        puts("false");
        exit(2);
    }
*/
}

int main()
{
    printf("HELLO WORLD\n");

    xassert("assert test", true);

    return 0;
}
