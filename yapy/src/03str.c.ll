; ModuleID = 'src/03str.c'
source_filename = "src/03str.c"

%_IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %_IO_marker*, %_IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, %_IO_codecvt*, %_IO_wide_data*, %_IO_FILE*, i8*, i64, i32, [20 x i8] }
%_IO_marker = type opaque
%_IO_codecvt = type opaque
%_IO_wide_data = type opaque
%_IO_cookie_io_functions_t = type { i64 (i8*, i8*, i64)*, i64 (i8*, i8*, i64)*, i32 (i8*, i64*, i32)*, i32 (i8*)* }
%_G_fpos_t = type { i64, %come_anon1 }
%come_anon1 = type { i32, %come_anon2 }
%come_anon2 = type { i32 }
%_G_fpos64_t = type { i64, %come_anon1 }
%obstack = type opaque
%__locale_struct = type { [13 x %__locale_data*], i16*, i32*, i32*, [13 x i8*] }
%__locale_data = type opaque
%come_anon8 = type { [16 x i64] }
%timeval = type { i64, i64 }
%timespec = type { i64, i64 }
%come_anon7 = type { [16 x i64] }
%random_data = type { i32*, i32*, i32*, i32, i32, i32, i32* }
%drand48_data = type { [3 x i16], [3 x i16], i16, i16, i64 }
%come_anon4 = type { i32, i32 }
%come_anon5 = type { i64, i64 }
%come_anon6 = type { i64, i64 }
%mallinfo = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i32 }
%GC_prof_stats_s = type { i64, i64, i64, i64, i64, i64, i64, i64, i64, i64 }
%GC_stack_base = type { i8* }
%come_anon32 = type { [16 x i64] }
%sched_param = type { i32 }
%timex = type { i32, i64, i64, i64, i64, i32, i64, i64, i64, %timeval, i64, i64, i64, i32, i64, i64, i64, i64, i64, i32, i256, i256, i256, i256, i256, i256, i256, i256, i256, i256, i256 }
%tm = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i64, i8* }
%sigevent = type opaque
%itimerspec = type { %timespec, %timespec }
%pthread_attr_t = type { [56 x i8] }
%come_anon55 = type { [1 x %come_anon56], [4 x i8*] }
%come_anon56 = type { [8 x i64], i32 }
%__jmp_buf_tag = type opaque
%come_anon23 = type { %__pthread_mutex_s }
%__pthread_mutex_s = type { i32, i32, i32, i32, i32, i16, i16, %__pthread_internal_list }
%__pthread_internal_list = type { %__pthread_internal_list*, %__pthread_internal_list* }
%come_anon21 = type { [4 x i8] }
%come_anon25 = type { %__pthread_rwlock_arch_t }
%__pthread_rwlock_arch_t = type { i32, i32, i32, i32, i32, i32, i32, i32, i8, [7 x i8], i64, i32 }
%come_anon26 = type { [8 x i8] }
%come_anon24 = type { %__pthread_cond_s }
%__pthread_cond_s = type { %come_anon15, %come_anon18, [2 x i32], [2 x i32], i32, i32, [2 x i32] }
%come_anon15 = type { i64 }
%come_anon18 = type { i64 }
%come_anon22 = type { [4 x i8] }
%come_anon27 = type { [32 x i8] }
%come_anon28 = type { [4 x i8] }
%timezone = type { i32, i32 }
%itimerval = type { %timeval, %timeval }
%stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %timespec, %timespec, %timespec, [3 x i64] }
%stat64 = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %timespec, %timespec, %timespec, [3 x i64] }
%statx = type { i32, i32, i64, i32, i32, i32, i16, [1 x i16], i64, i64, i64, i64, %statx_timestamp, %statx_timestamp, %statx_timestamp, %statx_timestamp, i32, i32, i32, i32, [14 x i64] }
%statx_timestamp = type { i64, i32, [1 x i32] }
%buffer = type { i8*, i32, i32 }
%sNode = type { i32, i8*, i32, %come_anon69 }
%come_anon69 = type { %come_anon70 }
%come_anon70 = type { %sNode*, %sNode*, %sNode* }
%sParserInfo = type { i8*, i32, i8* }

@stdin = external externally_initialized global %_IO_FILE*, align 4
@stdout = external externally_initialized global %_IO_FILE*, align 4
@stderr = external externally_initialized global %_IO_FILE*, align 4
@sys_nerr = external externally_initialized global i32
@sys_errlist = external externally_initialized global i8**, align 4
@_sys_nerr = external externally_initialized global i32
@_sys_errlist = external externally_initialized global i8**, align 4
@__morecore = external externally_initialized global i8* (i64)*, align 4
@__free_hook = external externally_initialized global void (i8*, i8*)*, align 4
@__malloc_hook = external externally_initialized global i8* (i64, i8*)*, align 4
@__realloc_hook = external externally_initialized global i8* (i8*, i64, i8*)*, align 4
@__memalign_hook = external externally_initialized global i8* (i64, i64, i8*)*, align 4
@__after_morecore_hook = external externally_initialized global void ()*, align 4
@GC_gc_no = external externally_initialized global i64
@GC_oom_fn = external externally_initialized global i8* (i64)*
@GC_on_heap_resize = external externally_initialized global void (i64)*
@GC_find_leak = external externally_initialized global i32
@GC_all_interior_pointers = external externally_initialized global i32
@GC_finalize_on_demand = external externally_initialized global i32
@GC_java_finalization = external externally_initialized global i32
@GC_finalizer_notifier = external externally_initialized global void ()*
@GC_dont_gc = external externally_initialized global i32
@GC_dont_expand = external externally_initialized global i32
@GC_use_entire_heap = external externally_initialized global i32
@GC_full_freq = external externally_initialized global i32
@GC_non_gc_bytes = external externally_initialized global i64
@GC_no_dls = external externally_initialized global i32
@GC_free_space_divisor = external externally_initialized global i64
@GC_max_retries = external externally_initialized global i64
@GC_stackbottom = external externally_initialized global i8*, align 4
@GC_dont_precollect = external externally_initialized global i32
@GC_time_limit = external externally_initialized global i64
@GC_same_obj_print_proc = external externally_initialized global void (i8*, i8*)*, align 4
@GC_is_valid_displacement_print_proc = external externally_initialized global void (i8*)*, align 4
@GC_is_visible_print_proc = external externally_initialized global void (i8*)*, align 4
@__tzname = external externally_initialized global [2 x i8*], align 4
@__daylight = external externally_initialized global i32
@__timezone = external externally_initialized global i64
@tzname = external externally_initialized global [2 x i8*], align 4
@daylight = external externally_initialized global i32
@timezone = external externally_initialized global i64
@getdate_err = external externally_initialized global i32
@__environ = external externally_initialized global i8**, align 4
@environ = external externally_initialized global i8**, align 4
@optarg = external externally_initialized global i8*, align 4
@optind = external externally_initialized global i32
@opterr = external externally_initialized global i32
@optopt = external externally_initialized global i32
@"can't get heap memory.\0A" = private unnamed_addr constant [24 x i8] c"can't get heap memory.\0A\00", align 1
@0 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@1 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@"%s %d: the source end" = private unnamed_addr constant [22 x i8] c"%s %d: the source end\00", align 1
@"%s %d: the source end.1" = private unnamed_addr constant [22 x i8] c"%s %d: the source end\00", align 1
@"%s %d: the source end.2" = private unnamed_addr constant [22 x i8] c"%s %d: the source end\00", align 1
@"%s %d: the source end.3" = private unnamed_addr constant [22 x i8] c"%s %d: the source end\00", align 1

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #0

declare void @__builtin_va_start(i8*)

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #0

declare void @__builtin_va_end(i8*)

; Function Attrs: nounwind willreturn
declare void @llvm.assume(i1) #1

; Function Attrs: nounwind
declare i64 @llvm.readcyclecounter() #0

; Function Attrs: nounwind readnone speculatable willreturn
declare i8 @llvm.bitreverse.i8(i8) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i16 @llvm.bitreverse.i16(i16) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i32 @llvm.bitreverse.i32(i32) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i64 @llvm.bitreverse.i64(i64) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i8 @llvm.fshl.i8(i8, i8) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i16 @llvm.fshl.i16(i16, i16) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i32 @llvm.fshl.i32(i32, i32) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i64 @llvm.fshl.i64(i64, i64) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i8 @llvm.fshr.i8(i8, i8) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i16 @llvm.fshr.i16(i16, i16) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i32 @llvm.fshr.i32(i32, i32) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i64 @llvm.fshr.i64(i64, i64) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare double @llvm.canonicalize.f64(double) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare float @llvm.canonicalize.f32(float) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare fp128 @llvm.canonicalize.f80(fp128) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare i64 @llvm.objectsize.i64.p0i8(i8*, i1 immarg, i1 immarg, i1 immarg) #2

declare i32 @remove(i8*)

declare i32 @rename(i8*, i8*)

declare i32 @renameat(i32, i8*, i32, i8*)

declare i32 @renameat2(i32, i8*, i32, i8*, i32)

declare %_IO_FILE* @tmpfile()

declare %_IO_FILE* @tmpfile64()

declare i8* @tmpnam(i8*)

declare i8* @tmpnam_r(i8*)

declare i8* @tempnam(i8*, i8*)

declare i32 @fclose(%_IO_FILE*)

declare i32 @fflush(%_IO_FILE*)

declare i32 @fflush_unlocked(%_IO_FILE*)

declare i32 @fcloseall()

declare %_IO_FILE* @fopen(i8*, i8*)

declare %_IO_FILE* @freopen(i8*, i8*, %_IO_FILE*)

declare %_IO_FILE* @fopen64(i8*, i8*)

declare %_IO_FILE* @freopen64(i8*, i8*, %_IO_FILE*)

declare %_IO_FILE* @fdopen(i32, i8*)

declare %_IO_FILE* @fopencookie(i8*, i8*, %_IO_cookie_io_functions_t)

declare %_IO_FILE* @fmemopen(i8*, i64, i8*)

declare %_IO_FILE* @open_memstream(i8**, i64*)

declare void @setbuf(%_IO_FILE*, i8*)

declare i32 @setvbuf(%_IO_FILE*, i8*, i32, i64)

declare void @setbuffer(%_IO_FILE*, i8*, i64)

declare void @setlinebuf(%_IO_FILE*)

declare i32 @fprintf(%_IO_FILE*, i8*, ...)

declare i32 @printf(i8*, ...)

declare i32 @sprintf(i8*, i8*, ...)

declare i32 @vfprintf(%_IO_FILE*, i8*, { i32, i32, i8*, i8* }*)

declare i32 @vprintf(i8*, { i32, i32, i8*, i8* }*)

declare i32 @vsprintf(i8*, i8*, { i32, i32, i8*, i8* }*)

declare i32 @snprintf(i8*, i64, i8*, ...)

declare i32 @vsnprintf(i8*, i64, i8*, { i32, i32, i8*, i8* }*)

declare i32 @vasprintf(i8**, i8*, { i32, i32, i8*, i8* }*)

declare i32 @__asprintf(i8**, i8*, ...)

declare i32 @asprintf(i8**, i8*, ...)

declare i32 @vdprintf(i32, i8*, { i32, i32, i8*, i8* }*)

declare i32 @dprintf(i32, i8*, ...)

declare i32 @fscanf(%_IO_FILE*, i8*, ...)

declare i32 @scanf(i8*, ...)

declare i32 @sscanf(i8*, i8*, ...)

declare i32 @vfscanf(%_IO_FILE*, i8*, { i32, i32, i8*, i8* }*)

declare i32 @vscanf(i8*, { i32, i32, i8*, i8* }*)

declare i32 @vsscanf(i8*, i8*, { i32, i32, i8*, i8* }*)

declare i32 @fgetc(%_IO_FILE*)

declare i32 @getc(%_IO_FILE*)

declare i32 @getchar()

declare i32 @getc_unlocked(%_IO_FILE*)

declare i32 @getchar_unlocked()

declare i32 @fgetc_unlocked(%_IO_FILE*)

declare i32 @fputc(i32, %_IO_FILE*)

declare i32 @putc(i32, %_IO_FILE*)

declare i32 @putchar(i32)

declare i32 @fputc_unlocked(i32, %_IO_FILE*)

declare i32 @putc_unlocked(i32, %_IO_FILE*)

declare i32 @putchar_unlocked(i32)

declare i32 @getw(%_IO_FILE*)

declare i32 @putw(i32, %_IO_FILE*)

declare i8* @fgets(i8*, i32, %_IO_FILE*)

declare i8* @fgets_unlocked(i8*, i32, %_IO_FILE*)

declare i64 @__getdelim(i8**, i64*, i32, %_IO_FILE*)

declare i64 @getdelim(i8**, i64*, i32, %_IO_FILE*)

declare i64 @getline(i8**, i64*, %_IO_FILE*)

declare i32 @fputs(i8*, %_IO_FILE*)

declare i32 @puts(i8*)

declare i32 @ungetc(i32, %_IO_FILE*)

declare i64 @fread(i8*, i64, i64, %_IO_FILE*)

declare i64 @fwrite(i8*, i64, i64, %_IO_FILE*)

declare i32 @fputs_unlocked(i8*, %_IO_FILE*)

declare i64 @fread_unlocked(i8*, i64, i64, %_IO_FILE*)

declare i64 @fwrite_unlocked(i8*, i64, i64, %_IO_FILE*)

declare i32 @fseek(%_IO_FILE*, i64, i32)

declare i64 @ftell(%_IO_FILE*)

declare void @rewind(%_IO_FILE*)

declare i32 @fseeko(%_IO_FILE*, i64, i32)

declare i64 @ftello(%_IO_FILE*)

declare i32 @fgetpos(%_IO_FILE*, %_G_fpos_t*)

declare i32 @fsetpos(%_IO_FILE*, %_G_fpos_t*)

declare i32 @fseeko64(%_IO_FILE*, i64, i32)

declare i64 @ftello64(%_IO_FILE*)

declare i32 @fgetpos64(%_IO_FILE*, %_G_fpos64_t*)

declare i32 @fsetpos64(%_IO_FILE*, %_G_fpos64_t*)

declare void @clearerr(%_IO_FILE*)

declare i32 @feof(%_IO_FILE*)

declare i32 @ferror(%_IO_FILE*)

declare void @clearerr_unlocked(%_IO_FILE*)

declare i32 @feof_unlocked(%_IO_FILE*)

declare i32 @ferror_unlocked(%_IO_FILE*)

declare void @perror(i8*)

declare i32 @fileno(%_IO_FILE*)

declare i32 @fileno_unlocked(%_IO_FILE*)

declare %_IO_FILE* @popen(i8*, i8*)

declare i32 @pclose(%_IO_FILE*)

declare i8* @ctermid(i8*)

declare i8* @cuserid(i8*)

declare i32 @obstack_printf(%obstack*, i8*, ...)

declare i32 @obstack_vprintf(%obstack*, i8*, { i32, i32, i8*, i8* }*)

declare void @flockfile(%_IO_FILE*)

declare i32 @ftrylockfile(%_IO_FILE*)

declare void @funlockfile(%_IO_FILE*)

declare i32 @__uflow(%_IO_FILE*)

declare i32 @__overflow(%_IO_FILE*, i32)

declare i64 @__ctype_get_mb_cur_max()

declare double @atof(i8*)

declare i32 @atoi(i8*)

declare i64 @atol(i8*)

declare i64 @atoll(i8*)

declare double @strtod(i8*, i8**)

declare float @strtof(i8*, i8**)

declare fp128 @strtold(i8*, i8**)

declare float @strtof32(i8*, i8**)

declare double @strtof64(i8*, i8**)

declare double @strtof32x(i8*, i8**)

declare fp128 @strtof64x(i8*, i8**)

declare i64 @strtol(i8*, i8**, i32)

declare i64 @strtoul(i8*, i8**, i32)

declare i64 @strtoq(i8*, i8**, i32)

declare i64 @strtouq(i8*, i8**, i32)

declare i64 @strtoll(i8*, i8**, i32)

declare i64 @strtoull(i8*, i8**, i32)

declare i32 @strfromd(i8*, i64, i8*, double)

declare i32 @strfromf(i8*, i64, i8*, float)

declare i32 @strfroml(i8*, i64, i8*, fp128)

declare i32 @strfromf32(i8*, i64, i8*, float)

declare i32 @strfromf64(i8*, i64, i8*, double)

declare i32 @strfromf32x(i8*, i64, i8*, double)

declare i32 @strfromf64x(i8*, i64, i8*, fp128)

declare i64 @strtol_l(i8*, i8**, i32, %__locale_struct*)

declare i64 @strtoul_l(i8*, i8**, i32, %__locale_struct*)

declare i64 @strtoll_l(i8*, i8**, i32, %__locale_struct*)

declare i64 @strtoull_l(i8*, i8**, i32, %__locale_struct*)

declare double @strtod_l(i8*, i8**, %__locale_struct*)

declare float @strtof_l(i8*, i8**, %__locale_struct*)

declare fp128 @strtold_l(i8*, i8**, %__locale_struct*)

declare float @strtof32_l(i8*, i8**, %__locale_struct*)

declare double @strtof64_l(i8*, i8**, %__locale_struct*)

declare double @strtof32x_l(i8*, i8**, %__locale_struct*)

declare fp128 @strtof64x_l(i8*, i8**, %__locale_struct*)

declare i8* @l64a(i64)

declare i64 @a64l(i8*)

declare i32 @select(i32, %come_anon8*, %come_anon8*, %come_anon8*, %timeval*)

declare i32 @pselect(i32, %come_anon8*, %come_anon8*, %come_anon8*, %timespec*, %come_anon7*)

declare i64 @random()

declare void @srandom(i32)

declare i8* @initstate(i32, i8*, i64)

declare i8* @setstate(i8*)

declare i32 @random_r(%random_data*, i32*)

declare i32 @srandom_r(i32, %random_data*)

declare i32 @initstate_r(i32, i8*, i64, %random_data*)

declare i32 @setstate_r(i8*, %random_data*)

declare i32 @rand()

declare void @srand(i32)

declare i32 @rand_r(i32*)

declare double @drand48()

declare double @erand48(i16*)

declare i64 @lrand48()

declare i64 @nrand48(i16*)

declare i64 @mrand48()

declare i64 @jrand48(i16*)

declare void @srand48(i64)

declare i16* @seed48(i16*)

declare void @lcong48(i16*)

declare i32 @drand48_r(%drand48_data*, double*)

declare i32 @erand48_r(i16*, %drand48_data*, double*)

declare i32 @lrand48_r(%drand48_data*, i64*)

declare i32 @nrand48_r(i16*, %drand48_data*, i64*)

declare i32 @mrand48_r(%drand48_data*, i64*)

declare i32 @jrand48_r(i16*, %drand48_data*, i64*)

declare i32 @srand48_r(i64, %drand48_data*)

declare i32 @seed48_r(i16*, %drand48_data*)

declare i32 @lcong48_r(i16*, %drand48_data*)

declare i8* @malloc(i64)

declare i8* @calloc(i64, i64)

declare i8* @realloc(i8*, i64)

declare i8* @reallocarray(i8*, i64, i64)

declare void @free(i8*)

declare i8* @alloca(i64)

declare i8* @valloc(i64)

declare i32 @posix_memalign(i8**, i64, i64)

declare i8* @aligned_alloc(i64, i64)

declare void @abort()

declare i32 @atexit(void ()*)

declare i32 @at_quick_exit(void ()*)

declare i32 @on_exit(void (i32, i8*)*, i8*)

declare void @exit(i32)

declare void @quick_exit(i32)

declare void @_Exit(i32)

declare i8* @getenv(i8*)

declare i8* @secure_getenv(i8*)

declare i32 @putenv(i8*)

declare i32 @setenv(i8*, i8*, i32)

declare i32 @unsetenv(i8*)

declare i32 @clearenv()

declare i8* @mktemp(i8*)

declare i32 @mkstemp(i8*)

declare i32 @mkstemp64(i8*)

declare i32 @mkstemps(i8*, i32)

declare i32 @mkstemps64(i8*, i32)

declare i8* @mkdtemp(i8*)

declare i32 @mkostemp(i8*, i32)

declare i32 @mkostemp64(i8*, i32)

declare i32 @mkostemps(i8*, i32, i32)

declare i32 @mkostemps64(i8*, i32, i32)

declare i32 @system(i8*)

declare i8* @canonicalize_file_name(i8*)

declare i8* @realpath(i8*, i8*)

declare i8* @bsearch(i8*, i8*, i64, i64, i32 (i8*, i8*)*)

declare void @qsort(i8*, i64, i64, i32 (i8*, i8*)*)

declare void @qsort_r(i8*, i64, i64, i32 (i8*, i8*, i8*)*, i8*)

declare i32 @abs(i32)

declare i64 @labs(i64)

declare i64 @llabs(i64)

declare %come_anon4 @div(i32, i32)

declare %come_anon5 @ldiv(i64, i64)

declare %come_anon6 @lldiv(i64, i64)

declare i8* @ecvt(double, i32, i32*, i32*)

declare i8* @fcvt(double, i32, i32*, i32*)

declare i8* @gcvt(double, i32, i8*)

declare i8* @qecvt(fp128, i32, i32*, i32*)

declare i8* @qfcvt(fp128, i32, i32*, i32*)

declare i8* @qgcvt(fp128, i32, i8*)

declare i32 @ecvt_r(double, i32, i32*, i32*, i8*, i64)

declare i32 @fcvt_r(double, i32, i32*, i32*, i8*, i64)

declare i32 @qecvt_r(fp128, i32, i32*, i32*, i8*, i64)

declare i32 @qfcvt_r(fp128, i32, i32*, i32*, i8*, i64)

declare i32 @mblen(i8*, i64)

declare i32 @mbtowc(i32*, i8*, i64)

declare i32 @wctomb(i8*, i32)

declare i64 @mbstowcs(i32*, i8*, i64)

declare i64 @wcstombs(i8*, i32*, i64)

declare i32 @rpmatch(i8*)

declare i32 @getsubopt(i8**, i8**, i8**)

declare i32 @posix_openpt(i32)

declare i32 @grantpt(i32)

declare i32 @unlockpt(i32)

declare i8* @ptsname(i32)

declare i32 @ptsname_r(i32, i8*, i64)

declare i32 @getpt()

declare i32 @getloadavg(double*, i32)

declare i8* @memcpy(i8*, i8*, i64)

declare i8* @memmove(i8*, i8*, i64)

declare i8* @memccpy(i8*, i8*, i32, i64)

declare i8* @memset(i8*, i32, i64)

declare i32 @memcmp(i8*, i8*, i64)

declare i8* @memchr(i8*, i32, i64)

declare i8* @rawmemchr(i8*, i32)

declare i8* @memrchr(i8*, i32, i64)

declare i8* @strcpy(i8*, i8*)

declare i8* @strncpy(i8*, i8*, i64)

declare i8* @strcat(i8*, i8*)

declare i8* @strncat(i8*, i8*, i64)

declare i32 @strcmp(i8*, i8*)

declare i32 @strncmp(i8*, i8*, i64)

declare i32 @strcoll(i8*, i8*)

declare i64 @strxfrm(i8*, i8*, i64)

declare i32 @strcoll_l(i8*, i8*, %__locale_struct*)

declare i64 @strxfrm_l(i8*, i8*, i64, %__locale_struct*)

declare i8* @strdup(i8*)

declare i8* @strndup(i8*, i64)

declare i8* @strchr(i8*, i32)

declare i8* @strrchr(i8*, i32)

declare i8* @strchrnul(i8*, i32)

declare i64 @strcspn(i8*, i8*)

declare i64 @strspn(i8*, i8*)

declare i8* @strpbrk(i8*, i8*)

declare i8* @strstr(i8*, i8*)

declare i8* @strtok(i8*, i8*)

declare i8* @__strtok_r(i8*, i8*, i8**)

declare i8* @strtok_r(i8*, i8*, i8**)

declare i8* @strcasestr(i8*, i8*)

declare i8* @memmem(i8*, i64, i8*, i64)

declare i8* @__mempcpy(i8*, i8*, i64)

declare i8* @mempcpy(i8*, i8*, i64)

declare i64 @strlen(i8*)

declare i64 @strnlen(i8*, i64)

declare i8* @strerror(i32)

declare i8* @strerror_r(i32, i8*, i64)

declare i8* @strerror_l(i32, %__locale_struct*)

declare i32 @bcmp(i8*, i8*, i64)

declare void @bcopy(i8*, i8*, i64)

declare void @bzero(i8*, i64)

declare i8* @index(i8*, i32)

declare i8* @rindex(i8*, i32)

declare i32 @ffs(i32)

declare i32 @ffsl(i64)

declare i32 @ffsll(i64)

declare i32 @strcasecmp(i8*, i8*)

declare i32 @strncasecmp(i8*, i8*, i64)

declare i32 @strcasecmp_l(i8*, i8*, %__locale_struct*)

declare i32 @strncasecmp_l(i8*, i8*, i64, %__locale_struct*)

declare void @explicit_bzero(i8*, i64)

declare i8* @strsep(i8**, i8*)

declare i8* @strsignal(i32)

declare i8* @__stpcpy(i8*, i8*)

declare i8* @stpcpy(i8*, i8*)

declare i8* @__stpncpy(i8*, i8*, i64)

declare i8* @stpncpy(i8*, i8*, i64)

declare i32 @strverscmp(i8*, i8*)

declare i8* @strfry(i8*)

declare i8* @memfrob(i8*, i64)

declare i8* @basename(i8*)

declare i8* @memalign(i64, i64)

declare i8* @pvalloc(i64)

declare i8* @__default_morecore(i64)

declare %mallinfo @mallinfo()

declare i32 @mallopt(i32, i32)

declare i32 @malloc_trim(i64)

declare i64 @malloc_usable_size(i8*)

declare void @malloc_stats()

declare i32 @malloc_info(i32, %_IO_FILE*)

declare void @__malloc_check_init()

declare i32 @GC_get_version()

declare i64 @GC_get_gc_no()

declare void @GC_set_oom_fn(i8* (i64)*)

declare i8* (i64)* @GC_get_oom_fn()

declare void @GC_set_on_heap_resize(void (i64)*)

declare void (i64)* @GC_get_on_heap_resize()

declare void @GC_set_on_collection_event(void (i32)*)

declare void (i32)* @GC_get_on_collection_event()

declare void @GC_set_find_leak(i32)

declare i32 @GC_get_find_leak()

declare void @GC_set_all_interior_pointers(i32)

declare i32 @GC_get_all_interior_pointers()

declare void @GC_set_finalize_on_demand(i32)

declare i32 @GC_get_finalize_on_demand()

declare void @GC_set_java_finalization(i32)

declare i32 @GC_get_java_finalization()

declare void @GC_set_finalizer_notifier(void ()*)

declare void ()* @GC_get_finalizer_notifier()

declare void @GC_set_dont_expand(i32)

declare i32 @GC_get_dont_expand()

declare void @GC_set_full_freq(i32)

declare i32 @GC_get_full_freq()

declare void @GC_set_non_gc_bytes(i64)

declare i64 @GC_get_non_gc_bytes()

declare void @GC_set_no_dls(i32)

declare i32 @GC_get_no_dls()

declare void @GC_set_free_space_divisor(i64)

declare i64 @GC_get_free_space_divisor()

declare void @GC_set_max_retries(i64)

declare i64 @GC_get_max_retries()

declare void @GC_set_dont_precollect(i32)

declare i32 @GC_get_dont_precollect()

declare void @GC_set_time_limit(i64)

declare i64 @GC_get_time_limit()

declare void @GC_set_pages_executable(i32)

declare i32 @GC_get_pages_executable()

declare void @GC_set_handle_fork(i32)

declare void @GC_atfork_prepare()

declare void @GC_atfork_parent()

declare void @GC_atfork_child()

declare void @GC_init()

declare i32 @GC_is_init_called()

declare i8* @GC_malloc(i64)

declare i8* @GC_malloc_atomic(i64)

declare i8* @GC_strdup(i8*)

declare i8* @GC_strndup(i8*, i64)

declare i8* @GC_malloc_uncollectable(i64)

declare i8* @GC_malloc_stubborn(i64)

declare i8* @GC_memalign(i64, i64)

declare i32 @GC_posix_memalign(i8**, i64, i64)

declare void @GC_free(i8*)

declare void @GC_change_stubborn(i8*)

declare void @GC_end_stubborn_change(i8*)

declare i8* @GC_base(i8*)

declare i32 @GC_is_heap_ptr(i8*)

declare i64 @GC_size(i8*)

declare i8* @GC_realloc(i8*, i64)

declare i32 @GC_expand_hp(i64)

declare void @GC_set_max_heap_size(i64)

declare void @GC_exclude_static_roots(i8*, i8*)

declare void @GC_clear_roots()

declare void @GC_add_roots(i8*, i8*)

declare void @GC_remove_roots(i8*, i8*)

declare void @GC_register_displacement(i64)

declare void @GC_debug_register_displacement(i64)

declare void @GC_gcollect()

declare void @GC_gcollect_and_unmap()

declare i32 @GC_try_to_collect(i32 ()*)

declare void @GC_set_stop_func(i32 ()*)

declare i32 ()* @GC_get_stop_func()

declare i64 @GC_get_heap_size()

declare i64 @GC_get_free_bytes()

declare i64 @GC_get_unmapped_bytes()

declare i64 @GC_get_bytes_since_gc()

declare i64 @GC_get_total_bytes()

declare void @GC_get_heap_usage_safe(i64*, i64*, i64*, i64*, i64*)

declare i64 @GC_get_prof_stats(%GC_prof_stats_s*, i64)

declare i64 @GC_get_memory_use()

declare void @GC_disable()

declare i32 @GC_is_disabled()

declare void @GC_enable()

declare void @GC_enable_incremental()

declare i32 @GC_incremental_protection_needs()

declare i32 @GC_collect_a_little()

declare i8* @GC_malloc_ignore_off_page(i64)

declare i8* @GC_malloc_atomic_ignore_off_page(i64)

declare i8* @GC_malloc_atomic_uncollectable(i64)

declare i8* @GC_debug_malloc_atomic_uncollectable(i64, i8*, i32)

declare i8* @GC_debug_malloc(i64, i8*, i32)

declare i8* @GC_debug_malloc_atomic(i64, i8*, i32)

declare i8* @GC_debug_strdup(i8*, i8*, i32)

declare i8* @GC_debug_strndup(i8*, i64, i8*, i32)

declare i8* @GC_debug_malloc_uncollectable(i64, i8*, i32)

declare i8* @GC_debug_malloc_stubborn(i64, i8*, i32)

declare i8* @GC_debug_malloc_ignore_off_page(i64, i8*, i32)

declare i8* @GC_debug_malloc_atomic_ignore_off_page(i64, i8*, i32)

declare void @GC_debug_free(i8*)

declare i8* @GC_debug_realloc(i8*, i64, i8*, i32)

declare void @GC_debug_change_stubborn(i8*)

declare void @GC_debug_end_stubborn_change(i8*)

declare i8* @GC_debug_malloc_replacement(i64)

declare i8* @GC_debug_realloc_replacement(i8*, i64)

declare void @GC_register_finalizer(i8*, void (i8*, i8*)*, i8*, void (i8*, i8*)*, i8**)

declare void @GC_debug_register_finalizer(i8*, void (i8*, i8*)*, i8*, void (i8*, i8*)*, i8**)

declare void @GC_register_finalizer_ignore_self(i8*, void (i8*, i8*)*, i8*, void (i8*, i8*)*, i8**)

declare void @GC_debug_register_finalizer_ignore_self(i8*, void (i8*, i8*)*, i8*, void (i8*, i8*)*, i8**)

declare void @GC_register_finalizer_no_order(i8*, void (i8*, i8*)*, i8*, void (i8*, i8*)*, i8**)

declare void @GC_debug_register_finalizer_no_order(i8*, void (i8*, i8*)*, i8*, void (i8*, i8*)*, i8**)

declare void @GC_register_finalizer_unreachable(i8*, void (i8*, i8*)*, i8*, void (i8*, i8*)*, i8**)

declare void @GC_debug_register_finalizer_unreachable(i8*, void (i8*, i8*)*, i8*, void (i8*, i8*)*, i8**)

declare i32 @GC_register_disappearing_link(i8**)

declare i32 @GC_general_register_disappearing_link(i8**, i8*)

declare i32 @GC_move_disappearing_link(i8**, i8**)

declare i32 @GC_unregister_disappearing_link(i8**)

declare i32 @GC_register_long_link(i8**, i8*)

declare i32 @GC_move_long_link(i8**, i8**)

declare i32 @GC_unregister_long_link(i8**)

declare void @GC_set_toggleref_func(i32 (i8*)*)

declare i32 (i8*)* @GC_get_toggleref_func()

declare i32 @GC_toggleref_add(i8*, i32)

declare void @GC_set_await_finalize_proc(void (i8*)*)

declare void (i8*)* @GC_get_await_finalize_proc()

declare i32 @GC_should_invoke_finalizers()

declare i32 @GC_invoke_finalizers()

declare void @GC_noop1(i64)

declare void @GC_set_warn_proc(void (i8*, i64)*)

declare void (i8*, i64)* @GC_get_warn_proc()

declare void @GC_ignore_warn_proc(i8*, i64)

declare void @GC_set_log_fd(i32)

declare void @GC_set_abort_func(void (i8*)*)

declare void (i8*)* @GC_get_abort_func()

declare i8* @GC_call_with_alloc_lock(i8* (i8*)*, i8*)

declare i8* @GC_call_with_stack_base(i8* (%GC_stack_base*, i8*)*, i8*)

declare i8* @GC_do_blocking(i8* (i8*)*, i8*)

declare i8* @GC_call_with_gc_active(i8* (i8*)*, i8*)

declare i32 @GC_get_stack_base(%GC_stack_base*)

declare i8* @GC_same_obj(i8*, i8*)

declare i8* @GC_pre_incr(i8**, i64)

declare i8* @GC_post_incr(i8**, i64)

declare i8* @GC_is_visible(i8*)

declare i8* @GC_is_valid_displacement(i8*)

declare void @GC_dump()

declare void @GC_dump_regions()

declare void @GC_dump_finalization()

declare i8* @GC_malloc_many(i64)

declare void @GC_register_has_static_roots_callback(i32 (i8*, i8*, i64)*)

declare void @GC_set_force_unmap_on_gcollect(i32)

declare i32 @GC_get_force_unmap_on_gcollect()

declare void @GC_win32_free_heap()

declare i32 @clone(i32 (i8*)*, i8*, i32, i8*, ...)

declare i32 @unshare(i32)

declare i32 @sched_getcpu()

declare i32 @setns(i32, i32)

declare i32 @__sched_cpucount(i64, %come_anon32*)

declare %come_anon32* @__sched_cpualloc(i64)

declare void @__sched_cpufree(%come_anon32*)

declare i32 @sched_setparam(i32, %sched_param*)

declare i32 @sched_getparam(i32, %sched_param*)

declare i32 @sched_setscheduler(i32, i32, %sched_param*)

declare i32 @sched_getscheduler(i32)

declare i32 @sched_yield()

declare i32 @sched_get_priority_max(i32)

declare i32 @sched_get_priority_min(i32)

declare i32 @sched_rr_get_interval(i32, %timespec*)

declare i32 @sched_setaffinity(i32, i64, %come_anon32*)

declare i32 @sched_getaffinity(i32, i64, %come_anon32*)

declare i32 @clock_adjtime(i32, %timex*)

declare i64 @clock()

declare i64 @time(i64*)

declare double @difftime(i64, i64)

declare i64 @mktime(%tm*)

declare i64 @strftime(i8*, i64, i8*, %tm*)

declare i8* @strptime(i8*, i8*, %tm*)

declare i64 @strftime_l(i8*, i64, i8*, %tm*, %__locale_struct*)

declare i8* @strptime_l(i8*, i8*, %tm*, %__locale_struct*)

declare %tm* @gmtime(i64*)

declare %tm* @localtime(i64*)

declare %tm* @gmtime_r(i64*, %tm*)

declare %tm* @localtime_r(i64*, %tm*)

declare i8* @asctime(%tm*)

declare i8* @ctime(i64*)

declare i8* @asctime_r(%tm*, i8*)

declare i8* @ctime_r(i64*, i8*)

declare void @tzset()

declare i32 @stime(i64*)

declare i64 @timegm(%tm*)

declare i64 @timelocal(%tm*)

declare i32 @dysize(i32)

declare i32 @nanosleep(%timespec*, %timespec*)

declare i32 @clock_getres(i32, %timespec*)

declare i32 @clock_gettime(i32, %timespec*)

declare i32 @clock_settime(i32, %timespec*)

declare i32 @clock_nanosleep(i32, i32, %timespec*, %timespec*)

declare i32 @clock_getcpuclockid(i32, i32*)

declare i32 @timer_create(i32, %sigevent*, i8**)

declare i32 @timer_delete(i8*)

declare i32 @timer_settime(i8*, i32, %itimerspec*, %itimerspec*)

declare i32 @timer_gettime(i8*, %itimerspec*)

declare i32 @timer_getoverrun(i8*)

declare i32 @timespec_get(%timespec*, i32)

declare %tm* @getdate(i8*)

declare i32 @getdate_r(i8*, %tm*)

declare i32 @pthread_create(i64*, %pthread_attr_t*, i8* (i8*)*, i8*)

declare void @pthread_exit(i8*)

declare i32 @pthread_join(i64, i8**)

declare i32 @pthread_tryjoin_np(i64, i8**)

declare i32 @pthread_timedjoin_np(i64, i8**, %timespec*)

declare i32 @pthread_detach(i64)

declare i64 @pthread_self()

declare i32 @pthread_equal(i64, i64)

declare i32 @pthread_attr_init(%pthread_attr_t*)

declare i32 @pthread_attr_destroy(%pthread_attr_t*)

declare i32 @pthread_attr_getdetachstate(%pthread_attr_t*, i32*)

declare i32 @pthread_attr_setdetachstate(%pthread_attr_t*, i32)

declare i32 @pthread_attr_getguardsize(%pthread_attr_t*, i64*)

declare i32 @pthread_attr_setguardsize(%pthread_attr_t*, i64)

declare i32 @pthread_attr_getschedparam(%pthread_attr_t*, %sched_param*)

declare i32 @pthread_attr_setschedparam(%pthread_attr_t*, %sched_param*)

declare i32 @pthread_attr_getschedpolicy(%pthread_attr_t*, i32*)

declare i32 @pthread_attr_setschedpolicy(%pthread_attr_t*, i32)

declare i32 @pthread_attr_getinheritsched(%pthread_attr_t*, i32*)

declare i32 @pthread_attr_setinheritsched(%pthread_attr_t*, i32)

declare i32 @pthread_attr_getscope(%pthread_attr_t*, i32*)

declare i32 @pthread_attr_setscope(%pthread_attr_t*, i32)

declare i32 @pthread_attr_getstackaddr(%pthread_attr_t*, i8**)

declare i32 @pthread_attr_setstackaddr(%pthread_attr_t*, i8*)

declare i32 @pthread_attr_getstacksize(%pthread_attr_t*, i64*)

declare i32 @pthread_attr_setstacksize(%pthread_attr_t*, i64)

declare i32 @pthread_attr_getstack(%pthread_attr_t*, i8**, i64*)

declare i32 @pthread_attr_setstack(%pthread_attr_t*, i8*, i64)

declare i32 @pthread_attr_setaffinity_np(%pthread_attr_t*, i64, %come_anon32*)

declare i32 @pthread_attr_getaffinity_np(%pthread_attr_t*, i64, %come_anon32*)

declare i32 @pthread_getattr_default_np(%pthread_attr_t*)

declare i32 @pthread_setattr_default_np(%pthread_attr_t*)

declare i32 @pthread_getattr_np(i64, %pthread_attr_t*)

declare i32 @pthread_setschedparam(i64, i32, %sched_param*)

declare i32 @pthread_getschedparam(i64, i32*, %sched_param*)

declare i32 @pthread_setschedprio(i64, i32)

declare i32 @pthread_getname_np(i64, i8*, i64)

declare i32 @pthread_setname_np(i64, i8*)

declare i32 @pthread_getconcurrency()

declare i32 @pthread_setconcurrency(i32)

declare i32 @pthread_yield()

declare i32 @pthread_setaffinity_np(i64, i64, %come_anon32*)

declare i32 @pthread_getaffinity_np(i64, i64, %come_anon32*)

declare i32 @pthread_once(i32*, void ()*)

declare i32 @pthread_setcancelstate(i32, i32*)

declare i32 @pthread_setcanceltype(i32, i32*)

declare i32 @pthread_cancel(i64)

declare void @pthread_testcancel()

declare void @__pthread_register_cancel(%come_anon55*)

declare void @__pthread_unregister_cancel(%come_anon55*)

declare void @__pthread_register_cancel_defer(%come_anon55*)

declare void @__pthread_unregister_cancel_restore(%come_anon55*)

declare void @__pthread_unwind_next(%come_anon55*)

declare i32 @__sigsetjmp(%__jmp_buf_tag*, i32)

declare i32 @pthread_mutex_init(%come_anon23*, %come_anon21*)

declare i32 @pthread_mutex_destroy(%come_anon23*)

declare i32 @pthread_mutex_trylock(%come_anon23*)

declare i32 @pthread_mutex_lock(%come_anon23*)

declare i32 @pthread_mutex_timedlock(%come_anon23*, %timespec*)

declare i32 @pthread_mutex_unlock(%come_anon23*)

declare i32 @pthread_mutex_getprioceiling(%come_anon23*, i32*)

declare i32 @pthread_mutex_setprioceiling(%come_anon23*, i32, i32*)

declare i32 @pthread_mutex_consistent(%come_anon23*)

declare i32 @pthread_mutex_consistent_np(%come_anon23*)

declare i32 @pthread_mutexattr_init(%come_anon21*)

declare i32 @pthread_mutexattr_destroy(%come_anon21*)

declare i32 @pthread_mutexattr_getpshared(%come_anon21*, i32*)

declare i32 @pthread_mutexattr_setpshared(%come_anon21*, i32)

declare i32 @pthread_mutexattr_gettype(%come_anon21*, i32*)

declare i32 @pthread_mutexattr_settype(%come_anon21*, i32)

declare i32 @pthread_mutexattr_getprotocol(%come_anon21*, i32*)

declare i32 @pthread_mutexattr_setprotocol(%come_anon21*, i32)

declare i32 @pthread_mutexattr_getprioceiling(%come_anon21*, i32*)

declare i32 @pthread_mutexattr_setprioceiling(%come_anon21*, i32)

declare i32 @pthread_mutexattr_getrobust(%come_anon21*, i32*)

declare i32 @pthread_mutexattr_getrobust_np(%come_anon21*, i32*)

declare i32 @pthread_mutexattr_setrobust(%come_anon21*, i32)

declare i32 @pthread_mutexattr_setrobust_np(%come_anon21*, i32)

declare i32 @pthread_rwlock_init(%come_anon25*, %come_anon26*)

declare i32 @pthread_rwlock_destroy(%come_anon25*)

declare i32 @pthread_rwlock_rdlock(%come_anon25*)

declare i32 @pthread_rwlock_tryrdlock(%come_anon25*)

declare i32 @pthread_rwlock_timedrdlock(%come_anon25*, %timespec*)

declare i32 @pthread_rwlock_wrlock(%come_anon25*)

declare i32 @pthread_rwlock_trywrlock(%come_anon25*)

declare i32 @pthread_rwlock_timedwrlock(%come_anon25*, %timespec*)

declare i32 @pthread_rwlock_unlock(%come_anon25*)

declare i32 @pthread_rwlockattr_init(%come_anon26*)

declare i32 @pthread_rwlockattr_destroy(%come_anon26*)

declare i32 @pthread_rwlockattr_getpshared(%come_anon26*, i32*)

declare i32 @pthread_rwlockattr_setpshared(%come_anon26*, i32)

declare i32 @pthread_rwlockattr_getkind_np(%come_anon26*, i32*)

declare i32 @pthread_rwlockattr_setkind_np(%come_anon26*, i32)

declare i32 @pthread_cond_init(%come_anon24*, %come_anon22*)

declare i32 @pthread_cond_destroy(%come_anon24*)

declare i32 @pthread_cond_signal(%come_anon24*)

declare i32 @pthread_cond_broadcast(%come_anon24*)

declare i32 @pthread_cond_wait(%come_anon24*, %come_anon23*)

declare i32 @pthread_cond_timedwait(%come_anon24*, %come_anon23*, %timespec*)

declare i32 @pthread_condattr_init(%come_anon22*)

declare i32 @pthread_condattr_destroy(%come_anon22*)

declare i32 @pthread_condattr_getpshared(%come_anon22*, i32*)

declare i32 @pthread_condattr_setpshared(%come_anon22*, i32)

declare i32 @pthread_condattr_getclock(%come_anon22*, i32*)

declare i32 @pthread_condattr_setclock(%come_anon22*, i32)

declare i32 @pthread_spin_init(i32*, i32)

declare i32 @pthread_spin_destroy(i32*)

declare i32 @pthread_spin_lock(i32*)

declare i32 @pthread_spin_trylock(i32*)

declare i32 @pthread_spin_unlock(i32*)

declare i32 @pthread_barrier_init(%come_anon27*, %come_anon28*, i32)

declare i32 @pthread_barrier_destroy(%come_anon27*)

declare i32 @pthread_barrier_wait(%come_anon27*)

declare i32 @pthread_barrierattr_init(%come_anon28*)

declare i32 @pthread_barrierattr_destroy(%come_anon28*)

declare i32 @pthread_barrierattr_getpshared(%come_anon28*, i32*)

declare i32 @pthread_barrierattr_setpshared(%come_anon28*, i32)

declare i32 @pthread_key_create(i32*, void (i8*)*)

declare i32 @pthread_key_delete(i32)

declare i8* @pthread_getspecific(i32)

declare i32 @pthread_setspecific(i32, i8*)

declare i32 @pthread_getcpuclockid(i64, i32*)

declare i32 @pthread_atfork(void ()*, void ()*, void ()*)

declare i32 @access(i8*, i32)

declare i32 @euidaccess(i8*, i32)

declare i32 @eaccess(i8*, i32)

declare i32 @faccessat(i32, i8*, i32, i32)

declare i64 @lseek(i32, i64, i32)

declare i64 @lseek64(i32, i64, i32)

declare i32 @close(i32)

declare i64 @read(i32, i8*, i64)

declare i64 @write(i32, i8*, i64)

declare i64 @pread(i32, i8*, i64, i64)

declare i64 @pwrite(i32, i8*, i64, i64)

declare i64 @pread64(i32, i8*, i64, i64)

declare i64 @pwrite64(i32, i8*, i64, i64)

declare i32 @pipe(i32*)

declare i32 @pipe2(i32*, i32)

declare i32 @alarm(i32)

declare i32 @sleep(i32)

declare i32 @ualarm(i32, i32)

declare i32 @usleep(i32)

declare i32 @pause()

declare i32 @chown(i8*, i32, i32)

declare i32 @fchown(i32, i32, i32)

declare i32 @lchown(i8*, i32, i32)

declare i32 @fchownat(i32, i8*, i32, i32, i32)

declare i32 @chdir(i8*)

declare i32 @fchdir(i32)

declare i8* @getcwd(i8*, i64)

declare i8* @get_current_dir_name()

declare i8* @getwd(i8*)

declare i32 @dup(i32)

declare i32 @dup2(i32, i32)

declare i32 @dup3(i32, i32, i32)

declare i32 @execve(i8*, i8**, i8**)

declare i32 @fexecve(i32, i8**, i8**)

declare i32 @execv(i8*, i8**)

declare i32 @execle(i8*, i8*, ...)

declare i32 @execl(i8*, i8*, ...)

declare i32 @execvp(i8*, i8**)

declare i32 @execlp(i8*, i8*, ...)

declare i32 @execvpe(i8*, i8**, i8**)

declare i32 @nice(i32)

declare void @_exit(i32)

declare i64 @pathconf(i8*, i32)

declare i64 @fpathconf(i32, i32)

declare i64 @sysconf(i32)

declare i64 @confstr(i32, i8*, i64)

declare i32 @getpid()

declare i32 @getppid()

declare i32 @getpgrp()

declare i32 @__getpgid(i32)

declare i32 @getpgid(i32)

declare i32 @setpgid(i32, i32)

declare i32 @setpgrp()

declare i32 @setsid()

declare i32 @getsid(i32)

declare i32 @getuid()

declare i32 @geteuid()

declare i32 @getgid()

declare i32 @getegid()

declare i32 @getgroups(i32, i32*)

declare i32 @group_member(i32)

declare i32 @setuid(i32)

declare i32 @setreuid(i32, i32)

declare i32 @seteuid(i32)

declare i32 @setgid(i32)

declare i32 @setregid(i32, i32)

declare i32 @setegid(i32)

declare i32 @getresuid(i32*, i32*, i32*)

declare i32 @getresgid(i32*, i32*, i32*)

declare i32 @setresuid(i32, i32, i32)

declare i32 @setresgid(i32, i32, i32)

declare i32 @fork()

declare i32 @vfork()

declare i8* @ttyname(i32)

declare i32 @ttyname_r(i32, i8*, i64)

declare i32 @isatty(i32)

declare i32 @ttyslot()

declare i32 @link(i8*, i8*)

declare i32 @linkat(i32, i8*, i32, i8*, i32)

declare i32 @symlink(i8*, i8*)

declare i64 @readlink(i8*, i8*, i64)

declare i32 @symlinkat(i8*, i32, i8*)

declare i64 @readlinkat(i32, i8*, i8*, i64)

declare i32 @unlink(i8*)

declare i32 @unlinkat(i32, i8*, i32)

declare i32 @rmdir(i8*)

declare i32 @tcgetpgrp(i32)

declare i32 @tcsetpgrp(i32, i32)

declare i8* @getlogin()

declare i32 @getlogin_r(i8*, i64)

declare i32 @setlogin(i8*)

declare i32 @getopt(i32, i8**, i8*)

declare i32 @gethostname(i8*, i64)

declare i32 @sethostname(i8*, i64)

declare i32 @sethostid(i64)

declare i32 @getdomainname(i8*, i64)

declare i32 @setdomainname(i8*, i64)

declare i32 @vhangup()

declare i32 @revoke(i8*)

declare i32 @profil(i16*, i64, i64, i32)

declare i32 @acct(i8*)

declare i8* @getusershell()

declare void @endusershell()

declare void @setusershell()

declare i32 @daemon(i32, i32)

declare i32 @chroot(i8*)

declare i8* @getpass(i8*)

declare i32 @fsync(i32)

declare i32 @syncfs(i32)

declare i64 @gethostid()

declare void @sync()

declare i32 @getpagesize()

declare i32 @getdtablesize()

declare i32 @truncate(i8*, i64)

declare i32 @truncate64(i8*, i64)

declare i32 @ftruncate(i32, i64)

declare i32 @ftruncate64(i32, i64)

declare i32 @brk(i8*)

declare i8* @sbrk(i64)

declare i64 @syscall(i64, ...)

declare i32 @lockf(i32, i32, i64)

declare i32 @lockf64(i32, i32, i64)

declare i64 @copy_file_range(i32, i64*, i32, i64*, i64, i32)

declare i32 @fdatasync(i32)

declare i8* @crypt(i8*, i8*)

declare void @swab(i8*, i8*, i64)

declare i32 @getentropy(i8*, i64)

declare i32 @gettimeofday(%timeval*, %timezone*)

declare i32 @settimeofday(%timeval*, %timezone*)

declare i32 @adjtime(%timeval*, %timeval*)

declare i32 @getitimer(i32, %itimerval*)

declare i32 @setitimer(i32, %itimerval*, %itimerval*)

declare i32 @utimes(i8*, %timeval*)

declare i32 @lutimes(i8*, %timeval*)

declare i32 @futimes(i32, %timeval*)

declare i32 @futimesat(i32, i8*, %timeval*)

declare i32 @stat(i8*, %stat*)

declare i32 @fstat(i32, %stat*)

declare i32 @stat64(i8*, %stat64*)

declare i32 @fstat64(i32, %stat64*)

declare i32 @fstatat(i32, i8*, %stat*, i32)

declare i32 @fstatat64(i32, i8*, %stat64*, i32)

declare i32 @lstat(i8*, %stat*)

declare i32 @lstat64(i8*, %stat64*)

declare i32 @chmod(i8*, i32)

declare i32 @lchmod(i8*, i32)

declare i32 @fchmod(i32, i32)

declare i32 @fchmodat(i32, i8*, i32, i32)

declare i32 @umask(i32)

declare i32 @getumask()

declare i32 @mkdir(i8*, i32)

declare i32 @mkdirat(i32, i8*, i32)

declare i32 @mknod(i8*, i32, i64)

declare i32 @mknodat(i32, i8*, i32, i64)

declare i32 @mkfifo(i8*, i32)

declare i32 @mkfifoat(i32, i8*, i32)

declare i32 @utimensat(i32, i8*, %timespec*, i32)

declare i32 @futimens(i32, %timespec*)

declare i32 @__fxstat(i32, i32, %stat*)

declare i32 @__xstat(i32, i8*, %stat*)

declare i32 @__lxstat(i32, i8*, %stat*)

declare i32 @__fxstatat(i32, i32, i8*, %stat*, i32)

declare i32 @__fxstat64(i32, i32, %stat64*)

declare i32 @__xstat64(i32, i8*, %stat64*)

declare i32 @__lxstat64(i32, i8*, %stat64*)

declare i32 @__fxstatat64(i32, i32, i8*, %stat64*, i32)

declare i32 @__xmknod(i32, i8*, i32, i64*)

declare i32 @__xmknodat(i32, i32, i8*, i32, i64*)

declare i32 @statx(i32, i8*, i32, i32, %statx*)

define internal void @p(i8* %0) !dbg !5 {
entry:
  %msg = alloca i8*, align 8, !dbg !10
  store i8* %0, i8** %msg, align 8, !dbg !10
  %stderr = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !11
  %msg1 = load i8*, i8** %msg, align 8, !dbg !11
  %fun_result = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr, i8* %msg1), !dbg !11
  ret void, !dbg !11
}

define internal void @ncfree(i8* %0) !dbg !12 {
entry:
  %mem = alloca i8*, align 8, !dbg !13
  store i8* %0, i8** %mem, align 8, !dbg !13
  %mem1 = load i8*, i8** %mem, align 8, !dbg !14
  call void @free(i8* %mem1), !dbg !14
  ret void, !dbg !14
}

define internal i8* @nccalloc(i64 %0, i64 %1) !dbg !15 {
entry:
  %result = alloca i8*, align 8, !dbg !19
  %nmemb = alloca i64, align 8, !dbg !19
  store i64 %0, i64* %nmemb, align 4, !dbg !19
  %size = alloca i64, align 8, !dbg !19
  store i64 %1, i64* %size, align 4, !dbg !19
  %nmemb1 = load i64, i64* %nmemb, align 4, !dbg !20
  %size2 = load i64, i64* %size, align 4, !dbg !20
  %fun_result = call i8* @calloc(i64 %nmemb1, i64 %size2), !dbg !20
  store i8* %fun_result, i8** %result, align 8, !dbg !19
  %result3 = load i8*, i8** %result, align 8, !dbg !21
  ret i8* %result3, !dbg !21
}

define internal i8* @ncmemdup(i8* %0) !dbg !22 {
entry:
  %p2 = alloca i8*, align 8, !dbg !23
  %p = alloca i8*, align 8, !dbg !23
  %ret = alloca i8*, align 8, !dbg !23
  %size = alloca i64, align 8, !dbg !23
  %block = alloca i8*, align 8, !dbg !23
  store i8* %0, i8** %block, align 8, !dbg !23
  %block1 = load i8*, i8** %block, align 8, !dbg !24
  %fun_result = call i64 @malloc_usable_size(i8* %block1), !dbg !24
  store i64 %fun_result, i64* %size, align 4, !dbg !23
  %block2 = load i8*, i8** %block, align 8, !dbg !25
  %logical_denial = icmp eq i8* %block2, null, !dbg !25
  br i1 %logical_denial, label %cond_jump_then, label %cond_end, !dbg !25

cond_jump_then:                                   ; preds = %entry
  ret i8* null, !dbg !26

cond_end:                                         ; preds = %entry
  %size3 = load i64, i64* %size, align 4, !dbg !27
  %fun_result4 = call i8* @nccalloc(i64 1, i64 %size3), !dbg !27
  store i8* %fun_result4, i8** %ret, align 8, !dbg !23
  %ret5 = load i8*, i8** %ret, align 8, !dbg !28
  %icmpB = icmp ne i8* %ret5, null, !dbg !28
  br i1 %icmpB, label %cond_jump_then6, label %cond_end7, !dbg !28

cond_jump_then6:                                  ; preds = %cond_end
  %ret8 = load i8*, i8** %ret, align 8, !dbg !29
  store i8* %ret8, i8** %p, align 8, !dbg !23
  %block9 = load i8*, i8** %block, align 8, !dbg !30
  store i8* %block9, i8** %p2, align 8, !dbg !23
  br label %loop_top_block, !dbg !31

cond_end7:                                        ; preds = %cond_end_block, %cond_end
  %ret24 = load i8*, i8** %ret, align 8, !dbg !32
  ret i8* %ret24, !dbg !32

loop_top_block:                                   ; preds = %cond_then_block, %cond_jump_then6
  %p10 = load i8*, i8** %p, align 8, !dbg !33
  %ret11 = load i8*, i8** %ret, align 8, !dbg !33
  %ptrToIntG = ptrtoint i8* %p10 to i64, !dbg !33
  %ptrToIntH = ptrtoint i8* %ret11 to i64, !dbg !33
  %sub = sub i64 %ptrToIntG, %ptrToIntH, !dbg !33
  %div = sdiv i64 %sub, 1, !dbg !33
  %size12 = load i64, i64* %size, align 4, !dbg !33
  %le = icmp slt i64 %div, %size12, !dbg !33
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !33

cond_then_block:                                  ; preds = %loop_top_block
  %p13 = load i8*, i8** %p, align 8, !dbg !34
  %p214 = load i8*, i8** %p2, align 8, !dbg !34
  %derefference_value = load i8, i8* %p214, align 1, !dbg !34
  store i8 %derefference_value, i8* %p13, align 1, !dbg !34
  %p15 = load i8*, i8** %p, align 8, !dbg !35
  %ptrToIntC = ptrtoint i8* %p15 to i64, !dbg !35
  %add = add i64 %ptrToIntC, 1, !dbg !35
  %intToPtr = inttoptr i64 %add to i8*, !dbg !35
  store i8* %intToPtr, i8** %p, align 8, !dbg !35
  %ptrToIntI = ptrtoint i8* %intToPtr to i64, !dbg !35
  %sub16 = sub i64 %ptrToIntI, 1, !dbg !35
  %iintToPtr = inttoptr i64 %sub16 to i8*, !dbg !35
  %p217 = load i8*, i8** %p2, align 8, !dbg !36
  %ptrToIntC18 = ptrtoint i8* %p217 to i64, !dbg !36
  %add19 = add i64 %ptrToIntC18, 1, !dbg !36
  %intToPtr20 = inttoptr i64 %add19 to i8*, !dbg !36
  store i8* %intToPtr20, i8** %p2, align 8, !dbg !36
  %ptrToIntI21 = ptrtoint i8* %intToPtr20 to i64, !dbg !36
  %sub22 = sub i64 %ptrToIntI21, 1, !dbg !36
  %iintToPtr23 = inttoptr i64 %sub22 to i8*, !dbg !36
  br label %loop_top_block, !dbg !36

cond_end_block:                                   ; preds = %loop_top_block
  br label %cond_end7, !dbg !36
}

define internal i8* @xsprintf(i8* %0, ...) !dbg !37 {
entry:
  %len = alloca i32, align 4, !dbg !38
  %result = alloca i8*, align 8, !dbg !38
  %args = alloca [1 x { i32, i32, i8*, i8* }], align 8, !dbg !38
  %msg = alloca i8*, align 8, !dbg !38
  store i8* %0, i8** %msg, align 8, !dbg !38
  %gep = getelementptr [1 x { i32, i32, i8*, i8* }], [1 x { i32, i32, i8*, i8* }]* %args, i32 0, i32 0, !dbg !39
  %castAN = bitcast { i32, i32, i8*, i8* }* %gep to i8*, !dbg !39
  %msg1 = load i8*, i8** %msg, align 8, !dbg !39
  call void @llvm.va_start(i8* %castAN), !dbg !39
  %result2 = load i8*, i8** %result, align 8, !dbg !40
  %msg3 = load i8*, i8** %msg, align 8, !dbg !40
  %gep4 = getelementptr [1 x { i32, i32, i8*, i8* }], [1 x { i32, i32, i8*, i8* }]* %args, i32 0, i32 0, !dbg !40
  %fun_result = call i32 @vasprintf(i8** %result, i8* %msg3, { i32, i32, i8*, i8* }* %gep4), !dbg !40
  store i32 %fun_result, i32* %len, align 4, !dbg !38
  %gep5 = getelementptr [1 x { i32, i32, i8*, i8* }], [1 x { i32, i32, i8*, i8* }]* %args, i32 0, i32 0, !dbg !41
  %castAN6 = bitcast { i32, i32, i8*, i8* }* %gep5 to i8*, !dbg !41
  call void @llvm.va_end(i8* %castAN6), !dbg !41
  %len7 = load i32, i32* %len, align 4, !dbg !42
  %le = icmp slt i32 %len7, 0, !dbg !42
  br i1 %le, label %cond_jump_then, label %cond_end, !dbg !42

cond_jump_then:                                   ; preds = %entry
  %stderr = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !43
  %fun_result8 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @"can't get heap memory.\0A", i32 0, i32 0)), !dbg !43
  call void @exit(i32 2), !dbg !44
  br label %cond_end, !dbg !44

cond_end:                                         ; preds = %cond_jump_then, %entry
  %result9 = load i8*, i8** %result, align 8, !dbg !45
  ret i8* %result9, !dbg !45
}

define internal i8* @char_reverse(i8* %0) !dbg !46 {
entry:
  %i = alloca i32, align 4, !dbg !47
  %result = alloca i8*, align 8, !dbg !47
  %len = alloca i32, align 4, !dbg !47
  %str = alloca i8*, align 8, !dbg !47
  store i8* %0, i8** %str, align 8, !dbg !47
  %str1 = load i8*, i8** %str, align 8, !dbg !48
  %fun_result = call i64 @strlen(i8* %str1), !dbg !48
  %icastM = trunc i64 %fun_result to i32, !dbg !48
  store i32 %icastM, i32* %len, align 4, !dbg !47
  %len2 = load i32, i32* %len, align 4, !dbg !49
  %add = add i32 %len2, 1, !dbg !49
  %icastD = sext i32 %add to i64, !dbg !49
  %fun_result3 = call i8* @calloc(i64 %icastD, i64 1), !dbg !49
  store i8* %fun_result3, i8** %result, align 8, !dbg !47
  store i32 0, i32* %i, align 4, !dbg !47
  br label %loop_top_block, !dbg !47

loop_top_block:                                   ; preds = %cond_then_block, %entry
  %i4 = load i32, i32* %i, align 4, !dbg !50
  %len5 = load i32, i32* %len, align 4, !dbg !50
  %le = icmp slt i32 %i4, %len5, !dbg !50
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !50

cond_then_block:                                  ; preds = %loop_top_block
  %result6 = load i8*, i8** %result, align 8, !dbg !51
  %i7 = load i32, i32* %i, align 4, !dbg !51
  %str8 = load i8*, i8** %str, align 8, !dbg !51
  %len9 = load i32, i32* %len, align 4, !dbg !51
  %i10 = load i32, i32* %i, align 4, !dbg !51
  %sub = sub i32 %len9, %i10, !dbg !51
  %sub11 = sub i32 %sub, 1, !dbg !51
  %element_address = getelementptr inbounds i8, i8* %str8, i32 %sub11, !dbg !51
  %element = load i8, i8* %element_address, align 1, !dbg !51
  %element_address12 = getelementptr i8, i8* %result6, i32 %i7, !dbg !51
  store i8 %element, i8* %element_address12, align 1, !dbg !51
  %i13 = load i32, i32* %i, align 4, !dbg !50
  %add14 = add i32 %i13, 1, !dbg !50
  store i32 %add14, i32* %i, align 4, !dbg !50
  %sub15 = sub i32 %add14, 1, !dbg !50
  br label %loop_top_block, !dbg !50

cond_end_block:                                   ; preds = %loop_top_block
  %result16 = load i8*, i8** %result, align 8, !dbg !52
  %len17 = load i32, i32* %len, align 4, !dbg !52
  %element_address18 = getelementptr i8, i8* %result16, i32 %len17, !dbg !52
  store i8 0, i8* %element_address18, align 1, !dbg !52
  %result19 = load i8*, i8** %result, align 8, !dbg !53
  ret i8* %result19, !dbg !53
}

define internal i8* @char_substring(i8* %0, i32 %1, i32 %2) !dbg !54 {
entry:
  %result111 = alloca i8*, align 8, !dbg !58
  %result97 = alloca i8*, align 8, !dbg !58
  %len93 = alloca i32, align 4, !dbg !58
  %result70 = alloca i8*, align 8, !dbg !58
  %len66 = alloca i32, align 4, !dbg !58
  %len16 = alloca i32, align 4, !dbg !58
  %result = alloca i8*, align 8, !dbg !58
  %len = alloca i32, align 4, !dbg !58
  %str = alloca i8*, align 8, !dbg !58
  store i8* %0, i8** %str, align 8, !dbg !58
  %head = alloca i32, align 4, !dbg !58
  store i32 %1, i32* %head, align 4, !dbg !58
  %tail = alloca i32, align 4, !dbg !58
  store i32 %2, i32* %tail, align 4, !dbg !58
  %str1 = load i8*, i8** %str, align 8, !dbg !59
  %eq = icmp eq i8* %str1, null, !dbg !59
  br i1 %eq, label %cond_jump_then, label %cond_end, !dbg !59

cond_jump_then:                                   ; preds = %entry
  br label %string, !dbg !60

cond_end:                                         ; preds = %entry
  %str13 = load i8*, i8** %str, align 8, !dbg !61
  %fun_result14 = call i64 @strlen(i8* %str13), !dbg !61
  %icastM15 = trunc i64 %fun_result14 to i32, !dbg !61
  store i32 %icastM15, i32* %len16, align 4, !dbg !58
  %head17 = load i32, i32* %head, align 4, !dbg !62
  %le = icmp slt i32 %head17, 0, !dbg !62
  br i1 %le, label %cond_jump_then18, label %cond_end19, !dbg !62

string:                                           ; preds = %cond_jump_then
  %inline_result_variable = alloca i8*, align 8, !dbg !60
  %str2 = alloca i8*, align 8, !dbg !60
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @0, i32 0, i32 0), i8** %str2, align 8, !dbg !60
  %str3 = load i8*, i8** %str2, align 8, !dbg !60
  %fun_result = call i64 @strlen(i8* %str3), !dbg !60
  %add = add i64 %fun_result, 1, !dbg !60
  %icastM = trunc i64 %add to i32, !dbg !60
  store i32 %icastM, i32* %len, align 4, !dbg !58
  %len4 = load i32, i32* %len, align 4, !dbg !58
  %icastD = sext i32 %len4 to i64, !dbg !58
  %fun_result5 = call i8* @nccalloc(i64 %icastD, i64 1), !dbg !58
  store i8* %fun_result5, i8** %result, align 8, !dbg !58
  %result6 = load i8*, i8** %result, align 8, !dbg !58
  %str7 = load i8*, i8** %str2, align 8, !dbg !58
  %len8 = load i32, i32* %len, align 4, !dbg !58
  %icastD9 = sext i32 %len8 to i64, !dbg !58
  %fun_result10 = call i8* @strncpy(i8* %result6, i8* %str7, i64 %icastD9), !dbg !58
  %result11 = load i8*, i8** %result, align 8, !dbg !58
  store i8* %result11, i8** %inline_result_variable, align 8, !dbg !58
  br label %string_end, !dbg !58

string_end:                                       ; preds = %string
  %inline_result_variable12 = load i8*, i8** %inline_result_variable, align 8, !dbg !58
  ret i8* %inline_result_variable12, !dbg !58

cond_jump_then18:                                 ; preds = %cond_end
  %head20 = load i32, i32* %head, align 4, !dbg !63
  %len21 = load i32, i32* %len16, align 4, !dbg !63
  %add22 = add i32 %head20, %len21, !dbg !63
  store i32 %add22, i32* %head, align 4, !dbg !63
  %len23 = load i32, i32* %len16, align 4, !dbg !63
  %sub = sub i32 %add22, %len23, !dbg !63
  br label %cond_end19, !dbg !63

cond_end19:                                       ; preds = %cond_jump_then18, %cond_end
  %tail24 = load i32, i32* %tail, align 4, !dbg !64
  %le25 = icmp slt i32 %tail24, 0, !dbg !64
  br i1 %le25, label %cond_jump_then26, label %cond_end27, !dbg !64

cond_jump_then26:                                 ; preds = %cond_end19
  %tail28 = load i32, i32* %tail, align 4, !dbg !65
  %len29 = load i32, i32* %len16, align 4, !dbg !65
  %add30 = add i32 %len29, 1, !dbg !65
  %add31 = add i32 %tail28, %add30, !dbg !65
  store i32 %add31, i32* %tail, align 4, !dbg !65
  %len32 = load i32, i32* %len16, align 4, !dbg !65
  %add33 = add i32 %len32, 1, !dbg !65
  %sub34 = sub i32 %add31, %add33, !dbg !65
  br label %cond_end27, !dbg !65

cond_end27:                                       ; preds = %cond_jump_then26, %cond_end19
  %head35 = load i32, i32* %head, align 4, !dbg !66
  %tail36 = load i32, i32* %tail, align 4, !dbg !66
  %gt = icmp sgt i32 %head35, %tail36, !dbg !66
  br i1 %gt, label %cond_jump_then37, label %cond_end38, !dbg !66

cond_jump_then37:                                 ; preds = %cond_end27
  %str39 = load i8*, i8** %str, align 8, !dbg !67
  %tail40 = load i32, i32* %tail, align 4, !dbg !67
  %head41 = load i32, i32* %head, align 4, !dbg !67
  %fun_result42 = call i8* @char_substring(i8* %str39, i32 %tail40, i32 %head41), !dbg !67
  %fun_result43 = call i8* @char_reverse(i8* %fun_result42), !dbg !67
  call void @free(i8* %fun_result42), !dbg !67
  ret i8* %fun_result43, !dbg !67

cond_end38:                                       ; preds = %cond_end27
  %head44 = load i32, i32* %head, align 4, !dbg !68
  %le45 = icmp slt i32 %head44, 0, !dbg !68
  br i1 %le45, label %cond_jump_then46, label %cond_end47, !dbg !68

cond_jump_then46:                                 ; preds = %cond_end38
  store i32 0, i32* %head, align 4, !dbg !69
  br label %cond_end47, !dbg !69

cond_end47:                                       ; preds = %cond_jump_then46, %cond_end38
  %tail48 = load i32, i32* %tail, align 4, !dbg !70
  %len49 = load i32, i32* %len16, align 4, !dbg !70
  %gteq = icmp sge i32 %tail48, %len49, !dbg !70
  br i1 %gteq, label %cond_jump_then50, label %cond_end51, !dbg !70

cond_jump_then50:                                 ; preds = %cond_end47
  %len52 = load i32, i32* %len16, align 4, !dbg !71
  store i32 %len52, i32* %tail, align 4, !dbg !71
  br label %cond_end51, !dbg !71

cond_end51:                                       ; preds = %cond_jump_then50, %cond_end47
  %head53 = load i32, i32* %head, align 4, !dbg !72
  %tail54 = load i32, i32* %tail, align 4, !dbg !72
  %eq55 = icmp eq i32 %head53, %tail54, !dbg !72
  br i1 %eq55, label %cond_jump_then56, label %cond_end57, !dbg !72

cond_jump_then56:                                 ; preds = %cond_end51
  br label %string58, !dbg !73

cond_end57:                                       ; preds = %cond_end51
  %tail78 = load i32, i32* %tail, align 4, !dbg !74
  %head79 = load i32, i32* %head, align 4, !dbg !74
  %sub80 = sub i32 %tail78, %head79, !dbg !74
  %add81 = add i32 %sub80, 1, !dbg !74
  %le82 = icmp slt i32 %add81, 1, !dbg !74
  br i1 %le82, label %cond_jump_then83, label %cond_end84, !dbg !74

string58:                                         ; preds = %cond_jump_then56
  %inline_result_variable59 = alloca i8*, align 8, !dbg !73
  %str60 = alloca i8*, align 8, !dbg !73
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @1, i32 0, i32 0), i8** %str60, align 8, !dbg !73
  %str62 = load i8*, i8** %str60, align 8, !dbg !73
  %fun_result63 = call i64 @strlen(i8* %str62), !dbg !73
  %add64 = add i64 %fun_result63, 1, !dbg !73
  %icastM65 = trunc i64 %add64 to i32, !dbg !73
  store i32 %icastM65, i32* %len66, align 4, !dbg !58
  %len67 = load i32, i32* %len66, align 4, !dbg !58
  %icastD68 = sext i32 %len67 to i64, !dbg !58
  %fun_result69 = call i8* @nccalloc(i64 %icastD68, i64 1), !dbg !58
  store i8* %fun_result69, i8** %result70, align 8, !dbg !58
  %result71 = load i8*, i8** %result70, align 8, !dbg !58
  %str72 = load i8*, i8** %str60, align 8, !dbg !58
  %len73 = load i32, i32* %len66, align 4, !dbg !58
  %icastD74 = sext i32 %len73 to i64, !dbg !58
  %fun_result75 = call i8* @strncpy(i8* %result71, i8* %str72, i64 %icastD74), !dbg !58
  %result76 = load i8*, i8** %result70, align 8, !dbg !58
  store i8* %result76, i8** %inline_result_variable59, align 8, !dbg !58
  br label %string_end61, !dbg !58

string_end61:                                     ; preds = %string58
  %inline_result_variable77 = load i8*, i8** %inline_result_variable59, align 8, !dbg !58
  ret i8* %inline_result_variable77, !dbg !58

cond_jump_then83:                                 ; preds = %cond_end57
  br label %string85, !dbg !75

cond_end84:                                       ; preds = %cond_end57
  %tail105 = load i32, i32* %tail, align 4, !dbg !76
  %head106 = load i32, i32* %head, align 4, !dbg !76
  %sub107 = sub i32 %tail105, %head106, !dbg !76
  %add108 = add i32 %sub107, 1, !dbg !76
  %icastD109 = sext i32 %add108 to i64, !dbg !76
  %fun_result110 = call i8* @calloc(i64 %icastD109, i64 1), !dbg !76
  store i8* %fun_result110, i8** %result111, align 8, !dbg !58
  %result112 = load i8*, i8** %result111, align 8, !dbg !77
  %str113 = load i8*, i8** %str, align 8, !dbg !77
  %head114 = load i32, i32* %head, align 4, !dbg !77
  %ptrToIntC = ptrtoint i8* %str113 to i64, !dbg !77
  %sext = sext i32 %head114 to i64, !dbg !77
  %mul = mul i64 %sext, 1, !dbg !77
  %add115 = add i64 %ptrToIntC, %mul, !dbg !77
  %intToPtr = inttoptr i64 %add115 to i8*, !dbg !77
  %tail116 = load i32, i32* %tail, align 4, !dbg !77
  %head117 = load i32, i32* %head, align 4, !dbg !77
  %sub118 = sub i32 %tail116, %head117, !dbg !77
  %icastD119 = sext i32 %sub118 to i64, !dbg !77
  %fun_result120 = call i8* @memcpy(i8* %result112, i8* %intToPtr, i64 %icastD119), !dbg !77
  %result121 = load i8*, i8** %result111, align 8, !dbg !78
  %tail122 = load i32, i32* %tail, align 4, !dbg !78
  %head123 = load i32, i32* %head, align 4, !dbg !78
  %sub124 = sub i32 %tail122, %head123, !dbg !78
  %element_address = getelementptr i8, i8* %result121, i32 %sub124, !dbg !78
  store i8 0, i8* %element_address, align 1, !dbg !78
  %result125 = load i8*, i8** %result111, align 8, !dbg !79
  ret i8* %result125, !dbg !79

string85:                                         ; preds = %cond_jump_then83
  %inline_result_variable86 = alloca i8*, align 8, !dbg !75
  %str87 = alloca i8*, align 8, !dbg !75
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @2, i32 0, i32 0), i8** %str87, align 8, !dbg !75
  %str89 = load i8*, i8** %str87, align 8, !dbg !75
  %fun_result90 = call i64 @strlen(i8* %str89), !dbg !75
  %add91 = add i64 %fun_result90, 1, !dbg !75
  %icastM92 = trunc i64 %add91 to i32, !dbg !75
  store i32 %icastM92, i32* %len93, align 4, !dbg !58
  %len94 = load i32, i32* %len93, align 4, !dbg !58
  %icastD95 = sext i32 %len94 to i64, !dbg !58
  %fun_result96 = call i8* @nccalloc(i64 %icastD95, i64 1), !dbg !58
  store i8* %fun_result96, i8** %result97, align 8, !dbg !58
  %result98 = load i8*, i8** %result97, align 8, !dbg !58
  %str99 = load i8*, i8** %str87, align 8, !dbg !58
  %len100 = load i32, i32* %len93, align 4, !dbg !58
  %icastD101 = sext i32 %len100 to i64, !dbg !58
  %fun_result102 = call i8* @strncpy(i8* %result98, i8* %str99, i64 %icastD101), !dbg !58
  %result103 = load i8*, i8** %result97, align 8, !dbg !58
  store i8* %result103, i8** %inline_result_variable86, align 8, !dbg !58
  br label %string_end88, !dbg !58

string_end88:                                     ; preds = %string85
  %inline_result_variable104 = load i8*, i8** %inline_result_variable86, align 8, !dbg !58
  ret i8* %inline_result_variable104, !dbg !58
}

define internal i32 @char_length(i8* %0) !dbg !80 {
entry:
  %str = alloca i8*, align 8, !dbg !81
  store i8* %0, i8** %str, align 8, !dbg !81
  %str1 = load i8*, i8** %str, align 8, !dbg !82
  %fun_result = call i64 @strlen(i8* %str1), !dbg !82
  %icastM = trunc i64 %fun_result to i32, !dbg !82
  ret i32 %icastM, !dbg !82
}

define internal i32 @int_get_hash_key(i32 %0) !dbg !83 {
entry:
  %value = alloca i32, align 4, !dbg !86
  store i32 %0, i32* %value, align 4, !dbg !86
  %value1 = load i32, i32* %value, align 4, !dbg !87
  ret i32 %value1, !dbg !87
}

define internal i32 @char_get_hash_key(i8* %0) !dbg !88 {
entry:
  %p = alloca i8*, align 8, !dbg !89
  %result = alloca i32, align 4, !dbg !89
  %value = alloca i8*, align 8, !dbg !89
  store i8* %0, i8** %value, align 8, !dbg !89
  store i32 0, i32* %result, align 4, !dbg !89
  %value1 = load i8*, i8** %value, align 8, !dbg !90
  store i8* %value1, i8** %p, align 8, !dbg !89
  br label %loop_top_block, !dbg !91

loop_top_block:                                   ; preds = %cond_then_block, %entry
  %p2 = load i8*, i8** %p, align 8, !dbg !92
  %derefference_value = load i8, i8* %p2, align 1, !dbg !92
  %icmpA = icmp ne i8 %derefference_value, 0, !dbg !92
  br i1 %icmpA, label %cond_then_block, label %cond_end_block, !dbg !92

cond_then_block:                                  ; preds = %loop_top_block
  %result3 = load i32, i32* %result, align 4, !dbg !93
  %p4 = load i8*, i8** %p, align 8, !dbg !93
  %derefference_value5 = load i8, i8* %p4, align 1, !dbg !93
  %icastL = sext i8 %derefference_value5 to i32, !dbg !93
  %add = add i32 %result3, %icastL, !dbg !93
  store i32 %add, i32* %result, align 4, !dbg !93
  %p6 = load i8*, i8** %p, align 8, !dbg !93
  %derefference_value7 = load i8, i8* %p6, align 1, !dbg !93
  %icastL8 = sext i8 %derefference_value7 to i32, !dbg !93
  %sub = sub i32 %add, %icastL8, !dbg !93
  %p9 = load i8*, i8** %p, align 8, !dbg !94
  %ptrToIntC = ptrtoint i8* %p9 to i64, !dbg !94
  %add10 = add i64 %ptrToIntC, 1, !dbg !94
  %intToPtr = inttoptr i64 %add10 to i8*, !dbg !94
  store i8* %intToPtr, i8** %p, align 8, !dbg !94
  %ptrToIntI = ptrtoint i8* %intToPtr to i64, !dbg !94
  %sub11 = sub i64 %ptrToIntI, 1, !dbg !94
  %iintToPtr = inttoptr i64 %sub11 to i8*, !dbg !94
  br label %loop_top_block, !dbg !94

cond_end_block:                                   ; preds = %loop_top_block
  %result12 = load i32, i32* %result, align 4, !dbg !91
  ret i32 %result12, !dbg !91
}

define internal i1 @char_equals(i8* %0, i8* %1) !dbg !95 {
entry:
  %left = alloca i8*, align 8, !dbg !98
  store i8* %0, i8** %left, align 8, !dbg !98
  %right = alloca i8*, align 8, !dbg !98
  store i8* %1, i8** %right, align 8, !dbg !98
  %left1 = load i8*, i8** %left, align 8, !dbg !99
  %right2 = load i8*, i8** %right, align 8, !dbg !99
  %fun_result = call i32 @strcmp(i8* %left1, i8* %right2), !dbg !99
  %eq = icmp eq i32 %fun_result, 0, !dbg !99
  ret i1 %eq, !dbg !99
}

define internal i32 @char_compare(i32 %0, i32 %1) !dbg !100 {
entry:
  %left = alloca i32, align 4, !dbg !103
  store i32 %0, i32* %left, align 4, !dbg !103
  %right = alloca i32, align 4, !dbg !103
  store i32 %1, i32* %right, align 4, !dbg !103
  %left1 = load i32, i32* %left, align 4, !dbg !104
  %right2 = load i32, i32* %right, align 4, !dbg !104
  %le = icmp slt i32 %left1, %right2, !dbg !104
  br i1 %le, label %cond_jump_then, label %cond_jump_elif0, !dbg !104

cond_jump_then:                                   ; preds = %entry
  ret i32 -1, !dbg !105

cond_jump_elif0:                                  ; preds = %entry
  %left3 = load i32, i32* %left, align 4, !dbg !106
  %right4 = load i32, i32* %right, align 4, !dbg !106
  %gt = icmp sgt i32 %left3, %right4, !dbg !106
  br i1 %gt, label %cond_jump_elif_then0, label %cond_else_block, !dbg !106

cond_jump_elif_then0:                             ; preds = %cond_jump_elif0
  ret i32 1, !dbg !107

cond_else_block:                                  ; preds = %cond_jump_elif0
  ret i32 0, !dbg !108

cond_end:                                         ; No predecessors!
  ret i32 0, !dbg !103
}

define internal %buffer* @buffer_initialize(%buffer* %0) !dbg !109 {
entry:
  %self = alloca %buffer*, align 8, !dbg !110
  store %buffer* %0, %buffer** %self, align 8, !dbg !110
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !111
  %field = getelementptr inbounds %buffer, %buffer* %self1, i32 0, i32 2, !dbg !111
  store i32 128, i32* %field, align 4, !dbg !111
  %self2 = load %buffer*, %buffer** %self, align 8, !dbg !112
  %self3 = load %buffer*, %buffer** %self, align 8, !dbg !112
  %field4 = getelementptr inbounds %buffer, %buffer* %self3, i32 0, i32 2, !dbg !112
  %size = load i32, i32* %field4, align 4, !dbg !112
  %icastD = sext i32 %size to i64, !dbg !112
  %fun_result = call i8* @calloc(i64 1, i64 %icastD), !dbg !112
  %field5 = getelementptr inbounds %buffer, %buffer* %self2, i32 0, i32 0, !dbg !112
  store i8* %fun_result, i8** %field5, align 8, !dbg !112
  %self6 = load %buffer*, %buffer** %self, align 8, !dbg !113
  %field7 = getelementptr inbounds %buffer, %buffer* %self6, i32 0, i32 0, !dbg !113
  %buf = load i8*, i8** %field7, align 8, !dbg !113
  %element_address = getelementptr i8, i8* %buf, i32 0, !dbg !113
  store i8 0, i8* %element_address, align 1, !dbg !113
  %self8 = load %buffer*, %buffer** %self, align 8, !dbg !113
  %field9 = getelementptr inbounds %buffer, %buffer* %self8, i32 0, i32 1, !dbg !113
  store i32 0, i32* %field9, align 4, !dbg !113
  %self10 = load %buffer*, %buffer** %self, align 8, !dbg !114
  ret %buffer* %self10, !dbg !114
}

define internal void @buffer_finalize(%buffer* %0) !dbg !115 {
entry:
  %self = alloca %buffer*, align 8, !dbg !116
  store %buffer* %0, %buffer** %self, align 8, !dbg !116
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !117
  %field = getelementptr inbounds %buffer, %buffer* %self1, i32 0, i32 0, !dbg !117
  %buf = load i8*, i8** %field, align 8, !dbg !117
  call void @free(i8* %buf), !dbg !117
  ret void, !dbg !117
}

define internal i32 @buffer_length(%buffer* %0) !dbg !118 {
entry:
  %self = alloca %buffer*, align 8, !dbg !119
  store %buffer* %0, %buffer** %self, align 8, !dbg !119
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !120
  %field = getelementptr inbounds %buffer, %buffer* %self1, i32 0, i32 1, !dbg !120
  %len = load i32, i32* %field, align 4, !dbg !120
  ret i32 %len, !dbg !120
}

define internal void @buffer_append(%buffer* %0, i8* %1, i64 %2) !dbg !121 {
entry:
  %new_size = alloca i32, align 4, !dbg !124
  %self = alloca %buffer*, align 8, !dbg !124
  store %buffer* %0, %buffer** %self, align 8, !dbg !124
  %mem = alloca i8*, align 8, !dbg !124
  store i8* %1, i8** %mem, align 8, !dbg !124
  %size = alloca i64, align 8, !dbg !124
  store i64 %2, i64* %size, align 4, !dbg !124
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !125
  %field = getelementptr inbounds %buffer, %buffer* %self1, i32 0, i32 1, !dbg !125
  %len = load i32, i32* %field, align 4, !dbg !125
  %size2 = load i64, i64* %size, align 4, !dbg !125
  %icastM = trunc i64 %size2 to i32, !dbg !125
  %add = add i32 %len, %icastM, !dbg !125
  %add3 = add i32 %add, 1, !dbg !125
  %add4 = add i32 %add3, 1, !dbg !125
  %self5 = load %buffer*, %buffer** %self, align 8, !dbg !125
  %field6 = getelementptr inbounds %buffer, %buffer* %self5, i32 0, i32 2, !dbg !125
  %size7 = load i32, i32* %field6, align 4, !dbg !125
  %gteq = icmp sge i32 %add4, %size7, !dbg !125
  br i1 %gteq, label %cond_jump_then, label %cond_end, !dbg !125

cond_jump_then:                                   ; preds = %entry
  %self8 = load %buffer*, %buffer** %self, align 8, !dbg !126
  %field9 = getelementptr inbounds %buffer, %buffer* %self8, i32 0, i32 2, !dbg !126
  %size10 = load i32, i32* %field9, align 4, !dbg !126
  %size11 = load i64, i64* %size, align 4, !dbg !126
  %icastM12 = trunc i64 %size11 to i32, !dbg !126
  %add13 = add i32 %size10, %icastM12, !dbg !126
  %add14 = add i32 %add13, 1, !dbg !126
  %mul = mul i32 %add14, 2, !dbg !126
  store i32 %mul, i32* %new_size, align 4, !dbg !124
  %self15 = load %buffer*, %buffer** %self, align 8, !dbg !127
  %self16 = load %buffer*, %buffer** %self, align 8, !dbg !127
  %field17 = getelementptr inbounds %buffer, %buffer* %self16, i32 0, i32 0, !dbg !127
  %buf = load i8*, i8** %field17, align 8, !dbg !127
  %new_size18 = load i32, i32* %new_size, align 4, !dbg !127
  %icastD = sext i32 %new_size18 to i64, !dbg !127
  %fun_result = call i8* @realloc(i8* %buf, i64 %icastD), !dbg !127
  %field19 = getelementptr inbounds %buffer, %buffer* %self15, i32 0, i32 0, !dbg !127
  store i8* %fun_result, i8** %field19, align 8, !dbg !127
  %self20 = load %buffer*, %buffer** %self, align 8, !dbg !128
  %new_size21 = load i32, i32* %new_size, align 4, !dbg !128
  %field22 = getelementptr inbounds %buffer, %buffer* %self20, i32 0, i32 2, !dbg !128
  store i32 %new_size21, i32* %field22, align 4, !dbg !128
  br label %cond_end, !dbg !128

cond_end:                                         ; preds = %cond_jump_then, %entry
  %self23 = load %buffer*, %buffer** %self, align 8, !dbg !129
  %field24 = getelementptr inbounds %buffer, %buffer* %self23, i32 0, i32 0, !dbg !129
  %buf25 = load i8*, i8** %field24, align 8, !dbg !129
  %self26 = load %buffer*, %buffer** %self, align 8, !dbg !129
  %field27 = getelementptr inbounds %buffer, %buffer* %self26, i32 0, i32 1, !dbg !129
  %len28 = load i32, i32* %field27, align 4, !dbg !129
  %ptrToIntC = ptrtoint i8* %buf25 to i64, !dbg !129
  %sext = sext i32 %len28 to i64, !dbg !129
  %mul29 = mul i64 %sext, 1, !dbg !129
  %add30 = add i64 %ptrToIntC, %mul29, !dbg !129
  %intToPtr = inttoptr i64 %add30 to i8*, !dbg !129
  %mem31 = load i8*, i8** %mem, align 8, !dbg !129
  %size32 = load i64, i64* %size, align 4, !dbg !129
  %fun_result33 = call i8* @memcpy(i8* %intToPtr, i8* %mem31, i64 %size32), !dbg !129
  %self34 = load %buffer*, %buffer** %self, align 8, !dbg !130
  %self35 = load %buffer*, %buffer** %self, align 8, !dbg !130
  %field36 = getelementptr inbounds %buffer, %buffer* %self35, i32 0, i32 1, !dbg !130
  %len37 = load i32, i32* %field36, align 4, !dbg !130
  %size38 = load i64, i64* %size, align 4, !dbg !130
  %icastM39 = trunc i64 %size38 to i32, !dbg !130
  %add40 = add i32 %len37, %icastM39, !dbg !130
  %field41 = getelementptr inbounds %buffer, %buffer* %self34, i32 0, i32 1, !dbg !130
  store i32 %add40, i32* %field41, align 4, !dbg !130
  %self42 = load %buffer*, %buffer** %self, align 8, !dbg !131
  %field43 = getelementptr inbounds %buffer, %buffer* %self42, i32 0, i32 0, !dbg !131
  %buf44 = load i8*, i8** %field43, align 8, !dbg !131
  %self45 = load %buffer*, %buffer** %self, align 8, !dbg !131
  %field46 = getelementptr inbounds %buffer, %buffer* %self45, i32 0, i32 1, !dbg !131
  %len47 = load i32, i32* %field46, align 4, !dbg !131
  %element_address = getelementptr i8, i8* %buf44, i32 %len47, !dbg !131
  store i8 0, i8* %element_address, align 1, !dbg !131
  ret void, !dbg !131
}

define internal void @buffer_append_char(%buffer* %0, i8 %1) !dbg !132 {
entry:
  %new_size = alloca i32, align 4, !dbg !136
  %self = alloca %buffer*, align 8, !dbg !136
  store %buffer* %0, %buffer** %self, align 8, !dbg !136
  %c = alloca i8, align 1, !dbg !136
  store i8 %1, i8* %c, align 1, !dbg !136
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !137
  %field = getelementptr inbounds %buffer, %buffer* %self1, i32 0, i32 1, !dbg !137
  %len = load i32, i32* %field, align 4, !dbg !137
  %add = add i32 %len, 1, !dbg !137
  %add2 = add i32 %add, 1, !dbg !137
  %add3 = add i32 %add2, 1, !dbg !137
  %self4 = load %buffer*, %buffer** %self, align 8, !dbg !137
  %field5 = getelementptr inbounds %buffer, %buffer* %self4, i32 0, i32 2, !dbg !137
  %size = load i32, i32* %field5, align 4, !dbg !137
  %gteq = icmp sge i32 %add3, %size, !dbg !137
  br i1 %gteq, label %cond_jump_then, label %cond_end, !dbg !137

cond_jump_then:                                   ; preds = %entry
  %self6 = load %buffer*, %buffer** %self, align 8, !dbg !138
  %field7 = getelementptr inbounds %buffer, %buffer* %self6, i32 0, i32 2, !dbg !138
  %size8 = load i32, i32* %field7, align 4, !dbg !138
  %add9 = add i32 %size8, 10, !dbg !138
  %add10 = add i32 %add9, 1, !dbg !138
  %mul = mul i32 %add10, 2, !dbg !138
  store i32 %mul, i32* %new_size, align 4, !dbg !136
  %self11 = load %buffer*, %buffer** %self, align 8, !dbg !139
  %self12 = load %buffer*, %buffer** %self, align 8, !dbg !139
  %field13 = getelementptr inbounds %buffer, %buffer* %self12, i32 0, i32 0, !dbg !139
  %buf = load i8*, i8** %field13, align 8, !dbg !139
  %new_size14 = load i32, i32* %new_size, align 4, !dbg !139
  %icastD = sext i32 %new_size14 to i64, !dbg !139
  %fun_result = call i8* @realloc(i8* %buf, i64 %icastD), !dbg !139
  %field15 = getelementptr inbounds %buffer, %buffer* %self11, i32 0, i32 0, !dbg !139
  store i8* %fun_result, i8** %field15, align 8, !dbg !139
  %self16 = load %buffer*, %buffer** %self, align 8, !dbg !140
  %new_size17 = load i32, i32* %new_size, align 4, !dbg !140
  %field18 = getelementptr inbounds %buffer, %buffer* %self16, i32 0, i32 2, !dbg !140
  store i32 %new_size17, i32* %field18, align 4, !dbg !140
  br label %cond_end, !dbg !140

cond_end:                                         ; preds = %cond_jump_then, %entry
  %self19 = load %buffer*, %buffer** %self, align 8, !dbg !141
  %field20 = getelementptr inbounds %buffer, %buffer* %self19, i32 0, i32 0, !dbg !141
  %buf21 = load i8*, i8** %field20, align 8, !dbg !141
  %self22 = load %buffer*, %buffer** %self, align 8, !dbg !141
  %field23 = getelementptr inbounds %buffer, %buffer* %self22, i32 0, i32 1, !dbg !141
  %len24 = load i32, i32* %field23, align 4, !dbg !141
  %c25 = load i8, i8* %c, align 1, !dbg !141
  %element_address = getelementptr i8, i8* %buf21, i32 %len24, !dbg !141
  store i8 %c25, i8* %element_address, align 1, !dbg !141
  %self26 = load %buffer*, %buffer** %self, align 8, !dbg !142
  %self27 = load %buffer*, %buffer** %self, align 8, !dbg !142
  %field28 = getelementptr inbounds %buffer, %buffer* %self27, i32 0, i32 1, !dbg !142
  %len29 = load i32, i32* %field28, align 4, !dbg !142
  %add30 = add i32 %len29, 1, !dbg !142
  %field31 = getelementptr inbounds %buffer, %buffer* %self26, i32 0, i32 1, !dbg !142
  store i32 %add30, i32* %field31, align 4, !dbg !142
  %sub = sub i32 %add30, 1, !dbg !142
  %self32 = load %buffer*, %buffer** %self, align 8, !dbg !143
  %field33 = getelementptr inbounds %buffer, %buffer* %self32, i32 0, i32 0, !dbg !143
  %buf34 = load i8*, i8** %field33, align 8, !dbg !143
  %self35 = load %buffer*, %buffer** %self, align 8, !dbg !143
  %field36 = getelementptr inbounds %buffer, %buffer* %self35, i32 0, i32 1, !dbg !143
  %len37 = load i32, i32* %field36, align 4, !dbg !143
  %element_address38 = getelementptr i8, i8* %buf34, i32 %len37, !dbg !143
  store i8 0, i8* %element_address38, align 1, !dbg !143
  ret void, !dbg !143
}

define internal void @buffer_append_str(%buffer* %0, i8* %1) !dbg !144 {
entry:
  %self = alloca %buffer*, align 8, !dbg !145
  store %buffer* %0, %buffer** %self, align 8, !dbg !145
  %str = alloca i8*, align 8, !dbg !145
  store i8* %1, i8** %str, align 8, !dbg !145
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !146
  %str2 = load i8*, i8** %str, align 8, !dbg !146
  %str3 = load i8*, i8** %str, align 8, !dbg !146
  %fun_result = call i64 @strlen(i8* %str3), !dbg !146
  call void @buffer_append(%buffer* %self1, i8* %str2, i64 %fun_result), !dbg !146
  ret void, !dbg !146
}

define internal void @buffer_append_nullterminated_str(%buffer* %0, i8* %1) !dbg !147 {
entry:
  %self = alloca %buffer*, align 8, !dbg !148
  store %buffer* %0, %buffer** %self, align 8, !dbg !148
  %str = alloca i8*, align 8, !dbg !148
  store i8* %1, i8** %str, align 8, !dbg !148
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !149
  %str2 = load i8*, i8** %str, align 8, !dbg !149
  %str3 = load i8*, i8** %str, align 8, !dbg !149
  %fun_result = call i64 @strlen(i8* %str3), !dbg !149
  call void @buffer_append(%buffer* %self1, i8* %str2, i64 %fun_result), !dbg !149
  %self4 = load %buffer*, %buffer** %self, align 8, !dbg !150
  call void @buffer_append_char(%buffer* %self4, i8 0), !dbg !150
  ret void, !dbg !150
}

define internal i8* @buffer_to_string(%buffer* %0) !dbg !151 {
entry:
  %result = alloca i8*, align 8, !dbg !152
  %len = alloca i32, align 4, !dbg !152
  %self = alloca %buffer*, align 8, !dbg !152
  store %buffer* %0, %buffer** %self, align 8, !dbg !152
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !153
  %field = getelementptr inbounds %buffer, %buffer* %self1, i32 0, i32 0, !dbg !153
  %buf = load i8*, i8** %field, align 8, !dbg !153
  br label %string, !dbg !153

string:                                           ; preds = %entry
  %inline_result_variable = alloca i8*, align 8, !dbg !153
  %str = alloca i8*, align 8, !dbg !153
  store i8* %buf, i8** %str, align 8, !dbg !153
  %str2 = load i8*, i8** %str, align 8, !dbg !153
  %fun_result = call i64 @strlen(i8* %str2), !dbg !153
  %add = add i64 %fun_result, 1, !dbg !153
  %icastM = trunc i64 %add to i32, !dbg !153
  store i32 %icastM, i32* %len, align 4, !dbg !152
  %len3 = load i32, i32* %len, align 4, !dbg !152
  %icastD = sext i32 %len3 to i64, !dbg !152
  %fun_result4 = call i8* @nccalloc(i64 %icastD, i64 1), !dbg !152
  store i8* %fun_result4, i8** %result, align 8, !dbg !152
  %result5 = load i8*, i8** %result, align 8, !dbg !152
  %str6 = load i8*, i8** %str, align 8, !dbg !152
  %len7 = load i32, i32* %len, align 4, !dbg !152
  %icastD8 = sext i32 %len7 to i64, !dbg !152
  %fun_result9 = call i8* @strncpy(i8* %result5, i8* %str6, i64 %icastD8), !dbg !152
  %result10 = load i8*, i8** %result, align 8, !dbg !152
  store i8* %result10, i8** %inline_result_variable, align 8, !dbg !152
  br label %string_end, !dbg !152

string_end:                                       ; preds = %string
  %inline_result_variable11 = load i8*, i8** %inline_result_variable, align 8, !dbg !152
  ret i8* %inline_result_variable11, !dbg !152
}

define internal void @buffer_append_int(%buffer* %0, i32 %1) !dbg !154 {
entry:
  %self = alloca %buffer*, align 8, !dbg !157
  store %buffer* %0, %buffer** %self, align 8, !dbg !157
  %value = alloca i32, align 4, !dbg !157
  store i32 %1, i32* %value, align 4, !dbg !157
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !158
  %value2 = load i32, i32* %value, align 4, !dbg !158
  %castAQ = bitcast i32* %value to i8*, !dbg !158
  call void @buffer_append(%buffer* %self1, i8* %castAQ, i64 4), !dbg !158
  ret void, !dbg !158
}

define internal void @buffer_append_long(%buffer* %0, i64 %1) !dbg !159 {
entry:
  %self = alloca %buffer*, align 8, !dbg !162
  store %buffer* %0, %buffer** %self, align 8, !dbg !162
  %value = alloca i64, align 8, !dbg !162
  store i64 %1, i64* %value, align 4, !dbg !162
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !163
  %value2 = load i64, i64* %value, align 4, !dbg !163
  %castAQ = bitcast i64* %value to i8*, !dbg !163
  call void @buffer_append(%buffer* %self1, i8* %castAQ, i64 8), !dbg !163
  ret void, !dbg !163
}

define internal void @buffer_append_short(%buffer* %0, i16 %1) !dbg !164 {
entry:
  %self = alloca %buffer*, align 8, !dbg !168
  store %buffer* %0, %buffer** %self, align 8, !dbg !168
  %value = alloca i16, align 2, !dbg !168
  store i16 %1, i16* %value, align 2, !dbg !168
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !169
  %value2 = load i16, i16* %value, align 2, !dbg !169
  %castAQ = bitcast i16* %value to i8*, !dbg !169
  call void @buffer_append(%buffer* %self1, i8* %castAQ, i64 2), !dbg !169
  ret void, !dbg !169
}

define internal void @buffer_alignment(%buffer* %0) !dbg !170 {
entry:
  %i = alloca i32, align 4, !dbg !171
  %len2 = alloca i32, align 4, !dbg !171
  %self = alloca %buffer*, align 8, !dbg !171
  store %buffer* %0, %buffer** %self, align 8, !dbg !171
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !172
  %field = getelementptr inbounds %buffer, %buffer* %self1, i32 0, i32 1, !dbg !172
  %len = load i32, i32* %field, align 4, !dbg !172
  store i32 %len, i32* %len2, align 4, !dbg !171
  %len3 = load i32, i32* %len2, align 4, !dbg !173
  %add = add i32 %len3, 3, !dbg !173
  %andtmp = and i32 %add, -4, !dbg !173
  store i32 %andtmp, i32* %len2, align 4, !dbg !173
  %self4 = load %buffer*, %buffer** %self, align 8, !dbg !174
  %field5 = getelementptr inbounds %buffer, %buffer* %self4, i32 0, i32 1, !dbg !174
  %len6 = load i32, i32* %field5, align 4, !dbg !174
  store i32 %len6, i32* %i, align 4, !dbg !171
  br label %loop_top_block, !dbg !171

loop_top_block:                                   ; preds = %cond_then_block, %entry
  %i7 = load i32, i32* %i, align 4, !dbg !174
  %len8 = load i32, i32* %len2, align 4, !dbg !174
  %le = icmp slt i32 %i7, %len8, !dbg !174
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !174

cond_then_block:                                  ; preds = %loop_top_block
  %self9 = load %buffer*, %buffer** %self, align 8, !dbg !175
  call void @buffer_append_char(%buffer* %self9, i8 0), !dbg !175
  %i10 = load i32, i32* %i, align 4, !dbg !174
  %add11 = add i32 %i10, 1, !dbg !174
  store i32 %add11, i32* %i, align 4, !dbg !174
  %sub = sub i32 %add11, 1, !dbg !174
  br label %loop_top_block, !dbg !174

cond_end_block:                                   ; preds = %loop_top_block
  ret void, !dbg !174
}

define internal i32 @buffer_compare(%buffer* %0, %buffer* %1) !dbg !176 {
entry:
  %left = alloca %buffer*, align 8, !dbg !177
  store %buffer* %0, %buffer** %left, align 8, !dbg !177
  %right = alloca %buffer*, align 8, !dbg !177
  store %buffer* %1, %buffer** %right, align 8, !dbg !177
  %left1 = load %buffer*, %buffer** %left, align 8, !dbg !178
  %field = getelementptr inbounds %buffer, %buffer* %left1, i32 0, i32 0, !dbg !178
  %buf = load i8*, i8** %field, align 8, !dbg !178
  %right2 = load %buffer*, %buffer** %right, align 8, !dbg !178
  %field3 = getelementptr inbounds %buffer, %buffer* %right2, i32 0, i32 0, !dbg !178
  %buf4 = load i8*, i8** %field3, align 8, !dbg !178
  %fun_result = call i32 @strcmp(i8* %buf, i8* %buf4), !dbg !178
  ret i32 %fun_result, !dbg !178
}

define internal %buffer* @char_to_buffer(i8* %0) !dbg !179 {
entry:
  %result = alloca %buffer*, align 8, !dbg !180
  %self = alloca i8*, align 8, !dbg !180
  store i8* %0, i8** %self, align 8, !dbg !180
  %fun_result = call i8* @calloc(i64 1, i64 16), !dbg !181
  %obj = bitcast i8* %fun_result to %buffer*, !dbg !181
  %fun_result1 = call %buffer* @buffer_initialize(%buffer* %obj), !dbg !181
  store %buffer* %fun_result1, %buffer** %result, align 8, !dbg !180
  %result2 = load %buffer*, %buffer** %result, align 8, !dbg !182
  %self3 = load i8*, i8** %self, align 8, !dbg !182
  call void @buffer_append_str(%buffer* %result2, i8* %self3), !dbg !182
  %result4 = load %buffer*, %buffer** %result, align 8, !dbg !183
  ret %buffer* %result4, !dbg !183
}

define internal void @come_fd_zero(%come_anon8* %0) !dbg !184 {
entry:
  %__arr = alloca %come_anon8*, align 8, !dbg !185
  %__i = alloca i32, align 4, !dbg !185
  %fds = alloca %come_anon8*, align 8, !dbg !185
  store %come_anon8* %0, %come_anon8** %fds, align 8, !dbg !185
  br label %loop_top_block, !dbg !186

loop_top_block:                                   ; preds = %cond_end_block4, %entry
  %fds1 = load %come_anon8*, %come_anon8** %fds, align 8, !dbg !186
  store %come_anon8* %fds1, %come_anon8** %__arr, align 8, !dbg !185
  store i32 0, i32* %__i, align 4, !dbg !186
  br label %loop_top_block2, !dbg !186

cond_end_block:                                   ; preds = %cond_end_block4
  ret void, !dbg !186

loop_top_block2:                                  ; preds = %cond_then_block, %loop_top_block
  %__i3 = load i32, i32* %__i, align 4, !dbg !186
  %le = icmp ult i32 %__i3, 16, !dbg !186
  br i1 %le, label %cond_then_block, label %cond_end_block4, !dbg !186

cond_then_block:                                  ; preds = %loop_top_block2
  %__arr5 = load %come_anon8*, %come_anon8** %__arr, align 8, !dbg !186
  %field = getelementptr inbounds %come_anon8, %come_anon8* %__arr5, i32 0, i32 0, !dbg !186
  %__i6 = load i32, i32* %__i, align 4, !dbg !186
  %array_cast = bitcast [16 x i64]* %field to i64*, !dbg !186
  %gep = getelementptr i64, i64* %array_cast, i32 %__i6, !dbg !186
  store i64 0, i64* %gep, align 4, !dbg !186
  %__i7 = load i32, i32* %__i, align 4, !dbg !186
  %add = add i32 %__i7, 1, !dbg !186
  store i32 %add, i32* %__i, align 4, !dbg !186
  br label %loop_top_block2, !dbg !186

cond_end_block4:                                  ; preds = %loop_top_block2
  br i1 false, label %loop_top_block, label %cond_end_block, !dbg !186
}

define internal void @come_fd_set(i32 %0, %come_anon8* %1) !dbg !187 {
entry:
  %fd = alloca i32, align 4, !dbg !190
  store i32 %0, i32* %fd, align 4, !dbg !190
  %fds = alloca %come_anon8*, align 8, !dbg !190
  store %come_anon8* %1, %come_anon8** %fds, align 8, !dbg !190
  %fds1 = load %come_anon8*, %come_anon8** %fds, align 8, !dbg !191
  %field = getelementptr inbounds %come_anon8, %come_anon8* %fds1, i32 0, i32 0, !dbg !191
  %fd2 = load i32, i32* %fd, align 4, !dbg !191
  %div = sdiv i32 %fd2, 64, !dbg !191
  %array_cast = bitcast [16 x i64]* %field to i64*, !dbg !191
  %gep = getelementptr i64, i64* %array_cast, i32 %div, !dbg !191
  %element = load i64, i64* %gep, align 4, !dbg !191
  %fd3 = load i32, i32* %fd, align 4, !dbg !191
  %div4 = srem i32 %fd3, 64, !dbg !191
  %icastD = sext i32 %div4 to i64, !dbg !191
  %lshifttmp = shl i64 1, %icastD, !dbg !191
  %load = load i64, i64* %gep, align 4, !dbg !191
  %ortmp = or i64 %load, %lshifttmp, !dbg !191
  store i64 %ortmp, i64* %gep, align 4, !dbg !191
  ret void, !dbg !191
}

define internal i32 @come_fd_isset(i32 %0, %come_anon8* %1) !dbg !192 {
entry:
  %fd = alloca i32, align 4, !dbg !193
  store i32 %0, i32* %fd, align 4, !dbg !193
  %fds = alloca %come_anon8*, align 8, !dbg !193
  store %come_anon8* %1, %come_anon8** %fds, align 8, !dbg !193
  %fds1 = load %come_anon8*, %come_anon8** %fds, align 8, !dbg !194
  %field = getelementptr inbounds %come_anon8, %come_anon8* %fds1, i32 0, i32 0, !dbg !194
  %fd2 = load i32, i32* %fd, align 4, !dbg !194
  %div = sdiv i32 %fd2, 64, !dbg !194
  %array_cast = bitcast [16 x i64]* %field to i64*, !dbg !194
  %gep = getelementptr i64, i64* %array_cast, i32 %div, !dbg !194
  %element = load i64, i64* %gep, align 4, !dbg !194
  %fd3 = load i32, i32* %fd, align 4, !dbg !194
  %div4 = srem i32 %fd3, 64, !dbg !194
  %icastD = sext i32 %div4 to i64, !dbg !194
  %lshifttmp = shl i64 1, %icastD, !dbg !194
  %andtmp = and i64 %element, %lshifttmp, !dbg !194
  %not_eq = icmp ne i64 %andtmp, 0, !dbg !194
  %icastL = sext i1 %not_eq to i32, !dbg !194
  ret i32 %icastL, !dbg !194
}

define internal i32 @int_expect(i32 %0, i8* %1, void (i8*)* %2) !dbg !195 {
entry:
  %self = alloca i32, align 4, !dbg !198
  store i32 %0, i32* %self, align 4, !dbg !198
  %parent = alloca i8*, align 8, !dbg !198
  store i8* %1, i8** %parent, align 8, !dbg !198
  %block = alloca void (i8*)*, align 8, !dbg !198
  store void (i8*)* %2, void (i8*)** %block, align 8, !dbg !198
  %self1 = load i32, i32* %self, align 4, !dbg !199
  %le = icmp slt i32 %self1, 0, !dbg !199
  br i1 %le, label %cond_jump_then, label %cond_end, !dbg !199

cond_jump_then:                                   ; preds = %entry
  %block2 = load void (i8*)*, void (i8*)** %block, align 8, !dbg !200
  %parent3 = load i8*, i8** %parent, align 8, !dbg !200
  call void %block2(i8* %parent3), !dbg !200
  br label %cond_end, !dbg !200

cond_end:                                         ; preds = %cond_jump_then, %entry
  %self4 = load i32, i32* %self, align 4, !dbg !201
  ret i32 %self4, !dbg !201
}

define internal i1 @bool_expect(i1 %0, i8* %1, void (i8*)* %2) !dbg !202 {
entry:
  %self = alloca i1, align 1, !dbg !205
  store i1 %0, i1* %self, align 1, !dbg !205
  %parent = alloca i8*, align 8, !dbg !205
  store i8* %1, i8** %parent, align 8, !dbg !205
  %block = alloca void (i8*)*, align 8, !dbg !205
  store void (i8*)* %2, void (i8*)** %block, align 8, !dbg !205
  %self1 = load i1, i1* %self, align 1, !dbg !206
  %logical_denial = icmp eq i1 %self1, false, !dbg !206
  br i1 %logical_denial, label %cond_jump_then, label %cond_end, !dbg !206

cond_jump_then:                                   ; preds = %entry
  %block2 = load void (i8*)*, void (i8*)** %block, align 8, !dbg !207
  %parent3 = load i8*, i8** %parent, align 8, !dbg !207
  call void %block2(i8* %parent3), !dbg !207
  br label %cond_end, !dbg !207

cond_end:                                         ; preds = %cond_jump_then, %entry
  %self4 = load i1, i1* %self, align 1, !dbg !208
  ret i1 %self4, !dbg !208
}

define internal void @int_times(i32 %0, i8* %1, void (i8*)* %2) !dbg !209 {
entry:
  %i = alloca i32, align 4, !dbg !210
  %self = alloca i32, align 4, !dbg !210
  store i32 %0, i32* %self, align 4, !dbg !210
  %parent = alloca i8*, align 8, !dbg !210
  store i8* %1, i8** %parent, align 8, !dbg !210
  %block = alloca void (i8*)*, align 8, !dbg !210
  store void (i8*)* %2, void (i8*)** %block, align 8, !dbg !210
  store i32 0, i32* %i, align 4, !dbg !211
  br label %loop_top_block, !dbg !211

loop_top_block:                                   ; preds = %cond_then_block, %entry
  %i1 = load i32, i32* %i, align 4, !dbg !211
  %self2 = load i32, i32* %self, align 4, !dbg !211
  %le = icmp slt i32 %i1, %self2, !dbg !211
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !211

cond_then_block:                                  ; preds = %loop_top_block
  %block3 = load void (i8*)*, void (i8*)** %block, align 8, !dbg !212
  %parent4 = load i8*, i8** %parent, align 8, !dbg !212
  call void %block3(i8* %parent4), !dbg !212
  %i5 = load i32, i32* %i, align 4, !dbg !211
  %add = add i32 %i5, 1, !dbg !211
  store i32 %add, i32* %i, align 4, !dbg !211
  %sub = sub i32 %add, 1, !dbg !211
  br label %loop_top_block, !dbg !211

cond_end_block:                                   ; preds = %loop_top_block
  ret void, !dbg !211
}

define internal i1 @xiswalpha(i32 %0) !dbg !213 {
entry:
  %result = alloca i1, align 1, !dbg !214
  %andand6 = alloca i1, align 1, !dbg !214
  %andand = alloca i1, align 1, !dbg !214
  %oror = alloca i1, align 1, !dbg !214
  %c = alloca i32, align 4, !dbg !214
  store i32 %0, i32* %c, align 4, !dbg !214
  %c1 = load i32, i32* %c, align 4, !dbg !215
  %gteq = icmp sge i32 %c1, 97, !dbg !215
  store i1 %gteq, i1* %andand, align 1, !dbg !215
  br i1 %gteq, label %cond_jump_then, label %cond_jump_end, !dbg !215

cond_jump_then:                                   ; preds = %entry
  %c2 = load i32, i32* %c, align 4, !dbg !215
  %leeq = icmp sle i32 %c2, 122, !dbg !215
  %andand3 = and i1 %gteq, %leeq, !dbg !215
  store i1 %andand3, i1* %andand, align 1, !dbg !215
  br label %cond_jump_end, !dbg !215

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %andand_result_value = load i1, i1* %andand, align 1, !dbg !215
  store i1 %andand_result_value, i1* %oror, align 1, !dbg !215
  br i1 %andand_result_value, label %cond_jump_end5, label %cond_jump_then4, !dbg !215

cond_jump_then4:                                  ; preds = %cond_jump_end
  %c7 = load i32, i32* %c, align 4, !dbg !215
  %gteq8 = icmp sge i32 %c7, 65, !dbg !215
  store i1 %gteq8, i1* %andand6, align 1, !dbg !215
  br i1 %gteq8, label %cond_jump_then9, label %cond_jump_end10, !dbg !215

cond_jump_end5:                                   ; preds = %cond_jump_end10, %cond_jump_end
  %oror_result_value = load i1, i1* %oror, align 1, !dbg !215
  store i1 %oror_result_value, i1* %result, align 1, !dbg !214
  %result16 = load i1, i1* %result, align 1, !dbg !216
  ret i1 %result16, !dbg !216

cond_jump_then9:                                  ; preds = %cond_jump_then4
  %c11 = load i32, i32* %c, align 4, !dbg !215
  %leeq12 = icmp sle i32 %c11, 90, !dbg !215
  %andand13 = and i1 %gteq8, %leeq12, !dbg !215
  store i1 %andand13, i1* %andand6, align 1, !dbg !215
  br label %cond_jump_end10, !dbg !215

cond_jump_end10:                                  ; preds = %cond_jump_then9, %cond_jump_then4
  %andand_result_value14 = load i1, i1* %andand6, align 1, !dbg !215
  %oror15 = or i1 %andand_result_value, %andand_result_value14, !dbg !215
  store i1 %oror15, i1* %oror, align 1, !dbg !215
  br label %cond_jump_end5, !dbg !215
}

define internal i1 @xiswblank(i32 %0) !dbg !217 {
entry:
  %oror = alloca i1, align 1, !dbg !218
  %c = alloca i32, align 4, !dbg !218
  store i32 %0, i32* %c, align 4, !dbg !218
  %c1 = load i32, i32* %c, align 4, !dbg !219
  %eq = icmp eq i32 %c1, 32, !dbg !219
  store i1 %eq, i1* %oror, align 1, !dbg !219
  br i1 %eq, label %cond_jump_end, label %cond_jump_then, !dbg !219

cond_jump_then:                                   ; preds = %entry
  %c2 = load i32, i32* %c, align 4, !dbg !219
  %eq3 = icmp eq i32 %c2, 9, !dbg !219
  %oror4 = or i1 %eq, %eq3, !dbg !219
  store i1 %oror4, i1* %oror, align 1, !dbg !219
  br label %cond_jump_end, !dbg !219

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %oror_result_value = load i1, i1* %oror, align 1, !dbg !219
  ret i1 %oror_result_value, !dbg !219
}

define internal i1 @xiswdigit(i32 %0) !dbg !220 {
entry:
  %andand = alloca i1, align 1, !dbg !221
  %c = alloca i32, align 4, !dbg !221
  store i32 %0, i32* %c, align 4, !dbg !221
  %c1 = load i32, i32* %c, align 4, !dbg !222
  %gteq = icmp sge i32 %c1, 48, !dbg !222
  store i1 %gteq, i1* %andand, align 1, !dbg !222
  br i1 %gteq, label %cond_jump_then, label %cond_jump_end, !dbg !222

cond_jump_then:                                   ; preds = %entry
  %c2 = load i32, i32* %c, align 4, !dbg !222
  %leeq = icmp sle i32 %c2, 57, !dbg !222
  %andand3 = and i1 %gteq, %leeq, !dbg !222
  store i1 %andand3, i1* %andand, align 1, !dbg !222
  br label %cond_jump_end, !dbg !222

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %andand_result_value = load i1, i1* %andand, align 1, !dbg !222
  ret i1 %andand_result_value, !dbg !222
}

define internal i1 @xiswalnum(i32 %0) !dbg !223 {
entry:
  %oror = alloca i1, align 1, !dbg !224
  %c = alloca i32, align 4, !dbg !224
  store i32 %0, i32* %c, align 4, !dbg !224
  %c1 = load i32, i32* %c, align 4, !dbg !225
  %fun_result = call i1 @xiswalpha(i32 %c1), !dbg !225
  store i1 %fun_result, i1* %oror, align 1, !dbg !225
  br i1 %fun_result, label %cond_jump_end, label %cond_jump_then, !dbg !225

cond_jump_then:                                   ; preds = %entry
  %c2 = load i32, i32* %c, align 4, !dbg !225
  %fun_result3 = call i1 @xiswdigit(i32 %c2), !dbg !225
  %oror4 = or i1 %fun_result, %fun_result3, !dbg !225
  store i1 %oror4, i1* %oror, align 1, !dbg !225
  br label %cond_jump_end, !dbg !225

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %oror_result_value = load i1, i1* %oror, align 1, !dbg !225
  ret i1 %oror_result_value, !dbg !225
}

define internal i8* @xbasename(i8* %0) !dbg !226 {
entry:
  %result44 = alloca i8*, align 8, !dbg !227
  %len40 = alloca i32, align 4, !dbg !227
  %result = alloca i8*, align 8, !dbg !227
  %len = alloca i32, align 4, !dbg !227
  %p = alloca i8*, align 8, !dbg !227
  %path = alloca i8*, align 8, !dbg !227
  store i8* %0, i8** %path, align 8, !dbg !227
  %path1 = load i8*, i8** %path, align 8, !dbg !228
  %path2 = load i8*, i8** %path, align 8, !dbg !228
  %fun_result = call i64 @strlen(i8* %path2), !dbg !228
  %ptrToIntC = ptrtoint i8* %path1 to i64, !dbg !228
  %mul = mul i64 %fun_result, 1, !dbg !228
  %add = add i64 %ptrToIntC, %mul, !dbg !228
  %intToPtr = inttoptr i64 %add to i8*, !dbg !228
  store i8* %intToPtr, i8** %p, align 8, !dbg !227
  br label %loop_top_block, !dbg !229

loop_top_block:                                   ; preds = %cond_end, %entry
  %p3 = load i8*, i8** %p, align 8, !dbg !230
  %path4 = load i8*, i8** %path, align 8, !dbg !230
  %gteq = icmp sge i8* %p3, %path4, !dbg !230
  br i1 %gteq, label %cond_then_block, label %cond_end_block, !dbg !230

cond_then_block:                                  ; preds = %loop_top_block
  %p5 = load i8*, i8** %p, align 8, !dbg !231
  %derefference_value = load i8, i8* %p5, align 1, !dbg !231
  %eq = icmp eq i8 %derefference_value, 47, !dbg !231
  br i1 %eq, label %cond_jump_then, label %cond_else_block, !dbg !231

cond_end_block:                                   ; preds = %cond_jump_then, %loop_top_block
  %p10 = load i8*, i8** %p, align 8, !dbg !229
  %path11 = load i8*, i8** %path, align 8, !dbg !229
  %le = icmp slt i8* %p10, %path11, !dbg !229
  br i1 %le, label %cond_jump_then12, label %cond_else_block13, !dbg !229

cond_jump_then:                                   ; preds = %cond_then_block
  br label %cond_end_block, !dbg !232

cond_else_block:                                  ; preds = %cond_then_block
  %p6 = load i8*, i8** %p, align 8, !dbg !233
  %ptrToIntI = ptrtoint i8* %p6 to i64, !dbg !233
  %sub = sub i64 %ptrToIntI, 1, !dbg !233
  %iintToPtr = inttoptr i64 %sub to i8*, !dbg !233
  store i8* %iintToPtr, i8** %p, align 8, !dbg !233
  %ptrToIntC7 = ptrtoint i8* %iintToPtr to i64, !dbg !233
  %add8 = add i64 %ptrToIntC7, 1, !dbg !233
  %intToPtr9 = inttoptr i64 %add8 to i8*, !dbg !233
  br label %cond_end, !dbg !233

cond_end:                                         ; preds = %cond_else_block, %after_break
  br label %loop_top_block, !dbg !233

after_break:                                      ; No predecessors!
  br label %cond_end, !dbg !232

cond_jump_then12:                                 ; preds = %cond_end_block
  %path15 = load i8*, i8** %path, align 8, !dbg !234
  br label %string, !dbg !234

cond_else_block13:                                ; preds = %cond_end_block
  %p28 = load i8*, i8** %p, align 8, !dbg !235
  %ptrToIntC29 = ptrtoint i8* %p28 to i64, !dbg !235
  %add30 = add i64 %ptrToIntC29, 1, !dbg !235
  %intToPtr31 = inttoptr i64 %add30 to i8*, !dbg !235
  br label %string32, !dbg !235

cond_end14:                                       ; No predecessors!
  ret i8* null, !dbg !227

string:                                           ; preds = %cond_jump_then12
  %inline_result_variable = alloca i8*, align 8, !dbg !234
  %str = alloca i8*, align 8, !dbg !234
  store i8* %path15, i8** %str, align 8, !dbg !234
  %str16 = load i8*, i8** %str, align 8, !dbg !234
  %fun_result17 = call i64 @strlen(i8* %str16), !dbg !234
  %add18 = add i64 %fun_result17, 1, !dbg !234
  %icastM = trunc i64 %add18 to i32, !dbg !234
  store i32 %icastM, i32* %len, align 4, !dbg !227
  %len19 = load i32, i32* %len, align 4, !dbg !227
  %icastD = sext i32 %len19 to i64, !dbg !227
  %fun_result20 = call i8* @nccalloc(i64 %icastD, i64 1), !dbg !227
  store i8* %fun_result20, i8** %result, align 8, !dbg !227
  %result21 = load i8*, i8** %result, align 8, !dbg !227
  %str22 = load i8*, i8** %str, align 8, !dbg !227
  %len23 = load i32, i32* %len, align 4, !dbg !227
  %icastD24 = sext i32 %len23 to i64, !dbg !227
  %fun_result25 = call i8* @strncpy(i8* %result21, i8* %str22, i64 %icastD24), !dbg !227
  %result26 = load i8*, i8** %result, align 8, !dbg !227
  store i8* %result26, i8** %inline_result_variable, align 8, !dbg !227
  br label %string_end, !dbg !227

string_end:                                       ; preds = %string
  %inline_result_variable27 = load i8*, i8** %inline_result_variable, align 8, !dbg !227
  ret i8* %inline_result_variable27, !dbg !227

string32:                                         ; preds = %cond_else_block13
  %inline_result_variable33 = alloca i8*, align 8, !dbg !235
  %str34 = alloca i8*, align 8, !dbg !235
  store i8* %intToPtr31, i8** %str34, align 8, !dbg !235
  %str36 = load i8*, i8** %str34, align 8, !dbg !235
  %fun_result37 = call i64 @strlen(i8* %str36), !dbg !235
  %add38 = add i64 %fun_result37, 1, !dbg !235
  %icastM39 = trunc i64 %add38 to i32, !dbg !235
  store i32 %icastM39, i32* %len40, align 4, !dbg !227
  %len41 = load i32, i32* %len40, align 4, !dbg !227
  %icastD42 = sext i32 %len41 to i64, !dbg !227
  %fun_result43 = call i8* @nccalloc(i64 %icastD42, i64 1), !dbg !227
  store i8* %fun_result43, i8** %result44, align 8, !dbg !227
  %result45 = load i8*, i8** %result44, align 8, !dbg !227
  %str46 = load i8*, i8** %str34, align 8, !dbg !227
  %len47 = load i32, i32* %len40, align 4, !dbg !227
  %icastD48 = sext i32 %len47 to i64, !dbg !227
  %fun_result49 = call i8* @strncpy(i8* %result45, i8* %str46, i64 %icastD48), !dbg !227
  %result50 = load i8*, i8** %result44, align 8, !dbg !227
  store i8* %result50, i8** %inline_result_variable33, align 8, !dbg !227
  br label %string_end35, !dbg !227

string_end35:                                     ; preds = %string32
  %inline_result_variable51 = load i8*, i8** %inline_result_variable33, align 8, !dbg !227
  ret i8* %inline_result_variable51, !dbg !227
}

define internal i8* @xextname(i8* %0) !dbg !236 {
entry:
  %result44 = alloca i8*, align 8, !dbg !237
  %len40 = alloca i32, align 4, !dbg !237
  %result = alloca i8*, align 8, !dbg !237
  %len = alloca i32, align 4, !dbg !237
  %p = alloca i8*, align 8, !dbg !237
  %path = alloca i8*, align 8, !dbg !237
  store i8* %0, i8** %path, align 8, !dbg !237
  %path1 = load i8*, i8** %path, align 8, !dbg !238
  %path2 = load i8*, i8** %path, align 8, !dbg !238
  %fun_result = call i64 @strlen(i8* %path2), !dbg !238
  %ptrToIntC = ptrtoint i8* %path1 to i64, !dbg !238
  %mul = mul i64 %fun_result, 1, !dbg !238
  %add = add i64 %ptrToIntC, %mul, !dbg !238
  %intToPtr = inttoptr i64 %add to i8*, !dbg !238
  store i8* %intToPtr, i8** %p, align 8, !dbg !237
  br label %loop_top_block, !dbg !239

loop_top_block:                                   ; preds = %cond_end, %entry
  %p3 = load i8*, i8** %p, align 8, !dbg !240
  %path4 = load i8*, i8** %path, align 8, !dbg !240
  %gteq = icmp sge i8* %p3, %path4, !dbg !240
  br i1 %gteq, label %cond_then_block, label %cond_end_block, !dbg !240

cond_then_block:                                  ; preds = %loop_top_block
  %p5 = load i8*, i8** %p, align 8, !dbg !241
  %derefference_value = load i8, i8* %p5, align 1, !dbg !241
  %eq = icmp eq i8 %derefference_value, 46, !dbg !241
  br i1 %eq, label %cond_jump_then, label %cond_else_block, !dbg !241

cond_end_block:                                   ; preds = %cond_jump_then, %loop_top_block
  %p10 = load i8*, i8** %p, align 8, !dbg !239
  %path11 = load i8*, i8** %path, align 8, !dbg !239
  %le = icmp slt i8* %p10, %path11, !dbg !239
  br i1 %le, label %cond_jump_then12, label %cond_else_block13, !dbg !239

cond_jump_then:                                   ; preds = %cond_then_block
  br label %cond_end_block, !dbg !242

cond_else_block:                                  ; preds = %cond_then_block
  %p6 = load i8*, i8** %p, align 8, !dbg !243
  %ptrToIntI = ptrtoint i8* %p6 to i64, !dbg !243
  %sub = sub i64 %ptrToIntI, 1, !dbg !243
  %iintToPtr = inttoptr i64 %sub to i8*, !dbg !243
  store i8* %iintToPtr, i8** %p, align 8, !dbg !243
  %ptrToIntC7 = ptrtoint i8* %iintToPtr to i64, !dbg !243
  %add8 = add i64 %ptrToIntC7, 1, !dbg !243
  %intToPtr9 = inttoptr i64 %add8 to i8*, !dbg !243
  br label %cond_end, !dbg !243

cond_end:                                         ; preds = %cond_else_block, %after_break
  br label %loop_top_block, !dbg !243

after_break:                                      ; No predecessors!
  br label %cond_end, !dbg !242

cond_jump_then12:                                 ; preds = %cond_end_block
  %path15 = load i8*, i8** %path, align 8, !dbg !244
  br label %string, !dbg !244

cond_else_block13:                                ; preds = %cond_end_block
  %p28 = load i8*, i8** %p, align 8, !dbg !245
  %ptrToIntC29 = ptrtoint i8* %p28 to i64, !dbg !245
  %add30 = add i64 %ptrToIntC29, 1, !dbg !245
  %intToPtr31 = inttoptr i64 %add30 to i8*, !dbg !245
  br label %string32, !dbg !245

cond_end14:                                       ; No predecessors!
  ret i8* null, !dbg !237

string:                                           ; preds = %cond_jump_then12
  %inline_result_variable = alloca i8*, align 8, !dbg !244
  %str = alloca i8*, align 8, !dbg !244
  store i8* %path15, i8** %str, align 8, !dbg !244
  %str16 = load i8*, i8** %str, align 8, !dbg !244
  %fun_result17 = call i64 @strlen(i8* %str16), !dbg !244
  %add18 = add i64 %fun_result17, 1, !dbg !244
  %icastM = trunc i64 %add18 to i32, !dbg !244
  store i32 %icastM, i32* %len, align 4, !dbg !237
  %len19 = load i32, i32* %len, align 4, !dbg !237
  %icastD = sext i32 %len19 to i64, !dbg !237
  %fun_result20 = call i8* @nccalloc(i64 %icastD, i64 1), !dbg !237
  store i8* %fun_result20, i8** %result, align 8, !dbg !237
  %result21 = load i8*, i8** %result, align 8, !dbg !237
  %str22 = load i8*, i8** %str, align 8, !dbg !237
  %len23 = load i32, i32* %len, align 4, !dbg !237
  %icastD24 = sext i32 %len23 to i64, !dbg !237
  %fun_result25 = call i8* @strncpy(i8* %result21, i8* %str22, i64 %icastD24), !dbg !237
  %result26 = load i8*, i8** %result, align 8, !dbg !237
  store i8* %result26, i8** %inline_result_variable, align 8, !dbg !237
  br label %string_end, !dbg !237

string_end:                                       ; preds = %string
  %inline_result_variable27 = load i8*, i8** %inline_result_variable, align 8, !dbg !237
  ret i8* %inline_result_variable27, !dbg !237

string32:                                         ; preds = %cond_else_block13
  %inline_result_variable33 = alloca i8*, align 8, !dbg !245
  %str34 = alloca i8*, align 8, !dbg !245
  store i8* %intToPtr31, i8** %str34, align 8, !dbg !245
  %str36 = load i8*, i8** %str34, align 8, !dbg !245
  %fun_result37 = call i64 @strlen(i8* %str36), !dbg !245
  %add38 = add i64 %fun_result37, 1, !dbg !245
  %icastM39 = trunc i64 %add38 to i32, !dbg !245
  store i32 %icastM39, i32* %len40, align 4, !dbg !237
  %len41 = load i32, i32* %len40, align 4, !dbg !237
  %icastD42 = sext i32 %len41 to i64, !dbg !237
  %fun_result43 = call i8* @nccalloc(i64 %icastD42, i64 1), !dbg !237
  store i8* %fun_result43, i8** %result44, align 8, !dbg !237
  %result45 = load i8*, i8** %result44, align 8, !dbg !237
  %str46 = load i8*, i8** %str34, align 8, !dbg !237
  %len47 = load i32, i32* %len40, align 4, !dbg !237
  %icastD48 = sext i32 %len47 to i64, !dbg !237
  %fun_result49 = call i8* @strncpy(i8* %result45, i8* %str46, i64 %icastD48), !dbg !237
  %result50 = load i8*, i8** %result44, align 8, !dbg !237
  store i8* %result50, i8** %inline_result_variable33, align 8, !dbg !237
  br label %string_end35, !dbg !237

string_end35:                                     ; preds = %string32
  %inline_result_variable51 = load i8*, i8** %inline_result_variable33, align 8, !dbg !237
  ret i8* %inline_result_variable51, !dbg !237
}

define internal i8* @xrealpath(i8* %0) !dbg !246 {
entry:
  %result215 = alloca i8*, align 8, !dbg !247
  %result7 = alloca i8*, align 8, !dbg !247
  %len = alloca i32, align 4, !dbg !247
  %result = alloca i8*, align 8, !dbg !247
  %path = alloca i8*, align 8, !dbg !247
  store i8* %0, i8** %path, align 8, !dbg !247
  %path1 = load i8*, i8** %path, align 8, !dbg !248
  %fun_result = call i8* @realpath(i8* %path1, i8* null), !dbg !248
  store i8* %fun_result, i8** %result, align 8, !dbg !247
  %result2 = load i8*, i8** %result, align 8, !dbg !249
  br label %string, !dbg !249

string:                                           ; preds = %entry
  %inline_result_variable = alloca i8*, align 8, !dbg !249
  %str = alloca i8*, align 8, !dbg !249
  store i8* %result2, i8** %str, align 8, !dbg !249
  %str3 = load i8*, i8** %str, align 8, !dbg !249
  %fun_result4 = call i64 @strlen(i8* %str3), !dbg !249
  %add = add i64 %fun_result4, 1, !dbg !249
  %icastM = trunc i64 %add to i32, !dbg !249
  store i32 %icastM, i32* %len, align 4, !dbg !247
  %len5 = load i32, i32* %len, align 4, !dbg !247
  %icastD = sext i32 %len5 to i64, !dbg !247
  %fun_result6 = call i8* @nccalloc(i64 %icastD, i64 1), !dbg !247
  store i8* %fun_result6, i8** %result7, align 8, !dbg !247
  %result8 = load i8*, i8** %result7, align 8, !dbg !247
  %str9 = load i8*, i8** %str, align 8, !dbg !247
  %len10 = load i32, i32* %len, align 4, !dbg !247
  %icastD11 = sext i32 %len10 to i64, !dbg !247
  %fun_result12 = call i8* @strncpy(i8* %result8, i8* %str9, i64 %icastD11), !dbg !247
  %result13 = load i8*, i8** %result7, align 8, !dbg !247
  store i8* %result13, i8** %inline_result_variable, align 8, !dbg !247
  br label %string_end, !dbg !247

string_end:                                       ; preds = %string
  %inline_result_variable14 = load i8*, i8** %inline_result_variable, align 8, !dbg !247
  store i8* %inline_result_variable14, i8** %result215, align 8, !dbg !247
  %result16 = load i8*, i8** %result, align 8, !dbg !250
  call void @free(i8* %result16), !dbg !250
  %result217 = load i8*, i8** %result215, align 8, !dbg !251
  ret i8* %result217, !dbg !251
}

declare void @sVar_finalize()

declare void @sFunction_finalize()

declare i1 @vm(%buffer*)

declare i1 @expression_v1(%sNode**, %sParserInfo*)

declare i1 @compile_v1(%sNode*, %buffer*, %sParserInfo*)

declare void @sNode_finalize_v1(%sNode*)

declare %sNode* @exp_node_v1(%sParserInfo*)

declare void @skip_spaces(%sParserInfo*)

declare i1 @expression(%sNode**, %sParserInfo*)

declare i1 @compile_v2(%sNode*, %buffer*, %sParserInfo*)

declare void @sNode_finalize_v2(%sNode*)

define i1 @compile(%sNode* %0, %buffer* %1, %sParserInfo* %2) !dbg !252 {
entry:
  %node = alloca %sNode*, align 8, !dbg !255
  store %sNode* %0, %sNode** %node, align 8, !dbg !255
  %codes = alloca %buffer*, align 8, !dbg !255
  store %buffer* %1, %buffer** %codes, align 8, !dbg !255
  %info = alloca %sParserInfo*, align 8, !dbg !255
  store %sParserInfo* %2, %sParserInfo** %info, align 8, !dbg !255
  %node1 = load %sNode*, %sNode** %node, align 8, !dbg !256
  %codes2 = load %buffer*, %buffer** %codes, align 8, !dbg !256
  %info3 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !256
  %fun_result = call i1 @compile_v2(%sNode* %node1, %buffer* %codes2, %sParserInfo* %info3), !dbg !256
  %node4 = load %sNode*, %sNode** %node, align 8, !dbg !257
  %field = getelementptr inbounds %sNode, %sNode* %node4, i32 0, i32 0, !dbg !257
  %kind = load i32, i32* %field, align 4, !dbg !257
  %eq = icmp eq i32 %kind, 3, !dbg !257
  br i1 %eq, label %cond_jump_then, label %cond_end, !dbg !257

cond_jump_then:                                   ; preds = %entry
  %codes5 = load %buffer*, %buffer** %codes, align 8, !dbg !258
  call void @buffer_append_int(%buffer* %codes5, i32 4), !dbg !258
  %codes6 = load %buffer*, %buffer** %codes, align 8, !dbg !259
  %node7 = load %sNode*, %sNode** %node, align 8, !dbg !259
  %field8 = getelementptr inbounds %sNode, %sNode* %node7, i32 0, i32 3, !dbg !259
  %value = load %come_anon69, %come_anon69* %field8, align 8, !dbg !259
  %field9 = getelementptr inbounds %come_anon69, %come_anon69* %field8, i32 0, i32 0, !dbg !259
  %icastO = bitcast %come_anon70* %field9 to i8**, !dbg !259
  %stringValue = load i8*, i8** %icastO, align 8, !dbg !259
  call void @buffer_append_str(%buffer* %codes6, i8* %stringValue), !dbg !259
  %codes10 = load %buffer*, %buffer** %codes, align 8, !dbg !260
  br label %cond_end, !dbg !260

cond_end:                                         ; preds = %cond_jump_then, %entry
  ret i1 true, !dbg !261
}

define void @sNode_finalize(%sNode* %0) !dbg !262 {
entry:
  %self = alloca %sNode*, align 8, !dbg !263
  store %sNode* %0, %sNode** %self, align 8, !dbg !263
  %self1 = load %sNode*, %sNode** %self, align 8, !dbg !264
  call void @sNode_finalize_v2(%sNode* %self1), !dbg !264
  %self2 = load %sNode*, %sNode** %self, align 8, !dbg !265
  %field = getelementptr inbounds %sNode, %sNode* %self2, i32 0, i32 0, !dbg !265
  %kind = load i32, i32* %field, align 4, !dbg !265
  %eq = icmp eq i32 %kind, 3, !dbg !265
  br i1 %eq, label %cond_jump_then, label %cond_end, !dbg !265

cond_jump_then:                                   ; preds = %entry
  %self3 = load %sNode*, %sNode** %self, align 8, !dbg !266
  %field4 = getelementptr inbounds %sNode, %sNode* %self3, i32 0, i32 3, !dbg !266
  %value = load %come_anon69, %come_anon69* %field4, align 8, !dbg !266
  %field5 = getelementptr inbounds %come_anon69, %come_anon69* %field4, i32 0, i32 0, !dbg !266
  %icastO = bitcast %come_anon70* %field5 to i8**, !dbg !266
  %stringValue = load i8*, i8** %icastO, align 8, !dbg !266
  call void @free(i8* %stringValue), !dbg !266
  br label %cond_end, !dbg !266

cond_end:                                         ; preds = %cond_jump_then, %entry
  ret void, !dbg !266
}

define %sNode* @exp_node(%sParserInfo* %0) !dbg !267 {
entry:
  %buf141 = alloca %buffer*, align 8, !dbg !268
  %buf = alloca %buffer*, align 8, !dbg !268
  %result = alloca %sNode*, align 8, !dbg !268
  %info = alloca %sParserInfo*, align 8, !dbg !268
  store %sParserInfo* %0, %sParserInfo** %info, align 8, !dbg !268
  %info1 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !269
  %fun_result = call %sNode* @exp_node_v1(%sParserInfo* %info1), !dbg !269
  store %sNode* %fun_result, %sNode** %result, align 8, !dbg !268
  %result2 = load %sNode*, %sNode** %result, align 8, !dbg !270
  %eq = icmp eq %sNode* %result2, null, !dbg !270
  br i1 %eq, label %cond_jump_then, label %cond_end, !dbg !270

cond_jump_then:                                   ; preds = %entry
  %info3 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !271
  %field = getelementptr inbounds %sParserInfo, %sParserInfo* %info3, i32 0, i32 0, !dbg !271
  %p = load i8*, i8** %field, align 8, !dbg !271
  %derefference_value = load i8, i8* %p, align 1, !dbg !271
  %eq4 = icmp eq i8 %derefference_value, 34, !dbg !271
  br i1 %eq4, label %cond_jump_then5, label %cond_jump_elif0, !dbg !271

cond_end:                                         ; preds = %cond_end6, %entry
  %result261 = load %sNode*, %sNode** %result, align 8, !dbg !272
  ret %sNode* %result261, !dbg !272

cond_jump_then5:                                  ; preds = %cond_jump_then
  %info7 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !273
  %info8 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !273
  %field9 = getelementptr inbounds %sParserInfo, %sParserInfo* %info8, i32 0, i32 0, !dbg !273
  %p10 = load i8*, i8** %field9, align 8, !dbg !273
  %ptrToIntC = ptrtoint i8* %p10 to i64, !dbg !273
  %add = add i64 %ptrToIntC, 1, !dbg !273
  %intToPtr = inttoptr i64 %add to i8*, !dbg !273
  %field11 = getelementptr inbounds %sParserInfo, %sParserInfo* %info7, i32 0, i32 0, !dbg !273
  store i8* %intToPtr, i8** %field11, align 8, !dbg !273
  %ptrToIntI = ptrtoint i8* %intToPtr to i64, !dbg !273
  %sub = sub i64 %ptrToIntI, 1, !dbg !273
  %iintToPtr = inttoptr i64 %sub to i8*, !dbg !273
  %fun_result12 = call i8* @calloc(i64 1, i64 16), !dbg !274
  %obj = bitcast i8* %fun_result12 to %buffer*, !dbg !274
  %fun_result13 = call %buffer* @buffer_initialize(%buffer* %obj), !dbg !274
  store %buffer* %fun_result13, %buffer** %buf, align 8, !dbg !268
  br label %loop_top_block, !dbg !275

cond_jump_elif0:                                  ; preds = %cond_jump_then
  %info122 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !276
  %field123 = getelementptr inbounds %sParserInfo, %sParserInfo* %info122, i32 0, i32 0, !dbg !276
  %p124 = load i8*, i8** %field123, align 8, !dbg !276
  %derefference_value125 = load i8, i8* %p124, align 1, !dbg !276
  %eq126 = icmp eq i8 %derefference_value125, 39, !dbg !276
  br i1 %eq126, label %cond_jump_elif_then0, label %cond_end6, !dbg !276

cond_jump_elif_then0:                             ; preds = %cond_jump_elif0
  %info127 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !277
  %info128 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !277
  %field129 = getelementptr inbounds %sParserInfo, %sParserInfo* %info128, i32 0, i32 0, !dbg !277
  %p130 = load i8*, i8** %field129, align 8, !dbg !277
  %ptrToIntC131 = ptrtoint i8* %p130 to i64, !dbg !277
  %add132 = add i64 %ptrToIntC131, 1, !dbg !277
  %intToPtr133 = inttoptr i64 %add132 to i8*, !dbg !277
  %field134 = getelementptr inbounds %sParserInfo, %sParserInfo* %info127, i32 0, i32 0, !dbg !277
  store i8* %intToPtr133, i8** %field134, align 8, !dbg !277
  %ptrToIntI135 = ptrtoint i8* %intToPtr133 to i64, !dbg !277
  %sub136 = sub i64 %ptrToIntI135, 1, !dbg !277
  %iintToPtr137 = inttoptr i64 %sub136 to i8*, !dbg !277
  %fun_result138 = call i8* @calloc(i64 1, i64 16), !dbg !278
  %obj139 = bitcast i8* %fun_result138 to %buffer*, !dbg !278
  %fun_result140 = call %buffer* @buffer_initialize(%buffer* %obj139), !dbg !278
  store %buffer* %fun_result140, %buffer** %buf141, align 8, !dbg !268
  br label %loop_top_block142, !dbg !279

cond_end6:                                        ; preds = %cond_jump_elif0
  br label %cond_end, !dbg !279

loop_top_block:                                   ; preds = %cond_end22, %cond_jump_then5
  br i1 true, label %cond_then_block, label %cond_end_block, !dbg !280

cond_then_block:                                  ; preds = %loop_top_block
  %info14 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !281
  %field15 = getelementptr inbounds %sParserInfo, %sParserInfo* %info14, i32 0, i32 0, !dbg !281
  %p16 = load i8*, i8** %field15, align 8, !dbg !281
  %derefference_value17 = load i8, i8* %p16, align 1, !dbg !281
  %eq18 = icmp eq i8 %derefference_value17, 0, !dbg !281
  br i1 %eq18, label %cond_jump_then19, label %cond_jump_elif020, !dbg !281

cond_end_block:                                   ; preds = %cond_jump_elif_then1, %loop_top_block
  %buf116 = load %buffer*, %buffer** %buf, align 8, !dbg !275
  %fun_result117 = call i8* @buffer_to_string(%buffer* %buf116), !dbg !275
  %info118 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !275
  %fun_result119 = call %sNode* @create_string_node(i8* %fun_result117, %sParserInfo* %info118), !dbg !275
  call void @free(i8* %fun_result117), !dbg !275
  %obj120 = load %buffer*, %buffer** %buf, align 8, !dbg !275
  call void @buffer_finalize(%buffer* %obj120), !dbg !275
  %castAK121 = bitcast %buffer* %obj120 to i8*, !dbg !275
  call void @free(i8* %castAK121), !dbg !275
  ret %sNode* %fun_result119, !dbg !275

cond_jump_then19:                                 ; preds = %cond_then_block
  %stderr = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !282
  %info23 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !282
  %field24 = getelementptr inbounds %sParserInfo, %sParserInfo* %info23, i32 0, i32 2, !dbg !282
  %fname = load i8*, i8** %field24, align 8, !dbg !282
  %info25 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !282
  %field26 = getelementptr inbounds %sParserInfo, %sParserInfo* %info25, i32 0, i32 1, !dbg !282
  %sline = load i32, i32* %field26, align 4, !dbg !282
  %fun_result27 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @"%s %d: the source end", i32 0, i32 0), i8* %fname, i32 %sline), !dbg !282
  %obj28 = load %buffer*, %buffer** %buf, align 8, !dbg !283
  call void @buffer_finalize(%buffer* %obj28), !dbg !283
  %castAK = bitcast %buffer* %obj28 to i8*, !dbg !283
  call void @free(i8* %castAK), !dbg !283
  ret %sNode* null, !dbg !283

cond_jump_elif020:                                ; preds = %cond_then_block
  %info29 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !284
  %field30 = getelementptr inbounds %sParserInfo, %sParserInfo* %info29, i32 0, i32 0, !dbg !284
  %p31 = load i8*, i8** %field30, align 8, !dbg !284
  %derefference_value32 = load i8, i8* %p31, align 1, !dbg !284
  %eq33 = icmp eq i8 %derefference_value32, 92, !dbg !284
  br i1 %eq33, label %cond_jump_elif_then021, label %cond_jump_elif1, !dbg !284

cond_jump_elif_then021:                           ; preds = %cond_jump_elif020
  %buf34 = load %buffer*, %buffer** %buf, align 8, !dbg !285
  %info35 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !285
  %field36 = getelementptr inbounds %sParserInfo, %sParserInfo* %info35, i32 0, i32 0, !dbg !285
  %p37 = load i8*, i8** %field36, align 8, !dbg !285
  %derefference_value38 = load i8, i8* %p37, align 1, !dbg !285
  call void @buffer_append_char(%buffer* %buf34, i8 %derefference_value38), !dbg !285
  %info39 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !286
  %info40 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !286
  %field41 = getelementptr inbounds %sParserInfo, %sParserInfo* %info40, i32 0, i32 0, !dbg !286
  %p42 = load i8*, i8** %field41, align 8, !dbg !286
  %ptrToIntC43 = ptrtoint i8* %p42 to i64, !dbg !286
  %add44 = add i64 %ptrToIntC43, 1, !dbg !286
  %intToPtr45 = inttoptr i64 %add44 to i8*, !dbg !286
  %field46 = getelementptr inbounds %sParserInfo, %sParserInfo* %info39, i32 0, i32 0, !dbg !286
  store i8* %intToPtr45, i8** %field46, align 8, !dbg !286
  %ptrToIntI47 = ptrtoint i8* %intToPtr45 to i64, !dbg !286
  %sub48 = sub i64 %ptrToIntI47, 1, !dbg !286
  %iintToPtr49 = inttoptr i64 %sub48 to i8*, !dbg !286
  %info50 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !287
  %field51 = getelementptr inbounds %sParserInfo, %sParserInfo* %info50, i32 0, i32 0, !dbg !287
  %p52 = load i8*, i8** %field51, align 8, !dbg !287
  %derefference_value53 = load i8, i8* %p52, align 1, !dbg !287
  %eq54 = icmp eq i8 %derefference_value53, 0, !dbg !287
  br i1 %eq54, label %cond_jump_then55, label %cond_end56, !dbg !287

cond_jump_elif1:                                  ; preds = %cond_jump_elif020
  %info83 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !288
  %field84 = getelementptr inbounds %sParserInfo, %sParserInfo* %info83, i32 0, i32 0, !dbg !288
  %p85 = load i8*, i8** %field84, align 8, !dbg !288
  %derefference_value86 = load i8, i8* %p85, align 1, !dbg !288
  %eq87 = icmp eq i8 %derefference_value86, 34, !dbg !288
  br i1 %eq87, label %cond_jump_elif_then1, label %cond_else_block, !dbg !288

cond_jump_elif_then1:                             ; preds = %cond_jump_elif1
  %info88 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !289
  %info89 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !289
  %field90 = getelementptr inbounds %sParserInfo, %sParserInfo* %info89, i32 0, i32 0, !dbg !289
  %p91 = load i8*, i8** %field90, align 8, !dbg !289
  %ptrToIntC92 = ptrtoint i8* %p91 to i64, !dbg !289
  %add93 = add i64 %ptrToIntC92, 1, !dbg !289
  %intToPtr94 = inttoptr i64 %add93 to i8*, !dbg !289
  %field95 = getelementptr inbounds %sParserInfo, %sParserInfo* %info88, i32 0, i32 0, !dbg !289
  store i8* %intToPtr94, i8** %field95, align 8, !dbg !289
  %ptrToIntI96 = ptrtoint i8* %intToPtr94 to i64, !dbg !289
  %sub97 = sub i64 %ptrToIntI96, 1, !dbg !289
  %iintToPtr98 = inttoptr i64 %sub97 to i8*, !dbg !289
  %info99 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !289
  call void @skip_spaces(%sParserInfo* %info99), !dbg !289
  br label %cond_end_block, !dbg !290

cond_else_block:                                  ; preds = %cond_jump_elif1
  %buf100 = load %buffer*, %buffer** %buf, align 8, !dbg !291
  %info101 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !291
  %field102 = getelementptr inbounds %sParserInfo, %sParserInfo* %info101, i32 0, i32 0, !dbg !291
  %p103 = load i8*, i8** %field102, align 8, !dbg !291
  %derefference_value104 = load i8, i8* %p103, align 1, !dbg !291
  call void @buffer_append_char(%buffer* %buf100, i8 %derefference_value104), !dbg !291
  %info105 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !292
  %info106 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !292
  %field107 = getelementptr inbounds %sParserInfo, %sParserInfo* %info106, i32 0, i32 0, !dbg !292
  %p108 = load i8*, i8** %field107, align 8, !dbg !292
  %ptrToIntC109 = ptrtoint i8* %p108 to i64, !dbg !292
  %add110 = add i64 %ptrToIntC109, 1, !dbg !292
  %intToPtr111 = inttoptr i64 %add110 to i8*, !dbg !292
  %field112 = getelementptr inbounds %sParserInfo, %sParserInfo* %info105, i32 0, i32 0, !dbg !292
  store i8* %intToPtr111, i8** %field112, align 8, !dbg !292
  %ptrToIntI113 = ptrtoint i8* %intToPtr111 to i64, !dbg !292
  %sub114 = sub i64 %ptrToIntI113, 1, !dbg !292
  %iintToPtr115 = inttoptr i64 %sub114 to i8*, !dbg !292
  br label %cond_end22, !dbg !292

cond_end22:                                       ; preds = %cond_else_block, %after_break, %cond_end56
  br label %loop_top_block, !dbg !292

cond_jump_then55:                                 ; preds = %cond_jump_elif_then021
  %stderr57 = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !293
  %info58 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !293
  %field59 = getelementptr inbounds %sParserInfo, %sParserInfo* %info58, i32 0, i32 2, !dbg !293
  %fname60 = load i8*, i8** %field59, align 8, !dbg !293
  %info61 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !293
  %field62 = getelementptr inbounds %sParserInfo, %sParserInfo* %info61, i32 0, i32 1, !dbg !293
  %sline63 = load i32, i32* %field62, align 4, !dbg !293
  %fun_result64 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr57, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @"%s %d: the source end.1", i32 0, i32 0), i8* %fname60, i32 %sline63), !dbg !293
  %obj65 = load %buffer*, %buffer** %buf, align 8, !dbg !294
  call void @buffer_finalize(%buffer* %obj65), !dbg !294
  %castAK66 = bitcast %buffer* %obj65 to i8*, !dbg !294
  call void @free(i8* %castAK66), !dbg !294
  ret %sNode* null, !dbg !294

cond_end56:                                       ; preds = %cond_jump_elif_then021
  %buf67 = load %buffer*, %buffer** %buf, align 8, !dbg !295
  %info68 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !295
  %field69 = getelementptr inbounds %sParserInfo, %sParserInfo* %info68, i32 0, i32 0, !dbg !295
  %p70 = load i8*, i8** %field69, align 8, !dbg !295
  %derefference_value71 = load i8, i8* %p70, align 1, !dbg !295
  call void @buffer_append_char(%buffer* %buf67, i8 %derefference_value71), !dbg !295
  %info72 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !296
  %info73 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !296
  %field74 = getelementptr inbounds %sParserInfo, %sParserInfo* %info73, i32 0, i32 0, !dbg !296
  %p75 = load i8*, i8** %field74, align 8, !dbg !296
  %ptrToIntC76 = ptrtoint i8* %p75 to i64, !dbg !296
  %add77 = add i64 %ptrToIntC76, 1, !dbg !296
  %intToPtr78 = inttoptr i64 %add77 to i8*, !dbg !296
  %field79 = getelementptr inbounds %sParserInfo, %sParserInfo* %info72, i32 0, i32 0, !dbg !296
  store i8* %intToPtr78, i8** %field79, align 8, !dbg !296
  %ptrToIntI80 = ptrtoint i8* %intToPtr78 to i64, !dbg !296
  %sub81 = sub i64 %ptrToIntI80, 1, !dbg !296
  %iintToPtr82 = inttoptr i64 %sub81 to i8*, !dbg !296
  br label %cond_end22, !dbg !296

after_break:                                      ; No predecessors!
  br label %cond_end22, !dbg !290

loop_top_block142:                                ; preds = %cond_end156, %cond_jump_elif_then0
  br i1 true, label %cond_then_block143, label %cond_end_block144, !dbg !297

cond_then_block143:                               ; preds = %loop_top_block142
  %info145 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !298
  %field146 = getelementptr inbounds %sParserInfo, %sParserInfo* %info145, i32 0, i32 0, !dbg !298
  %p147 = load i8*, i8** %field146, align 8, !dbg !298
  %derefference_value148 = load i8, i8* %p147, align 1, !dbg !298
  %eq149 = icmp eq i8 %derefference_value148, 0, !dbg !298
  br i1 %eq149, label %cond_jump_then150, label %cond_jump_elif0151, !dbg !298

cond_end_block144:                                ; preds = %cond_jump_elif_then1154, %loop_top_block142
  %buf255 = load %buffer*, %buffer** %buf141, align 8, !dbg !279
  %fun_result256 = call i8* @buffer_to_string(%buffer* %buf255), !dbg !279
  %info257 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !279
  %fun_result258 = call %sNode* @create_string_node(i8* %fun_result256, %sParserInfo* %info257), !dbg !279
  call void @free(i8* %fun_result256), !dbg !279
  %obj259 = load %buffer*, %buffer** %buf141, align 8, !dbg !279
  call void @buffer_finalize(%buffer* %obj259), !dbg !279
  %castAK260 = bitcast %buffer* %obj259 to i8*, !dbg !279
  call void @free(i8* %castAK260), !dbg !279
  ret %sNode* %fun_result258, !dbg !279

cond_jump_then150:                                ; preds = %cond_then_block143
  %stderr157 = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !299
  %info158 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !299
  %field159 = getelementptr inbounds %sParserInfo, %sParserInfo* %info158, i32 0, i32 2, !dbg !299
  %fname160 = load i8*, i8** %field159, align 8, !dbg !299
  %info161 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !299
  %field162 = getelementptr inbounds %sParserInfo, %sParserInfo* %info161, i32 0, i32 1, !dbg !299
  %sline163 = load i32, i32* %field162, align 4, !dbg !299
  %fun_result164 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr157, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @"%s %d: the source end.2", i32 0, i32 0), i8* %fname160, i32 %sline163), !dbg !299
  %obj165 = load %buffer*, %buffer** %buf141, align 8, !dbg !300
  call void @buffer_finalize(%buffer* %obj165), !dbg !300
  %castAK166 = bitcast %buffer* %obj165 to i8*, !dbg !300
  call void @free(i8* %castAK166), !dbg !300
  ret %sNode* null, !dbg !300

cond_jump_elif0151:                               ; preds = %cond_then_block143
  %info167 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !301
  %field168 = getelementptr inbounds %sParserInfo, %sParserInfo* %info167, i32 0, i32 0, !dbg !301
  %p169 = load i8*, i8** %field168, align 8, !dbg !301
  %derefference_value170 = load i8, i8* %p169, align 1, !dbg !301
  %eq171 = icmp eq i8 %derefference_value170, 92, !dbg !301
  br i1 %eq171, label %cond_jump_elif_then0152, label %cond_jump_elif1153, !dbg !301

cond_jump_elif_then0152:                          ; preds = %cond_jump_elif0151
  %buf172 = load %buffer*, %buffer** %buf141, align 8, !dbg !302
  %info173 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !302
  %field174 = getelementptr inbounds %sParserInfo, %sParserInfo* %info173, i32 0, i32 0, !dbg !302
  %p175 = load i8*, i8** %field174, align 8, !dbg !302
  %derefference_value176 = load i8, i8* %p175, align 1, !dbg !302
  call void @buffer_append_char(%buffer* %buf172, i8 %derefference_value176), !dbg !302
  %info177 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !303
  %info178 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !303
  %field179 = getelementptr inbounds %sParserInfo, %sParserInfo* %info178, i32 0, i32 0, !dbg !303
  %p180 = load i8*, i8** %field179, align 8, !dbg !303
  %ptrToIntC181 = ptrtoint i8* %p180 to i64, !dbg !303
  %add182 = add i64 %ptrToIntC181, 1, !dbg !303
  %intToPtr183 = inttoptr i64 %add182 to i8*, !dbg !303
  %field184 = getelementptr inbounds %sParserInfo, %sParserInfo* %info177, i32 0, i32 0, !dbg !303
  store i8* %intToPtr183, i8** %field184, align 8, !dbg !303
  %ptrToIntI185 = ptrtoint i8* %intToPtr183 to i64, !dbg !303
  %sub186 = sub i64 %ptrToIntI185, 1, !dbg !303
  %iintToPtr187 = inttoptr i64 %sub186 to i8*, !dbg !303
  %info188 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !304
  %field189 = getelementptr inbounds %sParserInfo, %sParserInfo* %info188, i32 0, i32 0, !dbg !304
  %p190 = load i8*, i8** %field189, align 8, !dbg !304
  %derefference_value191 = load i8, i8* %p190, align 1, !dbg !304
  %eq192 = icmp eq i8 %derefference_value191, 0, !dbg !304
  br i1 %eq192, label %cond_jump_then193, label %cond_end194, !dbg !304

cond_jump_elif1153:                               ; preds = %cond_jump_elif0151
  %info221 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !305
  %field222 = getelementptr inbounds %sParserInfo, %sParserInfo* %info221, i32 0, i32 0, !dbg !305
  %p223 = load i8*, i8** %field222, align 8, !dbg !305
  %derefference_value224 = load i8, i8* %p223, align 1, !dbg !305
  %eq225 = icmp eq i8 %derefference_value224, 39, !dbg !305
  br i1 %eq225, label %cond_jump_elif_then1154, label %cond_else_block155, !dbg !305

cond_jump_elif_then1154:                          ; preds = %cond_jump_elif1153
  %info226 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !306
  %info227 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !306
  %field228 = getelementptr inbounds %sParserInfo, %sParserInfo* %info227, i32 0, i32 0, !dbg !306
  %p229 = load i8*, i8** %field228, align 8, !dbg !306
  %ptrToIntC230 = ptrtoint i8* %p229 to i64, !dbg !306
  %add231 = add i64 %ptrToIntC230, 1, !dbg !306
  %intToPtr232 = inttoptr i64 %add231 to i8*, !dbg !306
  %field233 = getelementptr inbounds %sParserInfo, %sParserInfo* %info226, i32 0, i32 0, !dbg !306
  store i8* %intToPtr232, i8** %field233, align 8, !dbg !306
  %ptrToIntI234 = ptrtoint i8* %intToPtr232 to i64, !dbg !306
  %sub235 = sub i64 %ptrToIntI234, 1, !dbg !306
  %iintToPtr236 = inttoptr i64 %sub235 to i8*, !dbg !306
  %info237 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !306
  call void @skip_spaces(%sParserInfo* %info237), !dbg !306
  br label %cond_end_block144, !dbg !307

cond_else_block155:                               ; preds = %cond_jump_elif1153
  %buf239 = load %buffer*, %buffer** %buf141, align 8, !dbg !308
  %info240 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !308
  %field241 = getelementptr inbounds %sParserInfo, %sParserInfo* %info240, i32 0, i32 0, !dbg !308
  %p242 = load i8*, i8** %field241, align 8, !dbg !308
  %derefference_value243 = load i8, i8* %p242, align 1, !dbg !308
  call void @buffer_append_char(%buffer* %buf239, i8 %derefference_value243), !dbg !308
  %info244 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !309
  %info245 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !309
  %field246 = getelementptr inbounds %sParserInfo, %sParserInfo* %info245, i32 0, i32 0, !dbg !309
  %p247 = load i8*, i8** %field246, align 8, !dbg !309
  %ptrToIntC248 = ptrtoint i8* %p247 to i64, !dbg !309
  %add249 = add i64 %ptrToIntC248, 1, !dbg !309
  %intToPtr250 = inttoptr i64 %add249 to i8*, !dbg !309
  %field251 = getelementptr inbounds %sParserInfo, %sParserInfo* %info244, i32 0, i32 0, !dbg !309
  store i8* %intToPtr250, i8** %field251, align 8, !dbg !309
  %ptrToIntI252 = ptrtoint i8* %intToPtr250 to i64, !dbg !309
  %sub253 = sub i64 %ptrToIntI252, 1, !dbg !309
  %iintToPtr254 = inttoptr i64 %sub253 to i8*, !dbg !309
  br label %cond_end156, !dbg !309

cond_end156:                                      ; preds = %cond_else_block155, %after_break238, %cond_end194
  br label %loop_top_block142, !dbg !309

cond_jump_then193:                                ; preds = %cond_jump_elif_then0152
  %stderr195 = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !310
  %info196 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !310
  %field197 = getelementptr inbounds %sParserInfo, %sParserInfo* %info196, i32 0, i32 2, !dbg !310
  %fname198 = load i8*, i8** %field197, align 8, !dbg !310
  %info199 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !310
  %field200 = getelementptr inbounds %sParserInfo, %sParserInfo* %info199, i32 0, i32 1, !dbg !310
  %sline201 = load i32, i32* %field200, align 4, !dbg !310
  %fun_result202 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr195, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @"%s %d: the source end.3", i32 0, i32 0), i8* %fname198, i32 %sline201), !dbg !310
  %obj203 = load %buffer*, %buffer** %buf141, align 8, !dbg !311
  call void @buffer_finalize(%buffer* %obj203), !dbg !311
  %castAK204 = bitcast %buffer* %obj203 to i8*, !dbg !311
  call void @free(i8* %castAK204), !dbg !311
  ret %sNode* null, !dbg !311

cond_end194:                                      ; preds = %cond_jump_elif_then0152
  %buf205 = load %buffer*, %buffer** %buf141, align 8, !dbg !312
  %info206 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !312
  %field207 = getelementptr inbounds %sParserInfo, %sParserInfo* %info206, i32 0, i32 0, !dbg !312
  %p208 = load i8*, i8** %field207, align 8, !dbg !312
  %derefference_value209 = load i8, i8* %p208, align 1, !dbg !312
  call void @buffer_append_char(%buffer* %buf205, i8 %derefference_value209), !dbg !312
  %info210 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !313
  %info211 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !313
  %field212 = getelementptr inbounds %sParserInfo, %sParserInfo* %info211, i32 0, i32 0, !dbg !313
  %p213 = load i8*, i8** %field212, align 8, !dbg !313
  %ptrToIntC214 = ptrtoint i8* %p213 to i64, !dbg !313
  %add215 = add i64 %ptrToIntC214, 1, !dbg !313
  %intToPtr216 = inttoptr i64 %add215 to i8*, !dbg !313
  %field217 = getelementptr inbounds %sParserInfo, %sParserInfo* %info210, i32 0, i32 0, !dbg !313
  store i8* %intToPtr216, i8** %field217, align 8, !dbg !313
  %ptrToIntI218 = ptrtoint i8* %intToPtr216 to i64, !dbg !313
  %sub219 = sub i64 %ptrToIntI218, 1, !dbg !313
  %iintToPtr220 = inttoptr i64 %sub219 to i8*, !dbg !313
  br label %cond_end156, !dbg !313

after_break238:                                   ; No predecessors!
  br label %cond_end156, !dbg !307
}

declare i16** @__ctype_b_loc()

declare i32** @__ctype_tolower_loc()

declare i32** @__ctype_toupper_loc()

declare i32 @isalnum(i32)

declare i32 @isalpha(i32)

declare i32 @iscntrl(i32)

declare i32 @isdigit(i32)

declare i32 @islower(i32)

declare i32 @isgraph(i32)

declare i32 @isprint(i32)

declare i32 @ispunct(i32)

declare i32 @isspace(i32)

declare i32 @isupper(i32)

declare i32 @isxdigit(i32)

declare i32 @tolower(i32)

declare i32 @toupper(i32)

declare i32 @isblank(i32)

declare i32 @isascii(i32)

declare i32 @toascii(i32)

declare i32 @_toupper(i32)

declare i32 @_tolower(i32)

declare i32 @isalnum_l(i32, %__locale_struct*)

declare i32 @isalpha_l(i32, %__locale_struct*)

declare i32 @iscntrl_l(i32, %__locale_struct*)

declare i32 @isdigit_l(i32, %__locale_struct*)

declare i32 @islower_l(i32, %__locale_struct*)

declare i32 @isgraph_l(i32, %__locale_struct*)

declare i32 @isprint_l(i32, %__locale_struct*)

declare i32 @ispunct_l(i32, %__locale_struct*)

declare i32 @isspace_l(i32, %__locale_struct*)

declare i32 @isupper_l(i32, %__locale_struct*)

declare i32 @isxdigit_l(i32, %__locale_struct*)

declare i32 @isblank_l(i32, %__locale_struct*)

declare i32 @__tolower_l(i32, %__locale_struct*)

declare i32 @tolower_l(i32, %__locale_struct*)

declare i32 @__toupper_l(i32, %__locale_struct*)

declare i32 @toupper_l(i32, %__locale_struct*)

define internal %sNode* @create_string_node(i8* %0, %sParserInfo* %1) !dbg !314 {
entry:
  %result18 = alloca i8*, align 8, !dbg !315
  %len = alloca i32, align 4, !dbg !315
  %result = alloca %sNode*, align 8, !dbg !315
  %str = alloca i8*, align 8, !dbg !315
  store i8* %0, i8** %str, align 8, !dbg !315
  %info = alloca %sParserInfo*, align 8, !dbg !315
  store %sParserInfo* %1, %sParserInfo** %info, align 8, !dbg !315
  %fun_result = call i8* @calloc(i64 1, i64 48), !dbg !316
  %obj = bitcast i8* %fun_result to %sNode*, !dbg !316
  store %sNode* %obj, %sNode** %result, align 8, !dbg !315
  %result1 = load %sNode*, %sNode** %result, align 8, !dbg !317
  %field = getelementptr inbounds %sNode, %sNode* %result1, i32 0, i32 0, !dbg !317
  store i32 3, i32* %field, align 4, !dbg !317
  %result2 = load %sNode*, %sNode** %result, align 8, !dbg !318
  %info3 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !318
  %field4 = getelementptr inbounds %sParserInfo, %sParserInfo* %info3, i32 0, i32 2, !dbg !318
  %fname = load i8*, i8** %field4, align 8, !dbg !318
  %field5 = getelementptr inbounds %sNode, %sNode* %result2, i32 0, i32 1, !dbg !318
  store i8* %fname, i8** %field5, align 8, !dbg !318
  %result6 = load %sNode*, %sNode** %result, align 8, !dbg !319
  %info7 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !319
  %field8 = getelementptr inbounds %sParserInfo, %sParserInfo* %info7, i32 0, i32 1, !dbg !319
  %sline = load i32, i32* %field8, align 4, !dbg !319
  %field9 = getelementptr inbounds %sNode, %sNode* %result6, i32 0, i32 2, !dbg !319
  store i32 %sline, i32* %field9, align 4, !dbg !319
  %result10 = load %sNode*, %sNode** %result, align 8, !dbg !320
  %field11 = getelementptr inbounds %sNode, %sNode* %result10, i32 0, i32 3, !dbg !320
  %value = load %come_anon69, %come_anon69* %field11, align 8, !dbg !320
  %str12 = load i8*, i8** %str, align 8, !dbg !320
  br label %string, !dbg !320

string:                                           ; preds = %entry
  %inline_result_variable = alloca i8*, align 8, !dbg !320
  %str13 = alloca i8*, align 8, !dbg !320
  store i8* %str12, i8** %str13, align 8, !dbg !320
  %str14 = load i8*, i8** %str13, align 8, !dbg !320
  %fun_result15 = call i64 @strlen(i8* %str14), !dbg !320
  %add = add i64 %fun_result15, 1, !dbg !320
  %icastM = trunc i64 %add to i32, !dbg !320
  store i32 %icastM, i32* %len, align 4, !dbg !315
  %len16 = load i32, i32* %len, align 4, !dbg !315
  %icastD = sext i32 %len16 to i64, !dbg !315
  %fun_result17 = call i8* @nccalloc(i64 %icastD, i64 1), !dbg !315
  store i8* %fun_result17, i8** %result18, align 8, !dbg !315
  %result19 = load i8*, i8** %result18, align 8, !dbg !315
  %str20 = load i8*, i8** %str13, align 8, !dbg !315
  %len21 = load i32, i32* %len, align 4, !dbg !315
  %icastD22 = sext i32 %len21 to i64, !dbg !315
  %fun_result23 = call i8* @strncpy(i8* %result19, i8* %str20, i64 %icastD22), !dbg !315
  %result24 = load i8*, i8** %result18, align 8, !dbg !315
  store i8* %result24, i8** %inline_result_variable, align 8, !dbg !315
  br label %string_end, !dbg !315

string_end:                                       ; preds = %string
  %inline_result_variable25 = load i8*, i8** %inline_result_variable, align 8, !dbg !315
  %field26 = getelementptr inbounds %come_anon69, %come_anon69* %field11, i32 0, i32 0, !dbg !315
  %icastN = bitcast %come_anon70* %field26 to i8**, !dbg !315
  store i8* %inline_result_variable25, i8** %icastN, align 8, !dbg !315
  %result27 = load %sNode*, %sNode** %result, align 8, !dbg !321
  ret %sNode* %result27, !dbg !321
}

attributes #0 = { nounwind }
attributes #1 = { nounwind willreturn }
attributes #2 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "come", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false)
!1 = !DIFile(filename: "src/03str.c", directory: "/home/ab25cq/repo/neo-c2/yapy")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = distinct !DISubprogram(name: "p", linkageName: "p", scope: !6, file: !6, line: 28, type: !7, scopeLine: 28, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!6 = !DIFile(filename: "<stdin>", directory: "/home/ab25cq/repo/neo-c2/yapy")
!7 = !DISubroutineType(types: !8)
!8 = !{!9}
!9 = !DIBasicType(name: "pointer", size: 64)
!10 = !DILocation(line: 28, scope: !5)
!11 = !DILocation(line: 31, scope: !5)
!12 = distinct !DISubprogram(name: "ncfree", linkageName: "ncfree", scope: !6, file: !6, line: 34, type: !7, scopeLine: 34, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!13 = !DILocation(line: 34, scope: !12)
!14 = !DILocation(line: 37, scope: !12)
!15 = distinct !DISubprogram(name: "nccalloc", linkageName: "nccalloc", scope: !6, file: !6, line: 40, type: !16, scopeLine: 40, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!16 = !DISubroutineType(types: !17)
!17 = !{!18, !18}
!18 = !DIBasicType(name: "long", size: 64)
!19 = !DILocation(line: 40, scope: !15)
!20 = !DILocation(line: 42, scope: !15)
!21 = !DILocation(line: 46, scope: !15)
!22 = distinct !DISubprogram(name: "ncmemdup", linkageName: "ncmemdup", scope: !6, file: !6, line: 49, type: !7, scopeLine: 49, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!23 = !DILocation(line: 49, scope: !22)
!24 = !DILocation(line: 56, scope: !22)
!25 = !DILocation(line: 59, scope: !22)
!26 = !DILocation(line: 60, scope: !22)
!27 = !DILocation(line: 63, scope: !22)
!28 = !DILocation(line: 65, scope: !22)
!29 = !DILocation(line: 66, scope: !22)
!30 = !DILocation(line: 67, scope: !22)
!31 = !DILocation(line: 73, scope: !22)
!32 = !DILocation(line: 75, scope: !22)
!33 = !DILocation(line: 68, scope: !22)
!34 = !DILocation(line: 69, scope: !22)
!35 = !DILocation(line: 70, scope: !22)
!36 = !DILocation(line: 71, scope: !22)
!37 = distinct !DISubprogram(name: "xsprintf", linkageName: "xsprintf", scope: !6, file: !6, line: 102, type: !7, scopeLine: 102, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!38 = !DILocation(line: 102, scope: !37)
!39 = !DILocation(line: 105, scope: !37)
!40 = !DILocation(line: 107, scope: !37)
!41 = !DILocation(line: 108, scope: !37)
!42 = !DILocation(line: 110, scope: !37)
!43 = !DILocation(line: 111, scope: !37)
!44 = !DILocation(line: 113, scope: !37)
!45 = !DILocation(line: 116, scope: !37)
!46 = distinct !DISubprogram(name: "char_reverse", linkageName: "char_reverse", scope: !6, file: !6, line: 119, type: !7, scopeLine: 119, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!47 = !DILocation(line: 119, scope: !46)
!48 = !DILocation(line: 121, scope: !46)
!49 = !DILocation(line: 122, scope: !46)
!50 = !DILocation(line: 124, scope: !46)
!51 = !DILocation(line: 125, scope: !46)
!52 = !DILocation(line: 128, scope: !46)
!53 = !DILocation(line: 130, scope: !46)
!54 = distinct !DISubprogram(name: "char_substring", linkageName: "char_substring", scope: !6, file: !6, line: 133, type: !55, scopeLine: 133, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!55 = !DISubroutineType(types: !56)
!56 = !{!9, !57, !57}
!57 = !DIBasicType(name: "int", size: 32)
!58 = !DILocation(line: 133, scope: !54)
!59 = !DILocation(line: 135, scope: !54)
!60 = !DILocation(line: 136, scope: !54)
!61 = !DILocation(line: 139, scope: !54)
!62 = !DILocation(line: 141, scope: !54)
!63 = !DILocation(line: 142, scope: !54)
!64 = !DILocation(line: 144, scope: !54)
!65 = !DILocation(line: 145, scope: !54)
!66 = !DILocation(line: 148, scope: !54)
!67 = !DILocation(line: 149, scope: !54)
!68 = !DILocation(line: 152, scope: !54)
!69 = !DILocation(line: 153, scope: !54)
!70 = !DILocation(line: 156, scope: !54)
!71 = !DILocation(line: 157, scope: !54)
!72 = !DILocation(line: 160, scope: !54)
!73 = !DILocation(line: 161, scope: !54)
!74 = !DILocation(line: 164, scope: !54)
!75 = !DILocation(line: 165, scope: !54)
!76 = !DILocation(line: 168, scope: !54)
!77 = !DILocation(line: 170, scope: !54)
!78 = !DILocation(line: 171, scope: !54)
!79 = !DILocation(line: 173, scope: !54)
!80 = distinct !DISubprogram(name: "char_length", linkageName: "char_length", scope: !6, file: !6, line: 176, type: !7, scopeLine: 176, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!81 = !DILocation(line: 176, scope: !80)
!82 = !DILocation(line: 178, scope: !80)
!83 = distinct !DISubprogram(name: "int_get_hash_key", linkageName: "int_get_hash_key", scope: !6, file: !6, line: 182, type: !84, scopeLine: 182, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!84 = !DISubroutineType(types: !85)
!85 = !{!57}
!86 = !DILocation(line: 182, scope: !83)
!87 = !DILocation(line: 184, scope: !83)
!88 = distinct !DISubprogram(name: "char_get_hash_key", linkageName: "char_get_hash_key", scope: !6, file: !6, line: 188, type: !7, scopeLine: 188, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!89 = !DILocation(line: 188, scope: !88)
!90 = !DILocation(line: 191, scope: !88)
!91 = !DILocation(line: 196, scope: !88)
!92 = !DILocation(line: 192, scope: !88)
!93 = !DILocation(line: 193, scope: !88)
!94 = !DILocation(line: 194, scope: !88)
!95 = distinct !DISubprogram(name: "char_equals", linkageName: "char_equals", scope: !6, file: !6, line: 199, type: !96, scopeLine: 199, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!96 = !DISubroutineType(types: !97)
!97 = !{!9, !9}
!98 = !DILocation(line: 199, scope: !95)
!99 = !DILocation(line: 201, scope: !95)
!100 = distinct !DISubprogram(name: "char_compare", linkageName: "char_compare", scope: !6, file: !6, line: 204, type: !101, scopeLine: 204, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!101 = !DISubroutineType(types: !102)
!102 = !{!57, !57}
!103 = !DILocation(line: 204, scope: !100)
!104 = !DILocation(line: 206, scope: !100)
!105 = !DILocation(line: 207, scope: !100)
!106 = !DILocation(line: 209, scope: !100)
!107 = !DILocation(line: 210, scope: !100)
!108 = !DILocation(line: 213, scope: !100)
!109 = distinct !DISubprogram(name: "buffer_initialize", linkageName: "buffer_initialize", scope: !6, file: !6, line: 1572, type: !7, scopeLine: 1572, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!110 = !DILocation(line: 1572, scope: !109)
!111 = !DILocation(line: 1574, scope: !109)
!112 = !DILocation(line: 1575, scope: !109)
!113 = !DILocation(line: 1577, scope: !109)
!114 = !DILocation(line: 1579, scope: !109)
!115 = distinct !DISubprogram(name: "buffer_finalize", linkageName: "buffer_finalize", scope: !6, file: !6, line: 1582, type: !7, scopeLine: 1582, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!116 = !DILocation(line: 1582, scope: !115)
!117 = !DILocation(line: 1584, scope: !115)
!118 = distinct !DISubprogram(name: "buffer_length", linkageName: "buffer_length", scope: !6, file: !6, line: 1587, type: !7, scopeLine: 1587, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!119 = !DILocation(line: 1587, scope: !118)
!120 = !DILocation(line: 1589, scope: !118)
!121 = distinct !DISubprogram(name: "buffer_append", linkageName: "buffer_append", scope: !6, file: !6, line: 1592, type: !122, scopeLine: 1592, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!122 = !DISubroutineType(types: !123)
!123 = !{!9, !9, !18}
!124 = !DILocation(line: 1592, scope: !121)
!125 = !DILocation(line: 1594, scope: !121)
!126 = !DILocation(line: 1595, scope: !121)
!127 = !DILocation(line: 1596, scope: !121)
!128 = !DILocation(line: 1597, scope: !121)
!129 = !DILocation(line: 1600, scope: !121)
!130 = !DILocation(line: 1601, scope: !121)
!131 = !DILocation(line: 1603, scope: !121)
!132 = distinct !DISubprogram(name: "buffer_append_char", linkageName: "buffer_append_char", scope: !6, file: !6, line: 1606, type: !133, scopeLine: 1606, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!133 = !DISubroutineType(types: !134)
!134 = !{!9, !135}
!135 = !DIBasicType(name: "char", size: 8)
!136 = !DILocation(line: 1606, scope: !132)
!137 = !DILocation(line: 1608, scope: !132)
!138 = !DILocation(line: 1609, scope: !132)
!139 = !DILocation(line: 1610, scope: !132)
!140 = !DILocation(line: 1611, scope: !132)
!141 = !DILocation(line: 1614, scope: !132)
!142 = !DILocation(line: 1615, scope: !132)
!143 = !DILocation(line: 1617, scope: !132)
!144 = distinct !DISubprogram(name: "buffer_append_str", linkageName: "buffer_append_str", scope: !6, file: !6, line: 1620, type: !96, scopeLine: 1620, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!145 = !DILocation(line: 1620, scope: !144)
!146 = !DILocation(line: 1622, scope: !144)
!147 = distinct !DISubprogram(name: "buffer_append_nullterminated_str", linkageName: "buffer_append_nullterminated_str", scope: !6, file: !6, line: 1625, type: !96, scopeLine: 1625, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!148 = !DILocation(line: 1625, scope: !147)
!149 = !DILocation(line: 1627, scope: !147)
!150 = !DILocation(line: 1628, scope: !147)
!151 = distinct !DISubprogram(name: "buffer_to_string", linkageName: "buffer_to_string", scope: !6, file: !6, line: 1631, type: !7, scopeLine: 1631, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!152 = !DILocation(line: 1631, scope: !151)
!153 = !DILocation(line: 1634, scope: !151)
!154 = distinct !DISubprogram(name: "buffer_append_int", linkageName: "buffer_append_int", scope: !6, file: !6, line: 1636, type: !155, scopeLine: 1636, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!155 = !DISubroutineType(types: !156)
!156 = !{!9, !57}
!157 = !DILocation(line: 1636, scope: !154)
!158 = !DILocation(line: 1638, scope: !154)
!159 = distinct !DISubprogram(name: "buffer_append_long", linkageName: "buffer_append_long", scope: !6, file: !6, line: 1641, type: !160, scopeLine: 1641, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!160 = !DISubroutineType(types: !161)
!161 = !{!9, !18}
!162 = !DILocation(line: 1641, scope: !159)
!163 = !DILocation(line: 1643, scope: !159)
!164 = distinct !DISubprogram(name: "buffer_append_short", linkageName: "buffer_append_short", scope: !6, file: !6, line: 1646, type: !165, scopeLine: 1646, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!165 = !DISubroutineType(types: !166)
!166 = !{!9, !167}
!167 = !DIBasicType(name: "short", size: 16)
!168 = !DILocation(line: 1646, scope: !164)
!169 = !DILocation(line: 1648, scope: !164)
!170 = distinct !DISubprogram(name: "buffer_alignment", linkageName: "buffer_alignment", scope: !6, file: !6, line: 1651, type: !7, scopeLine: 1651, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!171 = !DILocation(line: 1651, scope: !170)
!172 = !DILocation(line: 1653, scope: !170)
!173 = !DILocation(line: 1654, scope: !170)
!174 = !DILocation(line: 1656, scope: !170)
!175 = !DILocation(line: 1657, scope: !170)
!176 = distinct !DISubprogram(name: "buffer_compare", linkageName: "buffer_compare", scope: !6, file: !6, line: 1661, type: !96, scopeLine: 1661, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!177 = !DILocation(line: 1661, scope: !176)
!178 = !DILocation(line: 1663, scope: !176)
!179 = distinct !DISubprogram(name: "char_to_buffer", linkageName: "char_to_buffer", scope: !6, file: !6, line: 1666, type: !7, scopeLine: 1666, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!180 = !DILocation(line: 1666, scope: !179)
!181 = !DILocation(line: 1668, scope: !179)
!182 = !DILocation(line: 1670, scope: !179)
!183 = !DILocation(line: 1672, scope: !179)
!184 = distinct !DISubprogram(name: "come_fd_zero", linkageName: "come_fd_zero", scope: !6, file: !6, line: 1675, type: !7, scopeLine: 1675, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!185 = !DILocation(line: 1675, scope: !184)
!186 = !DILocation(line: 1677, scope: !184)
!187 = distinct !DISubprogram(name: "come_fd_set", linkageName: "come_fd_set", scope: !6, file: !6, line: 1680, type: !188, scopeLine: 1680, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!188 = !DISubroutineType(types: !189)
!189 = !{!57, !9}
!190 = !DILocation(line: 1680, scope: !187)
!191 = !DILocation(line: 1682, scope: !187)
!192 = distinct !DISubprogram(name: "come_fd_isset", linkageName: "come_fd_isset", scope: !6, file: !6, line: 1685, type: !188, scopeLine: 1685, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!193 = !DILocation(line: 1685, scope: !192)
!194 = !DILocation(line: 1688, scope: !192)
!195 = distinct !DISubprogram(name: "int_expect", linkageName: "int_expect", scope: !6, file: !6, line: 1691, type: !196, scopeLine: 1691, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!196 = !DISubroutineType(types: !197)
!197 = !{!57, !9, !9}
!198 = !DILocation(line: 1691, scope: !195)
!199 = !DILocation(line: 1693, scope: !195)
!200 = !DILocation(line: 1694, scope: !195)
!201 = !DILocation(line: 1697, scope: !195)
!202 = distinct !DISubprogram(name: "bool_expect", linkageName: "bool_expect", scope: !6, file: !6, line: 1700, type: !203, scopeLine: 1700, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!203 = !DISubroutineType(types: !204)
!204 = !{null, !9, !9}
!205 = !DILocation(line: 1700, scope: !202)
!206 = !DILocation(line: 1702, scope: !202)
!207 = !DILocation(line: 1703, scope: !202)
!208 = !DILocation(line: 1706, scope: !202)
!209 = distinct !DISubprogram(name: "int_times", linkageName: "int_times", scope: !6, file: !6, line: 1709, type: !196, scopeLine: 1709, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!210 = !DILocation(line: 1709, scope: !209)
!211 = !DILocation(line: 1712, scope: !209)
!212 = !DILocation(line: 1713, scope: !209)
!213 = distinct !DISubprogram(name: "xiswalpha", linkageName: "xiswalpha", scope: !6, file: !6, line: 1770, type: !84, scopeLine: 1770, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!214 = !DILocation(line: 1770, scope: !213)
!215 = !DILocation(line: 1772, scope: !213)
!216 = !DILocation(line: 1773, scope: !213)
!217 = distinct !DISubprogram(name: "xiswblank", linkageName: "xiswblank", scope: !6, file: !6, line: 1776, type: !84, scopeLine: 1776, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!218 = !DILocation(line: 1776, scope: !217)
!219 = !DILocation(line: 1778, scope: !217)
!220 = distinct !DISubprogram(name: "xiswdigit", linkageName: "xiswdigit", scope: !6, file: !6, line: 1781, type: !84, scopeLine: 1781, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!221 = !DILocation(line: 1781, scope: !220)
!222 = !DILocation(line: 1783, scope: !220)
!223 = distinct !DISubprogram(name: "xiswalnum", linkageName: "xiswalnum", scope: !6, file: !6, line: 1786, type: !84, scopeLine: 1786, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!224 = !DILocation(line: 1786, scope: !223)
!225 = !DILocation(line: 1788, scope: !223)
!226 = distinct !DISubprogram(name: "xbasename", linkageName: "xbasename", scope: !6, file: !6, line: 1791, type: !7, scopeLine: 1791, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!227 = !DILocation(line: 1791, scope: !226)
!228 = !DILocation(line: 1793, scope: !226)
!229 = !DILocation(line: 1804, scope: !226)
!230 = !DILocation(line: 1795, scope: !226)
!231 = !DILocation(line: 1796, scope: !226)
!232 = !DILocation(line: 1797, scope: !226)
!233 = !DILocation(line: 1800, scope: !226)
!234 = !DILocation(line: 1805, scope: !226)
!235 = !DILocation(line: 1808, scope: !226)
!236 = distinct !DISubprogram(name: "xextname", linkageName: "xextname", scope: !6, file: !6, line: 1812, type: !7, scopeLine: 1812, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!237 = !DILocation(line: 1812, scope: !236)
!238 = !DILocation(line: 1814, scope: !236)
!239 = !DILocation(line: 1825, scope: !236)
!240 = !DILocation(line: 1816, scope: !236)
!241 = !DILocation(line: 1817, scope: !236)
!242 = !DILocation(line: 1818, scope: !236)
!243 = !DILocation(line: 1821, scope: !236)
!244 = !DILocation(line: 1826, scope: !236)
!245 = !DILocation(line: 1829, scope: !236)
!246 = distinct !DISubprogram(name: "xrealpath", linkageName: "xrealpath", scope: !6, file: !6, line: 1833, type: !7, scopeLine: 1833, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!247 = !DILocation(line: 1833, scope: !246)
!248 = !DILocation(line: 1835, scope: !246)
!249 = !DILocation(line: 1837, scope: !246)
!250 = !DILocation(line: 1839, scope: !246)
!251 = !DILocation(line: 1841, scope: !246)
!252 = distinct !DISubprogram(name: "compile", linkageName: "compile", scope: !1, file: !1, line: 106, type: !253, scopeLine: 106, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!253 = !DISubroutineType(types: !254)
!254 = !{!9, !9, !9}
!255 = !DILocation(line: 106, scope: !252)
!256 = !DILocation(line: 108, scope: !252)
!257 = !DILocation(line: 110, scope: !252)
!258 = !DILocation(line: 111, scope: !252)
!259 = !DILocation(line: 113, scope: !252)
!260 = !DILocation(line: 114, scope: !252)
!261 = !DILocation(line: 117, scope: !252)
!262 = distinct !DISubprogram(name: "sNode_finalize", linkageName: "sNode_finalize", scope: !1, file: !1, line: 17, type: !7, scopeLine: 17, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!263 = !DILocation(line: 17, scope: !262)
!264 = !DILocation(line: 19, scope: !262)
!265 = !DILocation(line: 21, scope: !262)
!266 = !DILocation(line: 22, scope: !262)
!267 = distinct !DISubprogram(name: "exp_node", linkageName: "exp_node", scope: !1, file: !1, line: 26, type: !7, scopeLine: 26, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!268 = !DILocation(line: 26, scope: !267)
!269 = !DILocation(line: 28, scope: !267)
!270 = !DILocation(line: 30, scope: !267)
!271 = !DILocation(line: 31, scope: !267)
!272 = !DILocation(line: 103, scope: !267)
!273 = !DILocation(line: 32, scope: !267)
!274 = !DILocation(line: 34, scope: !267)
!275 = !DILocation(line: 64, scope: !267)
!276 = !DILocation(line: 66, scope: !267)
!277 = !DILocation(line: 67, scope: !267)
!278 = !DILocation(line: 69, scope: !267)
!279 = !DILocation(line: 99, scope: !267)
!280 = !DILocation(line: 36, scope: !267)
!281 = !DILocation(line: 37, scope: !267)
!282 = !DILocation(line: 38, scope: !267)
!283 = !DILocation(line: 39, scope: !267)
!284 = !DILocation(line: 41, scope: !267)
!285 = !DILocation(line: 42, scope: !267)
!286 = !DILocation(line: 43, scope: !267)
!287 = !DILocation(line: 45, scope: !267)
!288 = !DILocation(line: 53, scope: !267)
!289 = !DILocation(line: 55, scope: !267)
!290 = !DILocation(line: 56, scope: !267)
!291 = !DILocation(line: 59, scope: !267)
!292 = !DILocation(line: 60, scope: !267)
!293 = !DILocation(line: 46, scope: !267)
!294 = !DILocation(line: 47, scope: !267)
!295 = !DILocation(line: 50, scope: !267)
!296 = !DILocation(line: 51, scope: !267)
!297 = !DILocation(line: 71, scope: !267)
!298 = !DILocation(line: 72, scope: !267)
!299 = !DILocation(line: 73, scope: !267)
!300 = !DILocation(line: 74, scope: !267)
!301 = !DILocation(line: 76, scope: !267)
!302 = !DILocation(line: 77, scope: !267)
!303 = !DILocation(line: 78, scope: !267)
!304 = !DILocation(line: 80, scope: !267)
!305 = !DILocation(line: 88, scope: !267)
!306 = !DILocation(line: 90, scope: !267)
!307 = !DILocation(line: 91, scope: !267)
!308 = !DILocation(line: 94, scope: !267)
!309 = !DILocation(line: 95, scope: !267)
!310 = !DILocation(line: 81, scope: !267)
!311 = !DILocation(line: 82, scope: !267)
!312 = !DILocation(line: 85, scope: !267)
!313 = !DILocation(line: 86, scope: !267)
!314 = distinct !DISubprogram(name: "create_string_node", linkageName: "create_string_node", scope: !1, file: !1, line: 4, type: !96, scopeLine: 4, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!315 = !DILocation(line: 4, scope: !314)
!316 = !DILocation(line: 6, scope: !314)
!317 = !DILocation(line: 8, scope: !314)
!318 = !DILocation(line: 10, scope: !314)
!319 = !DILocation(line: 11, scope: !314)
!320 = !DILocation(line: 12, scope: !314)
!321 = !DILocation(line: 14, scope: !314)
