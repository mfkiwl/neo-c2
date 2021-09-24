#include "common.h"

sVarTable* gHeadVTable;

void init_vtable()
{
    gHeadVTable = NULL;
}

void final_vtable()
{
    sVarTable* it;

    it = gHeadVTable;
    while(it) {
        sVarTable* next;

        next = it->mNext;
        free(it);

        it = next;
    }
}

static int mNumVarTables = 0;

sVarTable* init_var_table()
{
    sVarTable* result;

    result = xcalloc(1, sizeof(sVarTable));

    result->mNext = gHeadVTable;
    gHeadVTable = result;

    result->mID = mNumVarTables++;

    return result;
}

sVarTable* clone_var_table(sVarTable* lv_table)
{
    sVarTable* result = init_var_table();

    result->mMaxBlockVarNum = lv_table->mMaxBlockVarNum;
    result->mBlockLevel = lv_table->mBlockLevel;
    result->mID = lv_table->mID;

    result->mCloneTable = lv_table;
    lv_table->mClonedTable = result;

    sVarTable* it = lv_table;

    sVar* p = it->mLocalVariables;

    while(1) {
        if(p->mName[0] != 0) {
            if(!add_variable_to_table(result, p->mName, p->mType, p->mReadOnly, p->mLLVMValue, p->mIndex, p->mGlobal, p->mConstant))
            {
                fprintf(stderr, "overflow variable table\n");
                exit(2);
            }
        }

        p++;

        if(p == lv_table->mLocalVariables + LOCAL_VARIABLE_MAX) {
            break;
        }
    }

    if(it->mParent) {
        result->mParent = clone_var_table(it->mParent);
    }
    else {
        result->mParent = NULL;
    }

    return result;
}

void restore_var_table(sVarTable* left, sVarTable* right)
{
    sVarTable* it = left;
    sVarTable* it2 = right;

    while(it && it2) {
        sVar* p = it->mLocalVariables;

        while(1) {
            if(p->mName[0] != 0) {
                sVar* p2 = it2->mLocalVariables;
                while(1) {
                    if(p2->mName[0] != 0 && strcmp(p->mName, p2->mName) == 0) 
                    {
                        p->mType = p2->mType;
                    }

                    p2++;

                    if(p2 == it2->mLocalVariables + LOCAL_VARIABLE_MAX) {
                        break;
                    }
                }
            }

            p++;

            if(p == it->mLocalVariables + LOCAL_VARIABLE_MAX) {
                break;
            }
        }

        it = it->mParent;
        it2 = it2->mParent;
    }
}

//////////////////////////////////////////////////
// local variable table
//////////////////////////////////////////////////
// result: (true) success (false) overflow the table or a variable which has the same name exists
BOOL add_variable_to_table(sVarTable* table, char* name, sNodeType* type_, BOOL readonly, void* llvm_value, int index, BOOL global, BOOL constant)
{
    int hash_value;
    sVar* p;

    hash_value = get_hash_key(name, LOCAL_VARIABLE_MAX);
    p = table->mLocalVariables + hash_value;

    while(1) {
        if(p->mName[0] == 0) {
            xstrncpy(p->mName, name, VAR_NAME_MAX);
            if(index == -1) {
                p->mIndex = table->mVarNum++;
            }
            else {
                p->mIndex = index;
            }

            if(type_) {
                p->mType = clone_node_type(type_);
            }
            else {
                p->mType = NULL;
            }
            p->mBlockLevel = table->mBlockLevel;
            p->mReadOnly = readonly;
            p->mLLVMValue = llvm_value;
            p->mGlobal = global;
            p->mConstant = constant;

            if(table->mVarNum >= LOCAL_VARIABLE_MAX) {
                return FALSE;
            }

            return TRUE;
        }
        else {
            if(strcmp(p->mName, name) == 0) {
                return TRUE;

/*
                if(p->mBlockLevel < table->mBlockLevel) {
                    xstrncpy(p->mName, name, VAR_NAME_MAX);
                    p->mIndex = table->mVarNum++;
                    if(type_) {
                        p->mType = clone_node_type(type_);
                    }
                    else {
                        p->mType = NULL;
                    }

                    p->mBlockLevel = table->mBlockLevel;
                    p->mReadOnly = readonly;
                    p->mLLVMValue = llvm_value;

                    if(table->mVarNum >= LOCAL_VARIABLE_MAX) {
                        return FALSE;
                    }

                    return TRUE;
                }
                else {
                    return FALSE;
                }
*/
            }
            else {
                p++;

                if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
                    p = table->mLocalVariables;
                }
                else if(p == table->mLocalVariables + hash_value) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

sVar* get_variable_from_index(sVarTable* table, int index)
{
    int hash_value;
    sVar* p;

    p = table->mLocalVariables;

    while(1) {
        if(p->mName[0] != 0 && p->mIndex == index) {
            return p;
        }

        p++;

        if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
            break;
        }
    }

    return NULL;
}

// result: (null) not found (sVar*) found
sVar* get_variable_from_this_table_only(sVarTable* table, char* name)
{
    int hash_value;
    sVar* p;

    hash_value = get_hash_key(name, LOCAL_VARIABLE_MAX);

    p = table->mLocalVariables + hash_value;

    while(1) {
        if(p->mName[0] == 0) {
            return NULL;
        }
        else if(strcmp((char*)p->mName, name) == 0) {
            return p;
        }

        p++;

        if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
            p = table->mLocalVariables;
        }
        else if(p == table->mLocalVariables + hash_value) {
            return NULL;
        }
    }
}

BOOL is_included_var_from_this_table_only(sVarTable* table, sVar* var_)
{
    int hash_value = 0;

    sVar* p = table->mLocalVariables + hash_value;

    while(1) {
        if(p == var_) {
            return TRUE;
        }

        p++;

        if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
            return FALSE;
        }
    }
}



void check_already_added_variable(sVarTable* table, char* name, struct sParserInfoStruct* info)
{
    sVar* var_ = get_variable_from_this_table_only(table, name);
    
    if(var_ != NULL && !var_->mGlobal) {
        char msg[1024];
        snprintf(msg, 1024, "Variable (%s) has already_added in this variable table", name);
        parser_err_msg(info, msg);
        info->err_num++;
    }
}

// result: (null) not found (sVar*) found
sVar* get_variable_from_table(sVarTable* table, char* name)
{
    sVarTable* it;
    sVar* var_;

    it = table;

    while(it) {
        var_ = get_variable_from_this_table_only(it, name);

        if(var_) {
            return var_;
        }

        it = it->mParent;
    }

    return NULL;
}

static int get_sum_of_parent_var_num(sVarTable* table)
{
    int n = 0;
    sVarTable* p = table->mParent;

    while(p) {
        n += p->mVarNum;
        p = p->mParent;
    }

    return n;
}

int get_variable_index(sVarTable* table, char* name, BOOL* parent)
{
    sVarTable* it = table;

    while(it) {
        sVar* var_ = get_variable_from_this_table_only(it, name);

        if(var_) {
            return var_->mIndex + get_sum_of_parent_var_num(it);
        }

        it = it->mParent;
        *parent = TRUE;
    }

    return -1;
}

int get_var_num(sVarTable* table)
{
    return table->mVarNum + table->mMaxBlockVarNum;
}

int get_parent_var_num_of_sum(sVarTable* table)
{
    return get_sum_of_parent_var_num(table);
}

sVarTable* init_block_vtable(sVarTable* lv_table, BOOL no_increment_block_level)
{
    sVarTable* new_table;

    new_table = init_var_table();
    if(lv_table) {
        if(no_increment_block_level) {
            new_table->mBlockLevel = lv_table->mBlockLevel;
        }
        else {
            new_table->mBlockLevel = lv_table->mBlockLevel + 1;
        }
        new_table->mParent = lv_table;
    }
    else {
        new_table->mBlockLevel = 1;
        new_table->mParent = gModuleVarTable;
    }

    return new_table;
}

void set_max_block_var_num(sVarTable* lv_table, sVarTable* old_table)
{
    /// get local var number of this block ///
    int lv_num_of_this_block = lv_table->mVarNum + lv_table->mMaxBlockVarNum;
    if(lv_num_of_this_block > old_table->mMaxBlockVarNum) {
       old_table->mMaxBlockVarNum = lv_num_of_this_block;
    }
}

void show_vtable_current_only(sVarTable* table)
{
    sVarTable* it = table;

    while(it) {
        sVar* p = it->mLocalVariables;

        while(1) {
            if(p->mName[0] != 0) {
                printf("name %s index %d block level %d readonly %d constant %d value %p global %d\n", p->mName, p->mIndex, p->mBlockLevel, p->mReadOnly, p->mConstant, p->mLLVMValue, p->mGlobal);

                if(p->mType && p->mType->mClass) 
                {
                    printf("%s\n", CLASS_NAME(p->mType->mClass));
                }
            }

            p++;

            if(p == it->mLocalVariables + LOCAL_VARIABLE_MAX) {
                break;
            }
        }
        break;
    }
}

void show_vtable(sVarTable* table)
{
    sVarTable* it = table;

    while(it) {
        sVar* p = it->mLocalVariables;

        while(1) {
            if(p->mName[0] != 0) {
                printf("name %s index %d block level %d readonly %d constant %d value %p global %d\n", p->mName, p->mIndex, p->mBlockLevel, p->mReadOnly, p->mConstant, p->mLLVMValue, p->mGlobal);

                if(p->mType && p->mType->mClass) 
                {
                    printf("%s\n", CLASS_NAME(p->mType->mClass));
                }
            }

            p++;

            if(p == it->mLocalVariables + LOCAL_VARIABLE_MAX) {
                break;
            }
        }

        it = it->mParent;
    }
}

void free_objects(sVarTable* table, sCompileInfo* info)
{
    if(!info->no_output) {
        sVar* p = table->mLocalVariables;

        while(1) {
            if(p->mName[0] != 0) {
                sNodeType* node_type = p->mType;
                sCLClass* klass = node_type->mClass;

                if(node_type->mHeap)
                {
                    if(p->mLLVMValue)
                    {
                        if(p->mConstant) {
                            LLVMValueRef obj = p->mLLVMValue;
                            free_object(p->mType, obj, info);
                            remove_object_from_right_values(obj, info);
                        }
                        else {
                            LLVMValueRef obj = LLVMBuildLoad(gBuilder, p->mLLVMValue, "obj");
                            free_object(p->mType, obj, info);
                            remove_object_from_right_values(obj, info);
                        }

                        p->mLLVMValue = NULL;
                    }
                }
            }

            p++;

            if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
                break;
            }
        }
    }
}

static void free_block_variables(sVarTable* table, LLVMValueRef ret_value, sCompileInfo* info)
{
    sVar* p = table->mLocalVariables;

    while(1) {
        if(p->mName[0] != 0) {
            sNodeType* node_type = p->mType;

            if(node_type) {
                sCLClass* klass = node_type->mClass;
                if(node_type->mHeap)
                {
                    if(p->mLLVMValue)
                    {
                        if(p->mLLVMValue != ret_value) {
                            if(p->mConstant) {
                                LLVMValueRef obj = p->mLLVMValue;
                                free_object(p->mType, obj, info);
                                remove_object_from_right_values(obj, info);
                            }
                            else {
                                LLVMValueRef obj = LLVMBuildLoad(gBuilder, p->mLLVMValue, "obj");
                                free_object(p->mType, obj, info);
                                remove_object_from_right_values(obj, info);
                            }
                        }

                        //p->mLLVMValue = NULL;
                    }
                }
            }
        }

        p++;

        if(p == table->mLocalVariables + LOCAL_VARIABLE_MAX) {
            break;
        }
    }
}

void free_objects_on_return(struct sNodeBlockStruct* current_node_block, struct sCompileInfoStruct* info, LLVMValueRef ret_value, BOOL top_block)
{
    sVarTable* current_lv_table = info->pinfo->lv_table;

    sVarTable* current_block_lv_table = current_node_block->mLVTable;

    sVarTable* it = current_lv_table;

    if(current_lv_table->mID == current_block_lv_table->mID) {
        free_block_variables(it, ret_value, info);
    }
    else {
        while(it !=NULL && it->mID != current_block_lv_table->mID)
        {
            free_block_variables(it, ret_value, info);

            it = it->mParent;
        }

        if(top_block && it != NULL) {
            free_block_variables(it, ret_value, info);
        }
    }
}

void create_current_stack_frame_struct(char* type_name, sVarTable* lv_table)
{
    static int n = 0;

    int num_fields = 0;
    char field_names[STRUCT_FIELD_MAX][VAR_NAME_MAX];
    sNodeType* fields[STRUCT_FIELD_MAX];

    sVarTable* it = lv_table;

    while(it) {
        sVar* p = it->mLocalVariables;

        while(1) {
            if(p->mName[0] != 0 && p->mType) {
                xstrncpy(field_names[num_fields], p->mName, VAR_NAME_MAX);

                sNodeType* node_type = clone_node_type(p->mType);

                if(node_type->mArrayDimentionNum > 0) {
                    node_type->mArrayDimentionNum--;
                    node_type->mPointerNum++;
                    //node_type->mCurrentStackVariable = TRUE;
                }
                else {
                    node_type->mPointerNum++;
                }

                fields[num_fields] = node_type;

                num_fields++;
            }

            p++;

            if(p == it->mLocalVariables + LOCAL_VARIABLE_MAX) {
                break;
            }
        }

        if(it->mBlockLevel == 1) {
            break;
        }

        it = it->mParent;
    }

    char* field_names2[STRUCT_FIELD_MAX];

    int i;
    for(i=0; i<num_fields; i++) {
        field_names2[i] = field_names[i];
    }

/*
    sCLClass* current_stack = get_same_current_stack(num_fields, field_names2, fields);

    if(current_stack) {
        snprintf(type_name, VAR_NAME_MAX, "%s", CLASS_NAME(current_stack));
    }
    else {
*/
        snprintf(type_name, VAR_NAME_MAX, "__current_stack_frame__%d", n);
        sCLClass* klass = alloc_struct(type_name, FALSE, FALSE);

        add_fields_to_struct(klass, num_fields, field_names2, fields);

        sNodeType* node_type = create_node_type_with_class_pointer(klass);

        char* struct_name = CLASS_NAME(node_type->mClass);
        BOOL undefined_body = FALSE;
        (void)create_llvm_struct_type(struct_name, node_type, NULL, undefined_body);

        n++;
//    }
}
