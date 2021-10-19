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
bool expression(char** p, sNode** node, char* fname, int* sline);
bool compile(sNode* node, buffer* codes);

void skip_spaces(char** p, int* sline);

sNode* exp_node(char** p, char* fname, int* sline);

/// 02op.c ///
override bool expression(char** p, sNode** node, char* fname, int* sline);
override bool compile(sNode* node, buffer* codes);

