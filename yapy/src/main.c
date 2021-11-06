#include "common.h"

map<char*, ZVALUE>* gGlobalVar;
ZVALUE gNullValue;

bool parse(char* fname, buffer* codes)
{
    FILE* f = fopen(fname, "r");
    
    if(f == null) {
        fprintf(stderr, "file %s is not found\n", fname);
        return false;
    }
    
    buffer*% source = new buffer.initialize();
    
    char line[4096];

    while(fgets(line, 4096, f) != null)
    {
        line[strlen(line)-1] = '\0';
        source.append_str(line);
    }

    fclose(f);
    
    sParserInfo info;
    
    string source2 = source.to_string();
    
    info.p = source2;
    info.fname = fname;
    info.sline = 1;
    info.stack_num = 0;
    info.in_global_context = true;
    
    list<sNode*%>*% nodes = new list<sNode*%>.initialize();
    
    while(*info->p) {
        sNode* node = null;
        if(!expression(&node, &info)) {
            fprintf(stderr, "%s %d: unexpected character (%c)\n", fname, info->sline, *info->p);
            return false;
        }
        
        nodes.push_back(dummy_heap node);
    }
    
    foreach(it, nodes) {
        if(!compile(it, codes, &info)) {
            return false;
        }
        
        if(info->stack_num >= 0) {
            codes.append_int(OP_POP);
            codes.append_int(info->stack_num);
            info->stack_num = 0;
        }
        else {
            fprintf(stderr, "%s %d: invalid stack num\n", fname, info->sline);
            return false;
        }
    }
    
    return true;
}

int main(int argc, char** argv)
{
    char* fname = null;
    
    for(int i=0; i<argc; i++) {
        if(argv[i][0] == '-') {
        }
        else {
            fname = argv[i];
        }
    }
    
    if(fname == null) {
    }
    else {
        buffer*% codes = new buffer.initialize();
        
        parse(fname, codes).expect {
            exit(1);
        }
        
        gGlobalVar = borrow new map<char*, ZVALUE>.initialize();
        gNullValue.kind = kNullValue;
        gNullValue.objValue = null;
        
        vm(codes).expect {
            exit(1);
        }
        
        delete gGlobalVar;
    }
    
    return 0;
}

