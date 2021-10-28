#include "common.h"

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
    
    list<sNode*%>*% nodes = new list<sNode*%>.initialize();
    
    while(*info->p) {
        sNode* node = null;
        if(!expression(&node, &info)) {
            fprintf(stderr, "%s %d: unexpected character %c\n", fname, info->sline, *info->p);
            return false;
        }
        
        nodes.push_back(dummy_heap node);
    }
    
    foreach(it, nodes) {
        if(!compile(it, codes, &info)) {
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
        
        vm(codes).expect {
            exit(1);
        }
    }
    
    return 0;
}

