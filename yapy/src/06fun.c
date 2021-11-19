#include "common.h"

struct sFunction
{
    string name;
    buffer*% codes;
    vector<string>*% param_names;
};

sFunction*% sFunction_initialize(sFunction*% self, char* name, buffer* codes, vector<string>* param_names)
{
    self.name = clone name;
    self.codes = clone codes;
    self.param_names = clone param_names;
    
    return self;
}

void sFunction_finalize(sFunction* self)
{
    delete self.name;
    delete self.codes;
    delete self.param_names;
}

static map<string, sFunction*%>* gFuncs;

void initialize_modules() version 6
{
    inherit();
    
    gFuncs = borrow new map<string, sFunction*%>.initialize();
}

void finalize_modules() version 6
{
    delete gFuncs;
    
    inherit();
}

static sNode*% create_fun(char* fun_name, buffer*% codes, vector<string>*% param_names, sParserInfo* info)
{
    sNode*% result = new sNode;
    
    result.kind = kFun;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.funValue.name = string(fun_name);
    result.value.funValue.codes = codes;
    result.value.funValue.param_names = param_names;
    
    return result;
}

static sNode*% create_fun_call(char* fun_name, vector<sNode*%>*% params, sParserInfo* info)
{
    sNode*% result = new sNode;
    
    result.kind = kFunCall;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.funCallValue.name = string(fun_name);
    result.value.funCallValue.params = params;
    
    return result;
}

void sNode_finalize(sNode* self) version 6
{
    inherit(self);

    if(self.kind == kFun) {
        delete self.value.funValue.name;
        delete self.value.funValue.codes;
        delete self.value.funValue.param_names;
    }
    else if(self.kind == kFunCall) {
        delete self.value.funCallValue.name;
        delete self.value.funCallValue.params;
    }
}

sNode*%? def_node(sParserInfo* info) version 6
{
    buffer*% buf = new buffer.initialize();
    
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
    
    vector<string>*% param_names = new vector<string>.initialize();
    
    buffer*% buf2 = new buffer.initialize();
    
    while(true) {
        if(*info->p == ')') {
            info->p++;
            skip_spaces_until_eol(info);
            
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
            }
            
            param_names.push_back(buf2.to_string());
            
            delete buf2;
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
    
    buffer*% codes = parse_block(info);
    
    return create_fun(fun_name, codes, param_names, info);
}

sNode*%? fun_node(string fun_name, sParserInfo* info) version 6
{
    info->p++;
    skip_spaces_until_eol(info);
    
    vector<sNode*%>*% params = new vector<sNode*%>.initialize();
    
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
        
        params.push_back(dummy_heap node);
    }
    
    return create_fun_call(fun_name, params, info);
}

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 6
{
    inherit(node, codes, info);
    
    if(node.kind == kFun) {
        char* name = node.value.funValue.name;
        buffer* codes = node.value.funValue.codes;
        vector<string>* param_names = node.value.funValue.param_names;
        
        sFunction*% fun = new sFunction.initialize(name, codes, param_names);
        
        gFuncs.insert(name, fun);
    }
    else if(node.kind == kFunCall) {
        codes.append_int(OP_FUNCALL);
        
        char* name = node.value.funCallValue.name;
        
        int len = strlen(name);
        int offset = (len + 3) & ~3;
        offset /= sizeof(int);
        
        codes.append_int(offset);
        
        codes.append_str(name);
        codes.alignment();
        
        vector<sNode*%>* params = node.value.funCallValue.params;
        
        foreach(it, params) {
            if(!compile(it, codes, info)) {
                return false;
            }
        }
    }
    
    return true;
}

bool function_call(char* fun_name, ZVALUE* stack, int stack_num)
{
    sFunction* fun = gFuncs.at(fun_name, null);
    
    if(fun == null) {
        fprintf(stderr, "%s %d: function not found(%s)\n", fun_name);
        return false;
    }
    
    buffer* codes = fun->codes;
    vector<string>* param_names = fun->param_names;
    
    map<char*, ZVALUE>*% params = new map<char*, ZVALUE>.initialize();
    
    int i = 0;
    foreach(it, param_names) {
        ZVALUE value = stack[stack_num-param_names.length()+i];
        params.insert(it, value);
        
        i++;
    }
    
    if(!vm(codes, params)) {
        return false;
    }
    
    return true;
}
