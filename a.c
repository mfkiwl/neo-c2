#include <neo-c2.h>

int main()
{
    list<char*>*% li = new list<char*>.initialize();
    
    li.push_back("1");
    li.push_back("2");
    li.push_back("3");
    li.push_back("4");
    li.push_back("5");
    
    li.map { return atoi(it); }.filter { return it > 3; }.each { printf("%d\n", it); }
    
    return 0;
}
