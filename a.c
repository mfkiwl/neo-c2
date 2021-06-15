#include <come.h>

struct Data
{
    char array[128];
};

int main(int argc, char** argv)
{
    Data data;

    data.array[0] = 'A';
    data.array[1] = '\0';

    puts(data.array);

    return 0;
}
