#include "common.h"

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

BOOL compile_int_value(unsigned int node, sCompileInfo* info)
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

BOOL compile_uint_value(unsigned int node, sCompileInfo* info)
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
    info->type->mUnsigned = TRUE;

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

BOOL compile_long_value(unsigned long long int node, sCompileInfo* info)
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

BOOL compile_ulong_value(unsigned long long int node, sCompileInfo* info)
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
    info->type->mUnsigned = TRUE;

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

BOOL compile_true(unsigned int node, sCompileInfo* info)
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

BOOL compile_null(unsigned int node, sCompileInfo* info)
{
    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");

    LVALUE llvm_value;
    llvm_value.value = LLVMConstInt(llvm_type, 0, FALSE);
    LLVMTypeRef llvm_type2 = create_llvm_type_with_class_name("void*");
    llvm_value.value = LLVMBuildCast(gBuilder, LLVMBitCast, llvm_value.value, llvm_type2, "castAH");
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

BOOL compile_false(unsigned int node, sCompileInfo* info)
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

