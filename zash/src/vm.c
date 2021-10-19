#include "common.h"

bool vm(buffer* codes)
{
    ZVALUE stack[ZSTACK_MAX];
    int stack_num = 0;
    
    int* p = (int*)codes.buf;
    int* head = (int*)codes.buf;
    
    while((p - head) < (codes.length() / sizeof(int))) {
        switch(*p) {
            case OP_INT_VALUE:
                p++;
                int value = *p;
                p++;
                
                stack[stack_num].intValue = value;
                stack_num++;
                
                printf("int value %d\n", value);
                break;
                
            case OP_ADD: {
                p++;
                
                int lvalue = stack[stack_num-1].intValue;
                int rvalue = stack[stack_num-2].intValue;
                
                stack_num-=2;
                
                stack[stack_num].intValue = lvalue + rvalue;
                stack_num++;
                
                printf("add value %d\n", lvalue + rvalue);
                }
                break;
                
            case OP_SUB: {
                p++;
                
                int lvalue = stack[stack_num-1].intValue;
                int rvalue = stack[stack_num-2].intValue;
                
                stack_num-=2;
                
                stack[stack_num].intValue = lvalue - rvalue;
                stack_num++;
                
                printf("sub value %d\n", lvalue - rvalue);
                }
                break;
        }
    }
    
    return true;
}

