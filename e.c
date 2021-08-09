#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct sStruct {
    int a;
    int b;
};

int main()
{
    int x = 0;
    __builtin_assume(x == 0);

    unsigned long long y = __builtin_readcyclecounter();

    struct sStruct s;

    //__builtin_dump_struct(&s, &printf);
    
    //__builtin_shufflevector(v1, v1, 0, 1, 2, 3);

    //__builtin_convertvector(src_vec, dst_vec_type)

    uint8_t x1 = 1;
    uint8_t rev_x1 = __builtin_bitreverse8(x1);
    uint16_t x2 = 1;
    uint16_t rev_x2 = __builtin_bitreverse16(x2);
    uint32_t x3 = 1;
    uint32_t rev_x3 = __builtin_bitreverse32(x3);
    uint64_t x4 = 1;
    uint64_t rev_x4 = __builtin_bitreverse64(x4);

    uint8_t x11 = 1;
    uint8_t y11 = 1;

    uint8_t rot_x = __builtin_rotateleft8(x11, y11);

    uint16_t y22 = 1;
    uint16_t x22 = 1;

    uint16_t rot_x2 = __builtin_rotateleft16(x22, y22);

    uint32_t y33 = 1;
    uint32_t x33 = 1;

    uint32_t rot_x3 = __builtin_rotateleft32(x33, y33);

    uint64_t y44 = 1;
    uint64_t x44 = 1;

    uint64_t rot_x4 = __builtin_rotateleft64(x44, y44);

    uint8_t rot_xr = __builtin_rotateright8(x11, y11);
    uint16_t rot_xr2 = __builtin_rotateright16(x22, y22);
    uint32_t rot_xr3 = __builtin_rotateright32(x33, y33);
    uint64_t rot_xr4 = __builtin_rotateright64(x44, y44);

//    unsigned *xz, *yz, *zz, carryin=0, carryout;
//    zz[0] = __builtin_addc(xz[0], yz[0], carryin, &carryout);

    double xy;
    double xzz = __builtin_canonicalize(xy);

    float ax;
    ax = __builtin_canonicalizef(ax);

    long double xxx;
    long YYY = __builtin_canonicalizel(xxx);

//    void *ppppp = __builtin_memchr("foobar", 'b', 5);

    void *pxy, *pxc;
    __builtin_memcpy_inline(pxy, pxc, 128);

//    char* file = __builtin_FILE();

//    puts(file);

    int* a = malloc(sizeof(int));
    long size = __builtin_object_size(a, 0);
    long size2 = __builtin_dynamic_object_size(a, 0);

    return 0;
}

