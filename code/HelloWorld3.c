#include <come.h>

int main()
{
    xassert("xaasert test", true);

    xassert("xsprintf test", strcmp(xsprintf("AAA"), "AAA") == 0);

    xassert("string test", strcmp(string("AAA"), "AAA") == 0);

    vector<int>*% v = new vector<int>.initialize();

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    xassert("vector test1", v.item(0, -1) == 1 && v.length() == 3);
    
    return 0;
}
