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
if echo $ARG | sed -e 's/-gc/NEOC_GC/' | grep NEOC_GC 1> /dev/null 2> /dev/null
then
    cat $PREFIX/include/neo-c2-gc.h | cpp -I . -U__GNUC__
else
    cat $PREFIX/include/neo-c2-no-gc.h | cpp -I . -U__GNUC__
fi
```
# 2 "src/common.h" 2


# 3 "src/common.h"
struct sNode;

struct sNode
{
    enum { kIntValue, kOpAdd, kOpSub } kind;

    char* fname;
    int sline;

    union {
        int intValue;
        string stringValue;

        struct {
            sNode* left
            sNode* right
            sNode* middle
        } opValue;
    } value;
};

struct sParserInfo
{
    char* p;
    int sline;
    char* fname;
};

union ZVALUE {
    int intValue;
    bool boolValue;
    long longValue;
    void* objValue;
};
# 45 "src/common.h"
bool vm(buffer* codes);


bool expression(sNode** node, sParserInfo* info);
bool compile(sNode* node, buffer* codes, sParserInfo* info);

void skip_spaces(sParserInfo* info);

void sNode_finalize();

sNode*%? exp_node(sParserInfo* info);


override bool expression(sNode** node, sParserInfo* info);
override bool compile(sNode* node, buffer* codes, sParserInfo* info);

override void sNode_finalize();
# 2 "src/main.c" 2

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

    
# 44 "src/main.c" 3
   for(auto _obj = nomove (
# 44 "src/main.c"
   nodes
# 44 "src/main.c" 3
   ), auto 
# 44 "src/main.c"
   it 
# 44 "src/main.c" 3
   = _obj.begin(); !_obj.end(); 
# 44 "src/main.c"
   it 
# 44 "src/main.c" 3
   = _obj.next()) 
# 44 "src/main.c"
                      {
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
