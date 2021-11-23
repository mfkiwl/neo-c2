#include "common.h"

static map<char*, ZVALUE>* gGlobalVar;
static ZVALUE gNullValue;

void initialize_modules() version 1
{
    gGlobalVar = new map<char*, ZVALUE>.initialize();
    gNullValue.kind = kNullValue;
    gNullValue.objValue = null;
}

void finalize_modules() version 1
{
}

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

void print_op(int op)
{
    switch(op) {
        case OP_POP:
            puts("OP_POP");
            break;
                
        case OP_INT_VALUE: 
            puts("OP_INT_VALUE");
            break;
                
        case OP_ADD: 
            puts("OP_ADD");
            break;
                
        case OP_SUB:
            puts("OP_SUB");
            break;
                 
        case OP_STRING_VALUE:
            puts("OP_STRING_VALUE");
            break;
                
        case OP_PRINT: 
            puts("OP_PRINT");
            break;
                
        case OP_LOAD: 
            puts("OP_LOAD");
            break;
                
        case OP_STORE: 
            puts("OP_STORE");
            break;
                
        case OP_FUNCALL:
            puts("OP_FUNCALL");
            break;
                
        case OP_BOOL_VALUE: 
            puts("OP_BOOL_VALUE");
            break;
                
        case OP_GOTO: 
            puts("OP_GOTO");
            break;
                
        case OP_IF: 
            puts("OP_IF");
            break;
                
        default:
            printf("invalid op code %d\n", op);
            break;
    }
}

bool vm(buffer* codes, map<string, ZVALUE>* params)
{
    ZVALUE stack[ZSTACK_MAX];
    int stack_num = 0;
    
    int* p = (int*)codes.buf;
    int* head = (int*)codes.buf;
    
    map<string, ZVALUE>* vtable = new map<string, ZVALUE>.initialize();
    
    if(params) {
        foreach(it, params) {
            char* key = it;
            
            ZVALUE item = params.at(string(it), gNullValue);
            
            vtable.insert(key, item);
        }
    }
    
    while((p - head) < (codes.length() / sizeof(int))) {
//print_op(*p);
        switch(*p) {
            case OP_POP: {
                p++;
                int n = *p;
                p++;
                
                stack_num -= n;
                }
                break;
                
            case OP_INT_VALUE: {
                p++;
                int value = *p;
                p++;
                
                stack[stack_num].kind = kIntValue;
                stack[stack_num].value.intValue = value;
                stack_num++;
                }
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
                
                int offset = *p;
                p++;
                
                char* str = (char*)p;
                
                p += offset;
                
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
                        
                    case kBoolValue:
                       if(stack[stack_num-1].value.boolValue) {
                           puts("true");
                       }
                       else {
                           puts("false");
                       }
                       break;
                }
                break;
                
            case OP_LOAD: {
                p++;
                
                int offset = *p;
                p++;
                
                char* var_name = (char*)p;
                
                p += offset;
                
                bool in_global_context = (bool)*p;
                p++;
                
                if(in_global_context) {
                    stack[stack_num] = gGlobalVar.at(var_name, gNullValue);
                    stack_num++;
                }
                else {
                    stack[stack_num] = vtable.at(var_name, gNullValue);
                    
                    if(stack[stack_num-1].kind == kNullValue) {
                        fprintf(stderr, "var not found(%s)\n", var_name);
                    }
                    
                    stack[stack_num] = gGlobalVar.at(var_name, gNullValue);
                    stack_num++;
                }
                
                if(stack[stack_num-1].kind == kNullValue) {
                    fprintf(stderr, "var not found(%s)\n", var_name);
                }
                }
                break;
                
            case OP_STORE: {
                p++;
                
                int offset = *p;
                p++;
                
                char* var_name = (char*)p;
                
                p += offset;
                
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
                
            case OP_FUNCALL:
                p++;
                
                int offset = *p;
                p++;
                
                char* fun_name = (char*)p;
                
                p += offset;
                
                if(!function_call(fun_name, stack, stack_num)) {
                    return false;
                }
                break;
                
            case OP_BOOL_VALUE: {
                p++;
                int value = *p;
                p++;
                
                stack[stack_num].kind = kBoolValue;
                stack[stack_num].value.boolValue = value;
                stack_num++;
                }
                break;
                
            case OP_GOTO: {
                p++;
                
                int value = *p;
                p++;
                
                p = (int*)((char*)head + value);
                }
                break;
                
            case OP_IF: {
                p++;
                
                int value = *p;
                p++;
                
                bool exp = stack[stack_num-1].value.boolValue;
                stack_num--;
                
                if(!exp) {
                    p += value;
                }
                }
                break;
                
            default:
                printf("invalid op code %d\n", *p);
                exit(1);
        }
        
        if(stack_num < 0 || stack_num >= ZSTACK_MAX) {
            fprintf(stderr, "invalid stack num\n");
            return false;
        }
    }
    
    return true;
}

