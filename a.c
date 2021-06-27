#include <llvm-c/Core.h>
#include <stdio.h>
#include <llvm-c/DebugInfo.h>
#include <limits.h>

#define BOOL int

struct sBufStruct {
    char* mBuf;
    int mSize;
    int mLen;
};

typedef struct sBufStruct sBuf;

#define GENERICS_TYPES_MAX 10
#define VAR_NAME_MAX 128
#define CLASS_NUM_MAX 512*2*2*2*2*2
#define PARSER_ERR_MSG_MAX 5
#define COMPILE_ERR_MSG_MAX 5
#define NEO_C_STACK_SIZE 512
#define LOCAL_VARIABLE_MAX 4096
#define PARAMS_MAX 32
#define METHOD_DEFAULT_PARAM_MAX 128
#define SOURCE_EXPRESSION_MAX 4096*2
#define ELIF_NUM_MAX 128
#define STRUCT_FIELD_MAX 256
#define REAL_FUN_NAME_MAX (VAR_NAME_MAX*PARAMS_MAX+32)
#define REAL_STRUCT_NAME_MAX (VAR_NAME_MAX*PARAMS_MAX+32)
#define NODES_MAX 512
#define EXTERNAL_OBJECT_MAX 4096
#define INIT_ARRAY_MAX 128
#define LOOP_NEST_MAX 1024
#define TYPEDEF_MAX 4096
#define MACRO_MAX 1024
#define ARRAY_DIMENTION_MAX 5
#define FUN_NUM_MAX 8096*2
#define STRUCT_NUM_MAX 8096*2
#define LABEL_MAX 512
#define GENERICS_STRUCT_MAX 512
#define FUN_VERSION_MAX 512

#define clint64 long long      // for 32 bit cpu

struct sParserInfoStruct;
struct sNodeBlockStruct;
struct sCompileInfoStruct;
struct sVarTableStruct;


struct sConstStruct
{
    char* mConst;
    unsigned int mSize;
    unsigned int mLen;
};

typedef struct sConstStruct sConst;

#define CLASS_FLAGS_PRIMITIVE 0x01
#define CLASS_FLAGS_STRUCT 0x02
#define CLASS_FLAGS_NUMBER 0x04
#define CLASS_FLAGS_UNSIGNED_NUMBER 0x08
#define CLASS_FLAGS_GENERICS 0x10
#define CLASS_FLAGS_METHOD_GENERICS 0x20
#define CLASS_FLAGS_UNION 0x040
#define CLASS_FLAGS_ANONYMOUS 0x080
#define CLASS_FLAGS_ENUM 0x100
#define CLASS_FLAGS_ANONYMOUS_VAR_NAME 0x200

struct sCLClassStruct {
    clint64 mFlags;

    sConst mConst;

    int mClassNameOffset;

    int mGenericsNum;
    int mMethodGenericsNum;
    
    unsigned int mFieldNameOffsets[STRUCT_FIELD_MAX];
    struct sNodeTypeStruct* mFields[STRUCT_FIELD_MAX];
    int mNumFields;

    void* mUndefinedStructType;

    int mVersion;
};

typedef struct sCLClassStruct sCLClass;

struct sClassTableStruct
{
    char* mName;
    sCLClass* mItem;
    BOOL mFreed;
    BOOL mInitialized;

    struct sClassTableStruct* mNextClass;
};

typedef struct sClassTableStruct sClassTable;


struct sNodeTypeStruct {
    sCLClass* mClass;

    struct sNodeTypeStruct* mGenericsTypes[GENERICS_TYPES_MAX];
    int mNumGenericsTypes;

    int mArrayNum[ARRAY_DIMENTION_MAX];
    int mArrayDimentionNum;
    BOOL mNullable;
    BOOL mUnsigned;
    int mPointerNum;
    BOOL mConstant;
    BOOL mRegister;
    BOOL mVolatile;
    BOOL mStatic;
    BOOL mOverride;
    BOOL mUniq;
    int mSizeNum;

    struct sNodeTypeStruct* mParamTypes[PARAMS_MAX];
    struct sNodeTypeStruct* mResultType;
    BOOL mVarArgs;
    int mNumParams;

    BOOL mHeap;
    BOOL mDummyHeap;
    BOOL mNoHeap;

    unsigned int mDynamicArrayNum;

    int mArrayInitializeNum;

    unsigned int mTypeOfExpression;

    int mFinalizeGenericsFunNum;

    int mNumFields;

    char mTypeName[VAR_NAME_MAX];
    int mTypePointerNum;
};

typedef struct sNodeTypeStruct sNodeType;

struct sVarStruct {
    char mName[VAR_NAME_MAX];
    int mIndex;
    sNodeType* mType;

    int mBlockLevel;

    BOOL mReadOnly;
    BOOL mConstant;
    LLVMValueRef mLLVMValue;

    BOOL mGlobal;
};

typedef struct sVarStruct sVar;

struct sVarTableStruct {
    int mID;
    sVar mLocalVariables[LOCAL_VARIABLE_MAX];  // open address hash
    int mVarNum;
    int mMaxBlockVarNum;

    int mBlockLevel;

    struct sVarTableStruct* mParent;            // make linked list
    struct sVarTableStruct* mNext;              // for free var table
};

typedef struct sVarTableStruct sVarTable;

struct sNodeBlockStruct
{
    unsigned int* mNodes;
    unsigned int mSizeNodes;
    unsigned int mNumNodes;

    sVarTable* mLVTable;

    sBuf mSource;
    char mSName[PATH_MAX];
    int mSLine;
    
    BOOL mHasResult;
    int mExternCLang;

    BOOL mInCLang;
};

typedef struct sNodeBlockStruct sNodeBlock;

struct sParserInfoStruct
{
    sBuf mConst;

    char* p;
    char sname[PATH_MAX];
    char* source;
    char* module_name;
    int sline;
    int err_num;
    int parse_phase;
    int sline_top;
    sVarTable* lv_table;
    int mNumGenerics;
    char* mGenericsTypeNames[GENERICS_TYPES_MAX];

    int mNumMethodGenerics;
    char* mMethodGenericsTypeNames[GENERICS_TYPES_MAX];

    sNodeType* mMethodGenericsTypes[GENERICS_TYPES_MAX];
    int mNumMethodGenericsTypes;

    sNodeType* mGenericsType;

    int mBlockLevel;

    int switch_nest;
    BOOL first_case;
    BOOL case_after_return;

    BOOL change_sline;

    BOOL in_clang;

    char fun_name[VAR_NAME_MAX];

    char parse_struct_name[VAR_NAME_MAX];
    char impl_struct_name[VAR_NAME_MAX];

    int mFunVersion;
    int mImplVersion;

    BOOL parse_block;

    BOOL in_case;
    BOOL in_struct;
    BOOL in_conditional_operator;

    BOOL no_comma_operator;

    BOOL no_output_err_msg;
};

typedef struct sParserInfoStruct sParserInfo;

struct sParserParamStruct 
{
    char mName[VAR_NAME_MAX];
    sNodeType* mType;

    char mDefaultValue[METHOD_DEFAULT_PARAM_MAX];
};

typedef struct sParserParamStruct sParserParam;

struct sRightValueObject {
    LLVMValueRef obj;
    sNodeType* node_type;
    struct sRightValueObject* next;
    char fun_name[VAR_NAME_MAX];
    BOOL freed;
};

struct sCompileInfoStruct
{
    BOOL no_output;
    int err_num;
    struct sParserInfoStruct* pinfo;
    sNodeType* type;

    char sname[PATH_MAX];
    int sline;

    int stack_num;

    char compiling_struct_name[VAR_NAME_MAX];
    char compiling_fun_name[VAR_NAME_MAX];

    char fun_name[VAR_NAME_MAX];
    char real_fun_name[VAR_NAME_MAX];

    void* current_block;

    sNodeType* generics_type;

    sNodeType* result_type;
    void* function_lvtable;

    void* result_variable;

    BOOL last_expression_is_return;
    void* loop_end_block[LOOP_NEST_MAX];
    int num_loop;
    void* loop_begin_block[LOOP_NEST_MAX];
    int num_loop2;

    void* switch_expression;
    sNodeType* switch_expression_type;

    void* case_else_block;
    void* case_then_block;

    int mBlockLevel;

    BOOL prevent_from_free_right_value_objects;

    struct sNodeBlockStruct* current_node_block;

    struct sNodeBlockStruct* function_node_block;

    BOOL in_inline_function;
    int inline_sline;
    LLVMBasicBlockRef inline_func_end;

    BOOL in_lambda_function;
    int lambda_sline;

    BOOL has_block_result;
    void* andand_result_var;
    void* oror_result_var;

    LLVMMetadataRef function_meta_data;
    LLVMValueRef inline_result_variable;

    BOOL in_generics_function;
    char generics_sname[PATH_MAX];
    int generics_sline;

    LLVMBasicBlockRef block_after_creating_generics;

    struct sRightValueObject* right_value_objects;
};

typedef struct sCompileInfoStruct sCompileInfo;

int main()
{
    printf("sParserInfo %lu\n", sizeof(sParserInfo));
    printf("sVarTable %lu\n", sizeof(sVarTable));
    printf("sCompileInfo %lu\n", sizeof(sCompileInfo));

    return 0;
}



