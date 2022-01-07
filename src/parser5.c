#include "common.h"
#include <ctype.h>

BOOL postposition_operator(unsigned int* node, BOOL enable_assginment, sParserInfo* info)
{
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        char c = *(info->p+1);
        /// call method or access field ///
        if(*info->p == '.' || (*info->p == '-' && *(info->p+1) == '>'))
        {
            if(!parse_sharp(info)) {
                return FALSE;
            }
            if(*info->p == '-') {
                info->p+=2;
                skip_spaces_and_lf(info);
            }
            else {
                info->p++;
                skip_spaces_and_lf(info);
            }
            if(!parse_sharp(info)) {
                return FALSE;
            }

            if(xisalpha(*info->p) || *info->p == '_') 
            {
                char buf[VAR_NAME_MAX];

                if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
                    return FALSE;
                }
                skip_spaces_and_lf(info);

                if(!parse_sharp(info)) {
                    return FALSE;
                }

                BOOL type_name_after_word = FALSE;

                char* p = info->p;
                int sline = info->sline;

                char buf2[VAR_NAME_MAX];

                if(!parse_word(buf2, VAR_NAME_MAX, info, FALSE, FALSE)) {
                    return FALSE;
                }

                if(is_type_name(buf2, info)) {
                    type_name_after_word = TRUE;
                }

                info->p = p;
                info->sline = sline;

                /// call methods ///
                if(*info->p == '(' || *info->p == '{' || type_name_after_word) {
                    char* fun_name = buf;

                    unsigned int params[PARAMS_MAX];
                    int num_params = 0;

                    params[0] = *node;
                    num_params++;

                    if(!parse_funcation_call_params(&num_params, params, info)) 
                    {
                        return FALSE;
                    };

                    *node = sNodeTree_create_function_call(fun_name, params, num_params, TRUE, FALSE, info->mFunVersion, info);
                }
                /// access fields ///
                else {
                    if(enable_assginment && *info->p == '=' && *(info->p +1) != '=') {
                        info->p++;
                        skip_spaces_and_lf(info);

                        char var_name[VAR_NAME_MAX];
                        xstrncpy(var_name, buf, VAR_NAME_MAX);

                        unsigned int right_node = 0;

                        if(!expression(&right_node, FALSE, info)) {
                            return FALSE;
                        }

                        if(right_node == 0) {
                            parser_err_msg(info, "Require right value");
                            info->err_num++;

                            *node = 0;
                        }
                        else {
                            *node = sNodeTree_create_store_field(var_name, *node, right_node, info);
                        }
                    }
                    else {
                        unsigned int obj_node = *node;

                        if(*info->p == '+' && *(info->p+1) == '+')
                        {
                            info->p+=2;
                            skip_spaces_and_lf(info);

                            char var_name[VAR_NAME_MAX];
                            xstrncpy(var_name, buf, VAR_NAME_MAX);

                            *node = sNodeTree_create_load_field(buf, obj_node, info);

                            unsigned int field_node = *node;
                            unsigned int right_node = sNodeTree_create_int_value(1, info);

                            *node = sNodeTree_create_add(field_node, right_node, 0, info);
                            *node = sNodeTree_create_store_field(var_name, obj_node, *node, info);
                            *node = sNodeTree_create_sub(*node, right_node, 0, info);
                        }
                        else if(*info->p == '-' && *(info->p+1) == '-')
                        {
                            info->p+=2;
                            skip_spaces_and_lf(info);

                            char var_name[VAR_NAME_MAX];
                            xstrncpy(var_name, buf, VAR_NAME_MAX);

                            *node = sNodeTree_create_load_field(buf, obj_node, info);

                            unsigned int field_node = *node;
                            unsigned int right_node = sNodeTree_create_int_value(1, info);

                            *node = sNodeTree_create_sub(field_node, right_node, 0, info);
                            *node = sNodeTree_create_store_field(var_name, obj_node, *node, info);
                            *node = sNodeTree_create_add(*node, right_node, 0, info);
                        }
                        else if(enable_assginment && *info->p == '+' && *(info->p+1) == '=')
                        {
                            info->p+=2;
                            skip_spaces_and_lf(info);
                            unsigned int right_node = 0;
                            if(!expression(&right_node, FALSE, info)) {
                                return FALSE;
                            }

                            char var_name[VAR_NAME_MAX];
                            xstrncpy(var_name, buf, VAR_NAME_MAX);

                            unsigned int field_node = sNodeTree_create_load_field(buf, obj_node, info);

                            *node = sNodeTree_create_add(field_node, right_node, 0, info);
                            *node = sNodeTree_create_store_field(var_name, obj_node, *node, info);
                        }
                        else if(enable_assginment && *info->p == '-' && *(info->p+1) == '=')
                        {
                            info->p+=2;
                            skip_spaces_and_lf(info);
                            unsigned int right_node = 0;
                            if(!expression(&right_node, FALSE, info)) {
                                return FALSE;
                            }

                            char var_name[VAR_NAME_MAX];
                            xstrncpy(var_name, buf, VAR_NAME_MAX);

                            *node = sNodeTree_create_load_field(buf, obj_node, info);

                            unsigned int field_node = *node;

                            *node = sNodeTree_create_sub(field_node, right_node, 0, info);
                            *node = sNodeTree_create_store_field(var_name, obj_node, *node, info);
                        }
                        else if(enable_assginment && *info->p == '*' && *(info->p+1) == '=')
                        {
                            info->p+=2;
                            skip_spaces_and_lf(info);
                            unsigned int right_node = 0;
                            if(!expression(&right_node, FALSE, info)) {
                                return FALSE;
                            }

                            char var_name[VAR_NAME_MAX];
                            xstrncpy(var_name, buf, VAR_NAME_MAX);

                            *node = sNodeTree_create_load_field(buf, obj_node, info);

                            unsigned int field_node = *node;

                            *node = sNodeTree_create_mult(field_node, right_node, 0, info);
                            *node = sNodeTree_create_store_field(var_name, obj_node, *node, info);
                        }
                        else if(enable_assginment && *info->p == '/' && *(info->p+1) == '=')
                        {
                            info->p+=2;
                            skip_spaces_and_lf(info);
                            unsigned int right_node = 0;
                            if(!expression(&right_node, FALSE, info)) {
                                return FALSE;
                            }

                            char var_name[VAR_NAME_MAX];
                            xstrncpy(var_name, buf, VAR_NAME_MAX);

                            *node = sNodeTree_create_load_field(buf, obj_node, info);

                            unsigned int field_node = *node;

                            *node = sNodeTree_create_div(field_node, right_node, 0, info);
                            *node = sNodeTree_create_store_field(var_name, obj_node, *node, info);
                        }
                        else if(enable_assginment && *info->p == '%' && *(info->p+1) == '=')
                        {
                            info->p+=2;
                            skip_spaces_and_lf(info);
                            unsigned int right_node = 0;
                            if(!expression(&right_node, FALSE, info)) {
                                return FALSE;
                            }

                            char var_name[VAR_NAME_MAX];
                            xstrncpy(var_name, buf, VAR_NAME_MAX);

                            *node = sNodeTree_create_load_field(buf, obj_node, info);

                            unsigned int field_node = *node;

                            *node = sNodeTree_create_mod(field_node, right_node, 0, info);
                            *node = sNodeTree_create_store_field(var_name, obj_node, *node, info);
                        }
                        else if(enable_assginment && *info->p == '<' && *(info->p+1) == '<' && *(info->p+2) == '=')
                        {
                            info->p+=3;
                            skip_spaces_and_lf(info);
                            unsigned int right_node = 0;
                            if(!expression(&right_node, FALSE, info)) {
                                return FALSE;
                            }

                            char var_name[VAR_NAME_MAX];
                            xstrncpy(var_name, buf, VAR_NAME_MAX);

                            *node = sNodeTree_create_load_field(buf, obj_node, info);

                            unsigned int field_node = *node;

                            *node = sNodeTree_create_left_shift(field_node, right_node, 0, info);
                            *node = sNodeTree_create_store_field(var_name, obj_node, *node, info);
                        }
                        else if(enable_assginment && *info->p == '>' && *(info->p+1) == '>' && *(info->p+2) == '=')
                        {
                            info->p+=3;
                            skip_spaces_and_lf(info);
                            unsigned int right_node = 0;
                            if(!expression(&right_node, FALSE, info)) {
                                return FALSE;
                            }

                            char var_name[VAR_NAME_MAX];
                            xstrncpy(var_name, buf, VAR_NAME_MAX);

                            *node = sNodeTree_create_load_field(buf, obj_node, info);

                            unsigned int field_node = *node;

                            *node = sNodeTree_create_right_shift(field_node, right_node, 0, info);
                            *node = sNodeTree_create_store_field(var_name, obj_node, *node, info);
                        }
                        else if(enable_assginment && *info->p == '&' && *(info->p+1) == '=')
                        {
                            info->p+=2;
                            skip_spaces_and_lf(info);
                            unsigned int right_node = 0;
                            if(!expression(&right_node, FALSE, info)) {
                                return FALSE;
                            }

                            char var_name[VAR_NAME_MAX];
                            xstrncpy(var_name, buf, VAR_NAME_MAX);

                            *node = sNodeTree_create_load_field(buf, obj_node, info);

                            unsigned int field_node = *node;

                            *node = sNodeTree_create_and(field_node, right_node, 0, info);
                            *node = sNodeTree_create_store_field(var_name, obj_node, *node, info);
                        }
                        else if(enable_assginment && *info->p == '^' && *(info->p+1) == '=')
                        {
                            info->p+=2;
                            skip_spaces_and_lf(info);
                            unsigned int right_node = 0;
                            if(!expression(&right_node, FALSE, info)) {
                                return FALSE;
                            }

                            char var_name[VAR_NAME_MAX];
                            xstrncpy(var_name, buf, VAR_NAME_MAX);

                            *node = sNodeTree_create_load_field(buf, obj_node, info);

                            unsigned int field_node = *node;

                            *node = sNodeTree_create_xor(field_node, right_node, 0, info);
                            *node = sNodeTree_create_store_field(var_name, obj_node, *node, info);
                        }
                        else if(enable_assginment && *info->p == '|' && *(info->p+1) == '=')
                        {
                            info->p+=2;
                            skip_spaces_and_lf(info);
                            unsigned int right_node = 0;
                            if(!expression(&right_node, FALSE, info)) {
                                return FALSE;
                            }

                            char var_name[VAR_NAME_MAX];
                            xstrncpy(var_name, buf, VAR_NAME_MAX);

                            *node = sNodeTree_create_load_field(buf, obj_node, info);

                            unsigned int field_node = *node;

                            *node = sNodeTree_create_or(field_node, right_node, 0, info);
                            *node = sNodeTree_create_store_field(var_name, obj_node, *node, info);
                        }
                        else if(*info->p == '-' && *(info->p+1) == '>' && *(info->p+2) == '(')
                        {
                            info->p+=2;

                            unsigned int params[PARAMS_MAX];
                            int num_params = 0;

                            if(!parse_funcation_call_params(&num_params, params, info)) 
                            {
                                return FALSE;
                            };

                            *node = sNodeTree_create_load_field(buf, obj_node, info);

                            *node = sNodeTree_create_lambda_call(*node, params, num_params, info);

                        }
                        else {
                            *node = sNodeTree_create_load_field(buf, obj_node, info);
                        }
                    }
                }
            }
            else if(!(c >= '0' && c <= '9')) {
                char msg[1024];
                snprintf(msg, 1024, "require method name or field name after . (%c)", *info->p);
                parser_err_msg(info, msg);
                info->err_num++;
                *node = 0;
                break;
            }
        }
        /// access element ///
        else if(*info->p == '[') {
            int num_dimention = 0;
            unsigned int index_node[ARRAY_DIMENTION_MAX];

            while(*info->p == '[') {
                info->p++;
                skip_spaces_and_lf(info);

                if(!expression(&index_node[num_dimention], TRUE, info)) {
                    return FALSE;
                }

                if(index_node[num_dimention] == 0) {
                    parser_err_msg(info, "Require index value");
                    info->err_num++;

                    *node = 0;
                    break;
                }

                num_dimention++;

                if(num_dimention >= ARRAY_DIMENTION_MAX) {
                    parser_err_msg(info, "Ovewflow array dimetion");
                    return FALSE;
                }

                expect_next_character_with_one_forward("]", info);
            }

            if(enable_assginment && *info->p == '=' && *(info->p+1) != '=') {
                info->p++;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;

                if(!expression(&right_node, FALSE, info)) {
                    return FALSE;
                }

                if(right_node == 0) {
                    parser_err_msg(info, "Require right value");
                    info->err_num++;

                    *node = 0;
                }
                else {
                    *node = sNodeTree_create_store_element(*node, index_node, num_dimention, right_node, info);
                }
            }
            else {
                *node = sNodeTree_create_load_array_element(*node, index_node, num_dimention, info);
            }
        }
        /// access channel ///
        else if(*info->p == '@') {
            info->p++;
            skip_spaces_and_lf(info);

            int num;
            if(*info->p == '0') {
                info->p++;
                skip_spaces_and_lf(info);

                num = 0;
            }
            else if(*info->p == '1') {
                info->p++;
                skip_spaces_and_lf(info);

                num = 1;
            }
            else {
                parser_err_msg(info, "invalid channel element");
                return FALSE;
            }

            *node = sNodeTree_create_load_channel_element(*node, num, info);
        }
        else if(*info->p == '+' && *(info->p+1) == '+')
        {
            info->p+=2;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_plus_plus(*node, info);
        }
        else if(*info->p == '-' && *(info->p+1) == '-')
        {
            info->p+=2;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_minus_minus(*node, info);
        }
        else if(enable_assginment && *info->p == '+' && *(info->p+1) == '=')
        {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right_node = 0;
            if(!expression(&right_node, FALSE, info)) {
                return FALSE;
            };

            *node  = sNodeTree_create_equal_plus(*node, right_node, info);
        }
        else if(enable_assginment && *info->p == '-' && *(info->p+1) == '=')
        {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right_node = 0;
            if(!expression(&right_node, FALSE, info)) {
                return FALSE;
            };

            *node = sNodeTree_create_equal_minus(*node, right_node, info);
        }
        else if(enable_assginment && *info->p == '*' && *(info->p+1) == '=')
        {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right_node = 0;
            if(!expression(&right_node, FALSE, info)) {
                return FALSE;
            };

            *node  = sNodeTree_create_equal_mult(*node, right_node, info);
        }
        else if(enable_assginment && *info->p == '/' && *(info->p+1) == '=')
        {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right_node = 0;
            if(!expression(&right_node, FALSE, info)) {
                return FALSE;
            };

            *node  = sNodeTree_create_equal_div(*node, right_node, info);
        }
        else if(enable_assginment && *info->p == '%' && *(info->p+1) == '=')
        {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right_node = 0;
            if(!expression(&right_node, FALSE, info)) {
                return FALSE;
            };

            *node  = sNodeTree_create_equal_mod(*node, right_node, info);
        }
        else if(enable_assginment && *info->p == '<' && *(info->p+1) == '<' && *(info->p+2) == '=')
        {
            info->p+=3;
            skip_spaces_and_lf(info);

            unsigned int right_node = 0;
            if(!expression(&right_node, FALSE, info)) {
                return FALSE;
            };

            *node  = sNodeTree_create_equal_lshift(*node, right_node, info);
        }
        else if(enable_assginment && *info->p == '>' && *(info->p+1) == '>' && *(info->p+2) == '=')
        {
            info->p+=3;
            skip_spaces_and_lf(info);

            unsigned int right_node = 0;
            if(!expression(&right_node, FALSE, info)) {
                return FALSE;
            };

            *node = sNodeTree_create_equal_rshift(*node, right_node, info);
        }
        else if(enable_assginment && *info->p == '&' && *(info->p+1) == '=')
        {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right_node = 0;
            if(!expression(&right_node, FALSE, info)) {
                return FALSE;
            };

            *node = sNodeTree_create_equal_and(*node, right_node, info);
        }
        else if(enable_assginment && *info->p == '^' && *(info->p+1) == '=')
        {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right_node = 0;
            if(!expression(&right_node, FALSE, info)) {
                return FALSE;
            };

            *node = sNodeTree_create_equal_xor(*node, right_node, info);
        }
        else if(enable_assginment && *info->p == '|' && *(info->p+1) == '=')
        {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right_node = 0;
            if(!expression(&right_node, FALSE, info)) {
                return FALSE;
            };

            *node = sNodeTree_create_equal_or(*node, right_node, info);
        }
        else {
            break;
        }
    }

    if(!parse_sharp(info)) {
        return FALSE;
    }

    return TRUE;
}

BOOL parse_while(unsigned int* node, sParserInfo* info)
{
    expect_next_character_with_one_forward("(", info);

    /// expression ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, TRUE, info)) {
        return FALSE;
    }

    if(expression_node == 0) {
        parser_err_msg(info, "require expression for while");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(")", info);

    sNodeBlock* while_node_block = NULL;
    if(!parse_block_easy(ALLOC &while_node_block, FALSE, info))
    {
        return FALSE;
    };


    *node = sNodeTree_while_expression(expression_node, MANAGED while_node_block, info);

    return TRUE;
}

BOOL parse_do(unsigned int* node, sParserInfo* info)
{
    sNodeBlock* while_node_block = NULL;
    if(!parse_block_easy(ALLOC &while_node_block, FALSE, info))
    {
        return FALSE;
    }
    
    char buf[VAR_NAME_MAX];
    if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    if(strcmp(buf, "while") != 0) {
        parser_err_msg(info, "require while word");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward("(", info);

    /// expression ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, TRUE, info)) {
        return FALSE;
    }

    if(expression_node == 0) {
        parser_err_msg(info, "require expression for do while");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(")", info);

    *node = sNodeTree_do_while_expression(expression_node, MANAGED while_node_block, info);

    return TRUE;
}

BOOL parse_for(unsigned int* node, sParserInfo* info)
{
    sVarTable* old_vtable = info->lv_table;
    info->lv_table = init_block_vtable(old_vtable, FALSE);
    
    expect_next_character_with_one_forward("(", info);

    /// expression1 ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, TRUE, info)) {
        return FALSE;
    }

    if(expression_node == 0) {
        parser_err_msg(info, "require expression for \"for\"");
        info->err_num++;
        return TRUE;
    }

    if(*info->p == ';') {
        expect_next_character_with_one_forward(";", info);
    }
    else {
        *node = expression_node;
        return TRUE;
    }

    /// expression2 ///
    unsigned int expression_node2 = 0;
    if(!expression(&expression_node2, TRUE, info)) {
        return FALSE;
    }

    if(expression_node2 == 0) {
        parser_err_msg(info, "require expression2 for \"for\"");
        info->err_num++;
        return TRUE;
    }

    if(*info->p == ';') {
        expect_next_character_with_one_forward(";", info);
    }
    else {
        *node = expression_node2;
        return TRUE;
    }

    /// expression3 ///
    unsigned int expression_node3 = 0;
    if(!expression(&expression_node3, TRUE, info)) {
        return FALSE;
    }

    if(expression_node3 == 0) {
        parser_err_msg(info, "require expression3 for \"for\"");
        info->err_num++;
        return TRUE;
    }

    if(*info->p == ')') {
        expect_next_character_with_one_forward(")", info);
    }
    else {
        *node = expression_node3;
        return TRUE;
    }

    BOOL single_expression = FALSE;
    if(*info->p == '{') {
        info->p++;
    }
    else {
        single_expression = TRUE;
    }

    sVarTable* old_vtable2 = info->lv_table;
    info->lv_table = init_block_vtable(old_vtable2, FALSE);

    sNodeBlock* for_node_block = ALLOC sNodeBlock_alloc();
    if(!parse_block(for_node_block, FALSE, single_expression, info)) 
    {
        return FALSE;
    }

    if(!single_expression) {
        if(gNCType) {
            if(*info->p != '\0') {
                expect_next_character_with_one_forward("}", info);
            }
        }
        else {
            expect_next_character_with_one_forward("}", info);
        }
    }

    *node = sNodeTree_for_expression(expression_node, expression_node2, expression_node3, MANAGED for_node_block, info);

    info->lv_table = old_vtable;

    return TRUE;
}

BOOL parse_select(unsigned int* node, sParserInfo* info)
{
    int num_pipes = 0;
    char pipes[SELECT_MAX][VAR_NAME_MAX+1];
    sNodeBlock* pipe_blocks[SELECT_MAX];

    expect_next_character_with_one_forward("{", info);

    while(TRUE) {
        if(!parse_word(pipes[num_pipes], VAR_NAME_MAX, info, TRUE, FALSE))
        {
            return FALSE;
        }

        if(!parse_block_easy(ALLOC &pipe_blocks[num_pipes], FALSE, info))
        {
            return FALSE;
        }

        num_pipes++;

        if(*info->p == '}') {
            info->p++;
            skip_spaces_and_lf(info);
            break;
        }
    }

    char* pipes2[SELECT_MAX];

    int i;
    for(i=0; i<num_pipes; i++) {
        pipes2[i] = pipes[i];
    }

    *node = sNodeTree_create_select(num_pipes, pipes2, pipe_blocks, info);

    return TRUE;
}

BOOL parse_pselect(unsigned int* node, sParserInfo* info)
{
    int num_pipes = 0;
    char pipes[SELECT_MAX][VAR_NAME_MAX+1];
    sNodeBlock* pipe_blocks[SELECT_MAX];
    sNodeBlock* default_block = NULL;

    expect_next_character_with_one_forward("{", info);

    while(TRUE) {
        char buf[VAR_NAME_MAX];
        if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE))
        {
            return FALSE;
        }

        if(strcmp(buf, "default") == 0) {
            if(!parse_block_easy(ALLOC &default_block, FALSE, info))
            {
                return FALSE;
            }
        }
        else {
            xstrncpy(pipes[num_pipes], buf, VAR_NAME_MAX);

            if(!parse_block_easy(ALLOC &pipe_blocks[num_pipes], FALSE, info))
            {
                return FALSE;
            }

            num_pipes++;
        }

        if(*info->p == '}') {
            info->p++;
            skip_spaces_and_lf(info);
            break;
        }
    }

    char* pipes2[SELECT_MAX];

    int i;
    for(i=0; i<num_pipes; i++) {
        pipes2[i] = pipes[i];
    }

    *node = sNodeTree_create_pselect(num_pipes, pipes2, pipe_blocks, default_block, info);

    return TRUE;
}

BOOL parse_alloca(unsigned int* node, sParserInfo* info)
{
    sNodeType* node_type = NULL;

    if(!parse_type(&node_type, info, NULL, FALSE, FALSE, NULL, FALSE)) {
        return FALSE;
    }

    sCLClass* klass = node_type->mClass;

    if(klass) {
        unsigned int object_num = 0;
        if(*info->p == '[') {
            info->p++;
            skip_spaces_and_lf(info);

            if(!expression(&object_num, TRUE, info)) {
                return FALSE;
            }

            expect_next_character_with_one_forward("]", info);
        };

        *node = sNodeTree_create_stack_object(node_type, object_num, info->sname, info->sline, info);
    }
    else {
        parser_err_msg(info, "Invalid type name");
        info->err_num++;
    }

    return TRUE;
}

BOOL parse_sizeof(unsigned int* node, sParserInfo* info)
{
    expect_next_character_with_one_forward("(", info);

    char* p_before = info->p;
    int sline_before = info->sline;

    char buf[VAR_NAME_MAX+1];
    (void)parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE);

    info->p = p_before;
    info->sline = sline_before;

    if(is_type_name(buf, info)) {
        sNodeType* node_type = NULL;

        BOOL define_struct_only = FALSE;
        if(!parse_type(&node_type, info, NULL, FALSE, FALSE, NULL, FALSE)) {
            return FALSE;
        }

        expect_next_character_with_one_forward(")", info);

        *node = sNodeTree_create_sizeof(node_type, info);
    }
    else {
        if(!expression(node, FALSE, info)) {
            return FALSE;
        }

        expect_next_character_with_one_forward(")", info);

        *node = sNodeTree_create_sizeof_expression(*node, info);
    }

    return TRUE;
}

BOOL parse_alignof(unsigned int* node, sParserInfo* info)
{
    expect_next_character_with_one_forward("(", info);

    char* p_before = info->p;
    int sline_before = info->sline;

    char buf[VAR_NAME_MAX+1];
    (void)parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE);

    info->p = p_before;
    info->sline = sline_before;

    if(is_type_name(buf, info)) {
        sNodeType* node_type = NULL;

        if(!parse_type(&node_type, info, NULL, FALSE, FALSE, NULL, FALSE)) {
            return FALSE;
        }

        expect_next_character_with_one_forward(")", info);

        *node = sNodeTree_create_alignof(node_type, info);
    }
    else {
        if(!expression(node, FALSE, info)) {
            return FALSE;
        }

        expect_next_character_with_one_forward(")", info);

        *node = sNodeTree_create_alignof_expression(*node, info);
    }

    return TRUE;
}
