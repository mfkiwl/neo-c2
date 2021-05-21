#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

char*% string(char* str)
{
    int len = strlen(str) + 1;
    char%* result = dummy_heap calloc(len, sizeof(char));

    strncpy(result, str, len);

    return result;
}

int main()
{
    int*% value = int();

    *value = 123

    printf("value %d\n", *value);

    char*% value2 = string("ABC");

    printf("%s\n", value2);

    return 0;
}
