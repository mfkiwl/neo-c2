#include <neo-c2.h>

struct sNode;

struct sNode
{
    enum { kIntValue, kOpAdd, kOpSub, kStringValue, kPrint, kLoadVar, kStoreVar } kind;
    
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
    } value;
};

struct sParserInfo
{
    char* p;
    int sline;
    char* fname;
    
    int stack_num;
    
    bool in_global_context;
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

struct sFunction
{
    string name;
    list<sVar*%>*% vars;
};

void sFunction_finalize();

#define ZSTACK_MAX 1024

#define OP_INT_VALUE 1
#define OP_ADD 2
#define OP_SUB 3
#define OP_STRING_VALUE 4
#define OP_PRINT 5
#define OP_POP 6
#define OP_STORE 7
#define OP_LOAD 8

extern map<char*, ZVALUE>* gGlobalVar;
extern ZVALUE gNullValue;

/// vm.c ///
bool vm(buffer* codes);

/// 01int.c ///
bool expression(sNode** node, sParserInfo* info) version 1;
bool compile(sNode* node, buffer* codes, sParserInfo* info) version 1;

void sNode_finalize(sNode* self) version 1;
sNode*%? exp_node(sParserInfo* info) version 1;

void skip_spaces(sParserInfo* info);

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

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 5;
