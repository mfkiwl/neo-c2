#include "common.h"

sLabel gLabels[LABEL_MAX];

void label_init()
{
    memset(gLabels, 0, sizeof(sLabel)*LABEL_MAX);
}

void label_final()
{
    int i;
    for(i=0; i<LABEL_MAX; i++) {
        if(gLabels[i].mName != NULL) {
            free(gLabels[i].mName);
        }
    }
}

BOOL add_label_to_table(char* name, LLVMBasicBlockRef block)
{
    int hash_value = get_hash_key(name, LABEL_MAX);
    sLabel* p = gLabels + hash_value;

    while(1) {
        if(p->mName == NULL) {
            p->mName = strdup(name);

            p->mBlock = block;

            return TRUE;
        }
        else {
            if(strcmp(p->mName, name) == 0) {
                p->mBlock = block;

                return TRUE;
            }
            else {
                p++;

                if(p == gLabels + LABEL_MAX) {
                    p = gLabels;
                }
                else if(p == gLabels + hash_value) {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

LLVMBasicBlockRef get_label_from_table(char* name)
{
    int hash_value = get_hash_key(name, LABEL_MAX);

    sLabel* p = gLabels + hash_value;

    while(1) {
        if(p->mName == NULL) {
            return NULL;
        }
        else if(strcmp((char*)p->mName, name) == 0) {
            return p->mBlock;
        }

        p++;

        if(p == gLabels + LABEL_MAX) {
            p = gLabels;
        }
        else if(p == gLabels + hash_value) {
            return NULL;
        }
    }
}


unsigned int sNodeTree_if_expression(unsigned int expression_node, MANAGED struct sNodeBlockStruct* if_node_block, unsigned int* elif_expression_nodes, MANAGED struct sNodeBlockStruct** elif_node_blocks, int elif_num, MANAGED struct sNodeBlockStruct* else_node_block, sParserInfo* info, char* sname, int sline)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeIf;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = sline;

    gNodes[node].uValue.sIf.mExpressionNode = expression_node;
    gNodes[node].uValue.sIf.mIfNodeBlock = MANAGED if_node_block;
    memcpy(gNodes[node].uValue.sIf.mElifExpressionNodes, elif_expression_nodes, sizeof(unsigned int)*elif_num);
    memcpy(gNodes[node].uValue.sIf.mElifNodeBlocks, MANAGED elif_node_blocks, sizeof(sNodeBlock*)*elif_num);
    gNodes[node].uValue.sIf.mElifNum = elif_num;
    gNodes[node].uValue.sIf.mElseNodeBlock = MANAGED else_node_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_if_expression(unsigned int node, sCompileInfo* info)
{
    sNodeBlock* else_node_block = gNodes[node].uValue.sIf.mElseNodeBlock;
    int elif_num = gNodes[node].uValue.sIf.mElifNum;

    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sIf.mExpressionNode;

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    sNodeType* conditional_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, conditional_type)) {
        if(!cast_right_type_to_left_type(bool_type, &conditional_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    if(!type_identify_with_class_name(conditional_type, "bool")) {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }
    LLVMBasicBlockRef cond_then_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_jump_then");

    LLVMBasicBlockRef cond_else_block = NULL;

    LLVMBasicBlockRef cond_elif_block[ELIF_NUM_MAX];
    LLVMBasicBlockRef cond_elif_then_block[ELIF_NUM_MAX];
    if(elif_num > 0) {
        int i;
        for(i=0; i<elif_num; i++) {
            char buf[128];
            snprintf(buf, 128, "cond_jump_elif%d", i);

            cond_elif_block[i] = LLVMAppendBasicBlockInContext(gContext, gFunction, buf);

            char buf2[128];
            snprintf(buf2, 128, "cond_jump_elif_then%d", i);

            cond_elif_then_block[i] = LLVMAppendBasicBlockInContext(gContext, gFunction, buf2);
        }
    }

    if(else_node_block) {
        cond_else_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_else_block");
    }
    LLVMBasicBlockRef cond_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_end");

    free_right_value_objects(info);

    if(elif_num > 0) {
        LLVMBuildCondBr(gBuilder, conditional_value.value, cond_then_block, cond_elif_block[0]);
    }
    else if(else_node_block) {
        LLVMBuildCondBr(gBuilder, conditional_value.value, cond_then_block, cond_else_block);
    }
    else {
        LLVMBuildCondBr(gBuilder, conditional_value.value, cond_then_block, cond_end_block);
    }

    llvm_change_block(cond_then_block, info);

    sNodeBlock* if_block = gNodes[node].uValue.sIf.mIfNodeBlock;

    BOOL last_expression_is_return_before = info->last_expression_is_return;
    info->last_expression_is_return = FALSE;

    if(!compile_block(if_block, info)) {
        return FALSE;
    }

    if(!info->last_expression_is_return) {
        LLVMBuildBr(gBuilder, cond_end_block);
    }

    info->last_expression_is_return = last_expression_is_return_before;

    //// elif ///
    if(elif_num > 0) {
        int i;
        for(i=0; i<elif_num; i++) {
            llvm_change_block(cond_elif_block[i], info);

            unsigned int expression_node = gNodes[node].uValue.sIf.mElifExpressionNodes[i];

            if(!compile(expression_node, info)) {
                return FALSE;
            }

            sNodeType* conditional_type = info->type;

            LVALUE conditional_value = *get_value_from_stack(-1);
            dec_stack_ptr(1, info);

            sNodeType* bool_type = create_node_type_with_class_name("bool");

            if(auto_cast_posibility(bool_type, conditional_type)) {
                if(!cast_right_type_to_left_type(bool_type, &conditional_type, &conditional_value, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            if(!type_identify_with_class_name(conditional_type, "bool")) 
            {
                compile_err_msg(info, "This conditional type is not bool");
                info->err_num++;

                info->type = create_node_type_with_class_name("int"); // dummy

                return TRUE;
            }

            free_right_value_objects(info);

            if(i == elif_num-1) {
                if(else_node_block) {
                    LLVMBuildCondBr(gBuilder, conditional_value.value, cond_elif_then_block[i], cond_else_block);
                }
                else {
                    LLVMBuildCondBr(gBuilder, conditional_value.value, cond_elif_then_block[i], cond_end_block);
                }
            }
            else {
                LLVMBuildCondBr(gBuilder, conditional_value.value, cond_elif_then_block[i], cond_elif_block[i+1]);
            }

            llvm_change_block(cond_elif_then_block[i], info);

            sNodeBlock* elif_node_block = gNodes[node].uValue.sIf.mElifNodeBlocks[i];

            BOOL last_expression_is_return_before = info->last_expression_is_return;
            info->last_expression_is_return = FALSE;

            if(!compile_block(elif_node_block, info))
            {
                return FALSE;
            }

            if(!info->last_expression_is_return) {
                LLVMBuildBr(gBuilder, cond_end_block);
            }

            info->last_expression_is_return = last_expression_is_return_before;
        }
    }

    if(else_node_block) {
        llvm_change_block(cond_else_block, info);

        BOOL last_expression_is_return_before = info->last_expression_is_return;
        info->last_expression_is_return = FALSE;

        if(!compile_block(else_node_block, info))
        {
            return FALSE;
        }

        if(!info->last_expression_is_return) {
            LLVMBuildBr(gBuilder, cond_end_block);
        }

        info->last_expression_is_return = last_expression_is_return_before;
    }

    llvm_change_block(cond_end_block, info);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_while_expression(unsigned int expression_node, MANAGED struct sNodeBlockStruct* while_node_block, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeWhile;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sWhile.mExpressionNode = expression_node;
    gNodes[node].uValue.sWhile.mWhileNodeBlock = MANAGED while_node_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_while_expression(unsigned int node, sCompileInfo* info)
{
    void* switch_expression_before = info->switch_expression;
    info->switch_expression = NULL;

    sNodeBlock* while_node_block = gNodes[node].uValue.sWhile.mWhileNodeBlock;

    LLVMBasicBlockRef loop_top_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "loop_top_block");

    LLVMBuildBr(gBuilder, loop_top_block);

    llvm_change_block(loop_top_block, info);

    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sWhile.mExpressionNode;

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    sNodeType* conditional_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, conditional_type)) {
        if(!cast_right_type_to_left_type(bool_type, &conditional_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(conditional_type, "bool")) {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    LLVMBasicBlockRef cond_then_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_then_block");

    LLVMBasicBlockRef cond_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_end_block");

    info->loop_end_block[info->num_loop] = cond_end_block;
    info->num_loop++;

    if(info->num_loop >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. while(1)", info->num_loop);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    info->loop_begin_block[info->num_loop2] = cond_then_block;
    info->num_loop2++;

    if(info->num_loop2 >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. while(2)", info->num_loop2);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    free_right_value_objects(info);

    LLVMBuildCondBr(gBuilder, conditional_value.value, cond_then_block, cond_end_block);

    llvm_change_block(cond_then_block, info);

    BOOL last_expression_is_return_before = info->last_expression_is_return;
    info->last_expression_is_return = FALSE;

    sNodeBlock* current_node_block = info->current_node_block;
    info->current_node_block = while_node_block;

    if(!compile_block(while_node_block, info)) {
        return FALSE;
    }

    info->current_node_block = current_node_block;

    if(!info->last_expression_is_return) {
        LLVMBuildBr(gBuilder, loop_top_block);
    }

    info->num_loop--;
    info->num_loop2--;

    info->last_expression_is_return = last_expression_is_return_before;

    llvm_change_block(cond_end_block, info);

    info->type = create_node_type_with_class_name("void");

    info->switch_expression = switch_expression_before;

    return TRUE;
}

unsigned int sNodeTree_do_while_expression(unsigned int expression_node, MANAGED struct sNodeBlockStruct* while_node_block, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeDoWhile;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sWhile.mExpressionNode = expression_node;
    gNodes[node].uValue.sWhile.mWhileNodeBlock = MANAGED while_node_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_do_while_expression(unsigned int node, sCompileInfo* info)
{
    void* switch_expression_before = info->switch_expression;
    info->switch_expression = NULL;

    sNodeBlock* while_node_block = gNodes[node].uValue.sWhile.mWhileNodeBlock;

    LLVMBasicBlockRef loop_top_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "loop_top_block");

    LLVMBuildBr(gBuilder, loop_top_block);

    llvm_change_block(loop_top_block, info);

    info->loop_begin_block[info->num_loop2] = loop_top_block;
    info->num_loop2++;

    if(info->num_loop2 >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. do while", info->num_loop2);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMBasicBlockRef cond_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_end_block");

    info->loop_end_block[info->num_loop] = cond_end_block;
    info->num_loop++;

    if(info->num_loop >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. do while", info->num_loop);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    BOOL last_expression_is_return_before = info->last_expression_is_return;
    info->last_expression_is_return = FALSE;

    sNodeBlock* current_node_block = info->current_node_block;
    info->current_node_block = while_node_block;

    if(!compile_block(while_node_block, info)) {
        return FALSE;
    }

    info->current_node_block = current_node_block;

    /// compile expression ///
    unsigned int expression_node = gNodes[node].uValue.sWhile.mExpressionNode;

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    sNodeType* conditional_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    LLVMBuildCondBr(gBuilder, conditional_value.value, loop_top_block, cond_end_block);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, conditional_type)) {
        if(!cast_right_type_to_left_type(bool_type, &conditional_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(conditional_type, "bool")) {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy
        return TRUE;
    }

    llvm_change_block(cond_end_block, info);

    info->type = create_node_type_with_class_name("void");

    info->switch_expression = switch_expression_before;

    return TRUE;
}

unsigned int sNodeTree_create_and_and(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeAndAnd;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_and_and(unsigned int node, sCompileInfo* info)
{
    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("bool");
    LLVMValueRef result_var = LLVMBuildAlloca(gBuilder, llvm_type, "andand");

    /// compile expression ///
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    free_right_value_objects(info);

    sNodeType* left_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, left_type)) {
        if(!cast_right_type_to_left_type(bool_type, &left_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(left_type, "bool")) {
        compile_err_msg(info, "Left expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMBuildStore(gBuilder, conditional_value.value, result_var);

    LLVMBasicBlockRef cond_then_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_jump_then");

    LLVMBasicBlockRef cond_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_jump_end");

    LLVMBuildCondBr(gBuilder, conditional_value.value, cond_then_block, cond_end_block);

    llvm_change_block(cond_then_block, info);

    /// compile right expression ///
    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    free_right_value_objects(info);

    sNodeType* right_type = info->type;

    LVALUE conditional_value2 = *get_value_from_stack(-1);

    if(auto_cast_posibility(bool_type, right_type)) {
        if(!cast_right_type_to_left_type(bool_type, &right_type, &conditional_value2, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(right_type, "bool")) {
        compile_err_msg(info, "Right expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMValueRef andand_value = LLVMBuildAnd(gBuilder, conditional_value.value, conditional_value2.value, "andand");

    LLVMBuildStore(gBuilder, andand_value, result_var);

    LLVMBuildBr(gBuilder, cond_end_block);

    llvm_change_block(cond_end_block, info);

    dec_stack_ptr(2, info);

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildLoad(gBuilder, result_var, "andand_result_value");
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = result_var;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_create_or_or(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeOrOr;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_or_or(unsigned int node, sCompileInfo* info)
{
    LLVMTypeRef llvm_type = create_llvm_type_with_class_name("bool");
    LLVMValueRef result_var = LLVMBuildAlloca(gBuilder, llvm_type, "oror");

    /// compile expression ///
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    free_right_value_objects(info);

    sNodeType* left_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, left_type)) {
        if(!cast_right_type_to_left_type(bool_type, &left_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(left_type, "bool")) {
        compile_err_msg(info, "Right expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMBuildStore(gBuilder, conditional_value.value, result_var);

    LLVMBasicBlockRef cond_then_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_jump_then");
    LLVMBasicBlockRef cond_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_jump_end");

    LLVMBuildCondBr(gBuilder, conditional_value.value, cond_end_block, cond_then_block);

    llvm_change_block(cond_then_block, info);

    /// compile right expression ///
    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    free_right_value_objects(info);

    sNodeType* right_type = info->type;

    LVALUE conditional_value2 = *get_value_from_stack(-1);

    if(auto_cast_posibility(bool_type, right_type)) {
        if(!cast_right_type_to_left_type(bool_type, &right_type, &conditional_value2, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(right_type, "bool")) {
        compile_err_msg(info, "Right expression is not bool type");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMValueRef oror_value = LLVMBuildOr(gBuilder, conditional_value.value, conditional_value2.value, "oror");

    LLVMBuildStore(gBuilder, oror_value, result_var);

    LLVMBuildBr(gBuilder, cond_end_block);

    llvm_change_block(cond_end_block, info);

    dec_stack_ptr(2, info);

    LVALUE llvm_value;
    llvm_value.value = LLVMBuildLoad(gBuilder, result_var, "oror_result_value");
    llvm_value.type = create_node_type_with_class_name("bool");
    llvm_value.address = result_var;
    llvm_value.var = NULL;
    llvm_value.binded_value = FALSE;
    llvm_value.load_field = FALSE;

    push_value_to_stack_ptr(&llvm_value, info);

    info->type = create_node_type_with_class_name("bool");

    return TRUE;
}

unsigned int sNodeTree_for_expression(unsigned int expression_node1, unsigned int expression_node2, unsigned int expression_node3, MANAGED sNodeBlock* for_node_block, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeFor;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sFor.mExpressionNode = expression_node1;
    gNodes[node].uValue.sFor.mExpressionNode2 = expression_node2;
    gNodes[node].uValue.sFor.mExpressionNode3 = expression_node3;
    gNodes[node].uValue.sFor.mForNodeBlock = MANAGED for_node_block;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_for_expression(unsigned int node, sCompileInfo* info)
{
    void* switch_expression_before = info->switch_expression;
    info->switch_expression = NULL;

    sNodeBlock* for_block = gNodes[node].uValue.sFor.mForNodeBlock;

    sVarTable* lv_table_before = info->pinfo->lv_table;
    info->pinfo->lv_table = for_block->mLVTable->mParent;

    /// compile expression ///
    int stack_num_before = info->stack_num;

    unsigned int expression_node = gNodes[node].uValue.sFor.mExpressionNode;

    if(!compile(expression_node, info)) {
        info->pinfo->lv_table = lv_table_before;
        return FALSE;
    }

    arrange_stack(info, stack_num_before);

    /// compile expression ///
    LLVMBasicBlockRef loop_top_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "loop_top_block");
    free_right_value_objects(info);

    LLVMBuildBr(gBuilder, loop_top_block);

    llvm_change_block(loop_top_block, info);

    unsigned int expression_node2 = gNodes[node].uValue.sFor.mExpressionNode2;
    stack_num_before = info->stack_num;

    if(!compile(expression_node2, info)) {
        info->pinfo->lv_table = lv_table_before;
        return FALSE;
    }

    sNodeType* conditional_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    arrange_stack(info, stack_num_before);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, conditional_type)) {
        if(!cast_right_type_to_left_type(bool_type, &conditional_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            info->pinfo->lv_table = lv_table_before;
            return TRUE;
        }
    }

    if(!type_identify_with_class_name(conditional_type, "bool")) {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        info->pinfo->lv_table = lv_table_before;
        return TRUE;
    }

    LLVMBasicBlockRef cond_then_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_then_block");

    LLVMBasicBlockRef cond_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_end_block");

    info->loop_end_block[info->num_loop] = cond_end_block;
    info->num_loop++;

    if(info->num_loop >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. for", info->num_loop);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    info->loop_begin_block[info->num_loop2] = cond_then_block;
    info->num_loop2++;

    if(info->num_loop2 >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. for", info->num_loop2);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }
    free_right_value_objects(info);

    LLVMBuildCondBr(gBuilder, conditional_value.value, cond_then_block, cond_end_block);

    llvm_change_block(cond_then_block, info);

    sNodeBlock* current_node_block = info->current_node_block;
    info->current_node_block = for_block;

    /// block of for expression ///
    if(!compile_block(for_block, info))
    {
        info->num_loop--;
        info->pinfo->lv_table = lv_table_before;
        return FALSE;
    }

    info->current_node_block = current_node_block;

    /// expression 3 ///
    unsigned int expression_node3 = gNodes[node].uValue.sFor.mExpressionNode3;

    BOOL last_expression_is_return_before = info->last_expression_is_return;
    info->last_expression_is_return = FALSE;
    stack_num_before = info->stack_num;

    if(!compile(expression_node3, info)) {
        info->pinfo->lv_table = lv_table_before;
        return FALSE;
    }

    if(!info->last_expression_is_return) {
        free_right_value_objects(info);
        LLVMBuildBr(gBuilder, loop_top_block);
    }

    arrange_stack(info, stack_num_before);

    info->last_expression_is_return = last_expression_is_return_before;

    llvm_change_block(cond_end_block, info);
    info->num_loop--;

    free_objects(info->pinfo->lv_table, info);
    info->pinfo->lv_table = lv_table_before;

    info->type = create_node_type_with_class_name("void");

    info->switch_expression = switch_expression_before;

    return TRUE;
}

unsigned int sNodeTree_create_return(unsigned int left, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeReturn;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_return(unsigned int node, sCompileInfo* info)
{
    int left_node = gNodes[node].mLeft;

    if(left_node != 0) {
        if(!compile(left_node, info)) {
            return FALSE;
        }

        LVALUE llvm_value = *get_value_from_stack(-1);

        sNodeType* right_type = clone_node_type(info->type);

        sNodeType* result_type = gComeFunction->mResultType;

        if(auto_cast_posibility(result_type, right_type))
        {
            cast_right_type_to_left_type(result_type, &right_type, &llvm_value, info);
        }

        if(llvm_value.type->mHeap) {
            remove_object_from_right_values(llvm_value.value, info);
        }

        free_right_value_objects(info);

        if(info->in_inline_function) {
            free_objects_on_return(info->function_node_block, info, llvm_value.address, FALSE);
            LLVMBuildStore(gBuilder, llvm_value.value, info->inline_result_variable);
            LLVMBuildBr(gBuilder, info->inline_func_end);
        }
        else {
            free_objects_on_return(info->function_node_block, info, llvm_value.address, TRUE);
            LLVMBuildRet(gBuilder, llvm_value.value);
        }

        dec_stack_ptr(1, info);
    }
    else {
        free_right_value_objects(info);

        if(info->in_inline_function) {
            free_objects_on_return(info->function_node_block, info, NULL, FALSE);
            LLVMBuildBr(gBuilder, info->inline_func_end);
        }
        else {
            free_objects_on_return(info->function_node_block, info, NULL, TRUE);
            LLVMBuildRet(gBuilder, NULL);
        }

        info->type = create_node_type_with_class_name("void");
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_create_nodes(unsigned int* nodes, int num_nodes, sParserInfo* info)
{
    unsigned node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeNodes;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    memcpy(gNodes[node].uValue.sNodes.mNodes, nodes, sizeof(unsigned int)*NODES_MAX);
    gNodes[node].uValue.sNodes.mNumNodes = num_nodes;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_nodes(unsigned int node, sCompileInfo* info)
{
    unsigned int* nodes = gNodes[node].uValue.sNodes.mNodes;
    int num_nodes = gNodes[node].uValue.sNodes.mNumNodes;

    int stack_num_before = info->stack_num;

    int i;
    for(i=0; i<num_nodes; i++) {
        unsigned int node = nodes[i];

        xstrncpy(info->sname, gNodes[node].mSName, PATH_MAX);
        info->sline = gNodes[node].mLine;

        if(gNCDebug && !info->in_generics_function && !info->in_inline_function && !info->in_lambda_function) {
            setCurrentDebugLocation(info->sline, info);
        }

        if(!compile(node, info)) {
            return FALSE;
        }

        arrange_stack(info, stack_num_before);
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_create_normal_block(struct sNodeBlockStruct* node_block, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeNormalBlock;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sNormalBlock.mNodeBlock = node_block;
    gNodes[node].uValue.sNormalBlock.mHeap = FALSE;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_normal_block(unsigned int node, sCompileInfo* info)
{
    struct sNodeBlockStruct* node_block = gNodes[node].uValue.sNormalBlock.mNodeBlock;

    if(!compile_block(node_block, info)) {
        return FALSE;
    }

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_switch_expression(unsigned int expression_node, int num_switch_expression, MANAGED unsigned int* switch_expression, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeSwitch;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sSwitch.mExpression = expression_node;
    gNodes[node].uValue.sSwitch.mSwitchExpression = MANAGED switch_expression;
    gNodes[node].uValue.sSwitch.mNumSwitchExpression = num_switch_expression;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_switch_expression(unsigned int node, sCompileInfo* info)
{
    unsigned int* switch_expression = gNodes[node].uValue.sSwitch.mSwitchExpression;
    int num_switch_expression = gNodes[node].uValue.sSwitch.mNumSwitchExpression;
    unsigned int expression_node = gNodes[node].uValue.sSwitch.mExpression;
    LLVMBasicBlockRef loop_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "end_block");

    info->loop_end_block[info->num_loop] = loop_end_block;
    info->num_loop++;

    if(info->num_loop >= LOOP_NEST_MAX) {
        compile_err_msg(info, "Over flow loop number. Loop number is %d. switch", info->num_loop);
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    if(!compile(expression_node, info)) {
        return FALSE;
    }

    void* switch_expression_before = info->switch_expression;
    info->switch_expression = get_value_from_stack(-1)->value;
    sNodeType* switch_expression_type_before = info->switch_expression_type;
    info->switch_expression_type = clone_node_type(get_value_from_stack(-1)->type);
    dec_stack_ptr(1, info);

    info->case_else_block = NULL;

    int i;
    unsigned int node2;
    for(i=0; i<num_switch_expression; i++) {
        int sline = info->sline;
        gNodes[node].mLine = info->sline;
        
        /// compile node ///
        node2 = switch_expression[i];
        
        info->sline = gNodes[node2].mLine;

        if(!compile(node2, info)) {
            info->num_loop--;
            return FALSE;
        }
    }

    LLVMBasicBlockRef case_else_block;
    if(gNodes[node2].mNodeType == kNodeTypeReturn) {
        case_else_block = NULL;
    }
    else {
        case_else_block = (LLVMBasicBlockRef)info->case_else_block;
    }

    if(case_else_block) {
        LLVMBuildBr(gBuilder, case_else_block);

        llvm_change_block(case_else_block, info);
    }

    info->switch_expression = switch_expression_before;
    info->switch_expression_type = switch_expression_type_before;

    LLVMBuildBr(gBuilder, loop_end_block);

    llvm_change_block(loop_end_block, info);

    info->type = create_node_type_with_class_name("void");

    info->case_else_block = NULL;

    info->num_loop--;

    return TRUE;
}

unsigned int sNodeTree_case_expression(unsigned int expression_node, BOOL last_case, BOOL case_after_return, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeCase;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].uValue.sCase.mExpression = expression_node;
    gNodes[node].uValue.sCase.mLastCase = last_case;
    gNodes[node].uValue.sCase.mFirstCase = FALSE;
    gNodes[node].uValue.sCase.mCaseAfterReturn = case_after_return;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_case_expression(unsigned int node, sCompileInfo* info)
{
    unsigned int expression_node = gNodes[node].uValue.sCase.mExpression;
    BOOL first_case = gNodes[node].uValue.sCase.mFirstCase;
    BOOL last_case = gNodes[node].uValue.sCase.mLastCase;
    BOOL case_after_return = gNodes[node].uValue.sCase.mCaseAfterReturn;

    LLVMBasicBlockRef cond_then_block;
    if(first_case) {
        cond_then_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_then_block");
        info->case_then_block = cond_then_block;
    }
    else {
        cond_then_block = (LLVMBasicBlockRef)info->case_then_block;
    }
    LLVMBasicBlockRef cond_else_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_else_block");

    LLVMBasicBlockRef case_else_block = (LLVMBasicBlockRef)info->case_else_block;

    if(case_else_block) {
        if(first_case && !case_after_return) {
            LLVMBuildBr(gBuilder, case_else_block);
        }

        llvm_change_block(case_else_block, info);
    }

    if(expression_node == 0) {
        LLVMBuildBr(gBuilder, cond_then_block);
    }
    else {
        if(!compile(expression_node, info)) {
            return FALSE;
        }

        LVALUE rvalue = *get_value_from_stack(-1);

        dec_stack_ptr(1, info);
        LLVMValueRef lvalue = (LLVMValueRef)info->switch_expression;
        sNodeType* left_type = info->switch_expression_type;

        if(lvalue == NULL) {
            compile_err_msg(info, "No in the switch.");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }

        if(auto_cast_posibility(left_type, rvalue.type))
        {
            cast_right_type_to_left_type(left_type, &rvalue.type, &rvalue, info);
        }

        LLVMValueRef conditional_value = LLVMBuildICmp(gBuilder, LLVMIntEQ, lvalue, rvalue.value, "eqtmp");
        LLVMBuildCondBr(gBuilder, conditional_value, cond_then_block, cond_else_block);
    }

    if(last_case) {
        llvm_change_block(cond_then_block, info);
    }

    info->case_else_block = cond_else_block;

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_create_break_expression(sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeBreak;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_break_expression(unsigned int node, sCompileInfo* info)
{
    if(info->num_loop <= 0) {
        compile_err_msg(info, "No in the loop");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMBasicBlockRef loop_end_block = (LLVMBasicBlockRef)info->loop_end_block[info->num_loop-1];
    //info->num_loop--;

    if(info->switch_expression == NULL && info->current_node_block) {
        free_objects_on_return(info->current_node_block, info, NULL, TRUE);
    }
    free_right_value_objects(info);

    LLVMBuildBr(gBuilder, loop_end_block);

    LLVMBasicBlockRef after_break = LLVMAppendBasicBlockInContext(gContext, gFunction, "after_break");

    llvm_change_block(after_break, info);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_create_continue_expression(sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeContinue;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_continue_expression(unsigned int node, sCompileInfo* info)
{
    if(info->num_loop2 <= 0) {
        compile_err_msg(info, "No in the loop");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    LLVMBasicBlockRef loop_begin_block = (LLVMBasicBlockRef)info->loop_begin_block[info->num_loop2-1];
    info->num_loop2--;

    free_right_value_objects(info);
    LLVMBuildBr(gBuilder, loop_begin_block);

    LLVMBasicBlockRef after_continue = LLVMAppendBasicBlockInContext(gContext, gFunction, "after_continue");

    llvm_change_block(after_continue, info);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_label_expression(char* name, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeLabel;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sLabel.mName, name, PATH_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_label_expression(unsigned int node, sCompileInfo* info)
{
    char* label_name = gNodes[node].uValue.sLabel.mName;

    LLVMBasicBlockRef block = get_label_from_table(label_name);
    
    if(block == NULL) {
        block = LLVMAppendBasicBlockInContext(gContext, gFunction, label_name);
        if(!add_label_to_table(label_name, block)) {
            fprintf(stderr, "overflow label max\n");
            return FALSE;
        }
    }

    free_right_value_objects(info);
    LLVMBuildBr(gBuilder, block);

    llvm_change_block(block, info);

    info->type = create_node_type_with_class_name("void");

    return TRUE;
}

unsigned int sNodeTree_goto_expression(char* name, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeGoto;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    xstrncpy(gNodes[node].uValue.sGoto.mName, name, PATH_MAX);

    gNodes[node].mLeft = 0;
    gNodes[node].mRight = 0;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_goto_expression(unsigned int node, sCompileInfo* info)
{
    char* label_name = gNodes[node].uValue.sGoto.mName;

    LLVMBasicBlockRef block = get_label_from_table(label_name);
    
    if(block == NULL) {
        compile_err_msg(info, "no label");

        return FALSE;
    }

    free_right_value_objects(info);
    LLVMBuildBr(gBuilder, block);

    LLVMBasicBlockRef block2 = LLVMAppendBasicBlockInContext(gContext, gFunction, "after goto");

    llvm_change_block(block2, info);

    return TRUE;
}

unsigned int sNodeTree_create_conditional(unsigned int conditional, unsigned int value1, unsigned int value2, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeConditional;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = conditional;
    gNodes[node].mRight = value1;
    gNodes[node].mMiddle = value2;

    return node;
}

BOOL compile_conditional(unsigned int node, sCompileInfo* info)
{
    /// compile expression ///
    unsigned int conditional_node = gNodes[node].mLeft;

    if(!compile(conditional_node, info)) 
    {
        return FALSE;
    }

    sNodeType* conditional_type = info->type;

    LVALUE conditional_value = *get_value_from_stack(-1);
    dec_stack_ptr(1, info);

    sNodeType* bool_type = create_node_type_with_class_name("bool");

    if(auto_cast_posibility(bool_type, conditional_type)) 
    {
        if(!cast_right_type_to_left_type(bool_type, &conditional_type, &conditional_value, info))
        {
            compile_err_msg(info, "Cast failed");
            info->err_num++;

            info->type = create_node_type_with_class_name("int"); // dummy

            return TRUE;
        }
    }

    if(!type_identify_with_class_name(conditional_type, "bool")) 
    {
        compile_err_msg(info, "This conditional type is not bool");
        info->err_num++;

        info->type = create_node_type_with_class_name("int"); // dummy

        return TRUE;
    }

    int compile_time_value = -1;

    if(LLVMIsConstant(conditional_value.value)) {
        compile_time_value = LLVMConstIntGetZExtValue(conditional_value.value);
    }

    LVALUE llvm_value;
    if(compile_time_value != -1) {
        if(compile_time_value) {
            unsigned int value1_node  = gNodes[node].mRight;

            if(!compile(value1_node, info)) 
            {
                return FALSE;
            }
        }
        else {
            unsigned int value2_node  = gNodes[node].mMiddle;

            if(!compile(value2_node, info)) 
            {
                return FALSE;
            }
        }

        if(type_identify_with_class_name(info->type, "void")) {
            memset(&llvm_value, 0, sizeof(LVALUE));
        }
        else {
            llvm_value = *get_value_from_stack(-1);
        }
    }
    else {
        LLVMBasicBlockRef cond_then_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_jump_then");
        LLVMBasicBlockRef cond_else_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_else_block");

        LLVMBasicBlockRef cond_end_block = LLVMAppendBasicBlockInContext(gContext, gFunction, "cond_end");
        free_right_value_objects(info);

        LLVMBuildCondBr(gBuilder, conditional_value.value, cond_then_block, cond_else_block);

        llvm_change_block(cond_then_block, info);

        unsigned int value1_node  = gNodes[node].mRight;

        if(!compile(value1_node, info)) 
        {
            return FALSE;
        }


        sNodeType* value1_result_type = clone_node_type(info->type);

        free_right_value_objects(info);
        LVALUE value1;
        LLVMValueRef result_value;
        int result_value_alignment;
        if(type_identify_with_class_name(value1_result_type, "void")) {
            memset(&value1, 0, sizeof(LVALUE));

            value1_result_type = create_node_type_with_class_name("int");

            LLVMBasicBlockRef this_block = LLVMGetInsertBlock(gBuilder);
            LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(gFunction);
            LLVMValueRef inst = LLVMGetFirstInstruction(entry_block);
            LLVMPositionBuilderBefore(gBuilder, inst);

            LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(value1_result_type);

            result_value = LLVMBuildAlloca(gBuilder, llvm_result_type, "conditional_result_type");

            llvm_change_block(this_block, info);

            LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");
            LLVMValueRef zero_value = LLVMConstInt(llvm_type, 0, FALSE);

            LLVMBuildStore(gBuilder, zero_value, result_value);
        }
        else {
            LVALUE value1 = *get_value_from_stack(-1);
            dec_stack_ptr(1, info);

            value1_result_type = clone_node_type(info->type);

            LLVMBasicBlockRef this_block = LLVMGetInsertBlock(gBuilder);
            LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(gFunction);
            LLVMValueRef inst = LLVMGetFirstInstruction(entry_block);
            LLVMPositionBuilderBefore(gBuilder, inst);

            LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(value1_result_type);

            result_value = LLVMBuildAlloca(gBuilder, llvm_result_type, "condtional_result_value");

            llvm_change_block(this_block, info);

            LLVMBuildStore(gBuilder, value1.value, result_value);
        }

        LLVMBuildBr(gBuilder, cond_end_block);

        llvm_change_block(cond_else_block, info);

        unsigned int value2_node  = gNodes[node].mMiddle;

        if(!compile(value2_node, info)) 
        {
            return FALSE;
        }
        free_right_value_objects(info);

        LVALUE value2;
        if(type_identify_with_class_name(info->type, "void")) {
            memset(&value2, 0, sizeof(LVALUE));

            sNodeType* value2_result_type = create_node_type_with_class_name("int");

            LLVMTypeRef llvm_result_type = create_llvm_type_from_node_type(value2_result_type);

            LLVMTypeRef llvm_type = create_llvm_type_with_class_name("int");
            LLVMValueRef zero_value = LLVMConstInt(llvm_type, 0, FALSE);

            if(auto_cast_posibility(value1_result_type, value2_result_type)) 
            {
                if(!cast_right_type_to_left_type(value1_result_type
                                , &value2_result_type, &value2, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            LLVMBuildStore(gBuilder, zero_value, result_value);
        }
        else {
            value2 = *get_value_from_stack(-1);
            dec_stack_ptr(1, info);
            sNodeType* value2_result_type = clone_node_type(info->type);

            if(auto_cast_posibility(value1_result_type, value2_result_type)) 
            {
                if(!cast_right_type_to_left_type(value1_result_type
                                , &value2_result_type, &value2, info))
                {
                    compile_err_msg(info, "Cast failed");
                    info->err_num++;

                    info->type = create_node_type_with_class_name("int"); // dummy

                    return TRUE;
                }
            }

            LLVMBuildStore(gBuilder, value2.value, result_value);
        }

        LLVMBuildBr(gBuilder, cond_end_block);

        llvm_change_block(cond_end_block, info);

        llvm_value.value = LLVMBuildLoad(gBuilder, result_value, "conditional_result_value");
        llvm_value.type = clone_node_type(value1_result_type);
        llvm_value.address = NULL;
        llvm_value.var = NULL;
        llvm_value.binded_value = FALSE;
        llvm_value.load_field = FALSE;

        info->type = clone_node_type(value1_result_type);

        push_value_to_stack_ptr(&llvm_value, info);
    }

    return TRUE;
}

unsigned int sNodeTree_create_comma(unsigned int left_node, unsigned int right_node, sParserInfo* info)
{
    unsigned int node = alloc_node();

    gNodes[node].mNodeType = kNodeTypeComma;

    xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);
    gNodes[node].mLine = info->sline;

    gNodes[node].mLeft = left_node;
    gNodes[node].mRight = right_node;
    gNodes[node].mMiddle = 0;

    return node;
}

BOOL compile_comma(unsigned int node, sCompileInfo* info)
{
    unsigned int left_node = gNodes[node].mLeft;

    if(!compile(left_node, info)) {
        return FALSE;
    }

    sNodeType* left_type = info->type;

    if(!type_identify_with_class_name(info->type, "void")) {
        dec_stack_ptr(1, info);
    }

    unsigned int right_node = gNodes[node].mRight;

    if(!compile(right_node, info)) {
        return FALSE;
    }

    return TRUE;
}
