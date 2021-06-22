#include <stdarg.h>
#include <stdio.h>

#define PARSER_ERR_MSG_MAX 128

struct sParserInfo {
    int no_output_err_msg;
};

int main(int argc, char** argv)
{
    static int output_num = 0;

    struct sParserInfo info;

    info.no_output_err_msg = 0;

    if(output_num < PARSER_ERR_MSG_MAX && !info.no_output_err_msg) {
        puts("AAA");
    }

    return 0;
}
