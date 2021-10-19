#include "common.h"
#include <ctype.h>

void skip_spaces(char** p, int* sline)
{
    while(**p == ' ' || **p == '\t' || (**p == '\n' && (*sline)++)) {
        (*p)++;
    }
}

static sNode* create_int_node(int value, char* fname, int sline)
{
    sNode* result = new sNode;
    
    result.kind = kIntValue;
    
    result.fname = string(fname);
    result.sline = sline;
    result.value.intValue = value;
    
puts("int_node");
    return result;
}

sNode* exp_node(char** p, char* fname, int* sline)
{
    if(isdigit(**p)) {
        int n = 0;
        while(isdigit(**p)) {
            n = n * 10 + (**p - '0');
            (*p)++;
        }
        skip_spaces(p, sline);
        
        return create_int_node(n, fname, sline);
    }
    
    return null;
}

bool expression(char** p, sNode** node, char* fname, int* sline) version 1
{
    *node = exp_node(p, fname, sline);
    
    if(*node == null) {
        return false;
    }
    
    return true;
}

bool compile(sNode* node, buffer* codes) version 1
{
    if(node.kind == kIntValue) {
puts("compile int value");
        codes.append_int(OP_INT_VALUE);
        codes.append_int(node.value.intValue);
    }
    
    return true;
}

