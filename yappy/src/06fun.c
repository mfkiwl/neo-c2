#include "common.h"

static sNode* create_fun(char* fun_name, buffer* codes, vector<string>* param_names, vector<sPyType*>* param_types, sPyType* result_type, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kFun;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.funValue.name = string(fun_name);
    result.value.funValue.codes = codes;
    result.value.funValue.param_names = param_names;
    result.value.funValue.param_types = param_types;
    result.value.funValue.result_type = result_type;
    
    return result;
}

static sNode* create_class(char* class_name, buffer* codes, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kClass;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.funValue.name = string(class_name);
    result.value.funValue.codes = codes;
    result.value.funValue.param_names = null;
    result.value.funValue.param_types = null;
    result.value.funValue.result_type = null;
    
    return result;
}

static sNode* create_fun_call(char* fun_name, vector<sNode*>* params, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kFunCall;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.funCallValue.name = string(fun_name);
    result.value.funCallValue.params = params;
    
    return result;
}

sNode*? def_node(sParserInfo* info) version 6
{
    buffer* buf = new buffer.initialize();
    
    while(xisalnum(*info->p) || *info->p == '_') {
        buf.append_char(*info->p);
        info->p++;
    }
    skip_spaces_until_eol(info);
    
    string fun_name = buf.to_string();
    
    if(*info->p != '(') {
        fprintf(stderr, "%s %d: require (\n", info->fname, info->sline);
        exit(2);
    }
    
    info->p++;
    skip_spaces_until_eol(info);
    
    vector<string>* param_names = new vector<string>.initialize();
    vector<sPyType*>* param_types = new vector<sPyType*>.initialize();
    
    buffer* buf2 = new buffer.initialize();
    
    sPyType* result_type = null;
    
    while(true) {
        if(*info->p == ')') {
            info->p++;
            skip_spaces_until_eol(info);
            
            result_type = parse_type(info);
            
            if(*info->p == ':') {
                info->p++;
                skip_spaces_until_eol(info);
                break;
            }
            else {
                fprintf(stderr, "%s %d: require :\n", info->fname, info->sline);
                exit(2);
            }
        }
        else if(xisalpha(*info->p)) {
            while(xisalnum(*info->p) || *info->p == '_') {
                buf2.append_char(*info->p);
                info->p++;
            }
            
            sPyType* type_ = parse_type(info);
            param_types.push_back(type_);
            
            param_names.push_back(buf2.to_string());
            
            buf2 = new buffer.initialize();
            
            if(*info->p == ',') {
                info->p++;
                skip_spaces_until_eol(info);
            }
        }
        else {
            fprintf(stderr, "%s %d: require parametor name or )\n", info->fname, info->sline);
            exit(2);
        }
    }
    
    buffer* codes = compile_block(info);
    
    return create_fun(fun_name, codes, param_names, param_types, result_type, info);
}

sNode*? fun_node(string fun_name, sParserInfo* info) version 6
{
    info->p++;
    skip_spaces_until_eol(info);
    
    vector<sNode*>* params = new vector<sNode*>.initialize();
    
    while(*info->p) {
        if(*info->p == ')') {
            info->p++;
            skip_spaces_until_eol(info);
            break;
        }
        
        sNode* node = null;
        if(!expression(&node, info)) {
            fprintf(stderr, "%s %d: unexpected character (%c)\n", info->fname, info->sline, *info->p);
            exit(1);
        }
        
        if(*info->p == ',') {
            info->p++;
            skip_spaces_until_eol(info);
        }
        
        params.push_back(node);
    }
    
    return create_fun_call(fun_name, params, info);
}

sNode*? class_node(sParserInfo* info) version 6
{
    buffer* buf = new buffer.initialize();
    
    while(xisalnum(*info->p) || *info->p == '_') {
        buf.append_char(*info->p);
        info->p++;
    }
    skip_spaces_until_eol(info);
    
    if(*info->p == ':') {
        info->p++;
        skip_spaces_until_eol(info);
    }
    
    string class_name = buf.to_string();
    
    buffer* codes = compile_block(info);
    
    return create_class(class_name, codes, info);
}

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 6
{
    inherit(node, codes, info);
    
    if(node.kind == kFun) {
        codes.append_int(OP_FUN);
        
        char* name = node.value.funValue.name;
        
        int len = strlen(name);
        int offset = (len + 3) & ~3;
        offset /= sizeof(int);
        
        codes.append_int(offset);
        codes.append_int(len);
        
        codes.append_str(name);
        codes.alignment();
        
        buffer* codes2 = node.value.funValue.codes;
        
        codes.append_int(codes2.len);
        
        codes.append(codes2.buf, codes2.len);
        
        vector<string>* param_names = node.value.funValue.param_names;
        
        codes.append_int(param_names.length());
        
        foreach(it, param_names) {
            char* name = it;
            
            int len = strlen(name);
            int offset = (len + 3) & ~3;
            offset /= sizeof(int);
            
            codes.append_int(offset);
            codes.append_int(len);
            
            codes.append_str(name);
            codes.alignment();
        }
    }
    else if(node.kind == kClass) {
        codes.append_int(OP_CLASS);
        
        char* name = node.value.funValue.name;
        
        int len = strlen(name);
        int offset = (len + 3) & ~3;
        offset /= sizeof(int);
        
        codes.append_int(offset);
        codes.append_int(len);
        
        codes.append_str(name);
        codes.alignment();
        
        buffer* codes2 = node.value.funValue.codes;
        
        codes.append_int(codes2.len);
        
        codes.append(codes2.buf, codes2.len);
    }
    else if(node.kind == kFunCall) {
        int stack_num = info.stack_num;
        
        vector<sNode*>* params = node.value.funCallValue.params;
        
        foreach(it, params) {
            if(!compile(it, codes, info)) {
                return false;
            }
        }
        info.stack_num = stack_num;
        
        codes.append_int(OP_FUNCALL);
        
        char* name = node.value.funCallValue.name;
        int num_params = params.length();
        
        int len = strlen(name);
        int offset = (len + 3) & ~3;
        offset /= sizeof(int);
        
        codes.append_int(offset);
        codes.append_int(len);
        
        codes.append_str(name);
        codes.alignment();
        
        codes.append_int(num_params);
        
        stack_num++;
    }
    
    return true;
}

