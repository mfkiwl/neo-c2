#include "common.h"

static sNode*% create_load_var(char* str, sParserInfo* info)
{
    sNode*% result = new sNode;
    
    result.kind = kLoadVar;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.loadVarValue.name = string(str);
    result.value.loadVarValue.in_global_context = info->in_global_context;
    
    return result;
}

static sNode*% create_store_var(char* str, sNode*% right, sParserInfo* info)
{
    sNode*% result = new sNode;
    
    result.kind = kStoreVar;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.storeVarValue.name = string(str);
    result.value.storeVarValue.in_global_context = info->in_global_context;
    result.value.storeVarValue.right = right;
    
    return result;
}

void sNode_finalize(sNode* self) version 5
{
    inherit(self);

    if(self.kind == kLoadVar) {
        delete self.value.storeVarValue.name;
    }
    else if(self.kind == kStoreVar) {
        delete self.value.storeVarValue.name;
        delete self.value.storeVarValue.right;
    }
}

sNode*%? fun_node(string fun_name, sParserInfo* info) version 5   // implemented after layer
{
}

sNode*%? def_node(sParserInfo* info) version 5   // implemented after layer
{
}

sNode*%? exp_node(sParserInfo* info) version 5
{
    sNode* result = borrow inherit(info);
    
    if(result == null) {
        if(xisalpha(*info->p) || *info->p == '_') {
            buffer*% buf = new buffer.initialize();
            
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
                
                return create_store_var(buf.to_string(), dummy_heap right, info);
            }
            else if(*info->p == '(') {
                return fun_node(buf.to_string(), info)
            }
            else {
                return create_load_var(buf.to_string(), info);
            }
        }
    }
    
    return dummy_heap result;
}

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 5
{
    inherit(node, codes, info);
    
    if(node.kind == kLoadVar) {
        codes.append_int(OP_LOAD);
        
        codes.append_str(node.value.loadVarValue.name);
        codes.alignment();
        
        codes.append_int(node.value.loadVarValue.in_global_context);
        
        info->stack_num++;
    }
    else if(node.kind == kStoreVar) {
        sNode* right = borrow node.value.storeVarValue.right;
        
        if(!compile(right, codes, info)) {
            return false;
        }
        
        codes.append_int(OP_STORE);
        
        codes.append_str(node.value.storeVarValue.name);
        codes.alignment();
        
        codes.append_int(node.value.storeVarValue.in_global_context);
    }
    
    return true;
}

