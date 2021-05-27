#include <stdlib.h>
#include <stdio.h>

struct GData<T>
{
    T data;
};

impl GData<T>
{
    void fun(GData<T>* self, char* a)
    {
    }
    void fun2(GData<T>* self, char*% a)
    {
    }
}

inline void fun(char* a)
{
    puts(a);
}

inline void fun2(char*% a)
{
    puts(a);
}

void fun3(char* a)
{
    puts(a);
}

void fun4(char*% a)
{
    puts(a);
}

int main()
{
    GData<int>*% xvi = new GData<int>;

    xvi.fun(new char[123]);
    xvi.fun2(new char[123]);

    char*% xy = new char[123];

    xvi.fun(xy);
    xvi.fun2(xy);

    fun(new char[123]);
    fun2(new char[123]);

    char*% aa = new char[123];
    fun2(aa);

    char*% bb = new char[123];
    fun2(bb);

    fun3(new char[123]);
    fun4(new char[123]);

    char*% a = new char[123];
    char*% b = a;
    fun4(b);

    char*% c = new char[123];
    fun3(c);

    return 0;
}
