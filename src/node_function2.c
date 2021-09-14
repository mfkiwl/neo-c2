#include "common.h"

sFunction* gFuncs;
int gSizeFuncs;
int gNumFuncs;

void node_function_init()
{
    gSizeFuncs = 512;
    gFuncs = calloc(1, sizeof(sFunction)*gSizeFuncs);
    gNumFuncs = 0;
}

void free_funcs()
{
    int i;
    for(i=0; i<gSizeFuncs; i++) {
        if(gFuncs[i].mName) {
            free(gFuncs[i].mName);
            if(gFuncs[i].mAsmFunName) {
                free(gFuncs[i].mAsmFunName);
            }

            int j;
            for(j=0; j<gFuncs[i].mNumParams; j++) {
                free(gFuncs[i].mParamNames[j]);
            }

            for(j=0; j<gFuncs[i].mNumGenerics; j++) {
                free(gFuncs[i].mGenericsTypeNames[j]);
            }

            if(gFuncs[i].mSource) {
                free(gFuncs[i].mSource);
            }
        }
    }
    free(gFuncs);
}

void show_func(sFunction* fun, BOOL code)
{
    printf("%s(", fun->mName);

    int j;
    for(j=0; j<fun->mNumParams; j++) {
        show_node_type_one_line(fun->mParamTypes[j]);
        printf(" %s", fun->mParamNames[j]);

        if(j!=fun->mNumParams-1) {
            printf(",");
        }
    }
    printf(") ");

    if(fun->mAsmFunName) {
        printf("asm fun name %s ", fun->mAsmFunName);
    }
    printf("extern %d var args %d gnerics function %d ", fun->mExtern, fun->mVarArgs, fun->mGenericsFunction);

    printf("num params %d\n", fun->mNumParams);

    printf("[result type] ");
    show_node_type(fun->mResultType);

    if(fun->mNumGenerics > 0) {
        printf("num gererincs %d\n", fun->mNumGenerics);

        for(j=0; j<fun->mNumGenerics; j++) {
            puts(fun->mGenericsTypeNames[j]);
        }
    }

    if(fun->mSource) {
        printf("{\n%s\n}\n", fun->mSource);
    }
}

void show_funcs()
{
    int i;
    for(i=0; i<gSizeFuncs; i++) {
        if(gFuncs[i].mName) {
            show_func(&gFuncs[i], FALSE);
        }
    }
}

void node_function_final()
{
    free_funcs();
}

void rehash_funcs()
{
    int new_size_funcs = gSizeFuncs * 2;
    sFunction* new_funcs = calloc(1, sizeof(sFunction)*new_size_funcs);

    int i;
    for(i=0; i<gSizeFuncs; i++) {
        if(gFuncs[i].mName) {
            int hash_value = get_hash_key(gFuncs[i].mName, new_size_funcs);

            sFunction *p = new_funcs + hash_value;

            while(1) {
                if(p->mName == NULL) {
                    p->mName = strdup(gFuncs[i].mName);

                    p->mNumParams = gFuncs[i].mNumParams;

                    int j;
                    for(j=0; j<gFuncs[i].mNumParams; j++) {
                        p->mParamNames[j] = strdup(gFuncs[i].mParamNames[j]);
                        p->mParamTypes[j] = gFuncs[i].mParamTypes[j];
                    }

                    p->mResultType = gFuncs[i].mResultType;
                    p->mLLVMFunction = gFuncs[i].mLLVMFunction;
                    p->mBlockText = gFuncs[i].mBlockText;
                    p->mGenericsFunction = gFuncs[i].mGenericsFunction;
                    p->mVarArgs = gFuncs[i].mVarArgs;
                    p->mNumGenerics = gFuncs[i].mNumGenerics;
                    p->mExtern = gFuncs[i].mExtern;

                    for(j=0; j<gFuncs[i].mNumGenerics; j++) {
                        p->mGenericsTypeNames[j] = strdup(gFuncs[i].mGenericsTypeNames[j]);
                    }

                    if(p->mAsmFunName) {
                        p->mAsmFunName = strdup(gFuncs[i].mAsmFunName);
                    }
                    break;
                }
                else {
                    p++;

                    if(p == new_funcs + new_size_funcs) {
                        p = new_funcs;
                    }
                    else if(p == new_funcs + hash_value) {
                        fprintf(stderr, "ovewflow rehash_funcs\n");
                        exit(2);
                    }
                }
            }
        }
    }

    free_funcs();

    gFuncs = new_funcs;
    gSizeFuncs = new_size_funcs;
}

BOOL add_function_to_table(char* name, int num_params, char** param_names, sNodeType** param_types, sNodeType* result_type, LLVMValueRef llvm_fun, char* block_text, BOOL generics_function, BOOL var_args, int num_generics, char** generics_type_names, BOOL extern_, char* asm_fun_name, BOOL user, char* source)
{
    if(gNumFuncs >= gSizeFuncs/3) {
        rehash_funcs();
    }

    int hash_value = get_hash_key(name, gSizeFuncs);
    sFunction* p = gFuncs + hash_value;

    while(1) {
        if(p->mName == NULL) {
            p->mName = strdup(name);

            p->mNumParams = num_params;

            int i;
            for(i=0; i<num_params; i++) {
                p->mParamNames[i] = strdup(param_names[i]);
                p->mParamTypes[i] = clone_node_type(param_types[i]);
            }

            p->mResultType = clone_node_type(result_type);
            p->mLLVMFunction = llvm_fun;
            p->mBlockText = block_text;
            p->mGenericsFunction = generics_function;
            p->mVarArgs = var_args;
            p->mNumGenerics = num_generics;
            p->mExtern = extern_;
            p->mUser = user;
            if(source) {
                p->mSource = strdup(source);
            }
            else {
                p->mSource = NULL;
            }

            for(i=0; i<num_generics; i++) {
                p->mGenericsTypeNames[i] = strdup(generics_type_names[i]);
            }

            if(asm_fun_name == NULL || strcmp(asm_fun_name, "") == 0) {
                p->mAsmFunName = NULL;
            }
            else {
                p->mAsmFunName = strdup(asm_fun_name);
            }

            gNumFuncs++;

            return TRUE;
        }
        else {
            if(strcmp(p->mName, name) == 0) {
                free(p->mName);

                int i;
                for(i=0; i<p->mNumParams; i++) {
                    free(p->mParamNames[i]);
                }

                for(i=0; i<p->mNumGenerics; i++) {
                    free(p->mGenericsTypeNames[i]);
                }

                if(p->mAsmFunName) {
                    free(p->mAsmFunName);
                }

                p->mName = strdup(name);

                p->mNumParams = num_params;

                for(i=0; i<num_params; i++) {
                    p->mParamNames[i] = strdup(param_names[i]);
                    p->mParamTypes[i] = clone_node_type(param_types[i]);
                }

                p->mResultType = clone_node_type(result_type);
                p->mLLVMFunction = llvm_fun;
                p->mBlockText = block_text;
                p->mGenericsFunction = generics_function;
                p->mVarArgs = var_args;
                p->mNumGenerics = num_generics;
                p->mExtern = extern_;
                p->mUser = user;
                if(source) {
                    p->mSource = strdup(source);
                }
                else {
                    p->mSource = NULL;
                }

                for(i=0; i<num_generics; i++) {
                    p->mGenericsTypeNames[i] = strdup(generics_type_names[i]);
                }

                if(asm_fun_name == NULL || strcmp(asm_fun_name, "") == 0) {
                    p->mAsmFunName = NULL;
                }
                else {
                    p->mAsmFunName = strdup(asm_fun_name);
                }

                return TRUE;
            }
            else {
                p++;

                if(p == gFuncs + gSizeFuncs) {
                    p = gFuncs;
                }
                else if(p == gFuncs + hash_value) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

sFunction* get_function_from_table(char* name)
{
    int hash_value = get_hash_key(name, gSizeFuncs);

    sFunction* p = gFuncs + hash_value;

    while(1) {
        if(p->mName == NULL) {
            return NULL;
        }
        else if(strcmp((char*)p->mName, name) == 0) {
            return p;
        }

        p++;

        if(p == gFuncs + gSizeFuncs) {
            p = gFuncs;
        }
        else if(p == gFuncs + hash_value) {
            return NULL;
        }
    }
}
