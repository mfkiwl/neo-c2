#include "common.h"
#include <ctype.h>

static sNode* create_add_node(sNode* left, sNode* right, char* fname, int sline)
{
    sNode* result = new sNode;
    
    result.kind = kOpAdd;
    
    result.fname = string(fname);
    result.sline = sline;
    result.value.opValue.left = left;
    result.value.opValue.right = right;
    
    return result;
}

static sNode* create_sub_node(sNode* left, sNode* right, char* fname, int sline)
{
    sNode* result = new sNode;
    
    result.kind = kOpSub;
    
    result.fname = string(fname);
    result.sline = sline;
    result.value.opValue.left = left;
    result.value.opValue.right = right;
    
    return result;
}

static sNode* op_add_node(char** p, char* fname, int* sline)
{
    sNode* result = exp_node(p, fname, sline);
    
    while(**p == '+' || **p == '-') {
        if(**p == '+') {
            (*p)++;
            skip_spaces(p, sline);
            
            sNode* right = op_add_node(p, fname, sline);
            
            if(right == null) {
                return null;
            }
            
            result = create_add_node(result, right, fname, sline);
puts("add node");
        }
        else if(**p == '-') {
            (*p)++;
            skip_spaces(p, sline);
            
            sNode* right = op_add_node(p, fname, sline);
            
            if(right == null) {
                return null;
            }
            
            result = create_sub_node(result, right, fname, sline);
puts("sub node");
        }
    }
    
    return result;
}

bool expression(char** p, sNode** node, char* fname, int* sline)
{
    *node = op_add_node(p, fname, sline);
    
    if(*node == null) {
        return false;
    }
    
    return true;
}

bool compile(sNode* node, buffer* codes)
{
    inherit(node, codes);
    
    if(node.kind == kOpAdd) {
puts("compile add value");
        sNode* left = node.opValue.left
        
        if(!compile(left, codes)) {
            return false;
        }
        
        sNode* right = node.opValue.right;
        
        if(!compile(right, codes)) {
            return false;
        }
        
        codes.append_int(OP_ADD);
    }
    else if(node.kind == kOpSub) {
puts("compile sub value");
        sNode* left = node.opValue.left
        
        if(!compile(left, codes)) {
            return false;
        }
        
        sNode* right = node.opValue.right;
        
        if(!compile(right, codes)) {
            return false;
        }
        
        codes.append_int(OP_SUB);
    }
    
    return true;
}

