#include <stdarg.h>
#include <stdio.h>

typedef void (*LLVMDiagnosticHandler)(int, int);

int main(int argc, char** argv)
{
    LLVMDiagnosticHandler a;

    return 0;
}
