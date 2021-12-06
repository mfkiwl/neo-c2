; ModuleID = 'src/vm.c'
source_filename = "src/vm.c"

%_IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %_IO_marker*, %_IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, %_IO_codecvt*, %_IO_wide_data*, %_IO_FILE*, i8*, i64, i32, [20 x i8] }
%_IO_marker = type opaque
%_IO_codecvt = type opaque
%_IO_wide_data = type opaque
%map_charp_ZVALUE = type { i8**, i1*, %ZVALUE*, i32, i32, i32 }
%ZVALUE = type { i32, %come_anon86 }
%come_anon86 = type { i64 }
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
@gGlobalVar = global %map_charp_ZVALUE* null, align 4
@gNullValue = global %ZVALUE zeroinitializer
@"int value %d\0A" = private unnamed_addr constant [14 x i8] c"int value %d\0A\00", align 1
@"string value %s\0A" = private unnamed_addr constant [17 x i8] c"string value %s\0A\00", align 1
@OP_POP = private unnamed_addr constant [7 x i8] c"OP_POP\00", align 1
@OP_INT_VALUE = private unnamed_addr constant [13 x i8] c"OP_INT_VALUE\00", align 1
@OP_ADD = private unnamed_addr constant [7 x i8] c"OP_ADD\00", align 1
@OP_SUB = private unnamed_addr constant [7 x i8] c"OP_SUB\00", align 1
@OP_STRING_VALUE = private unnamed_addr constant [16 x i8] c"OP_STRING_VALUE\00", align 1
@OP_PRINT = private unnamed_addr constant [9 x i8] c"OP_PRINT\00", align 1
@OP_LOAD = private unnamed_addr constant [8 x i8] c"OP_LOAD\00", align 1
@OP_STORE = private unnamed_addr constant [9 x i8] c"OP_STORE\00", align 1
@OP_FUNCALL = private unnamed_addr constant [11 x i8] c"OP_FUNCALL\00", align 1
@OP_BOOL_VALUE = private unnamed_addr constant [14 x i8] c"OP_BOOL_VALUE\00", align 1
@OP_GOTO = private unnamed_addr constant [8 x i8] c"OP_GOTO\00", align 1
@OP_IF = private unnamed_addr constant [6 x i8] c"OP_IF\00", align 1
@"invalid op code %d\0A" = private unnamed_addr constant [20 x i8] c"invalid op code %d\0A\00", align 1
@"unexpected error in map.rehash(1)\0A" = private unnamed_addr constant [35 x i8] c"unexpected error in map.rehash(1)\0A\00", align 1
@"unexpected error in map.insert\0A" = private unnamed_addr constant [32 x i8] c"unexpected error in map.insert\0A\00", align 1
@"%d\0A" = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@true = private unnamed_addr constant [5 x i8] c"true\00", align 1
@false = private unnamed_addr constant [6 x i8] c"false\00", align 1
@"var not found(%s)\0A" = private unnamed_addr constant [19 x i8] c"var not found(%s)\0A\00", align 1
@"var not found(%s)\0A.1" = private unnamed_addr constant [19 x i8] c"var not found(%s)\0A\00", align 1
@"invalid op code %d\0A.2" = private unnamed_addr constant [20 x i8] c"invalid op code %d\0A\00", align 1
@"invalid stack num\0A" = private unnamed_addr constant [19 x i8] c"invalid stack num\0A\00", align 1

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

define void @initialize_modules_v1() !dbg !260 {
entry:
  %fun_result = call i8* @GC_malloc(i64 40), !dbg !262
  %obj = bitcast i8* %fun_result to %map_charp_ZVALUE*, !dbg !262
  %fun_result1 = call %map_charp_ZVALUE* @map_initialize_charp_ZVALUE(%map_charp_ZVALUE* %obj), !dbg !262
  store %map_charp_ZVALUE* %fun_result1, %map_charp_ZVALUE** @gGlobalVar, align 8, !dbg !262
  %gNullValue = load %ZVALUE, %ZVALUE* @gNullValue, align 4, !dbg !263
  store i32 5, i32* getelementptr inbounds (%ZVALUE, %ZVALUE* @gNullValue, i32 0, i32 0), align 4, !dbg !263
  %gNullValue2 = load %ZVALUE, %ZVALUE* @gNullValue, align 4, !dbg !264
  %gNullValue3 = load %ZVALUE, %ZVALUE* @gNullValue, align 4, !dbg !264
  %value = load %come_anon86, %come_anon86* getelementptr inbounds (%ZVALUE, %ZVALUE* @gNullValue, i32 0, i32 1), align 4, !dbg !264
  store i8* null, i8** bitcast (i64* getelementptr inbounds (%ZVALUE, %ZVALUE* @gNullValue, i32 0, i32 1, i32 0) to i8**), align 8, !dbg !264
  ret void, !dbg !264
}

define void @finalize_modules_v1() {
entry:
  ret void
}

define i1 @vm(%buffer* %0, %map_charp_ZVALUE* %1) !dbg !265 {
entry:
  %oror = alloca i1, align 1, !dbg !266
  %rvalue780 = alloca i32, align 4, !dbg !266
  %lvalue764 = alloca i32, align 4, !dbg !266
  %rvalue715 = alloca i32, align 4, !dbg !266
  %lvalue699 = alloca i32, align 4, !dbg !266
  %exp = alloca i1, align 1, !dbg !266
  %value635 = alloca i32, align 4, !dbg !266
  %value605 = alloca i32, align 4, !dbg !266
  %value566 = alloca i32, align 4, !dbg !266
  %fun_name = alloca i8*, align 8, !dbg !266
  %offset524 = alloca i32, align 4, !dbg !266
  %right507 = alloca %ZVALUE, align 8, !dbg !266
  %right = alloca %ZVALUE, align 8, !dbg !266
  %in_global_context482 = alloca i1, align 1, !dbg !266
  %var_name465 = alloca i8*, align 8, !dbg !266
  %offset455 = alloca i32, align 4, !dbg !266
  %in_global_context = alloca i1, align 1, !dbg !266
  %var_name = alloca i8*, align 8, !dbg !266
  %offset356 = alloca i32, align 4, !dbg !266
  %str245 = alloca i8*, align 8, !dbg !266
  %offset = alloca i32, align 4, !dbg !266
  %rvalue196 = alloca i32, align 4, !dbg !266
  %lvalue180 = alloca i32, align 4, !dbg !266
  %rvalue = alloca i32, align 4, !dbg !266
  %lvalue = alloca i32, align 4, !dbg !266
  %value = alloca i32, align 4, !dbg !266
  %n = alloca i32, align 4, !dbg !266
  %item = alloca %ZVALUE, align 8, !dbg !266
  %result = alloca i8*, align 8, !dbg !266
  %len = alloca i32, align 4, !dbg !266
  %key = alloca i8*, align 8, !dbg !266
  %it = alloca i8*, align 8, !dbg !266
  %_obj = alloca %map_charp_ZVALUE*, align 8, !dbg !266
  %vtable = alloca %map_charp_ZVALUE*, align 8, !dbg !266
  %head = alloca i32*, align 8, !dbg !266
  %p = alloca i32*, align 8, !dbg !266
  %stack_num = alloca i32, align 4, !dbg !266
  %stack = alloca [1024 x %ZVALUE], align 8, !dbg !266
  %codes = alloca %buffer*, align 8, !dbg !266
  store %buffer* %0, %buffer** %codes, align 8, !dbg !266
  %params = alloca %map_charp_ZVALUE*, align 8, !dbg !266
  store %map_charp_ZVALUE* %1, %map_charp_ZVALUE** %params, align 8, !dbg !266
  store i32 0, i32* %stack_num, align 4, !dbg !266
  %codes1 = load %buffer*, %buffer** %codes, align 8, !dbg !267
  %field = getelementptr inbounds %buffer, %buffer* %codes1, i32 0, i32 0, !dbg !267
  %buf = load i8*, i8** %field, align 8, !dbg !267
  %castAQ = bitcast i8* %buf to i32*, !dbg !267
  store i32* %castAQ, i32** %p, align 8, !dbg !266
  %codes2 = load %buffer*, %buffer** %codes, align 8, !dbg !268
  %field3 = getelementptr inbounds %buffer, %buffer* %codes2, i32 0, i32 0, !dbg !268
  %buf4 = load i8*, i8** %field3, align 8, !dbg !268
  %castAQ5 = bitcast i8* %buf4 to i32*, !dbg !268
  store i32* %castAQ5, i32** %head, align 8, !dbg !266
  %fun_result = call i8* @GC_malloc(i64 40), !dbg !269
  %obj = bitcast i8* %fun_result to %map_charp_ZVALUE*, !dbg !269
  %fun_result6 = call %map_charp_ZVALUE* @map_initialize_charp_ZVALUE(%map_charp_ZVALUE* %obj), !dbg !269
  store %map_charp_ZVALUE* %fun_result6, %map_charp_ZVALUE** %vtable, align 8, !dbg !266
  %params7 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %params, align 8, !dbg !270
  %icmpB = icmp ne %map_charp_ZVALUE* %params7, null, !dbg !270
  br i1 %icmpB, label %cond_jump_then, label %cond_end, !dbg !270

cond_jump_then:                                   ; preds = %entry
  %params8 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %params, align 8, !dbg !271
  store %map_charp_ZVALUE* %params8, %map_charp_ZVALUE** %_obj, align 8, !dbg !266
  %_obj9 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %_obj, align 8, !dbg !271
  %fun_result10 = call i8* @map_begin_charp_ZVALUE(%map_charp_ZVALUE* %_obj9), !dbg !271
  store i8* %fun_result10, i8** %it, align 8, !dbg !266
  br label %loop_top_block, !dbg !266

cond_end:                                         ; preds = %cond_end_block, %entry
  br label %loop_top_block33, !dbg !272

loop_top_block:                                   ; preds = %string_end, %cond_jump_then
  %_obj11 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %_obj, align 8, !dbg !271
  %fun_result12 = call i1 @map_end_charp_ZVALUE(%map_charp_ZVALUE* %_obj11), !dbg !271
  %logical_denial = icmp eq i1 %fun_result12, false, !dbg !271
  br i1 %logical_denial, label %cond_then_block, label %cond_end_block, !dbg !271

cond_then_block:                                  ; preds = %loop_top_block
  %it13 = load i8*, i8** %it, align 8, !dbg !273
  store i8* %it13, i8** %key, align 8, !dbg !266
  %params14 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %params, align 8, !dbg !274
  %it15 = load i8*, i8** %it, align 8, !dbg !274
  br label %string, !dbg !274

cond_end_block:                                   ; preds = %loop_top_block
  br label %cond_end, !dbg !271

string:                                           ; preds = %cond_then_block
  %inline_result_variable = alloca i8*, align 8, !dbg !274
  %str = alloca i8*, align 8, !dbg !274
  store i8* %it15, i8** %str, align 8, !dbg !274
  %str16 = load i8*, i8** %str, align 8, !dbg !274
  %fun_result17 = call i64 @strlen(i8* %str16), !dbg !274
  %add = add i64 %fun_result17, 1, !dbg !274
  %icastM = trunc i64 %add to i32, !dbg !274
  store i32 %icastM, i32* %len, align 4, !dbg !266
  %len18 = load i32, i32* %len, align 4, !dbg !266
  %icastD = sext i32 %len18 to i64, !dbg !266
  %mul = mul i64 1, %icastD, !dbg !266
  %fun_result19 = call i8* @GC_malloc(i64 %mul), !dbg !266
  store i8* %fun_result19, i8** %result, align 8, !dbg !266
  %result20 = load i8*, i8** %result, align 8, !dbg !266
  %str21 = load i8*, i8** %str, align 8, !dbg !266
  %len22 = load i32, i32* %len, align 4, !dbg !266
  %icastD23 = sext i32 %len22 to i64, !dbg !266
  %fun_result24 = call i8* @strncpy(i8* %result20, i8* %str21, i64 %icastD23), !dbg !266
  %result25 = load i8*, i8** %result, align 8, !dbg !266
  store i8* %result25, i8** %inline_result_variable, align 8, !dbg !266
  br label %string_end, !dbg !266

string_end:                                       ; preds = %string
  %inline_result_variable26 = load i8*, i8** %inline_result_variable, align 8, !dbg !266
  %gNullValue = load %ZVALUE, %ZVALUE* @gNullValue, align 4, !dbg !274
  %fun_result27 = call %ZVALUE @map_at_charp_ZVALUE(%map_charp_ZVALUE* %params14, i8* %inline_result_variable26, %ZVALUE %gNullValue), !dbg !274
  store %ZVALUE %fun_result27, %ZVALUE* %item, align 4, !dbg !266
  %vtable28 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %vtable, align 8, !dbg !275
  %key29 = load i8*, i8** %key, align 8, !dbg !275
  %item30 = load %ZVALUE, %ZVALUE* %item, align 4, !dbg !275
  call void @map_insert_charp_ZVALUE(%map_charp_ZVALUE* %vtable28, i8* %key29, %ZVALUE %item30), !dbg !275
  %_obj31 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %_obj, align 8, !dbg !271
  %fun_result32 = call i8* @map_next_charp_ZVALUE(%map_charp_ZVALUE* %_obj31), !dbg !271
  store i8* %fun_result32, i8** %it, align 8, !dbg !271
  br label %loop_top_block, !dbg !271

loop_top_block33:                                 ; preds = %cond_end814, %cond_end
  %p34 = load i32*, i32** %p, align 8, !dbg !276
  %head35 = load i32*, i32** %head, align 8, !dbg !276
  %ptrToIntG = ptrtoint i32* %p34 to i64, !dbg !276
  %ptrToIntH = ptrtoint i32* %head35 to i64, !dbg !276
  %sub = sub i64 %ptrToIntG, %ptrToIntH, !dbg !276
  %div = sdiv i64 %sub, 4, !dbg !276
  %codes36 = load %buffer*, %buffer** %codes, align 8, !dbg !276
  %fun_result37 = call i32 @buffer_length(%buffer* %codes36), !dbg !276
  %div38 = sdiv i32 %fun_result37, 4, !dbg !276
  %icastD39 = sext i32 %div38 to i64, !dbg !276
  %le = icmp slt i64 %div, %icastD39, !dbg !276
  br i1 %le, label %cond_then_block40, label %cond_end_block41, !dbg !276

cond_then_block40:                                ; preds = %loop_top_block33
  %p42 = load i32*, i32** %p, align 8, !dbg !277
  %derefference_value = load i32, i32* %p42, align 4, !dbg !277
  %eqtmp = icmp eq i32 %derefference_value, 6, !dbg !278
  br i1 %eqtmp, label %cond_then_block43, label %cond_else_blockX, !dbg !278

cond_end_block41:                                 ; preds = %loop_top_block33
  ret i1 true, !dbg !272

end_blockX:                                       ; preds = %cond_else_blockX804, %cond_then_block739, %cond_then_block674, %cond_end659, %cond_then_block593, %cond_then_block554, %cond_end552, %cond_end493, %cond_end438, %end_blockX290, %cond_then_block224, %cond_then_block155, %cond_then_block94, %cond_then_block61, %cond_then_block43
  %stack_num808 = load i32, i32* %stack_num, align 4, !dbg !279
  %le809 = icmp slt i32 %stack_num808, 0, !dbg !279
  store i1 %le809, i1* %oror, align 1, !dbg !279
  br i1 %le809, label %cond_jump_end, label %cond_jump_then810, !dbg !279

cond_then_block43:                                ; preds = %cond_then_block40
  %p44 = load i32*, i32** %p, align 8, !dbg !280
  %ptrToIntC = ptrtoint i32* %p44 to i64, !dbg !280
  %add45 = add i64 %ptrToIntC, 4, !dbg !280
  %intToPtr = inttoptr i64 %add45 to i32*, !dbg !280
  store i32* %intToPtr, i32** %p, align 8, !dbg !280
  %ptrToIntI = ptrtoint i32* %intToPtr to i64, !dbg !280
  %sub46 = sub i64 %ptrToIntI, 4, !dbg !280
  %iintToPtr = inttoptr i64 %sub46 to i32*, !dbg !280
  %p47 = load i32*, i32** %p, align 8, !dbg !281
  %derefference_value48 = load i32, i32* %p47, align 4, !dbg !281
  store i32 %derefference_value48, i32* %n, align 4, !dbg !266
  %p49 = load i32*, i32** %p, align 8, !dbg !282
  %ptrToIntC50 = ptrtoint i32* %p49 to i64, !dbg !282
  %add51 = add i64 %ptrToIntC50, 4, !dbg !282
  %intToPtr52 = inttoptr i64 %add51 to i32*, !dbg !282
  store i32* %intToPtr52, i32** %p, align 8, !dbg !282
  %ptrToIntI53 = ptrtoint i32* %intToPtr52 to i64, !dbg !282
  %sub54 = sub i64 %ptrToIntI53, 4, !dbg !282
  %iintToPtr55 = inttoptr i64 %sub54 to i32*, !dbg !282
  %stack_num56 = load i32, i32* %stack_num, align 4, !dbg !283
  %n57 = load i32, i32* %n, align 4, !dbg !283
  %sub58 = sub i32 %stack_num56, %n57, !dbg !283
  store i32 %sub58, i32* %stack_num, align 4, !dbg !283
  %n59 = load i32, i32* %n, align 4, !dbg !283
  %add60 = add i32 %sub58, %n59, !dbg !283
  br label %end_blockX, !dbg !284

cond_else_blockX:                                 ; preds = %after_break, %cond_then_block40
  %eqtmp63 = icmp eq i32 %derefference_value, 1, !dbg !285
  br i1 %eqtmp63, label %cond_then_block61, label %cond_else_blockX62, !dbg !285

after_break:                                      ; No predecessors!
  br label %cond_else_blockX, !dbg !285

cond_then_block61:                                ; preds = %cond_else_blockX
  %p64 = load i32*, i32** %p, align 8, !dbg !286
  %ptrToIntC65 = ptrtoint i32* %p64 to i64, !dbg !286
  %add66 = add i64 %ptrToIntC65, 4, !dbg !286
  %intToPtr67 = inttoptr i64 %add66 to i32*, !dbg !286
  store i32* %intToPtr67, i32** %p, align 8, !dbg !286
  %ptrToIntI68 = ptrtoint i32* %intToPtr67 to i64, !dbg !286
  %sub69 = sub i64 %ptrToIntI68, 4, !dbg !286
  %iintToPtr70 = inttoptr i64 %sub69 to i32*, !dbg !286
  %p71 = load i32*, i32** %p, align 8, !dbg !287
  %derefference_value72 = load i32, i32* %p71, align 4, !dbg !287
  store i32 %derefference_value72, i32* %value, align 4, !dbg !266
  %p73 = load i32*, i32** %p, align 8, !dbg !288
  %ptrToIntC74 = ptrtoint i32* %p73 to i64, !dbg !288
  %add75 = add i64 %ptrToIntC74, 4, !dbg !288
  %intToPtr76 = inttoptr i64 %add75 to i32*, !dbg !288
  store i32* %intToPtr76, i32** %p, align 8, !dbg !288
  %ptrToIntI77 = ptrtoint i32* %intToPtr76 to i64, !dbg !288
  %sub78 = sub i64 %ptrToIntI77, 4, !dbg !288
  %iintToPtr79 = inttoptr i64 %sub78 to i32*, !dbg !288
  %stack_num80 = load i32, i32* %stack_num, align 4, !dbg !289
  %array_cast = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !289
  %gep = getelementptr %ZVALUE, %ZVALUE* %array_cast, i32 %stack_num80, !dbg !289
  %element = load %ZVALUE, %ZVALUE* %gep, align 4, !dbg !289
  %field81 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep, i32 0, i32 0, !dbg !289
  store i32 0, i32* %field81, align 4, !dbg !289
  %stack_num82 = load i32, i32* %stack_num, align 4, !dbg !290
  %array_cast83 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !290
  %gep84 = getelementptr %ZVALUE, %ZVALUE* %array_cast83, i32 %stack_num82, !dbg !290
  %element85 = load %ZVALUE, %ZVALUE* %gep84, align 4, !dbg !290
  %field86 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep84, i32 0, i32 1, !dbg !290
  %value87 = load %come_anon86, %come_anon86* %field86, align 4, !dbg !290
  %value88 = load i32, i32* %value, align 4, !dbg !290
  %field89 = getelementptr inbounds %come_anon86, %come_anon86* %field86, i32 0, i32 0, !dbg !290
  %icastN = bitcast i64* %field89 to i32*, !dbg !290
  store i32 %value88, i32* %icastN, align 4, !dbg !290
  %stack_num90 = load i32, i32* %stack_num, align 4, !dbg !291
  %add91 = add i32 %stack_num90, 1, !dbg !291
  store i32 %add91, i32* %stack_num, align 4, !dbg !291
  %sub92 = sub i32 %add91, 1, !dbg !291
  br label %end_blockX, !dbg !292

cond_else_blockX62:                               ; preds = %after_break93, %cond_else_blockX
  %eqtmp96 = icmp eq i32 %derefference_value, 2, !dbg !293
  br i1 %eqtmp96, label %cond_then_block94, label %cond_else_blockX95, !dbg !293

after_break93:                                    ; No predecessors!
  br label %cond_else_blockX62, !dbg !293

cond_then_block94:                                ; preds = %cond_else_blockX62
  %p97 = load i32*, i32** %p, align 8, !dbg !294
  %ptrToIntC98 = ptrtoint i32* %p97 to i64, !dbg !294
  %add99 = add i64 %ptrToIntC98, 4, !dbg !294
  %intToPtr100 = inttoptr i64 %add99 to i32*, !dbg !294
  store i32* %intToPtr100, i32** %p, align 8, !dbg !294
  %ptrToIntI101 = ptrtoint i32* %intToPtr100 to i64, !dbg !294
  %sub102 = sub i64 %ptrToIntI101, 4, !dbg !294
  %iintToPtr103 = inttoptr i64 %sub102 to i32*, !dbg !294
  %stack_num104 = load i32, i32* %stack_num, align 4, !dbg !295
  %sub105 = sub i32 %stack_num104, 1, !dbg !295
  %array_cast106 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !295
  %gep107 = getelementptr %ZVALUE, %ZVALUE* %array_cast106, i32 %sub105, !dbg !295
  %element108 = load %ZVALUE, %ZVALUE* %gep107, align 4, !dbg !295
  %stack_num109 = load i32, i32* %stack_num, align 4, !dbg !295
  %sub110 = sub i32 %stack_num109, 1, !dbg !295
  %array_cast111 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !295
  %gep112 = getelementptr %ZVALUE, %ZVALUE* %array_cast111, i32 %sub110, !dbg !295
  %element113 = load %ZVALUE, %ZVALUE* %gep112, align 4, !dbg !295
  %field114 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep112, i32 0, i32 1, !dbg !295
  %value115 = load %come_anon86, %come_anon86* %field114, align 4, !dbg !295
  %field116 = getelementptr inbounds %come_anon86, %come_anon86* %field114, i32 0, i32 0, !dbg !295
  %icastO = bitcast i64* %field116 to i32*, !dbg !295
  %intValue = load i32, i32* %icastO, align 4, !dbg !295
  store i32 %intValue, i32* %lvalue, align 4, !dbg !266
  %stack_num117 = load i32, i32* %stack_num, align 4, !dbg !296
  %sub118 = sub i32 %stack_num117, 2, !dbg !296
  %array_cast119 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !296
  %gep120 = getelementptr %ZVALUE, %ZVALUE* %array_cast119, i32 %sub118, !dbg !296
  %element121 = load %ZVALUE, %ZVALUE* %gep120, align 4, !dbg !296
  %stack_num122 = load i32, i32* %stack_num, align 4, !dbg !296
  %sub123 = sub i32 %stack_num122, 2, !dbg !296
  %array_cast124 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !296
  %gep125 = getelementptr %ZVALUE, %ZVALUE* %array_cast124, i32 %sub123, !dbg !296
  %element126 = load %ZVALUE, %ZVALUE* %gep125, align 4, !dbg !296
  %field127 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep125, i32 0, i32 1, !dbg !296
  %value128 = load %come_anon86, %come_anon86* %field127, align 4, !dbg !296
  %field129 = getelementptr inbounds %come_anon86, %come_anon86* %field127, i32 0, i32 0, !dbg !296
  %icastO130 = bitcast i64* %field129 to i32*, !dbg !296
  %intValue131 = load i32, i32* %icastO130, align 4, !dbg !296
  store i32 %intValue131, i32* %rvalue, align 4, !dbg !266
  %stack_num132 = load i32, i32* %stack_num, align 4, !dbg !297
  %sub133 = sub i32 %stack_num132, 2, !dbg !297
  store i32 %sub133, i32* %stack_num, align 4, !dbg !297
  %add134 = add i32 %sub133, 2, !dbg !297
  %stack_num135 = load i32, i32* %stack_num, align 4, !dbg !298
  %array_cast136 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !298
  %gep137 = getelementptr %ZVALUE, %ZVALUE* %array_cast136, i32 %stack_num135, !dbg !298
  %element138 = load %ZVALUE, %ZVALUE* %gep137, align 4, !dbg !298
  %field139 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep137, i32 0, i32 0, !dbg !298
  store i32 0, i32* %field139, align 4, !dbg !298
  %stack_num140 = load i32, i32* %stack_num, align 4, !dbg !299
  %array_cast141 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !299
  %gep142 = getelementptr %ZVALUE, %ZVALUE* %array_cast141, i32 %stack_num140, !dbg !299
  %element143 = load %ZVALUE, %ZVALUE* %gep142, align 4, !dbg !299
  %field144 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep142, i32 0, i32 1, !dbg !299
  %value145 = load %come_anon86, %come_anon86* %field144, align 4, !dbg !299
  %lvalue146 = load i32, i32* %lvalue, align 4, !dbg !299
  %rvalue147 = load i32, i32* %rvalue, align 4, !dbg !299
  %add148 = add i32 %lvalue146, %rvalue147, !dbg !299
  %field149 = getelementptr inbounds %come_anon86, %come_anon86* %field144, i32 0, i32 0, !dbg !299
  %icastN150 = bitcast i64* %field149 to i32*, !dbg !299
  store i32 %add148, i32* %icastN150, align 4, !dbg !299
  %stack_num151 = load i32, i32* %stack_num, align 4, !dbg !300
  %add152 = add i32 %stack_num151, 1, !dbg !300
  store i32 %add152, i32* %stack_num, align 4, !dbg !300
  %sub153 = sub i32 %add152, 1, !dbg !300
  br label %end_blockX, !dbg !301

cond_else_blockX95:                               ; preds = %after_break154, %cond_else_blockX62
  %eqtmp157 = icmp eq i32 %derefference_value, 3, !dbg !302
  br i1 %eqtmp157, label %cond_then_block155, label %cond_else_blockX156, !dbg !302

after_break154:                                   ; No predecessors!
  br label %cond_else_blockX95, !dbg !302

cond_then_block155:                               ; preds = %cond_else_blockX95
  %p158 = load i32*, i32** %p, align 8, !dbg !303
  %ptrToIntC159 = ptrtoint i32* %p158 to i64, !dbg !303
  %add160 = add i64 %ptrToIntC159, 4, !dbg !303
  %intToPtr161 = inttoptr i64 %add160 to i32*, !dbg !303
  store i32* %intToPtr161, i32** %p, align 8, !dbg !303
  %ptrToIntI162 = ptrtoint i32* %intToPtr161 to i64, !dbg !303
  %sub163 = sub i64 %ptrToIntI162, 4, !dbg !303
  %iintToPtr164 = inttoptr i64 %sub163 to i32*, !dbg !303
  %stack_num165 = load i32, i32* %stack_num, align 4, !dbg !304
  %sub166 = sub i32 %stack_num165, 1, !dbg !304
  %array_cast167 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !304
  %gep168 = getelementptr %ZVALUE, %ZVALUE* %array_cast167, i32 %sub166, !dbg !304
  %element169 = load %ZVALUE, %ZVALUE* %gep168, align 4, !dbg !304
  %stack_num170 = load i32, i32* %stack_num, align 4, !dbg !304
  %sub171 = sub i32 %stack_num170, 1, !dbg !304
  %array_cast172 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !304
  %gep173 = getelementptr %ZVALUE, %ZVALUE* %array_cast172, i32 %sub171, !dbg !304
  %element174 = load %ZVALUE, %ZVALUE* %gep173, align 4, !dbg !304
  %field175 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep173, i32 0, i32 1, !dbg !304
  %value176 = load %come_anon86, %come_anon86* %field175, align 4, !dbg !304
  %field177 = getelementptr inbounds %come_anon86, %come_anon86* %field175, i32 0, i32 0, !dbg !304
  %icastO178 = bitcast i64* %field177 to i32*, !dbg !304
  %intValue179 = load i32, i32* %icastO178, align 4, !dbg !304
  store i32 %intValue179, i32* %lvalue180, align 4, !dbg !266
  %stack_num181 = load i32, i32* %stack_num, align 4, !dbg !305
  %sub182 = sub i32 %stack_num181, 2, !dbg !305
  %array_cast183 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !305
  %gep184 = getelementptr %ZVALUE, %ZVALUE* %array_cast183, i32 %sub182, !dbg !305
  %element185 = load %ZVALUE, %ZVALUE* %gep184, align 4, !dbg !305
  %stack_num186 = load i32, i32* %stack_num, align 4, !dbg !305
  %sub187 = sub i32 %stack_num186, 2, !dbg !305
  %array_cast188 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !305
  %gep189 = getelementptr %ZVALUE, %ZVALUE* %array_cast188, i32 %sub187, !dbg !305
  %element190 = load %ZVALUE, %ZVALUE* %gep189, align 4, !dbg !305
  %field191 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep189, i32 0, i32 1, !dbg !305
  %value192 = load %come_anon86, %come_anon86* %field191, align 4, !dbg !305
  %field193 = getelementptr inbounds %come_anon86, %come_anon86* %field191, i32 0, i32 0, !dbg !305
  %icastO194 = bitcast i64* %field193 to i32*, !dbg !305
  %intValue195 = load i32, i32* %icastO194, align 4, !dbg !305
  store i32 %intValue195, i32* %rvalue196, align 4, !dbg !266
  %stack_num197 = load i32, i32* %stack_num, align 4, !dbg !306
  %sub198 = sub i32 %stack_num197, 2, !dbg !306
  store i32 %sub198, i32* %stack_num, align 4, !dbg !306
  %add199 = add i32 %sub198, 2, !dbg !306
  %stack_num200 = load i32, i32* %stack_num, align 4, !dbg !307
  %array_cast201 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !307
  %gep202 = getelementptr %ZVALUE, %ZVALUE* %array_cast201, i32 %stack_num200, !dbg !307
  %element203 = load %ZVALUE, %ZVALUE* %gep202, align 4, !dbg !307
  %field204 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep202, i32 0, i32 0, !dbg !307
  store i32 0, i32* %field204, align 4, !dbg !307
  %stack_num205 = load i32, i32* %stack_num, align 4, !dbg !308
  %array_cast206 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !308
  %gep207 = getelementptr %ZVALUE, %ZVALUE* %array_cast206, i32 %stack_num205, !dbg !308
  %element208 = load %ZVALUE, %ZVALUE* %gep207, align 4, !dbg !308
  %stack_num209 = load i32, i32* %stack_num, align 4, !dbg !308
  %array_cast210 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !308
  %gep211 = getelementptr %ZVALUE, %ZVALUE* %array_cast210, i32 %stack_num209, !dbg !308
  %element212 = load %ZVALUE, %ZVALUE* %gep211, align 4, !dbg !308
  %field213 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep211, i32 0, i32 1, !dbg !308
  %value214 = load %come_anon86, %come_anon86* %field213, align 4, !dbg !308
  %lvalue215 = load i32, i32* %lvalue180, align 4, !dbg !308
  %rvalue216 = load i32, i32* %rvalue196, align 4, !dbg !308
  %sub217 = sub i32 %lvalue215, %rvalue216, !dbg !308
  %field218 = getelementptr inbounds %come_anon86, %come_anon86* %field213, i32 0, i32 0, !dbg !308
  %icastN219 = bitcast i64* %field218 to i32*, !dbg !308
  store i32 %sub217, i32* %icastN219, align 4, !dbg !308
  %stack_num220 = load i32, i32* %stack_num, align 4, !dbg !309
  %add221 = add i32 %stack_num220, 1, !dbg !309
  store i32 %add221, i32* %stack_num, align 4, !dbg !309
  %sub222 = sub i32 %add221, 1, !dbg !309
  br label %end_blockX, !dbg !310

cond_else_blockX156:                              ; preds = %after_break223, %cond_else_blockX95
  %eqtmp226 = icmp eq i32 %derefference_value, 4, !dbg !311
  br i1 %eqtmp226, label %cond_then_block224, label %cond_else_blockX225, !dbg !311

after_break223:                                   ; No predecessors!
  br label %cond_else_blockX156, !dbg !311

cond_then_block224:                               ; preds = %cond_else_blockX156
  %p227 = load i32*, i32** %p, align 8, !dbg !312
  %ptrToIntC228 = ptrtoint i32* %p227 to i64, !dbg !312
  %add229 = add i64 %ptrToIntC228, 4, !dbg !312
  %intToPtr230 = inttoptr i64 %add229 to i32*, !dbg !312
  store i32* %intToPtr230, i32** %p, align 8, !dbg !312
  %ptrToIntI231 = ptrtoint i32* %intToPtr230 to i64, !dbg !312
  %sub232 = sub i64 %ptrToIntI231, 4, !dbg !312
  %iintToPtr233 = inttoptr i64 %sub232 to i32*, !dbg !312
  %p234 = load i32*, i32** %p, align 8, !dbg !313
  %derefference_value235 = load i32, i32* %p234, align 4, !dbg !313
  store i32 %derefference_value235, i32* %offset, align 4, !dbg !266
  %p236 = load i32*, i32** %p, align 8, !dbg !314
  %ptrToIntC237 = ptrtoint i32* %p236 to i64, !dbg !314
  %add238 = add i64 %ptrToIntC237, 4, !dbg !314
  %intToPtr239 = inttoptr i64 %add238 to i32*, !dbg !314
  store i32* %intToPtr239, i32** %p, align 8, !dbg !314
  %ptrToIntI240 = ptrtoint i32* %intToPtr239 to i64, !dbg !314
  %sub241 = sub i64 %ptrToIntI240, 4, !dbg !314
  %iintToPtr242 = inttoptr i64 %sub241 to i32*, !dbg !314
  %p243 = load i32*, i32** %p, align 8, !dbg !315
  %castAQ244 = bitcast i32* %p243 to i8*, !dbg !315
  store i8* %castAQ244, i8** %str245, align 8, !dbg !266
  %p246 = load i32*, i32** %p, align 8, !dbg !316
  %offset247 = load i32, i32* %offset, align 4, !dbg !316
  %ptrToIntC248 = ptrtoint i32* %p246 to i64, !dbg !316
  %sext = sext i32 %offset247 to i64, !dbg !316
  %mul249 = mul i64 %sext, 4, !dbg !316
  %add250 = add i64 %ptrToIntC248, %mul249, !dbg !316
  %intToPtr251 = inttoptr i64 %add250 to i32*, !dbg !316
  store i32* %intToPtr251, i32** %p, align 8, !dbg !316
  %offset252 = load i32, i32* %offset, align 4, !dbg !316
  %ptrToIntI253 = ptrtoint i32* %intToPtr251 to i64, !dbg !316
  %sext254 = sext i32 %offset252 to i64, !dbg !316
  %mul255 = mul i64 %sext254, 4, !dbg !316
  %sub256 = sub i64 %ptrToIntI253, %mul255, !dbg !316
  %iintToPtr257 = inttoptr i64 %sub256 to i32*, !dbg !316
  %stack_num258 = load i32, i32* %stack_num, align 4, !dbg !317
  %array_cast259 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !317
  %gep260 = getelementptr %ZVALUE, %ZVALUE* %array_cast259, i32 %stack_num258, !dbg !317
  %element261 = load %ZVALUE, %ZVALUE* %gep260, align 4, !dbg !317
  %field262 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep260, i32 0, i32 0, !dbg !317
  store i32 3, i32* %field262, align 4, !dbg !317
  %stack_num263 = load i32, i32* %stack_num, align 4, !dbg !318
  %array_cast264 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !318
  %gep265 = getelementptr %ZVALUE, %ZVALUE* %array_cast264, i32 %stack_num263, !dbg !318
  %element266 = load %ZVALUE, %ZVALUE* %gep265, align 4, !dbg !318
  %stack_num267 = load i32, i32* %stack_num, align 4, !dbg !318
  %array_cast268 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !318
  %gep269 = getelementptr %ZVALUE, %ZVALUE* %array_cast268, i32 %stack_num267, !dbg !318
  %element270 = load %ZVALUE, %ZVALUE* %gep269, align 4, !dbg !318
  %field271 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep269, i32 0, i32 1, !dbg !318
  %value272 = load %come_anon86, %come_anon86* %field271, align 4, !dbg !318
  %str273 = load i8*, i8** %str245, align 8, !dbg !318
  %field274 = getelementptr inbounds %come_anon86, %come_anon86* %field271, i32 0, i32 0, !dbg !318
  %icastN275 = bitcast i64* %field274 to i8**, !dbg !318
  store i8* %str273, i8** %icastN275, align 8, !dbg !318
  %stack_num276 = load i32, i32* %stack_num, align 4, !dbg !319
  %add277 = add i32 %stack_num276, 1, !dbg !319
  store i32 %add277, i32* %stack_num, align 4, !dbg !319
  %sub278 = sub i32 %add277, 1, !dbg !319
  br label %end_blockX, !dbg !320

cond_else_blockX225:                              ; preds = %after_break279, %cond_else_blockX156
  %eqtmp282 = icmp eq i32 %derefference_value, 5, !dbg !321
  br i1 %eqtmp282, label %cond_then_block280, label %cond_else_blockX281, !dbg !321

after_break279:                                   ; No predecessors!
  br label %cond_else_blockX225, !dbg !321

cond_then_block280:                               ; preds = %cond_else_blockX225
  %p283 = load i32*, i32** %p, align 8, !dbg !322
  %ptrToIntC284 = ptrtoint i32* %p283 to i64, !dbg !322
  %add285 = add i64 %ptrToIntC284, 4, !dbg !322
  %intToPtr286 = inttoptr i64 %add285 to i32*, !dbg !322
  store i32* %intToPtr286, i32** %p, align 8, !dbg !322
  %ptrToIntI287 = ptrtoint i32* %intToPtr286 to i64, !dbg !322
  %sub288 = sub i64 %ptrToIntI287, 4, !dbg !322
  %iintToPtr289 = inttoptr i64 %sub288 to i32*, !dbg !322
  %stack_num291 = load i32, i32* %stack_num, align 4, !dbg !323
  %sub292 = sub i32 %stack_num291, 1, !dbg !323
  %array_cast293 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !323
  %gep294 = getelementptr %ZVALUE, %ZVALUE* %array_cast293, i32 %sub292, !dbg !323
  %element295 = load %ZVALUE, %ZVALUE* %gep294, align 4, !dbg !323
  %field296 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep294, i32 0, i32 0, !dbg !323
  %kind = load i32, i32* %field296, align 4, !dbg !323
  %eqtmp299 = icmp eq i32 %kind, 3, !dbg !324
  br i1 %eqtmp299, label %cond_then_block297, label %cond_else_blockX298, !dbg !324

cond_else_blockX281:                              ; preds = %after_break343, %cond_else_blockX225
  %eqtmp346 = icmp eq i32 %derefference_value, 8, !dbg !325
  br i1 %eqtmp346, label %cond_then_block344, label %cond_else_blockX345, !dbg !325

end_blockX290:                                    ; preds = %cond_else_blockX327, %cond_end339, %cond_then_block311, %cond_then_block297
  br label %end_blockX, !dbg !326

cond_then_block297:                               ; preds = %cond_then_block280
  %stack_num300 = load i32, i32* %stack_num, align 4, !dbg !327
  %sub301 = sub i32 %stack_num300, 1, !dbg !327
  %array_cast302 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !327
  %gep303 = getelementptr %ZVALUE, %ZVALUE* %array_cast302, i32 %sub301, !dbg !327
  %element304 = load %ZVALUE, %ZVALUE* %gep303, align 4, !dbg !327
  %field305 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep303, i32 0, i32 1, !dbg !327
  %value306 = load %come_anon86, %come_anon86* %field305, align 4, !dbg !327
  %field307 = getelementptr inbounds %come_anon86, %come_anon86* %field305, i32 0, i32 0, !dbg !327
  %icastO308 = bitcast i64* %field307 to i8**, !dbg !327
  %stringValue = load i8*, i8** %icastO308, align 8, !dbg !327
  %fun_result309 = call i32 @puts(i8* %stringValue), !dbg !327
  br label %end_blockX290, !dbg !328

cond_else_blockX298:                              ; preds = %after_break310, %cond_then_block280
  %eqtmp313 = icmp eq i32 %kind, 0, !dbg !329
  br i1 %eqtmp313, label %cond_then_block311, label %cond_else_blockX312, !dbg !329

after_break310:                                   ; No predecessors!
  br label %cond_else_blockX298, !dbg !329

cond_then_block311:                               ; preds = %cond_else_blockX298
  %stack_num314 = load i32, i32* %stack_num, align 4, !dbg !330
  %sub315 = sub i32 %stack_num314, 1, !dbg !330
  %array_cast316 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !330
  %gep317 = getelementptr %ZVALUE, %ZVALUE* %array_cast316, i32 %sub315, !dbg !330
  %element318 = load %ZVALUE, %ZVALUE* %gep317, align 4, !dbg !330
  %field319 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep317, i32 0, i32 1, !dbg !330
  %value320 = load %come_anon86, %come_anon86* %field319, align 4, !dbg !330
  %field321 = getelementptr inbounds %come_anon86, %come_anon86* %field319, i32 0, i32 0, !dbg !330
  %icastO322 = bitcast i64* %field321 to i32*, !dbg !330
  %intValue323 = load i32, i32* %icastO322, align 4, !dbg !330
  %fun_result324 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @"%d\0A", i32 0, i32 0), i32 %intValue323), !dbg !330
  br label %end_blockX290, !dbg !331

cond_else_blockX312:                              ; preds = %after_break325, %cond_else_blockX298
  %eqtmp328 = icmp eq i32 %kind, 1, !dbg !332
  br i1 %eqtmp328, label %cond_then_block326, label %cond_else_blockX327, !dbg !332

after_break325:                                   ; No predecessors!
  br label %cond_else_blockX312, !dbg !332

cond_then_block326:                               ; preds = %cond_else_blockX312
  %stack_num329 = load i32, i32* %stack_num, align 4, !dbg !333
  %sub330 = sub i32 %stack_num329, 1, !dbg !333
  %array_cast331 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !333
  %gep332 = getelementptr %ZVALUE, %ZVALUE* %array_cast331, i32 %sub330, !dbg !333
  %element333 = load %ZVALUE, %ZVALUE* %gep332, align 4, !dbg !333
  %field334 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep332, i32 0, i32 1, !dbg !333
  %value335 = load %come_anon86, %come_anon86* %field334, align 4, !dbg !333
  %field336 = getelementptr inbounds %come_anon86, %come_anon86* %field334, i32 0, i32 0, !dbg !333
  %icastO337 = bitcast i64* %field336 to i1*, !dbg !333
  %boolValue = load i1, i1* %icastO337, align 1, !dbg !333
  br i1 %boolValue, label %cond_jump_then338, label %cond_else_block, !dbg !333

cond_else_blockX327:                              ; preds = %after_break342, %cond_else_blockX312
  br label %end_blockX290, !dbg !334

cond_jump_then338:                                ; preds = %cond_then_block326
  %fun_result340 = call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @true, i32 0, i32 0)), !dbg !335
  br label %cond_end339, !dbg !335

cond_else_block:                                  ; preds = %cond_then_block326
  %fun_result341 = call i32 @puts(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @false, i32 0, i32 0)), !dbg !336
  br label %cond_end339, !dbg !336

cond_end339:                                      ; preds = %cond_else_block, %cond_jump_then338
  br label %end_blockX290, !dbg !334

after_break342:                                   ; No predecessors!
  br label %cond_else_blockX327, !dbg !334

after_break343:                                   ; No predecessors!
  br label %cond_else_blockX281, !dbg !325

cond_then_block344:                               ; preds = %cond_else_blockX281
  %p347 = load i32*, i32** %p, align 8, !dbg !337
  %ptrToIntC348 = ptrtoint i32* %p347 to i64, !dbg !337
  %add349 = add i64 %ptrToIntC348, 4, !dbg !337
  %intToPtr350 = inttoptr i64 %add349 to i32*, !dbg !337
  store i32* %intToPtr350, i32** %p, align 8, !dbg !337
  %ptrToIntI351 = ptrtoint i32* %intToPtr350 to i64, !dbg !337
  %sub352 = sub i64 %ptrToIntI351, 4, !dbg !337
  %iintToPtr353 = inttoptr i64 %sub352 to i32*, !dbg !337
  %p354 = load i32*, i32** %p, align 8, !dbg !338
  %derefference_value355 = load i32, i32* %p354, align 4, !dbg !338
  store i32 %derefference_value355, i32* %offset356, align 4, !dbg !266
  %p357 = load i32*, i32** %p, align 8, !dbg !339
  %ptrToIntC358 = ptrtoint i32* %p357 to i64, !dbg !339
  %add359 = add i64 %ptrToIntC358, 4, !dbg !339
  %intToPtr360 = inttoptr i64 %add359 to i32*, !dbg !339
  store i32* %intToPtr360, i32** %p, align 8, !dbg !339
  %ptrToIntI361 = ptrtoint i32* %intToPtr360 to i64, !dbg !339
  %sub362 = sub i64 %ptrToIntI361, 4, !dbg !339
  %iintToPtr363 = inttoptr i64 %sub362 to i32*, !dbg !339
  %p364 = load i32*, i32** %p, align 8, !dbg !340
  %castAQ365 = bitcast i32* %p364 to i8*, !dbg !340
  store i8* %castAQ365, i8** %var_name, align 8, !dbg !266
  %p366 = load i32*, i32** %p, align 8, !dbg !341
  %offset367 = load i32, i32* %offset356, align 4, !dbg !341
  %ptrToIntC368 = ptrtoint i32* %p366 to i64, !dbg !341
  %sext369 = sext i32 %offset367 to i64, !dbg !341
  %mul370 = mul i64 %sext369, 4, !dbg !341
  %add371 = add i64 %ptrToIntC368, %mul370, !dbg !341
  %intToPtr372 = inttoptr i64 %add371 to i32*, !dbg !341
  store i32* %intToPtr372, i32** %p, align 8, !dbg !341
  %offset373 = load i32, i32* %offset356, align 4, !dbg !341
  %ptrToIntI374 = ptrtoint i32* %intToPtr372 to i64, !dbg !341
  %sext375 = sext i32 %offset373 to i64, !dbg !341
  %mul376 = mul i64 %sext375, 4, !dbg !341
  %sub377 = sub i64 %ptrToIntI374, %mul376, !dbg !341
  %iintToPtr378 = inttoptr i64 %sub377 to i32*, !dbg !341
  %p379 = load i32*, i32** %p, align 8, !dbg !342
  %derefference_value380 = load i32, i32* %p379, align 4, !dbg !342
  %icmpA = icmp ne i32 %derefference_value380, 0, !dbg !342
  store i1 %icmpA, i1* %in_global_context, align 1, !dbg !266
  %p381 = load i32*, i32** %p, align 8, !dbg !343
  %ptrToIntC382 = ptrtoint i32* %p381 to i64, !dbg !343
  %add383 = add i64 %ptrToIntC382, 4, !dbg !343
  %intToPtr384 = inttoptr i64 %add383 to i32*, !dbg !343
  store i32* %intToPtr384, i32** %p, align 8, !dbg !343
  %ptrToIntI385 = ptrtoint i32* %intToPtr384 to i64, !dbg !343
  %sub386 = sub i64 %ptrToIntI385, 4, !dbg !343
  %iintToPtr387 = inttoptr i64 %sub386 to i32*, !dbg !343
  %in_global_context388 = load i1, i1* %in_global_context, align 1, !dbg !344
  br i1 %in_global_context388, label %cond_jump_then389, label %cond_else_block390, !dbg !344

cond_else_blockX345:                              ; preds = %after_break442, %cond_else_blockX281
  %eqtmp445 = icmp eq i32 %derefference_value, 7, !dbg !345
  br i1 %eqtmp445, label %cond_then_block443, label %cond_else_blockX444, !dbg !345

cond_jump_then389:                                ; preds = %cond_then_block344
  %stack_num392 = load i32, i32* %stack_num, align 4, !dbg !346
  %gGlobalVar = load %map_charp_ZVALUE*, %map_charp_ZVALUE** @gGlobalVar, align 8, !dbg !346
  %var_name393 = load i8*, i8** %var_name, align 8, !dbg !346
  %gNullValue394 = load %ZVALUE, %ZVALUE* @gNullValue, align 4, !dbg !346
  %fun_result395 = call %ZVALUE @map_at_charp_ZVALUE(%map_charp_ZVALUE* %gGlobalVar, i8* %var_name393, %ZVALUE %gNullValue394), !dbg !346
  %array_cast396 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !346
  %gep397 = getelementptr %ZVALUE, %ZVALUE* %array_cast396, i32 %stack_num392, !dbg !346
  store %ZVALUE %fun_result395, %ZVALUE* %gep397, align 4, !dbg !346
  %stack_num398 = load i32, i32* %stack_num, align 4, !dbg !347
  %add399 = add i32 %stack_num398, 1, !dbg !347
  store i32 %add399, i32* %stack_num, align 4, !dbg !347
  %sub400 = sub i32 %add399, 1, !dbg !347
  br label %cond_end391, !dbg !347

cond_else_block390:                               ; preds = %cond_then_block344
  %stack_num401 = load i32, i32* %stack_num, align 4, !dbg !348
  %vtable402 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %vtable, align 8, !dbg !348
  %var_name403 = load i8*, i8** %var_name, align 8, !dbg !348
  %gNullValue404 = load %ZVALUE, %ZVALUE* @gNullValue, align 4, !dbg !348
  %fun_result405 = call %ZVALUE @map_at_charp_ZVALUE(%map_charp_ZVALUE* %vtable402, i8* %var_name403, %ZVALUE %gNullValue404), !dbg !348
  %array_cast406 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !348
  %gep407 = getelementptr %ZVALUE, %ZVALUE* %array_cast406, i32 %stack_num401, !dbg !348
  store %ZVALUE %fun_result405, %ZVALUE* %gep407, align 4, !dbg !348
  %stack_num408 = load i32, i32* %stack_num, align 4, !dbg !349
  %sub409 = sub i32 %stack_num408, 1, !dbg !349
  %array_cast410 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !349
  %gep411 = getelementptr %ZVALUE, %ZVALUE* %array_cast410, i32 %sub409, !dbg !349
  %element412 = load %ZVALUE, %ZVALUE* %gep411, align 4, !dbg !349
  %field413 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep411, i32 0, i32 0, !dbg !349
  %kind414 = load i32, i32* %field413, align 4, !dbg !349
  %eq = icmp eq i32 %kind414, 5, !dbg !349
  br i1 %eq, label %cond_jump_then415, label %cond_end416, !dbg !349

cond_end391:                                      ; preds = %cond_end416, %cond_jump_then389
  %stack_num429 = load i32, i32* %stack_num, align 4, !dbg !350
  %sub430 = sub i32 %stack_num429, 1, !dbg !350
  %array_cast431 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !350
  %gep432 = getelementptr %ZVALUE, %ZVALUE* %array_cast431, i32 %sub430, !dbg !350
  %element433 = load %ZVALUE, %ZVALUE* %gep432, align 4, !dbg !350
  %field434 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep432, i32 0, i32 0, !dbg !350
  %kind435 = load i32, i32* %field434, align 4, !dbg !350
  %eq436 = icmp eq i32 %kind435, 5, !dbg !350
  br i1 %eq436, label %cond_jump_then437, label %cond_end438, !dbg !350

cond_jump_then415:                                ; preds = %cond_else_block390
  %stderr = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !351
  %var_name417 = load i8*, i8** %var_name, align 8, !dbg !351
  %fun_result418 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @"var not found(%s)\0A", i32 0, i32 0), i8* %var_name417), !dbg !351
  br label %cond_end416, !dbg !351

cond_end416:                                      ; preds = %cond_jump_then415, %cond_else_block390
  %stack_num419 = load i32, i32* %stack_num, align 4, !dbg !352
  %gGlobalVar420 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** @gGlobalVar, align 8, !dbg !352
  %var_name421 = load i8*, i8** %var_name, align 8, !dbg !352
  %gNullValue422 = load %ZVALUE, %ZVALUE* @gNullValue, align 4, !dbg !352
  %fun_result423 = call %ZVALUE @map_at_charp_ZVALUE(%map_charp_ZVALUE* %gGlobalVar420, i8* %var_name421, %ZVALUE %gNullValue422), !dbg !352
  %array_cast424 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !352
  %gep425 = getelementptr %ZVALUE, %ZVALUE* %array_cast424, i32 %stack_num419, !dbg !352
  store %ZVALUE %fun_result423, %ZVALUE* %gep425, align 4, !dbg !352
  %stack_num426 = load i32, i32* %stack_num, align 4, !dbg !353
  %add427 = add i32 %stack_num426, 1, !dbg !353
  store i32 %add427, i32* %stack_num, align 4, !dbg !353
  %sub428 = sub i32 %add427, 1, !dbg !353
  br label %cond_end391, !dbg !353

cond_jump_then437:                                ; preds = %cond_end391
  %stderr439 = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !354
  %var_name440 = load i8*, i8** %var_name, align 8, !dbg !354
  %fun_result441 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr439, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @"var not found(%s)\0A.1", i32 0, i32 0), i8* %var_name440), !dbg !354
  br label %cond_end438, !dbg !354

cond_end438:                                      ; preds = %cond_jump_then437, %cond_end391
  br label %end_blockX, !dbg !355

after_break442:                                   ; No predecessors!
  br label %cond_else_blockX345, !dbg !345

cond_then_block443:                               ; preds = %cond_else_blockX345
  %p446 = load i32*, i32** %p, align 8, !dbg !356
  %ptrToIntC447 = ptrtoint i32* %p446 to i64, !dbg !356
  %add448 = add i64 %ptrToIntC447, 4, !dbg !356
  %intToPtr449 = inttoptr i64 %add448 to i32*, !dbg !356
  store i32* %intToPtr449, i32** %p, align 8, !dbg !356
  %ptrToIntI450 = ptrtoint i32* %intToPtr449 to i64, !dbg !356
  %sub451 = sub i64 %ptrToIntI450, 4, !dbg !356
  %iintToPtr452 = inttoptr i64 %sub451 to i32*, !dbg !356
  %p453 = load i32*, i32** %p, align 8, !dbg !357
  %derefference_value454 = load i32, i32* %p453, align 4, !dbg !357
  store i32 %derefference_value454, i32* %offset455, align 4, !dbg !266
  %p456 = load i32*, i32** %p, align 8, !dbg !358
  %ptrToIntC457 = ptrtoint i32* %p456 to i64, !dbg !358
  %add458 = add i64 %ptrToIntC457, 4, !dbg !358
  %intToPtr459 = inttoptr i64 %add458 to i32*, !dbg !358
  store i32* %intToPtr459, i32** %p, align 8, !dbg !358
  %ptrToIntI460 = ptrtoint i32* %intToPtr459 to i64, !dbg !358
  %sub461 = sub i64 %ptrToIntI460, 4, !dbg !358
  %iintToPtr462 = inttoptr i64 %sub461 to i32*, !dbg !358
  %p463 = load i32*, i32** %p, align 8, !dbg !359
  %castAQ464 = bitcast i32* %p463 to i8*, !dbg !359
  store i8* %castAQ464, i8** %var_name465, align 8, !dbg !266
  %p466 = load i32*, i32** %p, align 8, !dbg !360
  %offset467 = load i32, i32* %offset455, align 4, !dbg !360
  %ptrToIntC468 = ptrtoint i32* %p466 to i64, !dbg !360
  %sext469 = sext i32 %offset467 to i64, !dbg !360
  %mul470 = mul i64 %sext469, 4, !dbg !360
  %add471 = add i64 %ptrToIntC468, %mul470, !dbg !360
  %intToPtr472 = inttoptr i64 %add471 to i32*, !dbg !360
  store i32* %intToPtr472, i32** %p, align 8, !dbg !360
  %offset473 = load i32, i32* %offset455, align 4, !dbg !360
  %ptrToIntI474 = ptrtoint i32* %intToPtr472 to i64, !dbg !360
  %sext475 = sext i32 %offset473 to i64, !dbg !360
  %mul476 = mul i64 %sext475, 4, !dbg !360
  %sub477 = sub i64 %ptrToIntI474, %mul476, !dbg !360
  %iintToPtr478 = inttoptr i64 %sub477 to i32*, !dbg !360
  %p479 = load i32*, i32** %p, align 8, !dbg !361
  %derefference_value480 = load i32, i32* %p479, align 4, !dbg !361
  %icmpA481 = icmp ne i32 %derefference_value480, 0, !dbg !361
  store i1 %icmpA481, i1* %in_global_context482, align 1, !dbg !266
  %p483 = load i32*, i32** %p, align 8, !dbg !362
  %ptrToIntC484 = ptrtoint i32* %p483 to i64, !dbg !362
  %add485 = add i64 %ptrToIntC484, 4, !dbg !362
  %intToPtr486 = inttoptr i64 %add485 to i32*, !dbg !362
  store i32* %intToPtr486, i32** %p, align 8, !dbg !362
  %ptrToIntI487 = ptrtoint i32* %intToPtr486 to i64, !dbg !362
  %sub488 = sub i64 %ptrToIntI487, 4, !dbg !362
  %iintToPtr489 = inttoptr i64 %sub488 to i32*, !dbg !362
  %in_global_context490 = load i1, i1* %in_global_context482, align 1, !dbg !363
  br i1 %in_global_context490, label %cond_jump_then491, label %cond_else_block492, !dbg !363

cond_else_blockX444:                              ; preds = %after_break511, %cond_else_blockX345
  %eqtmp514 = icmp eq i32 %derefference_value, 9, !dbg !364
  br i1 %eqtmp514, label %cond_then_block512, label %cond_else_blockX513, !dbg !364

cond_jump_then491:                                ; preds = %cond_then_block443
  %stack_num494 = load i32, i32* %stack_num, align 4, !dbg !365
  %sub495 = sub i32 %stack_num494, 1, !dbg !365
  %array_cast496 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !365
  %gep497 = getelementptr %ZVALUE, %ZVALUE* %array_cast496, i32 %sub495, !dbg !365
  %element498 = load %ZVALUE, %ZVALUE* %gep497, align 4, !dbg !365
  store %ZVALUE %element498, %ZVALUE* %right, align 4, !dbg !266
  %gGlobalVar499 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** @gGlobalVar, align 8, !dbg !366
  %var_name500 = load i8*, i8** %var_name465, align 8, !dbg !366
  %right501 = load %ZVALUE, %ZVALUE* %right, align 4, !dbg !366
  call void @map_insert_charp_ZVALUE(%map_charp_ZVALUE* %gGlobalVar499, i8* %var_name500, %ZVALUE %right501), !dbg !366
  br label %cond_end493, !dbg !366

cond_else_block492:                               ; preds = %cond_then_block443
  %stack_num502 = load i32, i32* %stack_num, align 4, !dbg !367
  %sub503 = sub i32 %stack_num502, 1, !dbg !367
  %array_cast504 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !367
  %gep505 = getelementptr %ZVALUE, %ZVALUE* %array_cast504, i32 %sub503, !dbg !367
  %element506 = load %ZVALUE, %ZVALUE* %gep505, align 4, !dbg !367
  store %ZVALUE %element506, %ZVALUE* %right507, align 4, !dbg !266
  %vtable508 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %vtable, align 8, !dbg !368
  %var_name509 = load i8*, i8** %var_name465, align 8, !dbg !368
  %right510 = load %ZVALUE, %ZVALUE* %right507, align 4, !dbg !368
  call void @map_insert_charp_ZVALUE(%map_charp_ZVALUE* %vtable508, i8* %var_name509, %ZVALUE %right510), !dbg !368
  br label %cond_end493, !dbg !368

cond_end493:                                      ; preds = %cond_else_block492, %cond_jump_then491
  br label %end_blockX, !dbg !369

after_break511:                                   ; No predecessors!
  br label %cond_else_blockX444, !dbg !364

cond_then_block512:                               ; preds = %cond_else_blockX444
  %p515 = load i32*, i32** %p, align 8, !dbg !370
  %ptrToIntC516 = ptrtoint i32* %p515 to i64, !dbg !370
  %add517 = add i64 %ptrToIntC516, 4, !dbg !370
  %intToPtr518 = inttoptr i64 %add517 to i32*, !dbg !370
  store i32* %intToPtr518, i32** %p, align 8, !dbg !370
  %ptrToIntI519 = ptrtoint i32* %intToPtr518 to i64, !dbg !370
  %sub520 = sub i64 %ptrToIntI519, 4, !dbg !370
  %iintToPtr521 = inttoptr i64 %sub520 to i32*, !dbg !370
  %p522 = load i32*, i32** %p, align 8, !dbg !371
  %derefference_value523 = load i32, i32* %p522, align 4, !dbg !371
  store i32 %derefference_value523, i32* %offset524, align 4, !dbg !266
  %p525 = load i32*, i32** %p, align 8, !dbg !372
  %ptrToIntC526 = ptrtoint i32* %p525 to i64, !dbg !372
  %add527 = add i64 %ptrToIntC526, 4, !dbg !372
  %intToPtr528 = inttoptr i64 %add527 to i32*, !dbg !372
  store i32* %intToPtr528, i32** %p, align 8, !dbg !372
  %ptrToIntI529 = ptrtoint i32* %intToPtr528 to i64, !dbg !372
  %sub530 = sub i64 %ptrToIntI529, 4, !dbg !372
  %iintToPtr531 = inttoptr i64 %sub530 to i32*, !dbg !372
  %p532 = load i32*, i32** %p, align 8, !dbg !373
  %castAQ533 = bitcast i32* %p532 to i8*, !dbg !373
  store i8* %castAQ533, i8** %fun_name, align 8, !dbg !266
  %p534 = load i32*, i32** %p, align 8, !dbg !374
  %offset535 = load i32, i32* %offset524, align 4, !dbg !374
  %ptrToIntC536 = ptrtoint i32* %p534 to i64, !dbg !374
  %sext537 = sext i32 %offset535 to i64, !dbg !374
  %mul538 = mul i64 %sext537, 4, !dbg !374
  %add539 = add i64 %ptrToIntC536, %mul538, !dbg !374
  %intToPtr540 = inttoptr i64 %add539 to i32*, !dbg !374
  store i32* %intToPtr540, i32** %p, align 8, !dbg !374
  %offset541 = load i32, i32* %offset524, align 4, !dbg !374
  %ptrToIntI542 = ptrtoint i32* %intToPtr540 to i64, !dbg !374
  %sext543 = sext i32 %offset541 to i64, !dbg !374
  %mul544 = mul i64 %sext543, 4, !dbg !374
  %sub545 = sub i64 %ptrToIntI542, %mul544, !dbg !374
  %iintToPtr546 = inttoptr i64 %sub545 to i32*, !dbg !374
  %fun_name547 = load i8*, i8** %fun_name, align 8, !dbg !375
  %autocast = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !375
  %stack_num548 = load i32, i32* %stack_num, align 4, !dbg !375
  %fun_result549 = call i1 @function_call(i8* %fun_name547, %ZVALUE* %autocast, i32 %stack_num548), !dbg !375
  %logical_denial550 = icmp eq i1 %fun_result549, false, !dbg !375
  br i1 %logical_denial550, label %cond_jump_then551, label %cond_end552, !dbg !375

cond_else_blockX513:                              ; preds = %after_break553, %cond_else_blockX444
  %eqtmp556 = icmp eq i32 %derefference_value, 10, !dbg !376
  br i1 %eqtmp556, label %cond_then_block554, label %cond_else_blockX555, !dbg !376

cond_jump_then551:                                ; preds = %cond_then_block512
  ret i1 false, !dbg !377

cond_end552:                                      ; preds = %cond_then_block512
  br label %end_blockX, !dbg !378

after_break553:                                   ; No predecessors!
  br label %cond_else_blockX513, !dbg !376

cond_then_block554:                               ; preds = %cond_else_blockX513
  %p557 = load i32*, i32** %p, align 8, !dbg !379
  %ptrToIntC558 = ptrtoint i32* %p557 to i64, !dbg !379
  %add559 = add i64 %ptrToIntC558, 4, !dbg !379
  %intToPtr560 = inttoptr i64 %add559 to i32*, !dbg !379
  store i32* %intToPtr560, i32** %p, align 8, !dbg !379
  %ptrToIntI561 = ptrtoint i32* %intToPtr560 to i64, !dbg !379
  %sub562 = sub i64 %ptrToIntI561, 4, !dbg !379
  %iintToPtr563 = inttoptr i64 %sub562 to i32*, !dbg !379
  %p564 = load i32*, i32** %p, align 8, !dbg !380
  %derefference_value565 = load i32, i32* %p564, align 4, !dbg !380
  store i32 %derefference_value565, i32* %value566, align 4, !dbg !266
  %p567 = load i32*, i32** %p, align 8, !dbg !381
  %ptrToIntC568 = ptrtoint i32* %p567 to i64, !dbg !381
  %add569 = add i64 %ptrToIntC568, 4, !dbg !381
  %intToPtr570 = inttoptr i64 %add569 to i32*, !dbg !381
  store i32* %intToPtr570, i32** %p, align 8, !dbg !381
  %ptrToIntI571 = ptrtoint i32* %intToPtr570 to i64, !dbg !381
  %sub572 = sub i64 %ptrToIntI571, 4, !dbg !381
  %iintToPtr573 = inttoptr i64 %sub572 to i32*, !dbg !381
  %stack_num574 = load i32, i32* %stack_num, align 4, !dbg !382
  %array_cast575 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !382
  %gep576 = getelementptr %ZVALUE, %ZVALUE* %array_cast575, i32 %stack_num574, !dbg !382
  %element577 = load %ZVALUE, %ZVALUE* %gep576, align 4, !dbg !382
  %field578 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep576, i32 0, i32 0, !dbg !382
  store i32 1, i32* %field578, align 4, !dbg !382
  %stack_num579 = load i32, i32* %stack_num, align 4, !dbg !383
  %array_cast580 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !383
  %gep581 = getelementptr %ZVALUE, %ZVALUE* %array_cast580, i32 %stack_num579, !dbg !383
  %element582 = load %ZVALUE, %ZVALUE* %gep581, align 4, !dbg !383
  %field583 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep581, i32 0, i32 1, !dbg !383
  %value584 = load %come_anon86, %come_anon86* %field583, align 4, !dbg !383
  %value585 = load i32, i32* %value566, align 4, !dbg !383
  %icmpA586 = icmp ne i32 %value585, 0, !dbg !383
  %field587 = getelementptr inbounds %come_anon86, %come_anon86* %field583, i32 0, i32 0, !dbg !383
  %icastN588 = bitcast i64* %field587 to i1*, !dbg !383
  store i1 %icmpA586, i1* %icastN588, align 1, !dbg !383
  %stack_num589 = load i32, i32* %stack_num, align 4, !dbg !384
  %add590 = add i32 %stack_num589, 1, !dbg !384
  store i32 %add590, i32* %stack_num, align 4, !dbg !384
  %sub591 = sub i32 %add590, 1, !dbg !384
  br label %end_blockX, !dbg !385

cond_else_blockX555:                              ; preds = %after_break592, %cond_else_blockX513
  %eqtmp595 = icmp eq i32 %derefference_value, 12, !dbg !386
  br i1 %eqtmp595, label %cond_then_block593, label %cond_else_blockX594, !dbg !386

after_break592:                                   ; No predecessors!
  br label %cond_else_blockX555, !dbg !386

cond_then_block593:                               ; preds = %cond_else_blockX555
  %p596 = load i32*, i32** %p, align 8, !dbg !387
  %ptrToIntC597 = ptrtoint i32* %p596 to i64, !dbg !387
  %add598 = add i64 %ptrToIntC597, 4, !dbg !387
  %intToPtr599 = inttoptr i64 %add598 to i32*, !dbg !387
  store i32* %intToPtr599, i32** %p, align 8, !dbg !387
  %ptrToIntI600 = ptrtoint i32* %intToPtr599 to i64, !dbg !387
  %sub601 = sub i64 %ptrToIntI600, 4, !dbg !387
  %iintToPtr602 = inttoptr i64 %sub601 to i32*, !dbg !387
  %p603 = load i32*, i32** %p, align 8, !dbg !388
  %derefference_value604 = load i32, i32* %p603, align 4, !dbg !388
  store i32 %derefference_value604, i32* %value605, align 4, !dbg !266
  %p606 = load i32*, i32** %p, align 8, !dbg !389
  %ptrToIntC607 = ptrtoint i32* %p606 to i64, !dbg !389
  %add608 = add i64 %ptrToIntC607, 4, !dbg !389
  %intToPtr609 = inttoptr i64 %add608 to i32*, !dbg !389
  store i32* %intToPtr609, i32** %p, align 8, !dbg !389
  %ptrToIntI610 = ptrtoint i32* %intToPtr609 to i64, !dbg !389
  %sub611 = sub i64 %ptrToIntI610, 4, !dbg !389
  %iintToPtr612 = inttoptr i64 %sub611 to i32*, !dbg !389
  %head613 = load i32*, i32** %head, align 8, !dbg !390
  %castAQ614 = bitcast i32* %head613 to i8*, !dbg !390
  %value615 = load i32, i32* %value605, align 4, !dbg !390
  %ptrToIntC616 = ptrtoint i8* %castAQ614 to i64, !dbg !390
  %sext617 = sext i32 %value615 to i64, !dbg !390
  %mul618 = mul i64 %sext617, 1, !dbg !390
  %add619 = add i64 %ptrToIntC616, %mul618, !dbg !390
  %intToPtr620 = inttoptr i64 %add619 to i8*, !dbg !390
  %castAQ621 = bitcast i8* %intToPtr620 to i32*, !dbg !390
  store i32* %castAQ621, i32** %p, align 8, !dbg !390
  br label %end_blockX, !dbg !391

cond_else_blockX594:                              ; preds = %after_break622, %cond_else_blockX555
  %eqtmp625 = icmp eq i32 %derefference_value, 11, !dbg !392
  br i1 %eqtmp625, label %cond_then_block623, label %cond_else_blockX624, !dbg !392

after_break622:                                   ; No predecessors!
  br label %cond_else_blockX594, !dbg !392

cond_then_block623:                               ; preds = %cond_else_blockX594
  %p626 = load i32*, i32** %p, align 8, !dbg !393
  %ptrToIntC627 = ptrtoint i32* %p626 to i64, !dbg !393
  %add628 = add i64 %ptrToIntC627, 4, !dbg !393
  %intToPtr629 = inttoptr i64 %add628 to i32*, !dbg !393
  store i32* %intToPtr629, i32** %p, align 8, !dbg !393
  %ptrToIntI630 = ptrtoint i32* %intToPtr629 to i64, !dbg !393
  %sub631 = sub i64 %ptrToIntI630, 4, !dbg !393
  %iintToPtr632 = inttoptr i64 %sub631 to i32*, !dbg !393
  %p633 = load i32*, i32** %p, align 8, !dbg !394
  %derefference_value634 = load i32, i32* %p633, align 4, !dbg !394
  store i32 %derefference_value634, i32* %value635, align 4, !dbg !266
  %p636 = load i32*, i32** %p, align 8, !dbg !395
  %ptrToIntC637 = ptrtoint i32* %p636 to i64, !dbg !395
  %add638 = add i64 %ptrToIntC637, 4, !dbg !395
  %intToPtr639 = inttoptr i64 %add638 to i32*, !dbg !395
  store i32* %intToPtr639, i32** %p, align 8, !dbg !395
  %ptrToIntI640 = ptrtoint i32* %intToPtr639 to i64, !dbg !395
  %sub641 = sub i64 %ptrToIntI640, 4, !dbg !395
  %iintToPtr642 = inttoptr i64 %sub641 to i32*, !dbg !395
  %stack_num643 = load i32, i32* %stack_num, align 4, !dbg !396
  %sub644 = sub i32 %stack_num643, 1, !dbg !396
  %array_cast645 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !396
  %gep646 = getelementptr %ZVALUE, %ZVALUE* %array_cast645, i32 %sub644, !dbg !396
  %element647 = load %ZVALUE, %ZVALUE* %gep646, align 4, !dbg !396
  %field648 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep646, i32 0, i32 1, !dbg !396
  %value649 = load %come_anon86, %come_anon86* %field648, align 4, !dbg !396
  %field650 = getelementptr inbounds %come_anon86, %come_anon86* %field648, i32 0, i32 0, !dbg !396
  %icastO651 = bitcast i64* %field650 to i1*, !dbg !396
  %boolValue652 = load i1, i1* %icastO651, align 1, !dbg !396
  store i1 %boolValue652, i1* %exp, align 1, !dbg !266
  %stack_num653 = load i32, i32* %stack_num, align 4, !dbg !397
  %sub654 = sub i32 %stack_num653, 1, !dbg !397
  store i32 %sub654, i32* %stack_num, align 4, !dbg !397
  %add655 = add i32 %sub654, 1, !dbg !397
  %exp656 = load i1, i1* %exp, align 1, !dbg !398
  %logical_denial657 = icmp eq i1 %exp656, false, !dbg !398
  br i1 %logical_denial657, label %cond_jump_then658, label %cond_end659, !dbg !398

cond_else_blockX624:                              ; preds = %after_break673, %cond_else_blockX594
  %eqtmp676 = icmp eq i32 %derefference_value, 13, !dbg !399
  br i1 %eqtmp676, label %cond_then_block674, label %cond_else_blockX675, !dbg !399

cond_jump_then658:                                ; preds = %cond_then_block623
  %p660 = load i32*, i32** %p, align 8, !dbg !400
  %value661 = load i32, i32* %value635, align 4, !dbg !400
  %ptrToIntC662 = ptrtoint i32* %p660 to i64, !dbg !400
  %sext663 = sext i32 %value661 to i64, !dbg !400
  %mul664 = mul i64 %sext663, 4, !dbg !400
  %add665 = add i64 %ptrToIntC662, %mul664, !dbg !400
  %intToPtr666 = inttoptr i64 %add665 to i32*, !dbg !400
  store i32* %intToPtr666, i32** %p, align 8, !dbg !400
  %value667 = load i32, i32* %value635, align 4, !dbg !400
  %ptrToIntI668 = ptrtoint i32* %intToPtr666 to i64, !dbg !400
  %sext669 = sext i32 %value667 to i64, !dbg !400
  %mul670 = mul i64 %sext669, 4, !dbg !400
  %sub671 = sub i64 %ptrToIntI668, %mul670, !dbg !400
  %iintToPtr672 = inttoptr i64 %sub671 to i32*, !dbg !400
  br label %cond_end659, !dbg !400

cond_end659:                                      ; preds = %cond_jump_then658, %cond_then_block623
  br label %end_blockX, !dbg !401

after_break673:                                   ; No predecessors!
  br label %cond_else_blockX624, !dbg !399

cond_then_block674:                               ; preds = %cond_else_blockX624
  %p677 = load i32*, i32** %p, align 8, !dbg !402
  %ptrToIntC678 = ptrtoint i32* %p677 to i64, !dbg !402
  %add679 = add i64 %ptrToIntC678, 4, !dbg !402
  %intToPtr680 = inttoptr i64 %add679 to i32*, !dbg !402
  store i32* %intToPtr680, i32** %p, align 8, !dbg !402
  %ptrToIntI681 = ptrtoint i32* %intToPtr680 to i64, !dbg !402
  %sub682 = sub i64 %ptrToIntI681, 4, !dbg !402
  %iintToPtr683 = inttoptr i64 %sub682 to i32*, !dbg !402
  %stack_num684 = load i32, i32* %stack_num, align 4, !dbg !403
  %sub685 = sub i32 %stack_num684, 1, !dbg !403
  %array_cast686 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !403
  %gep687 = getelementptr %ZVALUE, %ZVALUE* %array_cast686, i32 %sub685, !dbg !403
  %element688 = load %ZVALUE, %ZVALUE* %gep687, align 4, !dbg !403
  %stack_num689 = load i32, i32* %stack_num, align 4, !dbg !403
  %sub690 = sub i32 %stack_num689, 1, !dbg !403
  %array_cast691 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !403
  %gep692 = getelementptr %ZVALUE, %ZVALUE* %array_cast691, i32 %sub690, !dbg !403
  %element693 = load %ZVALUE, %ZVALUE* %gep692, align 4, !dbg !403
  %field694 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep692, i32 0, i32 1, !dbg !403
  %value695 = load %come_anon86, %come_anon86* %field694, align 4, !dbg !403
  %field696 = getelementptr inbounds %come_anon86, %come_anon86* %field694, i32 0, i32 0, !dbg !403
  %icastO697 = bitcast i64* %field696 to i32*, !dbg !403
  %intValue698 = load i32, i32* %icastO697, align 4, !dbg !403
  store i32 %intValue698, i32* %lvalue699, align 4, !dbg !266
  %stack_num700 = load i32, i32* %stack_num, align 4, !dbg !404
  %sub701 = sub i32 %stack_num700, 2, !dbg !404
  %array_cast702 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !404
  %gep703 = getelementptr %ZVALUE, %ZVALUE* %array_cast702, i32 %sub701, !dbg !404
  %element704 = load %ZVALUE, %ZVALUE* %gep703, align 4, !dbg !404
  %stack_num705 = load i32, i32* %stack_num, align 4, !dbg !404
  %sub706 = sub i32 %stack_num705, 2, !dbg !404
  %array_cast707 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !404
  %gep708 = getelementptr %ZVALUE, %ZVALUE* %array_cast707, i32 %sub706, !dbg !404
  %element709 = load %ZVALUE, %ZVALUE* %gep708, align 4, !dbg !404
  %field710 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep708, i32 0, i32 1, !dbg !404
  %value711 = load %come_anon86, %come_anon86* %field710, align 4, !dbg !404
  %field712 = getelementptr inbounds %come_anon86, %come_anon86* %field710, i32 0, i32 0, !dbg !404
  %icastO713 = bitcast i64* %field712 to i32*, !dbg !404
  %intValue714 = load i32, i32* %icastO713, align 4, !dbg !404
  store i32 %intValue714, i32* %rvalue715, align 4, !dbg !266
  %stack_num716 = load i32, i32* %stack_num, align 4, !dbg !405
  %sub717 = sub i32 %stack_num716, 2, !dbg !405
  store i32 %sub717, i32* %stack_num, align 4, !dbg !405
  %add718 = add i32 %sub717, 2, !dbg !405
  %stack_num719 = load i32, i32* %stack_num, align 4, !dbg !406
  %array_cast720 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !406
  %gep721 = getelementptr %ZVALUE, %ZVALUE* %array_cast720, i32 %stack_num719, !dbg !406
  %element722 = load %ZVALUE, %ZVALUE* %gep721, align 4, !dbg !406
  %field723 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep721, i32 0, i32 0, !dbg !406
  store i32 1, i32* %field723, align 4, !dbg !406
  %stack_num724 = load i32, i32* %stack_num, align 4, !dbg !407
  %array_cast725 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !407
  %gep726 = getelementptr %ZVALUE, %ZVALUE* %array_cast725, i32 %stack_num724, !dbg !407
  %element727 = load %ZVALUE, %ZVALUE* %gep726, align 4, !dbg !407
  %field728 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep726, i32 0, i32 1, !dbg !407
  %value729 = load %come_anon86, %come_anon86* %field728, align 4, !dbg !407
  %lvalue730 = load i32, i32* %lvalue699, align 4, !dbg !407
  %rvalue731 = load i32, i32* %rvalue715, align 4, !dbg !407
  %eq732 = icmp eq i32 %lvalue730, %rvalue731, !dbg !407
  %field733 = getelementptr inbounds %come_anon86, %come_anon86* %field728, i32 0, i32 0, !dbg !407
  %icastN734 = bitcast i64* %field733 to i1*, !dbg !407
  store i1 %eq732, i1* %icastN734, align 1, !dbg !407
  %stack_num735 = load i32, i32* %stack_num, align 4, !dbg !408
  %add736 = add i32 %stack_num735, 1, !dbg !408
  store i32 %add736, i32* %stack_num, align 4, !dbg !408
  %sub737 = sub i32 %add736, 1, !dbg !408
  br label %end_blockX, !dbg !409

cond_else_blockX675:                              ; preds = %after_break738, %cond_else_blockX624
  %eqtmp741 = icmp eq i32 %derefference_value, 14, !dbg !410
  br i1 %eqtmp741, label %cond_then_block739, label %cond_else_blockX740, !dbg !410

after_break738:                                   ; No predecessors!
  br label %cond_else_blockX675, !dbg !410

cond_then_block739:                               ; preds = %cond_else_blockX675
  %p742 = load i32*, i32** %p, align 8, !dbg !411
  %ptrToIntC743 = ptrtoint i32* %p742 to i64, !dbg !411
  %add744 = add i64 %ptrToIntC743, 4, !dbg !411
  %intToPtr745 = inttoptr i64 %add744 to i32*, !dbg !411
  store i32* %intToPtr745, i32** %p, align 8, !dbg !411
  %ptrToIntI746 = ptrtoint i32* %intToPtr745 to i64, !dbg !411
  %sub747 = sub i64 %ptrToIntI746, 4, !dbg !411
  %iintToPtr748 = inttoptr i64 %sub747 to i32*, !dbg !411
  %stack_num749 = load i32, i32* %stack_num, align 4, !dbg !412
  %sub750 = sub i32 %stack_num749, 1, !dbg !412
  %array_cast751 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !412
  %gep752 = getelementptr %ZVALUE, %ZVALUE* %array_cast751, i32 %sub750, !dbg !412
  %element753 = load %ZVALUE, %ZVALUE* %gep752, align 4, !dbg !412
  %stack_num754 = load i32, i32* %stack_num, align 4, !dbg !412
  %sub755 = sub i32 %stack_num754, 1, !dbg !412
  %array_cast756 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !412
  %gep757 = getelementptr %ZVALUE, %ZVALUE* %array_cast756, i32 %sub755, !dbg !412
  %element758 = load %ZVALUE, %ZVALUE* %gep757, align 4, !dbg !412
  %field759 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep757, i32 0, i32 1, !dbg !412
  %value760 = load %come_anon86, %come_anon86* %field759, align 4, !dbg !412
  %field761 = getelementptr inbounds %come_anon86, %come_anon86* %field759, i32 0, i32 0, !dbg !412
  %icastO762 = bitcast i64* %field761 to i32*, !dbg !412
  %intValue763 = load i32, i32* %icastO762, align 4, !dbg !412
  store i32 %intValue763, i32* %lvalue764, align 4, !dbg !266
  %stack_num765 = load i32, i32* %stack_num, align 4, !dbg !413
  %sub766 = sub i32 %stack_num765, 2, !dbg !413
  %array_cast767 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !413
  %gep768 = getelementptr %ZVALUE, %ZVALUE* %array_cast767, i32 %sub766, !dbg !413
  %element769 = load %ZVALUE, %ZVALUE* %gep768, align 4, !dbg !413
  %stack_num770 = load i32, i32* %stack_num, align 4, !dbg !413
  %sub771 = sub i32 %stack_num770, 2, !dbg !413
  %array_cast772 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !413
  %gep773 = getelementptr %ZVALUE, %ZVALUE* %array_cast772, i32 %sub771, !dbg !413
  %element774 = load %ZVALUE, %ZVALUE* %gep773, align 4, !dbg !413
  %field775 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep773, i32 0, i32 1, !dbg !413
  %value776 = load %come_anon86, %come_anon86* %field775, align 4, !dbg !413
  %field777 = getelementptr inbounds %come_anon86, %come_anon86* %field775, i32 0, i32 0, !dbg !413
  %icastO778 = bitcast i64* %field777 to i32*, !dbg !413
  %intValue779 = load i32, i32* %icastO778, align 4, !dbg !413
  store i32 %intValue779, i32* %rvalue780, align 4, !dbg !266
  %stack_num781 = load i32, i32* %stack_num, align 4, !dbg !414
  %sub782 = sub i32 %stack_num781, 2, !dbg !414
  store i32 %sub782, i32* %stack_num, align 4, !dbg !414
  %add783 = add i32 %sub782, 2, !dbg !414
  %stack_num784 = load i32, i32* %stack_num, align 4, !dbg !415
  %array_cast785 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !415
  %gep786 = getelementptr %ZVALUE, %ZVALUE* %array_cast785, i32 %stack_num784, !dbg !415
  %element787 = load %ZVALUE, %ZVALUE* %gep786, align 4, !dbg !415
  %field788 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep786, i32 0, i32 0, !dbg !415
  store i32 1, i32* %field788, align 4, !dbg !415
  %stack_num789 = load i32, i32* %stack_num, align 4, !dbg !416
  %array_cast790 = bitcast [1024 x %ZVALUE]* %stack to %ZVALUE*, !dbg !416
  %gep791 = getelementptr %ZVALUE, %ZVALUE* %array_cast790, i32 %stack_num789, !dbg !416
  %element792 = load %ZVALUE, %ZVALUE* %gep791, align 4, !dbg !416
  %field793 = getelementptr inbounds %ZVALUE, %ZVALUE* %gep791, i32 0, i32 1, !dbg !416
  %value794 = load %come_anon86, %come_anon86* %field793, align 4, !dbg !416
  %lvalue795 = load i32, i32* %lvalue764, align 4, !dbg !416
  %rvalue796 = load i32, i32* %rvalue780, align 4, !dbg !416
  %not_eq = icmp ne i32 %lvalue795, %rvalue796, !dbg !416
  %field797 = getelementptr inbounds %come_anon86, %come_anon86* %field793, i32 0, i32 0, !dbg !416
  %icastN798 = bitcast i64* %field797 to i1*, !dbg !416
  store i1 %not_eq, i1* %icastN798, align 1, !dbg !416
  %stack_num799 = load i32, i32* %stack_num, align 4, !dbg !417
  %add800 = add i32 %stack_num799, 1, !dbg !417
  store i32 %add800, i32* %stack_num, align 4, !dbg !417
  %sub801 = sub i32 %add800, 1, !dbg !417
  br label %end_blockX, !dbg !418

cond_else_blockX740:                              ; preds = %after_break802, %cond_else_blockX675
  br label %cond_then_block803, !dbg !419

after_break802:                                   ; No predecessors!
  br label %cond_else_blockX740, !dbg !419

cond_then_block803:                               ; preds = %cond_else_blockX740
  %p805 = load i32*, i32** %p, align 8, !dbg !420
  %derefference_value806 = load i32, i32* %p805, align 4, !dbg !420
  %fun_result807 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @"invalid op code %d\0A.2", i32 0, i32 0), i32 %derefference_value806), !dbg !420
  call void @exit(i32 1), !dbg !421
  br label %cond_else_blockX804, !dbg !421

cond_else_blockX804:                              ; preds = %cond_then_block803
  br label %end_blockX, !dbg !421

cond_jump_then810:                                ; preds = %end_blockX
  %stack_num811 = load i32, i32* %stack_num, align 4, !dbg !279
  %gteq = icmp sge i32 %stack_num811, 1024, !dbg !279
  %oror812 = or i1 %le809, %gteq, !dbg !279
  store i1 %oror812, i1* %oror, align 1, !dbg !279
  br label %cond_jump_end, !dbg !279

cond_jump_end:                                    ; preds = %cond_jump_then810, %end_blockX
  %oror_result_value = load i1, i1* %oror, align 1, !dbg !279
  br i1 %oror_result_value, label %cond_jump_then813, label %cond_end814, !dbg !279

cond_jump_then813:                                ; preds = %cond_jump_end
  %stderr815 = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !422
  %fun_result816 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr815, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @"invalid stack num\0A", i32 0, i32 0)), !dbg !422
  ret i1 false, !dbg !423

cond_end814:                                      ; preds = %cond_jump_end
  br label %loop_top_block33, !dbg !423
}

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

declare %sNode* @exp_node_v10(%sParserInfo*)

declare i1 @compile_v10(%sNode*, %buffer*, %sParserInfo*)

declare i1 @expression_v11(%sNode**, %sParserInfo*)

declare i1 @compile_v11(%sNode*, %buffer*, %sParserInfo*)

define internal %map_charp_ZVALUE* @map_initialize_charp_ZVALUE(%map_charp_ZVALUE* %0) {
entry:
  %i = alloca i32, align 4, !dbg !262
  %self = alloca %map_charp_ZVALUE*, align 8, !dbg !262
  store %map_charp_ZVALUE* %0, %map_charp_ZVALUE** %self, align 8, !dbg !262
  %self1 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !262
  %fun_result = call i8* @GC_malloc(i64 1024), !dbg !262
  %obj = bitcast i8* %fun_result to i8**, !dbg !262
  %field = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self1, i32 0, i32 0, !dbg !262
  store i8** %obj, i8*** %field, align 8, !dbg !262
  %self2 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !262
  %fun_result3 = call i8* @GC_malloc(i64 1536), !dbg !262
  %obj4 = bitcast i8* %fun_result3 to %ZVALUE*, !dbg !262
  %field5 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self2, i32 0, i32 2, !dbg !262
  store %ZVALUE* %obj4, %ZVALUE** %field5, align 8, !dbg !262
  %self6 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !262
  %fun_result7 = call i8* @GC_malloc(i64 128), !dbg !262
  %obj8 = bitcast i8* %fun_result7 to i1*, !dbg !262
  %field9 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self6, i32 0, i32 1, !dbg !262
  store i1* %obj8, i1** %field9, align 8, !dbg !262
  store i32 0, i32* %i, align 4, !dbg !262
  br label %loop_top_block, !dbg !262

loop_top_block:                                   ; preds = %cond_then_block, %entry
  %i10 = load i32, i32* %i, align 4, !dbg !262
  %le = icmp slt i32 %i10, 128, !dbg !262
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !262

cond_then_block:                                  ; preds = %loop_top_block
  %self11 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !262
  %field12 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self11, i32 0, i32 1, !dbg !262
  %item_existance = load i1*, i1** %field12, align 8, !dbg !262
  %i13 = load i32, i32* %i, align 4, !dbg !262
  %element_address = getelementptr i1, i1* %item_existance, i32 %i13, !dbg !262
  store i1 false, i1* %element_address, align 1, !dbg !262
  %i14 = load i32, i32* %i, align 4, !dbg !262
  %add = add i32 %i14, 1, !dbg !262
  store i32 %add, i32* %i, align 4, !dbg !262
  %sub = sub i32 %add, 1, !dbg !262
  br label %loop_top_block, !dbg !262

cond_end_block:                                   ; preds = %loop_top_block
  %self15 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !262
  %field16 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self15, i32 0, i32 3, !dbg !262
  store i32 128, i32* %field16, align 4, !dbg !262
  %self17 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !262
  %field18 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self17, i32 0, i32 4, !dbg !262
  store i32 0, i32* %field18, align 4, !dbg !262
  %self19 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !262
  %field20 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self19, i32 0, i32 5, !dbg !262
  store i32 0, i32* %field20, align 4, !dbg !262
  %self21 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !262
  ret %map_charp_ZVALUE* %self21, !dbg !262
}

define void @show_zvalue(%ZVALUE %0) !dbg !424 {
entry:
  %value = alloca %ZVALUE, align 8, !dbg !427
  store %ZVALUE %0, %ZVALUE* %value, align 4, !dbg !427
  %value1 = load %ZVALUE, %ZVALUE* %value, align 4, !dbg !428
  %field = getelementptr inbounds %ZVALUE, %ZVALUE* %value, i32 0, i32 0, !dbg !428
  %kind = load i32, i32* %field, align 4, !dbg !428
  %eqtmp = icmp eq i32 %kind, 0, !dbg !429
  br i1 %eqtmp, label %cond_then_block, label %cond_else_blockX, !dbg !429

end_blockX:                                       ; preds = %cond_else_blockX7, %cond_then_block6, %cond_then_block
  ret void, !dbg !430

cond_then_block:                                  ; preds = %entry
  %value2 = load %ZVALUE, %ZVALUE* %value, align 4, !dbg !431
  %field3 = getelementptr inbounds %ZVALUE, %ZVALUE* %value, i32 0, i32 1, !dbg !431
  %value4 = load %come_anon86, %come_anon86* %field3, align 4, !dbg !431
  %field5 = getelementptr inbounds %come_anon86, %come_anon86* %field3, i32 0, i32 0, !dbg !431
  %icastO = bitcast i64* %field5 to i32*, !dbg !431
  %intValue = load i32, i32* %icastO, align 4, !dbg !431
  %fun_result = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @"int value %d\0A", i32 0, i32 0), i32 %intValue), !dbg !431
  br label %end_blockX, !dbg !432

cond_else_blockX:                                 ; preds = %after_break, %entry
  %eqtmp8 = icmp eq i32 %kind, 3, !dbg !433
  br i1 %eqtmp8, label %cond_then_block6, label %cond_else_blockX7, !dbg !433

after_break:                                      ; No predecessors!
  br label %cond_else_blockX, !dbg !433

cond_then_block6:                                 ; preds = %cond_else_blockX
  %value9 = load %ZVALUE, %ZVALUE* %value, align 4, !dbg !434
  %field10 = getelementptr inbounds %ZVALUE, %ZVALUE* %value, i32 0, i32 1, !dbg !434
  %value11 = load %come_anon86, %come_anon86* %field10, align 4, !dbg !434
  %field12 = getelementptr inbounds %come_anon86, %come_anon86* %field10, i32 0, i32 0, !dbg !434
  %icastO13 = bitcast i64* %field12 to i8**, !dbg !434
  %stringValue = load i8*, i8** %icastO13, align 8, !dbg !434
  %fun_result14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @"string value %s\0A", i32 0, i32 0), i8* %stringValue), !dbg !434
  br label %end_blockX, !dbg !430

cond_else_blockX7:                                ; preds = %after_break15, %cond_else_blockX
  br label %end_blockX, !dbg !430

after_break15:                                    ; No predecessors!
  br label %cond_else_blockX7, !dbg !430
}

define void @print_op(i32 %0) !dbg !435 {
entry:
  %op = alloca i32, align 4, !dbg !436
  store i32 %0, i32* %op, align 4, !dbg !436
  %op1 = load i32, i32* %op, align 4, !dbg !437
  %eqtmp = icmp eq i32 %op1, 6, !dbg !438
  br i1 %eqtmp, label %cond_then_block, label %cond_else_blockX, !dbg !438

end_blockX:                                       ; preds = %cond_else_blockX58, %cond_then_block57, %cond_then_block52, %cond_then_block47, %cond_then_block42, %cond_then_block37, %cond_then_block32, %cond_then_block27, %cond_then_block22, %cond_then_block17, %cond_then_block12, %cond_then_block7, %cond_then_block2, %cond_then_block
  ret void, !dbg !439

cond_then_block:                                  ; preds = %entry
  %fun_result = call i32 @puts(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @OP_POP, i32 0, i32 0)), !dbg !440
  br label %end_blockX, !dbg !441

cond_else_blockX:                                 ; preds = %after_break, %entry
  %eqtmp4 = icmp eq i32 %op1, 1, !dbg !442
  br i1 %eqtmp4, label %cond_then_block2, label %cond_else_blockX3, !dbg !442

after_break:                                      ; No predecessors!
  br label %cond_else_blockX, !dbg !442

cond_then_block2:                                 ; preds = %cond_else_blockX
  %fun_result5 = call i32 @puts(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @OP_INT_VALUE, i32 0, i32 0)), !dbg !443
  br label %end_blockX, !dbg !444

cond_else_blockX3:                                ; preds = %after_break6, %cond_else_blockX
  %eqtmp9 = icmp eq i32 %op1, 2, !dbg !445
  br i1 %eqtmp9, label %cond_then_block7, label %cond_else_blockX8, !dbg !445

after_break6:                                     ; No predecessors!
  br label %cond_else_blockX3, !dbg !445

cond_then_block7:                                 ; preds = %cond_else_blockX3
  %fun_result10 = call i32 @puts(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @OP_ADD, i32 0, i32 0)), !dbg !446
  br label %end_blockX, !dbg !447

cond_else_blockX8:                                ; preds = %after_break11, %cond_else_blockX3
  %eqtmp14 = icmp eq i32 %op1, 3, !dbg !448
  br i1 %eqtmp14, label %cond_then_block12, label %cond_else_blockX13, !dbg !448

after_break11:                                    ; No predecessors!
  br label %cond_else_blockX8, !dbg !448

cond_then_block12:                                ; preds = %cond_else_blockX8
  %fun_result15 = call i32 @puts(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @OP_SUB, i32 0, i32 0)), !dbg !449
  br label %end_blockX, !dbg !450

cond_else_blockX13:                               ; preds = %after_break16, %cond_else_blockX8
  %eqtmp19 = icmp eq i32 %op1, 4, !dbg !451
  br i1 %eqtmp19, label %cond_then_block17, label %cond_else_blockX18, !dbg !451

after_break16:                                    ; No predecessors!
  br label %cond_else_blockX13, !dbg !451

cond_then_block17:                                ; preds = %cond_else_blockX13
  %fun_result20 = call i32 @puts(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @OP_STRING_VALUE, i32 0, i32 0)), !dbg !452
  br label %end_blockX, !dbg !453

cond_else_blockX18:                               ; preds = %after_break21, %cond_else_blockX13
  %eqtmp24 = icmp eq i32 %op1, 5, !dbg !454
  br i1 %eqtmp24, label %cond_then_block22, label %cond_else_blockX23, !dbg !454

after_break21:                                    ; No predecessors!
  br label %cond_else_blockX18, !dbg !454

cond_then_block22:                                ; preds = %cond_else_blockX18
  %fun_result25 = call i32 @puts(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @OP_PRINT, i32 0, i32 0)), !dbg !455
  br label %end_blockX, !dbg !456

cond_else_blockX23:                               ; preds = %after_break26, %cond_else_blockX18
  %eqtmp29 = icmp eq i32 %op1, 8, !dbg !457
  br i1 %eqtmp29, label %cond_then_block27, label %cond_else_blockX28, !dbg !457

after_break26:                                    ; No predecessors!
  br label %cond_else_blockX23, !dbg !457

cond_then_block27:                                ; preds = %cond_else_blockX23
  %fun_result30 = call i32 @puts(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OP_LOAD, i32 0, i32 0)), !dbg !458
  br label %end_blockX, !dbg !459

cond_else_blockX28:                               ; preds = %after_break31, %cond_else_blockX23
  %eqtmp34 = icmp eq i32 %op1, 7, !dbg !460
  br i1 %eqtmp34, label %cond_then_block32, label %cond_else_blockX33, !dbg !460

after_break31:                                    ; No predecessors!
  br label %cond_else_blockX28, !dbg !460

cond_then_block32:                                ; preds = %cond_else_blockX28
  %fun_result35 = call i32 @puts(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @OP_STORE, i32 0, i32 0)), !dbg !461
  br label %end_blockX, !dbg !462

cond_else_blockX33:                               ; preds = %after_break36, %cond_else_blockX28
  %eqtmp39 = icmp eq i32 %op1, 9, !dbg !463
  br i1 %eqtmp39, label %cond_then_block37, label %cond_else_blockX38, !dbg !463

after_break36:                                    ; No predecessors!
  br label %cond_else_blockX33, !dbg !463

cond_then_block37:                                ; preds = %cond_else_blockX33
  %fun_result40 = call i32 @puts(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @OP_FUNCALL, i32 0, i32 0)), !dbg !464
  br label %end_blockX, !dbg !465

cond_else_blockX38:                               ; preds = %after_break41, %cond_else_blockX33
  %eqtmp44 = icmp eq i32 %op1, 10, !dbg !466
  br i1 %eqtmp44, label %cond_then_block42, label %cond_else_blockX43, !dbg !466

after_break41:                                    ; No predecessors!
  br label %cond_else_blockX38, !dbg !466

cond_then_block42:                                ; preds = %cond_else_blockX38
  %fun_result45 = call i32 @puts(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @OP_BOOL_VALUE, i32 0, i32 0)), !dbg !467
  br label %end_blockX, !dbg !468

cond_else_blockX43:                               ; preds = %after_break46, %cond_else_blockX38
  %eqtmp49 = icmp eq i32 %op1, 12, !dbg !469
  br i1 %eqtmp49, label %cond_then_block47, label %cond_else_blockX48, !dbg !469

after_break46:                                    ; No predecessors!
  br label %cond_else_blockX43, !dbg !469

cond_then_block47:                                ; preds = %cond_else_blockX43
  %fun_result50 = call i32 @puts(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @OP_GOTO, i32 0, i32 0)), !dbg !470
  br label %end_blockX, !dbg !471

cond_else_blockX48:                               ; preds = %after_break51, %cond_else_blockX43
  %eqtmp54 = icmp eq i32 %op1, 11, !dbg !472
  br i1 %eqtmp54, label %cond_then_block52, label %cond_else_blockX53, !dbg !472

after_break51:                                    ; No predecessors!
  br label %cond_else_blockX48, !dbg !472

cond_then_block52:                                ; preds = %cond_else_blockX48
  %fun_result55 = call i32 @puts(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @OP_IF, i32 0, i32 0)), !dbg !473
  br label %end_blockX, !dbg !474

cond_else_blockX53:                               ; preds = %after_break56, %cond_else_blockX48
  br label %cond_then_block57, !dbg !475

after_break56:                                    ; No predecessors!
  br label %cond_else_blockX53, !dbg !475

cond_then_block57:                                ; preds = %cond_else_blockX53
  %op59 = load i32, i32* %op, align 4, !dbg !476
  %fun_result60 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @"invalid op code %d\0A", i32 0, i32 0), i32 %op59), !dbg !476
  br label %end_blockX, !dbg !439

cond_else_blockX58:                               ; preds = %after_break61
  br label %end_blockX, !dbg !439

after_break61:                                    ; No predecessors!
  br label %cond_else_blockX58, !dbg !439
}

define internal i8* @map_begin_charp_ZVALUE(%map_charp_ZVALUE* %0) {
entry:
  %self = alloca %map_charp_ZVALUE*, align 8, !dbg !271
  store %map_charp_ZVALUE* %0, %map_charp_ZVALUE** %self, align 8, !dbg !271
  %self1 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !271
  %field = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self1, i32 0, i32 5, !dbg !271
  store i32 0, i32* %field, align 4, !dbg !271
  br label %loop_top_block, !dbg !271

loop_top_block:                                   ; preds = %cond_end, %entry
  %self2 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !271
  %field3 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self2, i32 0, i32 5, !dbg !271
  %it = load i32, i32* %field3, align 4, !dbg !271
  %self4 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !271
  %field5 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self4, i32 0, i32 3, !dbg !271
  %size = load i32, i32* %field5, align 4, !dbg !271
  %le = icmp slt i32 %it, %size, !dbg !271
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !271

cond_then_block:                                  ; preds = %loop_top_block
  %self6 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !271
  %field7 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self6, i32 0, i32 1, !dbg !271
  %item_existance = load i1*, i1** %field7, align 8, !dbg !271
  %self8 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !271
  %field9 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self8, i32 0, i32 5, !dbg !271
  %it10 = load i32, i32* %field9, align 4, !dbg !271
  %element_address = getelementptr inbounds i1, i1* %item_existance, i32 %it10, !dbg !271
  %element = load i1, i1* %element_address, align 1, !dbg !271
  br i1 %element, label %cond_jump_then, label %cond_end, !dbg !271

cond_end_block:                                   ; preds = %loop_top_block
  ret i8* null, !dbg !271

cond_jump_then:                                   ; preds = %cond_then_block
  %self11 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !271
  %field12 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self11, i32 0, i32 0, !dbg !271
  %keys = load i8**, i8*** %field12, align 8, !dbg !271
  %self13 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !271
  %self14 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !271
  %field15 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self14, i32 0, i32 5, !dbg !271
  %it16 = load i32, i32* %field15, align 4, !dbg !271
  %add = add i32 %it16, 1, !dbg !271
  %field17 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self13, i32 0, i32 5, !dbg !271
  store i32 %add, i32* %field17, align 4, !dbg !271
  %sub = sub i32 %add, 1, !dbg !271
  %element_address18 = getelementptr inbounds i8*, i8** %keys, i32 %sub, !dbg !271
  %element19 = load i8*, i8** %element_address18, align 8, !dbg !271
  ret i8* %element19, !dbg !271

cond_end:                                         ; preds = %cond_then_block
  %self20 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !271
  %self21 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !271
  %field22 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self21, i32 0, i32 5, !dbg !271
  %it23 = load i32, i32* %field22, align 4, !dbg !271
  %add24 = add i32 %it23, 1, !dbg !271
  %field25 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self20, i32 0, i32 5, !dbg !271
  store i32 %add24, i32* %field25, align 4, !dbg !271
  %sub26 = sub i32 %add24, 1, !dbg !271
  br label %loop_top_block, !dbg !271
}

define internal i1 @map_end_charp_ZVALUE(%map_charp_ZVALUE* %0) {
entry:
  %i = alloca i32, align 4, !dbg !271
  %count = alloca i32, align 4, !dbg !271
  %self = alloca %map_charp_ZVALUE*, align 8, !dbg !271
  store %map_charp_ZVALUE* %0, %map_charp_ZVALUE** %self, align 8, !dbg !271
  store i32 0, i32* %count, align 4, !dbg !271
  %self1 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !271
  %field = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self1, i32 0, i32 5, !dbg !271
  %it = load i32, i32* %field, align 4, !dbg !271
  %sub = sub i32 %it, 1, !dbg !271
  store i32 %sub, i32* %i, align 4, !dbg !271
  br label %loop_top_block, !dbg !271

loop_top_block:                                   ; preds = %cond_end, %entry
  %i2 = load i32, i32* %i, align 4, !dbg !271
  %self3 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !271
  %field4 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self3, i32 0, i32 3, !dbg !271
  %size = load i32, i32* %field4, align 4, !dbg !271
  %le = icmp slt i32 %i2, %size, !dbg !271
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !271

cond_then_block:                                  ; preds = %loop_top_block
  %self5 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !271
  %field6 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self5, i32 0, i32 1, !dbg !271
  %item_existance = load i1*, i1** %field6, align 8, !dbg !271
  %i7 = load i32, i32* %i, align 4, !dbg !271
  %element_address = getelementptr inbounds i1, i1* %item_existance, i32 %i7, !dbg !271
  %element = load i1, i1* %element_address, align 1, !dbg !271
  br i1 %element, label %cond_jump_then, label %cond_end, !dbg !271

cond_end_block:                                   ; preds = %loop_top_block
  %count13 = load i32, i32* %count, align 4, !dbg !271
  %eq = icmp eq i32 %count13, 0, !dbg !271
  br i1 %eq, label %cond_jump_then14, label %cond_else_block, !dbg !271

cond_jump_then:                                   ; preds = %cond_then_block
  %count8 = load i32, i32* %count, align 4, !dbg !271
  %add = add i32 %count8, 1, !dbg !271
  store i32 %add, i32* %count, align 4, !dbg !271
  %sub9 = sub i32 %add, 1, !dbg !271
  br label %cond_end, !dbg !271

cond_end:                                         ; preds = %cond_jump_then, %cond_then_block
  %i10 = load i32, i32* %i, align 4, !dbg !271
  %add11 = add i32 %i10, 1, !dbg !271
  store i32 %add11, i32* %i, align 4, !dbg !271
  %sub12 = sub i32 %add11, 1, !dbg !271
  br label %loop_top_block, !dbg !271

cond_jump_then14:                                 ; preds = %cond_end_block
  ret i1 true, !dbg !271

cond_else_block:                                  ; preds = %cond_end_block
  ret i1 false, !dbg !271

cond_end15:                                       ; No predecessors!
  ret i1 false, !dbg !271
}

define internal %ZVALUE @map_at_charp_ZVALUE(%map_charp_ZVALUE* %0, i8* %1, %ZVALUE %2) {
entry:
  %it = alloca i32, align 4, !dbg !274
  %hash = alloca i32, align 4, !dbg !274
  %self = alloca %map_charp_ZVALUE*, align 8, !dbg !274
  store %map_charp_ZVALUE* %0, %map_charp_ZVALUE** %self, align 8, !dbg !274
  %key = alloca i8*, align 8, !dbg !274
  store i8* %1, i8** %key, align 8, !dbg !274
  %default_value = alloca %ZVALUE, align 8, !dbg !274
  store %ZVALUE %2, %ZVALUE* %default_value, align 4, !dbg !274
  %key1 = load i8*, i8** %key, align 8, !dbg !274
  %fun_result = call i32 @char_get_hash_key(i8* %key1), !dbg !274
  %self2 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !274
  %field = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self2, i32 0, i32 3, !dbg !274
  %size = load i32, i32* %field, align 4, !dbg !274
  %div = srem i32 %fun_result, %size, !dbg !274
  store i32 %div, i32* %hash, align 4, !dbg !274
  %hash3 = load i32, i32* %hash, align 4, !dbg !274
  store i32 %hash3, i32* %it, align 4, !dbg !274
  br label %loop_top_block, !dbg !274

loop_top_block:                                   ; preds = %cond_end, %entry
  br i1 true, label %cond_then_block, label %cond_end_block, !dbg !274

cond_then_block:                                  ; preds = %loop_top_block
  %self4 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !274
  %field5 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self4, i32 0, i32 1, !dbg !274
  %item_existance = load i1*, i1** %field5, align 8, !dbg !274
  %it6 = load i32, i32* %it, align 4, !dbg !274
  %element_address = getelementptr inbounds i1, i1* %item_existance, i32 %it6, !dbg !274
  %element = load i1, i1* %element_address, align 1, !dbg !274
  br i1 %element, label %cond_jump_then, label %cond_else_block, !dbg !274

cond_end_block:                                   ; preds = %loop_top_block
  %default_value32 = load %ZVALUE, %ZVALUE* %default_value, align 4, !dbg !274
  ret %ZVALUE %default_value32, !dbg !274

cond_jump_then:                                   ; preds = %cond_then_block
  %self7 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !274
  %field8 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self7, i32 0, i32 0, !dbg !274
  %keys = load i8**, i8*** %field8, align 8, !dbg !274
  %it9 = load i32, i32* %it, align 4, !dbg !274
  %element_address10 = getelementptr inbounds i8*, i8** %keys, i32 %it9, !dbg !274
  %element11 = load i8*, i8** %element_address10, align 8, !dbg !274
  %key12 = load i8*, i8** %key, align 8, !dbg !274
  %fun_result13 = call i1 @char_equals(i8* %element11, i8* %key12), !dbg !274
  br i1 %fun_result13, label %cond_jump_then14, label %cond_end15, !dbg !274

cond_else_block:                                  ; preds = %cond_then_block
  %default_value31 = load %ZVALUE, %ZVALUE* %default_value, align 4, !dbg !274
  ret %ZVALUE %default_value31, !dbg !274

cond_end:                                         ; preds = %cond_end27
  br label %loop_top_block, !dbg !274

cond_jump_then14:                                 ; preds = %cond_jump_then
  %self16 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !274
  %field17 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self16, i32 0, i32 2, !dbg !274
  %items = load %ZVALUE*, %ZVALUE** %field17, align 8, !dbg !274
  %it18 = load i32, i32* %it, align 4, !dbg !274
  %element_address19 = getelementptr inbounds %ZVALUE, %ZVALUE* %items, i32 %it18, !dbg !274
  %element20 = load %ZVALUE, %ZVALUE* %element_address19, align 4, !dbg !274
  ret %ZVALUE %element20, !dbg !274

cond_end15:                                       ; preds = %cond_jump_then
  %it21 = load i32, i32* %it, align 4, !dbg !274
  %add = add i32 %it21, 1, !dbg !274
  store i32 %add, i32* %it, align 4, !dbg !274
  %sub = sub i32 %add, 1, !dbg !274
  %it22 = load i32, i32* %it, align 4, !dbg !274
  %self23 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !274
  %field24 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self23, i32 0, i32 3, !dbg !274
  %size25 = load i32, i32* %field24, align 4, !dbg !274
  %gteq = icmp sge i32 %it22, %size25, !dbg !274
  br i1 %gteq, label %cond_jump_then26, label %cond_jump_elif0, !dbg !274

cond_jump_then26:                                 ; preds = %cond_end15
  store i32 0, i32* %it, align 4, !dbg !274
  br label %cond_end27, !dbg !274

cond_jump_elif0:                                  ; preds = %cond_end15
  %it28 = load i32, i32* %it, align 4, !dbg !274
  %hash29 = load i32, i32* %hash, align 4, !dbg !274
  %eq = icmp eq i32 %it28, %hash29, !dbg !274
  br i1 %eq, label %cond_jump_elif_then0, label %cond_end27, !dbg !274

cond_jump_elif_then0:                             ; preds = %cond_jump_elif0
  %default_value30 = load %ZVALUE, %ZVALUE* %default_value, align 4, !dbg !274
  ret %ZVALUE %default_value30, !dbg !274

cond_end27:                                       ; preds = %cond_jump_elif0, %cond_jump_then26
  br label %cond_end, !dbg !274
}

define internal void @map_insert_charp_ZVALUE(%map_charp_ZVALUE* %0, i8* %1, %ZVALUE %2) {
entry:
  %it = alloca i32, align 4, !dbg !275
  %hash = alloca i32, align 4, !dbg !275
  %self = alloca %map_charp_ZVALUE*, align 8, !dbg !275
  store %map_charp_ZVALUE* %0, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %key = alloca i8*, align 8, !dbg !275
  store i8* %1, i8** %key, align 8, !dbg !275
  %item = alloca %ZVALUE, align 8, !dbg !275
  store %ZVALUE %2, %ZVALUE* %item, align 4, !dbg !275
  %self1 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self1, i32 0, i32 4, !dbg !275
  %len = load i32, i32* %field, align 4, !dbg !275
  %mul = mul i32 %len, 2, !dbg !275
  %self2 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field3 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self2, i32 0, i32 3, !dbg !275
  %size = load i32, i32* %field3, align 4, !dbg !275
  %gteq = icmp sge i32 %mul, %size, !dbg !275
  br i1 %gteq, label %cond_jump_then, label %cond_end, !dbg !275

cond_jump_then:                                   ; preds = %entry
  %self4 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  call void @map_rehash_charp_ZVALUE(%map_charp_ZVALUE* %self4), !dbg !275
  br label %cond_end, !dbg !275

cond_end:                                         ; preds = %cond_jump_then, %entry
  %key5 = load i8*, i8** %key, align 8, !dbg !275
  %fun_result = call i32 @char_get_hash_key(i8* %key5), !dbg !275
  %self6 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field7 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self6, i32 0, i32 3, !dbg !275
  %size8 = load i32, i32* %field7, align 4, !dbg !275
  %div = srem i32 %fun_result, %size8, !dbg !275
  store i32 %div, i32* %hash, align 4, !dbg !275
  %hash9 = load i32, i32* %hash, align 4, !dbg !275
  store i32 %hash9, i32* %it, align 4, !dbg !275
  br label %loop_top_block, !dbg !275

loop_top_block:                                   ; preds = %cond_end14, %cond_end
  br i1 true, label %cond_then_block, label %cond_end_block, !dbg !275

cond_then_block:                                  ; preds = %loop_top_block
  %self10 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field11 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self10, i32 0, i32 1, !dbg !275
  %item_existance = load i1*, i1** %field11, align 8, !dbg !275
  %it12 = load i32, i32* %it, align 4, !dbg !275
  %element_address = getelementptr inbounds i1, i1* %item_existance, i32 %it12, !dbg !275
  %element = load i1, i1* %element_address, align 1, !dbg !275
  br i1 %element, label %cond_jump_then13, label %cond_else_block, !dbg !275

cond_end_block:                                   ; preds = %cond_else_block, %cond_jump_then22, %loop_top_block
  ret void, !dbg !275

cond_jump_then13:                                 ; preds = %cond_then_block
  %self15 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field16 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self15, i32 0, i32 0, !dbg !275
  %keys = load i8**, i8*** %field16, align 8, !dbg !275
  %it17 = load i32, i32* %it, align 4, !dbg !275
  %element_address18 = getelementptr inbounds i8*, i8** %keys, i32 %it17, !dbg !275
  %element19 = load i8*, i8** %element_address18, align 8, !dbg !275
  %key20 = load i8*, i8** %key, align 8, !dbg !275
  %fun_result21 = call i1 @char_equals(i8* %element19, i8* %key20), !dbg !275
  br i1 %fun_result21, label %cond_jump_then22, label %cond_end23, !dbg !275

cond_else_block:                                  ; preds = %cond_then_block
  %self46 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field47 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self46, i32 0, i32 1, !dbg !275
  %item_existance48 = load i1*, i1** %field47, align 8, !dbg !275
  %it49 = load i32, i32* %it, align 4, !dbg !275
  %element_address50 = getelementptr i1, i1* %item_existance48, i32 %it49, !dbg !275
  store i1 true, i1* %element_address50, align 1, !dbg !275
  %self51 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field52 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self51, i32 0, i32 0, !dbg !275
  %keys53 = load i8**, i8*** %field52, align 8, !dbg !275
  %it54 = load i32, i32* %it, align 4, !dbg !275
  %key55 = load i8*, i8** %key, align 8, !dbg !275
  %element_address56 = getelementptr i8*, i8** %keys53, i32 %it54, !dbg !275
  store i8* %key55, i8** %element_address56, align 8, !dbg !275
  %self57 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field58 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self57, i32 0, i32 2, !dbg !275
  %items59 = load %ZVALUE*, %ZVALUE** %field58, align 8, !dbg !275
  %it60 = load i32, i32* %it, align 4, !dbg !275
  %item61 = load %ZVALUE, %ZVALUE* %item, align 4, !dbg !275
  %element_address62 = getelementptr %ZVALUE, %ZVALUE* %items59, i32 %it60, !dbg !275
  store %ZVALUE %item61, %ZVALUE* %element_address62, align 4, !dbg !275
  %self63 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %self64 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field65 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self64, i32 0, i32 4, !dbg !275
  %len66 = load i32, i32* %field65, align 4, !dbg !275
  %add67 = add i32 %len66, 1, !dbg !275
  %field68 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self63, i32 0, i32 4, !dbg !275
  store i32 %add67, i32* %field68, align 4, !dbg !275
  %sub69 = sub i32 %add67, 1, !dbg !275
  br label %cond_end_block, !dbg !275

cond_end14:                                       ; preds = %after_break70, %cond_end42
  br label %loop_top_block, !dbg !275

cond_jump_then22:                                 ; preds = %cond_jump_then13
  %self24 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field25 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self24, i32 0, i32 0, !dbg !275
  %keys26 = load i8**, i8*** %field25, align 8, !dbg !275
  %it27 = load i32, i32* %it, align 4, !dbg !275
  %key28 = load i8*, i8** %key, align 8, !dbg !275
  %element_address29 = getelementptr i8*, i8** %keys26, i32 %it27, !dbg !275
  store i8* %key28, i8** %element_address29, align 8, !dbg !275
  %self30 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field31 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self30, i32 0, i32 2, !dbg !275
  %items = load %ZVALUE*, %ZVALUE** %field31, align 8, !dbg !275
  %it32 = load i32, i32* %it, align 4, !dbg !275
  %item33 = load %ZVALUE, %ZVALUE* %item, align 4, !dbg !275
  %element_address34 = getelementptr %ZVALUE, %ZVALUE* %items, i32 %it32, !dbg !275
  store %ZVALUE %item33, %ZVALUE* %element_address34, align 4, !dbg !275
  br label %cond_end_block, !dbg !275

cond_end23:                                       ; preds = %after_break, %cond_jump_then13
  %it35 = load i32, i32* %it, align 4, !dbg !275
  %add = add i32 %it35, 1, !dbg !275
  store i32 %add, i32* %it, align 4, !dbg !275
  %sub = sub i32 %add, 1, !dbg !275
  %it36 = load i32, i32* %it, align 4, !dbg !275
  %self37 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field38 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self37, i32 0, i32 3, !dbg !275
  %size39 = load i32, i32* %field38, align 4, !dbg !275
  %gteq40 = icmp sge i32 %it36, %size39, !dbg !275
  br i1 %gteq40, label %cond_jump_then41, label %cond_jump_elif0, !dbg !275

after_break:                                      ; No predecessors!
  br label %cond_end23, !dbg !275

cond_jump_then41:                                 ; preds = %cond_end23
  store i32 0, i32* %it, align 4, !dbg !275
  br label %cond_end42, !dbg !275

cond_jump_elif0:                                  ; preds = %cond_end23
  %it43 = load i32, i32* %it, align 4, !dbg !275
  %hash44 = load i32, i32* %hash, align 4, !dbg !275
  %eq = icmp eq i32 %it43, %hash44, !dbg !275
  br i1 %eq, label %cond_jump_elif_then0, label %cond_end42, !dbg !275

cond_jump_elif_then0:                             ; preds = %cond_jump_elif0
  %stderr = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !275
  %fun_result45 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @"unexpected error in map.insert\0A", i32 0, i32 0)), !dbg !275
  call void @exit(i32 2), !dbg !275
  br label %cond_end42, !dbg !275

cond_end42:                                       ; preds = %cond_jump_elif_then0, %cond_jump_elif0, %cond_jump_then41
  br label %cond_end14, !dbg !275

after_break70:                                    ; No predecessors!
  br label %cond_end14, !dbg !275
}

define internal void @map_rehash_charp_ZVALUE(%map_charp_ZVALUE* %0) {
entry:
  %default_value47 = alloca %ZVALUE, align 8, !dbg !275
  %n = alloca i32, align 4, !dbg !275
  %hash = alloca i32, align 4, !dbg !275
  %it2 = alloca %ZVALUE, align 8, !dbg !275
  %default_value = alloca %ZVALUE, align 8, !dbg !275
  %it = alloca i8*, align 8, !dbg !275
  %len = alloca i32, align 4, !dbg !275
  %item_existance = alloca i1*, align 8, !dbg !275
  %items = alloca %ZVALUE*, align 8, !dbg !275
  %keys = alloca i8**, align 8, !dbg !275
  %size2 = alloca i32, align 4, !dbg !275
  %self = alloca %map_charp_ZVALUE*, align 8, !dbg !275
  store %map_charp_ZVALUE* %0, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %self1 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self1, i32 0, i32 3, !dbg !275
  %size = load i32, i32* %field, align 4, !dbg !275
  %mul = mul i32 %size, 3, !dbg !275
  store i32 %mul, i32* %size2, align 4, !dbg !275
  %size3 = load i32, i32* %size2, align 4, !dbg !275
  %icastD = sext i32 %size3 to i64, !dbg !275
  %mul4 = mul i64 8, %icastD, !dbg !275
  %fun_result = call i8* @GC_malloc(i64 %mul4), !dbg !275
  %obj = bitcast i8* %fun_result to i8**, !dbg !275
  store i8** %obj, i8*** %keys, align 8, !dbg !275
  %size5 = load i32, i32* %size2, align 4, !dbg !275
  %icastD6 = sext i32 %size5 to i64, !dbg !275
  %mul7 = mul i64 12, %icastD6, !dbg !275
  %fun_result8 = call i8* @GC_malloc(i64 %mul7), !dbg !275
  %obj9 = bitcast i8* %fun_result8 to %ZVALUE*, !dbg !275
  store %ZVALUE* %obj9, %ZVALUE** %items, align 8, !dbg !275
  %size10 = load i32, i32* %size2, align 4, !dbg !275
  %icastD11 = sext i32 %size10 to i64, !dbg !275
  %mul12 = mul i64 1, %icastD11, !dbg !275
  %fun_result13 = call i8* @GC_malloc(i64 %mul12), !dbg !275
  %obj14 = bitcast i8* %fun_result13 to i1*, !dbg !275
  store i1* %obj14, i1** %item_existance, align 8, !dbg !275
  store i32 0, i32* %len, align 4, !dbg !275
  %self15 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %fun_result16 = call i8* @map_begin_charp_ZVALUE(%map_charp_ZVALUE* %self15), !dbg !275
  store i8* %fun_result16, i8** %it, align 8, !dbg !275
  br label %loop_top_block, !dbg !275

loop_top_block:                                   ; preds = %cond_end_block29, %entry
  %self17 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %fun_result18 = call i1 @map_end_charp_ZVALUE(%map_charp_ZVALUE* %self17), !dbg !275
  %logical_denial = icmp eq i1 %fun_result18, false, !dbg !275
  br i1 %logical_denial, label %cond_then_block, label %cond_end_block, !dbg !275

cond_then_block:                                  ; preds = %loop_top_block
  %self19 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %it20 = load i8*, i8** %it, align 8, !dbg !275
  %default_value21 = load %ZVALUE, %ZVALUE* %default_value, align 4, !dbg !275
  %fun_result22 = call %ZVALUE @map_at_charp_ZVALUE(%map_charp_ZVALUE* %self19, i8* %it20, %ZVALUE %default_value21), !dbg !275
  store %ZVALUE %fun_result22, %ZVALUE* %it2, align 4, !dbg !275
  %it23 = load i8*, i8** %it, align 8, !dbg !275
  %fun_result24 = call i32 @char_get_hash_key(i8* %it23), !dbg !275
  %size25 = load i32, i32* %size2, align 4, !dbg !275
  %div = srem i32 %fun_result24, %size25, !dbg !275
  store i32 %div, i32* %hash, align 4, !dbg !275
  %hash26 = load i32, i32* %hash, align 4, !dbg !275
  store i32 %hash26, i32* %n, align 4, !dbg !275
  br label %loop_top_block27, !dbg !275

cond_end_block:                                   ; preds = %loop_top_block
  %self60 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %keys61 = load i8**, i8*** %keys, align 8, !dbg !275
  %field62 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self60, i32 0, i32 0, !dbg !275
  store i8** %keys61, i8*** %field62, align 8, !dbg !275
  %self63 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %items64 = load %ZVALUE*, %ZVALUE** %items, align 8, !dbg !275
  %field65 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self63, i32 0, i32 2, !dbg !275
  store %ZVALUE* %items64, %ZVALUE** %field65, align 8, !dbg !275
  %self66 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %item_existance67 = load i1*, i1** %item_existance, align 8, !dbg !275
  %field68 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self66, i32 0, i32 1, !dbg !275
  store i1* %item_existance67, i1** %field68, align 8, !dbg !275
  %self69 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %size70 = load i32, i32* %size2, align 4, !dbg !275
  %field71 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self69, i32 0, i32 3, !dbg !275
  store i32 %size70, i32* %field71, align 4, !dbg !275
  %self72 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %len73 = load i32, i32* %len, align 4, !dbg !275
  %field74 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self72, i32 0, i32 4, !dbg !275
  store i32 %len73, i32* %field74, align 4, !dbg !275
  ret void, !dbg !275

loop_top_block27:                                 ; preds = %cond_end, %cond_then_block
  br i1 true, label %cond_then_block28, label %cond_end_block29, !dbg !275

cond_then_block28:                                ; preds = %loop_top_block27
  %item_existance30 = load i1*, i1** %item_existance, align 8, !dbg !275
  %n31 = load i32, i32* %n, align 4, !dbg !275
  %element_address = getelementptr inbounds i1, i1* %item_existance30, i32 %n31, !dbg !275
  %element = load i1, i1* %element_address, align 1, !dbg !275
  br i1 %element, label %cond_jump_then, label %cond_else_block, !dbg !275

cond_end_block29:                                 ; preds = %cond_else_block, %loop_top_block27
  %self58 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %fun_result59 = call i8* @map_next_charp_ZVALUE(%map_charp_ZVALUE* %self58), !dbg !275
  store i8* %fun_result59, i8** %it, align 8, !dbg !275
  br label %loop_top_block, !dbg !275

cond_jump_then:                                   ; preds = %cond_then_block28
  %n32 = load i32, i32* %n, align 4, !dbg !275
  %add = add i32 %n32, 1, !dbg !275
  store i32 %add, i32* %n, align 4, !dbg !275
  %sub = sub i32 %add, 1, !dbg !275
  %n33 = load i32, i32* %n, align 4, !dbg !275
  %size34 = load i32, i32* %size2, align 4, !dbg !275
  %gteq = icmp sge i32 %n33, %size34, !dbg !275
  br i1 %gteq, label %cond_jump_then35, label %cond_jump_elif0, !dbg !275

cond_else_block:                                  ; preds = %cond_then_block28
  %item_existance40 = load i1*, i1** %item_existance, align 8, !dbg !275
  %n41 = load i32, i32* %n, align 4, !dbg !275
  %element_address42 = getelementptr i1, i1* %item_existance40, i32 %n41, !dbg !275
  store i1 true, i1* %element_address42, align 1, !dbg !275
  %keys43 = load i8**, i8*** %keys, align 8, !dbg !275
  %n44 = load i32, i32* %n, align 4, !dbg !275
  %it45 = load i8*, i8** %it, align 8, !dbg !275
  %element_address46 = getelementptr i8*, i8** %keys43, i32 %n44, !dbg !275
  store i8* %it45, i8** %element_address46, align 8, !dbg !275
  %items48 = load %ZVALUE*, %ZVALUE** %items, align 8, !dbg !275
  %n49 = load i32, i32* %n, align 4, !dbg !275
  %self50 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %it51 = load i8*, i8** %it, align 8, !dbg !275
  %default_value52 = load %ZVALUE, %ZVALUE* %default_value47, align 4, !dbg !275
  %fun_result53 = call %ZVALUE @map_at_charp_ZVALUE(%map_charp_ZVALUE* %self50, i8* %it51, %ZVALUE %default_value52), !dbg !275
  %element_address54 = getelementptr %ZVALUE, %ZVALUE* %items48, i32 %n49, !dbg !275
  store %ZVALUE %fun_result53, %ZVALUE* %element_address54, align 4, !dbg !275
  %len55 = load i32, i32* %len, align 4, !dbg !275
  %add56 = add i32 %len55, 1, !dbg !275
  store i32 %add56, i32* %len, align 4, !dbg !275
  %sub57 = sub i32 %add56, 1, !dbg !275
  br label %cond_end_block29, !dbg !275

cond_end:                                         ; preds = %after_break, %cond_end36
  br label %loop_top_block27, !dbg !275

cond_jump_then35:                                 ; preds = %cond_jump_then
  store i32 0, i32* %n, align 4, !dbg !275
  br label %cond_end36, !dbg !275

cond_jump_elif0:                                  ; preds = %cond_jump_then
  %n37 = load i32, i32* %n, align 4, !dbg !275
  %hash38 = load i32, i32* %hash, align 4, !dbg !275
  %eq = icmp eq i32 %n37, %hash38, !dbg !275
  br i1 %eq, label %cond_jump_elif_then0, label %cond_end36, !dbg !275

cond_jump_elif_then0:                             ; preds = %cond_jump_elif0
  %stderr = load %_IO_FILE*, %_IO_FILE** @stderr, align 8, !dbg !275
  %fun_result39 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stderr, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @"unexpected error in map.rehash(1)\0A", i32 0, i32 0)), !dbg !275
  call void @exit(i32 2), !dbg !275
  br label %cond_end36, !dbg !275

cond_end36:                                       ; preds = %cond_jump_elif_then0, %cond_jump_elif0, %cond_jump_then35
  br label %cond_end, !dbg !275

after_break:                                      ; No predecessors!
  br label %cond_end, !dbg !275
}

define internal i8* @map_next_charp_ZVALUE(%map_charp_ZVALUE* %0) {
entry:
  %self = alloca %map_charp_ZVALUE*, align 8, !dbg !275
  store %map_charp_ZVALUE* %0, %map_charp_ZVALUE** %self, align 8, !dbg !275
  br label %loop_top_block, !dbg !275

loop_top_block:                                   ; preds = %cond_end, %entry
  %self1 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self1, i32 0, i32 5, !dbg !275
  %it = load i32, i32* %field, align 4, !dbg !275
  %self2 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field3 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self2, i32 0, i32 3, !dbg !275
  %size = load i32, i32* %field3, align 4, !dbg !275
  %le = icmp slt i32 %it, %size, !dbg !275
  br i1 %le, label %cond_then_block, label %cond_end_block, !dbg !275

cond_then_block:                                  ; preds = %loop_top_block
  %self4 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field5 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self4, i32 0, i32 1, !dbg !275
  %item_existance = load i1*, i1** %field5, align 8, !dbg !275
  %self6 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field7 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self6, i32 0, i32 5, !dbg !275
  %it8 = load i32, i32* %field7, align 4, !dbg !275
  %element_address = getelementptr inbounds i1, i1* %item_existance, i32 %it8, !dbg !275
  %element = load i1, i1* %element_address, align 1, !dbg !275
  br i1 %element, label %cond_jump_then, label %cond_end, !dbg !275

cond_end_block:                                   ; preds = %loop_top_block
  ret i8* null, !dbg !275

cond_jump_then:                                   ; preds = %cond_then_block
  %self9 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field10 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self9, i32 0, i32 0, !dbg !275
  %keys = load i8**, i8*** %field10, align 8, !dbg !275
  %self11 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %self12 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field13 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self12, i32 0, i32 5, !dbg !275
  %it14 = load i32, i32* %field13, align 4, !dbg !275
  %add = add i32 %it14, 1, !dbg !275
  %field15 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self11, i32 0, i32 5, !dbg !275
  store i32 %add, i32* %field15, align 4, !dbg !275
  %sub = sub i32 %add, 1, !dbg !275
  %element_address16 = getelementptr inbounds i8*, i8** %keys, i32 %sub, !dbg !275
  %element17 = load i8*, i8** %element_address16, align 8, !dbg !275
  ret i8* %element17, !dbg !275

cond_end:                                         ; preds = %cond_then_block
  %self18 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %self19 = load %map_charp_ZVALUE*, %map_charp_ZVALUE** %self, align 8, !dbg !275
  %field20 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self19, i32 0, i32 5, !dbg !275
  %it21 = load i32, i32* %field20, align 4, !dbg !275
  %add22 = add i32 %it21, 1, !dbg !275
  %field23 = getelementptr inbounds %map_charp_ZVALUE, %map_charp_ZVALUE* %self18, i32 0, i32 5, !dbg !275
  store i32 %add22, i32* %field23, align 4, !dbg !275
  %sub24 = sub i32 %add22, 1, !dbg !275
  br label %loop_top_block, !dbg !275
}

attributes #0 = { nounwind }
attributes #1 = { nounwind willreturn }
attributes #2 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "come", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false)
!1 = !DIFile(filename: "src/vm.c", directory: "/home/ab25cq/repo/neo-c2/yappy")
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
!260 = distinct !DISubprogram(name: "initialize_modules_v1", linkageName: "initialize_modules_v1", scope: !1, file: !1, line: 6, type: !261, scopeLine: 6, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!261 = !DISubroutineType(types: !2)
!262 = !DILocation(line: 8, scope: !260)
!263 = !DILocation(line: 9, scope: !260)
!264 = !DILocation(line: 10, scope: !260)
!265 = distinct !DISubprogram(name: "vm", linkageName: "vm", scope: !1, file: !1, line: 87, type: !85, scopeLine: 87, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!266 = !DILocation(line: 87, scope: !265)
!267 = !DILocation(line: 92, scope: !265)
!268 = !DILocation(line: 93, scope: !265)
!269 = !DILocation(line: 95, scope: !265)
!270 = !DILocation(line: 97, scope: !265)
!271 = !DILocation(line: 98, scope: !265)
!272 = !DILocation(line: 348, scope: !265)
!273 = !DILocation(line: 99, scope: !265)
!274 = !DILocation(line: 101, scope: !265)
!275 = !DILocation(line: 103, scope: !265)
!276 = !DILocation(line: 107, scope: !265)
!277 = !DILocation(line: 109, scope: !265)
!278 = !DILocation(line: 110, scope: !265)
!279 = !DILocation(line: 342, scope: !265)
!280 = !DILocation(line: 111, scope: !265)
!281 = !DILocation(line: 112, scope: !265)
!282 = !DILocation(line: 113, scope: !265)
!283 = !DILocation(line: 115, scope: !265)
!284 = !DILocation(line: 117, scope: !265)
!285 = !DILocation(line: 119, scope: !265)
!286 = !DILocation(line: 120, scope: !265)
!287 = !DILocation(line: 121, scope: !265)
!288 = !DILocation(line: 122, scope: !265)
!289 = !DILocation(line: 124, scope: !265)
!290 = !DILocation(line: 125, scope: !265)
!291 = !DILocation(line: 126, scope: !265)
!292 = !DILocation(line: 128, scope: !265)
!293 = !DILocation(line: 130, scope: !265)
!294 = !DILocation(line: 131, scope: !265)
!295 = !DILocation(line: 133, scope: !265)
!296 = !DILocation(line: 134, scope: !265)
!297 = !DILocation(line: 136, scope: !265)
!298 = !DILocation(line: 138, scope: !265)
!299 = !DILocation(line: 139, scope: !265)
!300 = !DILocation(line: 140, scope: !265)
!301 = !DILocation(line: 143, scope: !265)
!302 = !DILocation(line: 145, scope: !265)
!303 = !DILocation(line: 146, scope: !265)
!304 = !DILocation(line: 148, scope: !265)
!305 = !DILocation(line: 149, scope: !265)
!306 = !DILocation(line: 151, scope: !265)
!307 = !DILocation(line: 153, scope: !265)
!308 = !DILocation(line: 154, scope: !265)
!309 = !DILocation(line: 155, scope: !265)
!310 = !DILocation(line: 157, scope: !265)
!311 = !DILocation(line: 159, scope: !265)
!312 = !DILocation(line: 160, scope: !265)
!313 = !DILocation(line: 162, scope: !265)
!314 = !DILocation(line: 163, scope: !265)
!315 = !DILocation(line: 165, scope: !265)
!316 = !DILocation(line: 167, scope: !265)
!317 = !DILocation(line: 169, scope: !265)
!318 = !DILocation(line: 170, scope: !265)
!319 = !DILocation(line: 171, scope: !265)
!320 = !DILocation(line: 173, scope: !265)
!321 = !DILocation(line: 175, scope: !265)
!322 = !DILocation(line: 176, scope: !265)
!323 = !DILocation(line: 178, scope: !265)
!324 = !DILocation(line: 179, scope: !265)
!325 = !DILocation(line: 198, scope: !265)
!326 = !DILocation(line: 196, scope: !265)
!327 = !DILocation(line: 180, scope: !265)
!328 = !DILocation(line: 181, scope: !265)
!329 = !DILocation(line: 183, scope: !265)
!330 = !DILocation(line: 184, scope: !265)
!331 = !DILocation(line: 185, scope: !265)
!332 = !DILocation(line: 187, scope: !265)
!333 = !DILocation(line: 188, scope: !265)
!334 = !DILocation(line: 194, scope: !265)
!335 = !DILocation(line: 189, scope: !265)
!336 = !DILocation(line: 192, scope: !265)
!337 = !DILocation(line: 199, scope: !265)
!338 = !DILocation(line: 201, scope: !265)
!339 = !DILocation(line: 202, scope: !265)
!340 = !DILocation(line: 204, scope: !265)
!341 = !DILocation(line: 206, scope: !265)
!342 = !DILocation(line: 208, scope: !265)
!343 = !DILocation(line: 209, scope: !265)
!344 = !DILocation(line: 211, scope: !265)
!345 = !DILocation(line: 232, scope: !265)
!346 = !DILocation(line: 212, scope: !265)
!347 = !DILocation(line: 213, scope: !265)
!348 = !DILocation(line: 216, scope: !265)
!349 = !DILocation(line: 218, scope: !265)
!350 = !DILocation(line: 226, scope: !265)
!351 = !DILocation(line: 219, scope: !265)
!352 = !DILocation(line: 222, scope: !265)
!353 = !DILocation(line: 223, scope: !265)
!354 = !DILocation(line: 227, scope: !265)
!355 = !DILocation(line: 230, scope: !265)
!356 = !DILocation(line: 233, scope: !265)
!357 = !DILocation(line: 235, scope: !265)
!358 = !DILocation(line: 236, scope: !265)
!359 = !DILocation(line: 238, scope: !265)
!360 = !DILocation(line: 240, scope: !265)
!361 = !DILocation(line: 242, scope: !265)
!362 = !DILocation(line: 243, scope: !265)
!363 = !DILocation(line: 245, scope: !265)
!364 = !DILocation(line: 256, scope: !265)
!365 = !DILocation(line: 246, scope: !265)
!366 = !DILocation(line: 247, scope: !265)
!367 = !DILocation(line: 250, scope: !265)
!368 = !DILocation(line: 251, scope: !265)
!369 = !DILocation(line: 254, scope: !265)
!370 = !DILocation(line: 257, scope: !265)
!371 = !DILocation(line: 259, scope: !265)
!372 = !DILocation(line: 260, scope: !265)
!373 = !DILocation(line: 262, scope: !265)
!374 = !DILocation(line: 264, scope: !265)
!375 = !DILocation(line: 266, scope: !265)
!376 = !DILocation(line: 271, scope: !265)
!377 = !DILocation(line: 267, scope: !265)
!378 = !DILocation(line: 269, scope: !265)
!379 = !DILocation(line: 272, scope: !265)
!380 = !DILocation(line: 273, scope: !265)
!381 = !DILocation(line: 274, scope: !265)
!382 = !DILocation(line: 276, scope: !265)
!383 = !DILocation(line: 277, scope: !265)
!384 = !DILocation(line: 278, scope: !265)
!385 = !DILocation(line: 280, scope: !265)
!386 = !DILocation(line: 282, scope: !265)
!387 = !DILocation(line: 283, scope: !265)
!388 = !DILocation(line: 285, scope: !265)
!389 = !DILocation(line: 286, scope: !265)
!390 = !DILocation(line: 288, scope: !265)
!391 = !DILocation(line: 290, scope: !265)
!392 = !DILocation(line: 292, scope: !265)
!393 = !DILocation(line: 293, scope: !265)
!394 = !DILocation(line: 295, scope: !265)
!395 = !DILocation(line: 296, scope: !265)
!396 = !DILocation(line: 298, scope: !265)
!397 = !DILocation(line: 299, scope: !265)
!398 = !DILocation(line: 301, scope: !265)
!399 = !DILocation(line: 307, scope: !265)
!400 = !DILocation(line: 302, scope: !265)
!401 = !DILocation(line: 305, scope: !265)
!402 = !DILocation(line: 308, scope: !265)
!403 = !DILocation(line: 310, scope: !265)
!404 = !DILocation(line: 311, scope: !265)
!405 = !DILocation(line: 313, scope: !265)
!406 = !DILocation(line: 315, scope: !265)
!407 = !DILocation(line: 316, scope: !265)
!408 = !DILocation(line: 317, scope: !265)
!409 = !DILocation(line: 320, scope: !265)
!410 = !DILocation(line: 322, scope: !265)
!411 = !DILocation(line: 323, scope: !265)
!412 = !DILocation(line: 325, scope: !265)
!413 = !DILocation(line: 326, scope: !265)
!414 = !DILocation(line: 328, scope: !265)
!415 = !DILocation(line: 330, scope: !265)
!416 = !DILocation(line: 331, scope: !265)
!417 = !DILocation(line: 332, scope: !265)
!418 = !DILocation(line: 335, scope: !265)
!419 = !DILocation(line: 337, scope: !265)
!420 = !DILocation(line: 338, scope: !265)
!421 = !DILocation(line: 339, scope: !265)
!422 = !DILocation(line: 343, scope: !265)
!423 = !DILocation(line: 344, scope: !265)
!424 = distinct !DISubprogram(name: "show_zvalue", linkageName: "show_zvalue", scope: !1, file: !1, line: 17, type: !425, scopeLine: 17, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!425 = !DISubroutineType(types: !426)
!426 = !{null}
!427 = !DILocation(line: 17, scope: !424)
!428 = !DILocation(line: 19, scope: !424)
!429 = !DILocation(line: 20, scope: !424)
!430 = !DILocation(line: 26, scope: !424)
!431 = !DILocation(line: 21, scope: !424)
!432 = !DILocation(line: 22, scope: !424)
!433 = !DILocation(line: 24, scope: !424)
!434 = !DILocation(line: 25, scope: !424)
!435 = distinct !DISubprogram(name: "print_op", linkageName: "print_op", scope: !1, file: !1, line: 30, type: !73, scopeLine: 30, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !0, retainedNodes: !2)
!436 = !DILocation(line: 30, scope: !435)
!437 = !DILocation(line: 32, scope: !435)
!438 = !DILocation(line: 33, scope: !435)
!439 = !DILocation(line: 83, scope: !435)
!440 = !DILocation(line: 34, scope: !435)
!441 = !DILocation(line: 35, scope: !435)
!442 = !DILocation(line: 37, scope: !435)
!443 = !DILocation(line: 38, scope: !435)
!444 = !DILocation(line: 39, scope: !435)
!445 = !DILocation(line: 41, scope: !435)
!446 = !DILocation(line: 42, scope: !435)
!447 = !DILocation(line: 43, scope: !435)
!448 = !DILocation(line: 45, scope: !435)
!449 = !DILocation(line: 46, scope: !435)
!450 = !DILocation(line: 47, scope: !435)
!451 = !DILocation(line: 49, scope: !435)
!452 = !DILocation(line: 50, scope: !435)
!453 = !DILocation(line: 51, scope: !435)
!454 = !DILocation(line: 53, scope: !435)
!455 = !DILocation(line: 54, scope: !435)
!456 = !DILocation(line: 55, scope: !435)
!457 = !DILocation(line: 57, scope: !435)
!458 = !DILocation(line: 58, scope: !435)
!459 = !DILocation(line: 59, scope: !435)
!460 = !DILocation(line: 61, scope: !435)
!461 = !DILocation(line: 62, scope: !435)
!462 = !DILocation(line: 63, scope: !435)
!463 = !DILocation(line: 65, scope: !435)
!464 = !DILocation(line: 66, scope: !435)
!465 = !DILocation(line: 67, scope: !435)
!466 = !DILocation(line: 69, scope: !435)
!467 = !DILocation(line: 70, scope: !435)
!468 = !DILocation(line: 71, scope: !435)
!469 = !DILocation(line: 73, scope: !435)
!470 = !DILocation(line: 74, scope: !435)
!471 = !DILocation(line: 75, scope: !435)
!472 = !DILocation(line: 77, scope: !435)
!473 = !DILocation(line: 78, scope: !435)
!474 = !DILocation(line: 79, scope: !435)
!475 = !DILocation(line: 81, scope: !435)
!476 = !DILocation(line: 82, scope: !435)
