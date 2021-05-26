#include <stdlib.h>

struct sData3<T>
{
    T data;
    T data2;
};

struct sDataX <T>
{
    T data;
};

impl sData3<T>
{
    int fun(sData3<T>* self, T data)
    {
        T data2 = data;

        sDataX<T>*% x = sDataX<T>();

        x.data = data;

        self.data = data;

        return x.data;
    }
}

int main()
{
    sData3<int>*% xyi = sData3<int>();

    xyi.fun(123);

    return 0;
}
