#include <come.h>


int main()
{
    var l = new list<int>.initialize();

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    
    foreach(it, l.sublist(1,3)) {
        printf("%d\n", it);
    }


    return 0;
}

