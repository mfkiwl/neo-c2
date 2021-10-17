# 1 "src/main.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "src/main.c"
# 1 "src/common.h" 1
# 1 "/usr/local/include/neo-c2.h" 1 3


# 2 "/usr/local/include/neo-c2.h" 3
```
if echo $ARG | sed -e 's/-no-gc/NEOC_NO_GC/' | grep NEOC_NO_GC 1> /dev/null 2> /dev/null
then
    cat $PREFIX/include/neo-c2-no-gc.h | cpp -I . -U__GNUC__
else
    cat $PREFIX/include/neo-c2-gc.h | cpp -I . -U__GNUC__
fi
```
# 2 "src/common.h" 2


# 3 "src/common.h"
struct sNode
{
    enum { kIntValue, kStringValue } kind;

    char* fname;
    int sline;

    union {
        int intValue;
        string stringValue;
    } value;
};



bool parse(char* fname, list<sNode*>* nodes, buffer* codes);
bool compile(sNode* node, buffer* codes);
bool run(int* p);

void skip_spaces(char** p, int* sline);
# 2 "src/main.c" 2

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

        
# 26 "src/main.c" 3
       for(auto _obj = nomove (
# 26 "src/main.c"
       nodes
# 26 "src/main.c" 3
       ), auto 
# 26 "src/main.c"
       it 
# 26 "src/main.c" 3
       = _obj.begin(); !_obj.end(); 
# 26 "src/main.c"
       it 
# 26 "src/main.c" 3
       = _obj.next()) 
# 26 "src/main.c"
                          {
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
