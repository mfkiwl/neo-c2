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

static sNode* create_index_node(string var_name, sNode* index_node, sNode* index_node2, sNode* index_node3, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kListIndexNode;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.indexValue.var_name = clone var_name;
    result.value.indexValue.index_node = index_node;
    result.value.indexValue.index_node2 = index_node2;
    result.value.indexValue.index_node3 = index_node3;
    result.value.indexValue.in_global_context = info->in_global_context;
    
    return result;
}


sNode*? index_node(string var_name, sParserInfo* info) version 13
{
    info->p++;
    skip_spaces_until_eol(info);
    
    sNode* index_node = null;
    sNode* index_node2 = null;
    sNode* index_node3 = null;
    
    if(*info->p == ':') {
        info->p++;
        skip_spaces_until_eol(info);
        
        if(*info->p == ':') {
            info->p++;
            skip_spaces_until_eol(info);
            
            if(*info->p == ']') {
                index_node = create_int_node(0, info);
                index_node2 = create_int_node(-1, info);
                index_node3 = null;
            }
            else {
                index_node = create_int_node(0, info);
                index_node2 = create_int_node(-1, info);
                
                if(!expression(&index_node3, info)) {
                    return false;
                }
            }
        }
        else if(*info->p == ']') {
            index_node = create_int_node(0, info);
            index_node2 = create_int_node(-1, info);
            index_node3 = null;
        }
        else {
            index_node = create_int_node(0, info);
            
            if(!expression(&index_node2, info)) {
                return false;
            }
            
            if(*info->p == ':') {
                info->p++;
                skip_spaces_until_eol(info);
                
                if(!expression(&index_node3, info)) {
                    return false;
                }
            }
            else {
                index_node3 = null;
            }
        }
    }
    else {
        if(!expression(&index_node, info)) {
            return false;
        }
        
        if(*info->p == ':') {
            info->p++;
            skip_spaces_until_eol(info);
            
            if(*info->p == ']') {
                index_node2 = create_int_node(-1, info);
                index_node3 = null;
            }
            else if(*info->p == ':') {
                info->p++;
                skip_spaces_until_eol(info);
                
                index_node2 = create_int_node(-1, info);
                
                if(*info->p == ']') {
                    index_node3 = null;
                }
                else {
                    if(!expression(&index_node3, info)) {
                        return false;
                    }
                }
            }
            else {
                if(!expression(&index_node2, info)) {
                    return false;
                }
                
                if(*info->p == ':') {
                    info->p++;
                    skip_spaces_until_eol(info);
                    
                    if(*info->p == ']') {
                        index_node3 = null;
                    }
                    else {
                        if(!expression(&index_node3, info)) {
                            return false;
                        }
                    }
                }
            }
        }
        else if(*info->p == ']') {
            index_node2 = null;
            index_node3 = null;
        }
    }
    
    if(*info->p == ']'){
        info->p++;
        skip_spaces_until_eol(info);
    }
    else {
        fprintf(stderr, "%s %d: require ] for list index", info->fname, info->sline);
        return null;
    }

    return create_index_node(var_name, index_node, index_node2, index_node3, info);
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
            
            result = create_list_node(elements, info);
            
            if(*info->p == '.') {
                result = method_node(result, info);
            }
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
        
        info.stack_num -= len;
        
        codes.append_int(len);
        
        info->stack_num++;
    }
    else if(node.kind == kListIndexNode) {
        string var_name = node.value.indexValue.var_name;
        sNode* index_node = node.value.indexValue.index_node;
        sNode* index_node2 = node.value.indexValue.index_node2;
        sNode* index_node3 = node.value.indexValue.index_node3;
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
        
        if(index_node2) {
            if(!compile(index_node2, codes, info)) {
                return false;
            }
        }
        
        if(index_node3) {
            if(!compile(index_node3, codes, info)) {
                return false;
            }
        }
        
        codes.append_int(OP_LIST_INDEX);
        
        int slice = index_node2 ?1:0;
        codes.append_int(slice);
        
        int slice2 = index_node3 ? 1:0;
        codes.append_int(slice2);
        
        if(slice && slice2) {
            info->stack_num-=4;
            info->stack_num++;
        }
        else if(slice || slice2) {
            info->stack_num-=3;
            info->stack_num++;
        }
        else {
            info->stack_num-=2;
            info->stack_num++;
        }
    }
    
    return true;
}

