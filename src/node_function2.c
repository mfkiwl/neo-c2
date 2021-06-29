#include "common.h"

sFunction gFuncs[FUN_NUM_MAX];

void function_init()
{
    memset(gFuncs, 0, sizeof(sFunction)*FUN_NUM_MAX);
}

void function_final()
{
    int i;
    for(i=0; i<FUN_NUM_MAX; i++) {
        if(gFuncs[i].mName) {
            free(gFuncs[i].mName);

            int j;
            for(j=0; j<gFuncs[i].mNumParams; j++) {
                free(gFuncs[i].mParamNames[j]);
            }

            for(j=0; j<gFuncs[i].mNumGenerics; j++) {
                free(gFuncs[i].mGenericsTypeNames[j]);
            }
        }
    }
}

BOOL add_function_to_table(char* name, int num_params, char** param_names, sNodeType** param_types, sNodeType* result_type, LLVMValueRef llvm_fun, char* block_text, BOOL generics_function, BOOL var_args, int num_generics, char** generics_type_names, BOOL extern_)
{
    int hash_value = get_hash_key(name, FUN_NUM_MAX);
    sFunction* p = gFuncs + hash_value;

    while(1) {
        if(p->mName == NULL) {
            p->mName = strdup(name);

            p->mNumParams = num_params;

            int i;
            for(i=0; i<num_params; i++) {
                p->mParamNames[i] = strdup(param_names[i]);
                p->mParamTypes[i] = param_types[i];
            }

            p->mResultType = result_type;
            p->mLLVMFunction = llvm_fun;
            p->mBlockText = block_text;
            p->mGenericsFunction = generics_function;
            p->mVarArgs = var_args;
            p->mNumGenerics = num_generics;
            p->mExtern = extern_;

            for(i=0; i<num_generics; i++) {
                p->mGenericsTypeNames[i] = strdup(generics_type_names[i]);
            }

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

                p->mName = strdup(name);

                p->mNumParams = num_params;

                for(i=0; i<num_params; i++) {
                    p->mParamNames[i] = strdup(param_names[i]);
                    p->mParamTypes[i] = param_types[i];
                }

                p->mResultType = result_type;
                p->mLLVMFunction = llvm_fun;
                p->mBlockText = block_text;
                p->mGenericsFunction = generics_function;
                p->mVarArgs = var_args;
                p->mNumGenerics = num_generics;
                p->mExtern = extern_;

                for(i=0; i<num_generics; i++) {
                    p->mGenericsTypeNames[i] = strdup(generics_type_names[i]);
                }

                return TRUE;
            }
            else {
                p++;

                if(p == gFuncs + FUN_NUM_MAX) {
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
    int hash_value = get_hash_key(name, FUN_NUM_MAX);

    sFunction* p = gFuncs + hash_value;

    while(1) {
        if(p->mName == NULL) {
            return NULL;
        }
        else if(strcmp((char*)p->mName, name) == 0) {
            return p;
        }

        p++;

        if(p == gFuncs + FUN_NUM_MAX) {
            p = gFuncs;
        }
        else if(p == gFuncs + hash_value) {
            return NULL;
        }
    }
}
