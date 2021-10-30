#include "common.h"

BOOL create_generics_function(LLVMValueRef* llvm_fun, sFunction* fun, char* fun_name, sNodeType* generics_type, int num_method_generics_types, sNodeType** method_generics_types, sCompileInfo* info)
{
    sNodeType* generics_type_before = info->generics_type;
    if(generics_type) {
        info->generics_type = clone_node_type(generics_type);
    }
    else {
        info->generics_type = NULL;
    }

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
    create_generics_fun_name(real_fun_name, REAL_FUN_NAME_MAX, fun_name,  generics_type, num_method_generics_types, method_generics_types);

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

            if(!solve_type(&param->mType, generics_type, num_method_generics_types, method_generics_types, info)) {
                return FALSE;
            }
        }

        sParserInfo info2;

        memset(&info2, 0, sizeof(sParserInfo));

        sBuf_init(&info2.mConst);

        info2.p = buf;
        xstrncpy(info2.sname, info->sname, PATH_MAX);
        info2.source = &buf;
        info2.module_name = info->pinfo->module_name;
        info2.lv_table = init_block_vtable(NULL, FALSE);

        if(generics_type) {
            info2.mGenericsType = clone_node_type(generics_type);
        }
        else {
            info2.mGenericsType = NULL;
        }

        info2.mNumGenerics = fun->mNumGenerics;
        for(i=0; i<fun->mNumGenerics; i++) {
            info2.mGenericsTypeNames[i] = strdup(fun->mGenericsTypeNames[i]);
        }

        sNodeType* result_type = clone_node_type(fun->mResultType);

        if(!solve_type(&result_type,  generics_type, num_method_generics_types, method_generics_types, info)) {
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
        if(info->generics_type) {
            cinfo.generics_type = clone_node_type(info->generics_type);
        }
        else {
            cinfo.generics_type = NULL;
        }
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

    if(llvm_fun) {
        if(version > 0) {
            char new_fun_name[VAR_NAME_MAX];

            snprintf(new_fun_name, VAR_NAME_MAX, "%s_v%d", fun_name, version);

            char* block_text = NULL;

            char* param_names2[PARAMS_MAX];
            for(i=0; i<PARAMS_MAX; i++) {
                param_names2[i] = param_names[i];
            }

            BOOL generics_function = FALSE;
            if(!add_function_to_table(new_fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, 0, NULL, TRUE, asm_fun_name, TRUE, NULL)) {
                fprintf(stderr, "overflow function table\n");
                return FALSE;
            }

            if(strcmp(asm_fun_name, "") == 0) {
                llvm_fun = LLVMAddFunction(gModule, new_fun_name, function_type);
            }
            else {
                llvm_fun = LLVMAddFunction(gModule, asm_fun_name, function_type);
            }
        }
    }
    else {
        if(version > 0) {
            char new_fun_name[VAR_NAME_MAX];

            snprintf(new_fun_name, VAR_NAME_MAX, "%s_v%d", fun_name, version);

            char* block_text = NULL;

            char* param_names2[PARAMS_MAX];
            for(i=0; i<PARAMS_MAX; i++) {
                param_names2[i] = param_names[i];
            }

            BOOL generics_function = FALSE;
            if(!add_function_to_table(new_fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, 0, NULL, TRUE, asm_fun_name, TRUE, NULL)) {
                fprintf(stderr, "overflow function table\n");
                return FALSE;
            }

            if(strcmp(asm_fun_name, "") == 0) {
                llvm_fun = LLVMAddFunction(gModule, new_fun_name, function_type);
            }
            else {
                llvm_fun = LLVMAddFunction(gModule, asm_fun_name, function_type);
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
            if(!add_function_to_table(fun_name, num_params, param_names2, param_types, result_type, llvm_fun, block_text, generics_function, var_arg, 0, NULL, TRUE, asm_fun_name, TRUE, NULL)) {
                fprintf(stderr, "overflow function table\n");
                return FALSE;
            }
        }
    }

    info->type = create_node_type_with_class_name("void");

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
