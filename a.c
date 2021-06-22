#include <string.h>
#include <stdio.h>

struct sFunctionStruct {
    char mParamNames[128][128];
};

void add_function_to_table(char** param_names)
{
    struct sFunctionStruct fun;

    fun.mParamNames[0][0] = 'a';
    fun.mParamNames[0][1] = '\0';

    puts(fun.mParamNames[0]);
}

int main(int argc, char** argv)
{
    char* param_names2[128];

    param_names2[0] = "AAA";
    param_names2[1] = "BBB";
    param_names2[2] = "CCC";

    puts(param_names2[0]);
    puts(param_names2[1]);
    puts(param_names2[2]);

    add_function_to_table(param_names2);

    return 0;
}
