#include <stdlib.h>


struct Data <T>
{
    T a;
    T b;
};

struct Data2<T,T2>
{
    T a;
    T2 b;
};

impl Data2<T,T2>
{
    int fun(Data2<T,T2>* self) {
        return 2;
    }
}

impl Data <T>
{
    int fun(Data<T>* self,int a, int b) {
        return a+b;
    }

    int fun2(Data<T>* self, int a, int b) {
        Data2<T, char*>*% c = Data2<int, char*>();
        return c.fun();
    }
}

int main()
{
    Data<int>*% a = new Data<int>;

    a.fun2(1, 2);

    return 0;
}
