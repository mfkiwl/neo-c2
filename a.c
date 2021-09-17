#include <stdio.h>

int (*test(int,int))(int);
//void (*sigset(int, void (*fun)(int)))(int);
void (*sigset(int, void (*)(int)))(int);

extern void ( * GC_same_obj_print_proc)(void * ,
                                                   void * );


int main()
{
    int (*fun)(int, int);
    printf("%p\n", sigset);
    printf("%p\n", fun);
    printf("%p\n", test);
    printf("%p\n", GC_same_obj_print_proc);
}
