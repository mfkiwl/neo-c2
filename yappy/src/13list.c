#include "common.h"
#include <ctype.h>

static sNode* create_list_node(list<sNode*>* elements, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kListValueNode;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.listValue = clone elements;
    
    return result;
}

static sNode* create_index_node(string var_name, sNode* index_node, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kListIndexNode;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.indexValue.var_name = clone var_name;
    result.value.indexValue.index_node = index_node;
    result.value.indexValue.in_global_context = info->in_global_context;
    
    return result;
}


sNode*? index_node(string var_name, sParserInfo* info) version 13
{
    info->p++;
    skip_spaces_until_eol(info);
    
    sNode* index_node = null;
    if(!expression(&index_node, info)) {
        return false;
    }
    
    if(*info->p == ']'){
        info->p++;
        skip_spaces_until_eol(info);
    }
    else {
        fprintf(stderr, "%s %d: require ] for list index", info->fname, info->sline);
        return null;
    }

    return create_index_node(var_name, index_node, info);
}

sNode*? exp_node(sParserInfo* info) version 13
{
    sNode* result = inherit(info);
    
    if(result == null) {
        if(*info->p == '[') {
            info->p++;
            
            list<sNode*>* elements = new list<sNode*>.initialize();
            
            while(true) {
                if(*info->p == '\0') {
                    fprintf(stderr, "%s %d: the source end", info->fname, info->sline);
                    return null;
                }
                else if(*info->p == ']') {
                    info->p++;
                    skip_spaces_until_eol(info);
                    break;
                }
                else {
                    sNode* node = null;
                    if(!expression(&node, info)) {
                        return null;
                    }
                    
                    if(*info->p == ',') {
                        info->p++;
                        skip_spaces_until_eol(info);
                    }
                    
                    elements.push_back(node);
                }
            }
            
            return create_list_node(elements, info);
        }
    }
    
    return result;
}

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 13
{
    inherit(node, codes, info);
    
    if(node.kind == kListValueNode) {
        list<sNode*>* elements = node.value.listValue;
        
        foreach(it, elements) {
            if(!compile(it, codes, info)) {
                return false;
            }
        }
        
        codes.append_int(OP_LIST_VALUE);
        
        int len = elements.length();
        
        codes.append_int(len);
        
        info->stack_num+=len;
        info->stack_num++;
    }
    else if(node.kind == kListIndexNode) {
        string var_name = node.value.indexValue.var_name;
        sNode* index_node = node.value.indexValue.index_node;
        bool in_global_context = node.value.indexValue.in_global_context;
        
        codes.append_int(OP_LOAD);
        
        int len = strlen(var_name);
        int offset = (len + 3) & ~3;
        offset /= sizeof(int);
        
        codes.append_int(offset);
        codes.append_int(len);
        
        codes.append_str(var_name);
        codes.alignment();
        
        codes.append_int(in_global_context);
        
        info->stack_num++;
        
        if(!compile(index_node, codes, info)) {
            return  false;
        }
        
        codes.append_int(OP_LIST_INDEX);
        
        info->stack_num-=2;
        info->stack_num++;
    }
    
    return true;
}

