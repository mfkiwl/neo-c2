#include <stdarg.h>
#include <stdio.h>

void aaa(const char* msg, ...)
{
    char msg2[1024];

    va_list args;
    va_start(args, msg);
    vsnprintf(msg2, 1024, msg, args);
    va_end(args);

puts(msg2);
}

int main(int argc, char** argv)
{
    aaa("%s %d", "AAA", 1 + 1);

    return 0;
}
