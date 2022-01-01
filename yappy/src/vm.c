#include "common.h"
#include <locale.h>

static ZVALUE gNullValue;

typedef bool (*fNativeFun)(map<string, ZVALUE>* params, sVMInfo* info);

struct sFunction
{
    string name;
    buffer* codes;
    fNativeFun* native_fun;
    vector<string>* param_names;
};

static sFunction* sFunction_initialize(sFunction* self, char* name, buffer* codes, vector<string>* param_names)
{
    self.name = string(name);
    if(codes) {
        self.codes = clone codes;
    }
    else {
        self.codes = null;
    }
    self.param_names = clone param_names;
    self.native_fun = null;
    
    return self;
}

struct sClass
{
    string name;
    buffer* codes;
    
    map<string, ZVALUE>* class_vars;
    map<string, sFunction*>* funcs;
};

static sClass* sClass_initialize(sClass* self, char* name, buffer* codes)
{
    self.name = clone name;
    self.codes = clone codes;
    
    self.class_vars = new map<string, ZVALUE>.initialize();
    self.funcs = new map<string, sFunction*>.initialize();
    
    return self;
};

struct sModule
{
    string name;
    map<string, sFunction*>* funcs;
    map<string, ZVALUE>* global_vars;
    map<string, sClass*>* classes;
};

sModule* sModule_initialize(sModule* self, char* module_name)
{
    self.name = string(module_name);
    
    self.funcs = new map<string, sFunction*>.initialize();
    self.global_vars = new map<string, ZVALUE>.initialize();
    self.classes = new map<string, sClass*>.initialize();
    
    return self;
}

static map<string, sModule*>* gModules;

struct sObject
{
    sClass* klass;
    sModule* module;
    map<string, ZVALUE>* fields;
};

sObject* sObject_initialize(sObject* self, sModule* module, sClass* klass)
{
    self.klass = klass;
    self.module = module;
    self.fields = new map<string, ZVALUE>.initialize();
    
    return self;
}

bool ZVALUE_equals(ZVALUE self, ZVALUE right)
{
    if(self.kind != right.kind) {
        return false;
    }
    
    switch(self.kind) {
        case kIntValue:
            if(self.intValue != right.intValue) {
                return false;
            }
            break;
            
        case kBoolValue:
            if(self.boolValue != right.boolValue) {
                return false;
            }
            break;
            
        case kLongValue:
            if(self.longValue != right.longValue) {
                return false;
            }
            break;
            
        case kStringValue:
            if(wcscmp(self.stringValue, right.stringValue) != 0) {
                return false;
            }
            break;
            
        case kObjValue: {
            sObject* left_obj = self.objValue;
            sObject* right_obj = right.objValue;
            
            if(left_obj.klass != right_obj.klass) {
                return false;
            }
            if(left_obj.module != right_obj.module) {
                return false;
            }
            
            if(left_obj.fields.length() != right_obj.fields.length()) {
                return false;
            }
            
            foreach(it, left_obj.fields) {
                ZVALUE item1 = left_obj.fields.at(it, gNullValue);
                ZVALUE item2 = right_obj.fields.at(it, gNullValue);
                
                if(!item1.equals(item2)) {
                    return false;
                }
            }
            }
            break;
            
        case kNullValue:
            return true;
            break;
            
        case kExceptionValue:
            if(self.expValue != right.expValue) {
                return false;
            }
            break;
            
        case kModuleValue:
            return false;
            break;
            
        case kClassValue:
            return false;
            break;
            
        case kListValue:
            if(!self.listValue.equals(right.listValue)) {
                return false;
            }
            break;
    }
    
    return true;
}


bool native_sys_exit(map<string, ZVALUE>* params, sVMInfo* info)
{
    ZVALUE rcode = params.at("rcode", gNullValue);
    
    exit(rcode.value.intValue);
    
    return true;
}

void initialize_modules() version 1
{
    setlocale(LC_ALL, "");
    
    gNullValue.kind = kNullValue;
    gNullValue.objValue = null;
    
    gModules = new map<string, sModule*>.initialize();
    
    sModule* sys_module = new sModule.initialize("sys");
    gModules.insert("sys", sys_module);
    
    vector<string>* param_names = new vector<string>.initialize();
    
    param_names.push_back(string("rcode"));
    
    sFunction* sys_exit = new sFunction.initialize("exit", null, param_names);
    
    sys_exit.native_fun = native_sys_exit;
    
    sys_module.funcs.insert("exit", sys_exit);
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
            printf("string value %ls\n", value.value.stringValue);
            break;
    }
}

void print_op(int op)
{
    switch(op) {
        case OP_POP:
            puts("OP_POP");
            break;
        case OP_STORE_FIELD:
            puts("OP_STORE_FIELD");
            break;
            
        case OP_EQ:
            puts("OP_EQ");
            break;
            
        case OP_ANDAND:
            puts("OP_ANDAND");
            break;
            
        case OP_OROR:
            puts("OP_OROR");
            break;
            
        case OP_CLASS:
            puts("OP_CLASS");
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
                
        case OP_LEN: 
            puts("OP_LEN");
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
            
        case OP_METHOD_CALL:
            puts("OP_METHOD_CALL");
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
            
        case OP_EXIT: 
            puts("OP_EXIT");
            break;
            
        case OP_RETURN: 
            puts("OP_RETURN");
            break;
            
        case OP_FUN: 
            puts("OP_FUN");
            break;
            
        case OP_LOAD_FIELD:
            puts("OP_LOAD_FIELD");
            break;
            
        case OP_LOAD_FIELD:
            puts("OP_STORE_FIELD");
            break;
            
        case OP_LIST_VALUE:
            puts("OP_LIST_VALUE");
            break;
            
        case OP_LIST_INDEX:
            puts("OP_LIST_INDEX");
            break;
                
        default:
            printf("invalid op code %d\n", op);
            break;
    }
}

bool function_call(sFunction* fun, vector<ZVALUE>* param_values, sVMInfo* info)
{
    if(fun.native_fun) {
        fNativeFun* fun2 = fun.native_fun;
        
        vector<string>* param_names = fun->param_names;
        
        map<string, ZVALUE>* params = new map<string, ZVALUE>.initialize();
        
        int i = 0;
        foreach(it, param_names) {
            ZVALUE null_value;
            memset(&null_value, 0, sizeof(ZVALUE));
            
            ZVALUE value = param_values.item(i, null_value);
            params.insert(string(it), value);
            
            i++;
        }
        
        if(!fun2(params, info)) {
            return false;
        }
    }
    else {
        buffer* codes = fun->codes;
        
        vector<string>* param_names = fun->param_names;
        
        map<string, ZVALUE>* params = new map<string, ZVALUE>.initialize();
        
        int i = 0;
        foreach(it, param_names) {
            ZVALUE null_value;
            memset(&null_value, 0, sizeof(ZVALUE));
            
            ZVALUE value = param_values.item(i, null_value);
            params.insert(string(it), value);
            
            i++;
        }
        
        if(!vm(codes, params, info)) {
            return false;
        }
    }
    
    return true;
}

bool class_call(sClass* klass, sVMInfo* info)
{
    buffer* codes = klass->codes;
    
    string class_name = info->class_name;
    info->class_name = string(klass.name);
    
    if(!vm(codes, null, info)) {
        return false;
    }
    
    info->class_name = class_name;
    
    return true;
}

void add_module(char* module_name)
{
    sModule* module = new sModule.initialize(module_name);
    
    gModules.insert(string(module_name), module);
}

void print_obj(ZVALUE obj, bool lf)
{
    switch(obj.kind) {
        case kStringValue: 
            printf("%s", obj.value.stringValue.to_string());
            if(lf) {
                puts("");
            }
            break;
            
        case kIntValue: 
            printf("%d", obj.value.intValue);
            if(lf) {
                puts("");
            }
            break;
            
        case kBoolValue:
           if(obj.value.boolValue) {
               printf("true");
               if(lf) {
                   puts("");
               }
           }
           else {
               printf("false");
               if(lf) {
                   puts("");
               }
           }
           break;
           
       case kObjValue: {
           sObject* object = obj.value.objValue;
           printf("%s.%s object at %p\n", object.module.name, object.klass.name, object);
           if(lf) {
               puts("");
           }
           }
           break;
           
       case kListValue: {
           list<ZVALUE>* li = obj.value.listValue;
           
           printf("[");
           for(int i= 0; i<li.length(); i++) {
               print_obj(li.item(i, gNullValue), false);
               if(i != li.length()-1) {
                   printf(",");
               }
           }
           printf("]");
           if(lf) {
               puts("");
           }
           }
           break;
    }
}

bool vm(buffer* codes, map<string, ZVALUE>* params, sVMInfo* info)
{
    ZVALUE stack[ZSTACK_MAX];
    int stack_num = 0;
    
    info->return_value = gNullValue;
    
    int* p = (int*)codes.buf;
    int* head = (int*)codes.buf;
    
    map<string, ZVALUE>* vtable = new map<string, ZVALUE>.initialize();
    
    if(params) {
        foreach(it, params) {
            char* key = it;
            
            ZVALUE item = params.at(string(it), gNullValue);
            
            if(item.kind == kNullValue) {
                info->exception.kind = kExceptionValue;
                info->exception.value.expValue = kExceptionVarNotFound;
                return false;
            }
            
            vtable.insert(string(key), item);
        }
    }
    
    while((p - head) < (codes.length() / sizeof(int))) {
//print_op(*p);
//printf("stack_num %d\n", stack_num);
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
                
                ZVALUE lvalue = stack[stack_num-2];
                ZVALUE rvalue = stack[stack_num-1];
                
                stack_num-=2;
                
                if(lvalue.kind != rvalue.kind) {
                    info->exception.kind = kExceptionValue;
                    info->exception.value.expValue = kExceptionTypeError;
                    return false;
                }
                
                switch(lvalue.kind) {
                    case kIntValue:
                        stack[stack_num].kind = kIntValue;
                        stack[stack_num].value.intValue = lvalue.intValue + rvalue.intValue;
                        stack_num++;
                        break;
                        
                    case kStringValue: {
                        buffer* buf = new buffer.initialize();
                        
                        buf.append_str(lvalue.value.stringValue.to_string());
                        buf.append_str(rvalue.value.stringValue.to_string());
                        
                        stack[stack_num].kind = kStringValue;
                        stack[stack_num].value.stringValue = buf.to_string().to_wstring();
                        stack_num++;
                        }
                        break;
                        
                    case kListValue: {
                        list<ZVALUE>* list_object = new list<ZVALUE>.initialize();
                        
                        list<ZVALUE>* li = lvalue.value.listValue;
                        list<ZVALUE>* li2 = rvalue.value.listValue;
                        
                        foreach(it, li) {
                            list_object.push_back(it);
                        }
                        foreach(it, li2) {
                            list_object.push_back(it);
                        }
                        
                        stack[stack_num].kind = kListValue;
                        stack[stack_num].value.listValue = list_object;
                        stack_num++;
                        }
                        break;
                        
                    default:
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                        break;
                }
                
                }
                break;
                
            case OP_SUB: {
                p++;
                
                ZVALUE lvalue = stack[stack_num-2];
                ZVALUE rvalue = stack[stack_num-1];
                
                stack_num-=2;
                
                if(lvalue.kind != kIntValue && rvalue.kind != kIntValue) {
                    info->exception.kind = kExceptionValue;
                    info->exception.value.expValue = kExceptionTypeError;
                    return false;
                }
                
                stack[stack_num].kind = kIntValue;
                stack[stack_num].value.intValue = lvalue.intValue - rvalue.intValue;
                stack_num++;
                
                }
                break;
                 
            case OP_STRING_VALUE: {
                p++;
                
                int len = *p;
                p++;
                
                wchar_t* str = (wchar_t*)p;
                
                wchar_t* str2 = new wchar_t[len+1];
                memcpy(str2, str, sizeof(wchar_t)*len);
                str2[len] = '\0'
                
                p += len;
                
                stack[stack_num].kind = kStringValue;
                stack[stack_num].stringValue = str2;
                stack_num++;
                }
                break;
                
            case OP_PRINT: 
                p++;
                
                print_obj(stack[stack_num-1], true);
                break;
                
            case OP_LEN: 
                p++;
                
                if(stack[stack_num-1].kind == kStringValue) {
                    wstring wstr = stack[stack_num-1].value.stringValue;
                    int len = wstr.length();
                    
                    stack_num--;
                    
                    stack[stack_num].kind = kIntValue;
                    stack[stack_num].intValue = len;
                    stack_num++;
                }
                else if(stack[stack_num-1].kind == kListValue) {
                    list<ZVALUE>* list_object = stack[stack_num-1].value.listValue;
                    
                    int len = list_object.length();
                    
                    stack_num--;
                    
                    stack[stack_num].kind = kIntValue;
                    stack[stack_num].intValue = len;
                    stack_num++;
                }
                else {
                    info->exception.kind = kExceptionValue;
                    info->exception.value.expValue = kExceptionTypeError;
                    return false;
                }
                break;
                
            case OP_LOAD: {
                p++;
                
                int offset = *p;
                p++;
                
                int len = *p;
                p++;
                
                char* var_name = (char*)p;
                
                char var_name2[len+1];
                memcpy(var_name2, var_name, len);
                var_name2[len] = '\0'
                
                p += offset;
                
                bool in_global_context = (bool)*p;
                p++;
                
                sModule* module = gModules.at(string(var_name2), null);
                
                sModule* module2 = gModules.at(string(info.module_name), null);
                
                sClass* klass = module2.classes.at(string(var_name2), null);
                
                if(module) {
                    stack[stack_num].kind = kModuleValue;
                    stack[stack_num].value.moduleValue = module;
                    stack_num++;
                }
                else if(klass) {
                    stack[stack_num].kind = kClassValue;
                    stack[stack_num].value.classValue = klass;
                    stack_num++;
                }
                else if(in_global_context) {
                    stack[stack_num] = module2.global_vars.at(string(var_name2), gNullValue);
                    
                    if(stack[stack_num].kind == kNullValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionVarNotFound;
                        return false;
                    }
                    
                    stack_num++;
                }
                else {
                    stack[stack_num] = vtable.at(var_name2, gNullValue);
                    stack_num++;
                    
                    if(stack[stack_num-1].kind == kNullValue) {
                        stack[stack_num] = module2.global_vars.at(string(var_name2), gNullValue);
                        stack_num++;
                        
                        if(stack[stack_num-1].kind == kNullValue) {
                            info->exception.kind = kExceptionValue;
                            info->exception.value.expValue = kExceptionVarNotFound;
                            return false;
                        }
                    }
                }
                
                }
                break;
                
            case OP_STORE: {
                p++;
                
                int offset = *p;
                p++;
                
                int len = *p;
                p++;
                
                char* var_name = (char*)p;
                
                char var_name2[len+1];
                memcpy(var_name2, var_name, len);
                var_name2[len] = '\0'
                
                p += offset;
                
                bool in_global_context = (bool)*p;
                p++;
                
                if(in_global_context) {
                    if(info.module_name) {
                        sModule* module = gModules.at(info.module_name, null);
                        
                        if(module == null) {
                            info->exception.kind = kExceptionValue;
                            info->exception.value.expValue = kExceptionVarNotFound;
                            return false;
                        }
                        
                        ZVALUE right = stack[stack_num-1];
                        module.global_vars.insert(string(var_name2), right);
                    }
                }
                else {
                    if(info.module_name) {
                        sModule* module = gModules.at(info.module_name, null);
                        
                        if(module == null) {
                            info->exception.kind = kExceptionValue;
                            info->exception.value.expValue = kExceptionVarNotFound;
                            return false;
                        }
                        
                        if(info.class_name) {
                            sClass* klass = module->classes.at(info.class_name, null);
                            
                            if(klass == null) {
                                info->exception.kind = kExceptionValue;
                                info->exception.value.expValue = kExceptionVarNotFound;
                                return false;
                            }
                            
                            ZVALUE right = stack[stack_num-1];
                            klass.class_vars.insert(string(var_name2), right);
                        }
                        else {
                            ZVALUE right = stack[stack_num-1];
                            vtable.insert(string(var_name2), right);
                        }
                    }
                }
                }
                break;
                
            case OP_FUN: {
                p++;
                
                int offset = *p;
                p++;
                
                int len = *p;
                p++;
                
                char* name = (char*)p;
                
                char name2[len+1];
                memcpy(name2, name, len);
                name2[len] = '\0'
                
                p += offset;
                
                int len_codes = *p;
                p++;
                
                char* codes = (char*)p;
                
                p += len_codes / sizeof(int);
                
                buffer* codes2 = new buffer.initialize();
                
                codes2.append(codes, len_codes);
                
                int len_param_names = *p;
                p++;
                
                vector<string>* param_names = new vector<string>.initialize();
                
                for(int i=0; i<len_param_names; i++) {
                    int offset = *p;
                    p++;
                    
                    int len = *p;
                    p++;
                    
                    char* name = (char*)p;
                    
                    char name2[len+1];
                    memcpy(name2, name, len);
                    name2[len] = '\0'
                    
                    p += offset;
                    
                    param_names.push_back(string(name2));
                }
                
                sFunction* fun = new sFunction.initialize(string(name2), codes2, param_names);
                
                if(info.class_name) {
                    if(info.module_name) {
                        sModule* module = gModules.at(info.module_name, null);
                        
                        if(module == null) {
                            info->exception.kind = kExceptionValue;
                            info->exception.value.expValue = kExceptionVarNotFound;
                            return false;
                        }
                        
                        sClass* klass = module.classes.at(info.class_name, null);
                        
                        if(klass == null) {
                            info->exception.kind = kExceptionValue;
                            info->exception.value.expValue = kExceptionVarNotFound;
                            return false;
                        }
                        
                        klass->funcs.insert(string(name2), fun);
                    }
                }
                else if(info.module_name) {
                    sModule* module = gModules.at(info.module_name, null);
                    
                    if(module == null) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionVarNotFound;
                        return false;
                    }
                    
                    module.funcs.insert(string(name2), fun);
                }
                }
                break;
                
            case OP_CLASS: {
                p++;
                
                int offset = *p;
                p++;
                
                int len = *p;
                p++;
                
                char* name = (char*)p;
                
                char name2[len+1];
                memcpy(name2, name, len);
                name2[len] = '\0'
                
                p += offset;
                
                int len_codes = *p;
                p++;
                
                char* codes = (char*)p;
                
                p += len_codes / sizeof(int);
                
                buffer* codes2 = new buffer.initialize();
                
                codes2.append(codes, len_codes);
                
                sClass* klass = new sClass.initialize(string(name2), codes2);
                
                if(info.module_name) {
                    sModule* module = gModules.at(info.module_name, null);
                    
                    if(module == null) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionVarNotFound;
                        return false;
                    }
                    
                    module.classes.insert(string(name2), klass);
                }
                
                if(!class_call(klass, info)) {
                    return false;
                }
                }
                break;
                
            case OP_FUNCALL: {
                p++;
                
                int offset = *p;
                p++;
                
                int len = *p;
                p++;
                
                char* fun_name = (char*)p;
                
                char fun_name2[len+1];
                memcpy(fun_name2, fun_name, len);
                fun_name2[len] = '\0'
                
                p += offset;
                
                int num_params = *p;
                p++;
                
                sModule* module = gModules.at(info.module_name, null);
                sClass* klass = module.classes.at(string(fun_name2), null);
                
                /// new object ///
                if(klass) {
                    sObject* object = new sObject.initialize(module, klass);
                    
                    sFunction* constructor = klass.funcs.at("__init__", null);
                    
                    if(constructor) {
                        vector<ZVALUE>* param_values = new vector<ZVALUE>.initialize();
                        
                        ZVALUE object_value;
                        object_value.kind = kObjValue;
                        object_value.objValue = object;
                        
                        param_values.push_back(object_value);
                        
                        for(int i=0; i<num_params; i++) {
                            ZVALUE value = stack[stack_num-num_params+i];
                            
                            param_values.push_back(value);
                        }
                        
                        if(!function_call(constructor, param_values, info)) {
                            return false;
                        }
                        
                        stack_num -= param_values.length() -1;
                        
                        stack[stack_num].kind = kObjValue;
                        stack[stack_num].objValue = object;
                        stack_num++;
                    }
                    else {
                        stack[stack_num].kind = kObjValue;
                        stack[stack_num].objValue = object;
                        stack_num++;
                    }
                }
                /// function call ///
                else {
                    vector<ZVALUE>* param_values = new vector<ZVALUE>.initialize();
                    
                    for(int i=0; i<num_params; i++) {
                        ZVALUE value = stack[stack_num-num_params+i];
                        
                        param_values.push_back(value);
                    }
                    
                    sFunction* fun = null;
                    if(info.module_name) {
                        sModule* module = gModules.at(info.module_name, null);
                        
                        fun = module.funcs.at(fun_name2, null);
                    }
                    
                    if(fun == null) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionNameError;
                        return false;
                    }
                    
                    if(!function_call(fun, param_values, info)) {
                        return false;
                    }
                    
                    stack_num -= param_values.length();
                    
                    stack[stack_num] = info->return_value;
                    stack_num++;
                }
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
                
            case OP_EQ: {
                p++;
                
                ZVALUE lvalue = stack[stack_num-2];
                ZVALUE rvalue = stack[stack_num-1];
                
                stack_num-=2;
                
                if(lvalue.kind != rvalue.kind) {
                    info->exception.kind = kExceptionValue;
                    info->exception.value.expValue = kExceptionTypeError;
                    return false;
                }
                
                switch(lvalue.kind) {
                    case kIntValue:
                        stack[stack_num].kind = kBoolValue;
                        stack[stack_num].value.boolValue = lvalue.intValue == rvalue.intValue;
                        stack_num++;
                        break;
                        
                    case kStringValue:
                        stack[stack_num].kind = kBoolValue;
                        stack[stack_num].value.boolValue = wcscmp(lvalue.stringValue, rvalue.stringValue) == 0;
                        stack_num++;
                        break;
                        
                    case kListValue:
                        stack[stack_num].kind = kBoolValue;
                        stack[stack_num].value.boolValue = lvalue.listValue.equals(rvalue.listValue);
                        stack_num++;
                        break;
                        
                    default:
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                        break;
                }
                
                }
                break;
                
            case OP_NOT_EQ: {
                p++;
                
                ZVALUE lvalue = stack[stack_num-2];
                ZVALUE rvalue = stack[stack_num-1];
                
                stack_num-=2;
                
                if(lvalue.kind != rvalue.kind) {
                    info->exception.kind = kExceptionValue;
                    info->exception.value.expValue = kExceptionTypeError;
                    return false;
                }
                
                switch(lvalue.kind) {
                    case kIntValue:
                        stack[stack_num].kind = kBoolValue;
                        stack[stack_num].value.boolValue = lvalue.intValue != rvalue.intValue;
                        stack_num++;
                        break;
                        
                    case kStringValue:
                        stack[stack_num].kind = kBoolValue;
                        stack[stack_num].value.boolValue = wcscmp(lvalue.stringValue, rvalue.stringValue) != 0;
                        stack_num++;
                        break;
                        
                    case kListValue:
                        stack[stack_num].kind = kBoolValue;
                        stack[stack_num].value.boolValue = !lvalue.listValue.equals(rvalue.listValue);
                        stack_num++;
                        break;
                        
                    default:
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                        break;
                }
                
                }
                break;
                
            case OP_MULT: {
                p++;
                
                ZVALUE lvalue = stack[stack_num-2];
                ZVALUE rvalue = stack[stack_num-1];
                
                stack_num-=2;
                
                if(rvalue.kind != kIntValue) {
                    info->exception.kind = kExceptionValue;
                    info->exception.value.expValue = kExceptionTypeError;
                    return false;
                }
                
                switch(lvalue.kind) {
                    case kIntValue:
                        stack[stack_num].kind = kIntValue;
                        stack[stack_num].value.intValue = lvalue.intValue * rvalue.intValue;
                        stack_num++;
                        break;
                        
                    case kStringValue: {
                        buffer* buf = new buffer.initialize();
                        
                        for(int i=0; i<rvalue.intValue; i++) {
                            buf.append_str(lvalue.value.stringValue.to_string());
                        }
                        
                        stack[stack_num].kind = kStringValue;
                        stack[stack_num].value.stringValue = buf.to_string().to_wstring();
                        stack_num++;
                        }
                        break;
                        
                    case kListValue: {
                        list<ZVALUE>* list_object = new list<ZVALUE>.initialize();
                        
                        list<ZVALUE>* li = lvalue.value.listValue;
                        
                        for(int i=0; i<rvalue.intValue; i++) {
                            foreach(it, li) {
                                list_object.push_back(it);
                            }
                        }
                        
                        stack[stack_num].kind = kListValue;
                        stack[stack_num].value.listValue = list_object;
                        stack_num++;
                        }
                        break;
                        
                    default:
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                        break;
                }
                
                }
                break;
                
            case OP_DIV: {
                p++;
                
                ZVALUE lvalue = stack[stack_num-2];
                ZVALUE rvalue = stack[stack_num-1];
                
                stack_num-=2;
                
                if(lvalue.kind != kIntValue && rvalue.kind != kIntValue) {
                    info->exception.kind = kExceptionValue;
                    info->exception.value.expValue = kExceptionTypeError;
                    return false;
                }
                
                if(rvalue.intValue == 0) {
                    info->exception.kind = kExceptionValue;
                    info->exception.value.expValue = kExceptionDivisionByZero;
                    return false;
                }
                
                stack[stack_num].kind = kIntValue;
                stack[stack_num].value.intValue = lvalue.intValue / rvalue.intValue;
                stack_num++;
                
                }
                break;
                
            case OP_EXIT: 
                p++;
                
                if(stack[stack_num-1].kind == kIntValue) {
                    int rcode = stack[stack_num-1].value.intValue;
                    exit(rcode);
                }
                else {
                    info->exception.kind = kExceptionValue;
                    info->exception.value.expValue = kExceptionTypeError;
                    return false;
                }
                break;
                
            case OP_RETURN: 
                p++;
                
                ZVALUE return_value = stack[stack_num-1];
                
                stack_num--;
                
                info->return_value = return_value;
                
                return true;
                break;
                
            case OP_IMPORT:
                p++;
                
                int offset = *p;
                p++;
                
                int len = *p;
                p++;
                
                char* str = (char*)p;
                
                char str2[len+1];
                memcpy(str2, str, len);
                str2[len] = '\0'
                
                p += offset;
                
                if(!import_module(str2)) {
                    return false;
                }
                
                
                break;
                
            case OP_METHOD_CALL: {
                p++;
                
                int offset = *p;
                p++;
                
                int len = *p;
                p++;
                
                char* fun_name = (char*)p;
                
                char fun_name2[len+1];
                memcpy(fun_name2, fun_name, len);
                fun_name2[len] = '\0'
                
                p += offset;
                
                int num_params = *p;
                p++;
                
                if(stack[stack_num-1-num_params].kind == kModuleValue) {
                    sModule* module = (sModule*)stack[stack_num-num_params-1].moduleValue;
                    
                    
                    vector<ZVALUE>* param_values = new vector<ZVALUE>.initialize();
                    
                    for(int i=0; i<num_params; i++) {
                        ZVALUE value = stack[stack_num-num_params+i];
                        
                        param_values.push_back(value);
                    }
                    
                    sFunction* fun = module.funcs.at(fun_name2, null);
                    
                    if(fun == null) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionMethodNotFound;
                        return false;
                    }
                    
                    if(!function_call(fun, param_values, info)) {
                        return false;
                    }
                    
                    stack_num--;
                    stack_num -= param_values.length();
                    
                    stack[stack_num] = info->return_value;
                    stack_num++;
                }
                else if(stack[stack_num-num_params-1].kind == kObjValue) {
                    sObject* object = (sObject*)stack[stack_num-num_params-1].objValue;
                    
                    vector<ZVALUE>* param_values = new vector<ZVALUE>.initialize();
                    
                    ZVALUE object_value;
                    object_value.kind = kObjValue;
                    object_value.objValue = object;
                    
                    param_values.push_back(object_value);
                    
                    for(int i=0; i<num_params; i++) {
                        ZVALUE value = stack[stack_num-num_params+i];
                        
                        param_values.push_back(value);
                    }
                    
                    sFunction* fun = object.klass.funcs.at(fun_name2, null);
                    
                    if(fun == null) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionMethodNotFound;
                        return false;
                    }
                    
                    if(!function_call(fun, param_values, info)) {
                        return false;
                    }
                    
                    stack_num -= param_values.length();
                    
                    stack[stack_num] = info->return_value;
                    stack_num++;
                }
                else {
                    info->exception.kind = kExceptionValue;
                    info->exception.value.expValue = kExceptionMethodNotFound;
                    return false;
                }
                }
                break;
                
            case OP_LOAD_FIELD: {
                p++;
                
                int offset = *p;
                p++;
                
                int len = *p;
                p++;
                
                char* field_name = (char*)p;
                
                char field_name2[len+1];
                memcpy(field_name2, field_name, len);
                field_name2[len] = '\0'
                
                p += offset;
                
                
                if(stack[stack_num-1].kind == kModuleValue) {
                    sModule* module = (sModule*)stack[stack_num-1].moduleValue;
                    stack_num--;
                    
                    
                    sClass* klass = module->classes.at(string(field_name2), null);
                    
                    if(klass == null) {
                        stack[stack_num] = module->global_vars.at(string(field_name2), gNullValue);
                        stack_num++;
                        
                        if(stack[stack_num-1].kind == kNullValue) {
                            info->exception.kind = kExceptionValue;
                            info->exception.value.expValue = kExceptionVarNotFound;
                            return false;
                        }
                    }
                    else {
                        stack[stack_num].kind = kClassValue;
                        stack[stack_num].classValue = klass;
                        stack_num++;
                    }
                }
                else if(stack[stack_num-1].kind == kClassValue) {
                    sClass* klass = (sClass*)stack[stack_num-1].classValue;
                    stack_num--;
                    
                    stack[stack_num] = klass->class_vars.at(string(field_name2), gNullValue);
                    stack_num++;
                    
                    if(stack[stack_num-1].kind == kNullValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionVarNotFound;
                        return false;
                    }
                }
                else if(stack[stack_num-1].kind == kObjValue) {
                    sObject* object = (sObject*)stack[stack_num-1].objValue;
                    stack_num--;
                    
                    stack[stack_num] = object->fields.at(string(field_name2), gNullValue);
                    stack_num++;
                    
                    if(stack[stack_num-1].kind == kNullValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionVarNotFound;
                        return false;
                    }
                }
                else {
                    info->exception.kind = kExceptionValue;
                    info->exception.value.expValue = kExceptionVarNotFound;
                    return false;
                }
                }
                break;
                
            case OP_STORE_FIELD: {
                p++;
                
                int offset = *p;
                p++;
                
                int len = *p;
                p++;
                
                char* field_name = (char*)p;
                
                char field_name2[len+1];
                memcpy(field_name2, field_name, len);
                field_name2[len] = '\0'
                
                p += offset;
                
                ZVALUE left = stack[stack_num-2];
                ZVALUE right = stack[stack_num-1];
                
                if(left.kind == kModuleValue) {
                    sModule* module = (sModule*)left.moduleValue;
                    
                    module->global_vars.insert(string(field_name2), right);
                    
                    stack_num -= 2;
                    
                    stack[stack_num] = right;
                    stack_num++;
                }
                else if(left.kind == kClassValue) {
                    sClass* klass = (sClass*)left.classValue;
                    
                    klass->class_vars.insert(string(field_name2), right);
                    
                    stack_num -= 2;
                    
                    stack[stack_num] = right;
                    stack_num++;
                }
                else if(left.kind == kObjValue) {
                    sObject* obj = (sObject*)left.objValue;
                    
                    obj->fields.insert(string(field_name2), right);
                    
                    stack_num -= 2;
                    
                    stack[stack_num] = right;
                    stack_num++;
                }
                else {
                    info->exception.kind = kExceptionValue;
                    info->exception.value.expValue = kExceptionVarNotFound;
                    return false;
                }
                }
                break;
                
            case OP_LIST_VALUE: {
                p++;
                
                int len = *p;
                p++;
                
                list<ZVALUE>* list_object = new list<ZVALUE>.initialize();
                
                for(int i=0; i<len; i++) {
                    ZVALUE element = stack[stack_num-len+i];
                    
                    list_object.push_back(element);
                }
                
                stack_num -= len;
                
                stack[stack_num].kind = kListValue;
                stack[stack_num].listValue = list_object;
                stack_num++;
                
                }
                break;
                
            case OP_LIST_INDEX: {
                p++;
                
                int slice = *p;
                p++;
                
                int slice2 = *p;
                p++;
                
                if(slice && slice2) {
                    ZVALUE array_value = stack[stack_num-4];
                    ZVALUE index_value = stack[stack_num-3];
                    ZVALUE index_value2 = stack[stack_num-2];
                    ZVALUE index_value3 = stack[stack_num-1];
                    
                    if(array_value.kind != kListValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                    }
                    
                    if(index_value.kind != kIntValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                    }
                    
                    if(index_value2.kind != kIntValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                    }
                    
                    if(index_value3.kind != kIntValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                    }
                    
                    list<ZVALUE>* list_object = array_value.listValue;
                    
                    int index = index_value.intValue;
                    int index2 = index_value2.intValue;
                    int index3 = index_value3.intValue;
                    
                    if(index < 0) {
                        index += list_object.length();
                    }

                    if(index2 < 0) {
                        index2 += list_object.length() + 1;
                    }

                    if(index < 0) {
                        index = 0;
                    }

                    if(index2 >= list_object.length()) {
                        index2 = list_object.length();
                    }
                    
                    list<ZVALUE>* list_object2 = new list<ZVALUE>.initialize();
                    
                    int i = 0;
                    foreach(it, list_object) {
                        if(i >= index && i < index2 && (i % index3 == 0)) {
                            list_object2.push_back(it);
                        }
                        i++;
                    }
                    
                    stack_num -=4;
                    
                    stack[stack_num].kind = kListValue;
                    stack[stack_num].value.listValue = list_object2;
                    stack_num++;
                }
                else if(slice) {
                    ZVALUE array_value = stack[stack_num-3];
                    ZVALUE index_value = stack[stack_num-2];
                    ZVALUE index_value2 = stack[stack_num-1];
                    
                    if(array_value.kind != kListValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                    }
                    
                    if(index_value.kind != kIntValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                    }
                    
                    if(index_value2.kind != kIntValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                    }
                    
                    list<ZVALUE>* list_object = array_value.listValue;
                    
                    int index = index_value.intValue;
                    int index2 = index_value2.intValue;
                    
                    list<ZVALUE>* list_object2 = list_object.sublist(index, index2);
                    
                    stack_num -=3;
                    
                    stack[stack_num].kind = kListValue;
                    stack[stack_num].value.listValue = list_object2;
                    stack_num++;
                }
/*
                else if(slice2) {
                    ZVALUE array_value = stack[stack_num-3];
                    ZVALUE index_value = stack[stack_num-2];
                    ZVALUE index_value3 = stack[stack_num-1];
                    
                    if(array_value.kind != kListValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                    }
                    
                    if(index_value.kind != kIntValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                    }
                    
                    if(index_value3.kind != kIntValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                    }
                }
*/
                else {
                    ZVALUE array_value = stack[stack_num-2];
                    ZVALUE index_value = stack[stack_num-1];
                    
                    if(array_value.kind != kListValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                    }
                    
                    if(index_value.kind != kIntValue) {
                        info->exception.kind = kExceptionValue;
                        info->exception.value.expValue = kExceptionTypeError;
                        return false;
                    }
                    
                    list<ZVALUE>* list_object = array_value.listValue;
                    
                    int index = index_value.intValue;
                    
                    stack_num -=2;
                    
                    stack[stack_num] = list_object.item(index, gNullValue);
                    stack_num++;
                }
                
                }
                break;
                
            case OP_ANDAND: {
                p++;
                
                ZVALUE lvalue = stack[stack_num-2];
                ZVALUE rvalue = stack[stack_num-1];
                
                if(lvalue.kind != kBoolValue || rvalue.kind != kBoolValue) {
                    info->exception.kind = kExceptionValue;
                    info->exception.value.expValue = kExceptionTypeError;
                    return false;
                }
                
                stack_num-=2;
                
                stack[stack_num].kind = kBoolValue;
                stack[stack_num].value.boolValue = lvalue.boolValue && rvalue.boolValue;
                stack_num++;
                
                }
                break;
                
            case OP_OROR: {
                p++;
                
                ZVALUE lvalue = stack[stack_num-2];
                ZVALUE rvalue = stack[stack_num-1];
                
                if((lvalue.kind != kBoolValue) || (rvalue.kind != kBoolValue)) {
                    info->exception.kind = kExceptionValue;
                    info->exception.value.expValue = kExceptionTypeError;
                    return false;
                }
                
                stack_num-=2;
                
                stack[stack_num].kind = kBoolValue;
                stack[stack_num].value.boolValue = lvalue.boolValue || rvalue.boolValue;
                stack_num++;
                
                }
                break;
                
            default:
                printf("Interpreter Bug occurs. invalid op code %d\n", *p);
                exit(1);
        }
        
        if(stack_num < 0 || stack_num >= ZSTACK_MAX) {
            fprintf(stderr, "Inerpreter Bug occurs. invalid stack num %d\n", stack_num);
            exit(1);
        }
    }
    
    return true;
}

