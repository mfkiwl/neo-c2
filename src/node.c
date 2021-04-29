#include "common.h"
#include <llvm-c/Core.h>

sNodeTree* gNodes;

int gSizeNodes = 0;
int gUsedNodes = 0;

void init_nodes()
{
    const int node_size = 32;

    if(gUsedNodes == 0) {
        gNodes = (sNodeTree*)xcalloc(1, sizeof(sNodeTree)*node_size);
        gSizeNodes = node_size;
        gUsedNodes = 1;   // 0 of index means null
    }
}

void free_nodes()
{
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

                case kNodeTypeSimpleLambdaParam:
                    if(gNodes[i].uValue.sSimpleLambdaParam.mBuf) 
                    {
                        free(gNodes[i].uValue.sSimpleLambdaParam.mBuf);
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

LVALUE* gLLVMStack;
LVALUE* gLLVMStackHead;

void push_value_to_stack_ptr(LVALUE* value, sCompileInfo* info)
{
}

void dec_stack_ptr(int value, sCompileInfo* info)
{
}

void arrange_stack(sCompileInfo* info, int top)
{
}

LVALUE* get_value_from_stack(int offset)
{
}

BOOL get_const_value_from_node(int* array_size, unsigned int array_size_node, sParserInfo* info)
{
/*
    sCompileInfo cinfo;

    memset(&cinfo, 0, sizeof(sCompileInfo));

    new_right_value_objects_container(&cinfo);

    cinfo.pinfo = info;

    if(!compile(array_size_node, &cinfo)) {
        return FALSE;
    }

    sNodeType* node_type = cinfo.type;

    LVALUE llvm_value = *get_value_from_stack(-1);

    dec_stack_ptr(1, &cinfo);

    Value* value = llvm_value.value;

    ConstantInt* constant_value;

    if(constant_value = dyn_cast<ConstantInt>(value)) {
        *array_size = constant_value->getSExtValue();
    }
    else {
        return FALSE;
    }
*/

    return TRUE;
}

BOOL create_llvm_struct_type(sNodeType* node_type, sNodeType* generics_type, BOOL new_create, sCompileInfo* info)
{
/*
    int i;
    for(i=0; i<generics_type->mNumGenericsTypes; i++)
    {
        sNodeType* node_type2 = generics_type->mGenericsTypes[i];

        sCLClass* klass = node_type2->mClass;
        if(klass->mFlags & CLASS_FLAGS_STRUCT)
        {
            if(!create_llvm_struct_type(node_type2, node_type2, new_create, info))
            {
                return FALSE;
            }
        }
    }

    sCLClass* klass = node_type->mClass;

    char* class_name = CLASS_NAME(klass);

    char real_struct_name[REAL_STRUCT_NAME_MAX];
    int size_real_struct_name = REAL_STRUCT_NAME_MAX;
    xstrncpy(real_struct_name, class_name, size_real_struct_name);

    create_real_struct_name(real_struct_name, size_real_struct_name, node_type->mNumGenericsTypes, node_type->mGenericsTypes);

    if(klass->mUndefinedStructType)
    {
        if(!solve_undefined_strcut_type(node_type, generics_type, real_struct_name, info))
        {
            return FALSE;
        }
    }
    else if(gLLVMStructType[real_struct_name].first == nullptr || (info->pinfo && info->pinfo->parse_struct_phase && (node_type->mClass->mNumFields != gLLVMStructType[real_struct_name].second->mNumFields)))
    {
        if(TheModule->getTypeByName(real_struct_name) == nullptr || (info->pinfo && info->pinfo->parse_struct_phase && (node_type->mClass->mNumFields != gLLVMStructType[real_struct_name].second->mNumFields)))
        {
            StructType* struct_type = StructType::create(TheContext, real_struct_name);
            std::vector<Type*> fields;

            std::pair<Type*, sNodeType*> pair_value;
            pair_value.first = struct_type;
            pair_value.second = clone_node_type(node_type);
            pair_value.second->mNumFields = node_type->mClass->mNumFields;

            gLLVMStructType[real_struct_name] = pair_value;

            int i;
            for(i=0; i<klass->mNumFields; i++) {
                sNodeType* field = clone_node_type(klass->mFields[i]);


                sNodeType* generics_type2 = generics_type;

                if(!is_generics_type(field) && field->mNumGenericsTypes > 0)
                {
                    generics_type2 = clone_node_type(field);
                }
                else {
                    BOOL success_solve;
                    (void)solve_generics(&field, field, &success_solve);

                    if(!solve_generics(&field, generics_type, &success_solve))
                    {
                        return FALSE;
                    }
                }

                if(field->mClass == klass && field->mPointerNum == 0)
                {
                    return FALSE;
                }
                Type* field_type;

                if(!create_llvm_type_from_node_type(&field_type, field, generics_type2, info))
                {
                    compile_err_msg(info, "Getting llvm type failed(100)");
                    show_node_type(field);
                    show_node_type(generics_type2);
                    return FALSE;
                }

                fields.push_back(field_type);
            }

            if(struct_type->isOpaque()) 
            {
                struct_type->setBody(fields, false);
            }
        }
    }
*/

    return TRUE;
}

BOOL create_llvm_union_type(sNodeType* node_type, sNodeType* generics_type, sCompileInfo* info)
{
/*
    sCLClass* klass = node_type->mClass;

    char* class_name = CLASS_NAME(klass);

    char real_struct_name[REAL_STRUCT_NAME_MAX];
    int size_real_struct_name = REAL_STRUCT_NAME_MAX;
    xstrncpy(real_struct_name, class_name, size_real_struct_name);

    create_real_struct_name(real_struct_name, size_real_struct_name, node_type->mNumGenericsTypes, node_type->mGenericsTypes);

    if(gLLVMStructType[real_struct_name].first == nullptr) 
    {
        StructType* struct_type = StructType::create(TheContext, real_struct_name);
        std::vector<Type*> fields;

        uint64_t max_size = 0;
        Type* max_size_field = NULL;

        int i;
        for(i=0; i<klass->mNumFields; i++) {
            sNodeType* field = clone_node_type(klass->mFields[i]);

            sNodeType* generics_type2 = generics_type;

            BOOL success_solve;
            (void)solve_generics(&field, field, &success_solve);

            if(success_solve)
            {
                generics_type2 = field;
            }

            if(!success_solve) {
                (void)solve_generics(&field, generics_type, &success_solve);

                if(success_solve)
                {
                    generics_type2 = generics_type;
                }
            }


            Type* field_type;
            if(!create_llvm_type_from_node_type(&field_type, field, generics_type2, info))
            {
                return FALSE;
            }

            uint64_t alloc_size = 0;
            if(!get_size_from_node_type(&alloc_size, field, generics_type2, info))
            {
                return FALSE;
            }

            if(alloc_size > max_size) {
                max_size = alloc_size;

                max_size_field = field_type;
            }
        }

        if(max_size_field) {
            fields.push_back(max_size_field);
        }

        if(struct_type->isOpaque()) {
            struct_type->setBody(fields, false);
        }

        std::pair<Type*, sNodeType*> pair_value;
        pair_value.first = struct_type;
        pair_value.second = clone_node_type(node_type);
        pair_value.second->mNumFields = node_type->mClass->mNumFields;

        gLLVMStructType[real_struct_name] = pair_value;
    }
    else if(klass->mUndefinedStructType) {
        StructType* struct_type = (StructType*)klass->mUndefinedStructType;
        std::vector<Type*> fields;

        uint64_t max_size = 0;
        Type* max_size_field = NULL;

        int i;
        for(i=0; i<klass->mNumFields; i++) {
            sNodeType* field = clone_node_type(klass->mFields[i]);

            sNodeType* generics_type2 = generics_type;

            BOOL success_solve;
            (void)solve_generics(&field, field, &success_solve);

            if(success_solve)
            {
                generics_type2 = field;
            }

            if(!success_solve) {
                (void)solve_generics(&field, generics_type, &success_solve);

                if(success_solve)
                {
                    generics_type2 = generics_type;
                }
            }

            Type* field_type;
            if(!create_llvm_type_from_node_type(&field_type, field, generics_type2, info))
            {
                return FALSE;
            }

            uint64_t alloc_size = 0;
            if(!get_size_from_node_type(&alloc_size, field, generics_type2, info))
            {
                return FALSE;
            }

            if(alloc_size > max_size) {
                max_size = alloc_size;

                max_size_field = field_type;
            }
        }

        if(max_size_field) {
            fields.push_back(max_size_field);
        }

        if(struct_type->isOpaque()) {
            struct_type->setBody(fields, false);
        }

        klass->mUndefinedStructType = NULL;
    }
*/

    return TRUE;
}

void create_undefined_llvm_struct_type(sNodeType* node_type)
{
/*
    sCLClass* klass = node_type->mClass;

    char* class_name = CLASS_NAME(klass);

    char real_struct_name[REAL_STRUCT_NAME_MAX];
    int size_real_struct_name = REAL_STRUCT_NAME_MAX;
    xstrncpy(real_struct_name, class_name, size_real_struct_name);

    create_real_struct_name(real_struct_name, size_real_struct_name, node_type->mNumGenericsTypes, node_type->mGenericsTypes);

    if(gLLVMStructType[real_struct_name].first == nullptr) 
    {
        StructType* struct_type = StructType::create(TheContext, real_struct_name);

        std::pair<Type*, sNodeType*> pair_value;
        pair_value.first = struct_type;
        pair_value.second = clone_node_type(node_type);
        pair_value.second->mNumFields = node_type->mClass->mNumFields;

        gLLVMStructType[real_struct_name] = pair_value;

        klass->mUndefinedStructType = struct_type;
    }
*/
}

void create_anonymous_union_var_name(char* name, int size_name)
{
    char* prefix_name = "anon.union.var";
    static int num = 0;
    snprintf(name, size_name, "%s%d", prefix_name, num);
}

void compile_err_msg(sCompileInfo* info, const char* msg, ...)
{
    char msg2[1024];

    va_list args;
    va_start(args, msg);
    vsnprintf(msg2, 1024, msg, args);
    va_end(args);

    static int output_num = 0;

    if(output_num < COMPILE_ERR_MSG_MAX) {
        fprintf(stderr, "%s:%d: %s\n", info->sname, info->sline, msg2);
    }
    output_num++;
}

BOOL compile_block(sNodeBlock* block, sCompileInfo* info, sNodeType* result_type, BOOL free_var_object)
{

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

static BOOL compile_int_value(unsigned int node, sCompileInfo* info)
{

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

static BOOL compile_define_variable(unsigned int node, sCompileInfo* info)
{

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
    gNodes[node].uValue.sStoreVariable.mParseStructPhase = info->parse_struct_phase;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = right;
    gNodes[node].mMiddle = 0;

    return node;
}


static BOOL compile_store_variable(unsigned int node, sCompileInfo* info)
{

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
    gNodes[node].uValue.sFunction.mParseStructPhase = info->parse_struct_phase;
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
    gNodes[node].uValue.sFunction.mParseStructPhase = info->parse_struct_phase;

    return node;
}

BOOL compile_function(unsigned int node, sCompileInfo* info)
{

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

    return TRUE;
}

unsigned int sNodeTree_struct(sNodeType* struct_type, sParserInfo* info, char* sname, int sline, BOOL anonymous)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeStruct;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sStruct.mType = struct_type;
    gNodes[node].uValue.sStruct.mAnonymous = anonymous;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_struct(unsigned int node, sCompileInfo* info)
{

    return TRUE;
}

unsigned int sNodeTree_union(sNodeType* struct_type, sParserInfo* info, char* sname, int sline, BOOL anonymous)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeUnion;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sStruct.mType = struct_type;
    gNodes[node].uValue.sStruct.mAnonymous = anonymous;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_union(unsigned int node, sCompileInfo* info)
{
    return TRUE;
}

unsigned int sNodeTree_create_object(sNodeType* node_type, unsigned int object_num, char* sname, int sline, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeObject;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sObject.mType = clone_node_type(node_type);

    gNodes[node].mLeft = object_num;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}


static BOOL compile_object(unsigned int node, sCompileInfo* info)
{

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

    return TRUE;
}

unsigned int sNodeTree_create_simple_lambda_param(char* buf, char* sname, int sline, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].uValue.sSimpleLambdaParam.mBuf = MANAGED buf;
    xstrncpy(gNodes[node].uValue.sSimpleLambdaParam.mSName, sname, PATH_MAX);
    gNodes[node].uValue.sSimpleLambdaParam.mSLine = sline;
    
    gNodes[node].mNodeType = kNodeTypeSimpleLambdaParam;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_simple_lambda_param(unsigned int node, sCompileInfo* info)
{
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

    if(info->parse_struct_phase) {
        add_typedef(name, clone_node_type(node_type));
    }

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
    return TRUE;
}


unsigned int sNodeTree_create_define_variables(unsigned int* nodes, int num_nodes, BOOL extern_, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDefineVariables;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    memcpy(gNodes[node].uValue.sDefineVariables.mNodes, nodes, sizeof(unsigned int)*IMPL_DEF_MAX);
    gNodes[node].uValue.sDefineVariables.mNumNodes = num_nodes;
    gNodes[node].uValue.sDefineVariables.mGlobal = info->mBlockLevel == 0;
    gNodes[node].uValue.sDefineVariables.mExtern = extern_;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_define_variables(unsigned int node, sCompileInfo* info)
{
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

    return TRUE;
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

    return TRUE;
}

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

BOOL compile_is_heap_expression(unsigned int node, sCompileInfo* info)
{

    return TRUE;
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

    return TRUE;
}

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

static BOOL compile_class_name_expression(unsigned int node, sCompileInfo* info)
{

    return TRUE;
}

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

unsigned int sNodeTree_create_va_arg(unsigned int lnode, sNodeType* node_type, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeVaArg;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sVaArg.mNodeType = clone_node_type(node_type);

    gNodes[node].mLeft = lnode;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

static BOOL compile_va_arg(unsigned int node, sCompileInfo* info)
{
    return TRUE;
}

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

        case kNodeTypeSimpleLambdaParam:
            if(!compile_simple_lambda_param(node, info))
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

        case kNodeTypeDefineVariables:
            if(!compile_define_variables(node, info)) {
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

        case kNodeTypeIsHeapExpression:
            if(!compile_is_heap_expression(node, info))
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

        case kNodeTypeVaArg:
            if(!compile_va_arg(node, info))
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

        case kNodeTypeClassNameExpression:
            if(!compile_class_name_expression(node, info)) {
                return FALSE;
            }
            break;

        case kNodeTypeClassName:
            if(!compile_class_name(node, info)) {
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
