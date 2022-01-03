#include <stdio.h>

struct sData
{
    int a;
    int b;
};

sData fun(int a, int b)
{
    if(true) {
        sData data;
        data.a = a;
        data.b = b;
        return data
    }
}

int main()
{
    sData result = fun(1,2);
    
    printf("%d %d\n", result.a, result.b);
    
    return 0;
}

