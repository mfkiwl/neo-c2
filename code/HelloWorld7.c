#include <come.h>

void fun(int@ pipe) 
{
    sleep(3);
    @pipe = 4;
    sleep(3);
    @pipe = 4;
    sleep(3);
    @pipe = 4;
}

void fun2(int@ pipe2)
{
    sleep(1);
    @pipe2 = 5;
    sleep(1);
    @pipe2 = 5;
    sleep(1);
    @pipe2 = 5;
}

int main() 
{
    int@ pipe;
    come fun(pipe);

    int@ pipe2;
    come fun2(pipe2);

    while(true) {
        come pselect {
            pipe {
                printf("pipe %d\n", @pipe);
            }

            pipe2 {
                printf("pipe2 %d\n", @pipe2);
            }

            default {
                puts("wating...");
            }
        }
    }

    come join;
    
    puts("finish");
    
    return 0;
}
