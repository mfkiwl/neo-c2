#include "common.h"

void show_zvalue(ZVALUE value)
{
    switch(value.kind) {
        case kIntValue:
            printf("int value %d\n", value.value.intValue);
            break;
            
        case kStringValue:
            printf("string value %s\n", value.value.stringValue);
            break;
    }
}

bool vm(buffer* codes)
{
    ZVALUE stack[ZSTACK_MAX];
    int stack_num = 0;
    
    int* p = (int*)codes.buf;
    int* head = (int*)codes.buf;
    
    map<char*, ZVALUE>*% vtable = new map<char*, ZVALUE>.initialize();
    
    while((p - head) < (codes.length() / sizeof(int))) {
        switch(*p) {
            case OP_POP:
                p++;
                int n = *p;
                p++;
                
                stack_num -= n;
                
                break;
                
            case OP_INT_VALUE:
                p++;
                int value = *p;
                p++;
                
                stack[stack_num].kind = kIntValue;
                stack[stack_num].value.intValue = value;
                stack_num++;
                
                break;
                
            case OP_ADD: {
                p++;
                
                int lvalue = stack[stack_num-1].intValue;
                int rvalue = stack[stack_num-2].intValue;
                
                stack_num-=2;
                
                stack[stack_num].kind = kIntValue;
                stack[stack_num].value.intValue = lvalue + rvalue;
                stack_num++;
                
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
                }
                break;
                 
            case OP_STRING_VALUE: {
                p++;
                
                char* str = (char*)p;
                
                int len = strlen(str);
                len = (len + 3) & ~3;
                len /= sizeof(int);
                
                p += len;
                
                stack[stack_num].kind = kStringValue;
                stack[stack_num].stringValue = str;
                stack_num++;
                }
                break;
                
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
                break;
                
            case OP_LOAD: {
                p++;
                
                char* var_name = (char*)p;
                
                int len = strlen(var_name);
                len = (len + 3) & ~3;
                len /= sizeof(int);
                
                p += len;
                
                bool in_global_context = (bool)*p;
                p++;
                
                if(in_global_context) {
                    stack[stack_num] = gGlobalVar.at(var_name, gNullValue);
                    stack_num++;
                }
                else {
                    stack[stack_num] = vtable.at(var_name, gNullValue);
                    stack_num++;
                }
                
                if(stack[stack_num-1].kind == kNullValue) {
                    fprintf(stderr, "var not found(%s)\n", var_name);
                }
                }
                break;
                
            case OP_STORE: {
                p++;
                
                char* var_name = (char*)p;
                
                int len = strlen(var_name);
                len = (len + 3) & ~3;
                len /= sizeof(int);
                
                p += len;
                
                bool in_global_context = (bool)*p;
                p++;
                
                if(in_global_context) {
                    ZVALUE right = stack[stack_num-1];
                    gGlobalVar.insert(var_name, right);
                }
                else {
                    ZVALUE right = stack[stack_num-1];
                    vtable.insert(var_name, right);
                }
                }
                break;
        }
        
        if(stack_num < 0 || stack_num >= ZSTACK_MAX) {
            fprintf(stderr, "invalid stack num\n");
            return false;
        }
    }
    
    return true;
}

/*
*/
