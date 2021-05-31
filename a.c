#include <stdlib.h>

char*% get_char()
{
    return new char[123];
}

inline void inline_funX(char* a)
{
    int b = 123;
}

inline void inline_funX2(char*% a)
{
    int c = 123;
}

int main()
{
    inline_funX(new char[123]);
    inline_funX2(new char[123]);

    inline_funX(get_char());
    inline_funX2(get_char());

    return 0;
}
