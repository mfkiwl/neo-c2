#include <come.h>

void fun(int~ pipe) 
{
    pipe = 4;
}

void fun2(int~ pipe2)
{
    sleep(1);
    pipe2 = 5;
}

int main() 
{
    int~ pipe;
    come fun(pipe);

    int~ pipe2;
    come fun2(pipe2);

    for(bool end_flg = false; !end_flg; ) {
        select(pipe, pipe2) {
            case x = pipe2:
                end_flg = true;
                printf("x %d\n", x);
                break;

            case y = pipe: 
                end_flg = true;
                printf("y %d\n", y);
                break;

            default: 
                puts("AAA");
                break;
        }
    }

    join;
    
    puts("finish");
    
    return 0;
}
