#include "common.h"

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
        xstrncpy(fun_name, gFunctionName, VAR_NAME_MAX);
    }

    int num_generics = gNodes[node].uValue.sFunctionCall.mNumGenerics;
    char generics_type_names[GENERICS_TYPES_MAX][VAR_NAME_MAX];

    int i;
    for(i=0; i<num_generics; i++)
    {
        xstrncpy(generics_type_names[i], gNodes[node].uValue.sFunctionCall.mGenericsTypeNames[i], VAR_NAME_MAX);
    }

    /// method generics types ///
    sNodeType* method_generics_types[GENERICS_TYPES_MAX];
    memset(method_generics_types, 0, sizeof(sNodeType*)*GENERICS_TYPES_MAX);

    int num_method_generics_types = 0;

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
    else if(strcmp(fun_name, "__builtin_assume") == 0) {
        xstrncpy(fun_name, "llvm.assume", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_readcyclecounter") == 0) {
        xstrncpy(fun_name, "llvm.readcyclecounter", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_rotateleft8") == 0) {
        xstrncpy(fun_name, "llvm.fshl.i8", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_rotateleft16") == 0) {
        xstrncpy(fun_name, "llvm.fshl.i16", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_rotateleft32") == 0) {
        xstrncpy(fun_name, "llvm.fshl.i32", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_rotateleft64") == 0) {
        xstrncpy(fun_name, "llvm.fshl.i64", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_rotateright8") == 0) {
        xstrncpy(fun_name, "llvm.fshr.i8", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_rotateright16") == 0) {
        xstrncpy(fun_name, "llvm.fshr.i16", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_rotateright32") == 0) {
        xstrncpy(fun_name, "llvm.fshr.i32", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_rotateright64") == 0) {
        xstrncpy(fun_name, "llvm.fshr.i64", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_bitreverse8") == 0) {
        xstrncpy(fun_name, "llvm.bitreverse.i8", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_bitreverse16") == 0) {
        xstrncpy(fun_name, "llvm.bitreverse.i16", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_bitreverse32") == 0) {
        xstrncpy(fun_name, "llvm.bitreverse.i32", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_bitreverse64") == 0) {
        xstrncpy(fun_name, "llvm.bitreverse.i64", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_canonicalize") == 0) {
        xstrncpy(fun_name, "llvm.canonicalize.f64", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_canonicalizef") == 0) {
        xstrncpy(fun_name, "llvm.canonicalize.f32", VAR_NAME_MAX);
    }
    else if(strcmp(fun_name, "__builtin_canonicalizel") == 0) {
        xstrncpy(fun_name, "llvm.canonicalize.f80", VAR_NAME_MAX);
    }
/*
    else if(strcmp(fun_name, "__builtin_memcpy_inline") == 0) {
        xstrncpy(fun_name, "llvm.memcpy.inline.p0i8.p0i8.i64", VAR_NAME_MAX);
    }
*/
    else if(strcmp(fun_name, "__builtin_object_size") == 0) {
        xstrncpy(fun_name, "llvm.objectsize.i64.p0i8", VAR_NAME_MAX);
        num_params+=2;
        gNodes[node].uValue.sFunctionCall.mParams[2] = sNodeTree_create_true(info->pinfo);
        gNodes[node].uValue.sFunctionCall.mParams[3] = sNodeTree_create_true(info->pinfo);
    }
    else if(strcmp(fun_name, "__builtin_dynamic_object_size") == 0) {
        xstrncpy(fun_name, "llvm.objectsize.i64.p0i8", VAR_NAME_MAX);
        num_params+=2;
        gNodes[node].uValue.sFunctionCall.mParams[2] = sNodeTree_create_true(info->pinfo);
        gNodes[node].uValue.sFunctionCall.mParams[3] = sNodeTree_create_true(info->pinfo);
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

    sNodeType* method_block_generics_type = info->method_block_generics_type;
    if(generics_type) {
        info->method_block_generics_type = clone_node_type(generics_type);
    }

    sFunction* fun = NULL;
    if(inherit) {
        int version = 0;
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
        
        memcpy(real_fun_name, gFunctionName, p - gFunctionName);
        real_fun_name[p-gFunctionName] = '\0';
        
        for(i=n-1; i>=1; i--) {
            char new_fun_name[VAR_NAME_MAX];
            snprintf(new_fun_name, VAR_NAME_MAX, "%s_v%d", real_fun_name, i);
            fun = get_function_from_table(new_fun_name);
            
            if(fun) {
                xstrncpy(fun_name, new_fun_name, VAR_NAME_MAX);
                break;
            }
        }
    }
    else {
        for(i=FUNCTION_VERSION_MAX; i>=1; i--) {
            char new_fun_name[VAR_NAME_MAX];
            snprintf(new_fun_name, VAR_NAME_MAX, "%s_v%d", fun_name, i);
        
            fun = get_function_from_table(new_fun_name);
            
            if(fun) {
                xstrncpy(fun_name, new_fun_name, VAR_NAME_MAX);
                break;
            }
        }
    }
    
    if(fun == NULL) {
        fun = get_function_from_table(fun_name);
    }
//    sFunction* fun = get_function_from_table(fun_name);

    if(fun == NULL) {
        compile_err_msg(info, "function not found(%s)\n", fun_name);
        return TRUE;
    }
    
    char calling_fun_name_before[VAR_NAME_MAX];
    xstrncpy(calling_fun_name_before, info->calling_fun_name, VAR_NAME_MAX);
    xstrncpy(info->calling_fun_name, fun_name, VAR_NAME_MAX);

    if(method) {
        xstrncpy(param_names[0], fun->mParamNames[0], VAR_NAME_MAX);

        LVALUE param = lvalue_params[0];

        if(fun->mParamTypes[0]) {
            sNodeType* fun_param_type = clone_node_type(fun->mParamTypes[0]);

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

            solve_method_generics2(&fun_param_type, param_types[i]);

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

    /// get type of method generics ///
    if(strcmp(fun_name, "llvm.va_start") != 0 && strcmp(fun_name, "llvm.va_end") != 0) {
        for(i=0; i<num_params; i++) {
            if(fun->mParamTypes[i] && param_types[i]) {
                sNodeType* fun_param_type = clone_node_type(fun->mParamTypes[i]);
                sNodeType* param_type = param_types[i];

                if(!get_type_of_method_generics(method_generics_types, fun_param_type, param_type))
                {
                    compile_err_msg(info, "method generics getting type error(%s)", fun_name);
                    return FALSE;
                }
            }
        }

        for(i=0; i<GENERICS_TYPES_MAX; i++) {
            if(!method_generics_types[i]) {
                break;
            }
        }

        num_method_generics_types = i;
    }
    else {
        num_method_generics_types = 0;
    }

    /// param type check ///
    if(!fun->mVarArgs && strcmp(fun_name, "llvm.va_start") != 0 && strcmp(fun_name, "llvm.va_end") != 0) {
        if(fun->mNumParams != num_params) {
            compile_err_msg(info, "function(%s) param number error. fun param number %d, calling %d", fun_name, fun->mNumParams, num_params);
            info->err_num++;
            return TRUE;
        }
    }

    if(strcmp(fun_name, "llvm.va_start") != 0 && strcmp(fun_name, "llvm.va_end") != 0) {
        for(i=0; i<num_params; i++) {
            if(fun->mParamTypes[i] && param_types[i]) {
                sNodeType* fun_param_type = clone_node_type(fun->mParamTypes[i]);
                sNodeType* param_type = param_types[i];

                if(!solve_type(&fun_param_type, generics_type, num_method_generics_types, method_generics_types, info)) {
                    return FALSE;
                }

                if(!substitution_posibility(fun_param_type, param_type, info)) {
                    compile_err_msg(info, "function(%s) param type error %d", fun_name, i);
                    puts("fun param type");
                    show_node_type(fun_param_type);
                    
                    puts("param type");
                    show_node_type(param_type);
                    info->err_num++;
                    return TRUE;
                }
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

    /// call generics function ///
    if(fun->mGenericsFunction) {
        for(i=0; i<num_params; i++) {
            sNodeType* fun_param_type = clone_node_type(fun->mParamTypes[i]);
            sNodeType* param_type = param_types[i];

            if(!solve_type(&fun_param_type, generics_type, num_method_generics_types, method_generics_types, info))
            {
                return FALSE;
            }
        }

        LLVMValueRef llvm_fun= NULL;

        if(!create_generics_function(&llvm_fun, fun, fun_name, generics_type, num_method_generics_types, method_generics_types, info)) {
            return FALSE;
        }

        sNodeType* result_type = clone_node_type(fun->mResultType);

        if(!solve_type(&result_type, generics_type, num_method_generics_types, method_generics_types, info)) {
            return FALSE;
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
        }

    }
    /// call inline function ///
    else if(fun->mBlockText) {
        if(strcmp(fun->mName, info->in_inline_function_name) == 0 && info->in_inline_function) {
            compile_err_msg(info, "inline function can't call itself(%s)\n", fun_name);
            info->err_num++;
            return TRUE;
        }
        
        int sline = gNodes[node].mLine;

        sParserInfo info2;
        memset(&info2, 0, sizeof(sParserInfo));

        sBuf_init(&info2.mConst);

        info2.p = fun->mBlockText;
        xstrncpy(info2.sname, gFName, PATH_MAX);
        info2.source = &fun->mBlockText;
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

        sNodeType* result_type = clone_node_type(fun->mResultType);

        if(!solve_type(&result_type, generics_type, num_method_generics_types, method_generics_types, info)) {
            return FALSE;
        }

        LLVMValueRef inline_result_variable = info->inline_result_variable;
        info->inline_result_variable = NULL;
        if(!(type_identify_with_class_name(result_type, "void") && result_type->mPointerNum == 0))
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

                if(!solve_type(&node_type, generics_type, num_method_generics_types, method_generics_types, info)) {
                    return FALSE;
                }

                var->mLLVMValue = param;
            }
        }
        
        char inline_function_before[VAR_NAME_MAX];
        xstrncpy(inline_function_before, info->in_inline_function_name, VAR_NAME_MAX);
        xstrncpy(info->in_inline_function_name, fun->mSName, VAR_NAME_MAX);

        BOOL in_inline_function = info->in_inline_function;
        info->in_inline_function = TRUE;
        info->inline_sline = fun->mSLine + 1;

        char fun_end_label[PATH_MAX];
        snprintf(fun_end_label, PATH_MAX, "%s_end", fun_name);

        LLVMBasicBlockRef inline_func_end_before = info->inline_func_end;
        LLVMBasicBlockRef inline_func_end = LLVMAppendBasicBlockInContext(gContext, gFunction, fun_end_label);
        info->inline_func_end = inline_func_end;

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
        }

        info->type = clone_node_type(result_type);

        info->inline_result_variable = inline_result_variable;
        info->inline_func_end = inline_func_end_before;
        
        xstrncpy(info->in_inline_function_name, inline_function_before, VAR_NAME_MAX);
    }
    /// call normal function ///
    else {
        for(i=0; i<fun->mNumParams; i++) {
            sNodeType* node_type = clone_node_type(fun->mParamTypes[i]);

            if(!solve_type(&node_type, generics_type, num_method_generics_types, method_generics_types, info)) {
                return FALSE;
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

        sNodeType* result_type = clone_node_type(fun->mResultType);

        if(!solve_type(&result_type, generics_type, num_method_generics_types, method_generics_types, info)) {
            return FALSE;
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
        }
    }

    if(!solve_type(&info->type, generics_type, num_method_generics_types, method_generics_types, info)) {
        return FALSE;
    }

    info->method_block_generics_type = method_block_generics_type;
    xstrncpy(info->calling_fun_name, calling_fun_name_before, VAR_NAME_MAX);

    return TRUE;
}

