#include "common.h"
#include <ctype.h>

static sNode*% create_print_node(sNode* exp, sParserInfo* info)
{
    sNode*% result = new sNode;
    
    result.kind = kPrint;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.opValue.left = exp;
    
    return result;
}

void sNode_finalize(sNode* self) version 4
{
    inherit(self);
    
    if(self.kind == kPrint) {
        delete self.value.opValue.left;
    }
}

bool emb_funcmp(char* p, char* word2)
{
    bool result = strstr(p, word2) == p;
    
    char c = p[strlen(word2)];
    
    if(result && (c == ' ' || c == '\t' || c == '\0' || c == '(')) {
        return true;
    }
    
    return false;
}

sNode*%? exp_node(sParserInfo* info) version 4
{
    sNode* result = borrow inherit(info);
    
    if(result == null) {
        if(emb_funcmp(info->p, "print")) {
            info->p += strlen("print");
            skip_spaces_until_eol(info);
            
            if(*info->p == '(') {
                info->p++;
                skip_spaces_until_eol(info);
            }
            
            sNode* node = null;
            if(!expression(&node, info)) {
                return null;
            }
            
            if(*info->p == ')') {
                info->p++;
                skip_spaces_until_eol(info);
            }
            
            result = borrow create_print_node(node, info);
        }
    }
    
    return dummy_heap result;
}

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 4
{
    inherit(node, codes, info);
    
    if(node.kind == kPrint) {
        sNode* exp = node.opValue.left;
        
        if(!compile(exp, codes, info)) {
            return false;
        }
        
        codes.append_int(OP_PRINT);
    }
    
    return true;
}

