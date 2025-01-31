#ifndef COMMON_H
#define COMMON_H 1

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
#define LOCAL_VARIABLE_MAX 1024
#define PARAMS_MAX 32
#define METHOD_DEFAULT_PARAM_MAX 128
#define SOURCE_EXPRESSION_MAX 4096*2
#define ELIF_NUM_MAX 128
#define REAL_FUN_NAME_MAX (VAR_NAME_MAX*PARAMS_MAX+32)
#define REAL_STRUCT_NAME_MAX (VAR_NAME_MAX*PARAMS_MAX+32)
#define NODES_MAX 1014
#define INIT_ARRAY_MAX 128
#define LOOP_NEST_MAX 256
#define TYPEDEF_MAX 2048
#define ARRAY_DIMENTION_MAX 5
#define FUN_VERSION_MAX 512
#define STRUCT_FIELD_MAX 2048
#define SELECT_MAX 64
#define ENUM_ELEMENT_MAX 512
#define MACRO_MAX 512

#define FUNCTION_VERSION_MAX 100

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
extern BOOL gNCGC;
extern BOOL gNCNoMacro;
extern BOOL gNCType;
extern BOOL gNCGlobal;
extern BOOL gNCFunction;
extern BOOL gNCClass;
extern BOOL gNCTypedef;
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

    char* mEnumElementNames[ENUM_ELEMENT_MAX];
    int mEnumElementValues[ENUM_ELEMENT_MAX];
    int mNumElementNum;

    BOOL mUser;
};

#define CLASS_NAME(klass) (klass->mName)

typedef struct sCLClassStruct sCLClass;

void class_init();
void class_final();

void show_classes();

sCLClass* get_class(char* class_name);
sCLClass* alloc_struct(char* class_name, BOOL anonymous, BOOL user);
sCLClass* alloc_enum(char* class_name_, int num_element, char** element_names, int* element_values);
void add_fields_to_struct(sCLClass* klass, int num_fields, char** field_names, struct sNodeTypeStruct** fields);
sCLClass* alloc_union(char* class_name, BOOL anonymous, BOOL anonymous_var_name);
void add_fields_to_union(sCLClass* klass, int num_fields, char** field_names, struct sNodeTypeStruct** fields);
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
    BOOL mUniq;
    int mSizeNum;
    BOOL mChannel;

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

    char mOriginalTypeName[VAR_NAME_MAX];

    BOOL mCurrentStackVariable;
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
void show_node_type_one_line(sNodeType* type);
BOOL solve_generics(sNodeType** node_type, sNodeType* generics_type);
BOOL solve_method_generics(sNodeType** node_type, int num_method_generics_types, sNodeType* method_generics_types[GENERICS_TYPES_MAX]);
void solve_method_generics2(sNodeType** left_type, sNodeType* right_type);
BOOL solve_typeof(sNodeType** node_type, struct sCompileInfoStruct* info);
BOOL is_typeof_type(sNodeType* node_type);
BOOL included_generics_type(sNodeType* node_type, sCLClass* checked_class[], int* num_checked_class);
BOOL get_type_of_method_generics(sNodeType* method_generics_types[GENERICS_TYPES_MAX], sNodeType* fun_param_type, sNodeType* param_type);
void create_type_name_from_node_type(char* type_name, int type_name_max, sNodeType* node_type, BOOL neo_c);

sCLClass* get_same_current_stack(int num_fields, char** field_names, sNodeType** fields);
  
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
    sVar mLocalVariables[LOCAL_VARIABLE_MAX]; 
    int mVarNum;
    int mMaxBlockVarNum;

    int mBlockLevel;

    struct sVarTableStruct* mParent;            // make linked list
    struct sVarTableStruct* mNext;              // for free var table

    struct sVarTableStruct* mCloneTable;
    struct sVarTableStruct* mClonedTable;
};

typedef struct sVarTableStruct sVarTable;

void init_vtable();
void final_vtable();

BOOL is_included_var_from_this_table_only(sVarTable* table, sVar* var);
sVarTable* init_block_vtable(sVarTable* lv_table, BOOL no_increment_block_level);

sVarTable* init_var_table();
sVarTable* clone_var_table(sVarTable* lv_table);
void restore_var_table(sVarTable* left, sVarTable* right);
void create_current_stack_frame_struct(char* type_name, sVarTable* lv_table);

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

// result: (null) not found (sVar*) found
sVar* get_variable_from_this_table_only(sVarTable* table, char* name);

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
    BOOL mTerminated;
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

void show_typedefs();
void add_typedef(char* name, sNodeType* node_type, BOOL user);
sNodeType* get_typedef(char* name);

//////////////////////////////
/// compiler.c
//////////////////////////////
BOOL read_source(char* fname, sBuf* source);
BOOL compile_source(char* fname, char** source, BOOL optimize, sVarTable* module_var_table);

extern char gMainModulePath[PATH_MAX];

//////////////////////////////
/// parser.c
//////////////////////////////
struct sParserInfoStruct
{
    sBuf mConst;

    char* p;
    char sname[PATH_MAX];
    char** source;
    char* module_name;
    int sline;
    int err_num;
    int parse_phase;
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

void create_lambda_name(char* lambda_name, size_t size_lambda_name, char* module_name);
BOOL expression(unsigned int* node, BOOL comma, sParserInfo* info);
BOOL parse_sharp(sParserInfo* info);
int parse_cmp(char* p, char* str);
BOOL skip_paren(char head_char, char tail_char, sParserInfo* info);
BOOL get_number(BOOL minus, unsigned int* node, sParserInfo* info);
BOOL get_regex(unsigned int* node, sParserInfo* info);
void create_anonymous_name(char* name, int name_size);
BOOL parse_attribute(sParserInfo* info, char* asm_fname);
BOOL parse_typedef_attribute(sParserInfo* info);
BOOL parse_variable_name(char* buf, int buf_size, sParserInfo* info, sNodeType* node_type, BOOL array_size_is_dynamic, BOOL param_in_function);
BOOL parse_annotation(sParserInfo* info);
BOOL parse_type(sNodeType** result_type, sParserInfo* info, char* func_pointer_name, BOOL definition_typedef, BOOL definition_struct, BOOL* function_pointer_result_function, BOOL definition_function_pointer_result_function);
BOOL parse_struct(unsigned int* node, char* struct_name, int size_struct_name, BOOL anonymous, BOOL* terminated, BOOL definition_struct, sParserInfo* info) ;
BOOL parse_union(unsigned int* node, char* union_name, int size_union_name, BOOL* terminated, BOOL definition_struct, sParserInfo* info) ;
void create_lambda_name(char* lambda_name, size_t size_lambda_name, char* module_name);
BOOL parse_lambda(unsigned int* node, sNodeType* result_type, sParserInfo* info);
BOOL parse_enum(unsigned int* node, char* name, int name_size, BOOL* terminated, sParserInfo* info);
BOOL is_type_name(char* buf, sParserInfo* info);
BOOL is_premitive_type(char* buf, sParserInfo* info);
BOOL parse_return(unsigned int* node, sParserInfo* info);
BOOL parse_variable(unsigned int* node, sNodeType* result_type, char* name, BOOL extern_, sParserInfo* info, BOOL readonly);
BOOL parse_param(sParserParam* param, sParserInfo* info);
BOOL get_block_text(sBuf* buf, sParserInfo* info, BOOL append_head_currly_brace);
BOOL parse_params(sParserParam* params, int* num_params, sParserInfo* info, int character_type, BOOL* var_arg);
BOOL parse_generics_function(unsigned int* node, sNodeType* result_type, char* fun_name, char* struct_name, sParserInfo* info);
BOOL parse_method_generics_function(unsigned int* node, char* struct_name, sParserInfo* info);
void parse_version(int* version, sParserInfo* info);
BOOL parse_function(unsigned int* node, sNodeType* result_type, char* fun_name, char* struct_name, sParserInfo* info);
BOOL parse_inline_function(unsigned int* node, char* struct_name, sParserInfo* info);
BOOL parse_funcation_call_params(int* num_params, unsigned int* params, sParserInfo* info);
BOOL parse_if(unsigned int* node, sParserInfo* info);
BOOL postposition_operator(unsigned int* node, BOOL enable_assginment, sParserInfo* info);
BOOL parse_while(unsigned int* node, sParserInfo* info);
BOOL parse_do(unsigned int* node, sParserInfo* info);
BOOL parse_for(unsigned int* node, sParserInfo* info);
BOOL parse_select(unsigned int* node, sParserInfo* info);
BOOL parse_pselect(unsigned int* node, sParserInfo* info);
BOOL parse_alloca(unsigned int* node, sParserInfo* info);
BOOL parse_sizeof(unsigned int* node, sParserInfo* info);
BOOL parse_alignof(unsigned int* node, sParserInfo* info);
BOOL parse_clone(unsigned int* node, sParserInfo* info);
BOOL parse_is_gc_heap(unsigned int* node, sParserInfo* info);
BOOL parse_typedef(unsigned int* node, sParserInfo* info);
BOOL parse_switch(unsigned int* node, sParserInfo* info);
BOOL parse_case(unsigned int* node, sParserInfo* info);
BOOL parse_default(unsigned int* node, sParserInfo* info);
BOOL parse_label(unsigned int* node, char* name, sParserInfo* info);
BOOL parse_goto(unsigned int* node, sParserInfo* info);
BOOL get_hex_number(unsigned int* node, sParserInfo* info);
BOOL get_oct_number(unsigned int* node, sParserInfo* info);
BOOL parse_impl(unsigned int* node, sParserInfo* info);
void parse_impl_end(sParserInfo* info);
BOOL parse_new(unsigned int* node, sParserInfo* info);
BOOL parse_var(unsigned int* node, sParserInfo* info, BOOL readonly);
BOOL parse_inherit(unsigned int* node, sParserInfo* info);
BOOL parse_come(unsigned int* node, sParserInfo* info);
BOOL parse_macro(unsigned int* node, sParserInfo* info);
BOOL parse_defer(unsigned int* node, sParserInfo* info);
BOOL parse_call_macro(unsigned int* node, char* name, sParserInfo* info);
BOOL parse_function_pointer_result_function(unsigned int* node, sParserInfo* info);
BOOL expression_node(unsigned int* node, BOOL enable_assginment, sParserInfo* info);

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

    struct sNodeBlockStruct* current_node_block;

    struct sNodeBlockStruct* function_node_block;

    BOOL in_inline_function;
    char in_inline_function_name[VAR_NAME_MAX];
    int inline_sline;
    LLVMBasicBlockRef inline_func_end;

    BOOL in_lambda_function;
    int lambda_sline;
    BOOL in_select_block;

    BOOL has_block_result;

    void* andand_result_var;
    void* oror_result_var;

    LLVMMetadataRef function_meta_data;
    LLVMValueRef inline_result_variable;

    BOOL in_generics_function;
    char generics_sname[PATH_MAX];
    int generics_sline;

    LLVMBasicBlockRef block_after_creating_generics;

    BOOL in_thread_function;

    char calling_fun_name[VAR_NAME_MAX];

    sNodeType* method_block_generics_type;

    sNodeType* return_result_type;

    LLVMBasicBlockRef defer_block;
    BOOL empty_function;
};

typedef struct sCompileInfoStruct sCompileInfo;
extern LLVMBuilderRef gBuilder;

enum eNodeType { kNodeTypeIntValue, kNodeTypeFloatValue, kNodeTypeDoubleValue, kNodeTypeUIntValue, kNodeTypeLongValue, kNodeTypeULongValue, kNodeTypeAdd, kNodeTypeSub, kNodeTypeStoreVariable, kNodeTypeLoadVariable, kNodeTypeLoadChannelElement, kNodeTypeDefineVariable, kNodeTypeIsGCHeap, kNodeTypeCString, kNodeTypeRegex, kNodeTypeFunction, kNodeTypeExternalFunction, kNodeTypeFunctionCall, kNodeTypeComeFunctionCall, kNodeTypeIf, kNodeTypeEquals, kNodeTypeNotEquals, kNodeTypeStruct, kNodeTypeObject, kNodeTypeStackObject, kNodeTypeStoreField, kNodeTypeLoadField, kNodeTypeWhile, kNodeTypeDoWhile, kNodeTypeGteq, kNodeTypeLeeq, kNodeTypeGt, kNodeTypeLe, kNodeTypeLogicalDenial, kNodeTypeTrue, kNodeTypeFalse, kNodeTypeAndAnd, kNodeTypeOrOr, kNodeTypeFor, kNodeTypeLambdaCall, kNodeTypeDerefference, kNodeTypeRefference, kNodeTypeNull, kNodeTypeClone, kNodeTypeLoadElement, kNodeTypeStoreElement, kNodeTypeChar, kNodeTypeMult, kNodeTypeDiv, kNodeTypeMod, kNodeTypeCast, kNodeTypeGenericsFunction, kNodeTypeInlineFunction, kNodeTypeTypeDef, kNodeTypeUnion, kNodeTypeLeftShift, kNodeTypeRightShift, kNodeTypeAnd, kNodeTypeXor, kNodeTypeOr, kNodeTypeReturn, kNodeTypeSizeOf, kNodeTypeSizeOfExpression, kNodeTypeNodes, kNodeTypeLoadFunction, kNodeTypeArrayWithInitialization, kNodeTypeStructWithInitialization, kNodeTypeNormalBlock, kNodeTypeSelect, kNodeTypePSelect, kNodeTypeSwitch, kNodeTypeBreak, kNodeTypeContinue, kNodeTypeCase, kNodeTypeLabel, kNodeTypeGoto, kNodeTypeConditional, kNodeTypeAlignOf, kNodeTypeAlignOfExpression, kNodeTypeComplement, kNodeTypeStoreAddress, kNodeTypeLoadAddressValue, kNodeTypePlusPlus, kNodeTypeMinusMinus, kNodeTypeEqualPlus, kNodeTypeEqualMinus, kNodeTypeEqualMult, kNodeTypeEqualDiv, kNodeTypeEqualMod, kNodeTypeEqualLShift, kNodeTypeEqualRShift, kNodeTypeEqualAnd, kNodeTypeEqualXor, kNodeTypeEqualOr, kNodeTypeComma, kNodeTypeFunName, kNodeTypeJoin, kNodeTypeWriteChannel, kNodeTypeReadChannel, kNodeTypeStack, kNodeTypeMethodBlock, kNodeTypeDefer };

struct sNodeTreeStruct 
{
    enum eNodeType mNodeType;

    unsigned int mLeft;
    unsigned int mRight;
    unsigned int mMiddle;
    
    BOOL mTerminated;

    char mSName[PATH_MAX];
    int mLine;

    union {
        int mIntValue;
        long long int mLongValue;
        unsigned long long int mULongValue;
        char mCharValue;
        sNodeType* mType;
        
        float mFloatValue;
        double mDoubleValue;

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
            char* mString;
            BOOL mGlobal;
            BOOL mIgnoreCase;
        } sRegex;

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
            unsigned int mExpressionNode;
        } sDefer;

        struct {
            sNodeType* mType;
            BOOL mUndefinedBody;
            BOOL mAnonymous;
        } sStruct;

        struct {
            sNodeType* mType;
            unsigned int mParams[PARAMS_MAX];
            int mNumParams;
            BOOL mGC;
        } sObject;

        struct {
            BOOL mGC;
        } sClone;

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
            struct sNodeBlockStruct* mPipeBlocks[SELECT_MAX];
            char mPipes[SELECT_MAX][VAR_NAME_MAX];
            struct sNodeBlockStruct* mDefaultBlock;
            int mNumPipes;
        } sSelect;

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

        struct {
            sVarTable* mVarTable;
        } sStack;

        struct {
            char* mBlockText;
            char mBlockTextSName[PATH_MAX];
            int mBlockTextSLine;
            sVarTable* mVarTable;
            sNodeType* mResultType;
        } sMethodBlock;
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

void push_value_to_stack_ptr(LVALUE* value, sCompileInfo* info);
void dec_stack_ptr(int value, sCompileInfo* info);
void arrange_stack(sCompileInfo* info, int top);
LVALUE* get_value_from_stack(int offset);
BOOL get_const_value_from_node(int* array_size, unsigned int array_size_node, sParserInfo* info);

typedef struct sNodeTreeStruct sNodeTree;

extern sNodeTree* gNodes;
extern int gUsedNodes;
extern LLVMModuleRef  gModule;
extern LLVMContextRef gContext;
extern LLVMValueRef gFunction;
extern char gFunctionName[VAR_NAME_MAX];

void init_nodes(char* sname);
void free_nodes(char* snmae);

unsigned int alloc_node();

ALLOC sNodeBlock* sNodeBlock_alloc();
void sNodeBlock_free(sNodeBlock* block);

void append_node_to_node_block(sNodeBlock* node_block, unsigned int node);

void compile_err_msg(sCompileInfo* info, const char* msg, ...);
LLVMValueRef clone_object(sNodeType* node_type, LLVMValueRef obj, sCompileInfo* info);

void show_node(unsigned int node);
BOOL compile(unsigned int node, sCompileInfo* info);

struct sFunctionStruct 
{
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
    BOOL mUser;
    char* mSource;
    char mSName[PATH_MAX];
    int mSLine;
};

typedef struct sFunctionStruct sFunction;

extern sNodeType* gComeFunctionResultType;

void setCurrentDebugLocation(int sline, sCompileInfo* info);
void setNullCurrentDebugLocation(int sline, sCompileInfo* info);
LLVMMetadataRef create_llvm_debug_type(sNodeType* node_type, sCompileInfo* info);
void createDebugFunctionInfo(char* fname, int sline, char* fun_name, sFunction* function, char* module_name, sCompileInfo* info);
void finishDebugFunctionInfo();
unsigned int alloc_node();
sNodeBlock* sNodeBlock_alloc();
void sNodeBlock_free(sNodeBlock* block);
void append_node_to_node_block(sNodeBlock* node_block, unsigned int node);
void push_value_to_stack_ptr(LVALUE* value, sCompileInfo* info);
void dec_stack_ptr(int value, sCompileInfo* info);
void arrange_stack(sCompileInfo* info, int top);
LVALUE* get_value_from_stack(int offset);
void set_debug_info_to_variable(LLVMValueRef value, sNodeType* node_type, char* name, int sline, sCompileInfo* info);

struct sStructStruct {
    char* mName;
    LLVMTypeRef mLLVMType;
    sNodeType* mNodeType;
    BOOL mUndefinedBody;
};

typedef struct sStructStruct sStruct;

struct sLabelStruct {
    char* mName;
    LLVMBasicBlockRef mBlock;
};

typedef struct sLabelStruct sLabel;


void create_generics_struct_name(char* struct_name, size_t size, sNodeType* struct_type);
LLVMTypeRef create_llvm_type_from_node_type(sNodeType* node_type);
LLVMTypeRef create_llvm_type_with_class_name(char* class_name);
BOOL cast_right_type_to_left_type(sNodeType* left_type, sNodeType** right_type, LVALUE* rvalue, struct sCompileInfoStruct* info);
BOOL get_const_value_from_node(int* array_size, unsigned int array_size_node, sParserInfo* info);
BOOL create_llvm_struct_type(char* struct_name, sNodeType* node_type, sNodeType* generics_type, BOOL undefined_body);
uint64_t get_struct_size(sCLClass* klass, sNodeType* generics_type, int* alignment);
uint64_t get_union_size(sCLClass* klass, sNodeType* generics_type, int* alignment);
uint64_t get_size_from_node_type(sNodeType* node_type, int* alignment);
BOOL create_llvm_union_type(sNodeType* node_type, sNodeType* generics_type, BOOL undefined_body, sCompileInfo* info);
int get_llvm_alignment_from_node_type(sNodeType* node_type);
void compile_err_msg(sCompileInfo* info, const char* msg, ...);
BOOL compile_block(sNodeBlock* block, sCompileInfo* info);
BOOL compile_conditional_expression(unsigned int node, sCompileInfo* info);

struct sGenericsStructTypeStruct
{
    char* mName;
    sNodeType* mType;
};

typedef struct sGenericsStructTypeStruct sGenericsStructType;

BOOL create_generics_struct_type(sNodeType* node_type);
BOOL add_generics_struct_type_to_table(char* name, sNodeType* node_type);
sGenericsStructType* get_generics_struct_from_table(char* name);

BOOL xisdigit(char c);
BOOL xisalpha(char c);
BOOL xisalnum(char c);

//////////////////////////////
/// node_op.c ///
//////////////////////////////
unsigned int sNodeTree_create_plus_plus(unsigned int left_node, sParserInfo* info);
unsigned int sNodeTree_create_minus_minus(unsigned int left_node, sParserInfo* info);
unsigned int sNodeTree_create_equal_plus(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_equal_minus(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_equal_mult(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_equal_div(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_equal_mod(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_equal_lshift(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_equal_rshift(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_equal_and(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_equal_xor(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_equal_or(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_left_shift(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_right_shift(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_and(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_xor(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_or(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_mult(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_div(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_mod(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_gteq(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_leeq(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_gt(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_le(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_logical_denial(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_and_and(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_or_or(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_complement(unsigned int left_node, sParserInfo* info);
unsigned int sNodeTree_create_add(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_sub(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_equals(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);
unsigned int sNodeTree_create_not_equals(unsigned int left, unsigned int right, unsigned int middle, sParserInfo* info);

BOOL compile_equal_or(unsigned int node, sCompileInfo* info);
BOOL compile_equal_xor(unsigned int node, sCompileInfo* info);
BOOL compile_equal_and(unsigned int node, sCompileInfo* info);
BOOL compile_equal_rshift(unsigned int node, sCompileInfo* info);
BOOL compile_equal_lshift(unsigned int node, sCompileInfo* info);
BOOL compile_equal_mod(unsigned int node, sCompileInfo* info);
BOOL compile_equal_div(unsigned int node, sCompileInfo* info);
BOOL compile_equal_mult(unsigned int node, sCompileInfo* info);
BOOL compile_equal_minus(unsigned int node, sCompileInfo* info);
BOOL compile_equal_plus(unsigned int node, sCompileInfo* info);
BOOL compile_minus_minus(unsigned int node, sCompileInfo* info);
BOOL compile_plus_plus(unsigned int node, sCompileInfo* info);
BOOL compile_complement(unsigned int node, sCompileInfo* info);
BOOL compile_add(unsigned int node, sCompileInfo* info);
BOOL compile_sub(unsigned int node, sCompileInfo* info);
BOOL compile_mult(unsigned int node, sCompileInfo* info);
BOOL compile_div(unsigned int node, sCompileInfo* info);
BOOL compile_mod(unsigned int node, sCompileInfo* info);
BOOL compile_equals(unsigned int node, sCompileInfo* info);
BOOL compile_not_equals(unsigned int node, sCompileInfo* info);
BOOL compile_gteq(unsigned int node, sCompileInfo* info);
BOOL compile_leeq(unsigned int node, sCompileInfo* info);
BOOL compile_gt(unsigned int node, sCompileInfo* info);
BOOL compile_le(unsigned int node, sCompileInfo* info);
BOOL compile_logical_denial(unsigned int node, sCompileInfo* info);
BOOL compile_left_shift(unsigned int node, sCompileInfo* info);
BOOL compile_right_shift(unsigned int node, sCompileInfo* info);
BOOL compile_and(unsigned int node, sCompileInfo* info);
BOOL compile_xor(unsigned int node, sCompileInfo* info);
BOOL compile_or(unsigned int node, sCompileInfo* info);

//////////////////////////////
/// node_var.c ///
//////////////////////////////
void node_var_init();
void node_var_final();

BOOL add_struct_to_table(char* name, sNodeType* node_type, LLVMTypeRef llvm_type, BOOL undefined_body);
sStruct* get_struct_from_table(char* name);

unsigned int sNodeTree_create_stack(sParserInfo* info);

unsigned int sNodeTree_create_load_channel_element(unsigned int array, unsigned int num_chanel, sParserInfo* info);
unsigned int sNodeTree_create_stack_object(sNodeType* node_type, unsigned int object_num, char* sname, int sline, sParserInfo* info);
unsigned int sNodeTree_create_dereffernce(unsigned int left_node, sParserInfo* info);
unsigned int sNodeTree_create_reffernce(unsigned int left_node, sParserInfo* info);
unsigned int sNodeTree_create_clone(unsigned int left, BOOL gc, sParserInfo* info);
unsigned int sNodeTree_create_is_gc_heap(unsigned int left, sParserInfo* info);
unsigned int sNodeTree_create_load_array_element(unsigned int array, unsigned int index_node[], int num_dimetion, sParserInfo* info);
unsigned int sNodeTree_create_store_element(unsigned int array, unsigned int index_node[], int num_dimetion, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_func_name(sParserInfo* info);
unsigned int sNodeTree_create_load_adress_value(unsigned int address_node, sParserInfo* info);
unsigned int sNodeTree_create_store_value_to_address(unsigned int address_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_struct_with_initialization(char* name, int num_initialize_array_value, unsigned int* initialize_array_value, unsigned int left_node, sParserInfo* info);
unsigned int sNodeTree_create_array_initializer(char* name, int num_initialize_array_value, unsigned int* initialize_array_value, unsigned int left_node, sParserInfo* info);
unsigned int sNodeTree_create_load_function(char* fun_name, sParserInfo* info, int sline);
unsigned int sNodeTree_create_sizeof(sNodeType* node_type, sParserInfo* info);
unsigned int sNodeTree_create_sizeof_expression(unsigned int lnode, sParserInfo* info);
unsigned int sNodeTree_create_alignof(sNodeType* node_type, sParserInfo* info);
unsigned int sNodeTree_create_alignof_expression(unsigned int lnode, sParserInfo* info);
unsigned int sNodeTree_create_load_variable(char* var_name, sParserInfo* info);
unsigned int sNodeTree_create_define_variable(char* var_name, BOOL extern_, BOOL global, sParserInfo* info);
unsigned int sNodeTree_create_store_variable(char* var_name, int right, BOOL alloc, BOOL global, sParserInfo* info);
unsigned int sNodeTree_struct(sNodeType* struct_type, sParserInfo* info, char* sname, int sline, BOOL undefined_body);
unsigned int sNodeTree_union(sNodeType* struct_type, sParserInfo* info, char* sname, int sline, BOOL undefined_body);
unsigned int sNodeTree_create_object(sNodeType* node_type, unsigned int object_num, int num_params, unsigned int* params, char* sname, int sline, BOOL gc, sParserInfo* info);
unsigned int sNodeTree_create_store_field(char* var_name, unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_load_field(char* name, unsigned int left_node, sParserInfo* info);
unsigned int sNodeTree_create_cast(sNodeType* left_type, unsigned int left_node, sParserInfo* info);
unsigned int sNodeTree_create_typedef(char* name, sNodeType* node_type, sParserInfo* info);
unsigned int sNodeTree_create_write_channel(unsigned int address_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_read_channel(unsigned int left_node, sParserInfo* info);

BOOL is_generics_type(sNodeType* node_type);
BOOL is_method_generics_type(sNodeType* node_type);
BOOL is_generics_struct_type(sNodeType* node_type);

BOOL compile_read_channel(unsigned int node, sCompileInfo* info);
BOOL compile_write_channel(unsigned int node, sCompileInfo* info);
BOOL compile_load_channel_element(unsigned int node, sCompileInfo* info);
BOOL compile_func_name(unsigned int node, sCompileInfo* info);
BOOL compile_load_address_value(unsigned int node, sCompileInfo* info);
BOOL compile_store_address(unsigned int node, sCompileInfo* info);
BOOL compile_struct_with_initialization(unsigned int node, sCompileInfo* info);
BOOL compile_array_initializer(unsigned int node, sCompileInfo* info);
BOOL compile_load_function(unsigned int node, sCompileInfo* info);
BOOL compile_alignof(unsigned int node, sCompileInfo* info);
BOOL compile_alignof_expression(unsigned int node, sCompileInfo* info);
BOOL compile_sizeof(unsigned int node, sCompileInfo* info);
BOOL compile_sizeof_expression(unsigned int node, sCompileInfo* info);
BOOL compile_load_variable(unsigned int node, sCompileInfo* info);
BOOL compile_define_variable(unsigned int node, sCompileInfo* info);
BOOL compile_store_variable(unsigned int node, sCompileInfo* info);
BOOL compile_struct(unsigned int node, sCompileInfo* info);
BOOL compile_union(unsigned int node, sCompileInfo* info);
BOOL compile_object(unsigned int node, sCompileInfo* info);
BOOL compile_stack_object(unsigned int node, sCompileInfo* info);
BOOL compile_store_field(unsigned int node, sCompileInfo* info);
BOOL compile_load_field(unsigned int node, sCompileInfo* info);
BOOL compile_dereffernce(unsigned int node, sCompileInfo* info);
BOOL compile_reffernce(unsigned int node, sCompileInfo* info);
BOOL compile_clone(unsigned int node, sCompileInfo* info);
BOOL compile_is_gc_heap(unsigned int node, sCompileInfo* info);
BOOL compile_load_element(unsigned int node, sCompileInfo* info);
BOOL compile_store_element(unsigned int node, sCompileInfo* info);
BOOL compile_cast(unsigned int node, sCompileInfo* info);
BOOL compile_typedef(unsigned int node, sCompileInfo* info);
BOOL compile_stack(unsigned int node, sCompileInfo* info);

//////////////////////////////
/// node_value.c ///
//////////////////////////////
unsigned int sNodeTree_create_c_string_value(MANAGED char* value, int len, int sline, sParserInfo* info);
unsigned int sNodeTree_create_regex_value(MANAGED char* value, BOOL global, BOOL ignore_case, int sline, sParserInfo* info);
unsigned int sNodeTree_create_int_value(int value, sParserInfo* info);
unsigned int sNodeTree_create_float_value(float value, sParserInfo* info);
unsigned int sNodeTree_create_double_value(double value, sParserInfo* info);
unsigned int sNodeTree_create_uint_value(int value, sParserInfo* info);
unsigned int sNodeTree_create_long_value(long long int value, sParserInfo* info);
unsigned int sNodeTree_create_ulong_value(unsigned long long int value, sParserInfo* info);
unsigned int sNodeTree_create_character_value(char c, sParserInfo* info);
unsigned int sNodeTree_create_true(sParserInfo* info);
unsigned int sNodeTree_create_false(sParserInfo* info);
unsigned int sNodeTree_create_null(sParserInfo* info);

BOOL compile_c_string_value(unsigned int node, sCompileInfo* info);
BOOL compile_regex_value(unsigned int node, sCompileInfo* info);
BOOL compile_int_value(unsigned int node, sCompileInfo* info);
BOOL compile_uint_value(unsigned int node, sCompileInfo* info);
BOOL compile_long_value(unsigned long long int node, sCompileInfo* info);
BOOL compile_ulong_value(unsigned long long int node, sCompileInfo* info);
BOOL compile_char_value(unsigned int node, sCompileInfo* info);
BOOL compile_true(unsigned int node, sCompileInfo* info);
BOOL compile_false(unsigned int node, sCompileInfo* info);
BOOL compile_null(unsigned int node, sCompileInfo* info);
BOOL compile_float_value(unsigned int node, sCompileInfo* info);
BOOL compile_double_value(unsigned int node, sCompileInfo* info);

//////////////////////////////
/// node_function.c///
//////////////////////////////
extern int gThreadNum;

void node_function_init();
void node_function_final();

void show_funcs();
void show_func(sFunction* fun, BOOL code);

BOOL add_function_to_table(char* name, int num_params, char** param_names, sNodeType** param_types, sNodeType* result_type, LLVMValueRef llvm_fun, char* block_text, BOOL generics_function, BOOL var_args, int num_generics, char** generics_type_names, BOOL extern_, char* asm_fun_name, BOOL user, char* source, char* sname, int sline);
sFunction* get_function_from_table(char* name);

unsigned int sNodeTree_create_lambda_call(unsigned int lambda_node, unsigned int* params, int num_params, sParserInfo* info);
unsigned int sNodeTree_create_external_function(char* fun_name, char* asm_fname, sParserParam* params, int num_params, BOOL var_arg, sNodeType* result_type, char* struct_name, BOOL operator_fun, int version, sParserInfo* info);


unsigned int sNodeTree_create_function(char* fun_name, char* asm_fname, sParserParam* params, int num_params, sNodeType* result_type, MANAGED struct sNodeBlockStruct* node_block, BOOL lambda_, sVarTable* block_var_table, char* struct_name, BOOL operator_fun, BOOL constructor_fun, BOOL simple_lambda_param, sParserInfo* info, BOOL generics_function, BOOL var_arg, int version, BOOL finalize, int generics_fun_num, char* simple_fun_name, int sline);

unsigned int sNodeTree_create_function_call(char* fun_name, unsigned int* params, int num_params, BOOL method, BOOL inherit, int version, sParserInfo* info);
unsigned int sNodeTree_create_come_function_call(char* fun_name, unsigned int* params, int num_params, sParserInfo* info);
unsigned int sNodeTree_create_join(sParserInfo* info);
unsigned int sNodeTree_create_generics_function(char* fun_name, sParserParam* params, int num_params, sNodeType* result_type, MANAGED char* block_text, char* struct_name, char* sname, int sline, BOOL va_arg, int version, sParserInfo* info);
unsigned int sNodeTree_create_inline_function(char* fun_name, sParserParam* params, int num_params, sNodeType* result_type, MANAGED char* block_text, char* struct_name, char* sname, int sline, BOOL var_arg, sParserInfo* info);
unsigned int sNodeTree_create_method_block(MANAGED char* block, char* block_text_sname, int block_text_sline, sNodeType* result_type, sParserInfo* info);

void create_real_fun_name(char* real_fun_name, size_t size_real_fun_name, char* fun_name, char* struct_name);
void llvm_change_block(LLVMBasicBlockRef current_block, sCompileInfo* info);
BOOL create_generics_function(LLVMValueRef* llvm_fun, sFunction* fun, char* fun_name, sNodeType* generics_type, int num_method_generics_types, sNodeType** method_generics_types, sCompileInfo* info);
BOOL solve_type(sNodeType** node_type, sNodeType* generics_type, int num_method_generics_types, sNodeType** method_generics_types, sCompileInfo* info);
void create_generics_fun_name(char* real_fun_name, int size_real_fun_name, char* fun_name,  sNodeType* generics_type, int num_method_generics_types, sNodeType** method_generics_types);


BOOL compile_external_function(unsigned int node, sCompileInfo* info);
BOOL compile_function_call(unsigned int node, sCompileInfo* info);
BOOL compile_come_function_call(unsigned int node, sCompileInfo* info);
BOOL compile_function(unsigned int node, sCompileInfo* info);
BOOL compile_generics_function(unsigned int node, sCompileInfo* info);
BOOL compile_inline_function(unsigned int node, sCompileInfo* info);
BOOL compile_lambda_call(unsigned int node, sCompileInfo* info);
BOOL compile_method_block(unsigned int node, sCompileInfo* info);

//////////////////////////////
/// node_loop ///
//////////////////////////////
void node_loop_init();
void node_loop_final();

BOOL add_label_to_table(char* name, LLVMBasicBlockRef block);
LLVMBasicBlockRef get_label_from_table(char* name);

unsigned int sNodeTree_create_conditional(unsigned int conditional, unsigned int value1, unsigned int value2, sParserInfo* info);
unsigned int sNodeTree_create_comma(unsigned int left_node, unsigned int right_node, sParserInfo* info);
unsigned int sNodeTree_create_return(unsigned int left, sParserInfo* info);
unsigned int sNodeTree_create_nodes(unsigned int* nodes, int num_nodes, sParserInfo* info);
BOOL is_function_name(char* name);
unsigned int sNodeTree_create_normal_block(MANAGED struct sNodeBlockStruct* node_block, sParserInfo* info);
unsigned int sNodeTree_switch_expression(unsigned int expression_node, int num_switch_expression, MANAGED unsigned int* switch_expression, sParserInfo* info);
unsigned int sNodeTree_create_break_expression(sParserInfo* info);
unsigned int sNodeTree_create_continue_expression(sParserInfo* info);
unsigned int sNodeTree_case_expression(unsigned int expression_node, BOOL last_case, BOOL case_after_return, sParserInfo* info);
unsigned int sNodeTree_label_expression(char* name, sParserInfo* info);
unsigned int sNodeTree_goto_expression(char* name, sParserInfo* info);
unsigned int sNodeTree_for_expression(unsigned int expression_node1, unsigned int expression_node2, unsigned int expression_node3, MANAGED struct sNodeBlockStruct* for_node_block, sParserInfo* info);
unsigned int sNodeTree_if_expression(unsigned int expression_node, MANAGED struct sNodeBlockStruct* if_node_block, unsigned int* elif_expression_nodes, MANAGED struct sNodeBlockStruct** elif_node_blocks, int elif_num, MANAGED struct sNodeBlockStruct* else_node_block, sParserInfo* info, char* sname, int sline);
unsigned int sNodeTree_while_expression(unsigned int expression_node, MANAGED struct sNodeBlockStruct* while_node_block, sParserInfo* info);
unsigned int sNodeTree_do_while_expression(unsigned int expression_node, MANAGED struct sNodeBlockStruct* while_node_block, sParserInfo* info);
unsigned int sNodeTree_create_defer(unsigned int expression_node, sParserInfo* info);
unsigned int sNodeTree_create_select(int num_pipes, char** pipes, struct sNodeBlockStruct** pipe_blocks, sParserInfo* info);
unsigned int sNodeTree_create_pselect(int num_pipes, char** pipes, struct sNodeBlockStruct** pipe_blocks, struct sNodeBlockStruct* default_block, sParserInfo* info);

BOOL compile_comma(unsigned int node, sCompileInfo* info);
BOOL compile_conditional(unsigned int node, sCompileInfo* info);
BOOL compile_goto_expression(unsigned int node, sCompileInfo* info);
BOOL compile_label_expression(unsigned int node, sCompileInfo* info);
BOOL compile_continue_expression(unsigned int node, sCompileInfo* info);
BOOL compile_break_expression(unsigned int node, sCompileInfo* info);
BOOL compile_switch_expression(unsigned int node, sCompileInfo* info);
BOOL compile_case_expression(unsigned int node, sCompileInfo* info);
BOOL compile_normal_block(unsigned int node, sCompileInfo* info);
BOOL compile_nodes(unsigned int node, sCompileInfo* info);
BOOL compile_if_expression(unsigned int node, sCompileInfo* info);
BOOL compile_while_expression(unsigned int node, sCompileInfo* info);
BOOL compile_do_while_expression(unsigned int node, sCompileInfo* info);
BOOL compile_defer(unsigned int node, sCompileInfo* info);
BOOL compile_and_and(unsigned int node, sCompileInfo* info);
BOOL compile_or_or(unsigned int node, sCompileInfo* info);
BOOL compile_for_expression(unsigned int node, sCompileInfo* info);
BOOL compile_return(unsigned int node, sCompileInfo* info);
BOOL compile_join(unsigned int node, sCompileInfo* info);
BOOL compile_select(unsigned int node, sCompileInfo* info);
BOOL compile_pselect(unsigned int node, sCompileInfo* info);

/////////////
/// macro.c
/////////////
void init_macro();
void finalize_macro();
void append_macro(char* name, char* body);
char* get_macro(char* name);
BOOL get_command_result(sBuf* command_result, char* macro_name, char* cmdline, char* params);
BOOL call_macro(unsigned * node, char* name, char* params, sParserInfo* info);

#endif

