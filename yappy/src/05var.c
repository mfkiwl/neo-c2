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

sNode*? index_node(string var_name, sParserInfo* info) version 5   // implemented after layer
{
    return null;
}

sNode*? def_node(sParserInfo* info) version 5   // implemented after layer
{
    return null;
}

sNode*? class_node(sParserInfo* info) version 5   // implemented after layer
{
    return null;
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

sPyType* parse_type(sParserInfo* info)
{
    char* p = info->p;
    int sline = info->sline;
    
    sPyType* type_ = null;
    
    if(*info->p == ':' || (*info->p == '-' && *(info->p+1) == '>')) {
        if(*info->p == ':') {
            info->p++;
            skip_spaces_until_eol(info);
        }
        else {
            info->p+=2;
            skip_spaces_until_eol(info);
        }
        
        if(*info->p == '\n') {
            info->p = p;
            info->sline = sline;
            return null;
        }
        
        buffer* buf = new buffer.initialize();
        while(xisalnum(*info->p) || *info->p == '_') {
            buf.append_char(*info->p);
            info->p++;
        }
        skip_spaces_until_eol(info);
        
        type_ = get_type(buf.to_string());
    }
    
    return type_;
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
            
            parse_type(info);
            
            if(strcmp(buf.to_string(), "def") == 0) {
                return def_node(info);
            }
            else if(strcmp(buf.to_string(), "class") == 0) {
                return class_node(info);
            }
            else if(*info->p == '=' && *(info->p+1) != '=') {
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
                result = fun_node(buf.to_string(), info)
                
                if(*info->p == '.') {
                    result = method_node(result, info);
                }
                
                return result;
            }
            else if(*info->p == '[') {
                result = index_node(buf.to_string(), info)
                
                if(*info->p == '.') {
                    result = method_node(result, info);
                }
                
                return result;
            }
            else {
                result = create_load_var(buf.to_string(), info);
                
                if(*info->p == '.') {
                    result = method_node(result, info);
                }
                
                return result;
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
        codes.append_int(len);
        
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
        codes.append_int(len);
        
        codes.append_str(name);
        codes.alignment();
        
        codes.append_int(node.value.storeVarValue.in_global_context);
    }
    
    return true;
}

