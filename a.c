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

void int_show(int self)
{
    printf("int_show %d\n", self);
}

struct sData {
    int value1;
    int value2;
};

sData*% sData(int value1, int value2)
{
    sData*% self = sData();

    self.value1 = value1;
    self.value2 = value2;

    return self;
}

void sData_finalize(sData* self)
{
    printf("finalize %d %d\n", self.value1, self.value2);
}

void sData_show(sData* self)
{
    printf("show %d %d\n", self.value1, self.value2);
}

int main()
{
    int*% value = int();

    *value = 123

    printf("value %d\n", *value);

    char*% value2 = string("ABC");

    printf("%s\n", value2);

    sData*% data = sData();

    data.value1 = 111;
    data.value2 = 222;

    data.show();

    3.show();

    sData*% data2 = sData(123, 345);

    data2.show();

    return 0;
}
