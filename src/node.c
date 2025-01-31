#include "common.h"

sNodeTree* gNodes;

int gSizeNodes = 0;
int gUsedNodes = 0;

LLVMContextRef gContext;
LLVMModuleRef  gModule;
LLVMBuilderRef gBuilder;
LLVMDIBuilderRef gDIBuilder;

LLVMValueRef gFunction;
char gFunctionName[VAR_NAME_MAX];

LVALUE* gLLVMStack;
LVALUE* gLLVMStackHead;

LLVMTypeRef create_llvm_type_with_class_name(char* class_name);
sFunction* get_function_from_table(char* name);

LLVMTypeRef create_llvm_type_from_node_type(sNodeType* node_type);

LLVMValueRef clone_object(sNodeType* node_type, LLVMValueRef obj, sCompileInfo* info)
{
    sCLClass* klass = node_type->mClass;

    if(node_type->mPointerNum > 0) {
        sCLClass* klass = node_type->mClass;

        char* class_name = CLASS_NAME(klass);

        char fun_name[VAR_NAME_MAX];
        snprintf(fun_name, VAR_NAME_MAX, "%s_clone", class_name);

        int i;
        sFunction* cloner = NULL;
        for(i=FUN_VERSION_MAX-1; i>=1; i--) {
            char new_fun_name[VAR_NAME_MAX];
            snprintf(new_fun_name, VAR_NAME_MAX, "%s_v%d", fun_name, i);
            cloner = get_function_from_table(new_fun_name);
            
            if(cloner) {
                xstrncpy(fun_name, new_fun_name, VAR_NAME_MAX);
                break;
            }
        }
        
        cloner = get_function_from_table(fun_name);

        if(cloner != NULL) {
            if(cloner->mGenericsFunction) {
                LLVMValueRef llvm_fun = NULL;

                if(!create_generics_function(&llvm_fun, cloner, fun_name, node_type, 0, NULL, info)) {
                    fprintf(stderr, "can't craete generics finalizer %s\n", fun_name);
                    exit(1);
                }

                int num_params = 1;

                LLVMValueRef llvm_params[PARAMS_MAX];
                memset(llvm_params, 0, sizeof(LLVMValueRef)*PARAMS_MAX);

                llvm_params[0] = obj;

                obj = LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "");
            }
            else {
                int num_params = 1;

                LLVMValueRef llvm_params[PARAMS_MAX];
                memset(llvm_params, 0, sizeof(LLVMValueRef)*PARAMS_MAX);

                llvm_params[0] = obj;

                LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, fun_name);
                obj = LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "");
            }
        }
        else {
            /// ncmemdup ///
            int num_params = 1;

            LLVMValueRef llvm_params[PARAMS_MAX];
            memset(llvm_params, 0, sizeof(LLVMValueRef)*PARAMS_MAX);

            char* fun_name2 = "ncmemdup";

            LLVMTypeRef llvm_type = create_llvm_type_with_class_name("char*");

            LLVMValueRef llvm_value = LLVMBuildCast(gBuilder, LLVMBitCast, obj, llvm_type, "castAL");

            llvm_params[0] = llvm_value;

            LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, fun_name2);
            obj = LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "");

            LLVMTypeRef llvm_type2 = create_llvm_type_from_node_type(node_type);

            obj = LLVMBuildCast(gBuilder, LLVMBitCast, obj, llvm_type2, "castAM");
        }
    }

    return obj;
}

LLVMTypeRef create_llvm_type_with_class_name(char* class_name);

void init_nodes(char* sname)
{
    // create context, module and builder
    gContext = LLVMContextCreate();
    gModule = LLVMModuleCreateWithNameInContext(sname, gContext);
    gBuilder = LLVMCreateBuilderInContext(gContext);

    gLLVMStack = (LVALUE*)xcalloc(1, sizeof(LVALUE)*NEO_C_STACK_SIZE);
    gLLVMStackHead = gLLVMStack;

    const int node_size = 32;

    if(gUsedNodes == 0) {
        gNodes = (sNodeTree*)xcalloc(1, sizeof(sNodeTree)*node_size);
        gSizeNodes = node_size;
        gUsedNodes = 1;   // 0 of index means null
    }

    if(gNCDebug) {
        gDIBuilder = LLVMCreateDIBuilder(gModule);

        char cwd[PATH_MAX];
        getcwd(cwd, PATH_MAX);

        char directory[PATH_MAX];

        snprintf(directory, PATH_MAX, "%s", cwd);

        int directory_len = strlen(directory);

        LLVMMetadataRef file = LLVMDIBuilderCreateFile(gDIBuilder, gFName, strlen(gFName), directory, directory_len);

        char* procedure = "come";
        int procedure_len = strlen("come");

        int is_optimized = 0;
        const char* flags = "";
        int flags_len = 0;
        int runtime_ver = 0;
        char* split_name = NULL;
        int split_name_len = 0;
        int dwold = 0;
        int split_debugginginling = 0;
        int debug_info_for_profiling = 0;
        const char* sys_root = "";
        int sys_root_len = 0;
        const char* sdk = "";
        int sdk_len = 0;


#if LLVM_VERSION >= 11
        LLVMMetadataRef compile_unit = LLVMDIBuilderCreateCompileUnit(gDIBuilder, LLVMDWARFSourceLanguageC, file, procedure, procedure_len, is_optimized, flags, flags_len, runtime_ver, split_name,  split_name_len, LLVMDWARFEmissionFull, dwold, split_debugginginling, debug_info_for_profiling, sys_root, sys_root_len, sdk, sdk_len);
#else
        LLVMMetadataRef compile_unit = LLVMDIBuilderCreateCompileUnit(gDIBuilder, LLVMDWARFSourceLanguageC, file, procedure, procedure_len, is_optimized, flags, flags_len, runtime_ver, split_name,  split_name_len, LLVMDWARFEmissionFull, dwold, split_debugginginling, debug_info_for_profiling);
#endif

        char include_path[PATH_MAX];

        snprintf(include_path, PATH_MAX, "%s/%s", cwd, gFName);
        /*
        xstrncpy(include_path, cwd, PATH_MAX);
        xstrncat(include_path, "/", PATH_MAX);
        xstrncat(include_path, gFName, PATH_MAX);
        */

        LLVMMetadataRef module = LLVMDIBuilderCreateModule(gDIBuilder, compile_unit,
                              procedure, procedure_len,
                              "", 0,
                              include_path, strlen(include_path),
                              "", 0);


        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

        LLVMValueRef dwarf_version = LLVMConstInt(llvm_type, 4, FALSE);

        LLVMMetadataRef dwarf_version_meta_data = LLVMValueAsMetadata(dwarf_version);
        
        LLVMAddModuleFlag(gModule, 6, "Dwarf Version", strlen("Dwarf Version"), dwarf_version_meta_data);

        LLVMValueRef dwarf_info_version = LLVMConstInt(llvm_type, LLVMDebugMetadataVersion(), FALSE);

        LLVMMetadataRef dwarf_info_version_meta_data = LLVMValueAsMetadata(dwarf_info_version);

        LLVMAddModuleFlag(gModule, LLVMModuleFlagBehaviorWarning, "Debug Info Version", strlen("Debug Info Version"), dwarf_info_version_meta_data);
    }

    /// va_list ///
#ifdef __DARWIN__
    LLVMTypeRef field_types[STRUCT_FIELD_MAX];

    field_types[0] = create_llvm_type_with_class_name("int");
    field_types[1] = create_llvm_type_with_class_name("int");
    field_types[2] = create_llvm_type_with_class_name("char*");
    field_types[3] = create_llvm_type_with_class_name("char*");

    int num_fields = 4;

    LLVMTypeRef struct_type = LLVMStructTypeInContext(gContext, field_types, num_fields, FALSE);

    LLVMStructSetBody(struct_type, field_types, num_fields, FALSE);

    char* class_name = "__builtin_va_list";
    sCLClass* va_list_struct = alloc_struct("__builtin_va_list", FALSE, FALSE);
    sNodeType* node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }

    class_name = "va_list";
    va_list_struct = alloc_struct("va_list", FALSE, FALSE);
    node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }
#elif  defined(__X86_64_CPU__ )
    LLVMTypeRef field_types[STRUCT_FIELD_MAX];

    field_types[0] = create_llvm_type_with_class_name("int");
    field_types[1] = create_llvm_type_with_class_name("int");
    field_types[2] = create_llvm_type_with_class_name("char*");
    field_types[3] = create_llvm_type_with_class_name("char*");

    int num_fields = 4;

    LLVMTypeRef struct_type = LLVMStructTypeInContext(gContext, field_types, num_fields, FALSE);

    LLVMStructSetBody(struct_type, field_types, num_fields, FALSE);

    char* class_name = "__builtin_va_list";
    sCLClass* va_list_struct = alloc_struct("__builtin_va_list", FALSE, FALSE);
    sNodeType* node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }

    class_name = "va_list";
    va_list_struct = alloc_struct("va_list", FALSE, FALSE);
    node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }
#elif __AARCH64_CPU__
    LLVMTypeRef field_types[STRUCT_FIELD_MAX];

    field_types[0] = create_llvm_type_with_class_name("char*");
    field_types[1] = create_llvm_type_with_class_name("char*");
    field_types[2] = create_llvm_type_with_class_name("char*");
    field_types[3] = create_llvm_type_with_class_name("int");
    field_types[4] = create_llvm_type_with_class_name("int");

    int num_fields = 5;

    LLVMTypeRef struct_type = LLVMStructTypeInContext(gContext, field_types, num_fields, FALSE);

    LLVMStructSetBody(struct_type, field_types, num_fields, FALSE);

    char* class_name = "__builtin_va_list";
    sCLClass* va_list_struct = alloc_struct("__builtin_va_list", FALSE, FALSE);
    sNodeType* node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }

    class_name = "va_list";
    va_list_struct = alloc_struct("va_list", FALSE, FALSE);
    node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }
#elif __RASPBERRY_PI__
    LLVMTypeRef field_types[STRUCT_FIELD_MAX];

    field_types[0] = create_llvm_type_with_class_name("char*");

    int num_fields = 1;

    LLVMTypeRef struct_type = LLVMStructTypeInContext(gContext, field_types, num_fields, FALSE);

    LLVMStructSetBody(struct_type, field_types, num_fields, FALSE);

    char* class_name = "__builtin_va_list";
    sCLClass* va_list_struct = alloc_struct("__builtin_va_list", FALSE, FALSE);
    sNodeType* node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }

    class_name = "va_list";
    va_list_struct = alloc_struct("va_list", FALSE, FALSE);
    node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }
#else
    LLVMTypeRef field_types[STRUCT_FIELD_MAX];

    field_types[0] = create_llvm_type_with_class_name("char*");
    field_types[1] = create_llvm_type_with_class_name("char*");
    field_types[2] = create_llvm_type_with_class_name("char*");
    field_types[3] = create_llvm_type_with_class_name("int");
    field_types[4] = create_llvm_type_with_class_name("int");

    int num_fields = 5;

    LLVMTypeRef struct_type = LLVMStructTypeInContext(gContext, field_types, num_fields, FALSE);

    LLVMStructSetBody(struct_type, field_types, num_fields, FALSE);

    char* class_name = "__builtin_va_list";
    sCLClass* va_list_struct = alloc_struct("__builtin_va_list", FALSE, FALSE);
    sNodeType* node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }

    class_name = "va_list";
    va_list_struct = alloc_struct("va_list", FALSE, FALSE);
    node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }
#endif
    {
        char* name = "llvm.va_start";
        int num_params = 1;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "p", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("char*");

        sNodeType* result_type = create_node_type_with_class_name("void");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }

    {
        char* name = "__builtin_va_start";
        int num_params = 1;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "p", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("char*");

        sNodeType* result_type = create_node_type_with_class_name("void");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }

    /// va_end ///
    {
        char* name = "llvm.va_end";
        int num_params = 1;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "p", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("char*");

        sNodeType* result_type = create_node_type_with_class_name("void");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }

    {
        char* name = "__builtin_va_end";
        int num_params = 1;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "p", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("char*");

        sNodeType* result_type = create_node_type_with_class_name("void");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.assume";
        int num_params = 1;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "exp", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("bool");

        sNodeType* result_type = create_node_type_with_class_name("void");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.readcyclecounter";
        int num_params = 0;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        sNodeType* result_type = create_node_type_with_class_name("long");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.bitreverse.i8";
        int num_params = 1;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("char");

        sNodeType* result_type = create_node_type_with_class_name("char");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.bitreverse.i16";
        int num_params = 1;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("short");

        sNodeType* result_type = create_node_type_with_class_name("short");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.bitreverse.i32";
        int num_params = 1;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("int");

        sNodeType* result_type = create_node_type_with_class_name("int");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.bitreverse.i64";
        int num_params = 1;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("long");

        sNodeType* result_type = create_node_type_with_class_name("long");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.fshl.i8";
        int num_params = 2;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("char");

        xstrncpy(param_names[1], "m", VAR_NAME_MAX);
        param_types[1] = create_node_type_with_class_name("char");

        sNodeType* result_type = create_node_type_with_class_name("char");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.fshl.i16";
        int num_params = 2;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("short");

        xstrncpy(param_names[1], "m", VAR_NAME_MAX);
        param_types[1] = create_node_type_with_class_name("short");

        sNodeType* result_type = create_node_type_with_class_name("short");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.fshl.i32";
        int num_params = 2;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("int");

        xstrncpy(param_names[1], "m", VAR_NAME_MAX);
        param_types[1] = create_node_type_with_class_name("int");

        sNodeType* result_type = create_node_type_with_class_name("int");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.fshl.i64";
        int num_params = 2;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("long");

        xstrncpy(param_names[1], "m", VAR_NAME_MAX);
        param_types[1] = create_node_type_with_class_name("long");

        sNodeType* result_type = create_node_type_with_class_name("long");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.fshr.i8";
        int num_params = 2;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("char");

        xstrncpy(param_names[1], "m", VAR_NAME_MAX);
        param_types[1] = create_node_type_with_class_name("char");

        sNodeType* result_type = create_node_type_with_class_name("char");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.fshr.i16";
        int num_params = 2;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("short");

        xstrncpy(param_names[1], "m", VAR_NAME_MAX);
        param_types[1] = create_node_type_with_class_name("short");

        sNodeType* result_type = create_node_type_with_class_name("short");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.fshr.i32";
        int num_params = 2;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("int");

        xstrncpy(param_names[1], "m", VAR_NAME_MAX);
        param_types[1] = create_node_type_with_class_name("int");

        sNodeType* result_type = create_node_type_with_class_name("int");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.fshr.i64";
        int num_params = 2;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("long");

        xstrncpy(param_names[1], "m", VAR_NAME_MAX);
        param_types[1] = create_node_type_with_class_name("long");

        sNodeType* result_type = create_node_type_with_class_name("long");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.canonicalize.f64";
        int num_params = 1;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("double");

        sNodeType* result_type = create_node_type_with_class_name("double");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.canonicalize.f32";
        int num_params = 1;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("float");

        sNodeType* result_type = create_node_type_with_class_name("float");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
    {
        char* name = "llvm.canonicalize.f80";
        int num_params = 1;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "n", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("long_double");

        sNodeType* result_type = create_node_type_with_class_name("long_double");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
/*
    {
        char* name = "llvm.memcpy.inline.p0i8.p0i8.i64";
        int num_params = 3;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "dst", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("void*");

        xstrncpy(param_names[1], "src", VAR_NAME_MAX);
        param_types[1] = create_node_type_with_class_name("void*");

        xstrncpy(param_names[2], "size", VAR_NAME_MAX);
        param_types[2] = create_node_type_with_class_name("long");

        sNodeType* result_type = create_node_type_with_class_name("void");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
*/
    {
        char* name = "llvm.objectsize.i64.p0i8";
        int num_params = 4;
        char param_names[PARAMS_MAX][VAR_NAME_MAX];
        sNodeType* param_types[PARAMS_MAX];
        char* block_text = NULL;
        BOOL var_arg = FALSE;

        xstrncpy(param_names[0], "p", VAR_NAME_MAX);
        param_types[0] = create_node_type_with_class_name("void*");

        xstrncpy(param_names[1], "arg2", VAR_NAME_MAX);
        param_types[1] = create_node_type_with_class_name("bool");

        xstrncpy(param_names[2], "arg3", VAR_NAME_MAX);
        param_types[2] = create_node_type_with_class_name("bool");

        xstrncpy(param_names[3], "arg4", VAR_NAME_MAX);
        param_types[3] = create_node_type_with_class_name("bool");

        sNodeType* result_type = create_node_type_with_class_name("long");

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }

        LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);

        LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
        LLVMValueRef llvm_fun = LLVMAddFunction(gModule, name, function_type);

        char* param_names2[PARAMS_MAX];
        for(i=0; i<num_params; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        BOOL var_args = FALSE;
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL, FALSE, NULL, "", -1))
        {
            fprintf(stderr, "overflow function number\n");
            exit(1);
        }
    }
}

void free_nodes(char* sname)
{
    if(gNCDebug) {
        LLVMDIBuilderFinalize(gDIBuilder);
        LLVMDisposeDIBuilder(gDIBuilder);
    }
    free(gLLVMStack);

    char sname2[PATH_MAX];

    snprintf(sname2, PATH_MAX, "%s.ll", sname);

    //LLVMDumpModule(gModule); // dump module to STDOUT
    if(!gNCType && !gNCGlobal && !gNCFunction && !gNCClass && !gNCTypedef && strcmp(sname, "") != 0) {
        LLVMPrintModuleToFile(gModule, sname2, NULL);
    }

    // clean memory
    LLVMDisposeBuilder(gBuilder);
    LLVMDisposeModule(gModule);
    LLVMContextDispose(gContext);

    if(gUsedNodes > 0) {
        int i;
        for(i=1; i<gUsedNodes; i++) {
            switch(gNodes[i].mNodeType) {
                case kNodeTypeCString:
                    free(gNodes[i].uValue.sString.mString);
                    break;
                    
                case kNodeTypeRegex:
                    free(gNodes[i].uValue.sRegex.mString);
                    break;

                case kNodeTypeFunction:
                    sNodeBlock_free(gNodes[i].uValue.sFunction.mNodeBlock);
                    break;

                case kNodeTypeMethodBlock:
                    free(gNodes[i].uValue.sMethodBlock.mBlockText);
                    break;

                case kNodeTypeIf:
                    {
                    if(gNodes[i].uValue.sIf.mIfNodeBlock) {
                        sNodeBlock_free(gNodes[i].uValue.sIf.mIfNodeBlock);
                    }
                    int j;
                    for(j=0; j<gNodes[i].uValue.sIf.mElifNum; j++) {
                        sNodeBlock* node_block = gNodes[i].uValue.sIf.mElifNodeBlocks[j];
                        if(node_block) {
                            sNodeBlock_free(node_block);
                        }
                    }
                    if(gNodes[i].uValue.sIf.mElseNodeBlock) {
                        sNodeBlock_free(gNodes[i].uValue.sIf.mElseNodeBlock);
                    }
                    }
                    break;

                case kNodeTypeWhile:
                    {
                    if(gNodes[i].uValue.sWhile.mWhileNodeBlock) {
                        sNodeBlock_free(gNodes[i].uValue.sWhile.mWhileNodeBlock);
                    }
                    }
                    break;

                case kNodeTypeFor:
                    if(gNodes[i].uValue.sFor.mForNodeBlock) 
                    {
                        sNodeBlock_free(gNodes[i].uValue.sFor.mForNodeBlock);
                    }
                    break;

                case kNodeTypeGenericsFunction:
                    free(gNodes[i].uValue.sFunction.mBlockText);
                    break;

                case kNodeTypeInlineFunction:
                    free(gNodes[i].uValue.sFunction.mBlockText);
                    break;

                case kNodeTypeNormalBlock:
                    if(gNodes[i].uValue.sNormalBlock.mNodeBlock) 
                    {
                        sNodeBlock_free(gNodes[i].uValue.sNormalBlock.mNodeBlock);
                    }
                    break;

                case kNodeTypeSelect:{
                    int num_pipes = gNodes[i].uValue.sSelect.mNumPipes;
                    int j;
                    for(j=0; j<num_pipes; j++) {
                        sNodeBlock_free(gNodes[i].uValue.sSelect.mPipeBlocks[j]);
                    }

                    if(gNodes[i].uValue.sSelect.mDefaultBlock) {
                        sNodeBlock_free(gNodes[i].uValue.sSelect.mDefaultBlock);
                    }
                    }
                    break;

                case kNodeTypeSwitch:
                    if(gNodes[i].uValue.sSwitch.mSwitchExpression)
                    {
                        free(gNodes[i].uValue.sSwitch.mSwitchExpression);
                    }
                    break;

                default:
                    break;
            }
        }

        free(gNodes);

        gSizeNodes = 0;
        gUsedNodes = 0;
    }
}

void setCurrentDebugLocation(int sline, sCompileInfo* info)
{
    int colum = 0;
    LLVMMetadataRef scope = info->function_meta_data;
    LLVMMetadataRef inlinedat = NULL;
    LLVMMetadataRef loc = LLVMDIBuilderCreateDebugLocation(gContext, sline, colum, scope, inlinedat);

    LLVMSetCurrentDebugLocation(gBuilder, LLVMMetadataAsValue(gContext, loc));
}

void setNullCurrentDebugLocation(int sline, sCompileInfo* info)
{
//    LLVMSetCurrentDebugLocation(gBuilder, NULL);
}



LLVMMetadataRef create_llvm_debug_type(sNodeType* node_type, sCompileInfo* info)
{
    LLVMMetadataRef result = NULL;

    if(type_identify_with_class_name(node_type, "int")) {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "int", strlen("int"), 32, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "int", strlen("int"), 32, 0, 0);
#endif
    }
    else if(type_identify_with_class_name(node_type, "bool")) {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "bool", strlen("bool"), 1, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "bool", strlen("bool"), 1, 0, 0);
#endif
    }
    else if(type_identify_with_class_name(node_type, "char")) {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "char", strlen("char"), 8, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "char", strlen("char"), 8, 0, 0);
#endif
    }
    else if(type_identify_with_class_name(node_type, "short")) {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "short", strlen("short"), 16, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "short", strlen("short"), 16, 0, 0);
#endif
    }
    else if(type_identify_with_class_name(node_type, "long")) {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "long", strlen("long"), 64, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "long", strlen("long"), 64, 0, 0);
#endif
    }
    else if(type_identify_with_class_name(node_type, "float")) {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 32, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 32, 0, 0);
#endif
    }
    else if(type_identify_with_class_name(node_type, "double")) {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "double", strlen("doube"), 64, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "double", strlen("double"), 64, 0, 0);
#endif
    }
    else if(type_identify_with_class_name(node_type, "_Float16") || type_identify_with_class_name(node_type, "_Float16x")) 
    {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 16, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 16, 0, 0);
#endif
    }
    else if(type_identify_with_class_name(node_type, "_Float32") || type_identify_with_class_name(node_type, "_Float32x")) 
    {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 16, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 16, 0, 0);
#endif
    }
    else if(type_identify_with_class_name(node_type, "_Float64") || type_identify_with_class_name(node_type, "_Float64x")) 
    {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 64, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 64, 0, 0);
#endif
    }
    else if(type_identify_with_class_name(node_type, "_Float128") || type_identify_with_class_name(node_type, "_Float128x")) 
    {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 128, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 128, 0, 0);
#endif
    }
    else if(node_type->mClass->mFlags & CLASS_FLAGS_STRUCT) {
        sCLClass* klass = node_type->mClass;
        char* class_name = klass->mName;
        
        char* fname = info->sname;
        
        char cwd[PATH_MAX];
        getcwd(cwd, PATH_MAX);
    
        char directory[PATH_MAX];
        
        snprintf(directory, PATH_MAX, "%s", cwd);
        int directory_len = strlen(directory);
    
        LLVMMetadataRef scope = LLVMDIBuilderCreateFile(gDIBuilder, fname, strlen(fname), directory, directory_len);
        
        LLVMMetadataRef llvm_debug_fields[STRUCT_FIELD_MAX];
        
        int num_fields = klass->mNumFields;
        
        for(int i=0; i<num_fields; i++) {
            LLVMMetadataRef llvm_debug_type;
            
            if(type_identify(node_type, klass->mFields[i])) {
#if LLVM_VERSION <= 7
                llvm_debug_type = LLVMDIBuilderCreateBasicType(gDIBuilder, "union", strlen("union"), 64, 0);
#else
                llvm_debug_type = LLVMDIBuilderCreateBasicType(gDIBuilder, "union", strlen("union"), 64, 0, 0);
#endif
            }
            else {
                llvm_debug_type = create_llvm_debug_type(klass->mFields[i], info);
            }
            
            char* name = klass->mFieldName[i];
            LLVMMetadataRef file = scope;
            int sline = info->sline;
            
            sNodeType* field_type = clone_node_type(klass->mFields[i]);
            
            int alignment = 0;
            uint64_t size_in_bits = get_size_from_node_type(field_type, &alignment) * 8;
            uint32_t align_in_bits = alignment * 8;
            
            klass->mNumFields = i+1;
            uint64_t offset_in_bits;
            if(i == 0) {
                offset_in_bits = 0;
            }
            else if(i+1 > num_fields) {
                klass->mNumFields = num_fields;
            }
            else {
                offset_in_bits = get_size_from_node_type(node_type, &alignment) * 8 - size_in_bits;
            }
            klass->mNumFields = num_fields;
            LLVMDIFlags flags = 0;
            
            llvm_debug_fields[i] = LLVMDIBuilderCreateMemberType(
                gDIBuilder, scope, name, strlen(name), file, sline, size_in_bits, align_in_bits,
                offset_in_bits, flags, llvm_debug_type);
        }
        
        LLVMMetadataRef file = scope;
        unsigned line_number = info->sline;
        int alignment = 0;
        uint64_t size_in_bits = get_size_from_node_type(node_type, &alignment) * 8;
        uint32_t align_in_bits = alignment * 8;
        LLVMDIFlags flags = 0;
        LLVMMetadataRef deriverd_from = NULL;
        unsigned run_time_lang = 0;
        const char* unique_id = class_name;
        LLVMMetadataRef vtable_holder = NULL;
        
        result = LLVMDIBuilderCreateStructType(gDIBuilder, scope, class_name, strlen(class_name), file, line_number, size_in_bits,
            align_in_bits, flags, deriverd_from, llvm_debug_fields, klass->mNumFields, run_time_lang, vtable_holder,
            unique_id, strlen(unique_id));
    }
    else if(node_type->mClass->mFlags & CLASS_FLAGS_UNION) {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "union", strlen("union"), 64, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "union", strlen("union"), 64, 0, 0);
#endif
    }
    else if(node_type->mArrayDimentionNum > 0) {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "pointer", strlen("pointer"), 64, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "pointer", strlen("pointer"), 64, 0, 0);
#endif
    }
    else if(node_type->mClass->mFlags & CLASS_FLAGS_GENERICS) {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "generics", strlen("generics"), 64, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "generics", strlen("generics"), 64, 0, 0);
#endif
    }
    else if(node_type->mClass->mFlags & CLASS_FLAGS_METHOD_GENERICS) {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "mgenerics", strlen("mgenerics"), 64, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "mgenerics", strlen("mgenerics"), 64, 0, 0);
#endif
    }
    
    if(node_type->mPointerNum > 0) {
        int i;
        for(i=0; i<node_type->mPointerNum; i++) {
            result = LLVMDIBuilderCreatePointerType(gDIBuilder, result, sizeof(char*)*8, 0, 0, "pointer", strlen("pointer"));
        }
    }

    return result;
}

void createDebugFunctionInfo(char* fname, int sline, char* fun_name, sFunction* function, char* module_name, sCompileInfo* info)
{
    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);

    char directory[PATH_MAX];

    snprintf(directory, PATH_MAX, "%s", cwd);

    int directory_len = strlen(directory);

    LLVMMetadataRef file = LLVMDIBuilderCreateFile(gDIBuilder, fname, strlen(fname), directory, directory_len);

    int num_params;
    if(function) {
        num_params = function->mNumParams;
    }
    else {
        num_params = 0;
    }
    LLVMMetadataRef param_types[PARAMS_MAX];

    int i;
    for(i=0; i<num_params; i++) {
        param_types[i] = create_llvm_debug_type(function->mParamTypes[i], info);
    }

    LLVMMetadataRef FunctionTy = LLVMDIBuilderCreateSubroutineType(gDIBuilder, file, param_types, num_params, 0);

    unsigned tag = 0x15;

    LLVMMetadataRef ReplaceableFunctionMetadata = LLVMDIBuilderCreateReplaceableCompositeType(gDIBuilder, tag, fun_name, strlen(fun_name), 
                                                    file, file, sline,
                                                    0, 0, 0,
                                                    LLVMDIFlagFwdDecl,
                                                    "", 0);


    LLVMMetadataRef function_meta_data = LLVMDIBuilderCreateFunction(gDIBuilder, file, fun_name, strlen(fun_name), fun_name, strlen(fun_name),
                                file, sline, FunctionTy, TRUE, TRUE, sline, 0, FALSE);

    info->function_meta_data = function_meta_data;
}

void finishDebugFunctionInfo()
{
}

// return node index
unsigned int alloc_node()
{
    if(gSizeNodes == gUsedNodes) {
        int new_size = (gSizeNodes+1) * 2;
        gNodes = (sNodeTree*)realloc(gNodes, sizeof(sNodeTree)*new_size);
        memset(gNodes + gSizeNodes, 0, sizeof(sNodeTree)*(new_size - gSizeNodes));

        gSizeNodes = new_size;
    }

    return gUsedNodes++;
}

sNodeBlock* sNodeBlock_alloc()
{
    sNodeBlock* block = (sNodeBlock*)xcalloc(1, sizeof(sNodeBlock));

    block->mSizeNodes = 32;
    block->mNumNodes = 0;
    block->mNodes = (unsigned int*)xcalloc(1, sizeof(unsigned int)*block->mSizeNodes);
    block->mLVTable = NULL;

    return block;
}

void sNodeBlock_free(sNodeBlock* block)
{
/// this is compiler, so allow me to make memory leak
/*
    if(block->mNodes) free(block->mNodes);
    free(block->mSource.mBuf);
    free(block);
*/
}

void append_node_to_node_block(sNodeBlock* node_block, unsigned int node)
{
    if(node_block->mSizeNodes <= node_block->mNumNodes) {
        unsigned int new_size = node_block->mSizeNodes * 2;
        node_block->mNodes = (unsigned int*)xrealloc(node_block->mNodes, sizeof(unsigned int)*new_size);
        memset(node_block->mNodes + node_block->mSizeNodes, 0, sizeof(unsigned int)*(new_size-node_block->mSizeNodes));
        node_block->mSizeNodes = new_size;
    }

    node_block->mNodes[node_block->mNumNodes] = node;
    node_block->mNumNodes++;
}

void push_value_to_stack_ptr(LVALUE* value, sCompileInfo* info)
{
    *gLLVMStack= *value;
    gLLVMStack++;

    info->stack_num++;
}

void dec_stack_ptr(int value, sCompileInfo* info)
{
    gLLVMStack -= value;

    info->stack_num -= value;
}

void arrange_stack(sCompileInfo* info, int top)
{
    if(info->stack_num > top) {
        dec_stack_ptr(info->stack_num-top, info);
    }
    if(info->stack_num < top) {
        fprintf(stderr, "%s %d: unexpected stack value. The stack num is %d. top is %d\n", info->sname, info->sline, info->stack_num, top);
        exit(2);
    }
}

LVALUE* get_value_from_stack(int offset)
{
    return gLLVMStack + offset;
}
void create_generics_struct_name(char* struct_name, size_t size, sNodeType* struct_type)
{
    char* class_name = CLASS_NAME(struct_type->mClass);

    xstrncpy(struct_name, class_name, size);

    int i;
    for(i=0; i<struct_type->mNumGenericsTypes; i++) {
        sNodeType* node_type = struct_type->mGenericsTypes[i];
        sCLClass* klass = node_type->mClass;

        xstrncat(struct_name, "_", size);
        xstrncat(struct_name, CLASS_NAME(klass), size);

        int j;
        for(j=0; j<node_type->mPointerNum; j++) {
            xstrncat(struct_name, "p", size);
        }
    }
}

LLVMTypeRef create_llvm_type_from_node_type(sNodeType* node_type)
{
    LLVMTypeRef result_type = NULL;

    char class_name[VAR_NAME_MAX];
    create_generics_struct_name(class_name, VAR_NAME_MAX, node_type);

    sStruct* st = get_struct_from_table(class_name);

    if(st == NULL) {
        create_generics_struct_type(node_type);
    }

    sCLClass* klass = node_type->mClass;

#ifdef __ISH__
    if(type_identify_with_class_name(node_type, "__va_list"))
    {
        result_type = LLVMInt8TypeInContext(gContext);
    }
    else
#endif
    if(klass->mFlags & CLASS_FLAGS_ENUM) 
    {
        result_type = LLVMInt32TypeInContext(gContext);
    }
    else if(node_type->mSizeNum > 0) {
        result_type = LLVMIntTypeInContext(gContext, node_type->mSizeNum*8);
    }
    else if(node_type->mChannel) {
        result_type = LLVMInt32TypeInContext(gContext);
        result_type = LLVMArrayType(result_type, 2);
    }
    else if(type_identify_with_class_name(node_type, "int")) {
        result_type = LLVMInt32TypeInContext(gContext);
    }
    else if(type_identify_with_class_name(node_type, "long")) {
        result_type = LLVMInt64TypeInContext(gContext);
    }
    else if(type_identify_with_class_name(node_type, "char")) {
        result_type = LLVMInt8TypeInContext(gContext);
    }
    else if(type_identify_with_class_name(node_type, "short")) {
        result_type = LLVMInt16TypeInContext(gContext);
    }
    else if(type_identify_with_class_name(node_type, "__uint128_t"))
    {
        result_type = LLVMInt128TypeInContext(gContext);
    }
    else if(type_identify_with_class_name(node_type, "float"))
    {
        result_type = LLVMFloatTypeInContext(gContext);
    }
    else if(type_identify_with_class_name(node_type, "double"))
    {
        result_type = LLVMDoubleTypeInContext(gContext);
    }
    else if(type_identify_with_class_name(node_type, "long_double"))
    {
#ifdef __RASPBERRY_PI__
        result_type = LLVMDoubleTypeInContext(gContext);
#else
        result_type = LLVMFP128TypeInContext(gContext);
#endif
    }
    else if(type_identify_with_class_name(node_type, "bool")) {
        result_type = LLVMInt1TypeInContext(gContext);
    }
    else if(type_identify_with_class_name(node_type, "void")) {
        result_type = LLVMVoidTypeInContext(gContext);
    }
    else if(get_struct_from_table(class_name)) {
        sStruct* st = get_struct_from_table(class_name);
        result_type = st->mLLVMType;
    }
    else if(type_identify_with_class_name(node_type, "lambda"))
    {
        int num_params = node_type->mNumParams;
        sNodeType* fun_result_type = node_type->mResultType;

        LLVMTypeRef llvm_result_type= create_llvm_type_from_node_type(fun_result_type);

        LLVMTypeRef llvm_param_types[PARAMS_MAX];

        int i;
        for(i=0; i<num_params; i++) {
            sNodeType* param_type = node_type->mParamTypes[i];

            LLVMTypeRef llvm_param_type = create_llvm_type_from_node_type(param_type);

            llvm_param_types[i] = llvm_param_type;
        }

        BOOL var_args = node_type->mVarArgs;
        
        result_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_args);
    }

    if(result_type == NULL) {
        fprintf(stderr, "invalid type %s(1)\n", class_name);
        exit(1);
    }

    if(node_type->mPointerNum > 0 && type_identify_with_class_name(node_type, "void")) {
        result_type = LLVMInt8TypeInContext(gContext);
    }

    int i;
    for(i=0; i<node_type->mPointerNum; i++) {
        result_type = LLVMPointerType(result_type, 0);
    }

    for(i=node_type->mArrayDimentionNum-1; i>=0; i--) {
        result_type = LLVMArrayType(result_type, node_type->mArrayNum[i]);
    }

/*
    if(node_type->mCurrentStackVariable) {
        result_type = LLVMPointerType(result_type, 0);
    }
*/

    return result_type;
}

LLVMTypeRef create_llvm_type_with_class_name(char* class_name)
{
    sNodeType* node_type = create_node_type_with_class_name(class_name);

    return create_llvm_type_from_node_type(node_type);
}

BOOL cast_right_type_to_left_type(sNodeType* left_type, sNodeType** right_type, LVALUE* rvalue, struct sCompileInfoStruct* info)
{
    sCLClass* left_class = left_type->mClass;
    sCLClass* right_class = (*right_type)->mClass;

    /// va_list ///
    if(type_identify_with_class_name(left_type, "char*") && (type_identify_with_class_name(*right_type, "va_list") || type_identify_with_class_name(*right_type, "__builtin_va_list")))
    {
        if(rvalue) {
            LLVMTypeRef llvm_type = create_llvm_type_with_class_name("char*");
            rvalue->value = LLVMBuildCast(gBuilder, LLVMBitCast, rvalue->value, llvm_type, "castAN");
            rvalue->type = create_node_type_with_class_name("char*");
        }

        *right_type = create_node_type_with_class_name("char*");
    }
    else if((type_identify_with_class_name(left_type, "__builtin_va_list") || type_identify_with_class_name(left_type, "va_list") || type_identify_with_class_name(left_type, "__va_list")) && type_identify_with_class_name(*right_type, "char*"))
    {
        if(rvalue) {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

            rvalue->value = LLVMBuildCast(gBuilder, LLVMBitCast, rvalue->value, llvm_type, "castAO");
            rvalue->type = create_node_type_with_class_name("va_list");
        }

        *right_type = create_node_type_with_class_name("va_list");
    }

    /// go ///
    else if((left_type->mPointerNum-1 == (*right_type)->mPointerNum) && (*right_type)->mArrayDimentionNum == 1) 
    {
        if(rvalue) {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

            rvalue->value = LLVMBuildCast(gBuilder, LLVMBitCast, rvalue->address, llvm_type, "autocast");
        }

        *right_type = clone_node_type(left_type);
    }
    else if((left_type->mPointerNum-1 == (*right_type)->mPointerNum) && (*right_type)->mChannel) 
    {
        if(rvalue) {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

            rvalue->value = LLVMBuildCast(gBuilder, LLVMBitCast, rvalue->address, llvm_type, "autocast");
        }

        *right_type = clone_node_type(left_type);
    }
    else if(left_type->mPointerNum > 0 && (*right_type)->mPointerNum == 0) {
        if(rvalue) {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

            if((*right_type)->mArrayDimentionNum > 0) {
                rvalue->value = LLVMBuildCast(gBuilder, LLVMBitCast, rvalue->address, llvm_type, "castBA");
            }
            else {
                rvalue->value = LLVMBuildCast(gBuilder, LLVMIntToPtr, rvalue->value, llvm_type, "castBA");
            }

            rvalue->type = clone_node_type(left_type);
        }

        *right_type = clone_node_type(left_type);
    }
    else if(left_type->mPointerNum > 0 && (*right_type)->mPointerNum > 0) {
        if(rvalue) {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

            rvalue->value = LLVMBuildCast(gBuilder, LLVMBitCast, rvalue->value, llvm_type, "castAQ");
            rvalue->type = clone_node_type(left_type);
        }

        *right_type = clone_node_type(left_type);
    }

    else if(type_identify_with_class_name(left_type, "bool") && left_type->mPointerNum == 0)
    {
        if(rvalue) {
            if((*right_type)->mPointerNum == 0 && (type_identify_with_class_name(*right_type, "int") || type_identify_with_class_name(*right_type, "char") || type_identify_with_class_name(*right_type, "short") || type_identify_with_class_name(*right_type, "long"))) 
            {
                LLVMTypeRef llvm_type = create_llvm_type_from_node_type(*right_type);

                LLVMValueRef cmp_right_value = LLVMConstInt(llvm_type, 0, FALSE);
                rvalue->value = LLVMBuildICmp(gBuilder, LLVMIntNE, rvalue->value, cmp_right_value, "icmpA");

                llvm_type = create_llvm_type_with_class_name("bool");

                rvalue->value = LLVMBuildTrunc(gBuilder, rvalue->value, llvm_type, "icastA");
            }
            else if((*right_type)->mPointerNum > 0) {
                LLVMTypeRef llvm_type = create_llvm_type_from_node_type(*right_type);

                LLVMValueRef cmp_right_value = LLVMConstNull(llvm_type);
                rvalue->value = LLVMBuildICmp(gBuilder, LLVMIntNE, rvalue->value, cmp_right_value, "icmpB");

                llvm_type = create_llvm_type_with_class_name("bool");

                rvalue->value = LLVMBuildTrunc(gBuilder, rvalue->value, llvm_type, "icastB");
            }

            rvalue->type = create_node_type_with_class_name("bool");
        }

        *right_type = create_node_type_with_class_name("bool");
    }
    else if(type_identify_with_class_name(left_type, "long") && left_type->mPointerNum == 0)
    {
        if(rvalue) {
            if((*right_type)->mPointerNum == 0 && (type_identify_with_class_name(*right_type, "int") || type_identify_with_class_name(*right_type, "char") || type_identify_with_class_name(*right_type, "short") || type_identify_with_class_name(*right_type, "bool"))) 
            {
                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("long");

                if((*right_type)->mUnsigned) {
                    rvalue->value = LLVMBuildCast(gBuilder, LLVMZExt, rvalue->value, llvm_type, "icastC");
                }
                else {
                    rvalue->value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue->value, llvm_type, "icastD");
                }
            }

            rvalue->type = create_node_type_with_class_name("long");
        }

        *right_type = create_node_type_with_class_name("long");
    }
    else if(type_identify_with_class_name(left_type, "short") && left_type->mPointerNum == 0)
    {
        if(rvalue) {
            if((type_identify_with_class_name(*right_type, "char") || type_identify_with_class_name(*right_type, "bool")) && (*right_type)->mPointerNum == 0) {
                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("short");

                if((*right_type)->mUnsigned) {
                    rvalue->value = LLVMBuildCast(gBuilder, LLVMZExt, rvalue->value, llvm_type, "icastE");
                }
                else {
                    rvalue->value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue->value, llvm_type, "icastF");
                }
            }
            else if((*right_type)->mPointerNum == 0 && (type_identify_with_class_name(*right_type, "int") || type_identify_with_class_name(*right_type, "long"))) {
                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("short");

                rvalue->value = LLVMBuildTrunc(gBuilder, rvalue->value, llvm_type, "icastG");
            }
            else if((*right_type)->mPointerNum > 0) {
                if(rvalue) {
                    LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

                    rvalue->value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue->value, llvm_type, "castAA");
                    rvalue->type = clone_node_type(left_type);
                }

                *right_type = clone_node_type(left_type);
            }

            rvalue->type = create_node_type_with_class_name("short");
        }

        *right_type = create_node_type_with_class_name("short");
    }
    else if(type_identify_with_class_name(left_type, "char") && left_type->mPointerNum == 0)
    {
        if(rvalue) {
            if(type_identify_with_class_name(*right_type, "bool") && (*right_type)->mPointerNum == 0) {
                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("char");

                if((*right_type)->mUnsigned) {
                    rvalue->value = LLVMBuildCast(gBuilder, LLVMZExt, rvalue->value, llvm_type, "icastH");
                }
                else {
                    rvalue->value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue->value, llvm_type, "icastI");
                }
            }
            else if((*right_type)->mPointerNum == 0  && (type_identify_with_class_name(*right_type, "short") || (type_identify_with_class_name(*right_type, "int") || type_identify_with_class_name(*right_type, "long")))) {
                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("char");

                rvalue->value = LLVMBuildTrunc(gBuilder, rvalue->value, llvm_type, "icastJ");
            }
            else if((*right_type)->mPointerNum > 0) {
                if(rvalue) {
                    LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

                    rvalue->value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue->value, llvm_type, "castAB");
                    rvalue->type = clone_node_type(left_type);
                }

                *right_type = clone_node_type(left_type);
            }

            rvalue->type = create_node_type_with_class_name("char");
        }

        *right_type = create_node_type_with_class_name("char");
    }
    else if(type_identify_with_class_name(left_type, "int") && left_type->mPointerNum == 0)
    {
        if(rvalue) {
            if((*right_type)->mArrayDimentionNum > 0 && (*right_type)->mPointerNum == 0) {
                if(rvalue) {
                    LLVMValueRef indices[3];

                    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");
                    indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
                    indices[1] = LLVMConstInt(llvm_type, 0, FALSE);

                    LLVMValueRef llvm_value1 = LLVMBuildGEP(gBuilder, rvalue->address, indices, 2, "castXX1");

                    sNodeType* left_type2 = clone_node_type(left_type);
                    left_type2->mPointerNum++;
                    llvm_type = create_llvm_type_from_node_type(left_type2);

                    LLVMValueRef llvm_value2 = LLVMBuildCast(gBuilder, LLVMBitCast, llvm_value1, llvm_type, "castXX");
                    rvalue->value = LLVMBuildLoad(gBuilder, llvm_value2, "castZZ");
                    rvalue->type = clone_node_type(left_type);
                }

                *right_type = clone_node_type(left_type);
            }
            else if((*right_type)->mPointerNum == 0 && (type_identify_with_class_name(*right_type, "char") || type_identify_with_class_name(*right_type, "short") || type_identify_with_class_name(*right_type, "bool"))) 
            {
                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

                if((*right_type)->mUnsigned) {
                    rvalue->value = LLVMBuildCast(gBuilder, LLVMZExt, rvalue->value, llvm_type, "icastK");
                }
                else {
                    rvalue->value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue->value, llvm_type, "icastL");
                }
            }
            else if((*right_type)->mPointerNum == 0 && type_identify_with_class_name(*right_type, "long")) {
                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

                rvalue->value = LLVMBuildTrunc(gBuilder, rvalue->value, llvm_type, "icastM");
            }
            else if((*right_type)->mPointerNum > 0) {
                if(rvalue) {
                    LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

                    rvalue->value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue->value, llvm_type, "castAC");
                    rvalue->type = clone_node_type(left_type);
                }

                *right_type = clone_node_type(left_type);
            }

            rvalue->type = create_node_type_with_class_name("int");
        }

        *right_type = create_node_type_with_class_name("int");
    }
    else if(type_identify_with_class_name(left_type, "float") && left_type->mPointerNum == 0)
    {
        if(rvalue) {
            if((*right_type)->mPointerNum == 0 && (type_identify_with_class_name(*right_type, "double")))
            {
                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("float");

                rvalue->value = LLVMBuildCast(gBuilder, LLVMFPTrunc, rvalue->value, llvm_type, "icastK");
            }

            rvalue->type = create_node_type_with_class_name("float");
        }

        *right_type = create_node_type_with_class_name("float");
    }
    else if(type_identify_with_class_name(left_type, "double") && left_type->mPointerNum == 0)
    {
        if(rvalue) {
            if((*right_type)->mPointerNum == 0 && (type_identify_with_class_name(*right_type, "float")))
            {
                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("double");

                rvalue->value = LLVMBuildCast(gBuilder, LLVMFPExt, rvalue->value, llvm_type, "icastK");
            }

            rvalue->type = create_node_type_with_class_name("double");
        }

        *right_type = create_node_type_with_class_name("double");
    }

    return TRUE;
}

BOOL get_const_value_from_node(int* array_size, unsigned int array_size_node, sParserInfo* info)
{
    info->no_output_err_msg = TRUE;
    sCompileInfo cinfo;

    memset(&cinfo, 0, sizeof(sCompileInfo));
    cinfo.pinfo = info;

    if(!compile(array_size_node, &cinfo)) {
        info->no_output_err_msg = FALSE;
        return FALSE;
    }
    info->no_output_err_msg = FALSE;

    sNodeType* node_type = cinfo.type;

    LVALUE llvm_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, &cinfo);
    LLVMValueRef value = llvm_value.value;

    if(LLVMIsConstant(value)) {
        *array_size = LLVMConstIntGetZExtValue(value);
    }
    else {
        fprintf(stderr, "%s %d: can't create const value", info->sname, info->sline);
        return FALSE;
    }

    return TRUE;
}

BOOL create_llvm_struct_type(char* struct_name, sNodeType* node_type, sNodeType* generics_type, BOOL undefined_body)
{
    sCLClass* klass = node_type->mClass;

    sStruct* struct_ = get_struct_from_table(struct_name);

    if(struct_ == NULL && !undefined_body) {
        LLVMTypeRef field_types[STRUCT_FIELD_MAX];

        int num_fields = 0;
        LLVMTypeRef struct_type = LLVMStructCreateNamed(gContext, struct_name);

        if(!add_struct_to_table(struct_name, node_type, struct_type, TRUE)) {
            fprintf(stderr, "overflow struct number\n");
            exit(2);
        }

        sStruct* struct_ = get_struct_from_table(struct_name);

        int i;
        for(i=0; i<klass->mNumFields; i++) {
            sNodeType* field = clone_node_type(klass->mFields[i]);

            if(!solve_generics(&field, generics_type)) {
                fprintf(stderr, "can't solve generics types");
                return FALSE;
            }

            field_types[i] = create_llvm_type_from_node_type(field);
        }

        num_fields = klass->mNumFields;
        //LLVMTypeRef struct_type = struct_->mLLVMType;

        LLVMStructSetBody(struct_type, field_types, num_fields, FALSE);

        struct_->mUndefinedBody = FALSE;
    }
    else if(struct_ == NULL && undefined_body) {
        LLVMTypeRef field_types[STRUCT_FIELD_MAX];

        int num_fields = 0;
        LLVMTypeRef struct_type = LLVMStructCreateNamed(gContext, struct_name);

        if(!add_struct_to_table(struct_name, node_type, struct_type, TRUE)) {
            fprintf(stderr, "overflow struct number\n");
            exit(2);
        }
    }
    else if(struct_ && struct_->mUndefinedBody) {
        if(undefined_body) {
            return TRUE;
        }
        else {
            LLVMTypeRef field_types[STRUCT_FIELD_MAX];

            int i;
            for(i=0; i<klass->mNumFields; i++) {
                sNodeType* field = clone_node_type(klass->mFields[i]);

                if(!solve_generics(&field, generics_type)) {
                    fprintf(stderr, "can't solve generics types");
                    return FALSE;
                }

                field_types[i] = create_llvm_type_from_node_type(field);
            }

            int num_fields = klass->mNumFields;
            LLVMTypeRef struct_type = struct_->mLLVMType;

            LLVMStructSetBody(struct_type, field_types, num_fields, FALSE);

            struct_->mUndefinedBody = FALSE;
        }
    }

    return TRUE;
}

uint64_t get_size_from_node_type(sNodeType* node_type, int* alignment);

#if defined(__32BIT_CPU__)
uint64_t get_struct_size(sCLClass* klass, sNodeType* generics_type, int* alignment)
{
    uint64_t result = 0;
    int space = 0;
    int max_alignment = 4;
    int i;
    for(i=0; i<klass->mNumFields; i++) {
        sNodeType* field_type = clone_node_type(klass->mFields[i]);

        if(!solve_generics(&field_type, generics_type)) {
            fprintf(stderr, "can't solve generics types");
            exit(1);
        }

        sNodeType* element_type = clone_node_type(field_type);
        element_type->mArrayDimentionNum = 0;
        
        int element_size = get_size_from_node_type(element_type, alignment);

        uint64_t result_before = result;
        int size = get_size_from_node_type(field_type, alignment);

        BOOL struct_ = field_type->mClass->mFlags & CLASS_FLAGS_STRUCT;
        BOOL union_ = field_type->mClass->mFlags & CLASS_FLAGS_UNION;

        if(element_size < space && space > 0 && size > space) {
            size -= space;
            space = 0;
        }

        if(size <= space) {
            space -= size;
        }
        else {
            space = 0;

            if(*alignment == size) {
                result += size;
            }
            else if(*alignment < element_size) {
                if(element_size == 1) {
                    result += size;
                }
                else if(element_size == 2) {
                    result = (result + 1) & ~1;
                    result += size;
                }
                else if(element_size == 4) {
                    result = (result + 3) & ~3;
                    result += size;
                }
                else if(element_size == 8) {
#ifdef __ISH__
                    result = (result + 3) & ~3;
#else
                    result = (result + 7) & ~7;
#endif
                    result += size;
                }
                else {
                    result = (result + *alignment-1) & ~(*alignment-1);
                    result += size;
                }

                if(struct_ || union_) {
                    if(element_type->mPointerNum > 0) {
                        *alignment = 4;
                    }
                    if(union_ && size > 8) {
                        *alignment = 8;
                    }
                }
                else if(element_type->mPointerNum > 0) {
                    if(type_identify_with_class_name(element_type, "void")) {
                        *alignment = 4;
                    }
                    else {
                        *alignment = element_size;
                    }
                }
                else {
                    *alignment = element_size;
                }

                if(max_alignment < *alignment) {
                    max_alignment = *alignment;
                }
            }
            else {
                if(*alignment == 1) {
                    result += size;
                }
                else if(*alignment == 2) {
                    result += size;
                    result = (result + 1) & ~1;
                }
                else if(*alignment == 4) {
                    result += size;
                    result = (result + 3) & ~3;
                }
                else if(*alignment == 8) {
                    result += size;
#ifdef __ISH__
                    result = (result + 3) & ~3;
#else
                    result = (result + 7) & ~7;
#endif
                }
                else {
                    result += size;
                }

                space = result - result_before - size;
            }
        }
    }
#ifndef __ISH__
    result = (result + max_alignment-1) & ~(max_alignment-1);
#endif

    return result;
}
#else
uint64_t get_struct_size(sCLClass* klass, sNodeType* generics_type, int* alignment)
{
    uint64_t result = 0;
    int space = 0;
    int i;
    for(i=0; i<klass->mNumFields; i++) {
        sNodeType* field_type = clone_node_type(klass->mFields[i]);

        if(!solve_generics(&field_type, generics_type)) {
            fprintf(stderr, "can't solve generics types");
            exit(1);
        }

        sNodeType* element_type = clone_node_type(field_type);
        element_type->mArrayDimentionNum = 0;
        
        int element_size = get_size_from_node_type(element_type, alignment);

        uint64_t result_before = result;
        int size = get_size_from_node_type(field_type, alignment);

        BOOL struct_ = field_type->mClass->mFlags & CLASS_FLAGS_STRUCT;
        BOOL union_ = field_type->mClass->mFlags & CLASS_FLAGS_UNION;

        if(element_size < space && space > 0 && size > space) {
            size -= space;
            space = 0;
        }

        if(size <= space) {
            space -= size;
        }
        else {
            space = 0;

            if(*alignment == size) {
                result += size;
            }
            else if(*alignment < element_size) {
                if(element_size == 1) {
                    result += size;
                }
                else if(element_size == 2) {
                    result = (result + 1) & ~1;
                    result += size;
                }
                else if(element_size == 4) {
                    result = (result + 3) & ~3;
                    result += size;
                }
                else if(element_size == 8) {
                    result = (result + 7) & ~7;
                    result += size;
                }
                else {
                    result = (result + *alignment-1) & ~(*alignment-1);
                    result += size;
                }

                if(struct_ || union_) {
                    if(element_type->mPointerNum > 0) {
                        *alignment = 8;
                    }
                }
                else if(element_type->mPointerNum > 0) {
                    if(type_identify_with_class_name(element_type, "void")) {
                        *alignment = 4;
                    }
                    else {
                        *alignment = element_size;
                    }
                }
                else {
                    *alignment = element_size;
                }
            }
            else {
                if(*alignment == 1) {
                    result += size;
                }
                else if(*alignment == 2) {
                    result += size;
                    result = (result + 1) & ~1;
                }
                else if(*alignment == 4) {
                    result += size;
                    result = (result + 3) & ~3;
                }
                else if(*alignment == 8) {
                    result += size;
                    result = (result + 7) & ~7;
                }
                else {
                    result += size;
                }

                space = result - result_before - size;
            }
        }
    }

    return result;
}
#endif

#ifdef __32BIT_CPU__
uint64_t get_union_size(sCLClass* klass, sNodeType* generics_type, int* alignment)
{
    char* class_name = CLASS_NAME(klass);

    sStruct* struct_ = get_struct_from_table(class_name);

    uint64_t max_size = 0;
    int max_alignment = 4;

    int i;
    for(i=0; i<klass->mNumFields; i++) {
        sNodeType* field = clone_node_type(klass->mFields[i]);

        if(!solve_generics(&field, generics_type)) {
            return FALSE;
        }

        int alignment = 0;
        uint64_t size = get_size_from_node_type(field, &alignment);

        if(alignment > max_alignment) {
            max_alignment = alignment;
        }

        if(size > max_size) {
            max_size = size;
        }
    }

#if __ISH__
    if(max_alignment > 4) {
        max_alignment = 4;
    }
#endif
    max_size = (max_size + max_alignment-1) & ~(max_alignment-1);

    return max_size;
}
#else
uint64_t get_union_size(sCLClass* klass, sNodeType* generics_type, int* alignment)
{
    uint64_t result = 0;
    int i;
    for(i=0; i<klass->mNumFields; i++) {
        sNodeType* field_type = clone_node_type(klass->mFields[i]);

        if(!solve_generics(&field_type, generics_type)) {
            fprintf(stderr, "can't solve generics types");
            exit(1);
        }

        uint64_t size = get_size_from_node_type(field_type, alignment);

        sNodeType* element_type = clone_node_type(field_type);
        element_type->mArrayDimentionNum = 0;

        BOOL struct_ = field_type->mClass->mFlags & CLASS_FLAGS_STRUCT;

        BOOL union_ = field_type->mClass->mFlags & CLASS_FLAGS_UNION;

        int element_size = get_size_from_node_type(element_type, alignment);

        if(*alignment == size) {
        }
        else if(*alignment < element_size) {
            if(!struct_ && !union_) {
                *alignment = element_size;
            }
        }

        if(result < size) {
            result = size;
        }
    }

    return result;
}
#endif

uint64_t get_size_from_node_type(sNodeType* node_type, int* alignment)
{
    uint64_t result = 0;
    sNodeType* node_type2 = clone_node_type(node_type);

    if(node_type2->mArrayInitializeNum > 0){
        node_type2->mPointerNum--;
        node_type2->mArrayNum[0] = node_type2->mArrayInitializeNum;
        node_type2->mArrayDimentionNum = 1;
    }

    if(node_type2->mSizeNum > 0) {
        result = node_type2->mSizeNum;

        int i;
        for(i=0; i<node_type2->mArrayDimentionNum; i++) {
            result *= node_type2->mArrayNum[i];
        }
    }
    else if(node_type2->mPointerNum > 0) {
#ifdef __32BIT_CPU__
        result = 4;
#else
        result = 8;
#endif

        int i;
        for(i=0; i<node_type2->mArrayDimentionNum; i++) {
            result *= node_type2->mArrayNum[i];
        }
    }
    else {
        if(node_type2->mClass->mUndefinedStructType) {
        }

        if(node_type->mPointerNum == 0 && (node_type->mClass->mFlags & CLASS_FLAGS_STRUCT)) {
            result = get_struct_size(node_type->mClass, node_type, alignment);

            int i;
            for(i=0; i<node_type2->mArrayDimentionNum; i++) {
                result *= node_type2->mArrayNum[i];
            }
        }
        else if(node_type->mPointerNum == 0 && (node_type->mClass->mFlags & CLASS_FLAGS_UNION)) {
            result = get_union_size(node_type->mClass, node_type, alignment);

            int i;
            for(i=0; i<node_type2->mArrayDimentionNum; i++) {
                result *= node_type2->mArrayNum[i];
            }
        }
        else if(type_identify_with_class_name(node_type, "int")){
            result = 4;

            int i;
            for(i=0; i<node_type2->mArrayDimentionNum; i++) {
                result *= node_type2->mArrayNum[i];
            }
        }
        else if(type_identify_with_class_name(node_type, "long")){
            result = 8;

            int i;
            for(i=0; i<node_type2->mArrayDimentionNum; i++) {
                result *= node_type2->mArrayNum[i];
            }
        }
        else if(type_identify_with_class_name(node_type, "short")){
            result = 2;

            int i;
            for(i=0; i<node_type2->mArrayDimentionNum; i++) {
                result *= node_type2->mArrayNum[i];
            }
        }
        else if(type_identify_with_class_name(node_type, "char")){
            result = 1;

            int i;
            for(i=0; i<node_type2->mArrayDimentionNum; i++) {
                result *= node_type2->mArrayNum[i];
            }
        }
        else if(type_identify_with_class_name(node_type, "bool")){
            result = 1;

            int i;
            for(i=0; i<node_type2->mArrayDimentionNum; i++) {
                result *= node_type2->mArrayNum[i];
            }
        }
        else if(type_identify_with_class_name(node_type, "float")){
            result = 4;

            int i;
            for(i=0; i<node_type2->mArrayDimentionNum; i++) {
                result *= node_type2->mArrayNum[i];
            }
        }
        else if(type_identify_with_class_name(node_type, "double")){
            result = 8;

            int i;
            for(i=0; i<node_type2->mArrayDimentionNum; i++) {
                result *= node_type2->mArrayNum[i];
            }
        }
        else if(type_identify_with_class_name(node_type, "long_double")){
#if defined(__RASPBERRY_PI__)
            result = 8;
#elif defined(__ISH__)
            result = 12;
#else
            result = 16;
#endif

            int i;
            for(i=0; i<node_type2->mArrayDimentionNum; i++) {
                result *= node_type2->mArrayNum[i];
            }
        }
        else if(type_identify_with_class_name(node_type, "__uint128_t"))
        {
#if defined(__RASPBERRY_PI__)
            result = 8;
#else
            result = 16;
#endif

            int i;
            for(i=0; i<node_type2->mArrayDimentionNum; i++) {
                result *= node_type2->mArrayNum[i];
            }
        }
    }

    return result;
}

int get_llvm_alignment_from_node_type(sNodeType* node_type)
{
    int result = 0;

    sCLClass* klass = node_type->mClass;

    if(klass->mFlags & CLASS_FLAGS_STRUCT) {
        result = 8;
    }
    else if(klass->mFlags & CLASS_FLAGS_UNION) {
        result = 8;
    }
    else if(node_type->mPointerNum > 0) {
        result = 8;
    }
    else if(type_identify_with_class_name(node_type, "char"))
    {
        result = 1;
    }
    else if(type_identify_with_class_name(node_type, "short"))
    {
        result = 2;
    }
    else if(type_identify_with_class_name(node_type, "int"))
    {
        result = 4;
    }
    else if(type_identify_with_class_name(node_type, "bool"))
    {
        result = 1;
    }
    else if(type_identify_with_class_name(node_type, "lambda"))
    {
        result = 8;
    }

    return result;
}

#ifdef __32BIT_CPU__
BOOL create_llvm_union_type(sNodeType* node_type, sNodeType* generics_type, BOOL undefined_body, sCompileInfo* info)
{
    sCLClass* klass = node_type->mClass;
    char* class_name = CLASS_NAME(klass);

    sStruct* struct_ = get_struct_from_table(class_name);

    if(struct_ == NULL && !undefined_body) {
        LLVMTypeRef field_types[STRUCT_FIELD_MAX];

        uint64_t max_size = 0;
        int num_fields = 1;

        int i;
        for(i=0; i<klass->mNumFields; i++) {
            sNodeType* field = clone_node_type(klass->mFields[i]);

            if(!solve_generics(&field, generics_type)) {
                compile_err_msg(info, "can't solve generics types");
                return FALSE;
            }

            int alignment = 0;
            uint64_t size = get_size_from_node_type(field, &alignment);

            if(size > max_size) {
                max_size = size;

                if(max_size > 8) {
                    sNodeType* field_type = create_node_type_with_class_name("long");
                    field_types[0] = create_llvm_type_from_node_type(field_type);

                    sNodeType* field_type2 = create_node_type_with_class_name("char");
                    max_size = (max_size + 3) & ~3;
                    field_type2->mArrayNum[0] = max_size-8;
                    field_type2->mArrayDimentionNum = 1;
                    field_types[1] = create_llvm_type_from_node_type(field_type2);

                    num_fields = 2;
                }
                else {
                    field_types[0] = create_llvm_type_from_node_type(field);

                    num_fields = 1;
                }
            }
        }

        LLVMTypeRef struct_type = LLVMStructCreateNamed(gContext, class_name);

        LLVMStructSetBody(struct_type, field_types, num_fields, FALSE);

        if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
            fprintf(stderr, "overflow struct number\n");
            exit(2);
        }
    }
    else if(struct_ == NULL && undefined_body) {
        LLVMTypeRef field_types[STRUCT_FIELD_MAX];

        int num_fields = 0;
        LLVMTypeRef struct_type = LLVMStructCreateNamed(gContext, class_name);

        if(!add_struct_to_table(class_name, node_type, struct_type, TRUE)) {
            fprintf(stderr, "overflow struct number\n");
            exit(2);
        }
    }
    else if(struct_ && struct_->mUndefinedBody) {
        if(undefined_body) {
            return TRUE;
        }
        else {
            int num_fields = 1;

            LLVMTypeRef field_types[STRUCT_FIELD_MAX];

            uint64_t max_size = 0;

            int i;
            for(i=0; i<klass->mNumFields; i++) {
                sNodeType* field = clone_node_type(klass->mFields[i]);

                if(!solve_generics(&field, generics_type)) {
                    compile_err_msg(info, "can't solve generics types");
                    return FALSE;
                }

                int alignment = 0;
                uint64_t size = get_size_from_node_type(field, &alignment);

                if(size > max_size) {
                    field_types[0] = create_llvm_type_from_node_type(field);
                    max_size = size;
                }
                if(size > max_size) {
                    field_types[0] = create_llvm_type_from_node_type(field);
                    num_fields = 1;
                }
            }

            LLVMTypeRef struct_type = struct_->mLLVMType;

            LLVMStructSetBody(struct_type, field_types, num_fields, FALSE);

            struct_->mUndefinedBody = FALSE;
        }
    }
    else if((klass->mFlags & CLASS_FLAGS_GENERICS) && generics_type == NULL) {
        LLVMTypeRef struct_type = NULL;

        if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
            fprintf(stderr, "overflow struct number\n");
            exit(2);
        }
    }

    return TRUE;
}
#else
BOOL create_llvm_union_type(sNodeType* node_type, sNodeType* generics_type, BOOL undefined_body, sCompileInfo* info)
{
    sCLClass* klass = node_type->mClass;
    char* class_name = CLASS_NAME(klass);

    sStruct* struct_ = get_struct_from_table(class_name);

    if(struct_ == NULL && !undefined_body) {
        LLVMTypeRef field_types[STRUCT_FIELD_MAX];

        uint64_t max_size = 0;

        int i;
        for(i=0; i<klass->mNumFields; i++) {
            sNodeType* field = clone_node_type(klass->mFields[i]);

            if(!solve_generics(&field, generics_type)) {
                compile_err_msg(info, "can't solve generics types");
                return FALSE;
            }

            int alignment = 0;
            uint64_t size = get_size_from_node_type(field, &alignment);

            if(size > max_size) {
                field_types[0] = create_llvm_type_from_node_type(field);
                max_size = size;
            }
        }

        int num_fields = 1;
        LLVMTypeRef struct_type = LLVMStructCreateNamed(gContext, class_name);

        LLVMStructSetBody(struct_type, field_types, num_fields, FALSE);

        if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
            fprintf(stderr, "overflow struct number\n");
            exit(2);
        }
    }
    else if(struct_ == NULL && undefined_body) {
        LLVMTypeRef field_types[STRUCT_FIELD_MAX];

        int num_fields = 0;
        LLVMTypeRef struct_type = LLVMStructCreateNamed(gContext, class_name);

        if(!add_struct_to_table(class_name, node_type, struct_type, TRUE)) {
            fprintf(stderr, "overflow struct number\n");
            exit(2);
        }
    }
    else if(struct_ && struct_->mUndefinedBody) {
        if(undefined_body) {
            return TRUE;
        }
        else {
            LLVMTypeRef field_types[STRUCT_FIELD_MAX];

            uint64_t max_size = 0;

            int i;
            for(i=0; i<klass->mNumFields; i++) {
                sNodeType* field = clone_node_type(klass->mFields[i]);

                if(!solve_generics(&field, generics_type)) {
                    compile_err_msg(info, "can't solve generics types");
                    return FALSE;
                }

                int alignment = 0;
                uint64_t size = get_size_from_node_type(field, &alignment);

                if(size > max_size) {
                    field_types[0] = create_llvm_type_from_node_type(field);
                    max_size = size;
                }
            }

            int num_fields = 1;
            LLVMTypeRef struct_type = struct_->mLLVMType;

            LLVMStructSetBody(struct_type, field_types, num_fields, FALSE);

            struct_->mUndefinedBody = FALSE;
        }
    }
    else if((klass->mFlags & CLASS_FLAGS_GENERICS) && generics_type == NULL) {
        LLVMTypeRef struct_type = NULL;

        if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
            fprintf(stderr, "overflow struct number\n");
            exit(2);
        }
    }

    return TRUE;
}
#endif


void compile_err_msg(sCompileInfo* info, const char* msg, ...)
{
    char msg2[1024];

    va_list args;
    va_start(args, msg);
    vsnprintf(msg2, 1024, msg, args);
    va_end(args);

    static int output_num = 0;

    if(output_num < COMPILE_ERR_MSG_MAX && !info->pinfo->no_output_err_msg) {
        if(info->in_generics_function) {
            fprintf(stderr, "%s:%d generics function error\n", info->generics_sname, info->generics_sline);
            fprintf(stderr, "%s:%d: %s\n", info->sname, info->sline, msg2);
        }
        else if(info->in_inline_function) {
            fprintf(stderr, "%s:%d inline function error\n", info->sname, info->sline);
            fprintf(stderr, "%s:%d: %s\n", info->in_inline_function_name, info->inline_sline, msg2);
        }
        else {
            fprintf(stderr, "%s:%d: %s\n", info->sname, info->sline, msg2);
        }
        output_num++;
    }
}

BOOL compile_block(sNodeBlock* block, sCompileInfo* info)
{
    int sline_before = info->pinfo->sline;

    sVarTable* old_table = info->pinfo->lv_table;
    info->pinfo->lv_table = block->mLVTable;

    BOOL has_result = block->mHasResult;

    int stack_num_before = info->stack_num;

    BOOL last_expression_is_return = FALSE;

    if(block->mNumNodes == 0) {
        info->type = create_node_type_with_class_name("void");
    }
    else {
        BOOL last_expression_is_return = FALSE;
        int i;
        for(i=0; i<block->mNumNodes; i++) {
            unsigned int node = block->mNodes[i];

            char sname[PATH_MAX];
            xstrncpy(sname, info->sname, VAR_NAME_MAX);
            int sline = info->sline;

            xstrncpy(info->sname, gNodes[node].mSName, PATH_MAX);
            info->sline = gNodes[node].mLine;

            if(gNCDebug) {
                if(info->in_generics_function || info->in_inline_function || info->in_lambda_function || info->empty_function) {
                    setNullCurrentDebugLocation(info->sline, info);
                }
                else {
                    setCurrentDebugLocation(info->sline, info);
                }
            }
            
            if(!compile(node, info)) {
                if(gNCType && !gNCGlobal && !gNCFunction && !gNCClass && !gNCTypedef) {
                    show_node_type(info->type);
                    gNCType = FALSE;
                }
                info->pinfo->lv_table = old_table;
                return FALSE;
            }

            xstrncpy(info->sname, sname, VAR_NAME_MAX);
            info->sline = sline;

            arrange_stack(info, stack_num_before);

            if(gNodes[node].mNodeType == kNodeTypeReturn) {
                last_expression_is_return = TRUE;
            }
            else {
                last_expression_is_return = FALSE;
            }
        }

        info->last_expression_is_return = last_expression_is_return;
    }

    info->pinfo->sline = sline_before;

    info->pinfo->lv_table = old_table;
    
    if(gNCType && block->mTerminated) {
        if(!gNCGlobal && !gNCFunction && !gNCClass && !gNCTypedef) {
            show_node_type(info->type);
            gNCType = FALSE;
            return FALSE;
        }
        return TRUE;
    }

    return TRUE;
}

BOOL compile_conditional_expression(unsigned int node, sCompileInfo* info)
{
    if(!compile(node, info)) {
        if(gNCType && !gNCGlobal && !gNCFunction && !gNCClass && !gNCTypedef) {
            show_node_type(info->type);
            gNCType = FALSE;
        }
        return FALSE;
    }
    
    if(gNodes[node].mTerminated) {
        if(gNCType && !gNCGlobal && !gNCFunction && !gNCClass && !gNCTypedef) {
            show_node_type(info->type);
            gNCType = FALSE;
        }
        return FALSE;
    }

    return TRUE;
}

BOOL create_generics_struct_type(sNodeType* node_type)
{
    sCLClass* klass = node_type->mClass;

    char* class_name = CLASS_NAME(klass);

    sGenericsStructType* generics_struct_type = get_generics_struct_from_table(class_name);

    if(generics_struct_type) {
        sNodeType* generics_type = clone_node_type(node_type);
        sNodeType* struct_type = clone_node_type(generics_struct_type->mType);

        if(!solve_generics(&struct_type, generics_type)) {
            return FALSE;
        }

        char struct_name[VAR_NAME_MAX];
        create_generics_struct_name(struct_name, VAR_NAME_MAX, generics_type);

        BOOL undefined_body = FALSE;
        create_llvm_struct_type(struct_name, generics_type, generics_type, undefined_body);
    }

    return TRUE;
}


void set_debug_info_to_variable(LLVMValueRef value, sNodeType* node_type, char* name, int sline, sCompileInfo* info)
{
    if(gNCDebug && !info->in_generics_function && !info->in_inline_function && !info->in_lambda_function && !info->empty_function && !info->in_thread_function) {
        char cwd[PATH_MAX];
        getcwd(cwd, PATH_MAX);

        char directory[PATH_MAX];

        snprintf(directory, PATH_MAX, "%s", cwd);

        int directory_len = strlen(directory);
        
        LLVMMetadataRef di_type = create_llvm_debug_type(node_type, info);
        
        int arg_no = 0;
        
        LLVMMetadataRef file = LLVMDIBuilderCreateFile(gDIBuilder, gFName, strlen(gFName), directory, directory_len);
        LLVMMetadataRef scope = info->function_meta_data;
        LLVMMetadataRef llvm_info = LLVMDIBuilderCreateParameterVariable(gDIBuilder
                    , scope
                    , name
                    , strlen(name)
                    , arg_no
                    , file
                    , sline
                    , (LLVMMetadataRef)di_type
                    , FALSE
                    , 0);
        
        LLVMMetadataRef expr = LLVMDIBuilderCreateExpression(gDIBuilder, NULL, 0);
        int colum = 0;
        LLVMMetadataRef scope2 = info->function_meta_data;
        LLVMMetadataRef inlinedat = NULL;
        LLVMMetadataRef loc = LLVMDIBuilderCreateDebugLocation(gContext, sline, colum, scope2, inlinedat);
        
        LLVMDIBuilderInsertDeclareAtEnd(gDIBuilder, value, llvm_info, expr, loc, LLVMGetInsertBlock(gBuilder));
    }
}
