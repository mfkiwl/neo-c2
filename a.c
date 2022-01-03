#include <stdio.h>

int main()
{
    int a = 1;
    switch(a) {
        case 1:
            puts("BBB");
            return 123;
            
        case 2:
            puts("AAA");
            return 1;
            
        default:
            return 0;
            break;
    }
    
    return 0;
}

