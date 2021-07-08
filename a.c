#include "config.h"
#include "buffer.h"
#include "xfunc.h"
#include "alignment.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdarg.h>

#include <llvm-c/Core.h>
#include <llvm-c/DebugInfo.h>

//////////////////////////////
/// limits 
//////////////////////////////
#define GENERICS_TYPES_MAX 10
#define VAR_NAME_MAX 128
#define CLASS_NUM_MAX 8192
#define PARSER_ERR_MSG_MAX 5
#define COMPILE_ERR_MSG_MAX 5
#define NEO_C_STACK_SIZE 512
#define LOCAL_VARIABLE_MAX 4096
#define PARAMS_MAX 32
#define METHOD_DEFAULT_PARAM_MAX 128
#define SOURCE_EXPRESSION_MAX 4096*2
#define ELIF_NUM_MAX 128
#define REAL_FUN_NAME_MAX (VAR_NAME_MAX*PARAMS_MAX+32)
#define REAL_STRUCT_NAME_MAX (VAR_NAME_MAX*PARAMS_MAX+32)
#define NODES_MAX 512
#define INIT_ARRAY_MAX 128
#define LOOP_NEST_MAX 256
#define TYPEDEF_MAX 2048
#define MACRO_MAX 1024
#define ARRAY_DIMENTION_MAX 5
#define FUN_VERSION_MAX 512
#define STRUCT_FIELD_MAX 2048

#define clint64 long long      // for 32 bit cpu

//////////////////////////////
/// progressive declaration
//////////////////////////////
struct sParserInfoStruct;
struct sNodeBlockStruct;
struct sCompileInfoStruct;
struct sVarTableStruct;

//////////////////////////////
/// main.c 
//////////////////////////////
extern BOOL gNCDebug;
extern char gFName[PATH_MAX];
extern struct sVarTableStruct* gModuleVarTable;

//////////////////////////////
/// constant.c 
//////////////////////////////
struct sConstStruct
{
    char* mConst;
    unsigned int mSize;
    unsigned int mLen;
};

typedef struct sConstStruct sConst;

#define CONS_str(constant, offset) (char*)((constant)->mConst + offset)

void sConst_init(sConst* self);
void sConst_init_with_size(sConst* self, unsigned int size);
void sConst_free(sConst* self);
void sConst_clone(sConst* self, sConst* constant);

unsigned int sConst_append(sConst* self, void* data, int size, BOOL no_output);
unsigned int append_int_value_to_constant_pool(sConst* constant, int n, BOOL no_output);
unsigned int append_float_value_to_constant_pool(sConst* constant, float n, BOOL no_output);
unsigned int append_double_value_to_constant_pool(sConst* constant, double n, BOOL no_output);
unsigned int append_str_to_constant_pool(sConst* constant, char* str, BOOL no_output);
unsigned int append_wstr_to_constant_pool(sConst* constant, char* str, BOOL no_output);

//////////////////////////////
/// klass.c 
//////////////////////////////
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

    char* mName;

    int mGenericsNum;
    int mMethodGenericsNum;
    
    char** mFieldName;
    struct sNodeTypeStruct** mFields;
    int mNumFields;

    void* mUndefinedStructType;

    int mVersion;
};

#define CLASS_NAME(klass) (klass->mName)

typedef struct sCLClassStruct sCLClass;

void class_init();
void class_final();

sCLClass* get_class(char* class_name);
sCLClass* alloc_struct(char* class_name, BOOL anonymous);
sCLClass* alloc_enum(char* class_name);
void add_fields_to_struct(sCLClass* klass, int num_fields, char** field_name, struct sNodeTypeStruct** fields);
sCLClass* alloc_union(char* class_name, BOOL anonymous, BOOL anonymous_var_name);
void add_fields_to_union(sCLClass* klass, int num_fields, char** field_name, struct sNodeTypeStruct** fields);
unsigned int get_hash_key(char* name, unsigned int max);
int get_field_index(sCLClass* klass, char* var_name, int* parent_field_index);
sCLClass* clone_class(sCLClass* klass);

extern BOOL gInhibitsRehashClasses;

//////////////////////////////
/// node_type.c
//////////////////////////////
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

void init_node_types();
void free_node_types();

BOOL check_the_same_fields(sNodeType* left_node, sNodeType* right_node);

sNodeType* clone_node_type(sNodeType* node_type);
sNodeType* create_node_type_with_class_name(char* class_name);
sNodeType* create_node_type_with_class_pointer(sCLClass* klass);
BOOL cast_posibility(sNodeType* left_type, sNodeType* right_type);
BOOL auto_cast_posibility(sNodeType* left_type, sNodeType* right_type);

BOOL substitution_posibility(sNodeType* left_type, sNodeType* right_type, struct sCompileInfoStruct* info);
BOOL type_identify(sNodeType* left, sNodeType* right);
BOOL type_identify_with_class_name(sNodeType* left, char* right_class_name);
BOOL is_number_type(sNodeType* node_type);
void show_node_type(sNodeType* node_type);
BOOL solve_generics(sNodeType** node_type, sNodeType* generics_type);
BOOL solve_method_generics(sNodeType** node_type, int num_method_generics_types, sNodeType* method_generics_types[GENERICS_TYPES_MAX]);
BOOL solve_typeof(sNodeType** node_type, struct sCompileInfoStruct* info);
BOOL is_typeof_type(sNodeType* node_type);
BOOL included_generics_type(sNodeType* node_type, sCLClass* checked_class[], int* num_checked_class);
BOOL get_type_of_method_generics(sNodeType* method_generics_types[GENERICS_TYPES_MAX], sNodeType* fun_param_type, sNodeType* param_type);
void create_type_name_from_node_type(char* type_name, int type_name_max, sNodeType* node_type, BOOL neo_c);
  
//////////////////////////////
/// vtable.c
//////////////////////////////
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

void init_vtable();
void final_vtable();

BOOL is_included_var_from_this_table_only(sVarTable* table, sVar* var);
sVarTable* init_block_vtable(sVarTable* lv_table, BOOL no_increment_block_level);

sVarTable* init_var_table();
sVarTable* clone_var_table(sVarTable* lv_table);
void restore_var_table(sVarTable* left, sVarTable* right);

void set_max_block_var_num(sVarTable* new_table, sVarTable* lv_table);

int get_variable_index(sVarTable* table, char* name, BOOL* parent);

void check_already_added_variable(sVarTable* table, char* name, struct sParserInfoStruct* info);

// result: (true) success (false) overflow the table or a variable which has the same name exists
BOOL add_variable_to_table(sVarTable* table, char* name, sNodeType* type_, BOOL readonly, void* llvm_value, int index, BOOL global, BOOL constant);

// result: (null) not found (sVar*) found
sVar* get_variable_from_table(sVarTable* table, char* name);

// result: (null) not found (sVar*) found
sVar* get_variable_from_index(sVarTable* table, int index);

int get_var_num(sVarTable* table);
void show_vtable(sVarTable* table);
void show_vtable_current_only(sVarTable* table);

int get_parent_var_num_of_sum(sVarTable* table);

void free_objects(sVarTable* table, struct sCompileInfoStruct* info);

// result: (null) not found (sVar*) found
sVar* get_variable_from_this_table_only(sVarTable* table, char* name);

void free_objects_on_return(struct sNodeBlockStruct* current_node_block, struct sCompileInfoStruct* info, LLVMValueRef ret_value, BOOL top_block);

//////////////////////////////
/// node_block.c
//////////////////////////////
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

BOOL parse_block_easy(ALLOC sNodeBlock** node_block, BOOL extern_clang, struct sParserInfoStruct* info);
BOOL parse_block(sNodeBlock* node_block, BOOL extern_clang, BOOL single_expression, struct sParserInfoStruct* info);
BOOL skip_block(struct sParserInfoStruct* info);


//////////////////////////////
/// typedef.c
//////////////////////////////
void init_typedef();
void final_typedef();

void add_typedef(char* name, sNodeType* node_type);
sNodeType* get_typedef(char* name);

//////////////////////////////
/// compiler.c
//////////////////////////////
BOOL delete_comment(sBuf* source, sBuf* source2);
BOOL read_source(char* fname, sBuf* source);
BOOL compile_source(char* fname, char* source, BOOL optimize, sVarTable* module_var_table);

extern char gMainModulePath[PATH_MAX];

//////////////////////////////
/// parser.c
//////////////////////////////
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

int parse_cmp(char* p, char* str);

typedef struct sParserParamStruct sParserParam;

void parser_init();
void parser_final();
void parser_err_msg(sParserInfo* info, char* msg);
void skip_spaces_and_lf(sParserInfo* info);
BOOL parse_word(char* buf, int buf_size, sParserInfo* info, BOOL print_out_err_msg, BOOL no_skip_lf);
void expect_next_character_with_one_forward(char* characters, sParserInfo* info);
BOOL parse_function(unsigned int* node, sNodeType* result_type, char* fun_name, char* struct_name, sParserInfo* info);
void expect_next_character_with_one_forward(char* characters, sParserInfo* info);
void skip_spaces(sParserInfo* info);

BOOL expression(unsigned int* node, BOOL comma, sParserInfo* info);
BOOL parse_sharp(sParserInfo* info);

//////////////////////////////
/// node.c
//////////////////////////////
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
extern LLVMBuilderRef gBuilder;

enum eNodeType { kNodeTypeIntValue, kNodeTypeUIntValue, kNodeTypeLongValue, kNodeTypeULongValue, kNodeTypeAdd, kNodeTypeSub, kNodeTypeStoreVariable, kNodeTypeLoadVariable, kNodeTypeDefineVariable, kNodeTypeCString, kNodeTypeFunction, kNodeTypeExternalFunction, kNodeTypeFunctionCall, kNodeTypeIf, kNodeTypeEquals, kNodeTypeNotEquals, kNodeTypeStruct, kNodeTypeObject, kNodeTypeStackObject, kNodeTypeStoreField, kNodeTypeLoadField, kNodeTypeWhile, kNodeTypeDoWhile, kNodeTypeGteq, kNodeTypeLeeq, kNodeTypeGt, kNodeTypeLe, kNodeTypeLogicalDenial, kNodeTypeTrue, kNodeTypeFalse, kNodeTypeAndAnd, kNodeTypeOrOr, kNodeTypeFor, kNodeTypeLambdaCall, kNodeTypeDerefference, kNodeTypeRefference, kNodeTypeNull, kNodeTypeClone, kNodeTypeLoadElement, kNodeTypeStoreElement, kNodeTypeChar, kNodeTypeMult, kNodeTypeDiv, kNodeTypeMod, kNodeTypeCast, kNodeTypeGenericsFunction, kNodeTypeInlineFunction, kNodeTypeTypeDef, kNodeTypeUnion, kNodeTypeLeftShift, kNodeTypeRightShift, kNodeTypeAnd, kNodeTypeXor, kNodeTypeOr, kNodeTypeReturn, kNodeTypeSizeOf, kNodeTypeSizeOfExpression, kNodeTypeNodes, kNodeTypeLoadFunction, kNodeTypeArrayWithInitialization, kNodeTypeStructWithInitialization, kNodeTypeNormalBlock, kNodeTypeSwitch, kNodeTypeBreak, kNodeTypeContinue, kNodeTypeCase, kNodeTypeLabel, kNodeTypeGoto, kNodeTypeIsHeap, kNodeTypeDelete, kNodeTypeConditional, kNodeTypeAlignOf, kNodeTypeAlignOfExpression, kNodeTypeBorrow, kNodeTypeDummyHeap, kNodeTypeManaged, kNodeTypeComplement, kNodeTypeStoreAddress, kNodeTypeLoadAddressValue, kNodeTypePlusPlus, kNodeTypeMinusMinus, kNodeTypeEqualPlus, kNodeTypeEqualMinus, kNodeTypeEqualMult, kNodeTypeEqualDiv, kNodeTypeEqualMod, kNodeTypeEqualLShift, kNodeTypeEqualRShift, kNodeTypeEqualAnd, kNodeTypeEqualXor, kNodeTypeEqualOr, kNodeTypeComma, kNodeTypeFunName, kNodeTypeNoMove };

struct sNodeTreeStruct 
{
    enum eNodeType mNodeType;

    unsigned int mLeft;
    unsigned int mRight;
    unsigned int mMiddle;

    char mSName[PATH_MAX];
    int mLine;

    union {
        int mIntValue;
        long long int mLongValue;
        unsigned long long int mULongValue;
        char mCharValue;
        sNodeType* mType;

        struct {
            char mVarName[VAR_NAME_MAX];
            BOOL mAlloc;
            BOOL mGlobal;
        } sStoreVariable;

        struct {
            char mVarName[VAR_NAME_MAX];
            BOOL mGlobal;
            BOOL mExtern;
        } sDefineVariable;

        struct {
            char mFunName[VAR_NAME_MAX];
        } sLoadFunction;

        struct {
            unsigned int mNodes[NODES_MAX];
            int mNumNodes;
        } sNodes;

        struct {
            char mVarName[VAR_NAME_MAX];
            BOOL mGlobal;
        } sLoadVariable;

        struct {
            char mVarName[VAR_NAME_MAX];
        } sManaged;

        struct {
            char* mString;
        } sString;

        struct {
            sNodeType* mNodeType;
        } sVaArg;

        struct {
            char mName[VAR_NAME_MAX];
            char mAsmName[VAR_NAME_MAX];
            char mSimpleName[VAR_NAME_MAX];
            sParserParam mParams[PARAMS_MAX];
            int mNumParams;
            sNodeType* mResultType;
            struct sNodeBlockStruct* mNodeBlock;
            BOOL mLambda;
            sVarTable* mVarTable;
            BOOL mVarArg;
            char mStructName[VAR_NAME_MAX];
            BOOL mOperatorFun;
            char* mBlockText;
            int mNumGenerics;
            char mGenericsTypeNames[PARAMS_MAX][VAR_NAME_MAX];

            int mNumMethodGenerics;
            char mMethodGenericsTypeNames[GENERICS_TYPES_MAX][VAR_NAME_MAX];
            BOOL mSimpleLambdaParam;
            BOOL mGenericsFunction;
            BOOL mConstructorFun;
            int mSLine;
            BOOL mInCLang;
            int mVersion;
            BOOL mFinalize;
            int mGenericsFunNum;
        } sFunction;

        struct {
            int mNumParams;
            unsigned int mParams[PARAMS_MAX];
        } sVector;

        struct {
            char mName[VAR_NAME_MAX];
            unsigned int mParams[PARAMS_MAX];
            int mNumParams;
            BOOL mMethod;
            BOOL mInCLang;
            BOOL mInherit;

            int mNumGenerics;
            char mGenericsTypeNames[PARAMS_MAX][VAR_NAME_MAX];
            int mVersion;
            char mImplStructName[VAR_NAME_MAX];
        } sFunctionCall;

        struct {
            unsigned int mExpressionNode;
            MANAGED struct sNodeBlockStruct* mIfNodeBlock;
            unsigned int mElifExpressionNodes[ELIF_NUM_MAX];
            MANAGED struct sNodeBlockStruct* mElifNodeBlocks[ELIF_NUM_MAX];
            int mElifNum;
            MANAGED struct sNodeBlockStruct* mElseNodeBlock;
        } sIf;

        struct {
            unsigned int mExpressionNode;
            MANAGED struct sNodeBlockStruct* mWhileNodeBlock;
        } sWhile;

        struct {
            sNodeType* mType;
            BOOL mUndefinedBody;
            BOOL mAnonymous;
        } sStruct;

        struct {
            sNodeType* mType;
            unsigned int mParams[PARAMS_MAX];
            int mNumParams;
        } sObject;

        struct {
            char mVarName[VAR_NAME_MAX];
        } sStoreField;

        struct {
            char mVarName[VAR_NAME_MAX];
        } sLoadField;

        struct {
            unsigned int mExpressionNode;
            unsigned int mExpressionNode2;
            unsigned int mExpressionNode3;
            MANAGED struct sNodeBlockStruct* mForNodeBlock;
        } sFor;

        struct {
            char* mBuf;
            char mSName[PATH_MAX];
            int mSLine;
        } sSimpleLambdaParam;

        struct {
            unsigned int mNodes[NODES_MAX];
            int mNumNodes;
        } sImpl;

        struct {
            char mName[VAR_NAME_MAX];
            sNodeType* mNodeType;
        } sTypeDef;

        struct {
            sNodeType* mType;
        } sSizeOf;

        struct {
            sNodeType* mType;
        } sAlignOf;

        struct {
            sNodeType* mType;
        } sIsHeap;

        struct {
            sNodeType* mType;
        } sIsManaged;

        struct {
            char mVarName[VAR_NAME_MAX];
            int mNumInitializeArrayValue;
            unsigned int mInitializeArrayValue[INIT_ARRAY_MAX];
        } sArrayWithInitialization;

        struct {
            struct sNodeBlockStruct* mNodeBlock;
            BOOL mHeap;
        } sNormalBlock;

        struct {
            unsigned int* mSwitchExpression;
            int mNumSwitchExpression;
            unsigned int mExpression;
        } sSwitch;

        struct {
            unsigned int mExpression;
            BOOL mLastCase;
            BOOL mFirstCase;
            BOOL mCaseAfterReturn;
        } sCase;

        struct {
            char mName[VAR_NAME_MAX];
        } sLabel;

        struct {
            char mName[VAR_NAME_MAX];
        } sGoto;

        struct {
            unsigned int mIndex[ARRAY_DIMENTION_MAX];
            int mArrayDimentionNum;
        } sStoreElement;

        struct {
            unsigned int mIndex[ARRAY_DIMENTION_MAX];
            int mArrayDimentionNum;
        } sLoadElement;
    } uValue;
};

struct LVALUEStruct {
    sNodeType* type;
    LLVMValueRef value;
    LLVMValueRef address;
    sVar* var;
    BOOL binded_value;
    BOOL load_field;
};

typedef struct LVALUEStruct LVALUE;

union uA {
    int mIntValue;
    long long int mLongValue;
    unsigned long long int mULongValue;
    char mCharValue;
    sNodeType* mType;

    struct {
        char mName[VAR_NAME_MAX];
        char mAsmName[VAR_NAME_MAX];
        char mSimpleName[VAR_NAME_MAX];
        sParserParam mParams[PARAMS_MAX];
        int mNumParams;
        sNodeType* mResultType;

        struct sNodeBlockStruct* mNodeBlock;
        BOOL mLambda;
        sVarTable* mVarTable;
        BOOL mVarArg;
        char mStructName[VAR_NAME_MAX];
        BOOL mOperatorFun;
        char* mBlockText;
        int mNumGenerics;
        char mGenericsTypeNames[PARAMS_MAX][VAR_NAME_MAX];

        int mNumMethodGenerics;
        char mMethodGenericsTypeNames[GENERICS_TYPES_MAX][VAR_NAME_MAX];
        BOOL mSimpleLambdaParam;
        BOOL mGenericsFunction;
        BOOL mConstructorFun;
        int mSLine;
        BOOL mInCLang;
        int mVersion;
        BOOL mFinalize;
        int mGenericsFunNum;
    } sFunction;
};

struct sX {
    char mName[VAR_NAME_MAX];
    char mAsmName[VAR_NAME_MAX];
    char mSimpleName[VAR_NAME_MAX];
    sParserParam mParams[PARAMS_MAX];
    int mNumParams;
    sNodeType* mResultType;

    struct sNodeBlockStruct* mNodeBlock;
    BOOL mLambda;
    sVarTable* mVarTable;
    BOOL mVarArg;
    char mStructName[VAR_NAME_MAX];
    BOOL mOperatorFun;
    char* mBlockText;
    int mNumGenerics;
    char mGenericsTypeNames[PARAMS_MAX][VAR_NAME_MAX];

    int mNumMethodGenerics;
    char mMethodGenericsTypeNames[GENERICS_TYPES_MAX][VAR_NAME_MAX];
    BOOL mSimpleLambdaParam;
    BOOL mGenericsFunction;
    BOOL mConstructorFun;
    int mSLine;
    BOOL mInCLang;
    int mVersion;
    BOOL mFinalize;
    int mGenericsFunNum;
};

struct sFunctionStruct {
    char* mName;
    int mNumParams;
    char* mParamNames[PARAMS_MAX];
    sNodeType* mParamTypes[PARAMS_MAX];
    sNodeType* mResultType;
    LLVMValueRef mLLVMFunction;
    char* mBlockText;
    BOOL mGenericsFunction;
    BOOL mVarArgs;
    int mNumGenerics;
    BOOL mExtern;
    char* mGenericsTypeNames[GENERICS_TYPES_MAX];
    char* mAsmFunName;
};

struct sGenericsStructTypeStruct
{
    char* mName;
    sNodeType* mType;
};

struct sLabelStruct {
    char* mName;
    LLVMBasicBlockRef mBlock;
};

struct sStructStruct {
    char* mName;
    LLVMTypeRef mLLVMType;
    sNodeType* mNodeType;
    BOOL mUndefinedBody;
};

typedef struct sStructStruct sStruct;

struct sTypeDefTable
{
    char* mName;
    sNodeType* mItem;
};

typedef struct sNodeTreeStruct sNodeTree;

sNodeTree* gNodes;


struct sXXX {
    char mName[VAR_NAME_MAX];
    char mAsmName[VAR_NAME_MAX];
    char mSimpleName[VAR_NAME_MAX];
    sParserParam mParams[PARAMS_MAX];
    int mNumParams;
    sNodeType* mResultType;
    struct sNodeBlockStruct* mNodeBlock;
    BOOL mLambda;
    sVarTable* mVarTable;
    BOOL mVarArg;
    char mStructName[VAR_NAME_MAX];
    BOOL mOperatorFun;
    char* mBlockText;
    int mNumGenerics;
    char mGenericsTypeNames[PARAMS_MAX][VAR_NAME_MAX];

    int mNumMethodGenerics;
    char mMethodGenericsTypeNames[GENERICS_TYPES_MAX][VAR_NAME_MAX];
    BOOL mSimpleLambdaParam;
    BOOL mGenericsFunction;
    BOOL mConstructorFun;
    int mSLine;
    BOOL mInCLang;
    int mVersion;
    BOOL mFinalize;
    int mGenericsFunNum;
};

union uLLL {
    int a;
    int b;
    char c[9];
};

union uLLL2 {
    int a;
    int b;
    char c[16];
};

union uLLL3 {
    int a;
    int b;
    char c[17];
};

union uLLL4 {
    int a;
    int b;
    char c[24];
};

union uLLL5 {
    int a;
    int b;
    char c[32];
};

struct sLLL {
    char c[128][32];
    long long int d;
    char e;
    long long int f;
};

union uLLL6 {
    int a;
    int b;
    struct sLLL c;
    char d[128];
};

int main()
{
    printf("sParserParam %u\n", sizeof(sParserParam));
    printf("sNodeTreeStruct %u\n", sizeof(struct sNodeTreeStruct));
    printf("uA %u\n", sizeof(union uA));
    printf("sX %u\n", sizeof(struct sX));
    printf("sCLClassStruct %u\n", sizeof(struct sCLClassStruct));
    printf("sNodeTypeStruct %u\n", sizeof(struct sNodeTypeStruct));
    printf("sVarStruct %u\n", sizeof(struct sVarStruct));
    printf("sVarTableStruct %u\n", sizeof(struct sVarTableStruct));
    printf("sNodeBlockStruct %u\n", sizeof(struct sNodeBlockStruct));
    printf("sParserInfoStruct %u\n", sizeof(struct sParserInfoStruct));
    printf("sParserInfoStruct %u\n", sizeof(struct sParserInfoStruct));
    printf("sRightValueObject %u\n", sizeof(struct sRightValueObject));
    printf("sCompileInfoStruct %u\n", sizeof(struct sCompileInfoStruct));
    printf("XXX %u\n", sizeof(struct sNodeBlockStruct));
    printf("%d\n", sizeof(size_t));
    printf("%d\n", sizeof(long));
    printf("%d\n", sizeof(long int));
    printf("%d\n", sizeof(long long int));
    printf("%d\n", sizeof(long double));

    printf("LVALUEStruct %d\n", sizeof(struct LVALUEStruct));
    printf("__pthread_cond_s %d\n", sizeof(struct __pthread_cond_s));
    printf("__pthread_internal_slist %d\n", sizeof(struct __pthread_internal_slist));
    printf("__pthread_mutex_s %d\n", sizeof(struct __pthread_mutex_s));
    printf("__pthread_rwlock_arch_t %d\n", sizeof(struct __pthread_rwlock_arch_t));
    printf("sBufStruct %d\n", sizeof(struct sBufStruct));
    printf("sCLClassStruct %d\n", sizeof(struct sCLClassStruct));
    printf("sCompileInfoStruct %d\n", sizeof(struct sCompileInfoStruct));
    printf("sFunctionStruct %d\n", sizeof(struct sFunctionStruct));
    printf("sGenericsStructTypeStruct %d\n", sizeof(struct sGenericsStructTypeStruct));
    printf("sLabelStruct %d\n", sizeof(struct sLabelStruct));
    printf("sNodeBlockStruct %d\n", sizeof(struct sNodeBlockStruct));
    printf("sNodeTreeStruct %d\n", sizeof(struct sNodeTreeStruct));
    printf("sNodeTypeStruct %d\n", sizeof(struct sNodeTypeStruct));
    printf("sParserInfoStruct %d\n", sizeof(struct sParserInfoStruct));
    printf("sParserParamStruct %d\n", sizeof(struct sParserParamStruct));
    printf("sRightValueObject %d\n", sizeof(struct sRightValueObject));
    printf("sStructStruct %d\n", sizeof(struct sStructStruct));
    printf("sTypeDefTable %d\n", sizeof(struct sTypeDefTable));
    printf("sVarStruct %d\n", sizeof(struct sVarStruct));
    printf("sVarTableStruct %d\n", sizeof(struct sVarTableStruct));
    
    long double yyy;

    printf("%Lf\n", yyy);

    struct __pthread_mutex_s a;

    struct sXXX xxx;
    printf("sXXX %d\n", sizeof(struct sXXX));

    int node_size = 5;
    gNodes = (sNodeTree*)calloc(1, sizeof(sNodeTree)*node_size);
    int node = 1;

    int x = (int)&gNodes[node];
    int y = (int)gNodes;

    printf("pointer &gNodes[1] %p gNodes %p %d %d\n", &gNodes[node], gNodes, x-y, sizeof(sNodeTree));

    union uLLL aaaa;
    union uLLL2 aaaa2;
    union uLLL3 aaaa3;
    union uLLL4 aaaa4;
    union uLLL5 aaaa5;
    union uLLL6 aaaa6;
    struct sLLL aaaa7;
    union uA aaaaa8;

    printf("%d\n", sizeof(union uLLL));
    printf("%d\n", sizeof(union uLLL2));
    printf("%d\n", sizeof(union uLLL3));
    printf("%d\n", sizeof(union uLLL4));
    printf("%d\n", sizeof(union uLLL5));
    printf("%d\n", sizeof(union uLLL5));
    printf("%d\n", sizeof(union uLLL6));
    printf("%d\n", sizeof(struct sLLL));

    return 0;
}

