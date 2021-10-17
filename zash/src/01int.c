#include "common.h"
#include <ctype.h>

void skip_spaces(char** p, int* sline)
{
    while(**p == ' ' || **p == '\t' || (**p == '\n' && (*sline)++)) {
        (*p)++;
    }
}

sNode* create_int_node(int value, char* fname, int sline)
{
    sNode* result = new sNode;
    
    result.kind = kIntValue;
    
    result.fname = string(fname);
    result.sline = sline;
    result.value.intValue = value;
    
    return result;
}

sNode* exp_node(char** p, char* fname, int* sline)
{
    if(isdigit(**p)) {
        int n = 0;
        while(isdigit(**p)) {
            n = n * 10 + (**p - '0');
            (*p)++;
        }
        skip_spaces(p, sline);
        
        return create_int_node(n, fname, sline);
    }
    
    return null;
}

bool expression(char** p, sNode** node, char* fname, int* sline)
{
    *node = exp_node(p, fname, sline);
    
    if(*node == null) {
        return false;
    }
    
    return true;
}

bool parse(char* fname, list<sNode*>* nodes, buffer* codes)
{
    FILE* f = fopen(fname, "r");
    
    if(f == null) {
        fprintf(stderr, "file %s is not found\n", fname);
        return false;
    }
    
    buffer* source = new buffer.initialize();
    
    char line[4096];

    while(fgets(line, 4096, f) != null)
    {
        line[strlen(line)-1] = '\0';
        source.append_str(line);
    }

    fclose(f);
    
    char* p = source.to_string();
    int sline = 1;
    
    while(*p) {
        sNode* node = null;
        if(!expression(&p, &node, fname, &sline)) {
            fprintf(stderr, "%s %d: unexpected character %c\n", fname, sline, *p);
            return false;
        }
        
        nodes.push_back(node);
    }
    
    return true;
}

bool compile(sNode* node, buffer* codes)
{
    if(node.kind == kIntValue) {
        codes.append_int(OP_INT_VALUE);
        codes.append_int(node.value.intValue);
    }
    
    return true;
}

bool run(int* p)
{
    if(*p == OP_INT_VALUE) {
        p++;
        int value = *p;
        p++;
        
        printf("int value %d\n", value);
    }
    
    return true;
}
