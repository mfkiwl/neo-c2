#include "common.h"

bool vm(buffer* codes)
{
    ZVALUE stack[ZSTACK_MAX];
    int stack_num = 0;
    
    int* p = (int*)codes.buf;
    int* head = (int*)codes.buf;
    
    while((p - head) < (codes.length() / sizeof(int))) {
        switch(*p) {
            case OP_POP:
                p++;
                int n = *p;
                p++;
                
                stack_num -= n;
                
printf("pop %d\n", n);
                break;
                
            case OP_INT_VALUE:
                p++;
                int value = *p;
                p++;
                
                stack[stack_num].kind = kIntValue;
                stack[stack_num].value.intValue = value;
                stack_num++;
                
printf("int value %d\n", value);
                break;
                
            case OP_ADD: {
                p++;
                
                int lvalue = stack[stack_num-1].intValue;
                int rvalue = stack[stack_num-2].intValue;
                
                stack_num-=2;
                
                stack[stack_num].kind = kIntValue;
                stack[stack_num].value.intValue = lvalue + rvalue;
                stack_num++;
                
printf("add value %d\n", lvalue + rvalue);
                }
                break;
                
            case OP_SUB: {
                p++;
                
                int lvalue = stack[stack_num-1].intValue;
                int rvalue = stack[stack_num-2].intValue;
                
                stack_num-=2;
                
                stack[stack_num].kind = kIntValue;
                stack[stack_num].intValue = lvalue - rvalue;
                stack_num++;
                
printf("sub value %d\n", lvalue - rvalue);
                }
                break;
                 
            case OP_STRING_VALUE: {
                p++;
                
                char* str = (char*)p;
                
printf("string value (%s)\n", str);

                int len = strlen(str);
                len = (len + 3) & ~3;
                len /= sizeof(int);
                
                p += len;
                
                stack[stack_num].kind = kStringValue;
                stack[stack_num].stringValue = str;
                stack_num++;
                }
                break;
                
                
        }
        
printf("stack_num %d\n", stack_num);
        
        if(stack_num < 0 || stack_num >= ZSTACK_MAX) {
            fprintf(stderr, "invalid stack num\n");
            return false;
        }
    }
    
    return true;
}

/*
            case OP_PRINT: 
                p++;
                
                switch(stack[stack_num-1].kind) {
                    case kStringValue: 
                        puts(stack[stack_num-1].value.stringValue);
                        break;
                        
                    case kIntValue: 
                        printf("%d\n", stack[stack_num-1].value.intValue);
                        break;
                }
                stack_num--;
               
                break;
*/
