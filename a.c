#include <stdio.h>
#include <stdlib.h>


struct _libc_fpstate
{
  struct
  {
    unsigned int sign1:1;
    unsigned int unused:15;
    unsigned int sign2:1;
    unsigned int exponent:14;
    unsigned int j:1;
    unsigned int mantissa1:31;
    unsigned int mantissa0:32;
  } fpregs;
  unsigned int fpsr:32;
  unsigned int fpcr:32;
  unsigned char ftype[8];
  unsigned int init_flag;
};


int main()
{
    struct _libc_fpstate fpstat_;

    return 0;
}



