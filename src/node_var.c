#include "common.h"

sGenericsStructType* gGenericsStructTypes;
int gSizeGenericsStructTypes;
int gNumGenericsStructTypes;

sStruct* gStructs;
int gSizeStructs;
int gNumStructs;

void free_generics_struct_types()
{
    int i;
    for(i=0; i<gSizeGenericsStructTypes; i++) {
        if(gGenericsStructTypes[i].mName) {
            free(gGenericsStructTypes[i].mName);
        }
    }

    free(gGenericsStructTypes);
}

void free_structs()
{
    int i;
    for(i=0; i<gNumStructs; i++) {
        if(gStructs[i].mName) {
            free(gStructs[i].mName);
        }
    }

    free(gStructs);
}

void node_var_init()
{
    gSizeGenericsStructTypes = 128;
    gGenericsStructTypes = calloc(1, sizeof(sGenericsStructType)*gSizeGenericsStructTypes);
    gNumGenericsStructTypes = 0;

    gSizeStructs = 256;
    gStructs = calloc(1, sizeof(sStruct)*gSizeStructs);
    gNumStructs = 0;
}

void node_var_final()
{
    free_generics_struct_types();
    free_structs();
}

void rehash_generics_struct_types()
{
    int new_size_generics_struct_types = gSizeGenericsStructTypes * 2;
    sGenericsStructType* new_generics_struct_types = calloc(1, sizeof(sGenericsStructType)*new_size_generics_struct_types);

    int i;
    for(i=0; i<gSizeGenericsStructTypes; i++) {
        if(gGenericsStructTypes[i].mName) {
            int hash_value = get_hash_key(gGenericsStructTypes[i].mName, new_size_generics_struct_types);
            sGenericsStructType* p = new_generics_struct_types + hash_value;

            while(1) {
                if(p->mName == NULL) {
                    p->mName = strdup(gGenericsStructTypes[i].mName);

                    p->mType = gGenericsStructTypes[i].mType;
                    break;
                }
                else {
                    p++;

                    if(p == new_generics_struct_types + new_size_generics_struct_types) {
                        p = new_generics_struct_types;
                    }
                    else if(p == new_generics_struct_types + hash_value) {
                        fprintf(stderr, "rehash_generics_struct_types ovewflow\n");
                        exit(1);
                    }
                }
            }
            
        }
    }

    free_generics_struct_types();

    gGenericsStructTypes = new_generics_struct_types;
    gSizeGenericsStructTypes = new_size_generics_struct_types;
}

BOOL add_generics_struct_type_to_table(char* name, sNodeType* node_type)
{
    if(gNumGenericsStructTypes >= gSizeGenericsStructTypes/3) {
        rehash_generics_struct_types();
    }

    int hash_value = get_hash_key(name, gSizeGenericsStructTypes);
    sGenericsStructType* p = gGenericsStructTypes + hash_value;

    while(1) {
        if(p->mName == NULL) {
            p->mName = strdup(name);

            p->mType = clone_node_type(node_type);

            gNumGenericsStructTypes++;

            return TRUE;
        }
        else {
            if(strcmp(p->mName, name) == 0) {
                free(p->mName);
                p->mName = strdup(name);

                p->mType = clone_node_type(node_type);

                return TRUE;
            }
            else {
                p++;

                if(p == gGenericsStructTypes + gSizeGenericsStructTypes) {
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
    int hash_value = get_hash_key(name, gSizeGenericsStructTypes);

    sGenericsStructType* p = gGenericsStructTypes + hash_value;

    while(1) {
        if(p->mName == NULL) {
            return NULL;
        }
        else if(strcmp((char*)p->mName, name) == 0) {
            return p;
        }

        p++;

        if(p == gGenericsStructTypes + gSizeGenericsStructTypes) {
            p = gGenericsStructTypes;
        }
        else if(p == gGenericsStructTypes + hash_value) {
            return NULL;
        }
    }
}

void rehash_struct()
{
    int new_size_structs = gSizeStructs * 2;
    sStruct* new_strucs = calloc(1, sizeof(sStruct)*new_size_structs);

    int i;
    for(i=0; i<gSizeStructs; i++) {
        if(gStructs[i].mName) {
            int hash_value = get_hash_key(gStructs[i].mName, new_size_structs);
            sStruct* p = new_strucs + hash_value;

            while(1) {
                if(p->mName == NULL) {
                    p->mName = strdup(gStructs[i].mName);

                    p->mNodeType = gStructs[i].mNodeType;
                    p->mLLVMType = gStructs[i].mLLVMType;
                    p->mUndefinedBody = gStructs[i].mUndefinedBody;
                    break;
                }
                else {
                    p++;

                    if(p == new_strucs + new_size_structs) {
                        p = new_strucs;
                    }
                    else if(p == new_strucs + hash_value) {
                        fprintf(stderr, "overflow rehash_struct\n");
                        exit(2);
                    }
                }
            }
        }
    }

    free_structs();

    gSizeStructs = new_size_structs;
    gStructs = new_strucs;
}

BOOL add_struct_to_table(char* name, sNodeType* node_type, LLVMTypeRef llvm_type, BOOL undefined_body)
{
    if(gNumStructs >= gSizeStructs/3) {
        rehash_struct();
    }

    int hash_value = get_hash_key(name, gSizeStructs);
    sStruct* p = gStructs + hash_value;

    while(1) {
        if(p->mName == NULL) {
            p->mName = strdup(name);

            p->mNodeType = clone_node_type(node_type);
            p->mLLVMType = llvm_type;
            p->mUndefinedBody = undefined_body;

            gNumStructs++;

            return TRUE;
        }
        else {
            if(strcmp(p->mName, name) == 0) {
                p->mNodeType = clone_node_type(node_type);
                p->mLLVMType = llvm_type;
                p->mUndefinedBody = undefined_body;

                return TRUE;
            }
            else {
                p++;

                if(p == gStructs + gSizeStructs) {
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
    int hash_value = get_hash_key(name, gSizeStructs);

    sStruct* p = gStructs + hash_value;

    while(1) {
        if(p->mName == NULL) {
            return NULL;
        }
        else if(strcmp((char*)p->mName, name) == 0) {
            return p;
        }

        p++;

        if(p == gStructs + gSizeStructs) {
            p = gStructs;
        }
        else if(p == gStructs + hash_value) {
            return NULL;
        }
    }
}

unsigned int sNodeTree_create_define_variable(char* var_name, BOOL extern_, BOOL global, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDefineVariable;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sDefineVariable.mVarName, var_name, VAR_NAME_MAX);
    gNodes[node].uValue.sDefineVariable.mGlobal = global;
    gNodes[node].uValue.sDefineVariable.mExtern = extern_;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_define_variable(unsigned int node, sCompileInfo* info)
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

    sNodeType* var_type = var->mType;

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

    if(!create_generics_struct_type(var_type)) {
        compile_err_msg(info, "invalid type %s(2)", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    LLVMTypeRef llvm_type = create_llvm_type_from_node_type(var_type);

#if defined(__X86_64_CPU__ ) || defined(__DARWIN__)
    if(type_identify_with_class_name(var_type, "__builtin_va_list") || type_identify_with_class_name(var_type, "va_list")) {
        llvm_type = LLVMArrayType(llvm_type, 1);
    }
#endif

    if(extern_) {
        LLVMValueRef global = LLVMGetNamedGlobal(gModule, var_name);
        if(global == NULL) {
            LLVMValueRef alloca_value = LLVMAddGlobal(gModule, llvm_type, var_name);

            LLVMSetExternallyInitialized(alloca_value, TRUE);
if(var_type->mPointerNum > 0) {
    LLVMSetAlignment(alloca_value, 4);
}

            var->mLLVMValue = alloca_value;
        }
        else {
            var->mLLVMValue = global;
        }
    }
    else if(global) {
        LLVMValueRef global = LLVMGetNamedGlobal(gModule, var_name);

        if(global) {
            LLVMDeleteGlobal(global);
        }

        LLVMValueRef alloca_value = LLVMAddGlobal(gModule, llvm_type, var_name);
if(var_type->mPointerNum > 0) {
    LLVMSetAlignment(alloca_value, 4);
}

        if(var_type->mArrayDimentionNum == 1) {
            /// zero initializer ///
            sNodeType* element_node_type = clone_node_type(var_type);
            element_node_type->mArrayDimentionNum = 0;
            LLVMTypeRef llvm_element_type = create_llvm_type_from_node_type(element_node_type);

            LLVMValueRef values[element_node_type->mArrayNum[0]];

            int i;
            LLVMValueRef zero_value;
            if(element_node_type->mPointerNum > 0)
            {
                zero_value = LLVMConstNull(llvm_element_type);
            }
            else {
                zero_value = LLVMConstInt(llvm_element_type, 0, FALSE);
            }

            for(i=0; i<element_node_type->mArrayNum[0]; i++) 
            {
                values[i] = zero_value;
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
            LLVMValueRef zero_value;
            if(element_node_type->mPointerNum > 0)
            {
                zero_value = LLVMConstNull(llvm_element_type);
            }
            else {
                zero_value = LLVMConstInt(llvm_element_type, 0, FALSE);
            }
            for(i=0; i<element_node_type->mArrayNum[0]*element_node_type->mArrayNum[1]; i++) {
                values[i] = zero_value;
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
            LLVMValueRef zero_value;
            if(element_node_type->mPointerNum > 0)
            {
                zero_value = LLVMConstNull(llvm_element_type);
            }
            else {
                zero_value = LLVMConstInt(llvm_element_type, 0, FALSE);
            }
            for(i=0; i<element_node_type->mArrayNum[0]*element_node_type->mArrayNum[1]*element_node_type->mArrayNum[2]; i++) {
                values[i] = zero_value;
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
        else if(var_type->mPointerNum > 0) {
            LLVMValueRef value = LLVMConstNull(llvm_type);
            LLVMSetInitializer(alloca_value, value);
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

#ifdef __32BIT_CPU__
            sNodeType* left_type = create_node_type_with_class_name("int");

            if(!cast_right_type_to_left_type(left_type, &llvm_value.type, &llvm_value, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
            dec_stack_ptr(1, info);

            LLVMValueRef len_value = llvm_value.value;

            LLVMValueRef alloca_value = LLVMBuildArrayAlloca(gBuilder, llvm_type, len_value, var_name);
            var->mLLVMValue = alloca_value;
#else
            sNodeType* left_type = create_node_type_with_class_name("long");

            if(!cast_right_type_to_left_type(left_type, &llvm_value.type, &llvm_value, info))
            {
                compile_err_msg(info, "Cast failed");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }
            dec_stack_ptr(1, info);

            LLVMValueRef len_value = llvm_value.value;

            LLVMValueRef alloca_value = LLVMBuildArrayAlloca(gBuilder, llvm_type, len_value, var_name);
            var->mLLVMValue = alloca_value;
#endif
        }
        else if(var_type->mChannel) {
            LLVMBasicBlockRef this_block = LLVMGetInsertBlock(gBuilder);
            LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(gFunction);
            LLVMValueRef inst = LLVMGetFirstInstruction(entry_block);
            if(inst != NULL) {
                LLVMPositionBuilderBefore(gBuilder, inst);
            }

            LLVMValueRef alloca_value = LLVMBuildAlloca(gBuilder, llvm_type, var_name);

            llvm_change_block(this_block, info);

            var->mLLVMValue = alloca_value;

            /// call pipe ///
            char fun_name[VAR_NAME_MAX];
            
            xstrncpy(fun_name, "pipe", VAR_NAME_MAX);
            
            int num_params = 1;
            unsigned int params[PARAMS_MAX];
            
            params[0] = sNodeTree_create_load_variable(var_name, info->pinfo);
            
            BOOL method2 = FALSE;
            BOOL inherit2 = FALSE;
            int version2 = 0;
            
            unsigned int node = sNodeTree_create_function_call(fun_name, params, num_params, method2, inherit2, version2, info->pinfo);
            
            if(!compile(node, info)) {
                return FALSE;
            }
        }
        else {
            LLVMBasicBlockRef this_block = LLVMGetInsertBlock(gBuilder);
            LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(gFunction);
            LLVMValueRef inst = LLVMGetFirstInstruction(entry_block);
            if(inst != NULL) {
                LLVMPositionBuilderBefore(gBuilder, inst);
            }

            LLVMValueRef alloca_value = LLVMBuildAlloca(gBuilder, llvm_type, var_name);

            llvm_change_block(this_block, info);

            var->mLLVMValue = alloca_value;
        }
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_create_store_variable(char* var_name, int right, BOOL alloc, BOOL global, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStoreVariable;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sStoreVariable.mVarName, var_name, VAR_NAME_MAX);
    gNodes[node].uValue.sStoreVariable.mAlloc = alloc;
    gNodes[node].uValue.sStoreVariable.mGlobal = global;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}


BOOL compile_store_variable(unsigned int node, sCompileInfo* info)
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

    if(!compile(right_node, info)) {
        return FALSE;
    }

    sNodeType* right_type = clone_node_type(info->type);

    /// type inference ///
    sNodeType* left_type = NULL;
    if(var->mType == NULL) {
        right_type->mStatic = FALSE;
        var->mType = clone_node_type(right_type);
        left_type = var->mType;
    }
    else {
        left_type = var->mType;
    }

    BOOL static_ = var->mType->mStatic;

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

    if(!create_generics_struct_type(left_type)) {
        compile_err_msg(info, "invalid type %s(3)", var_name);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

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

    /// std::move ///
    if(left_type->mHeap && right_type->mHeap) {
        sVar* var = rvalue.var;
        if(var) {
            var->mLLVMValue = NULL;
        }
    }

    BOOL constant = var->mConstant;

    if(alloc) {
        if(constant) {
            var->mLLVMValue = rvalue.value;

            info->type = left_type;

            if(left_type->mHeap) {
                remove_object_from_right_values(rvalue.value, info);
            }
        }
        else if(global) {
            LLVMValueRef global = LLVMGetNamedGlobal(gModule, var_name);

            if(global) {
                LLVMDeleteGlobal(global);
            }

            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

#if defined(__X86_64_CPU__ ) || defined(__DARWIN__)
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
                remove_object_from_right_values(rvalue.value, info);
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
                    remove_object_from_right_values(rvalue.value, info);
                }
            }
        }
        else {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

#if defined(__X86_64_CPU__ ) || defined(__DARWIN__)
            if(type_identify_with_class_name(left_type, "__builtin_va_list") || type_identify_with_class_name(left_type, "va_list")) {
                llvm_type = LLVMArrayType(llvm_type, 1);
            }
#endif


            LLVMBasicBlockRef this_block = LLVMGetInsertBlock(gBuilder);
            LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(gFunction);
            LLVMValueRef inst = LLVMGetFirstInstruction(entry_block);
            if(inst != NULL) {
                LLVMPositionBuilderBefore(gBuilder, inst);
            }

            LLVMValueRef alloca_value = LLVMBuildAlloca(gBuilder, llvm_type, var_name);

            llvm_change_block(this_block, info);

            LLVMBuildStore(gBuilder, rvalue.value, alloca_value);

            var->mLLVMValue = alloca_value;

            info->type = left_type;

            if(left_type->mHeap) {
                remove_object_from_right_values(rvalue.value, info);
            }
        }
    }
    else if(constant) {
        var->mLLVMValue = rvalue.value;

        if(left_type->mHeap) {
            remove_object_from_right_values(rvalue.value, info);
        }

        info->type = left_type;
    }
    else {
        LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

#if defined(__X86_64_CPU__ ) || defined(__DARWIN__)
        if(type_identify_with_class_name(left_type, "__builtin_va_list") || type_identify_with_class_name(left_type, "va_list")) {
            llvm_type = LLVMArrayType(llvm_type, 1);
        }
#endif

        LLVMValueRef alloca_value = var->mLLVMValue;

        LLVMBuildStore(gBuilder, rvalue.value, alloca_value);

        info->type = left_type;

        if(left_type->mHeap) {
            remove_object_from_right_values(rvalue.value, info);
        }
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

BOOL compile_clone(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    LVALUE lvalue = *get_value_from_stack(-1);

    if(lvalue.value == NULL) {
        compile_err_msg(info, "Can't get address of this value on clone operator");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    sNodeType* left_type = clone_node_type(info->type);
    sNodeType* left_type2 = clone_node_type(left_type);
    left_type2->mHeap = TRUE;

    LLVMValueRef obj = clone_object(left_type, lvalue.value, info);

    dec_stack_ptr(1, info);

    LVALUE llvm_value;
    llvm_value.value = obj;
    llvm_value.type = clone_node_type(left_type2);
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    append_object_to_right_values(llvm_value.value, left_type2, info);

    info->type = clone_node_type(left_type2);

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

BOOL compile_reffernce(unsigned int node, sCompileInfo* info)
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

BOOL compile_dereffernce(unsigned int node, sCompileInfo* info)
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

    info->type = clone_node_type(derefference_type);

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
        compile_err_msg(info, "comelang can't get an element from this type.(2)");
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
        var_type->mArrayDimentionNum = 0;
        //var_type->mPointerNum++;
    }
    else {
        var_type->mPointerNum-=num_dimention;
    }
    var_type->mHeap = right_type->mHeap;

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

        sNodeType* node_type = clone_node_type(var_type);
        node_type->mPointerNum = 1;
        node_type->mArrayDimentionNum = 0;

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

        sNodeType* node_type = clone_node_type(var_type);
        node_type->mPointerNum = 1;
        node_type->mArrayDimentionNum = 0;

        LLVMBuildStore(gBuilder, rvalue.value, load_element_addresss);

        dec_stack_ptr(2+num_dimention, info);
        push_value_to_stack_ptr(&rvalue, info);

        info->type = clone_node_type(right_type);
    }
    else if(left_type->mPointerNum > 0) {
        LLVMValueRef lvalue2 = lvalue.value;

        LLVMValueRef element_address = lvalue2;
        for(i=0; i<num_dimention; i++) {
            element_address = LLVMBuildGEP(gBuilder, element_address, &mvalue[i].value,  1, "element_address");
            if(i != num_dimention-1) {
                element_address = LLVMBuildLoad(gBuilder, element_address, "element_address");
            }
        }

        LLVMBuildStore(gBuilder, rvalue.value, element_address);

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

    if(type_identify_with_class_name(right_type, "void") && right_type->mPointerNum == 0)
    {
        info->type = create_node_type_with_class_name("void");
    }
    else {
        LVALUE lvalue = *get_value_from_stack(-1);
        dec_stack_ptr(1, info);

        if(!cast_right_type_to_left_type(right_type, &left_type, &lvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        push_value_to_stack_ptr(&lvalue, info);

        info->type = clone_node_type(lvalue.type);
    }

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

    add_typedef(name, clone_node_type(node_type), TRUE);

    return node;
}

BOOL compile_typedef(unsigned int node, sCompileInfo* info)
{
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

BOOL compile_sizeof(unsigned int node, sCompileInfo* info)
{
    sNodeType* node_type = gNodes[node].uValue.sSizeOf.mType;
    sNodeType* node_type2 = clone_node_type(node_type);

    //LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type2);
    
    if(!solve_generics(&node_type2, info->generics_type)) {
        compile_err_msg(info, "can't solve generics types");
        return FALSE;
    }

    int alignment = 0;
    uint64_t alloc_size = get_size_from_node_type(node_type2, &alignment);

#ifdef __32BIT_CPU__
    LLVMTypeRef int_type = create_llvm_type_with_class_name("int");
    LLVMValueRef alloc_size_value = LLVMConstInt(int_type, alloc_size, FALSE);

    /// result ///
    LVALUE llvm_value;
    llvm_value.value = alloc_size_value;
    llvm_value.type = create_node_type_with_class_name("int");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("int");
#else
    LLVMTypeRef long_type = create_llvm_type_with_class_name("long");
    LLVMValueRef alloc_size_value = LLVMConstInt(long_type, alloc_size, FALSE);

    //LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type2);

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
#endif

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
    
    if(!solve_generics(&node_type, info->generics_type)) {
        compile_err_msg(info, "can't solve generics types");
        return FALSE;
    }

    LVALUE llvm_value = *get_value_from_stack(-1);

    dec_stack_ptr(1, info);

#ifdef __32BIT_CPU__
    int alignment = 0;
    uint32_t alloc_size = get_size_from_node_type(node_type, &alignment);

    LLVMTypeRef int_type = create_llvm_type_with_class_name("int");
    LLVMValueRef value = LLVMConstInt(int_type, alloc_size, FALSE);

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
    int alignment = 0;
    uint64_t alloc_size = get_size_from_node_type(node_type, &alignment);

    LLVMTypeRef long_type = create_llvm_type_with_class_name("long");
    LLVMValueRef value = LLVMConstInt(long_type, alloc_size, FALSE);

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

BOOL compile_alignof(unsigned int node, sCompileInfo* info)
{
    sNodeType* node_type = gNodes[node].uValue.sSizeOf.mType;
    sNodeType* node_type2 = clone_node_type(node_type);

    LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type2);

    int align_size = get_llvm_alignment_from_node_type(node_type2);

#ifdef __32BIT_CPU__
    LLVMTypeRef int_type = create_llvm_type_with_class_name("int");
    LLVMValueRef value = LLVMConstInt(int_type, align_size, FALSE);
#else
    LLVMTypeRef long_type = create_llvm_type_with_class_name("long");
    LLVMValueRef value = LLVMConstInt(long_type, align_size, FALSE);
#endif

#ifdef __32BIT_CPU__
    /// result ///
    LVALUE llvm_value;
    llvm_value.value = value;
    //llvm_value.value = LLVMAlignOf(llvm_type);
    llvm_value.type = create_node_type_with_class_name("int");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("int");
#else
    /// result ///
    LVALUE llvm_value;
    llvm_value.value = value;
    //llvm_value.value = LLVMAlignOf(llvm_type);
    llvm_value.type = create_node_type_with_class_name("long");
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("long");
#endif

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

    int align_size = get_llvm_alignment_from_node_type(llvm_value.type);

#ifdef __32BIT_CPU__
    LLVMTypeRef int_type = create_llvm_type_with_class_name("int");
    LLVMValueRef value = LLVMConstInt(int_type, align_size, FALSE);
#else
    LLVMTypeRef long_type = create_llvm_type_with_class_name("long");
    LLVMValueRef value = LLVMConstInt(long_type, align_size, FALSE);
#endif

    //LLVMValueRef value = LLVMAlignOf(llvm_type);

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

unsigned int sNodeTree_create_load_function(char* fun_name, sParserInfo* info, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadFunction;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

    xstrncpy(gNodes[node].uValue.sLoadFunction.mFunName, fun_name, VAR_NAME_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_load_function(unsigned int node, sCompileInfo* info)
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

unsigned int sNodeTree_create_array_initializer(char* name, int num_initialize_array_value, unsigned int* initialize_array_value, unsigned int left_node, sParserInfo* info)
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

BOOL compile_array_initializer(unsigned int node, sCompileInfo* info)
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
        LLVMValueRef** values = (LLVMValueRef**)calloc(1, sizeof(LLVMValueRef*)*var_type->mArrayNum[0]);

        int i;
        for(i=0; i<var_type->mArrayNum[0]; i++) {
            values[i] = calloc(1, sizeof(LLVMValueRef)*INIT_ARRAY_MAX);
        }

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

        for(i=0; i<var_type->mArrayNum[0]; i++) {
            free(values[i]);
        }
        free(values);
    }
    else if(var_type->mArrayDimentionNum == 3) {
        /// zero initializer ///
        ///LLVMValueRef values[var_type->mArrayNum[0]][var_type->mArrayNum[1]][INIT_ARRAY_MAX];
        LLVMValueRef*** values = calloc(1, sizeof(LLVMValueRef**)*var_type->mArrayNum[0]);

        int i;
        int j;

        for(i=0; i<var_type->mArrayNum[0]; i++) {
            values[i] = calloc(1, sizeof(LLVMValueRef*)*var_type->mArrayNum[1]);

            for(j=0; j<var_type->mArrayNum[1]; j++) {
                values[i][j] = calloc(1, sizeof(LLVMValueRef)*INIT_ARRAY_MAX);
            }
        }

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

        for(i=0; i<var_type->mArrayNum[0]; i++) {
            for(j=0; j<var_type->mArrayNum[1]; j++) {
                free(values[i][j]);
            }
            free(values[i]);
        }

        free(values);
    }

    info->type = create_node_type_with_class_name("void");

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

    if(is_typeof_type(node_type2))
    {
        if(!solve_typeof(&node_type2, info))
        {
            compile_err_msg(info, "Can't solve typeof types");
            show_node_type(node_type2);
            info->err_num++;
            return FALSE;
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

BOOL compile_store_address(unsigned int node, sCompileInfo* info)
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

    info->type = create_node_type_with_class_name("void");

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

BOOL compile_load_address_value(unsigned int node, sCompileInfo* info)
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

BOOL compile_func_name(unsigned int node, sCompileInfo* info)
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


BOOL compile_load_variable(unsigned int node, sCompileInfo* info)
{
    char* var_name = gNodes[node].uValue.sLoadVariable.mVarName;

    sVar* var = get_variable_from_table(info->pinfo->lv_table, var_name);

    BOOL global = var->mGlobal;
    BOOL constant = var->mConstant;

    sNodeType* var_type = clone_node_type(var->mType);

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

    LLVMValueRef var_address = var->mLLVMValue;

    if(var_address == NULL) {
        compile_err_msg(info, "no variable address(%s)", var_name);
        return FALSE;
    }

    LVALUE llvm_value;

    if(constant) {
        llvm_value.value = var_address;

        llvm_value.type = var_type;
        llvm_value.address = var_address;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(var_type);
    }
    else if(global) {
        llvm_value.value = LLVMBuildLoad(gBuilder, var_address, var_name);

        llvm_value.type = var_type;
        llvm_value.address = var_address;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(var_type);
    }
    else if(var_type->mArrayDimentionNum >= 1 || var_type->mDynamicArrayNum != 0) {
        llvm_value.value = var_address;

        llvm_value.type = var_type;
        llvm_value.address = var_address;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(var_type);
    }
    else {
        if(type_identify_with_class_name(var_type, "__builtin_va_list") || type_identify_with_class_name(var_type, "va_list") || type_identify_with_class_name(var_type, "__va_list")) 
        {
#if defined(__X86_64_CPU__ ) && !defined(__DARWIN__)

            LLVMValueRef indices[2];

            LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

            indices[0] = LLVMConstInt(llvm_type, 0, FALSE);
            indices[1] = LLVMConstInt(llvm_type, 0, FALSE);

            llvm_value.value = LLVMBuildGEP(gBuilder, var_address, indices, 2, "gep");
#else
            llvm_value.value = var_address;
#endif

            llvm_value.type = var_type;
            llvm_value.address = var_address;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(var_type);
        }
        else {
            llvm_value.value = LLVMBuildLoad(gBuilder, var_address, var_name);
            llvm_value.var = var;

            llvm_value.type = var_type;
            llvm_value.address = var_address;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(var_type);
        }
    }

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

BOOL compile_struct(unsigned int node, sCompileInfo* info)
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
    
    info->type = create_node_type_with_class_name("void");

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

BOOL compile_union(unsigned int node, sCompileInfo* info)
{
    sNodeType* node_type = gNodes[node].uValue.sStruct.mType;
    BOOL undefined_body = gNodes[node].uValue.sStruct.mUndefinedBody;

    create_llvm_union_type(node_type, NULL, undefined_body, info);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_create_object(sNodeType* node_type, unsigned int object_num, int num_params, unsigned int* params, char* sname, int sline, BOOL gc, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeObject;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sObject.mType = clone_node_type(node_type);
    gNodes[node].uValue.sObject.mNumParams = num_params;
    gNodes[node].uValue.sObject.mGC = gc;

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

BOOL compile_object(unsigned int node, sCompileInfo* info)
{
    sNodeType* node_type = gNodes[node].uValue.sObject.mType;
    int num_params = gNodes[node].uValue.sObject.mNumParams;
    unsigned int params[PARAMS_MAX];
    BOOL gc = gNodes[node].uValue.sObject.mGC;

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

    if(!solve_generics(&node_type2, node_type2)) 
    {
        compile_err_msg(info, "Can't solve generics types(3)");
        show_node_type(node_type2);
        show_node_type(info->generics_type);
        info->err_num++;

        return FALSE;
    }

    if(!create_generics_struct_type(node_type2)) {
        compile_err_msg(info, "invalid type %s(6)", CLASS_NAME(node_type2->mClass));
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    unsigned int left_node = gNodes[node].mLeft;

    LLVMValueRef object_num;
    if(left_node == 0) {
#ifdef __32BIT_CPU__
        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");
#else
        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("long");
#endif
        object_num = LLVMConstInt(llvm_type, 1, FALSE);
    }
    else {
        if(!compile(left_node, info)) {
            return FALSE;
        }

#ifdef __32BIT_CPU__
        sNodeType* left_type = create_node_type_with_class_name("int");
#else
        sNodeType* left_type = create_node_type_with_class_name("long");
#endif

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
    else if(gc) {
        /// calloc ///
        int num_params = 1;

        LLVMValueRef llvm_params[PARAMS_MAX];
        memset(llvm_params, 0, sizeof(LLVMValueRef)*PARAMS_MAX);

        char* fun_name = "GC_malloc";

        LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type2);

        int alignment = 0;
        uint64_t alloc_size = get_size_from_node_type(node_type2, &alignment);

#ifdef __32BIT_CPU__
        LLVMTypeRef long_type = create_llvm_type_with_class_name("int");
#else
        LLVMTypeRef long_type = create_llvm_type_with_class_name("long");
#endif
        llvm_params[0] = LLVMConstInt(long_type, alloc_size, FALSE);

        llvm_params[0] = LLVMBuildMul(gBuilder, llvm_params[0], object_num, "mul");

        LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, fun_name);

        if(llvm_fun == NULL) {
            compile_err_msg(info, "require calloc difinition to create object");
            return FALSE;
        }

        LLVMValueRef address = LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "fun_result");

        node_type2->mPointerNum++;
        node_type2->mHeap = FALSE;

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

        //append_object_to_right_values(address, node_type2, info);

        info->type = clone_node_type(node_type2);
    }
    else {
        /// calloc ///
        int num_params = 2;

        LLVMValueRef llvm_params[PARAMS_MAX];
        memset(llvm_params, 0, sizeof(LLVMValueRef)*PARAMS_MAX);

        char* fun_name = "calloc";
        //char* fun_name = "nccalloc";

        llvm_params[0] = object_num;

        LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type2);

        int alignment = 0;
        uint64_t alloc_size = get_size_from_node_type(node_type2, &alignment);

#ifdef __32BIT_CPU__
        LLVMTypeRef long_type = create_llvm_type_with_class_name("int");
#else
        LLVMTypeRef long_type = create_llvm_type_with_class_name("long");
#endif
        llvm_params[1] = LLVMConstInt(long_type, alloc_size, FALSE);

        LLVMValueRef llvm_fun = LLVMGetNamedFunction(gModule, fun_name);

        if(llvm_fun == NULL) {
            compile_err_msg(info, "require calloc difinition to create object");
            return FALSE;
        }

        LLVMValueRef address = LLVMBuildCall(gBuilder, llvm_fun, llvm_params, num_params, "fun_result");

        node_type2->mPointerNum++;
        node_type2->mHeap = TRUE;

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

BOOL compile_delete(unsigned int node, sCompileInfo* info)
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

    //node_type->mHeap = TRUE;

    free_object(node_type, llvm_value.value, info);

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

BOOL compile_borrow(unsigned int node, sCompileInfo* info)
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

    sNodeType* node_type = clone_node_type(info->type);

    llvm_value.type->mHeap = FALSE;
    node_type->mHeap = FALSE;

    remove_object_from_right_values(llvm_value.value, info);

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = node_type;

    return TRUE;
}

unsigned int sNodeTree_create_nomove(unsigned int object_node, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeNoMove;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = object_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_nomove(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(left_node == 0) {
        compile_err_msg(info, "require nomove target object");
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

    if(is_right_values(llvm_value.value, info)) {
        llvm_value.type->mHeap = TRUE;
        node_type->mHeap = TRUE;
        remove_object_from_right_values(llvm_value.value, info);
    }
    else {
        if(llvm_value.var) {
            llvm_value.var = NULL;
            node_type->mHeap = FALSE;
            llvm_value.type->mHeap = FALSE;
        }
    }

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = node_type;

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

BOOL compile_dummy_heap(unsigned int node, sCompileInfo* info)
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
    llvm_value.type->mDummyHeap = TRUE;

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


BOOL compile_managed(unsigned int node, sCompileInfo* info)
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

BOOL compile_stack_object(unsigned int node, sCompileInfo* info)
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

        LLVMBasicBlockRef this_block = LLVMGetInsertBlock(gBuilder);
        LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(gFunction);
        LLVMValueRef inst = LLVMGetFirstInstruction(entry_block);
        if(inst != NULL) {
            LLVMPositionBuilderBefore(gBuilder, inst);
        }

        llvm_value.value = LLVMBuildAlloca(gBuilder, llvm_type, "stack_object");

        llvm_change_block(this_block, info);

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

BOOL compile_store_field(unsigned int node, sCompileInfo* info)
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

            char* field_name = klass->mFieldName[i];

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
            compile_err_msg(info, "The field(%s) is not found(1) in struct %s", var_name, CLASS_NAME(klass));
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }
    else if(field_index == -1) {
        compile_err_msg(info, "The field(%s) is not found(2) in struct %s", var_name, CLASS_NAME(left_type->mClass));
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

    if(!solve_generics(&left_type, info->generics_type)) {
        compile_err_msg(info, "Solve Generics Error");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

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

        field_address = LLVMBuildCast(gBuilder, LLVMBitCast, field_address, llvm_type, "icastN");
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

BOOL compile_load_field(unsigned int node, sCompileInfo* info)
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
            char* field_name = klass->mFieldName[i];

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
            compile_err_msg(info, "The field(%s) is not found(1) in %s", var_name, CLASS_NAME(klass));
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }
    else if(field_index == -1) {
        compile_err_msg(info, "The field(%s) is not found(2) in %s", var_name, CLASS_NAME(left_type->mClass));
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

        LVALUE llvm_value;
        
        LLVMValueRef field_address;
        if(field_type->mArrayDimentionNum > 0) {
            if(left_type->mPointerNum == 0) {
                field_address = LLVMBuildStructGEP(gBuilder, lvalue.address, field_index, "field");
            }
            else {
                field_address = LLVMBuildStructGEP(gBuilder, lvalue.value, field_index, "field");
            }
            llvm_value.value = field_address; 
        }
        else if(left_type->mPointerNum == 0) {
            field_address = LLVMBuildStructGEP(gBuilder, lvalue.address, field_index, "field");
            
            sNodeType* field_type2 = clone_node_type(field_type);

            field_type2->mPointerNum++;

            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(field_type2);

            field_address = LLVMBuildCast(gBuilder, LLVMBitCast, field_address, llvm_type, "icastO");
            llvm_value.value = LLVMBuildLoad(gBuilder, field_address, var_name);
        }
        else {
            field_address = LLVMBuildStructGEP(gBuilder, lvalue.value, field_index, "field");
            
            sNodeType* field_type2 = clone_node_type(field_type);

            field_type2->mPointerNum++;

            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(field_type2);

            field_address = LLVMBuildCast(gBuilder, LLVMBitCast, field_address, llvm_type, "icastP");
            llvm_value.value = LLVMBuildLoad(gBuilder, field_address, var_name);
        }

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

        if(info->generics_type) {
            if(!solve_generics(&field_type, info->generics_type)) 
            {
                compile_err_msg(info, "Can't solve generics types(3)");
                show_node_type(field_type);
                show_node_type(info->generics_type);
                info->err_num++;

                return FALSE;
            }
        }

        LVALUE llvm_value;
        LLVMValueRef field_address;
        if(field_type->mArrayDimentionNum > 0) {
            if(left_type->mPointerNum == 0) {
                field_address = LLVMBuildStructGEP(gBuilder, lvalue.address, field_index, "field");
            }
            else {
                field_address = LLVMBuildStructGEP(gBuilder, lvalue.value, field_index, "field");
            }
            llvm_value.value = field_address; 
        }
        else if(left_type->mPointerNum == 0) {
            field_address = LLVMBuildStructGEP(gBuilder, lvalue.address, field_index, "field");
            llvm_value.value = LLVMBuildLoad(gBuilder, field_address, var_name);
        }
        else {
            field_address = LLVMBuildStructGEP(gBuilder, lvalue.value, field_index, "field");
            llvm_value.value = LLVMBuildLoad(gBuilder, field_address, var_name);
        }

        llvm_value.type = clone_node_type(field_type);
        llvm_value.address = field_address;
        llvm_value.var = NULL;
        llvm_value.binded_value = TRUE;
        llvm_value.load_field = TRUE;

        dec_stack_ptr(1, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(field_type);
    }

    info->type->mHeap = FALSE;

    return TRUE;
}

unsigned int sNodeTree_create_load_channel_element(unsigned int array, unsigned int num_chanel, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLoadChannelElement;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sLoadElement.mArrayDimentionNum = num_chanel;

    gNodes[node].mLeft = array;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_load_channel_element(unsigned int node, sCompileInfo* info)
{
    int num_channel = gNodes[node].uValue.sLoadElement.mArrayDimentionNum;

    /// compile left node ///
    unsigned int lnode = gNodes[node].mLeft;

    if(!compile(lnode, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    LVALUE lvalue = *get_value_from_stack(-1);

    sVar* var = lvalue.var;

    if(!left_type->mChannel)
    {
        compile_err_msg(info, "comelang can't get an element from this type.(3)");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    sNodeType* element_type = create_node_type_with_class_name("int");

    sNodeType* node_type = clone_node_type(element_type);
    node_type->mPointerNum++;

    LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type);

    LLVMValueRef lvalue2 = LLVMBuildCast(gBuilder, LLVMBitCast, lvalue.address, llvm_type, "array_cast");

    LLVMValueRef lvalue3;
    if(num_channel == 1) {
        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");
        lvalue3 = LLVMConstInt(llvm_type, 1, TRUE);
    }
    else {
        LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");
        lvalue3 = LLVMConstInt(llvm_type, 0, TRUE);
    }

    LLVMValueRef load_element_addresss = LLVMBuildGEP(gBuilder, lvalue2, &lvalue3, 1, "gep");

    LLVMValueRef element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "element");

    LVALUE llvm_value;

    llvm_value.value = element_value;
    llvm_value.type = clone_node_type(element_type);
    llvm_value.address = load_element_addresss;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    dec_stack_ptr(1, info);
    push_value_to_stack_ptr(&llvm_value, info);

    info->type = clone_node_type(element_type);

    info->type->mHeap = FALSE;

    return TRUE;
}

unsigned int sNodeTree_create_write_channel(unsigned int address_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeWriteChannel;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = address_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_write_channel(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    if(!left_type->mChannel) {
        compile_err_msg(info, "This is not channel type2(%s)", CLASS_NAME(left_type->mClass));
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

    if(auto_cast_posibility(left_type, right_type)) {
        if(!cast_right_type_to_left_type(left_type, &right_type, &rvalue, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    /// create buffer ///
    int alignment = 0;
    size_t buffer_size = get_size_from_node_type(left_type, &alignment);

    char buffer_var_name[VAR_NAME_MAX];
    snprintf(buffer_var_name, VAR_NAME_MAX, "channel_buf%d", gThreadNum);

    sNodeType* buffer_var_type = create_node_type_with_class_name("char");
    buffer_var_type->mArrayDimentionNum = 1;
    buffer_var_type->mArrayNum[0] = buffer_size;
    
    BOOL readonly = FALSE;
    if(!add_variable_to_table(info->pinfo->lv_table, buffer_var_name, buffer_var_type, readonly, NULL, -1, FALSE, FALSE))
    {
        return FALSE;
    }

    BOOL extern_ = FALSE;
    BOOL global = FALSE;
    unsigned int node2 = sNodeTree_create_define_variable(buffer_var_name, extern_, global, info->pinfo);
    
    if(!compile(node2, info)) {
        return FALSE;
    }

    /// create right value variable ///
    char right_var_name[VAR_NAME_MAX];
    snprintf(right_var_name, VAR_NAME_MAX, "channel_bufB%d", gThreadNum);

    sNodeType* right_var_type = clone_node_type(left_type);
    right_var_type->mChannel = FALSE;
    
    if(!add_variable_to_table(info->pinfo->lv_table, right_var_name, right_var_type, readonly, NULL, -1, FALSE, FALSE))
    {
        return FALSE;
    }

    BOOL alloc = TRUE;
    BOOL global2 = info->mBlockLevel == 0;
    unsigned int node3 = sNodeTree_create_store_variable(right_var_name, right_node, alloc, global2, info->pinfo);
    
    if(!compile(node3, info)) {
        return FALSE;
    }

    /// memcpy ///
    char fun_name[VAR_NAME_MAX];
    
    xstrncpy(fun_name, "memcpy", VAR_NAME_MAX);
    
    int num_params = 3;
    unsigned int params[PARAMS_MAX];

    unsigned int index_node[ARRAY_DIMENTION_MAX];

    index_node[0] = sNodeTree_create_int_value(1, info->pinfo);
    
    params[0] = sNodeTree_create_load_variable(buffer_var_name, info->pinfo);

    params[1] = sNodeTree_create_load_variable(right_var_name, info->pinfo);
    params[1] = sNodeTree_create_reffernce(params[1], info->pinfo);

    sNodeType* right_var_type2 = create_node_type_with_class_name("char*");

    params[1] = sNodeTree_create_cast(right_var_type2, params[1], info->pinfo);
    params[2] = sNodeTree_create_long_value(buffer_size, info->pinfo);
    
    BOOL method2 = FALSE;
    BOOL inherit2 = FALSE;
    int version2 = 0;
    
    unsigned int node4 = sNodeTree_create_function_call(fun_name, params, num_params, method2, inherit2, version2, info->pinfo);
    
    if(!compile(node4, info)) {
        return FALSE;
    }

    /// write ///
    char fun_name2[VAR_NAME_MAX];
    
    xstrncpy(fun_name2, "write", VAR_NAME_MAX);
    
    int num_params2 = 3;
    unsigned int params2[PARAMS_MAX];

    unsigned int index_node2[ARRAY_DIMENTION_MAX];

    index_node2[0] = sNodeTree_create_int_value(1, info->pinfo);
    
    params2[0] = left_node;
    params2[0] = sNodeTree_create_load_array_element(params2[0], index_node2, 1, info->pinfo);

    params2[1] = sNodeTree_create_load_variable(buffer_var_name, info->pinfo);
    params2[2] = sNodeTree_create_long_value(buffer_size, info->pinfo);
    
    unsigned int node5 = sNodeTree_create_function_call(fun_name2, params2, num_params2, method2, inherit2, version2, info->pinfo);
    
    if(!compile(node5, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_create_read_channel(unsigned int left_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeReadChannel;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_read_channel(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    sNodeType* var_type = clone_node_type(left_type);

    /// create buffer //
    int alignment = 0;
    size_t buffer_size = get_size_from_node_type(var_type, &alignment);

    char buffer_var_name[VAR_NAME_MAX];
    snprintf(buffer_var_name, VAR_NAME_MAX, "channel_buf%d", gThreadNum);
    
    sNodeType* buffer_var_type = create_node_type_with_class_name("char");
    buffer_var_type->mArrayDimentionNum = 1;
    buffer_var_type->mArrayNum[0] = buffer_size;
    
    BOOL readonly = FALSE;
    if(!add_variable_to_table(info->pinfo->lv_table, buffer_var_name, buffer_var_type, readonly, NULL, -1, FALSE, FALSE))
    {
        return FALSE;
    }

    BOOL extern_ = FALSE;
    BOOL global = FALSE;
    unsigned int node2 = sNodeTree_create_define_variable(buffer_var_name, extern_, global, info->pinfo);
    
    if(!compile(node2, info)) {
        return FALSE;
    }

    /// read ///
    char fun_name[VAR_NAME_MAX];
    
    xstrncpy(fun_name, "read", VAR_NAME_MAX);

    int num_params = 3;
    unsigned int params[PARAMS_MAX];

    unsigned int index_node[ARRAY_DIMENTION_MAX];

    index_node[0] = sNodeTree_create_int_value(0, info->pinfo);
    
    params[0] = left_node;
    params[0] = sNodeTree_create_load_array_element(params[0], index_node, 1, info->pinfo);

    params[1] = sNodeTree_create_load_variable(buffer_var_name, info->pinfo);
    params[2] = sNodeTree_create_long_value(buffer_size, info->pinfo);
    
    BOOL method2 = FALSE;
    BOOL inherit2 = FALSE;
    int version2 = 0;
    
    unsigned int node3 = sNodeTree_create_function_call(fun_name, params, num_params, method2, inherit2, version2, info->pinfo);

    if(!compile(node3, info)) {
        return FALSE;
    }

    unsigned int node4 = sNodeTree_create_load_variable(buffer_var_name, info->pinfo);
    sNodeType* var_type2 = clone_node_type(var_type);
    var_type2->mChannel = FALSE;
    node4 = sNodeTree_create_cast(var_type2, node4, info->pinfo);

    if(!compile(node4, info)) {
        return FALSE;
    }

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

BOOL compile_load_element(unsigned int node, sCompileInfo* info)
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

    if(left_type->mArrayDimentionNum == 0 && left_type->mPointerNum == 0 && left_type->mDynamicArrayNum == 0 && !left_type->mChannel)
    {
        compile_err_msg(info, "comelang can't get an element from this type.(1)");
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
        int k;
        for(k=0; j<left_type->mArrayDimentionNum; j++, k++) {
            indices[j] = rvalue[k].value;
        }
        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, left_type->mArrayDimentionNum, "gep");

        for(j=0; j<left_type->mArrayDimentionNum; j++) {
            LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");
            indices[j] = LLVMConstInt(llvm_type, 0, FALSE);
        }
        load_element_addresss = LLVMBuildGEP(gBuilder, load_element_addresss, indices, left_type->mArrayDimentionNum, "gep2");

        sNodeType* element_type = clone_node_type(var_type);
        element_type->mArrayDimentionNum = 0;
        element_type->mDynamicArrayNum = 0;

        sNodeType* node_type = clone_node_type(element_type);
        node_type->mPointerNum -= num_dimention;
        node_type->mPointerNum+=2;

        if(node_type->mPointerNum == 0) {
            LLVMValueRef element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "element");

            LVALUE llvm_value;
            llvm_value.value = element_value;
            llvm_value.type = clone_node_type(node_type);
            llvm_value.address = load_element_addresss;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            dec_stack_ptr(1+num_dimention, info);
            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(node_type);
        }
        else {
            LLVMTypeRef llvm_var_type2 = create_llvm_type_from_node_type(node_type);
            load_element_addresss = LLVMBuildCast(gBuilder, LLVMBitCast, load_element_addresss, llvm_var_type2, "array_cast");
            LLVMValueRef element_value = load_element_addresss;

            LVALUE llvm_value;
            llvm_value.value = element_value;
            llvm_value.type = clone_node_type(node_type);
            llvm_value.address = load_element_addresss;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            dec_stack_ptr(1+num_dimention, info);
            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(node_type);
        }
    }
    else if(left_type->mChannel) {
        sNodeType* element_type = create_node_type_with_class_name("int");

        sNodeType* node_type = clone_node_type(element_type);
        node_type->mPointerNum++;

        LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type);

        LLVMValueRef lvalue2 = LLVMBuildCast(gBuilder, LLVMBitCast, lvalue.address, llvm_type, "array_cast");
        LLVMValueRef load_element_addresss = LLVMBuildGEP(gBuilder, lvalue2, &rvalue[0].value, 1, "gep");

        LLVMValueRef element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "element");

        LVALUE llvm_value;

        llvm_value.value = element_value;
        llvm_value.type = clone_node_type(element_type);
        llvm_value.address = load_element_addresss;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1+num_dimention, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(element_type);
    }
    else if(left_type->mArrayDimentionNum == 1 || left_type->mDynamicArrayNum != 0) {
        sNodeType* element_type = clone_node_type(var_type);

        element_type->mArrayDimentionNum = 0;
        element_type->mDynamicArrayNum = 0;

        sNodeType* node_type = clone_node_type(element_type);
        node_type->mPointerNum++;

        LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type);

        LLVMValueRef lvalue2 = LLVMBuildCast(gBuilder, LLVMBitCast, lvalue.address, llvm_type, "array_cast");
        LLVMValueRef load_element_addresss = LLVMBuildGEP(gBuilder, lvalue2, &rvalue[0].value, 1, "gep");

        LLVMValueRef element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "element");

        LVALUE llvm_value;

        llvm_value.value = element_value;
        llvm_value.type = clone_node_type(element_type);
        llvm_value.address = load_element_addresss;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1+num_dimention, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(element_type);
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

        sNodeType* element_type = clone_node_type(var_type);
        element_type->mArrayDimentionNum = 0;
        element_type->mDynamicArrayNum = 0;

        sNodeType* node_type = clone_node_type(element_type);
        node_type->mPointerNum -= num_dimention;
        node_type->mPointerNum+=2;

        if(node_type->mPointerNum == 0) {
            LLVMValueRef element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "element");

            LVALUE llvm_value;

            llvm_value.value = element_value;
            llvm_value.type = clone_node_type(element_type);
            llvm_value.address = load_element_addresss;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            dec_stack_ptr(1+num_dimention, info);
            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(element_type);
        }
        else {
            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type);

            load_element_addresss = LLVMBuildCast(gBuilder, LLVMBitCast, load_element_addresss, llvm_type, "array_cast");
            LLVMValueRef element_value = load_element_addresss;

            LVALUE llvm_value;

            llvm_value.value = element_value;
            llvm_value.type = clone_node_type(element_type);
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

        sNodeType* element_type = clone_node_type(var_type);
        element_type->mArrayDimentionNum = 0;
        element_type->mDynamicArrayNum = 0;

        sNodeType* node_type = clone_node_type(element_type);
        node_type->mPointerNum -= num_dimention;
        node_type->mPointerNum+=2;

        if(node_type->mPointerNum == 0) {
            LLVMValueRef element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "element");

            LVALUE llvm_value;

            llvm_value.value = element_value;
            llvm_value.type = clone_node_type(element_type);
            llvm_value.address = load_element_addresss;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            dec_stack_ptr(1+num_dimention, info);
            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(element_type);
        }
        else {
            LLVMValueRef element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "element");

            LVALUE llvm_value;

            llvm_value.value = element_value;
            llvm_value.type = clone_node_type(element_type);
            llvm_value.address = load_element_addresss;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            dec_stack_ptr(1+num_dimention, info);
            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(element_type);
        }
    }
    else if(left_type->mPointerNum > 0) {
        LLVMValueRef lvalue2 = lvalue.value;

        LLVMValueRef load_element_addresss = lvalue2;

        LLVMValueRef element_value;

        for(i=0; i<num_dimention; i++) {
            LLVMValueRef value = rvalue[i].value;
            load_element_addresss = LLVMBuildInBoundsGEP(gBuilder, load_element_addresss, &value, 1, "element_address");

            element_value = LLVMBuildLoad(gBuilder, load_element_addresss, "element");
            if(i < num_dimention-1) {
                load_element_addresss = element_value;
            }
        }

        sNodeType* element_type = clone_node_type(var_type);
        element_type->mPointerNum -= num_dimention;

        LVALUE llvm_value;
        llvm_value.value = element_value;
        llvm_value.type = clone_node_type(element_type);
        llvm_value.address = load_element_addresss;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        dec_stack_ptr(1+num_dimention, info);
        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(element_type);
    }
    else {
        compile_err_msg(info, "come lang supports under 3 dimention array. this is %d dimetion", left_type->mArrayDimentionNum);
        return FALSE;
    }

    info->type->mHeap = FALSE;

    return TRUE;
}

unsigned int sNodeTree_create_stack(sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStack;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sStack.mVarTable = clone_var_table(info->lv_table);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_stack(unsigned int node, sCompileInfo* info)
{
    sVarTable* lv_table = gNodes[node].uValue.sStack.mVarTable;

    char type_name[VAR_NAME_MAX];

    create_current_stack_frame_struct(type_name, lv_table);

    sNodeType* node_type = create_node_type_with_class_name(type_name);

    LLVMTypeRef llvm_type = create_llvm_type_from_node_type(node_type);

    LLVMValueRef stack = LLVMBuildAlloca(gBuilder, llvm_type, "current_stack");

    sVarTable* it = lv_table;
    int field_index = 0;

    while(it) {
        sVar* p = it->mLocalVariables;

        while(1) {
            if(p->mName[0] != 0 && p->mType) {
                sVar* var = get_variable_from_table(info->pinfo->lv_table, p->mName);
                
                LLVMValueRef field_address = LLVMBuildStructGEP(gBuilder, stack, field_index, "field");

                LLVMBuildStore(gBuilder, var->mLLVMValue, field_address);

                field_index++;
            }

            p++;

            if(p == it->mLocalVariables + LOCAL_VARIABLE_MAX) {
                break;
            }
        }

        if(it->mBlockLevel == 1) {
            break;
        }

        it = it->mParent;
    }

    node_type->mPointerNum++;

    LVALUE llvm_value;
    llvm_value.value = stack;
    llvm_value.type = clone_node_type(node_type);
    llvm_value.address = NULL;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;
    llvm_value.type = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = clone_node_type(node_type);

    return TRUE;
}
