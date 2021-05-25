#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>

struct Data <T>
{
    int a;
    int b;
};

impl Data <T>
{
    void fun(Data<T>* self,int a, int b) {
        return a+b;
    }
}

int main()
{
    Data<int>*% a = Data<int>();

//    a.fun(1,2);
//    a.fun(3,4);


    return 0;
}
