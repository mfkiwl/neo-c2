# 1 "src/01int.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "src/01int.c"
# 1 "src/common.h" 1
# 1 "/usr/local/include/neo-c2.h" 1 3


# 2 "/usr/local/include/neo-c2.h" 3
```
if echo $ARG | sed -e 's/-no-gc/NEOC_NO_GC/' | grep NEOC_NO_GC 1> /dev/null 2> /dev/null
then
    cat $PREFIX/include/neo-c2-no-gc.h | cpp -I . -U__GNUC__
else
    cat $PREFIX/include/neo-c2-gc.h | cpp -I . -U__GNUC__
fi
```
# 2 "src/common.h" 2


# 3 "src/common.h"
struct sNode
{
    enum { kIntValue, kStringValue } kind;

    char* fname;
    int sline;

    union {
        int intValue;
        string stringValue;
    } value;
};



bool parse(char* fname, list<sNode*>* nodes, buffer* codes);
bool compile(sNode* node, buffer* codes);
bool run(int* p);

void skip_spaces(char** p, int* sline);
# 2 "src/01int.c" 2
# 1 "/usr/include/ctype.h" 1 3 4
# 25 "/usr/include/ctype.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 424 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 1 3 4
# 442 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 443 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/long-double.h" 1 3 4
# 444 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 425 "/usr/include/features.h" 2 3 4
# 448 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 1 3 4
# 10 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 2 3 4
# 449 "/usr/include/features.h" 2 3 4
# 26 "/usr/include/ctype.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 28 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4



# 30 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;






typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;



typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
# 140 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 1 3 4
# 141 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;
# 27 "/usr/include/ctype.h" 2 3 4


# 39 "/usr/include/ctype.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 36 "/usr/include/endian.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/endian.h" 1 3 4
# 37 "/usr/include/endian.h" 2 3 4
# 60 "/usr/include/endian.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 1 3 4
# 33 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
static inline __uint16_t
__bswap_16 (__uint16_t __bsx)
{



  return ((__uint16_t) ((((__bsx) >> 8) & 0xff) | (((__bsx) & 0xff) << 8)));

}






static inline __uint32_t
__bswap_32 (__uint32_t __bsx)
{



  return ((((__bsx) & 0xff000000u) >> 24) | (((__bsx) & 0x00ff0000u) >> 8) | (((__bsx) & 0x0000ff00u) << 8) | (((__bsx) & 0x000000ffu) << 24));

}
# 69 "/usr/include/x86_64-linux-gnu/bits/byteswap.h" 3 4
 static inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{



  return ((((__bsx) & 0xff00000000000000ull) >> 56) | (((__bsx) & 0x00ff000000000000ull) >> 40) | (((__bsx) & 0x0000ff0000000000ull) >> 24) | (((__bsx) & 0x000000ff00000000ull) >> 8) | (((__bsx) & 0x00000000ff000000ull) << 8) | (((__bsx) & 0x0000000000ff0000ull) << 24) | (((__bsx) & 0x000000000000ff00ull) << 40) | (((__bsx) & 0x00000000000000ffull) << 56));

}
# 61 "/usr/include/endian.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/uintn-identity.h" 1 3 4
# 32 "/usr/include/x86_64-linux-gnu/bits/uintn-identity.h" 3 4
static inline __uint16_t
__uint16_identity (__uint16_t __x)
{
  return __x;
}

static inline __uint32_t
__uint32_identity (__uint32_t __x)
{
  return __x;
}

static inline __uint64_t
__uint64_identity (__uint64_t __x)
{
  return __x;
}
# 62 "/usr/include/endian.h" 2 3 4
# 40 "/usr/include/ctype.h" 2 3 4






enum
{
  _ISupper = ((0) < 8 ? ((1 << (0)) << 8) : ((1 << (0)) >> 8)),
  _ISlower = ((1) < 8 ? ((1 << (1)) << 8) : ((1 << (1)) >> 8)),
  _ISalpha = ((2) < 8 ? ((1 << (2)) << 8) : ((1 << (2)) >> 8)),
  _ISdigit = ((3) < 8 ? ((1 << (3)) << 8) : ((1 << (3)) >> 8)),
  _ISxdigit = ((4) < 8 ? ((1 << (4)) << 8) : ((1 << (4)) >> 8)),
  _ISspace = ((5) < 8 ? ((1 << (5)) << 8) : ((1 << (5)) >> 8)),
  _ISprint = ((6) < 8 ? ((1 << (6)) << 8) : ((1 << (6)) >> 8)),
  _ISgraph = ((7) < 8 ? ((1 << (7)) << 8) : ((1 << (7)) >> 8)),
  _ISblank = ((8) < 8 ? ((1 << (8)) << 8) : ((1 << (8)) >> 8)),
  _IScntrl = ((9) < 8 ? ((1 << (9)) << 8) : ((1 << (9)) >> 8)),
  _ISpunct = ((10) < 8 ? ((1 << (10)) << 8) : ((1 << (10)) >> 8)),
  _ISalnum = ((11) < 8 ? ((1 << (11)) << 8) : ((1 << (11)) >> 8))
};
# 79 "/usr/include/ctype.h" 3 4
extern const unsigned short int **__ctype_b_loc (void)
     ;
extern const __int32_t **__ctype_tolower_loc (void)
     ;
extern const __int32_t **__ctype_toupper_loc (void)
     ;
# 108 "/usr/include/ctype.h" 3 4
extern int isalnum (int) ;
extern int isalpha (int) ;
extern int iscntrl (int) ;
extern int isdigit (int) ;
extern int islower (int) ;
extern int isgraph (int) ;
extern int isprint (int) ;
extern int ispunct (int) ;
extern int isspace (int) ;
extern int isupper (int) ;
extern int isxdigit (int) ;



extern int tolower (int __c) ;


extern int toupper (int __c) ;




extern int isblank (int) ;
# 142 "/usr/include/ctype.h" 3 4
extern int isascii (int __c) ;



extern int toascii (int __c) ;



extern int _toupper (int) ;
extern int _tolower (int) ;
# 237 "/usr/include/ctype.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/locale_t.h" 1 3 4
# 22 "/usr/include/x86_64-linux-gnu/bits/types/locale_t.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/__locale_t.h" 1 3 4
# 28 "/usr/include/x86_64-linux-gnu/bits/types/__locale_t.h" 3 4
struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
};

typedef struct __locale_struct *__locale_t;
# 23 "/usr/include/x86_64-linux-gnu/bits/types/locale_t.h" 2 3 4

typedef __locale_t locale_t;
# 238 "/usr/include/ctype.h" 2 3 4
# 251 "/usr/include/ctype.h" 3 4
extern int isalnum_l (int, locale_t) ;
extern int isalpha_l (int, locale_t) ;
extern int iscntrl_l (int, locale_t) ;
extern int isdigit_l (int, locale_t) ;
extern int islower_l (int, locale_t) ;
extern int isgraph_l (int, locale_t) ;
extern int isprint_l (int, locale_t) ;
extern int ispunct_l (int, locale_t) ;
extern int isspace_l (int, locale_t) ;
extern int isupper_l (int, locale_t) ;
extern int isxdigit_l (int, locale_t) ;

extern int isblank_l (int, locale_t) ;



extern int __tolower_l (int __c, locale_t __l) ;
extern int tolower_l (int __c, locale_t __l) ;


extern int __toupper_l (int __c, locale_t __l) ;
extern int toupper_l (int __c, locale_t __l) ;
# 327 "/usr/include/ctype.h" 3 4

# 3 "src/01int.c" 2


# 4 "src/01int.c"
void skip_spaces(char** p, int* sline)
{
    while(**p == ' ' || **p == '\t' || (**p == '\n' && (*sline)++)) {
        (*p)++;
    }
}

sNode* create_int_node(int value, char* fname, int sline)
{
    sNode* result = new sNode;

    result.kind = kIntValue;

    result.fname = string(fname);
    result.sline = sline;
    result.value.intValue = value;

    return result;
}

sNode* exp_node(char** p, char* fname, int* sline)
{
    if(
# 26 "src/01int.c" 3 4
      ((*__ctype_b_loc ())[(int) ((
# 26 "src/01int.c"
      **p
# 26 "src/01int.c" 3 4
      ))] & (unsigned short int) _ISdigit)
# 26 "src/01int.c"
                  ) {
        int n = 0;
        while(
# 28 "src/01int.c" 3 4
             ((*__ctype_b_loc ())[(int) ((
# 28 "src/01int.c"
             **p
# 28 "src/01int.c" 3 4
             ))] & (unsigned short int) _ISdigit)
# 28 "src/01int.c"
                         ) {
            n = n * 10 + (**p - '0');
            (*p)++;
        }
        skip_spaces(p, sline);

        return create_int_node(n, fname, sline);
    }

    return null;
}

bool expression(char** p, sNode** node, char* fname, int* sline)
{
    *node = exp_node(p, fname, sline);

    if(*node == null) {
        return false;
    }

    return true;
}

bool parse(char* fname, list<sNode*>* nodes, buffer* codes)
{
    FILE* f = fopen(fname, "r");

    if(f == null) {
        fprintf(stderr, "file %s is not found\n", fname);
        return false;
    }

    buffer* source = new buffer.initialize();

    char line[4096];

    while(fgets(line, 4096, f) != null)
    {
        line[strlen(line)-1] = '\0';
        source.append_str(line);
    }

    fclose(f);

    char* p = source.to_string();
    int sline = 1;

    while(*p) {
        sNode* node = null;
        if(!expression(&p, &node, fname, &sline)) {
            fprintf(stderr, "%s %d: unexpected character %c\n", fname, sline, *p);
            return false;
        }

        nodes.push_back(node);
    }

    return true;
}

bool compile(sNode* node, buffer* codes)
{
    if(node.kind == kIntValue) {
        codes.append_int(1);
        codes.append_int(node.value.intValue);
    }

    return true;
}

bool run(int* p)
{
    if(*p == 1) {
        p++;
        int value = *p;
        p++;

        printf("int value %d\n", value);
    }

    return true;
}
