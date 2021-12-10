#include <neo-c2.h>

struct sNode;

struct sNode
{
    enum { kIntValueNode, kOpAdd, kOpSub, kStringValueNode, kPrint, kExit, kReturn, kLoadVar, kStoreVar, kFun, kFunCall, kTrue, kFalse, kIf, kWhile, kContinue, kBreak, kOpEq, kOpNotEq, kOpDiv, kOpMult } kind;
    
    char* fname;
    int sline;
    
    union {
        int intValue;
        
        struct {
            sNode* left
            sNode* right
            sNode* middle
        } opValue;
        
        string stringValue;
        
        struct {
            string name;
            sNode* right;
            bool in_global_context;
        } storeVarValue;
        
        struct {
            string name;
            bool in_global_context;
        } loadVarValue;
        
        struct {
            string name;
            buffer* codes;
            vector<string>* param_names;
        } funValue;
        
        struct {
            string name;
            vector<sNode*>* params;
        } funCallValue;
        
        struct {
            sNode* if_exp;
            buffer* if_codes;
            vector<sNode*>* elif_exps;
            vector<buffer*>* elif_blocks;
            buffer*? else_block;
        } ifValue;
        
        struct {
            sNode* while_exp;
            list<sNode*>* while_nodes;
            list<sNode*>* else_nodes;
        } whileValue;
    } value;
};

struct sParserInfo
{
    char* p;
    int sline;
    char* fname;
    
    int stack_num;
    
    bool in_global_context;
    int space_num;
    
    int loop_head;
    vector<int>* breaks;
};

struct ZVALUE 
{
    enum { kIntValue, kBoolValue, kLongValue, kStringValue, kObjValue, kNullValue, kExceptionValue } kind;
    
    union {
        int intValue;
        bool boolValue;
        long longValue;
        char* stringValue;
        void* objValue;
        enum { kExceptionVarNotFound, kExceptionDivisionByZero, kExceptionNameError, kExceptionTypeError } expValue;
    } value;
};

inline void print_exception(ZVALUE exception)
{
    if(exception.kind != kExceptionValue) {
        fprintf(stderr, "not exception\n");
        exit(1);
    }
    switch(exception.value.expValue) {
        case kExceptionDivisionByZero:
            fprintf(stderr, "DivisionByZerro Excetpion\n");
            break;
            
        case kExceptionNameError:
            fprintf(stderr, "NameError Excetpion\n");
            break;
            
        case kExceptionVarNotFound:
            fprintf(stderr, "VarNotFound Excetpion\n");
            break;
            
        case kExceptionTypeError:
            fprintf(stderr, "Type Error Excetpion\n");
            break;
    }
}

struct sVar
{
    string name;
    ZVALUE value;
};

#define ZSTACK_MAX 1024

#define OP_INT_VALUE 1
#define OP_ADD 2
#define OP_SUB 3
#define OP_STRING_VALUE 4
#define OP_PRINT 5
#define OP_POP 6
#define OP_STORE 7
#define OP_LOAD 8
#define OP_FUNCALL 9
#define OP_BOOL_VALUE 10
#define OP_IF 11
#define OP_GOTO 12
#define OP_EQ 13
#define OP_NOT_EQ 14
#define OP_MULT 15
#define OP_DIV 16
#define OP_EXIT 17
#define OP_RETURN 18

/// main.c ///
void skip_spaces(sParserInfo* info);
void skip_spaces_until_eol(sParserInfo* info);
list<sNode*>* parse_block(sParserInfo* info);
buffer* compile_nodes(list<sNode*>* nodes, sParserInfo* info);
buffer* compile_block(sParserInfo* info);

/// vm.c ///
void initialize_modules() version 1;
void finalize_modules() version 1;

struct sVMInfo 
{
    ZVALUE exception;
    ZVALUE return_value;
};

bool vm(buffer* codes, map<string, ZVALUE>* params, sVMInfo* info);

/// 01int.c ///
bool expression(sNode** node, sParserInfo* info) version 1;
bool compile(sNode* node, buffer* codes, sParserInfo* info) version 1;

sNode*? exp_node(sParserInfo* info) version 1;

/// 02add.c ///
sNode* op_add_node(sParserInfo* info);

bool expression(sNode** node, sParserInfo* info) version 2;
bool compile(sNode* node, buffer* codes, sParserInfo* info) version 2;

/// 03str.c ///
bool compile(sNode* node, buffer* codes, sParserInfo* info) version 3;

sNode*? exp_node(sParserInfo* info) version 3;

/// 04print.c ///
bool wordcmp(char* p, char* word2);

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 4;

sNode*? exp_node(sParserInfo* info) version 4;

/// 05var.c ///
sNode*? exp_node(sParserInfo* info) version 5;
sNode*? fun_node(string fun_name, sParserInfo* info) version 5;   // implemented after layer
sNode*? def_node(sParserInfo* info) version 5;   // implemented after layer

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 5;

/// 06fun.c ///
void initialize_modules() version 6;

sNode*? fun_node(string fun_name, sParserInfo* info) version 6;
sNode*? def_node(sParserInfo* info) version 6;

bool function_call(char* fun_name, vector<ZVALUE>* param_values, sVMInfo* info);

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 6;

/// 07bool.c ///
sNode*? exp_node(sParserInfo* info) version 7;

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 7;

/// 08if.c ///
sNode*? exp_node(sParserInfo* info) version 8;

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 8;

/// 09comment.c ///
bool expression(sNode** node, sParserInfo* info) version 99;

/// 10while.c ///
sNode*? exp_node(sParserInfo* info) version 10;
bool compile(sNode* node, buffer* codes, sParserInfo* info) version 10;

/// 11op.c ///
bool expression(sNode** node, sParserInfo* info) version 11;
bool compile(sNode* node, buffer* codes, sParserInfo* info) version 11;
