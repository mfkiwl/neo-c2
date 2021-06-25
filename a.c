
#include <stdio.h>

#include <llvm-c/Core.h>
#include <llvm-c/DebugInfo.h>

#define BOOL int


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

struct sConstStruct
{
    char* mConst;
    unsigned int mSize;
    unsigned int mLen;
};

typedef struct sConstStruct sConst;

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

#define CLASS_NAME(klass) (CONS_str((&(klass)->mConst), (klass)->mClassNameOffset))

typedef struct sCLClassStruct sCLClass;

struct sNodeTypeStruct {
    sCLClass* mClass;

    struct sNodeTypeStruct* mGenericsTypes[1];
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

int main()
{
    printf("sNodeType %lu\n", sizeof(sNodeType));
    printf("sVar %lu\n", sizeof(sVar));
    printf("sVarTable %lu\n", sizeof(sVarTable));

    return 0;
}



