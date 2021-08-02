#include "common.h"
#include <pthread.h>

int gThreadNum = 0;

sNodeType* gComeFunctionResultType;

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

BOOL compile_external_function(unsigned int node, sCompileInfo* info)
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
            compile_err_msg(info, "invalid type %s(4)", param_names[i]);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }

        xstrncpy(param_names[i], params[i].mName, VAR_NAME_MAX);
        param_types[i] = param_type;
    }

    LLVMTypeRef llvm_param_types[PARAMS_MAX];

    for(i=0; i<num_params; i++) {
#ifdef __RASPBERRY_PI__
        if(type_identify_with_class_name(param_types[i], "__builtin_va_list") || type_identify_with_class_name(param_types[i], "va_list")) {
            llvm_param_types[i] = create_llvm_type_with_class_name("int");
            llvm_param_types[i] = LLVMArrayType(llvm_param_types[i], 1);
        }
        else {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }
#else
        if(type_identify_with_class_name(param_types[i], "__builtin_va_list") || type_identify_with_class_name(param_types[i], "va_list")) {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
            llvm_param_types[i] = LLVMPointerType(llvm_param_types[i], 0);
        }
        else {
            llvm_param_types[i] = create_llvm_type_from_node_type(param_types[i]);
        }
#endif
    }

    LLVMTypeRef llvm_result_type;

    llvm_result_type = create_llvm_type_from_node_type(result_type);

    LLVMTypeRef function_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
    LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, fun_name);

    BOOL override_ = result_type->mOverride;

    if(llvm_fun) {
        if(override_) {
            char old_fun_name[VAR_NAME_MAX];

            int i;
            for(i=1; i<FUN_VERSION_MAX; i++) {
                snprintf(old_fun_name, VAR_NAME_MAX, "%s_v%d", fun_name, i);

                LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, old_fun_name);

                if(llvm_fun == NULL) {
                   break;
                }
            }

            LLVMSetValueName2(llvm_fun, old_fun_name, strlen(old_fun_name));

            char* block_text = NULL;

            char* param_names2[PARAMS_MAX];
            for(i=0; i<PARAMS_MAX; i++) {
                param_names2[i] = param_names[i];
            }

            BOOL generics_function = FALSE;
            if(!add_function_to_table(old_fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, 0, NULL, TRUE, asm_fun_name)) {
                fprintf(stderr, "overflow function table\n");
                return FALSE;
            }

            if(strcmp(asm_fun_name, "") == 0) {
                llvm_fun = LLVMAddFunction(gModule, fun_name, function_type);
            }
            else {
                llvm_fun = LLVMAddFunction(gModule, asm_fun_name, function_type);
            }
        }
    }
    else {
        if(strcmp(asm_fun_name, "") == 0) {
            llvm_fun = LLVMAddFunction(gModule, fun_name, function_type);
        }
        else {
#ifdef __DARWIN__
            llvm_fun = LLVMAddFunction(gModule, fun_name, function_type);
#else
            llvm_fun = LLVMAddFunction(gModule, asm_fun_name, function_type);
#endif
        }

        char* block_text = NULL;

        char* param_names2[PARAMS_MAX];
        for(i=0; i<PARAMS_MAX; i++) {
            param_names2[i] = param_names[i];
        }

        BOOL generics_function = FALSE;
        if(!add_function_to_table(fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, 0, NULL, TRUE, asm_fun_name)) {
            fprintf(stderr, "overflow function table\n");
            return FALSE;
        }
    }

    return TRUE;
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

        if(node_type->mHeap) {
            xstrncat(real_fun_name, "h", size_real_fun_name);
        }

        if(i != generics_type->mNumGenericsTypes-1) {
            xstrncat(real_fun_name, "_", size_real_fun_name);
        }
    }

}

BOOL create_generics_function(LLVMValueRef* llvm_fun, sFunction* fun, char* fun_name, sNodeType* generics_type, sCompileInfo* info)
{
    sNodeType* generics_type_before = info->generics_type;
    info->generics_type = clone_node_type(generics_type);

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

    char real_fun_name[REAL_FUN_NAME_MAX];
    create_generics_fun_name(real_fun_name, REAL_FUN_NAME_MAX, fun_name,  generics_type);

    *llvm_fun = LLVMGetNamedFunction(gModule, real_fun_name);

    if(*llvm_fun == NULL) {
        LLVMBasicBlockRef current_block = info->current_block; //LLVMGetLastBasicBlock(gFunction);

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

        BOOL lambda_ = FALSE;
        BOOL simple_lambda_param = FALSE;
        BOOL constructor_fun = FALSE;
        BOOL operator_fun = FALSE;
        BOOL generics_function = FALSE;
        int version = 0;
        BOOL finalize = FALSE;
        int generics_fun_num = 0;
        char* struct_name = NULL;

        result_type->mStatic = TRUE;

        unsigned int node = sNodeTree_create_function(real_fun_name, real_fun_name, params, num_params, result_type, MANAGED node_block, lambda_, block_var_table, struct_name, operator_fun, constructor_fun, simple_lambda_param, &info2, generics_function, var_args, version, finalize, generics_fun_num, fun->mName, 0);

        sCompileInfo cinfo;

        memset(&cinfo, 0, sizeof(sCompileInfo));

        cinfo.no_output = FALSE;
        cinfo.pinfo = info->pinfo;
        cinfo.sline = info->sline;
        xstrncpy(cinfo.sname, info->sname, PATH_MAX);
        cinfo.generics_type = clone_node_type(info->generics_type);
        xstrncpy(cinfo.generics_sname, info->sname, PATH_MAX);
        cinfo.generics_sline = info->sline;

        cinfo.in_generics_function = TRUE;

        if(!compile(node, &cinfo)) {
            return FALSE;
        }

        llvm_change_block(current_block, info);

        *llvm_fun = LLVMGetNamedFunction(gModule, real_fun_name);
    }

    info->generics_type = generics_type_before;

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

    if(inherit) {
        char real_fun_name[VAR_NAME_MAX];

        char* p = gFunctionName;

        BOOL get_ = FALSE;
        int n = 0;

        while(*p) {
            if(*p == '_' && *(p+1) == 'v' && xisdigit(*(p+2))) {
                char* p2 = p + 2;
                n = 0;
                while(xisdigit(*p2)) {
                    n = n * 10 + (*p2 - '0');
                    p2++;
                }
                break;
            }
            else {
                p++;
            }
        }

        version = n;

        if(*p == '\0') {
            char* fun_name2 = gFunctionName;

            char old_fun_name[VAR_NAME_MAX];

            int i;
            for(i=FUN_VERSION_MAX; i>=0; i--) {
                snprintf(old_fun_name, VAR_NAME_MAX, "%s_v%d", fun_name2, i);

                LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, old_fun_name);

                if(llvm_fun) {
                    break;
                }
            }

            strncpy(fun_name, old_fun_name, VAR_NAME_MAX);
        }
        else {
            memcpy(real_fun_name, gFunctionName, p - gFunctionName);
            real_fun_name[p-gFunctionName] = '\0';

            char fun_name2[VAR_NAME_MAX];
            snprintf(fun_name2, VAR_NAME_MAX, "%s_v%d", real_fun_name, version-1);

            strncpy(fun_name, fun_name2, VAR_NAME_MAX);
        }
    }

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

    LVALUE lvalue_params[PARAMS_MAX];

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

        lvalue_params[0] = param;
        llvm_params[0] = param.value;

        xstrncpy(struct_name, CLASS_NAME(param_types[0]->mClass), VAR_NAME_MAX);

        char method_name[VAR_NAME_MAX];
        snprintf(method_name, VAR_NAME_MAX, "%s_%s", struct_name, fun_name);

        xstrncpy(fun_name, method_name, VAR_NAME_MAX);
    }

    sFunction* fun = get_function_from_table(fun_name);

    if(fun == NULL) {
        compile_err_msg(info, "function not found(%s)\n", fun_name);
        return FALSE;
    }

    if(method) {
        xstrncpy(param_names[0], fun->mParamNames[0], VAR_NAME_MAX);

        LVALUE param = lvalue_params[0];

        if(fun->mParamTypes[0]) {
            sNodeType* fun_param_type = clone_node_type(fun->mParamTypes[0]);

            if(is_typeof_type(fun_param_type))
            {
                if(!solve_typeof(&fun_param_type, info)) 
                {
                    compile_err_msg(info, "Can't solve typeof types");
                    show_node_type(fun_param_type);
                    info->err_num++;
                    return TRUE;
                }
            }

            if(generics_type) {
                if(!solve_generics(&fun_param_type, generics_type))
                {
                    compile_err_msg(info, "Can't solve generics types(3)");
                    show_node_type(fun_param_type);
                    show_node_type(generics_type);
                    info->err_num++;

                    return FALSE;
                }
            }

            if(auto_cast_posibility(fun_param_type, param_types[0])) {
                if(!cast_right_type_to_left_type(fun_param_type, &param_types[0], &param, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }
        }

        llvm_params[0] = param.value;
    }

    for(i=method?1:0; i<num_params; i++) {
        params[i] = gNodes[node].uValue.sFunctionCall.mParams[i];
        
        if(!compile(params[i], info)) {
            return FALSE;
        }

        if(fun->mParamNames[i]) {
            xstrncpy(param_names[i], fun->mParamNames[i], VAR_NAME_MAX);
        }
        else {
            xstrncpy(param_names[i], "", VAR_NAME_MAX);
        }
        param_types[i] = clone_node_type(info->type);

        LVALUE param = *get_value_from_stack(-1);
        lvalue_params[i] = param;

        if(fun->mParamTypes[i]) {
            sNodeType* fun_param_type = clone_node_type(fun->mParamTypes[i]);

            if(is_typeof_type(fun_param_type))
            {
                if(!solve_typeof(&fun_param_type, info)) 
                {
                    compile_err_msg(info, "Can't solve typeof types");
                    show_node_type(fun_param_type);
                    info->err_num++;
                    return TRUE;
                }
            }

            if(generics_type) {
                if(!solve_generics(&fun_param_type, generics_type))
                {
                    compile_err_msg(info, "Can't solve generics types(3)");
                    show_node_type(fun_param_type);
                    show_node_type(generics_type);
                    info->err_num++;

                    return FALSE;
                }
            }

#ifdef __ISH__
if(type_identify_with_class_name(fun_param_type, "__va_list") && type_identify_with_class_name(param_types[i], "__va_list"))
{
    param.value = LLVMBuildLoad(gBuilder, param.value, "va_list_load");
}
#endif

            if(auto_cast_posibility(fun_param_type, param_types[i])) {
                if(!cast_right_type_to_left_type(fun_param_type, &param_types[i], &param, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            if(strcmp(fun_name, "llvm.va_start") != 0 && strcmp(fun_name, "llvm.va_end") != 0) {
                if(!substitution_posibility(fun_param_type, param_types[i], info)) {
                    compile_err_msg(info, "function(%s) param type error %d", fun_name, i);
                    show_node_type(fun_param_type);
                    show_node_type(param_types[i]);
                    info->err_num++;
                    return TRUE;
                }
            }
        }
        else {
            if(fun->mVarArgs) {
                if(param_types[i]->mArrayDimentionNum == 1) {
                    sNodeType* fun_param_type = clone_node_type(param_types[i]);

                    fun_param_type->mArrayDimentionNum = 0;
                    fun_param_type->mPointerNum++;

                    if(auto_cast_posibility(fun_param_type, param_types[i])) {
                        if(!cast_right_type_to_left_type(fun_param_type, &param_types[i], &param, info))
                        {
                            compile_err_msg(info, "Cast failed");
                            info->err_num++;

                            info->type = create_node_type_with_class_name("int"); // dummy

                            return TRUE;
                        }
                    }
                }
            }
        }

        llvm_params[i] = param.value;
    }

    /// param type check ///
    if(!fun->mVarArgs && strcmp(fun_name, "llvm.va_start") != 0 && strcmp(fun_name, "llvm.va_end") != 0) {
        if(fun->mNumParams != num_params) {
            compile_err_msg(info, "function(%s) param number error. fun param number %d, calling %d", fun_name, fun->mNumParams, num_params);
            info->err_num++;
            return TRUE;
        }
    }

    /// std move //
    for(i=0; i<fun->mNumParams; i++) {
        LVALUE param = lvalue_params[i];

        if(fun->mParamTypes[i]->mHeap && param.type->mHeap) {
            sVar* var = param.var;
            if(var) {
                var->mLLVMValue = NULL;
            }
        }
    }

    if(strcmp(fun_name, "llvm.va_start") == 0 || strcmp(fun_name, "llvm.va_end") == 0)
    {
#ifdef __DARWIN__
        LLVMValueRef param = llvm_params[0];

        LLVMValueRef indices[2];

        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

        indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
        indices[1] = LLVMConstInt(llvm_type, 0, FALSE);

        param = LLVMBuildGEP(gBuilder, param, indices, 2, "gep");

        LLVMTypeRef llvm_type2 = create_llvm_type_with_class_name("char*");
        param = LLVMBuildCast(gBuilder, LLVMBitCast, param, llvm_type2, "castAE");

        llvm_params[0] = param;
        num_params = 1;
#else
        LLVMValueRef param = llvm_params[0];

        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("char*");
        param = LLVMBuildCast(gBuilder, LLVMBitCast, param, llvm_type, "castAE");

        llvm_params[0] = param;
        num_params = 1;
#endif
    }
#ifdef __DARWIN__
    else {
        int i;
        for(i=0;i<num_params; i++) {
            if(type_identify_with_class_name(param_types[i], "__builtin_va_list") || type_identify_with_class_name(param_types[i], "va_list")) {
                LLVMValueRef indices[2];

                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

                indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
                indices[1] = LLVMConstInt(llvm_type, 0, FALSE);

                llvm_params[i] = LLVMBuildGEP(gBuilder, llvm_params[i], indices, 2, "gep");
            }
        }
    }
#elif __RASPBERRY_PI__
    else {
        int i;
        for(i=0;i<num_params; i++) {
            if(type_identify_with_class_name(param_types[i], "__builtin_va_list") || type_identify_with_class_name(param_types[i], "va_list")) {
                LLVMValueRef indices[2];

                LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

                indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
                indices[1] = LLVMConstInt(llvm_type, 0, FALSE);

                llvm_params[i] = LLVMBuildGEP(gBuilder, llvm_params[i], indices, 2, "gep");

                sNodeType* node_type = create_node_type_with_class_name("int");
                node_type->mArrayDimentionNum = 1;
                node_type->mArrayNum[0] = 1;

                LLVMTypeRef llvm_type2 = create_llvm_type_from_node_type(node_type);

                llvm_type2 = LLVMPointerType(llvm_type2, 0);

                llvm_params[i] = LLVMBuildCast(gBuilder, LLVMBitCast, llvm_params[i], llvm_type2, "icastXXX");
                llvm_params[i] = LLVMBuildLoad(gBuilder, llvm_params[i], "va_list");
            }
        }
    }
#endif

    sNodeType* result_type = clone_node_type(fun->mResultType);

    /// call generics function ///
    if(fun->mGenericsFunction) {
        for(i=0; i<num_params; i++) {
            sNodeType* node_type = clone_node_type(fun->mParamTypes[i]);

            if(is_typeof_type(node_type))
            {
                if(!solve_typeof(&node_type, info)) 
                {
                    compile_err_msg(info, "Can't solve typeof types");
                    show_node_type(node_type);
                    info->err_num++;
                    return TRUE;
                }
            }

            if(generics_type) {
                if(!solve_generics(&node_type, generics_type))
                {
                    compile_err_msg(info, "Can't solve generics types(3)");
                    show_node_type(node_type);
                    show_node_type(generics_type);
                    info->err_num++;

                    return FALSE;
                }
            }

            if(node_type->mHeap) {
                remove_object_from_right_values(llvm_params[i], info);
            }
        }

        LLVMValueRef llvm_fun= NULL;

        if(!create_generics_function(&llvm_fun, fun, fun_name, generics_type, info)) {
            return FALSE;
        }

        if(type_identify_with_class_name(result_type, "void") && result_type->mPointerNum == 0) {
            LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "");

            dec_stack_ptr(num_params, info);

            info->type = create_node_type_with_class_name("void");
        }
        else {
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

            if(generics_type) {
                if(!solve_generics(&result_type, generics_type))
                {
                    compile_err_msg(info, "Can't solve generics types(3)");
                    show_node_type(result_type);
                    show_node_type(generics_type);
                    info->err_num++;

                    return FALSE;
                }
            }

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
        //info2.lv_table = info->pinfo->lv_table;
        info2.lv_table = init_block_vtable(NULL, FALSE);
        info2.in_clang = info->pinfo->in_clang;

        sNodeBlock* node_block = ALLOC sNodeBlock_alloc();
        expect_next_character_with_one_forward("{", &info2);
        sVarTable* old_table = info2.lv_table;

        info2.lv_table = init_block_vtable(old_table, FALSE);
        sVarTable* block_var_table = info2.lv_table;

        for(i=0; i<num_params; i++) {
            BOOL readonly = FALSE;
            if(!add_variable_to_table(info2.lv_table, param_names[i], fun->mParamTypes[i], readonly, NULL, -1, FALSE, param_types[i]->mConstant))
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

            if(fun->mParamTypes[i] != NULL) {
                sNodeType* node_type = clone_node_type(fun->mParamTypes[i]);

                if(is_typeof_type(node_type))
                {
                    if(!solve_typeof(&node_type, info)) 
                    {
                        compile_err_msg(info, "Can't solve typeof types");
                        show_node_type(node_type);
                        info->err_num++;
                        return TRUE;
                    }
                }

                if(generics_type) {
                    if(!solve_generics(&node_type, generics_type))
                    {
                        compile_err_msg(info, "Can't solve generics types(3)");
                        show_node_type(node_type);
                        show_node_type(generics_type);
                        info->err_num++;

                        return FALSE;
                    }
                }

                if(node_type->mHeap) {
                    remove_object_from_right_values(llvm_params[i], info);
                }

                var->mLLVMValue = param;
            }
        }

        BOOL in_inline_function = info->in_inline_function;
        info->in_inline_function = TRUE;
        info->inline_sline = info->sline;

        char fun_end_label[PATH_MAX];
        snprintf(fun_end_label, PATH_MAX, "%s_end", fun_name);

        LLVMBasicBlockRef inline_func_end_before = info->inline_func_end;
        LLVMBasicBlockRef inline_func_end = LLVMAppendBasicBlockInContext(gContext, gFunction, fun_end_label);
        info->inline_func_end = inline_func_end;

        struct sRightValueObject* right_value_objects = info->right_value_objects;
        info->right_value_objects = NULL;

        sNodeType* come_function_result_type = gComeFunctionResultType;
        gComeFunctionResultType = clone_node_type(fun->mResultType);

        if(!compile_block(node_block, info)) {
            return FALSE;
        }

        gComeFunctionResultType = come_function_result_type;

        info->in_inline_function = in_inline_function;

        if(!info->last_expression_is_return) {
            LLVMBuildBr(gBuilder, inline_func_end);
        }

        llvm_change_block(inline_func_end, info);

        info->right_value_objects = right_value_objects;

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
        info->inline_func_end = inline_func_end_before;
    }
    /// call normal function ///
    else {
        for(i=0; i<fun->mNumParams; i++) {
            sNodeType* node_type = clone_node_type(fun->mParamTypes[i]);

            if(is_typeof_type(node_type))
            {
                if(!solve_typeof(&node_type, info)) 
                {
                    compile_err_msg(info, "Can't solve typeof types");
                    show_node_type(node_type);
                    info->err_num++;
                    return TRUE;
                }
            }

            if(generics_type) {
                if(!solve_generics(&node_type, generics_type))
                {
                    compile_err_msg(info, "Can't solve generics types(3)");
                    show_node_type(node_type);
                    show_node_type(generics_type);
                    info->err_num++;

                    return FALSE;
                }
            }
            if(node_type->mHeap) {
                remove_object_from_right_values(llvm_params[i], info);
            }
        }

        LLVMValueRef llvm_fun;
        if(fun->mAsmFunName) {
#ifdef __DARWIN__
            llvm_fun = LLVMGetNamedFunction(gModule, fun_name);
#else
            llvm_fun = LLVMGetNamedFunction(gModule, fun->mAsmFunName);
#endif
        }
        else {
            llvm_fun = LLVMGetNamedFunction(gModule, fun_name);
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

    if(is_typeof_type(info->type))
    {
        if(!solve_typeof(&info->type, info)) 
        {
            compile_err_msg(info, "Can't solve typeof types");
            show_node_type(info->type); 
            info->err_num++;
            return TRUE;
        }
    }

    if(generics_type) {
        if(!solve_generics(&info->type, generics_type))
        {
            compile_err_msg(info, "Can't solve generics types(3)");
            show_node_type(info->type);
            show_node_type(generics_type);
            info->err_num++;

            return FALSE;
        }
    }

    return TRUE;
}

unsigned int sNodeTree_create_function(char* fun_name, char* asm_fname, sParserParam* params, int num_params, sNodeType* result_type, MANAGED struct sNodeBlockStruct* node_block, BOOL lambda_, sVarTable* block_var_table, char* struct_name, BOOL operator_fun, BOOL constructor_fun, BOOL simple_lambda_param, sParserInfo* info, BOOL generics_function, BOOL var_arg, int version, BOOL finalize, int generics_fun_num, char* simple_fun_name, int sline)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFunction;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

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
    gNodes[node].uValue.sFunction.mLambda = lambda_;
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
    int thread_num = gThreadNum;
    gThreadNum = 0;

    /// get result type ///
    sNodeType* result_type = clone_node_type(gNodes[node].uValue.sFunction.mResultType);

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
    BOOL lambda_ = gNodes[node].uValue.sFunction.mLambda;
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

    LLVMBasicBlockRef current_block = NULL;

    if(lambda_) {
        current_block = info->current_block; //LLVMGetLastBasicBlock(gFunction);
    }

    BOOL in_lambda_function = info->in_lambda_function;
    info->in_lambda_function = lambda_;
    info->lambda_sline = info->sline;

    sNodeBlock* function_node_block = info->function_node_block;
    info->function_node_block = node_block;

    sNodeType* param_types[PARAMS_MAX];
    LLVMTypeRef llvm_param_types[PARAMS_MAX];
    char param_names[PARAMS_MAX][VAR_NAME_MAX];
    for(i=0; i<num_params; i++) {
        param_types[i] = params[i].mType;

        if(is_typeof_type(param_types[i]))
        {
            if(!solve_typeof(&param_types[i], info))
            {
                compile_err_msg(info, "Can't solve typeof types");
                show_node_type(param_types[i]);
                info->err_num++;

                return TRUE;
            }
        }

        if(!create_generics_struct_type(param_types[i])) {
            compile_err_msg(info, "invalid type %s(5)", param_names[i]);
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }

        llvm_param_types[i] = create_llvm_type_from_node_type(params[i].mType);

//#ifndef __RASPBERRY_PI__
        if(type_identify_with_class_name(param_types[i], "__builtin_va_list") || type_identify_with_class_name(param_types[i], "va_list")) {
            llvm_param_types[i] = LLVMPointerType(llvm_param_types[i], 0);
        }
//#endif

        xstrncpy(param_names[i], params[i].mName, VAR_NAME_MAX);
    }

    BOOL static_ = result_type->mStatic;

    if(version > 0) {
        int i;
        for(i=FUN_VERSION_MAX; i>=0; i--) {
            char old_fun_name[VAR_NAME_MAX];
            snprintf(old_fun_name, VAR_NAME_MAX, "%s_v%d", fun_name, i);

            LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, old_fun_name);

            if(llvm_fun) {
                break;
            }
        }

        if(version <= i) {
            char fun_name2[VAR_NAME_MAX];
            snprintf(fun_name2, VAR_NAME_MAX, "%s_v%d", fun_name, version);

            xstrncpy(fun_name, fun_name2, VAR_NAME_MAX);
        }
    }

    LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(result_type);
    LLVMTypeRef  llvm_fun_type;
    if(num_params == 0) {
        llvm_fun_type = LLVMFunctionType(llvm_result_type, NULL, 0, var_arg);
    }
    else {
        llvm_fun_type = LLVMFunctionType(llvm_result_type, llvm_param_types, num_params, var_arg);
    }

    LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, fun_name);

    if(llvm_fun == NULL) {
        if(strcmp(asm_fun_name, "") == 0) {
            llvm_fun = LLVMAddFunction(gModule, fun_name, llvm_fun_type);
        }
        else {
            llvm_fun = LLVMAddFunction(gModule, asm_fun_name, llvm_fun_type);
        }
    }

    if(static_) {
        LLVMSetLinkage(llvm_fun, LLVMInternalLinkage);
    }

    LLVMValueRef function = gFunction;
    char fun_name_before[VAR_NAME_MAX];
    xstrncpy(fun_name_before, gFunctionName, VAR_NAME_MAX);

    gFunction = llvm_fun;

    xstrncpy(gFunctionName, fun_name, VAR_NAME_MAX);

    LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(gContext, llvm_fun, "entry");
    llvm_change_block(entry, info);

    BOOL empty_function = node_block->mNumNodes == 0;

    char* block_text = NULL;

    char* param_names2[PARAMS_MAX];
    for(i=0; i<PARAMS_MAX; i++) {
        param_names2[i] = param_names[i];
    }

    BOOL generics_function = FALSE;
    if(!add_function_to_table(fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, 0, NULL, FALSE, asm_fun_name)) {
        fprintf(stderr, "overflow function table\n");
        info->function_node_block = function_node_block;
        return FALSE;
    }

    sFunction* fun = get_function_from_table(fun_name);

    sNodeType* come_function_result_type = gComeFunctionResultType;
    gComeFunctionResultType = fun->mResultType;

    if(gNCDebug && !info->in_generics_function && !info->in_inline_function && !info->in_lambda_function && !empty_function) {
        int sline = gNodes[node].mLine;
        char fname[PATH_MAX];
        xstrncpy(fname, gNodes[node].mSName, PATH_MAX);
        createDebugFunctionInfo(fname, sline, fun_name, fun, llvm_fun, gFName, info);
    }

    for(i=0; i<num_params; i++) {
        LLVMValueRef param = LLVMGetParam(llvm_fun, i);

        char* name = params[i].mName;
        sNodeType* type_ = params[i].mType;

        sVar* var = get_variable_from_table(block_var_table, name);

        LLVMTypeRef llvm_type = create_llvm_type_from_node_type(type_);

        if(gNCDebug && !info->in_generics_function && !info->in_inline_function && !info->in_lambda_function) {
            setCurrentDebugLocation(info->sline, info);
        }

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildAlloca(gBuilder, llvm_type, name);

        LLVMBuildStore(gBuilder, param, llvm_value.value);

        var->mLLVMValue = llvm_value.value;
        var->mConstant = FALSE;
    }

    if(!compile_block(node_block, info)) {
        info->function_node_block = function_node_block;
        return FALSE;
    }

    if(gNCDebug && !info->in_generics_function && !empty_function &&info->in_inline_function && info->in_lambda_function) {
        finishDebugFunctionInfo();
    }

    if(type_identify_with_class_name(result_type, "void") && result_type->mPointerNum == 0) {
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

    if(lambda_) {
        sNodeType* lambda_type = create_node_type_with_class_name("lambda");

        for(i=0; i<num_params; i++) {
            sNodeType* param_type = param_types[i];

            lambda_type->mParamTypes[i] = param_type;
        }

        lambda_type->mResultType = clone_node_type(result_type);
        lambda_type->mNumParams = num_params;

        LVALUE llvm_value;
        llvm_value.value = llvm_fun;
        llvm_value.type = clone_node_type(lambda_type);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(lambda_type);
    }
    else {
        info->type = create_node_type_with_class_name("void");
    }

    gFunction = function;
    xstrncpy(gFunctionName, fun_name_before, VAR_NAME_MAX);
    info->function_node_block = function_node_block;
    gComeFunctionResultType = come_function_result_type;
    info->in_lambda_function = in_lambda_function;

    if(lambda_) {
        llvm_change_block(current_block, info);
    }

    gThreadNum = thread_num;

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
    if(!add_function_to_table(real_fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, num_generics, generics_type_names2, FALSE, NULL)) {
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
    if(!add_function_to_table(fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, 0, NULL, FALSE, NULL)) {
        fprintf(stderr, "overflow function table\n");
        return FALSE;
    }

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

    if(type_identify_with_class_name(lambda_type->mResultType, "void") && lambda_type->mResultType->mPointerNum == 0)
    {
        LLVMBuildCall(gBuilder, lambda_value.value, llvm_params, num_params, "");

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

unsigned int sNodeTree_create_come_function_call(char* fun_name, unsigned int* params, int num_params, sParserInfo* info)
{
    unsigned int node = alloc_node();

    xstrncpy(gNodes[node].uValue.sFunctionCall.mName, fun_name, VAR_NAME_MAX);
    gNodes[node].uValue.sFunctionCall.mNumParams = num_params;

    int i;
    for(i=0; i<num_params; i++) {
        gNodes[node].uValue.sFunctionCall.mParams[i] = params[i];
    }

    gNodes[node].uValue.sFunctionCall.mMethod = FALSE;
    gNodes[node].uValue.sFunctionCall.mInherit = FALSE;
    
    gNodes[node].mNodeType = kNodeTypeComeFunctionCall;

    gNodes[node].uValue.sFunctionCall.mNumGenerics = info->mNumGenerics;
    for(i=0; i<info->mNumGenerics; i++)
    {
        xstrncpy(gNodes[node].uValue.sFunctionCall.mGenericsTypeNames[i], info->mGenericsTypeNames[i], VAR_NAME_MAX);
    }
    gNodes[node].uValue.sFunctionCall.mVersion = 0;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sFunctionCall.mImplStructName, info->impl_struct_name, VAR_NAME_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_come_function_call(unsigned int node, sCompileInfo* info)
{
    /// rename variables ///
    char fun_name[VAR_NAME_MAX];
    xstrncpy(fun_name, gNodes[node].uValue.sFunctionCall.mName, VAR_NAME_MAX);
    int num_params = gNodes[node].uValue.sFunctionCall.mNumParams;
    unsigned int params[PARAMS_MAX];
    BOOL method = gNodes[node].uValue.sFunctionCall.mMethod;
    BOOL inherit = gNodes[node].uValue.sFunctionCall.mInherit;
    int version = gNodes[node].uValue.sFunctionCall.mVersion;

    BOOL in_come_function = info->in_come_function;
    info->in_come_function = TRUE;
    
    /// create thread handler ///
    char thread_var_name[VAR_NAME_MAX];
    snprintf(thread_var_name, VAR_NAME_MAX, "thread%d", gThreadNum);
    
    sNodeType* var_type = get_typedef("pthread_t");
    
    if(var_type == NULL) {
        var_type = create_node_type_with_class_name("pthread_t");
    }
    
    BOOL readonly = FALSE;
    if(!add_variable_to_table(info->pinfo->lv_table, thread_var_name, var_type, readonly, NULL, -1, FALSE, FALSE))
    {
        return FALSE;
    }
    
    BOOL extern_ = FALSE;
    unsigned int node2 = sNodeTree_create_define_variable(thread_var_name, extern_, info->pinfo);
    
    if(!compile(node2, info)) {
        return FALSE;
    }

    //// thread arg struct ///
    char thread_arg_struct_name[VAR_NAME_MAX];

    snprintf(thread_arg_struct_name, VAR_NAME_MAX, "thread_struct%d", gThreadNum);

    sCLClass* thread_arg_struct_class = alloc_struct(thread_arg_struct_name, FALSE);

    int num_fields = num_params;
    char* field_names[STRUCT_FIELD_MAX];
    sNodeType* fields[STRUCT_FIELD_MAX];
    LLVMValueRef llvm_params[STRUCT_FIELD_MAX];

    int i;
    for(i=0; i<num_params; i++) {
        field_names[i] = calloc(1, sizeof(char)*VAR_NAME_MAX);
        snprintf(field_names[i], VAR_NAME_MAX, "param%d", i);

        params[i] = gNodes[node].uValue.sFunctionCall.mParams[i];
        
        if(!compile(params[i], info)) {
            return FALSE;
        }

        fields[i] = info->type;
    }

    add_fields_to_struct(thread_arg_struct_class, num_fields, field_names, fields);

    sNodeType* thread_arg_struct_type = create_node_type_with_class_pointer(thread_arg_struct_class);
    unsigned int node3 = sNodeTree_struct(thread_arg_struct_type, info->pinfo, info->sname, info->sline, FALSE);

    if(!compile(node3, info)) {
        return FALSE;
    }

    for(i=0; i<num_params; i++) {
        free(field_names[i]);
    }

    /// thread arg ///
    char thread_arg_var_name[VAR_NAME_MAX];

    snprintf(thread_arg_var_name, VAR_NAME_MAX, "thread_arg%d", gThreadNum);
    
    if(!add_variable_to_table(info->pinfo->lv_table, thread_arg_var_name, thread_arg_struct_type, FALSE, NULL, -1, FALSE, FALSE))
    {
        return FALSE;
    }

    unsigned int node4 = sNodeTree_create_define_variable(thread_arg_var_name, FALSE, info->pinfo);

    if(!compile(node4, info)) {
        return FALSE;
    }

    unsigned int node5 = sNodeTree_create_load_variable(thread_arg_var_name, info->pinfo);

    for(i=0; i<num_params; i++) {
        char var_name[VAR_NAME_MAX];
        snprintf(var_name, VAR_NAME_MAX, "param%d", i);

        unsigned int node = sNodeTree_create_store_field(var_name, node5, params[i], info->pinfo);

        if(!compile(node, info)) {
            return FALSE;
        }
    }

    /// create thread fun ///
    char thread_fun_name[VAR_NAME_MAX];
    snprintf(thread_fun_name, VAR_NAME_MAX, "thread_fun%d", gThreadNum);
    
    sParserParam thread_fun_params[PARAMS_MAX];
    
    xstrncpy(thread_fun_params[0].mName, "param", VAR_NAME_MAX);
    thread_fun_params[0].mType = create_node_type_with_class_name("void");
    thread_fun_params[0].mType->mPointerNum++;
    
    int thread_fun_num_params = 1;
    
    sNodeType* thread_fun_result_type = create_node_type_with_class_name("void");
    thread_fun_result_type->mPointerNum++;
    
    char source[1024];
    snprintf(source, 1024, "{ %s* real_param = (%s*)param;", thread_arg_struct_name, thread_arg_struct_name);
    snprintf(source + strlen(source), 1024-strlen(source), "%s(", fun_name);

    for(i=0; i<num_params; i++) {
        snprintf(source + strlen(source), 1024-strlen(source), "real_param->param%d", i);

        if(i != num_params-1) {
            xstrncat(source, ",", 1024);
        }
    }
    
    xstrncat(source, "); }", 1024);

    sParserInfo pinfo;
    memset(&pinfo, 0, sizeof(sParserInfo));
    pinfo.p = source;
    pinfo.source = source;
    snprintf(pinfo.sname, PATH_MAX, "thread_fun%d", gThreadNum);
    pinfo.lv_table = init_var_table();
    pinfo.sline = 1;
    
    if(!add_variable_to_table(pinfo.lv_table, thread_fun_params[0].mName, thread_fun_params[0].mType, readonly, NULL, -1, FALSE, FALSE))
    {
        return FALSE;
    }

    sNodeBlock* thread_fun_block;
    if(!parse_block_easy(&thread_fun_block, FALSE, &pinfo))
    {
        return FALSE;
    }
    
    sVarTable* thread_fun_var_table = pinfo.lv_table;
    
    LLVMBasicBlockRef current_block = info->current_block;

    unsigned int node6 = sNodeTree_create_function(thread_fun_name, "", thread_fun_params, thread_fun_num_params, thread_fun_result_type,  thread_fun_block, FALSE, thread_fun_var_table, "", FALSE, FALSE, FALSE, info->pinfo, FALSE, FALSE, 0, FALSE, 0, "", info->pinfo->sline);
    
    if(!compile(node6, info)) {
        return FALSE;
    }

    llvm_change_block(current_block, info);

    /// call pthread ///
    char pthread_create_fun_name[VAR_NAME_MAX];
    
    xstrncpy(pthread_create_fun_name, "pthread_create", VAR_NAME_MAX);
    
    int pthread_create_fun_num_params = 4;
    unsigned int pthread_create_fun_params[PARAMS_MAX];
    
    pthread_create_fun_params[0] = sNodeTree_create_load_variable(thread_var_name, info->pinfo);
    pthread_create_fun_params[0] = sNodeTree_create_reffernce(pthread_create_fun_params[0], info->pinfo);
    
    pthread_create_fun_params[1] = sNodeTree_create_null(info->pinfo);
    
    pthread_create_fun_params[2] = sNodeTree_create_load_function(thread_fun_name, info->pinfo, info->pinfo->sline);
    
    pthread_create_fun_params[3] = sNodeTree_create_load_variable(thread_arg_var_name, info->pinfo);
    pthread_create_fun_params[3] = sNodeTree_create_reffernce(pthread_create_fun_params[3], info->pinfo);
    
    BOOL method2 = FALSE;
    BOOL inherit2 = FALSE;
    int version2 = 0;
    
    unsigned int node7 = sNodeTree_create_function_call(pthread_create_fun_name, pthread_create_fun_params, pthread_create_fun_num_params, method2, inherit2, version2, info->pinfo);
    
    if(!compile(node7, info)) {
        return FALSE;
    }
    
    info->in_come_function = in_come_function;

    gThreadNum++;

    return TRUE;
}

unsigned int sNodeTree_create_join(sParserInfo* info)
{
    unsigned int node = alloc_node();
    
    gNodes[node].mNodeType = kNodeTypeJoin;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_join(unsigned int node, sCompileInfo* info)
{
    int i;
    for(i=0; i<gThreadNum; i++) {
        char thread_var_name[VAR_NAME_MAX];

        snprintf(thread_var_name, VAR_NAME_MAX, "thread%d", i);

        /// call pthread ///
        char pthread_join_fun_name[VAR_NAME_MAX];
        
        xstrncpy(pthread_join_fun_name, "pthread_join", VAR_NAME_MAX);
        
        int pthread_join_fun_num_params = 2;
        unsigned int pthread_join_fun_params[PARAMS_MAX];
        
        pthread_join_fun_params[0] = sNodeTree_create_load_variable(thread_var_name, info->pinfo);
        
        pthread_join_fun_params[1] = sNodeTree_create_null(info->pinfo);
        
        BOOL method2 = FALSE;
        BOOL inherit2 = FALSE;
        int version2 = 0;
        
        unsigned int node = sNodeTree_create_function_call(pthread_join_fun_name, pthread_join_fun_params, pthread_join_fun_num_params, method2, inherit2, version2, info->pinfo);
        
        if(!compile(node, info)) {
            return FALSE;
        }
    }
    
    return TRUE;
}
