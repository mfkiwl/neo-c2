#include <stdlib.h>

struct Data <T>
{
    T a;
    T b;
};

impl Data <T>
{
    int fun(Data<T>* self,int a, int b) {
        return a+b;
    }
}

int main()
{
    Data<int>*% a = Data<int>();

    a.fun(1,2);
    a.fun(3,4);

    return 0;
}
