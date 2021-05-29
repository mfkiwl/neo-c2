#include <come.h>

int main()
{
    xassert("xaasert test", true);

    xassert("xsprintf test", strcmp(xsprintf("AAA"), "AAA") == 0);

    xassert("string test", strcmp(string("AAA"), "AAA") == 0);

    vector<int>*% v = new vector<int>.initialize();
    
    return 0;
}
