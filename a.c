#include <stdlib.h>
#include <stdio.h>

struct Data<T>
{
    T a;
};

impl Data <T>
{
    int fun(Data<T>* self,int a, int b) {
        return a+b;
    }
}

int main()
{
    Data<int>*% data = new Data<int>;

    data.fun(1, 2);

    return 0;
}
