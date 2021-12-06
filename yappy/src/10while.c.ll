; ModuleID = 'src/10while.c'
source_filename = "src/10while.c"

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
%stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %timespec, %timespec, %timespec, [3 x i64] }
%stat64 = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %timespec, %timespec, %timespec, [3 x i64] }
%statx = type { i32, i32, i64, i32, i32, i32, i16, [1 x i16], i64, i64, i64, i64, %statx_timestamp, %statx_timestamp, %statx_timestamp, %statx_timestamp, i32, i32, i32, i32, [14 x i64] }
%statx_timestamp = type { i64, i32, [1 x i32] }
%buffer = type { i8*, i32, i32 }
%sParserInfo = type { i8*, i32, i8*, i32, i1, i32, i32, %vector_int* }
%vector_int = type { i32*, i32, i32, i32 }
%list_sNodep = type { %list_item_sNodep*, %list_item_sNodep*, i32, %list_item_sNodep* }
%list_item_sNodep = type { %sNode*, %list_item_sNodep*, %list_item_sNodep* }
%sNode = type { i32, i8*, i32, %come_anon75 }
%come_anon75 = type { %come_anon81 }
%come_anon81 = type { %sNode*, %buffer*, %vector_sNodep*, %vector_bufferp*, %buffer* }
%vector_sNodep = type { %sNode**, i32, i32, i32 }
%vector_bufferp = type { %buffer**, i32, i32, i32 }
%map_charp_ZVALUE = type { i8**, i1*, %ZVALUE*, i32, i32, i32 }
%ZVALUE = type { i32, %come_anon86 }
%come_anon86 = type { i64 }
%come_anon82 = type { %sNode*, %list_sNodep*, %list_sNodep* }

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
@while = private unnamed_addr constant [6 x i8] c"while\00", align 1
@while.1 = private unnamed_addr constant [6 x i8] c"while\00", align 1
@"%s %d: invalid while exp\0A" = private unnamed_addr constant [26 x i8] c"%s %d: invalid while exp\0A\00", align 1
@"%s %d: require : for block\0A" = private unnamed_addr constant [28 x i8] c"%s %d: require : for block\0A\00", align 1
@else = private unnamed_addr constant [5 x i8] c"else\00", align 1
@else.2 = private unnamed_addr constant [5 x i8] c"else\00", align 1
@"%s %d: require : for block\0A.3" = private unnamed_addr constant [28 x i8] c"%s %d: require : for block\0A\00", align 1
@break = private unnamed_addr constant [6 x i8] c"break\00", align 1
@break.4 = private unnamed_addr constant [6 x i8] c"break\00", align 1
@continue = private unnamed_addr constant [9 x i8] c"continue\00", align 1
@continue.5 = private unnamed_addr constant [9 x i8] c"continue\00", align 1
@"%s %d: require loop for break\0A" = private unnamed_addr constant [31 x i8] c"%s %d: require loop for break\0A\00", align 1
@"%s %d: require loop for continue\0A" = private unnamed_addr constant [34 x i8] c"%s %d: require loop for continue\0A\00", align 1

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
  %new_size = alloca i32, align 4, !dbg !158
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
  %len4 = load i32, i32* %len2, align 4, !dbg !161
  %self5 = load %buffer*, %buffer** %self, align 8, !dbg !161
  %field6 = getelementptr inbounds %buffer, %buffer* %self5, i32 0, i32 2, !dbg !161
  %size = load i32, i32* %field6, align 4, !dbg !161
  %gteq = icmp sge i32 %len4, %size, !dbg !161
  br i1 %gteq, label %cond_jump_then, label %cond_end, !dbg !161

cond_jump_then:                                   ; preds = %entry
  %self7 = load %buffer*, %buffer** %self, align 8, !dbg !162
  %field8 = getelementptr inbounds %buffer, %buffer* %self7, i32 0, i32 2, !dbg !162
  %size9 = load i32, i32* %field8, align 4, !dbg !162
  %add10 = add i32 %size9, 1, !dbg !162
  %add11 = add i32 %add10, 1, !dbg !162
  %mul = mul i32 %add11, 2, !dbg !162
  store i32 %mul, i32* %new_size, align 4, !dbg !158
  %self12 = load %buffer*, %buffer** %self, align 8, !dbg !163
  %self13 = load %buffer*, %buffer** %self, align 8, !dbg !163
  %field14 = getelementptr inbounds %buffer, %buffer* %self13, i32 0, i32 0, !dbg !163
  %buf = load i8*, i8** %field14, align 8, !dbg !163
  %new_size15 = load i32, i32* %new_size, align 4, !dbg !163
  %icastD = sext i32 %new_size15 to i64, !dbg !163
  %fun_result = call i8* @GC_realloc(i8* %buf, i64 %icastD), !dbg !163
  %field16 = getelementptr inbounds %buffer, %buffer* %self12, i32 0, i32 0, !dbg !163
  store i8* %fun_result, i8** %field16, align 8, !dbg !163
  %self17 = load %buffer*, %buffer** %self, align 8, !dbg !164
  %new_size18 = load i32, i32* %new_size, align 4, !dbg !164
  %field19 = getelementptr inbounds %buffer, %buffer* %self17, i32 0, i32 2, !dbg !164
  store i32 %new_size18, i32* %field19, align 4, !dbg !164
  br label %cond_end, !dbg !164

cond_end:                                         ; preds = %cond_jump_then, %entry
  %self20 = load %buffer*, %buffer** %self, align 8, !dbg !165
  %field21 = getelementptr inbounds %buffer, %buffer* %self20, i32 0, i32 1, !dbg !165
  %len22 = load i32, i32* %field21, align 4, !dbg !165
  store i32 %len22, i32* %i, align 4, !dbg !158
  br label %loop_top_block, !dbg !158

loop_top_block:                                   ; preds = %cond_then_block, %cond_end
  %i23 = load i32, i32* %i, align 4, !dbg !165
  %len24 = load i32, i32* %len2, align 4, !dbg !165
  %le = icmp slt i32 %i23, %len24, !dbg !165
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !165

cond_then_block:                                  ; preds = %loop_top_block
  %self25 = load %buffer*, %buffer** %self, align 8, !dbg !166
  %field26 = getelementptr inbounds %buffer, %buffer* %self25, i32 0, i32 0, !dbg !166
  %buf27 = load i8*, i8** %field26, align 8, !dbg !166
  %i28 = load i32, i32* %i, align 4, !dbg !166
  %element_address = getelementptr i8, i8* %buf27, i32 %i28, !dbg !166
  store i8 0, i8* %element_address, align 1, !dbg !166
  %i29 = load i32, i32* %i, align 4, !dbg !165
  %add30 = add i32 %i29, 1, !dbg !165
  store i32 %add30, i32* %i, align 4, !dbg !165
  %sub = sub i32 %add30, 1, !dbg !165
  br label %loop_top_block, !dbg !165

cond_end_block:                                   ; preds = %loop_top_block
  %self31 = load %buffer*, %buffer** %self, align 8, !dbg !167
  %len32 = load i32, i32* %len2, align 4, !dbg !167
  %field33 = getelementptr inbounds %buffer, %buffer* %self31, i32 0, i32 1, !dbg !167
  store i32 %len32, i32* %field33, align 4, !dbg !167
  ret void, !dbg !167
}

define internal i32 @buffer_compare(%buffer* %0, %buffer* %1) !dbg !168 {
entry:
  %left = alloca %buffer*, align 8, !dbg !169
  store %buffer* %0, %buffer** %left, align 8, !dbg !169
  %right = alloca %buffer*, align 8, !dbg !169
  store %buffer* %1, %buffer** %right, align 8, !dbg !169
  %left1 = load %buffer*, %buffer** %left, align 8, !dbg !170
  %field = getelementptr inbounds %buffer, %buffer* %left1, i32 0, i32 0, !dbg !170
  %buf = load i8*, i8** %field, align 8, !dbg !170
  %right2 = load %buffer*, %buffer** %right, align 8, !dbg !170
  %field3 = getelementptr inbounds %buffer, %buffer* %right2, i32 0, i32 0, !dbg !170
  %buf4 = load i8*, i8** %field3, align 8, !dbg !170
  %fun_result = call i32 @strcmp(i8* %buf, i8* %buf4), !dbg !170
  ret i32 %fun_result, !dbg !170
}

define internal %buffer* @char_to_buffer(i8* %0) !dbg !171 {
entry:
  %result = alloca %buffer*, align 8, !dbg !172
  %self = alloca i8*, align 8, !dbg !172
  store i8* %0, i8** %self, align 8, !dbg !172
  %fun_result = call i8* @GC_malloc(i64 16), !dbg !173
  %obj = bitcast i8* %fun_result to %buffer*, !dbg !173
  %fun_result1 = call %buffer* @buffer_initialize(%buffer* %obj), !dbg !173
  store %buffer* %fun_result1, %buffer** %result, align 8, !dbg !172
  %result2 = load %buffer*, %buffer** %result, align 8, !dbg !174
  %self3 = load i8*, i8** %self, align 8, !dbg !174
  call void @buffer_append_str(%buffer* %result2, i8* %self3), !dbg !174
  %result4 = load %buffer*, %buffer** %result, align 8, !dbg !175
  ret %buffer* %result4, !dbg !175
}

define internal i32 @int_expect(i32 %0, i8* %1, void (i8*)* %2) !dbg !176 {
entry:
  %self = alloca i32, align 4, !dbg !179
  store i32 %0, i32* %self, align 4, !dbg !179
  %parent = alloca i8*, align 8, !dbg !179
  store i8* %1, i8** %parent, align 8, !dbg !179
  %block = alloca void (i8*)*, align 8, !dbg !179
  store void (i8*)* %2, void (i8*)** %block, align 8, !dbg !179
  %self1 = load i32, i32* %self, align 4, !dbg !180
  %le = icmp slt i32 %self1, 0, !dbg !180
  br i1 %le, label %cond_jump_then, label %cond_end, !dbg !180

cond_jump_then:                                   ; preds = %entry
  %block2 = load void (i8*)*, void (i8*)** %block, align 8, !dbg !181
  %parent3 = load i8*, i8** %parent, align 8, !dbg !181
  call void %block2(i8* %parent3), !dbg !181
  br label %cond_end, !dbg !181

cond_end:                                         ; preds = %cond_jump_then, %entry
  %self4 = load i32, i32* %self, align 4, !dbg !182
  ret i32 %self4, !dbg !182
}

define internal i1 @bool_expect(i1 %0, i8* %1, void (i8*)* %2) !dbg !183 {
entry:
  %self = alloca i1, align 1, !dbg !186
  store i1 %0, i1* %self, align 1, !dbg !186
  %parent = alloca i8*, align 8, !dbg !186
  store i8* %1, i8** %parent, align 8, !dbg !186
  %block = alloca void (i8*)*, align 8, !dbg !186
  store void (i8*)* %2, void (i8*)** %block, align 8, !dbg !186
  %self1 = load i1, i1* %self, align 1, !dbg !187
  %logical_denial = icmp eq i1 %self1, false, !dbg !187
  br i1 %logical_denial, label %cond_jump_then, label %cond_end, !dbg !187

cond_jump_then:                                   ; preds = %entry
  %block2 = load void (i8*)*, void (i8*)** %block, align 8, !dbg !188
  %parent3 = load i8*, i8** %parent, align 8, !dbg !188
  call void %block2(i8* %parent3), !dbg !188
  br label %cond_end, !dbg !188

cond_end:                                         ; preds = %cond_jump_then, %entry
  %self4 = load i1, i1* %self, align 1, !dbg !189
  ret i1 %self4, !dbg !189
}

define internal void @int_times(i32 %0, i8* %1, void (i8*)* %2) !dbg !190 {
entry:
  %i = alloca i32, align 4, !dbg !191
  %self = alloca i32, align 4, !dbg !191
  store i32 %0, i32* %self, align 4, !dbg !191
  %parent = alloca i8*, align 8, !dbg !191
  store i8* %1, i8** %parent, align 8, !dbg !191
  %block = alloca void (i8*)*, align 8, !dbg !191
  store void (i8*)* %2, void (i8*)** %block, align 8, !dbg !191
  store i32 0, i32* %i, align 4, !dbg !192
  br label %loop_top_block, !dbg !192

loop_top_block:                                   ; preds = %cond_then_block, %entry
  %i1 = load i32, i32* %i, align 4, !dbg !192
  %self2 = load i32, i32* %self, align 4, !dbg !192
  %le = icmp slt i32 %i1, %self2, !dbg !192
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !192

cond_then_block:                                  ; preds = %loop_top_block
  %block3 = load void (i8*)*, void (i8*)** %block, align 8, !dbg !193
  %parent4 = load i8*, i8** %parent, align 8, !dbg !193
  call void %block3(i8* %parent4), !dbg !193
  %i5 = load i32, i32* %i, align 4, !dbg !192
  %add = add i32 %i5, 1, !dbg !192
  store i32 %add, i32* %i, align 4, !dbg !192
  %sub = sub i32 %add, 1, !dbg !192
  br label %loop_top_block, !dbg !192

cond_end_block:                                   ; preds = %loop_top_block
  ret void, !dbg !192
}

define internal i1 @xiswalpha(i32 %0) !dbg !194 {
entry:
  %result = alloca i1, align 1, !dbg !195
  %andand6 = alloca i1, align 1, !dbg !195
  %andand = alloca i1, align 1, !dbg !195
  %oror = alloca i1, align 1, !dbg !195
  %c = alloca i32, align 4, !dbg !195
  store i32 %0, i32* %c, align 4, !dbg !195
  %c1 = load i32, i32* %c, align 4, !dbg !196
  %gteq = icmp sge i32 %c1, 97, !dbg !196
  store i1 %gteq, i1* %andand, align 1, !dbg !196
  br i1 %gteq, label %cond_jump_then, label %cond_jump_end, !dbg !196

cond_jump_then:                                   ; preds = %entry
  %c2 = load i32, i32* %c, align 4, !dbg !196
  %leeq = icmp sle i32 %c2, 122, !dbg !196
  %andand3 = and i1 %gteq, %leeq, !dbg !196
  store i1 %andand3, i1* %andand, align 1, !dbg !196
  br label %cond_jump_end, !dbg !196

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %andand_result_value = load i1, i1* %andand, align 1, !dbg !196
  store i1 %andand_result_value, i1* %oror, align 1, !dbg !196
  br i1 %andand_result_value, label %cond_jump_end5, label %cond_jump_then4, !dbg !196

cond_jump_then4:                                  ; preds = %cond_jump_end
  %c7 = load i32, i32* %c, align 4, !dbg !196
  %gteq8 = icmp sge i32 %c7, 65, !dbg !196
  store i1 %gteq8, i1* %andand6, align 1, !dbg !196
  br i1 %gteq8, label %cond_jump_then9, label %cond_jump_end10, !dbg !196

cond_jump_end5:                                   ; preds = %cond_jump_end10, %cond_jump_end
  %oror_result_value = load i1, i1* %oror, align 1, !dbg !196
  store i1 %oror_result_value, i1* %result, align 1, !dbg !195
  %result16 = load i1, i1* %result, align 1, !dbg !197
  ret i1 %result16, !dbg !197

cond_jump_then9:                                  ; preds = %cond_jump_then4
  %c11 = load i32, i32* %c, align 4, !dbg !196
  %leeq12 = icmp sle i32 %c11, 90, !dbg !196
  %andand13 = and i1 %gteq8, %leeq12, !dbg !196
  store i1 %andand13, i1* %andand6, align 1, !dbg !196
  br label %cond_jump_end10, !dbg !196

cond_jump_end10:                                  ; preds = %cond_jump_then9, %cond_jump_then4
  %andand_result_value14 = load i1, i1* %andand6, align 1, !dbg !196
  %oror15 = or i1 %andand_result_value, %andand_result_value14, !dbg !196
  store i1 %oror15, i1* %oror, align 1, !dbg !196
  br label %cond_jump_end5, !dbg !196
}

define internal i1 @xiswblank(i32 %0) !dbg !198 {
entry:
  %oror = alloca i1, align 1, !dbg !199
  %c = alloca i32, align 4, !dbg !199
  store i32 %0, i32* %c, align 4, !dbg !199
  %c1 = load i32, i32* %c, align 4, !dbg !200
  %eq = icmp eq i32 %c1, 32, !dbg !200
  store i1 %eq, i1* %oror, align 1, !dbg !200
  br i1 %eq, label %cond_jump_end, label %cond_jump_then, !dbg !200

cond_jump_then:                                   ; preds = %entry
  %c2 = load i32, i32* %c, align 4, !dbg !200
  %eq3 = icmp eq i32 %c2, 9, !dbg !200
  %oror4 = or i1 %eq, %eq3, !dbg !200
  store i1 %oror4, i1* %oror, align 1, !dbg !200
  br label %cond_jump_end, !dbg !200

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %oror_result_value = load i1, i1* %oror, align 1, !dbg !200
  ret i1 %oror_result_value, !dbg !200
}

define internal i1 @xiswdigit(i32 %0) !dbg !201 {
entry:
  %andand = alloca i1, align 1, !dbg !202
  %c = alloca i32, align 4, !dbg !202
  store i32 %0, i32* %c, align 4, !dbg !202
  %c1 = load i32, i32* %c, align 4, !dbg !203
  %gteq = icmp sge i32 %c1, 48, !dbg !203
  store i1 %gteq, i1* %andand, align 1, !dbg !203
  br i1 %gteq, label %cond_jump_then, label %cond_jump_end, !dbg !203

cond_jump_then:                                   ; preds = %entry
  %c2 = load i32, i32* %c, align 4, !dbg !203
  %leeq = icmp sle i32 %c2, 57, !dbg !203
  %andand3 = and i1 %gteq, %leeq, !dbg !203
  store i1 %andand3, i1* %andand, align 1, !dbg !203
  br label %cond_jump_end, !dbg !203

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %andand_result_value = load i1, i1* %andand, align 1, !dbg !203
  ret i1 %andand_result_value, !dbg !203
}

define internal i1 @xiswalnum(i32 %0) !dbg !204 {
entry:
  %oror = alloca i1, align 1, !dbg !205
  %c = alloca i32, align 4, !dbg !205
  store i32 %0, i32* %c, align 4, !dbg !205
  %c1 = load i32, i32* %c, align 4, !dbg !206
  %fun_result = call i1 @xiswalpha(i32 %c1), !dbg !206
  store i1 %fun_result, i1* %oror, align 1, !dbg !206
  br i1 %fun_result, label %cond_jump_end, label %cond_jump_then, !dbg !206

cond_jump_then:                                   ; preds = %entry
  %c2 = load i32, i32* %c, align 4, !dbg !206
  %fun_result3 = call i1 @xiswdigit(i32 %c2), !dbg !206
  %oror4 = or i1 %fun_result, %fun_result3, !dbg !206
  store i1 %oror4, i1* %oror, align 1, !dbg !206
  br label %cond_jump_end, !dbg !206

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %oror_result_value = load i1, i1* %oror, align 1, !dbg !206
  ret i1 %oror_result_value, !dbg !206
}

define internal i1 @xisalpha(i8 %0) !dbg !207 {
entry:
  %result = alloca i1, align 1, !dbg !210
  %andand6 = alloca i1, align 1, !dbg !210
  %andand = alloca i1, align 1, !dbg !210
  %oror = alloca i1, align 1, !dbg !210
  %c = alloca i8, align 1, !dbg !210
  store i8 %0, i8* %c, align 1, !dbg !210
  %c1 = load i8, i8* %c, align 1, !dbg !211
  %gteq = icmp sge i8 %c1, 97, !dbg !211
  store i1 %gteq, i1* %andand, align 1, !dbg !211
  br i1 %gteq, label %cond_jump_then, label %cond_jump_end, !dbg !211

cond_jump_then:                                   ; preds = %entry
  %c2 = load i8, i8* %c, align 1, !dbg !211
  %leeq = icmp sle i8 %c2, 122, !dbg !211
  %andand3 = and i1 %gteq, %leeq, !dbg !211
  store i1 %andand3, i1* %andand, align 1, !dbg !211
  br label %cond_jump_end, !dbg !211

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %andand_result_value = load i1, i1* %andand, align 1, !dbg !211
  store i1 %andand_result_value, i1* %oror, align 1, !dbg !211
  br i1 %andand_result_value, label %cond_jump_end5, label %cond_jump_then4, !dbg !211

cond_jump_then4:                                  ; preds = %cond_jump_end
  %c7 = load i8, i8* %c, align 1, !dbg !211
  %gteq8 = icmp sge i8 %c7, 65, !dbg !211
  store i1 %gteq8, i1* %andand6, align 1, !dbg !211
  br i1 %gteq8, label %cond_jump_then9, label %cond_jump_end10, !dbg !211

cond_jump_end5:                                   ; preds = %cond_jump_end10, %cond_jump_end
  %oror_result_value = load i1, i1* %oror, align 1, !dbg !211
  store i1 %oror_result_value, i1* %result, align 1, !dbg !210
  %result16 = load i1, i1* %result, align 1, !dbg !212
  ret i1 %result16, !dbg !212

cond_jump_then9:                                  ; preds = %cond_jump_then4
  %c11 = load i8, i8* %c, align 1, !dbg !211
  %leeq12 = icmp sle i8 %c11, 90, !dbg !211
  %andand13 = and i1 %gteq8, %leeq12, !dbg !211
  store i1 %andand13, i1* %andand6, align 1, !dbg !211
  br label %cond_jump_end10, !dbg !211

cond_jump_end10:                                  ; preds = %cond_jump_then9, %cond_jump_then4
  %andand_result_value14 = load i1, i1* %andand6, align 1, !dbg !211
  %oror15 = or i1 %andand_result_value, %andand_result_value14, !dbg !211
  store i1 %oror15, i1* %oror, align 1, !dbg !211
  br label %cond_jump_end5, !dbg !211
}

define internal i1 @xisblank(i8 %0) !dbg !213 {
entry:
  %oror = alloca i1, align 1, !dbg !214
  %c = alloca i8, align 1, !dbg !214
  store i8 %0, i8* %c, align 1, !dbg !214
  %c1 = load i8, i8* %c, align 1, !dbg !215
  %eq = icmp eq i8 %c1, 32, !dbg !215
  store i1 %eq, i1* %oror, align 1, !dbg !215
  br i1 %eq, label %cond_jump_end, label %cond_jump_then, !dbg !215

cond_jump_then:                                   ; preds = %entry
  %c2 = load i8, i8* %c, align 1, !dbg !215
  %eq3 = icmp eq i8 %c2, 9, !dbg !215
  %oror4 = or i1 %eq, %eq3, !dbg !215
  store i1 %oror4, i1* %oror, align 1, !dbg !215
  br label %cond_jump_end, !dbg !215

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %oror_result_value = load i1, i1* %oror, align 1, !dbg !215
  ret i1 %oror_result_value, !dbg !215
}

define internal i1 @xisdigit(i8 %0) !dbg !216 {
entry:
  %andand = alloca i1, align 1, !dbg !217
  %c = alloca i8, align 1, !dbg !217
  store i8 %0, i8* %c, align 1, !dbg !217
  %c1 = load i8, i8* %c, align 1, !dbg !218
  %gteq = icmp sge i8 %c1, 48, !dbg !218
  store i1 %gteq, i1* %andand, align 1, !dbg !218
  br i1 %gteq, label %cond_jump_then, label %cond_jump_end, !dbg !218

cond_jump_then:                                   ; preds = %entry
  %c2 = load i8, i8* %c, align 1, !dbg !218
  %leeq = icmp sle i8 %c2, 57, !dbg !218
  %andand3 = and i1 %gteq, %leeq, !dbg !218
  store i1 %andand3, i1* %andand, align 1, !dbg !218
  br label %cond_jump_end, !dbg !218

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %andand_result_value = load i1, i1* %andand, align 1, !dbg !218
  ret i1 %andand_result_value, !dbg !218
}

define internal i1 @xisalnum(i8 %0) !dbg !219 {
entry:
  %oror = alloca i1, align 1, !dbg !220
  %c = alloca i8, align 1, !dbg !220
  store i8 %0, i8* %c, align 1, !dbg !220
  %c1 = load i8, i8* %c, align 1, !dbg !221
  %fun_result = call i1 @xisalpha(i8 %c1), !dbg !221
  store i1 %fun_result, i1* %oror, align 1, !dbg !221
  br i1 %fun_result, label %cond_jump_end, label %cond_jump_then, !dbg !221

cond_jump_then:                                   ; preds = %entry
  %c2 = load i8, i8* %c, align 1, !dbg !221
  %fun_result3 = call i1 @xisdigit(i8 %c2), !dbg !221
  %oror4 = or i1 %fun_result, %fun_result3, !dbg !221
  store i1 %oror4, i1* %oror, align 1, !dbg !221
  br label %cond_jump_end, !dbg !221

cond_jump_end:                                    ; preds = %cond_jump_then, %entry
  %oror_result_value = load i1, i1* %oror, align 1, !dbg !221
  ret i1 %oror_result_value, !dbg !221
}

define internal i8* @xbasename(i8* %0) !dbg !222 {
entry:
  %result46 = alloca i8*, align 8, !dbg !223
  %len41 = alloca i32, align 4, !dbg !223
  %result = alloca i8*, align 8, !dbg !223
  %len = alloca i32, align 4, !dbg !223
  %p = alloca i8*, align 8, !dbg !223
  %path = alloca i8*, align 8, !dbg !223
  store i8* %0, i8** %path, align 8, !dbg !223
  %path1 = load i8*, i8** %path, align 8, !dbg !224
  %path2 = load i8*, i8** %path, align 8, !dbg !224
  %fun_result = call i64 @strlen(i8* %path2), !dbg !224
  %ptrToIntC = ptrtoint i8* %path1 to i64, !dbg !224
  %mul = mul i64 %fun_result, 1, !dbg !224
  %add = add i64 %ptrToIntC, %mul, !dbg !224
  %intToPtr = inttoptr i64 %add to i8*, !dbg !224
  store i8* %intToPtr, i8** %p, align 8, !dbg !223
  br label %loop_top_block, !dbg !225

loop_top_block:                                   ; preds = %cond_end, %entry
  %p3 = load i8*, i8** %p, align 8, !dbg !226
  %path4 = load i8*, i8** %path, align 8, !dbg !226
  %gteq = icmp sge i8* %p3, %path4, !dbg !226
  br i1 %gteq, label %cond_then_block, label %cond_end_block, !dbg !226

cond_then_block:                                  ; preds = %loop_top_block
  %p5 = load i8*, i8** %p, align 8, !dbg !227
  %derefference_value = load i8, i8* %p5, align 1, !dbg !227
  %eq = icmp eq i8 %derefference_value, 47, !dbg !227
  br i1 %eq, label %cond_jump_then, label %cond_else_block, !dbg !227

cond_end_block:                                   ; preds = %cond_jump_then, %loop_top_block
  %p10 = load i8*, i8** %p, align 8, !dbg !225
  %path11 = load i8*, i8** %path, align 8, !dbg !225
  %le = icmp slt i8* %p10, %path11, !dbg !225
  br i1 %le, label %cond_jump_then12, label %cond_else_block13, !dbg !225

cond_jump_then:                                   ; preds = %cond_then_block
  br label %cond_end_block, !dbg !228

cond_else_block:                                  ; preds = %cond_then_block
  %p6 = load i8*, i8** %p, align 8, !dbg !229
  %ptrToIntI = ptrtoint i8* %p6 to i64, !dbg !229
  %sub = sub i64 %ptrToIntI, 1, !dbg !229
  %iintToPtr = inttoptr i64 %sub to i8*, !dbg !229
  store i8* %iintToPtr, i8** %p, align 8, !dbg !229
  %ptrToIntC7 = ptrtoint i8* %iintToPtr to i64, !dbg !229
  %add8 = add i64 %ptrToIntC7, 1, !dbg !229
  %intToPtr9 = inttoptr i64 %add8 to i8*, !dbg !229
  br label %cond_end, !dbg !229

cond_end:                                         ; preds = %cond_else_block, %after_break
  br label %loop_top_block, !dbg !229

after_break:                                      ; No predecessors!
  br label %cond_end, !dbg !228

cond_jump_then12:                                 ; preds = %cond_end_block
  %path15 = load i8*, i8** %path, align 8, !dbg !230
  br label %string, !dbg !230

cond_else_block13:                                ; preds = %cond_end_block
  %p29 = load i8*, i8** %p, align 8, !dbg !231
  %ptrToIntC30 = ptrtoint i8* %p29 to i64, !dbg !231
  %add31 = add i64 %ptrToIntC30, 1, !dbg !231
  %intToPtr32 = inttoptr i64 %add31 to i8*, !dbg !231
  br label %string33, !dbg !231

cond_end14:                                       ; No predecessors!
  ret i8* null, !dbg !223

string:                                           ; preds = %cond_jump_then12
  %inline_result_variable = alloca i8*, align 8, !dbg !230
  %str = alloca i8*, align 8, !dbg !230
  store i8* %path15, i8** %str, align 8, !dbg !230
  %str16 = load i8*, i8** %str, align 8, !dbg !230
  %fun_result17 = call i64 @strlen(i8* %str16), !dbg !230
  %add18 = add i64 %fun_result17, 1, !dbg !230
  %icastM = trunc i64 %add18 to i32, !dbg !230
  store i32 %icastM, i32* %len, align 4, !dbg !223
  %len19 = load i32, i32* %len, align 4, !dbg !223
  %icastD = sext i32 %len19 to i64, !dbg !223
  %mul20 = mul i64 1, %icastD, !dbg !223
  %fun_result21 = call i8* @GC_malloc(i64 %mul20), !dbg !223
  store i8* %fun_result21, i8** %result, align 8, !dbg !223
  %result22 = load i8*, i8** %result, align 8, !dbg !223
  %str23 = load i8*, i8** %str, align 8, !dbg !223
  %len24 = load i32, i32* %len, align 4, !dbg !223
  %icastD25 = sext i32 %len24 to i64, !dbg !223
  %fun_result26 = call i8* @strncpy(i8* %result22, i8* %str23, i64 %icastD25), !dbg !223
  %result27 = load i8*, i8** %result, align 8, !dbg !223
  store i8* %result27, i8** %inline_result_variable, align 8, !dbg !223
  br label %string_end, !dbg !223

string_end:                                       ; preds = %string
  %inline_result_variable28 = load i8*, i8** %inline_result_variable, align 8, !dbg !223
  ret i8* %inline_result_variable28, !dbg !223

string33:                                         ; preds = %cond_else_block13
  %inline_result_variable34 = alloca i8*, align 8, !dbg !231
  %str35 = alloca i8*, align 8, !dbg !231
  store i8* %intToPtr32, i8** %str35, align 8, !dbg !231
  %str37 = load i8*, i8** %str35, align 8, !dbg !231
  %fun_result38 = call i64 @strlen(i8* %str37), !dbg !231
  %add39 = add i64 %fun_result38, 1, !dbg !231
  %icastM40 = trunc i64 %add39 to i32, !dbg !231
  store i32 %icastM40, i32* %len41, align 4, !dbg !223
  %len42 = load i32, i32* %len41, align 4, !dbg !223
  %icastD43 = sext i32 %len42 to i64, !dbg !223
  %mul44 = mul i64 1, %icastD43, !dbg !223
  %fun_result45 = call i8* @GC_malloc(i64 %mul44), !dbg !223
  store i8* %fun_result45, i8** %result46, align 8, !dbg !223
  %result47 = load i8*, i8** %result46, align 8, !dbg !223
  %str48 = load i8*, i8** %str35, align 8, !dbg !223
  %len49 = load i32, i32* %len41, align 4, !dbg !223
  %icastD50 = sext i32 %len49 to i64, !dbg !223
  %fun_result51 = call i8* @strncpy(i8* %result47, i8* %str48, i64 %icastD50), !dbg !223
  %result52 = load i8*, i8** %result46, align 8, !dbg !223
  store i8* %result52, i8** %inline_result_variable34, align 8, !dbg !223
  br label %string_end36, !dbg !223

string_end36:                                     ; preds = %string33
  %inline_result_variable53 = load i8*, i8** %inline_result_variable34, align 8, !dbg !223
  ret i8* %inline_result_variable53, !dbg !223
}

define internal i8* @xextname(i8* %0) !dbg !232 {
entry:
  %result46 = alloca i8*, align 8, !dbg !233
  %len41 = alloca i32, align 4, !dbg !233
  %result = alloca i8*, align 8, !dbg !233
  %len = alloca i32, align 4, !dbg !233
  %p = alloca i8*, align 8, !dbg !233
  %path = alloca i8*, align 8, !dbg !233
  store i8* %0, i8** %path, align 8, !dbg !233
  %path1 = load i8*, i8** %path, align 8, !dbg !234
  %path2 = load i8*, i8** %path, align 8, !dbg !234
  %fun_result = call i64 @strlen(i8* %path2), !dbg !234
  %ptrToIntC = ptrtoint i8* %path1 to i64, !dbg !234
  %mul = mul i64 %fun_result, 1, !dbg !234
  %add = add i64 %ptrToIntC, %mul, !dbg !234
  %intToPtr = inttoptr i64 %add to i8*, !dbg !234
  store i8* %intToPtr, i8** %p, align 8, !dbg !233
  br label %loop_top_block, !dbg !235

loop_top_block:                                   ; preds = %cond_end, %entry
  %p3 = load i8*, i8** %p, align 8, !dbg !236
  %path4 = load i8*, i8** %path, align 8, !dbg !236
  %gteq = icmp sge i8* %p3, %path4, !dbg !236
  br i1 %gteq, label %cond_then_block, label %cond_end_block, !dbg !236

cond_then_block:                                  ; preds = %loop_top_block
  %p5 = load i8*, i8** %p, align 8, !dbg !237
  %derefference_value = load i8, i8* %p5, align 1, !dbg !237
  %eq = icmp eq i8 %derefference_value, 46, !dbg !237
  br i1 %eq, label %cond_jump_then, label %cond_else_block, !dbg !237

cond_end_block:                                   ; preds = %cond_jump_then, %loop_top_block
  %p10 = load i8*, i8** %p, align 8, !dbg !235
  %path11 = load i8*, i8** %path, align 8, !dbg !235
  %le = icmp slt i8* %p10, %path11, !dbg !235
  br i1 %le, label %cond_jump_then12, label %cond_else_block13, !dbg !235

cond_jump_then:                                   ; preds = %cond_then_block
  br label %cond_end_block, !dbg !238

cond_else_block:                                  ; preds = %cond_then_block
  %p6 = load i8*, i8** %p, align 8, !dbg !239
  %ptrToIntI = ptrtoint i8* %p6 to i64, !dbg !239
  %sub = sub i64 %ptrToIntI, 1, !dbg !239
  %iintToPtr = inttoptr i64 %sub to i8*, !dbg !239
  store i8* %iintToPtr, i8** %p, align 8, !dbg !239
  %ptrToIntC7 = ptrtoint i8* %iintToPtr to i64, !dbg !239
  %add8 = add i64 %ptrToIntC7, 1, !dbg !239
  %intToPtr9 = inttoptr i64 %add8 to i8*, !dbg !239
  br label %cond_end, !dbg !239

cond_end:                                         ; preds = %cond_else_block, %after_break
  br label %loop_top_block, !dbg !239

after_break:                                      ; No predecessors!
  br label %cond_end, !dbg !238

cond_jump_then12:                                 ; preds = %cond_end_block
  %path15 = load i8*, i8** %path, align 8, !dbg !240
  br label %string, !dbg !240

cond_else_block13:                                ; preds = %cond_end_block
  %p29 = load i8*, i8** %p, align 8, !dbg !241
  %ptrToIntC30 = ptrtoint i8* %p29 to i64, !dbg !241
  %add31 = add i64 %ptrToIntC30, 1, !dbg !241
  %intToPtr32 = inttoptr i64 %add31 to i8*, !dbg !241
  br label %string33, !dbg !241

cond_end14:                                       ; No predecessors!
  ret i8* null, !dbg !233

string:                                           ; preds = %cond_jump_then12
  %inline_result_variable = alloca i8*, align 8, !dbg !240
  %str = alloca i8*, align 8, !dbg !240
  store i8* %path15, i8** %str, align 8, !dbg !240
  %str16 = load i8*, i8** %str, align 8, !dbg !240
  %fun_result17 = call i64 @strlen(i8* %str16), !dbg !240
  %add18 = add i64 %fun_result17, 1, !dbg !240
  %icastM = trunc i64 %add18 to i32, !dbg !240
  store i32 %icastM, i32* %len, align 4, !dbg !233
  %len19 = load i32, i32* %len, align 4, !dbg !233
  %icastD = sext i32 %len19 to i64, !dbg !233
  %mul20 = mul i64 1, %icastD, !dbg !233
  %fun_result21 = call i8* @GC_malloc(i64 %mul20), !dbg !233
  store i8* %fun_result21, i8** %result, align 8, !dbg !233
  %result22 = load i8*, i8** %result, align 8, !dbg !233
  %str23 = load i8*, i8** %str, align 8, !dbg !233
  %len24 = load i32, i32* %len, align 4, !dbg !233
  %icastD25 = sext i32 %len24 to i64, !dbg !233
  %fun_result26 = call i8* @strncpy(i8* %result22, i8* %str23, i64 %icastD25), !dbg !233
  %result27 = load i8*, i8** %result, align 8, !dbg !233
  store i8* %result27, i8** %inline_result_variable, align 8, !dbg !233
  br label %string_end, !dbg !233

string_end:                                       ; preds = %string
  %inline_result_variable28 = load i8*, i8** %inline_result_variable, align 8, !dbg !233
  ret i8* %inline_result_variable28, !dbg !233

string33:                                         ; preds = %cond_else_block13
  %inline_result_variable34 = alloca i8*, align 8, !dbg !241
  %str35 = alloca i8*, align 8, !dbg !241
  store i8* %intToPtr32, i8** %str35, align 8, !dbg !241
  %str37 = load i8*, i8** %str35, align 8, !dbg !241
  %fun_result38 = call i64 @strlen(i8* %str37), !dbg !241
  %add39 = add i64 %fun_result38, 1, !dbg !241
  %icastM40 = trunc i64 %add39 to i32, !dbg !241
  store i32 %icastM40, i32* %len41, align 4, !dbg !233
  %len42 = load i32, i32* %len41, align 4, !dbg !233
  %icastD43 = sext i32 %len42 to i64, !dbg !233
  %mul44 = mul i64 1, %icastD43, !dbg !233
  %fun_result45 = call i8* @GC_malloc(i64 %mul44), !dbg !233
  store i8* %fun_result45, i8** %result46, align 8, !dbg !233
  %result47 = load i8*, i8** %result46, align 8, !dbg !233
  %str48 = load i8*, i8** %str35, align 8, !dbg !233
  %len49 = load i32, i32* %len41, align 4, !dbg !233
  %icastD50 = sext i32 %len49 to i64, !dbg !233
  %fun_result51 = call i8* @strncpy(i8* %result47, i8* %str48, i64 %icastD50), !dbg !233
  %result52 = load i8*, i8** %result46, align 8, !dbg !233
  store i8* %result52, i8** %inline_result_variable34, align 8, !dbg !233
  br label %string_end36, !dbg !233

string_end36:                                     ; preds = %string33
  %inline_result_variable53 = load i8*, i8** %inline_result_variable34, align 8, !dbg !233
  ret i8* %inline_result_variable53, !dbg !233
}

define internal i8* @xrealpath(i8* %0) !dbg !242 {
entry:
  %result215 = alloca i8*, align 8, !dbg !243
  %result7 = alloca i8*, align 8, !dbg !243
  %len = alloca i32, align 4, !dbg !243
  %result = alloca i8*, align 8, !dbg !243
  %path = alloca i8*, align 8, !dbg !243
  store i8* %0, i8** %path, align 8, !dbg !243
  %path1 = load i8*, i8** %path, align 8, !dbg !244
  %fun_result = call i8* @realpath(i8* %path1, i8* null), !dbg !244
  store i8* %fun_result, i8** %result, align 8, !dbg !243
  %result2 = load i8*, i8** %result, align 8, !dbg !245
  br label %string, !dbg !245

string:                                           ; preds = %entry
  %inline_result_variable = alloca i8*, align 8, !dbg !245
  %str = alloca i8*, align 8, !dbg !245
  store i8* %result2, i8** %str, align 8, !dbg !245
  %str3 = load i8*, i8** %str, align 8, !dbg !245
  %fun_result4 = call i64 @strlen(i8* %str3), !dbg !245
  %add = add i64 %fun_result4, 1, !dbg !245
  %icastM = trunc i64 %add to i32, !dbg !245
  store i32 %icastM, i32* %len, align 4, !dbg !243
  %len5 = load i32, i32* %len, align 4, !dbg !243
  %icastD = sext i32 %len5 to i64, !dbg !243
  %mul = mul i64 1, %icastD, !dbg !243
  %fun_result6 = call i8* @GC_malloc(i64 %mul), !dbg !243
  store i8* %fun_result6, i8** %result7, align 8, !dbg !243
  %result8 = load i8*, i8** %result7, align 8, !dbg !243
  %str9 = load i8*, i8** %str, align 8, !dbg !243
  %len10 = load i32, i32* %len, align 4, !dbg !243
  %icastD11 = sext i32 %len10 to i64, !dbg !243
  %fun_result12 = call i8* @strncpy(i8* %result8, i8* %str9, i64 %icastD11), !dbg !243
  %result13 = load i8*, i8** %result7, align 8, !dbg !243
  store i8* %result13, i8** %inline_result_variable, align 8, !dbg !243
  br label %string_end, !dbg !243

string_end:                                       ; preds = %string
  %inline_result_variable14 = load i8*, i8** %inline_result_variable, align 8, !dbg !243
  store i8* %inline_result_variable14, i8** %result215, align 8, !dbg !243
  %result16 = load i8*, i8** %result, align 8, !dbg !246
  call void @free(i8* %result16), !dbg !246
  %result217 = load i8*, i8** %result215, align 8, !dbg !247
  ret i8* %result217, !dbg !247
}

define internal void @come_fd_zero(%come_anon8* %0) !dbg !248 {
entry:
  %__arr = alloca %come_anon8*, align 8, !dbg !249
  %__i = alloca i32, align 4, !dbg !249
  %fds = alloca %come_anon8*, align 8, !dbg !249
  store %come_anon8* %0, %come_anon8** %fds, align 8, !dbg !249
  br label %loop_top_block, !dbg !250

loop_top_block:                                   ; preds = %cond_end_block4, %entry
  %fds1 = load %come_anon8*, %come_anon8** %fds, align 8, !dbg !250
  store %come_anon8* %fds1, %come_anon8** %__arr, align 8, !dbg !249
  store i32 0, i32* %__i, align 4, !dbg !250
  br label %loop_top_block2, !dbg !250

cond_end_block:                                   ; preds = %cond_end_block4
  ret void, !dbg !250

loop_top_block2:                                  ; preds = %cond_then_block, %loop_top_block
  %__i3 = load i32, i32* %__i, align 4, !dbg !250
  %le = icmp ult i32 %__i3, 16, !dbg !250
  br i1 %le, label %cond_then_block, label %cond_end_block4, !dbg !250

cond_then_block:                                  ; preds = %loop_top_block2
  %__arr5 = load %come_anon8*, %come_anon8** %__arr, align 8, !dbg !250
  %field = getelementptr inbounds %come_anon8, %come_anon8* %__arr5, i32 0, i32 0, !dbg !250
  %__i6 = load i32, i32* %__i, align 4, !dbg !250
  %array_cast = bitcast [16 x i64]* %field to i64*, !dbg !250
  %gep = getelementptr i64, i64* %array_cast, i32 %__i6, !dbg !250
  store i64 0, i64* %gep, align 4, !dbg !250
  %__i7 = load i32, i32* %__i, align 4, !dbg !250
  %add = add i32 %__i7, 1, !dbg !250
  store i32 %add, i32* %__i, align 4, !dbg !250
  br label %loop_top_block2, !dbg !250

cond_end_block4:                                  ; preds = %loop_top_block2
  br i1 false, label %loop_top_block, label %cond_end_block, !dbg !250
}

define internal void @come_fd_set(i32 %0, %come_anon8* %1) !dbg !251 {
entry:
  %fd = alloca i32, align 4, !dbg !254
  store i32 %0, i32* %fd, align 4, !dbg !254
  %fds = alloca %come_anon8*, align 8, !dbg !254
  store %come_anon8* %1, %come_anon8** %fds, align 8, !dbg !254
  %fds1 = load %come_anon8*, %come_anon8** %fds, align 8, !dbg !255
  %field = getelementptr inbounds %come_anon8, %come_anon8* %fds1, i32 0, i32 0, !dbg !255
  %fd2 = load i32, i32* %fd, align 4, !dbg !255
  %div = sdiv i32 %fd2, 64, !dbg !255
  %array_cast = bitcast [16 x i64]* %field to i64*, !dbg !255
  %gep = getelementptr i64, i64* %array_cast, i32 %div, !dbg !255
  %element = load i64, i64* %gep, align 4, !dbg !255
  %fd3 = load i32, i32* %fd, align 4, !dbg !255
  %div4 = srem i32 %fd3, 64, !dbg !255
  %icastD = sext i32 %div4 to i64, !dbg !255
  %lshifttmp = shl i64 1, %icastD, !dbg !255
  %load = load i64, i64* %gep, align 4, !dbg !255
  %ortmp = or i64 %load, %lshifttmp, !dbg !255
  store i64 %ortmp, i64* %gep, align 4, !dbg !255
  ret void, !dbg !255
}

define internal i32 @come_fd_isset(i32 %0, %come_anon8* %1) !dbg !256 {
entry:
  %fd = alloca i32, align 4, !dbg !258
  store i32 %0, i32* %fd, align 4, !dbg !258
  %fds = alloca %come_anon8*, align 8, !dbg !258
  store %come_anon8* %1, %come_anon8** %fds, align 8, !dbg !258
  %fds1 = load %come_anon8*, %come_anon8** %fds, align 8, !dbg !259
  %field = getelementptr inbounds %come_anon8, %come_anon8* %fds1, i32 0, i32 0, !dbg !259
  %fd2 = load i32, i32* %fd, align 4, !dbg !259
  %div = sdiv i32 %fd2, 64, !dbg !259
  %array_cast = bitcast [16 x i64]* %field to i64*, !dbg !259
  %gep = getelementptr i64, i64* %array_cast, i32 %div, !dbg !259
  %element = load i64, i64* %gep, align 4, !dbg !259
  %fd3 = load i32, i32* %fd, align 4, !dbg !259
  %div4 = srem i32 %fd3, 64, !dbg !259
  %icastD = sext i32 %div4 to i64, !dbg !259
  %lshifttmp = shl i64 1, %icastD, !dbg !259
  %andtmp = and i64 %element, %lshifttmp, !dbg !259
  %not_eq = icmp ne i64 %andtmp, 0, !dbg !259
  %icastL = sext i1 %not_eq to i32, !dbg !259
  ret i32 %icastL, !dbg !259
}

declare void @skip_spaces(%sParserInfo*)

declare void @skip_spaces_until_eol(%sParserInfo*)

declare %list_sNodep* @parse_block(%sParserInfo*)

declare %buffer* @compile_nodes(%list_sNodep*, %sParserInfo*)

declare %buffer* @compile_block(%sParserInfo*)

declare void @initialize_modules_v1()

declare void @finalize_modules_v1()

declare i1 @vm(%buffer*, %map_charp_ZVALUE*)

declare i1 @expression_v1(%sNode**, %sParserInfo*)

declare i1 @compile_v1(%sNode*, %buffer*, %sParserInfo*)

declare %sNode* @exp_node_v1(%sParserInfo*)

declare %sNode* @op_add_node(%sParserInfo*)

declare i1 @expression_v2(%sNode**, %sParserInfo*)

declare i1 @compile_v2(%sNode*, %buffer*, %sParserInfo*)

declare i1 @compile_v3(%sNode*, %buffer*, %sParserInfo*)

declare %sNode* @exp_node_v3(%sParserInfo*)

declare i1 @wordcmp(i8*, i8*)

declare i1 @compile_v4(%sNode*, %buffer*, %sParserInfo*)

declare %sNode* @exp_node_v4(%sParserInfo*)

declare %sNode* @exp_node_v5(%sParserInfo*)

declare %sNode* @fun_node_v5(i8*, %sParserInfo*)

declare %sNode* @def_node_v5(%sParserInfo*)

declare i1 @compile_v5(%sNode*, %buffer*, %sParserInfo*)

declare void @initialize_modules_v6()

declare %sNode* @fun_node_v6(i8*, %sParserInfo*)

declare %sNode* @def_node_v6(%sParserInfo*)

declare i1 @function_call(i8*, %ZVALUE*, i32)

declare i1 @compile_v6(%sNode*, %buffer*, %sParserInfo*)

declare %sNode* @exp_node_v7(%sParserInfo*)

declare i1 @compile_v7(%sNode*, %buffer*, %sParserInfo*)

declare %sNode* @exp_node_v8(%sParserInfo*)

declare i1 @compile_v8(%sNode*, %buffer*, %sParserInfo*)

declare i1 @expression_v9(%sNode**, %sParserInfo*)

define %sNode* @exp_node_v10(%sParserInfo* %0) !dbg !260 {
entry:
  %else_nodes = alloca %list_sNodep*, align 8, !dbg !261
  %while_nodes = alloca %list_sNodep*, align 8, !dbg !261
  %while_exp = alloca %sNode*, align 8, !dbg !261
  %node = alloca %sNode*, align 8, !dbg !261
  %result = alloca %sNode*, align 8, !dbg !261
  %info = alloca %sParserInfo*, align 8, !dbg !261
  store %sParserInfo* %0, %sParserInfo** %info, align 8, !dbg !261
  store %sNode* null, %sNode** %result, align 8, !dbg !261
  %info1 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !262
  %field = getelementptr inbounds %sParserInfo, %sParserInfo* %info1, i32 0, i32 0, !dbg !262
  %p = load i8*, i8** %field, align 8, !dbg !262
  %fun_result = call i1 @word_cmp(i8* %p, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @while, i32 0, i32 0)), !dbg !262
  br i1 %fun_result, label %cond_jump_then, label %cond_jump_elif0, !dbg !262

cond_jump_then:                                   ; preds = %entry
  %info2 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !263
  %info3 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !263
  %field4 = getelementptr inbounds %sParserInfo, %sParserInfo* %info3, i32 0, i32 0, !dbg !263
  %p5 = load i8*, i8** %field4, align 8, !dbg !263
  %fun_result6 = call i64 @strlen(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @while.1, i32 0, i32 0)), !dbg !263
  %ptrToIntC = ptrtoint i8* %p5 to i64, !dbg !263
  %mul = mul i64 %fun_result6, 1, !dbg !263
  %add = add i64 %ptrToIntC, %mul, !dbg !263
  %intToPtr = inttoptr i64 %add to i8*, !dbg !263
  %field7 = getelementptr inbounds %sParserInfo, %sParserInfo* %info2, i32 0, i32 0, !dbg !263
  store i8* %intToPtr, i8** %field7, align 8, !dbg !263
  %info8 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !264
  call void @skip_spaces_until_eol(%sParserInfo* %info8), !dbg !264
  store %sNode* null, %sNode** %node, align 8, !dbg !261
  %node9 = load %sNode*, %sNode** %node, align 8, !dbg !265
  %info10 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !265
  %fun_result11 = call i1 @expression_v11(%sNode** %node, %sParserInfo* %info10), !dbg !265
  %logical_denial = icmp eq i1 %fun_result11, false, !dbg !265
  br i1 %logical_denial, label %cond_jump_then12, label %cond_end13, !dbg !265

cond_jump_elif0:                                  ; preds = %entry
  %info96 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !266
  %field97 = getelementptr inbounds %sParserInfo, %sParserInfo* %info96, i32 0, i32 0, !dbg !266
  %p98 = load i8*, i8** %field97, align 8, !dbg !266
  %fun_result99 = call i1 @word_cmp(i8* %p98, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @break, i32 0, i32 0)), !dbg !266
  br i1 %fun_result99, label %cond_jump_elif_then0, label %cond_jump_elif1, !dbg !266

cond_jump_elif_then0:                             ; preds = %cond_jump_elif0
  %info100 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !267
  %info101 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !267
  %field102 = getelementptr inbounds %sParserInfo, %sParserInfo* %info101, i32 0, i32 0, !dbg !267
  %p103 = load i8*, i8** %field102, align 8, !dbg !267
  %fun_result104 = call i64 @strlen(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @break.4, i32 0, i32 0)), !dbg !267
  %ptrToIntC105 = ptrtoint i8* %p103 to i64, !dbg !267
  %mul106 = mul i64 %fun_result104, 1, !dbg !267
  %add107 = add i64 %ptrToIntC105, %mul106, !dbg !267
  %intToPtr108 = inttoptr i64 %add107 to i8*, !dbg !267
  %field109 = getelementptr inbounds %sParserInfo, %sParserInfo* %info100, i32 0, i32 0, !dbg !267
  store i8* %intToPtr108, i8** %field109, align 8, !dbg !267
  %info110 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !268
  call void @skip_spaces_until_eol(%sParserInfo* %info110), !dbg !268
  %info111 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !269
  %fun_result112 = call %sNode* @create_break(%sParserInfo* %info111), !dbg !269
  store %sNode* %fun_result112, %sNode** %result, align 8, !dbg !269
  br label %cond_end, !dbg !269

cond_jump_elif1:                                  ; preds = %cond_jump_elif0
  %info113 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !270
  %field114 = getelementptr inbounds %sParserInfo, %sParserInfo* %info113, i32 0, i32 0, !dbg !270
  %p115 = load i8*, i8** %field114, align 8, !dbg !270
  %fun_result116 = call i1 @word_cmp(i8* %p115, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @continue, i32 0, i32 0)), !dbg !270
  br i1 %fun_result116, label %cond_jump_elif_then1, label %cond_end, !dbg !270

cond_jump_elif_then1:                             ; preds = %cond_jump_elif1
  %info117 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !271
  %info118 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !271
  %field119 = getelementptr inbounds %sParserInfo, %sParserInfo* %info118, i32 0, i32 0, !dbg !271
  %p120 = load i8*, i8** %field119, align 8, !dbg !271
  %fun_result121 = call i64 @strlen(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @continue.5, i32 0, i32 0)), !dbg !271
  %ptrToIntC122 = ptrtoint i8* %p120 to i64, !dbg !271
  %mul123 = mul i64 %fun_result121, 1, !dbg !271
  %add124 = add i64 %ptrToIntC122, %mul123, !dbg !271
  %intToPtr125 = inttoptr i64 %add124 to i8*, !dbg !271
  %field126 = getelementptr inbounds %sParserInfo, %sParserInfo* %info117, i32 0, i32 0, !dbg !271
  store i8* %intToPtr125, i8** %field126, align 8, !dbg !271
  %info127 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !272
  call void @skip_spaces_until_eol(%sParserInfo* %info127), !dbg !272
  %info128 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !273
  %fun_result129 = call %sNode* @create_continue(%sParserInfo* %info128), !dbg !273
  store %sNode* %fun_result129, %sNode** %result, align 8, !dbg !273
  br label %cond_end, !dbg !273

cond_end:                                         ; preds = %cond_jump_elif_then1, %cond_jump_elif1, %cond_jump_elif_then0, %cond_end49
  %result130 = load %sNode*, %sNode** %result, align 8, !dbg !274
  %eq131 = icmp eq %sNode* %result130, null, !dbg !274
  br i1 %eq131, label %cond_jump_then132, label %cond_end133, !dbg !274

cond_jump_then12:                                 ; preds = %cond_jump_then
  %stderr = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !275
  %info14 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !275
  %field15 = getelementptr inbounds %sParserInfo, %sParserInfo* %info14, i32 0, i32 2, !dbg !275
  %fname = load i8*, i8** %field15, align 8, !dbg !275
  %info16 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !275
  %field17 = getelementptr inbounds %sParserInfo, %sParserInfo* %info16, i32 0, i32 1, !dbg !275
  %sline = load i32, i32* %field17, align 4, !dbg !275
  %fun_result18 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @"%s %d: invalid while exp\0A", i32 0, i32 0), i8* %fname, i32 %sline), !dbg !275
  ret %sNode* null, !dbg !276

cond_end13:                                       ; preds = %cond_jump_then
  %node19 = load %sNode*, %sNode** %node, align 8, !dbg !277
  store %sNode* %node19, %sNode** %while_exp, align 8, !dbg !261
  %info20 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !278
  %field21 = getelementptr inbounds %sParserInfo, %sParserInfo* %info20, i32 0, i32 0, !dbg !278
  %p22 = load i8*, i8** %field21, align 8, !dbg !278
  %derefference_value = load i8, i8* %p22, align 1, !dbg !278
  %eq = icmp eq i8 %derefference_value, 58, !dbg !278
  br i1 %eq, label %cond_jump_then23, label %cond_else_block, !dbg !278

cond_jump_then23:                                 ; preds = %cond_end13
  %info25 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !279
  %info26 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !279
  %field27 = getelementptr inbounds %sParserInfo, %sParserInfo* %info26, i32 0, i32 0, !dbg !279
  %p28 = load i8*, i8** %field27, align 8, !dbg !279
  %ptrToIntC29 = ptrtoint i8* %p28 to i64, !dbg !279
  %add30 = add i64 %ptrToIntC29, 1, !dbg !279
  %intToPtr31 = inttoptr i64 %add30 to i8*, !dbg !279
  %field32 = getelementptr inbounds %sParserInfo, %sParserInfo* %info25, i32 0, i32 0, !dbg !279
  store i8* %intToPtr31, i8** %field32, align 8, !dbg !279
  %ptrToIntI = ptrtoint i8* %intToPtr31 to i64, !dbg !279
  %sub = sub i64 %ptrToIntI, 1, !dbg !279
  %iintToPtr = inttoptr i64 %sub to i8*, !dbg !279
  %info33 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !280
  call void @skip_spaces_until_eol(%sParserInfo* %info33), !dbg !280
  br label %cond_end24, !dbg !280

cond_else_block:                                  ; preds = %cond_end13
  %stderr34 = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !281
  %info35 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !281
  %field36 = getelementptr inbounds %sParserInfo, %sParserInfo* %info35, i32 0, i32 2, !dbg !281
  %fname37 = load i8*, i8** %field36, align 8, !dbg !281
  %info38 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !281
  %field39 = getelementptr inbounds %sParserInfo, %sParserInfo* %info38, i32 0, i32 1, !dbg !281
  %sline40 = load i32, i32* %field39, align 4, !dbg !281
  %fun_result41 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr34, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @"%s %d: require : for block\0A", i32 0, i32 0), i8* %fname37, i32 %sline40), !dbg !281
  ret %sNode* null, !dbg !282

cond_end24:                                       ; preds = %cond_jump_then23
  %info42 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !283
  %fun_result43 = call %list_sNodep* @parse_block(%sParserInfo* %info42), !dbg !283
  store %list_sNodep* %fun_result43, %list_sNodep** %while_nodes, align 8, !dbg !261
  store %list_sNodep* null, %list_sNodep** %else_nodes, align 8, !dbg !261
  %info44 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !284
  %field45 = getelementptr inbounds %sParserInfo, %sParserInfo* %info44, i32 0, i32 0, !dbg !284
  %p46 = load i8*, i8** %field45, align 8, !dbg !284
  %fun_result47 = call i1 @word_cmp(i8* %p46, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @else, i32 0, i32 0)), !dbg !284
  br i1 %fun_result47, label %cond_jump_then48, label %cond_end49, !dbg !284

cond_jump_then48:                                 ; preds = %cond_end24
  %info50 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !285
  %info51 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !285
  %field52 = getelementptr inbounds %sParserInfo, %sParserInfo* %info51, i32 0, i32 0, !dbg !285
  %p53 = load i8*, i8** %field52, align 8, !dbg !285
  %fun_result54 = call i64 @strlen(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @else.2, i32 0, i32 0)), !dbg !285
  %ptrToIntC55 = ptrtoint i8* %p53 to i64, !dbg !285
  %mul56 = mul i64 %fun_result54, 1, !dbg !285
  %add57 = add i64 %ptrToIntC55, %mul56, !dbg !285
  %intToPtr58 = inttoptr i64 %add57 to i8*, !dbg !285
  %field59 = getelementptr inbounds %sParserInfo, %sParserInfo* %info50, i32 0, i32 0, !dbg !285
  store i8* %intToPtr58, i8** %field59, align 8, !dbg !285
  %info60 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !286
  call void @skip_spaces_until_eol(%sParserInfo* %info60), !dbg !286
  %info61 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !287
  %field62 = getelementptr inbounds %sParserInfo, %sParserInfo* %info61, i32 0, i32 0, !dbg !287
  %p63 = load i8*, i8** %field62, align 8, !dbg !287
  %derefference_value64 = load i8, i8* %p63, align 1, !dbg !287
  %eq65 = icmp eq i8 %derefference_value64, 58, !dbg !287
  br i1 %eq65, label %cond_jump_then66, label %cond_else_block67, !dbg !287

cond_end49:                                       ; preds = %cond_end68, %cond_end24
  %while_exp91 = load %sNode*, %sNode** %while_exp, align 8, !dbg !288
  %while_nodes92 = load %list_sNodep*, %list_sNodep** %while_nodes, align 8, !dbg !288
  %else_nodes93 = load %list_sNodep*, %list_sNodep** %else_nodes, align 8, !dbg !288
  %info94 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !288
  %fun_result95 = call %sNode* @create_while(%sNode* %while_exp91, %list_sNodep* %while_nodes92, %list_sNodep* %else_nodes93, %sParserInfo* %info94), !dbg !288
  store %sNode* %fun_result95, %sNode** %result, align 8, !dbg !288
  br label %cond_end, !dbg !288

cond_jump_then66:                                 ; preds = %cond_jump_then48
  %info69 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !289
  %info70 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !289
  %field71 = getelementptr inbounds %sParserInfo, %sParserInfo* %info70, i32 0, i32 0, !dbg !289
  %p72 = load i8*, i8** %field71, align 8, !dbg !289
  %ptrToIntC73 = ptrtoint i8* %p72 to i64, !dbg !289
  %add74 = add i64 %ptrToIntC73, 1, !dbg !289
  %intToPtr75 = inttoptr i64 %add74 to i8*, !dbg !289
  %field76 = getelementptr inbounds %sParserInfo, %sParserInfo* %info69, i32 0, i32 0, !dbg !289
  store i8* %intToPtr75, i8** %field76, align 8, !dbg !289
  %ptrToIntI77 = ptrtoint i8* %intToPtr75 to i64, !dbg !289
  %sub78 = sub i64 %ptrToIntI77, 1, !dbg !289
  %iintToPtr79 = inttoptr i64 %sub78 to i8*, !dbg !289
  %info80 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !290
  call void @skip_spaces_until_eol(%sParserInfo* %info80), !dbg !290
  br label %cond_end68, !dbg !290

cond_else_block67:                                ; preds = %cond_jump_then48
  %stderr81 = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !291
  %info82 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !291
  %field83 = getelementptr inbounds %sParserInfo, %sParserInfo* %info82, i32 0, i32 2, !dbg !291
  %fname84 = load i8*, i8** %field83, align 8, !dbg !291
  %info85 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !291
  %field86 = getelementptr inbounds %sParserInfo, %sParserInfo* %info85, i32 0, i32 1, !dbg !291
  %sline87 = load i32, i32* %field86, align 4, !dbg !291
  %fun_result88 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr81, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @"%s %d: require : for block\0A.3", i32 0, i32 0), i8* %fname84, i32 %sline87), !dbg !291
  ret %sNode* null, !dbg !292

cond_end68:                                       ; preds = %cond_jump_then66
  %info89 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !293
  %fun_result90 = call %list_sNodep* @parse_block(%sParserInfo* %info89), !dbg !293
  store %list_sNodep* %fun_result90, %list_sNodep** %else_nodes, align 8, !dbg !293
  br label %cond_end49, !dbg !293

cond_jump_then132:                                ; preds = %cond_end
  %info134 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !294
  %fun_result135 = call %sNode* @exp_node_v8(%sParserInfo* %info134), !dbg !294
  store %sNode* %fun_result135, %sNode** %result, align 8, !dbg !294
  br label %cond_end133, !dbg !294

cond_end133:                                      ; preds = %cond_jump_then132, %cond_end
  %result136 = load %sNode*, %sNode** %result, align 8, !dbg !295
  ret %sNode* %result136, !dbg !295
}

define i1 @compile_v10(%sNode* %0, %buffer* %1, %sParserInfo* %2) !dbg !296 {
entry:
  %break_point142 = alloca i32, align 4, !dbg !299
  %p = alloca i32*, align 8, !dbg !299
  %break_point = alloca i32, align 4, !dbg !299
  %i = alloca i32, align 4, !dbg !299
  %else_codes = alloca %buffer*, align 8, !dbg !299
  %while_codes_top = alloca i32, align 4, !dbg !299
  %offset = alloca i32, align 4, !dbg !299
  %while_codes = alloca %buffer*, align 8, !dbg !299
  %breaks_before = alloca %vector_int*, align 8, !dbg !299
  %head_before = alloca i32, align 4, !dbg !299
  %head = alloca i32, align 4, !dbg !299
  %else_nodes25 = alloca %list_sNodep*, align 8, !dbg !299
  %while_nodes17 = alloca %list_sNodep*, align 8, !dbg !299
  %while_exp9 = alloca %sNode*, align 8, !dbg !299
  %node = alloca %sNode*, align 8, !dbg !299
  store %sNode* %0, %sNode** %node, align 8, !dbg !299
  %codes = alloca %buffer*, align 8, !dbg !299
  store %buffer* %1, %buffer** %codes, align 8, !dbg !299
  %info = alloca %sParserInfo*, align 8, !dbg !299
  store %sParserInfo* %2, %sParserInfo** %info, align 8, !dbg !299
  %node1 = load %sNode*, %sNode** %node, align 8, !dbg !300
  %codes2 = load %buffer*, %buffer** %codes, align 8, !dbg !300
  %info3 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !300
  %fun_result = call i1 @compile_v8(%sNode* %node1, %buffer* %codes2, %sParserInfo* %info3), !dbg !300
  %node4 = load %sNode*, %sNode** %node, align 8, !dbg !301
  %field = getelementptr inbounds %sNode, %sNode* %node4, i32 0, i32 0, !dbg !301
  %kind = load i32, i32* %field, align 4, !dbg !301
  %eq = icmp eq i32 %kind, 12, !dbg !301
  br i1 %eq, label %cond_jump_then, label %cond_jump_elif0, !dbg !301

cond_jump_then:                                   ; preds = %entry
  %node5 = load %sNode*, %sNode** %node, align 8, !dbg !302
  %field6 = getelementptr inbounds %sNode, %sNode* %node5, i32 0, i32 3, !dbg !302
  %value = load %come_anon75, %come_anon75* %field6, align 8, !dbg !302
  %field7 = getelementptr inbounds %come_anon75, %come_anon75* %field6, i32 0, i32 0, !dbg !302
  %icastO = bitcast %come_anon81* %field7 to %come_anon82*, !dbg !302
  %whileValue = load %come_anon82, %come_anon82* %icastO, align 8, !dbg !302
  %field8 = getelementptr inbounds %come_anon82, %come_anon82* %icastO, i32 0, i32 0, !dbg !302
  %while_exp = load %sNode*, %sNode** %field8, align 8, !dbg !302
  store %sNode* %while_exp, %sNode** %while_exp9, align 8, !dbg !299
  %node10 = load %sNode*, %sNode** %node, align 8, !dbg !303
  %field11 = getelementptr inbounds %sNode, %sNode* %node10, i32 0, i32 3, !dbg !303
  %value12 = load %come_anon75, %come_anon75* %field11, align 8, !dbg !303
  %field13 = getelementptr inbounds %come_anon75, %come_anon75* %field11, i32 0, i32 0, !dbg !303
  %icastO14 = bitcast %come_anon81* %field13 to %come_anon82*, !dbg !303
  %whileValue15 = load %come_anon82, %come_anon82* %icastO14, align 8, !dbg !303
  %field16 = getelementptr inbounds %come_anon82, %come_anon82* %icastO14, i32 0, i32 1, !dbg !303
  %while_nodes = load %list_sNodep*, %list_sNodep** %field16, align 8, !dbg !303
  store %list_sNodep* %while_nodes, %list_sNodep** %while_nodes17, align 8, !dbg !299
  %node18 = load %sNode*, %sNode** %node, align 8, !dbg !304
  %field19 = getelementptr inbounds %sNode, %sNode* %node18, i32 0, i32 3, !dbg !304
  %value20 = load %come_anon75, %come_anon75* %field19, align 8, !dbg !304
  %field21 = getelementptr inbounds %come_anon75, %come_anon75* %field19, i32 0, i32 0, !dbg !304
  %icastO22 = bitcast %come_anon81* %field21 to %come_anon82*, !dbg !304
  %whileValue23 = load %come_anon82, %come_anon82* %icastO22, align 8, !dbg !304
  %field24 = getelementptr inbounds %come_anon82, %come_anon82* %icastO22, i32 0, i32 2, !dbg !304
  %else_nodes = load %list_sNodep*, %list_sNodep** %field24, align 8, !dbg !304
  store %list_sNodep* %else_nodes, %list_sNodep** %else_nodes25, align 8, !dbg !299
  %codes26 = load %buffer*, %buffer** %codes, align 8, !dbg !305
  %fun_result27 = call i32 @buffer_length(%buffer* %codes26), !dbg !305
  store i32 %fun_result27, i32* %head, align 4, !dbg !299
  %info28 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !306
  %field29 = getelementptr inbounds %sParserInfo, %sParserInfo* %info28, i32 0, i32 6, !dbg !306
  %loop_head = load i32, i32* %field29, align 4, !dbg !306
  store i32 %loop_head, i32* %head_before, align 4, !dbg !299
  %info30 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !307
  %head31 = load i32, i32* %head, align 4, !dbg !307
  %field32 = getelementptr inbounds %sParserInfo, %sParserInfo* %info30, i32 0, i32 6, !dbg !307
  store i32 %head31, i32* %field32, align 4, !dbg !307
  %info33 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !308
  %field34 = getelementptr inbounds %sParserInfo, %sParserInfo* %info33, i32 0, i32 7, !dbg !308
  %breaks = load %vector_int*, %vector_int** %field34, align 8, !dbg !308
  store %vector_int* %breaks, %vector_int** %breaks_before, align 8, !dbg !299
  %info35 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !309
  %fun_result36 = call i8* @GC_malloc(i64 24), !dbg !309
  %obj = bitcast i8* %fun_result36 to %vector_int*, !dbg !309
  %fun_result37 = call %vector_int* @vector_initialize_int(%vector_int* %obj), !dbg !309
  %field38 = getelementptr inbounds %sParserInfo, %sParserInfo* %info35, i32 0, i32 7, !dbg !309
  store %vector_int* %fun_result37, %vector_int** %field38, align 8, !dbg !309
  %while_nodes39 = load %list_sNodep*, %list_sNodep** %while_nodes17, align 8, !dbg !310
  %info40 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !310
  %fun_result41 = call %buffer* @compile_nodes(%list_sNodep* %while_nodes39, %sParserInfo* %info40), !dbg !310
  store %buffer* %fun_result41, %buffer** %while_codes, align 8, !dbg !299
  %while_exp42 = load %sNode*, %sNode** %while_exp9, align 8, !dbg !311
  %codes43 = load %buffer*, %buffer** %codes, align 8, !dbg !311
  %info44 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !311
  %fun_result45 = call i1 @compile_v11(%sNode* %while_exp42, %buffer* %codes43, %sParserInfo* %info44), !dbg !311
  %logical_denial = icmp eq i1 %fun_result45, false, !dbg !311
  br i1 %logical_denial, label %cond_jump_then46, label %cond_end47, !dbg !311

cond_jump_elif0:                                  ; preds = %entry
  %node123 = load %sNode*, %sNode** %node, align 8, !dbg !312
  %field124 = getelementptr inbounds %sNode, %sNode* %node123, i32 0, i32 0, !dbg !312
  %kind125 = load i32, i32* %field124, align 4, !dbg !312
  %eq126 = icmp eq i32 %kind125, 14, !dbg !312
  br i1 %eq126, label %cond_jump_elif_then0, label %cond_jump_elif1, !dbg !312

cond_jump_elif_then0:                             ; preds = %cond_jump_elif0
  %info127 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !313
  %field128 = getelementptr inbounds %sParserInfo, %sParserInfo* %info127, i32 0, i32 7, !dbg !313
  %breaks129 = load %vector_int*, %vector_int** %field128, align 8, !dbg !313
  %eq130 = icmp eq %vector_int* %breaks129, null, !dbg !313
  br i1 %eq130, label %cond_jump_then131, label %cond_end132, !dbg !313

cond_jump_elif1:                                  ; preds = %cond_jump_elif0
  %node148 = load %sNode*, %sNode** %node, align 8, !dbg !314
  %field149 = getelementptr inbounds %sNode, %sNode* %node148, i32 0, i32 0, !dbg !314
  %kind150 = load i32, i32* %field149, align 4, !dbg !314
  %eq151 = icmp eq i32 %kind150, 13, !dbg !314
  br i1 %eq151, label %cond_jump_elif_then1, label %cond_end, !dbg !314

cond_jump_elif_then1:                             ; preds = %cond_jump_elif1
  %info152 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !315
  %field153 = getelementptr inbounds %sParserInfo, %sParserInfo* %info152, i32 0, i32 6, !dbg !315
  %loop_head154 = load i32, i32* %field153, align 4, !dbg !315
  %eq155 = icmp eq i32 %loop_head154, -1, !dbg !315
  br i1 %eq155, label %cond_jump_then156, label %cond_end157, !dbg !315

cond_end:                                         ; preds = %cond_end157, %cond_jump_elif1, %cond_end132, %cond_end_block
  ret i1 true, !dbg !316

cond_jump_then46:                                 ; preds = %cond_jump_then
  ret i1 false, !dbg !317

cond_end47:                                       ; preds = %cond_jump_then
  %codes48 = load %buffer*, %buffer** %codes, align 8, !dbg !318
  call void @buffer_append_int(%buffer* %codes48, i32 11), !dbg !318
  %while_codes49 = load %buffer*, %buffer** %while_codes, align 8, !dbg !319
  %fun_result50 = call i32 @buffer_length(%buffer* %while_codes49), !dbg !319
  store i32 %fun_result50, i32* %offset, align 4, !dbg !299
  %offset51 = load i32, i32* %offset, align 4, !dbg !320
  %add = add i32 %offset51, 3, !dbg !320
  %andtmp = and i32 %add, -4, !dbg !320
  store i32 %andtmp, i32* %offset, align 4, !dbg !320
  %offset52 = load i32, i32* %offset, align 4, !dbg !321
  %div = sdiv i32 %offset52, 4, !dbg !321
  store i32 %div, i32* %offset, align 4, !dbg !321
  %offset53 = load i32, i32* %offset, align 4, !dbg !322
  %add54 = add i32 %offset53, 2, !dbg !322
  store i32 %add54, i32* %offset, align 4, !dbg !322
  %sub = sub i32 %add54, 2, !dbg !322
  %codes55 = load %buffer*, %buffer** %codes, align 8, !dbg !323
  %offset56 = load i32, i32* %offset, align 4, !dbg !323
  call void @buffer_append_int(%buffer* %codes55, i32 %offset56), !dbg !323
  %codes57 = load %buffer*, %buffer** %codes, align 8, !dbg !324
  %field58 = getelementptr inbounds %buffer, %buffer* %codes57, i32 0, i32 1, !dbg !324
  %len = load i32, i32* %field58, align 4, !dbg !324
  store i32 %len, i32* %while_codes_top, align 4, !dbg !299
  %codes59 = load %buffer*, %buffer** %codes, align 8, !dbg !325
  %while_codes60 = load %buffer*, %buffer** %while_codes, align 8, !dbg !325
  %field61 = getelementptr inbounds %buffer, %buffer* %while_codes60, i32 0, i32 0, !dbg !325
  %buf = load i8*, i8** %field61, align 8, !dbg !325
  %while_codes62 = load %buffer*, %buffer** %while_codes, align 8, !dbg !325
  %field63 = getelementptr inbounds %buffer, %buffer* %while_codes62, i32 0, i32 1, !dbg !325
  %len64 = load i32, i32* %field63, align 4, !dbg !325
  %icastD = sext i32 %len64 to i64, !dbg !325
  call void @buffer_append(%buffer* %codes59, i8* %buf, i64 %icastD), !dbg !325
  %codes65 = load %buffer*, %buffer** %codes, align 8, !dbg !326
  call void @buffer_alignment(%buffer* %codes65), !dbg !326
  %info66 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !327
  %info67 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !327
  %field68 = getelementptr inbounds %sParserInfo, %sParserInfo* %info67, i32 0, i32 3, !dbg !327
  %stack_num = load i32, i32* %field68, align 4, !dbg !327
  %sub69 = sub i32 %stack_num, 1, !dbg !327
  %field70 = getelementptr inbounds %sParserInfo, %sParserInfo* %info66, i32 0, i32 3, !dbg !327
  store i32 %sub69, i32* %field70, align 4, !dbg !327
  %add71 = add i32 %sub69, 1, !dbg !327
  %codes72 = load %buffer*, %buffer** %codes, align 8, !dbg !328
  call void @buffer_append_int(%buffer* %codes72, i32 12), !dbg !328
  %codes73 = load %buffer*, %buffer** %codes, align 8, !dbg !329
  %head74 = load i32, i32* %head, align 4, !dbg !329
  call void @buffer_append_int(%buffer* %codes73, i32 %head74), !dbg !329
  %else_nodes75 = load %list_sNodep*, %list_sNodep** %else_nodes25, align 8, !dbg !330
  %icmpB = icmp ne %list_sNodep* %else_nodes75, null, !dbg !330
  br i1 %icmpB, label %cond_jump_then76, label %cond_end77, !dbg !330

cond_jump_then76:                                 ; preds = %cond_end47
  %else_nodes78 = load %list_sNodep*, %list_sNodep** %else_nodes25, align 8, !dbg !331
  %info79 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !331
  %fun_result80 = call %buffer* @compile_nodes(%list_sNodep* %else_nodes78, %sParserInfo* %info79), !dbg !331
  store %buffer* %fun_result80, %buffer** %else_codes, align 8, !dbg !299
  %codes81 = load %buffer*, %buffer** %codes, align 8, !dbg !332
  %else_codes82 = load %buffer*, %buffer** %else_codes, align 8, !dbg !332
  %field83 = getelementptr inbounds %buffer, %buffer* %else_codes82, i32 0, i32 0, !dbg !332
  %buf84 = load i8*, i8** %field83, align 8, !dbg !332
  %else_codes85 = load %buffer*, %buffer** %else_codes, align 8, !dbg !332
  %field86 = getelementptr inbounds %buffer, %buffer* %else_codes85, i32 0, i32 1, !dbg !332
  %len87 = load i32, i32* %field86, align 4, !dbg !332
  %icastD88 = sext i32 %len87 to i64, !dbg !332
  call void @buffer_append(%buffer* %codes81, i8* %buf84, i64 %icastD88), !dbg !332
  %codes89 = load %buffer*, %buffer** %codes, align 8, !dbg !333
  call void @buffer_alignment(%buffer* %codes89), !dbg !333
  br label %cond_end77, !dbg !333

cond_end77:                                       ; preds = %cond_jump_then76, %cond_end47
  store i32 0, i32* %i, align 4, !dbg !299
  br label %loop_top_block, !dbg !299

loop_top_block:                                   ; preds = %cond_then_block, %cond_end77
  %i90 = load i32, i32* %i, align 4, !dbg !334
  %info91 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !334
  %field92 = getelementptr inbounds %sParserInfo, %sParserInfo* %info91, i32 0, i32 7, !dbg !334
  %breaks93 = load %vector_int*, %vector_int** %field92, align 8, !dbg !334
  %fun_result94 = call i32 @vector_length_int(%vector_int* %breaks93), !dbg !334
  %le = icmp slt i32 %i90, %fun_result94, !dbg !334
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !334

cond_then_block:                                  ; preds = %loop_top_block
  %info95 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !335
  %field96 = getelementptr inbounds %sParserInfo, %sParserInfo* %info95, i32 0, i32 7, !dbg !335
  %breaks97 = load %vector_int*, %vector_int** %field96, align 8, !dbg !335
  %i98 = load i32, i32* %i, align 4, !dbg !335
  %fun_result99 = call i32 @vector_item_int(%vector_int* %breaks97, i32 %i98, i32 -1), !dbg !335
  store i32 %fun_result99, i32* %break_point, align 4, !dbg !299
  %codes100 = load %buffer*, %buffer** %codes, align 8, !dbg !336
  %field101 = getelementptr inbounds %buffer, %buffer* %codes100, i32 0, i32 0, !dbg !336
  %buf102 = load i8*, i8** %field101, align 8, !dbg !336
  %while_codes_top103 = load i32, i32* %while_codes_top, align 4, !dbg !336
  %ptrToIntC = ptrtoint i8* %buf102 to i64, !dbg !336
  %sext = sext i32 %while_codes_top103 to i64, !dbg !336
  %mul = mul i64 %sext, 1, !dbg !336
  %add104 = add i64 %ptrToIntC, %mul, !dbg !336
  %intToPtr = inttoptr i64 %add104 to i8*, !dbg !336
  %break_point105 = load i32, i32* %break_point, align 4, !dbg !336
  %ptrToIntC106 = ptrtoint i8* %intToPtr to i64, !dbg !336
  %sext107 = sext i32 %break_point105 to i64, !dbg !336
  %mul108 = mul i64 %sext107, 1, !dbg !336
  %add109 = add i64 %ptrToIntC106, %mul108, !dbg !336
  %intToPtr110 = inttoptr i64 %add109 to i8*, !dbg !336
  %castAQ = bitcast i8* %intToPtr110 to i32*, !dbg !336
  store i32* %castAQ, i32** %p, align 8, !dbg !299
  %p111 = load i32*, i32** %p, align 8, !dbg !337
  %codes112 = load %buffer*, %buffer** %codes, align 8, !dbg !337
  %fun_result113 = call i32 @buffer_length(%buffer* %codes112), !dbg !337
  store i32 %fun_result113, i32* %p111, align 4, !dbg !337
  %i114 = load i32, i32* %i, align 4, !dbg !334
  %add115 = add i32 %i114, 1, !dbg !334
  store i32 %add115, i32* %i, align 4, !dbg !334
  %sub116 = sub i32 %add115, 1, !dbg !334
  br label %loop_top_block, !dbg !334

cond_end_block:                                   ; preds = %loop_top_block
  %info117 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !338
  %breaks_before118 = load %vector_int*, %vector_int** %breaks_before, align 8, !dbg !338
  %field119 = getelementptr inbounds %sParserInfo, %sParserInfo* %info117, i32 0, i32 7, !dbg !338
  store %vector_int* %breaks_before118, %vector_int** %field119, align 8, !dbg !338
  %info120 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !339
  %head_before121 = load i32, i32* %head_before, align 4, !dbg !339
  %field122 = getelementptr inbounds %sParserInfo, %sParserInfo* %info120, i32 0, i32 6, !dbg !339
  store i32 %head_before121, i32* %field122, align 4, !dbg !339
  br label %cond_end, !dbg !339

cond_jump_then131:                                ; preds = %cond_jump_elif_then0
  %stderr = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !340
  %info133 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !340
  %field134 = getelementptr inbounds %sParserInfo, %sParserInfo* %info133, i32 0, i32 2, !dbg !340
  %fname = load i8*, i8** %field134, align 8, !dbg !340
  %info135 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !340
  %field136 = getelementptr inbounds %sParserInfo, %sParserInfo* %info135, i32 0, i32 1, !dbg !340
  %sline = load i32, i32* %field136, align 4, !dbg !340
  %fun_result137 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @"%s %d: require loop for break\0A", i32 0, i32 0), i8* %fname, i32 %sline), !dbg !340
  ret i1 false, !dbg !341

cond_end132:                                      ; preds = %cond_jump_elif_then0
  %codes138 = load %buffer*, %buffer** %codes, align 8, !dbg !342
  call void @buffer_append_int(%buffer* %codes138, i32 12), !dbg !342
  %codes139 = load %buffer*, %buffer** %codes, align 8, !dbg !343
  %field140 = getelementptr inbounds %buffer, %buffer* %codes139, i32 0, i32 1, !dbg !343
  %len141 = load i32, i32* %field140, align 4, !dbg !343
  store i32 %len141, i32* %break_point142, align 4, !dbg !299
  %info143 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !344
  %field144 = getelementptr inbounds %sParserInfo, %sParserInfo* %info143, i32 0, i32 7, !dbg !344
  %breaks145 = load %vector_int*, %vector_int** %field144, align 8, !dbg !344
  %break_point146 = load i32, i32* %break_point142, align 4, !dbg !344
  call void @vector_push_back_int(%vector_int* %breaks145, i32 %break_point146), !dbg !344
  %codes147 = load %buffer*, %buffer** %codes, align 8, !dbg !345
  call void @buffer_append_int(%buffer* %codes147, i32 0), !dbg !345
  br label %cond_end, !dbg !345

cond_jump_then156:                                ; preds = %cond_jump_elif_then1
  %stderr158 = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !346
  %info159 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !346
  %field160 = getelementptr inbounds %sParserInfo, %sParserInfo* %info159, i32 0, i32 2, !dbg !346
  %fname161 = load i8*, i8** %field160, align 8, !dbg !346
  %info162 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !346
  %field163 = getelementptr inbounds %sParserInfo, %sParserInfo* %info162, i32 0, i32 1, !dbg !346
  %sline164 = load i32, i32* %field163, align 4, !dbg !346
  %fun_result165 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr158, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @"%s %d: require loop for continue\0A", i32 0, i32 0), i8* %fname161, i32 %sline164), !dbg !346
  ret i1 false, !dbg !347

cond_end157:                                      ; preds = %cond_jump_elif_then1
  %codes166 = load %buffer*, %buffer** %codes, align 8, !dbg !348
  call void @buffer_append_int(%buffer* %codes166, i32 12), !dbg !348
  %codes167 = load %buffer*, %buffer** %codes, align 8, !dbg !349
  %info168 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !349
  %field169 = getelementptr inbounds %sParserInfo, %sParserInfo* %info168, i32 0, i32 6, !dbg !349
  %loop_head170 = load i32, i32* %field169, align 4, !dbg !349
  call void @buffer_append_int(%buffer* %codes167, i32 %loop_head170), !dbg !349
  br label %cond_end, !dbg !349
}

declare i1 @expression_v11(%sNode**, %sParserInfo*)

declare i1 @compile_v11(%sNode*, %buffer*, %sParserInfo*)

define internal %sNode* @create_while(%sNode* %0, %list_sNodep* %1, %list_sNodep* %2, %sParserInfo* %3) !dbg !350 {
entry:
  %result = alloca %sNode*, align 8, !dbg !353
  %while_exp = alloca %sNode*, align 8, !dbg !353
  store %sNode* %0, %sNode** %while_exp, align 8, !dbg !353
  %while_nodes = alloca %list_sNodep*, align 8, !dbg !353
  store %list_sNodep* %1, %list_sNodep** %while_nodes, align 8, !dbg !353
  %else_nodes = alloca %list_sNodep*, align 8, !dbg !353
  store %list_sNodep* %2, %list_sNodep** %else_nodes, align 8, !dbg !353
  %info = alloca %sParserInfo*, align 8, !dbg !353
  store %sParserInfo* %3, %sParserInfo** %info, align 8, !dbg !353
  %fun_result = call i8* @GC_malloc(i64 64), !dbg !354
  %obj = bitcast i8* %fun_result to %sNode*, !dbg !354
  store %sNode* %obj, %sNode** %result, align 8, !dbg !353
  %result1 = load %sNode*, %sNode** %result, align 8, !dbg !355
  %field = getelementptr inbounds %sNode, %sNode* %result1, i32 0, i32 0, !dbg !355
  store i32 12, i32* %field, align 4, !dbg !355
  %result2 = load %sNode*, %sNode** %result, align 8, !dbg !356
  %info3 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !356
  %field4 = getelementptr inbounds %sParserInfo, %sParserInfo* %info3, i32 0, i32 2, !dbg !356
  %fname = load i8*, i8** %field4, align 8, !dbg !356
  %field5 = getelementptr inbounds %sNode, %sNode* %result2, i32 0, i32 1, !dbg !356
  store i8* %fname, i8** %field5, align 8, !dbg !356
  %result6 = load %sNode*, %sNode** %result, align 8, !dbg !357
  %info7 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !357
  %field8 = getelementptr inbounds %sParserInfo, %sParserInfo* %info7, i32 0, i32 1, !dbg !357
  %sline = load i32, i32* %field8, align 4, !dbg !357
  %field9 = getelementptr inbounds %sNode, %sNode* %result6, i32 0, i32 2, !dbg !357
  store i32 %sline, i32* %field9, align 4, !dbg !357
  %result10 = load %sNode*, %sNode** %result, align 8, !dbg !358
  %field11 = getelementptr inbounds %sNode, %sNode* %result10, i32 0, i32 3, !dbg !358
  %value = load %come_anon75, %come_anon75* %field11, align 8, !dbg !358
  %field12 = getelementptr inbounds %come_anon75, %come_anon75* %field11, i32 0, i32 0, !dbg !358
  %icastO = bitcast %come_anon81* %field12 to %come_anon82*, !dbg !358
  %whileValue = load %come_anon82, %come_anon82* %icastO, align 8, !dbg !358
  %while_exp13 = load %sNode*, %sNode** %while_exp, align 8, !dbg !358
  %field14 = getelementptr inbounds %come_anon82, %come_anon82* %icastO, i32 0, i32 0, !dbg !358
  store %sNode* %while_exp13, %sNode** %field14, align 8, !dbg !358
  %result15 = load %sNode*, %sNode** %result, align 8, !dbg !359
  %field16 = getelementptr inbounds %sNode, %sNode* %result15, i32 0, i32 3, !dbg !359
  %value17 = load %come_anon75, %come_anon75* %field16, align 8, !dbg !359
  %field18 = getelementptr inbounds %come_anon75, %come_anon75* %field16, i32 0, i32 0, !dbg !359
  %icastO19 = bitcast %come_anon81* %field18 to %come_anon82*, !dbg !359
  %whileValue20 = load %come_anon82, %come_anon82* %icastO19, align 8, !dbg !359
  %while_nodes21 = load %list_sNodep*, %list_sNodep** %while_nodes, align 8, !dbg !359
  %field22 = getelementptr inbounds %come_anon82, %come_anon82* %icastO19, i32 0, i32 1, !dbg !359
  store %list_sNodep* %while_nodes21, %list_sNodep** %field22, align 8, !dbg !359
  %result23 = load %sNode*, %sNode** %result, align 8, !dbg !360
  %field24 = getelementptr inbounds %sNode, %sNode* %result23, i32 0, i32 3, !dbg !360
  %value25 = load %come_anon75, %come_anon75* %field24, align 8, !dbg !360
  %field26 = getelementptr inbounds %come_anon75, %come_anon75* %field24, i32 0, i32 0, !dbg !360
  %icastO27 = bitcast %come_anon81* %field26 to %come_anon82*, !dbg !360
  %whileValue28 = load %come_anon82, %come_anon82* %icastO27, align 8, !dbg !360
  %else_nodes29 = load %list_sNodep*, %list_sNodep** %else_nodes, align 8, !dbg !360
  %field30 = getelementptr inbounds %come_anon82, %come_anon82* %icastO27, i32 0, i32 2, !dbg !360
  store %list_sNodep* %else_nodes29, %list_sNodep** %field30, align 8, !dbg !360
  %result31 = load %sNode*, %sNode** %result, align 8, !dbg !361
  ret %sNode* %result31, !dbg !361
}

define internal %sNode* @create_continue(%sParserInfo* %0) !dbg !362 {
entry:
  %result = alloca %sNode*, align 8, !dbg !363
  %info = alloca %sParserInfo*, align 8, !dbg !363
  store %sParserInfo* %0, %sParserInfo** %info, align 8, !dbg !363
  %fun_result = call i8* @GC_malloc(i64 64), !dbg !364
  %obj = bitcast i8* %fun_result to %sNode*, !dbg !364
  store %sNode* %obj, %sNode** %result, align 8, !dbg !363
  %result1 = load %sNode*, %sNode** %result, align 8, !dbg !365
  %field = getelementptr inbounds %sNode, %sNode* %result1, i32 0, i32 0, !dbg !365
  store i32 13, i32* %field, align 4, !dbg !365
  %result2 = load %sNode*, %sNode** %result, align 8, !dbg !366
  %info3 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !366
  %field4 = getelementptr inbounds %sParserInfo, %sParserInfo* %info3, i32 0, i32 2, !dbg !366
  %fname = load i8*, i8** %field4, align 8, !dbg !366
  %field5 = getelementptr inbounds %sNode, %sNode* %result2, i32 0, i32 1, !dbg !366
  store i8* %fname, i8** %field5, align 8, !dbg !366
  %result6 = load %sNode*, %sNode** %result, align 8, !dbg !367
  %info7 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !367
  %field8 = getelementptr inbounds %sParserInfo, %sParserInfo* %info7, i32 0, i32 1, !dbg !367
  %sline = load i32, i32* %field8, align 4, !dbg !367
  %field9 = getelementptr inbounds %sNode, %sNode* %result6, i32 0, i32 2, !dbg !367
  store i32 %sline, i32* %field9, align 4, !dbg !367
  %result10 = load %sNode*, %sNode** %result, align 8, !dbg !368
  ret %sNode* %result10, !dbg !368
}

define internal %sNode* @create_break(%sParserInfo* %0) !dbg !369 {
entry:
  %result = alloca %sNode*, align 8, !dbg !370
  %info = alloca %sParserInfo*, align 8, !dbg !370
  store %sParserInfo* %0, %sParserInfo** %info, align 8, !dbg !370
  %fun_result = call i8* @GC_malloc(i64 64), !dbg !371
  %obj = bitcast i8* %fun_result to %sNode*, !dbg !371
  store %sNode* %obj, %sNode** %result, align 8, !dbg !370
  %result1 = load %sNode*, %sNode** %result, align 8, !dbg !372
  %field = getelementptr inbounds %sNode, %sNode* %result1, i32 0, i32 0, !dbg !372
  store i32 14, i32* %field, align 4, !dbg !372
  %result2 = load %sNode*, %sNode** %result, align 8, !dbg !373
  %info3 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !373
  %field4 = getelementptr inbounds %sParserInfo, %sParserInfo* %info3, i32 0, i32 2, !dbg !373
  %fname = load i8*, i8** %field4, align 8, !dbg !373
  %field5 = getelementptr inbounds %sNode, %sNode* %result2, i32 0, i32 1, !dbg !373
  store i8* %fname, i8** %field5, align 8, !dbg !373
  %result6 = load %sNode*, %sNode** %result, align 8, !dbg !374
  %info7 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !374
  %field8 = getelementptr inbounds %sParserInfo, %sParserInfo* %info7, i32 0, i32 1, !dbg !374
  %sline = load i32, i32* %field8, align 4, !dbg !374
  %field9 = getelementptr inbounds %sNode, %sNode* %result6, i32 0, i32 2, !dbg !374
  store i32 %sline, i32* %field9, align 4, !dbg !374
  %result10 = load %sNode*, %sNode** %result, align 8, !dbg !375
  ret %sNode* %result10, !dbg !375
}

define internal i1 @word_cmp(i8* %0, i8* %1) !dbg !376 {
entry:
  %oror10 = alloca i1, align 1, !dbg !377
  %oror9 = alloca i1, align 1, !dbg !377
  %oror8 = alloca i1, align 1, !dbg !377
  %oror = alloca i1, align 1, !dbg !377
  %andand = alloca i1, align 1, !dbg !377
  %c = alloca i8, align 1, !dbg !377
  %result = alloca i1, align 1, !dbg !377
  %p = alloca i8*, align 8, !dbg !377
  store i8* %0, i8** %p, align 8, !dbg !377
  %word2 = alloca i8*, align 8, !dbg !377
  store i8* %1, i8** %word2, align 8, !dbg !377
  %p1 = load i8*, i8** %p, align 8, !dbg !378
  %word22 = load i8*, i8** %word2, align 8, !dbg !378
  %fun_result = call i8* @strstr(i8* %p1, i8* %word22), !dbg !378
  %p3 = load i8*, i8** %p, align 8, !dbg !378
  %eq = icmp eq i8* %fun_result, %p3, !dbg !378
  store i1 %eq, i1* %result, align 1, !dbg !377
  %p4 = load i8*, i8** %p, align 8, !dbg !379
  %word25 = load i8*, i8** %word2, align 8, !dbg !379
  %fun_result6 = call i64 @strlen(i8* %word25), !dbg !379
  %icastM = trunc i64 %fun_result6 to i32, !dbg !379
  %element_address = getelementptr inbounds i8, i8* %p4, i32 %icastM, !dbg !379
  %element = load i8, i8* %element_address, align 1, !dbg !379
  store i8 %element, i8* %c, align 1, !dbg !377
  %result7 = load i1, i1* %result, align 1, !dbg !380
  store i1 %result7, i1* %andand, align 1, !dbg !380
  br i1 %result7, label %cond_jump_then, label %cond_jump_end, !dbg !380

cond_jump_then:                                   ; preds = %entry
  %c11 = load i8, i8* %c, align 1, !dbg !380
  %eq12 = icmp eq i8 %c11, 10, !dbg !380
  store i1 %eq12, i1* %oror10, align 1, !dbg !380
  br i1 %eq12, label %cond_jump_end14, label %cond_jump_then13, !dbg !380

cond_jump_end:                                    ; preds = %cond_jump_end31, %entry
  %andand_result_value = load i1, i1* %andand, align 1, !dbg !380
  br i1 %andand_result_value, label %cond_jump_then37, label %cond_end, !dbg !380

cond_jump_then13:                                 ; preds = %cond_jump_then
  %c15 = load i8, i8* %c, align 1, !dbg !380
  %eq16 = icmp eq i8 %c15, 32, !dbg !380
  %oror17 = or i1 %eq12, %eq16, !dbg !380
  store i1 %oror17, i1* %oror10, align 1, !dbg !380
  br label %cond_jump_end14, !dbg !380

cond_jump_end14:                                  ; preds = %cond_jump_then13, %cond_jump_then
  %oror_result_value = load i1, i1* %oror10, align 1, !dbg !380
  store i1 %oror_result_value, i1* %oror9, align 1, !dbg !380
  br i1 %oror_result_value, label %cond_jump_end19, label %cond_jump_then18, !dbg !380

cond_jump_then18:                                 ; preds = %cond_jump_end14
  %c20 = load i8, i8* %c, align 1, !dbg !380
  %eq21 = icmp eq i8 %c20, 9, !dbg !380
  %oror22 = or i1 %oror_result_value, %eq21, !dbg !380
  store i1 %oror22, i1* %oror9, align 1, !dbg !380
  br label %cond_jump_end19, !dbg !380

cond_jump_end19:                                  ; preds = %cond_jump_then18, %cond_jump_end14
  %oror_result_value23 = load i1, i1* %oror9, align 1, !dbg !380
  store i1 %oror_result_value23, i1* %oror8, align 1, !dbg !380
  br i1 %oror_result_value23, label %cond_jump_end25, label %cond_jump_then24, !dbg !380

cond_jump_then24:                                 ; preds = %cond_jump_end19
  %c26 = load i8, i8* %c, align 1, !dbg !380
  %eq27 = icmp eq i8 %c26, 0, !dbg !380
  %oror28 = or i1 %oror_result_value23, %eq27, !dbg !380
  store i1 %oror28, i1* %oror8, align 1, !dbg !380
  br label %cond_jump_end25, !dbg !380

cond_jump_end25:                                  ; preds = %cond_jump_then24, %cond_jump_end19
  %oror_result_value29 = load i1, i1* %oror8, align 1, !dbg !380
  store i1 %oror_result_value29, i1* %oror, align 1, !dbg !380
  br i1 %oror_result_value29, label %cond_jump_end31, label %cond_jump_then30, !dbg !380

cond_jump_then30:                                 ; preds = %cond_jump_end25
  %c32 = load i8, i8* %c, align 1, !dbg !380
  %eq33 = icmp eq i8 %c32, 58, !dbg !380
  %oror34 = or i1 %oror_result_value29, %eq33, !dbg !380
  store i1 %oror34, i1* %oror, align 1, !dbg !380
  br label %cond_jump_end31, !dbg !380

cond_jump_end31:                                  ; preds = %cond_jump_then30, %cond_jump_end25
  %oror_result_value35 = load i1, i1* %oror, align 1, !dbg !380
  %andand36 = and i1 %result7, %oror_result_value35, !dbg !380
  store i1 %andand36, i1* %andand, align 1, !dbg !380
  br label %cond_jump_end, !dbg !380

cond_jump_then37:                                 ; preds = %cond_jump_end
  ret i1 true, !dbg !381

cond_end:                                         ; preds = %cond_jump_end
  ret i1 false, !dbg !382
}

define internal %vector_int* @vector_initialize_int(%vector_int* %0) {
entry:
  %self = alloca %vector_int*, align 8, !dbg !309
  store %vector_int* %0, %vector_int** %self, align 8, !dbg !309
  %self1 = load %vector_int*, %vector_int** %self, align 8, !dbg !309
  %field = getelementptr inbounds %vector_int, %vector_int* %self1, i32 0, i32 2, !dbg !309
  store i32 16, i32* %field, align 4, !dbg !309
  %self2 = load %vector_int*, %vector_int** %self, align 8, !dbg !309
  %field3 = getelementptr inbounds %vector_int, %vector_int* %self2, i32 0, i32 1, !dbg !309
  store i32 0, i32* %field3, align 4, !dbg !309
  %self4 = load %vector_int*, %vector_int** %self, align 8, !dbg !309
  %self5 = load %vector_int*, %vector_int** %self, align 8, !dbg !309
  %field6 = getelementptr inbounds %vector_int, %vector_int* %self5, i32 0, i32 2, !dbg !309
  %size = load i32, i32* %field6, align 4, !dbg !309
  %icastD = sext i32 %size to i64, !dbg !309
  %mul = mul i64 4, %icastD, !dbg !309
  %fun_result = call i8* @GC_malloc(i64 %mul), !dbg !309
  %obj = bitcast i8* %fun_result to i32*, !dbg !309
  %field7 = getelementptr inbounds %vector_int, %vector_int* %self4, i32 0, i32 0, !dbg !309
  store i32* %obj, i32** %field7, align 8, !dbg !309
  %self8 = load %vector_int*, %vector_int** %self, align 8, !dbg !309
  ret %vector_int* %self8, !dbg !309
}

define internal i32 @vector_length_int(%vector_int* %0) {
entry:
  %self = alloca %vector_int*, align 8, !dbg !334
  store %vector_int* %0, %vector_int** %self, align 8, !dbg !334
  %self1 = load %vector_int*, %vector_int** %self, align 8, !dbg !334
  %field = getelementptr inbounds %vector_int, %vector_int* %self1, i32 0, i32 1, !dbg !334
  %len = load i32, i32* %field, align 4, !dbg !334
  ret i32 %len, !dbg !334
}

define internal i32 @vector_item_int(%vector_int* %0, i32 %1, i32 %2) {
entry:
  %andand = alloca i1, align 1, !dbg !335
  %self = alloca %vector_int*, align 8, !dbg !335
  store %vector_int* %0, %vector_int** %self, align 8, !dbg !335
  %index = alloca i32, align 4, !dbg !335
  store i32 %1, i32* %index, align 4, !dbg !335
  %default_value = alloca i32, align 4, !dbg !335
  store i32 %2, i32* %default_value, align 4, !dbg !335
  %index1 = load i32, i32* %index, align 4, !dbg !335
  %le = icmp slt i32 %index1, 0, !dbg !335
  br i1 %le, label %cond_jump_then, label %cond_end, !dbg !335

cond_jump_then:                                   ; preds = %entry
  %index2 = load i32, i32* %index, align 4, !dbg !335
  %self3 = load %vector_int*, %vector_int** %self, align 8, !dbg !335
  %field = getelementptr inbounds %vector_int, %vector_int* %self3, i32 0, i32 1, !dbg !335
  %len = load i32, i32* %field, align 4, !dbg !335
  %add = add i32 %index2, %len, !dbg !335
  store i32 %add, i32* %index, align 4, !dbg !335
  %self4 = load %vector_int*, %vector_int** %self, align 8, !dbg !335
  %field5 = getelementptr inbounds %vector_int, %vector_int* %self4, i32 0, i32 1, !dbg !335
  %len6 = load i32, i32* %field5, align 4, !dbg !335
  %sub = sub i32 %add, %len6, !dbg !335
  br label %cond_end, !dbg !335

cond_end:                                         ; preds = %cond_jump_then, %entry
  %index7 = load i32, i32* %index, align 4, !dbg !335
  %gteq = icmp sge i32 %index7, 0, !dbg !335
  store i1 %gteq, i1* %andand, align 1, !dbg !335
  br i1 %gteq, label %cond_jump_then8, label %cond_jump_end, !dbg !335

cond_jump_then8:                                  ; preds = %cond_end
  %index9 = load i32, i32* %index, align 4, !dbg !335
  %self10 = load %vector_int*, %vector_int** %self, align 8, !dbg !335
  %field11 = getelementptr inbounds %vector_int, %vector_int* %self10, i32 0, i32 1, !dbg !335
  %len12 = load i32, i32* %field11, align 4, !dbg !335
  %le13 = icmp slt i32 %index9, %len12, !dbg !335
  %andand14 = and i1 %gteq, %le13, !dbg !335
  store i1 %andand14, i1* %andand, align 1, !dbg !335
  br label %cond_jump_end, !dbg !335

cond_jump_end:                                    ; preds = %cond_jump_then8, %cond_end
  %andand_result_value = load i1, i1* %andand, align 1, !dbg !335
  br i1 %andand_result_value, label %cond_jump_then15, label %cond_end16, !dbg !335

cond_jump_then15:                                 ; preds = %cond_jump_end
  %self17 = load %vector_int*, %vector_int** %self, align 8, !dbg !335
  %field18 = getelementptr inbounds %vector_int, %vector_int* %self17, i32 0, i32 0, !dbg !335
  %items = load i32*, i32** %field18, align 8, !dbg !335
  %index19 = load i32, i32* %index, align 4, !dbg !335
  %element_address = getelementptr inbounds i32, i32* %items, i32 %index19, !dbg !335
  %element = load i32, i32* %element_address, align 4, !dbg !335
  ret i32 %element, !dbg !335

cond_end16:                                       ; preds = %cond_jump_end
  %default_value20 = load i32, i32* %default_value, align 4, !dbg !335
  ret i32 %default_value20, !dbg !335
}

define internal void @vector_push_back_int(%vector_int* %0, i32 %1) {
entry:
  %i = alloca i32, align 4, !dbg !344
  %items9 = alloca i32*, align 8, !dbg !344
  %new_size = alloca i32, align 4, !dbg !344
  %self = alloca %vector_int*, align 8, !dbg !344
  store %vector_int* %0, %vector_int** %self, align 8, !dbg !344
  %item = alloca i32, align 4, !dbg !344
  store i32 %1, i32* %item, align 4, !dbg !344
  %self1 = load %vector_int*, %vector_int** %self, align 8, !dbg !344
  %field = getelementptr inbounds %vector_int, %vector_int* %self1, i32 0, i32 1, !dbg !344
  %len = load i32, i32* %field, align 4, !dbg !344
  %self2 = load %vector_int*, %vector_int** %self, align 8, !dbg !344
  %field3 = getelementptr inbounds %vector_int, %vector_int* %self2, i32 0, i32 2, !dbg !344
  %size = load i32, i32* %field3, align 4, !dbg !344
  %eq = icmp eq i32 %len, %size, !dbg !344
  br i1 %eq, label %cond_jump_then, label %cond_end, !dbg !344

cond_jump_then:                                   ; preds = %entry
  %self4 = load %vector_int*, %vector_int** %self, align 8, !dbg !344
  %field5 = getelementptr inbounds %vector_int, %vector_int* %self4, i32 0, i32 2, !dbg !344
  %size6 = load i32, i32* %field5, align 4, !dbg !344
  %mul = mul i32 %size6, 2, !dbg !344
  store i32 %mul, i32* %new_size, align 4, !dbg !344
  %self7 = load %vector_int*, %vector_int** %self, align 8, !dbg !344
  %field8 = getelementptr inbounds %vector_int, %vector_int* %self7, i32 0, i32 0, !dbg !344
  %items = load i32*, i32** %field8, align 8, !dbg !344
  store i32* %items, i32** %items9, align 8, !dbg !344
  %self10 = load %vector_int*, %vector_int** %self, align 8, !dbg !344
  %new_size11 = load i32, i32* %new_size, align 4, !dbg !344
  %icastD = sext i32 %new_size11 to i64, !dbg !344
  %mul12 = mul i64 4, %icastD, !dbg !344
  %fun_result = call i8* @GC_malloc(i64 %mul12), !dbg !344
  %castAQ = bitcast i8* %fun_result to i32*, !dbg !344
  %field13 = getelementptr inbounds %vector_int, %vector_int* %self10, i32 0, i32 0, !dbg !344
  store i32* %castAQ, i32** %field13, align 8, !dbg !344
  store i32 0, i32* %i, align 4, !dbg !344
  br label %loop_top_block, !dbg !344

cond_end:                                         ; preds = %cond_end_block, %entry
  %self29 = load %vector_int*, %vector_int** %self, align 8, !dbg !344
  %field30 = getelementptr inbounds %vector_int, %vector_int* %self29, i32 0, i32 0, !dbg !344
  %items31 = load i32*, i32** %field30, align 8, !dbg !344
  %self32 = load %vector_int*, %vector_int** %self, align 8, !dbg !344
  %field33 = getelementptr inbounds %vector_int, %vector_int* %self32, i32 0, i32 1, !dbg !344
  %len34 = load i32, i32* %field33, align 4, !dbg !344
  %item35 = load i32, i32* %item, align 4, !dbg !344
  %element_address36 = getelementptr i32, i32* %items31, i32 %len34, !dbg !344
  store i32 %item35, i32* %element_address36, align 4, !dbg !344
  %self37 = load %vector_int*, %vector_int** %self, align 8, !dbg !344
  %self38 = load %vector_int*, %vector_int** %self, align 8, !dbg !344
  %field39 = getelementptr inbounds %vector_int, %vector_int* %self38, i32 0, i32 1, !dbg !344
  %len40 = load i32, i32* %field39, align 4, !dbg !344
  %add41 = add i32 %len40, 1, !dbg !344
  %field42 = getelementptr inbounds %vector_int, %vector_int* %self37, i32 0, i32 1, !dbg !344
  store i32 %add41, i32* %field42, align 4, !dbg !344
  %sub43 = sub i32 %add41, 1, !dbg !344
  ret void, !dbg !344

loop_top_block:                                   ; preds = %cond_then_block, %cond_jump_then
  %i14 = load i32, i32* %i, align 4, !dbg !344
  %self15 = load %vector_int*, %vector_int** %self, align 8, !dbg !344
  %field16 = getelementptr inbounds %vector_int, %vector_int* %self15, i32 0, i32 2, !dbg !344
  %size17 = load i32, i32* %field16, align 4, !dbg !344
  %le = icmp slt i32 %i14, %size17, !dbg !344
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !344

cond_then_block:                                  ; preds = %loop_top_block
  %self18 = load %vector_int*, %vector_int** %self, align 8, !dbg !344
  %field19 = getelementptr inbounds %vector_int, %vector_int* %self18, i32 0, i32 0, !dbg !344
  %items20 = load i32*, i32** %field19, align 8, !dbg !344
  %i21 = load i32, i32* %i, align 4, !dbg !344
  %items22 = load i32*, i32** %items9, align 8, !dbg !344
  %i23 = load i32, i32* %i, align 4, !dbg !344
  %element_address = getelementptr inbounds i32, i32* %items22, i32 %i23, !dbg !344
  %element = load i32, i32* %element_address, align 4, !dbg !344
  %element_address24 = getelementptr i32, i32* %items20, i32 %i21, !dbg !344
  store i32 %element, i32* %element_address24, align 4, !dbg !344
  %i25 = load i32, i32* %i, align 4, !dbg !344
  %add = add i32 %i25, 1, !dbg !344
  store i32 %add, i32* %i, align 4, !dbg !344
  %sub = sub i32 %add, 1, !dbg !344
  br label %loop_top_block, !dbg !344

cond_end_block:                                   ; preds = %loop_top_block
  %self26 = load %vector_int*, %vector_int** %self, align 8, !dbg !344
  %new_size27 = load i32, i32* %new_size, align 4, !dbg !344
  %field28 = getelementptr inbounds %vector_int, %vector_int* %self26, i32 0, i32 2, !dbg !344
  store i32 %new_size27, i32* %field28, align 4, !dbg !344
  br label %cond_end, !dbg !344
}

attributes #0 = { nounwind }
attributes #1 = { nounwind willreturn }
attributes #2 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "come", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false)
!1 = !DIFile(filename: "src/10while.c", directory: "/home/ab25cq/repo/neo-c2/yappy")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = distinct !DISubprogram(name: "ncmemdup", linkageName: "ncmemdup", scope: !6, file: !6, line: 24, type: !7, scopeLine: 24, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!6 = !DIFile(filename: "/usr/local/include/neo-c2.h", directory: "/home/ab25cq/repo/neo-c2/yappy")
!7 = !DISubroutineType(types: !8)
!8 = !{!9}
!9 = !DIBasicType(name: "pointer", size: 64)
!10 = !DILocation(line: 24, scope: !5)
!11 = !DILocation(line: 26, scope: !5)
!12 = !DILocation(line: 28, scope: !5)
!13 = !DILocation(line: 29, scope: !5)
!14 = !DILocation(line: 32, scope: !5)
!15 = !DILocation(line: 34, scope: !5)
!16 = !DILocation(line: 35, scope: !5)
!17 = !DILocation(line: 36, scope: !5)
!18 = !DILocation(line: 42, scope: !5)
!19 = !DILocation(line: 44, scope: !5)
!20 = !DILocation(line: 37, scope: !5)
!21 = !DILocation(line: 38, scope: !5)
!22 = !DILocation(line: 39, scope: !5)
!23 = !DILocation(line: 40, scope: !5)
!24 = distinct !DISubprogram(name: "xsprintf", linkageName: "xsprintf", scope: !6, file: !6, line: 71, type: !7, scopeLine: 71, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!25 = !DILocation(line: 71, scope: !24)
!26 = !DILocation(line: 74, scope: !24)
!27 = !DILocation(line: 76, scope: !24)
!28 = !DILocation(line: 77, scope: !24)
!29 = !DILocation(line: 79, scope: !24)
!30 = !DILocation(line: 80, scope: !24)
!31 = !DILocation(line: 82, scope: !24)
!32 = !DILocation(line: 85, scope: !24)
!33 = !DILocation(line: 87, scope: !24)
!34 = !DILocation(line: 89, scope: !24)
!35 = distinct !DISubprogram(name: "char_reverse", linkageName: "char_reverse", scope: !6, file: !6, line: 92, type: !7, scopeLine: 92, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!36 = !DILocation(line: 92, scope: !35)
!37 = !DILocation(line: 94, scope: !35)
!38 = !DILocation(line: 95, scope: !35)
!39 = !DILocation(line: 97, scope: !35)
!40 = !DILocation(line: 98, scope: !35)
!41 = !DILocation(line: 101, scope: !35)
!42 = !DILocation(line: 103, scope: !35)
!43 = distinct !DISubprogram(name: "char_substring", linkageName: "char_substring", scope: !6, file: !6, line: 106, type: !44, scopeLine: 106, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!44 = !DISubroutineType(types: !45)
!45 = !{!9, !46, !46}
!46 = !DIBasicType(name: "int", size: 32)
!47 = !DILocation(line: 106, scope: !43)
!48 = !DILocation(line: 108, scope: !43)
!49 = !DILocation(line: 109, scope: !43)
!50 = !DILocation(line: 112, scope: !43)
!51 = !DILocation(line: 114, scope: !43)
!52 = !DILocation(line: 115, scope: !43)
!53 = !DILocation(line: 117, scope: !43)
!54 = !DILocation(line: 118, scope: !43)
!55 = !DILocation(line: 121, scope: !43)
!56 = !DILocation(line: 122, scope: !43)
!57 = !DILocation(line: 125, scope: !43)
!58 = !DILocation(line: 126, scope: !43)
!59 = !DILocation(line: 129, scope: !43)
!60 = !DILocation(line: 130, scope: !43)
!61 = !DILocation(line: 133, scope: !43)
!62 = !DILocation(line: 134, scope: !43)
!63 = !DILocation(line: 137, scope: !43)
!64 = !DILocation(line: 138, scope: !43)
!65 = !DILocation(line: 141, scope: !43)
!66 = !DILocation(line: 143, scope: !43)
!67 = !DILocation(line: 144, scope: !43)
!68 = !DILocation(line: 146, scope: !43)
!69 = distinct !DISubprogram(name: "char_length", linkageName: "char_length", scope: !6, file: !6, line: 149, type: !7, scopeLine: 149, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!70 = !DILocation(line: 149, scope: !69)
!71 = !DILocation(line: 151, scope: !69)
!72 = distinct !DISubprogram(name: "int_get_hash_key", linkageName: "int_get_hash_key", scope: !6, file: !6, line: 155, type: !73, scopeLine: 155, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!73 = !DISubroutineType(types: !74)
!74 = !{!46}
!75 = !DILocation(line: 155, scope: !72)
!76 = !DILocation(line: 157, scope: !72)
!77 = distinct !DISubprogram(name: "char_get_hash_key", linkageName: "char_get_hash_key", scope: !6, file: !6, line: 161, type: !7, scopeLine: 161, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!78 = !DILocation(line: 161, scope: !77)
!79 = !DILocation(line: 164, scope: !77)
!80 = !DILocation(line: 169, scope: !77)
!81 = !DILocation(line: 165, scope: !77)
!82 = !DILocation(line: 166, scope: !77)
!83 = !DILocation(line: 167, scope: !77)
!84 = distinct !DISubprogram(name: "char_equals", linkageName: "char_equals", scope: !6, file: !6, line: 172, type: !85, scopeLine: 172, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!85 = !DISubroutineType(types: !86)
!86 = !{!9, !9}
!87 = !DILocation(line: 172, scope: !84)
!88 = !DILocation(line: 174, scope: !84)
!89 = distinct !DISubprogram(name: "char_compare", linkageName: "char_compare", scope: !6, file: !6, line: 177, type: !90, scopeLine: 177, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!90 = !DISubroutineType(types: !91)
!91 = !{!46, !46}
!92 = !DILocation(line: 177, scope: !89)
!93 = !DILocation(line: 179, scope: !89)
!94 = !DILocation(line: 180, scope: !89)
!95 = !DILocation(line: 182, scope: !89)
!96 = !DILocation(line: 183, scope: !89)
!97 = !DILocation(line: 186, scope: !89)
!98 = distinct !DISubprogram(name: "buffer_initialize", linkageName: "buffer_initialize", scope: !6, file: !6, line: 1407, type: !7, scopeLine: 1407, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!99 = !DILocation(line: 1407, scope: !98)
!100 = !DILocation(line: 1409, scope: !98)
!101 = !DILocation(line: 1410, scope: !98)
!102 = !DILocation(line: 1412, scope: !98)
!103 = !DILocation(line: 1414, scope: !98)
!104 = distinct !DISubprogram(name: "buffer_length", linkageName: "buffer_length", scope: !6, file: !6, line: 1417, type: !7, scopeLine: 1417, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!105 = !DILocation(line: 1417, scope: !104)
!106 = !DILocation(line: 1419, scope: !104)
!107 = distinct !DISubprogram(name: "buffer_append", linkageName: "buffer_append", scope: !6, file: !6, line: 1422, type: !108, scopeLine: 1422, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!108 = !DISubroutineType(types: !109)
!109 = !{!9, !9, !110}
!110 = !DIBasicType(name: "long", size: 64)
!111 = !DILocation(line: 1422, scope: !107)
!112 = !DILocation(line: 1424, scope: !107)
!113 = !DILocation(line: 1425, scope: !107)
!114 = !DILocation(line: 1426, scope: !107)
!115 = !DILocation(line: 1427, scope: !107)
!116 = !DILocation(line: 1430, scope: !107)
!117 = !DILocation(line: 1431, scope: !107)
!118 = !DILocation(line: 1433, scope: !107)
!119 = distinct !DISubprogram(name: "buffer_append_char", linkageName: "buffer_append_char", scope: !6, file: !6, line: 1436, type: !120, scopeLine: 1436, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!120 = !DISubroutineType(types: !121)
!121 = !{!9, !122}
!122 = !DIBasicType(name: "char", size: 8)
!123 = !DILocation(line: 1436, scope: !119)
!124 = !DILocation(line: 1438, scope: !119)
!125 = !DILocation(line: 1439, scope: !119)
!126 = !DILocation(line: 1440, scope: !119)
!127 = !DILocation(line: 1441, scope: !119)
!128 = !DILocation(line: 1444, scope: !119)
!129 = !DILocation(line: 1445, scope: !119)
!130 = !DILocation(line: 1447, scope: !119)
!131 = distinct !DISubprogram(name: "buffer_append_str", linkageName: "buffer_append_str", scope: !6, file: !6, line: 1450, type: !85, scopeLine: 1450, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!132 = !DILocation(line: 1450, scope: !131)
!133 = !DILocation(line: 1452, scope: !131)
!134 = distinct !DISubprogram(name: "buffer_append_nullterminated_str", linkageName: "buffer_append_nullterminated_str", scope: !6, file: !6, line: 1455, type: !85, scopeLine: 1455, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!135 = !DILocation(line: 1455, scope: !134)
!136 = !DILocation(line: 1457, scope: !134)
!137 = !DILocation(line: 1458, scope: !134)
!138 = distinct !DISubprogram(name: "buffer_to_string", linkageName: "buffer_to_string", scope: !6, file: !6, line: 1461, type: !7, scopeLine: 1461, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!139 = !DILocation(line: 1461, scope: !138)
!140 = !DILocation(line: 1464, scope: !138)
!141 = distinct !DISubprogram(name: "buffer_append_int", linkageName: "buffer_append_int", scope: !6, file: !6, line: 1466, type: !142, scopeLine: 1466, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!142 = !DISubroutineType(types: !143)
!143 = !{!9, !46}
!144 = !DILocation(line: 1466, scope: !141)
!145 = !DILocation(line: 1468, scope: !141)
!146 = distinct !DISubprogram(name: "buffer_append_long", linkageName: "buffer_append_long", scope: !6, file: !6, line: 1471, type: !147, scopeLine: 1471, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!147 = !DISubroutineType(types: !148)
!148 = !{!9, !110}
!149 = !DILocation(line: 1471, scope: !146)
!150 = !DILocation(line: 1473, scope: !146)
!151 = distinct !DISubprogram(name: "buffer_append_short", linkageName: "buffer_append_short", scope: !6, file: !6, line: 1476, type: !152, scopeLine: 1476, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!152 = !DISubroutineType(types: !153)
!153 = !{!9, !154}
!154 = !DIBasicType(name: "short", size: 16)
!155 = !DILocation(line: 1476, scope: !151)
!156 = !DILocation(line: 1478, scope: !151)
!157 = distinct !DISubprogram(name: "buffer_alignment", linkageName: "buffer_alignment", scope: !6, file: !6, line: 1481, type: !7, scopeLine: 1481, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!158 = !DILocation(line: 1481, scope: !157)
!159 = !DILocation(line: 1483, scope: !157)
!160 = !DILocation(line: 1484, scope: !157)
!161 = !DILocation(line: 1486, scope: !157)
!162 = !DILocation(line: 1487, scope: !157)
!163 = !DILocation(line: 1488, scope: !157)
!164 = !DILocation(line: 1489, scope: !157)
!165 = !DILocation(line: 1492, scope: !157)
!166 = !DILocation(line: 1493, scope: !157)
!167 = !DILocation(line: 1496, scope: !157)
!168 = distinct !DISubprogram(name: "buffer_compare", linkageName: "buffer_compare", scope: !6, file: !6, line: 1499, type: !85, scopeLine: 1499, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!169 = !DILocation(line: 1499, scope: !168)
!170 = !DILocation(line: 1501, scope: !168)
!171 = distinct !DISubprogram(name: "char_to_buffer", linkageName: "char_to_buffer", scope: !6, file: !6, line: 1504, type: !7, scopeLine: 1504, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!172 = !DILocation(line: 1504, scope: !171)
!173 = !DILocation(line: 1506, scope: !171)
!174 = !DILocation(line: 1508, scope: !171)
!175 = !DILocation(line: 1510, scope: !171)
!176 = distinct !DISubprogram(name: "int_expect", linkageName: "int_expect", scope: !6, file: !6, line: 1514, type: !177, scopeLine: 1514, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!177 = !DISubroutineType(types: !178)
!178 = !{!46, !9, !9}
!179 = !DILocation(line: 1514, scope: !176)
!180 = !DILocation(line: 1516, scope: !176)
!181 = !DILocation(line: 1517, scope: !176)
!182 = !DILocation(line: 1520, scope: !176)
!183 = distinct !DISubprogram(name: "bool_expect", linkageName: "bool_expect", scope: !6, file: !6, line: 1523, type: !184, scopeLine: 1523, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!184 = !DISubroutineType(types: !185)
!185 = !{null, !9, !9}
!186 = !DILocation(line: 1523, scope: !183)
!187 = !DILocation(line: 1525, scope: !183)
!188 = !DILocation(line: 1526, scope: !183)
!189 = !DILocation(line: 1529, scope: !183)
!190 = distinct !DISubprogram(name: "int_times", linkageName: "int_times", scope: !6, file: !6, line: 1532, type: !177, scopeLine: 1532, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!191 = !DILocation(line: 1532, scope: !190)
!192 = !DILocation(line: 1535, scope: !190)
!193 = !DILocation(line: 1536, scope: !190)
!194 = distinct !DISubprogram(name: "xiswalpha", linkageName: "xiswalpha", scope: !6, file: !6, line: 1593, type: !73, scopeLine: 1593, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!195 = !DILocation(line: 1593, scope: !194)
!196 = !DILocation(line: 1595, scope: !194)
!197 = !DILocation(line: 1596, scope: !194)
!198 = distinct !DISubprogram(name: "xiswblank", linkageName: "xiswblank", scope: !6, file: !6, line: 1599, type: !73, scopeLine: 1599, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!199 = !DILocation(line: 1599, scope: !198)
!200 = !DILocation(line: 1601, scope: !198)
!201 = distinct !DISubprogram(name: "xiswdigit", linkageName: "xiswdigit", scope: !6, file: !6, line: 1604, type: !73, scopeLine: 1604, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!202 = !DILocation(line: 1604, scope: !201)
!203 = !DILocation(line: 1606, scope: !201)
!204 = distinct !DISubprogram(name: "xiswalnum", linkageName: "xiswalnum", scope: !6, file: !6, line: 1609, type: !73, scopeLine: 1609, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!205 = !DILocation(line: 1609, scope: !204)
!206 = !DILocation(line: 1611, scope: !204)
!207 = distinct !DISubprogram(name: "xisalpha", linkageName: "xisalpha", scope: !6, file: !6, line: 1614, type: !208, scopeLine: 1614, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!208 = !DISubroutineType(types: !209)
!209 = !{!122}
!210 = !DILocation(line: 1614, scope: !207)
!211 = !DILocation(line: 1616, scope: !207)
!212 = !DILocation(line: 1617, scope: !207)
!213 = distinct !DISubprogram(name: "xisblank", linkageName: "xisblank", scope: !6, file: !6, line: 1620, type: !208, scopeLine: 1620, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!214 = !DILocation(line: 1620, scope: !213)
!215 = !DILocation(line: 1622, scope: !213)
!216 = distinct !DISubprogram(name: "xisdigit", linkageName: "xisdigit", scope: !6, file: !6, line: 1625, type: !208, scopeLine: 1625, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!217 = !DILocation(line: 1625, scope: !216)
!218 = !DILocation(line: 1627, scope: !216)
!219 = distinct !DISubprogram(name: "xisalnum", linkageName: "xisalnum", scope: !6, file: !6, line: 1630, type: !208, scopeLine: 1630, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!220 = !DILocation(line: 1630, scope: !219)
!221 = !DILocation(line: 1632, scope: !219)
!222 = distinct !DISubprogram(name: "xbasename", linkageName: "xbasename", scope: !6, file: !6, line: 1635, type: !7, scopeLine: 1635, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!223 = !DILocation(line: 1635, scope: !222)
!224 = !DILocation(line: 1637, scope: !222)
!225 = !DILocation(line: 1648, scope: !222)
!226 = !DILocation(line: 1639, scope: !222)
!227 = !DILocation(line: 1640, scope: !222)
!228 = !DILocation(line: 1641, scope: !222)
!229 = !DILocation(line: 1644, scope: !222)
!230 = !DILocation(line: 1649, scope: !222)
!231 = !DILocation(line: 1652, scope: !222)
!232 = distinct !DISubprogram(name: "xextname", linkageName: "xextname", scope: !6, file: !6, line: 1656, type: !7, scopeLine: 1656, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!233 = !DILocation(line: 1656, scope: !232)
!234 = !DILocation(line: 1658, scope: !232)
!235 = !DILocation(line: 1669, scope: !232)
!236 = !DILocation(line: 1660, scope: !232)
!237 = !DILocation(line: 1661, scope: !232)
!238 = !DILocation(line: 1662, scope: !232)
!239 = !DILocation(line: 1665, scope: !232)
!240 = !DILocation(line: 1670, scope: !232)
!241 = !DILocation(line: 1673, scope: !232)
!242 = distinct !DISubprogram(name: "xrealpath", linkageName: "xrealpath", scope: !6, file: !6, line: 1677, type: !7, scopeLine: 1677, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!243 = !DILocation(line: 1677, scope: !242)
!244 = !DILocation(line: 1679, scope: !242)
!245 = !DILocation(line: 1681, scope: !242)
!246 = !DILocation(line: 1683, scope: !242)
!247 = !DILocation(line: 1685, scope: !242)
!248 = distinct !DISubprogram(name: "come_fd_zero", linkageName: "come_fd_zero", scope: !6, file: !6, line: 1690, type: !7, scopeLine: 1690, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!249 = !DILocation(line: 1690, scope: !248)
!250 = !DILocation(line: 1692, scope: !248)
!251 = distinct !DISubprogram(name: "come_fd_set", linkageName: "come_fd_set", scope: !6, file: !6, line: 1695, type: !252, scopeLine: 1695, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!252 = !DISubroutineType(types: !253)
!253 = !{!46, !9}
!254 = !DILocation(line: 1695, scope: !251)
!255 = !DILocation(line: 1697, scope: !251)
!256 = distinct !DISubprogram(name: "come_fd_isset", linkageName: "come_fd_isset", scope: !257, file: !257, line: 3, type: !252, scopeLine: 3, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!257 = !DIFile(filename: "src/common.h", directory: "/home/ab25cq/repo/neo-c2/yappy")
!258 = !DILocation(line: 3, scope: !256)
!259 = !DILocation(line: 1703, scope: !256)
!260 = distinct !DISubprogram(name: "exp_node_v10", linkageName: "exp_node_v10", scope: !1, file: !1, line: 55, type: !7, scopeLine: 55, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!261 = !DILocation(line: 55, scope: !260)
!262 = !DILocation(line: 59, scope: !260)
!263 = !DILocation(line: 60, scope: !260)
!264 = !DILocation(line: 61, scope: !260)
!265 = !DILocation(line: 64, scope: !260)
!266 = !DILocation(line: 102, scope: !260)
!267 = !DILocation(line: 103, scope: !260)
!268 = !DILocation(line: 104, scope: !260)
!269 = !DILocation(line: 106, scope: !260)
!270 = !DILocation(line: 108, scope: !260)
!271 = !DILocation(line: 109, scope: !260)
!272 = !DILocation(line: 110, scope: !260)
!273 = !DILocation(line: 112, scope: !260)
!274 = !DILocation(line: 115, scope: !260)
!275 = !DILocation(line: 65, scope: !260)
!276 = !DILocation(line: 66, scope: !260)
!277 = !DILocation(line: 69, scope: !260)
!278 = !DILocation(line: 71, scope: !260)
!279 = !DILocation(line: 72, scope: !260)
!280 = !DILocation(line: 73, scope: !260)
!281 = !DILocation(line: 76, scope: !260)
!282 = !DILocation(line: 77, scope: !260)
!283 = !DILocation(line: 80, scope: !260)
!284 = !DILocation(line: 84, scope: !260)
!285 = !DILocation(line: 85, scope: !260)
!286 = !DILocation(line: 86, scope: !260)
!287 = !DILocation(line: 88, scope: !260)
!288 = !DILocation(line: 100, scope: !260)
!289 = !DILocation(line: 89, scope: !260)
!290 = !DILocation(line: 90, scope: !260)
!291 = !DILocation(line: 93, scope: !260)
!292 = !DILocation(line: 94, scope: !260)
!293 = !DILocation(line: 97, scope: !260)
!294 = !DILocation(line: 116, scope: !260)
!295 = !DILocation(line: 119, scope: !260)
!296 = distinct !DISubprogram(name: "compile_v10", linkageName: "compile_v10", scope: !1, file: !1, line: 122, type: !297, scopeLine: 122, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!297 = !DISubroutineType(types: !298)
!298 = !{!9, !9, !9}
!299 = !DILocation(line: 122, scope: !296)
!300 = !DILocation(line: 124, scope: !296)
!301 = !DILocation(line: 126, scope: !296)
!302 = !DILocation(line: 127, scope: !296)
!303 = !DILocation(line: 128, scope: !296)
!304 = !DILocation(line: 129, scope: !296)
!305 = !DILocation(line: 131, scope: !296)
!306 = !DILocation(line: 133, scope: !296)
!307 = !DILocation(line: 134, scope: !296)
!308 = !DILocation(line: 136, scope: !296)
!309 = !DILocation(line: 137, scope: !296)
!310 = !DILocation(line: 139, scope: !296)
!311 = !DILocation(line: 141, scope: !296)
!312 = !DILocation(line: 184, scope: !296)
!313 = !DILocation(line: 185, scope: !296)
!314 = !DILocation(line: 197, scope: !296)
!315 = !DILocation(line: 198, scope: !296)
!316 = !DILocation(line: 207, scope: !296)
!317 = !DILocation(line: 142, scope: !296)
!318 = !DILocation(line: 145, scope: !296)
!319 = !DILocation(line: 147, scope: !296)
!320 = !DILocation(line: 148, scope: !296)
!321 = !DILocation(line: 150, scope: !296)
!322 = !DILocation(line: 152, scope: !296)
!323 = !DILocation(line: 154, scope: !296)
!324 = !DILocation(line: 156, scope: !296)
!325 = !DILocation(line: 158, scope: !296)
!326 = !DILocation(line: 159, scope: !296)
!327 = !DILocation(line: 161, scope: !296)
!328 = !DILocation(line: 163, scope: !296)
!329 = !DILocation(line: 164, scope: !296)
!330 = !DILocation(line: 166, scope: !296)
!331 = !DILocation(line: 167, scope: !296)
!332 = !DILocation(line: 169, scope: !296)
!333 = !DILocation(line: 170, scope: !296)
!334 = !DILocation(line: 173, scope: !296)
!335 = !DILocation(line: 174, scope: !296)
!336 = !DILocation(line: 176, scope: !296)
!337 = !DILocation(line: 178, scope: !296)
!338 = !DILocation(line: 181, scope: !296)
!339 = !DILocation(line: 182, scope: !296)
!340 = !DILocation(line: 186, scope: !296)
!341 = !DILocation(line: 187, scope: !296)
!342 = !DILocation(line: 190, scope: !296)
!343 = !DILocation(line: 192, scope: !296)
!344 = !DILocation(line: 193, scope: !296)
!345 = !DILocation(line: 195, scope: !296)
!346 = !DILocation(line: 199, scope: !296)
!347 = !DILocation(line: 200, scope: !296)
!348 = !DILocation(line: 203, scope: !296)
!349 = !DILocation(line: 204, scope: !296)
!350 = distinct !DISubprogram(name: "create_while", linkageName: "create_while", scope: !1, file: !1, line: 3, type: !351, scopeLine: 3, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!351 = !DISubroutineType(types: !352)
!352 = !{!9, !9, !9, !9}
!353 = !DILocation(line: 3, scope: !350)
!354 = !DILocation(line: 5, scope: !350)
!355 = !DILocation(line: 7, scope: !350)
!356 = !DILocation(line: 9, scope: !350)
!357 = !DILocation(line: 10, scope: !350)
!358 = !DILocation(line: 11, scope: !350)
!359 = !DILocation(line: 12, scope: !350)
!360 = !DILocation(line: 13, scope: !350)
!361 = !DILocation(line: 15, scope: !350)
!362 = distinct !DISubprogram(name: "create_continue", linkageName: "create_continue", scope: !1, file: !1, line: 18, type: !7, scopeLine: 18, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!363 = !DILocation(line: 18, scope: !362)
!364 = !DILocation(line: 20, scope: !362)
!365 = !DILocation(line: 22, scope: !362)
!366 = !DILocation(line: 24, scope: !362)
!367 = !DILocation(line: 25, scope: !362)
!368 = !DILocation(line: 27, scope: !362)
!369 = distinct !DISubprogram(name: "create_break", linkageName: "create_break", scope: !1, file: !1, line: 30, type: !7, scopeLine: 30, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!370 = !DILocation(line: 30, scope: !369)
!371 = !DILocation(line: 32, scope: !369)
!372 = !DILocation(line: 34, scope: !369)
!373 = !DILocation(line: 36, scope: !369)
!374 = !DILocation(line: 37, scope: !369)
!375 = !DILocation(line: 39, scope: !369)
!376 = distinct !DISubprogram(name: "word_cmp", linkageName: "word_cmp", scope: !1, file: !1, line: 42, type: !85, scopeLine: 42, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!377 = !DILocation(line: 42, scope: !376)
!378 = !DILocation(line: 44, scope: !376)
!379 = !DILocation(line: 46, scope: !376)
!380 = !DILocation(line: 48, scope: !376)
!381 = !DILocation(line: 49, scope: !376)
!382 = !DILocation(line: 52, scope: !376)
