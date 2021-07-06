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

void clear_right_value_objects(sCompileInfo* info)
{
    struct sRightValueObject* it = info->right_value_objects;
    while(it) {
        struct sRightValueObject* it_next = it->next;
        free(it);
        it = it_next;
    }

    info->right_value_objects = NULL;
}

void append_object_to_right_values(LLVMValueRef obj, sNodeType* node_type, sCompileInfo* info)
{
    struct sRightValueObject* new_list_item = calloc(1, sizeof(struct sRightValueObject));
    new_list_item->obj = obj;
    new_list_item->node_type = clone_node_type(node_type);
    new_list_item->next = info->right_value_objects;
    new_list_item->freed = FALSE;
    xstrncpy(new_list_item->fun_name, gFunctionName, VAR_NAME_MAX);
    info->right_value_objects = new_list_item;
}

void remove_object_from_right_values(LLVMValueRef obj, sCompileInfo* info)
{
    struct sRightValueObject* it = info->right_value_objects;
    struct sRightValueObject* it_before = NULL;
    while(it) {
        if(it->obj == obj) {
            if(it_before == NULL) {
                info->right_value_objects = it->next;
            }
            else {
                it_before->next = it->next;
            }
            free(it);
        }
        it_before = it;
        it = it->next;
    }
}

BOOL is_right_values(LLVMValueRef obj, sCompileInfo* info)
{
    struct sRightValueObject* it = info->right_value_objects;
    while(it) {
        if(it->obj == obj) {
            return TRUE;
        }
        it = it->next;
    }

    return FALSE;
}

void free_object(sNodeType* node_type, LLVMValueRef obj, sCompileInfo* info);

void free_right_value_objects(sCompileInfo* info)
{
    struct sRightValueObject* it = info->right_value_objects;

    while(it) {
        struct sRightValueObject* it_next = it->next;
        if(!it->freed) {
            if(strcmp(it->fun_name, gFunctionName) == 0) {
                sNodeType* node_type = clone_node_type(it->node_type);

                if(is_typeof_type(node_type))
                {
                    if(!solve_typeof(&node_type, info))
                    {
                        compile_err_msg(info, "Can't solve typeof types");
                        show_node_type(node_type);
                        info->err_num++;
                        return;
                    }
                }

                if(info->generics_type) {
                    if(!solve_generics(&node_type, info->generics_type)) 
                    {
                        compile_err_msg(info, "Can't solve generics types(3)");
                        show_node_type(node_type);
                        show_node_type(info->generics_type);
                        info->err_num++;

                        return;
                    }
                }

                free_object(node_type, it->obj, info);

                it->freed = TRUE;
            }
        }

        it = it_next;
    }
}

LLVMTypeRef create_llvm_type_with_class_name(char* class_name);
sFunction* get_function_from_table(char* name);
BOOL create_generics_function(LLVMValueRef* llvm_fun, sFunction* fun, char* fun_name, sNodeType* generics_type, sCompileInfo* info);

void free_object(sNodeType* node_type, LLVMValueRef obj, sCompileInfo* info)
{
    if(node_type->mPointerNum > 0) {
        sCLClass* klass = node_type->mClass;

        char* class_name = CLASS_NAME(klass);

        char fun_name[VAR_NAME_MAX];
        snprintf(fun_name, VAR_NAME_MAX, "%s_finalize", class_name);

        sFunction* finalizer = get_function_from_table(fun_name);

        if(node_type->mHeap && finalizer != NULL) {
            if(finalizer->mGenericsFunction) {
                LLVMValueRef llvm_fun = NULL;

                if(!create_generics_function(&llvm_fun, finalizer, fun_name, node_type, info)) {
                    fprintf(stderr, "can't craete generics finalizer %s\n", fun_name);
                    return;
                }

                int num_params = 1;

                LLVMValueRef llvm_params[PARAMS_MAX];
                memset(llvm_params, 0, sizeof(LLVMValueRef)*PARAMS_MAX);

                llvm_params[0] = obj;

                LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "");
            }
            else {
                int num_params = 1;

                LLVMValueRef llvm_params[PARAMS_MAX];
                memset(llvm_params, 0, sizeof(LLVMValueRef)*PARAMS_MAX);

                llvm_params[0] = obj;

                LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, fun_name);
                LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "");
            }
        }

        /// free ///
        int num_params = 1;

        LLVMValueRef llvm_params[PARAMS_MAX];
        memset(llvm_params, 0, sizeof(LLVMValueRef)*PARAMS_MAX);


        char* fun_name2 = "free";
        //char* fun_name2 = "ncfree";

        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("char*");

        obj = LLVMBuildCast(gBuilder, LLVMBitCast, obj, llvm_type, "castAK");

        llvm_params[0] = obj;

        LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, fun_name2);
        LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "");

        /// remove right value objects from list
        remove_object_from_right_values(obj, info);
    }
}



LLVMTypeRef create_llvm_type_from_node_type(sNodeType* node_type);

LLVMValueRef clone_object(sNodeType* node_type, LLVMValueRef obj, sCompileInfo* info)
{
    sCLClass* klass = node_type->mClass;

    if(node_type->mPointerNum > 0) {
        sCLClass* klass = node_type->mClass;

        char* class_name = CLASS_NAME(klass);

        char fun_name[VAR_NAME_MAX];
        snprintf(fun_name, VAR_NAME_MAX, "%s_clone", class_name);

        sFunction* cloner = get_function_from_table(fun_name);

        if(cloner != NULL) {
            if(cloner->mGenericsFunction) {
                LLVMValueRef llvm_fun = NULL;

                if(!create_generics_function(&llvm_fun, cloner, fun_name, node_type, info)) {
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
    sCLClass* va_list_struct = alloc_struct("__builtin_va_list", FALSE);
    sNodeType* node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }

    class_name = "va_list";
    va_list_struct = alloc_struct("va_list", FALSE);
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
    sCLClass* va_list_struct = alloc_struct("__builtin_va_list", FALSE);
    sNodeType* node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }

    class_name = "va_list";
    va_list_struct = alloc_struct("va_list", FALSE);
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
    sCLClass* va_list_struct = alloc_struct("__builtin_va_list", FALSE);
    sNodeType* node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }

    class_name = "va_list";
    va_list_struct = alloc_struct("va_list", FALSE);
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
    sCLClass* va_list_struct = alloc_struct("__builtin_va_list", FALSE);
    sNodeType* node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }

    class_name = "va_list";
    va_list_struct = alloc_struct("va_list", FALSE);
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
    sCLClass* va_list_struct = alloc_struct("__builtin_va_list", FALSE);
    sNodeType* node_type = create_node_type_with_class_pointer(va_list_struct);

    if(!add_struct_to_table(class_name, node_type, struct_type, FALSE)) {
        fprintf(stderr, "overflow struct number\n");
        exit(2);
    }

    class_name = "va_list";
    va_list_struct = alloc_struct("va_list", FALSE);
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
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL))
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
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL))
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
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL))
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
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL, FALSE, NULL))
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
    LLVMPrintModuleToFile(gModule, sname2, NULL);

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

                case kNodeTypeFunction:
                    sNodeBlock_free(gNodes[i].uValue.sFunction.mNodeBlock);
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



LLVMMetadataRef create_llvm_debug_type(sNodeType* node_type)
{
    LLVMMetadataRef result = NULL;

    if(node_type->mPointerNum > 0) {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "pointer", strlen("pointer"), 64, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "pointer", strlen("pointer"), 64, 0, 0);
#endif
    }
    else if(node_type->mArrayDimentionNum > 0) {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "pointer", strlen("pointer"), 64, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "pointer", strlen("pointer"), 64, 0, 0);
#endif
    }
    else if(type_identify_with_class_name(node_type, "int")) {
#if LLVM_VERSION <= 7
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "int", strlen("int"), 32, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "int", strlen("int"), 32, 0, 0);
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
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 16, 0);
#else
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 16, 0, 0);
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

    return result;
}

void createDebugFunctionInfo(int sline, char* fun_name, sFunction* function, LLVMValueRef llvm_function, char* module_name, sCompileInfo* info)
{
    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);

    char directory[PATH_MAX];

    snprintf(directory, PATH_MAX, "%s", cwd);

    int directory_len = strlen(directory);

    LLVMMetadataRef file = LLVMDIBuilderCreateFile(gDIBuilder, gFName, strlen(gFName), directory, directory_len);


    int num_params = function->mNumParams;
    LLVMMetadataRef param_types[PARAMS_MAX];

    int i;
    for(i=0; i<num_params; i++) {
        param_types[i] = create_llvm_debug_type(function->mParamTypes[i]);
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

    LLVMSetSubprogram(llvm_function, function_meta_data);
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
//        memset(gNodes + gSizeNodes, 0, sizeof(sNodeTree)*(new_size - gSizeNodes));

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
        int a = 0;
        int b = 1;
        int c = b/a;
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
        if(node_type->mPointerNum == 0) {
            result_type = LLVMPointerType(result_type, 0);
        }
    }

    if(result_type == NULL) {
        fprintf(stderr, "invalid type %s(1)\n", class_name);
        int a = 0;
        int b = 1;
        int c = b/a;
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
            if((*right_type)->mPointerNum == 0 && (type_identify_with_class_name(*right_type, "char") || type_identify_with_class_name(*right_type, "short") || type_identify_with_class_name(*right_type, "bool"))) 
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
#ifdef __32BIT_CPU__
                    result = (result + 3) & ~3;
                    result += size;
#else
                    result = (result + 7) & ~7;
                    result += size;
#endif
                }
                else {
                    result = (result + *alignment-1) & ~(*alignment-1);
                    result += size;
                }

                if(struct_ || union_) {
#ifdef __32BIT_CPU__
                    if(element_type->mPointerNum > 0) {
                        *alignment = 4;
                    }
#else
                    if(element_type->mPointerNum > 0) {
                        *alignment = 8;
                    }
#endif



/*
                    if(field_type->mArrayDimentionNum > 0) {
                        *alignment = element_size;
                    }
                    else if(field_type->mPointerNum > 0) {
                        *alignment = 4;
                    }
                    if(element_type->mPointerNum > 0) {
                        *alignment = element_size;
                    }
                    else {
                        *alignment = element_size;
                    }
*/
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
#ifdef __32BIT_CPU__
                    result += size;
                    result = (result + 3) & ~3;
#else
                    result += size;
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

    return result;
}

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

void compile_err_msg(sCompileInfo* info, const char* msg, ...)
{
    char msg2[1024];

    va_list args;
    va_start(args, msg);
    vsnprintf(msg2, 1024, msg, args);
    va_end(args);

    static int output_num = 0;

    if(output_num < COMPILE_ERR_MSG_MAX && !info->pinfo->no_output_err_msg) {
       fprintf(stderr, "%s:%d: %s\n", info->sname, info->sline, msg2);
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

    clear_right_value_objects(info);

    if(block->mNumNodes == 0) {
        free_right_value_objects(info);
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

            if(info->in_generics_function) {
                xstrncpy(info->sname, info->generics_sname, PATH_MAX);
                info->sline = info->generics_sline;
            }
            else if(info->in_inline_function) {
                xstrncpy(info->sname, gNodes[node].mSName, PATH_MAX);
                info->sline = info->inline_sline;
            }
            else if(info->in_lambda_function) {
                xstrncpy(info->sname, gNodes[node].mSName, PATH_MAX);
                info->sline = info->lambda_sline;
            }
            else {
                xstrncpy(info->sname, gNodes[node].mSName, PATH_MAX);
                info->sline = gNodes[node].mLine;
            }

            if(gNCDebug) {
                if(info->in_generics_function || info->in_inline_function || info->in_lambda_function) {
                    setNullCurrentDebugLocation(info->sline, info);
                }
                else {
                    setCurrentDebugLocation(info->sline, info);
                }
            }

            if(!compile(node, info)) {
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

            if(!last_expression_is_return) {
                free_right_value_objects(info);
            }
        }


        info->last_expression_is_return = last_expression_is_return;
    }

    if(!info->last_expression_is_return) {
        free_objects(info->pinfo->lv_table, info);
    }

    info->pinfo->sline = sline_before;

    info->pinfo->lv_table = old_table;

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

