#include "common.h"

static sNode* create_load_var(char* str, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kLoadVar;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.loadVarValue.name = string(str);
    result.value.loadVarValue.in_global_context = info->in_global_context;
    
    return result;
}

static sNode* create_store_var(char* str, sNode* right, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kStoreVar;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.storeVarValue.name = string(str);
    result.value.storeVarValue.in_global_context = info->in_global_context;
    result.value.storeVarValue.right = right;
    
    return result;
}

sNode*? fun_node(string fun_name, sParserInfo* info) version 5   // implemented after layer
{
    return null;
}

sNode*? def_node(sParserInfo* info) version 5   // implemented after layer
{
    return null;
}

sNode*? exp_node(sParserInfo* info) version 5
{
    sNode* result = inherit(info);
    
    if(result == null) {
        if(xisalpha(*info->p) || *info->p == '_') {
            buffer* buf = new buffer.initialize();
            
            while(xisalnum(*info->p) || *info->p == '_') {
                buf.append_char(*info->p);
                info->p++;
            }
            skip_spaces_until_eol(info);
            
            if(strcmp(buf.to_string(), "def") == 0) {
                return def_node(info);
            }
            else if(*info->p == '=') {
                info->p++;
                skip_spaces_until_eol(info);
                
                sNode* right;
                if(!expression(&right, info)) {
                    fprintf(stderr, "%s %d: require right value\n", info->fname, info->sline);
                    return null;
                }
                
                return create_store_var(buf.to_string(), right, info);
            }
            else if(*info->p == '(') {
                return fun_node(buf.to_string(), info)
            }
            else {
                return create_load_var(buf.to_string(), info);
            }
        }
    }
    
    return result;
}

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 5
{
    inherit(node, codes, info);
    
    if(node.kind == kLoadVar) {
        codes.append_int(OP_LOAD);
        
        char* name = node.value.loadVarValue.name;
        
        int len = strlen(name);
        int offset = (len + 3) & ~3;
        offset /= sizeof(int);
        
        codes.append_int(offset);
        
        codes.append_str(name);
        codes.alignment();
        
        codes.append_int(node.value.loadVarValue.in_global_context);
        
        info->stack_num++;
    }
    else if(node.kind == kStoreVar) {
        sNode* right = node.value.storeVarValue.right;
        
        if(!compile(right, codes, info)) {
            return false;
        }
        
        codes.append_int(OP_STORE);
        
        char* name = node.value.storeVarValue.name;
        
        int len = strlen(name);
        int offset = (len + 3) & ~3;
        offset /= sizeof(int);
        
        codes.append_int(offset);
        
        codes.append_str(name);
        codes.alignment();
        
        codes.append_int(node.value.storeVarValue.in_global_context);
    }
    
    return true;
}

