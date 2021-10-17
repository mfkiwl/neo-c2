; ModuleID = 'src/01int.c'
source_filename = "src/01int.c"

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
%list_sNodep = type { %list_item_sNodep*, %list_item_sNodep*, i32, %list_item_sNodep* }
%list_item_sNodep = type { %sNode*, %list_item_sNodep*, %list_item_sNodep* }
%sNode = type { i32, i8*, i32, %come_anon68 }
%come_anon68 = type { i8* }

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
@r = private unnamed_addr constant [2 x i8] c"r\00", align 1
@"file %s is not found\0A" = private unnamed_addr constant [22 x i8] c"file %s is not found\0A\00", align 1
@"%s %d: unexpected character %c\0A" = private unnamed_addr constant [32 x i8] c"%s %d: unexpected character %c\0A\00", align 1
@"int value %d\0A" = private unnamed_addr constant [14 x i8] c"int value %d\0A\00", align 1

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

define internal i8* @ncmemdup(i8* %0) !dbg !5 {
entry:
  %p2 = alloca i8*, align 8, !dbg !10
  %p = alloca i8*, align 8, !dbg !10
  %ret = alloca i8*, align 8, !dbg !10
  %size = alloca i64, align 8, !dbg !10
  %block = alloca i8*, align 8, !dbg !10
  store i8* %0, i8** %block, align 8, !dbg !10
  %block1 = load i8*, i8** %block, align 8, !dbg !11
  %fun_result = call i64 @GC_size(i8* %block1), !dbg !11
  store i64 %fun_result, i64* %size, align 4, !dbg !10
  %block2 = load i8*, i8** %block, align 8, !dbg !12
  %logical_denial = icmp eq i8* %block2, null, !dbg !12
  br i1 %logical_denial, label %cond_jump_then, label %cond_end, !dbg !12

cond_jump_then:                                   ; preds = %entry
  ret i8* null, !dbg !13

cond_end:                                         ; preds = %entry
  %size3 = load i64, i64* %size, align 4, !dbg !14
  %fun_result4 = call i8* @GC_malloc(i64 %size3), !dbg !14
  store i8* %fun_result4, i8** %ret, align 8, !dbg !10
  %ret5 = load i8*, i8** %ret, align 8, !dbg !15
  %icmpB = icmp ne i8* %ret5, null, !dbg !15
  br i1 %icmpB, label %cond_jump_then6, label %cond_end7, !dbg !15

cond_jump_then6:                                  ; preds = %cond_end
  %ret8 = load i8*, i8** %ret, align 8, !dbg !16
  store i8* %ret8, i8** %p, align 8, !dbg !10
  %block9 = load i8*, i8** %block, align 8, !dbg !17
  store i8* %block9, i8** %p2, align 8, !dbg !10
  br label %loop_top_block, !dbg !18

cond_end7:                                        ; preds = %cond_end_block, %cond_end
  %ret24 = load i8*, i8** %ret, align 8, !dbg !19
  ret i8* %ret24, !dbg !19

loop_top_block:                                   ; preds = %cond_then_block, %cond_jump_then6
  %p10 = load i8*, i8** %p, align 8, !dbg !20
  %ret11 = load i8*, i8** %ret, align 8, !dbg !20
  %ptrToIntG = ptrtoint i8* %p10 to i64, !dbg !20
  %ptrToIntH = ptrtoint i8* %ret11 to i64, !dbg !20
  %sub = sub i64 %ptrToIntG, %ptrToIntH, !dbg !20
  %div = sdiv i64 %sub, 1, !dbg !20
  %size12 = load i64, i64* %size, align 4, !dbg !20
  %le = icmp slt i64 %div, %size12, !dbg !20
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !20

cond_then_block:                                  ; preds = %loop_top_block
  %p13 = load i8*, i8** %p, align 8, !dbg !21
  %p214 = load i8*, i8** %p2, align 8, !dbg !21
  %derefference_value = load i8, i8* %p214, align 1, !dbg !21
  store i8 %derefference_value, i8* %p13, align 1, !dbg !21
  %p15 = load i8*, i8** %p, align 8, !dbg !22
  %ptrToIntC = ptrtoint i8* %p15 to i64, !dbg !22
  %add = add i64 %ptrToIntC, 1, !dbg !22
  %intToPtr = inttoptr i64 %add to i8*, !dbg !22
  store i8* %intToPtr, i8** %p, align 8, !dbg !22
  %ptrToIntI = ptrtoint i8* %intToPtr to i64, !dbg !22
  %sub16 = sub i64 %ptrToIntI, 1, !dbg !22
  %iintToPtr = inttoptr i64 %sub16 to i8*, !dbg !22
  %p217 = load i8*, i8** %p2, align 8, !dbg !23
  %ptrToIntC18 = ptrtoint i8* %p217 to i64, !dbg !23
  %add19 = add i64 %ptrToIntC18, 1, !dbg !23
  %intToPtr20 = inttoptr i64 %add19 to i8*, !dbg !23
  store i8* %intToPtr20, i8** %p2, align 8, !dbg !23
  %ptrToIntI21 = ptrtoint i8* %intToPtr20 to i64, !dbg !23
  %sub22 = sub i64 %ptrToIntI21, 1, !dbg !23
  %iintToPtr23 = inttoptr i64 %sub22 to i8*, !dbg !23
  br label %loop_top_block, !dbg !23

cond_end_block:                                   ; preds = %loop_top_block
  br label %cond_end7, !dbg !23
}

define internal i8* @xsprintf(i8* %0, ...) !dbg !24 {
entry:
  %result223 = alloca i8*, align 8, !dbg !25
  %result15 = alloca i8*, align 8, !dbg !25
  %len12 = alloca i32, align 4, !dbg !25
  %len = alloca i32, align 4, !dbg !25
  %result = alloca i8*, align 8, !dbg !25
  %args = alloca [1 x { i32, i32, i8*, i8* }], align 8, !dbg !25
  %msg = alloca i8*, align 8, !dbg !25
  store i8* %0, i8** %msg, align 8, !dbg !25
  %gep = getelementptr [1 x { i32, i32, i8*, i8* }], [1 x { i32, i32, i8*, i8* }]* %args, i32 0, i32 0, !dbg !26
  %castAN = bitcast { i32, i32, i8*, i8* }* %gep to i8*, !dbg !26
  %msg1 = load i8*, i8** %msg, align 8, !dbg !26
  call void @llvm.va_start(i8* %castAN), !dbg !26
  %result2 = load i8*, i8** %result, align 8, !dbg !27
  %msg3 = load i8*, i8** %msg, align 8, !dbg !27
  %gep4 = getelementptr [1 x { i32, i32, i8*, i8* }], [1 x { i32, i32, i8*, i8* }]* %args, i32 0, i32 0, !dbg !27
  %fun_result = call i32 @vasprintf(i8** %result, i8* %msg3, { i32, i32, i8*, i8* }* %gep4), !dbg !27
  store i32 %fun_result, i32* %len, align 4, !dbg !25
  %gep5 = getelementptr [1 x { i32, i32, i8*, i8* }], [1 x { i32, i32, i8*, i8* }]* %args, i32 0, i32 0, !dbg !28
  %castAN6 = bitcast { i32, i32, i8*, i8* }* %gep5 to i8*, !dbg !28
  call void @llvm.va_end(i8* %castAN6), !dbg !28
  %len7 = load i32, i32* %len, align 4, !dbg !29
  %le = icmp slt i32 %len7, 0, !dbg !29
  br i1 %le, label %cond_jump_then, label %cond_end, !dbg !29

cond_jump_then:                                   ; preds = %entry
  %stderr = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !30
  %fun_result8 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @"can't get heap memory.\0A", i32 0, i32 0)), !dbg !30
  call void @exit(i32 2), !dbg !31
  br label %cond_end, !dbg !31

cond_end:                                         ; preds = %cond_jump_then, %entry
  %result9 = load i8*, i8** %result, align 8, !dbg !32
  br label %string, !dbg !32

string:                                           ; preds = %cond_end
  %inline_result_variable = alloca i8*, align 8, !dbg !32
  %str = alloca i8*, align 8, !dbg !32
  store i8* %result9, i8** %str, align 8, !dbg !32
  %str10 = load i8*, i8** %str, align 8, !dbg !32
  %fun_result11 = call i64 @strlen(i8* %str10), !dbg !32
  %add = add i64 %fun_result11, 1, !dbg !32
  %icastM = trunc i64 %add to i32, !dbg !32
  store i32 %icastM, i32* %len12, align 4, !dbg !25
  %len13 = load i32, i32* %len12, align 4, !dbg !25
  %icastD = sext i32 %len13 to i64, !dbg !25
  %mul = mul i64 1, %icastD, !dbg !25
  %fun_result14 = call i8* @GC_malloc(i64 %mul), !dbg !25
  store i8* %fun_result14, i8** %result15, align 8, !dbg !25
  %result16 = load i8*, i8** %result15, align 8, !dbg !25
  %str17 = load i8*, i8** %str, align 8, !dbg !25
  %len18 = load i32, i32* %len12, align 4, !dbg !25
  %icastD19 = sext i32 %len18 to i64, !dbg !25
  %fun_result20 = call i8* @strncpy(i8* %result16, i8* %str17, i64 %icastD19), !dbg !25
  %result21 = load i8*, i8** %result15, align 8, !dbg !25
  store i8* %result21, i8** %inline_result_variable, align 8, !dbg !25
  br label %string_end, !dbg !25

string_end:                                       ; preds = %string
  %inline_result_variable22 = load i8*, i8** %inline_result_variable, align 8, !dbg !25
  store i8* %inline_result_variable22, i8** %result223, align 8, !dbg !25
  %result24 = load i8*, i8** %result, align 8, !dbg !33
  call void @free(i8* %result24), !dbg !33
  %result225 = load i8*, i8** %result223, align 8, !dbg !34
  ret i8* %result225, !dbg !34
}

define internal i8* @char_reverse(i8* %0) !dbg !35 {
entry:
  %i = alloca i32, align 4, !dbg !36
  %result = alloca i8*, align 8, !dbg !36
  %len = alloca i32, align 4, !dbg !36
  %str = alloca i8*, align 8, !dbg !36
  store i8* %0, i8** %str, align 8, !dbg !36
  %str1 = load i8*, i8** %str, align 8, !dbg !37
  %fun_result = call i64 @strlen(i8* %str1), !dbg !37
  %icastM = trunc i64 %fun_result to i32, !dbg !37
  store i32 %icastM, i32* %len, align 4, !dbg !36
  %len2 = load i32, i32* %len, align 4, !dbg !38
  %add = add i32 %len2, 1, !dbg !38
  %icastD = sext i32 %add to i64, !dbg !38
  %mul = mul i64 1, %icastD, !dbg !38
  %fun_result3 = call i8* @GC_malloc(i64 %mul), !dbg !38
  store i8* %fun_result3, i8** %result, align 8, !dbg !36
  store i32 0, i32* %i, align 4, !dbg !36
  br label %loop_top_block, !dbg !36

loop_top_block:                                   ; preds = %cond_then_block, %entry
  %i4 = load i32, i32* %i, align 4, !dbg !39
  %len5 = load i32, i32* %len, align 4, !dbg !39
  %le = icmp slt i32 %i4, %len5, !dbg !39
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !39

cond_then_block:                                  ; preds = %loop_top_block
  %result6 = load i8*, i8** %result, align 8, !dbg !40
  %i7 = load i32, i32* %i, align 4, !dbg !40
  %str8 = load i8*, i8** %str, align 8, !dbg !40
  %len9 = load i32, i32* %len, align 4, !dbg !40
  %i10 = load i32, i32* %i, align 4, !dbg !40
  %sub = sub i32 %len9, %i10, !dbg !40
  %sub11 = sub i32 %sub, 1, !dbg !40
  %element_address = getelementptr inbounds i8, i8* %str8, i32 %sub11, !dbg !40
  %element = load i8, i8* %element_address, align 1, !dbg !40
  %element_address12 = getelementptr i8, i8* %result6, i32 %i7, !dbg !40
  store i8 %element, i8* %element_address12, align 1, !dbg !40
  %i13 = load i32, i32* %i, align 4, !dbg !39
  %add14 = add i32 %i13, 1, !dbg !39
  store i32 %add14, i32* %i, align 4, !dbg !39
  %sub15 = sub i32 %add14, 1, !dbg !39
  br label %loop_top_block, !dbg !39

cond_end_block:                                   ; preds = %loop_top_block
  %result16 = load i8*, i8** %result, align 8, !dbg !41
  %len17 = load i32, i32* %len, align 4, !dbg !41
  %element_address18 = getelementptr i8, i8* %result16, i32 %len17, !dbg !41
  store i8 0, i8* %element_address18, align 1, !dbg !41
  %result19 = load i8*, i8** %result, align 8, !dbg !42
  ret i8* %result19, !dbg !42
}

define internal i8* @char_substring(i8* %0, i32 %1, i32 %2) !dbg !43 {
entry:
  %result114 = alloca i8*, align 8, !dbg !47
  %result99 = alloca i8*, align 8, !dbg !47
  %len94 = alloca i32, align 4, !dbg !47
  %result71 = alloca i8*, align 8, !dbg !47
  %len66 = alloca i32, align 4, !dbg !47
  %len16 = alloca i32, align 4, !dbg !47
  %result = alloca i8*, align 8, !dbg !47
  %len = alloca i32, align 4, !dbg !47
  %str = alloca i8*, align 8, !dbg !47
  store i8* %0, i8** %str, align 8, !dbg !47
  %head = alloca i32, align 4, !dbg !47
  store i32 %1, i32* %head, align 4, !dbg !47
  %tail = alloca i32, align 4, !dbg !47
  store i32 %2, i32* %tail, align 4, !dbg !47
  %str1 = load i8*, i8** %str, align 8, !dbg !48
  %eq = icmp eq i8* %str1, null, !dbg !48
  br i1 %eq, label %cond_jump_then, label %cond_end, !dbg !48

cond_jump_then:                                   ; preds = %entry
  br label %string, !dbg !49

cond_end:                                         ; preds = %entry
  %str13 = load i8*, i8** %str, align 8, !dbg !50
  %fun_result14 = call i64 @strlen(i8* %str13), !dbg !50
  %icastM15 = trunc i64 %fun_result14 to i32, !dbg !50
  store i32 %icastM15, i32* %len16, align 4, !dbg !47
  %head17 = load i32, i32* %head, align 4, !dbg !51
  %le = icmp slt i32 %head17, 0, !dbg !51
  br i1 %le, label %cond_jump_then18, label %cond_end19, !dbg !51

string:                                           ; preds = %cond_jump_then
  %inline_result_variable = alloca i8*, align 8, !dbg !49
  %str2 = alloca i8*, align 8, !dbg !49
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @0, i32 0, i32 0), i8** %str2, align 8, !dbg !49
  %str3 = load i8*, i8** %str2, align 8, !dbg !49
  %fun_result = call i64 @strlen(i8* %str3), !dbg !49
  %add = add i64 %fun_result, 1, !dbg !49
  %icastM = trunc i64 %add to i32, !dbg !49
  store i32 %icastM, i32* %len, align 4, !dbg !47
  %len4 = load i32, i32* %len, align 4, !dbg !47
  %icastD = sext i32 %len4 to i64, !dbg !47
  %mul = mul i64 1, %icastD, !dbg !47
  %fun_result5 = call i8* @GC_malloc(i64 %mul), !dbg !47
  store i8* %fun_result5, i8** %result, align 8, !dbg !47
  %result6 = load i8*, i8** %result, align 8, !dbg !47
  %str7 = load i8*, i8** %str2, align 8, !dbg !47
  %len8 = load i32, i32* %len, align 4, !dbg !47
  %icastD9 = sext i32 %len8 to i64, !dbg !47
  %fun_result10 = call i8* @strncpy(i8* %result6, i8* %str7, i64 %icastD9), !dbg !47
  %result11 = load i8*, i8** %result, align 8, !dbg !47
  store i8* %result11, i8** %inline_result_variable, align 8, !dbg !47
  br label %string_end, !dbg !47

string_end:                                       ; preds = %string
  %inline_result_variable12 = load i8*, i8** %inline_result_variable, align 8, !dbg !47
  ret i8* %inline_result_variable12, !dbg !47

cond_jump_then18:                                 ; preds = %cond_end
  %head20 = load i32, i32* %head, align 4, !dbg !52
  %len21 = load i32, i32* %len16, align 4, !dbg !52
  %add22 = add i32 %head20, %len21, !dbg !52
  store i32 %add22, i32* %head, align 4, !dbg !52
  %len23 = load i32, i32* %len16, align 4, !dbg !52
  %sub = sub i32 %add22, %len23, !dbg !52
  br label %cond_end19, !dbg !52

cond_end19:                                       ; preds = %cond_jump_then18, %cond_end
  %tail24 = load i32, i32* %tail, align 4, !dbg !53
  %le25 = icmp slt i32 %tail24, 0, !dbg !53
  br i1 %le25, label %cond_jump_then26, label %cond_end27, !dbg !53

cond_jump_then26:                                 ; preds = %cond_end19
  %tail28 = load i32, i32* %tail, align 4, !dbg !54
  %len29 = load i32, i32* %len16, align 4, !dbg !54
  %add30 = add i32 %len29, 1, !dbg !54
  %add31 = add i32 %tail28, %add30, !dbg !54
  store i32 %add31, i32* %tail, align 4, !dbg !54
  %len32 = load i32, i32* %len16, align 4, !dbg !54
  %add33 = add i32 %len32, 1, !dbg !54
  %sub34 = sub i32 %add31, %add33, !dbg !54
  br label %cond_end27, !dbg !54

cond_end27:                                       ; preds = %cond_jump_then26, %cond_end19
  %head35 = load i32, i32* %head, align 4, !dbg !55
  %tail36 = load i32, i32* %tail, align 4, !dbg !55
  %gt = icmp sgt i32 %head35, %tail36, !dbg !55
  br i1 %gt, label %cond_jump_then37, label %cond_end38, !dbg !55

cond_jump_then37:                                 ; preds = %cond_end27
  %str39 = load i8*, i8** %str, align 8, !dbg !56
  %tail40 = load i32, i32* %tail, align 4, !dbg !56
  %head41 = load i32, i32* %head, align 4, !dbg !56
  %fun_result42 = call i8* @char_substring(i8* %str39, i32 %tail40, i32 %head41), !dbg !56
  %fun_result43 = call i8* @char_reverse(i8* %fun_result42), !dbg !56
  ret i8* %fun_result43, !dbg !56

cond_end38:                                       ; preds = %cond_end27
  %head44 = load i32, i32* %head, align 4, !dbg !57
  %le45 = icmp slt i32 %head44, 0, !dbg !57
  br i1 %le45, label %cond_jump_then46, label %cond_end47, !dbg !57

cond_jump_then46:                                 ; preds = %cond_end38
  store i32 0, i32* %head, align 4, !dbg !58
  br label %cond_end47, !dbg !58

cond_end47:                                       ; preds = %cond_jump_then46, %cond_end38
  %tail48 = load i32, i32* %tail, align 4, !dbg !59
  %len49 = load i32, i32* %len16, align 4, !dbg !59
  %gteq = icmp sge i32 %tail48, %len49, !dbg !59
  br i1 %gteq, label %cond_jump_then50, label %cond_end51, !dbg !59

cond_jump_then50:                                 ; preds = %cond_end47
  %len52 = load i32, i32* %len16, align 4, !dbg !60
  store i32 %len52, i32* %tail, align 4, !dbg !60
  br label %cond_end51, !dbg !60

cond_end51:                                       ; preds = %cond_jump_then50, %cond_end47
  %head53 = load i32, i32* %head, align 4, !dbg !61
  %tail54 = load i32, i32* %tail, align 4, !dbg !61
  %eq55 = icmp eq i32 %head53, %tail54, !dbg !61
  br i1 %eq55, label %cond_jump_then56, label %cond_end57, !dbg !61

cond_jump_then56:                                 ; preds = %cond_end51
  br label %string58, !dbg !62

cond_end57:                                       ; preds = %cond_end51
  %tail79 = load i32, i32* %tail, align 4, !dbg !63
  %head80 = load i32, i32* %head, align 4, !dbg !63
  %sub81 = sub i32 %tail79, %head80, !dbg !63
  %add82 = add i32 %sub81, 1, !dbg !63
  %le83 = icmp slt i32 %add82, 1, !dbg !63
  br i1 %le83, label %cond_jump_then84, label %cond_end85, !dbg !63

string58:                                         ; preds = %cond_jump_then56
  %inline_result_variable59 = alloca i8*, align 8, !dbg !62
  %str60 = alloca i8*, align 8, !dbg !62
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @1, i32 0, i32 0), i8** %str60, align 8, !dbg !62
  %str62 = load i8*, i8** %str60, align 8, !dbg !62
  %fun_result63 = call i64 @strlen(i8* %str62), !dbg !62
  %add64 = add i64 %fun_result63, 1, !dbg !62
  %icastM65 = trunc i64 %add64 to i32, !dbg !62
  store i32 %icastM65, i32* %len66, align 4, !dbg !47
  %len67 = load i32, i32* %len66, align 4, !dbg !47
  %icastD68 = sext i32 %len67 to i64, !dbg !47
  %mul69 = mul i64 1, %icastD68, !dbg !47
  %fun_result70 = call i8* @GC_malloc(i64 %mul69), !dbg !47
  store i8* %fun_result70, i8** %result71, align 8, !dbg !47
  %result72 = load i8*, i8** %result71, align 8, !dbg !47
  %str73 = load i8*, i8** %str60, align 8, !dbg !47
  %len74 = load i32, i32* %len66, align 4, !dbg !47
  %icastD75 = sext i32 %len74 to i64, !dbg !47
  %fun_result76 = call i8* @strncpy(i8* %result72, i8* %str73, i64 %icastD75), !dbg !47
  %result77 = load i8*, i8** %result71, align 8, !dbg !47
  store i8* %result77, i8** %inline_result_variable59, align 8, !dbg !47
  br label %string_end61, !dbg !47

string_end61:                                     ; preds = %string58
  %inline_result_variable78 = load i8*, i8** %inline_result_variable59, align 8, !dbg !47
  ret i8* %inline_result_variable78, !dbg !47

cond_jump_then84:                                 ; preds = %cond_end57
  br label %string86, !dbg !64

cond_end85:                                       ; preds = %cond_end57
  %tail107 = load i32, i32* %tail, align 4, !dbg !65
  %head108 = load i32, i32* %head, align 4, !dbg !65
  %sub109 = sub i32 %tail107, %head108, !dbg !65
  %add110 = add i32 %sub109, 1, !dbg !65
  %icastD111 = sext i32 %add110 to i64, !dbg !65
  %mul112 = mul i64 1, %icastD111, !dbg !65
  %fun_result113 = call i8* @GC_malloc(i64 %mul112), !dbg !65
  store i8* %fun_result113, i8** %result114, align 8, !dbg !47
  %result115 = load i8*, i8** %result114, align 8, !dbg !66
  %str116 = load i8*, i8** %str, align 8, !dbg !66
  %head117 = load i32, i32* %head, align 4, !dbg !66
  %ptrToIntC = ptrtoint i8* %str116 to i64, !dbg !66
  %sext = sext i32 %head117 to i64, !dbg !66
  %mul118 = mul i64 %sext, 1, !dbg !66
  %add119 = add i64 %ptrToIntC, %mul118, !dbg !66
  %intToPtr = inttoptr i64 %add119 to i8*, !dbg !66
  %tail120 = load i32, i32* %tail, align 4, !dbg !66
  %head121 = load i32, i32* %head, align 4, !dbg !66
  %sub122 = sub i32 %tail120, %head121, !dbg !66
  %icastD123 = sext i32 %sub122 to i64, !dbg !66
  %fun_result124 = call i8* @memcpy(i8* %result115, i8* %intToPtr, i64 %icastD123), !dbg !66
  %result125 = load i8*, i8** %result114, align 8, !dbg !67
  %tail126 = load i32, i32* %tail, align 4, !dbg !67
  %head127 = load i32, i32* %head, align 4, !dbg !67
  %sub128 = sub i32 %tail126, %head127, !dbg !67
  %element_address = getelementptr i8, i8* %result125, i32 %sub128, !dbg !67
  store i8 0, i8* %element_address, align 1, !dbg !67
  %result129 = load i8*, i8** %result114, align 8, !dbg !68
  ret i8* %result129, !dbg !68

string86:                                         ; preds = %cond_jump_then84
  %inline_result_variable87 = alloca i8*, align 8, !dbg !64
  %str88 = alloca i8*, align 8, !dbg !64
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @2, i32 0, i32 0), i8** %str88, align 8, !dbg !64
  %str90 = load i8*, i8** %str88, align 8, !dbg !64
  %fun_result91 = call i64 @strlen(i8* %str90), !dbg !64
  %add92 = add i64 %fun_result91, 1, !dbg !64
  %icastM93 = trunc i64 %add92 to i32, !dbg !64
  store i32 %icastM93, i32* %len94, align 4, !dbg !47
  %len95 = load i32, i32* %len94, align 4, !dbg !47
  %icastD96 = sext i32 %len95 to i64, !dbg !47
  %mul97 = mul i64 1, %icastD96, !dbg !47
  %fun_result98 = call i8* @GC_malloc(i64 %mul97), !dbg !47
  store i8* %fun_result98, i8** %result99, align 8, !dbg !47
  %result100 = load i8*, i8** %result99, align 8, !dbg !47
  %str101 = load i8*, i8** %str88, align 8, !dbg !47
  %len102 = load i32, i32* %len94, align 4, !dbg !47
  %icastD103 = sext i32 %len102 to i64, !dbg !47
  %fun_result104 = call i8* @strncpy(i8* %result100, i8* %str101, i64 %icastD103), !dbg !47
  %result105 = load i8*, i8** %result99, align 8, !dbg !47
  store i8* %result105, i8** %inline_result_variable87, align 8, !dbg !47
  br label %string_end89, !dbg !47

string_end89:                                     ; preds = %string86
  %inline_result_variable106 = load i8*, i8** %inline_result_variable87, align 8, !dbg !47
  ret i8* %inline_result_variable106, !dbg !47
}

define internal i32 @char_length(i8* %0) !dbg !69 {
entry:
  %str = alloca i8*, align 8, !dbg !70
  store i8* %0, i8** %str, align 8, !dbg !70
  %str1 = load i8*, i8** %str, align 8, !dbg !71
  %fun_result = call i64 @strlen(i8* %str1), !dbg !71
  %icastM = trunc i64 %fun_result to i32, !dbg !71
  ret i32 %icastM, !dbg !71
}

define internal i32 @int_get_hash_key(i32 %0) !dbg !72 {
entry:
  %value = alloca i32, align 4, !dbg !75
  store i32 %0, i32* %value, align 4, !dbg !75
  %value1 = load i32, i32* %value, align 4, !dbg !76
  ret i32 %value1, !dbg !76
}

define internal i32 @char_get_hash_key(i8* %0) !dbg !77 {
entry:
  %p = alloca i8*, align 8, !dbg !78
  %result = alloca i32, align 4, !dbg !78
  %value = alloca i8*, align 8, !dbg !78
  store i8* %0, i8** %value, align 8, !dbg !78
  store i32 0, i32* %result, align 4, !dbg !78
  %value1 = load i8*, i8** %value, align 8, !dbg !79
  store i8* %value1, i8** %p, align 8, !dbg !78
  br label %loop_top_block, !dbg !80

loop_top_block:                                   ; preds = %cond_then_block, %entry
  %p2 = load i8*, i8** %p, align 8, !dbg !81
  %derefference_value = load i8, i8* %p2, align 1, !dbg !81
  %icmpA = icmp ne i8 %derefference_value, 0, !dbg !81
  br i1 %icmpA, label %cond_then_block, label %cond_end_block, !dbg !81

cond_then_block:                                  ; preds = %loop_top_block
  %result3 = load i32, i32* %result, align 4, !dbg !82
  %p4 = load i8*, i8** %p, align 8, !dbg !82
  %derefference_value5 = load i8, i8* %p4, align 1, !dbg !82
  %icastL = sext i8 %derefference_value5 to i32, !dbg !82
  %add = add i32 %result3, %icastL, !dbg !82
  store i32 %add, i32* %result, align 4, !dbg !82
  %p6 = load i8*, i8** %p, align 8, !dbg !82
  %derefference_value7 = load i8, i8* %p6, align 1, !dbg !82
  %icastL8 = sext i8 %derefference_value7 to i32, !dbg !82
  %sub = sub i32 %add, %icastL8, !dbg !82
  %p9 = load i8*, i8** %p, align 8, !dbg !83
  %ptrToIntC = ptrtoint i8* %p9 to i64, !dbg !83
  %add10 = add i64 %ptrToIntC, 1, !dbg !83
  %intToPtr = inttoptr i64 %add10 to i8*, !dbg !83
  store i8* %intToPtr, i8** %p, align 8, !dbg !83
  %ptrToIntI = ptrtoint i8* %intToPtr to i64, !dbg !83
  %sub11 = sub i64 %ptrToIntI, 1, !dbg !83
  %iintToPtr = inttoptr i64 %sub11 to i8*, !dbg !83
  br label %loop_top_block, !dbg !83

cond_end_block:                                   ; preds = %loop_top_block
  %result12 = load i32, i32* %result, align 4, !dbg !80
  ret i32 %result12, !dbg !80
}

define internal i1 @char_equals(i8* %0, i8* %1) !dbg !84 {
entry:
  %left = alloca i8*, align 8, !dbg !87
  store i8* %0, i8** %left, align 8, !dbg !87
  %right = alloca i8*, align 8, !dbg !87
  store i8* %1, i8** %right, align 8, !dbg !87
  %left1 = load i8*, i8** %left, align 8, !dbg !88
  %right2 = load i8*, i8** %right, align 8, !dbg !88
  %fun_result = call i32 @strcmp(i8* %left1, i8* %right2), !dbg !88
  %eq = icmp eq i32 %fun_result, 0, !dbg !88
  ret i1 %eq, !dbg !88
}

define internal i32 @char_compare(i32 %0, i32 %1) !dbg !89 {
entry:
  %left = alloca i32, align 4, !dbg !92
  store i32 %0, i32* %left, align 4, !dbg !92
  %right = alloca i32, align 4, !dbg !92
  store i32 %1, i32* %right, align 4, !dbg !92
  %left1 = load i32, i32* %left, align 4, !dbg !93
  %right2 = load i32, i32* %right, align 4, !dbg !93
  %le = icmp slt i32 %left1, %right2, !dbg !93
  br i1 %le, label %cond_jump_then, label %cond_jump_elif0, !dbg !93

cond_jump_then:                                   ; preds = %entry
  ret i32 -1, !dbg !94

cond_jump_elif0:                                  ; preds = %entry
  %left3 = load i32, i32* %left, align 4, !dbg !95
  %right4 = load i32, i32* %right, align 4, !dbg !95
  %gt = icmp sgt i32 %left3, %right4, !dbg !95
  br i1 %gt, label %cond_jump_elif_then0, label %cond_else_block, !dbg !95

cond_jump_elif_then0:                             ; preds = %cond_jump_elif0
  ret i32 1, !dbg !96

cond_else_block:                                  ; preds = %cond_jump_elif0
  ret i32 0, !dbg !97

cond_end:                                         ; No predecessors!
  ret i32 0, !dbg !92
}

define internal %buffer* @buffer_initialize(%buffer* %0) !dbg !98 {
entry:
  %self = alloca %buffer*, align 8, !dbg !99
  store %buffer* %0, %buffer** %self, align 8, !dbg !99
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !100
  %field = getelementptr inbounds %buffer, %buffer* %self1, i32 0, i32 2, !dbg !100
  store i32 128, i32* %field, align 4, !dbg !100
  %self2 = load %buffer*, %buffer** %self, align 8, !dbg !101
  %self3 = load %buffer*, %buffer** %self, align 8, !dbg !101
  %field4 = getelementptr inbounds %buffer, %buffer* %self3, i32 0, i32 2, !dbg !101
  %size = load i32, i32* %field4, align 4, !dbg !101
  %icastD = sext i32 %size to i64, !dbg !101
  %fun_result = call i8* @GC_malloc(i64 %icastD), !dbg !101
  %field5 = getelementptr inbounds %buffer, %buffer* %self2, i32 0, i32 0, !dbg !101
  store i8* %fun_result, i8** %field5, align 8, !dbg !101
  %self6 = load %buffer*, %buffer** %self, align 8, !dbg !102
  %field7 = getelementptr inbounds %buffer, %buffer* %self6, i32 0, i32 0, !dbg !102
  %buf = load i8*, i8** %field7, align 8, !dbg !102
  %element_address = getelementptr i8, i8* %buf, i32 0, !dbg !102
  store i8 0, i8* %element_address, align 1, !dbg !102
  %self8 = load %buffer*, %buffer** %self, align 8, !dbg !102
  %field9 = getelementptr inbounds %buffer, %buffer* %self8, i32 0, i32 1, !dbg !102
  store i32 0, i32* %field9, align 4, !dbg !102
  %self10 = load %buffer*, %buffer** %self, align 8, !dbg !103
  ret %buffer* %self10, !dbg !103
}

define internal i32 @buffer_length(%buffer* %0) !dbg !104 {
entry:
  %self = alloca %buffer*, align 8, !dbg !105
  store %buffer* %0, %buffer** %self, align 8, !dbg !105
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !106
  %field = getelementptr inbounds %buffer, %buffer* %self1, i32 0, i32 1, !dbg !106
  %len = load i32, i32* %field, align 4, !dbg !106
  ret i32 %len, !dbg !106
}

define internal void @buffer_append(%buffer* %0, i8* %1, i64 %2) !dbg !107 {
entry:
  %new_size = alloca i32, align 4, !dbg !111
  %self = alloca %buffer*, align 8, !dbg !111
  store %buffer* %0, %buffer** %self, align 8, !dbg !111
  %mem = alloca i8*, align 8, !dbg !111
  store i8* %1, i8** %mem, align 8, !dbg !111
  %size = alloca i64, align 8, !dbg !111
  store i64 %2, i64* %size, align 4, !dbg !111
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !112
  %field = getelementptr inbounds %buffer, %buffer* %self1, i32 0, i32 1, !dbg !112
  %len = load i32, i32* %field, align 4, !dbg !112
  %size2 = load i64, i64* %size, align 4, !dbg !112
  %icastM = trunc i64 %size2 to i32, !dbg !112
  %add = add i32 %len, %icastM, !dbg !112
  %add3 = add i32 %add, 1, !dbg !112
  %add4 = add i32 %add3, 1, !dbg !112
  %self5 = load %buffer*, %buffer** %self, align 8, !dbg !112
  %field6 = getelementptr inbounds %buffer, %buffer* %self5, i32 0, i32 2, !dbg !112
  %size7 = load i32, i32* %field6, align 4, !dbg !112
  %gteq = icmp sge i32 %add4, %size7, !dbg !112
  br i1 %gteq, label %cond_jump_then, label %cond_end, !dbg !112

cond_jump_then:                                   ; preds = %entry
  %self8 = load %buffer*, %buffer** %self, align 8, !dbg !113
  %field9 = getelementptr inbounds %buffer, %buffer* %self8, i32 0, i32 2, !dbg !113
  %size10 = load i32, i32* %field9, align 4, !dbg !113
  %size11 = load i64, i64* %size, align 4, !dbg !113
  %icastM12 = trunc i64 %size11 to i32, !dbg !113
  %add13 = add i32 %size10, %icastM12, !dbg !113
  %add14 = add i32 %add13, 1, !dbg !113
  %mul = mul i32 %add14, 2, !dbg !113
  store i32 %mul, i32* %new_size, align 4, !dbg !111
  %self15 = load %buffer*, %buffer** %self, align 8, !dbg !114
  %self16 = load %buffer*, %buffer** %self, align 8, !dbg !114
  %field17 = getelementptr inbounds %buffer, %buffer* %self16, i32 0, i32 0, !dbg !114
  %buf = load i8*, i8** %field17, align 8, !dbg !114
  %new_size18 = load i32, i32* %new_size, align 4, !dbg !114
  %icastD = sext i32 %new_size18 to i64, !dbg !114
  %fun_result = call i8* @GC_realloc(i8* %buf, i64 %icastD), !dbg !114
  %field19 = getelementptr inbounds %buffer, %buffer* %self15, i32 0, i32 0, !dbg !114
  store i8* %fun_result, i8** %field19, align 8, !dbg !114
  %self20 = load %buffer*, %buffer** %self, align 8, !dbg !115
  %new_size21 = load i32, i32* %new_size, align 4, !dbg !115
  %field22 = getelementptr inbounds %buffer, %buffer* %self20, i32 0, i32 2, !dbg !115
  store i32 %new_size21, i32* %field22, align 4, !dbg !115
  br label %cond_end, !dbg !115

cond_end:                                         ; preds = %cond_jump_then, %entry
  %self23 = load %buffer*, %buffer** %self, align 8, !dbg !116
  %field24 = getelementptr inbounds %buffer, %buffer* %self23, i32 0, i32 0, !dbg !116
  %buf25 = load i8*, i8** %field24, align 8, !dbg !116
  %self26 = load %buffer*, %buffer** %self, align 8, !dbg !116
  %field27 = getelementptr inbounds %buffer, %buffer* %self26, i32 0, i32 1, !dbg !116
  %len28 = load i32, i32* %field27, align 4, !dbg !116
  %ptrToIntC = ptrtoint i8* %buf25 to i64, !dbg !116
  %sext = sext i32 %len28 to i64, !dbg !116
  %mul29 = mul i64 %sext, 1, !dbg !116
  %add30 = add i64 %ptrToIntC, %mul29, !dbg !116
  %intToPtr = inttoptr i64 %add30 to i8*, !dbg !116
  %mem31 = load i8*, i8** %mem, align 8, !dbg !116
  %size32 = load i64, i64* %size, align 4, !dbg !116
  %fun_result33 = call i8* @memcpy(i8* %intToPtr, i8* %mem31, i64 %size32), !dbg !116
  %self34 = load %buffer*, %buffer** %self, align 8, !dbg !117
  %self35 = load %buffer*, %buffer** %self, align 8, !dbg !117
  %field36 = getelementptr inbounds %buffer, %buffer* %self35, i32 0, i32 1, !dbg !117
  %len37 = load i32, i32* %field36, align 4, !dbg !117
  %size38 = load i64, i64* %size, align 4, !dbg !117
  %icastM39 = trunc i64 %size38 to i32, !dbg !117
  %add40 = add i32 %len37, %icastM39, !dbg !117
  %field41 = getelementptr inbounds %buffer, %buffer* %self34, i32 0, i32 1, !dbg !117
  store i32 %add40, i32* %field41, align 4, !dbg !117
  %self42 = load %buffer*, %buffer** %self, align 8, !dbg !118
  %field43 = getelementptr inbounds %buffer, %buffer* %self42, i32 0, i32 0, !dbg !118
  %buf44 = load i8*, i8** %field43, align 8, !dbg !118
  %self45 = load %buffer*, %buffer** %self, align 8, !dbg !118
  %field46 = getelementptr inbounds %buffer, %buffer* %self45, i32 0, i32 1, !dbg !118
  %len47 = load i32, i32* %field46, align 4, !dbg !118
  %element_address = getelementptr i8, i8* %buf44, i32 %len47, !dbg !118
  store i8 0, i8* %element_address, align 1, !dbg !118
  ret void, !dbg !118
}

define internal void @buffer_append_char(%buffer* %0, i8 %1) !dbg !119 {
entry:
  %new_size = alloca i32, align 4, !dbg !123
  %self = alloca %buffer*, align 8, !dbg !123
  store %buffer* %0, %buffer** %self, align 8, !dbg !123
  %c = alloca i8, align 1, !dbg !123
  store i8 %1, i8* %c, align 1, !dbg !123
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !124
  %field = getelementptr inbounds %buffer, %buffer* %self1, i32 0, i32 1, !dbg !124
  %len = load i32, i32* %field, align 4, !dbg !124
  %add = add i32 %len, 1, !dbg !124
  %add2 = add i32 %add, 1, !dbg !124
  %add3 = add i32 %add2, 1, !dbg !124
  %self4 = load %buffer*, %buffer** %self, align 8, !dbg !124
  %field5 = getelementptr inbounds %buffer, %buffer* %self4, i32 0, i32 2, !dbg !124
  %size = load i32, i32* %field5, align 4, !dbg !124
  %gteq = icmp sge i32 %add3, %size, !dbg !124
  br i1 %gteq, label %cond_jump_then, label %cond_end, !dbg !124

cond_jump_then:                                   ; preds = %entry
  %self6 = load %buffer*, %buffer** %self, align 8, !dbg !125
  %field7 = getelementptr inbounds %buffer, %buffer* %self6, i32 0, i32 2, !dbg !125
  %size8 = load i32, i32* %field7, align 4, !dbg !125
  %add9 = add i32 %size8, 10, !dbg !125
  %add10 = add i32 %add9, 1, !dbg !125
  %mul = mul i32 %add10, 2, !dbg !125
  store i32 %mul, i32* %new_size, align 4, !dbg !123
  %self11 = load %buffer*, %buffer** %self, align 8, !dbg !126
  %self12 = load %buffer*, %buffer** %self, align 8, !dbg !126
  %field13 = getelementptr inbounds %buffer, %buffer* %self12, i32 0, i32 0, !dbg !126
  %buf = load i8*, i8** %field13, align 8, !dbg !126
  %new_size14 = load i32, i32* %new_size, align 4, !dbg !126
  %icastD = sext i32 %new_size14 to i64, !dbg !126
  %fun_result = call i8* @GC_realloc(i8* %buf, i64 %icastD), !dbg !126
  %field15 = getelementptr inbounds %buffer, %buffer* %self11, i32 0, i32 0, !dbg !126
  store i8* %fun_result, i8** %field15, align 8, !dbg !126
  %self16 = load %buffer*, %buffer** %self, align 8, !dbg !127
  %new_size17 = load i32, i32* %new_size, align 4, !dbg !127
  %field18 = getelementptr inbounds %buffer, %buffer* %self16, i32 0, i32 2, !dbg !127
  store i32 %new_size17, i32* %field18, align 4, !dbg !127
  br label %cond_end, !dbg !127

cond_end:                                         ; preds = %cond_jump_then, %entry
  %self19 = load %buffer*, %buffer** %self, align 8, !dbg !128
  %field20 = getelementptr inbounds %buffer, %buffer* %self19, i32 0, i32 0, !dbg !128
  %buf21 = load i8*, i8** %field20, align 8, !dbg !128
  %self22 = load %buffer*, %buffer** %self, align 8, !dbg !128
  %field23 = getelementptr inbounds %buffer, %buffer* %self22, i32 0, i32 1, !dbg !128
  %len24 = load i32, i32* %field23, align 4, !dbg !128
  %c25 = load i8, i8* %c, align 1, !dbg !128
  %element_address = getelementptr i8, i8* %buf21, i32 %len24, !dbg !128
  store i8 %c25, i8* %element_address, align 1, !dbg !128
  %self26 = load %buffer*, %buffer** %self, align 8, !dbg !129
  %self27 = load %buffer*, %buffer** %self, align 8, !dbg !129
  %field28 = getelementptr inbounds %buffer, %buffer* %self27, i32 0, i32 1, !dbg !129
  %len29 = load i32, i32* %field28, align 4, !dbg !129
  %add30 = add i32 %len29, 1, !dbg !129
  %field31 = getelementptr inbounds %buffer, %buffer* %self26, i32 0, i32 1, !dbg !129
  store i32 %add30, i32* %field31, align 4, !dbg !129
  %sub = sub i32 %add30, 1, !dbg !129
  %self32 = load %buffer*, %buffer** %self, align 8, !dbg !130
  %field33 = getelementptr inbounds %buffer, %buffer* %self32, i32 0, i32 0, !dbg !130
  %buf34 = load i8*, i8** %field33, align 8, !dbg !130
  %self35 = load %buffer*, %buffer** %self, align 8, !dbg !130
  %field36 = getelementptr inbounds %buffer, %buffer* %self35, i32 0, i32 1, !dbg !130
  %len37 = load i32, i32* %field36, align 4, !dbg !130
  %element_address38 = getelementptr i8, i8* %buf34, i32 %len37, !dbg !130
  store i8 0, i8* %element_address38, align 1, !dbg !130
  ret void, !dbg !130
}

define internal void @buffer_append_str(%buffer* %0, i8* %1) !dbg !131 {
entry:
  %self = alloca %buffer*, align 8, !dbg !132
  store %buffer* %0, %buffer** %self, align 8, !dbg !132
  %str = alloca i8*, align 8, !dbg !132
  store i8* %1, i8** %str, align 8, !dbg !132
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !133
  %str2 = load i8*, i8** %str, align 8, !dbg !133
  %str3 = load i8*, i8** %str, align 8, !dbg !133
  %fun_result = call i64 @strlen(i8* %str3), !dbg !133
  call void @buffer_append(%buffer* %self1, i8* %str2, i64 %fun_result), !dbg !133
  ret void, !dbg !133
}

define internal void @buffer_append_nullterminated_str(%buffer* %0, i8* %1) !dbg !134 {
entry:
  %self = alloca %buffer*, align 8, !dbg !135
  store %buffer* %0, %buffer** %self, align 8, !dbg !135
  %str = alloca i8*, align 8, !dbg !135
  store i8* %1, i8** %str, align 8, !dbg !135
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !136
  %str2 = load i8*, i8** %str, align 8, !dbg !136
  %str3 = load i8*, i8** %str, align 8, !dbg !136
  %fun_result = call i64 @strlen(i8* %str3), !dbg !136
  call void @buffer_append(%buffer* %self1, i8* %str2, i64 %fun_result), !dbg !136
  %self4 = load %buffer*, %buffer** %self, align 8, !dbg !137
  call void @buffer_append_char(%buffer* %self4, i8 0), !dbg !137
  ret void, !dbg !137
}

define internal i8* @buffer_to_string(%buffer* %0) !dbg !138 {
entry:
  %result = alloca i8*, align 8, !dbg !139
  %len = alloca i32, align 4, !dbg !139
  %self = alloca %buffer*, align 8, !dbg !139
  store %buffer* %0, %buffer** %self, align 8, !dbg !139
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !140
  %field = getelementptr inbounds %buffer, %buffer* %self1, i32 0, i32 0, !dbg !140
  %buf = load i8*, i8** %field, align 8, !dbg !140
  br label %string, !dbg !140

string:                                           ; preds = %entry
  %inline_result_variable = alloca i8*, align 8, !dbg !140
  %str = alloca i8*, align 8, !dbg !140
  store i8* %buf, i8** %str, align 8, !dbg !140
  %str2 = load i8*, i8** %str, align 8, !dbg !140
  %fun_result = call i64 @strlen(i8* %str2), !dbg !140
  %add = add i64 %fun_result, 1, !dbg !140
  %icastM = trunc i64 %add to i32, !dbg !140
  store i32 %icastM, i32* %len, align 4, !dbg !139
  %len3 = load i32, i32* %len, align 4, !dbg !139
  %icastD = sext i32 %len3 to i64, !dbg !139
  %mul = mul i64 1, %icastD, !dbg !139
  %fun_result4 = call i8* @GC_malloc(i64 %mul), !dbg !139
  store i8* %fun_result4, i8** %result, align 8, !dbg !139
  %result5 = load i8*, i8** %result, align 8, !dbg !139
  %str6 = load i8*, i8** %str, align 8, !dbg !139
  %len7 = load i32, i32* %len, align 4, !dbg !139
  %icastD8 = sext i32 %len7 to i64, !dbg !139
  %fun_result9 = call i8* @strncpy(i8* %result5, i8* %str6, i64 %icastD8), !dbg !139
  %result10 = load i8*, i8** %result, align 8, !dbg !139
  store i8* %result10, i8** %inline_result_variable, align 8, !dbg !139
  br label %string_end, !dbg !139

string_end:                                       ; preds = %string
  %inline_result_variable11 = load i8*, i8** %inline_result_variable, align 8, !dbg !139
  ret i8* %inline_result_variable11, !dbg !139
}

define internal void @buffer_append_int(%buffer* %0, i32 %1) !dbg !141 {
entry:
  %self = alloca %buffer*, align 8, !dbg !144
  store %buffer* %0, %buffer** %self, align 8, !dbg !144
  %value = alloca i32, align 4, !dbg !144
  store i32 %1, i32* %value, align 4, !dbg !144
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !145
  %value2 = load i32, i32* %value, align 4, !dbg !145
  %castAQ = bitcast i32* %value to i8*, !dbg !145
  call void @buffer_append(%buffer* %self1, i8* %castAQ, i64 4), !dbg !145
  ret void, !dbg !145
}

define internal void @buffer_append_long(%buffer* %0, i64 %1) !dbg !146 {
entry:
  %self = alloca %buffer*, align 8, !dbg !149
  store %buffer* %0, %buffer** %self, align 8, !dbg !149
  %value = alloca i64, align 8, !dbg !149
  store i64 %1, i64* %value, align 4, !dbg !149
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !150
  %value2 = load i64, i64* %value, align 4, !dbg !150
  %castAQ = bitcast i64* %value to i8*, !dbg !150
  call void @buffer_append(%buffer* %self1, i8* %castAQ, i64 8), !dbg !150
  ret void, !dbg !150
}

define internal void @buffer_append_short(%buffer* %0, i16 %1) !dbg !151 {
entry:
  %self = alloca %buffer*, align 8, !dbg !155
  store %buffer* %0, %buffer** %self, align 8, !dbg !155
  %value = alloca i16, align 2, !dbg !155
  store i16 %1, i16* %value, align 2, !dbg !155
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !156
  %value2 = load i16, i16* %value, align 2, !dbg !156
  %castAQ = bitcast i16* %value to i8*, !dbg !156
  call void @buffer_append(%buffer* %self1, i8* %castAQ, i64 2), !dbg !156
  ret void, !dbg !156
}

define internal void @buffer_alignment(%buffer* %0) !dbg !157 {
entry:
  %i = alloca i32, align 4, !dbg !158
  %len2 = alloca i32, align 4, !dbg !158
  %self = alloca %buffer*, align 8, !dbg !158
  store %buffer* %0, %buffer** %self, align 8, !dbg !158
  %self1 = load %buffer*, %buffer** %self, align 8, !dbg !159
  %field = getelementptr inbounds %buffer, %buffer* %self1, i32 0, i32 1, !dbg !159
  %len = load i32, i32* %field, align 4, !dbg !159
  store i32 %len, i32* %len2, align 4, !dbg !158
  %len3 = load i32, i32* %len2, align 4, !dbg !160
  %add = add i32 %len3, 3, !dbg !160
  %andtmp = and i32 %add, -4, !dbg !160
  store i32 %andtmp, i32* %len2, align 4, !dbg !160
  %self4 = load %buffer*, %buffer** %self, align 8, !dbg !161
  %field5 = getelementptr inbounds %buffer, %buffer* %self4, i32 0, i32 1, !dbg !161
  %len6 = load i32, i32* %field5, align 4, !dbg !161
  store i32 %len6, i32* %i, align 4, !dbg !158
  br label %loop_top_block, !dbg !158

loop_top_block:                                   ; preds = %cond_then_block, %entry
  %i7 = load i32, i32* %i, align 4, !dbg !161
  %len8 = load i32, i32* %len2, align 4, !dbg !161
  %le = icmp slt i32 %i7, %len8, !dbg !161
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !161

cond_then_block:                                  ; preds = %loop_top_block
  %self9 = load %buffer*, %buffer** %self, align 8, !dbg !162
  call void @buffer_append_char(%buffer* %self9, i8 0), !dbg !162
  %i10 = load i32, i32* %i, align 4, !dbg !161
  %add11 = add i32 %i10, 1, !dbg !161
  store i32 %add11, i32* %i, align 4, !dbg !161
  %sub = sub i32 %add11, 1, !dbg !161
  br label %loop_top_block, !dbg !161

cond_end_block:                                   ; preds = %loop_top_block
  ret void, !dbg !161
}

define internal i32 @buffer_compare(%buffer* %0, %buffer* %1) !dbg !163 {
entry:
  %left = alloca %buffer*, align 8, !dbg !164
  store %buffer* %0, %buffer** %left, align 8, !dbg !164
  %right = alloca %buffer*, align 8, !dbg !164
  store %buffer* %1, %buffer** %right, align 8, !dbg !164
  %left1 = load %buffer*, %buffer** %left, align 8, !dbg !165
  %field = getelementptr inbounds %buffer, %buffer* %left1, i32 0, i32 0, !dbg !165
  %buf = load i8*, i8** %field, align 8, !dbg !165
  %right2 = load %buffer*, %buffer** %right, align 8, !dbg !165
  %field3 = getelementptr inbounds %buffer, %buffer* %right2, i32 0, i32 0, !dbg !165
  %buf4 = load i8*, i8** %field3, align 8, !dbg !165
  %fun_result = call i32 @strcmp(i8* %buf, i8* %buf4), !dbg !165
  ret i32 %fun_result, !dbg !165
}

define internal %buffer* @char_to_buffer(i8* %0) !dbg !166 {
entry:
  %result = alloca %buffer*, align 8, !dbg !167
  %self = alloca i8*, align 8, !dbg !167
  store i8* %0, i8** %self, align 8, !dbg !167
  %fun_result = call i8* @GC_malloc(i64 16), !dbg !168
  %obj = bitcast i8* %fun_result to %buffer*, !dbg !168
  %fun_result1 = call %buffer* @buffer_initialize(%buffer* %obj), !dbg !168
  store %buffer* %fun_result1, %buffer** %result, align 8, !dbg !167
  %result2 = load %buffer*, %buffer** %result, align 8, !dbg !169
  %self3 = load i8*, i8** %self, align 8, !dbg !169
  call void @buffer_append_str(%buffer* %result2, i8* %self3), !dbg !169
  %result4 = load %buffer*, %buffer** %result, align 8, !dbg !170
  ret %buffer* %result4, !dbg !170
}

define internal void @come_fd_zero(%come_anon8* %0) !dbg !171 {
entry:
  %__arr = alloca %come_anon8*, align 8, !dbg !172
  %__i = alloca i32, align 4, !dbg !172
  %fds = alloca %come_anon8*, align 8, !dbg !172
  store %come_anon8* %0, %come_anon8** %fds, align 8, !dbg !172
  br label %loop_top_block, !dbg !173

loop_top_block:                                   ; preds = %cond_end_block4, %entry
  %fds1 = load %come_anon8*, %come_anon8** %fds, align 8, !dbg !173
  store %come_anon8* %fds1, %come_anon8** %__arr, align 8, !dbg !172
  store i32 0, i32* %__i, align 4, !dbg !173
  br label %loop_top_block2, !dbg !173

cond_end_block:                                   ; preds = %cond_end_block4
  ret void, !dbg !173

loop_top_block2:                                  ; preds = %cond_then_block, %loop_top_block
  %__i3 = load i32, i32* %__i, align 4, !dbg !173
  %le = icmp ult i32 %__i3, 16, !dbg !173
  br i1 %le, label %cond_then_block, label %cond_end_block4, !dbg !173

cond_then_block:                                  ; preds = %loop_top_block2
  %__arr5 = load %come_anon8*, %come_anon8** %__arr, align 8, !dbg !173
  %field = getelementptr inbounds %come_anon8, %come_anon8* %__arr5, i32 0, i32 0, !dbg !173
  %__i6 = load i32, i32* %__i, align 4, !dbg !173
  %array_cast = bitcast [16 x i64]* %field to i64*, !dbg !173
  %gep = getelementptr i64, i64* %array_cast, i32 %__i6, !dbg !173
  store i64 0, i64* %gep, align 4, !dbg !173
  %__i7 = load i32, i32* %__i, align 4, !dbg !173
  %add = add i32 %__i7, 1, !dbg !173
  store i32 %add, i32* %__i, align 4, !dbg !173
  br label %loop_top_block2, !dbg !173

cond_end_block4:                                  ; preds = %loop_top_block2
  br i1 false, label %loop_top_block, label %cond_end_block, !dbg !173
}

define internal void @come_fd_set(i32 %0, %come_anon8* %1) !dbg !174 {
entry:
  %fd = alloca i32, align 4, !dbg !177
  store i32 %0, i32* %fd, align 4, !dbg !177
  %fds = alloca %come_anon8*, align 8, !dbg !177
  store %come_anon8* %1, %come_anon8** %fds, align 8, !dbg !177
  %fds1 = load %come_anon8*, %come_anon8** %fds, align 8, !dbg !178
  %field = getelementptr inbounds %come_anon8, %come_anon8* %fds1, i32 0, i32 0, !dbg !178
  %fd2 = load i32, i32* %fd, align 4, !dbg !178
  %div = sdiv i32 %fd2, 64, !dbg !178
  %array_cast = bitcast [16 x i64]* %field to i64*, !dbg !178
  %gep = getelementptr i64, i64* %array_cast, i32 %div, !dbg !178
  %element = load i64, i64* %gep, align 4, !dbg !178
  %fd3 = load i32, i32* %fd, align 4, !dbg !178
  %div4 = srem i32 %fd3, 64, !dbg !178
  %icastD = sext i32 %div4 to i64, !dbg !178
  %lshifttmp = shl i64 1, %icastD, !dbg !178
  %load = load i64, i64* %gep, align 4, !dbg !178
  %ortmp = or i64 %load, %lshifttmp, !dbg !178
  store i64 %ortmp, i64* %gep, align 4, !dbg !178
  ret void, !dbg !178
}

define internal i32 @come_fd_isset(i32 %0, %come_anon8* %1) !dbg !179 {
entry:
  %fd = alloca i32, align 4, !dbg !180
  store i32 %0, i32* %fd, align 4, !dbg !180
  %fds = alloca %come_anon8*, align 8, !dbg !180
  store %come_anon8* %1, %come_anon8** %fds, align 8, !dbg !180
  %fds1 = load %come_anon8*, %come_anon8** %fds, align 8, !dbg !181
  %field = getelementptr inbounds %come_anon8, %come_anon8* %fds1, i32 0, i32 0, !dbg !181
  %fd2 = load i32, i32* %fd, align 4, !dbg !181
  %div = sdiv i32 %fd2, 64, !dbg !181
  %array_cast = bitcast [16 x i64]* %field to i64*, !dbg !181
  %gep = getelementptr i64, i64* %array_cast, i32 %div, !dbg !181
  %element = load i64, i64* %gep, align 4, !dbg !181
  %fd3 = load i32, i32* %fd, align 4, !dbg !181
  %div4 = srem i32 %fd3, 64, !dbg !181
  %icastD = sext i32 %div4 to i64, !dbg !181
  %lshifttmp = shl i64 1, %icastD, !dbg !181
  %andtmp = and i64 %element, %lshifttmp, !dbg !181
  %not_eq = icmp ne i64 %andtmp, 0, !dbg !181
  %icastL = sext i1 %not_eq to i32, !dbg !181
  ret i32 %icastL, !dbg !181
}

define internal i32 @int_expect(i32 %0, i8* %1, void (i8*)* %2) !dbg !182 {
entry:
  %self = alloca i32, align 4, !dbg !185
  store i32 %0, i32* %self, align 4, !dbg !185
  %parent = alloca i8*, align 8, !dbg !185
  store i8* %1, i8** %parent, align 8, !dbg !185
  %block = alloca void (i8*)*, align 8, !dbg !185
  store void (i8*)* %2, void (i8*)** %block, align 8, !dbg !185
  %self1 = load i32, i32* %self, align 4, !dbg !186
  %le = icmp slt i32 %self1, 0, !dbg !186
  br i1 %le, label %cond_jump_then, label %cond_end, !dbg !186

cond_jump_then:                                   ; preds = %entry
  %block2 = load void (i8*)*, void (i8*)** %block, align 8, !dbg !187
  %parent3 = load i8*, i8** %parent, align 8, !dbg !187
  call void %block2(i8* %parent3), !dbg !187
  br label %cond_end, !dbg !187

cond_end:                                         ; preds = %cond_jump_then, %entry
  %self4 = load i32, i32* %self, align 4, !dbg !188
  ret i32 %self4, !dbg !188
}

define internal i1 @bool_expect(i1 %0, i8* %1, void (i8*)* %2) !dbg !189 {
entry:
  %self = alloca i1, align 1, !dbg !192
  store i1 %0, i1* %self, align 1, !dbg !192
  %parent = alloca i8*, align 8, !dbg !192
  store i8* %1, i8** %parent, align 8, !dbg !192
  %block = alloca void (i8*)*, align 8, !dbg !192
  store void (i8*)* %2, void (i8*)** %block, align 8, !dbg !192
  %self1 = load i1, i1* %self, align 1, !dbg !193
  %logical_denial = icmp eq i1 %self1, false, !dbg !193
  br i1 %logical_denial, label %cond_jump_then, label %cond_end, !dbg !193

cond_jump_then:                                   ; preds = %entry
  %block2 = load void (i8*)*, void (i8*)** %block, align 8, !dbg !194
  %parent3 = load i8*, i8** %parent, align 8, !dbg !194
  call void %block2(i8* %parent3), !dbg !194
  br label %cond_end, !dbg !194

cond_end:                                         ; preds = %cond_jump_then, %entry
  %self4 = load i1, i1* %self, align 1, !dbg !195
  ret i1 %self4, !dbg !195
}

define internal void @int_times(i32 %0, i8* %1, void (i8*)* %2) !dbg !196 {
entry:
  %i = alloca i32, align 4, !dbg !197
  %self = alloca i32, align 4, !dbg !197
  store i32 %0, i32* %self, align 4, !dbg !197
  %parent = alloca i8*, align 8, !dbg !197
  store i8* %1, i8** %parent, align 8, !dbg !197
  %block = alloca void (i8*)*, align 8, !dbg !197
  store void (i8*)* %2, void (i8*)** %block, align 8, !dbg !197
  store i32 0, i32* %i, align 4, !dbg !198
  br label %loop_top_block, !dbg !198

loop_top_block:                                   ; preds = %cond_then_block, %entry
  %i1 = load i32, i32* %i, align 4, !dbg !198
  %self2 = load i32, i32* %self, align 4, !dbg !198
  %le = icmp slt i32 %i1, %self2, !dbg !198
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !198

cond_then_block:                                  ; preds = %loop_top_block
  %block3 = load void (i8*)*, void (i8*)** %block, align 8, !dbg !199
  %parent4 = load i8*, i8** %parent, align 8, !dbg !199
  call void %block3(i8* %parent4), !dbg !199
  %i5 = load i32, i32* %i, align 4, !dbg !198
  %add = add i32 %i5, 1, !dbg !198
  store i32 %add, i32* %i, align 4, !dbg !198
  %sub = sub i32 %add, 1, !dbg !198
  br label %loop_top_block, !dbg !198

cond_end_block:                                   ; preds = %loop_top_block
  ret void, !dbg !198
}

define internal i1 @xiswalpha(i32 %0) !dbg !200 {
entry:
  %result = alloca i1, align 1, !dbg !201
  %andand6 = alloca i1, align 1, !dbg !201
  %andand = alloca i1, align 1, !dbg !201
  %oror = alloca i1, align 1, !dbg !201
  %c = alloca i32, align 4, !dbg !201
  store i32 %0, i32* %c, align 4, !dbg !201
  %c1 = load i32, i32* %c, align 4, !dbg !202
  %gteq = icmp sge i32 %c1, 97, !dbg !202
  store i1 %gteq, i1* %andand, align 1, !dbg !202
  br i1 %gteq, label %cond_jump_then, label %cond_jump_end, !dbg !202

cond_jump_then:                                   ; preds = %entry
  %c2 = load i32, i32* %c, align 4, !dbg !202
  %leeq = icmp sle i32 %c2, 122, !dbg !202
  %andand3 = and i1 %gteq, %leeq, !dbg !202
  store i1 %andand3, i1* %andand, align 1, !dbg !202
  br label %cond_jump_end, !dbg !202

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %andand_result_value = load i1, i1* %andand, align 1, !dbg !202
  store i1 %andand_result_value, i1* %oror, align 1, !dbg !202
  br i1 %andand_result_value, label %cond_jump_end5, label %cond_jump_then4, !dbg !202

cond_jump_then4:                                  ; preds = %cond_jump_end
  %c7 = load i32, i32* %c, align 4, !dbg !202
  %gteq8 = icmp sge i32 %c7, 65, !dbg !202
  store i1 %gteq8, i1* %andand6, align 1, !dbg !202
  br i1 %gteq8, label %cond_jump_then9, label %cond_jump_end10, !dbg !202

cond_jump_end5:                                   ; preds = %cond_jump_end10, %cond_jump_end
  %oror_result_value = load i1, i1* %oror, align 1, !dbg !202
  store i1 %oror_result_value, i1* %result, align 1, !dbg !201
  %result16 = load i1, i1* %result, align 1, !dbg !203
  ret i1 %result16, !dbg !203

cond_jump_then9:                                  ; preds = %cond_jump_then4
  %c11 = load i32, i32* %c, align 4, !dbg !202
  %leeq12 = icmp sle i32 %c11, 90, !dbg !202
  %andand13 = and i1 %gteq8, %leeq12, !dbg !202
  store i1 %andand13, i1* %andand6, align 1, !dbg !202
  br label %cond_jump_end10, !dbg !202

cond_jump_end10:                                  ; preds = %cond_jump_then9, %cond_jump_then4
  %andand_result_value14 = load i1, i1* %andand6, align 1, !dbg !202
  %oror15 = or i1 %andand_result_value, %andand_result_value14, !dbg !202
  store i1 %oror15, i1* %oror, align 1, !dbg !202
  br label %cond_jump_end5, !dbg !202
}

define internal i1 @xiswblank(i32 %0) !dbg !204 {
entry:
  %oror = alloca i1, align 1, !dbg !205
  %c = alloca i32, align 4, !dbg !205
  store i32 %0, i32* %c, align 4, !dbg !205
  %c1 = load i32, i32* %c, align 4, !dbg !206
  %eq = icmp eq i32 %c1, 32, !dbg !206
  store i1 %eq, i1* %oror, align 1, !dbg !206
  br i1 %eq, label %cond_jump_end, label %cond_jump_then, !dbg !206

cond_jump_then:                                   ; preds = %entry
  %c2 = load i32, i32* %c, align 4, !dbg !206
  %eq3 = icmp eq i32 %c2, 9, !dbg !206
  %oror4 = or i1 %eq, %eq3, !dbg !206
  store i1 %oror4, i1* %oror, align 1, !dbg !206
  br label %cond_jump_end, !dbg !206

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %oror_result_value = load i1, i1* %oror, align 1, !dbg !206
  ret i1 %oror_result_value, !dbg !206
}

define internal i1 @xiswdigit(i32 %0) !dbg !207 {
entry:
  %andand = alloca i1, align 1, !dbg !208
  %c = alloca i32, align 4, !dbg !208
  store i32 %0, i32* %c, align 4, !dbg !208
  %c1 = load i32, i32* %c, align 4, !dbg !209
  %gteq = icmp sge i32 %c1, 48, !dbg !209
  store i1 %gteq, i1* %andand, align 1, !dbg !209
  br i1 %gteq, label %cond_jump_then, label %cond_jump_end, !dbg !209

cond_jump_then:                                   ; preds = %entry
  %c2 = load i32, i32* %c, align 4, !dbg !209
  %leeq = icmp sle i32 %c2, 57, !dbg !209
  %andand3 = and i1 %gteq, %leeq, !dbg !209
  store i1 %andand3, i1* %andand, align 1, !dbg !209
  br label %cond_jump_end, !dbg !209

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %andand_result_value = load i1, i1* %andand, align 1, !dbg !209
  ret i1 %andand_result_value, !dbg !209
}

define internal i1 @xiswalnum(i32 %0) !dbg !210 {
entry:
  %oror = alloca i1, align 1, !dbg !211
  %c = alloca i32, align 4, !dbg !211
  store i32 %0, i32* %c, align 4, !dbg !211
  %c1 = load i32, i32* %c, align 4, !dbg !212
  %fun_result = call i1 @xiswalpha(i32 %c1), !dbg !212
  store i1 %fun_result, i1* %oror, align 1, !dbg !212
  br i1 %fun_result, label %cond_jump_end, label %cond_jump_then, !dbg !212

cond_jump_then:                                   ; preds = %entry
  %c2 = load i32, i32* %c, align 4, !dbg !212
  %fun_result3 = call i1 @xiswdigit(i32 %c2), !dbg !212
  %oror4 = or i1 %fun_result, %fun_result3, !dbg !212
  store i1 %oror4, i1* %oror, align 1, !dbg !212
  br label %cond_jump_end, !dbg !212

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %oror_result_value = load i1, i1* %oror, align 1, !dbg !212
  ret i1 %oror_result_value, !dbg !212
}

define internal i8* @xbasename(i8* %0) !dbg !213 {
entry:
  %result46 = alloca i8*, align 8, !dbg !214
  %len41 = alloca i32, align 4, !dbg !214
  %result = alloca i8*, align 8, !dbg !214
  %len = alloca i32, align 4, !dbg !214
  %p = alloca i8*, align 8, !dbg !214
  %path = alloca i8*, align 8, !dbg !214
  store i8* %0, i8** %path, align 8, !dbg !214
  %path1 = load i8*, i8** %path, align 8, !dbg !215
  %path2 = load i8*, i8** %path, align 8, !dbg !215
  %fun_result = call i64 @strlen(i8* %path2), !dbg !215
  %ptrToIntC = ptrtoint i8* %path1 to i64, !dbg !215
  %mul = mul i64 %fun_result, 1, !dbg !215
  %add = add i64 %ptrToIntC, %mul, !dbg !215
  %intToPtr = inttoptr i64 %add to i8*, !dbg !215
  store i8* %intToPtr, i8** %p, align 8, !dbg !214
  br label %loop_top_block, !dbg !216

loop_top_block:                                   ; preds = %cond_end, %entry
  %p3 = load i8*, i8** %p, align 8, !dbg !217
  %path4 = load i8*, i8** %path, align 8, !dbg !217
  %gteq = icmp sge i8* %p3, %path4, !dbg !217
  br i1 %gteq, label %cond_then_block, label %cond_end_block, !dbg !217

cond_then_block:                                  ; preds = %loop_top_block
  %p5 = load i8*, i8** %p, align 8, !dbg !218
  %derefference_value = load i8, i8* %p5, align 1, !dbg !218
  %eq = icmp eq i8 %derefference_value, 47, !dbg !218
  br i1 %eq, label %cond_jump_then, label %cond_else_block, !dbg !218

cond_end_block:                                   ; preds = %cond_jump_then, %loop_top_block
  %p10 = load i8*, i8** %p, align 8, !dbg !216
  %path11 = load i8*, i8** %path, align 8, !dbg !216
  %le = icmp slt i8* %p10, %path11, !dbg !216
  br i1 %le, label %cond_jump_then12, label %cond_else_block13, !dbg !216

cond_jump_then:                                   ; preds = %cond_then_block
  br label %cond_end_block, !dbg !219

cond_else_block:                                  ; preds = %cond_then_block
  %p6 = load i8*, i8** %p, align 8, !dbg !220
  %ptrToIntI = ptrtoint i8* %p6 to i64, !dbg !220
  %sub = sub i64 %ptrToIntI, 1, !dbg !220
  %iintToPtr = inttoptr i64 %sub to i8*, !dbg !220
  store i8* %iintToPtr, i8** %p, align 8, !dbg !220
  %ptrToIntC7 = ptrtoint i8* %iintToPtr to i64, !dbg !220
  %add8 = add i64 %ptrToIntC7, 1, !dbg !220
  %intToPtr9 = inttoptr i64 %add8 to i8*, !dbg !220
  br label %cond_end, !dbg !220

cond_end:                                         ; preds = %cond_else_block, %after_break
  br label %loop_top_block, !dbg !220

after_break:                                      ; No predecessors!
  br label %cond_end, !dbg !219

cond_jump_then12:                                 ; preds = %cond_end_block
  %path15 = load i8*, i8** %path, align 8, !dbg !221
  br label %string, !dbg !221

cond_else_block13:                                ; preds = %cond_end_block
  %p29 = load i8*, i8** %p, align 8, !dbg !222
  %ptrToIntC30 = ptrtoint i8* %p29 to i64, !dbg !222
  %add31 = add i64 %ptrToIntC30, 1, !dbg !222
  %intToPtr32 = inttoptr i64 %add31 to i8*, !dbg !222
  br label %string33, !dbg !222

cond_end14:                                       ; No predecessors!
  ret i8* null, !dbg !214

string:                                           ; preds = %cond_jump_then12
  %inline_result_variable = alloca i8*, align 8, !dbg !221
  %str = alloca i8*, align 8, !dbg !221
  store i8* %path15, i8** %str, align 8, !dbg !221
  %str16 = load i8*, i8** %str, align 8, !dbg !221
  %fun_result17 = call i64 @strlen(i8* %str16), !dbg !221
  %add18 = add i64 %fun_result17, 1, !dbg !221
  %icastM = trunc i64 %add18 to i32, !dbg !221
  store i32 %icastM, i32* %len, align 4, !dbg !214
  %len19 = load i32, i32* %len, align 4, !dbg !214
  %icastD = sext i32 %len19 to i64, !dbg !214
  %mul20 = mul i64 1, %icastD, !dbg !214
  %fun_result21 = call i8* @GC_malloc(i64 %mul20), !dbg !214
  store i8* %fun_result21, i8** %result, align 8, !dbg !214
  %result22 = load i8*, i8** %result, align 8, !dbg !214
  %str23 = load i8*, i8** %str, align 8, !dbg !214
  %len24 = load i32, i32* %len, align 4, !dbg !214
  %icastD25 = sext i32 %len24 to i64, !dbg !214
  %fun_result26 = call i8* @strncpy(i8* %result22, i8* %str23, i64 %icastD25), !dbg !214
  %result27 = load i8*, i8** %result, align 8, !dbg !214
  store i8* %result27, i8** %inline_result_variable, align 8, !dbg !214
  br label %string_end, !dbg !214

string_end:                                       ; preds = %string
  %inline_result_variable28 = load i8*, i8** %inline_result_variable, align 8, !dbg !214
  ret i8* %inline_result_variable28, !dbg !214

string33:                                         ; preds = %cond_else_block13
  %inline_result_variable34 = alloca i8*, align 8, !dbg !222
  %str35 = alloca i8*, align 8, !dbg !222
  store i8* %intToPtr32, i8** %str35, align 8, !dbg !222
  %str37 = load i8*, i8** %str35, align 8, !dbg !222
  %fun_result38 = call i64 @strlen(i8* %str37), !dbg !222
  %add39 = add i64 %fun_result38, 1, !dbg !222
  %icastM40 = trunc i64 %add39 to i32, !dbg !222
  store i32 %icastM40, i32* %len41, align 4, !dbg !214
  %len42 = load i32, i32* %len41, align 4, !dbg !214
  %icastD43 = sext i32 %len42 to i64, !dbg !214
  %mul44 = mul i64 1, %icastD43, !dbg !214
  %fun_result45 = call i8* @GC_malloc(i64 %mul44), !dbg !214
  store i8* %fun_result45, i8** %result46, align 8, !dbg !214
  %result47 = load i8*, i8** %result46, align 8, !dbg !214
  %str48 = load i8*, i8** %str35, align 8, !dbg !214
  %len49 = load i32, i32* %len41, align 4, !dbg !214
  %icastD50 = sext i32 %len49 to i64, !dbg !214
  %fun_result51 = call i8* @strncpy(i8* %result47, i8* %str48, i64 %icastD50), !dbg !214
  %result52 = load i8*, i8** %result46, align 8, !dbg !214
  store i8* %result52, i8** %inline_result_variable34, align 8, !dbg !214
  br label %string_end36, !dbg !214

string_end36:                                     ; preds = %string33
  %inline_result_variable53 = load i8*, i8** %inline_result_variable34, align 8, !dbg !214
  ret i8* %inline_result_variable53, !dbg !214
}

define internal i8* @xextname(i8* %0) !dbg !223 {
entry:
  %result46 = alloca i8*, align 8, !dbg !224
  %len41 = alloca i32, align 4, !dbg !224
  %result = alloca i8*, align 8, !dbg !224
  %len = alloca i32, align 4, !dbg !224
  %p = alloca i8*, align 8, !dbg !224
  %path = alloca i8*, align 8, !dbg !224
  store i8* %0, i8** %path, align 8, !dbg !224
  %path1 = load i8*, i8** %path, align 8, !dbg !225
  %path2 = load i8*, i8** %path, align 8, !dbg !225
  %fun_result = call i64 @strlen(i8* %path2), !dbg !225
  %ptrToIntC = ptrtoint i8* %path1 to i64, !dbg !225
  %mul = mul i64 %fun_result, 1, !dbg !225
  %add = add i64 %ptrToIntC, %mul, !dbg !225
  %intToPtr = inttoptr i64 %add to i8*, !dbg !225
  store i8* %intToPtr, i8** %p, align 8, !dbg !224
  br label %loop_top_block, !dbg !226

loop_top_block:                                   ; preds = %cond_end, %entry
  %p3 = load i8*, i8** %p, align 8, !dbg !227
  %path4 = load i8*, i8** %path, align 8, !dbg !227
  %gteq = icmp sge i8* %p3, %path4, !dbg !227
  br i1 %gteq, label %cond_then_block, label %cond_end_block, !dbg !227

cond_then_block:                                  ; preds = %loop_top_block
  %p5 = load i8*, i8** %p, align 8, !dbg !228
  %derefference_value = load i8, i8* %p5, align 1, !dbg !228
  %eq = icmp eq i8 %derefference_value, 46, !dbg !228
  br i1 %eq, label %cond_jump_then, label %cond_else_block, !dbg !228

cond_end_block:                                   ; preds = %cond_jump_then, %loop_top_block
  %p10 = load i8*, i8** %p, align 8, !dbg !226
  %path11 = load i8*, i8** %path, align 8, !dbg !226
  %le = icmp slt i8* %p10, %path11, !dbg !226
  br i1 %le, label %cond_jump_then12, label %cond_else_block13, !dbg !226

cond_jump_then:                                   ; preds = %cond_then_block
  br label %cond_end_block, !dbg !229

cond_else_block:                                  ; preds = %cond_then_block
  %p6 = load i8*, i8** %p, align 8, !dbg !230
  %ptrToIntI = ptrtoint i8* %p6 to i64, !dbg !230
  %sub = sub i64 %ptrToIntI, 1, !dbg !230
  %iintToPtr = inttoptr i64 %sub to i8*, !dbg !230
  store i8* %iintToPtr, i8** %p, align 8, !dbg !230
  %ptrToIntC7 = ptrtoint i8* %iintToPtr to i64, !dbg !230
  %add8 = add i64 %ptrToIntC7, 1, !dbg !230
  %intToPtr9 = inttoptr i64 %add8 to i8*, !dbg !230
  br label %cond_end, !dbg !230

cond_end:                                         ; preds = %cond_else_block, %after_break
  br label %loop_top_block, !dbg !230

after_break:                                      ; No predecessors!
  br label %cond_end, !dbg !229

cond_jump_then12:                                 ; preds = %cond_end_block
  %path15 = load i8*, i8** %path, align 8, !dbg !231
  br label %string, !dbg !231

cond_else_block13:                                ; preds = %cond_end_block
  %p29 = load i8*, i8** %p, align 8, !dbg !232
  %ptrToIntC30 = ptrtoint i8* %p29 to i64, !dbg !232
  %add31 = add i64 %ptrToIntC30, 1, !dbg !232
  %intToPtr32 = inttoptr i64 %add31 to i8*, !dbg !232
  br label %string33, !dbg !232

cond_end14:                                       ; No predecessors!
  ret i8* null, !dbg !224

string:                                           ; preds = %cond_jump_then12
  %inline_result_variable = alloca i8*, align 8, !dbg !231
  %str = alloca i8*, align 8, !dbg !231
  store i8* %path15, i8** %str, align 8, !dbg !231
  %str16 = load i8*, i8** %str, align 8, !dbg !231
  %fun_result17 = call i64 @strlen(i8* %str16), !dbg !231
  %add18 = add i64 %fun_result17, 1, !dbg !231
  %icastM = trunc i64 %add18 to i32, !dbg !231
  store i32 %icastM, i32* %len, align 4, !dbg !224
  %len19 = load i32, i32* %len, align 4, !dbg !224
  %icastD = sext i32 %len19 to i64, !dbg !224
  %mul20 = mul i64 1, %icastD, !dbg !224
  %fun_result21 = call i8* @GC_malloc(i64 %mul20), !dbg !224
  store i8* %fun_result21, i8** %result, align 8, !dbg !224
  %result22 = load i8*, i8** %result, align 8, !dbg !224
  %str23 = load i8*, i8** %str, align 8, !dbg !224
  %len24 = load i32, i32* %len, align 4, !dbg !224
  %icastD25 = sext i32 %len24 to i64, !dbg !224
  %fun_result26 = call i8* @strncpy(i8* %result22, i8* %str23, i64 %icastD25), !dbg !224
  %result27 = load i8*, i8** %result, align 8, !dbg !224
  store i8* %result27, i8** %inline_result_variable, align 8, !dbg !224
  br label %string_end, !dbg !224

string_end:                                       ; preds = %string
  %inline_result_variable28 = load i8*, i8** %inline_result_variable, align 8, !dbg !224
  ret i8* %inline_result_variable28, !dbg !224

string33:                                         ; preds = %cond_else_block13
  %inline_result_variable34 = alloca i8*, align 8, !dbg !232
  %str35 = alloca i8*, align 8, !dbg !232
  store i8* %intToPtr32, i8** %str35, align 8, !dbg !232
  %str37 = load i8*, i8** %str35, align 8, !dbg !232
  %fun_result38 = call i64 @strlen(i8* %str37), !dbg !232
  %add39 = add i64 %fun_result38, 1, !dbg !232
  %icastM40 = trunc i64 %add39 to i32, !dbg !232
  store i32 %icastM40, i32* %len41, align 4, !dbg !224
  %len42 = load i32, i32* %len41, align 4, !dbg !224
  %icastD43 = sext i32 %len42 to i64, !dbg !224
  %mul44 = mul i64 1, %icastD43, !dbg !224
  %fun_result45 = call i8* @GC_malloc(i64 %mul44), !dbg !224
  store i8* %fun_result45, i8** %result46, align 8, !dbg !224
  %result47 = load i8*, i8** %result46, align 8, !dbg !224
  %str48 = load i8*, i8** %str35, align 8, !dbg !224
  %len49 = load i32, i32* %len41, align 4, !dbg !224
  %icastD50 = sext i32 %len49 to i64, !dbg !224
  %fun_result51 = call i8* @strncpy(i8* %result47, i8* %str48, i64 %icastD50), !dbg !224
  %result52 = load i8*, i8** %result46, align 8, !dbg !224
  store i8* %result52, i8** %inline_result_variable34, align 8, !dbg !224
  br label %string_end36, !dbg !224

string_end36:                                     ; preds = %string33
  %inline_result_variable53 = load i8*, i8** %inline_result_variable34, align 8, !dbg !224
  ret i8* %inline_result_variable53, !dbg !224
}

define internal i8* @xrealpath(i8* %0) !dbg !233 {
entry:
  %result215 = alloca i8*, align 8, !dbg !234
  %result7 = alloca i8*, align 8, !dbg !234
  %len = alloca i32, align 4, !dbg !234
  %result = alloca i8*, align 8, !dbg !234
  %path = alloca i8*, align 8, !dbg !234
  store i8* %0, i8** %path, align 8, !dbg !234
  %path1 = load i8*, i8** %path, align 8, !dbg !235
  %fun_result = call i8* @realpath(i8* %path1, i8* null), !dbg !235
  store i8* %fun_result, i8** %result, align 8, !dbg !234
  %result2 = load i8*, i8** %result, align 8, !dbg !236
  br label %string, !dbg !236

string:                                           ; preds = %entry
  %inline_result_variable = alloca i8*, align 8, !dbg !236
  %str = alloca i8*, align 8, !dbg !236
  store i8* %result2, i8** %str, align 8, !dbg !236
  %str3 = load i8*, i8** %str, align 8, !dbg !236
  %fun_result4 = call i64 @strlen(i8* %str3), !dbg !236
  %add = add i64 %fun_result4, 1, !dbg !236
  %icastM = trunc i64 %add to i32, !dbg !236
  store i32 %icastM, i32* %len, align 4, !dbg !234
  %len5 = load i32, i32* %len, align 4, !dbg !234
  %icastD = sext i32 %len5 to i64, !dbg !234
  %mul = mul i64 1, %icastD, !dbg !234
  %fun_result6 = call i8* @GC_malloc(i64 %mul), !dbg !234
  store i8* %fun_result6, i8** %result7, align 8, !dbg !234
  %result8 = load i8*, i8** %result7, align 8, !dbg !234
  %str9 = load i8*, i8** %str, align 8, !dbg !234
  %len10 = load i32, i32* %len, align 4, !dbg !234
  %icastD11 = sext i32 %len10 to i64, !dbg !234
  %fun_result12 = call i8* @strncpy(i8* %result8, i8* %str9, i64 %icastD11), !dbg !234
  %result13 = load i8*, i8** %result7, align 8, !dbg !234
  store i8* %result13, i8** %inline_result_variable, align 8, !dbg !234
  br label %string_end, !dbg !234

string_end:                                       ; preds = %string
  %inline_result_variable14 = load i8*, i8** %inline_result_variable, align 8, !dbg !234
  store i8* %inline_result_variable14, i8** %result215, align 8, !dbg !234
  %result16 = load i8*, i8** %result, align 8, !dbg !237
  call void @free(i8* %result16), !dbg !237
  %result217 = load i8*, i8** %result215, align 8, !dbg !238
  ret i8* %result217, !dbg !238
}

define i1 @parse(i8* %0, %list_sNodep* %1, %buffer* %2) !dbg !239 {
entry:
  %node = alloca %sNode*, align 8, !dbg !242
  %sline = alloca i32, align 4, !dbg !242
  %p = alloca i8*, align 8, !dbg !242
  %line = alloca [4096 x i8], align 1, !dbg !242
  %source = alloca %buffer*, align 8, !dbg !242
  %f = alloca %_IO_FILE*, align 8, !dbg !242
  %fname = alloca i8*, align 8, !dbg !242
  store i8* %0, i8** %fname, align 8, !dbg !242
  %nodes = alloca %list_sNodep*, align 8, !dbg !242
  store %list_sNodep* %1, %list_sNodep** %nodes, align 8, !dbg !242
  %codes = alloca %buffer*, align 8, !dbg !242
  store %buffer* %2, %buffer** %codes, align 8, !dbg !242
  %fname1 = load i8*, i8** %fname, align 8, !dbg !243
  %fun_result = call %_IO_FILE* @fopen(i8* %fname1, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @r, i32 0, i32 0)), !dbg !243
  store %_IO_FILE* %fun_result, %_IO_FILE** %f, align 8, !dbg !242
  %f2 = load %_IO_FILE*, %_IO_FILE** %f, align 8, !dbg !244
  %eq = icmp eq %_IO_FILE* %f2, null, !dbg !244
  br i1 %eq, label %cond_jump_then, label %cond_end, !dbg !244

cond_jump_then:                                   ; preds = %entry
  %stderr = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !245
  %fname3 = load i8*, i8** %fname, align 8, !dbg !245
  %fun_result4 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @"file %s is not found\0A", i32 0, i32 0), i8* %fname3), !dbg !245
  ret i1 false, !dbg !246

cond_end:                                         ; preds = %entry
  %fun_result5 = call i8* @GC_malloc(i64 16), !dbg !247
  %obj = bitcast i8* %fun_result5 to %buffer*, !dbg !247
  %fun_result6 = call %buffer* @buffer_initialize(%buffer* %obj), !dbg !247
  store %buffer* %fun_result6, %buffer** %source, align 8, !dbg !242
  br label %loop_top_block, !dbg !248

loop_top_block:                                   ; preds = %cond_then_block, %cond_end
  %autocast = bitcast [4096 x i8]* %line to i8*, !dbg !249
  %f7 = load %_IO_FILE*, %_IO_FILE** %f, align 8, !dbg !249
  %fun_result8 = call i8* @fgets(i8* %autocast, i32 4096, %_IO_FILE* %f7), !dbg !249
  %not_eq = icmp ne i8* %fun_result8, null, !dbg !249
  br i1 %not_eq, label %cond_then_block, label %cond_end_block, !dbg !249

cond_then_block:                                  ; preds = %loop_top_block
  %autocast9 = bitcast [4096 x i8]* %line to i8*, !dbg !250
  %fun_result10 = call i64 @strlen(i8* %autocast9), !dbg !250
  %sub = sub i64 %fun_result10, 1, !dbg !250
  %icastM = trunc i64 %sub to i32, !dbg !250
  %array_cast = bitcast [4096 x i8]* %line to i8*, !dbg !250
  %gep = getelementptr i8, i8* %array_cast, i64 %sub, !dbg !250
  store i8 0, i8* %gep, align 1, !dbg !250
  %source11 = load %buffer*, %buffer** %source, align 8, !dbg !251
  %autocast12 = bitcast [4096 x i8]* %line to i8*, !dbg !251
  call void @buffer_append_str(%buffer* %source11, i8* %autocast12), !dbg !251
  br label %loop_top_block, !dbg !251

cond_end_block:                                   ; preds = %loop_top_block
  %f13 = load %_IO_FILE*, %_IO_FILE** %f, align 8, !dbg !248
  %fun_result14 = call i32 @fclose(%_IO_FILE* %f13), !dbg !248
  %source15 = load %buffer*, %buffer** %source, align 8, !dbg !252
  %fun_result16 = call i8* @buffer_to_string(%buffer* %source15), !dbg !252
  store i8* %fun_result16, i8** %p, align 8, !dbg !242
  store i32 1, i32* %sline, align 4, !dbg !242
  br label %loop_top_block17, !dbg !253

loop_top_block17:                                 ; preds = %cond_end27, %cond_end_block
  %p18 = load i8*, i8** %p, align 8, !dbg !254
  %derefference_value = load i8, i8* %p18, align 1, !dbg !254
  %icmpA = icmp ne i8 %derefference_value, 0, !dbg !254
  br i1 %icmpA, label %cond_then_block19, label %cond_end_block20, !dbg !254

cond_then_block19:                                ; preds = %loop_top_block17
  store %sNode* null, %sNode** %node, align 8, !dbg !242
  %p21 = load i8*, i8** %p, align 8, !dbg !255
  %node22 = load %sNode*, %sNode** %node, align 8, !dbg !255
  %fname23 = load i8*, i8** %fname, align 8, !dbg !255
  %sline24 = load i32, i32* %sline, align 4, !dbg !255
  %fun_result25 = call i1 @expression(i8** %p, %sNode** %node, i8* %fname23, i32* %sline), !dbg !255
  %logical_denial = icmp eq i1 %fun_result25, false, !dbg !255
  br i1 %logical_denial, label %cond_jump_then26, label %cond_end27, !dbg !255

cond_end_block20:                                 ; preds = %loop_top_block17
  ret i1 true, !dbg !253

cond_jump_then26:                                 ; preds = %cond_then_block19
  %stderr28 = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !256
  %fname29 = load i8*, i8** %fname, align 8, !dbg !256
  %sline30 = load i32, i32* %sline, align 4, !dbg !256
  %p31 = load i8*, i8** %p, align 8, !dbg !256
  %derefference_value32 = load i8, i8* %p31, align 1, !dbg !256
  %fun_result33 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr28, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @"%s %d: unexpected character %c\0A", i32 0, i32 0), i8* %fname29, i32 %sline30, i8 %derefference_value32), !dbg !256
  ret i1 false, !dbg !257

cond_end27:                                       ; preds = %cond_then_block19
  %nodes34 = load %list_sNodep*, %list_sNodep** %nodes, align 8, !dbg !258
  %node35 = load %sNode*, %sNode** %node, align 8, !dbg !258
  call void @list_push_back_sNodep(%list_sNodep* %nodes34, %sNode* %node35), !dbg !258
  br label %loop_top_block17, !dbg !258
}

define i1 @compile(%sNode* %0, %buffer* %1) !dbg !259 {
entry:
  %node = alloca %sNode*, align 8, !dbg !260
  store %sNode* %0, %sNode** %node, align 8, !dbg !260
  %codes = alloca %buffer*, align 8, !dbg !260
  store %buffer* %1, %buffer** %codes, align 8, !dbg !260
  %node1 = load %sNode*, %sNode** %node, align 8, !dbg !261
  %field = getelementptr inbounds %sNode, %sNode* %node1, i32 0, i32 0, !dbg !261
  %kind = load i32, i32* %field, align 4, !dbg !261
  %eq = icmp eq i32 %kind, 0, !dbg !261
  br i1 %eq, label %cond_jump_then, label %cond_end, !dbg !261

cond_jump_then:                                   ; preds = %entry
  %codes2 = load %buffer*, %buffer** %codes, align 8, !dbg !262
  call void @buffer_append_int(%buffer* %codes2, i32 1), !dbg !262
  %codes3 = load %buffer*, %buffer** %codes, align 8, !dbg !263
  %node4 = load %sNode*, %sNode** %node, align 8, !dbg !263
  %field5 = getelementptr inbounds %sNode, %sNode* %node4, i32 0, i32 3, !dbg !263
  %value = load %come_anon68, %come_anon68* %field5, align 8, !dbg !263
  %field6 = getelementptr inbounds %come_anon68, %come_anon68* %field5, i32 0, i32 0, !dbg !263
  %icastO = bitcast i8** %field6 to i32*, !dbg !263
  %intValue = load i32, i32* %icastO, align 4, !dbg !263
  call void @buffer_append_int(%buffer* %codes3, i32 %intValue), !dbg !263
  br label %cond_end, !dbg !263

cond_end:                                         ; preds = %cond_jump_then, %entry
  ret i1 true, !dbg !264
}

define i1 @run(i32* %0) !dbg !265 {
entry:
  %value = alloca i32, align 4, !dbg !266
  %p = alloca i32*, align 8, !dbg !266
  store i32* %0, i32** %p, align 8, !dbg !266
  %p1 = load i32*, i32** %p, align 8, !dbg !267
  %derefference_value = load i32, i32* %p1, align 4, !dbg !267
  %eq = icmp eq i32 %derefference_value, 1, !dbg !267
  br i1 %eq, label %cond_jump_then, label %cond_end, !dbg !267

cond_jump_then:                                   ; preds = %entry
  %p2 = load i32*, i32** %p, align 8, !dbg !268
  %ptrToIntC = ptrtoint i32* %p2 to i64, !dbg !268
  %add = add i64 %ptrToIntC, 4, !dbg !268
  %intToPtr = inttoptr i64 %add to i32*, !dbg !268
  store i32* %intToPtr, i32** %p, align 8, !dbg !268
  %ptrToIntI = ptrtoint i32* %intToPtr to i64, !dbg !268
  %sub = sub i64 %ptrToIntI, 4, !dbg !268
  %iintToPtr = inttoptr i64 %sub to i32*, !dbg !268
  %p3 = load i32*, i32** %p, align 8, !dbg !269
  %derefference_value4 = load i32, i32* %p3, align 4, !dbg !269
  store i32 %derefference_value4, i32* %value, align 4, !dbg !266
  %p5 = load i32*, i32** %p, align 8, !dbg !270
  %ptrToIntC6 = ptrtoint i32* %p5 to i64, !dbg !270
  %add7 = add i64 %ptrToIntC6, 4, !dbg !270
  %intToPtr8 = inttoptr i64 %add7 to i32*, !dbg !270
  store i32* %intToPtr8, i32** %p, align 8, !dbg !270
  %ptrToIntI9 = ptrtoint i32* %intToPtr8 to i64, !dbg !270
  %sub10 = sub i64 %ptrToIntI9, 4, !dbg !270
  %iintToPtr11 = inttoptr i64 %sub10 to i32*, !dbg !270
  %value12 = load i32, i32* %value, align 4, !dbg !271
  %fun_result = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @"int value %d\0A", i32 0, i32 0), i32 %value12), !dbg !271
  br label %cond_end, !dbg !271

cond_end:                                         ; preds = %cond_jump_then, %entry
  ret i1 true, !dbg !272
}

define void @skip_spaces(i8** %0, i32* %1) !dbg !273 {
entry:
  %andand = alloca i1, align 1, !dbg !274
  %oror1 = alloca i1, align 1, !dbg !274
  %oror = alloca i1, align 1, !dbg !274
  %p = alloca i8**, align 8, !dbg !274
  store i8** %0, i8*** %p, align 8, !dbg !274
  %sline = alloca i32*, align 8, !dbg !274
  store i32* %1, i32** %sline, align 8, !dbg !274
  br label %loop_top_block, !dbg !275

loop_top_block:                                   ; preds = %cond_then_block, %entry
  %p2 = load i8**, i8*** %p, align 8, !dbg !276
  %derefference_value = load i8*, i8** %p2, align 8, !dbg !276
  %derefference_value3 = load i8, i8* %derefference_value, align 1, !dbg !276
  %eq = icmp eq i8 %derefference_value3, 32, !dbg !276
  store i1 %eq, i1* %oror1, align 1, !dbg !276
  br i1 %eq, label %cond_jump_end, label %cond_jump_then, !dbg !276

cond_jump_then:                                   ; preds = %loop_top_block
  %p4 = load i8**, i8*** %p, align 8, !dbg !276
  %derefference_value5 = load i8*, i8** %p4, align 8, !dbg !276
  %derefference_value6 = load i8, i8* %derefference_value5, align 1, !dbg !276
  %eq7 = icmp eq i8 %derefference_value6, 9, !dbg !276
  %oror8 = or i1 %eq, %eq7, !dbg !276
  store i1 %oror8, i1* %oror1, align 1, !dbg !276
  br label %cond_jump_end, !dbg !276

cond_jump_end:                                    ; preds = %cond_jump_then, %loop_top_block
  %oror_result_value = load i1, i1* %oror1, align 1, !dbg !276
  store i1 %oror_result_value, i1* %oror, align 1, !dbg !276
  br i1 %oror_result_value, label %cond_jump_end10, label %cond_jump_then9, !dbg !276

cond_jump_then9:                                  ; preds = %cond_jump_end
  %p11 = load i8**, i8*** %p, align 8, !dbg !276
  %derefference_value12 = load i8*, i8** %p11, align 8, !dbg !276
  %derefference_value13 = load i8, i8* %derefference_value12, align 1, !dbg !276
  %eq14 = icmp eq i8 %derefference_value13, 10, !dbg !276
  store i1 %eq14, i1* %andand, align 1, !dbg !276
  br i1 %eq14, label %cond_jump_then15, label %cond_jump_end16, !dbg !276

cond_jump_end10:                                  ; preds = %cond_jump_end16, %cond_jump_end
  %oror_result_value21 = load i1, i1* %oror, align 1, !dbg !276
  br i1 %oror_result_value21, label %cond_then_block, label %cond_end_block, !dbg !276

cond_jump_then15:                                 ; preds = %cond_jump_then9
  %sline17 = load i32*, i32** %sline, align 8, !dbg !276
  %derefference_value18 = load i32, i32* %sline17, align 4, !dbg !276
  %load = load i32, i32* %sline17, align 4, !dbg !276
  %add = add i32 %load, 1, !dbg !276
  store i32 %add, i32* %sline17, align 4, !dbg !276
  %icmpA = icmp ne i32 %add, 0, !dbg !276
  %andand19 = and i1 %eq14, %icmpA, !dbg !276
  store i1 %andand19, i1* %andand, align 1, !dbg !276
  br label %cond_jump_end16, !dbg !276

cond_jump_end16:                                  ; preds = %cond_jump_then15, %cond_jump_then9
  %andand_result_value = load i1, i1* %andand, align 1, !dbg !276
  %oror20 = or i1 %oror_result_value, %andand_result_value, !dbg !276
  store i1 %oror20, i1* %oror, align 1, !dbg !276
  br label %cond_jump_end10, !dbg !276

cond_then_block:                                  ; preds = %cond_jump_end10
  %p22 = load i8**, i8*** %p, align 8, !dbg !277
  %derefference_value23 = load i8*, i8** %p22, align 8, !dbg !277
  %castAI = ptrtoint i8* %derefference_value23 to i64, !dbg !277
  %add24 = add i64 %castAI, 1, !dbg !277
  %IntToPtr = inttoptr i64 %add24 to i8*, !dbg !277
  store i8* %IntToPtr, i8** %p22, align 8, !dbg !277
  br label %loop_top_block, !dbg !277

cond_end_block:                                   ; preds = %cond_jump_end10
  ret void, !dbg !277
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

define %sNode* @create_int_node(i32 %0, i8* %1, i32 %2) !dbg !278 {
entry:
  %result8 = alloca i8*, align 8, !dbg !281
  %len = alloca i32, align 4, !dbg !281
  %result = alloca %sNode*, align 8, !dbg !281
  %value = alloca i32, align 4, !dbg !281
  store i32 %0, i32* %value, align 4, !dbg !281
  %fname = alloca i8*, align 8, !dbg !281
  store i8* %1, i8** %fname, align 8, !dbg !281
  %sline = alloca i32, align 4, !dbg !281
  store i32 %2, i32* %sline, align 4, !dbg !281
  %fun_result = call i8* @GC_malloc(i64 32), !dbg !282
  %obj = bitcast i8* %fun_result to %sNode*, !dbg !282
  store %sNode* %obj, %sNode** %result, align 8, !dbg !281
  %result1 = load %sNode*, %sNode** %result, align 8, !dbg !283
  %field = getelementptr inbounds %sNode, %sNode* %result1, i32 0, i32 0, !dbg !283
  store i32 0, i32* %field, align 4, !dbg !283
  %result2 = load %sNode*, %sNode** %result, align 8, !dbg !284
  %fname3 = load i8*, i8** %fname, align 8, !dbg !284
  br label %string, !dbg !284

string:                                           ; preds = %entry
  %inline_result_variable = alloca i8*, align 8, !dbg !284
  %str = alloca i8*, align 8, !dbg !284
  store i8* %fname3, i8** %str, align 8, !dbg !284
  %str4 = load i8*, i8** %str, align 8, !dbg !284
  %fun_result5 = call i64 @strlen(i8* %str4), !dbg !284
  %add = add i64 %fun_result5, 1, !dbg !284
  %icastM = trunc i64 %add to i32, !dbg !284
  store i32 %icastM, i32* %len, align 4, !dbg !281
  %len6 = load i32, i32* %len, align 4, !dbg !281
  %icastD = sext i32 %len6 to i64, !dbg !281
  %mul = mul i64 1, %icastD, !dbg !281
  %fun_result7 = call i8* @GC_malloc(i64 %mul), !dbg !281
  store i8* %fun_result7, i8** %result8, align 8, !dbg !281
  %result9 = load i8*, i8** %result8, align 8, !dbg !281
  %str10 = load i8*, i8** %str, align 8, !dbg !281
  %len11 = load i32, i32* %len, align 4, !dbg !281
  %icastD12 = sext i32 %len11 to i64, !dbg !281
  %fun_result13 = call i8* @strncpy(i8* %result9, i8* %str10, i64 %icastD12), !dbg !281
  %result14 = load i8*, i8** %result8, align 8, !dbg !281
  store i8* %result14, i8** %inline_result_variable, align 8, !dbg !281
  br label %string_end, !dbg !281

string_end:                                       ; preds = %string
  %inline_result_variable15 = load i8*, i8** %inline_result_variable, align 8, !dbg !281
  %field16 = getelementptr inbounds %sNode, %sNode* %result2, i32 0, i32 1, !dbg !281
  store i8* %inline_result_variable15, i8** %field16, align 8, !dbg !281
  %result17 = load %sNode*, %sNode** %result, align 8, !dbg !285
  %sline18 = load i32, i32* %sline, align 4, !dbg !285
  %field19 = getelementptr inbounds %sNode, %sNode* %result17, i32 0, i32 2, !dbg !285
  store i32 %sline18, i32* %field19, align 4, !dbg !285
  %result20 = load %sNode*, %sNode** %result, align 8, !dbg !286
  %field21 = getelementptr inbounds %sNode, %sNode* %result20, i32 0, i32 3, !dbg !286
  %value22 = load %come_anon68, %come_anon68* %field21, align 8, !dbg !286
  %value23 = load i32, i32* %value, align 4, !dbg !286
  %field24 = getelementptr inbounds %come_anon68, %come_anon68* %field21, i32 0, i32 0, !dbg !286
  %icastN = bitcast i8** %field24 to i32*, !dbg !286
  store i32 %value23, i32* %icastN, align 4, !dbg !286
  %result25 = load %sNode*, %sNode** %result, align 8, !dbg !287
  ret %sNode* %result25, !dbg !287
}

define %sNode* @exp_node(i8** %0, i8* %1, i32* %2) !dbg !288 {
entry:
  %n = alloca i32, align 4, !dbg !289
  %p = alloca i8**, align 8, !dbg !289
  store i8** %0, i8*** %p, align 8, !dbg !289
  %fname = alloca i8*, align 8, !dbg !289
  store i8* %1, i8** %fname, align 8, !dbg !289
  %sline = alloca i32*, align 8, !dbg !289
  store i32* %2, i32** %sline, align 8, !dbg !289
  %fun_result = call i16** @__ctype_b_loc(), !dbg !290
  %derefference_value = load i16*, i16** %fun_result, align 8, !dbg !290
  %p1 = load i8**, i8*** %p, align 8, !dbg !290
  %derefference_value2 = load i8*, i8** %p1, align 8, !dbg !290
  %derefference_value3 = load i8, i8* %derefference_value2, align 1, !dbg !290
  %icastL = sext i8 %derefference_value3 to i32, !dbg !290
  %element_address = getelementptr inbounds i16, i16* %derefference_value, i32 %icastL, !dbg !290
  %element = load i16, i16* %element_address, align 2, !dbg !290
  %andtmp = and i16 %element, 2048, !dbg !290
  %icmpA = icmp ne i16 %andtmp, 0, !dbg !290
  br i1 %icmpA, label %cond_jump_then, label %cond_end, !dbg !290

cond_jump_then:                                   ; preds = %entry
  store i32 0, i32* %n, align 4, !dbg !289
  br label %loop_top_block, !dbg !291

cond_end:                                         ; preds = %entry
  ret %sNode* null, !dbg !292

loop_top_block:                                   ; preds = %cond_then_block, %cond_jump_then
  %fun_result4 = call i16** @__ctype_b_loc(), !dbg !293
  %derefference_value5 = load i16*, i16** %fun_result4, align 8, !dbg !293
  %p6 = load i8**, i8*** %p, align 8, !dbg !293
  %derefference_value7 = load i8*, i8** %p6, align 8, !dbg !293
  %derefference_value8 = load i8, i8* %derefference_value7, align 1, !dbg !293
  %icastL9 = sext i8 %derefference_value8 to i32, !dbg !293
  %element_address10 = getelementptr inbounds i16, i16* %derefference_value5, i32 %icastL9, !dbg !293
  %element11 = load i16, i16* %element_address10, align 2, !dbg !293
  %andtmp12 = and i16 %element11, 2048, !dbg !293
  %icmpA13 = icmp ne i16 %andtmp12, 0, !dbg !293
  br i1 %icmpA13, label %cond_then_block, label %cond_end_block, !dbg !293

cond_then_block:                                  ; preds = %loop_top_block
  %n14 = load i32, i32* %n, align 4, !dbg !294
  %mul = mul i32 %n14, 10, !dbg !294
  %p15 = load i8**, i8*** %p, align 8, !dbg !294
  %derefference_value16 = load i8*, i8** %p15, align 8, !dbg !294
  %derefference_value17 = load i8, i8* %derefference_value16, align 1, !dbg !294
  %sub = sub i8 %derefference_value17, 48, !dbg !294
  %icastL18 = sext i8 %sub to i32, !dbg !294
  %add = add i32 %mul, %icastL18, !dbg !294
  store i32 %add, i32* %n, align 4, !dbg !294
  %p19 = load i8**, i8*** %p, align 8, !dbg !295
  %derefference_value20 = load i8*, i8** %p19, align 8, !dbg !295
  %castAI = ptrtoint i8* %derefference_value20 to i64, !dbg !295
  %add21 = add i64 %castAI, 1, !dbg !295
  %IntToPtr = inttoptr i64 %add21 to i8*, !dbg !295
  store i8* %IntToPtr, i8** %p19, align 8, !dbg !295
  br label %loop_top_block, !dbg !295

cond_end_block:                                   ; preds = %loop_top_block
  %p22 = load i8**, i8*** %p, align 8, !dbg !291
  %sline23 = load i32*, i32** %sline, align 8, !dbg !291
  call void @skip_spaces(i8** %p22, i32* %sline23), !dbg !291
  %n24 = load i32, i32* %n, align 4, !dbg !296
  %fname25 = load i8*, i8** %fname, align 8, !dbg !296
  %sline26 = load i32*, i32** %sline, align 8, !dbg !296
  %castAC = ptrtoint i32* %sline26 to i32, !dbg !296
  %fun_result27 = call %sNode* @create_int_node(i32 %n24, i8* %fname25, i32 %castAC), !dbg !296
  ret %sNode* %fun_result27, !dbg !296
}

define i1 @expression(i8** %0, %sNode** %1, i8* %2, i32* %3) !dbg !297 {
entry:
  %p = alloca i8**, align 8, !dbg !300
  store i8** %0, i8*** %p, align 8, !dbg !300
  %node = alloca %sNode**, align 8, !dbg !300
  store %sNode** %1, %sNode*** %node, align 8, !dbg !300
  %fname = alloca i8*, align 8, !dbg !300
  store i8* %2, i8** %fname, align 8, !dbg !300
  %sline = alloca i32*, align 8, !dbg !300
  store i32* %3, i32** %sline, align 8, !dbg !300
  %node1 = load %sNode**, %sNode*** %node, align 8, !dbg !301
  %p2 = load i8**, i8*** %p, align 8, !dbg !301
  %fname3 = load i8*, i8** %fname, align 8, !dbg !301
  %sline4 = load i32*, i32** %sline, align 8, !dbg !301
  %fun_result = call %sNode* @exp_node(i8** %p2, i8* %fname3, i32* %sline4), !dbg !301
  store %sNode* %fun_result, %sNode** %node1, align 8, !dbg !301
  %node5 = load %sNode**, %sNode*** %node, align 8, !dbg !302
  %derefference_value = load %sNode*, %sNode** %node5, align 8, !dbg !302
  %eq = icmp eq %sNode* %derefference_value, null, !dbg !302
  br i1 %eq, label %cond_jump_then, label %cond_end, !dbg !302

cond_jump_then:                                   ; preds = %entry
  ret i1 false, !dbg !303

cond_end:                                         ; preds = %entry
  ret i1 true, !dbg !304
}

define internal void @list_push_back_sNodep(%list_sNodep* %0, %sNode* %1) {
entry:
  %litem41 = alloca %list_item_sNodep*, align 8, !dbg !258
  %litem21 = alloca %list_item_sNodep*, align 8, !dbg !258
  %litem = alloca %list_item_sNodep*, align 8, !dbg !258
  %self = alloca %list_sNodep*, align 8, !dbg !258
  store %list_sNodep* %0, %list_sNodep** %self, align 8, !dbg !258
  %item = alloca %sNode*, align 8, !dbg !258
  store %sNode* %1, %sNode** %item, align 8, !dbg !258
  %self1 = load %list_sNodep*, %list_sNodep** %self, align 8, !dbg !258
  %field = getelementptr inbounds %list_sNodep, %list_sNodep* %self1, i32 0, i32 2, !dbg !258
  %len = load i32, i32* %field, align 4, !dbg !258
  %eq = icmp eq i32 %len, 0, !dbg !258
  br i1 %eq, label %cond_jump_then, label %cond_jump_elif0, !dbg !258

cond_jump_then:                                   ; preds = %entry
  %fun_result = call i8* @GC_malloc(i64 24), !dbg !258
  %obj = bitcast i8* %fun_result to %list_item_sNodep*, !dbg !258
  store %list_item_sNodep* %obj, %list_item_sNodep** %litem, align 8, !dbg !258
  %litem2 = load %list_item_sNodep*, %list_item_sNodep** %litem, align 8, !dbg !258
  %field3 = getelementptr inbounds %list_item_sNodep, %list_item_sNodep* %litem2, i32 0, i32 1, !dbg !258
  store %list_item_sNodep* null, %list_item_sNodep** %field3, align 8, !dbg !258
  %litem4 = load %list_item_sNodep*, %list_item_sNodep** %litem, align 8, !dbg !258
  %field5 = getelementptr inbounds %list_item_sNodep, %list_item_sNodep* %litem4, i32 0, i32 2, !dbg !258
  store %list_item_sNodep* null, %list_item_sNodep** %field5, align 8, !dbg !258
  %litem6 = load %list_item_sNodep*, %list_item_sNodep** %litem, align 8, !dbg !258
  %item7 = load %sNode*, %sNode** %item, align 8, !dbg !258
  %field8 = getelementptr inbounds %list_item_sNodep, %list_item_sNodep* %litem6, i32 0, i32 0, !dbg !258
  store %sNode* %item7, %sNode** %field8, align 8, !dbg !258
  %self9 = load %list_sNodep*, %list_sNodep** %self, align 8, !dbg !258
  %litem10 = load %list_item_sNodep*, %list_item_sNodep** %litem, align 8, !dbg !258
  %field11 = getelementptr inbounds %list_sNodep, %list_sNodep* %self9, i32 0, i32 1, !dbg !258
  store %list_item_sNodep* %litem10, %list_item_sNodep** %field11, align 8, !dbg !258
  %self12 = load %list_sNodep*, %list_sNodep** %self, align 8, !dbg !258
  %litem13 = load %list_item_sNodep*, %list_item_sNodep** %litem, align 8, !dbg !258
  %field14 = getelementptr inbounds %list_sNodep, %list_sNodep* %self12, i32 0, i32 0, !dbg !258
  store %list_item_sNodep* %litem13, %list_item_sNodep** %field14, align 8, !dbg !258
  br label %cond_end, !dbg !258

cond_jump_elif0:                                  ; preds = %entry
  %self15 = load %list_sNodep*, %list_sNodep** %self, align 8, !dbg !258
  %field16 = getelementptr inbounds %list_sNodep, %list_sNodep* %self15, i32 0, i32 2, !dbg !258
  %len17 = load i32, i32* %field16, align 4, !dbg !258
  %eq18 = icmp eq i32 %len17, 1, !dbg !258
  br i1 %eq18, label %cond_jump_elif_then0, label %cond_else_block, !dbg !258

cond_jump_elif_then0:                             ; preds = %cond_jump_elif0
  %fun_result19 = call i8* @GC_malloc(i64 24), !dbg !258
  %obj20 = bitcast i8* %fun_result19 to %list_item_sNodep*, !dbg !258
  store %list_item_sNodep* %obj20, %list_item_sNodep** %litem21, align 8, !dbg !258
  %litem22 = load %list_item_sNodep*, %list_item_sNodep** %litem21, align 8, !dbg !258
  %self23 = load %list_sNodep*, %list_sNodep** %self, align 8, !dbg !258
  %field24 = getelementptr inbounds %list_sNodep, %list_sNodep* %self23, i32 0, i32 0, !dbg !258
  %head = load %list_item_sNodep*, %list_item_sNodep** %field24, align 8, !dbg !258
  %field25 = getelementptr inbounds %list_item_sNodep, %list_item_sNodep* %litem22, i32 0, i32 1, !dbg !258
  store %list_item_sNodep* %head, %list_item_sNodep** %field25, align 8, !dbg !258
  %litem26 = load %list_item_sNodep*, %list_item_sNodep** %litem21, align 8, !dbg !258
  %field27 = getelementptr inbounds %list_item_sNodep, %list_item_sNodep* %litem26, i32 0, i32 2, !dbg !258
  store %list_item_sNodep* null, %list_item_sNodep** %field27, align 8, !dbg !258
  %litem28 = load %list_item_sNodep*, %list_item_sNodep** %litem21, align 8, !dbg !258
  %item29 = load %sNode*, %sNode** %item, align 8, !dbg !258
  %field30 = getelementptr inbounds %list_item_sNodep, %list_item_sNodep* %litem28, i32 0, i32 0, !dbg !258
  store %sNode* %item29, %sNode** %field30, align 8, !dbg !258
  %self31 = load %list_sNodep*, %list_sNodep** %self, align 8, !dbg !258
  %litem32 = load %list_item_sNodep*, %list_item_sNodep** %litem21, align 8, !dbg !258
  %field33 = getelementptr inbounds %list_sNodep, %list_sNodep* %self31, i32 0, i32 1, !dbg !258
  store %list_item_sNodep* %litem32, %list_item_sNodep** %field33, align 8, !dbg !258
  %self34 = load %list_sNodep*, %list_sNodep** %self, align 8, !dbg !258
  %field35 = getelementptr inbounds %list_sNodep, %list_sNodep* %self34, i32 0, i32 0, !dbg !258
  %head36 = load %list_item_sNodep*, %list_item_sNodep** %field35, align 8, !dbg !258
  %litem37 = load %list_item_sNodep*, %list_item_sNodep** %litem21, align 8, !dbg !258
  %field38 = getelementptr inbounds %list_item_sNodep, %list_item_sNodep* %head36, i32 0, i32 2, !dbg !258
  store %list_item_sNodep* %litem37, %list_item_sNodep** %field38, align 8, !dbg !258
  br label %cond_end, !dbg !258

cond_else_block:                                  ; preds = %cond_jump_elif0
  %fun_result39 = call i8* @GC_malloc(i64 24), !dbg !258
  %obj40 = bitcast i8* %fun_result39 to %list_item_sNodep*, !dbg !258
  store %list_item_sNodep* %obj40, %list_item_sNodep** %litem41, align 8, !dbg !258
  %litem42 = load %list_item_sNodep*, %list_item_sNodep** %litem41, align 8, !dbg !258
  %self43 = load %list_sNodep*, %list_sNodep** %self, align 8, !dbg !258
  %field44 = getelementptr inbounds %list_sNodep, %list_sNodep* %self43, i32 0, i32 1, !dbg !258
  %tail = load %list_item_sNodep*, %list_item_sNodep** %field44, align 8, !dbg !258
  %field45 = getelementptr inbounds %list_item_sNodep, %list_item_sNodep* %litem42, i32 0, i32 1, !dbg !258
  store %list_item_sNodep* %tail, %list_item_sNodep** %field45, align 8, !dbg !258
  %litem46 = load %list_item_sNodep*, %list_item_sNodep** %litem41, align 8, !dbg !258
  %field47 = getelementptr inbounds %list_item_sNodep, %list_item_sNodep* %litem46, i32 0, i32 2, !dbg !258
  store %list_item_sNodep* null, %list_item_sNodep** %field47, align 8, !dbg !258
  %litem48 = load %list_item_sNodep*, %list_item_sNodep** %litem41, align 8, !dbg !258
  %item49 = load %sNode*, %sNode** %item, align 8, !dbg !258
  %field50 = getelementptr inbounds %list_item_sNodep, %list_item_sNodep* %litem48, i32 0, i32 0, !dbg !258
  store %sNode* %item49, %sNode** %field50, align 8, !dbg !258
  %self51 = load %list_sNodep*, %list_sNodep** %self, align 8, !dbg !258
  %field52 = getelementptr inbounds %list_sNodep, %list_sNodep* %self51, i32 0, i32 1, !dbg !258
  %tail53 = load %list_item_sNodep*, %list_item_sNodep** %field52, align 8, !dbg !258
  %litem54 = load %list_item_sNodep*, %list_item_sNodep** %litem41, align 8, !dbg !258
  %field55 = getelementptr inbounds %list_item_sNodep, %list_item_sNodep* %tail53, i32 0, i32 2, !dbg !258
  store %list_item_sNodep* %litem54, %list_item_sNodep** %field55, align 8, !dbg !258
  %self56 = load %list_sNodep*, %list_sNodep** %self, align 8, !dbg !258
  %litem57 = load %list_item_sNodep*, %list_item_sNodep** %litem41, align 8, !dbg !258
  %field58 = getelementptr inbounds %list_sNodep, %list_sNodep* %self56, i32 0, i32 1, !dbg !258
  store %list_item_sNodep* %litem57, %list_item_sNodep** %field58, align 8, !dbg !258
  br label %cond_end, !dbg !258

cond_end:                                         ; preds = %cond_else_block, %cond_jump_elif_then0, %cond_jump_then
  %self59 = load %list_sNodep*, %list_sNodep** %self, align 8, !dbg !258
  %self60 = load %list_sNodep*, %list_sNodep** %self, align 8, !dbg !258
  %field61 = getelementptr inbounds %list_sNodep, %list_sNodep* %self60, i32 0, i32 2, !dbg !258
  %len62 = load i32, i32* %field61, align 4, !dbg !258
  %add = add i32 %len62, 1, !dbg !258
  %field63 = getelementptr inbounds %list_sNodep, %list_sNodep* %self59, i32 0, i32 2, !dbg !258
  store i32 %add, i32* %field63, align 4, !dbg !258
  %sub = sub i32 %add, 1, !dbg !258
  ret void, !dbg !258
}

attributes #0 = { nounwind }
attributes #1 = { nounwind willreturn }
attributes #2 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "come", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false)
!1 = !DIFile(filename: "src/01int.c", directory: "/home/ab25cq/repo/neo-c2/zash")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = distinct !DISubprogram(name: "ncmemdup", linkageName: "ncmemdup", scope: !6, file: !6, line: 27, type: !7, scopeLine: 27, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!6 = !DIFile(filename: "<stdin>", directory: "/home/ab25cq/repo/neo-c2/zash")
!7 = !DISubroutineType(types: !8)
!8 = !{!9}
!9 = !DIBasicType(name: "pointer", size: 64)
!10 = !DILocation(line: 27, scope: !5)
!11 = !DILocation(line: 29, scope: !5)
!12 = !DILocation(line: 31, scope: !5)
!13 = !DILocation(line: 32, scope: !5)
!14 = !DILocation(line: 35, scope: !5)
!15 = !DILocation(line: 37, scope: !5)
!16 = !DILocation(line: 38, scope: !5)
!17 = !DILocation(line: 39, scope: !5)
!18 = !DILocation(line: 45, scope: !5)
!19 = !DILocation(line: 47, scope: !5)
!20 = !DILocation(line: 40, scope: !5)
!21 = !DILocation(line: 41, scope: !5)
!22 = !DILocation(line: 42, scope: !5)
!23 = !DILocation(line: 43, scope: !5)
!24 = distinct !DISubprogram(name: "xsprintf", linkageName: "xsprintf", scope: !6, file: !6, line: 74, type: !7, scopeLine: 74, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!25 = !DILocation(line: 74, scope: !24)
!26 = !DILocation(line: 77, scope: !24)
!27 = !DILocation(line: 79, scope: !24)
!28 = !DILocation(line: 80, scope: !24)
!29 = !DILocation(line: 82, scope: !24)
!30 = !DILocation(line: 83, scope: !24)
!31 = !DILocation(line: 85, scope: !24)
!32 = !DILocation(line: 88, scope: !24)
!33 = !DILocation(line: 90, scope: !24)
!34 = !DILocation(line: 92, scope: !24)
!35 = distinct !DISubprogram(name: "char_reverse", linkageName: "char_reverse", scope: !6, file: !6, line: 95, type: !7, scopeLine: 95, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!36 = !DILocation(line: 95, scope: !35)
!37 = !DILocation(line: 97, scope: !35)
!38 = !DILocation(line: 98, scope: !35)
!39 = !DILocation(line: 100, scope: !35)
!40 = !DILocation(line: 101, scope: !35)
!41 = !DILocation(line: 104, scope: !35)
!42 = !DILocation(line: 106, scope: !35)
!43 = distinct !DISubprogram(name: "char_substring", linkageName: "char_substring", scope: !6, file: !6, line: 109, type: !44, scopeLine: 109, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!44 = !DISubroutineType(types: !45)
!45 = !{!9, !46, !46}
!46 = !DIBasicType(name: "int", size: 32)
!47 = !DILocation(line: 109, scope: !43)
!48 = !DILocation(line: 111, scope: !43)
!49 = !DILocation(line: 112, scope: !43)
!50 = !DILocation(line: 115, scope: !43)
!51 = !DILocation(line: 117, scope: !43)
!52 = !DILocation(line: 118, scope: !43)
!53 = !DILocation(line: 120, scope: !43)
!54 = !DILocation(line: 121, scope: !43)
!55 = !DILocation(line: 124, scope: !43)
!56 = !DILocation(line: 125, scope: !43)
!57 = !DILocation(line: 128, scope: !43)
!58 = !DILocation(line: 129, scope: !43)
!59 = !DILocation(line: 132, scope: !43)
!60 = !DILocation(line: 133, scope: !43)
!61 = !DILocation(line: 136, scope: !43)
!62 = !DILocation(line: 137, scope: !43)
!63 = !DILocation(line: 140, scope: !43)
!64 = !DILocation(line: 141, scope: !43)
!65 = !DILocation(line: 144, scope: !43)
!66 = !DILocation(line: 146, scope: !43)
!67 = !DILocation(line: 147, scope: !43)
!68 = !DILocation(line: 149, scope: !43)
!69 = distinct !DISubprogram(name: "char_length", linkageName: "char_length", scope: !6, file: !6, line: 152, type: !7, scopeLine: 152, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!70 = !DILocation(line: 152, scope: !69)
!71 = !DILocation(line: 154, scope: !69)
!72 = distinct !DISubprogram(name: "int_get_hash_key", linkageName: "int_get_hash_key", scope: !6, file: !6, line: 158, type: !73, scopeLine: 158, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!73 = !DISubroutineType(types: !74)
!74 = !{!46}
!75 = !DILocation(line: 158, scope: !72)
!76 = !DILocation(line: 160, scope: !72)
!77 = distinct !DISubprogram(name: "char_get_hash_key", linkageName: "char_get_hash_key", scope: !6, file: !6, line: 164, type: !7, scopeLine: 164, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!78 = !DILocation(line: 164, scope: !77)
!79 = !DILocation(line: 167, scope: !77)
!80 = !DILocation(line: 172, scope: !77)
!81 = !DILocation(line: 168, scope: !77)
!82 = !DILocation(line: 169, scope: !77)
!83 = !DILocation(line: 170, scope: !77)
!84 = distinct !DISubprogram(name: "char_equals", linkageName: "char_equals", scope: !6, file: !6, line: 175, type: !85, scopeLine: 175, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!85 = !DISubroutineType(types: !86)
!86 = !{!9, !9}
!87 = !DILocation(line: 175, scope: !84)
!88 = !DILocation(line: 177, scope: !84)
!89 = distinct !DISubprogram(name: "char_compare", linkageName: "char_compare", scope: !6, file: !6, line: 180, type: !90, scopeLine: 180, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!90 = !DISubroutineType(types: !91)
!91 = !{!46, !46}
!92 = !DILocation(line: 180, scope: !89)
!93 = !DILocation(line: 182, scope: !89)
!94 = !DILocation(line: 183, scope: !89)
!95 = !DILocation(line: 185, scope: !89)
!96 = !DILocation(line: 186, scope: !89)
!97 = !DILocation(line: 189, scope: !89)
!98 = distinct !DISubprogram(name: "buffer_initialize", linkageName: "buffer_initialize", scope: !6, file: !6, line: 1396, type: !7, scopeLine: 1396, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!99 = !DILocation(line: 1396, scope: !98)
!100 = !DILocation(line: 1398, scope: !98)
!101 = !DILocation(line: 1399, scope: !98)
!102 = !DILocation(line: 1401, scope: !98)
!103 = !DILocation(line: 1403, scope: !98)
!104 = distinct !DISubprogram(name: "buffer_length", linkageName: "buffer_length", scope: !6, file: !6, line: 1406, type: !7, scopeLine: 1406, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!105 = !DILocation(line: 1406, scope: !104)
!106 = !DILocation(line: 1408, scope: !104)
!107 = distinct !DISubprogram(name: "buffer_append", linkageName: "buffer_append", scope: !6, file: !6, line: 1411, type: !108, scopeLine: 1411, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!108 = !DISubroutineType(types: !109)
!109 = !{!9, !9, !110}
!110 = !DIBasicType(name: "long", size: 64)
!111 = !DILocation(line: 1411, scope: !107)
!112 = !DILocation(line: 1413, scope: !107)
!113 = !DILocation(line: 1414, scope: !107)
!114 = !DILocation(line: 1415, scope: !107)
!115 = !DILocation(line: 1416, scope: !107)
!116 = !DILocation(line: 1419, scope: !107)
!117 = !DILocation(line: 1420, scope: !107)
!118 = !DILocation(line: 1422, scope: !107)
!119 = distinct !DISubprogram(name: "buffer_append_char", linkageName: "buffer_append_char", scope: !6, file: !6, line: 1425, type: !120, scopeLine: 1425, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!120 = !DISubroutineType(types: !121)
!121 = !{!9, !122}
!122 = !DIBasicType(name: "char", size: 8)
!123 = !DILocation(line: 1425, scope: !119)
!124 = !DILocation(line: 1427, scope: !119)
!125 = !DILocation(line: 1428, scope: !119)
!126 = !DILocation(line: 1429, scope: !119)
!127 = !DILocation(line: 1430, scope: !119)
!128 = !DILocation(line: 1433, scope: !119)
!129 = !DILocation(line: 1434, scope: !119)
!130 = !DILocation(line: 1436, scope: !119)
!131 = distinct !DISubprogram(name: "buffer_append_str", linkageName: "buffer_append_str", scope: !6, file: !6, line: 1439, type: !85, scopeLine: 1439, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!132 = !DILocation(line: 1439, scope: !131)
!133 = !DILocation(line: 1441, scope: !131)
!134 = distinct !DISubprogram(name: "buffer_append_nullterminated_str", linkageName: "buffer_append_nullterminated_str", scope: !6, file: !6, line: 1444, type: !85, scopeLine: 1444, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!135 = !DILocation(line: 1444, scope: !134)
!136 = !DILocation(line: 1446, scope: !134)
!137 = !DILocation(line: 1447, scope: !134)
!138 = distinct !DISubprogram(name: "buffer_to_string", linkageName: "buffer_to_string", scope: !6, file: !6, line: 1450, type: !7, scopeLine: 1450, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!139 = !DILocation(line: 1450, scope: !138)
!140 = !DILocation(line: 1453, scope: !138)
!141 = distinct !DISubprogram(name: "buffer_append_int", linkageName: "buffer_append_int", scope: !6, file: !6, line: 1455, type: !142, scopeLine: 1455, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!142 = !DISubroutineType(types: !143)
!143 = !{!9, !46}
!144 = !DILocation(line: 1455, scope: !141)
!145 = !DILocation(line: 1457, scope: !141)
!146 = distinct !DISubprogram(name: "buffer_append_long", linkageName: "buffer_append_long", scope: !6, file: !6, line: 1460, type: !147, scopeLine: 1460, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!147 = !DISubroutineType(types: !148)
!148 = !{!9, !110}
!149 = !DILocation(line: 1460, scope: !146)
!150 = !DILocation(line: 1462, scope: !146)
!151 = distinct !DISubprogram(name: "buffer_append_short", linkageName: "buffer_append_short", scope: !6, file: !6, line: 1465, type: !152, scopeLine: 1465, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!152 = !DISubroutineType(types: !153)
!153 = !{!9, !154}
!154 = !DIBasicType(name: "short", size: 16)
!155 = !DILocation(line: 1465, scope: !151)
!156 = !DILocation(line: 1467, scope: !151)
!157 = distinct !DISubprogram(name: "buffer_alignment", linkageName: "buffer_alignment", scope: !6, file: !6, line: 1470, type: !7, scopeLine: 1470, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!158 = !DILocation(line: 1470, scope: !157)
!159 = !DILocation(line: 1472, scope: !157)
!160 = !DILocation(line: 1473, scope: !157)
!161 = !DILocation(line: 1475, scope: !157)
!162 = !DILocation(line: 1476, scope: !157)
!163 = distinct !DISubprogram(name: "buffer_compare", linkageName: "buffer_compare", scope: !6, file: !6, line: 1480, type: !85, scopeLine: 1480, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!164 = !DILocation(line: 1480, scope: !163)
!165 = !DILocation(line: 1482, scope: !163)
!166 = distinct !DISubprogram(name: "char_to_buffer", linkageName: "char_to_buffer", scope: !6, file: !6, line: 1485, type: !7, scopeLine: 1485, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!167 = !DILocation(line: 1485, scope: !166)
!168 = !DILocation(line: 1487, scope: !166)
!169 = !DILocation(line: 1489, scope: !166)
!170 = !DILocation(line: 1491, scope: !166)
!171 = distinct !DISubprogram(name: "come_fd_zero", linkageName: "come_fd_zero", scope: !6, file: !6, line: 1494, type: !7, scopeLine: 1494, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!172 = !DILocation(line: 1494, scope: !171)
!173 = !DILocation(line: 1496, scope: !171)
!174 = distinct !DISubprogram(name: "come_fd_set", linkageName: "come_fd_set", scope: !6, file: !6, line: 1499, type: !175, scopeLine: 1499, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!175 = !DISubroutineType(types: !176)
!176 = !{!46, !9}
!177 = !DILocation(line: 1499, scope: !174)
!178 = !DILocation(line: 1501, scope: !174)
!179 = distinct !DISubprogram(name: "come_fd_isset", linkageName: "come_fd_isset", scope: !6, file: !6, line: 1504, type: !175, scopeLine: 1504, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!180 = !DILocation(line: 1504, scope: !179)
!181 = !DILocation(line: 1507, scope: !179)
!182 = distinct !DISubprogram(name: "int_expect", linkageName: "int_expect", scope: !6, file: !6, line: 1510, type: !183, scopeLine: 1510, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!183 = !DISubroutineType(types: !184)
!184 = !{!46, !9, !9}
!185 = !DILocation(line: 1510, scope: !182)
!186 = !DILocation(line: 1512, scope: !182)
!187 = !DILocation(line: 1513, scope: !182)
!188 = !DILocation(line: 1516, scope: !182)
!189 = distinct !DISubprogram(name: "bool_expect", linkageName: "bool_expect", scope: !6, file: !6, line: 1519, type: !190, scopeLine: 1519, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!190 = !DISubroutineType(types: !191)
!191 = !{null, !9, !9}
!192 = !DILocation(line: 1519, scope: !189)
!193 = !DILocation(line: 1521, scope: !189)
!194 = !DILocation(line: 1522, scope: !189)
!195 = !DILocation(line: 1525, scope: !189)
!196 = distinct !DISubprogram(name: "int_times", linkageName: "int_times", scope: !6, file: !6, line: 1528, type: !183, scopeLine: 1528, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!197 = !DILocation(line: 1528, scope: !196)
!198 = !DILocation(line: 1531, scope: !196)
!199 = !DILocation(line: 1532, scope: !196)
!200 = distinct !DISubprogram(name: "xiswalpha", linkageName: "xiswalpha", scope: !6, file: !6, line: 1589, type: !73, scopeLine: 1589, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!201 = !DILocation(line: 1589, scope: !200)
!202 = !DILocation(line: 1591, scope: !200)
!203 = !DILocation(line: 1592, scope: !200)
!204 = distinct !DISubprogram(name: "xiswblank", linkageName: "xiswblank", scope: !6, file: !6, line: 1595, type: !73, scopeLine: 1595, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!205 = !DILocation(line: 1595, scope: !204)
!206 = !DILocation(line: 1597, scope: !204)
!207 = distinct !DISubprogram(name: "xiswdigit", linkageName: "xiswdigit", scope: !6, file: !6, line: 1600, type: !73, scopeLine: 1600, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!208 = !DILocation(line: 1600, scope: !207)
!209 = !DILocation(line: 1602, scope: !207)
!210 = distinct !DISubprogram(name: "xiswalnum", linkageName: "xiswalnum", scope: !6, file: !6, line: 1605, type: !73, scopeLine: 1605, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!211 = !DILocation(line: 1605, scope: !210)
!212 = !DILocation(line: 1607, scope: !210)
!213 = distinct !DISubprogram(name: "xbasename", linkageName: "xbasename", scope: !6, file: !6, line: 1610, type: !7, scopeLine: 1610, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!214 = !DILocation(line: 1610, scope: !213)
!215 = !DILocation(line: 1612, scope: !213)
!216 = !DILocation(line: 1623, scope: !213)
!217 = !DILocation(line: 1614, scope: !213)
!218 = !DILocation(line: 1615, scope: !213)
!219 = !DILocation(line: 1616, scope: !213)
!220 = !DILocation(line: 1619, scope: !213)
!221 = !DILocation(line: 1624, scope: !213)
!222 = !DILocation(line: 1627, scope: !213)
!223 = distinct !DISubprogram(name: "xextname", linkageName: "xextname", scope: !6, file: !6, line: 1631, type: !7, scopeLine: 1631, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!224 = !DILocation(line: 1631, scope: !223)
!225 = !DILocation(line: 1633, scope: !223)
!226 = !DILocation(line: 1644, scope: !223)
!227 = !DILocation(line: 1635, scope: !223)
!228 = !DILocation(line: 1636, scope: !223)
!229 = !DILocation(line: 1637, scope: !223)
!230 = !DILocation(line: 1640, scope: !223)
!231 = !DILocation(line: 1645, scope: !223)
!232 = !DILocation(line: 1648, scope: !223)
!233 = distinct !DISubprogram(name: "xrealpath", linkageName: "xrealpath", scope: !6, file: !6, line: 1652, type: !7, scopeLine: 1652, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!234 = !DILocation(line: 1652, scope: !233)
!235 = !DILocation(line: 1654, scope: !233)
!236 = !DILocation(line: 1656, scope: !233)
!237 = !DILocation(line: 1658, scope: !233)
!238 = !DILocation(line: 1660, scope: !233)
!239 = distinct !DISubprogram(name: "parse", linkageName: "parse", scope: !1, file: !1, line: 51, type: !240, scopeLine: 51, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!240 = !DISubroutineType(types: !241)
!241 = !{!9, !9, !9}
!242 = !DILocation(line: 51, scope: !239)
!243 = !DILocation(line: 53, scope: !239)
!244 = !DILocation(line: 55, scope: !239)
!245 = !DILocation(line: 56, scope: !239)
!246 = !DILocation(line: 57, scope: !239)
!247 = !DILocation(line: 60, scope: !239)
!248 = !DILocation(line: 70, scope: !239)
!249 = !DILocation(line: 64, scope: !239)
!250 = !DILocation(line: 66, scope: !239)
!251 = !DILocation(line: 67, scope: !239)
!252 = !DILocation(line: 72, scope: !239)
!253 = !DILocation(line: 85, scope: !239)
!254 = !DILocation(line: 75, scope: !239)
!255 = !DILocation(line: 77, scope: !239)
!256 = !DILocation(line: 78, scope: !239)
!257 = !DILocation(line: 79, scope: !239)
!258 = !DILocation(line: 82, scope: !239)
!259 = distinct !DISubprogram(name: "compile", linkageName: "compile", scope: !1, file: !1, line: 88, type: !85, scopeLine: 88, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!260 = !DILocation(line: 88, scope: !259)
!261 = !DILocation(line: 90, scope: !259)
!262 = !DILocation(line: 91, scope: !259)
!263 = !DILocation(line: 92, scope: !259)
!264 = !DILocation(line: 95, scope: !259)
!265 = distinct !DISubprogram(name: "run", linkageName: "run", scope: !1, file: !1, line: 98, type: !7, scopeLine: 98, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!266 = !DILocation(line: 98, scope: !265)
!267 = !DILocation(line: 100, scope: !265)
!268 = !DILocation(line: 101, scope: !265)
!269 = !DILocation(line: 102, scope: !265)
!270 = !DILocation(line: 103, scope: !265)
!271 = !DILocation(line: 105, scope: !265)
!272 = !DILocation(line: 108, scope: !265)
!273 = distinct !DISubprogram(name: "skip_spaces", linkageName: "skip_spaces", scope: !1, file: !1, line: 4, type: !85, scopeLine: 4, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!274 = !DILocation(line: 4, scope: !273)
!275 = !DILocation(line: 9, scope: !273)
!276 = !DILocation(line: 6, scope: !273)
!277 = !DILocation(line: 7, scope: !273)
!278 = distinct !DISubprogram(name: "create_int_node", linkageName: "create_int_node", scope: !1, file: !1, line: 11, type: !279, scopeLine: 11, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!279 = !DISubroutineType(types: !280)
!280 = !{!46, !9, !46}
!281 = !DILocation(line: 11, scope: !278)
!282 = !DILocation(line: 13, scope: !278)
!283 = !DILocation(line: 15, scope: !278)
!284 = !DILocation(line: 17, scope: !278)
!285 = !DILocation(line: 18, scope: !278)
!286 = !DILocation(line: 19, scope: !278)
!287 = !DILocation(line: 21, scope: !278)
!288 = distinct !DISubprogram(name: "exp_node", linkageName: "exp_node", scope: !1, file: !1, line: 24, type: !240, scopeLine: 24, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!289 = !DILocation(line: 24, scope: !288)
!290 = !DILocation(line: 26, scope: !288)
!291 = !DILocation(line: 32, scope: !288)
!292 = !DILocation(line: 37, scope: !288)
!293 = !DILocation(line: 28, scope: !288)
!294 = !DILocation(line: 29, scope: !288)
!295 = !DILocation(line: 30, scope: !288)
!296 = !DILocation(line: 34, scope: !288)
!297 = distinct !DISubprogram(name: "expression", linkageName: "expression", scope: !1, file: !1, line: 40, type: !298, scopeLine: 40, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!298 = !DISubroutineType(types: !299)
!299 = !{!9, !9, !9, !9}
!300 = !DILocation(line: 40, scope: !297)
!301 = !DILocation(line: 42, scope: !297)
!302 = !DILocation(line: 44, scope: !297)
!303 = !DILocation(line: 45, scope: !297)
!304 = !DILocation(line: 48, scope: !297)
