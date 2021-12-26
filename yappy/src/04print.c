#include "common.h"
#include <ctype.h>

static sNode* create_print_node(sNode* exp, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kPrint;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.opValue.left = exp;
    
    return result;
}

static sNode* create_len_node(sNode* exp, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kLen;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.opValue.left = exp;
    
    return result;
}

static sNode* create_exit_node(sNode* exp, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kExit;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.opValue.left = exp;
    
    return result;
}

static sNode* create_return_node(sNode* exp, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kReturn;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.opValue.left = exp;
    
    return result;
}


static bool emb_funcmp(char* p, char* word2)
{
    bool result = strstr(p, word2) == p;
    
    char c = p[strlen(word2)];
    
    if(result && (c == ' ' || c == '\t' || c == '\0' || c == '(' || c == '\n')) {
        return true;
    }
    
    return false;
}

sNode*? exp_node(sParserInfo* info) version 4
{
    sNode* result = inherit(info);
    
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
            
            result = create_print_node(node, info);
        }
        else if(emb_funcmp(info->p, "len")) {
            info->p += strlen("len");
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
            
            result = create_len_node(node, info);
        }
        else if(emb_funcmp(info->p, "exit")) {
            info->p += strlen("exit");
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
            
            result = create_exit_node(node, info);
        }
        else if(emb_funcmp(info->p, "return")) {
            info->p += strlen("return");
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
            
            result = create_return_node(node, info);
        }
    }
    
    return result;
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
    else if(node.kind == kLen) {
        sNode* exp = node.opValue.left;
        
        if(!compile(exp, codes, info)) {
            return false;
        }
        
        codes.append_int(OP_LEN);
    }
    else if(node.kind == kExit) {
        sNode* exp = node.opValue.left;
        
        if(!compile(exp, codes, info)) {
            return false;
        }
        
        codes.append_int(OP_EXIT);
    }
    else if(node.kind == kReturn) {
        sNode* exp = node.opValue.left;
        
        if(!compile(exp, codes, info)) {
            return false;
        }
        
        codes.append_int(OP_RETURN);
    }
    
    return true;
}

