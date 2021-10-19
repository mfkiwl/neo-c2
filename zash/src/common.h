#include <neo-c2.h>

struct sNode;

struct sNode
{
    enum { kIntValue, kOpAdd, kOpSub } kind;
    
    char* fname;
    int sline;
    
    union {
        int intValue;
        string stringValue;
        
        struct {
            sNode* left
            sNode* right
            sNode* middle
        } opValue;
    } value;
};

struct sParserInfo
{
    char* p;
    int sline;
    char* fname;
};

union ZVALUE {
    int intValue;
    bool boolValue;
    long longValue;
    void* objValue;
};

#define ZSTACK_MAX 1024

#define OP_INT_VALUE 1
#define OP_ADD 2
#define OP_SUB 3

/// vm.c ///
bool vm(buffer* codes);

/// 01int.c ///
bool expression(sNode** node, sParserInfo* info);
bool compile(sNode* node, buffer* codes, sParserInfo* info);

void skip_spaces(sParserInfo* info);

sNode* exp_node(sParserInfo* info);

/// 02op.c ///
override bool expression(sNode** node, sParserInfo* info);
override bool compile(sNode* node, buffer* codes, sParserInfo* info);

