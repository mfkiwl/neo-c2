#include "common.h"

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
        char new_fun_name[VAR_NAME_MAX];
        snprintf(new_fun_name, VAR_NAME_MAX, "%s_v%d", fun_name, version);
        xstrncpy(fun_name, new_fun_name, VAR_NAME_MAX);
    }

/*
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
*/
    BOOL result_type_is_method_generics = FALSE;
    if(is_method_generics_type(result_type)) {
        result_type_is_method_generics = TRUE;
        result_type = create_node_type_with_class_name("void");
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

    LLVMBasicBlockRef defer_block = info->defer_block;

    BOOL empty_function = info->empty_function;
    info->empty_function = node_block->mNumNodes == 0;

    char* block_text = NULL;

    char* param_names2[PARAMS_MAX];
    for(i=0; i<PARAMS_MAX; i++) {
        param_names2[i] = param_names[i];
    }

    BOOL generics_function = FALSE;
    if(!add_function_to_table(fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, 0, NULL, FALSE, asm_fun_name, TRUE, node_block->mSource.mBuf, info->sname, info->sline)) {
        fprintf(stderr, "overflow function table\n");
        info->function_node_block = function_node_block;
        return FALSE;
    }

    sFunction* fun = get_function_from_table(fun_name);

    sNodeType* come_function_result_type = gComeFunctionResultType;
    gComeFunctionResultType = fun->mResultType;

    if(gNCDebug && !info->in_generics_function && !info->in_inline_function && !info->in_lambda_function && !info->empty_function && !info->in_thread_function) {
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

        if(gNCDebug && !info->in_generics_function && !info->in_inline_function && !info->in_lambda_function && !info->in_thread_function && !info->empty_function) {
            setCurrentDebugLocation(info->sline, info);
        }

        LVALUE llvm_value;
        llvm_value.value = LLVMBuildAlloca(gBuilder, llvm_type, name);

        LLVMBuildStore(gBuilder, param, llvm_value.value);

        var->mLLVMValue = llvm_value.value;
        var->mConstant = FALSE;
    }

    sNodeType* return_result_type = info->return_result_type;
    info->return_result_type = create_node_type_with_class_name("void");

    if(!compile_block(node_block, info)) {
        info->function_node_block = function_node_block;
        return FALSE;
    }

    if(gNCType && node_block->mTerminated) {
        if(!gNCGlobal && !gNCFunction && !gNCClass && !gNCTypedef) {
            show_node_type(info->type);
        }
        return TRUE;
    }

    if(type_identify_with_class_name(result_type, "void") && result_type->mPointerNum == 0) {
        if(info->defer_block) {
            LLVMBuildBr(gBuilder, info->defer_block);
            llvm_change_block(info->defer_block, info);
        }

        if(info->empty_function) {
            LLVMSetCurrentDebugLocation(gBuilder, NULL);
        }

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

            if(info->defer_block) {
                LLVMBuildBr(gBuilder, info->defer_block);
                llvm_change_block(info->defer_block, info);
            }

            if(gNCDebug && !info->in_generics_function && !info->in_inline_function && !info->in_lambda_function && !info->in_thread_function && !info->empty_function) {
                setCurrentDebugLocation(info->sline, info);
            }
            if(info->empty_function) {
                LLVMSetCurrentDebugLocation(gBuilder, NULL);
            }

            LLVMBuildRet(gBuilder, llvm_value.value);
        }
    }

    if(gNCDebug && !info->in_generics_function && !info->empty_function &&info->in_inline_function && info->in_lambda_function && !info->in_thread_function) {
        finishDebugFunctionInfo();
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
    
    sNodeType* return_result_type2 = clone_node_type(info->return_result_type);

    info->return_result_type = return_result_type;
    info->defer_block = defer_block;
    info->empty_function = empty_function;
    
    if(result_type_is_method_generics) {
        LLVMDeleteFunction(llvm_fun);
        gNodes[node].uValue.sFunction.mResultType = clone_node_type(return_result_type2);
        
        return compile(node, info);
    }

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
    
    //int sline = info->sline;

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
    if(!add_function_to_table(real_fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, num_generics, generics_type_names2, FALSE, NULL, TRUE, block_text, sname, sline)) {
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
    if(!add_function_to_table(fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, 0, NULL, FALSE, NULL, TRUE, block_text, info->sname, info->sline)) {
        fprintf(stderr, "overflow function table\n");
        return FALSE;
    }

    return TRUE;
}

unsigned int sNodeTree_create_method_block(MANAGED char* block, char* block_text_sname, int block_text_sline, sNodeType* result_type, sParserInfo* info)
{
    unsigned int node = alloc_node();
    
    gNodes[node].mNodeType = kNodeTypeMethodBlock;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sMethodBlock.mBlockText = MANAGED block;
    xstrncpy(gNodes[node].uValue.sMethodBlock.mBlockTextSName, block_text_sname, PATH_MAX);
    gNodes[node].uValue.sMethodBlock.mBlockTextSLine = block_text_sline;
    gNodes[node].uValue.sMethodBlock.mVarTable = info->lv_table;
    //gNodes[node].uValue.sMethodBlock.mVarTable = clone_var_table(info->lv_table);
    gNodes[node].uValue.sMethodBlock.mResultType = result_type;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_method_block(unsigned int node, sCompileInfo* info)
{
    char* block_text = gNodes[node].uValue.sMethodBlock.mBlockText;
    sVarTable* lv_table = gNodes[node].uValue.sMethodBlock.mVarTable;
    sNodeType* result_type = gNodes[node].uValue.sMethodBlock.mResultType;

    sFunction* fun = get_function_from_table(info->calling_fun_name);
    
    char block_text_sname[PATH_MAX];
    xstrncpy(block_text_sname, gNodes[node].uValue.sMethodBlock.mBlockTextSName, PATH_MAX);
    int block_text_sline = gNodes[node].uValue.sMethodBlock.mBlockTextSLine;

    int sline = info->sline;

    /// params ///
    if(fun->mNumParams < 2) {
        compile_err_msg(info, "unexpected method block");
        return FALSE;
    }

    sParserParam params[PARAMS_MAX];
    memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);
    sNodeType* lambda_type = fun->mParamTypes[fun->mNumParams-1];

    int num_params = lambda_type->mNumParams;
    sNodeType* result_type2 = clone_node_type(lambda_type->mResultType);

    if(result_type) {
        result_type2 = clone_node_type(result_type);
    }

    if(info->method_block_generics_type) {
        if(!solve_generics(&result_type2, info->method_block_generics_type)) 
        {
            compile_err_msg(info, "Can't solve generics types(3)");
            show_node_type(result_type2);
            show_node_type(info->generics_type);
            return FALSE;
        }
    }

    if(num_params == 0) {
        compile_err_msg(info, "require parent stack parametor");
        return FALSE;
    }

    char type_name[VAR_NAME_MAX];
    create_current_stack_frame_struct(type_name, lv_table);

    sNodeType* current_stack_frame_type = create_node_type_with_class_name(type_name);
    current_stack_frame_type->mPointerNum++;

    xstrncpy(params[0].mName, "parent", VAR_NAME_MAX);
    params[0].mType = current_stack_frame_type;

    int i;
    for(i=1; i<num_params; i++) {
        char param_name[VAR_NAME_MAX];
        snprintf(param_name, VAR_NAME_MAX, "it%d", i-1);

        if(strcmp(param_name, "it0") == 0) {
            xstrncpy(param_name, "it", VAR_NAME_MAX);
        }

        xstrncpy(params[i].mName, param_name, VAR_NAME_MAX);
        params[i].mType = clone_node_type(lambda_type->mParamTypes[i]);

        if(info->method_block_generics_type) {
            if(!solve_generics(&params[i].mType, info->method_block_generics_type)) 
            {
                compile_err_msg(info, "Can't solve generics types(3)");
                show_node_type(params[i].mType);
                show_node_type(info->generics_type);
                return FALSE;
            }
        }
    }

    sNodeBlock* node_block = ALLOC sNodeBlock_alloc();

    sParserInfo pinfo;
    pinfo = *info->pinfo;
    pinfo.p = block_text;

    xstrncpy(pinfo.sname, block_text_sname, PATH_MAX);
    pinfo.sline = block_text_sline;
    
    sVarTable* block_var_table = init_block_vtable(NULL, FALSE);
    pinfo.lv_table = block_var_table;

    for(i=0; i<num_params; i++) {
        sParserParam* param = params + i;

        BOOL readonly = TRUE;
        if(!add_variable_to_table(pinfo.lv_table, param->mName, param->mType, readonly, NULL, -1, FALSE, param->mType->mConstant))
        {
            return FALSE;
        }
    }

    expect_next_character_with_one_forward("{", &pinfo);

    BOOL single_expression = FALSE;
    if(!parse_block(node_block, FALSE, single_expression, &pinfo)) {
        sNodeBlock_free(node_block);
        return FALSE;
    }

    expect_next_character_with_one_forward("}", &pinfo);

    char fun_name[VAR_NAME_MAX];
    create_lambda_name(fun_name, VAR_NAME_MAX, pinfo.module_name);

    BOOL lambda_ = TRUE;
    BOOL simple_lambda_param = TRUE;
    BOOL construct_fun = FALSE;
    BOOL operator_fun = FALSE;

    result_type2->mStatic = TRUE;

    unsigned int node2 = sNodeTree_create_function(fun_name, "", params, num_params, result_type2, MANAGED node_block, lambda_, block_var_table, NULL, operator_fun, construct_fun, simple_lambda_param, &pinfo, FALSE, FALSE, 0, FALSE, -1, fun_name, sline);

    return compile(node2, info);
}
