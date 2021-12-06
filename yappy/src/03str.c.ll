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

define i1 @compile_v3(%sNode* %0, %buffer* %1, %sParserInfo* %2) !dbg !260 {
entry:
  %offset = alloca i32, align 4, !dbg !263
  %len = alloca i32, align 4, !dbg !263
  %str = alloca i8*, align 8, !dbg !263
  %node = alloca %sNode*, align 8, !dbg !263
  store %sNode* %0, %sNode** %node, align 8, !dbg !263
  %codes = alloca %buffer*, align 8, !dbg !263
  store %buffer* %1, %buffer** %codes, align 8, !dbg !263
  %info = alloca %sParserInfo*, align 8, !dbg !263
  store %sParserInfo* %2, %sParserInfo** %info, align 8, !dbg !263
  %node1 = load %sNode*, %sNode** %node, align 8, !dbg !264
  %codes2 = load %buffer*, %buffer** %codes, align 8, !dbg !264
  %info3 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !264
  %fun_result = call i1 @compile_v2(%sNode* %node1, %buffer* %codes2, %sParserInfo* %info3), !dbg !264
  %node4 = load %sNode*, %sNode** %node, align 8, !dbg !265
  %field = getelementptr inbounds %sNode, %sNode* %node4, i32 0, i32 0, !dbg !265
  %kind = load i32, i32* %field, align 4, !dbg !265
  %eq = icmp eq i32 %kind, 3, !dbg !265
  br i1 %eq, label %cond_jump_then, label %cond_end, !dbg !265

cond_jump_then:                                   ; preds = %entry
  %codes5 = load %buffer*, %buffer** %codes, align 8, !dbg !266
  call void @buffer_append_int(%buffer* %codes5, i32 4), !dbg !266
  %node6 = load %sNode*, %sNode** %node, align 8, !dbg !267
  %field7 = getelementptr inbounds %sNode, %sNode* %node6, i32 0, i32 3, !dbg !267
  %value = load %come_anon75, %come_anon75* %field7, align 8, !dbg !267
  %field8 = getelementptr inbounds %come_anon75, %come_anon75* %field7, i32 0, i32 0, !dbg !267
  %icastO = bitcast %come_anon81* %field8 to i8**, !dbg !267
  %stringValue = load i8*, i8** %icastO, align 8, !dbg !267
  store i8* %stringValue, i8** %str, align 8, !dbg !263
  %str9 = load i8*, i8** %str, align 8, !dbg !268
  %fun_result10 = call i64 @strlen(i8* %str9), !dbg !268
  %icastM = trunc i64 %fun_result10 to i32, !dbg !268
  store i32 %icastM, i32* %len, align 4, !dbg !263
  %len11 = load i32, i32* %len, align 4, !dbg !269
  %add = add i32 %len11, 3, !dbg !269
  %andtmp = and i32 %add, -4, !dbg !269
  store i32 %andtmp, i32* %offset, align 4, !dbg !263
  %offset12 = load i32, i32* %offset, align 4, !dbg !270
  %div = sdiv i32 %offset12, 4, !dbg !270
  store i32 %div, i32* %offset, align 4, !dbg !270
  %codes13 = load %buffer*, %buffer** %codes, align 8, !dbg !271
  %offset14 = load i32, i32* %offset, align 4, !dbg !271
  call void @buffer_append_int(%buffer* %codes13, i32 %offset14), !dbg !271
  %codes15 = load %buffer*, %buffer** %codes, align 8, !dbg !272
  %str16 = load i8*, i8** %str, align 8, !dbg !272
  call void @buffer_append_str(%buffer* %codes15, i8* %str16), !dbg !272
  %codes17 = load %buffer*, %buffer** %codes, align 8, !dbg !273
  call void @buffer_alignment(%buffer* %codes17), !dbg !273
  %info18 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !274
  %info19 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !274
  %field20 = getelementptr inbounds %sParserInfo, %sParserInfo* %info19, i32 0, i32 3, !dbg !274
  %stack_num = load i32, i32* %field20, align 4, !dbg !274
  %add21 = add i32 %stack_num, 1, !dbg !274
  %field22 = getelementptr inbounds %sParserInfo, %sParserInfo* %info18, i32 0, i32 3, !dbg !274
  store i32 %add21, i32* %field22, align 4, !dbg !274
  %sub = sub i32 %add21, 1, !dbg !274
  br label %cond_end, !dbg !274

cond_end:                                         ; preds = %cond_jump_then, %entry
  ret i1 true, !dbg !275
}

define %sNode* @exp_node_v3(%sParserInfo* %0) !dbg !276 {
entry:
  %buf136 = alloca %buffer*, align 8, !dbg !277
  %buf = alloca %buffer*, align 8, !dbg !277
  %result = alloca %sNode*, align 8, !dbg !277
  %info = alloca %sParserInfo*, align 8, !dbg !277
  store %sParserInfo* %0, %sParserInfo** %info, align 8, !dbg !277
  %info1 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !278
  %fun_result = call %sNode* @exp_node_v1(%sParserInfo* %info1), !dbg !278
  store %sNode* %fun_result, %sNode** %result, align 8, !dbg !277
  %result2 = load %sNode*, %sNode** %result, align 8, !dbg !279
  %eq = icmp eq %sNode* %result2, null, !dbg !279
  br i1 %eq, label %cond_jump_then, label %cond_end, !dbg !279

cond_jump_then:                                   ; preds = %entry
  %info3 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !280
  %field = getelementptr inbounds %sParserInfo, %sParserInfo* %info3, i32 0, i32 0, !dbg !280
  %p = load i8*, i8** %field, align 8, !dbg !280
  %derefference_value = load i8, i8* %p, align 1, !dbg !280
  %eq4 = icmp eq i8 %derefference_value, 34, !dbg !280
  br i1 %eq4, label %cond_jump_then5, label %cond_jump_elif0, !dbg !280

cond_end:                                         ; preds = %cond_end6, %entry
  %result250 = load %sNode*, %sNode** %result, align 8, !dbg !281
  ret %sNode* %result250, !dbg !281

cond_jump_then5:                                  ; preds = %cond_jump_then
  %info7 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !282
  %info8 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !282
  %field9 = getelementptr inbounds %sParserInfo, %sParserInfo* %info8, i32 0, i32 0, !dbg !282
  %p10 = load i8*, i8** %field9, align 8, !dbg !282
  %ptrToIntC = ptrtoint i8* %p10 to i64, !dbg !282
  %add = add i64 %ptrToIntC, 1, !dbg !282
  %intToPtr = inttoptr i64 %add to i8*, !dbg !282
  %field11 = getelementptr inbounds %sParserInfo, %sParserInfo* %info7, i32 0, i32 0, !dbg !282
  store i8* %intToPtr, i8** %field11, align 8, !dbg !282
  %ptrToIntI = ptrtoint i8* %intToPtr to i64, !dbg !282
  %sub = sub i64 %ptrToIntI, 1, !dbg !282
  %iintToPtr = inttoptr i64 %sub to i8*, !dbg !282
  %fun_result12 = call i8* @GC_malloc(i64 16), !dbg !283
  %obj = bitcast i8* %fun_result12 to %buffer*, !dbg !283
  %fun_result13 = call %buffer* @buffer_initialize(%buffer* %obj), !dbg !283
  store %buffer* %fun_result13, %buffer** %buf, align 8, !dbg !277
  br label %loop_top_block, !dbg !284

cond_jump_elif0:                                  ; preds = %cond_jump_then
  %info117 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !285
  %field118 = getelementptr inbounds %sParserInfo, %sParserInfo* %info117, i32 0, i32 0, !dbg !285
  %p119 = load i8*, i8** %field118, align 8, !dbg !285
  %derefference_value120 = load i8, i8* %p119, align 1, !dbg !285
  %eq121 = icmp eq i8 %derefference_value120, 39, !dbg !285
  br i1 %eq121, label %cond_jump_elif_then0, label %cond_end6, !dbg !285

cond_jump_elif_then0:                             ; preds = %cond_jump_elif0
  %info122 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !286
  %info123 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !286
  %field124 = getelementptr inbounds %sParserInfo, %sParserInfo* %info123, i32 0, i32 0, !dbg !286
  %p125 = load i8*, i8** %field124, align 8, !dbg !286
  %ptrToIntC126 = ptrtoint i8* %p125 to i64, !dbg !286
  %add127 = add i64 %ptrToIntC126, 1, !dbg !286
  %intToPtr128 = inttoptr i64 %add127 to i8*, !dbg !286
  %field129 = getelementptr inbounds %sParserInfo, %sParserInfo* %info122, i32 0, i32 0, !dbg !286
  store i8* %intToPtr128, i8** %field129, align 8, !dbg !286
  %ptrToIntI130 = ptrtoint i8* %intToPtr128 to i64, !dbg !286
  %sub131 = sub i64 %ptrToIntI130, 1, !dbg !286
  %iintToPtr132 = inttoptr i64 %sub131 to i8*, !dbg !286
  %fun_result133 = call i8* @GC_malloc(i64 16), !dbg !287
  %obj134 = bitcast i8* %fun_result133 to %buffer*, !dbg !287
  %fun_result135 = call %buffer* @buffer_initialize(%buffer* %obj134), !dbg !287
  store %buffer* %fun_result135, %buffer** %buf136, align 8, !dbg !277
  br label %loop_top_block137, !dbg !288

cond_end6:                                        ; preds = %cond_jump_elif0
  br label %cond_end, !dbg !288

loop_top_block:                                   ; preds = %cond_end22, %cond_jump_then5
  br i1 true, label %cond_then_block, label %cond_end_block, !dbg !289

cond_then_block:                                  ; preds = %loop_top_block
  %info14 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !290
  %field15 = getelementptr inbounds %sParserInfo, %sParserInfo* %info14, i32 0, i32 0, !dbg !290
  %p16 = load i8*, i8** %field15, align 8, !dbg !290
  %derefference_value17 = load i8, i8* %p16, align 1, !dbg !290
  %eq18 = icmp eq i8 %derefference_value17, 0, !dbg !290
  br i1 %eq18, label %cond_jump_then19, label %cond_jump_elif020, !dbg !290

cond_end_block:                                   ; preds = %cond_jump_elif_then1, %loop_top_block
  %buf113 = load %buffer*, %buffer** %buf, align 8, !dbg !284
  %fun_result114 = call i8* @buffer_to_string(%buffer* %buf113), !dbg !284
  %info115 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !284
  %fun_result116 = call %sNode* @create_string_node(i8* %fun_result114, %sParserInfo* %info115), !dbg !284
  ret %sNode* %fun_result116, !dbg !284

cond_jump_then19:                                 ; preds = %cond_then_block
  %stderr = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !291
  %info23 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !291
  %field24 = getelementptr inbounds %sParserInfo, %sParserInfo* %info23, i32 0, i32 2, !dbg !291
  %fname = load i8*, i8** %field24, align 8, !dbg !291
  %info25 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !291
  %field26 = getelementptr inbounds %sParserInfo, %sParserInfo* %info25, i32 0, i32 1, !dbg !291
  %sline = load i32, i32* %field26, align 4, !dbg !291
  %fun_result27 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @"%s %d: the source end", i32 0, i32 0), i8* %fname, i32 %sline), !dbg !291
  ret %sNode* null, !dbg !292

cond_jump_elif020:                                ; preds = %cond_then_block
  %info28 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !293
  %field29 = getelementptr inbounds %sParserInfo, %sParserInfo* %info28, i32 0, i32 0, !dbg !293
  %p30 = load i8*, i8** %field29, align 8, !dbg !293
  %derefference_value31 = load i8, i8* %p30, align 1, !dbg !293
  %eq32 = icmp eq i8 %derefference_value31, 92, !dbg !293
  br i1 %eq32, label %cond_jump_elif_then021, label %cond_jump_elif1, !dbg !293

cond_jump_elif_then021:                           ; preds = %cond_jump_elif020
  %buf33 = load %buffer*, %buffer** %buf, align 8, !dbg !294
  %info34 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !294
  %field35 = getelementptr inbounds %sParserInfo, %sParserInfo* %info34, i32 0, i32 0, !dbg !294
  %p36 = load i8*, i8** %field35, align 8, !dbg !294
  %derefference_value37 = load i8, i8* %p36, align 1, !dbg !294
  call void @buffer_append_char(%buffer* %buf33, i8 %derefference_value37), !dbg !294
  %info38 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !295
  %info39 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !295
  %field40 = getelementptr inbounds %sParserInfo, %sParserInfo* %info39, i32 0, i32 0, !dbg !295
  %p41 = load i8*, i8** %field40, align 8, !dbg !295
  %ptrToIntC42 = ptrtoint i8* %p41 to i64, !dbg !295
  %add43 = add i64 %ptrToIntC42, 1, !dbg !295
  %intToPtr44 = inttoptr i64 %add43 to i8*, !dbg !295
  %field45 = getelementptr inbounds %sParserInfo, %sParserInfo* %info38, i32 0, i32 0, !dbg !295
  store i8* %intToPtr44, i8** %field45, align 8, !dbg !295
  %ptrToIntI46 = ptrtoint i8* %intToPtr44 to i64, !dbg !295
  %sub47 = sub i64 %ptrToIntI46, 1, !dbg !295
  %iintToPtr48 = inttoptr i64 %sub47 to i8*, !dbg !295
  %info49 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !296
  %field50 = getelementptr inbounds %sParserInfo, %sParserInfo* %info49, i32 0, i32 0, !dbg !296
  %p51 = load i8*, i8** %field50, align 8, !dbg !296
  %derefference_value52 = load i8, i8* %p51, align 1, !dbg !296
  %eq53 = icmp eq i8 %derefference_value52, 0, !dbg !296
  br i1 %eq53, label %cond_jump_then54, label %cond_end55, !dbg !296

cond_jump_elif1:                                  ; preds = %cond_jump_elif020
  %info80 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !297
  %field81 = getelementptr inbounds %sParserInfo, %sParserInfo* %info80, i32 0, i32 0, !dbg !297
  %p82 = load i8*, i8** %field81, align 8, !dbg !297
  %derefference_value83 = load i8, i8* %p82, align 1, !dbg !297
  %eq84 = icmp eq i8 %derefference_value83, 34, !dbg !297
  br i1 %eq84, label %cond_jump_elif_then1, label %cond_else_block, !dbg !297

cond_jump_elif_then1:                             ; preds = %cond_jump_elif1
  %info85 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !298
  %info86 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !298
  %field87 = getelementptr inbounds %sParserInfo, %sParserInfo* %info86, i32 0, i32 0, !dbg !298
  %p88 = load i8*, i8** %field87, align 8, !dbg !298
  %ptrToIntC89 = ptrtoint i8* %p88 to i64, !dbg !298
  %add90 = add i64 %ptrToIntC89, 1, !dbg !298
  %intToPtr91 = inttoptr i64 %add90 to i8*, !dbg !298
  %field92 = getelementptr inbounds %sParserInfo, %sParserInfo* %info85, i32 0, i32 0, !dbg !298
  store i8* %intToPtr91, i8** %field92, align 8, !dbg !298
  %ptrToIntI93 = ptrtoint i8* %intToPtr91 to i64, !dbg !298
  %sub94 = sub i64 %ptrToIntI93, 1, !dbg !298
  %iintToPtr95 = inttoptr i64 %sub94 to i8*, !dbg !298
  %info96 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !298
  call void @skip_spaces_until_eol(%sParserInfo* %info96), !dbg !298
  br label %cond_end_block, !dbg !299

cond_else_block:                                  ; preds = %cond_jump_elif1
  %buf97 = load %buffer*, %buffer** %buf, align 8, !dbg !300
  %info98 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !300
  %field99 = getelementptr inbounds %sParserInfo, %sParserInfo* %info98, i32 0, i32 0, !dbg !300
  %p100 = load i8*, i8** %field99, align 8, !dbg !300
  %derefference_value101 = load i8, i8* %p100, align 1, !dbg !300
  call void @buffer_append_char(%buffer* %buf97, i8 %derefference_value101), !dbg !300
  %info102 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !301
  %info103 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !301
  %field104 = getelementptr inbounds %sParserInfo, %sParserInfo* %info103, i32 0, i32 0, !dbg !301
  %p105 = load i8*, i8** %field104, align 8, !dbg !301
  %ptrToIntC106 = ptrtoint i8* %p105 to i64, !dbg !301
  %add107 = add i64 %ptrToIntC106, 1, !dbg !301
  %intToPtr108 = inttoptr i64 %add107 to i8*, !dbg !301
  %field109 = getelementptr inbounds %sParserInfo, %sParserInfo* %info102, i32 0, i32 0, !dbg !301
  store i8* %intToPtr108, i8** %field109, align 8, !dbg !301
  %ptrToIntI110 = ptrtoint i8* %intToPtr108 to i64, !dbg !301
  %sub111 = sub i64 %ptrToIntI110, 1, !dbg !301
  %iintToPtr112 = inttoptr i64 %sub111 to i8*, !dbg !301
  br label %cond_end22, !dbg !301

cond_end22:                                       ; preds = %cond_else_block, %after_break, %cond_end55
  br label %loop_top_block, !dbg !301

cond_jump_then54:                                 ; preds = %cond_jump_elif_then021
  %stderr56 = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !302
  %info57 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !302
  %field58 = getelementptr inbounds %sParserInfo, %sParserInfo* %info57, i32 0, i32 2, !dbg !302
  %fname59 = load i8*, i8** %field58, align 8, !dbg !302
  %info60 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !302
  %field61 = getelementptr inbounds %sParserInfo, %sParserInfo* %info60, i32 0, i32 1, !dbg !302
  %sline62 = load i32, i32* %field61, align 4, !dbg !302
  %fun_result63 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr56, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @"%s %d: the source end.1", i32 0, i32 0), i8* %fname59, i32 %sline62), !dbg !302
  ret %sNode* null, !dbg !303

cond_end55:                                       ; preds = %cond_jump_elif_then021
  %buf64 = load %buffer*, %buffer** %buf, align 8, !dbg !304
  %info65 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !304
  %field66 = getelementptr inbounds %sParserInfo, %sParserInfo* %info65, i32 0, i32 0, !dbg !304
  %p67 = load i8*, i8** %field66, align 8, !dbg !304
  %derefference_value68 = load i8, i8* %p67, align 1, !dbg !304
  call void @buffer_append_char(%buffer* %buf64, i8 %derefference_value68), !dbg !304
  %info69 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !305
  %info70 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !305
  %field71 = getelementptr inbounds %sParserInfo, %sParserInfo* %info70, i32 0, i32 0, !dbg !305
  %p72 = load i8*, i8** %field71, align 8, !dbg !305
  %ptrToIntC73 = ptrtoint i8* %p72 to i64, !dbg !305
  %add74 = add i64 %ptrToIntC73, 1, !dbg !305
  %intToPtr75 = inttoptr i64 %add74 to i8*, !dbg !305
  %field76 = getelementptr inbounds %sParserInfo, %sParserInfo* %info69, i32 0, i32 0, !dbg !305
  store i8* %intToPtr75, i8** %field76, align 8, !dbg !305
  %ptrToIntI77 = ptrtoint i8* %intToPtr75 to i64, !dbg !305
  %sub78 = sub i64 %ptrToIntI77, 1, !dbg !305
  %iintToPtr79 = inttoptr i64 %sub78 to i8*, !dbg !305
  br label %cond_end22, !dbg !305

after_break:                                      ; No predecessors!
  br label %cond_end22, !dbg !299

loop_top_block137:                                ; preds = %cond_end151, %cond_jump_elif_then0
  br i1 true, label %cond_then_block138, label %cond_end_block139, !dbg !306

cond_then_block138:                               ; preds = %loop_top_block137
  %info140 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !307
  %field141 = getelementptr inbounds %sParserInfo, %sParserInfo* %info140, i32 0, i32 0, !dbg !307
  %p142 = load i8*, i8** %field141, align 8, !dbg !307
  %derefference_value143 = load i8, i8* %p142, align 1, !dbg !307
  %eq144 = icmp eq i8 %derefference_value143, 0, !dbg !307
  br i1 %eq144, label %cond_jump_then145, label %cond_jump_elif0146, !dbg !307

cond_end_block139:                                ; preds = %cond_jump_elif_then1149, %loop_top_block137
  %buf246 = load %buffer*, %buffer** %buf136, align 8, !dbg !288
  %fun_result247 = call i8* @buffer_to_string(%buffer* %buf246), !dbg !288
  %info248 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !288
  %fun_result249 = call %sNode* @create_string_node(i8* %fun_result247, %sParserInfo* %info248), !dbg !288
  ret %sNode* %fun_result249, !dbg !288

cond_jump_then145:                                ; preds = %cond_then_block138
  %stderr152 = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !308
  %info153 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !308
  %field154 = getelementptr inbounds %sParserInfo, %sParserInfo* %info153, i32 0, i32 2, !dbg !308
  %fname155 = load i8*, i8** %field154, align 8, !dbg !308
  %info156 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !308
  %field157 = getelementptr inbounds %sParserInfo, %sParserInfo* %info156, i32 0, i32 1, !dbg !308
  %sline158 = load i32, i32* %field157, align 4, !dbg !308
  %fun_result159 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr152, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @"%s %d: the source end.2", i32 0, i32 0), i8* %fname155, i32 %sline158), !dbg !308
  ret %sNode* null, !dbg !309

cond_jump_elif0146:                               ; preds = %cond_then_block138
  %info160 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !310
  %field161 = getelementptr inbounds %sParserInfo, %sParserInfo* %info160, i32 0, i32 0, !dbg !310
  %p162 = load i8*, i8** %field161, align 8, !dbg !310
  %derefference_value163 = load i8, i8* %p162, align 1, !dbg !310
  %eq164 = icmp eq i8 %derefference_value163, 92, !dbg !310
  br i1 %eq164, label %cond_jump_elif_then0147, label %cond_jump_elif1148, !dbg !310

cond_jump_elif_then0147:                          ; preds = %cond_jump_elif0146
  %buf165 = load %buffer*, %buffer** %buf136, align 8, !dbg !311
  %info166 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !311
  %field167 = getelementptr inbounds %sParserInfo, %sParserInfo* %info166, i32 0, i32 0, !dbg !311
  %p168 = load i8*, i8** %field167, align 8, !dbg !311
  %derefference_value169 = load i8, i8* %p168, align 1, !dbg !311
  call void @buffer_append_char(%buffer* %buf165, i8 %derefference_value169), !dbg !311
  %info170 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !312
  %info171 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !312
  %field172 = getelementptr inbounds %sParserInfo, %sParserInfo* %info171, i32 0, i32 0, !dbg !312
  %p173 = load i8*, i8** %field172, align 8, !dbg !312
  %ptrToIntC174 = ptrtoint i8* %p173 to i64, !dbg !312
  %add175 = add i64 %ptrToIntC174, 1, !dbg !312
  %intToPtr176 = inttoptr i64 %add175 to i8*, !dbg !312
  %field177 = getelementptr inbounds %sParserInfo, %sParserInfo* %info170, i32 0, i32 0, !dbg !312
  store i8* %intToPtr176, i8** %field177, align 8, !dbg !312
  %ptrToIntI178 = ptrtoint i8* %intToPtr176 to i64, !dbg !312
  %sub179 = sub i64 %ptrToIntI178, 1, !dbg !312
  %iintToPtr180 = inttoptr i64 %sub179 to i8*, !dbg !312
  %info181 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !313
  %field182 = getelementptr inbounds %sParserInfo, %sParserInfo* %info181, i32 0, i32 0, !dbg !313
  %p183 = load i8*, i8** %field182, align 8, !dbg !313
  %derefference_value184 = load i8, i8* %p183, align 1, !dbg !313
  %eq185 = icmp eq i8 %derefference_value184, 0, !dbg !313
  br i1 %eq185, label %cond_jump_then186, label %cond_end187, !dbg !313

cond_jump_elif1148:                               ; preds = %cond_jump_elif0146
  %info212 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !314
  %field213 = getelementptr inbounds %sParserInfo, %sParserInfo* %info212, i32 0, i32 0, !dbg !314
  %p214 = load i8*, i8** %field213, align 8, !dbg !314
  %derefference_value215 = load i8, i8* %p214, align 1, !dbg !314
  %eq216 = icmp eq i8 %derefference_value215, 39, !dbg !314
  br i1 %eq216, label %cond_jump_elif_then1149, label %cond_else_block150, !dbg !314

cond_jump_elif_then1149:                          ; preds = %cond_jump_elif1148
  %info217 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !315
  %info218 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !315
  %field219 = getelementptr inbounds %sParserInfo, %sParserInfo* %info218, i32 0, i32 0, !dbg !315
  %p220 = load i8*, i8** %field219, align 8, !dbg !315
  %ptrToIntC221 = ptrtoint i8* %p220 to i64, !dbg !315
  %add222 = add i64 %ptrToIntC221, 1, !dbg !315
  %intToPtr223 = inttoptr i64 %add222 to i8*, !dbg !315
  %field224 = getelementptr inbounds %sParserInfo, %sParserInfo* %info217, i32 0, i32 0, !dbg !315
  store i8* %intToPtr223, i8** %field224, align 8, !dbg !315
  %ptrToIntI225 = ptrtoint i8* %intToPtr223 to i64, !dbg !315
  %sub226 = sub i64 %ptrToIntI225, 1, !dbg !315
  %iintToPtr227 = inttoptr i64 %sub226 to i8*, !dbg !315
  %info228 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !315
  call void @skip_spaces_until_eol(%sParserInfo* %info228), !dbg !315
  br label %cond_end_block139, !dbg !316

cond_else_block150:                               ; preds = %cond_jump_elif1148
  %buf230 = load %buffer*, %buffer** %buf136, align 8, !dbg !317
  %info231 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !317
  %field232 = getelementptr inbounds %sParserInfo, %sParserInfo* %info231, i32 0, i32 0, !dbg !317
  %p233 = load i8*, i8** %field232, align 8, !dbg !317
  %derefference_value234 = load i8, i8* %p233, align 1, !dbg !317
  call void @buffer_append_char(%buffer* %buf230, i8 %derefference_value234), !dbg !317
  %info235 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !318
  %info236 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !318
  %field237 = getelementptr inbounds %sParserInfo, %sParserInfo* %info236, i32 0, i32 0, !dbg !318
  %p238 = load i8*, i8** %field237, align 8, !dbg !318
  %ptrToIntC239 = ptrtoint i8* %p238 to i64, !dbg !318
  %add240 = add i64 %ptrToIntC239, 1, !dbg !318
  %intToPtr241 = inttoptr i64 %add240 to i8*, !dbg !318
  %field242 = getelementptr inbounds %sParserInfo, %sParserInfo* %info235, i32 0, i32 0, !dbg !318
  store i8* %intToPtr241, i8** %field242, align 8, !dbg !318
  %ptrToIntI243 = ptrtoint i8* %intToPtr241 to i64, !dbg !318
  %sub244 = sub i64 %ptrToIntI243, 1, !dbg !318
  %iintToPtr245 = inttoptr i64 %sub244 to i8*, !dbg !318
  br label %cond_end151, !dbg !318

cond_end151:                                      ; preds = %cond_else_block150, %after_break229, %cond_end187
  br label %loop_top_block137, !dbg !318

cond_jump_then186:                                ; preds = %cond_jump_elif_then0147
  %stderr188 = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !319
  %info189 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !319
  %field190 = getelementptr inbounds %sParserInfo, %sParserInfo* %info189, i32 0, i32 2, !dbg !319
  %fname191 = load i8*, i8** %field190, align 8, !dbg !319
  %info192 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !319
  %field193 = getelementptr inbounds %sParserInfo, %sParserInfo* %info192, i32 0, i32 1, !dbg !319
  %sline194 = load i32, i32* %field193, align 4, !dbg !319
  %fun_result195 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr188, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @"%s %d: the source end.3", i32 0, i32 0), i8* %fname191, i32 %sline194), !dbg !319
  ret %sNode* null, !dbg !320

cond_end187:                                      ; preds = %cond_jump_elif_then0147
  %buf196 = load %buffer*, %buffer** %buf136, align 8, !dbg !321
  %info197 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !321
  %field198 = getelementptr inbounds %sParserInfo, %sParserInfo* %info197, i32 0, i32 0, !dbg !321
  %p199 = load i8*, i8** %field198, align 8, !dbg !321
  %derefference_value200 = load i8, i8* %p199, align 1, !dbg !321
  call void @buffer_append_char(%buffer* %buf196, i8 %derefference_value200), !dbg !321
  %info201 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !322
  %info202 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !322
  %field203 = getelementptr inbounds %sParserInfo, %sParserInfo* %info202, i32 0, i32 0, !dbg !322
  %p204 = load i8*, i8** %field203, align 8, !dbg !322
  %ptrToIntC205 = ptrtoint i8* %p204 to i64, !dbg !322
  %add206 = add i64 %ptrToIntC205, 1, !dbg !322
  %intToPtr207 = inttoptr i64 %add206 to i8*, !dbg !322
  %field208 = getelementptr inbounds %sParserInfo, %sParserInfo* %info201, i32 0, i32 0, !dbg !322
  store i8* %intToPtr207, i8** %field208, align 8, !dbg !322
  %ptrToIntI209 = ptrtoint i8* %intToPtr207 to i64, !dbg !322
  %sub210 = sub i64 %ptrToIntI209, 1, !dbg !322
  %iintToPtr211 = inttoptr i64 %sub210 to i8*, !dbg !322
  br label %cond_end151, !dbg !322

after_break229:                                   ; No predecessors!
  br label %cond_end151, !dbg !316
}

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

declare %sNode* @exp_node_v10(%sParserInfo*)

declare i1 @compile_v10(%sNode*, %buffer*, %sParserInfo*)

declare i1 @expression_v11(%sNode**, %sParserInfo*)

declare i1 @compile_v11(%sNode*, %buffer*, %sParserInfo*)

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

declare i32 @isctype(i32, i32)

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

define internal %sNode* @create_string_node(i8* %0, %sParserInfo* %1) !dbg !323 {
entry:
  %result18 = alloca i8*, align 8, !dbg !324
  %len = alloca i32, align 4, !dbg !324
  %result = alloca %sNode*, align 8, !dbg !324
  %str = alloca i8*, align 8, !dbg !324
  store i8* %0, i8** %str, align 8, !dbg !324
  %info = alloca %sParserInfo*, align 8, !dbg !324
  store %sParserInfo* %1, %sParserInfo** %info, align 8, !dbg !324
  %fun_result = call i8* @GC_malloc(i64 64), !dbg !325
  %obj = bitcast i8* %fun_result to %sNode*, !dbg !325
  store %sNode* %obj, %sNode** %result, align 8, !dbg !324
  %result1 = load %sNode*, %sNode** %result, align 8, !dbg !326
  %field = getelementptr inbounds %sNode, %sNode* %result1, i32 0, i32 0, !dbg !326
  store i32 3, i32* %field, align 4, !dbg !326
  %result2 = load %sNode*, %sNode** %result, align 8, !dbg !327
  %info3 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !327
  %field4 = getelementptr inbounds %sParserInfo, %sParserInfo* %info3, i32 0, i32 2, !dbg !327
  %fname = load i8*, i8** %field4, align 8, !dbg !327
  %field5 = getelementptr inbounds %sNode, %sNode* %result2, i32 0, i32 1, !dbg !327
  store i8* %fname, i8** %field5, align 8, !dbg !327
  %result6 = load %sNode*, %sNode** %result, align 8, !dbg !328
  %info7 = load %sParserInfo*, %sParserInfo** %info, align 8, !dbg !328
  %field8 = getelementptr inbounds %sParserInfo, %sParserInfo* %info7, i32 0, i32 1, !dbg !328
  %sline = load i32, i32* %field8, align 4, !dbg !328
  %field9 = getelementptr inbounds %sNode, %sNode* %result6, i32 0, i32 2, !dbg !328
  store i32 %sline, i32* %field9, align 4, !dbg !328
  %result10 = load %sNode*, %sNode** %result, align 8, !dbg !329
  %field11 = getelementptr inbounds %sNode, %sNode* %result10, i32 0, i32 3, !dbg !329
  %value = load %come_anon75, %come_anon75* %field11, align 8, !dbg !329
  %str12 = load i8*, i8** %str, align 8, !dbg !329
  br label %string, !dbg !329

string:                                           ; preds = %entry
  %inline_result_variable = alloca i8*, align 8, !dbg !329
  %str13 = alloca i8*, align 8, !dbg !329
  store i8* %str12, i8** %str13, align 8, !dbg !329
  %str14 = load i8*, i8** %str13, align 8, !dbg !329
  %fun_result15 = call i64 @strlen(i8* %str14), !dbg !329
  %add = add i64 %fun_result15, 1, !dbg !329
  %icastM = trunc i64 %add to i32, !dbg !329
  store i32 %icastM, i32* %len, align 4, !dbg !324
  %len16 = load i32, i32* %len, align 4, !dbg !324
  %icastD = sext i32 %len16 to i64, !dbg !324
  %mul = mul i64 1, %icastD, !dbg !324
  %fun_result17 = call i8* @GC_malloc(i64 %mul), !dbg !324
  store i8* %fun_result17, i8** %result18, align 8, !dbg !324
  %result19 = load i8*, i8** %result18, align 8, !dbg !324
  %str20 = load i8*, i8** %str13, align 8, !dbg !324
  %len21 = load i32, i32* %len, align 4, !dbg !324
  %icastD22 = sext i32 %len21 to i64, !dbg !324
  %fun_result23 = call i8* @strncpy(i8* %result19, i8* %str20, i64 %icastD22), !dbg !324
  %result24 = load i8*, i8** %result18, align 8, !dbg !324
  store i8* %result24, i8** %inline_result_variable, align 8, !dbg !324
  br label %string_end, !dbg !324

string_end:                                       ; preds = %string
  %inline_result_variable25 = load i8*, i8** %inline_result_variable, align 8, !dbg !324
  %field26 = getelementptr inbounds %come_anon75, %come_anon75* %field11, i32 0, i32 0, !dbg !324
  %icastN = bitcast %come_anon81* %field26 to i8**, !dbg !324
  store i8* %inline_result_variable25, i8** %icastN, align 8, !dbg !324
  %result27 = load %sNode*, %sNode** %result, align 8, !dbg !330
  ret %sNode* %result27, !dbg !330
}

attributes #0 = { nounwind }
attributes #1 = { nounwind willreturn }
attributes #2 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "come", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false)
!1 = !DIFile(filename: "src/03str.c", directory: "/home/ab25cq/repo/neo-c2/yappy")
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
!260 = distinct !DISubprogram(name: "compile_v3", linkageName: "compile_v3", scope: !1, file: !1, line: 97, type: !261, scopeLine: 97, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!261 = !DISubroutineType(types: !262)
!262 = !{!9, !9, !9}
!263 = !DILocation(line: 97, scope: !260)
!264 = !DILocation(line: 99, scope: !260)
!265 = !DILocation(line: 101, scope: !260)
!266 = !DILocation(line: 102, scope: !260)
!267 = !DILocation(line: 104, scope: !260)
!268 = !DILocation(line: 106, scope: !260)
!269 = !DILocation(line: 107, scope: !260)
!270 = !DILocation(line: 108, scope: !260)
!271 = !DILocation(line: 110, scope: !260)
!272 = !DILocation(line: 111, scope: !260)
!273 = !DILocation(line: 112, scope: !260)
!274 = !DILocation(line: 114, scope: !260)
!275 = !DILocation(line: 117, scope: !260)
!276 = distinct !DISubprogram(name: "exp_node_v3", linkageName: "exp_node_v3", scope: !1, file: !1, line: 17, type: !7, scopeLine: 17, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!277 = !DILocation(line: 17, scope: !276)
!278 = !DILocation(line: 19, scope: !276)
!279 = !DILocation(line: 21, scope: !276)
!280 = !DILocation(line: 22, scope: !276)
!281 = !DILocation(line: 94, scope: !276)
!282 = !DILocation(line: 23, scope: !276)
!283 = !DILocation(line: 25, scope: !276)
!284 = !DILocation(line: 55, scope: !276)
!285 = !DILocation(line: 57, scope: !276)
!286 = !DILocation(line: 58, scope: !276)
!287 = !DILocation(line: 60, scope: !276)
!288 = !DILocation(line: 90, scope: !276)
!289 = !DILocation(line: 27, scope: !276)
!290 = !DILocation(line: 28, scope: !276)
!291 = !DILocation(line: 29, scope: !276)
!292 = !DILocation(line: 30, scope: !276)
!293 = !DILocation(line: 32, scope: !276)
!294 = !DILocation(line: 33, scope: !276)
!295 = !DILocation(line: 34, scope: !276)
!296 = !DILocation(line: 36, scope: !276)
!297 = !DILocation(line: 44, scope: !276)
!298 = !DILocation(line: 46, scope: !276)
!299 = !DILocation(line: 47, scope: !276)
!300 = !DILocation(line: 50, scope: !276)
!301 = !DILocation(line: 51, scope: !276)
!302 = !DILocation(line: 37, scope: !276)
!303 = !DILocation(line: 38, scope: !276)
!304 = !DILocation(line: 41, scope: !276)
!305 = !DILocation(line: 42, scope: !276)
!306 = !DILocation(line: 62, scope: !276)
!307 = !DILocation(line: 63, scope: !276)
!308 = !DILocation(line: 64, scope: !276)
!309 = !DILocation(line: 65, scope: !276)
!310 = !DILocation(line: 67, scope: !276)
!311 = !DILocation(line: 68, scope: !276)
!312 = !DILocation(line: 69, scope: !276)
!313 = !DILocation(line: 71, scope: !276)
!314 = !DILocation(line: 79, scope: !276)
!315 = !DILocation(line: 81, scope: !276)
!316 = !DILocation(line: 82, scope: !276)
!317 = !DILocation(line: 85, scope: !276)
!318 = !DILocation(line: 86, scope: !276)
!319 = !DILocation(line: 72, scope: !276)
!320 = !DILocation(line: 73, scope: !276)
!321 = !DILocation(line: 76, scope: !276)
!322 = !DILocation(line: 77, scope: !276)
!323 = distinct !DISubprogram(name: "create_string_node", linkageName: "create_string_node", scope: !1, file: !1, line: 4, type: !85, scopeLine: 4, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!324 = !DILocation(line: 4, scope: !323)
!325 = !DILocation(line: 6, scope: !323)
!326 = !DILocation(line: 8, scope: !323)
!327 = !DILocation(line: 10, scope: !323)
!328 = !DILocation(line: 11, scope: !323)
!329 = !DILocation(line: 12, scope: !323)
!330 = !DILocation(line: 14, scope: !323)
