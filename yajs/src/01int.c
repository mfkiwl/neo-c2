#include "common.h"
#include <ctype.h>

void skip_spaces(sParserInfo* info)
{
    while(*info->p == ' ' || *info->p == '\t' || (*info->p == '\n' && info->sline++)) {
        info->p++;
    }
}

static sNode*% create_int_node(int value, sParserInfo* info)
{
    sNode*% result = new sNode;
    
    result.kind = kIntValue;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.intValue = value;
    
    return result;
}

void sNode_finalize(sNode* self) 
{
}

sNode*%? exp_node(sParserInfo* info)
{
    if(isdigit(*info->p)) {
        int n = 0;
        while(isdigit(*info->p)) {
            n = n * 10 + (*info->p - '0');
            info->p++;
        }
        skip_spaces(info);
        
        return create_int_node(n, info);
    }
    
    return null;
}

bool expression(sNode** node, sParserInfo* info) 
{
    *node = borrow exp_node(info);
    
    if(*node == null) {
        return false;
    }
    
    return true;
}

bool compile(sNode* node, buffer* codes, sParserInfo* info) 
{
    if(node.kind == kIntValue) {
puts("compile int value");
        codes.append_int(OP_INT_VALUE);
        codes.append_int(node.value.intValue);
    }
    
    return true;
}

