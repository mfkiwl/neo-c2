#include "common.h"

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

int main(int argc, char** argv)
{
    char* fname = null;
    
    for(int i=0; i<argc; i++) {
        if(argv[i][0] == '-') {
        }
        else {
            fname = string(argv[i]);
        }
    }
    
    if(fname == null) {
    }
    else {
        list<sNode*>* nodes = new list<sNode*>.initialize();
        
        buffer* codes = new buffer.initialize();
        
        parse(fname, nodes, codes).expect {
            exit(1);
        }
        
        foreach(it, nodes) {
            compile(it, codes).expect {
                exit(1);
            }
        }
        
        vm(codes).expect {
            exit(1);
        }
    }
    
    return 0;
}

