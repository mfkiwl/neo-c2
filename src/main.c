#include "common.h"

static void compiler_init(char* sname)
{
    init_typedef();
    parser_init();
    init_node_types();
    class_init();
    init_vtable();
    init_nodes(sname);
}

static void compiler_final(char* sname)
{
    free_nodes(sname);
    final_vtable();
    class_final();
    free_node_types();
    parser_final();
}

static BOOL compiler(char* fname, BOOL optimize, sVarTable* module_var_table, BOOL neo_c_header)
{
    if(access(fname, F_OK) != 0) {
        fprintf(stderr, "%s doesn't exist\n", fname);
        return FALSE;
    }
    
    sBuf source;
    sBuf_init(&source);

    char fname2[PATH_MAX];

    char* cflags = getenv("CFLAGS");

    xstrncpy(fname2, fname, PATH_MAX);
    xstrncat(fname2, ".i", PATH_MAX);

    char cmd[1024];
#ifdef __DARWIN__
    if(cflags) {
        snprintf(cmd, 1024, "/usr/local/opt/llvm/bin/clnag-cpp %s -U__GNUC__ -C %s > %s", cflags, fname, fname2);
    }
    else {
        snprintf(cmd, 1024, "/usr/local/opt/llvm/bin/clang-cpp -U__GNUC__ -C %s > %s", fname, fname2);
    }
#else
    if(cflags) {
        snprintf(cmd, 1024, "cpp %s -U__GNUC__ -C %s > %s", cflags, fname, fname2);
    }
    else {
        snprintf(cmd, 1024, "cpp -U__GNUC__ -C %s > %s", fname, fname2);
    }
#endif

    puts(cmd);
    int rc = system(cmd);
    if(rc != 0) {
        char cmd[1024];
        if(cflags) {
            snprintf(cmd, 1024, "cpp %s -C %s > %s", cflags, fname, fname2);
        } else {
            snprintf(cmd, 1024, "cpp -C %s > %s", fname, fname2);
        }

        puts(cmd);
        rc = system(cmd);

        if(rc != 0) {
            fprintf(stderr, "failed to cpp(2)\n");
            exit(2);
        }
    }

    if(!read_source(fname2, &source)) {
        free(source.mBuf);
        return FALSE;
    }

    sBuf source2;
    sBuf_init(&source2);

    if(!delete_comment(&source, &source2)) {
        free(source.mBuf);
        free(source2.mBuf);
        return FALSE;
    }

    if(!compile_source(fname, source2.mBuf, optimize, module_var_table)) 
    {
        free(source.mBuf);
        free(source2.mBuf);
        return FALSE;
    }

    free(source.mBuf);
    free(source2.mBuf);

    return TRUE;
}

char* gVersion = "0.9.1";
BOOL gNCDebug = FALSE;
char gFName[PATH_MAX];

int main(int argc, char** argv)
{
    char sname[PATH_MAX];
    sname[0] = '\0';

    const int max_c_include_path = 1024*2*2*2;
    char c_include_path[max_c_include_path];
    snprintf(c_include_path, max_c_include_path, "%s/include/", PREFIX);

    int i;
    for(i=1; i<argc; i++) {
        if(strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-version") == 0 || strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "-V") == 0)
        {
            printf("come version %s\n", gVersion);
            exit(0);
        }
        else if(strcmp(argv[i], "-g") == 0)
        {
            gNCDebug = TRUE;
        }
        else if(strstr(argv[i], "-I") == argv[i])
        {
            xstrncat(c_include_path, ":", max_c_include_path);
            xstrncat(c_include_path, argv[i]+2, max_c_include_path);
        }
        else if(strcmp(argv[i], "-I") == 0)
        {
            if(i + 1 < argc) {
                xstrncat(c_include_path, ":", max_c_include_path);
                xstrncat(c_include_path, argv[i+1], max_c_include_path);
                i++;
            }
        }
        else if(*argv[i] != '-' && sname[0] == '\0') {
            xstrncpy(sname, argv[i], PATH_MAX);
        }
    }
    
    setenv("C_INCLUDE_PATH", c_include_path, 1);

    xstrncpy(gFName, sname, PATH_MAX);

    compiler_init(sname);

    sVarTable* module_var_table = init_var_table();

    BOOL optimize = TRUE;
    if(!compiler(sname, optimize, module_var_table, FALSE))
    {
        fprintf(stderr, "come can't compile(2) %s\n", sname);
        compiler_final(sname);
        return 1;
    }

    compiler_final(sname);

    return 0;
}
