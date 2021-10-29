# 1 "src/vm.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "src/vm.c"
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
    enum { kIntValue, kOpAdd, kOpSub, kStringValue } kind;

    char* fname;
    int sline;

    union {
        int intValue;

        struct {
            sNode*% left
            sNode*% right
            sNode*% middle
        } opValue;

        string stringValue;
    } value;
};

struct sParserInfo
{
    char* p;
    int sline;
    char* fname;
};

union ZVALUE
{
    int intValue;
    bool boolValue;
    long longValue;
    void* objValue;
};

struct sVar
{
    string name;
    ZVALUE value;
};

void sVar_finalize();

struct sFunction
{
    string name;
    list<sVar*%>*% vars;
};

void sFunction_finalize();
# 64 "src/common.h"
bool vm(buffer* codes);


bool expression(sNode** node, sParserInfo* info);
bool compile(sNode* node, buffer* codes, sParserInfo* info);

void sNode_finalize(sNode* self);
sNode*%? exp_node(sParserInfo* info);

void skip_spaces(sParserInfo* info);


override bool expression(sNode** node, sParserInfo* info);
override bool compile(sNode* node, buffer* codes, sParserInfo* info);

override void sNode_finalize(sNode* self);


override bool compile(sNode* node, buffer* codes, sParserInfo* info);

override void sNode_finalize(sNode* self);
override sNode*%? exp_node(sParserInfo* info);
# 2 "src/vm.c" 2

bool vm(buffer* codes)
{
    ZVALUE stack[1024];
    int stack_num = 0;

    int* p = (int*)codes.buf;
    int* head = (int*)codes.buf;

    while((p - head) < (codes.length() / sizeof(int))) {
        switch(*p) {
            case 1:
                p++;
                int value = *p;
                p++;

                stack[stack_num].intValue = value;
                stack_num++;

printf("int value %d\n", value);
                break;

            case 2: {
                p++;

                int lvalue = stack[stack_num-1].intValue;
                int rvalue = stack[stack_num-2].intValue;

                stack_num-=2;

                stack[stack_num].intValue = lvalue + rvalue;
                stack_num++;

printf("add value %d\n", lvalue + rvalue);
                }
                break;

            case 3: {
                p++;

                int lvalue = stack[stack_num-1].intValue;
                int rvalue = stack[stack_num-2].intValue;

                stack_num-=2;

                stack[stack_num].intValue = lvalue - rvalue;
                stack_num++;

printf("sub value %d\n", lvalue - rvalue);
                }
                break;

            case 4: {
                p++;

                char* str = (char*)p;

printf("string value (%s)\n", str);

                int len = strlen(str);
                len = (len + 3) & ~3;

                p += len
                }
                break;
        }

        if(stack_num < 0 || stack_num >= 1024) {
            fprintf(stderr, "invalid stack num\n");
            return false;
        }
    }

    return true;
}
