#include "common.h"
#include <llvm-c/Core.h>

sNodeTree* gNodes;

int gSizeNodes = 0;
int gUsedNodes = 0;

LLVMContextRef gContext;
LLVMModuleRef  gModule;
LLVMBuilderRef gBuilder;
LLVMDIBuilderRef gDIBuilder;

LLVMValueRef gFunction;

LVALUE* gLLVMStack;
LVALUE* gLLVMStackHead;

struct sRightValueObject {
    LLVMValueRef obj;
    sNodeType* node_type;
    struct sRightValueObject* next;
};

struct sRightValueObject* gRightValueObjects;

void append_object_to_right_values(LLVMValueRef obj, sNodeType* node_type, sCompileInfo* info)
{
    struct sRightValueObject* new_list_item = calloc(1, sizeof(struct sRightValueObject));
    new_list_item->obj = obj;
    new_list_item->node_type = clone_node_type(node_type);
    new_list_item->next = gRightValueObjects;
    gRightValueObjects = new_list_item;
}

void remove_object_from_right_values(LLVMValueRef obj)
{
    struct sRightValueObject* it = gRightValueObjects;
    struct sRightValueObject* it_before = NULL;
    while(it) {
        if(it->obj == obj) {
            if(it_before == NULL) {
                gRightValueObjects = it->next;
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

struct sFunctionStruct {
    char mName[VAR_NAME_MAX];
    int mNumParams;
    char mParamNames[PARAMS_MAX][VAR_NAME_MAX];
    sNodeType* mParamTypes[PARAMS_MAX];
    sNodeType* mResultType;
    LLVMValueRef mLLVMFunction;
    char* mBlockText;
    BOOL mGenericsFunction;
    BOOL mVarArgs;
    int mNumGenerics;
    char mGenericsTypeNames[GENERICS_TYPES_MAX][VAR_NAME_MAX];
};

typedef struct sFunctionStruct sFunction;

LLVMTypeRef create_llvm_type_with_class_name(char* class_name);
sFunction* get_function_from_table(char* name);

void free_object(sNodeType* node_type, LLVMValueRef obj, sCompileInfo* info)
{
    sCLClass* klass = node_type->mClass;

    char* class_name = CLASS_NAME(klass);

    char fun_name[VAR_NAME_MAX];
    snprintf(fun_name, VAR_NAME_MAX, "%s_finalize", class_name);

    sFunction* finalizer = get_function_from_table(fun_name);

    if(finalizer != NULL) {
        int num_params = 1;

        LLVMValueRef llvm_params[PARAMS_MAX];
        memset(llvm_params, 0, sizeof(LLVMValueRef)*PARAMS_MAX);

        llvm_params[0] = obj;

        LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, fun_name);
        LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "");
    }

    /// free ///
    if(node_type->mHeap && node_type->mPointerNum > 0) {
        int num_params = 1;

        LLVMValueRef llvm_params[PARAMS_MAX];
        memset(llvm_params, 0, sizeof(LLVMValueRef)*PARAMS_MAX);

        char* fun_name = "free";

        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("char*");

        LLVMValueRef llvm_value = LLVMBuildCast(gBuilder, LLVMBitCast, obj, llvm_type, "cast");

        llvm_params[0] = llvm_value;

        LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, fun_name);
        LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "");
    }

    /// remove right value objects from list
    remove_object_from_right_values(obj);
}

void free_right_value_objects(sCompileInfo* info)
{
    struct sRightValueObject* it = gRightValueObjects;
    struct sRightValueObject* it_next = NULL;
    while(it) {
        it_next = it->next;
        free_object(it->node_type, it->obj, info);
        it = it_next;
    }
}

LLVMTypeRef create_llvm_type_with_class_name(char* class_name);

BOOL add_struct_to_table(char* name, sNodeType* node_type, LLVMTypeRef llvm_type, BOOL undefined_body);
BOOL add_function_to_table(char* name, int num_params, char** param_names, sNodeType** param_types, sNodeType* result_type, LLVMValueRef llvm_fun, char* block_text, BOOL generics_function, BOOL var_args, int num_generics, char** generics_type_names);
LLVMTypeRef create_llvm_type_from_node_type(sNodeType* node_type);
BOOL create_generics_struct_type(sNodeType* node_type);

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

    gRightValueObjects = NULL;

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

        LLVMMetadataRef compile_unit = LLVMDIBuilderCreateCompileUnit(gDIBuilder, LLVMDWARFSourceLanguageC, file, procedure, procedure_len, is_optimized, flags, flags_len, runtime_ver, split_name,  split_name_len, LLVMDWARFEmissionFull, dwold, split_debugginginling, debug_info_for_profiling, sys_root, sys_root_len, sdk, sdk_len);

        char include_path[PATH_MAX];

        snprintf(include_path, PATH_MAX, "%s/%s", cwd, gFName);

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
#ifdef __X86_64_CPU__
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
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL))
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
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL))
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
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL))
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
        if(!add_function_to_table(name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_args, 0, NULL))
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

    struct sRightValueObject* it = gRightValueObjects;
    struct sRightValueObject* it_next = NULL;
    while(it) {
        it_next = it->next;
        free(it);
        it = it_next;
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


/*
static DISubroutineType* createDebugFunctionType(sFunction* function, DIFile* unit)
{
    SmallVector<Metadata *, 8> EltTys;

    sNodeType* result_type = function->mResultType;
    DIType* debug_result_type = create_debug_type(result_type);

    EltTys.push_back(debug_result_type);

    for(int i = 0; i<function->mNumParams; i++) {
        sNodeType* arg_type = function->mParamTypes[i];
        DIType* debug_arg_type = create_debug_type(result_type);

        EltTys.push_back(debug_arg_type);
    }

    return DBuilder->createSubroutineType(DBuilder->getOrCreateTypeArray(EltTys));
}
*/

LLVMMetadataRef create_llvm_debug_type(sNodeType* node_type)
{
    LLVMMetadataRef result = NULL;

    if(node_type->mPointerNum > 0) {
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "pointer", strlen("pointer"), 64, 0, 0);
    }
    else if(node_type->mArrayDimentionNum > 0) {
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "pointer", strlen("pointer"), 64, 0, 0);
    }
    else if(type_identify_with_class_name(node_type, "int")) {
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "int", strlen("int"), 32, 0, 0);
    }
    else if(type_identify_with_class_name(node_type, "char")) {
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "char", strlen("char"), 8, 0, 0);
    }
    else if(type_identify_with_class_name(node_type, "short")) {
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "short", strlen("short"), 16, 0, 0);
    }
    else if(type_identify_with_class_name(node_type, "long")) {
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "long", strlen("long"), 64, 0, 0);
    }
    else if(type_identify_with_class_name(node_type, "float")) {
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 16, 0, 0);
    }
    else if(type_identify_with_class_name(node_type, "_Float16") || type_identify_with_class_name(node_type, "_Float16x")) 
    {
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 16, 0, 0);
    }
    else if(type_identify_with_class_name(node_type, "_Float32") || type_identify_with_class_name(node_type, "_Float32x")) 
    {
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 16, 0, 0);
    }
    else if(type_identify_with_class_name(node_type, "_Float64") || type_identify_with_class_name(node_type, "_Float64x")) 
    {
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 64, 0, 0);
    }
    else if(type_identify_with_class_name(node_type, "_Float128") || type_identify_with_class_name(node_type, "_Float128x")) 
    {
        result = LLVMDIBuilderCreateBasicType(gDIBuilder, "float", strlen("float"), 128, 0, 0);
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
        gNodes = (sNodeTree*)xrealloc(gNodes, sizeof(sNodeTree)*new_size);
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
        exit(2);
    }
}

LVALUE* get_value_from_stack(int offset)
{
    return gLLVMStack + offset;
}

struct sStructStruct {
    char mName[VAR_NAME_MAX];
    LLVMTypeRef mLLVMType;
    sNodeType* mNodeType;
    BOOL mUndefinedBody;
};

typedef struct sStructStruct sStruct;

sStruct gStructs[STRUCT_NUM_MAX];

BOOL add_struct_to_table(char* name, sNodeType* node_type, LLVMTypeRef llvm_type, BOOL undefined_body)
{
    int hash_value = get_hash_key(name, STRUCT_NUM_MAX);
    sStruct* p = gStructs + hash_value;

    while(1) {
        if(p->mName[0] == 0) {
            xstrncpy(p->mName, name, VAR_NAME_MAX);

            p->mNodeType = clone_node_type(node_type);
            p->mLLVMType = llvm_type;
            p->mUndefinedBody = undefined_body;

            return TRUE;
        }
        else {
            if(strcmp(p->mName, name) == 0) {
                xstrncpy(p->mName, name, VAR_NAME_MAX);

                p->mNodeType = clone_node_type(node_type);
                p->mLLVMType = llvm_type;
                p->mUndefinedBody = undefined_body;

                return TRUE;
            }
            else {
                p++;

                if(p == gStructs + STRUCT_NUM_MAX) {
                    p = gStructs;
                }
                else if(p == gStructs + hash_value) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

sStruct* get_struct_from_table(char* name)
{
    int hash_value = get_hash_key(name, STRUCT_NUM_MAX);

    sStruct* p = gStructs + hash_value;

    while(1) {
        if(p->mName[0] == 0) {
            return NULL;
        }
        else if(strcmp((char*)p->mName, name) == 0) {
            return p;
        }

        p++;

        if(p == gStructs + STRUCT_NUM_MAX) {
            p = gStructs;
        }
        else if(p == gStructs + hash_value) {
            return NULL;
        }
    }
}

struct sLabelStruct {
    char mName[VAR_NAME_MAX];
    LLVMBasicBlockRef mBlock;
};

typedef struct sLabelStruct sLabel;

sLabel gLabels[LABEL_MAX];

BOOL add_label_to_table(char* name, LLVMBasicBlockRef block)
{
    int hash_value = get_hash_key(name, LABEL_MAX);
    sLabel* p = gLabels + hash_value;

    while(1) {
        if(p->mName[0] == 0) {
            xstrncpy(p->mName, name, VAR_NAME_MAX);

            p->mBlock = block;

            return TRUE;
        }
        else {
            if(strcmp(p->mName, name) == 0) {
                xstrncpy(p->mName, name, VAR_NAME_MAX);

                p->mBlock = block;

                return TRUE;
            }
            else {
                p++;

                if(p == gLabels + LABEL_MAX) {
                    p = gLabels;
                }
                else if(p == gLabels + hash_value) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

LLVMBasicBlockRef get_label_from_table(char* name)
{
    int hash_value = get_hash_key(name, LABEL_MAX);

    sLabel* p = gLabels + hash_value;

    while(1) {
        if(p->mName[0] == 0) {
            return NULL;
        }
        else if(strcmp((char*)p->mName, name) == 0) {
            return p->mBlock;
        }

        p++;

        if(p == gLabels + LABEL_MAX) {
            p = gLabels;
        }
        else if(p == gLabels + hash_value) {
            return NULL;
        }
    }
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
        result_type = LLVMFP128TypeInContext(gContext);
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
        fprintf(stderr, "invalid type %s\n", class_name);
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

    if((left_type->mPointerNum-1 == (*right_type)->mPointerNum) && (*right_type)->mArrayDimentionNum == 1) 
    {
        if(rvalue) {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

/*
#if __DARWIN__
                Value* index = ConstantInt::get(TheContext, llvm::APInt(32, 0));
                rvalue->value = Builder.CreateGEP(rvalue->address, index);
                rvalue->value = Builder.CreateCast(Instruction::BitCast, rvalue->value, llvm_type);
                rvalue->type = clone_node_type(left_type);
#else
*/
            rvalue->value = LLVMBuildCast(gBuilder, LLVMBitCast, rvalue->address, llvm_type, "autocast");
//#endif
        }

        *right_type = clone_node_type(left_type);
    }
    else if(left_type->mPointerNum > 0 && (*right_type)->mPointerNum > 0) {
        if(rvalue) {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

            rvalue->value = LLVMBuildCast(gBuilder, LLVMBitCast, rvalue->value, llvm_type, "cast");
            rvalue->type = clone_node_type(left_type);
        }

        *right_type = clone_node_type(left_type);
    }
    else if(type_identify_with_class_name(left_type, "bool"))
    {
        if(rvalue) {
            if(type_identify_with_class_name(*right_type, "int")) {
                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("bool");

                LLVMValueRef cmp_right_value = LLVMConstInt(llvm_type, 0, FALSE);
                rvalue->value = LLVMBuildICmp(gBuilder, LLVMIntNE, rvalue->value, cmp_right_value, "icmp");
            }

            rvalue->type = create_node_type_with_class_name("bool");
        }

        *right_type = create_node_type_with_class_name("bool");
    }
    else if(type_identify_with_class_name(left_type, "long"))
    {
        if(rvalue) {
            if(type_identify_with_class_name(*right_type, "int") || type_identify_with_class_name(*right_type, "char") || type_identify_with_class_name(*right_type, "short")) {
                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("long");

                if(left_type->mUnsigned) {
                    rvalue->value = LLVMBuildCast(gBuilder, LLVMZExt, rvalue->value, llvm_type, "icast");
                }
                else {
                    rvalue->value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue->value, llvm_type, "icast");
                }
            }

            rvalue->type = create_node_type_with_class_name("long");
        }

        *right_type = create_node_type_with_class_name("long");
    }
    else if(type_identify_with_class_name(left_type, "int"))
    {
        if(rvalue) {
            if(type_identify_with_class_name(*right_type, "char") || type_identify_with_class_name(*right_type, "short")) {
                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

                if(left_type->mUnsigned) {
                    rvalue->value = LLVMBuildCast(gBuilder, LLVMZExt, rvalue->value, llvm_type, "icast");
                }
                else {
                    rvalue->value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue->value, llvm_type, "icast");
                }
            }
            else if(type_identify_with_class_name(*right_type, "long")) {
                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

                rvalue->value = LLVMBuildTrunc(gBuilder, rvalue->value, llvm_type, "icast");
            }

            rvalue->type = create_node_type_with_class_name("int");
        }

        *right_type = create_node_type_with_class_name("int");
    }
    else if(type_identify_with_class_name(left_type, "char*") && (type_identify_with_class_name(*right_type, "va_list") || type_identify_with_class_name(*right_type, "__builtin_va_list")))
    {
        if(rvalue) {
            LLVMTypeRef llvm_type = create_llvm_type_with_class_name("char*");
            rvalue->value = LLVMBuildCast(gBuilder, LLVMBitCast, rvalue->value, llvm_type, "cast");
            rvalue->type = create_node_type_with_class_name("char*");
        }

        *right_type = create_node_type_with_class_name("char*");
    }
    else if((type_identify_with_class_name(left_type, "__builtin_va_list") || type_identify_with_class_name(left_type, "va_list")) && type_identify_with_class_name(*right_type, "char*"))
    {
        if(rvalue) {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

            rvalue->value = LLVMBuildCast(gBuilder, LLVMBitCast, rvalue->value, llvm_type, "cast");
            rvalue->type = create_node_type_with_class_name("va_list");
        }

        *right_type = create_node_type_with_class_name("va_list");
    }
    else if((type_identify_with_class_name(left_type, "__builtin_va_list") || type_identify_with_class_name(left_type, "va_list")) && type_identify_with_class_name(*right_type, "char*"))
    {
        if(rvalue) {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

            rvalue->value = LLVMBuildCast(gBuilder, LLVMBitCast, rvalue->value, llvm_type, "cast");
            rvalue->type = create_node_type_with_class_name("__builtin_va_list");
        }

        *right_type = create_node_type_with_class_name("__builtin_va_list");
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

uint64_t get_size_from_node_type(sNodeType* node_type);

uint64_t get_struct_size(sCLClass* klass)
{
    uint64_t result = 0;
    int i;
    for(i=0; i<klass->mNumFields; i++) {
        sNodeType* field_type = clone_node_type(klass->mFields[i]);

        uint64_t size = get_size_from_node_type(field_type);

        if(size == 4 || size == 8) {
            result = (result + 3) & ~3;
            result += size;
        }
        else {
            result = (result + 1) & ~1;
            result += size;
        }
    }

    return result;
}

uint64_t get_union_size(sCLClass* klass)
{
    uint64_t result = 0;
    int i;
    for(i=0; i<klass->mNumFields; i++) {
        sNodeType* field_type = clone_node_type(klass->mFields[i]);

        uint64_t size = get_size_from_node_type(field_type);

        if(result < size) {
            result = size;
        }
    }

    return result;
}

uint64_t get_size_from_node_type(sNodeType* node_type)
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

        if(node_type2->mArrayDimentionNum == 1) {
            result *= node_type2->mArrayNum[0];
        }
    }
    else if(node_type2->mPointerNum > 0) {
#ifdef __32BIT_CPU__
        result = 4;
#else
        result = 8;
#endif

        if(node_type2->mArrayDimentionNum == 1) {
            result *= node_type2->mArrayNum[0];
        }
    }
    else {
        if(node_type2->mClass->mUndefinedStructType) {
        }

        if(node_type->mPointerNum == 0 && (node_type->mClass->mFlags & CLASS_FLAGS_STRUCT)) {
            result = get_struct_size(node_type->mClass);

            if(node_type->mArrayDimentionNum == 1) {
                result *= node_type->mArrayNum[0];
            }
        }
        else if(node_type->mPointerNum == 0 && (node_type->mClass->mFlags & CLASS_FLAGS_UNION)) {
            result = get_union_size(node_type->mClass);

            if(node_type->mArrayDimentionNum == 1) {
                result *= node_type->mArrayNum[0];
            }
        }
        else if(type_identify_with_class_name(node_type, "int")){
            result = 4;

            if(node_type->mArrayDimentionNum == 1) {
                result *= node_type->mArrayNum[0];
            }
        }
        else if(type_identify_with_class_name(node_type, "long")){
            result = 8;

            if(node_type->mArrayDimentionNum == 1) {
                result *= node_type->mArrayNum[0];
            }
        }
        else if(type_identify_with_class_name(node_type, "short")){
            result = 2;

            if(node_type->mArrayDimentionNum == 1) {
                result *= node_type->mArrayNum[0];
            }
        }
        else if(type_identify_with_class_name(node_type, "char")){
            result = 1;

            if(node_type->mArrayDimentionNum == 1) {
                result *= node_type->mArrayNum[0];
            }
        }
        else if(type_identify_with_class_name(node_type, "bool")){
            result = 1;

            if(node_type->mArrayDimentionNum == 1) {
                result *= node_type->mArrayNum[0];
            }
        }
        else if(type_identify_with_class_name(node_type, "float")){
            result = 4;

            if(node_type->mArrayDimentionNum == 1) {
                result *= node_type->mArrayNum[0];
            }
        }
        else if(type_identify_with_class_name(node_type, "float")){
            result = 8;

            if(node_type->mArrayDimentionNum == 1) {
                result *= node_type->mArrayNum[0];
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

            uint64_t size = get_size_from_node_type(field);

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


                uint64_t size = get_size_from_node_type(field);

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
    }
    output_num++;
}

BOOL compile_block(sNodeBlock* block, sCompileInfo* info, sNodeType* result_type)
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

            xstrncpy(info->sname, gNodes[node].mSName, PATH_MAX);
            info->sline = gNodes[node].mLine;

            if(gNCDebug) {
                setCurrentDebugLocation(info->sline, info);
            }

            if(!compile(node, info)) {
                info->pinfo->lv_table = old_table;
                return FALSE;
            }

            if(gNodes[node].mNodeType == kNodeTypeReturn) {
                last_expression_is_return = TRUE;
            }
            else {
                last_expression_is_return = FALSE;
            }

            arrange_stack(info, stack_num_before);
            free_right_value_objects(info);
        }

        info->last_expression_is_return = last_expression_is_return;
    }

    free_objects(info->pinfo->lv_table, info);

    info->pinfo->sline = sline_before;

    info->pinfo->lv_table = old_table;

    return TRUE;
}

sFunction gFuncs[FUN_NUM_MAX];

BOOL add_function_to_table(char* name, int num_params, char** param_names, sNodeType** param_types, sNodeType* result_type, LLVMValueRef llvm_fun, char* block_text, BOOL generics_function, BOOL var_args, int num_generics, char** generics_type_names)
{
    int hash_value = get_hash_key(name, FUN_NUM_MAX);
    sFunction* p = gFuncs + hash_value;

    while(1) {
        if(p->mName[0] == 0) {
            xstrncpy(p->mName, name, VAR_NAME_MAX);

            p->mNumParams = num_params;

            int i;
            for(i=0; i<num_params; i++) {
                xstrncpy(p->mParamNames[i], param_names[i], VAR_NAME_MAX);
                p->mParamTypes[i] = param_types[i];
            }

            p->mResultType = result_type;
            p->mLLVMFunction = llvm_fun;
            p->mBlockText = block_text;
            p->mGenericsFunction = generics_function;
            p->mVarArgs = var_args;
            p->mNumGenerics = num_generics;

            for(i=0; i<num_generics; i++) {
                xstrncpy(p->mGenericsTypeNames[i], generics_type_names[i], VAR_NAME_MAX);
            }

            return TRUE;
        }
        else {
            if(strcmp(p->mName, name) == 0) {
                xstrncpy(p->mName, name, VAR_NAME_MAX);

                p->mNumParams = num_params;

                int i;
                for(i=0; i<num_params; i++) {
                    xstrncpy(p->mParamNames[i], param_names[i], VAR_NAME_MAX);
                    p->mParamTypes[i] = param_types[i];
                }

                p->mResultType = result_type;
                p->mLLVMFunction = llvm_fun;
                p->mBlockText = block_text;
                p->mGenericsFunction = generics_function;
                p->mVarArgs = var_args;
                p->mNumGenerics = num_generics;

                for(i=0; i<num_generics; i++) {
                    xstrncpy(p->mGenericsTypeNames[i], generics_type_names[i], VAR_NAME_MAX);
                }

                return TRUE;
            }
            else {
                p++;

                if(p == gFuncs + FUN_NUM_MAX) {
                    p = gFuncs;
                }
                else if(p == gFuncs + hash_value) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

sFunction* get_function_from_table(char* name)
{
    int hash_value = get_hash_key(name, FUN_NUM_MAX);

    sFunction* p = gFuncs + hash_value;

    while(1) {
        if(p->mName[0] == 0) {
            return NULL;
        }
        else if(strcmp((char*)p->mName, name) == 0) {
            return p;
        }

        p++;

        if(p == gFuncs + FUN_NUM_MAX) {
            p = gFuncs;
        }
        else if(p == gFuncs + hash_value) {
            return NULL;
        }
    }
}

struct sGenericsStructTypeStruct
{
    char mName[VAR_NAME_MAX];
    sNodeType* mType;
};

typedef struct sGenericsStructTypeStruct sGenericsStructType;

sGenericsStructType gGenericsStructTypes[GENERICS_STRUCT_MAX];

BOOL add_generics_struct_type_to_table(char* name, sNodeType* node_type)
{
    int hash_value = get_hash_key(name, GENERICS_STRUCT_MAX);
    sGenericsStructType* p = gGenericsStructTypes + hash_value;

    while(1) {
        if(p->mName[0] == 0) {
            xstrncpy(p->mName, name, VAR_NAME_MAX);

            p->mType = clone_node_type(node_type);

            return TRUE;
        }
        else {
            if(strcmp(p->mName, name) == 0) {
                xstrncpy(p->mName, name, VAR_NAME_MAX);

                p->mType = clone_node_type(node_type);

                return TRUE;
            }
            else {
                p++;

                if(p == gGenericsStructTypes + GENERICS_STRUCT_MAX) {
                    p = gGenericsStructTypes;
                }
                else if(p == gGenericsStructTypes + hash_value) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

sGenericsStructType* get_generics_struct_from_table(char* name)
{
    int hash_value = get_hash_key(name, GENERICS_STRUCT_MAX);

    sGenericsStructType* p = gGenericsStructTypes + hash_value;

    while(1) {
        if(p->mName[0] == 0) {
            return NULL;
        }
        else if(strcmp((char*)p->mName, name) == 0) {
            return p;
        }

        p++;

        if(p == gGenericsStructTypes + GENERICS_STRUCT_MAX) {
            p = gGenericsStructTypes;
        }
        else if(p == gGenericsStructTypes + hash_value) {
            return NULL;
        }
    }
}


unsigned int sNodeTree_create_int_value(int value, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIntValue;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mIntValue = value;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_int_value(unsigned int node, sCompileInfo* info)
{
    int value = gNodes[node].uValue.mIntValue;

    LVALUE llvm_value;

    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

    llvm_value.value = LLVMConstInt(llvm_type, value, TRUE);
    llvm_value.type = create_node_type_with_class_name("int");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("int");

    return TRUE;
}

unsigned int sNodeTree_create_uint_value(int value, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeUIntValue;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mIntValue = value;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_uint_value(unsigned int node, sCompileInfo* info)
{
    int value = gNodes[node].uValue.mIntValue;

    LVALUE llvm_value;

    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

    llvm_value.value = LLVMConstInt(llvm_type, value, FALSE);
    llvm_value.type = create_node_type_with_class_name("int");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("int");

    return TRUE;

    return TRUE;
}

unsigned int sNodeTree_create_long_value(long long int value, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLongValue;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mLongValue = value;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_long_value(unsigned long long int node, sCompileInfo* info)
{
    long long int value = gNodes[node].uValue.mLongValue;

    LVALUE llvm_value;

    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("long");

    llvm_value.value = LLVMConstInt(llvm_type, value, TRUE);
    llvm_value.type = create_node_type_with_class_name("long");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("long");

    return TRUE;
}

unsigned int sNodeTree_create_ulong_value(unsigned long long int value, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeULongValue;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.mULongValue = value;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_ulong_value(unsigned long long int node, sCompileInfo* info)
{
    long long int value = gNodes[node].uValue.mLongValue;

    LVALUE llvm_value;

    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("long");

    llvm_value.value = LLVMConstInt(llvm_type, value, FALSE);
    llvm_value.type = create_node_type_with_class_name("long");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("long");

    return TRUE;

    return TRUE;
}

unsigned int sNodeTree_create_add(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAdd;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_add(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    if(left_type->mArrayDimentionNum == 1 && is_number_type(right_type))
    {
        left_type->mArrayDimentionNum = 0;
        left_type->mPointerNum++;

        LLVMTypeRef llvm_left_type = create_llvm_type_from_node_type(left_type);

        LLVMTypeRef long_type = create_llvm_type_with_class_name("long");

        LLVMValueRef left_value = LLVMBuildCast(gBuilder, LLVMBitCast, lvalue.address, llvm_left_type, "bit_cast");
        LLVMValueRef left_value2 = LLVMBuildCast(gBuilder, LLVMPtrToInt, left_value, long_type, "ptr_to_int");

        LLVMValueRef right_value;
        if(type_identify_with_class_name(right_type, "long")) {
            right_value = rvalue.value;
        }
        else {
            if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "ptrToInt");
            }
            else {
                right_value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue.value, long_type, "sext1");
            }
        }

        LLVMTypeRef llvm_var_type = create_llvm_type_from_node_type(left_type);

        sNodeType* left_type3 = clone_node_type(left_type);
        left_type3->mPointerNum--;

        uint64_t alloc_size = get_size_from_node_type(left_type3);

        LLVMValueRef alloc_size_value = LLVMConstInt(long_type, alloc_size, FALSE);

        right_value = LLVMBuildMul(gBuilder, right_value, alloc_size_value, "mul");

        sNodeType* left_type2 = clone_node_type(left_type);
        left_type2->mHeap = FALSE;

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildAdd(gBuilder, left_value2, right_value, "add");
        llvm_value.value = LLVMBuildCast(gBuilder, LLVMIntToPtr, llvm_value.value, llvm_var_type, "intToPtr");
        llvm_value.type = clone_node_type(left_type2);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(left_type2);
    }
    else if(left_type->mPointerNum > 0 && is_number_type(right_type))
    {
        LLVMTypeRef long_type = create_llvm_type_with_class_name("long");

        LLVMValueRef left_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, lvalue.value, long_type, "ptrToInt");

        LLVMValueRef right_value;
        if(type_identify_with_class_name(right_type, "long")) {
            right_value = rvalue.value;
        }
        else {
            if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "ptrToInt");
            }
            else {
                right_value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue.value, long_type, "sext");
            }
        }

        LLVMTypeRef llvm_var_type = create_llvm_type_from_node_type(left_type);

        sNodeType* left_type3 = clone_node_type(left_type);
        left_type3->mPointerNum--;

        uint64_t alloc_size = get_size_from_node_type(left_type3);

        LLVMValueRef alloc_size_value = LLVMConstInt(long_type, alloc_size, FALSE);

        right_value = LLVMBuildMul(gBuilder, right_value, alloc_size_value, "mul");

        sNodeType* left_type2 = clone_node_type(left_type);
        left_type2->mHeap = FALSE;

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildAdd(gBuilder, left_value, right_value, "add");
        llvm_value.value = LLVMBuildCast(gBuilder, LLVMIntToPtr, llvm_value.value, llvm_var_type, "intToPtr");
        llvm_value.type = clone_node_type(left_type2);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(left_type2);
    }
    else {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildAdd(gBuilder, lvalue.value, rvalue.value, "add");
        llvm_value.type = clone_node_type(left_type);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(left_type);
    }

    return TRUE;
}

unsigned int sNodeTree_create_sub(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeSub;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_sub(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    if(!(left_type->mPointerNum > 0 && is_number_type(right_type)))
    {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }
    }

    if(left_type->mArrayDimentionNum == 1 && is_number_type(right_type))
    {
        left_type->mArrayDimentionNum = 0;
        left_type->mPointerNum++;

        LLVMTypeRef llvm_left_type = create_llvm_type_from_node_type(left_type);

        LLVMTypeRef long_type = create_llvm_type_with_class_name("long");

        LLVMValueRef left_value = LLVMBuildCast(gBuilder, LLVMBitCast, lvalue.address, llvm_left_type, "bitcast");
        LLVMValueRef left_value2 = LLVMBuildCast(gBuilder, LLVMPtrToInt, left_value, long_type, "ptrToInt");

        LLVMValueRef right_value;
        if(type_identify_with_class_name(right_type, "long")) {
            right_value = rvalue.value;
        }
        else {
            if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "ptrToInt");
            }
            else {
                right_value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue.value, long_type, "sext");
            }
        }

        LLVMTypeRef llvm_var_type = create_llvm_type_from_node_type(left_type);

        sNodeType* left_type3 = clone_node_type(left_type);
        left_type3->mPointerNum--;

        uint64_t alloc_size = get_size_from_node_type(left_type3);

        LLVMValueRef alloc_size_value = LLVMConstInt(long_type, alloc_size, FALSE);

        right_value = LLVMBuildMul(gBuilder, right_value, alloc_size_value, "mul");

        sNodeType* left_type2 = clone_node_type(left_type);
        left_type2->mHeap = FALSE;

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildSub(gBuilder, left_value, right_value, "sub");
        llvm_value.value = LLVMBuildCast(gBuilder, LLVMIntToPtr, llvm_value.value, llvm_var_type, "intToPtr");
        llvm_value.type = clone_node_type(left_type2);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(left_type2);
    }
    else if((left_type->mPointerNum > 0 || left_type->mArrayDimentionNum == 1) && (right_type->mPointerNum > 0 || right_type->mArrayDimentionNum == 1))
    {
        LLVMTypeRef long_type = create_llvm_type_with_class_name("long");

        LLVMValueRef left_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, lvalue.value, long_type, "ptrToInt");
        LLVMValueRef right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "ptrToInt");

        sNodeType* node_type = create_node_type_with_class_name("long");

        LLVMTypeRef llvm_var_type = create_llvm_type_from_node_type(node_type);

        sNodeType* element_type = clone_node_type(left_type);
        element_type->mPointerNum = 0;
        element_type->mArrayDimentionNum = 0;

        uint64_t element_size = get_size_from_node_type(element_type);

        LLVMValueRef elemet_size_value = LLVMConstInt(long_type, element_size, FALSE);

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildSub(gBuilder, left_value, right_value, "sub");
        llvm_value.value = LLVMBuildSDiv(gBuilder, llvm_value.value, elemet_size_value, "div");
        llvm_value.value = LLVMBuildCast(gBuilder, LLVMBitCast, llvm_value.value, llvm_var_type, "bitcast");
        llvm_value.type = clone_node_type(node_type);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(node_type);
    }
    else if(left_type->mPointerNum > 0 && is_number_type(right_type))
    {
        LLVMTypeRef long_type = create_llvm_type_with_class_name("long");

        LLVMValueRef left_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, lvalue.value, long_type, "ptrToInt");

        LLVMValueRef right_value;
        if(type_identify_with_class_name(right_type, "long")) {
            right_value = rvalue.value;
        }
        else {
            if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "ptrToInt");
            }
            else {
                right_value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue.value, long_type, "sext");
            }
        }

        LLVMTypeRef llvm_var_type = create_llvm_type_from_node_type(left_type);

        sNodeType* left_type3 = clone_node_type(left_type);
        left_type3->mPointerNum--;

        uint64_t alloc_size = get_size_from_node_type(left_type3);

        LLVMValueRef alloc_size_value = LLVMConstInt(long_type, alloc_size, FALSE);

        right_value = LLVMBuildMul(gBuilder, right_value, alloc_size_value, "mul");

        sNodeType* left_type2 = clone_node_type(left_type);
        left_type2->mHeap = FALSE;

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildSub(gBuilder, left_value, right_value, "sub");
        llvm_value.value = LLVMBuildCast(gBuilder, LLVMIntToPtr, llvm_value.value, llvm_var_type, "iintToPtr");
        llvm_value.type = clone_node_type(left_type2);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(left_type2);
    }
    else {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildSub(gBuilder, lvalue.value, rvalue.value, "sub");
        llvm_value.type = clone_node_type(left_type);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(2, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(left_type);
    }

    return TRUE;
}

unsigned int sNodeTree_create_mult(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeMult;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_mult(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildMul(gBuilder, lvalue.value, rvalue.value, "mul");
    llvm_value.type = clone_node_type(left_type);
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = clone_node_type(left_type);

    return TRUE;
}

unsigned int sNodeTree_create_div(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDiv;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_div(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LVALUE llvm_value;
    if(left_type->mUnsigned) {
        llvm_value.value = LLVMBuildUDiv(gBuilder, lvalue.value, rvalue.value, "div");
    }
    else {
        llvm_value.value = LLVMBuildSDiv(gBuilder, lvalue.value, rvalue.value, "div");
    }
    llvm_value.type = clone_node_type(left_type);
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = clone_node_type(left_type);

    return TRUE;
}

unsigned int sNodeTree_create_mod(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeMod;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_mod(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LVALUE llvm_value;
    if(left_type->mUnsigned) {
        llvm_value.value = LLVMBuildURem(gBuilder, lvalue.value, rvalue.value, "div");
    }
    else {
        llvm_value.value = LLVMBuildSRem(gBuilder, lvalue.value, rvalue.value, "div");
    }
    llvm_value.type = clone_node_type(left_type);
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = clone_node_type(left_type);

    return TRUE;
}

unsigned int sNodeTree_create_equals(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeEquals;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_equals(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildICmp(gBuilder, LLVMIntEQ, lvalue.value, rvalue.value, "eq");
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_create_not_equals(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeNotEquals;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_not_equals(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildICmp(gBuilder, LLVMIntNE, lvalue.value, rvalue.value, "not_eq");
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_create_gteq(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeGteq;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_gteq(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LVALUE llvm_value;
    if(left_type->mUnsigned) {
        llvm_value.value = LLVMBuildICmp(gBuilder, LLVMIntUGE, lvalue.value, rvalue.value, "gteq");
    }
    else {
        llvm_value.value = LLVMBuildICmp(gBuilder, LLVMIntSGE, lvalue.value, rvalue.value, "gteq");
    }
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_create_leeq(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLeeq;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_leeq(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LVALUE llvm_value;
    if(left_type->mUnsigned) {
        llvm_value.value = LLVMBuildICmp(gBuilder, LLVMIntULE, lvalue.value, rvalue.value, "leeq");
    }
    else {
        llvm_value.value = LLVMBuildICmp(gBuilder, LLVMIntSLE, lvalue.value, rvalue.value, "leeq");
    }
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_create_gt(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeGt;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_gt(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LVALUE llvm_value;
    if(left_type->mUnsigned) {
        llvm_value.value = LLVMBuildICmp(gBuilder, LLVMIntUGT, lvalue.value, rvalue.value, "gt");
    }
    else {
        llvm_value.value = LLVMBuildICmp(gBuilder, LLVMIntSGT, lvalue.value, rvalue.value, "gt");
    }
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_create_le(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLe;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_le(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LVALUE llvm_value;
    if(left_type->mUnsigned) {
        llvm_value.value = LLVMBuildICmp(gBuilder, LLVMIntULT, lvalue.value, rvalue.value, "leeq");
    }
    else {
        llvm_value.value = LLVMBuildICmp(gBuilder, LLVMIntSLT, lvalue.value, rvalue.value, "leeq");
    }
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_create_logical_denial(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLogicalDenial;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_logical_denial(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, left_type)) {
        if(!cast_right_type_to_left_type(bool_type, &left_type, &lvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    if(!type_identify_with_class_name(left_type, "bool")) {
        compile_err_msg(info, "Left expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("bool");

    LVALUE rvalue;
    rvalue.value = LLVMConstInt(llvm_type, 0, FALSE);
    rvalue.type = NULL;
    rvalue.address = NULL;
    rvalue.var = NULL;
    rvalue.binded_value = FALSE;
    rvalue.load_field = FALSE;

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildICmp(gBuilder, LLVMIntEQ, lvalue.value, rvalue.value, "logical_denial");
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(1, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_create_define_variable(char* var_name, BOOL extern_, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDefineVariable;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sDefineVariable.mVarName, var_name, VAR_NAME_MAX);
    gNodes[node].uValue.sDefineVariable.mGlobal = info->mBlockLevel == 0;
    gNodes[node].uValue.sDefineVariable.mExtern = extern_;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
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

static BOOL compile_define_variable(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX];
    xstrncpy(var_name, gNodes[node].uValue.sStoreVariable.mVarName, VAR_NAME_MAX);
    BOOL global = gNodes[node].uValue.sDefineVariable.mGlobal;
    BOOL extern_ = gNodes[node].uValue.sDefineVariable.mExtern;

    sVar* var = get_variable_from_table(info->pinfo->lv_table, var_name);

    if(var == NULL) {
        compile_err_msg(info, "undeclared variable %s(1)", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    sNodeType* var_type = clone_node_type(var->mType);

    if(info->generics_type) {
        if(!solve_generics(&var_type, info->generics_type)) 
        {
            compile_err_msg(info, "Can't solve generics types(3)");
            show_node_type(var_type);
            show_node_type(info->generics_type);
            info->err_num++;

            return FALSE;
        }
    }

    if(!create_generics_struct_type(var_type)) {
        compile_err_msg(info, "invalid type %s", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    if(is_typeof_type(var_type))
    {
        if(!solve_typeof(&var_type, info))
        {
            compile_err_msg(info, "Can't solve typeof types");
            show_node_type(var_type);
            info->err_num++;

            return TRUE;
        }
    }

    if(info->generics_type) {
        if(!solve_generics(&var_type, info->generics_type)) 
        {
            compile_err_msg(info, "Can't solve generics types(3)");
            show_node_type(var_type);
            show_node_type(info->generics_type);
            info->err_num++;

            return FALSE;
        }
    }

    LLVMTypeRef llvm_type = create_llvm_type_from_node_type(var_type);

#ifdef __X86_64_CPU__
    if(type_identify_with_class_name(var_type, "__builtin_va_list") || type_identify_with_class_name(var_type, "va_list")) {
        llvm_type = LLVMArrayType(llvm_type, 1);
    }
#endif

    if(extern_) {
        LLVMValueRef alloca_value = LLVMAddGlobal(gModule, llvm_type, var_name);

        LLVMSetExternallyInitialized(alloca_value, TRUE);

        var->mLLVMValue = alloca_value;
    }
    else if(global) {
        LLVMValueRef alloca_value = LLVMAddGlobal(gModule, llvm_type, var_name);

        if(var_type->mArrayDimentionNum == 1) {
            /// zero initializer ///
            sNodeType* element_node_type = clone_node_type(var_type);
            element_node_type->mArrayDimentionNum = 0;
            LLVMTypeRef llvm_element_type = create_llvm_type_from_node_type(element_node_type);

            LLVMValueRef values[element_node_type->mArrayNum[0]];

            int i;
            for(i=0; i<element_node_type->mArrayNum[0]; i++) {
                values[i] = LLVMConstInt(llvm_element_type, 0, FALSE);
            }
            
            LLVMValueRef value2 = LLVMConstArray(llvm_element_type, values, element_node_type->mArrayNum[0]);
            LLVMSetInitializer(alloca_value, value2);
        }
        else if(var_type->mArrayDimentionNum == 2) {
            /// zero initializer ///
            sNodeType* element_node_type = clone_node_type(var_type);
            element_node_type->mArrayDimentionNum = 0;
            LLVMTypeRef llvm_element_type = create_llvm_type_from_node_type(element_node_type);

            LLVMValueRef values[element_node_type->mArrayNum[0]*element_node_type->mArrayNum[1]];

            int i;
            for(i=0; i<element_node_type->mArrayNum[0]*element_node_type->mArrayNum[1]; i++) {
                values[i] = LLVMConstInt(llvm_element_type, 0, FALSE);
            }
            
            LLVMValueRef value2 = LLVMConstArray(llvm_element_type, values, element_node_type->mArrayNum[0]*element_node_type->mArrayNum[1]);
            LLVMSetInitializer(alloca_value, value2);
        }
        else if(var_type->mArrayDimentionNum == 3) {
            /// zero initializer ///
            sNodeType* element_node_type = clone_node_type(var_type);
            element_node_type->mArrayDimentionNum = 0;
            LLVMTypeRef llvm_element_type = create_llvm_type_from_node_type(element_node_type);

            LLVMValueRef values[element_node_type->mArrayNum[0]*element_node_type->mArrayNum[1]*element_node_type->mArrayNum[2]];

            int i;
            for(i=0; i<element_node_type->mArrayNum[0]*element_node_type->mArrayNum[1]*element_node_type->mArrayNum[2]; i++) {
                values[i] = LLVMConstInt(llvm_element_type, 0, FALSE);
            }
            
            LLVMValueRef value2 = LLVMConstArray(llvm_element_type, values, element_node_type->mArrayNum[0]*element_node_type->mArrayNum[1]*element_node_type->mArrayNum[2]);
            LLVMSetInitializer(alloca_value, value2);
        }
        else if(((var_type->mClass->mFlags & CLASS_FLAGS_STRUCT) || (var_type->mClass->mFlags & CLASS_FLAGS_UNION)) && var_type->mPointerNum == 0) {
            /// zero initializer ///
            LLVMValueRef value = LLVMConstInt(llvm_type, 0, FALSE);
            LLVMValueRef value2 = LLVMConstStruct(&value, 0, FALSE);
            LLVMSetInitializer(alloca_value, value2);
        }
        else {
            LLVMValueRef value = LLVMConstInt(llvm_type, 0, FALSE);
            LLVMSetInitializer(alloca_value, value);
        }

        var->mLLVMValue = alloca_value;
    }
    else {
        if(var_type->mDynamicArrayNum != 0) {
            if(!compile(var_type->mDynamicArrayNum, info)) {
                return FALSE;
            }

            LVALUE llvm_value = *get_value_from_stack(-1);
            dec_stack_ptr(1, info);

            LLVMValueRef len_value = llvm_value.value;

            LLVMValueRef alloca_value = LLVMBuildArrayAlloca(gBuilder, llvm_type, len_value, var_name);
            var->mLLVMValue = alloca_value;
        }
        else {
            LLVMValueRef alloca_value = LLVMBuildAlloca(gBuilder, llvm_type, var_name);
            var->mLLVMValue = alloca_value;
        }
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_create_store_variable(char* var_name, int right, BOOL alloc, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreVariable;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sStoreVariable.mVarName, var_name, VAR_NAME_MAX);
    gNodes[node].uValue.sStoreVariable.mAlloc = alloc;
    gNodes[node].uValue.sStoreVariable.mGlobal = info->mBlockLevel == 0;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}


static BOOL compile_store_variable(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX];
    xstrncpy(var_name, gNodes[node].uValue.sStoreVariable.mVarName, VAR_NAME_MAX);
    BOOL alloc = gNodes[node].uValue.sStoreVariable.mAlloc;
    BOOL global = gNodes[node].uValue.sStoreVariable.mGlobal;

    unsigned int right_node = gNodes[node].mRight;

    sVar* var = get_variable_from_table(info->pinfo->lv_table, var_name);

    if(var == NULL) {
        compile_err_msg(info, "undeclared variable %s(2)", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    BOOL static_ = var->mType->mStatic;

    sNodeType* left_type = clone_node_type(var->mType);

    if(info->generics_type) {
        if(!solve_generics(&left_type, info->generics_type)) 
        {
            compile_err_msg(info, "Can't solve generics types(3)");
            show_node_type(left_type);
            show_node_type(info->generics_type);
            info->err_num++;

            return FALSE;
        }
    }

    if(!create_generics_struct_type(left_type)) {
        compile_err_msg(info, "invalid type %s", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    if(is_typeof_type(left_type))
    {
        if(!solve_typeof(&left_type, info))
        {
            compile_err_msg(info, "Can't solve typeof types");
            show_node_type(left_type);
            info->err_num++;

            return TRUE;
        }
    }

    if(info->generics_type) {
        if(!solve_generics(&left_type, info->generics_type)) 
        {
            compile_err_msg(info, "Can't solve generics types(3)");
            show_node_type(left_type);
            show_node_type(info->generics_type);
            info->err_num++;

            return FALSE;
        }
    }

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    BOOL constant = var->mConstant;

    if(alloc) {
        if(global) {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

#ifdef __X86_64_CPU__
            if(type_identify_with_class_name(left_type, "__builtin_va_list") || type_identify_with_class_name(left_type, "va_list")) {
                llvm_type = LLVMArrayType(llvm_type, 1);
            }
#endif

            LLVMValueRef alloca_value = LLVMAddGlobal(gModule, llvm_type, var_name);

            if(((left_type->mClass->mFlags & CLASS_FLAGS_STRUCT) || (left_type->mClass->mFlags & CLASS_FLAGS_UNION)) && left_type->mPointerNum == 0) {
                LLVMValueRef value = LLVMConstInt(llvm_type, 0, FALSE);
                LLVMValueRef value2 = LLVMConstStruct(&value, 0, FALSE);
                LLVMSetInitializer(alloca_value, value2);
            }
            else {
                LLVMSetInitializer(alloca_value, rvalue.value);
            }

            var->mLLVMValue = alloca_value;

            info->type = left_type;

            if(left_type->mHeap) {
                remove_object_from_right_values(rvalue.value);
            }
        }
        else if(static_) {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

            char static_var_name[VAR_NAME_MAX*2];
            snprintf(static_var_name, VAR_NAME_MAX*2, "%s_%s", info->fun_name, var_name);

            if(var->mLLVMValue == NULL)
            {
                LLVMValueRef alloca_value = LLVMAddGlobal(gModule, llvm_type, static_var_name);

                if(((left_type->mClass->mFlags & CLASS_FLAGS_STRUCT) || (left_type->mClass->mFlags & CLASS_FLAGS_UNION)) && left_type->mPointerNum == 0) {
                    LLVMValueRef value = LLVMConstInt(llvm_type, 0, FALSE);
                    LLVMValueRef value2 = LLVMConstStruct(&value, 0, FALSE);
                    LLVMSetInitializer(alloca_value, value2);
                }
                else {
                    LLVMSetInitializer(alloca_value, rvalue.value);
                }

                var->mLLVMValue = alloca_value;

                info->type = left_type;

                if(left_type->mHeap) {
                    remove_object_from_right_values(rvalue.value);
                }
            }
        }
        else if(constant) {
            var->mLLVMValue = rvalue.value;

            info->type = left_type;

            if(left_type->mHeap) {
                remove_object_from_right_values(rvalue.value);
            }
        }
        else {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

#ifdef __X86_64_CPU__
            if(type_identify_with_class_name(left_type, "__builtin_va_list") || type_identify_with_class_name(left_type, "va_list")) {
                llvm_type = LLVMArrayType(llvm_type, 1);
            }
#endif

            LLVMValueRef alloca_value = LLVMBuildAlloca(gBuilder, llvm_type, var_name);

            LLVMBuildStore(gBuilder, rvalue.value, alloca_value);

            var->mLLVMValue = alloca_value;

            info->type = left_type;

            if(left_type->mHeap) {
                remove_object_from_right_values(rvalue.value);
            }
        }
    }
    else if(constant) {
        var->mLLVMValue = rvalue.value;

        info->type = left_type;
    }
    else {
        LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

#ifdef __X86_64_CPU__
        if(type_identify_with_class_name(left_type, "__builtin_va_list") || type_identify_with_class_name(left_type, "va_list")) {
            llvm_type = LLVMArrayType(llvm_type, 1);
        }
#endif

        LLVMValueRef alloca_value = var->mLLVMValue;

        LLVMBuildStore(gBuilder, rvalue.value, alloca_value);

        info->type = left_type;
    }

    return TRUE;
}

unsigned int sNodeTree_create_c_string_value(MANAGED char* value, int len, int sline, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCString;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].uValue.sString.mString = MANAGED value;

    return node;
}

BOOL compile_c_string_value(unsigned int node, sCompileInfo* info)
{
    char* buf = gNodes[node].uValue.sString.mString;

    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("char*");

    LLVMValueRef value = LLVMBuildPointerCast(gBuilder, LLVMBuildGlobalString(gBuilder, buf, buf), llvm_type, "str");

    LVALUE llvm_value;
    llvm_value.value = value;
    llvm_value.type = create_node_type_with_class_name("char*");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("char*");

    return TRUE;
}

unsigned int sNodeTree_create_external_function(char* fun_name, char* asm_fname, sParserParam* params, int num_params, BOOL var_arg, sNodeType* result_type, char* struct_name, BOOL operator_fun, int version, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeExternalFunction;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    xstrncpy(gNodes[node].uValue.sFunction.mName, fun_name, VAR_NAME_MAX);
    xstrncpy(gNodes[node].uValue.sFunction.mAsmName, asm_fname, VAR_NAME_MAX);

    int i;
    for(i=0; i<num_params; i++) {
        gNodes[node].uValue.sFunction.mParams[i] = params[i]; // copy struct
        gNodes[node].uValue.sFunction.mParams[i].mType = clone_node_type(params[i].mType);

    }

    gNodes[node].uValue.sFunction.mNumParams = num_params;
    gNodes[node].uValue.sFunction.mResultType = clone_node_type(result_type);
    gNodes[node].uValue.sFunction.mVarArg = var_arg;
    gNodes[node].uValue.sFunction.mOperatorFun = operator_fun;
    gNodes[node].uValue.sFunction.mInCLang = info->in_clang;
    gNodes[node].uValue.sFunction.mVersion = version;

    if(struct_name && strcmp(struct_name, "") != 0) {
        xstrncpy(gNodes[node].uValue.sFunction.mStructName, struct_name, VAR_NAME_MAX);
    }
    else {
        xstrncpy(gNodes[node].uValue.sFunction.mStructName, "", VAR_NAME_MAX);
    }

    return node;
}


static BOOL compile_external_function(unsigned int node, sCompileInfo* info)
{
    /// rename variables ///
    char fun_name[VAR_NAME_MAX];
    xstrncpy(fun_name, gNodes[node].uValue.sFunction.mName, VAR_NAME_MAX);

    char asm_fun_name[VAR_NAME_MAX];
    xstrncpy(asm_fun_name, gNodes[node].uValue.sFunction.mAsmName, VAR_NAME_MAX);

    int num_params = gNodes[node].uValue.sFunction.mNumParams;

    sParserParam params[PARAMS_MAX];
    memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);

    int i;
    for(i=0; i<num_params; i++) {
        params[i] = gNodes[node].uValue.sFunction.mParams[i];
    }

    sNodeType* result_type = gNodes[node].uValue.sFunction.mResultType;
    BOOL var_arg = gNodes[node].uValue.sFunction.mVarArg;
    char* struct_name = gNodes[node].uValue.sFunction.mStructName;
    BOOL operator_fun = gNodes[node].uValue.sFunction.mOperatorFun;
    int version = gNodes[node].uValue.sFunction.mVersion;

    /// go ///
    sNodeType* param_types[PARAMS_MAX];
    char param_names[PARAMS_MAX][VAR_NAME_MAX];

    for(i=0; i<num_params; i++) {
        sNodeType* param_type = params[i].mType;

        if(!create_generics_struct_type(param_type)) {
            compile_err_msg(info, "invalid type %s", param_names[i]);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }

        xstrncpy(param_names[i], params[i].mName, VAR_NAME_MAX);
        param_types[i] = param_type;
    }

    // puts function
    LLVMTypeRef llvm_param_types[PARAMS_MAX];

    for(i=0; i<num_params; i++) {
        if(type_identify_with_class_name(param_types[i], "__builtin_va_list") || type_identify_with_class_name(param_types[i], "va_list")) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
            llvm_param_types[i] = LLVMPointerType(llvm_param_types[i], 0);
        }
        else {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }
    }

    LLVMTypeRef llvm_result_type;

    llvm_result_type = create_llvm_type_from_node_type(result_type);

    LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
    LLVMValueRef llvm_fun = LLVMAddFunction(gModule, fun_name, function_type);

    char* block_text = NULL;

    char* param_names2[PARAMS_MAX];
    for(i=0; i<PARAMS_MAX; i++) {
        param_names2[i] = param_names[i];
    }

    BOOL generics_function = FALSE;
    if(!add_function_to_table(fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, 0, NULL)) {
        fprintf(stderr, "overflow function table\n");
        return FALSE;
    }

    return TRUE;
}

unsigned int sNodeTree_create_function_call(char* fun_name, unsigned int* params, int num_params, BOOL method, BOOL inherit, int version, sParserInfo* info)
{
    unsigned int node = alloc_node();

/*
    if(strcmp(fun_name, "memset") == 0) {
        params[num_params] = sNodeTree_create_false(info);
        num_params++;
    }
*/
    if(strcmp(fun_name, "__builtin___strcpy_chk") == 0) {
        xstrncpy(fun_name, "strcpy", VAR_NAME_MAX);
        num_params--;
    }

    xstrncpy(gNodes[node].uValue.sFunctionCall.mName, fun_name, VAR_NAME_MAX);
    gNodes[node].uValue.sFunctionCall.mNumParams = num_params;

    int i;
    for(i=0; i<num_params; i++) {
        gNodes[node].uValue.sFunctionCall.mParams[i] = params[i];
    }

    gNodes[node].uValue.sFunctionCall.mMethod = method;
    gNodes[node].uValue.sFunctionCall.mInherit = inherit;
    
    gNodes[node].mNodeType = kNodeTypeFunctionCall;

    gNodes[node].uValue.sFunctionCall.mNumGenerics = info->mNumGenerics;
    for(i=0; i<info->mNumGenerics; i++)
    {
        xstrncpy(gNodes[node].uValue.sFunctionCall.mGenericsTypeNames[i], info->mGenericsTypeNames[i], VAR_NAME_MAX);
    }
    gNodes[node].uValue.sFunctionCall.mVersion = version;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sFunctionCall.mImplStructName, info->impl_struct_name, VAR_NAME_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

void llvm_change_block(LLVMBasicBlockRef current_block, sCompileInfo* info)
{
    LLVMPositionBuilderAtEnd(gBuilder, current_block);
    info->current_block = current_block;
}

void create_generics_fun_name(char* real_fun_name, int size_real_fun_name, char* fun_name,  sNodeType* generics_type)
{
    xstrncpy(real_fun_name, "", size_real_fun_name);

    xstrncat(real_fun_name, fun_name, size_real_fun_name);

    int i;
    if(generics_type->mNumGenericsTypes > 0) {
        xstrncat(real_fun_name, "_", size_real_fun_name);
    }

    for(i=0; i<generics_type->mNumGenericsTypes; i++)
    {
        sNodeType* node_type = generics_type->mGenericsTypes[i];

        sCLClass* klass = node_type->mClass;
        xstrncat(real_fun_name, CLASS_NAME(klass), size_real_fun_name);

        int j;
        for(j=0; j<node_type->mPointerNum; j++) 
        {
            xstrncat(real_fun_name, "p", size_real_fun_name);
        }

        if(i != generics_type->mNumGenericsTypes-1) {
            xstrncat(real_fun_name, "_", size_real_fun_name);
        }
    }
}


BOOL compile_function_call(unsigned int node, sCompileInfo* info)
{
    /// rename variables ///
    char fun_name[VAR_NAME_MAX];
    xstrncpy(fun_name, gNodes[node].uValue.sFunctionCall.mName, VAR_NAME_MAX);
    int num_params = gNodes[node].uValue.sFunctionCall.mNumParams;
    unsigned int params[PARAMS_MAX];
    BOOL method = gNodes[node].uValue.sFunctionCall.mMethod;
    BOOL inherit = gNodes[node].uValue.sFunctionCall.mInherit;
    int version = gNodes[node].uValue.sFunctionCall.mVersion;

    int num_generics = gNodes[node].uValue.sFunctionCall.mNumGenerics;
    char generics_type_names[GENERICS_TYPES_MAX][VAR_NAME_MAX];

    int i;
    for(i=0; i<num_generics; i++)
    {
        xstrncpy(generics_type_names[i], gNodes[node].uValue.sFunctionCall.mGenericsTypeNames[i], VAR_NAME_MAX);
    }

    if(strcmp(fun_name, "__builtin_va_start") == 0 || strcmp(fun_name, "va_start") == 0) {
        xstrncpy(fun_name, "llvm.va_start", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_va_end") == 0 || strcmp(fun_name, "va_end") == 0) {
        xstrncpy(fun_name, "llvm.va_end", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_memmove") == 0) {
        xstrncpy(fun_name, "llvm.memmove.p0i8.p0i8.i64", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_memcpy") == 0) {
        xstrncpy(fun_name, "llvm.memcpy.p0i8.p0i8.i64", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_memset") == 0) {
        xstrncpy(fun_name, "llvm.memset.p0i8.i64", VAR_NAME_MAX);
    }

    /// go ///
    sNodeType* param_types[PARAMS_MAX];
    memset(param_types, 0, sizeof(sNodeType*)*PARAMS_MAX);

    char param_names[PARAMS_MAX][VAR_NAME_MAX];
    memset(param_names, 0 , sizeof(char)*PARAMS_MAX*VAR_NAME_MAX);

    /// compile parametors ///
    LLVMValueRef llvm_params[PARAMS_MAX];
    memset(llvm_params, 0, sizeof(LLVMValueRef)*PARAMS_MAX);

    sNodeType* generics_type = NULL;

    char struct_name[VAR_NAME_MAX];

    if(method) {
        params[0] = gNodes[node].uValue.sFunctionCall.mParams[0];

        if(!compile(params[0], info)) {
            return FALSE;
        }

        param_types[0] = clone_node_type(info->type);
        LVALUE param = *get_value_from_stack(-1);

        generics_type = clone_node_type(info->type);

        llvm_params[0] = param.value;

        xstrncpy(struct_name, CLASS_NAME(param_types[0]->mClass), VAR_NAME_MAX);

        char method_name[VAR_NAME_MAX];
        snprintf(method_name, VAR_NAME_MAX, "%s_%s", struct_name, fun_name);

        xstrncpy(fun_name, method_name, VAR_NAME_MAX);
    }

    sNodeType* generics_type_before = info->generics_type;
    info->generics_type = generics_type;

    if(info->generics_type) {
        if(!solve_generics(&generics_type, generics_type_before))
        {
            compile_err_msg(info, "Can't solve generics types(3)");
            show_node_type(generics_type);
            show_node_type(info->generics_type);
            info->err_num++;

            return FALSE;
        }
    }

    sFunction* fun = get_function_from_table(fun_name);

    if(fun == NULL) {
        fprintf(stderr, "function not found(%s)\n", fun_name);
        return FALSE;
    }

    if(method) {
        xstrncpy(param_names[0], fun->mParamNames[0], VAR_NAME_MAX);
    }

    for(i=method?1:0; i<num_params; i++) {
        params[i] = gNodes[node].uValue.sFunctionCall.mParams[i];
        
        if(!compile(params[i], info)) {
            return FALSE;
        }

        param_types[i] = clone_node_type(info->type);
        xstrncpy(param_names[i], fun->mParamNames[i], VAR_NAME_MAX);

        LVALUE param = *get_value_from_stack(-1);

        if(fun->mParamTypes[i]) {
            if(auto_cast_posibility(fun->mParamTypes[i], param_types[i])) {
                if(!cast_right_type_to_left_type(fun->mParamTypes[i], &param_types[i], &param, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }
        }

        llvm_params[i] = param.value;
    }

    if(strcmp(fun_name, "llvm.va_start") == 0 || strcmp(fun_name, "llvm.va_end") == 0)
    {
        LLVMValueRef param = llvm_params[0];

        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("char*");
        param = LLVMBuildCast(gBuilder, LLVMBitCast, param, llvm_type, "cast");

        llvm_params[0] = param;
        num_params = 1;
    }

    sNodeType* result_type = clone_node_type(fun->mResultType);

    /// call generics function ///
    if(fun->mGenericsFunction) {
        char real_fun_name[REAL_FUN_NAME_MAX];
        create_generics_fun_name(real_fun_name, REAL_FUN_NAME_MAX, fun_name,  generics_type);
        
        LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, real_fun_name);

        if(llvm_fun == NULL) {
            LLVMBasicBlockRef current_block = LLVMGetLastBasicBlock(gFunction);

            char* buf = fun->mBlockText;
            BOOL var_args = fun->mVarArgs;

            /// params ///
            sParserParam params[PARAMS_MAX];
            memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);

            int num_params = fun->mNumParams;
            int i;
            for(i=0; i<num_params; i++) {
                sParserParam* param = params + i;

                xstrncpy(param->mName, fun->mParamNames[i], VAR_NAME_MAX);

                param->mType = clone_node_type(fun->mParamTypes[i]);

                if(is_typeof_type(param->mType))
                {
                    if(!solve_typeof(&param->mType, info)) 
                    {
                        compile_err_msg(info, "Can't solve typeof types");
                        show_node_type(param->mType);
                        info->err_num++;

                        return TRUE;
                    }
                }

                if(!solve_generics(&param->mType, generics_type)) 
                {
                    compile_err_msg(info, "Can't solve generics types(3)");
                    show_node_type(param->mType);
                    show_node_type(generics_type);
                    info->err_num++;

                    return FALSE;
                }
            }

            sParserInfo info2;

            memset(&info2, 0, sizeof(sParserInfo));

            sBuf_init(&info2.mConst);

            info2.p = buf;
            xstrncpy(info2.sname, info->sname, PATH_MAX);
            info2.source = buf;
            info2.module_name = info->pinfo->module_name;
            info2.lv_table = init_block_vtable(NULL, FALSE);

            info2.mGenericsType = clone_node_type(generics_type);

            info2.mNumGenerics = fun->mNumGenerics;
            for(i=0; i<fun->mNumGenerics; i++) {
                info2.mGenericsTypeNames[i] = strdup(fun->mGenericsTypeNames[i]);
            }

            sNodeType* result_type = clone_node_type(fun->mResultType);

            result_type->mStatic = TRUE;

            if(is_typeof_type(result_type))
            {
                if(!solve_typeof(&result_type, info)) 
                {
                    compile_err_msg(info, "Can't solve typeof types");
                    show_node_type(result_type);
                    info->err_num++;

                    return TRUE;
                }
            }

            if(!solve_generics(&result_type, generics_type))
            {
                compile_err_msg(info, "Can't solve generics types(4))");
                show_node_type(result_type);
                show_node_type(generics_type);
                info->err_num++;

                return FALSE;
            }

            xstrncpy(info2.fun_name, fun->mName, VAR_NAME_MAX);

            sNodeBlock* node_block = ALLOC sNodeBlock_alloc();
            expect_next_character_with_one_forward("{", &info2);
            sVarTable* old_table = info2.lv_table;

            info2.lv_table = init_block_vtable(old_table, FALSE);
            sVarTable* block_var_table = info2.lv_table;
            for(i=0; i<num_params; i++) {
                sParserParam param = params[i];

                BOOL readonly = FALSE;
                if(!add_variable_to_table(info2.lv_table, param.mName, param.mType, readonly, NULL, -1, FALSE, param.mType->mConstant))
                {
                    compile_err_msg(info, "overflow variable table");
                    return FALSE;
                }
            }

            info2.sline = info->pinfo->sline;
            if(!parse_block(node_block, FALSE, FALSE, &info2)) {
                sNodeBlock_free(node_block);
                return FALSE;
            }

            if(info2.err_num > 0) {
                fprintf(stderr, "Parser error number is %d. ", info2.err_num);
                return FALSE;
            }

            expect_next_character_with_one_forward("}", &info2);
            info2.lv_table = old_table;

            BOOL lambda = FALSE;
            BOOL simple_lambda_param = FALSE;
            BOOL constructor_fun = FALSE;
            BOOL operator_fun = FALSE;
            BOOL generics_function = FALSE;
            int version = 0;
            BOOL finalize = FALSE;
            int generics_fun_num = 0;
            char* struct_name = NULL;

            unsigned int node = sNodeTree_create_function(real_fun_name, real_fun_name, params, num_params, result_type, MANAGED node_block, lambda, block_var_table, struct_name, operator_fun, constructor_fun, simple_lambda_param, &info2, generics_function, var_args, version, finalize, generics_fun_num, fun->mName);

            sCompileInfo cinfo;

            memset(&cinfo, 0, sizeof(sCompileInfo));

            cinfo.no_output = FALSE;
            cinfo.pinfo = info->pinfo;
            cinfo.sline = info->sline;
            xstrncpy(cinfo.sname, info->sname, PATH_MAX);
            cinfo.generics_type = clone_node_type(info->generics_type);

            if(!compile(node, &cinfo)) {
                return FALSE;
            }

            LLVMPositionBuilderAtEnd(gBuilder, current_block);

            llvm_fun = LLVMGetNamedFunction(gModule, real_fun_name);
        }


        if(type_identify_with_class_name(result_type, "void") && result_type->mPointerNum == 0) {
            LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "");

            dec_stack_ptr(num_params, info);

            info->type = create_node_type_with_class_name("void");
        }
        else {
            LVALUE llvm_value;
            llvm_value.value = LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "fun_result");
            llvm_value.type = clone_node_type(result_type);
            llvm_value.address = NULL;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            dec_stack_ptr(num_params, info);
            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(result_type);

            if(result_type->mHeap) {
                append_object_to_right_values(llvm_value.value, result_type, info);
            }
        }

    }
    /// call inline function ///
    else if(fun->mBlockText) {
        int sline = gNodes[node].mLine;

        sParserInfo info2;
        memset(&info2, 0, sizeof(sParserInfo));

        sBuf_init(&info2.mConst);

        info2.p = fun->mBlockText;
        xstrncpy(info2.sname, gFName, PATH_MAX);
        info2.source = fun->mBlockText;
        info2.module_name = info->pinfo->module_name;
        info2.sline = sline;
        info2.parse_phase = info->pinfo->parse_phase;
        info2.lv_table = info->pinfo->lv_table;
        info2.in_clang = info->pinfo->in_clang;

        sNodeBlock* node_block = ALLOC sNodeBlock_alloc();
        expect_next_character_with_one_forward("{", &info2);
        sVarTable* old_table = info2.lv_table;

        info2.lv_table = init_block_vtable(old_table, FALSE);
        sVarTable* block_var_table = info2.lv_table;

        for(i=0; i<num_params; i++) {
            BOOL readonly = FALSE;
            if(!add_variable_to_table(info2.lv_table, param_names[i], param_types[i], readonly, NULL, -1, FALSE, param_types[i]->mConstant))
            {
                compile_err_msg(info, "overflow variable table");
                return FALSE;
            }
        }

        if(!parse_block(node_block, FALSE, FALSE, &info2)) {
            return FALSE;
        }

        if(info2.err_num > 0) {
            fprintf(stderr, "Parser error number is %d. ", info2.err_num);
            return FALSE;
        }

        expect_next_character_with_one_forward("}", &info2);
        info2.lv_table = old_table;

        LLVMBasicBlockRef inline_func_begin = LLVMAppendBasicBlockInContext(gContext, gFunction, fun_name);

        LLVMBuildBr(gBuilder, inline_func_begin);

        LLVMPositionBuilderAtEnd(gBuilder, inline_func_begin);

        llvm_change_block(inline_func_begin, info);

        LLVMValueRef inline_result_variable = info->inline_result_variable;
        info->inline_result_variable = NULL;
        if(!type_identify_with_class_name(result_type, "void"))
        {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(result_type);
            info->inline_result_variable = LLVMBuildAlloca(gBuilder, llvm_type, "inline_result_variable");
        }

        for(i=0; i<num_params; i++) {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(param_types[i]);
            LLVMValueRef param = LLVMBuildAlloca(gBuilder, llvm_type, param_names[i]);

            sVar* var = get_variable_from_table(block_var_table, param_names[i]);

            LLVMBuildStore(gBuilder, llvm_params[i], param);

            if(param_types[i]->mHeap) {
                remove_object_from_right_values(llvm_params[i]);
            }

            var->mLLVMValue = param;
        }

        BOOL in_inline_function = info->in_inline_function;
        info->in_inline_function = TRUE;

        if(!compile_block(node_block, info, result_type)) {
            return FALSE;
        }

        info->in_inline_function = in_inline_function;

        LLVMBasicBlockRef inline_func_end = LLVMAppendBasicBlockInContext(gContext, gFunction, "inline_func_end");

        LLVMBuildBr(gBuilder, inline_func_end);
        llvm_change_block(inline_func_end, info);

        if(type_identify_with_class_name(result_type, "void") && result_type->mPointerNum == 0) {
            dec_stack_ptr(num_params, info);

            info->type = create_node_type_with_class_name("void");
        }
        else {
            LVALUE llvm_value;
            llvm_value.value = LLVMBuildLoad(gBuilder, info->inline_result_variable, "inline_result_variable");
            llvm_value.type = result_type;
            llvm_value.address = info->inline_result_variable;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            dec_stack_ptr(num_params, info);
            push_value_to_stack_ptr(&llvm_value, info);

            if(result_type->mHeap) {
                append_object_to_right_values(llvm_value.value, result_type, info);
            }
        }

        info->type = clone_node_type(result_type);

        info->inline_result_variable = inline_result_variable;
    }
    /// call normal function ///
    else {
        LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, fun_name);

        if(type_identify_with_class_name(result_type, "void") && result_type->mPointerNum == 0) {
            LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "");

            dec_stack_ptr(num_params, info);

            info->type = create_node_type_with_class_name("void");
        }
        else {
            LVALUE llvm_value;
            llvm_value.value = LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "fun_result");
            llvm_value.type = clone_node_type(result_type);
            llvm_value.address = NULL;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            dec_stack_ptr(num_params, info);
            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(result_type);

            if(result_type->mHeap) {
                append_object_to_right_values(llvm_value.value, result_type, info);
            }
        }
    }

    info->generics_type = generics_type_before;

    return TRUE;
}

unsigned int sNodeTree_create_function(char* fun_name, char* asm_fname, sParserParam* params, int num_params, sNodeType* result_type, MANAGED struct sNodeBlockStruct* node_block, BOOL lambda, sVarTable* block_var_table, char* struct_name, BOOL operator_fun, BOOL constructor_fun, BOOL simple_lambda_param, sParserInfo* info, BOOL generics_function, BOOL var_arg, int version, BOOL finalize, int generics_fun_num, char* simple_fun_name)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFunction;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    xstrncpy(gNodes[node].uValue.sFunction.mName, fun_name, VAR_NAME_MAX);
    xstrncpy(gNodes[node].uValue.sFunction.mAsmName, asm_fname, VAR_NAME_MAX);
    xstrncpy(gNodes[node].uValue.sFunction.mSimpleName, simple_fun_name, VAR_NAME_MAX);

    int i;
    for(i=0; i<num_params; i++) {
        gNodes[node].uValue.sFunction.mParams[i] = params[i]; // copy struct
        gNodes[node].uValue.sFunction.mParams[i].mType = clone_node_type(params[i].mType);
    }

    gNodes[node].uValue.sFunction.mNumParams = num_params;
    gNodes[node].uValue.sFunction.mResultType = clone_node_type(result_type);
    gNodes[node].uValue.sFunction.mNodeBlock = MANAGED node_block;
    gNodes[node].uValue.sFunction.mLambda = lambda;
    gNodes[node].uValue.sFunction.mVarTable = block_var_table;
    gNodes[node].uValue.sFunction.mVarArg = var_arg;
    gNodes[node].uValue.sFunction.mInCLang = info->in_clang;
    gNodes[node].uValue.sFunction.mVersion = version;
    gNodes[node].uValue.sFunction.mFinalize = finalize;
    gNodes[node].uValue.sFunction.mGenericsFunNum = generics_fun_num;

    if(struct_name && strcmp(struct_name, "") != 0) {
        xstrncpy(gNodes[node].uValue.sFunction.mStructName, struct_name, VAR_NAME_MAX);
    }
    else {
        xstrncpy(gNodes[node].uValue.sFunction.mStructName, "", VAR_NAME_MAX);
    }

    gNodes[node].uValue.sFunction.mOperatorFun = operator_fun;
    gNodes[node].uValue.sFunction.mSimpleLambdaParam = simple_lambda_param;
    gNodes[node].uValue.sFunction.mGenericsFunction = generics_function; gNodes[node].uValue.sFunction.mConstructorFun = constructor_fun;

    return node;
}

BOOL compile_function(unsigned int node, sCompileInfo* info)
{
    /// get result type ///
    sNodeType* result_type = gNodes[node].uValue.sFunction.mResultType;

    char fun_name[VAR_NAME_MAX];
    xstrncpy(fun_name, gNodes[node].uValue.sFunction.mName, VAR_NAME_MAX);

    xstrncpy(info->fun_name, fun_name, VAR_NAME_MAX);

    char asm_fun_name[VAR_NAME_MAX];
    xstrncpy(asm_fun_name, gNodes[node].uValue.sFunction.mAsmName, VAR_NAME_MAX);

    char simple_fun_name[VAR_NAME_MAX];
    xstrncpy(simple_fun_name, gNodes[node].uValue.sFunction.mSimpleName, VAR_NAME_MAX);

    BOOL var_arg = gNodes[node].uValue.sFunction.mVarArg;
    int version = gNodes[node].uValue.sFunction.mVersion;
    int generics_fun_num = gNodes[node].uValue.sFunction.mGenericsFunNum;

    /// rename variables ///
    int num_params = gNodes[node].uValue.sFunction.mNumParams;
    BOOL lambda = gNodes[node].uValue.sFunction.mLambda;
    sVarTable* block_var_table = gNodes[node].uValue.sFunction.mVarTable;

    BOOL finalize = gNodes[node].uValue.sFunction.mFinalize;

    sNodeBlock* node_block = gNodes[node].uValue.sFunction.mNodeBlock;
    char* struct_name = gNodes[node].uValue.sFunction.mStructName;

    sParserParam params[PARAMS_MAX];
    memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);

    int i;
    for(i=0; i<num_params; i++) {
        params[i] = gNodes[node].uValue.sFunction.mParams[i];
    }

    sNodeBlock* function_node_block = info->function_node_block;
    info->function_node_block = node_block;

    sNodeType* param_types[PARAMS_MAX];
    LLVMTypeRef llvm_param_types[PARAMS_MAX];
    char param_names[PARAMS_MAX][VAR_NAME_MAX];
    for(i=0; i<num_params; i++) {
        param_types[i] = params[i].mType;

        if(!create_generics_struct_type(param_types[i])) {
            compile_err_msg(info, "invalid type %s", param_names[i]);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }

        llvm_param_types[i] = create_llvm_type_from_node_type(params[i].mType);

        if(type_identify_with_class_name(param_types[i], "__builtin_va_list") || type_identify_with_class_name(param_types[i], "va_list")) {
            llvm_param_types[i] = LLVMPointerType(llvm_param_types[i], 0);
        }

        xstrncpy(param_names[i], params[i].mName, VAR_NAME_MAX);
    }

    LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);
    LLVMTypeRef  llvm_fun_type;
    if(num_params == 0) {
        llvm_fun_type = LLVMFunctionType(llvm_result_type, NULL, 0, var_arg);
    }
    else {
        llvm_fun_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
    }
    LLVMValueRef llvm_fun = LLVMAddFunction(gModule, fun_name, llvm_fun_type);
    BOOL static_ = result_type->mStatic;
    if(static_) {
        LLVMSetLinkage(llvm_fun, LLVMInternalLinkage);
    }

    LLVMValueRef function = gFunction;
    gFunction = llvm_fun;

    LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(gContext, llvm_fun, "entry");
    LLVMPositionBuilderAtEnd(gBuilder, entry);

    for(i=0; i<num_params; i++) {
        LLVMValueRef llvm_value = LLVMGetParam(llvm_fun, i);

        char* name = params[i].mName;
        sNodeType* type_ = params[i].mType;

        LLVMSetValueName2(llvm_value, name, strlen(name));

        sVar* var = get_variable_from_table(block_var_table, name);

        var->mLLVMValue = llvm_value;
        var->mConstant = TRUE;
    }

    char* block_text = NULL;

    char* param_names2[PARAMS_MAX];
    for(i=0; i<PARAMS_MAX; i++) {
        param_names2[i] = param_names[i];
    }

    BOOL generics_function = FALSE;
    if(!add_function_to_table(fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, 0, NULL)) {
        fprintf(stderr, "overflow function table\n");
        info->function_node_block = function_node_block;
        return FALSE;
    }

    sFunction* fun = get_function_from_table(fun_name);

    if(gNCDebug) {
        int sline = gNodes[node].mLine;
        createDebugFunctionInfo(sline, fun_name, fun, llvm_fun, gFName, info);
    }

    if(!compile_block(node_block, info, result_type)) {
        info->function_node_block = function_node_block;
        return FALSE;
    }

    if(gNCDebug) {
        finishDebugFunctionInfo();
    }

    if(type_identify_with_class_name(result_type, "void")) {
        LLVMBuildRet(gBuilder, NULL);
    }
    else {
        if(!info->last_expression_is_return) {
            LVALUE llvm_value;

            sNodeType* node_type = create_node_type_with_class_name("int");

            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type);

            int value = 0;
            llvm_value.value = LLVMConstInt(llvm_type, value, FALSE);
            llvm_value.type = create_node_type_with_class_name("int");
            llvm_value.address = NULL;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            if(!cast_right_type_to_left_type(result_type, &node_type, &llvm_value, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            LLVMBuildRet(gBuilder, llvm_value.value);
        }
    }

    info->type = clone_node_type(result_type);

    gFunction = function;
    info->function_node_block = function_node_block;

    return TRUE;
}

unsigned int sNodeTree_create_generics_function(char* fun_name, sParserParam* params, int num_params, sNodeType* result_type, MANAGED char* block_text, char* struct_name, char* sname, int sline, BOOL var_arg, int version, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeGenericsFunction;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    xstrncpy(gNodes[node].uValue.sFunction.mName, fun_name, VAR_NAME_MAX);

    int i;
    for(i=0; i<num_params; i++) {
        gNodes[node].uValue.sFunction.mParams[i] = params[i]; // copy struct
        gNodes[node].uValue.sFunction.mParams[i].mType = clone_node_type(params[i].mType);
    }

    gNodes[node].uValue.sFunction.mNumParams = num_params;
    gNodes[node].uValue.sFunction.mResultType = clone_node_type(result_type);

    gNodes[node].uValue.sFunction.mBlockText = MANAGED block_text;

    if(struct_name) {
        xstrncpy(gNodes[node].uValue.sFunction.mStructName, struct_name, VAR_NAME_MAX);
    }
    else {
        xstrncpy(gNodes[node].uValue.sFunction.mStructName, "", VAR_NAME_MAX);
    }

    gNodes[node].uValue.sFunction.mNumGenerics = info->mNumGenerics;

    for(i=0; i<info->mNumGenerics; i++) {
        xstrncpy(gNodes[node].uValue.sFunction.mGenericsTypeNames[i], info->mGenericsTypeNames[i], VAR_NAME_MAX);
    }

    gNodes[node].uValue.sFunction.mNumMethodGenerics = info->mNumMethodGenerics;
    gNodes[node].uValue.sFunction.mSLine = sline;
    gNodes[node].uValue.sFunction.mInCLang = info->in_clang;
    gNodes[node].uValue.sFunction.mVarArg = var_arg;
    gNodes[node].uValue.sFunction.mVersion = version;

    for(i=0; i<info->mNumMethodGenerics; i++) {
        xstrncpy(gNodes[node].uValue.sFunction.mMethodGenericsTypeNames[i], info->mMethodGenericsTypeNames[i], VAR_NAME_MAX);
    }

    return node;
}

void create_real_fun_name(char* real_fun_name, size_t size_real_fun_name, char* fun_name, char* struct_name)
{
    if(strcmp(struct_name, "") == 0) {
        xstrncpy(real_fun_name, fun_name, size_real_fun_name);
    }
    else {
        xstrncpy(real_fun_name, struct_name, size_real_fun_name);
        xstrncat(real_fun_name, "_", size_real_fun_name);
        xstrncat(real_fun_name, fun_name, size_real_fun_name);
    }
}

BOOL compile_generics_function(unsigned int node, sCompileInfo* info)
{
    BOOL in_clang = gNodes[node].uValue.sFunction.mInCLang;
    int version = gNodes[node].uValue.sFunction.mVersion;

    /// rename variables ///
    char fun_name[VAR_NAME_MAX];
    xstrncpy(fun_name, gNodes[node].uValue.sFunction.mName, VAR_NAME_MAX);
    int num_params = gNodes[node].uValue.sFunction.mNumParams;
    sParserParam params[PARAMS_MAX];
    memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);
    BOOL var_arg = gNodes[node].uValue.sFunction.mVarArg;

    int i;
    for(i=0; i<num_params; i++) {
        params[i] = gNodes[node].uValue.sFunction.mParams[i];
    }

    sNodeType* result_type = gNodes[node].uValue.sFunction.mResultType;

    char* block_text = gNodes[node].uValue.sFunction.mBlockText;
    char struct_name[VAR_NAME_MAX];
    xstrncpy(struct_name, gNodes[node].uValue.sFunction.mStructName, VAR_NAME_MAX);
    char sname[PATH_MAX];
    xstrncpy(sname, gNodes[node].mSName, PATH_MAX);
    int sline = gNodes[node].uValue.sFunction.mSLine;

    int num_generics = gNodes[node].uValue.sFunction.mNumGenerics;

    char generics_type_names[GENERICS_TYPES_MAX][VAR_NAME_MAX];
    for(i=0; i<num_generics; i++) {
        xstrncpy(generics_type_names[i], gNodes[node].uValue.sFunction.mGenericsTypeNames[i], VAR_NAME_MAX);
    }

    xstrncpy(info->fun_name, fun_name, VAR_NAME_MAX);

    /// go ///
    sNodeType* param_types[PARAMS_MAX];
    char param_names[PARAMS_MAX][VAR_NAME_MAX];

    for(i=0; i<num_params; i++) {
        sNodeType* param_type = params[i].mType;

        xstrncpy(param_names[i], params[i].mName, VAR_NAME_MAX);

        param_types[i] = param_type;
    }

    char real_fun_name[REAL_FUN_NAME_MAX];
    create_real_fun_name(real_fun_name, REAL_FUN_NAME_MAX, fun_name, struct_name);

    /// go ///
    char* param_names2[PARAMS_MAX];
    for(i=0; i<num_params; i++) {
        param_names2[i] = param_names[i];
    }

    char* generics_type_names2[PARAMS_MAX];
    for(i=0; i<num_generics; i++) {
        generics_type_names2[i] = generics_type_names[i];
    }

    LLVMValueRef llvm_fun = NULL;
    BOOL generics_function = TRUE;
    if(!add_function_to_table(real_fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, num_generics, generics_type_names2)) {
        return TRUE;
    }
    

    return TRUE;
}

unsigned int sNodeTree_create_inline_function(char* fun_name, sParserParam* params, int num_params, sNodeType* result_type, MANAGED char* block_text, char* struct_name, char* sname, int sline, BOOL var_arg, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeInlineFunction;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    xstrncpy(gNodes[node].uValue.sFunction.mName, fun_name, VAR_NAME_MAX);

    int i;
    for(i=0; i<num_params; i++) {
        gNodes[node].uValue.sFunction.mParams[i] = params[i]; // copy struct
        gNodes[node].uValue.sFunction.mParams[i].mType = clone_node_type(params[i].mType);
    }

    gNodes[node].uValue.sFunction.mNumParams = num_params;
    gNodes[node].uValue.sFunction.mResultType = clone_node_type(result_type);
    gNodes[node].uValue.sFunction.mBlockText = MANAGED block_text;
    gNodes[node].uValue.sFunction.mSLine = sline;
    gNodes[node].uValue.sFunction.mVarArg = var_arg;

    if(struct_name) {
        xstrncpy(gNodes[node].uValue.sFunction.mStructName, struct_name, VAR_NAME_MAX);
    }
    else {
        xstrncpy(gNodes[node].uValue.sFunction.mStructName, "", VAR_NAME_MAX);
    }

    gNodes[node].uValue.sFunction.mNumGenerics = info->mNumGenerics;

    for(i=0; i<info->mNumGenerics; i++) {
        xstrncpy(gNodes[node].uValue.sFunction.mGenericsTypeNames[i], info->mGenericsTypeNames[i], VAR_NAME_MAX);
    }

    gNodes[node].uValue.sFunction.mNumMethodGenerics = info->mNumMethodGenerics;
    gNodes[node].uValue.sFunction.mSLine = sline;
    gNodes[node].uValue.sFunction.mInCLang = info->in_clang;

    for(i=0; i<info->mNumMethodGenerics; i++) {
        xstrncpy(gNodes[node].uValue.sFunction.mMethodGenericsTypeNames[i], info->mMethodGenericsTypeNames[i], VAR_NAME_MAX);
    }

    return node;
}

BOOL compile_inline_function(unsigned int node, sCompileInfo* info)
{
    /// rename variables ///
    char fun_name[VAR_NAME_MAX];
    xstrncpy(fun_name, gNodes[node].uValue.sFunction.mName, VAR_NAME_MAX);
    int num_params = gNodes[node].uValue.sFunction.mNumParams;
    sParserParam params[PARAMS_MAX];
    memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);
    BOOL var_arg = gNodes[node].uValue.sFunction.mVarArg;

    int i;
    for(i=0; i<num_params; i++) {
        params[i] = gNodes[node].uValue.sFunction.mParams[i];
    }

    sNodeType* result_type = gNodes[node].uValue.sFunction.mResultType;

    char* block_text = gNodes[node].uValue.sFunction.mBlockText;
    char struct_name[VAR_NAME_MAX];
    xstrncpy(struct_name, gNodes[node].uValue.sFunction.mStructName, VAR_NAME_MAX);
    char sname[PATH_MAX];
    xstrncpy(sname, gNodes[node].mSName, PATH_MAX);
    int sline = gNodes[node].uValue.sFunction.mSLine;

    int num_generics = gNodes[node].uValue.sFunction.mNumGenerics;

    char generics_type_names[PARAMS_MAX][VAR_NAME_MAX];
    for(i=0; i<num_generics; i++) {
        xstrncpy(generics_type_names[i], gNodes[node].uValue.sFunction.mGenericsTypeNames[i], VAR_NAME_MAX);
    }

    /// go ///
    sNodeType* param_types[PARAMS_MAX];
    char param_names[PARAMS_MAX][VAR_NAME_MAX];

    for(i=0; i<num_params; i++) {
        sNodeType* param_type = params[i].mType;

        xstrncpy(param_names[i], params[i].mName, VAR_NAME_MAX);

        param_types[i] = param_type;
    }

    /// go ///
    LLVMValueRef llvm_fun = NULL;

    char* param_names2[PARAMS_MAX];
    for(i=0; i<PARAMS_MAX; i++) {
        param_names2[i] = param_names[i];
    }

    BOOL generics_function = FALSE;
    if(!add_function_to_table(fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, 0, NULL)) {
        fprintf(stderr, "overflow function table\n");
        return FALSE;
    }

    return TRUE;
}

unsigned int sNodeTree_create_load_variable(char* var_name, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadVariable;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sLoadVariable.mVarName, var_name, VAR_NAME_MAX);
    gNodes[node].uValue.sLoadVariable.mGlobal = info->mBlockLevel == 0;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}


static BOOL compile_load_variable(unsigned int node, sCompileInfo* info)
{
    char* var_name = gNodes[node].uValue.sLoadVariable.mVarName;

    sVar* var = get_variable_from_table(info->pinfo->lv_table, var_name);

    BOOL global = var->mGlobal;
    BOOL constant = var->mConstant;

    sNodeType* var_type = clone_node_type(var->mType);

    LLVMValueRef var_address = var->mLLVMValue;

    if(var_address == NULL) {
        compile_err_msg(info, "no variable address");
        return FALSE;
    }

    LVALUE llvm_value;

    if(global) {
        llvm_value.value = LLVMBuildLoad(gBuilder, var_address, var_name);
    }
    else if(constant) {
        llvm_value.value = var_address;
    }
    else if(var_type->mArrayDimentionNum >= 1) {
        llvm_value.value = var_address;
    }
    else {
        if(type_identify_with_class_name(var_type, "__builtin_va_list") || type_identify_with_class_name(var_type, "va_list")) {
#ifdef __X86_64_CPU__

            LLVMValueRef indices[2];

            LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

            indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
            indices[1] = LLVMConstInt(llvm_type, 0, FALSE);

            llvm_value.value = LLVMBuildGEP(gBuilder, var_address, indices, 2, "gep");
#else
            llvm_value.value = var_address;
#endif
        }
        else {
            llvm_value.value = LLVMBuildLoad(gBuilder, var_address, var_name);
        }
    }

    llvm_value.type = var_type;
    llvm_value.address = var_address;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = clone_node_type(var_type);

    return TRUE;
}

unsigned int sNodeTree_if_expression(unsigned int expression_node, MANAGED struct sNodeBlockStruct* if_node_block, unsigned int* elif_expression_nodes, MANAGED struct sNodeBlockStruct** elif_node_blocks, int elif_num, MANAGED struct sNodeBlockStruct* else_node_block, sParserInfo* info, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIf;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sIf.mExpressionNode = expression_node;
    gNodes[node].uValue.sIf.mIfNodeBlock = MANAGED if_node_block;
    memcpy(gNodes[node].uValue.sIf.mElifExpressionNodes, elif_expression_nodes, sizeof(unsigned int)*elif_num);
    memcpy(gNodes[node].uValue.sIf.mElifNodeBlocks, MANAGED elif_node_blocks, sizeof(sNodeBlock*)*elif_num);
    gNodes[node].uValue.sIf.mElifNum = elif_num;
    gNodes[node].uValue.sIf.mElseNodeBlock = MANAGED else_node_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}


static BOOL compile_if_expression(unsigned int node, sCompileInfo* info)
{
    sNodeBlock* else_node_block = gNodes[node].uValue.sIf.mElseNodeBlock;
    int elif_num = gNodes[node].uValue.sIf.mElifNum;

    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sIf.mExpressionNode;

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    sNodeType* conditional_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, conditional_type)) {
        if(!cast_right_type_to_left_type(bool_type, &conditional_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    if(!type_identify_with_class_name(conditional_type, "bool")) {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }
    LLVMBasicBlockRef cond_then_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_jump_then");

    LLVMBasicBlockRef cond_else_block = NULL;

    LLVMBasicBlockRef cond_elif_block[ELIF_NUM_MAX];
    LLVMBasicBlockRef cond_elif_then_block[ELIF_NUM_MAX];
    if(elif_num > 0) {
        int i;
        for(i=0; i<elif_num; i++) {
            char buf[128];
            snprintf(buf, 128, "cond_jump_elif%d\n", i);

            cond_elif_block[i] = LLVMAppendBasicBlockInContext(gContext, gFunction, buf);

            snprintf(buf, 128, "cond_jump_elif_then%d\n", i);

            cond_elif_then_block[i] = LLVMAppendBasicBlockInContext(gContext, gFunction, buf);
        }
    }

    if(else_node_block) {
        cond_else_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_else_block");
    }
    LLVMBasicBlockRef cond_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_end");

    if(elif_num > 0) {
        LLVMBuildCondBr(gBuilder, conditional_value.value, cond_then_block, cond_elif_block[0]);
    }
    else if(else_node_block) {
        LLVMBuildCondBr(gBuilder, conditional_value.value, cond_then_block, cond_else_block);
    }
    else {
        LLVMBuildCondBr(gBuilder, conditional_value.value, cond_then_block, cond_end_block);
    }

    llvm_change_block(cond_then_block, info);

    sNodeBlock* if_block = gNodes[node].uValue.sIf.mIfNodeBlock;
    sNodeType* result_type = create_node_type_with_class_name("void");

    BOOL last_expression_is_return_before = info->last_expression_is_return;
    info->last_expression_is_return = FALSE;

    if(!compile_block(if_block, info, result_type)) {
        return FALSE;
    }

    if(!info->last_expression_is_return) {
        LLVMBuildBr(gBuilder, cond_end_block);
    }

    info->last_expression_is_return = last_expression_is_return_before;

    //// elif ///
    if(elif_num > 0) {
        int i;
        for(i=0; i<elif_num; i++) {
            llvm_change_block(cond_elif_block[i], info);

            unsigned int expression_node = gNodes[node].uValue.sIf.mElifExpressionNodes[i];

            if(!compile(expression_node, info)) {
                return FALSE;
            }

            sNodeType* conditional_type = info->type;

            LVALUE conditional_value = *get_value_from_stack(-1);
            dec_stack_ptr(1, info);

            sNodeType* bool_type = create_node_type_with_class_name("bool");

            if(auto_cast_posibility(bool_type, conditional_type)) {
                if(!cast_right_type_to_left_type(bool_type, &conditional_type, &conditional_value, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            if(!type_identify_with_class_name(conditional_type, "bool")) 
            {
                compile_err_msg(info, "This conditional type is not bool");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            if(i == elif_num-1) {
                if(else_node_block) {
                    LLVMBuildCondBr(gBuilder, conditional_value.value, cond_elif_then_block[i], cond_else_block);
                }
                else {
                    LLVMBuildCondBr(gBuilder, conditional_value.value, cond_elif_then_block[i], cond_end_block);
                }
            }
            else {
                LLVMBuildCondBr(gBuilder, conditional_value.value, cond_elif_then_block[i], cond_elif_block[i+1]);
            }

            llvm_change_block(cond_elif_then_block[i], info);

            sNodeBlock* elif_node_block = gNodes[node].uValue.sIf.mElifNodeBlocks[i];

            BOOL last_expression_is_return_before = info->last_expression_is_return;
            info->last_expression_is_return = FALSE;

            if(!compile_block(elif_node_block, info, result_type)) 
            {
                return FALSE;
            }

            if(!info->last_expression_is_return) {
                LLVMBuildBr(gBuilder, cond_end_block);
            }

            info->last_expression_is_return = last_expression_is_return_before;
        }
    }

    if(else_node_block) {
        llvm_change_block(cond_else_block, info);

        BOOL last_expression_is_return_before = info->last_expression_is_return;
        info->last_expression_is_return = FALSE;

        if(!compile_block(else_node_block, info, result_type)) 
        {
            return FALSE;
        }

        if(!info->last_expression_is_return) {
            LLVMBuildBr(gBuilder, cond_end_block);
        }

        info->last_expression_is_return = last_expression_is_return_before;
    }

    llvm_change_block(cond_end_block, info);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_struct(sNodeType* struct_type, sParserInfo* info, char* sname, int sline, BOOL undefined_body)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStruct;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sStruct.mType = struct_type;
    gNodes[node].uValue.sStruct.mUndefinedBody = undefined_body;
    gNodes[node].uValue.sStruct.mAnonymous = FALSE;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL is_generics_type(sNodeType* node_type)
{
    sCLClass* klass = node_type->mClass;

    if(klass->mFlags & CLASS_FLAGS_GENERICS) {
        return TRUE;
    }
    else {
        int i;
        for(i=0; i<node_type->mNumGenericsTypes; i++) {
            if(is_generics_type(node_type->mGenericsTypes[i])) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

BOOL is_generics_struct_type(sNodeType* node_type)
{
    sCLClass* klass = node_type->mClass;

    int i;
    for(i=0; i<klass->mNumFields; i++) {
        if(is_generics_type(klass->mFields[i])) {
            return TRUE;
        }
    }

    return FALSE;
}

static BOOL compile_struct(unsigned int node, sCompileInfo* info)
{
    sNodeType* node_type = gNodes[node].uValue.sStruct.mType;
    BOOL undefined_body = gNodes[node].uValue.sStruct.mUndefinedBody;

    if(is_generics_struct_type(node_type)) {
        if(!add_generics_struct_type_to_table(CLASS_NAME(node_type->mClass), node_type)) {
            fprintf(stderr, "overflow generics struct type\n");
            exit(1);
        }
    }
    else {
        char* struct_name = CLASS_NAME(node_type->mClass);
        create_llvm_struct_type(struct_name, node_type, NULL, undefined_body);
    }

    return TRUE;
}

unsigned int sNodeTree_union(sNodeType* struct_type, sParserInfo* info, char* sname, int sline, BOOL undefined_body)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeUnion;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sStruct.mType = struct_type;
    gNodes[node].uValue.sStruct.mUndefinedBody = undefined_body;
    gNodes[node].uValue.sStruct.mAnonymous = FALSE;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_union(unsigned int node, sCompileInfo* info)
{
    sNodeType* node_type = gNodes[node].uValue.sStruct.mType;
    BOOL undefined_body = gNodes[node].uValue.sStruct.mUndefinedBody;

    create_llvm_union_type(node_type, NULL, undefined_body, info);

    return TRUE;
}

unsigned int sNodeTree_create_object(sNodeType* node_type, unsigned int object_num, int num_params, unsigned int* params, char* sname, int sline, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeObject;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sObject.mType = clone_node_type(node_type);
    gNodes[node].uValue.sObject.mNumParams = num_params;

    int i;
    if(num_params > 0) {
        for(i=0; i<num_params; i++) {
            gNodes[node].uValue.sObject.mParams[i] = params[i];
        }
    }

    gNodes[node].mLeft = object_num;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_object(unsigned int node, sCompileInfo* info)
{
    sNodeType* node_type = gNodes[node].uValue.sObject.mType;
    int num_params = gNodes[node].uValue.sObject.mNumParams;
    unsigned int params[PARAMS_MAX];

    int i;
    if(num_params > 0) {
        for(i=0; i<num_params; i++) {
            params[i] = gNodes[node].uValue.sObject.mParams[i];
        }
    }

    sNodeType* node_type2 = clone_node_type(node_type);
    node_type2->mHeap = TRUE;
    node_type2->mPointerNum = 0;

    if(is_typeof_type(node_type2))
    {
        if(!solve_typeof(&node_type2, info)) 
        {
            compile_err_msg(info, "Can't solve typeof types");
            show_node_type(node_type2); 
            info->err_num++;
            return TRUE;
        }
    }

    if(info->generics_type) {
        if(!solve_generics(&node_type2, info->generics_type)) 
        {
            compile_err_msg(info, "Can't solve generics types(3)");
            show_node_type(node_type2);
            show_node_type(info->generics_type);
            info->err_num++;

            return FALSE;
        }
    }

    if(!create_generics_struct_type(node_type2)) {
        compile_err_msg(info, "invalid type %s", CLASS_NAME(node_type2->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    unsigned int left_node = gNodes[node].mLeft;

    LLVMValueRef object_num;
    if(left_node == 0) {
        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("long");
        object_num = LLVMConstInt(llvm_type, 1, FALSE);
    }
    else {
        if(!compile(left_node, info)) {
            return FALSE;
        }

        sNodeType* left_type = create_node_type_with_class_name("long");

        LVALUE llvm_value = *get_value_from_stack(-1);
        dec_stack_ptr(1, info);

        sNodeType* right_type = clone_node_type(llvm_value.type);

        if(auto_cast_posibility(left_type, right_type)) 
        {
            if(!cast_right_type_to_left_type(left_type, &right_type, &llvm_value, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        object_num = llvm_value.value;
    }

    char* class_name = CLASS_NAME(node_type->mClass);

    sFunction* constructor_fun = get_function_from_table(class_name);

    if(constructor_fun && num_params >= 0 && num_params == constructor_fun->mNumParams) {
        unsigned int node2 = sNodeTree_create_function_call(class_name, params, num_params, FALSE, FALSE, 0, info->pinfo);

        if(!compile(node2, info)) {
            return FALSE;
        }

        return TRUE;
    }
    else {
        /// calloc ///
        int num_params = 2;

        LLVMValueRef llvm_params[PARAMS_MAX];
        memset(llvm_params, 0, sizeof(LLVMValueRef)*PARAMS_MAX);

        char* fun_name = "calloc";

        llvm_params[0] = object_num;

        LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type2);

        uint64_t alloc_size = get_size_from_node_type(node_type2);

        LLVMTypeRef long_type = create_llvm_type_with_class_name("long");
        llvm_params[1] = LLVMConstInt(long_type, alloc_size, FALSE);

        LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, fun_name);

        if(llvm_fun == NULL) {
            compile_err_msg(info, "require calloc difinition to create object");
            return FALSE;
        }

        LLVMValueRef address = LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "fun_result");

        node_type2->mPointerNum++;

        LLVMTypeRef llvm_type2 = create_llvm_type_from_node_type(node_type2);

        address = LLVMBuildPointerCast(gBuilder, address, llvm_type2, "obj");

        /// result ///
        LVALUE llvm_value;
        llvm_value.value = address;
        llvm_value.type = clone_node_type(node_type2);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        append_object_to_right_values(address, node_type2, info);

        info->type = clone_node_type(node_type2);
    }

    return TRUE;
}

unsigned int sNodeTree_create_delete(unsigned int object_node, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDelete;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = object_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_delete(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(left_node == 0) {
        compile_err_msg(info, "require delete target object");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(!compile(left_node, info)) {
        return FALSE;
    }

    LVALUE llvm_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    sNodeType* node_type = clone_node_type(info->type);

    free_object(node_type, llvm_value.address, info);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_create_borrow(unsigned int object_node, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeBorrow;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = object_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_borrow(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(left_node == 0) {
        compile_err_msg(info, "require borrow target object");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(!compile(left_node, info)) {
        return FALSE;
    }

    LVALUE llvm_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    llvm_value.type->mHeap = FALSE;

    remove_object_from_right_values(llvm_value.value);

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = clone_node_type(llvm_value.type);

    return TRUE;
}

unsigned int sNodeTree_create_dummy_heap(unsigned int object_node, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDummyHeap;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = object_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_dummy_heap(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(left_node == 0) {
        compile_err_msg(info, "require dummy heap target object");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(!compile(left_node, info)) {
        return FALSE;
    }

    LVALUE llvm_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    llvm_value.type->mHeap = TRUE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = clone_node_type(llvm_value.type);

    return TRUE;
}

unsigned int sNodeTree_create_managed(char* var_name, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeManaged;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sManaged.mVarName, var_name, VAR_NAME_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}


static BOOL compile_managed(unsigned int node, sCompileInfo* info)
{
    char* var_name = gNodes[node].uValue.sLoadVariable.mVarName;

    sVar* var = get_variable_from_table(info->pinfo->lv_table, var_name);

    if(var == NULL) {
        compile_err_msg(info, "undeclared variable %s(99)", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    sNodeType* var_type = clone_node_type(var->mType);

    if(var_type == NULL || var_type->mClass == NULL) 
    {
        compile_err_msg(info, "null type %s", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    var->mType->mHeap = FALSE;

    info->type = create_node_type_with_class_name("void"); // dummy

    return TRUE;
}

unsigned int sNodeTree_create_stack_object(sNodeType* node_type, unsigned int object_num, char* sname, int sline, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStackObject;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sObject.mType = clone_node_type(node_type);

    gNodes[node].mLeft = object_num;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_stack_object(unsigned int node, sCompileInfo* info)
{
    sNodeType* node_type = gNodes[node].uValue.sObject.mType;

    sNodeType* node_type2 = clone_node_type(node_type);
    node_type2->mPointerNum++;
    node_type2->mHeap = FALSE;

    if(is_typeof_type(node_type2))
    {
        if(!solve_typeof(&node_type2, info)) 
        {
            compile_err_msg(info, "Can't solve typeof types");
            show_node_type(node_type2); 
            info->err_num++;
            return TRUE;
        }
    }

    unsigned int left_node = gNodes[node].mLeft;

    if(left_node == 0) {
        LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type);

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildAlloca(gBuilder, llvm_type, "stack_object");
        llvm_value.type = node_type2;
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        info->type = node_type2;
    }
    else {
        if(!compile(left_node, info)) {
            return FALSE;
        }

        if(!type_identify_with_class_name(info->type, "int")) {
            compile_err_msg(info, "Require number value for []");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        LVALUE llvm_value = *get_value_from_stack(-1);
        dec_stack_ptr(1, info);

        LLVMValueRef object_num = llvm_value.value;

        LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type);

        LVALUE llvm_value2;
        llvm_value2.value = LLVMBuildArrayAlloca(gBuilder, llvm_type, object_num, "stack_object");
        llvm_value2.type = node_type2;
        llvm_value2.address = NULL;
        llvm_value2.var = NULL;
        llvm_value2.binded_value = FALSE;
        llvm_value2.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value2, info);

        info->type = node_type2;
    }

    return TRUE;
}

unsigned int sNodeTree_create_store_field(char* var_name, unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreField;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sStoreField.mVarName, var_name, VAR_NAME_MAX);

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_store_field(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX];
    xstrncpy(var_name, gNodes[node].uValue.sStoreField.mVarName, VAR_NAME_MAX);

    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    int parent_field_index = -1;
    int field_index = get_field_index(left_type->mClass, var_name, &parent_field_index);

    if(field_index == -1) {
        sCLClass* klass = left_type->mClass;

        char var_name2[VAR_NAME_MAX];

        int i;
        for(i=0; i<klass->mNumFields; i++) {
            sNodeType* field_type = klass->mFields[i];
            char* field_name = CONS_str(&klass->mConst, klass->mFieldNameOffsets[i]);

            int parent_field_index = -1;
            field_index = get_field_index(field_type->mClass, var_name, &parent_field_index);

            if(field_index != -1) {
                xstrncpy(var_name2, field_name, VAR_NAME_MAX);
                break;
            }
        }

        if(i < klass->mNumFields) {
            dec_stack_ptr(-1, info);
            unsigned int new_lnode = sNodeTree_create_load_field(var_name2, lnode, info->pinfo);

            if(!compile(new_lnode, info)) {
                return FALSE;
            }

            left_type = clone_node_type(info->type);
        }
        else {
            compile_err_msg(info, "The field(%s) is not found(1)", var_name);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }
    else if(field_index == -1) {
        compile_err_msg(info, "The field(%s) is not found(2)", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LVALUE lvalue = *get_value_from_stack(-1);

    if(!(left_type->mClass->mFlags & CLASS_FLAGS_STRUCT) && !(left_type->mClass->mFlags & CLASS_FLAGS_UNION)) {
        compile_err_msg(info, "This is not struct type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// compile right node ///
    unsigned int rnode = gNodes[node].mRight;

    if(!compile(rnode, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);

    sNodeType* field_type = clone_node_type(left_type->mClass->mFields[field_index]);

    if(is_typeof_type(field_type))
    {
        if(!solve_typeof(&field_type, info)) 
        {
            compile_err_msg(info, "Can't solve typeof types");
            show_node_type(field_type); 
            info->err_num++;
            return FALSE;
        }
    }

    if(!solve_generics(&field_type, left_type)) {
        compile_err_msg(info, "Solve Generics Error");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(auto_cast_posibility(field_type, right_type)) {
        if(!cast_right_type_to_left_type(field_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }
    
    if(!substitution_posibility(field_type, right_type, info)) {
        compile_err_msg(info, "The different type between left type and right type. store field");
        show_node_type(field_type);
        show_node_type(right_type);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMValueRef field_address;

    if(left_type->mClass->mFlags & CLASS_FLAGS_UNION) {
        field_index = 0;
        if(left_type->mPointerNum == 0) {
            field_address = LLVMBuildStructGEP(gBuilder, lvalue.address, field_index, "field");
        }
        else {
            field_address = LLVMBuildStructGEP(gBuilder, lvalue.value, field_index, "field");
        }

        field_type->mPointerNum++;

        LLVMTypeRef llvm_type = create_llvm_type_from_node_type(field_type);

        field_address = LLVMBuildCast(gBuilder, LLVMBitCast, field_address, llvm_type, "icast");
    }
    else {
        if(left_type->mPointerNum == 0) {
            field_address = LLVMBuildStructGEP(gBuilder, lvalue.address, field_index, "field");
        }
        else {
            field_address = LLVMBuildStructGEP(gBuilder, lvalue.value, field_index, "field");
        }
    }

    LLVMBuildStore(gBuilder, rvalue.value, field_address);

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&rvalue, info);

    info->type = clone_node_type(right_type);

    return TRUE;
}

unsigned int sNodeTree_create_load_field(char* name, unsigned int left_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadField;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sLoadField.mVarName, name, VAR_NAME_MAX);

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_load_field(unsigned int node, sCompileInfo* info)
{
    char var_name[VAR_NAME_MAX]; 
    xstrncpy(var_name, gNodes[node].uValue.sLoadField.mVarName, VAR_NAME_MAX);

    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    int parent_field_index = -1;
    int field_index = get_field_index(left_type->mClass, var_name, &parent_field_index);

    if(field_index == -1) {
        sCLClass* klass = left_type->mClass;

        char var_name2[VAR_NAME_MAX];

        int i;
        for(i=0; i<klass->mNumFields; i++) {
            sNodeType* field_type = klass->mFields[i];
            char* field_name = CONS_str(&klass->mConst, klass->mFieldNameOffsets[i]);

            int parent_field_index = -1;
            int field_index = get_field_index(field_type->mClass, var_name, &parent_field_index);

            if(field_index != -1) {
                xstrncpy(var_name2, field_name, VAR_NAME_MAX);
                break;
            }
        }

        if(i < klass->mNumFields) {
            dec_stack_ptr(-1, info);
            unsigned int new_lnode = sNodeTree_create_load_field(var_name2, lnode, info->pinfo);

            if(!compile(new_lnode, info)) {
                return FALSE;
            }

            left_type = clone_node_type(info->type);
        }
        else {
            compile_err_msg(info, "The field(%s) is not found(1)", var_name);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }
    else if(field_index == -1) {
        compile_err_msg(info, "The field(%s) is not found(2)", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LVALUE lvalue = *get_value_from_stack(-1);

    if(!(left_type->mClass->mFlags & CLASS_FLAGS_STRUCT) && !(left_type->mClass->mFlags & CLASS_FLAGS_UNION)) {
        compile_err_msg(info, "This is not struct type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(left_type->mPointerNum > 1) {
        compile_err_msg(info, "This is pointer of pointer type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(left_type->mClass->mFlags & CLASS_FLAGS_UNION) {
        int parent_field_index = -1;
        int field_index = get_field_index(left_type->mClass, var_name, &parent_field_index);

        if(field_index == -1) {
            compile_err_msg(info, "The field(%s) is not found", var_name);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sNodeType* field_type = clone_node_type(left_type->mClass->mFields[field_index]);

        field_index = 0;
        
        LLVMValueRef field_address;
        if(left_type->mPointerNum == 0) {
            field_address = LLVMBuildStructGEP(gBuilder, lvalue.address, field_index, "field");
        }
        else {
            field_address = LLVMBuildStructGEP(gBuilder, lvalue.value, field_index, "field");
        }
        
        sNodeType* field_type2 = clone_node_type(field_type);

        field_type2->mPointerNum++;

        LLVMTypeRef llvm_type = create_llvm_type_from_node_type(field_type2);

        field_address = LLVMBuildCast(gBuilder, LLVMBitCast, field_address, llvm_type, "icast");

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildLoad(gBuilder, field_address, var_name);
        llvm_value.type = clone_node_type(field_type);
        llvm_value.address = field_address;
        llvm_value.var = NULL;
        llvm_value.binded_value = TRUE;
        llvm_value.load_field = TRUE;

        dec_stack_ptr(1, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(field_type);
    }
    else {
        int parent_field_index = -1;
        int field_index = get_field_index(left_type->mClass, var_name, &parent_field_index);

        if(field_index == -1) {
            compile_err_msg(info, "The field(%s) is not found", var_name);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        sNodeType* field_type = clone_node_type(left_type->mClass->mFields[field_index]);

        if(is_typeof_type(field_type))
        {
            if(!solve_typeof(&field_type, info)) 
            {
                compile_err_msg(info, "Can't solve typeof types");
                show_node_type(field_type); 
                info->err_num++;
                return FALSE;
            }
        }

        if(!solve_generics(&field_type, left_type)) {
            compile_err_msg(info, "Solve Generics Error");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
        
        LLVMValueRef field_address;
        if(left_type->mPointerNum == 0) {
            field_address = LLVMBuildStructGEP(gBuilder, lvalue.address, field_index, "field");
        }
        else {
            field_address = LLVMBuildStructGEP(gBuilder, lvalue.value, field_index, "field");
        }

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildLoad(gBuilder, field_address, var_name);
        llvm_value.type = clone_node_type(field_type);
        llvm_value.address = field_address;
        llvm_value.var = NULL;
        llvm_value.binded_value = TRUE;
        llvm_value.load_field = TRUE;

        dec_stack_ptr(1, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(field_type);
    }

    return TRUE;
}

unsigned int sNodeTree_while_expression(unsigned int expression_node, MANAGED struct sNodeBlockStruct* while_node_block, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeWhile;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sWhile.mExpressionNode = expression_node;
    gNodes[node].uValue.sWhile.mWhileNodeBlock = MANAGED while_node_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_while_expression(unsigned int node, sCompileInfo* info)
{
    void* switch_expression_before = info->switch_expression;
    info->switch_expression = NULL;

    sNodeBlock* while_node_block = gNodes[node].uValue.sWhile.mWhileNodeBlock;

    LLVMBasicBlockRef loop_top_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "loop_top_block");

    LLVMBuildBr(gBuilder, loop_top_block);

    llvm_change_block(loop_top_block, info);

    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sWhile.mExpressionNode;

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    sNodeType* conditional_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, conditional_type)) {
        if(!cast_right_type_to_left_type(bool_type, &conditional_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(conditional_type, "bool")) {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    LLVMBasicBlockRef cond_then_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_then_block");

    LLVMBasicBlockRef cond_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_end_block");

    info->loop_end_block[info->num_loop] = cond_end_block;
    info->num_loop++;

    if(info->num_loop >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. while(1)", info->num_loop);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    info->loop_begin_block[info->num_loop2] = cond_then_block;
    info->num_loop2++;

    if(info->num_loop2 >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. while(2)", info->num_loop2);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMBuildCondBr(gBuilder, conditional_value.value, cond_then_block, cond_end_block);

    llvm_change_block(cond_then_block, info);

    BOOL last_expression_is_return_before = info->last_expression_is_return;
    info->last_expression_is_return = FALSE;

    sNodeBlock* current_node_block = info->current_node_block;
    info->current_node_block = while_node_block;

    sNodeType* result_type = create_node_type_with_class_name("void");

    if(!compile_block(while_node_block, info, result_type)) {
        return FALSE;
    }

    info->current_node_block = current_node_block;

    if(!info->last_expression_is_return) {
        LLVMBuildBr(gBuilder, loop_top_block);
    }

    info->num_loop--;
    info->num_loop2--;

    info->last_expression_is_return = last_expression_is_return_before;

    llvm_change_block(cond_end_block, info);

    info->type = create_node_type_with_class_name("void");

    info->switch_expression = switch_expression_before;

    return TRUE;
}

unsigned int sNodeTree_do_while_expression(unsigned int expression_node, MANAGED struct sNodeBlockStruct* while_node_block, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDoWhile;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sWhile.mExpressionNode = expression_node;
    gNodes[node].uValue.sWhile.mWhileNodeBlock = MANAGED while_node_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_do_while_expression(unsigned int node, sCompileInfo* info)
{
    void* switch_expression_before = info->switch_expression;
    info->switch_expression = NULL;

    sNodeBlock* while_node_block = gNodes[node].uValue.sWhile.mWhileNodeBlock;

    LLVMBasicBlockRef loop_top_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "loop_top_block");

    LLVMBuildBr(gBuilder, loop_top_block);

    llvm_change_block(loop_top_block, info);

    info->loop_begin_block[info->num_loop2] = loop_top_block;
    info->num_loop2++;

    if(info->num_loop2 >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. do while", info->num_loop2);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMBasicBlockRef cond_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_end_block");

    info->loop_end_block[info->num_loop] = cond_end_block;
    info->num_loop++;

    if(info->num_loop >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. do while", info->num_loop);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    BOOL last_expression_is_return_before = info->last_expression_is_return;
    info->last_expression_is_return = FALSE;

    sNodeBlock* current_node_block = info->current_node_block;
    info->current_node_block = while_node_block;

    sNodeType* result_type = create_node_type_with_class_name("void");
    if(!compile_block(while_node_block, info, result_type)) {
        return FALSE;
    }

    info->current_node_block = current_node_block;

    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sWhile.mExpressionNode;

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    sNodeType* conditional_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    LLVMBuildCondBr(gBuilder, conditional_value.value, loop_top_block, cond_end_block);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, conditional_type)) {
        if(!cast_right_type_to_left_type(bool_type, &conditional_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(conditional_type, "bool")) {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    llvm_change_block(cond_end_block, info);

/*
    if(!info->last_expression_is_return) {
        free_right_value_objects(info);
        Builder.CreateBr(loop_top_block);
    }

    info->last_expression_is_return = last_expression_is_return_before;
*/
    info->type = create_node_type_with_class_name("void");

    info->switch_expression = switch_expression_before;

    return TRUE;
}

unsigned int sNodeTree_create_true(sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeTrue;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_true(unsigned int node, sCompileInfo* info)
{
    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("bool");

    LVALUE llvm_value;
    llvm_value.value = LLVMConstInt(llvm_type, 1, FALSE);
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_create_null(sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeNull;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_null(unsigned int node, sCompileInfo* info)
{
    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

    LVALUE llvm_value;
    llvm_value.value = LLVMConstInt(llvm_type, 0, FALSE);
    LLVMTypeRef llvm_type2 = create_llvm_type_with_class_name("char*");
    llvm_value.value = LLVMBuildCast(gBuilder, LLVMBitCast, llvm_value.value, llvm_type2, "cast");
    llvm_value.type = create_node_type_with_class_name("void*");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("void*");

    return TRUE;
}

unsigned int sNodeTree_create_false(sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFalse;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_false(unsigned int node, sCompileInfo* info)
{
    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("bool");

    LVALUE llvm_value;
    llvm_value.value = LLVMConstInt(llvm_type, 0, FALSE);
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_create_and_and(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAndAnd;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_and_and(unsigned int node, sCompileInfo* info)
{
    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("bool");
    LLVMValueRef result_var = LLVMBuildAlloca(gBuilder, llvm_type, "andand");

    /// compile expression ///
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, left_type)) {
        if(!cast_right_type_to_left_type(bool_type, &left_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(left_type, "bool")) {
        compile_err_msg(info, "Left expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMBuildStore(gBuilder, conditional_value.value, result_var);

    LLVMBasicBlockRef cond_then_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_jump_then");

    LLVMBasicBlockRef cond_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_jump_end");

    LLVMBuildCondBr(gBuilder, conditional_value.value, cond_then_block, cond_end_block);

    llvm_change_block(cond_then_block, info);

    /// compile right expression ///
    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE conditional_value2 = *get_value_from_stack(-1);

    if(auto_cast_posibility(bool_type, right_type)) {
        if(!cast_right_type_to_left_type(bool_type, &right_type, &conditional_value2, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(right_type, "bool")) {
        compile_err_msg(info, "Right expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMValueRef andand_value = LLVMBuildAnd(gBuilder, conditional_value.value, conditional_value2.value, "andand");

    LLVMBuildStore(gBuilder, andand_value, result_var);

    LLVMBuildBr(gBuilder, cond_end_block);

    llvm_change_block(cond_end_block, info);

    dec_stack_ptr(2, info);

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildLoad(gBuilder, result_var, "andand_result_value");
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = result_var;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_create_or_or(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeOrOr;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_or_or(unsigned int node, sCompileInfo* info)
{
    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("bool");
    LLVMValueRef result_var = LLVMBuildAlloca(gBuilder, llvm_type, "oror");

    /// compile expression ///
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, left_type)) {
        if(!cast_right_type_to_left_type(bool_type, &left_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(left_type, "bool")) {
        compile_err_msg(info, "Right expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMBuildStore(gBuilder, conditional_value.value, result_var);

    LLVMBasicBlockRef cond_then_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_jump_then");
    LLVMBasicBlockRef cond_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_jump_end");

    LLVMBuildCondBr(gBuilder, conditional_value.value, cond_end_block, cond_then_block);

    llvm_change_block(cond_then_block, info);

    /// compile right expression ///
    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE conditional_value2 = *get_value_from_stack(-1);

    if(auto_cast_posibility(bool_type, right_type)) {
        if(!cast_right_type_to_left_type(bool_type, &right_type, &conditional_value2, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(right_type, "bool")) {
        compile_err_msg(info, "Right expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMValueRef oror_value = LLVMBuildOr(gBuilder, conditional_value.value, conditional_value2.value, "oror");

    LLVMBuildStore(gBuilder, oror_value, result_var);

    LLVMBuildBr(gBuilder, cond_end_block);

    llvm_change_block(cond_end_block, info);

    dec_stack_ptr(2, info);

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildLoad(gBuilder, result_var, "oror_result_value");
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = result_var;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_for_expression(unsigned int expression_node1, unsigned int expression_node2, unsigned int expression_node3, MANAGED sNodeBlock* for_node_block, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFor;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sFor.mExpressionNode = expression_node1;
    gNodes[node].uValue.sFor.mExpressionNode2 = expression_node2;
    gNodes[node].uValue.sFor.mExpressionNode3 = expression_node3;
    gNodes[node].uValue.sFor.mForNodeBlock = MANAGED for_node_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_for_expression(unsigned int node, sCompileInfo* info)
{
    void* switch_expression_before = info->switch_expression;
    info->switch_expression = NULL;

    sNodeBlock* for_block = gNodes[node].uValue.sFor.mForNodeBlock;

    sVarTable* lv_table_before = info->pinfo->lv_table;
    info->pinfo->lv_table = for_block->mLVTable;

    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sFor.mExpressionNode;

    if(!compile(expression_node, info)) {
        info->pinfo->lv_table = lv_table_before;
        return FALSE;
    }

    /// compile expression ///
    LLVMBasicBlockRef loop_top_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "loop_top_block");

    LLVMBuildBr(gBuilder, loop_top_block);

    llvm_change_block(loop_top_block, info);

    unsigned int expression_node2 = gNodes[node].uValue.sFor.mExpressionNode2;

    if(!compile(expression_node2, info)) {
        info->pinfo->lv_table = lv_table_before;
        return FALSE;
    }

    sNodeType* conditional_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, conditional_type)) {
        if(!cast_right_type_to_left_type(bool_type, &conditional_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            info->pinfo->lv_table = lv_table_before;
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(conditional_type, "bool")) {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        info->pinfo->lv_table = lv_table_before;
        return TRUE;
    }

    LLVMBasicBlockRef cond_then_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_then_block");

    LLVMBasicBlockRef cond_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_end_block");

    info->loop_end_block[info->num_loop] = cond_end_block;
    info->num_loop++;

    if(info->num_loop >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. for", info->num_loop);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    info->loop_begin_block[info->num_loop2] = cond_then_block;
    info->num_loop2++;

    if(info->num_loop2 >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. for", info->num_loop2);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMBuildCondBr(gBuilder, conditional_value.value, cond_then_block, cond_end_block);

    llvm_change_block(cond_then_block, info);

    sNodeBlock* current_node_block = info->current_node_block;
    info->current_node_block = for_block;

    /// block of for expression ///
    sNodeType* result_type = create_node_type_with_class_name("void");
    if(!compile_block(for_block, info, result_type))
    {
        info->num_loop--;
        info->pinfo->lv_table = lv_table_before;
        return FALSE;
    }

    info->current_node_block = current_node_block;

    /// expression 3 ///
    unsigned int expression_node3 = gNodes[node].uValue.sFor.mExpressionNode3;

    BOOL last_expression_is_return_before = info->last_expression_is_return;
    info->last_expression_is_return = FALSE;

    if(!compile(expression_node3, info)) {
        info->pinfo->lv_table = lv_table_before;
        return FALSE;
    }

    if(!info->last_expression_is_return) {
        LLVMBuildBr(gBuilder, loop_top_block);
    }

    info->last_expression_is_return = last_expression_is_return_before;

    llvm_change_block(cond_end_block, info);
    info->num_loop--;

    info->pinfo->lv_table = lv_table_before;

    info->type = create_node_type_with_class_name("void");

    info->switch_expression = switch_expression_before;

    return TRUE;
}

unsigned int sNodeTree_create_lambda_call(unsigned int lambda_node, unsigned int* params, int num_params, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].uValue.sFunctionCall.mNumParams = num_params;

    int i;
    for(i=0; i<num_params; i++) {
        gNodes[node].uValue.sFunctionCall.mParams[i] = params[i];
    }
    
    gNodes[node].mNodeType = kNodeTypeLambdaCall;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = lambda_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_lambda_call(unsigned int node, sCompileInfo* info)
{
    int num_params = gNodes[node].uValue.sFunctionCall.mNumParams;
    unsigned int params[PARAMS_MAX];

    unsigned int lambda_node = gNodes[node].mLeft;

    /// go ///
    if(!compile(lambda_node, info)) {
        return FALSE;
    }

    sNodeType* lambda_type = info->type;

    LVALUE lambda_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    sNodeType* param_types[PARAMS_MAX];

    int i;
    for(i=0; i<num_params; i++) {
        params[i] = gNodes[node].uValue.sFunctionCall.mParams[i];
        
        if(!compile(params[i], info)) {
            return FALSE;
        }

        param_types[i] = info->type;

        LVALUE param = *get_value_from_stack(-1);
    }

    /// convert param type ///
    LLVMValueRef llvm_params[PARAMS_MAX];
    LVALUE* lvalue_params[PARAMS_MAX];

    for(i=0; i<num_params; i++) {
        sNodeType* left_type = lambda_type->mParamTypes[i];
        sNodeType* right_type = param_types[i];

        LVALUE* param = get_value_from_stack(-num_params+i);

        lvalue_params[i] = param;
        
        if(left_type == NULL || right_type == NULL) {
            compile_err_msg(info, "null lambda type");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(auto_cast_posibility(left_type, right_type)) 
        {
            if(!cast_right_type_to_left_type(left_type, &right_type, param, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        llvm_params[i] = param->value;
    }

    dec_stack_ptr(num_params, info);

    if(type_identify_with_class_name(lambda_type->mResultType, "void"))
    {
        LLVMBuildCall(gBuilder, lambda_value.value, llvm_params, num_params, "fun_result");

        info->type = clone_node_type(lambda_type->mResultType);
    }
    else {
        sNodeType* result_type = clone_node_type(lambda_type->mResultType);

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildCall(gBuilder, lambda_value.value, llvm_params, num_params, "fun_result");
        llvm_value.type = result_type;
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        info->type = result_type;


        if(result_type->mHeap) {
            append_object_to_right_values(llvm_value.value, result_type, info);
        }
    }

    return TRUE;
}

unsigned int sNodeTree_create_dereffernce(unsigned int left_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDerefference;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_dereffernce(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    sNodeType* derefference_type = clone_node_type(left_type);

    if(derefference_type->mPointerNum == 0) {
        compile_err_msg(info, "This is not pointer type1(%s)", CLASS_NAME(derefference_type->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    derefference_type->mPointerNum--;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildLoad(gBuilder, lvalue.value, "derefference_value");
    llvm_value.type = derefference_type;
    llvm_value.address = lvalue.value;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = derefference_type;

    return TRUE;
}

unsigned int sNodeTree_create_reffernce(unsigned int left_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeRefference;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_reffernce(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(lvalue.address == NULL) {
        compile_err_msg(info, "Can't get address of this value on & operator");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    sNodeType* left_type = info->type;

    sNodeType* refference_type = clone_node_type(left_type);

    refference_type->mPointerNum++;

    LVALUE llvm_value;
    llvm_value.value = lvalue.address;
    llvm_value.type = refference_type;
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = refference_type;

    return TRUE;
}

unsigned int sNodeTree_create_clone(unsigned int left, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeClone;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_clone(unsigned int node, sCompileInfo* info)
{
    return TRUE;
}

unsigned int sNodeTree_create_load_array_element(unsigned int array, unsigned int index_node[], int num_dimention, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadElement;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sLoadElement.mArrayDimentionNum = num_dimention;
    int i;
    for(i=0; i<num_dimention; i++) {
        gNodes[node].uValue.sLoadElement.mIndex[i] = index_node[i];
    }

    gNodes[node].mLeft = array;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = index_node[0];

    return node;
}

static BOOL compile_load_element(unsigned int node, sCompileInfo* info)
{
    int num_dimention = gNodes[node].uValue.sLoadElement.mArrayDimentionNum;
    int i;
    unsigned int index_node[ARRAY_DIMENTION_MAX];
    for(i=0; i<num_dimention; i++) {
        index_node[i] = gNodes[node].uValue.sLoadElement.mIndex[i];
    }
    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    sVar* var = lvalue.var;

    if(left_type->mArrayDimentionNum == 0 && left_type->mPointerNum == 0 && left_type->mDynamicArrayNum == 0)
    {
        compile_err_msg(info, "comelang can't get an element from this type.");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// compile middle node ///
    LVALUE rvalue[ARRAY_DIMENTION_MAX];
    for(i=0; i<num_dimention; i++) {
        unsigned int mnode = index_node[i];

        if(!compile(mnode, info)) {
            return FALSE;
        }

        sNodeType* middle_type = info->type;

        rvalue[i] = *get_value_from_stack(-1);

        sNodeType* int_type = create_node_type_with_class_name("int");

        if(!cast_right_type_to_left_type(int_type, &middle_type, &rvalue[i], info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(!type_identify_with_class_name(middle_type, "int")) {
            compile_err_msg(info, "Type of index should be number");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    /// generate code ///
    sNodeType* var_type = clone_node_type(left_type);

    if(var_type->mDynamicArrayNum != 0) {
        var_type->mArrayDimentionNum = 0;
    }
    else if(var_type->mArrayDimentionNum > 0) {
        var_type->mArrayDimentionNum-=num_dimention;
    }
    else {
        var_type->mPointerNum--;
    }

    //if(var_type->mPointerNum == 0) {
        var_type->mHeap = FALSE;
    //}

    /// go ///
    if(left_type->mArrayDimentionNum > num_dimention) {
        int i;
        LLVMValueRef lvalue2 = lvalue.address;

        LLVMValueRef load_element_addresss = lvalue2;

        LLVMValueRef indices[left_type->mArrayDimentionNum+1];

        int j;
        for(j=0; j<left_type->mArrayDimentionNum-num_dimention; j++) {
            LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");
            indices[j] = LLVMConstInt(llvm_type, 0, FALSE);
        }
        int k=0;
        for(; j<left_type->mArrayDimentionNum; j++, k++) {
            indices[j] = rvalue[k].value;
        }
        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, left_type->mArrayDimentionNum, "gep");

        for(j=0; j<left_type->mArrayDimentionNum; j++) {
            LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");
            indices[j] = LLVMConstInt(llvm_type, 0, FALSE);
        }
        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, left_type->mArrayDimentionNum, "gep2");

        sNodeType* var_type3 = clone_node_type(var_type);
        var_type3->mPointerNum -= num_dimention;
        var_type3->mPointerNum+=2;
        var_type3->mArrayDimentionNum = 0;


        if(var_type3->mPointerNum == 0) {
            LLVMValueRef element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "element");

            LVALUE llvm_value;
            llvm_value.value = element_value;
            llvm_value.type = clone_node_type(var_type);
            llvm_value.address = load_element_addresss;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            dec_stack_ptr(1+num_dimention, info);
            push_value_to_stack_ptr(&llvm_value, info);
        }
        else {
            LLVMTypeRef llvm_var_type2 = create_llvm_type_from_node_type(var_type3);
            load_element_addresss = LLVMBuildCast(gBuilder, LLVMBitCast, load_element_addresss, llvm_var_type2, "array_cast");
            LLVMValueRef element_value = load_element_addresss;

            LVALUE llvm_value;
            llvm_value.value = element_value;
            llvm_value.type = clone_node_type(var_type);
            llvm_value.address = load_element_addresss;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            dec_stack_ptr(1+num_dimention, info);
            push_value_to_stack_ptr(&llvm_value, info);
        }
    }
    else if(left_type->mArrayDimentionNum == 1 || left_type->mDynamicArrayNum != 0) {
        sNodeType* var_type2 = clone_node_type(var_type);
        var_type2->mPointerNum++;

        LLVMTypeRef llvm_var_type = create_llvm_type_from_node_type(var_type2);

        LLVMValueRef lvalue2 = LLVMBuildCast(gBuilder, LLVMBitCast, lvalue.address, llvm_var_type, "array_cast");
        LLVMValueRef load_element_addresss = LLVMBuildGEP(gBuilder, lvalue2, &rvalue[0].value, 1, "gep");

        LLVMValueRef element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "element");

        LVALUE llvm_value;

        llvm_value.value = element_value;
        llvm_value.type = clone_node_type(var_type);
        llvm_value.address = load_element_addresss;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1+num_dimention, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(var_type);
    }
    else if(left_type->mArrayDimentionNum == 2) {
        LLVMValueRef lvalue2 = lvalue.address;

        LLVMValueRef load_element_addresss = lvalue2;

        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

        LLVMValueRef indices[2];

        indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
        indices[1] = rvalue[0].value;
        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, 2, "gep");

        indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
        indices[1] = rvalue[1].value;
        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, 2, "gep2");

        sNodeType* var_type3 = clone_node_type(var_type);
        var_type3->mPointerNum -= num_dimention;
        var_type3->mPointerNum+=2;
        var_type3->mArrayDimentionNum = 0;

        if(var_type3->mPointerNum == 0) {
            LLVMValueRef element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "element");

            LVALUE llvm_value;

            llvm_value.value = element_value;
            llvm_value.type = clone_node_type(var_type);
            llvm_value.address = load_element_addresss;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            dec_stack_ptr(1+num_dimention, info);
            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(var_type);
        }
        else {
            LLVMTypeRef llvm_var_type2 = create_llvm_type_from_node_type(var_type3);

            load_element_addresss = LLVMBuildCast(gBuilder, LLVMBitCast, load_element_addresss, llvm_var_type2, "array_cast");
            LLVMValueRef element_value = load_element_addresss;

            LVALUE llvm_value;

            llvm_value.value = element_value;
            llvm_value.type = clone_node_type(var_type);
            llvm_value.address = load_element_addresss;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            dec_stack_ptr(1+num_dimention, info);
            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(var_type);
        }
    }
    else if(left_type->mArrayDimentionNum == 3) {
        LLVMValueRef lvalue2 = lvalue.address;

        LLVMValueRef load_element_addresss = lvalue2;

        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

        LLVMValueRef indices[2];

        indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
        indices[1] = rvalue[0].value;
        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, 2, "gep");

        indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
        indices[1] = rvalue[1].value;

        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, 2, "gep2");

        indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
        indices[1] = rvalue[2].value;

        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, 2, "gep3");

        sNodeType* var_type3 = clone_node_type(var_type);

        var_type3->mPointerNum -= num_dimention;
        var_type3->mPointerNum+=2;
        var_type3->mArrayDimentionNum = 0;

        if(var_type3->mPointerNum == 0) {
            LLVMValueRef element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "element");

            LVALUE llvm_value;

            llvm_value.value = element_value;
            llvm_value.type = clone_node_type(var_type);
            llvm_value.address = load_element_addresss;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            dec_stack_ptr(1+num_dimention, info);
            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(var_type);
        }
        else {
            //LLVMTypeRef llvm_var_type2 = create_llvm_type_from_node_type(var_type3);

            //load_element_addresss = LLVMBuildCast(gBuilder, LLVMBitCast, load_element_addresss, llvm_var_type2, "array_cast");
            LLVMValueRef element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "element");
            //LLVMValueRef element_value = load_element_addresss;

            LVALUE llvm_value;

            llvm_value.value = element_value;
            llvm_value.type = clone_node_type(var_type);
            llvm_value.address = load_element_addresss;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            dec_stack_ptr(1+num_dimention, info);
            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(var_type);
        }
    }
    else {
        compile_err_msg(info, "come lang supports under 3 dimention array");
        return FALSE;
    }
/*
    else if(left_type->mArrayDimentionNum > 3) {
        int i;
        LLVMValueRef lvalue2 = lvalue.address;

        LLVMValueRef load_element_addresss = lvalue2;

        LLVMValueRef indices[left_type->mArrayDimentionNum+1];

        int j;
        for(j=0; j<left_type->mArrayDimentionNum-num_dimention; j++) {
            LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");
            indices[j] = LLVMConstInt(llvm_type, 0, FALSE);
        }
        int k=0;
        for(; j<left_type->mArrayDimentionNum; j++, k++) {
            indices[j] = rvalue[k].value;
        }
        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, left_type->mArrayDimentionNum, "gep");

        for(j=0; j<left_type->mArrayDimentionNum; j++) {
            LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");
            indices[j] = LLVMConstInt(llvm_type, 0, FALSE);
        }
        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, left_type->mArrayDimentionNum, "gep");

        sNodeType* var_type3 = clone_node_type(var_type);
        var_type3->mPointerNum -= num_dimention;
        var_type3->mPointerNum+=2;
        var_type3->mArrayDimentionNum = 0;

        LLVMTypeRef llvm_var_type2 = create_llvm_type_from_node_type(var_type3);

        LLVMValueRef element_value;
        if(var_type3->mPointerNum == 0) {
            element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "element");
        }
        else {
            load_element_addresss = LLVMBuildCast(gBuilder, LLVMBitCast, load_element_addresss, llvm_var_type2, "array_cast");
            element_value = load_element_addresss;
        }

        LVALUE llvm_value;
        llvm_value.value = element_value;
        llvm_value.type = clone_node_type(var_type);
        llvm_value.address = load_element_addresss;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1+num_dimention, info);
        push_value_to_stack_ptr(&llvm_value, info);
    }
    else {
        LLVMValueRef lvalue2 = lvalue.value;

        LLVMValueRef load_element_addresss = lvalue2;

        int pointer_num = left_type->mPointerNum;

        LLVMValueRef element_value = NULL;
        for(i=0; i<num_dimention; i++) {
            load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, &rvalue[i].value, 1, "element_address");

            element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "elementX");
            if(i < num_dimention-1) {
                load_element_addresss = element_value;
            }
        }

        var_type->mPointerNum -= num_dimention -1;

        LVALUE llvm_value;
        llvm_value.value = element_value;
        llvm_value.type = clone_node_type(var_type);
        llvm_value.address = load_element_addresss;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1+num_dimention, info);
        push_value_to_stack_ptr(&llvm_value, info);
    }
*/

    return TRUE;
}

unsigned int sNodeTree_create_store_element(unsigned int array, unsigned int index_node[], int num_dimention, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreElement;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sStoreElement.mArrayDimentionNum = num_dimention;
    int i;
    for(i=0; i<num_dimention; i++) {
        gNodes[node].uValue.sStoreElement.mIndex[i] = index_node[i];
    }

    gNodes[node].mLeft = array;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = index_node[0];

    return node;
}

BOOL compile_store_element(unsigned int node, sCompileInfo* info)
{
    int num_dimention = gNodes[node].uValue.sStoreElement.mArrayDimentionNum;
    int i;
    unsigned int index_node[ARRAY_DIMENTION_MAX];
    for(i=0; i<num_dimention; i++) {
        index_node[i] = gNodes[node].uValue.sStoreElement.mIndex[i];
    }

    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    if(left_type->mArrayDimentionNum == 0 && left_type->mPointerNum == 0 && left_type->mDynamicArrayNum == 0)
    {
        compile_err_msg(info, "comelang can't get an element from this type.");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// compile middle node ///
    LVALUE mvalue[ARRAY_DIMENTION_MAX];

    for(i=0; i<num_dimention; i++) {
        unsigned int mnode = index_node[i];

        if(!compile(mnode, info)) {
            return FALSE;
        }

        sNodeType* middle_type = info->type;

        LVALUE llvm_value = *get_value_from_stack(-1);

        sNodeType* int_type = create_node_type_with_class_name("int");

        if(!cast_right_type_to_left_type(int_type, &middle_type, &llvm_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(!type_identify_with_class_name(middle_type, "int")) {
            compile_err_msg(info, "Type of index should be number");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        mvalue[i] = *get_value_from_stack(-1);
    }

    /// compile right node ///
    unsigned int rnode = gNodes[node].mRight;

    if(!compile(rnode, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);

    sNodeType* var_type = clone_node_type(left_type);

    if(var_type->mDynamicArrayNum !=0 ) {
        var_type->mArrayDimentionNum = 0;
        var_type->mDynamicArrayNum = 0;
        left_type->mArrayDimentionNum = 1;
    }
    else if(var_type->mArrayDimentionNum > 0) {
        var_type->mArrayDimentionNum--;
        //var_type->mPointerNum++;
    }
    else {
        var_type->mPointerNum--;
    }
    var_type->mHeap = right_type->mHeap;

    if(auto_cast_posibility(var_type, right_type)) {
        if(!cast_right_type_to_left_type(var_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    if(!substitution_posibility(var_type, right_type, info)) 
    {
        compile_err_msg(info, "The different type between left type and right type, store element");
        show_node_type(var_type);
        show_node_type(right_type);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    /// generate code ///
    if(left_type->mArrayDimentionNum == 1) {
        sNodeType* var_type2 = clone_node_type(var_type);
        var_type2->mPointerNum++;

        LLVMTypeRef llvm_var_type = create_llvm_type_from_node_type(var_type2);

        LLVMValueRef lvalue2 = LLVMBuildCast(gBuilder, LLVMBitCast, lvalue.address, llvm_var_type, "array_cast");
        LLVMValueRef load_element_addresss = LLVMBuildGEP(gBuilder, lvalue2, &mvalue[0].value, 1, "gep");

        LLVMBuildStore(gBuilder, rvalue.value, load_element_addresss);

        dec_stack_ptr(2+num_dimention, info);
        push_value_to_stack_ptr(&rvalue, info);

        info->type = clone_node_type(right_type);
    }
    else if(left_type->mArrayDimentionNum == 2) {
        LLVMValueRef load_element_addresss = lvalue.address;

        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

        LLVMValueRef indices[2];

        indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
        indices[1] = mvalue[0].value;

        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, 2, "gep");

        indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
        indices[1] = mvalue[1].value;

        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, 2, "gep2");

        sNodeType* var_type3 = clone_node_type(var_type);
        var_type3->mPointerNum = 1;
        var_type3->mArrayDimentionNum = 0;

        LLVMBuildStore(gBuilder, rvalue.value, load_element_addresss);

        dec_stack_ptr(2+num_dimention, info);
        push_value_to_stack_ptr(&rvalue, info);

        info->type = clone_node_type(right_type);
    }
    else if(left_type->mArrayDimentionNum == 3) {
        LLVMValueRef load_element_addresss = lvalue.address;

        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

        LLVMValueRef indices[2];

        indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
        indices[1] = mvalue[0].value;

        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, 2, "gep");

        indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
        indices[1] = mvalue[1].value;

        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, 2, "gep2");

        indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
        indices[1] = mvalue[2].value;

        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, 2, "gep3");

        sNodeType* var_type3 = clone_node_type(var_type);
        var_type3->mPointerNum = 1;
        var_type3->mArrayDimentionNum = 0;

        LLVMBuildStore(gBuilder, rvalue.value, load_element_addresss);

        dec_stack_ptr(2+num_dimention, info);
        push_value_to_stack_ptr(&rvalue, info);

        info->type = clone_node_type(right_type);
    }
    else {
        compile_err_msg(info, "come lang supports under 3 array dimention");
        return FALSE;
    }

    return TRUE;
}

unsigned int sNodeTree_create_character_value(char c, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeChar;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].uValue.mCharValue = c;

    return node;
}

BOOL compile_char_value(unsigned int node, sCompileInfo* info)
{
    char c = gNodes[node].uValue.mCharValue;

    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("char");

    LVALUE llvm_value;
    llvm_value.value = LLVMConstInt(llvm_type, c, FALSE);
    llvm_value.type = create_node_type_with_class_name("char");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("char");

    return TRUE;
}

unsigned int sNodeTree_create_cast(sNodeType* left_type, unsigned int left_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCast;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    gNodes[node].uValue.mType = left_type;

    return node;
}

BOOL compile_cast(unsigned int node, sCompileInfo* info)
{
    sNodeType* right_type = gNodes[node].uValue.mType;

    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

/*
    if(cast_posibility(left_type, right_type)) {
*/
        if(!cast_right_type_to_left_type(right_type, &left_type, &lvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
//    }

    push_value_to_stack_ptr(&lvalue, info);

    info->type = clone_node_type(lvalue.type);

    return TRUE;
}

unsigned int sNodeTree_create_impl(unsigned int* nodes, int num_nodes, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeImpl;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    memcpy(gNodes[node].uValue.sImpl.mNodes, nodes, sizeof(unsigned int)*num_nodes);
    gNodes[node].uValue.sImpl.mNumNodes = num_nodes;

    return node;
}

static BOOL compile_impl(unsigned int node, sCompileInfo* info)
{

    return TRUE;
}

unsigned int sNodeTree_create_typedef(char* name, sNodeType* node_type, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeTypeDef;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    add_typedef(name, clone_node_type(node_type));

    return node;
}

static BOOL compile_typedef(unsigned int node, sCompileInfo* info)
{
    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_create_left_shift(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLeftShift;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_left_shift(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildShl(gBuilder, lvalue.value, rvalue.value, "lshifttmp");
    llvm_value.type = clone_node_type(right_type);
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = llvm_value.type;
    
    return TRUE;
}

unsigned int sNodeTree_create_right_shift(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeRightShift;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_right_shift(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildAShr(gBuilder, lvalue.value, rvalue.value, "rshifttmp");
    llvm_value.type = clone_node_type(right_type);
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = llvm_value.type;

    return TRUE;
}

unsigned int sNodeTree_create_and(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAnd;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_and(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildAnd(gBuilder, lvalue.value, rvalue.value, "andtmp");
    llvm_value.type = clone_node_type(right_type);
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = llvm_value.type;

    return TRUE;
}

unsigned int sNodeTree_create_xor(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeXor;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_xor(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildXor(gBuilder, lvalue.value, rvalue.value, "xortmp");
    llvm_value.type = clone_node_type(right_type);
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = llvm_value.type;

    return TRUE;
}

unsigned int sNodeTree_create_or(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeOr;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = middle;

    return node;
}

static BOOL compile_or(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }
    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    int right_node = gNodes[node].mRight;
    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildOr(gBuilder, lvalue.value, rvalue.value, "ortmp");
    llvm_value.type = clone_node_type(right_type);
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(2, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = llvm_value.type;

    return TRUE;
}

unsigned int sNodeTree_create_return(unsigned int left, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeReturn;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_return(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;

    if(left_node != 0) {
        if(!compile(left_node, info)) {
            return FALSE;
        }

        LVALUE llvm_value = *get_value_from_stack(-1);

        if(info->in_inline_function) {
            free_objects_on_return(info->function_node_block, info, llvm_value.address, FALSE);
            LLVMBuildStore(gBuilder, llvm_value.value, info->inline_result_variable);
        }
        else {
            free_objects_on_return(info->function_node_block, info, llvm_value.address, TRUE);
            LLVMBuildRet(gBuilder, llvm_value.value);
        }

        if(llvm_value.type->mHeap) {
            remove_object_from_right_values(llvm_value.value);
        }

        dec_stack_ptr(1, info);
    }
    else {
        if(info->in_inline_function) {
            free_objects_on_return(info->function_node_block, info, NULL, FALSE);
        }
        else {
            free_objects_on_return(info->function_node_block, info, NULL, TRUE);
        }
        LLVMBuildRet(gBuilder, NULL);

        info->type = create_node_type_with_class_name("void");
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_create_sizeof(sNodeType* node_type, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeSizeOf;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sSizeOf.mType = clone_node_type(node_type);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_sizeof(unsigned int node, sCompileInfo* info)
{
    sNodeType* node_type = gNodes[node].uValue.sSizeOf.mType;
    sNodeType* node_type2 = clone_node_type(node_type);

    //LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type2);

    uint64_t alloc_size = get_size_from_node_type(node_type2);

    LLVMTypeRef long_type = create_llvm_type_with_class_name("long");
    LLVMValueRef alloc_size_value = LLVMConstInt(long_type, alloc_size, FALSE);

    /// result ///
    LVALUE llvm_value;
    //llvm_value.value = LLVMSizeOf(llvm_type);
    llvm_value.value = alloc_size_value;
    llvm_value.type = create_node_type_with_class_name("long");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("long");

    return TRUE;
}

unsigned int sNodeTree_create_sizeof_expression(unsigned int lnode, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeSizeOfExpression;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = lnode;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_sizeof_expression(unsigned int node, sCompileInfo* info)
{
    unsigned int lnode = gNodes[node].mLeft;

    BOOL no_output = info->no_output;
    info->no_output = TRUE;

    if(!compile(lnode, info)) {
        info->no_output = no_output;
        return FALSE;
    }

    info->no_output = no_output;

    sNodeType* node_type = clone_node_type(info->type);

    LVALUE llvm_value = *get_value_from_stack(-1);

    dec_stack_ptr(1, info);

    uint64_t alloc_size = get_size_from_node_type(llvm_value.type);

    LLVMTypeRef long_type = create_llvm_type_with_class_name("long");
    LLVMValueRef value = LLVMConstInt(long_type, alloc_size, FALSE);

#ifdef __32BIT_CPU__
    LVALUE llvm_value2;
    llvm_value2.value = value;
    llvm_value2.type = create_node_type_with_class_name("int");
    llvm_value2.address = NULL;
    llvm_value2.var = NULL;
    llvm_value2.binded_value = FALSE;
    llvm_value2.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value2, info);

    info->type = create_node_type_with_class_name("int");
#else
    LVALUE llvm_value2;
    llvm_value2.value = value;
    llvm_value2.type = create_node_type_with_class_name("long");
    llvm_value2.address = NULL;
    llvm_value2.var = NULL;
    llvm_value2.binded_value = FALSE;
    llvm_value2.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value2, info);

    info->type = create_node_type_with_class_name("long");
#endif

    return TRUE;
}

unsigned int sNodeTree_create_alignof(sNodeType* node_type, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAlignOf;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sAlignOf.mType = clone_node_type(node_type);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_alignof(unsigned int node, sCompileInfo* info)
{
    sNodeType* node_type = gNodes[node].uValue.sSizeOf.mType;
    sNodeType* node_type2 = clone_node_type(node_type);

    LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type2);

    /// result ///
    LVALUE llvm_value;
    llvm_value.value = LLVMAlignOf(llvm_type);
    llvm_value.type = create_node_type_with_class_name("long");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("long");

    return TRUE;
}

unsigned int sNodeTree_create_alignof_expression(unsigned int lnode, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAlignOfExpression;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = lnode;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_alignof_expression(unsigned int node, sCompileInfo* info)
{
    unsigned int lnode = gNodes[node].mLeft;

    BOOL no_output = info->no_output;
    info->no_output = TRUE;

    if(!compile(lnode, info)) {
        info->no_output = no_output;
        return FALSE;
    }

    info->no_output = no_output;

    sNodeType* node_type = clone_node_type(info->type);

    LVALUE llvm_value = *get_value_from_stack(-1);

    dec_stack_ptr(1, info);

    LLVMTypeRef llvm_type = create_llvm_type_from_node_type(llvm_value.type);


    LLVMValueRef value = LLVMAlignOf(llvm_type);

#ifdef __32BIT_CPU__
    LVALUE llvm_value2;
    llvm_value2.value = value;
    llvm_value2.type = create_node_type_with_class_name("int");
    llvm_value2.address = NULL;
    llvm_value2.var = NULL;
    llvm_value2.binded_value = FALSE;
    llvm_value2.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value2, info);

    info->type = create_node_type_with_class_name("int");
#else
    LVALUE llvm_value2;
    llvm_value2.value = value;
    llvm_value2.type = create_node_type_with_class_name("long");
    llvm_value2.address = NULL;
    llvm_value2.var = NULL;
    llvm_value2.binded_value = FALSE;
    llvm_value2.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value2, info);

    info->type = create_node_type_with_class_name("long");
#endif

    return TRUE;
}


unsigned int sNodeTree_create_nodes(unsigned int* nodes, int num_nodes, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeNodes;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    memcpy(gNodes[node].uValue.sNodes.mNodes, nodes, sizeof(unsigned int)*NODES_MAX);
    gNodes[node].uValue.sNodes.mNumNodes = num_nodes;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_nodes(unsigned int node, sCompileInfo* info)
{
    unsigned int* nodes = gNodes[node].uValue.sNodes.mNodes;
    int num_nodes = gNodes[node].uValue.sNodes.mNumNodes;

    int stack_num_before = info->stack_num;

    int i;
    for(i=0; i<num_nodes; i++) {
        unsigned int node = nodes[i];

        xstrncpy(info->sname, gNodes[node].mSName, PATH_MAX);
        info->sline = gNodes[node].mLine;

        if(gNCDebug) {
            setCurrentDebugLocation(info->sline, info);
        }

        if(!compile(node, info)) {
            return FALSE;
        }

        arrange_stack(info, stack_num_before);
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_create_load_function(char* fun_name, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadFunction;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sLoadFunction.mFunName, fun_name, VAR_NAME_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_load_function(unsigned int node, sCompileInfo* info)
{
    char* fun_name = gNodes[node].uValue.sLoadFunction.mFunName;

    sFunction* fun = get_function_from_table(fun_name);

    if(fun == NULL) {
        compile_err_msg(info, "undeclared function %s\n", fun_name);
        return FALSE;
    }
    
    sNodeType* lambda_type = create_node_type_with_class_name("lambda");

    int num_params = fun->mNumParams;

    int i;
    for(i=0; i<num_params; i++) {
        sNodeType* param_type = fun->mParamTypes[i];

        lambda_type->mParamTypes[i] = param_type;
    }

    lambda_type->mResultType = clone_node_type(fun->mResultType);
    lambda_type->mNumParams = num_params;

    LVALUE llvm_value;
    llvm_value.value = fun->mLLVMFunction;
    llvm_value.type = lambda_type;
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = lambda_type;

    return TRUE;
}

unsigned int sNodeTree_create_array_with_initialization(char* name, int num_initialize_array_value, unsigned int* initialize_array_value, unsigned int left_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeArrayWithInitialization;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sArrayWithInitialization.mVarName, name, VAR_NAME_MAX);
    gNodes[node].uValue.sArrayWithInitialization.mNumInitializeArrayValue = num_initialize_array_value;
    memcpy(gNodes[node].uValue.sArrayWithInitialization.mInitializeArrayValue, initialize_array_value, sizeof(unsigned int)*INIT_ARRAY_MAX);

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_array_with_initialization(unsigned int node, sCompileInfo* info)
{
    char* var_name = gNodes[node].uValue.sArrayWithInitialization.mVarName;
    int num_initialize_array_value = gNodes[node].uValue.sArrayWithInitialization.mNumInitializeArrayValue;
    unsigned int* initialize_array_value = gNodes[node].uValue.sArrayWithInitialization.mInitializeArrayValue;

    /// compile node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sVar* var = get_variable_from_table(info->pinfo->lv_table, var_name);

    if(var == NULL) {
        compile_err_msg(info, "undeclared variable %s(4)", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    sNodeType* var_type = var->mType;

    LLVMValueRef alloca_value = var->mLLVMValue;

    if(var_type->mArrayDimentionNum == 1 && type_identify_with_class_name(var_type, "char") && var_type->mPointerNum == 0
         && num_initialize_array_value == 1 && gNodes[initialize_array_value[0]].mNodeType == kNodeTypeCString) 
    {
        unsigned int node = initialize_array_value[0];

        char* str = gNodes[node].uValue.sString.mString;

        if(strlen(str)+1 >= INIT_ARRAY_MAX) {
            compile_err_msg(info, "invalid array initializer");
            info->err_num++;

            info->type = create_node_type_with_class_name("int");
            return TRUE;
        }

        int i;
        for(i=0; i<strlen(str); i++) {
            initialize_array_value[i] = sNodeTree_create_character_value(str[i], info->pinfo);
        }
        initialize_array_value[i] = sNodeTree_create_character_value('\0', info->pinfo);

        num_initialize_array_value = strlen(str)+1;
    }

    if(var_type->mArrayDimentionNum == 1) {
        sNodeType* element_node_type = clone_node_type(var_type);
        element_node_type->mArrayDimentionNum = 0;
        LLVMTypeRef llvm_element_type = create_llvm_type_from_node_type(element_node_type);

        /// zero initializer ///
        LLVMValueRef values[INIT_ARRAY_MAX];

        int i;
        for(i=0; i<num_initialize_array_value; i++) {
            unsigned int node = initialize_array_value[i];

            if(!compile(node, info)) {
                return FALSE;
            }


            LVALUE llvm_value = *get_value_from_stack(-1);

            dec_stack_ptr(1, info);

            values[i] = llvm_value.value;
        }

        LLVMValueRef value = LLVMConstArray(llvm_element_type, values, num_initialize_array_value);
        LLVMSetInitializer(alloca_value, value);
    }
    else if(var_type->mArrayDimentionNum == 2) {
        /// zero initializer ///
        LLVMValueRef values[var_type->mArrayNum[0]][INIT_ARRAY_MAX];

        int i;
        for(i=0; i<num_initialize_array_value; i++) {
            unsigned int node = initialize_array_value[i];

            if(!compile(node, info)) {
                return FALSE;
            }


            LVALUE llvm_value = *get_value_from_stack(-1);

            dec_stack_ptr(1, info);

            int n = i / var_type->mArrayNum[1];
            int m = i % var_type->mArrayNum[1];

            values[n][m] = llvm_value.value;
        }

        LLVMValueRef array_value[INIT_ARRAY_MAX];
        for(i=0; i<var_type->mArrayNum[0]; i++) {
            sNodeType* element_node_type = clone_node_type(var_type);
            element_node_type->mArrayDimentionNum = 0;
            LLVMTypeRef llvm_element_type = create_llvm_type_from_node_type(element_node_type);

            array_value[i] = LLVMConstArray(llvm_element_type, values[i], var_type->mArrayNum[1]);
        }

        sNodeType* element_node_type = clone_node_type(var_type);
        element_node_type->mArrayDimentionNum = 1;
        element_node_type->mArrayNum[0] = element_node_type->mArrayNum[1];
        LLVMTypeRef llvm_element_type = create_llvm_type_from_node_type(element_node_type);

        LLVMValueRef value = LLVMConstArray(llvm_element_type, array_value, var_type->mArrayNum[0]);

        LLVMSetInitializer(alloca_value, value);
    }
    else if(var_type->mArrayDimentionNum == 3) {
        /// zero initializer ///
        LLVMValueRef values[var_type->mArrayNum[0]][var_type->mArrayNum[1]][INIT_ARRAY_MAX];

        int i;
        for(i=0; i<num_initialize_array_value; i++) {
            unsigned int node = initialize_array_value[i];

            if(!compile(node, info)) {
                return FALSE;
            }


            LVALUE llvm_value = *get_value_from_stack(-1);

            dec_stack_ptr(1, info);

            int n = var_type->mArrayNum[1]*var_type->mArrayNum[2];

            int a = i/n;
            int b = (i/var_type->mArrayNum[2])%var_type->mArrayNum[1];
            int c = i%var_type->mArrayNum[2];

            values[a][b][c] = llvm_value.value;
        }

        LLVMValueRef array_array_value[var_type->mArrayNum[0]];
        int j;
        for(j=0; j<var_type->mArrayNum[0]; j++) {
            LLVMValueRef array_value[INIT_ARRAY_MAX];

            for(i=0; i<var_type->mArrayNum[1]; i++) {
                sNodeType* element_node_type = clone_node_type(var_type);
                element_node_type->mArrayDimentionNum = 0;
                LLVMTypeRef llvm_element_type = create_llvm_type_from_node_type(element_node_type);

                array_value[i] = LLVMConstArray(llvm_element_type, values[j][i], var_type->mArrayNum[2]);
            }

            sNodeType* element_node_type = clone_node_type(var_type);
            element_node_type->mArrayDimentionNum = 1;
            element_node_type->mArrayNum[0] = element_node_type->mArrayNum[2];
            LLVMTypeRef llvm_element_type = create_llvm_type_from_node_type(element_node_type);

            array_array_value[j] = LLVMConstArray(llvm_element_type, array_value, var_type->mArrayNum[1]);
        }

        sNodeType* element_node_type = clone_node_type(var_type);
        element_node_type->mArrayDimentionNum = 2;
        element_node_type->mArrayNum[0] = element_node_type->mArrayNum[1];
        element_node_type->mArrayNum[1] = element_node_type->mArrayNum[2];
        LLVMTypeRef llvm_element_type = create_llvm_type_from_node_type(element_node_type);
        LLVMValueRef value = LLVMConstArray(llvm_element_type, array_array_value, var_type->mArrayNum[0]);
        LLVMSetInitializer(alloca_value, value);
    }

    return TRUE;
}

unsigned int sNodeTree_create_struct_with_initialization(char* name, int num_initialize_array_value, unsigned int* initialize_array_value, unsigned int left_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStructWithInitialization;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sArrayWithInitialization.mVarName, name, VAR_NAME_MAX);
    gNodes[node].uValue.sArrayWithInitialization.mNumInitializeArrayValue = num_initialize_array_value;
    memcpy(gNodes[node].uValue.sArrayWithInitialization.mInitializeArrayValue, initialize_array_value, sizeof(unsigned int)*INIT_ARRAY_MAX);

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_struct_with_initialization(unsigned int node, sCompileInfo* info)
{
    compile_err_msg(info, "no support for struct initializer(2)");

    return FALSE;
}

unsigned int sNodeTree_create_normal_block(struct sNodeBlockStruct* node_block, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeNormalBlock;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sNormalBlock.mNodeBlock = node_block;
    gNodes[node].uValue.sNormalBlock.mHeap = FALSE;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_normal_block(unsigned int node, sCompileInfo* info)
{
    struct sNodeBlockStruct* node_block = gNodes[node].uValue.sNormalBlock.mNodeBlock;

    sNodeType* result_type = create_node_type_with_class_name("void");

    if(!compile_block(node_block, info, result_type))
    {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_switch_expression(unsigned int expression_node, int num_switch_expression, MANAGED unsigned int* switch_expression, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeSwitch;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sSwitch.mExpression = expression_node;
    gNodes[node].uValue.sSwitch.mSwitchExpression = MANAGED switch_expression;
    gNodes[node].uValue.sSwitch.mNumSwitchExpression = num_switch_expression;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_switch_expression(unsigned int node, sCompileInfo* info)
{
    unsigned int* switch_expression = gNodes[node].uValue.sSwitch.mSwitchExpression;
    int num_switch_expression = gNodes[node].uValue.sSwitch.mNumSwitchExpression;
    unsigned int expression_node = gNodes[node].uValue.sSwitch.mExpression;
    LLVMBasicBlockRef loop_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "end_block");

    info->loop_end_block[info->num_loop] = loop_end_block;
    info->num_loop++;

    if(info->num_loop >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. switch", info->num_loop);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    void* switch_expression_before = info->switch_expression;
    info->switch_expression = get_value_from_stack(-1)->value;
    sNodeType* switch_expression_type_before = info->switch_expression_type;
    info->switch_expression_type = clone_node_type(get_value_from_stack(-1)->type);
    dec_stack_ptr(1, info);

    info->case_else_block = NULL;

    int i;
    unsigned int node2;
    for(i=0; i<num_switch_expression; i++) {
        int sline = info->sline;
        gNodes[node].mLine = info->sline;
        
        /// compile node ///
        node2 = switch_expression[i];
        
        info->sline = gNodes[node2].mLine;

        if(!compile(node2, info)) {
            info->num_loop--;
            return FALSE;
        }
    }

    LLVMBasicBlockRef case_else_block;
    if(gNodes[node2].mNodeType == kNodeTypeReturn) {
        case_else_block = NULL;
    }
    else {
        case_else_block = (LLVMBasicBlockRef)info->case_else_block;
    }

    if(case_else_block) {
        LLVMBuildBr(gBuilder, case_else_block);

        llvm_change_block(case_else_block, info);
    }

    info->switch_expression = switch_expression_before;
    info->switch_expression_type = switch_expression_type_before;

    LLVMBuildBr(gBuilder, loop_end_block);

    llvm_change_block(loop_end_block, info);

    info->type = create_node_type_with_class_name("void");

    info->case_else_block = NULL;

    info->num_loop--;

    return TRUE;
}

unsigned int sNodeTree_case_expression(unsigned int expression_node, BOOL last_case, BOOL case_after_return, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCase;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sCase.mExpression = expression_node;
    gNodes[node].uValue.sCase.mLastCase = last_case;
    gNodes[node].uValue.sCase.mFirstCase = FALSE;
    gNodes[node].uValue.sCase.mCaseAfterReturn = case_after_return;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_case_expression(unsigned int node, sCompileInfo* info)
{
    unsigned int expression_node = gNodes[node].uValue.sCase.mExpression;
    BOOL first_case = gNodes[node].uValue.sCase.mFirstCase;
    BOOL last_case = gNodes[node].uValue.sCase.mLastCase;
    BOOL case_after_return = gNodes[node].uValue.sCase.mCaseAfterReturn;

    LLVMBasicBlockRef cond_then_block;
    if(first_case) {
        cond_then_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_then_block");
        info->case_then_block = cond_then_block;
    }
    else {
        cond_then_block = (LLVMBasicBlockRef)info->case_then_block;
    }
    LLVMBasicBlockRef cond_else_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_else_block");

    LLVMBasicBlockRef case_else_block = (LLVMBasicBlockRef)info->case_else_block;

    if(case_else_block) {
        if(first_case && !case_after_return) {
            LLVMBuildBr(gBuilder, case_else_block);
        }

        llvm_change_block(case_else_block, info);
    }

    if(expression_node == 0) {
        LLVMBuildBr(gBuilder, cond_then_block);
    }
    else {
        if(!compile(expression_node, info)) {
            return FALSE;
        }

        LVALUE rvalue = *get_value_from_stack(-1);

        dec_stack_ptr(1, info);
        LLVMValueRef lvalue = (LLVMValueRef)info->switch_expression;
        sNodeType* left_type = info->switch_expression_type;

        if(lvalue == NULL) {
            compile_err_msg(info, "No in the switch.");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(auto_cast_posibility(left_type, rvalue.type))
        {
            cast_right_type_to_left_type(left_type, &rvalue.type, &rvalue, info);
        }

        LLVMValueRef conditional_value = LLVMBuildICmp(gBuilder, LLVMIntEQ, lvalue, rvalue.value, "eqtmp");
        LLVMBuildCondBr(gBuilder, conditional_value, cond_then_block, cond_else_block);
    }

    if(last_case) {
        llvm_change_block(cond_then_block, info);
    }

    info->case_else_block = cond_else_block;

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_create_break_expression(sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeBreak;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_break_expression(unsigned int node, sCompileInfo* info)
{
    if(info->num_loop <= 0) {
        compile_err_msg(info, "No in the loop");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMBasicBlockRef loop_end_block = (LLVMBasicBlockRef)info->loop_end_block[info->num_loop-1];
    //info->num_loop--;

    if(info->switch_expression == NULL && info->current_node_block) {
        free_objects_on_return(info->current_node_block, info, NULL, TRUE);
    }
    LLVMBuildBr(gBuilder, loop_end_block);

    LLVMBasicBlockRef after_break = LLVMAppendBasicBlockInContext(gContext, gFunction, "after_break");

    llvm_change_block(after_break, info);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_create_continue_expression(sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeContinue;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_continue_expression(unsigned int node, sCompileInfo* info)
{
    if(info->num_loop2 <= 0) {
        compile_err_msg(info, "No in the loop");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMBasicBlockRef loop_begin_block = (LLVMBasicBlockRef)info->loop_begin_block[info->num_loop2-1];
    info->num_loop2--;

    LLVMBuildBr(gBuilder, loop_begin_block);

    LLVMBasicBlockRef after_continue = LLVMAppendBasicBlockInContext(gContext, gFunction, "after_continue");

    llvm_change_block(after_continue, info);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_label_expression(char* name, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLabel;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sLabel.mName, name, PATH_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_label_expression(unsigned int node, sCompileInfo* info)
{
    char* label_name = gNodes[node].uValue.sLabel.mName;

    LLVMBasicBlockRef block = get_label_from_table(label_name);
    
    if(block == NULL) {
        block = LLVMAppendBasicBlockInContext(gContext, gFunction, label_name);
        if(!add_label_to_table(label_name, block)) {
            fprintf(stderr, "overflow label max\n");
            return FALSE;
        }
    }

    LLVMBuildBr(gBuilder, block);

    llvm_change_block(block, info);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_goto_expression(char* name, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeGoto;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sGoto.mName, name, PATH_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_goto_expression(unsigned int node, sCompileInfo* info)
{
    char* label_name = gNodes[node].uValue.sGoto.mName;

    LLVMBasicBlockRef block = get_label_from_table(label_name);
    
    if(block == NULL) {
        compile_err_msg(info, "no label");

        return FALSE;
    }

    LLVMBuildBr(gBuilder, block);

    LLVMBasicBlockRef block2 = LLVMAppendBasicBlockInContext(gContext, gFunction, "after goto");

    llvm_change_block(block2, info);

    return TRUE;
}

/*
unsigned int sNodeTree_create_is_heap_expression(unsigned int lnode, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIsHeapExpression;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = lnode;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}
*/

unsigned int sNodeTree_create_is_heap(sNodeType* node_type, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIsHeap;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sIsHeap.mType = clone_node_type(node_type);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_is_heap(unsigned int node, sCompileInfo* info)
{
    sNodeType* node_type = gNodes[node].uValue.sIsHeap.mType;
    sNodeType* node_type2 = clone_node_type(node_type);

    BOOL value = node_type2->mHeap && node_type2->mPointerNum > 0;

    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("bool");

    LVALUE llvm_value;
    llvm_value.value = LLVMConstInt(llvm_type, value, FALSE);
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;

    return TRUE;
}

/*
unsigned int sNodeTree_create_class_name_expression(unsigned int lnode, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeClassNameExpression;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = lnode;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}
*/

/*
static BOOL compile_class_name_expression(unsigned int node, sCompileInfo* info)
{
    unsigned int lnode = gNodes[node].mLeft;

    BOOL no_output = info->no_output;
    info->no_output = TRUE;

    if(!compile(lnode, info)) {
        info->no_output = FALSE;
        return FALSE;
    }

    info->no_output = no_output;

    sNodeType* node_type = clone_node_type(info->type);

    dec_stack_ptr(1, info);

    char type_name[1024];
    type_name[0] = '\0';

    create_type_name_from_node_type(type_name, 1024, node_type, FALSE);

    LVALUE llvm_value;
    llvm_value.value = llvm_create_string(type_name);
    llvm_value.type = create_node_type_with_class_name("char*");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("char*");

    return TRUE;
}

    return TRUE;
}
*/

/*
unsigned int sNodeTree_create_class_name(sNodeType* node_type, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeClassName;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sIsHeap.mType = clone_node_type(node_type);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_class_name(unsigned int node, sCompileInfo* info)
{

    return TRUE;
}
*/

unsigned int sNodeTree_create_conditional(unsigned int conditional, unsigned int value1, unsigned int value2, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeConditional;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = conditional;
    gNodes[node].mRight = value1;
    gNodes[node].mMiddle = value2;

    return node;
}

static BOOL compile_conditional(unsigned int node, sCompileInfo* info)
{
    /// compile expression ///
    unsigned int conditional_node = gNodes[node].mLeft;

    if(!compile(conditional_node, info)) 
    {
        return FALSE;
    }

    sNodeType* conditional_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, conditional_type)) 
    {
        if(!cast_right_type_to_left_type(bool_type, &conditional_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    if(!type_identify_with_class_name(conditional_type, "bool")) 
    {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    int compile_time_value = -1;

    if(LLVMIsConstant(conditional_value.value)) {
        compile_time_value = LLVMConstIntGetZExtValue(conditional_value.value);
    }

    LVALUE llvm_value;
    if(compile_time_value != -1) {
        if(compile_time_value) {
            unsigned int value1_node  = gNodes[node].mRight;

            if(!compile(value1_node, info)) 
            {
                return FALSE;
            }
        }
        else {
            unsigned int value2_node  = gNodes[node].mMiddle;

            if(!compile(value2_node, info)) 
            {
                return FALSE;
            }
        }

        if(type_identify_with_class_name(info->type, "void")) {
            memset(&llvm_value, 0, sizeof(LVALUE));
        }
        else {
            llvm_value = *get_value_from_stack(-1);
        }
    }
    else {
        LLVMBasicBlockRef cond_then_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_jump_then");
        LLVMBasicBlockRef cond_else_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_else_block");

        LLVMBasicBlockRef cond_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_end");

        LLVMBuildCondBr(gBuilder, conditional_value.value, cond_then_block, cond_else_block);

        llvm_change_block(cond_then_block, info);

        unsigned int value1_node  = gNodes[node].mRight;

        if(!compile(value1_node, info)) 
        {
            return FALSE;
        }

        LVALUE value1;
        LLVMValueRef result_value;
        int result_value_alignment;
        sNodeType* value1_result_type;
        if(type_identify_with_class_name(info->type, "void")) {
            memset(&value1, 0, sizeof(LVALUE));

            value1_result_type = create_node_type_with_class_name("int");

            LLVMBasicBlockRef this_block = LLVMGetInsertBlock(gBuilder);
            LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(gFunction);
            LLVMValueRef inst = LLVMGetFirstInstruction(entry_block);
            LLVMPositionBuilderBefore(gBuilder, inst);

            LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(value1_result_type);

            result_value = LLVMBuildAlloca(gBuilder, llvm_result_type, "conditional_result_type");

            LLVMPositionBuilderAtEnd(gBuilder, this_block);

            LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");
            LLVMValueRef zero_value = LLVMConstInt(llvm_type, 0, FALSE);

            LLVMBuildStore(gBuilder, zero_value, result_value);
        }
        else {
            LVALUE value1 = *get_value_from_stack(-1);
            dec_stack_ptr(1, info);

            value1_result_type = clone_node_type(info->type);

            LLVMBasicBlockRef this_block = LLVMGetInsertBlock(gBuilder);
            LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(gFunction);
            LLVMValueRef inst = LLVMGetFirstInstruction(entry_block);
            LLVMPositionBuilderBefore(gBuilder, inst);

            LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(value1_result_type);

            result_value = LLVMBuildAlloca(gBuilder, llvm_result_type, "condtional_result_value");

            LLVMPositionBuilderAtEnd(gBuilder, this_block);

            LLVMBuildStore(gBuilder, value1.value, result_value);
        }

        LLVMBuildBr(gBuilder, cond_end_block);

        llvm_change_block(cond_else_block, info);

        unsigned int value2_node  = gNodes[node].mMiddle;

        if(!compile(value2_node, info)) 
        {
            return FALSE;
        }

        LVALUE value2;
        if(type_identify_with_class_name(info->type, "void")) {
            memset(&value2, 0, sizeof(LVALUE));

            sNodeType* value2_result_type = create_node_type_with_class_name("int");

            LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(value2_result_type);

            LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");
            LLVMValueRef zero_value = LLVMConstInt(llvm_type, 0, FALSE);

            if(auto_cast_posibility(value1_result_type, value2_result_type)) 
            {
                if(!cast_right_type_to_left_type(value1_result_type
                                , &value2_result_type, &value2, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            LLVMBuildStore(gBuilder, zero_value, result_value);
        }
        else {
            value2 = *get_value_from_stack(-1);
            dec_stack_ptr(1, info);
            sNodeType* value2_result_type = clone_node_type(info->type);

            if(auto_cast_posibility(value1_result_type, value2_result_type)) 
            {
                if(!cast_right_type_to_left_type(value1_result_type
                                , &value2_result_type, &value2, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            LLVMBuildStore(gBuilder, value2.value, result_value);
        }

        LLVMBuildBr(gBuilder, cond_end_block);

        llvm_change_block(cond_end_block, info);

        llvm_value.value = LLVMBuildLoad(gBuilder, result_value, "conditional_result_value");
        llvm_value.type = clone_node_type(value1_result_type);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        info->type = clone_node_type(value1_result_type);

        push_value_to_stack_ptr(&llvm_value, info);
    }

    return TRUE;
}

unsigned int sNodeTree_create_complement(unsigned int left_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeComplement;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_complement(unsigned int node, sCompileInfo* info)
{
    int expression_node = gNodes[node].mLeft;

    if(!compile(expression_node, info))
    {
        return FALSE;
    }

    sNodeType* left_node_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);
    
    if(type_identify_with_class_name(left_node_type, "char"))
    {
        LVALUE rvalue;

        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("char");
        rvalue.value = LLVMConstInt(llvm_type, (uint8_t)0xFF, FALSE);

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildXor(gBuilder, lvalue.value, rvalue.value, "xortmp");
        llvm_value.type = clone_node_type(left_node_type);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type= left_node_type;
    }
    else if(type_identify_with_class_name(left_node_type, "short"))
    {
        LVALUE rvalue;

        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("short");
        rvalue.value = LLVMConstInt(llvm_type, (uint16_t)0xFFFF, FALSE);

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildXor(gBuilder, lvalue.value, rvalue.value, "xortmp");
        llvm_value.type = clone_node_type(left_node_type);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type= left_node_type;
    }
    else if(type_identify_with_class_name(left_node_type, "int"))
    {
        LVALUE rvalue;

        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");
        rvalue.value = LLVMConstInt(llvm_type, (uint32_t)0xFFFFFFFF, FALSE);

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildXor(gBuilder, lvalue.value, rvalue.value, "xortmp");
        llvm_value.type = clone_node_type(left_node_type);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type= left_node_type;
    }
    else if(type_identify_with_class_name(left_node_type, "long"))
    {
        LVALUE rvalue;

        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("long");
        rvalue.value = LLVMConstInt(llvm_type, (uint64_t)0xFFFFFFFFFFFFFFFF, FALSE);

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildXor(gBuilder, lvalue.value, rvalue.value, "xortmp");
        llvm_value.type = clone_node_type(left_node_type);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type= left_node_type;
    }
    else {
        compile_err_msg(info, "Invalid type for complement operator");
        info->err_num++;
    }

    return TRUE;
}

unsigned int sNodeTree_create_store_value_to_address(unsigned int address_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreAddress;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = address_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_store_address(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    if(left_type->mPointerNum == 0) {
        compile_err_msg(info, "This is not pointer type2(%s)", CLASS_NAME(left_type->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    left_type->mPointerNum--;

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    LLVMValueRef address = lvalue.value;
    LLVMValueRef value = rvalue.value;

    LLVMBuildStore(gBuilder, value, address);

    return TRUE;
}

unsigned int sNodeTree_create_load_adress_value(unsigned int address_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadAddressValue;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = address_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_load_address_value(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    if(left_type->mPointerNum == 0) {
        compile_err_msg(info, "This is not pointer type3(%s)", CLASS_NAME(left_type->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    sNodeType* left_type2 = clone_node_type(left_type);
    left_type2->mPointerNum--;

    LLVMValueRef address = lvalue.value;

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildLoad(gBuilder, address, "load_address_value");
    llvm_value.type = clone_node_type(left_type2);
    llvm_value.address = address;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = clone_node_type(llvm_value.type);

    return TRUE;
}

unsigned int sNodeTree_create_plus_plus(unsigned int left_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypePlusPlus;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_plus_plus(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    BOOL derefference = gNodes[left_node].mNodeType == kNodeTypeDerefference;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = sNodeTree_create_int_value(1, info->pinfo);

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(derefference && left_type->mPointerNum == 0) {
            LLVMValueRef address = lvalue.value;

            LLVMTypeRef llvm_left_type = create_llvm_type_from_node_type(left_type);

            LLVMValueRef left_value = address;
            LLVMTypeRef long_type = create_llvm_type_with_class_name("long");
            LLVMValueRef left_value2 = LLVMBuildCast(gBuilder, LLVMPtrToInt, left_value, long_type, "cast");

            LLVMValueRef right_value;
            if(type_identify_with_class_name(right_type, "long")) {
                right_value = rvalue.value;
            }
            else {
                if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                    right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "sext");
                }
                else {
                    right_value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue.value, long_type, "sext");
                }
            }

            uint64_t alloc_size = get_size_from_node_type(left_type);

            LLVMValueRef alloc_size_value = LLVMConstInt(long_type, alloc_size, FALSE);

            right_value = LLVMBuildMul(gBuilder, right_value, alloc_size_value, "mul");

            LLVMValueRef value = LLVMBuildAdd(gBuilder, left_value2, right_value, "add");
            value = LLVMBuildCast(gBuilder, LLVMIntToPtr, value, LLVMPointerType(llvm_left_type, 0), "IntToPtr");
            LLVMBuildStore(gBuilder, value, lvalue.address);
        }
        else {
            if(auto_cast_posibility(left_type, right_type)) {
                if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            LLVMValueRef address = lvalue.value;

            LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
            LLVMValueRef add_rvalue = rvalue.value;

            LLVMValueRef value = LLVMBuildAdd(gBuilder, add_lvalue, add_rvalue, "add");

            LLVMBuildStore(gBuilder, value, address);
        }
    }
    else {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.address;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value = LLVMBuildAdd(gBuilder, add_lvalue, add_rvalue, "add");

        LLVMBuildStore(gBuilder, value, address);
    }

    return TRUE;
}

unsigned int sNodeTree_create_minus_minus(unsigned int left_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeMinusMinus;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_minus_minus(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    BOOL derefference = gNodes[left_node].mNodeType == kNodeTypeDerefference;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = sNodeTree_create_int_value(1, info->pinfo);

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(derefference && left_type->mPointerNum == 0) {
            LLVMValueRef address = lvalue.value;

            LLVMTypeRef llvm_left_type = create_llvm_type_from_node_type(left_type);

            LLVMTypeRef long_type = create_llvm_type_with_class_name("long");

            LLVMValueRef left_value = address;
            LLVMValueRef left_value2 = LLVMBuildCast(gBuilder, LLVMPtrToInt, left_value, long_type, "ptrToInt");

            LLVMValueRef right_value;
            if(type_identify_with_class_name(right_type, "long")) {
                right_value = rvalue.value;
            }
            else {
                if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                    right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "sext");
                }
                else {
                    right_value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue.value, long_type, "sext");
                }
            }

            uint64_t alloc_size = get_size_from_node_type(left_type);

            LLVMValueRef alloc_size_value = LLVMConstInt(long_type, alloc_size, FALSE);

            right_value = LLVMBuildMul(gBuilder, right_value, alloc_size_value, "mul");

            LLVMValueRef value = LLVMBuildSub(gBuilder, left_value2, right_value, "subtmp");
            value = LLVMBuildCast(gBuilder, LLVMIntToPtr, value, LLVMPointerType(llvm_left_type,0), "IntToPtr");
            LLVMBuildStore(gBuilder, value, lvalue.address);
        }
        else {
            if(auto_cast_posibility(left_type, right_type)) {
                if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            LLVMValueRef address = lvalue.value;

            LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
            LLVMValueRef add_rvalue = rvalue.value;

            LLVMValueRef value = LLVMBuildSub(gBuilder, add_lvalue, add_rvalue, "sub");

            LLVMBuildStore(gBuilder, value, address);
        }
    }
    else {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.address;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value = LLVMBuildSub(gBuilder, add_lvalue, add_rvalue, "add");

        LLVMBuildStore(gBuilder, value, address);
    }

    return TRUE;
}

unsigned int sNodeTree_create_equal_plus(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeEqualPlus;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_equal_plus(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    BOOL derefference = gNodes[left_node].mNodeType == kNodeTypeDerefference;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(derefference && left_type->mPointerNum == 0) {
            LLVMValueRef address = lvalue.value;

            LLVMTypeRef llvm_left_type = create_llvm_type_from_node_type(left_type);

            LLVMTypeRef long_type = create_llvm_type_with_class_name("long");

            LLVMValueRef left_value = address;
            LLVMValueRef left_value2 = LLVMBuildCast(gBuilder, LLVMPtrToInt, left_value, long_type, "ptrToInt");

            LLVMValueRef right_value;
            if(type_identify_with_class_name(right_type, "long")) {
                right_value = rvalue.value;
            }
            else {
                if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                    right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "ptToInt");
                }
                else {
                    right_value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue.value, long_type, "sext");
                }
            }

            uint64_t alloc_size = get_size_from_node_type(left_type);

            LLVMValueRef alloc_size_value = LLVMConstInt(long_type, alloc_size, FALSE);

            right_value = LLVMBuildMul(gBuilder, right_value, alloc_size_value, "mult");

            LLVMValueRef value = LLVMBuildAdd(gBuilder, left_value2, right_value, "add");
            value = LLVMBuildCast(gBuilder, LLVMIntToPtr, value, LLVMPointerType(llvm_left_type,0), "IntToPtr");
            LLVMBuildStore(gBuilder, value, lvalue.address);
        }
        else {
            if(auto_cast_posibility(left_type, right_type)) {
                if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            LLVMValueRef address = lvalue.value;

            LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
            LLVMValueRef add_rvalue = rvalue.value;

            LLVMValueRef value = LLVMBuildAdd(gBuilder, add_lvalue, add_rvalue, "add");

            LLVMBuildStore(gBuilder, value, address);
        }
    }
    else {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.address;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value = LLVMBuildAdd(gBuilder, add_lvalue, add_rvalue, "add");

        LLVMBuildStore(gBuilder, value, address);
    }

    return TRUE;
}

unsigned int sNodeTree_create_equal_minus(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeEqualMinus;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_equal_minus(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;
    BOOL derefference = gNodes[left_node].mNodeType == kNodeTypeDerefference;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(derefference && left_type->mPointerNum == 0) {
            LLVMValueRef address = lvalue.value;

            LLVMTypeRef llvm_left_type = create_llvm_type_from_node_type(left_type);

            LLVMTypeRef long_type = create_llvm_type_with_class_name("long");

            LLVMValueRef left_value = address;
            LLVMValueRef left_value2 = LLVMBuildCast(gBuilder, LLVMPtrToInt, left_value, long_type, "cast");

            LLVMValueRef right_value;
            if(type_identify_with_class_name(right_type, "long")) {
                right_value = rvalue.value;
            }
            else {
                if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                    right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "ptrToInt");
                }
                else {
                    right_value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue.value, long_type, "sext");
                }
            }

            uint64_t alloc_size = get_size_from_node_type(left_type);

            LLVMValueRef alloc_size_value = LLVMConstInt(long_type, alloc_size, FALSE);

            right_value = LLVMBuildMul(gBuilder, right_value, alloc_size_value, "mul");

            LLVMValueRef value = LLVMBuildSub(gBuilder, left_value2, right_value, "sub");
            value = LLVMBuildCast(gBuilder, LLVMIntToPtr, value, LLVMPointerType(llvm_left_type,0), "IntToPtr");
            LLVMBuildStore(gBuilder, value, lvalue.address);
        }
        else {
            if(auto_cast_posibility(left_type, right_type)) {
                if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            LLVMValueRef address = lvalue.value;

            LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
            LLVMValueRef add_rvalue = rvalue.value;

            LLVMValueRef value = LLVMBuildSub(gBuilder, add_lvalue, add_rvalue, "sub");

            LLVMBuildStore(gBuilder, value, address);
        }
    }
    else {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.address;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value = LLVMBuildSub(gBuilder, add_lvalue, add_rvalue, "subtmp");

        LLVMBuildStore(gBuilder, value, address);
    }

    return TRUE;
}

unsigned int sNodeTree_create_equal_mult(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeEqualMult;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_equal_mult(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.value;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value = LLVMBuildMul(gBuilder, add_lvalue, add_rvalue, "mult");

        LLVMBuildStore(gBuilder, value, address);
    }
    else {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.address;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value = LLVMBuildMul(gBuilder, add_lvalue, add_rvalue, "multmp");

        LLVMBuildStore(gBuilder, value, address);
    }

    return TRUE;
}

unsigned int sNodeTree_create_equal_div(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeEqualDiv;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_equal_div(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.value;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value;

        if(left_type->mUnsigned) {
            value = LLVMBuildUDiv(gBuilder, add_lvalue, add_rvalue, "div");
        }
        else {
            value = LLVMBuildSDiv(gBuilder, add_lvalue, add_rvalue, "div");
        }

        LLVMBuildStore(gBuilder, value, address);
    }
    else {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.address;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value;

        if(left_type->mUnsigned) {
            value = LLVMBuildUDiv(gBuilder, add_lvalue, add_rvalue, "div");
        }
        else {
            value = LLVMBuildSDiv(gBuilder, add_lvalue, add_rvalue, "div");
        }

        LLVMBuildStore(gBuilder, value, address);
    }

    return TRUE;
}

unsigned int sNodeTree_create_equal_mod(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeEqualMod;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_equal_mod(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.value;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value;
        if(left_type->mUnsigned) {
            value = LLVMBuildURem(gBuilder, add_lvalue, add_rvalue, "rem");
        }
        else {
            value = LLVMBuildSRem(gBuilder, add_lvalue, add_rvalue, "rem");
        }

        LLVMBuildStore(gBuilder, value, address);
    }
    else {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.address;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value;
        if(left_type->mUnsigned) {
            value = LLVMBuildURem(gBuilder, add_lvalue, add_rvalue, "rem");
        }
        else {
            value = LLVMBuildSRem(gBuilder, add_lvalue, add_rvalue, "rem");
        }

        LLVMBuildStore(gBuilder, value, address);
    }

    return TRUE;
}

unsigned int sNodeTree_create_equal_lshift(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeEqualLShift;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_equal_lshift(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.value;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value;
        value = LLVMBuildShl(gBuilder, add_lvalue, add_rvalue, "lshift");

        LLVMBuildStore(gBuilder, value, address);
    }
    else {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.address;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value;
        value = LLVMBuildShl(gBuilder, add_lvalue, add_rvalue, "lshift");

        LLVMBuildStore(gBuilder, value, address);
    }

    return TRUE;
}

unsigned int sNodeTree_create_equal_rshift(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeEqualRShift;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_equal_rshift(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.value;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value;
        value = LLVMBuildAShr(gBuilder, add_lvalue, add_rvalue, "rshift");

        LLVMBuildStore(gBuilder, value, address);
    }
    else {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.address;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value;
        value = LLVMBuildAShr(gBuilder, add_lvalue, add_rvalue, "rshift");

        LLVMBuildStore(gBuilder, value, address);
    }

    return TRUE;
}

unsigned int sNodeTree_create_equal_and(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeEqualAnd;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_equal_and(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.value;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value;
        value = LLVMBuildAnd(gBuilder, add_lvalue, add_rvalue, "andtmp");

        LLVMBuildStore(gBuilder, value, address);
    }
    else {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.address;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value;
        value = LLVMBuildAnd(gBuilder, add_lvalue, add_rvalue, "and");

        LLVMBuildStore(gBuilder, value, address);
    }

    return TRUE;
}

unsigned int sNodeTree_create_equal_xor(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeEqualXor;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_equal_xor(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.value;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value;
        value = LLVMBuildXor(gBuilder, add_lvalue, add_rvalue, "xortmp");

        LLVMBuildStore(gBuilder, value, address);
    }
    else {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.address;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value;
        value = LLVMBuildXor(gBuilder, add_lvalue, add_rvalue, "xortmp");

        LLVMBuildStore(gBuilder, value, address);
    }

    return TRUE;
}

unsigned int sNodeTree_create_equal_or(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeEqualOr;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_equal_or(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = info->type;

    LVALUE rvalue = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.value;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value;
        value = LLVMBuildOr(gBuilder, add_lvalue, add_rvalue, "ortmp");

        LLVMBuildStore(gBuilder, value, address);
    }
    else {
        if(auto_cast_posibility(left_type, right_type)) {
            if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
        }

        LLVMValueRef address = lvalue.address;

        LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
        LLVMValueRef add_rvalue = rvalue.value;

        LLVMValueRef value;
        value = LLVMBuildOr(gBuilder, add_lvalue, add_rvalue, "ortmp");

        LLVMBuildStore(gBuilder, value, address);
    }

    return TRUE;
}

unsigned int sNodeTree_create_comma(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeComma;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_comma(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    dec_stack_ptr(1, info);

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    return TRUE;
}

unsigned int sNodeTree_create_func_name(sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFunName;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_func_name(unsigned int node, sCompileInfo* info)
{
    LVALUE llvm_value;

    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("char*");
    LLVMValueRef value = LLVMBuildPointerCast(gBuilder, LLVMBuildGlobalString(gBuilder, info->fun_name, info->fun_name), llvm_type, "func_name");

    llvm_value.value = value;
    llvm_value.type = create_node_type_with_class_name("char*");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = clone_node_type(llvm_value.type);

    return TRUE;
}

BOOL compile(unsigned int node, sCompileInfo* info)
{
    if(node == 0) {
        return TRUE;
    }

    switch(gNodes[node].mNodeType) {
        case kNodeTypeFunction:
            if(!compile_function(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeExternalFunction:
            if(!compile_external_function(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeStruct:
            if(!compile_struct(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeIntValue:
            if(!compile_int_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeUIntValue:
            if(!compile_uint_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeAdd:
            if(!compile_add(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeSub:
            if(!compile_sub(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeMult:
            if(!compile_mult(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeDiv:
            if(!compile_div(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeMod:
            if(!compile_mod(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeEquals:
            if(!compile_equals(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeNotEquals:
            if(!compile_not_equals(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCString:
            if(!compile_c_string_value(node, info)) 
            {
                return FALSE;
            }
            break;

        case kNodeTypeStoreVariable:
            if(!compile_store_variable(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeDefineVariable:
            if(!compile_define_variable(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeFunctionCall:
            if(!compile_function_call(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLoadVariable:
            if(!compile_load_variable(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeIf:
            if(!compile_if_expression(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeObject:
            if(!compile_object(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeStackObject:
            if(!compile_stack_object(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeStoreField:
            if(!compile_store_field(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLoadField:
            if(!compile_load_field(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeWhile:
            if(!compile_while_expression(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeGteq:
            if(!compile_gteq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLeeq:
            if(!compile_leeq(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeGt:
            if(!compile_gt(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLe:
            if(!compile_le(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLogicalDenial:
            if(!compile_logical_denial(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeTrue:
            if(!compile_true(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeFalse:
            if(!compile_false(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeAndAnd:
            if(!compile_and_and(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeOrOr:
            if(!compile_or_or(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeFor:
            if(!compile_for_expression(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeLambdaCall:
            if(!compile_lambda_call(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeDerefference:
            if(!compile_dereffernce(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeRefference:
            if(!compile_reffernce(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeNull:
            if(!compile_null(node, info))
            { 
                return FALSE;
            }
            break;

        case kNodeTypeClone:
            if(!compile_clone(node, info))
            { 
                return FALSE;
            }
            break;

        case kNodeTypeLoadElement:
            if(!compile_load_element(node, info))
            { 
                return FALSE;
            }
            break;

        case kNodeTypeStoreElement:
            if(!compile_store_element(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeChar:
            if(!compile_char_value(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeCast:
            if(!compile_cast(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeImpl:
            if(!compile_impl(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeGenericsFunction:
            if(!compile_generics_function(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeInlineFunction:
            if(!compile_inline_function(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeTypeDef:
            if(!compile_typedef(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeUnion:
            if(!compile_union(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeLeftShift:
            if(!compile_left_shift(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeRightShift:
            if(!compile_right_shift(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeAnd:
            if(!compile_and(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeXor:
            if(!compile_xor(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeOr:
            if(!compile_or(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeReturn:
            if(!compile_return(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeSizeOf:
            if(!compile_sizeof(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeNodes:
            if(!compile_nodes(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeLoadFunction:
            if(!compile_load_function(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeArrayWithInitialization:
            if(!compile_array_with_initialization(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeNormalBlock:
            if(!compile_normal_block(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeStructWithInitialization:
            if(!compile_struct_with_initialization(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeSwitch:
            if(!compile_switch_expression(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeBreak:
            if(!compile_break_expression(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeContinue:
            if(!compile_continue_expression(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeDoWhile:
            if(!compile_do_while_expression(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeCase:
            if(!compile_case_expression(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeLabel:
            if(!compile_label_expression(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeGoto:
            if(!compile_goto_expression(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeIsHeap:
            if(!compile_is_heap(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeSizeOfExpression:
            if(!compile_sizeof_expression(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeDelete:
            if(!compile_delete(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeBorrow:
            if(!compile_borrow(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeDummyHeap:
            if(!compile_dummy_heap(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeManaged:
            if(!compile_managed(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeConditional:
            if(!compile_conditional(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeAlignOf:
            if(!compile_alignof(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeAlignOfExpression:
            if(!compile_alignof_expression(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeLongValue:
            if(!compile_long_value(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeULongValue:
            if(!compile_ulong_value(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeComplement:
            if(!compile_complement(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeStoreAddress:
            if(!compile_store_address(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeLoadAddressValue:
            if(!compile_load_address_value(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypePlusPlus:
            if(!compile_plus_plus(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeMinusMinus:
            if(!compile_minus_minus(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeEqualPlus:
            if(!compile_equal_plus(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeEqualMinus:
            if(!compile_equal_minus(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeEqualMult:
            if(!compile_equal_mult(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeEqualDiv:
            if(!compile_equal_div(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeEqualMod:
            if(!compile_equal_mod(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeEqualLShift:
            if(!compile_equal_lshift(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeEqualRShift:
            if(!compile_equal_rshift(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeEqualAnd:
            if(!compile_equal_and(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeEqualXor:
            if(!compile_equal_xor(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeEqualOr:
            if(!compile_equal_or(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeComma:
            if(!compile_comma(node, info))
            {
                return FALSE;
            }
            break;

        case kNodeTypeFunName:
            if(!compile_func_name(node, info))
            {
                return FALSE;
            }
            break;
    }

    return node;
}
