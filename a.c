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

char*% get_char()
{
    return new char[123];
}

int main()
{
    GData<int>*% xvi = new GData<int>;

    xvi.fun(new char[123]);
    xvi.fun2(new char[123]);

    char*% xy = new char[123];

    xvi.fun(xy);
    xvi.fun2(xy);

    xvi.fun(get_char());
    xvi.fun2(get_char());

    fun3(new char[123]);
    fun4(new char[123]);

    char*% a = new char[123];

    fun3(a);
    fun4(a);

    fun3(get_char());
    fun4(get_char());

    char*% b = new char[123];
    char*% c = b;
    fun4(c);

    fun(new char[123]);
    fun2(new char[123]);

    fun(get_char());
    fun2(get_char());

    char*% aa = new char[123];
    fun(aa);

    char*% bb = new char[123];
    fun2(bb);

    return 0;
}
