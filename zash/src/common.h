#include <neo-c2.h>

struct sNode
{
    enum { kIntValue, kStringValue } kind;
    
    char* fname;
    int sline;
    
    union {
        int intValue;
        string stringValue;
    } value;
};

#define OP_INT_VALUE 1

bool parse(char* fname, list<sNode*>* nodes, buffer* codes);
bool compile(sNode* node, buffer* codes);
bool run(int* p);

void skip_spaces(char** p, int* sline);
