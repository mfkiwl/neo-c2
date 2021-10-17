#include "common.h"

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
        
        int* p = (int*)codes.buf;
        
        run(p).expect {
            exit(1);
        }
    }
    
    return 0;
}

