#include <neo-c2.h>

struct sNode;

struct sNode
{
    enum { kIntValue, kOpAdd, kOpSub, kStringValue, kPrint, kLoadVar, kStoreVar, kFun, kFunCall, kTrue, kFalse, kIf } kind;
    
    char* fname;
    int sline;
    
    union {
        int intValue;
        
        struct {
            sNode*% left
            sNode*% right
            sNode*% middle
        } opValue;
        
        string stringValue;
        
        struct {
            string name;
            sNode*% right;
            bool in_global_context;
        } storeVarValue;
        
        struct {
            string name;
            bool in_global_context;
        } loadVarValue;
        
        struct {
            string name;
            buffer*% codes;
            vector<string>*% param_names;
        } funValue;
        
        struct {
            string name;
            vector<sNode*%>*% params;
        } funCallValue;
        
        struct {
            sNode*% if_exp;
            buffer*% if_codes;
            vector<sNode*%>*% elif_exps;
            vector<buffer*%>*% elif_blocks;
            buffer*? else_block;
        } ifValue;
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
};

struct ZVALUE 
{
    enum { kIntValue, kBoolValue, kLongValue, kStringValue, kObjValue, kNullValue } kind;
    
    union {
        int intValue;
        bool boolValue;
        long longValue;
        char* stringValue;
        void* objValue;
    } value;
};

struct sVar
{
    string name;
    ZVALUE value;
};

void sVar_finalize();

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

/// main.c ///
void skip_spaces(sParserInfo* info);
void skip_spaces_until_eol(sParserInfo* info);
buffer*% parse_block(sParserInfo* info);

/// vm.c ///
void initialize_modules() version 1;
void finalize_modules() version 1;

bool vm(buffer* codes, map<char*, ZVALUE>* params);

/// 01int.c ///
bool expression(sNode** node, sParserInfo* info) version 1;
bool compile(sNode* node, buffer* codes, sParserInfo* info) version 1;

void sNode_finalize(sNode* self) version 1;
sNode*%? exp_node(sParserInfo* info) version 1;

/// 02add.c ///
bool expression(sNode** node, sParserInfo* info) version 2;
bool compile(sNode* node, buffer* codes, sParserInfo* info) version 2;

void sNode_finalize(sNode* self);

/// 03str.c ///
bool compile(sNode* node, buffer* codes, sParserInfo* info) version 3;

void sNode_finalize(sNode* self) version 3;
sNode*%? exp_node(sParserInfo* info) version 3;

/// 04print.c ///
bool wordcmp(char* p, char* word2);

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 4;

void sNode_finalize(sNode* self) version 4;
sNode*%? exp_node(sParserInfo* info) version 4;

/// 05var.c ///
void sNode_finalize(sNode* self) version 5;
sNode*%? exp_node(sParserInfo* info) version 5;
sNode*%? fun_node(string fun_name, sParserInfo* info) version 5;   // implemented after layer
sNode*%? def_node(sParserInfo* info) version 5;   // implemented after layer

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 5;

/// 06fun.c ///
void initialize_modules() version 6;
void finalize_modules() version 6;

void sNode_finalize(sNode* self) version 6;
sNode*%? fun_node(string fun_name, sParserInfo* info) version 6;
sNode*%? def_node(sParserInfo* info) version 6;

bool function_call(char* fun_name, ZVALUE* stack, int stack_num);

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 6;

/// 07bool.c ///
void sNode_finalize(sNode* self) version 7;

sNode*%? exp_node(sParserInfo* info) version 7;

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 7;

/// 08if.c ///
void sNode_finalize(sNode* self) version 8;

sNode*%? exp_node(sParserInfo* info) version 8;

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 8;
