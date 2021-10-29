#include <neo-c2.h>

struct sNode;

struct sNode
{
    enum { kIntValue, kOpAdd, kOpSub, kStringValue } kind;
    
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
    } value;
};

struct sParserInfo
{
    char* p;
    int sline;
    char* fname;
};

union ZVALUE 
{
    int intValue;
    bool boolValue;
    long longValue;
    void* objValue;
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

/// vm.c ///
bool vm(buffer* codes);

/// 01int.c ///
bool expression(sNode** node, sParserInfo* info);
bool compile(sNode* node, buffer* codes, sParserInfo* info);

void sNode_finalize(sNode* self);
sNode*%? exp_node(sParserInfo* info);

void skip_spaces(sParserInfo* info);

/// 02add.c ///
override bool expression(sNode** node, sParserInfo* info);
override bool compile(sNode* node, buffer* codes, sParserInfo* info);

override void sNode_finalize(sNode* self);

/// 03str.c ///
override bool compile(sNode* node, buffer* codes, sParserInfo* info);

override void sNode_finalize(sNode* self);
override sNode*%? exp_node(sParserInfo* info);

