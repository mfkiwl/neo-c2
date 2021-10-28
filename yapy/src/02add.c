#include "common.h"
#include <ctype.h>

static sNode*% create_add_node(sNode* left, sNode* right, sParserInfo* info)
{
    sNode*% result = new sNode;
    
    result.kind = kOpAdd;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.opValue.left = left;
    result.value.opValue.right = right;
    
    return result;
}

static sNode* create_sub_node(sNode* left, sNode* right, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kOpSub;
    
    result.fname = string(info->fname);
    result.sline = info->sline;
    result.value.opValue.left = left;
    result.value.opValue.right = right;
    
    return result;
}

static sNode* op_add_node(sParserInfo* info)
{
    sNode* result = exp_node(info);
    
    while(*info->p == '+' || *info->p == '-') {
        if(*info->p == '+') {
            info->p++;
            skip_spaces(info);
            
            sNode* right = op_add_node(info);
            
            if(right == null) {
                return null;
            }
            
            result = create_add_node(result, right, info);
        }
        else if(*info->p == '-') {
            info->p++;
            skip_spaces(info);
            
            sNode* right = op_add_node(info);
            
            if(right == null) {
                return null;
            }
            
            result = create_sub_node(result, right, info);
        }
    }
    
    return result;
}

bool expression(sNode** node, sParserInfo* info)
{
    *node = op_add_node(info);
    
    if(*node == null) {
        return false;
    }
    
    return true;
}

bool compile(sNode* node, buffer* codes, sParserInfo* info)
{
    inherit(node, codes, info);
    
    if(node.kind == kOpAdd) {
puts("compile add value");
        sNode* left = node.opValue.left
        
        if(!compile(left, codes, info)) {
            return false;
        }
        
        sNode* right = node.opValue.right;
        
        if(!compile(right, codes, info)) {
            return false;
        }
        
        codes.append_int(OP_ADD);
    }
    else if(node.kind == kOpSub) {
puts("compile sub value");
        sNode* left = node.opValue.left
        
        if(!compile(left, codes, info)) {
            return false;
        }
        
        sNode* right = node.opValue.right;
        
        if(!compile(right, codes, info)) {
            return false;
        }
        
        codes.append_int(OP_SUB);
    }
    
    return true;
}

