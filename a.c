#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
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
*/

char* string(char* str)
{
    int len = strlen(str) + 1;
    char* msg = calloc(len, sizeof(char));

    strncpy(msg, str, len);

    return msg;
}

int main()
{
    return 0;
}
