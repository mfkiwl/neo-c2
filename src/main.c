#include "common.h"
#include <libgen.h>

static void compiler_init(char* sname)
{
    node_var_init();
    node_function_init();
    node_loop_init();
    init_typedef();
    parser_init();
    init_node_types();
    class_init();
    init_vtable();
    init_nodes(sname);
}

static void compiler_final(char* sname)
{
    final_vtable();
    class_final();
    free_node_types();
    parser_final();
    free_nodes(sname);
    node_function_final();
    node_var_final();
    node_loop_final();
}

static BOOL compiler(char* fname, BOOL optimize, sVarTable* module_var_table, BOOL neo_c_header, char* macro_definition)
{
    if(access(fname, F_OK) != 0) {
        fprintf(stderr, "%s doesn't exist\n", fname);
        return FALSE;
    }
    
    sBuf source;
    sBuf_init(&source);

    char fname2[PATH_MAX];

    char cflags[1024];

    if(strstr(fname, "/")) {
        if(getenv("CFLAGS")) {
            char tmp[PATH_MAX];
            strcpy(tmp, fname);
            snprintf(cflags, 1024, "%s -I %s", getenv("CFLAGS"), dirname(tmp));
        }
        else {
            char tmp[PATH_MAX];
            strcpy(tmp, fname);
            snprintf(cflags, 1024, "-I %s", dirname(tmp));
        }
    }
    else if(getenv("CFLAGS")) {
        xstrncpy(cflags, getenv("CFLAGS"), 1024);
    }
    else {
        xstrncpy(cflags, "", 1024);
    }

    xstrncpy(fname2, fname, PATH_MAX);
    xstrncat(fname2, ".i", PATH_MAX);

    char cmd[1024];
#ifdef __DARWIN__
    snprintf(cmd, 1024, "/usr/local/opt/llvm/bin/clnag-cpp -I/usr/local/include %s -D__DARWIN__ -D__GNUC__=7 -U__GNUC__ %s %s > %s", cflags, fname, macro_definition, fname2);
#else
    snprintf(cmd, 1024, "cpp %s -U__GNUC__ %s %s > %s", cflags, fname, macro_definition, fname2);
#endif

    //puts(cmd);
    int rc = system(cmd);
    if(rc != 0) {
        char cmd[1024];
        snprintf(cmd, 1024, "cpp %s -C %s %s > %s", cflags, fname, macro_definition, fname2);

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

    if(!compile_source(fname, &source.mBuf, optimize, module_var_table)) 
    {
        free(source.mBuf);
        return FALSE;
    }
    
    free(source.mBuf);

    return TRUE;
}

char* gVersion = "1.0.9";
BOOL gNCDebug = FALSE;
BOOL gNCGC = FALSE;
char gFName[PATH_MAX];
sVarTable* gModuleVarTable;
BOOL gNCType = FALSE;
BOOL gNCGlobal = FALSE;
BOOL gNCFunction = FALSE;
BOOL gNCClass = FALSE;
BOOL gNCTypedef = FALSE;
BOOL gNCNoMacro = FALSE;

int main(int argc, char** argv)
{
    char sname[PATH_MAX];
    sname[0] = '\0';

    const int max_c_include_path = 1024*2*2*2;
    char c_include_path[max_c_include_path];
    snprintf(c_include_path, max_c_include_path, "%s/include/", PREFIX);
    char macro_definition[max_c_include_path];

    macro_definition[0] = '\0';

    char optiones[1024];

    optiones[0] = '\0';

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
            xstrncat(optiones, "-g ", 1024);
        }
        else if(strcmp(argv[i], "-gc") == 0)
        {
            gNCGC = TRUE;
            xstrncat(optiones, "-gc ", 1024);
        }
        else if(strcmp(argv[i], "type") == 0)
        {
            gNCType = TRUE;
            xstrncat(optiones, "type ", 1024);
        }
        else if(strcmp(argv[i], "global") == 0)
        {
            gNCGlobal = TRUE;
            gNCType = TRUE;
            xstrncat(optiones, "global ", 1024);
        }
        else if(strcmp(argv[i], "class") == 0)
        {
            gNCClass = TRUE;
            gNCType = TRUE;

            xstrncat(optiones, "class ", 1024);
        }
        else if(strcmp(argv[i], "typedef") == 0)
        {
            gNCTypedef = TRUE;
            gNCType = TRUE;

            xstrncat(optiones, "typedef ", 1024);
        }
        else if(strcmp(argv[i], "function") == 0)
        {
            gNCFunction = TRUE;
            gNCType = TRUE;

            xstrncat(optiones, "function ", 1024);
        }
        else if(strcmp(argv[i], "-n") == 0) 
        {
            gNCNoMacro = TRUE;

            xstrncat(optiones, "-n ", 1024);
        }
        else if(strstr(argv[i], "-I") == argv[i])
        {
            xstrncat(c_include_path, ":", max_c_include_path);
            xstrncat(c_include_path, argv[i]+2, max_c_include_path);

            xstrncat(optiones, "-I ", 1024);
        }
        else if(strcmp(argv[i], "-I") == 0)
        {
            if(i + 1 < argc) {
                xstrncat(c_include_path, ":", max_c_include_path);
                xstrncat(c_include_path, argv[i+1], max_c_include_path);

                xstrncat(optiones, "-I ", 1024);
                xstrncat(optiones, argv[i+1], 1024);
                xstrncat(optiones, " ", 1024);
                i++;
            }
        }
        else if(argv[i][0] == '-' && argv[i][1] == 'D') 
        {
            char dquort_argv[256];

            char* p = dquort_argv;
            char* p2 = argv[i];
            while(*p2) {
                if(*p2 == '"') {
                    *p++ = '\\';
                    *p++ = '"';
                    p2++;
                }
                else if(*p2 == '\'') {
                    *p++ = '\\';
                    *p++ = '\'';
                    p2++;
                }
                else {
                    *p++ = *p2++;
                }
            }
            *p++ = '\0';

            xstrncat(optiones, argv[i], 1024);

            xstrncat(macro_definition, dquort_argv, max_c_include_path);
            xstrncat(macro_definition, " ", max_c_include_path);
            i++;
        }
        else if(*argv[i] != '-' && sname[0] == '\0') {
            xstrncpy(sname, argv[i], PATH_MAX);
        }
    }
    
    setenv("C_INCLUDE_PATH", c_include_path, 1);
    
    setenv("ARG", optiones, 1);

    xstrncpy(gFName, sname, PATH_MAX);

    setenv("SOURCE_NAME", sname, 1);
    setenv("PREFIX", PREFIX, 1);

    compiler_init(sname);

    gModuleVarTable = init_var_table();

    BOOL optimize = TRUE;
    if(!compiler(sname, optimize, gModuleVarTable, FALSE, macro_definition))
    {
        fprintf(stderr, "come can't compile(2) %s\n", sname);
        compiler_final(sname);

        return 1;
    }

    compiler_final(sname);

    return 0;
}
