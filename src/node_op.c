#include "common.h"


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

BOOL compile_add(unsigned int node, sCompileInfo* info)
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
        LLVMValueRef left_value2 = LLVMBuildCast(gBuilder, LLVMPtrToInt, left_value, long_type, "ptr_to_intA");

        LLVMValueRef right_value;
        if(type_identify_with_class_name(right_type, "long")) {
            right_value = rvalue.value;
        }
        else {
            if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "ptrToIntB");
            }
            else {
                right_value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue.value, long_type, "sext1");
            }
        }

        LLVMTypeRef llvm_var_type = create_llvm_type_from_node_type(left_type);

        sNodeType* left_type3 = clone_node_type(left_type);
        left_type3->mPointerNum--;

        int alignment = 0;
        uint64_t alloc_size = get_size_from_node_type(left_type3, &alignment);

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

        LLVMValueRef left_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, lvalue.value, long_type, "ptrToIntC");

        LLVMValueRef right_value;
        if(type_identify_with_class_name(right_type, "long")) {
            right_value = rvalue.value;
        }
        else {
            if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "ptrToIntD");
            }
            else {
                right_value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue.value, long_type, "sext");
            }
        }

        LLVMTypeRef llvm_var_type = create_llvm_type_from_node_type(left_type);

        sNodeType* left_type3 = clone_node_type(left_type);
        left_type3->mPointerNum--;

        int alignment = 0;
        uint64_t alloc_size = get_size_from_node_type(left_type3, &alignment);

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

BOOL compile_sub(unsigned int node, sCompileInfo* info)
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
        LLVMValueRef left_value2 = LLVMBuildCast(gBuilder, LLVMPtrToInt, left_value, long_type, "ptrToIntE");

        LLVMValueRef right_value;
        if(type_identify_with_class_name(right_type, "long")) {
            right_value = rvalue.value;
        }
        else {
            if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "ptrToIntF");
            }
            else {
                right_value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue.value, long_type, "sext");
            }
        }

        LLVMTypeRef llvm_var_type = create_llvm_type_from_node_type(left_type);

        sNodeType* left_type3 = clone_node_type(left_type);
        left_type3->mPointerNum--;

        int alignment = 0;
        uint64_t alloc_size = get_size_from_node_type(left_type3, &alignment);

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

        LLVMValueRef left_value;
        if(left_type->mArrayDimentionNum > 0) {
            sNodeType* left_type2 = clone_node_type(left_type);

            left_type2->mPointerNum++;
            left_type2->mArrayDimentionNum = 0;

            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type2);

            left_value = LLVMBuildCast(gBuilder, LLVMBitCast, lvalue.address, llvm_type, "ptrToIntG");
        }
        else {
            left_value = lvalue.value;
        }

        LLVMValueRef right_value;
        if(right_type->mArrayDimentionNum > 0) {
            sNodeType* right_type2 = clone_node_type(right_type);

            right_type2->mPointerNum++;
            right_type2->mArrayDimentionNum = 0;

            LLVMTypeRef llvm_type = create_llvm_type_from_node_type(right_type2);

            right_value = LLVMBuildCast(gBuilder, LLVMBitCast, rvalue.address, llvm_type, "ptrToIntG");
        }
        else {
            right_value = rvalue.value;
        }

        left_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, left_value, long_type, "ptrToIntG");
        right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, right_value, long_type, "ptrToIntH");

        sNodeType* node_type = create_node_type_with_class_name("long");

        LLVMTypeRef llvm_var_type = create_llvm_type_from_node_type(node_type);

        sNodeType* element_type = clone_node_type(left_type);
        element_type->mPointerNum = 0;
        element_type->mArrayDimentionNum = 0;

        int alignment = 0;
        uint64_t element_size = get_size_from_node_type(element_type, &alignment);

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

        LLVMValueRef left_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, lvalue.value, long_type, "ptrToIntI");

        LLVMValueRef right_value;
        if(type_identify_with_class_name(right_type, "long")) {
            right_value = rvalue.value;
        }
        else {
            if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "ptrToIntJ");
            }
            else {
                right_value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue.value, long_type, "sext");
            }
        }

        LLVMTypeRef llvm_var_type = create_llvm_type_from_node_type(left_type);

        sNodeType* left_type3 = clone_node_type(left_type);
        left_type3->mPointerNum--;

        int alignment = 0;
        uint64_t alloc_size = get_size_from_node_type(left_type3, &alignment);

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

BOOL compile_mult(unsigned int node, sCompileInfo* info)
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

BOOL compile_div(unsigned int node, sCompileInfo* info)
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

BOOL compile_mod(unsigned int node, sCompileInfo* info)
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

BOOL compile_equals(unsigned int node, sCompileInfo* info)
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

BOOL compile_not_equals(unsigned int node, sCompileInfo* info)
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

BOOL compile_gteq(unsigned int node, sCompileInfo* info)
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

BOOL compile_leeq(unsigned int node, sCompileInfo* info)
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

BOOL compile_gt(unsigned int node, sCompileInfo* info)
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

BOOL compile_le(unsigned int node, sCompileInfo* info)
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
        llvm_value.value = LLVMBuildICmp(gBuilder, LLVMIntULT, lvalue.value, rvalue.value, "le");
    }
    else {
        llvm_value.value = LLVMBuildICmp(gBuilder, LLVMIntSLT, lvalue.value, rvalue.value, "le");
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

BOOL compile_logical_denial(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;
    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = clone_node_type(info->type);

    LVALUE lvalue = *get_value_from_stack(-1);

    dec_stack_ptr(1, info);

    LLVMTypeRef llvm_type = create_llvm_type_from_node_type(left_type);

    LVALUE rvalue;

    if(left_type->mPointerNum > 0) {
        rvalue.value = LLVMConstNull(llvm_type);
    }
    else {
        rvalue.value = LLVMConstInt(llvm_type, 0, FALSE);
    }

    rvalue.type = clone_node_type(left_type);
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

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

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

BOOL compile_left_shift(unsigned int node, sCompileInfo* info)
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

BOOL compile_right_shift(unsigned int node, sCompileInfo* info)
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

BOOL compile_and(unsigned int node, sCompileInfo* info)
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

BOOL compile_xor(unsigned int node, sCompileInfo* info)
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

BOOL compile_or(unsigned int node, sCompileInfo* info)
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

BOOL compile_complement(unsigned int node, sCompileInfo* info)
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

BOOL compile_plus_plus(unsigned int node, sCompileInfo* info)
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
            LLVMValueRef left_value2 = LLVMBuildCast(gBuilder, LLVMPtrToInt, left_value, long_type, "castAI");

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

            int alignment = 0;
            uint64_t alloc_size = get_size_from_node_type(left_type, &alignment);

            LLVMValueRef alloc_size_value = LLVMConstInt(long_type, alloc_size, FALSE);

            right_value = LLVMBuildMul(gBuilder, right_value, alloc_size_value, "mul");

            LLVMValueRef value = LLVMBuildAdd(gBuilder, left_value2, right_value, "add");
            value = LLVMBuildCast(gBuilder, LLVMIntToPtr, value, LLVMPointerType(llvm_left_type, 0), "IntToPtr");
            LLVMBuildStore(gBuilder, value, lvalue.address);

            sNodeType* left_type2 = clone_node_type(left_type);
            left_type2->mPointerNum++;

            LVALUE llvm_value;
            llvm_value.value = value;
            llvm_value.type = clone_node_type(left_type2);
            llvm_value.address = NULL;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

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

            LLVMValueRef address = lvalue.value;

            LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
            LLVMValueRef add_rvalue = rvalue.value;

            LLVMValueRef value = LLVMBuildAdd(gBuilder, add_lvalue, add_rvalue, "add");

            LLVMBuildStore(gBuilder, value, address);

            LVALUE llvm_value;
            llvm_value.value = value;
            llvm_value.type = clone_node_type(left_type);
            llvm_value.address = NULL;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(left_type);
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

        LVALUE llvm_value;
        llvm_value.value = value;
        llvm_value.type = clone_node_type(left_type);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(left_type);
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

BOOL compile_minus_minus(unsigned int node, sCompileInfo* info)
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

    sNodeType* result_type = clone_node_type(left_type);

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

            int alignment = 0;
            uint64_t alloc_size = get_size_from_node_type(left_type, &alignment);

            LLVMValueRef alloc_size_value = LLVMConstInt(long_type, alloc_size, FALSE);

            right_value = LLVMBuildMul(gBuilder, right_value, alloc_size_value, "mul");

            LLVMValueRef value = LLVMBuildSub(gBuilder, left_value2, right_value, "subtmp");
            value = LLVMBuildCast(gBuilder, LLVMIntToPtr, value, LLVMPointerType(llvm_left_type,0), "IntToPtr");
            LLVMBuildStore(gBuilder, value, lvalue.address);

            sNodeType* left_type2 = clone_node_type(left_type);
            left_type2->mPointerNum++;

            LVALUE llvm_value;
            llvm_value.value = value;
            llvm_value.type = clone_node_type(left_type2);
            llvm_value.address = NULL;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

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

            LLVMValueRef address = lvalue.value;

            LLVMValueRef add_lvalue = LLVMBuildLoad(gBuilder, address, "load");
            LLVMValueRef add_rvalue = rvalue.value;

            LLVMValueRef value = LLVMBuildSub(gBuilder, add_lvalue, add_rvalue, "sub");

            LLVMBuildStore(gBuilder, value, address);

            LVALUE llvm_value;
            llvm_value.value = value;
            llvm_value.type = clone_node_type(left_type);
            llvm_value.address = NULL;
            llvm_value.var = NULL;
            llvm_value.binded_value = FALSE;
            llvm_value.load_field = FALSE;

            push_value_to_stack_ptr(&llvm_value, info);

            info->type = clone_node_type(left_type);
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

        LVALUE llvm_value;
        llvm_value.value = value;
        llvm_value.type = clone_node_type(left_type);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        push_value_to_stack_ptr(&llvm_value, info);

        info->type = clone_node_type(left_type);
    }

    info->type = result_type;

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

BOOL compile_equal_plus(unsigned int node, sCompileInfo* info)
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

    sNodeType* result_type = clone_node_type(right_type);

    if(left_type->mPointerNum > 0) {
        left_type->mPointerNum--;

        if(derefference && left_type->mPointerNum == 0) {
            LLVMValueRef address = lvalue.value;

            LLVMTypeRef llvm_left_type = create_llvm_type_from_node_type(left_type);

            LLVMTypeRef long_type = create_llvm_type_with_class_name("long");

            LLVMValueRef left_value = address;
            LLVMValueRef left_value2 = LLVMBuildCast(gBuilder, LLVMPtrToInt, left_value, long_type, "ptrToIntZZ");

            LLVMValueRef right_value;
            if(type_identify_with_class_name(right_type, "long")) {
                right_value = rvalue.value;
            }
            else {
                if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                    right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "ptToIntJJ");
                }
                else {
                    right_value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue.value, long_type, "sext");
                }
            }

            int alignment = 0;
            uint64_t alloc_size = get_size_from_node_type(left_type, &alignment);

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

    info->type = create_node_type_with_class_name("void");

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

BOOL compile_equal_minus(unsigned int node, sCompileInfo* info)
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
            LLVMValueRef left_value2 = LLVMBuildCast(gBuilder, LLVMPtrToInt, left_value, long_type, "castAJ");

            LLVMValueRef right_value;
            if(type_identify_with_class_name(right_type, "long")) {
                right_value = rvalue.value;
            }
            else {
                if(right_type->mPointerNum > 0 || right_type->mArrayDimentionNum > 0) {
                    right_value = LLVMBuildCast(gBuilder, LLVMPtrToInt, rvalue.value, long_type, "ptrToIntL");
                }
                else {
                    right_value = LLVMBuildCast(gBuilder, LLVMSExt, rvalue.value, long_type, "sext");
                }
            }

            int alignment = 0;
            uint64_t alloc_size = get_size_from_node_type(left_type, &alignment);

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

    info->type = create_node_type_with_class_name("void");

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

BOOL compile_equal_mult(unsigned int node, sCompileInfo* info)
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

    info->type = create_node_type_with_class_name("void");

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

BOOL compile_equal_div(unsigned int node, sCompileInfo* info)
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

    info->type = create_node_type_with_class_name("void");

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

BOOL compile_equal_mod(unsigned int node, sCompileInfo* info)
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

    info->type = create_node_type_with_class_name("void");

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

BOOL compile_equal_lshift(unsigned int node, sCompileInfo* info)
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

    info->type = create_node_type_with_class_name("void");

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

BOOL compile_equal_rshift(unsigned int node, sCompileInfo* info)
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

    info->type = create_node_type_with_class_name("void");

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

BOOL compile_equal_and(unsigned int node, sCompileInfo* info)
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

    info->type = create_node_type_with_class_name("void");

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

BOOL compile_equal_xor(unsigned int node, sCompileInfo* info)
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

    info->type = create_node_type_with_class_name("void");

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

BOOL compile_equal_or(unsigned int node, sCompileInfo* info)
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
    
    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

