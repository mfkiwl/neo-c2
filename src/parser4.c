#include "common.h"
#include <ctype.h>

BOOL parse_param(sParserParam* param, sParserInfo* info)
{
    if(!parse_type(&param->mType, info, param->mName, FALSE, FALSE, NULL, FALSE)) {
        return FALSE;
    }

    if(param->mName[0] == 0 && (*info->p == ',' || *info->p == ')')) {
        param->mName[0] = '\0';
    }
    else {
        if(param->mName[0] == '\0') {
            if(!parse_variable_name(param->mName, VAR_NAME_MAX, info, param->mType, FALSE, TRUE))
            {
                return FALSE;
            }
        }
    }

    return TRUE;
}

BOOL get_block_text(sBuf* buf, sParserInfo* info, BOOL append_head_currly_brace)
{
    if(append_head_currly_brace) {
        sBuf_append_str(buf, "{ ");
    }

    BOOL dquort = FALSE;
    BOOL squort = FALSE;

    int nest = 0;
    while(TRUE) {
        if(!squort && *info->p == '"') {
            sBuf_append_char(buf, *info->p);
            info->p++;
            dquort = !dquort;
        }
        else if(!dquort && *info->p == '\'') {
            sBuf_append_char(buf, *info->p);
            info->p++;
            sBuf_append_char(buf, *info->p);
            info->p++;
            squort = !squort;
        }
        else if(dquort || squort) {
            if(*info->p == '\n') {
                info->sline++;
            }

            sBuf_append_char(buf, *info->p);
            info->p++;
        }
        else if(*info->p == '{') {
            sBuf_append_char(buf, *info->p);
            info->p++;

            nest++;
        }
        else if(*info->p == '#') {
            char* p = info->p;
            if(!parse_sharp(info)) {
                return FALSE;
            }
            sBuf_append(buf, p, info->p-p);
        }
        else if(*info->p == '}') {
            if(nest == 0) {
                sBuf_append_str(buf, "}");
                info->p++;

                while(TRUE) {
                    if(*info->p == ' ' || *info->p == '\t') {
                        info->p++;
                    }
                    else if(*info->p == '\n') {
                        info->sline++;

                        info->p++;
                        sBuf_append_str(buf, "\n");
                    }
                    else {
                        break;
                    }
                }

                break;
            }
            else {
                sBuf_append_str(buf, "}");
                info->p++;

                while(TRUE) {
                    if(*info->p == ' ' || *info->p == '\t') {
                        info->p++;
                    }
                    else if(*info->p == '\n') {

                        info->sline++;
                        info->p++;
                        sBuf_append_str(buf, "\n");
                    }
                    else {
                        break;
                    }
                }
            }

            nest--;
        }
        else if(*info->p == '\n') {
            info->sline++;

            sBuf_append_char(buf, *info->p);
            info->p++;
        }
        else if(*info->p == '\0') {
            parser_err_msg(info, "require } before the source end");
            return FALSE;
        }
        else {
            sBuf_append_char(buf, *info->p);
            info->p++;
        }
    }

    return TRUE;
}


/// character_type --> 0: () 1: ||
BOOL parse_params(sParserParam* params, int* num_params, sParserInfo* info, int character_type, BOOL* var_arg)
{
    char* p_before = info->p;
    int sline_before = info->sline;

    char buf[VAR_NAME_MAX];
    if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE)) {
        return FALSE;
    }

    if(strcmp(buf, "void") == 0 && *info->p == ')') {
        info->p++;
        skip_spaces_and_lf(info);
        return TRUE;
    }
    else {
        info->p = p_before;
        info->sline = sline_before;
    }

    if((character_type == 0 && *info->p == ')') || (character_type == 1 && *info->p == '|')) {
        info->p++;
        skip_spaces_and_lf(info);

        return TRUE;
    };
     
    *var_arg = FALSE;

    while(1) {
        if(*info->p == '.' && *(info->p + 1) == '.' && *(info->p + 2) == '.') {
            info->p += 3;
            skip_spaces_and_lf(info);

            expect_next_character_with_one_forward(")", info);
            skip_spaces_and_lf(info);

            *var_arg = TRUE;
            break;
        }

        if(!parse_param(params + *num_params, info)) {
            return FALSE;
        }

        (*num_params)++;

        if(*num_params >= PARAMS_MAX) {
            parser_err_msg(info, "overflow params number");
            return FALSE;
        }

        if(*info->p == ',') {
            info->p++;
            skip_spaces_and_lf(info);
        }
        else if((character_type == 0 && *info->p == ')') || (character_type == 1 && *info->p == '|')) {
            info->p++;
            skip_spaces_and_lf(info);
            break;
        }
        else if(*info->p == '\0') {
            parser_err_msg(info, "It is required to ',' or ')' before the source end");
            info->err_num++;
            break;
        }
        else {
            char msg[1024];
            snprintf(msg, 1024, "Unexpected character(%c). It is required to ',' or ')' or '|' character", *info->p);
            parser_err_msg(info, msg);
            if(*info->p == '\n') {
                info->sline++;
            }
            info->p++;

            info->err_num++;
        }
    }

    return TRUE;
}



BOOL parse_generics_function(unsigned int* node, sNodeType* result_type, char* fun_name, char* struct_name, sParserInfo* info)
{
    xstrncpy(info->fun_name, fun_name, VAR_NAME_MAX);

    char* function_head = info->p;

    BOOL operator_fun = FALSE;

    expect_next_character_with_one_forward("(", info);

    /// params ///
    sParserParam params[PARAMS_MAX];
    memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);
    int num_params = 0;

    /// parse_params ///
    BOOL var_arg = FALSE;
    if(!parse_params(params, &num_params, info, 0, &var_arg))
    {
        return FALSE;
    }

    int i;
    for(i=0; i<num_params; i++) {
        char* name = params[i].mName;

        if(name[0] == '\0') {
            parser_err_msg(info, "Require parametor variable names");
            info->err_num++;
        }
    }

    char asm_fname[VAR_NAME_MAX];
    if(!parse_attribute(info, asm_fname)) {
        return FALSE;
    }

    skip_spaces_and_lf(info);

    char sname[PATH_MAX];
    xstrncpy(sname, info->sname, PATH_MAX);

    skip_spaces_and_lf(info);

    int sline = info->sline;

    if(*info->p == '{') {
        info->p++;
    }

    sBuf buf;
    sBuf_init(&buf);

    if(!get_block_text(&buf, info, TRUE)) {
        free(buf.mBuf);
        return FALSE;
    };

    *node = sNodeTree_create_generics_function(fun_name, params, num_params, result_type, MANAGED buf.mBuf, struct_name, sname, sline, var_arg, 0, info);

    //info->mNumMethodGenerics = 0;

    return TRUE;
}

BOOL parse_method_generics_function(unsigned int* node, char* struct_name, sParserInfo* info)
{
    char* function_head = info->p;

    /// method generics ///
    info->mNumMethodGenerics = 0;

    if(*info->p == '<') {
        info->p++;
        skip_spaces_and_lf(info);

        int num_generics = 0;

        while(TRUE) {
            char buf[VAR_NAME_MAX];
            if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
                return FALSE;
            }

            info->mMethodGenericsTypeNames[num_generics] = strdup(buf);
            num_generics++;

            if(num_generics >= GENERICS_TYPES_MAX)
            {
                parser_err_msg(info, "overflow generics types");
                return FALSE;
            }

            info->mNumMethodGenerics = num_generics;

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '>') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
            else {
                parser_err_msg(info, "require , or > character");
                info->err_num++;
                break;
            }
        }
    }

    sNodeType* result_type = NULL;
    if(!parse_type(&result_type, info, NULL, FALSE, FALSE, NULL, FALSE)) 
    {
        return FALSE;
    }

    char fun_name[VAR_NAME_MAX+1];
    if(!parse_word(fun_name, VAR_NAME_MAX, info, TRUE, FALSE))
    {
        return FALSE;
    }

    xstrncpy(info->fun_name, fun_name, VAR_NAME_MAX);

    expect_next_character_with_one_forward("(", info);

    /// params ///
    sParserParam params[PARAMS_MAX];
    memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);
    int num_params = 0;

    /// parse_params ///
    BOOL var_arg = FALSE;
    if(!parse_params(params, &num_params, info, 0, &var_arg))
    {
        return FALSE;
    }

    int i;
    for(i=0; i<num_params; i++) {
        char* name = params[i].mName;

        if(name[0] == '\0') {
            parser_err_msg(info, "Require parametor variable names");
            info->err_num++;
        }
    }

    char asm_fname[VAR_NAME_MAX];
    if(!parse_attribute(info, asm_fname)) {
        return FALSE;
    }

    char sname[PATH_MAX];
    xstrncpy(sname, info->sname, PATH_MAX);

    skip_spaces_and_lf(info);

    int sline = info->sline;

    if(*info->p == '{') {
        info->p++;
    }

    sBuf buf;
    sBuf_init(&buf);

    if(!get_block_text(&buf, info, TRUE)) {
        free(buf.mBuf);
        return FALSE;
    };

    *node = sNodeTree_create_generics_function(fun_name, params, num_params, result_type, MANAGED buf.mBuf, struct_name, sname, sline, var_arg, 0, info);

    return TRUE;
}

void parse_version(int* version, sParserInfo* info)
{
    if(parse_cmp(info->p, "version") == 0) {
        info->p += 7;
        skip_spaces_and_lf(info);

        *version = 0;
        while(xisdigit(*info->p)) {
            *version = *version * 10 + (*info->p - '0');
            info->p++;
            skip_spaces_and_lf(info);
        }
        
        if(*version >= FUNCTION_VERSION_MAX) {
            fprintf(stderr, "overflow function version max");
            exit(2);
        }

        skip_spaces_and_lf(info);
    }
}

BOOL parse_function(unsigned int* node, sNodeType* result_type, char* fun_name, char* struct_name, sParserInfo* info)
{
    int sline = info->sline;
    char* function_head = info->p;

    /// method generics ///
    info->mNumMethodGenerics = 0;

    BOOL operator_fun = FALSE;

    expect_next_character_with_one_forward("(", info);

    /// params ///
    sParserParam params[PARAMS_MAX];
    memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);

    /// parse_params ///
    int num_params = 0;
    BOOL var_arg = FALSE;
    if(!parse_params(params, &num_params, info, 0, &var_arg))
    {
        return FALSE;
    }

    char asm_fname[VAR_NAME_MAX];
    if(!parse_attribute(info, asm_fname)) {
        return FALSE;
    }

    xstrncpy(info->fun_name, fun_name, VAR_NAME_MAX);

    /// remove function pointer params if the result is function pointer ///
    if(*info->p == ')') {
        info->p++;
        skip_spaces_and_lf(info);

        int nest = 0;
        while(*info->p) {
            if(*info->p == '(') {
                info->p++;
                nest++;
            }
            else if(*info->p == ')') {
                info->p++;
                
                if(nest <= 1) {
                    break;
                }
                else {
                    nest--;
                }
            }
            else {
                info->p++;
            }
        }
    }

    if(*info->p == ';') {
        info->p++;
        skip_spaces_and_lf(info);

        *node = sNodeTree_create_external_function(fun_name, asm_fname, params, num_params, var_arg, result_type, struct_name, operator_fun, 0, info);
    }
    else {
        int version = 0;
        parse_version(&version, info);

        int i;
        for(i=0; i<num_params; i++) {
            char* name = params[i].mName;

            if(name[0] == '\0') {
                parser_err_msg(info, "Require parametor variable names");
                info->err_num++;
            }
        }

        sNodeBlock* node_block = ALLOC sNodeBlock_alloc();
        expect_next_character_with_one_forward("{", info);
        sVarTable* old_table = info->lv_table;

        info->lv_table = init_block_vtable(old_table, FALSE);

        sVarTable* block_var_table = info->lv_table;

        for(i=0; i<num_params; i++) {
            sParserParam* param = params + i;

            BOOL readonly = FALSE;
            if(!add_variable_to_table(info->lv_table, param->mName, param->mType, readonly, NULL, -1, FALSE, param->mType->mConstant))
            {
                return FALSE;
            }
        }

        if(!parse_block(node_block, FALSE, FALSE, info)) {
            sNodeBlock_free(node_block);
            return FALSE;
        }

        if(gNCType) {
            if(*info->p != '\0') {
                expect_next_character_with_one_forward("}", info);
            }
        }
        else {
            expect_next_character_with_one_forward("}", info);
        }

        info->lv_table = old_table;

        BOOL lambda_ = FALSE;

        BOOL simple_lambda_param = FALSE;
        BOOL construct_fun = FALSE;

        *node = sNodeTree_create_function(fun_name, asm_fname, params, num_params, result_type, MANAGED node_block, lambda_, block_var_table, struct_name, operator_fun, construct_fun, simple_lambda_param, info, FALSE, var_arg, version, FALSE, -1, fun_name, sline);
    }

    info->mNumMethodGenerics = 0;

    return TRUE;
}

BOOL parse_inline_function(unsigned int* node, char* struct_name, sParserInfo* info)
{
    BOOL operator_fun = FALSE;

    /// method generics ///
    info->mNumMethodGenerics = 0;

    char asm_fname[VAR_NAME_MAX];
    if(!parse_attribute(info, asm_fname)) {
        return FALSE;
    }

    sNodeType* result_type = NULL;
    if(!parse_type(&result_type, info, NULL, FALSE, FALSE, NULL, FALSE))
    {
        return FALSE;
    }

    if(result_type == NULL) {
        return TRUE;
    }

    char fun_name[VAR_NAME_MAX+1];
    if(!parse_word(fun_name, VAR_NAME_MAX, info, TRUE, FALSE))
    {
        return FALSE;
    }

    if(*info->p != '(') {
        parser_err_msg(info, "require function definition\n");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward("(", info);

    /// params ///
    sParserParam params[PARAMS_MAX];
    memset(params, 0, sizeof(sParserParam)*PARAMS_MAX);
    int num_params = 0;

    /// parse_params ///
    BOOL var_arg = FALSE;
    if(!parse_params(params, &num_params, info, 0, &var_arg))
    {
        return FALSE;
    }

    int i;
    for(i=0; i<num_params; i++) {
        char* name = params[i].mName;

        if(name[0] == '\0') {
            parser_err_msg(info, "Require parametor variable names");
            info->err_num++;
        }
    }

    if(!parse_attribute(info, asm_fname)) {
        return FALSE;
    }

    char sname[PATH_MAX];
    xstrncpy(sname, info->sname, PATH_MAX);

    skip_spaces_and_lf(info);

    int sline = info->sline;

    skip_spaces_and_lf(info);

    if(*info->p == '{') {
        info->p++;
        skip_spaces_and_lf(info);
    }

    sBuf buf;
    sBuf_init(&buf);

    if(!get_block_text(&buf, info, TRUE)) {
        free(buf.mBuf);
        return FALSE;
    };

    *node = sNodeTree_create_inline_function(fun_name, params, num_params, result_type, MANAGED buf.mBuf, struct_name, sname, sline, var_arg, info);

    return TRUE;
}

BOOL parse_funcation_call_params(int* num_params, unsigned int* params, sParserInfo* info)
{
    if(*info->p == '(') {
        BOOL no_comma_operator = info->no_comma_operator;
        info->no_comma_operator = TRUE;

        info->p++;
        skip_spaces_and_lf(info);

        if(*info->p == ')') {
            info->p++;
            skip_spaces_and_lf(info);
        }
        else {
            while(1) {
                if(*info->p == '#') {
                    if(!parse_sharp(info)) {
                        return FALSE;
                    }
                }

                unsigned int node = 0;
                if(!expression(&node, FALSE, info)) {
                    return FALSE;
                }

                if(node == 0) {
                    parser_err_msg(info, "require expression");
                    info->err_num++;
                    break;
                }

                params[*num_params] = node;
                (*num_params)++;

                if(*num_params >= PARAMS_MAX) {
                    parser_err_msg(info, "overflow parametor number for method call");
                    return FALSE;
                }

                if(*info->p == '@') {
                    info->p++;
                    while(xisalnum(*info->p) || *info->p == '_') {
                        info->p++;
                    }
                    skip_spaces_and_lf(info);
                }

                if(*info->p == '#') {
                    if(!parse_sharp(info)) {
                        return FALSE;
                    }
                }


                if(*info->p == ',') {
                    info->p++;
                    skip_spaces_and_lf(info);
                }
                else if(*info->p == ')') {
                    info->p++;
                    skip_spaces_and_lf(info);
                    break;
                }
                else if(*info->p == '\0') {
                    parser_err_msg(info, "unexpected the source end");
                    info->err_num++;
                    break;
                }
                else {
                    char msg[1024];
                    snprintf(msg, 1024, "comelang requires , or ) for method call. it is %c", *info->p);
                    parser_err_msg(info, msg);
                    info->err_num++;
                    break;
                }
            }
        }

        info->no_comma_operator = no_comma_operator;
    }

    skip_spaces_and_lf(info);

    sNodeType* result_type = NULL;

    char* p = info->p;
    int sline = info->sline;

    char buf[VAR_NAME_MAX];

    parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE);

    if(is_type_name(buf, info)) {
        info->p = p;
        info->sline = sline;

        parse_type(&result_type, info, NULL, FALSE, FALSE, NULL, FALSE);
    }
    else {
        info->p = p;
        info->sline = sline;
    }

    if(*info->p == '{') {
        params[*num_params] = sNodeTree_create_stack(info);
        (*num_params)++;
        
        if(*num_params >= PARAMS_MAX) {
            parser_err_msg(info, "overflow parametor number for method call");
            return FALSE;
        }

        char* p = info->p;
        if(!skip_block(info)) {
            return FALSE;
        }

        char* p2 = info->p;

        sBuf buf;
        sBuf_init(&buf);

        sBuf_append(&buf, p, p2-p);

        params[*num_params] = sNodeTree_create_method_block(MANAGED buf.mBuf, result_type, info);

        (*num_params)++;
        
        if(*num_params >= PARAMS_MAX) {
            parser_err_msg(info, "overflow parametor number for method call");
            return FALSE;
        }
    }

    return TRUE;
}

BOOL parse_if(unsigned int* node, sParserInfo* info)
{
    char sname[PATH_MAX];
    xstrncpy(sname, info->sname, PATH_MAX);
    int sline = info->sline;

    expect_next_character_with_one_forward("(", info);

    /// expression ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, TRUE, info)) {
        return FALSE;
    }

    if(expression_node == 0) {
        parser_err_msg(info, "require expression for if");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(")", info);

    sNodeBlock* if_node_block = NULL;
    if(!parse_block_easy(ALLOC &if_node_block, FALSE, info))
    {
        return FALSE;
    }

    unsigned int elif_expression_nodes[ELIF_NUM_MAX];
    memset(elif_expression_nodes, 0, sizeof(unsigned int)*ELIF_NUM_MAX);

    sNodeBlock* elif_node_blocks[ELIF_NUM_MAX];
    memset(elif_node_blocks, 0, sizeof(sNodeBlock*)*ELIF_NUM_MAX);

    int elif_num = 0;

    sNodeBlock* else_node_block = NULL;

    while(1) {
        char* saved_p = info->p;
        int saved_sline = info->sline;

        char buf[VAR_NAME_MAX];

        /// else ///
        if(!xisalpha(*info->p)) {
            break;
        }
        if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
            return FALSE;
        }

        if(strcmp(buf, "else") == 0) {
            if(parse_cmp(info->p, "if") == 0) {
                info->p+=2;
                skip_spaces_and_lf(info);

                expect_next_character_with_one_forward("(", info);

                /// expression ///
                if(!expression(&elif_expression_nodes[elif_num], TRUE, info)) {
                    return FALSE;
                }

                if(elif_expression_nodes[elif_num] == 0) {
                    parser_err_msg(info, "require elif expression");
                    info->err_num++;
                    return TRUE;
                }

                expect_next_character_with_one_forward(")", info);

                if(!parse_block_easy(ALLOC &elif_node_blocks[elif_num], FALSE, info))
                {
                    return FALSE;
                }

                elif_num++;
                if(elif_num >= ELIF_NUM_MAX) {
                    parser_err_msg(info, "overflow elif num");
                    info->err_num++;
                    return FALSE;
                }
            }
            else {
                if(!parse_block_easy(ALLOC &else_node_block, FALSE, info))
                {
                    return FALSE;
                }
                break;
            }
        }
        else {
            info->p = saved_p;
            info->sline = saved_sline;
            break;
        }
    };

    *node = sNodeTree_if_expression(expression_node, MANAGED if_node_block, elif_expression_nodes, elif_node_blocks, elif_num, MANAGED else_node_block, info, sname, sline);

    return TRUE;
}


