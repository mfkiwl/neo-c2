#include <string.h>
#include <stdio.h>

char* xstrncpy(char* des, char* src, size_t size)
{
    char* result;

    result = strncpy(des, src, size-1);
    des[size-1] = 0;

    return result;
}

#define PATH_MAX 128

struct sParserInfoStruct
{
    char sname[PATH_MAX];
};

typedef struct sParserInfoStruct sParserInfo;

int main(int argc, char** argv)
{
    sParserInfo info;

    xstrncpy(info.sname, fname, PATH_MAX);

    return 0;
}
