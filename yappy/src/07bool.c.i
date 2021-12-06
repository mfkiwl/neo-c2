# 1 "src/07bool.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "src/07bool.c"
# 1 "src/common.h" 1
# 1 "/usr/local/include/neo-c2.h" 1 3




# 1 "/usr/include/stdio.h" 1 3 4
# 27 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 33 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 3 4
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
# 34 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 2 3 4
# 28 "/usr/include/stdio.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 1 3 4
# 216 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 3 4

# 216 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 34 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 37 "/usr/include/stdio.h" 2 3 4

# 1 "/usr/include/x86_64-linux-gnu/bits/types.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 28 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4


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
# 39 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h" 1 3 4




# 1 "/usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h" 1 3 4
# 13 "/usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h" 3 4
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
# 6 "/usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h" 2 3 4




typedef struct _G_fpos_t
{
  __off_t __pos;
  __mbstate_t __state;
} __fpos_t;
# 40 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h" 1 3 4
# 10 "/usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h" 3 4
typedef struct _G_fpos64_t
{
  __off64_t __pos;
  __mbstate_t __state;
} __fpos64_t;
# 41 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/__FILE.h" 1 3 4



struct _IO_FILE;
typedef struct _IO_FILE __FILE;
# 42 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/FILE.h" 1 3 4



struct _IO_FILE;


typedef struct _IO_FILE FILE;
# 43 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h" 1 3 4
# 35 "/usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h" 3 4
struct _IO_FILE;
struct _IO_marker;
struct _IO_codecvt;
struct _IO_wide_data;




typedef void _IO_lock_t;





struct _IO_FILE
{
  int _flags;


  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;


  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;
  int _flags2;
  __off_t _old_offset;


  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];

  _IO_lock_t *_lock;







  __off64_t _offset;

  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
  size_t __pad5;
  int _mode;

  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};
# 44 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/types/cookie_io_functions_t.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/types/cookie_io_functions_t.h" 3 4
typedef __ssize_t cookie_read_function_t (void *__cookie, char *__buf,
                                          size_t __nbytes);







typedef __ssize_t cookie_write_function_t (void *__cookie, const char *__buf,
                                           size_t __nbytes);







typedef int cookie_seek_function_t (void *__cookie, __off64_t *__pos, int __w);


typedef int cookie_close_function_t (void *__cookie);






typedef struct _IO_cookie_io_functions_t
{
  cookie_read_function_t *read;
  cookie_write_function_t *write;
  cookie_seek_function_t *seek;
  cookie_close_function_t *close;
} cookie_io_functions_t;
# 47 "/usr/include/stdio.h" 2 3 4
# 56 "/usr/include/stdio.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stdarg.h" 1 3 4
# 99 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 57 "/usr/include/stdio.h" 2 3 4






typedef __off_t off_t;






typedef __off64_t off64_t;






typedef __ssize_t ssize_t;






typedef __fpos_t fpos_t;




typedef __fpos64_t fpos64_t;
# 133 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/stdio_lim.h" 1 3 4
# 134 "/usr/include/stdio.h" 2 3 4



extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;






extern int remove (const char *__filename) ;

extern int rename (const char *__old, const char *__new) ;



extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) ;
# 164 "/usr/include/stdio.h" 3 4
extern int renameat2 (int __oldfd, const char *__old, int __newfd,
        const char *__new, unsigned int __flags) ;







extern FILE *tmpfile (void) ;
# 183 "/usr/include/stdio.h" 3 4
extern FILE *tmpfile64 (void) ;



extern char *tmpnam (char *__s) ;




extern char *tmpnam_r (char *__s) ;
# 204 "/usr/include/stdio.h" 3 4
extern char *tempnam (const char *__dir, const char *__pfx)
     ;







extern int fclose (FILE *__stream);




extern int fflush (FILE *__stream);
# 227 "/usr/include/stdio.h" 3 4
extern int fflush_unlocked (FILE *__stream);
# 237 "/usr/include/stdio.h" 3 4
extern int fcloseall (void);
# 246 "/usr/include/stdio.h" 3 4
extern FILE *fopen (const char *restrict __filename,
      const char *restrict __modes) ;




extern FILE *freopen (const char *restrict __filename,
        const char *restrict __modes,
        FILE *restrict __stream) ;
# 270 "/usr/include/stdio.h" 3 4
extern FILE *fopen64 (const char *restrict __filename,
        const char *restrict __modes) ;
extern FILE *freopen64 (const char *restrict __filename,
   const char *restrict __modes,
   FILE *restrict __stream) ;




extern FILE *fdopen (int __fd, const char *__modes) ;





extern FILE *fopencookie (void *restrict __magic_cookie,
     const char *restrict __modes,
     cookie_io_functions_t __io_funcs) ;




extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) ;





extern void setbuf (FILE *restrict __stream, char *restrict __buf) ;



extern int setvbuf (FILE *restrict __stream, char *restrict __buf,
      int __modes, size_t __n) ;




extern void setbuffer (FILE *restrict __stream, char *restrict __buf,
         size_t __size) ;


extern void setlinebuf (FILE *__stream) ;







extern int fprintf (FILE *restrict __stream,
      const char *restrict __format, ...);




extern int printf (const char *restrict __format, ...);

extern int sprintf (char *restrict __s,
      const char *restrict __format, ...) ;





extern int vfprintf (FILE *restrict __s, const char *restrict __format,
       __gnuc_va_list __arg);




extern int vprintf (const char *restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *restrict __s, const char *restrict __format,
       __gnuc_va_list __arg) ;



extern int snprintf (char *restrict __s, size_t __maxlen,
       const char *restrict __format, ...)
     ;

extern int vsnprintf (char *restrict __s, size_t __maxlen,
        const char *restrict __format, __gnuc_va_list __arg)
     ;





extern int vasprintf (char **restrict __ptr, const char *restrict __f,
        __gnuc_va_list __arg)
     ;
extern int __asprintf (char **restrict __ptr,
         const char *restrict __fmt, ...)
     ;
extern int asprintf (char **restrict __ptr,
       const char *restrict __fmt, ...)
     ;




extern int vdprintf (int __fd, const char *restrict __fmt,
       __gnuc_va_list __arg)
     ;
extern int dprintf (int __fd, const char *restrict __fmt, ...)
     ;







extern int fscanf (FILE *restrict __stream,
     const char *restrict __format, ...) ;




extern int scanf (const char *restrict __format, ...) ;

extern int sscanf (const char *restrict __s,
     const char *restrict __format, ...) ;
# 434 "/usr/include/stdio.h" 3 4
extern int vfscanf (FILE *restrict __s, const char *restrict __format,
      __gnuc_va_list __arg)
     ;





extern int vscanf (const char *restrict __format, __gnuc_va_list __arg)
     ;


extern int vsscanf (const char *restrict __s,
      const char *restrict __format, __gnuc_va_list __arg)
     ;
# 491 "/usr/include/stdio.h" 3 4
extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);






extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
# 516 "/usr/include/stdio.h" 3 4
extern int fgetc_unlocked (FILE *__stream);
# 527 "/usr/include/stdio.h" 3 4
extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);
# 543 "/usr/include/stdio.h" 3 4
extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);







extern char *fgets (char *restrict __s, int __n, FILE *restrict __stream)
     ;
# 593 "/usr/include/stdio.h" 3 4
extern char *fgets_unlocked (char *restrict __s, int __n,
        FILE *restrict __stream) ;
# 609 "/usr/include/stdio.h" 3 4
extern __ssize_t __getdelim (char **restrict __lineptr,
                             size_t *restrict __n, int __delimiter,
                             FILE *restrict __stream) ;
extern __ssize_t getdelim (char **restrict __lineptr,
                           size_t *restrict __n, int __delimiter,
                           FILE *restrict __stream) ;







extern __ssize_t getline (char **restrict __lineptr,
                          size_t *restrict __n,
                          FILE *restrict __stream) ;







extern int fputs (const char *restrict __s, FILE *restrict __stream);





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *restrict __ptr, size_t __size,
       size_t __n, FILE *restrict __stream) ;




extern size_t fwrite (const void *restrict __ptr, size_t __size,
        size_t __n, FILE *restrict __s);
# 668 "/usr/include/stdio.h" 3 4
extern int fputs_unlocked (const char *restrict __s,
      FILE *restrict __stream);
# 679 "/usr/include/stdio.h" 3 4
extern size_t fread_unlocked (void *restrict __ptr, size_t __size,
         size_t __n, FILE *restrict __stream) ;
extern size_t fwrite_unlocked (const void *restrict __ptr, size_t __size,
          size_t __n, FILE *restrict __stream);







extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) ;




extern void rewind (FILE *__stream);
# 713 "/usr/include/stdio.h" 3 4
extern int fseeko (FILE *__stream, __off_t __off, int __whence);




extern __off_t ftello (FILE *__stream) ;
# 737 "/usr/include/stdio.h" 3 4
extern int fgetpos (FILE *restrict __stream, fpos_t *restrict __pos);




extern int fsetpos (FILE *__stream, const fpos_t *__pos);
# 756 "/usr/include/stdio.h" 3 4
extern int fseeko64 (FILE *__stream, __off64_t __off, int __whence);
extern __off64_t ftello64 (FILE *__stream) ;
extern int fgetpos64 (FILE *restrict __stream, fpos64_t *restrict __pos);
extern int fsetpos64 (FILE *__stream, const fpos64_t *__pos);



extern void clearerr (FILE *__stream) ;

extern int feof (FILE *__stream) ;

extern int ferror (FILE *__stream) ;



extern void clearerr_unlocked (FILE *__stream) ;
extern int feof_unlocked (FILE *__stream) ;
extern int ferror_unlocked (FILE *__stream) ;







extern void perror (const char *__s);





# 1 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h" 1 3 4
# 26 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h" 3 4
extern int sys_nerr;
extern const char *const sys_errlist[];


extern int _sys_nerr;
extern const char *const _sys_errlist[];
# 788 "/usr/include/stdio.h" 2 3 4




extern int fileno (FILE *__stream) ;




extern int fileno_unlocked (FILE *__stream) ;
# 806 "/usr/include/stdio.h" 3 4
extern FILE *popen (const char *__command, const char *__modes) ;





extern int pclose (FILE *__stream);





extern char *ctermid (char *__s) ;





extern char *cuserid (char *__s);




struct obstack;


extern int obstack_printf (struct obstack *restrict __obstack,
      const char *restrict __format, ...)
     ;
extern int obstack_vprintf (struct obstack *restrict __obstack,
       const char *restrict __format,
       __gnuc_va_list __args)
     ;







extern void flockfile (FILE *__stream) ;



extern int ftrylockfile (FILE *__stream) ;


extern void funlockfile (FILE *__stream) ;
# 864 "/usr/include/stdio.h" 3 4
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);
# 879 "/usr/include/stdio.h" 3 4

# 6 "/usr/local/include/neo-c2.h" 2 3
# 1 "/usr/include/stdlib.h" 1 3 4
# 25 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 26 "/usr/include/stdlib.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 1 3 4
# 328 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 3 4
typedef int wchar_t;
# 32 "/usr/include/stdlib.h" 2 3 4







# 1 "/usr/include/x86_64-linux-gnu/bits/waitflags.h" 1 3 4
# 52 "/usr/include/x86_64-linux-gnu/bits/waitflags.h" 3 4
typedef enum
{
  P_ALL,
  P_PID,
  P_PGID
} idtype_t;
# 40 "/usr/include/stdlib.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/waitstatus.h" 1 3 4
# 41 "/usr/include/stdlib.h" 2 3 4
# 55 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/floatn.h" 1 3 4
# 120 "/usr/include/x86_64-linux-gnu/bits/floatn.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/long-double.h" 1 3 4
# 25 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 2 3 4
# 214 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 3 4
typedef float _Float32;
# 251 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 3 4
typedef double _Float64;
# 268 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 3 4
typedef double _Float32x;
# 285 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 3 4
typedef long double _Float64x;
# 121 "/usr/include/x86_64-linux-gnu/bits/floatn.h" 2 3 4
# 56 "/usr/include/stdlib.h" 2 3 4


typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;





 typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;
# 97 "/usr/include/stdlib.h" 3 4
extern size_t __ctype_get_mb_cur_max (void) ;



extern double atof (const char *__nptr)
     ;

extern int atoi (const char *__nptr)
     ;

extern long int atol (const char *__nptr)
     ;



 extern long long int atoll (const char *__nptr)
     ;



extern double strtod (const char *restrict __nptr,
        char **restrict __endptr)
     ;



extern float strtof (const char *restrict __nptr,
       char **restrict __endptr) ;

extern long double strtold (const char *restrict __nptr,
       char **restrict __endptr)
     ;
# 140 "/usr/include/stdlib.h" 3 4
extern _Float32 strtof32 (const char *restrict __nptr,
     char **restrict __endptr)
     ;



extern _Float64 strtof64 (const char *restrict __nptr,
     char **restrict __endptr)
     ;
# 158 "/usr/include/stdlib.h" 3 4
extern _Float32x strtof32x (const char *restrict __nptr,
       char **restrict __endptr)
     ;



extern _Float64x strtof64x (const char *restrict __nptr,
       char **restrict __endptr)
     ;
# 176 "/usr/include/stdlib.h" 3 4
extern long int strtol (const char *restrict __nptr,
   char **restrict __endptr, int __base)
     ;

extern unsigned long int strtoul (const char *restrict __nptr,
      char **restrict __endptr, int __base)
     ;




extern long long int strtoq (const char *restrict __nptr,
        char **restrict __endptr, int __base)
     ;


extern unsigned long long int strtouq (const char *restrict __nptr,
           char **restrict __endptr, int __base)
     ;





extern long long int strtoll (const char *restrict __nptr,
         char **restrict __endptr, int __base)
     ;


extern unsigned long long int strtoull (const char *restrict __nptr,
     char **restrict __endptr, int __base)
     ;




extern int strfromd (char *__dest, size_t __size, const char *__format,
       double __f)
     ;

extern int strfromf (char *__dest, size_t __size, const char *__format,
       float __f)
     ;

extern int strfroml (char *__dest, size_t __size, const char *__format,
       long double __f)
     ;
# 232 "/usr/include/stdlib.h" 3 4
extern int strfromf32 (char *__dest, size_t __size, const char * __format,
         _Float32 __f)
     ;



extern int strfromf64 (char *__dest, size_t __size, const char * __format,
         _Float64 __f)
     ;
# 250 "/usr/include/stdlib.h" 3 4
extern int strfromf32x (char *__dest, size_t __size, const char * __format,
   _Float32x __f)
     ;



extern int strfromf64x (char *__dest, size_t __size, const char * __format,
   _Float64x __f)
     ;
# 272 "/usr/include/stdlib.h" 3 4
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
# 273 "/usr/include/stdlib.h" 2 3 4

extern long int strtol_l (const char *restrict __nptr,
     char **restrict __endptr, int __base,
     locale_t __loc) ;

extern unsigned long int strtoul_l (const char *restrict __nptr,
        char **restrict __endptr,
        int __base, locale_t __loc)
     ;


extern long long int strtoll_l (const char *restrict __nptr,
    char **restrict __endptr, int __base,
    locale_t __loc)
     ;


extern unsigned long long int strtoull_l (const char *restrict __nptr,
       char **restrict __endptr,
       int __base, locale_t __loc)
     ;

extern double strtod_l (const char *restrict __nptr,
   char **restrict __endptr, locale_t __loc)
     ;

extern float strtof_l (const char *restrict __nptr,
         char **restrict __endptr, locale_t __loc)
     ;

extern long double strtold_l (const char *restrict __nptr,
         char **restrict __endptr,
         locale_t __loc)
     ;
# 316 "/usr/include/stdlib.h" 3 4
extern _Float32 strtof32_l (const char *restrict __nptr,
       char **restrict __endptr,
       locale_t __loc)
     ;



extern _Float64 strtof64_l (const char *restrict __nptr,
       char **restrict __endptr,
       locale_t __loc)
     ;
# 337 "/usr/include/stdlib.h" 3 4
extern _Float32x strtof32x_l (const char *restrict __nptr,
         char **restrict __endptr,
         locale_t __loc)
     ;



extern _Float64x strtof64x_l (const char *restrict __nptr,
         char **restrict __endptr,
         locale_t __loc)
     ;
# 385 "/usr/include/stdlib.h" 3 4
extern char *l64a (long int __n) ;


extern long int a64l (const char *__s)
     ;




# 1 "/usr/include/x86_64-linux-gnu/sys/types.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4






typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;


typedef __loff_t loff_t;




typedef __ino_t ino_t;






typedef __ino64_t ino64_t;




typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;
# 97 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
typedef __pid_t pid_t;





typedef __id_t id_t;
# 114 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;




# 1 "/usr/include/x86_64-linux-gnu/bits/types/clock_t.h" 1 3 4






typedef __clock_t clock_t;
# 127 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4

# 1 "/usr/include/x86_64-linux-gnu/bits/types/clockid_t.h" 1 3 4






typedef __clockid_t clockid_t;
# 129 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/time_t.h" 1 3 4






typedef __time_t time_t;
# 130 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/timer_t.h" 1 3 4






typedef __timer_t timer_t;
# 131 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4



typedef __useconds_t useconds_t;



typedef __suseconds_t suseconds_t;





# 1 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 1 3 4
# 145 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;




# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h" 3 4
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 156 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4




typedef unsigned char u_int8_t;
typedef unsigned short int u_int16_t;
typedef unsigned int u_int32_t;

typedef unsigned long int u_int64_t;




typedef int register_t;
# 193 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
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
# 194 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/sys/select.h" 1 3 4
# 30 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/select.h" 1 3 4
# 22 "/usr/include/x86_64-linux-gnu/bits/select.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 23 "/usr/include/x86_64-linux-gnu/bits/select.h" 2 3 4
# 31 "/usr/include/x86_64-linux-gnu/sys/select.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/types/sigset_t.h" 1 3 4



# 1 "/usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h" 1 3 4




typedef struct
{
  unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
} __sigset_t;
# 5 "/usr/include/x86_64-linux-gnu/bits/types/sigset_t.h" 2 3 4


typedef __sigset_t sigset_t;
# 34 "/usr/include/x86_64-linux-gnu/sys/select.h" 2 3 4



# 1 "/usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h" 1 3 4







struct timeval
{
  __time_t tv_sec;
  __suseconds_t tv_usec;
};
# 38 "/usr/include/x86_64-linux-gnu/sys/select.h" 2 3 4

# 1 "/usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h" 1 3 4
# 9 "/usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h" 3 4
struct timespec
{
  __time_t tv_sec;
  __syscall_slong_t tv_nsec;
};
# 40 "/usr/include/x86_64-linux-gnu/sys/select.h" 2 3 4
# 49 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
typedef long int __fd_mask;
# 59 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
typedef struct
  {



    __fd_mask fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];





  } fd_set;






typedef __fd_mask fd_mask;
# 91 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4

# 101 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
extern int select (int __nfds, fd_set *restrict __readfds,
     fd_set *restrict __writefds,
     fd_set *restrict __exceptfds,
     struct timeval *restrict __timeout);
# 113 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4
extern int pselect (int __nfds, fd_set *restrict __readfds,
      fd_set *restrict __writefds,
      fd_set *restrict __exceptfds,
      const struct timespec *restrict __timeout,
      const __sigset_t *restrict __sigmask);
# 126 "/usr/include/x86_64-linux-gnu/sys/select.h" 3 4

# 197 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4





typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 236 "/usr/include/x86_64-linux-gnu/sys/types.h" 3 4
typedef __blkcnt64_t blkcnt64_t;
typedef __fsblkcnt64_t fsblkcnt64_t;
typedef __fsfilcnt64_t fsfilcnt64_t;





# 1 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 1 3 4
# 23 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/thread-shared-types.h" 1 3 4
# 77 "/usr/include/x86_64-linux-gnu/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h" 1 3 4
# 21 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 22 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h" 2 3 4
# 65 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h" 3 4
struct __pthread_rwlock_arch_t
{
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad3;
  unsigned int __pad4;

  int __cur_writer;
  int __shared;
  signed char __rwelision;




  unsigned char __pad1[7];


  unsigned long int __pad2;


  unsigned int __flags;
# 99 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h" 3 4
};
# 78 "/usr/include/x86_64-linux-gnu/bits/thread-shared-types.h" 2 3 4




typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
# 118 "/usr/include/x86_64-linux-gnu/bits/thread-shared-types.h" 3 4
struct __pthread_mutex_s
{
  int __lock ;
  unsigned int __count;
  int __owner;

  unsigned int __nusers;
# 148 "/usr/include/x86_64-linux-gnu/bits/thread-shared-types.h" 3 4
  int __kind;
 




  short __spins; short __elision;
  __pthread_list_t __list;
# 165 "/usr/include/x86_64-linux-gnu/bits/thread-shared-types.h" 3 4
 
};




struct __pthread_cond_s
{
  union
  {
    unsigned long long int __wseq;
    struct
    {
      unsigned int __low;
      unsigned int __high;
    } __wseq32;
  };
  union
  {
    unsigned long long int __g1_start;
    struct
    {
      unsigned int __low;
      unsigned int __high;
    } __g1_start32;
  };
  unsigned int __g_refs[2] ;
  unsigned int __g_size[2];
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
};
# 24 "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h" 2 3 4



typedef unsigned long int pthread_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;


union pthread_attr_t
{
  char __size[56];
  long int __align;
};

typedef union pthread_attr_t pthread_attr_t;




typedef union
{
  struct __pthread_mutex_s __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;


typedef union
{
  struct __pthread_cond_s __data;
  char __size[48];
  long long int __align;
} pthread_cond_t;





typedef union
{
  struct __pthread_rwlock_arch_t __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 245 "/usr/include/x86_64-linux-gnu/sys/types.h" 2 3 4



# 395 "/usr/include/stdlib.h" 2 3 4






extern long int random (void) ;


extern void srandom (unsigned int __seed) ;





extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) ;



extern char *setstate (char *__statebuf) ;







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *restrict __buf,
       int32_t *restrict __result) ;

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     ;

extern int initstate_r (unsigned int __seed, char *restrict __statebuf,
   size_t __statelen,
   struct random_data *restrict __buf)
     ;

extern int setstate_r (char *restrict __statebuf,
         struct random_data *restrict __buf)
     ;





extern int rand (void) ;

extern void srand (unsigned int __seed) ;



extern int rand_r (unsigned int *__seed) ;







extern double drand48 (void) ;
extern double erand48 (unsigned short int __xsubi[3]) ;


extern long int lrand48 (void) ;
extern long int nrand48 (unsigned short int __xsubi[3])
     ;


extern long int mrand48 (void) ;
extern long int jrand48 (unsigned short int __xsubi[3])
     ;


extern void srand48 (long int __seedval) ;
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     ;
extern void lcong48 (unsigned short int __param[7]) ;





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    unsigned long long int __a;

  };


extern int drand48_r (struct drand48_data *restrict __buffer,
        double *restrict __result) ;
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *restrict __buffer,
        double *restrict __result) ;


extern int lrand48_r (struct drand48_data *restrict __buffer,
        long int *restrict __result)
     ;
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *restrict __buffer,
        long int *restrict __result)
     ;


extern int mrand48_r (struct drand48_data *restrict __buffer,
        long int *restrict __result)
     ;
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *restrict __buffer,
        long int *restrict __result)
     ;


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     ;

extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) ;

extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     ;




extern void *malloc (size_t __size) ;

extern void *calloc (size_t __nmemb, size_t __size)
     ;






extern void *realloc (void *__ptr, size_t __size)
     ;







extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     ;



extern void free (void *__ptr) ;


# 1 "/usr/include/alloca.h" 1 3 4
# 24 "/usr/include/alloca.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 1 3 4
# 25 "/usr/include/alloca.h" 2 3 4







extern void *alloca (size_t __size) ;






# 567 "/usr/include/stdlib.h" 2 3 4





extern void *valloc (size_t __size) ;




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     ;




extern void *aligned_alloc (size_t __alignment, size_t __size)
     ;



extern void abort (void) ;



extern int atexit (void (*__func) (void)) ;







extern int at_quick_exit (void (*__func) (void)) ;






extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     ;





extern void exit (int __status) ;





extern void quick_exit (int __status) ;





extern void _Exit (int __status) ;




extern char *getenv (const char *__name) ;




extern char *secure_getenv (const char *__name)
     ;






extern int putenv (char *__string) ;





extern int setenv (const char *__name, const char *__value, int __replace)
     ;


extern int unsetenv (const char *__name) ;






extern int clearenv (void) ;
# 672 "/usr/include/stdlib.h" 3 4
extern char *mktemp (char *__template) ;
# 685 "/usr/include/stdlib.h" 3 4
extern int mkstemp (char *__template) ;
# 695 "/usr/include/stdlib.h" 3 4
extern int mkstemp64 (char *__template) ;
# 707 "/usr/include/stdlib.h" 3 4
extern int mkstemps (char *__template, int __suffixlen) ;
# 717 "/usr/include/stdlib.h" 3 4
extern int mkstemps64 (char *__template, int __suffixlen)
     ;
# 728 "/usr/include/stdlib.h" 3 4
extern char *mkdtemp (char *__template) ;
# 739 "/usr/include/stdlib.h" 3 4
extern int mkostemp (char *__template, int __flags) ;
# 749 "/usr/include/stdlib.h" 3 4
extern int mkostemp64 (char *__template, int __flags) ;
# 759 "/usr/include/stdlib.h" 3 4
extern int mkostemps (char *__template, int __suffixlen, int __flags)
     ;
# 771 "/usr/include/stdlib.h" 3 4
extern int mkostemps64 (char *__template, int __suffixlen, int __flags)
     ;
# 781 "/usr/include/stdlib.h" 3 4
extern int system (const char *__command) ;





extern char *canonicalize_file_name (const char *__name)
     ;
# 797 "/usr/include/stdlib.h" 3 4
extern char *realpath (const char *restrict __name,
         char *restrict __resolved) ;






typedef int (*__compar_fn_t) (const void *, const void *);


typedef __compar_fn_t comparison_fn_t;



typedef int (*__compar_d_fn_t) (const void *, const void *, void *);




extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     ;







extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) ;

extern void qsort_r (void *__base, size_t __nmemb, size_t __size,
       __compar_d_fn_t __compar, void *__arg)
  ;




extern int abs (int __x) ;
extern long int labs (long int __x) ;


 extern long long int llabs (long long int __x)
     ;






extern div_t div (int __numer, int __denom)
     ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     ;


 extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     ;
# 869 "/usr/include/stdlib.h" 3 4
extern char *ecvt (double __value, int __ndigit, int *restrict __decpt,
     int *restrict __sign) ;




extern char *fcvt (double __value, int __ndigit, int *restrict __decpt,
     int *restrict __sign) ;




extern char *gcvt (double __value, int __ndigit, char *__buf)
     ;




extern char *qecvt (long double __value, int __ndigit,
      int *restrict __decpt, int *restrict __sign)
     ;
extern char *qfcvt (long double __value, int __ndigit,
      int *restrict __decpt, int *restrict __sign)
     ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     ;




extern int ecvt_r (double __value, int __ndigit, int *restrict __decpt,
     int *restrict __sign, char *restrict __buf,
     size_t __len) ;
extern int fcvt_r (double __value, int __ndigit, int *restrict __decpt,
     int *restrict __sign, char *restrict __buf,
     size_t __len) ;

extern int qecvt_r (long double __value, int __ndigit,
      int *restrict __decpt, int *restrict __sign,
      char *restrict __buf, size_t __len)
     ;
extern int qfcvt_r (long double __value, int __ndigit,
      int *restrict __decpt, int *restrict __sign,
      char *restrict __buf, size_t __len)
     ;





extern int mblen (const char *__s, size_t __n) ;


extern int mbtowc (wchar_t *restrict __pwc,
     const char *restrict __s, size_t __n) ;


extern int wctomb (char *__s, wchar_t __wchar) ;



extern size_t mbstowcs (wchar_t *restrict __pwcs,
   const char *restrict __s, size_t __n) ;

extern size_t wcstombs (char *restrict __s,
   const wchar_t *restrict __pwcs, size_t __n)
     ;







extern int rpmatch (const char *__response) ;
# 954 "/usr/include/stdlib.h" 3 4
extern int getsubopt (char **restrict __optionp,
        char *const *restrict __tokens,
        char **restrict __valuep)
     ;







extern int posix_openpt (int __oflag) ;







extern int grantpt (int __fd) ;



extern int unlockpt (int __fd) ;




extern char *ptsname (int __fd) ;






extern int ptsname_r (int __fd, char *__buf, size_t __buflen)
     ;


extern int getpt (void);






extern int getloadavg (double __loadavg[], int __nelem)
     ;
# 1010 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/stdlib-float.h" 1 3 4
# 1011 "/usr/include/stdlib.h" 2 3 4
# 1020 "/usr/include/stdlib.h" 3 4

# 7 "/usr/local/include/neo-c2.h" 2 3
# 1 "/usr/include/string.h" 1 3 4
# 26 "/usr/include/string.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/string.h" 2 3 4






# 1 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 1 3 4
# 34 "/usr/include/string.h" 2 3 4
# 42 "/usr/include/string.h" 3 4
extern void *memcpy (void *restrict __dest, const void *restrict __src,
       size_t __n) ;


extern void *memmove (void *__dest, const void *__src, size_t __n)
     ;





extern void *memccpy (void *restrict __dest, const void *restrict __src,
        int __c, size_t __n)
     ;




extern void *memset (void *__s, int __c, size_t __n) ;


extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     ;
# 90 "/usr/include/string.h" 3 4
extern void *memchr (const void *__s, int __c, size_t __n)
      ;
# 103 "/usr/include/string.h" 3 4
extern void *rawmemchr (const void *__s, int __c)
     ;
# 114 "/usr/include/string.h" 3 4
extern void *memrchr (const void *__s, int __c, size_t __n)
      ;





extern char *strcpy (char *restrict __dest, const char *restrict __src)
     ;

extern char *strncpy (char *restrict __dest,
        const char *restrict __src, size_t __n)
     ;


extern char *strcat (char *restrict __dest, const char *restrict __src)
     ;

extern char *strncat (char *restrict __dest, const char *restrict __src,
        size_t __n) ;


extern int strcmp (const char *__s1, const char *__s2)
     ;

extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     ;


extern int strcoll (const char *__s1, const char *__s2)
     ;

extern size_t strxfrm (char *restrict __dest,
         const char *restrict __src, size_t __n)
     ;






extern int strcoll_l (const char *__s1, const char *__s2, locale_t __l)
     ;


extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    locale_t __l) ;





extern char *strdup (const char *__s)
     ;






extern char *strndup (const char *__string, size_t __n)
     ;
# 225 "/usr/include/string.h" 3 4
extern char *strchr (const char *__s, int __c)
     ;
# 252 "/usr/include/string.h" 3 4
extern char *strrchr (const char *__s, int __c)
     ;
# 265 "/usr/include/string.h" 3 4
extern char *strchrnul (const char *__s, int __c)
     ;





extern size_t strcspn (const char *__s, const char *__reject)
     ;


extern size_t strspn (const char *__s, const char *__accept)
     ;
# 302 "/usr/include/string.h" 3 4
extern char *strpbrk (const char *__s, const char *__accept)
     ;
# 329 "/usr/include/string.h" 3 4
extern char *strstr (const char *__haystack, const char *__needle)
     ;




extern char *strtok (char *restrict __s, const char *restrict __delim)
     ;



extern char *__strtok_r (char *restrict __s,
    const char *restrict __delim,
    char **restrict __save_ptr)
     ;

extern char *strtok_r (char *restrict __s, const char *restrict __delim,
         char **restrict __save_ptr)
     ;
# 359 "/usr/include/string.h" 3 4
extern char *strcasestr (const char *__haystack, const char *__needle)
     ;







extern void *memmem (const void *__haystack, size_t __haystacklen,
       const void *__needle, size_t __needlelen)
     ;



extern void *__mempcpy (void *restrict __dest,
   const void *restrict __src, size_t __n)
     ;
extern void *mempcpy (void *restrict __dest,
        const void *restrict __src, size_t __n)
     ;




extern size_t strlen (const char *__s)
     ;




extern size_t strnlen (const char *__string, size_t __maxlen)
     ;




extern char *strerror (int __errnum) ;
# 420 "/usr/include/string.h" 3 4
extern char *strerror_r (int __errnum, char *__buf, size_t __buflen)
     ;





extern char *strerror_l (int __errnum, locale_t __l) ;



# 1 "/usr/include/strings.h" 1 3 4
# 23 "/usr/include/strings.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 1 3 4
# 24 "/usr/include/strings.h" 2 3 4










extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     ;


extern void bcopy (const void *__src, void *__dest, size_t __n)
  ;


extern void bzero (void *__s, size_t __n) ;
# 68 "/usr/include/strings.h" 3 4
extern char *index (const char *__s, int __c)
     ;
# 96 "/usr/include/strings.h" 3 4
extern char *rindex (const char *__s, int __c)
     ;






extern int ffs (int __i) ;





extern int ffsl (long int __l) ;
 extern int ffsll (long long int __ll)
     ;



extern int strcasecmp (const char *__s1, const char *__s2)
     ;


extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     ;






extern int strcasecmp_l (const char *__s1, const char *__s2, locale_t __loc)
     ;



extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, locale_t __loc)
     ;



# 432 "/usr/include/string.h" 2 3 4



extern void explicit_bzero (void *__s, size_t __n) ;



extern char *strsep (char **restrict __stringp,
       const char *restrict __delim)
     ;




extern char *strsignal (int __sig) ;


extern char *__stpcpy (char *restrict __dest, const char *restrict __src)
     ;
extern char *stpcpy (char *restrict __dest, const char *restrict __src)
     ;



extern char *__stpncpy (char *restrict __dest,
   const char *restrict __src, size_t __n)
     ;
extern char *stpncpy (char *restrict __dest,
        const char *restrict __src, size_t __n)
     ;




extern int strverscmp (const char *__s1, const char *__s2)
     ;


extern char *strfry (char *__string) ;


extern void *memfrob (void *__s, size_t __n) ;
# 486 "/usr/include/string.h" 3 4
extern char *basename (const char *__filename) ;
# 498 "/usr/include/string.h" 3 4

# 8 "/usr/local/include/neo-c2.h" 2 3



# 1 "/usr/include/malloc.h" 1 3 4
# 23 "/usr/include/malloc.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 1 3 4
# 149 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 3 4
typedef long int ptrdiff_t;
# 426 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll ;
  long double __max_align_ld ;
# 437 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 3 4
} max_align_t;
# 24 "/usr/include/malloc.h" 2 3 4
# 35 "/usr/include/malloc.h" 3 4



extern void *malloc (size_t __size) ;


extern void *calloc (size_t __nmemb, size_t __size)
 ;






extern void *realloc (void *__ptr, size_t __size)
 ;






extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
 ;


extern void free (void *__ptr) ;


extern void *memalign (size_t __alignment, size_t __size)
 ;


extern void *valloc (size_t __size) ;



extern void *pvalloc (size_t __size) ;



extern void *(*__morecore) (ptrdiff_t __size);


extern void *__default_morecore (ptrdiff_t __size)
 ;



struct mallinfo
{
  int arena;
  int ordblks;
  int smblks;
  int hblks;
  int hblkhd;
  int usmblks;
  int fsmblks;
  int uordblks;
  int fordblks;
  int keepcost;
};


extern struct mallinfo mallinfo (void) ;
# 126 "/usr/include/malloc.h" 3 4
extern int mallopt (int __param, int __val) ;



extern int malloc_trim (size_t __pad) ;



extern size_t malloc_usable_size (void *__ptr) ;


extern void malloc_stats (void) ;


extern int malloc_info (int __options, FILE *__fp) ;


extern void (*volatile __free_hook) (void *__ptr,
                                                   const void *)
;
extern void *(*volatile __malloc_hook)(size_t __size,
                                                     const void *)
;
extern void *(*volatile __realloc_hook)(void *__ptr,
                                                      size_t __size,
                                                      const void *)
;
extern void *(*volatile __memalign_hook)(size_t __alignment,
                                                       size_t __size,
                                                       const void *)
;
extern void (*volatile __after_morecore_hook) (void);


extern void __malloc_check_init (void) ;



# 12 "/usr/local/include/neo-c2.h" 2 3


# 1 "/usr/include/gc.h" 1 3 4

# 1 "/usr/include/gc/gc.h" 1 3 4
# 39 "/usr/include/gc/gc.h" 3 4
# 1 "/usr/include/gc/gc_version.h" 1 3 4
# 40 "/usr/include/gc/gc.h" 2 3 4






# 1 "/usr/include/gc/gc_config_macros.h" 1 3 4
# 154 "/usr/include/gc/gc_config_macros.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 1 3 4
# 155 "/usr/include/gc/gc_config_macros.h" 2 3 4
# 47 "/usr/include/gc/gc.h" 2 3 4





typedef void * GC_PTR;
# 70 "/usr/include/gc/gc.h" 3 4
  typedef unsigned long GC_word;
  typedef long GC_signed_word;




extern unsigned GC_get_version(void);




extern GC_word GC_gc_no;


extern GC_word GC_get_gc_no(void);
# 113 "/usr/include/gc/gc.h" 3 4
typedef void * ( * GC_oom_func)(size_t );
extern GC_oom_func GC_oom_fn;
# 124 "/usr/include/gc/gc.h" 3 4
extern void GC_set_oom_fn(GC_oom_func) ;
extern GC_oom_func GC_get_oom_fn(void);

typedef void ( * GC_on_heap_resize_proc)(GC_word );
extern GC_on_heap_resize_proc GC_on_heap_resize;



extern void GC_set_on_heap_resize(GC_on_heap_resize_proc);
extern GC_on_heap_resize_proc GC_get_on_heap_resize(void);



typedef enum {
    GC_EVENT_START ,
    GC_EVENT_MARK_START,
    GC_EVENT_MARK_END,
    GC_EVENT_RECLAIM_START,
    GC_EVENT_RECLAIM_END,
    GC_EVENT_END ,
    GC_EVENT_PRE_STOP_WORLD ,
    GC_EVENT_POST_STOP_WORLD ,
    GC_EVENT_PRE_START_WORLD ,
    GC_EVENT_POST_START_WORLD ,
    GC_EVENT_THREAD_SUSPENDED,
    GC_EVENT_THREAD_UNSUSPENDED
} GC_EventType;

typedef void ( * GC_on_collection_event_proc)(GC_EventType);





extern void GC_set_on_collection_event(GC_on_collection_event_proc);
extern GC_on_collection_event_proc GC_get_on_collection_event(void);
# 176 "/usr/include/gc/gc.h" 3 4
extern int GC_find_leak;
# 185 "/usr/include/gc/gc.h" 3 4
extern void GC_set_find_leak(int);
extern int GC_get_find_leak(void);

extern int GC_all_interior_pointers;
# 201 "/usr/include/gc/gc.h" 3 4
extern void GC_set_all_interior_pointers(int);
extern int GC_get_all_interior_pointers(void);

extern int GC_finalize_on_demand;






extern void GC_set_finalize_on_demand(int);
extern int GC_get_finalize_on_demand(void);

extern int GC_java_finalization;
# 223 "/usr/include/gc/gc.h" 3 4
extern void GC_set_java_finalization(int);
extern int GC_get_java_finalization(void);

typedef void ( * GC_finalizer_notifier_proc)(void);
extern GC_finalizer_notifier_proc GC_finalizer_notifier;
# 237 "/usr/include/gc/gc.h" 3 4
extern void GC_set_finalizer_notifier(GC_finalizer_notifier_proc);
extern GC_finalizer_notifier_proc GC_get_finalizer_notifier(void);

extern

   

  int GC_dont_gc;
# 254 "/usr/include/gc/gc.h" 3 4
extern int GC_dont_expand;



extern void GC_set_dont_expand(int);
extern int GC_get_dont_expand(void);

extern int GC_use_entire_heap;
# 272 "/usr/include/gc/gc.h" 3 4
extern int GC_full_freq;
# 286 "/usr/include/gc/gc.h" 3 4
extern void GC_set_full_freq(int);
extern int GC_get_full_freq(void);

extern GC_word GC_non_gc_bytes;
# 299 "/usr/include/gc/gc.h" 3 4
extern void GC_set_non_gc_bytes(GC_word);
extern GC_word GC_get_non_gc_bytes(void);

extern int GC_no_dls;
# 311 "/usr/include/gc/gc.h" 3 4
extern void GC_set_no_dls(int);
extern int GC_get_no_dls(void);

extern GC_word GC_free_space_divisor;
# 333 "/usr/include/gc/gc.h" 3 4
extern void GC_set_free_space_divisor(GC_word);
extern GC_word GC_get_free_space_divisor(void);

extern GC_word GC_max_retries;







extern void GC_set_max_retries(GC_word);
extern GC_word GC_get_max_retries(void);


extern char *GC_stackbottom;
# 364 "/usr/include/gc/gc.h" 3 4
extern int GC_dont_precollect;
# 375 "/usr/include/gc/gc.h" 3 4
extern void GC_set_dont_precollect(int);
extern int GC_get_dont_precollect(void);

extern unsigned long GC_time_limit;
# 395 "/usr/include/gc/gc.h" 3 4
extern void GC_set_time_limit(unsigned long);
extern unsigned long GC_get_time_limit(void);
# 408 "/usr/include/gc/gc.h" 3 4
extern void GC_set_pages_executable(int);





extern int GC_get_pages_executable(void);
# 428 "/usr/include/gc/gc.h" 3 4
extern void GC_set_handle_fork(int);
# 437 "/usr/include/gc/gc.h" 3 4
extern void GC_atfork_prepare(void);
extern void GC_atfork_parent(void);
extern void GC_atfork_child(void);



extern void GC_init(void);



extern int GC_is_init_called(void);
# 462 "/usr/include/gc/gc.h" 3 4
extern void *
        GC_malloc(size_t );
extern void *
        GC_malloc_atomic(size_t );
extern char * GC_strdup(const char *);
extern char *
        GC_strndup(const char *, size_t) ;
extern void *
        GC_malloc_uncollectable(size_t );
extern void *
        GC_malloc_stubborn(size_t );


extern void *
        GC_memalign(size_t , size_t );
extern int GC_posix_memalign(void ** , size_t ,
                        size_t ) ;
# 487 "/usr/include/gc/gc.h" 3 4
extern void GC_free(void *);
# 502 "/usr/include/gc/gc.h" 3 4
extern void GC_change_stubborn(const void *) ;
extern void GC_end_stubborn_change(const void *) ;
# 516 "/usr/include/gc/gc.h" 3 4
extern void * GC_base(void * );





extern int GC_is_heap_ptr(const void *);




extern size_t GC_size(const void * ) ;
# 550 "/usr/include/gc/gc.h" 3 4
extern void * GC_realloc(void * ,
                                 size_t )
                                             ;



extern int GC_expand_hp(size_t );






extern void GC_set_max_heap_size(GC_word );







extern void GC_exclude_static_roots(void * ,
                                            void * );


extern void GC_clear_roots(void);




extern void GC_add_roots(void * ,
                                 void * );



extern void GC_remove_roots(void * ,
                                    void * );
# 600 "/usr/include/gc/gc.h" 3 4
extern void GC_register_displacement(size_t );



extern void GC_debug_register_displacement(size_t );


extern void GC_gcollect(void);






extern void GC_gcollect_and_unmap(void);
# 629 "/usr/include/gc/gc.h" 3 4
typedef int ( * GC_stop_func)(void);
extern int GC_try_to_collect(GC_stop_func )
                                                        ;





extern void GC_set_stop_func(GC_stop_func )
                                                        ;
extern GC_stop_func GC_get_stop_func(void);
# 654 "/usr/include/gc/gc.h" 3 4
extern size_t GC_get_heap_size(void);




extern size_t GC_get_free_bytes(void);





extern size_t GC_get_unmapped_bytes(void);




extern size_t GC_get_bytes_since_gc(void);




extern size_t GC_get_total_bytes(void);
# 684 "/usr/include/gc/gc.h" 3 4
extern void GC_get_heap_usage_safe(GC_word * ,
                                           GC_word * ,
                                           GC_word * ,
                                           GC_word * ,
                                           GC_word * );





struct GC_prof_stats_s {
  GC_word heapsize_full;


  GC_word free_bytes_full;


  GC_word unmapped_bytes;


  GC_word bytes_allocd_since_gc;


  GC_word allocd_bytes_before_gc;



  GC_word non_gc_bytes;


  GC_word gc_no;


  GC_word markers_m1;



  GC_word bytes_reclaimed_since_gc;

  GC_word reclaimed_bytes_before_gc;


};
# 737 "/usr/include/gc/gc.h" 3 4
extern size_t GC_get_prof_stats(struct GC_prof_stats_s *,
                                        size_t );
# 749 "/usr/include/gc/gc.h" 3 4
extern size_t GC_get_memory_use(void);



extern void GC_disable(void);



extern int GC_is_disabled(void);




extern void GC_enable(void);
# 775 "/usr/include/gc/gc.h" 3 4
extern void GC_enable_incremental(void);
# 786 "/usr/include/gc/gc.h" 3 4
extern int GC_incremental_protection_needs(void);
# 796 "/usr/include/gc/gc.h" 3 4
extern int GC_collect_a_little(void);
# 812 "/usr/include/gc/gc.h" 3 4
extern void *
        GC_malloc_ignore_off_page(size_t );
extern void *
        GC_malloc_atomic_ignore_off_page(size_t );
# 827 "/usr/include/gc/gc.h" 3 4
extern void *
        GC_malloc_atomic_uncollectable(size_t );
extern void *
        GC_debug_malloc_atomic_uncollectable(size_t, const char * s, int i);



extern void *
        GC_debug_malloc(size_t , const char * s, int i);
extern void *
        GC_debug_malloc_atomic(size_t , const char * s, int i);
extern char *
        GC_debug_strdup(const char *, const char * s, int i);
extern char *
        GC_debug_strndup(const char *, size_t, const char * s, int i)
                                                        ;
extern void *
        GC_debug_malloc_uncollectable(size_t ,
                                      const char * s, int i);
extern void *
        GC_debug_malloc_stubborn(size_t , const char * s, int i);
extern void *
        GC_debug_malloc_ignore_off_page(size_t ,
                                        const char * s, int i);
extern void *
        GC_debug_malloc_atomic_ignore_off_page(size_t ,
                                        const char * s, int i);
extern void GC_debug_free(void *);
extern void * GC_debug_realloc(void * ,
                        size_t , const char * s, int i)
                                             ;
extern void GC_debug_change_stubborn(const void *) ;
extern void GC_debug_end_stubborn_change(const void *)
                                                        ;
# 874 "/usr/include/gc/gc.h" 3 4
extern void *
        GC_debug_malloc_replacement(size_t );
extern void *
        GC_debug_realloc_replacement(void * ,
                                     size_t );
# 981 "/usr/include/gc/gc.h" 3 4
typedef void ( * GC_finalization_proc)(void * ,
                                                  void * );

extern void GC_register_finalizer(void * ,
                        GC_finalization_proc , void * ,
                        GC_finalization_proc * , void ** )
                                                ;
extern void GC_debug_register_finalizer(void * ,
                        GC_finalization_proc , void * ,
                        GC_finalization_proc * , void ** )
                                                ;
# 1041 "/usr/include/gc/gc.h" 3 4
extern void GC_register_finalizer_ignore_self(void * ,
                        GC_finalization_proc , void * ,
                        GC_finalization_proc * , void ** )
                                                ;
extern void GC_debug_register_finalizer_ignore_self(void * ,
                        GC_finalization_proc , void * ,
                        GC_finalization_proc * , void ** )
                                                ;





extern void GC_register_finalizer_no_order(void * ,
                        GC_finalization_proc , void * ,
                        GC_finalization_proc * , void ** )
                                                ;
extern void GC_debug_register_finalizer_no_order(void * ,
                        GC_finalization_proc , void * ,
                        GC_finalization_proc * , void ** )
                                                ;
# 1079 "/usr/include/gc/gc.h" 3 4
extern void GC_register_finalizer_unreachable(void * ,
                        GC_finalization_proc , void * ,
                        GC_finalization_proc * , void ** )
                                                ;
extern void GC_debug_register_finalizer_unreachable(void * ,
                        GC_finalization_proc , void * ,
                        GC_finalization_proc * , void ** )
                                                ;
# 1097 "/usr/include/gc/gc.h" 3 4
extern int GC_register_disappearing_link(void ** )
                                                ;
# 1119 "/usr/include/gc/gc.h" 3 4
extern int GC_general_register_disappearing_link(void ** ,
                                                    const void * )
                        ;
# 1158 "/usr/include/gc/gc.h" 3 4
extern int GC_move_disappearing_link(void ** ,
                                             void ** )
                        ;
# 1173 "/usr/include/gc/gc.h" 3 4
extern int GC_unregister_disappearing_link(void ** );




extern int GC_register_long_link(void ** ,
                                    const void * )
                        ;
# 1189 "/usr/include/gc/gc.h" 3 4
extern int GC_move_long_link(void ** ,
                                     void ** )
                        ;



extern int GC_unregister_long_link(void ** );
# 1205 "/usr/include/gc/gc.h" 3 4
typedef enum {
   GC_TOGGLE_REF_DROP,
   GC_TOGGLE_REF_STRONG,
   GC_TOGGLE_REF_WEAK
} GC_ToggleRefStatus;





typedef GC_ToggleRefStatus ( *GC_toggleref_func)(void * );






extern void GC_set_toggleref_func(GC_toggleref_func);
extern GC_toggleref_func GC_get_toggleref_func(void);
# 1233 "/usr/include/gc/gc.h" 3 4
extern int GC_toggleref_add(void * , int )
                                                ;




typedef void ( * GC_await_finalize_proc)(void * );
extern void GC_set_await_finalize_proc(GC_await_finalize_proc);
extern GC_await_finalize_proc GC_get_await_finalize_proc(void);





extern int GC_should_invoke_finalizers(void);

extern int GC_invoke_finalizers(void);
# 1270 "/usr/include/gc/gc.h" 3 4
  extern void GC_noop1(GC_word);
# 1279 "/usr/include/gc/gc.h" 3 4
typedef void ( * GC_warn_proc)(char * ,
                                          GC_word );
extern void GC_set_warn_proc(GC_warn_proc ) ;

extern GC_warn_proc GC_get_warn_proc(void);



extern void GC_ignore_warn_proc(char *, GC_word);


extern void GC_set_log_fd(int);
# 1299 "/usr/include/gc/gc.h" 3 4
typedef void ( * GC_abort_func)(const char * );
extern void GC_set_abort_func(GC_abort_func) ;
extern GC_abort_func GC_get_abort_func(void);
# 1311 "/usr/include/gc/gc.h" 3 4
typedef GC_word GC_hidden_pointer;
# 1325 "/usr/include/gc/gc.h" 3 4
typedef void * ( * GC_fn_type)(void * );
extern void * GC_call_with_alloc_lock(GC_fn_type ,
                                void * ) ;
# 1341 "/usr/include/gc/gc.h" 3 4
struct GC_stack_base {
  void * mem_base;



};

typedef void * ( * GC_stack_base_func)(
                struct GC_stack_base * , void * );





extern void * GC_call_with_stack_base(GC_stack_base_func ,
                                        void * ) ;
# 1466 "/usr/include/gc/gc.h" 3 4
extern void * GC_do_blocking(GC_fn_type ,
                                void * ) ;
# 1478 "/usr/include/gc/gc.h" 3 4
extern void * GC_call_with_gc_active(GC_fn_type ,
                                void * ) ;
# 1488 "/usr/include/gc/gc.h" 3 4
extern int GC_get_stack_base(struct GC_stack_base *)
                                                        ;
# 1500 "/usr/include/gc/gc.h" 3 4
extern void * GC_same_obj(void * , void * );





extern void * GC_pre_incr(void **, ptrdiff_t )
                                                        ;
extern void * GC_post_incr(void **, ptrdiff_t )
                                                        ;
# 1519 "/usr/include/gc/gc.h" 3 4
extern void * GC_is_visible(void * );






extern void * GC_is_valid_displacement(void * );





extern void GC_dump(void);



extern void GC_dump_regions(void);




extern void GC_dump_finalization(void);
# 1581 "/usr/include/gc/gc.h" 3 4
extern void ( * GC_same_obj_print_proc)(void * ,
                                                   void * );
extern void ( * GC_is_valid_displacement_print_proc)(void *);
extern void ( * GC_is_visible_print_proc)(void *);
# 1595 "/usr/include/gc/gc.h" 3 4
extern void * GC_malloc_many(size_t );
# 1607 "/usr/include/gc/gc.h" 3 4
typedef int ( * GC_has_static_roots_func)(
                                        const char * ,
                                        void * ,
                                        size_t );





extern void GC_register_has_static_roots_callback(
                                        GC_has_static_roots_func);
# 1764 "/usr/include/gc/gc.h" 3 4
extern void GC_set_force_unmap_on_gcollect(int);
extern int GC_get_force_unmap_on_gcollect(void);
# 1938 "/usr/include/gc/gc.h" 3 4
extern void GC_win32_free_heap(void);
# 2 "/usr/include/gc.h" 2 3 4
# 15 "/usr/local/include/neo-c2.h" 2 3
# 1 "/usr/include/pthread.h" 1 3 4
# 23 "/usr/include/pthread.h" 3 4
# 1 "/usr/include/sched.h" 1 3 4
# 29 "/usr/include/sched.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 1 3 4
# 30 "/usr/include/sched.h" 2 3 4
# 43 "/usr/include/sched.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/sched.h" 1 3 4
# 74 "/usr/include/x86_64-linux-gnu/bits/sched.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/struct_sched_param.h" 1 3 4
# 23 "/usr/include/x86_64-linux-gnu/bits/types/struct_sched_param.h" 3 4
struct sched_param
{
  int sched_priority;
};
# 75 "/usr/include/x86_64-linux-gnu/bits/sched.h" 2 3 4





extern int clone (int (*__fn) (void *__arg), void *__child_stack,
    int __flags, void *__arg, ...) ;


extern int unshare (int __flags) ;


extern int sched_getcpu (void) ;


extern int setns (int __fd, int __nstype) ;



# 44 "/usr/include/sched.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/cpu-set.h" 1 3 4
# 32 "/usr/include/x86_64-linux-gnu/bits/cpu-set.h" 3 4
typedef unsigned long int __cpu_mask;






typedef struct
{
  __cpu_mask __bits[1024 / (8 * sizeof (__cpu_mask))];
} cpu_set_t;
# 115 "/usr/include/x86_64-linux-gnu/bits/cpu-set.h" 3 4


extern int __sched_cpucount (size_t __setsize, const cpu_set_t *__setp)
     ;
extern cpu_set_t *__sched_cpualloc (size_t __count) ;
extern void __sched_cpufree (cpu_set_t *__set) ;


# 45 "/usr/include/sched.h" 2 3 4









extern int sched_setparam (__pid_t __pid, const struct sched_param *__param)
     ;


extern int sched_getparam (__pid_t __pid, struct sched_param *__param) ;


extern int sched_setscheduler (__pid_t __pid, int __policy,
          const struct sched_param *__param) ;


extern int sched_getscheduler (__pid_t __pid) ;


extern int sched_yield (void) ;


extern int sched_get_priority_max (int __algorithm) ;


extern int sched_get_priority_min (int __algorithm) ;


extern int sched_rr_get_interval (__pid_t __pid, struct timespec *__t) ;
# 121 "/usr/include/sched.h" 3 4
extern int sched_setaffinity (__pid_t __pid, size_t __cpusetsize,
         const cpu_set_t *__cpuset) ;


extern int sched_getaffinity (__pid_t __pid, size_t __cpusetsize,
         cpu_set_t *__cpuset) ;



# 24 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/time.h" 1 3 4
# 29 "/usr/include/time.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 1 3 4
# 30 "/usr/include/time.h" 2 3 4



# 1 "/usr/include/x86_64-linux-gnu/bits/time.h" 1 3 4
# 73 "/usr/include/x86_64-linux-gnu/bits/time.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/timex.h" 1 3 4
# 26 "/usr/include/x86_64-linux-gnu/bits/timex.h" 3 4
struct timex
{
  unsigned int modes;
  __syscall_slong_t offset;
  __syscall_slong_t freq;
  __syscall_slong_t maxerror;
  __syscall_slong_t esterror;
  int status;
  __syscall_slong_t constant;
  __syscall_slong_t precision;
  __syscall_slong_t tolerance;
  struct timeval time;
  __syscall_slong_t tick;
  __syscall_slong_t ppsfreq;
  __syscall_slong_t jitter;
  int shift;
  __syscall_slong_t stabil;
  __syscall_slong_t jitcnt;
  __syscall_slong_t calcnt;
  __syscall_slong_t errcnt;
  __syscall_slong_t stbcnt;

  int tai;


  int :32; int :32; int :32; int :32;
  int :32; int :32; int :32; int :32;
  int :32; int :32; int :32;
};
# 74 "/usr/include/x86_64-linux-gnu/bits/time.h" 2 3 4




extern int clock_adjtime (__clockid_t __clock_id, struct timex *__utx) ;


# 34 "/usr/include/time.h" 2 3 4





# 1 "/usr/include/x86_64-linux-gnu/bits/types/struct_tm.h" 1 3 4






struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;


  long int tm_gmtoff;
  const char *tm_zone;




};
# 40 "/usr/include/time.h" 2 3 4
# 48 "/usr/include/time.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h" 1 3 4







struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };
# 49 "/usr/include/time.h" 2 3 4
struct sigevent;
# 68 "/usr/include/time.h" 3 4




extern clock_t clock (void) ;


extern time_t time (time_t *__timer) ;


extern double difftime (time_t __time1, time_t __time0)
     ;


extern time_t mktime (struct tm *__tp) ;





extern size_t strftime (char *restrict __s, size_t __maxsize,
   const char *restrict __format,
   const struct tm *restrict __tp) ;




extern char *strptime (const char *restrict __s,
         const char *restrict __fmt, struct tm *__tp)
     ;






extern size_t strftime_l (char *restrict __s, size_t __maxsize,
     const char *restrict __format,
     const struct tm *restrict __tp,
     locale_t __loc) ;



extern char *strptime_l (const char *restrict __s,
    const char *restrict __fmt, struct tm *__tp,
    locale_t __loc) ;





extern struct tm *gmtime (const time_t *__timer) ;



extern struct tm *localtime (const time_t *__timer) ;




extern struct tm *gmtime_r (const time_t *restrict __timer,
       struct tm *restrict __tp) ;



extern struct tm *localtime_r (const time_t *restrict __timer,
          struct tm *restrict __tp) ;




extern char *asctime (const struct tm *__tp) ;


extern char *ctime (const time_t *__timer) ;






extern char *asctime_r (const struct tm *restrict __tp,
   char *restrict __buf) ;


extern char *ctime_r (const time_t *restrict __timer,
        char *restrict __buf) ;




extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;




extern char *tzname[2];



extern void tzset (void) ;



extern int daylight;
extern long int timezone;





extern int stime (const time_t *__when) ;
# 196 "/usr/include/time.h" 3 4
extern time_t timegm (struct tm *__tp) ;


extern time_t timelocal (struct tm *__tp) ;


extern int dysize (int __year) ;
# 211 "/usr/include/time.h" 3 4
extern int nanosleep (const struct timespec *__requested_time,
        struct timespec *__remaining);



extern int clock_getres (clockid_t __clock_id, struct timespec *__res) ;


extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) ;


extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     ;






extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       const struct timespec *__req,
       struct timespec *__rem);


extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) ;




extern int timer_create (clockid_t __clock_id,
    struct sigevent *restrict __evp,
    timer_t *restrict __timerid) ;


extern int timer_delete (timer_t __timerid) ;


extern int timer_settime (timer_t __timerid, int __flags,
     const struct itimerspec *restrict __value,
     struct itimerspec *restrict __ovalue) ;


extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     ;


extern int timer_getoverrun (timer_t __timerid) ;





extern int timespec_get (struct timespec *__ts, int __base)
     ;
# 280 "/usr/include/time.h" 3 4
extern int getdate_err;
# 289 "/usr/include/time.h" 3 4
extern struct tm *getdate (const char *__string);
# 303 "/usr/include/time.h" 3 4
extern int getdate_r (const char *restrict __string,
        struct tm *restrict __resbufp);



# 25 "/usr/include/pthread.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/setjmp.h" 1 3 4
# 26 "/usr/include/x86_64-linux-gnu/bits/setjmp.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/setjmp.h" 2 3 4




typedef long int __jmp_buf[8];
# 28 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 29 "/usr/include/pthread.h" 2 3 4




enum
{
  PTHREAD_CREATE_JOINABLE,

  PTHREAD_CREATE_DETACHED

};



enum
{
  PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_ADAPTIVE_NP

  ,
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL



  , PTHREAD_MUTEX_FAST_NP = PTHREAD_MUTEX_TIMED_NP

};




enum
{
  PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_STALLED_NP = PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_ROBUST,
  PTHREAD_MUTEX_ROBUST_NP = PTHREAD_MUTEX_ROBUST
};





enum
{
  PTHREAD_PRIO_NONE,
  PTHREAD_PRIO_INHERIT,
  PTHREAD_PRIO_PROTECT
};
# 115 "/usr/include/pthread.h" 3 4
enum
{
  PTHREAD_RWLOCK_PREFER_READER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP,
  PTHREAD_RWLOCK_DEFAULT_NP = PTHREAD_RWLOCK_PREFER_READER_NP
};
# 156 "/usr/include/pthread.h" 3 4
enum
{
  PTHREAD_INHERIT_SCHED,

  PTHREAD_EXPLICIT_SCHED

};



enum
{
  PTHREAD_SCOPE_SYSTEM,

  PTHREAD_SCOPE_PROCESS

};



enum
{
  PTHREAD_PROCESS_PRIVATE,

  PTHREAD_PROCESS_SHARED

};
# 191 "/usr/include/pthread.h" 3 4
struct _pthread_cleanup_buffer
{
  void (*__routine) (void *);
  void *__arg;
  int __canceltype;
  struct _pthread_cleanup_buffer *__prev;
};


enum
{
  PTHREAD_CANCEL_ENABLE,

  PTHREAD_CANCEL_DISABLE

};
enum
{
  PTHREAD_CANCEL_DEFERRED,

  PTHREAD_CANCEL_ASYNCHRONOUS

};
# 229 "/usr/include/pthread.h" 3 4





extern int pthread_create (pthread_t *restrict __newthread,
      const pthread_attr_t *restrict __attr,
      void *(*__start_routine) (void *),
      void *restrict __arg) ;





extern void pthread_exit (void *__retval) ;







extern int pthread_join (pthread_t __th, void **__thread_return);




extern int pthread_tryjoin_np (pthread_t __th, void **__thread_return) ;







extern int pthread_timedjoin_np (pthread_t __th, void **__thread_return,
     const struct timespec *__abstime);






extern int pthread_detach (pthread_t __th) ;



extern pthread_t pthread_self (void) ;


extern int pthread_equal (pthread_t __thread1, pthread_t __thread2)
  ;







extern int pthread_attr_init (pthread_attr_t *__attr) ;


extern int pthread_attr_destroy (pthread_attr_t *__attr)
     ;


extern int pthread_attr_getdetachstate (const pthread_attr_t *__attr,
     int *__detachstate)
     ;


extern int pthread_attr_setdetachstate (pthread_attr_t *__attr,
     int __detachstate)
     ;



extern int pthread_attr_getguardsize (const pthread_attr_t *__attr,
          size_t *__guardsize)
     ;


extern int pthread_attr_setguardsize (pthread_attr_t *__attr,
          size_t __guardsize)
     ;



extern int pthread_attr_getschedparam (const pthread_attr_t *restrict __attr,
           struct sched_param *restrict __param)
     ;


extern int pthread_attr_setschedparam (pthread_attr_t *restrict __attr,
           const struct sched_param *restrict
           __param) ;


extern int pthread_attr_getschedpolicy (const pthread_attr_t *restrict
     __attr, int *restrict __policy)
     ;


extern int pthread_attr_setschedpolicy (pthread_attr_t *__attr, int __policy)
     ;


extern int pthread_attr_getinheritsched (const pthread_attr_t *restrict
      __attr, int *restrict __inherit)
     ;


extern int pthread_attr_setinheritsched (pthread_attr_t *__attr,
      int __inherit)
     ;



extern int pthread_attr_getscope (const pthread_attr_t *restrict __attr,
      int *restrict __scope)
     ;


extern int pthread_attr_setscope (pthread_attr_t *__attr, int __scope)
     ;


extern int pthread_attr_getstackaddr (const pthread_attr_t *restrict
          __attr, void **restrict __stackaddr)
     ;





extern int pthread_attr_setstackaddr (pthread_attr_t *__attr,
          void *__stackaddr)
     ;


extern int pthread_attr_getstacksize (const pthread_attr_t *restrict
          __attr, size_t *restrict __stacksize)
     ;




extern int pthread_attr_setstacksize (pthread_attr_t *__attr,
          size_t __stacksize)
     ;



extern int pthread_attr_getstack (const pthread_attr_t *restrict __attr,
      void **restrict __stackaddr,
      size_t *restrict __stacksize)
     ;




extern int pthread_attr_setstack (pthread_attr_t *__attr, void *__stackaddr,
      size_t __stacksize) ;





extern int pthread_attr_setaffinity_np (pthread_attr_t *__attr,
     size_t __cpusetsize,
     const cpu_set_t *__cpuset)
     ;



extern int pthread_attr_getaffinity_np (const pthread_attr_t *__attr,
     size_t __cpusetsize,
     cpu_set_t *__cpuset)
     ;


extern int pthread_getattr_default_np (pthread_attr_t *__attr)
     ;



extern int pthread_setattr_default_np (const pthread_attr_t *__attr)
     ;




extern int pthread_getattr_np (pthread_t __th, pthread_attr_t *__attr)
     ;







extern int pthread_setschedparam (pthread_t __target_thread, int __policy,
      const struct sched_param *__param)
     ;


extern int pthread_getschedparam (pthread_t __target_thread,
      int *restrict __policy,
      struct sched_param *restrict __param)
     ;


extern int pthread_setschedprio (pthread_t __target_thread, int __prio)
     ;




extern int pthread_getname_np (pthread_t __target_thread, char *__buf,
          size_t __buflen)
     ;


extern int pthread_setname_np (pthread_t __target_thread, const char *__name)
     ;





extern int pthread_getconcurrency (void) ;


extern int pthread_setconcurrency (int __level) ;







extern int pthread_yield (void) ;




extern int pthread_setaffinity_np (pthread_t __th, size_t __cpusetsize,
       const cpu_set_t *__cpuset)
     ;


extern int pthread_getaffinity_np (pthread_t __th, size_t __cpusetsize,
       cpu_set_t *__cpuset)
     ;
# 495 "/usr/include/pthread.h" 3 4
extern int pthread_once (pthread_once_t *__once_control,
    void (*__init_routine) (void)) ;
# 507 "/usr/include/pthread.h" 3 4
extern int pthread_setcancelstate (int __state, int *__oldstate);



extern int pthread_setcanceltype (int __type, int *__oldtype);


extern int pthread_cancel (pthread_t __th);




extern void pthread_testcancel (void);




typedef struct
{
  struct
  {
    __jmp_buf __cancel_jmp_buf;
    int __mask_was_saved;
  } __cancel_jmp_buf[1];
  void *__pad[4];
} __pthread_unwind_buf_t ;
# 541 "/usr/include/pthread.h" 3 4
struct __pthread_cleanup_frame
{
  void (*__cancel_routine) (void *);
  void *__cancel_arg;
  int __do_it;
  int __cancel_type;
};
# 681 "/usr/include/pthread.h" 3 4
extern void __pthread_register_cancel (__pthread_unwind_buf_t *__buf)
     ;
# 693 "/usr/include/pthread.h" 3 4
extern void __pthread_unregister_cancel (__pthread_unwind_buf_t *__buf)
  ;
# 716 "/usr/include/pthread.h" 3 4
extern void __pthread_register_cancel_defer (__pthread_unwind_buf_t *__buf)
     ;
# 729 "/usr/include/pthread.h" 3 4
extern void __pthread_unregister_cancel_restore (__pthread_unwind_buf_t *__buf)
  ;



extern void __pthread_unwind_next (__pthread_unwind_buf_t *__buf)
    

    

     ;



struct __jmp_buf_tag;
extern int __sigsetjmp (struct __jmp_buf_tag *__env, int __savemask) ;





extern int pthread_mutex_init (pthread_mutex_t *__mutex,
          const pthread_mutexattr_t *__mutexattr)
     ;


extern int pthread_mutex_destroy (pthread_mutex_t *__mutex)
     ;


extern int pthread_mutex_trylock (pthread_mutex_t *__mutex)
     ;


extern int pthread_mutex_lock (pthread_mutex_t *__mutex)
     ;



extern int pthread_mutex_timedlock (pthread_mutex_t *restrict __mutex,
        const struct timespec *restrict
        __abstime) ;



extern int pthread_mutex_unlock (pthread_mutex_t *__mutex)
     ;



extern int pthread_mutex_getprioceiling (const pthread_mutex_t *
      restrict __mutex,
      int *restrict __prioceiling)
     ;



extern int pthread_mutex_setprioceiling (pthread_mutex_t *restrict __mutex,
      int __prioceiling,
      int *restrict __old_ceiling)
     ;




extern int pthread_mutex_consistent (pthread_mutex_t *__mutex)
     ;

extern int pthread_mutex_consistent_np (pthread_mutex_t *__mutex)
     ;
# 807 "/usr/include/pthread.h" 3 4
extern int pthread_mutexattr_init (pthread_mutexattr_t *__attr)
     ;


extern int pthread_mutexattr_destroy (pthread_mutexattr_t *__attr)
     ;


extern int pthread_mutexattr_getpshared (const pthread_mutexattr_t *
      restrict __attr,
      int *restrict __pshared)
     ;


extern int pthread_mutexattr_setpshared (pthread_mutexattr_t *__attr,
      int __pshared)
     ;



extern int pthread_mutexattr_gettype (const pthread_mutexattr_t *restrict
          __attr, int *restrict __kind)
     ;




extern int pthread_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind)
     ;



extern int pthread_mutexattr_getprotocol (const pthread_mutexattr_t *
       restrict __attr,
       int *restrict __protocol)
     ;



extern int pthread_mutexattr_setprotocol (pthread_mutexattr_t *__attr,
       int __protocol)
     ;


extern int pthread_mutexattr_getprioceiling (const pthread_mutexattr_t *
          restrict __attr,
          int *restrict __prioceiling)
     ;


extern int pthread_mutexattr_setprioceiling (pthread_mutexattr_t *__attr,
          int __prioceiling)
     ;



extern int pthread_mutexattr_getrobust (const pthread_mutexattr_t *__attr,
     int *__robustness)
     ;

extern int pthread_mutexattr_getrobust_np (const pthread_mutexattr_t *__attr,
        int *__robustness)
     ;



extern int pthread_mutexattr_setrobust (pthread_mutexattr_t *__attr,
     int __robustness)
     ;

extern int pthread_mutexattr_setrobust_np (pthread_mutexattr_t *__attr,
        int __robustness)
     ;
# 889 "/usr/include/pthread.h" 3 4
extern int pthread_rwlock_init (pthread_rwlock_t *restrict __rwlock,
    const pthread_rwlockattr_t *restrict
    __attr) ;


extern int pthread_rwlock_destroy (pthread_rwlock_t *__rwlock)
     ;


extern int pthread_rwlock_rdlock (pthread_rwlock_t *__rwlock)
     ;


extern int pthread_rwlock_tryrdlock (pthread_rwlock_t *__rwlock)
  ;



extern int pthread_rwlock_timedrdlock (pthread_rwlock_t *restrict __rwlock,
           const struct timespec *restrict
           __abstime) ;



extern int pthread_rwlock_wrlock (pthread_rwlock_t *__rwlock)
     ;


extern int pthread_rwlock_trywrlock (pthread_rwlock_t *__rwlock)
     ;



extern int pthread_rwlock_timedwrlock (pthread_rwlock_t *restrict __rwlock,
           const struct timespec *restrict
           __abstime) ;



extern int pthread_rwlock_unlock (pthread_rwlock_t *__rwlock)
     ;





extern int pthread_rwlockattr_init (pthread_rwlockattr_t *__attr)
     ;


extern int pthread_rwlockattr_destroy (pthread_rwlockattr_t *__attr)
     ;


extern int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t *
       restrict __attr,
       int *restrict __pshared)
     ;


extern int pthread_rwlockattr_setpshared (pthread_rwlockattr_t *__attr,
       int __pshared)
     ;


extern int pthread_rwlockattr_getkind_np (const pthread_rwlockattr_t *
       restrict __attr,
       int *restrict __pref)
     ;


extern int pthread_rwlockattr_setkind_np (pthread_rwlockattr_t *__attr,
       int __pref) ;







extern int pthread_cond_init (pthread_cond_t *restrict __cond,
         const pthread_condattr_t *restrict __cond_attr)
     ;


extern int pthread_cond_destroy (pthread_cond_t *__cond)
     ;


extern int pthread_cond_signal (pthread_cond_t *__cond)
     ;


extern int pthread_cond_broadcast (pthread_cond_t *__cond)
     ;






extern int pthread_cond_wait (pthread_cond_t *restrict __cond,
         pthread_mutex_t *restrict __mutex)
     ;
# 1001 "/usr/include/pthread.h" 3 4
extern int pthread_cond_timedwait (pthread_cond_t *restrict __cond,
       pthread_mutex_t *restrict __mutex,
       const struct timespec *restrict __abstime)
     ;




extern int pthread_condattr_init (pthread_condattr_t *__attr)
     ;


extern int pthread_condattr_destroy (pthread_condattr_t *__attr)
     ;


extern int pthread_condattr_getpshared (const pthread_condattr_t *
     restrict __attr,
     int *restrict __pshared)
     ;


extern int pthread_condattr_setpshared (pthread_condattr_t *__attr,
     int __pshared) ;



extern int pthread_condattr_getclock (const pthread_condattr_t *
          restrict __attr,
          __clockid_t *restrict __clock_id)
     ;


extern int pthread_condattr_setclock (pthread_condattr_t *__attr,
          __clockid_t __clock_id)
     ;
# 1045 "/usr/include/pthread.h" 3 4
extern int pthread_spin_init (pthread_spinlock_t *__lock, int __pshared)
     ;


extern int pthread_spin_destroy (pthread_spinlock_t *__lock)
     ;


extern int pthread_spin_lock (pthread_spinlock_t *__lock)
     ;


extern int pthread_spin_trylock (pthread_spinlock_t *__lock)
     ;


extern int pthread_spin_unlock (pthread_spinlock_t *__lock)
     ;






extern int pthread_barrier_init (pthread_barrier_t *restrict __barrier,
     const pthread_barrierattr_t *restrict
     __attr, unsigned int __count)
     ;


extern int pthread_barrier_destroy (pthread_barrier_t *__barrier)
     ;


extern int pthread_barrier_wait (pthread_barrier_t *__barrier)
     ;



extern int pthread_barrierattr_init (pthread_barrierattr_t *__attr)
     ;


extern int pthread_barrierattr_destroy (pthread_barrierattr_t *__attr)
     ;


extern int pthread_barrierattr_getpshared (const pthread_barrierattr_t *
        restrict __attr,
        int *restrict __pshared)
     ;


extern int pthread_barrierattr_setpshared (pthread_barrierattr_t *__attr,
        int __pshared)
     ;
# 1112 "/usr/include/pthread.h" 3 4
extern int pthread_key_create (pthread_key_t *__key,
          void (*__destr_function) (void *))
     ;


extern int pthread_key_delete (pthread_key_t __key) ;


extern void *pthread_getspecific (pthread_key_t __key) ;


extern int pthread_setspecific (pthread_key_t __key,
    const void *__pointer) ;




extern int pthread_getcpuclockid (pthread_t __thread_id,
      __clockid_t *__clock_id)
     ;
# 1146 "/usr/include/pthread.h" 3 4
extern int pthread_atfork (void (*__prepare) (void),
      void (*__parent) (void),
      void (*__child) (void)) ;
# 1160 "/usr/include/pthread.h" 3 4

# 16 "/usr/local/include/neo-c2.h" 2 3
# 1 "/usr/include/unistd.h" 1 3 4
# 27 "/usr/include/unistd.h" 3 4

# 202 "/usr/include/unistd.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/posix_opt.h" 1 3 4
# 203 "/usr/include/unistd.h" 2 3 4



# 1 "/usr/include/x86_64-linux-gnu/bits/environments.h" 1 3 4
# 22 "/usr/include/x86_64-linux-gnu/bits/environments.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 23 "/usr/include/x86_64-linux-gnu/bits/environments.h" 2 3 4
# 207 "/usr/include/unistd.h" 2 3 4
# 226 "/usr/include/unistd.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/8/include/stddef.h" 1 3 4
# 227 "/usr/include/unistd.h" 2 3 4
# 267 "/usr/include/unistd.h" 3 4
typedef __intptr_t intptr_t;






typedef __socklen_t socklen_t;
# 287 "/usr/include/unistd.h" 3 4
extern int access (const char *__name, int __type) ;




extern int euidaccess (const char *__name, int __type)
     ;


extern int eaccess (const char *__name, int __type)
     ;






extern int faccessat (int __fd, const char *__file, int __type, int __flag)
     ;
# 334 "/usr/include/unistd.h" 3 4
extern __off_t lseek (int __fd, __off_t __offset, int __whence) ;
# 345 "/usr/include/unistd.h" 3 4
extern __off64_t lseek64 (int __fd, __off64_t __offset, int __whence)
     ;






extern int close (int __fd);






extern ssize_t read (int __fd, void *__buf, size_t __nbytes) ;





extern ssize_t write (int __fd, const void *__buf, size_t __n) ;
# 376 "/usr/include/unistd.h" 3 4
extern ssize_t pread (int __fd, void *__buf, size_t __nbytes,
        __off_t __offset) ;






extern ssize_t pwrite (int __fd, const void *__buf, size_t __n,
         __off_t __offset) ;
# 404 "/usr/include/unistd.h" 3 4
extern ssize_t pread64 (int __fd, void *__buf, size_t __nbytes,
   __off64_t __offset) ;


extern ssize_t pwrite64 (int __fd, const void *__buf, size_t __n,
    __off64_t __offset) ;







extern int pipe (int __pipedes[2]) ;




extern int pipe2 (int __pipedes[2], int __flags) ;
# 432 "/usr/include/unistd.h" 3 4
extern unsigned int alarm (unsigned int __seconds) ;
# 444 "/usr/include/unistd.h" 3 4
extern unsigned int sleep (unsigned int __seconds);







extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
     ;






extern int usleep (__useconds_t __useconds);
# 469 "/usr/include/unistd.h" 3 4
extern int pause (void);



extern int chown (const char *__file, __uid_t __owner, __gid_t __group)
     ;



extern int fchown (int __fd, __uid_t __owner, __gid_t __group) ;




extern int lchown (const char *__file, __uid_t __owner, __gid_t __group)
     ;






extern int fchownat (int __fd, const char *__file, __uid_t __owner,
       __gid_t __group, int __flag)
     ;



extern int chdir (const char *__path) ;



extern int fchdir (int __fd) ;
# 511 "/usr/include/unistd.h" 3 4
extern char *getcwd (char *__buf, size_t __size) ;





extern char *get_current_dir_name (void) ;







extern char *getwd (char *__buf)
     ;




extern int dup (int __fd) ;


extern int dup2 (int __fd, int __fd2) ;




extern int dup3 (int __fd, int __fd2, int __flags) ;



extern char **__environ;

extern char **environ;





extern int execve (const char *__path, char *const __argv[],
     char *const __envp[]) ;




extern int fexecve (int __fd, char *const __argv[], char *const __envp[])
     ;




extern int execv (const char *__path, char *const __argv[])
     ;



extern int execle (const char *__path, const char *__arg, ...)
     ;



extern int execl (const char *__path, const char *__arg, ...)
     ;



extern int execvp (const char *__file, char *const __argv[])
     ;




extern int execlp (const char *__file, const char *__arg, ...)
     ;




extern int execvpe (const char *__file, char *const __argv[],
      char *const __envp[])
     ;





extern int nice (int __inc) ;




extern void _exit (int __status) ;





# 1 "/usr/include/x86_64-linux-gnu/bits/confname.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/confname.h" 3 4
enum
  {
    _PC_LINK_MAX,

    _PC_MAX_CANON,

    _PC_MAX_INPUT,

    _PC_NAME_MAX,

    _PC_PATH_MAX,

    _PC_PIPE_BUF,

    _PC_CHOWN_RESTRICTED,

    _PC_NO_TRUNC,

    _PC_VDISABLE,

    _PC_SYNC_IO,

    _PC_ASYNC_IO,

    _PC_PRIO_IO,

    _PC_SOCK_MAXBUF,

    _PC_FILESIZEBITS,

    _PC_REC_INCR_XFER_SIZE,

    _PC_REC_MAX_XFER_SIZE,

    _PC_REC_MIN_XFER_SIZE,

    _PC_REC_XFER_ALIGN,

    _PC_ALLOC_SIZE_MIN,

    _PC_SYMLINK_MAX,

    _PC_2_SYMLINKS

  };


enum
  {
    _SC_ARG_MAX,

    _SC_CHILD_MAX,

    _SC_CLK_TCK,

    _SC_NGROUPS_MAX,

    _SC_OPEN_MAX,

    _SC_STREAM_MAX,

    _SC_TZNAME_MAX,

    _SC_JOB_CONTROL,

    _SC_SAVED_IDS,

    _SC_REALTIME_SIGNALS,

    _SC_PRIORITY_SCHEDULING,

    _SC_TIMERS,

    _SC_ASYNCHRONOUS_IO,

    _SC_PRIORITIZED_IO,

    _SC_SYNCHRONIZED_IO,

    _SC_FSYNC,

    _SC_MAPPED_FILES,

    _SC_MEMLOCK,

    _SC_MEMLOCK_RANGE,

    _SC_MEMORY_PROTECTION,

    _SC_MESSAGE_PASSING,

    _SC_SEMAPHORES,

    _SC_SHARED_MEMORY_OBJECTS,

    _SC_AIO_LISTIO_MAX,

    _SC_AIO_MAX,

    _SC_AIO_PRIO_DELTA_MAX,

    _SC_DELAYTIMER_MAX,

    _SC_MQ_OPEN_MAX,

    _SC_MQ_PRIO_MAX,

    _SC_VERSION,

    _SC_PAGESIZE,


    _SC_RTSIG_MAX,

    _SC_SEM_NSEMS_MAX,

    _SC_SEM_VALUE_MAX,

    _SC_SIGQUEUE_MAX,

    _SC_TIMER_MAX,




    _SC_BC_BASE_MAX,

    _SC_BC_DIM_MAX,

    _SC_BC_SCALE_MAX,

    _SC_BC_STRING_MAX,

    _SC_COLL_WEIGHTS_MAX,

    _SC_EQUIV_CLASS_MAX,

    _SC_EXPR_NEST_MAX,

    _SC_LINE_MAX,

    _SC_RE_DUP_MAX,

    _SC_CHARCLASS_NAME_MAX,


    _SC_2_VERSION,

    _SC_2_C_BIND,

    _SC_2_C_DEV,

    _SC_2_FORT_DEV,

    _SC_2_FORT_RUN,

    _SC_2_SW_DEV,

    _SC_2_LOCALEDEF,


    _SC_PII,

    _SC_PII_XTI,

    _SC_PII_SOCKET,

    _SC_PII_INTERNET,

    _SC_PII_OSI,

    _SC_POLL,

    _SC_SELECT,

    _SC_UIO_MAXIOV,

    _SC_IOV_MAX = _SC_UIO_MAXIOV,

    _SC_PII_INTERNET_STREAM,

    _SC_PII_INTERNET_DGRAM,

    _SC_PII_OSI_COTS,

    _SC_PII_OSI_CLTS,

    _SC_PII_OSI_M,

    _SC_T_IOV_MAX,



    _SC_THREADS,

    _SC_THREAD_SAFE_FUNCTIONS,

    _SC_GETGR_R_SIZE_MAX,

    _SC_GETPW_R_SIZE_MAX,

    _SC_LOGIN_NAME_MAX,

    _SC_TTY_NAME_MAX,

    _SC_THREAD_DESTRUCTOR_ITERATIONS,

    _SC_THREAD_KEYS_MAX,

    _SC_THREAD_STACK_MIN,

    _SC_THREAD_THREADS_MAX,

    _SC_THREAD_ATTR_STACKADDR,

    _SC_THREAD_ATTR_STACKSIZE,

    _SC_THREAD_PRIORITY_SCHEDULING,

    _SC_THREAD_PRIO_INHERIT,

    _SC_THREAD_PRIO_PROTECT,

    _SC_THREAD_PROCESS_SHARED,


    _SC_NPROCESSORS_CONF,

    _SC_NPROCESSORS_ONLN,

    _SC_PHYS_PAGES,

    _SC_AVPHYS_PAGES,

    _SC_ATEXIT_MAX,

    _SC_PASS_MAX,


    _SC_XOPEN_VERSION,

    _SC_XOPEN_XCU_VERSION,

    _SC_XOPEN_UNIX,

    _SC_XOPEN_CRYPT,

    _SC_XOPEN_ENH_I18N,

    _SC_XOPEN_SHM,


    _SC_2_CHAR_TERM,

    _SC_2_C_VERSION,

    _SC_2_UPE,


    _SC_XOPEN_XPG2,

    _SC_XOPEN_XPG3,

    _SC_XOPEN_XPG4,


    _SC_CHAR_BIT,

    _SC_CHAR_MAX,

    _SC_CHAR_MIN,

    _SC_INT_MAX,

    _SC_INT_MIN,

    _SC_LONG_BIT,

    _SC_WORD_BIT,

    _SC_MB_LEN_MAX,

    _SC_NZERO,

    _SC_SSIZE_MAX,

    _SC_SCHAR_MAX,

    _SC_SCHAR_MIN,

    _SC_SHRT_MAX,

    _SC_SHRT_MIN,

    _SC_UCHAR_MAX,

    _SC_UINT_MAX,

    _SC_ULONG_MAX,

    _SC_USHRT_MAX,


    _SC_NL_ARGMAX,

    _SC_NL_LANGMAX,

    _SC_NL_MSGMAX,

    _SC_NL_NMAX,

    _SC_NL_SETMAX,

    _SC_NL_TEXTMAX,


    _SC_XBS5_ILP32_OFF32,

    _SC_XBS5_ILP32_OFFBIG,

    _SC_XBS5_LP64_OFF64,

    _SC_XBS5_LPBIG_OFFBIG,


    _SC_XOPEN_LEGACY,

    _SC_XOPEN_REALTIME,

    _SC_XOPEN_REALTIME_THREADS,


    _SC_ADVISORY_INFO,

    _SC_BARRIERS,

    _SC_BASE,

    _SC_C_LANG_SUPPORT,

    _SC_C_LANG_SUPPORT_R,

    _SC_CLOCK_SELECTION,

    _SC_CPUTIME,

    _SC_THREAD_CPUTIME,

    _SC_DEVICE_IO,

    _SC_DEVICE_SPECIFIC,

    _SC_DEVICE_SPECIFIC_R,

    _SC_FD_MGMT,

    _SC_FIFO,

    _SC_PIPE,

    _SC_FILE_ATTRIBUTES,

    _SC_FILE_LOCKING,

    _SC_FILE_SYSTEM,

    _SC_MONOTONIC_CLOCK,

    _SC_MULTI_PROCESS,

    _SC_SINGLE_PROCESS,

    _SC_NETWORKING,

    _SC_READER_WRITER_LOCKS,

    _SC_SPIN_LOCKS,

    _SC_REGEXP,

    _SC_REGEX_VERSION,

    _SC_SHELL,

    _SC_SIGNALS,

    _SC_SPAWN,

    _SC_SPORADIC_SERVER,

    _SC_THREAD_SPORADIC_SERVER,

    _SC_SYSTEM_DATABASE,

    _SC_SYSTEM_DATABASE_R,

    _SC_TIMEOUTS,

    _SC_TYPED_MEMORY_OBJECTS,

    _SC_USER_GROUPS,

    _SC_USER_GROUPS_R,

    _SC_2_PBS,

    _SC_2_PBS_ACCOUNTING,

    _SC_2_PBS_LOCATE,

    _SC_2_PBS_MESSAGE,

    _SC_2_PBS_TRACK,

    _SC_SYMLOOP_MAX,

    _SC_STREAMS,

    _SC_2_PBS_CHECKPOINT,


    _SC_V6_ILP32_OFF32,

    _SC_V6_ILP32_OFFBIG,

    _SC_V6_LP64_OFF64,

    _SC_V6_LPBIG_OFFBIG,


    _SC_HOST_NAME_MAX,

    _SC_TRACE,

    _SC_TRACE_EVENT_FILTER,

    _SC_TRACE_INHERIT,

    _SC_TRACE_LOG,


    _SC_LEVEL1_ICACHE_SIZE,

    _SC_LEVEL1_ICACHE_ASSOC,

    _SC_LEVEL1_ICACHE_LINESIZE,

    _SC_LEVEL1_DCACHE_SIZE,

    _SC_LEVEL1_DCACHE_ASSOC,

    _SC_LEVEL1_DCACHE_LINESIZE,

    _SC_LEVEL2_CACHE_SIZE,

    _SC_LEVEL2_CACHE_ASSOC,

    _SC_LEVEL2_CACHE_LINESIZE,

    _SC_LEVEL3_CACHE_SIZE,

    _SC_LEVEL3_CACHE_ASSOC,

    _SC_LEVEL3_CACHE_LINESIZE,

    _SC_LEVEL4_CACHE_SIZE,

    _SC_LEVEL4_CACHE_ASSOC,

    _SC_LEVEL4_CACHE_LINESIZE,



    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,

    _SC_RAW_SOCKETS,


    _SC_V7_ILP32_OFF32,

    _SC_V7_ILP32_OFFBIG,

    _SC_V7_LP64_OFF64,

    _SC_V7_LPBIG_OFFBIG,


    _SC_SS_REPL_MAX,


    _SC_TRACE_EVENT_NAME_MAX,

    _SC_TRACE_NAME_MAX,

    _SC_TRACE_SYS_MAX,

    _SC_TRACE_USER_EVENT_MAX,


    _SC_XOPEN_STREAMS,


    _SC_THREAD_ROBUST_PRIO_INHERIT,

    _SC_THREAD_ROBUST_PRIO_PROTECT

  };


enum
  {
    _CS_PATH,


    _CS_V6_WIDTH_RESTRICTED_ENVS,



    _CS_GNU_LIBC_VERSION,

    _CS_GNU_LIBPTHREAD_VERSION,


    _CS_V5_WIDTH_RESTRICTED_ENVS,



    _CS_V7_WIDTH_RESTRICTED_ENVS,



    _CS_LFS_CFLAGS = 1000,

    _CS_LFS_LDFLAGS,

    _CS_LFS_LIBS,

    _CS_LFS_LINTFLAGS,

    _CS_LFS64_CFLAGS,

    _CS_LFS64_LDFLAGS,

    _CS_LFS64_LIBS,

    _CS_LFS64_LINTFLAGS,


    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,

    _CS_XBS5_ILP32_OFF32_LDFLAGS,

    _CS_XBS5_ILP32_OFF32_LIBS,

    _CS_XBS5_ILP32_OFF32_LINTFLAGS,

    _CS_XBS5_ILP32_OFFBIG_CFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,

    _CS_XBS5_ILP32_OFFBIG_LIBS,

    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,

    _CS_XBS5_LP64_OFF64_CFLAGS,

    _CS_XBS5_LP64_OFF64_LDFLAGS,

    _CS_XBS5_LP64_OFF64_LIBS,

    _CS_XBS5_LP64_OFF64_LINTFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,

    _CS_XBS5_LPBIG_OFFBIG_LIBS,

    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFF32_LIBS,

    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V6_LP64_OFF64_CFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V6_LP64_OFF64_LIBS,

    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,


    _CS_POSIX_V7_ILP32_OFF32_CFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,

    _CS_POSIX_V7_ILP32_OFF32_LIBS,

    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,

    _CS_POSIX_V7_ILP32_OFFBIG_LIBS,

    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,

    _CS_POSIX_V7_LP64_OFF64_CFLAGS,

    _CS_POSIX_V7_LP64_OFF64_LDFLAGS,

    _CS_POSIX_V7_LP64_OFF64_LIBS,

    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,

    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS,


    _CS_V6_ENV,

    _CS_V7_ENV

  };
# 610 "/usr/include/unistd.h" 2 3 4


extern long int pathconf (const char *__path, int __name)
     ;


extern long int fpathconf (int __fd, int __name) ;


extern long int sysconf (int __name) ;



extern size_t confstr (int __name, char *__buf, size_t __len) ;




extern __pid_t getpid (void) ;


extern __pid_t getppid (void) ;


extern __pid_t getpgrp (void) ;


extern __pid_t __getpgid (__pid_t __pid) ;

extern __pid_t getpgid (__pid_t __pid) ;






extern int setpgid (__pid_t __pid, __pid_t __pgid) ;
# 660 "/usr/include/unistd.h" 3 4
extern int setpgrp (void) ;






extern __pid_t setsid (void) ;



extern __pid_t getsid (__pid_t __pid) ;



extern __uid_t getuid (void) ;


extern __uid_t geteuid (void) ;


extern __gid_t getgid (void) ;


extern __gid_t getegid (void) ;




extern int getgroups (int __size, __gid_t __list[]) ;



extern int group_member (__gid_t __gid) ;






extern int setuid (__uid_t __uid) ;




extern int setreuid (__uid_t __ruid, __uid_t __euid) ;




extern int seteuid (__uid_t __uid) ;






extern int setgid (__gid_t __gid) ;




extern int setregid (__gid_t __rgid, __gid_t __egid) ;




extern int setegid (__gid_t __gid) ;





extern int getresuid (__uid_t *__ruid, __uid_t *__euid, __uid_t *__suid)
     ;



extern int getresgid (__gid_t *__rgid, __gid_t *__egid, __gid_t *__sgid)
     ;



extern int setresuid (__uid_t __ruid, __uid_t __euid, __uid_t __suid)
     ;



extern int setresgid (__gid_t __rgid, __gid_t __egid, __gid_t __sgid)
     ;






extern __pid_t fork (void) ;







extern __pid_t vfork (void) ;





extern char *ttyname (int __fd) ;



extern int ttyname_r (int __fd, char *__buf, size_t __buflen)
     ;



extern int isatty (int __fd) ;




extern int ttyslot (void) ;




extern int link (const char *__from, const char *__to)
     ;




extern int linkat (int __fromfd, const char *__from, int __tofd,
     const char *__to, int __flags)
     ;




extern int symlink (const char *__from, const char *__to)
     ;




extern ssize_t readlink (const char *restrict __path,
    char *restrict __buf, size_t __len)
     ;




extern int symlinkat (const char *__from, int __tofd,
        const char *__to) ;


extern ssize_t readlinkat (int __fd, const char *restrict __path,
      char *restrict __buf, size_t __len)
     ;



extern int unlink (const char *__name) ;



extern int unlinkat (int __fd, const char *__name, int __flag)
     ;



extern int rmdir (const char *__path) ;



extern __pid_t tcgetpgrp (int __fd) ;


extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) ;






extern char *getlogin (void);







extern int getlogin_r (char *__name, size_t __name_len) ;




extern int setlogin (const char *__name) ;







# 1 "/usr/include/x86_64-linux-gnu/bits/getopt_posix.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/getopt_posix.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/getopt_core.h" 1 3 4
# 28 "/usr/include/x86_64-linux-gnu/bits/getopt_core.h" 3 4








extern char *optarg;
# 50 "/usr/include/x86_64-linux-gnu/bits/getopt_core.h" 3 4
extern int optind;




extern int opterr;



extern int optopt;
# 91 "/usr/include/x86_64-linux-gnu/bits/getopt_core.h" 3 4
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       ;


# 28 "/usr/include/x86_64-linux-gnu/bits/getopt_posix.h" 2 3 4


# 49 "/usr/include/x86_64-linux-gnu/bits/getopt_posix.h" 3 4

# 870 "/usr/include/unistd.h" 2 3 4







extern int gethostname (char *__name, size_t __len) ;






extern int sethostname (const char *__name, size_t __len)
     ;



extern int sethostid (long int __id) ;





extern int getdomainname (char *__name, size_t __len)
     ;
extern int setdomainname (const char *__name, size_t __len)
     ;





extern int vhangup (void) ;


extern int revoke (const char *__file) ;







extern int profil (unsigned short int *__sample_buffer, size_t __size,
     size_t __offset, unsigned int __scale)
     ;





extern int acct (const char *__name) ;



extern char *getusershell (void) ;
extern void endusershell (void) ;
extern void setusershell (void) ;





extern int daemon (int __nochdir, int __noclose) ;






extern int chroot (const char *__path) ;



extern char *getpass (const char *__prompt) ;







extern int fsync (int __fd);





extern int syncfs (int __fd) ;






extern long int gethostid (void);


extern void sync (void) ;





extern int getpagesize (void) ;




extern int getdtablesize (void) ;
# 991 "/usr/include/unistd.h" 3 4
extern int truncate (const char *__file, __off_t __length)
     ;
# 1003 "/usr/include/unistd.h" 3 4
extern int truncate64 (const char *__file, __off64_t __length)
     ;
# 1014 "/usr/include/unistd.h" 3 4
extern int ftruncate (int __fd, __off_t __length) ;
# 1024 "/usr/include/unistd.h" 3 4
extern int ftruncate64 (int __fd, __off64_t __length) ;
# 1035 "/usr/include/unistd.h" 3 4
extern int brk (void *__addr) ;





extern void *sbrk (intptr_t __delta) ;
# 1056 "/usr/include/unistd.h" 3 4
extern long int syscall (long int __sysno, ...) ;
# 1079 "/usr/include/unistd.h" 3 4
extern int lockf (int __fd, int __cmd, __off_t __len) ;
# 1089 "/usr/include/unistd.h" 3 4
extern int lockf64 (int __fd, int __cmd, __off64_t __len) ;
# 1107 "/usr/include/unistd.h" 3 4
ssize_t copy_file_range (int __infd, __off64_t *__pinoff,
    int __outfd, __off64_t *__poutoff,
    size_t __length, unsigned int __flags);





extern int fdatasync (int __fildes);
# 1124 "/usr/include/unistd.h" 3 4
extern char *crypt (const char *__key, const char *__salt)
     ;







extern void swab (const void *restrict __from, void *restrict __to,
    ssize_t __n) ;
# 1161 "/usr/include/unistd.h" 3 4
int getentropy (void *__buffer, size_t __length) ;








# 17 "/usr/local/include/neo-c2.h" 2 3
# 1 "/usr/include/x86_64-linux-gnu/sys/stat.h" 1 3 4
# 99 "/usr/include/x86_64-linux-gnu/sys/stat.h" 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/stat.h" 1 3 4
# 46 "/usr/include/x86_64-linux-gnu/bits/stat.h" 3 4
struct stat
  {
    __dev_t st_dev;




    __ino_t st_ino;







    __nlink_t st_nlink;
    __mode_t st_mode;

    __uid_t st_uid;
    __gid_t st_gid;

    int __pad0;

    __dev_t st_rdev;




    __off_t st_size;



    __blksize_t st_blksize;

    __blkcnt_t st_blocks;
# 91 "/usr/include/x86_64-linux-gnu/bits/stat.h" 3 4
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
# 106 "/usr/include/x86_64-linux-gnu/bits/stat.h" 3 4
    __syscall_slong_t __glibc_reserved[3];
# 115 "/usr/include/x86_64-linux-gnu/bits/stat.h" 3 4
  };



struct stat64
  {
    __dev_t st_dev;

    __ino64_t st_ino;
    __nlink_t st_nlink;
    __mode_t st_mode;






    __uid_t st_uid;
    __gid_t st_gid;

    int __pad0;
    __dev_t st_rdev;
    __off_t st_size;





    __blksize_t st_blksize;
    __blkcnt64_t st_blocks;







    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
# 164 "/usr/include/x86_64-linux-gnu/bits/stat.h" 3 4
    __syscall_slong_t __glibc_reserved[3];



  };
# 102 "/usr/include/x86_64-linux-gnu/sys/stat.h" 2 3 4
# 205 "/usr/include/x86_64-linux-gnu/sys/stat.h" 3 4
extern int stat (const char *restrict __file,
   struct stat *restrict __buf) ;



extern int fstat (int __fd, struct stat *__buf) ;
# 224 "/usr/include/x86_64-linux-gnu/sys/stat.h" 3 4
extern int stat64 (const char *restrict __file,
     struct stat64 *restrict __buf) ;
extern int fstat64 (int __fd, struct stat64 *__buf) ;







extern int fstatat (int __fd, const char *restrict __file,
      struct stat *restrict __buf, int __flag)
     ;
# 249 "/usr/include/x86_64-linux-gnu/sys/stat.h" 3 4
extern int fstatat64 (int __fd, const char *restrict __file,
        struct stat64 *restrict __buf, int __flag)
     ;







extern int lstat (const char *restrict __file,
    struct stat *restrict __buf) ;
# 272 "/usr/include/x86_64-linux-gnu/sys/stat.h" 3 4
extern int lstat64 (const char *restrict __file,
      struct stat64 *restrict __buf)
     ;





extern int chmod (const char *__file, __mode_t __mode)
     ;





extern int lchmod (const char *__file, __mode_t __mode)
     ;




extern int fchmod (int __fd, __mode_t __mode) ;





extern int fchmodat (int __fd, const char *__file, __mode_t __mode,
       int __flag)
     ;






extern __mode_t umask (__mode_t __mask) ;




extern __mode_t getumask (void) ;



extern int mkdir (const char *__path, __mode_t __mode)
     ;





extern int mkdirat (int __fd, const char *__path, __mode_t __mode)
     ;






extern int mknod (const char *__path, __mode_t __mode, __dev_t __dev)
     ;





extern int mknodat (int __fd, const char *__path, __mode_t __mode,
      __dev_t __dev) ;





extern int mkfifo (const char *__path, __mode_t __mode)
     ;





extern int mkfifoat (int __fd, const char *__path, __mode_t __mode)
     ;





extern int utimensat (int __fd, const char *__path,
        const struct timespec __times[2],
        int __flags)
     ;




extern int futimens (int __fd, const struct timespec __times[2]) ;
# 395 "/usr/include/x86_64-linux-gnu/sys/stat.h" 3 4
extern int __fxstat (int __ver, int __fildes, struct stat *__stat_buf)
     ;
extern int __xstat (int __ver, const char *__filename,
      struct stat *__stat_buf) ;
extern int __lxstat (int __ver, const char *__filename,
       struct stat *__stat_buf) ;
extern int __fxstatat (int __ver, int __fildes, const char *__filename,
         struct stat *__stat_buf, int __flag)
     ;
# 428 "/usr/include/x86_64-linux-gnu/sys/stat.h" 3 4
extern int __fxstat64 (int __ver, int __fildes, struct stat64 *__stat_buf)
     ;
extern int __xstat64 (int __ver, const char *__filename,
        struct stat64 *__stat_buf) ;
extern int __lxstat64 (int __ver, const char *__filename,
         struct stat64 *__stat_buf) ;
extern int __fxstatat64 (int __ver, int __fildes, const char *__filename,
    struct stat64 *__stat_buf, int __flag)
     ;

extern int __xmknod (int __ver, const char *__path, __mode_t __mode,
       __dev_t *__dev) ;

extern int __xmknodat (int __ver, int __fd, const char *__path,
         __mode_t __mode, __dev_t *__dev)
     ;


# 1 "/usr/include/x86_64-linux-gnu/bits/statx.h" 1 3 4
# 25 "/usr/include/x86_64-linux-gnu/bits/statx.h" 3 4
struct statx_timestamp
{
  __int64_t tv_sec;
  __uint32_t tv_nsec;
  __int32_t __statx_timestamp_pad1[1];
};





struct statx
{
  __uint32_t stx_mask;
  __uint32_t stx_blksize;
  __uint64_t stx_attributes;
  __uint32_t stx_nlink;
  __uint32_t stx_uid;
  __uint32_t stx_gid;
  __uint16_t stx_mode;
  __uint16_t __statx_pad1[1];
  __uint64_t stx_ino;
  __uint64_t stx_size;
  __uint64_t stx_blocks;
  __uint64_t stx_attributes_mask;
  struct statx_timestamp stx_atime;
  struct statx_timestamp stx_btime;
  struct statx_timestamp stx_ctime;
  struct statx_timestamp stx_mtime;
  __uint32_t stx_rdev_major;
  __uint32_t stx_rdev_minor;
  __uint32_t stx_dev_major;
  __uint32_t stx_dev_minor;
  __uint64_t __statx_pad2[14];
};
# 84 "/usr/include/x86_64-linux-gnu/bits/statx.h" 3 4



int statx (int __dirfd, const char *restrict __path, int __flags,
           unsigned int __mask, struct statx *restrict __buf)
  ;


# 447 "/usr/include/x86_64-linux-gnu/sys/stat.h" 2 3 4
# 534 "/usr/include/x86_64-linux-gnu/sys/stat.h" 3 4

# 18 "/usr/local/include/neo-c2.h" 2 3




typedef char* string;

static void* ncmemdup(void* block)
{
    size_t size = GC_size(block);

    if(!block) {
        return null;
    }

    void* ret = GC_malloc(size);

    if (ret) {
        char* p = ret;
        char* p2 = block;
        while(p - ret < size) {
            *p = *p2;
            p++;
            p2++;
        }
    }

    return ret;
}

inline void xassert(const char* msg, bool exp)
{
    printf(msg);
    printf("...");

    if(exp) {
        puts("ok");
    }
    else {
        puts("false");
        exit(2);
    }
}

inline string string(char* str)
{
    int len = strlen(str) + 1;
    char* result = (char*)GC_malloc(sizeof(char)*len);

    strncpy(result, str, len);

    return result;
}

static string xsprintf(char* msg, ...)
{
    va_list args;
    __builtin_va_start(args,msg);
    char* result;
    int len = vasprintf(&result, msg, args);
    __builtin_va_end(args);

    if(len < 0) {
        fprintf(stderr, "can't get heap memory.\n");

        exit(2);
    }

    string result2 = string(result);

    free(result);

    return result2;
}

static string char::reverse(char* str)
{
    int len = strlen(str);
    char* result = new char[len + 1];

    for(int i=0; i<len; i++) {
        result[i] = str[len-i-1];
    }

    result[len] = '\0';

    return result;
}

static string char::substring(char* str, int head, int tail)
{
    if(str == null) {
        return string("");
    }

    int len = strlen(str);

    if(head < 0) {
        head += len;
    }
    if(tail < 0) {
        tail += len + 1;
    }

    if(head > tail) {
        return str.substring(tail, head).reverse();
    }

    if(head < 0) {
        head = 0;
    }

    if(tail >= len) {
        tail = len;
    }

    if(head == tail) {
        return string("");
    }

    if(tail-head+1 < 1) {
        return string("");
    }

    string result = new char[tail-head+1];

    memcpy(result, str + head, tail-head);
    result[tail-head] = '\0';

    return result;
}

static int char::length(char* str)
{
    return strlen(str);
}


static int int::get_hash_key(int value)
{
    return value;
}


static int char::get_hash_key(char* value)
{
    int result = 0;
    char* p = value;
    while(*p) {
        result += (*p);
        p++;
    }
    return result;
}

static bool char::equals(string left, string right)
{
    return strcmp(left, right) == 0;
}

static int char::compare(int left, int right)
{
    if(left < right) {
        return -1;
    }
    else if(left > right) {
        return 1;
    }
    else {
        return 0;
    }
}


struct vector<T>
{
    T* items;
    int len;
    int size;

    int it;
};

impl vector<T>
{
    vector<T>* initialize(vector<T>* self)
    {
        self.size = 16;
        self.len = 0;
        self.items = new T[self.size];

        return self;
    }

    vector<T>* clone(vector<T>* self)
    {
        vector<T>* result = new vector<T>;

        result.len = self.len;
        result.size = self.size;
        result.it = 0;
        result.items = new T[result.size];

        for(int i=0; i<self.len; i++)
        {
            if(GC_is_heap_ptr(self.items[i])) {
                result.items[i] = clone self.items[i];
            }
            else {
                result.items[i] = self.items[i];
            }
        }

        return result;
    }

    void push_back(vector<T>* self, T item) {
        if(self.len == self.size) {
            auto new_size = self.size * 2;
            auto items = self.items;

            self.items = GC_malloc(sizeof(T)*new_size);

            int i;
            for(i=0; i<self.size; i++) {
                self.items[i] = items[i];
            }

            self.size = new_size;
        }

        self.items[self.len] = item;
        self.len++;
    }

    T item(vector<T>* self, int index, T default_value)
    {
        if(index < 0) {
            index += self.len;
        }

        if(index >= 0 && index < self.len)
        {
            return self.items[index];
        }

        return default_value;
    }

    bool equals(vector<T>* left, vector<T>* right)
    {
        if(left.len != right.len) {
            return false;
        }

        for(int i=0; i<left.len; i++) {
            if(!(left.items[i].equals(right.items[i])))
            {
                return false;
            }
        }

        return true;
    }

    bool replace(vector<T>* self, int index, T value)
    {
        if(index < 0) {
            index += self.len;
        }

        if(index >= 0 && index < self.len)
        {
            self.items[index] = value;

            return true;
        }

        return false;
    }

    int find(vector<T>* self, T item, int default_value) {
        int it2 = 0;
        for(auto _obj = (self), auto it = _obj.begin(); !_obj.end(); it = _obj.next()) {
            if(it.equals(item)) {
                return it2;
            }
            it2++;
        }

        return default_value;
    }

    int length(vector<T>* self)
    {
        return self.len;
    }

    void reset(vector<T>* self) {
        self.len = 0;
    }

    T begin(vector<T>* self) {
        self.it = 0;

        T default_value;
        return self.item(0, default_value);
    }

    T next(vector<T>* self) {
        self.it++;

        T default_value
        return self.item(self.it, default_value);
    }

    bool end(vector<T>* self) {
        return self.it >= self.len;
    }
}


struct list_item<T>
{
    T item;
    list_item<T>* prev;
    list_item<T>* next;
};

struct list<T>
{
    list_item<T>* head;
    list_item<T>* tail;
    int len;

    list_item<T>* it;
};


impl list <T>
{
    list<T>* initialize(list<T>* self) {
        self.head = null;
        self.tail = null;
        self.len = 0;

        return self;
    }

    list<T>* clone(list<T>* self) {
        auto result = new list<T>.initialize();

        list_item<T>* it = self.head;
        while(it != null) {
            if(GC_is_heap_ptr(it.item)) {
                result.push_back(clone it.item);
            }
            else {
                result.push_back(it.item);
            }

            it = it.next;
        }

        return result;
    }

    int length(list<T>* self)
    {
        return self.len;
    }
    void push_back(list<T>* self, T item)
    {
        if(self.len == 0) {
            list_item<T>* litem = new list_item<T>;

            litem.prev = null;
            litem.next = null;
            litem.item = item;

            self.tail = litem;
            self.head = litem;
        }
        else if(self.len == 1) {
            list_item<T>* litem = new list_item<T>;

            litem.prev = self.head;
            litem.next = null;
            litem.item = item;

            self.tail = litem;
            self.head.next = litem;
        }
        else {
            list_item<T>* litem = new list_item<T>;

            litem.prev = self.tail;
            litem.next = null;
            litem.item = item;

            self.tail.next = litem;
            self.tail = litem;
        }

        self.len++;
    }

    T item(list<T>* self, int position, T default_value)
    {
        if(position < 0) {
            position += self.len;
        }

        list_item<T>* it = self.head;
        auto i = 0;
        while(it != null) {
            if(position == i) {
                return it.item;
            }
            it = it.next;
            i++;
        };

        return default_value;
    }

    void insert(list<T>* self, int position, T item)
    {
        if(position < 0) {
            position += self.len + 1;
        }
        if(position < 0) {
            position = 0;
        }
        if(self.len == 0 || position >= self.len)
        {
            self.push_back(item);
            return;
        }

        if(position == 0) {
            list_item<T>* litem = new list_item<T>;

            litem.prev = null;
            litem.next = self.head;
            litem.item = item;

            self.head.prev = litem;
            self.head = litem;

            self.len++;
        }
        else if(self.len == 1) {
            auto litem = new list_item<T>;

            litem.prev = self.head;
            litem.next = self.tail;
            litem.item = item;

            self.tail.prev = litem;
            self.head.next = litem;

            self.len++;
        }
        else {
            list_item<T>* it = self.head;
            auto i = 0;
            while(it != null) {
                if(position == i) {
                    list_item<T>* litem = new list_item<T>;

                    litem.prev = it.prev;
                    litem.next = it;
                    litem.item = item;

                    it.prev.next = litem;
                    it.prev = litem;

                    self.len++;
                }

                it = it.next;
                i++;
            }
        }
    }

    void reset(list<T>* self) {
        list_item<T>* it = self.head;
        while(it != null) {
            auto prev_it = it;
            it = it.next;
        }

        self.head = null;
        self.tail = null;

        self.len = 0;
    }

    void delete(list<T>* self, int head, int tail)
    {
        if(head < 0) {
            head += self.len;
        }
        if(tail < 0) {
            tail += self.len + 1;
        }

        if(head > tail) {
            int tmp = tail;
            tail = head;
            head = tmp;
        }

        if(head < 0) {
            head = 0;
        }

        if(tail > self.len) {
            tail = self.len;
        }

        if(head == tail) {
            return;
        }

        if(head == 0 && tail == self.len)
        {
            self.reset();
        }
        else if(head == 0) {
            list_item<T>* it = self.head;
            auto i = 0;
            while(it != null) {
                if(i < tail) {
                    list_item<T>* prev_it = it;

                    it = it.next;
                    i++;

                    self.len--;
                }
                else if(i == tail) {
                    self.head = it;
                    self.head.prev = null;
                    break;
                }
                else {
                    it = it.next;
                    i++;
                }
            }
        }
        else if(tail == self.len) {
            list_item<T>* it = self.head;
            auto i = 0;
            while(it != null) {
                if(i == head) {
                    self.tail = it.prev;
                    self.tail.next = null;
                }

                if(i >= head) {
                    list_item<T>* prev_it = it;

                    it = it.next;
                    i++;

                    self.len--;
                }
                else {
                    it = it.next;
                    i++;
                }
            }
        }
        else {
            list_item<T>* it = self.head;

            list_item<T>* head_prev_it = null;
            list_item<T>* tail_it = null;

            auto i = 0;
            while(it != null) {
                if(i == head) {
                    head_prev_it = it.prev;
                }
                if(i == tail) {
                    tail_it = it;
                }

                if(i >= head && i < tail)
                {
                    list_item<T>* prev_it = it;

                    it = it.next;
                    i++;

                    self.len--;
                }
                else {
                    it = it.next;
                    i++;
                }
            }

            if(head_prev_it != null) {
                head_prev_it.next = tail_it;
            }
            if(tail_it != null) {
                tail_it.prev = head_prev_it;
            }
        }
    }

    void replace(list<T>* self, int position, T item)
    {
        if(position < 0) {
            position += self.len;
        }

        list_item<T>* it = self.head;
        int i = 0;
        while(it != null) {
            if(position == i) {
                it.item = item;
                break;
            }
            it = it.next;
            i++;
        }
    }

    int find(list<T>* self, T item, int default_value) {
        int it2 = 0;
        for(auto _obj = (self), auto it = _obj.begin(); !_obj.end(); it = _obj.next()) {
            if(it.equals(item)) {
                return it2;
            }
            it2++;
        }

        return default_value;
    }

    list<T>* sublist(list<T>* self, int begin, int tail) {
        list<T>* result = new list<T>.initialize();

        if(begin < 0) {
            begin += self.len;
        }

        if(tail < 0) {
            tail += self.len + 1;
        }

        if(begin < 0) {
            begin = 0;
        }

        if(tail >= self.len) {
            tail = self.len;
        }

        list_item<T>* it = self.head;
        int i = 0;
        while(it != null) {
            if(i >= begin && i < tail) {
                if(GC_is_heap_ptr(it.item)) {
                    result.push_back(clone it.item);
                }
                else {
                    result.push_back(it.item);
                }
            }
            it = it.next;
            i++;
        };

        return result;
    }

    list<T>* reverse(list<T>* self) {
        list<T>* result = new list<T>.initialize();

        list_item<T>* it = self.tail;
        while(it != null) {
            if(GC_is_heap_ptr(it.item)) {
                result.push_back(clone it.item);
            }
            else {
                result.push_back(it.item);
            }
            it = it.prev;
        };

        return result;
    }

    list<T>* merge_list(list<T>* left, list<T>* right, int (*compare)(T,T)) {
        auto result = new list<T>.initialize();

        list_item<T>*? it = left.head;
        list_item<T>*? it2= right.head;

        while(true) {
            if(it && it2) {
                if(it.item == null) {
                    it = it.next;
                }
                else if(it2.item == null) {
                    it2 = it2.next;
                }
                else if(compare(it.item, it2.item) <= 0)
                {
                    if(GC_is_heap_ptr(it.item)) {
                        result.push_back(clone it.item);
                    }
                    else {
                        result.push_back(it.item);
                    }

                    it = it.next;
                }
                else {
                    if(GC_is_heap_ptr(it.item)) {
                        result.push_back(clone it2.item);
                    }
                    else {
                        result.push_back(it2.item);
                    }

                    it2 = it2.next;
                }
            }

            if(it == null) {
                if(it2 != null) {
                    while(it2 != null) {
                        if(GC_is_heap_ptr(it2.item)) {
                            result.push_back(clone it2.item);
                        }
                        else {
                            result.push_back(it2.item);
                        }

                        it2 = it2.next;
                    }
                }
                break;
            }
            else if(it2 == null) {
                if(it != null) {
                    while(it != null) {
                        if(GC_is_heap_ptr(it.item)) {
                            result.push_back(clone it.item);
                        }
                        else {
                            result.push_back(it.item);
                        }

                        it = it.next;
                    }
                }
                break;
            }
        }

        return result;
    }
    list<T>* merge_sort(list<T>* self, int (*compare)(T,T)) {
        if(self.head == null) {
            return clone self;
        }
        if(self.head.next == null) {
            return clone self;
        }

        auto list1 = new list<T>.initialize();
        auto list2 = new list<T>.initialize();

        list_item<T>* it = self.head;

        while(true) {
            if(GC_is_heap_ptr(it.item)) {
                list1.push_back(clone it.item);
            }
            else {
                list1.push_back(it.item);
            }

            if(GC_is_heap_ptr(it.next.item)) {
                list2.push_back(clone it.next.item);
            }
            else {
                list2.push_back(it.next.item);
            }

            if(it.next.next == null) {
                break;
            }

            it = it.next.next;

            if(it.next == null) {
                if(GC_is_heap_ptr(it.item)) {
                    list1.push_back(clone it.item);
                }
                else {
                    list1.push_back(it.item);
                }
                break;
            }
        }

        return list1.merge_sort(compare).merge_list( list2.merge_sort(compare), compare);
    }
    list<T>* sort(list<T>* self, int (*compare)(T,T)) {
        return self.merge_sort(compare);
    }

    list<T>* uniq(list<T>* self) {
        list<T>* result = new list<T>.initialize();

        if(self.length() > 0) {
            T default_value;
            T item_before = self.item(0, default_value);

            if(GC_is_heap_ptr(item_before)) {
                result.push_back(clone item_before);
            }
            else {
                result.push_back(item_before);
            }

            for(auto _obj = (self.sublist(1,-1)), auto it = _obj.begin(); !_obj.end(); it = _obj.next()) {
                if(!it.equals(item_before)) {
                    if(GC_is_heap_ptr(it)) {
                        result.push_back(clone it);
                    }
                    else {
                        result.push_back(it);
                    }
                }

                item_before = it;
            }
        }

        return result;
    }

    bool equals(list<T>* left, list<T>* right)
    {
        if(left.len != right.len) {
            return false;
        }

        list_item<T>* it = left.head;
        list_item<T>* it2 = right.head;

        while(it != null) {
            if(!it.item.equals(it2.item)) {
                return false;
            }

            it = it.next;
            it2 = it2.next;
        }

        return true;
    }

    T begin(list<T>* self) {
        self.it = self.head;

        if(self.it) {
            return self.it.item;
        }
        else {
            return null;
        }
    }

    T next(list<T>* self) {
        self.it = self.it.next;

        if(self.it) {
            return self.it.item;
        }
        else {
            return null;
        }
    }

    bool end(list<T>* self) {
        return self.it == null;
    }
}

impl vector<T>
{
    list<T>* to_list(vector<T>* self) {
        auto result = new list<T>.initialize();

        for(auto _obj = (self), auto it = _obj.begin(); !_obj.end(); it = _obj.next()) {
            if(GC_is_heap_ptr(it)) {
                result.push_back(clone it);
            }
            else {
                result.push_back(it);
            }
        }

        return result;
    }
}

struct map<T, T2>
{
    T* keys;
    bool* item_existance;
    T2* items;
    int size;
    int len;

    int it;
};



impl map <T, T2>
{
    map<T,T2>* initialize(map<T,T2>* self) {
        self.keys = new T[128];
        self.items = new T2[128];
        self.item_existance = new bool[128];

        for(int i=0; i<128; i++)
        {
            self.item_existance[i] = false;
        }

        self.size = 128;
        self.len = 0;

        self.it = 0;

        return self;
    }


    T2 at(map<T, T2>* self, T key, T2 default_value)
    {
        int hash = ((T)key).get_hash_key() % self.size;
        int it = hash;

        while(true) {
            if(self.item_existance[it])
            {
                if(self.keys[it].equals(key))
                {
                    return self.items[it];
                }

                it++;

                if(it >= self.size) {
                    it = 0;
                }
                else if(it == hash) {
                    return default_value;
                }
            }
            else {
                return default_value;
            }
        }

        return default_value;
    }

    void rehash(map<T,T2>* self) {
        int size = self.size * 3;
        T* keys = new T[size];
        T2* items = new T2[size];
        bool* item_existance = new bool[size];

        int len = 0;

        for(auto it = self.begin(); !self.end(); it = self.next()) {
            T2 default_value;
            T2 it2 = self.at(it, default_value);
            int hash = it.get_hash_key() % size;
            int n = hash;

            while(true) {
                if(item_existance[n])
                {
                    n++;

                    if(n >= size) {
                        n = 0;
                    }
                    else if(n == hash) {
                        fprintf(stderr, "unexpected error in map.rehash(1)\n");
                        exit(2);
                    }
                }
                else {
                    item_existance[n] = true;
                    keys[n] = it;
                    T2 default_value;
                    items[n] = self.at(it, default_value);

                    len++;
                    break;
                }
            }
        }

        self.keys = keys;
        self.items = items;
        self.item_existance = item_existance;

        self.size = size;
        self.len = len;
    }

    void insert(map<T,T2>* self, T key, T2 item)
    {
        if(self.len*2 >= self.size) {
            self.rehash();
        }

        int hash = key.get_hash_key() % self.size;
        int it = hash;

        while(true) {
            if(self.item_existance[it])
            {
                if(self.keys[it].equals(key))
                {
                    self.keys[it] = key;
                    self.items[it] = item;

                    break;
                }

                it++;

                if(it >= self.size) {
                    it = 0;
                }
                else if(it == hash) {
                    fprintf(stderr, "unexpected error in map.insert\n");
                    exit(2);
                }
            }
            else {
                self.item_existance[it] = true;
                self.keys[it] = key;
                self.items[it] = item;

                self.len++;

                break;
            }
        }
    }

    map<T, T2>* clone(map<T, T2>* self)
    {
        auto result = new map<T,T2>.initialize();

        for(auto it = self.begin(); !self.end(); it = self.next()) {
            T2 default_value;
            auto it2 = self.at(it, default_value);

            if(GC_is_heap_ptr(it)) {
                if(GC_is_heap_ptr(it2)) {
                    result.insert(clone it, clone it2);
                }
                else {
                    result.insert(clone it, it2);
                }
            }
            else {
                if(GC_is_heap_ptr(it2)) {
                    result.insert(it, clone it2);
                }
                else {
                    result.insert(it, it2);
                }
            }
        }

        return result;
    }

    bool find(map<T, T2>* self, T key) {
        int hash = ((T)key).get_hash_key() % self.size;
        int it = hash;

        while(true) {
            if(self.item_existance[it])
            {
                if(self.keys[it].equals(key))
                {
                    return true;
                }

                it++;

                if(it >= self.size) {
                    it = 0;
                }
                else if(it == hash) {
                    return false;
                }
            }
            else {
                return false;
            }
        }

        return false;
    }

    bool equals(map<T, T2>* left, map<T, T2>* right)
    {
        if(left.len != right.len) {
            return false;
        }

        bool result = true;
        for(auto _obj = (left), auto it = _obj.begin(); !_obj.end(); it = _obj.next()) {
            T2 default_value;
            T2 it2 = left.at(it, default_value);

            if(right.find(it)) {
                T2 default_value;
                T2 item = right.at(it, default_value);
                if(!it2.equals(item)) {
                    result = false;
                }
            }
            else {
                result = false;
            }
        }

        return result;
    }

    int length(map<T, T2>* self) {
        return self.len;
    }

    T begin(map<T, T2>* self) {
        self.it = 0;
        while(self.it < self.size) {
            if(self.item_existance[self.it]) {
                return self.keys[self.it++];
            }
            self.it++;
        }

        return null;
    }

    T next(map<T, T2>* self) {
        while(self.it < self.size) {
            if(self.item_existance[self.it]) {
                return self.keys[self.it++];
            }
            self.it++;
        }

        return null;
    }

    bool end(map<T, T2>* self) {
        int count = 0;
        for(int i=self.it-1; i<self.size; i++) {
            if(self.item_existance[i]) {
                count ++;
            }
        }

        if(count == 0) {
            return true;
        }
        else {
            return false;
        }
    }
}

struct tuple1<T>
{
    T v1;
};

impl tuple1 <T>
{
    tuple1<T>* clone(tuple1<T>* self)
    {
        tuple1<T>* result = new tuple1<T>;

        if(GC_is_heap_ptr(self.v1)) {
            result.v1 = clone self.v1;
        }
        else {
            result.v1 = self.v1;
        }

        return result;
    }

    bool equals(tuple1<T>* left, tuple1<T>* right)
    {
        if(!left.v1.equals(right.v1)) {
            return false;
        }

        return true;
    }
}

struct tuple2<T, T2>
{
    T v1;
    T2 v2;
};

impl tuple2 <T, T2>
{
    tuple2<T,T2>* clone(tuple2<T, T2>* self)
    {
        tuple2<T,T2>* result = new tuple2<T, T2>;

        if(GC_is_heap_ptr(self.v1)) {
            result.v1 = clone self.v1;
        }
        else {
            result.v1 = self.v1;
        }
        if(GC_is_heap_ptr(self.v2)) {
            result.v2 = clone self.v2;
        }
        else {
            result.v2 = self.v2;
        }

        return result;
    }

    bool equals(tuple2<T, T2>* left, tuple2<T, T2>* right)
    {
        if(!left.v1.equals(right.v1)) {
            return false;
        }
        if(!left.v2.equals(right.v2)) {
            return false;
        }

        return true;
    }
}

struct tuple3<T, T2, T3>
{
    T v1;
    T2 v2;
    T3 v3;
};

impl tuple3 <T, T2, T3>
{
    tuple3<T,T2, T3>* clone(tuple3<T, T2, T3>* self)
    {
        tuple3<T,T2,T3>* result = new tuple3<T, T2, T3>;

        if(GC_is_heap_ptr(self.v1)) {
            result.v1 = clone self.v1;
        }
        else {
            result.v1 = self.v1;
        }
        if(GC_is_heap_ptr(self.v2)) {
            result.v2 = clone self.v2;
        }
        else {
            result.v2 = self.v2;
        }
        if(GC_is_heap_ptr(self.v3)) {
            result.v3 = clone self.v3;
        }
        else {
            result.v3 = self.v3;
        }

        return result;
    }

    bool equals(tuple3<T, T2, T3>* left, tuple3<T, T2, T3>* right)
    {
        if(!left.v1.equals(right.v1)) {
            return false;
        }
        if(!left.v2.equals(right.v2)) {
            return false;
        }
        if(!left.v3.equals(right.v3)) {
            return false;
        }

        return true;
    }
}

struct tuple4<T, T2, T3, T4>
{
    T v1;
    T2 v2;
    T3 v3;
    T4 v3;
};

impl tuple4 <T, T2, T3, T4>
{
    tuple4<T,T2, T3, T4>* clone(tuple4<T, T2, T3, T4>* self)
    {
        tuple4<T,T2,T3,T4>* result = new tuple4<T, T2, T3, T4>;

        if(GC_is_heap_ptr(self.v1)) {
            result.v1 = clone self.v1;
        }
        else {
            result.v1 = self.v1;
        }
        if(GC_is_heap_ptr(self.v2)) {
            result.v2 = clone self.v2;
        }
        else {
            result.v2 = self.v2;
        }
        if(GC_is_heap_ptr(self.v3)) {
            result.v3 = clone self.v3;
        }
        else {
            result.v3 = self.v3;
        }
        if(GC_is_heap_ptr(self.v4)) {
            result.v4 = clone self.v4;
        }
        else {
            result.v4 = self.v4;
        }

        return result;
    }

    bool equals(tuple4<T, T2, T3, T4>* left, tuple4<T, T2, T3, T4>* right)
    {
        if(!left.v1.equals(right.v1)) {
            return false;
        }
        if(!left.v2.equals(right.v2)) {
            return false;
        }
        if(!left.v3.equals(right.v3)) {
            return false;
        }
        if(!left.v4.equals(right.v4)) {
            return false;
        }

        return true;
    }
}

struct buffer {
    char* buf;
    int len;
    int size;
};

static buffer* buffer_initialize(buffer* self)
{
    self.size = 128;
    self.buf = GC_malloc(self.size);
    self.buf[0] = '\0'
    self.len = 0;

    return self;
}

static int buffer_length(buffer* self)
{
    return self.len;
}

static void buffer_append(buffer* self, char* mem, size_t size)
{
    if(self.len + size + 1 + 1 >= self.size) {
        int new_size = (self.size + size + 1) * 2;
        self.buf = GC_realloc(self.buf, new_size);
        self.size = new_size;
    }

    memcpy(self.buf + self.len, mem, size);
    self.len += size;

    self.buf[self.len] = '\0';
}

static void buffer_append_char(buffer* self, char c)
{
    if(self.len + 1 + 1 + 1 >= self.size) {
        int new_size = (self.size + 10 + 1) * 2;
        self.buf = GC_realloc(self.buf, new_size);
        self.size = new_size;
    }

    self.buf[self.len] = c;
    self.len++;

    self.buf[self.len] = '\0';
}

static void buffer_append_str(buffer* self, char* str)
{
    self.append(str, strlen(str));
}

static void buffer_append_nullterminated_str(buffer* self, char* str)
{
    self.append(str, strlen(str));
    self.append_char('\0');
}

static string buffer_to_string(buffer* self)
{
    return (string(self.buf));
}

static void buffer_append_int(buffer* self, int value)
{
    self.append((char*)&value, sizeof(int));
}

static void buffer_append_long(buffer* self, long value)
{
    self.append((char*)&value, sizeof(long));
}

static void buffer_append_short(buffer* self, short value)
{
    self.append((char*)&value, sizeof(short));
}

static void buffer_alignment(buffer* self)
{
    int len = self.len;
    len = (len + 3) & ~3;

    if(len >= self.size) {
        int new_size = (self.size + 1 + 1) * 2;
        self.buf = GC_realloc(self.buf, new_size);
        self.size = new_size;
    }

    for(int i=self.len; i<len; i++) {
        self.buf[i] = '\0';
    }

    self.len = len;
}

static int buffer_compare(buffer* left, buffer* right)
{
    return strcmp(left.buf, right.buf);
}

static buffer* char::to_buffer(char* self)
{
    auto result = new buffer.initialize();

    result.append_str(self);

    return result;
}


static int int::expect(int self, void* parent, void (*block)(void* parent))
{
    if(self < 0) {
        block(parent);
    }

    return self;
}

static bool bool::expect(bool self, void* parent, void (*block)(void* parent))
{
    if(!self) {
        block(parent);
    }

    return self;
}

static void int::times(int self, void* parent, void (*block)(void* parent))
{
    int i;
    for(i=0; i<self; i++) {
        block(parent);
    }
}

impl list<T>
{
    list<T>* filter(list<T>* self, void* parent, bool (*block)(void*, T))
    {
        auto result = new list<T>.initialize();

        list_item<T>?* it = self.head;
        while(it != null) {
            if(block(parent, it.item)) {
                if(GC_is_heap_ptr(it.item)) {
                    result.push_back(clone it.item);
                }
                else {
                    result.push_back(it.item);
                }
            }

            it = it.next;
        }

        return result;
    }
    list<T>* each(list<T>* self, void* parent, void (*block_)(void*, T,int,bool*)) {
        list_item<T>?* it = self.head;
        int i = 0;
        while(it != null) {
            bool end_flag = false;
            block_(parent, it.item, i, &end_flag);

            if(end_flag == true) {
                break;
            }
            it = it.next;
            i++;
        }

        return self;
    }
    template <R> list<R>* map(list<T>* self, void* parent, R (*block)(void*, T))
    {
        auto result = new list<R>.initialize();

        list_item<T>?* it = self.head;
        while(it != null) {
            result.push_back(block(parent, it.item));

            it = it.next;
        }

        return result;
    }
}

static bool xiswalpha(wchar_t c)
{
    bool result = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    return result;
}

static bool xiswblank(wchar_t c)
{
    return c == ' ' || c == '\t';
}

static bool xiswdigit(wchar_t c)
{
    return (c >= '0' && c <= '9');
}

static bool xiswalnum(wchar_t c)
{
    return xiswalpha(c) || xiswdigit(c);
}

static bool xisalpha(char c)
{
    bool result = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    return result;
}

static bool xisblank(char c)
{
    return c == ' ' || c == '\t';
}

static bool xisdigit(char c)
{
    return (c >= '0' && c <= '9');
}

static bool xisalnum(char c)
{
    return xisalpha(c) || xisdigit(c);
}

static string xbasename(char* path)
{
    char* p = path + strlen(path);

    while(p >= path) {
        if(*p == '/') {
            break;
        }
        else {
            p--;
        }
    }

    if(p < path) {
        return string(path);
    }
    else {
        return string(p+1);
    }
}

static string xextname(char* path)
{
    char* p = path + strlen(path);

    while(p >= path) {
        if(*p == '.') {
            break;
        }
        else {
            p--;
        }
    }

    if(p < path) {
        return string(path);
    }
    else {
        return string(p+1);
    }
}

static string xrealpath(char* path)
{
    char* result = realpath(path, null);

    string result2 = string(result);

    free(result);

    return result2;
}



static void come_fd_zero(fd_set* fds)
{
    do { unsigned int __i; fd_set *__arr = (fds); for (__i = 0; __i < sizeof (fd_set) / sizeof (__fd_mask); ++__i) ((__arr)->fds_bits)[__i] = 0; } while (0);
}

static void come_fd_set(int fd, fd_set* fds)
{
    ((void) (((fds)->fds_bits)[((fd) / (8 * (int) sizeof (__fd_mask)))] |= ((__fd_mask) (1UL << ((fd) % (8 * (int) sizeof (__fd_mask)))))));
}

static int come_fd_isset(int fd, fd_set* fds)
{
    return ((((fds)->fds_bits)[((fd) / (8 * (int) sizeof (__fd_mask)))] & ((__fd_mask) (1UL << ((fd) % (8 * (int) sizeof (__fd_mask)))))) != 0);
}
# 2 "src/common.h" 2


# 3 "src/common.h"
struct sNode;

struct sNode
{
    enum { kIntValueNode, kOpAdd, kOpSub, kStringValueNode, kPrint, kLoadVar, kStoreVar, kFun, kFunCall, kTrue, kFalse, kIf, kWhile, kContinue, kBreak, kOpEq, kOpNotEq } kind;

    char* fname;
    int sline;

    union {
        int intValue;

        struct {
            sNode* left
            sNode* right
            sNode* middle
        } opValue;

        string stringValue;

        struct {
            string name;
            sNode* right;
            bool in_global_context;
        } storeVarValue;

        struct {
            string name;
            bool in_global_context;
        } loadVarValue;

        struct {
            string name;
            buffer* codes;
            vector<string>* param_names;
        } funValue;

        struct {
            string name;
            vector<sNode*>* params;
        } funCallValue;

        struct {
            sNode* if_exp;
            buffer* if_codes;
            vector<sNode*>* elif_exps;
            vector<buffer*>* elif_blocks;
            buffer*? else_block;
        } ifValue;

        struct {
            sNode* while_exp;
            list<sNode*>* while_nodes;
            list<sNode*>* else_nodes;
        } whileValue;
    } value;
};

struct sParserInfo
{
    char* p;
    int sline;
    char* fname;

    int stack_num;

    bool in_global_context;
    int space_num;

    int loop_head;
    vector<int>* breaks;
};

struct ZVALUE
{
    enum { kIntValue, kBoolValue, kLongValue, kStringValue, kObjValue, kNullValue } kind;

    union {
        int intValue;
        bool boolValue;
        long longValue;
        char* stringValue;
        void* objValue;
    } value;
};

struct sVar
{
    string name;
    ZVALUE value;
};
# 113 "src/common.h"
void skip_spaces(sParserInfo* info);
void skip_spaces_until_eol(sParserInfo* info);
list<sNode*>* parse_block(sParserInfo* info);
buffer* compile_nodes(list<sNode*>* nodes, sParserInfo* info);
buffer* compile_block(sParserInfo* info);


void initialize_modules() version 1;
void finalize_modules() version 1;

bool vm(buffer* codes, map<string, ZVALUE>* params);


bool expression(sNode** node, sParserInfo* info) version 1;
bool compile(sNode* node, buffer* codes, sParserInfo* info) version 1;

sNode*? exp_node(sParserInfo* info) version 1;


sNode* op_add_node(sParserInfo* info);

bool expression(sNode** node, sParserInfo* info) version 2;
bool compile(sNode* node, buffer* codes, sParserInfo* info) version 2;


bool compile(sNode* node, buffer* codes, sParserInfo* info) version 3;

sNode*? exp_node(sParserInfo* info) version 3;


bool wordcmp(char* p, char* word2);

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 4;

sNode*? exp_node(sParserInfo* info) version 4;


sNode*? exp_node(sParserInfo* info) version 5;
sNode*? fun_node(string fun_name, sParserInfo* info) version 5;
sNode*? def_node(sParserInfo* info) version 5;

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 5;


void initialize_modules() version 6;

sNode*? fun_node(string fun_name, sParserInfo* info) version 6;
sNode*? def_node(sParserInfo* info) version 6;

bool function_call(char* fun_name, ZVALUE* stack, int stack_num);

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 6;


sNode*? exp_node(sParserInfo* info) version 7;

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 7;


sNode*? exp_node(sParserInfo* info) version 8;

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 8;


bool expression(sNode** node, sParserInfo* info) version 9;


sNode*? exp_node(sParserInfo* info) version 10;
bool compile(sNode* node, buffer* codes, sParserInfo* info) version 10;


bool expression(sNode** node, sParserInfo* info) version 11;
bool compile(sNode* node, buffer* codes, sParserInfo* info) version 11;
# 2 "src/07bool.c" 2

static sNode* create_true(sParserInfo* info)
{
    sNode* result = new sNode;

    result.kind = kTrue;

    result.fname = info->fname;
    result.sline = info->sline;

    return result;
}

static sNode* create_false(sParserInfo* info)
{
    sNode* result = new sNode;

    result.kind = kFalse;

    result.fname = info->fname;
    result.sline = info->sline;

    return result;
}

static bool word_cmp(char* p, char* word2)
{
    bool result = strstr(p, word2) == p;

    char c = p[strlen(word2)];

    if(result && (c == '\n' || c == ' ' || c == '\t' || c == '\0' || c == ':')) {
        return true;
    }

    return false;
}

sNode*? exp_node(sParserInfo* info) version 7
{
    sNode* result = null;

    if(word_cmp(info->p, "True")) {
        info->p += strlen("True");
        skip_spaces_until_eol(info);

        result = create_true(info);
    }
    else if(word_cmp(info->p, "False")) {
        info->p += strlen("False");
        skip_spaces_until_eol(info);

        result = create_false(info);
    }

    if(result == null) {
        result = inherit(info);
    }

    return result;
}

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 7
{
    inherit(node, codes, info);

    if(node.kind == kTrue) {
        codes.append_int(10);

        codes.append_int(1);

        info->stack_num++;
    }
    else if(node.kind == kFalse) {
        codes.append_int(10);

        codes.append_int(0);

        info->stack_num++;
    }

    return true;
}
