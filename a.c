#include <stdio.h>


int main()
{
    char c = 'd';
    switch(c) {
        case 'a':
            puts("AAA");
            break;
            
        case 'c':
            puts("CCC");
            break;
            
        case 'd': {
            int n = 1;
            switch(n) {
                case 1:
                    puts("111");
                    break;
                    
                case 2:
                    puts("222");
                    break;
            }
            }
            break;
    }

    return 0;
}

