#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    char buf[4];

    int f = open("LLL", O_RDONLY);

    read(f, buf, sizeof(int));

    int x = *(int*)buf;

    close(f);

    printf("%d\n", x);

    return 0;
}

