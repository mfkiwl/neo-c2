#include "common.h"
#include <ctype.h>

BOOL parse_clone(unsigned int* node, sParserInfo* info)
{
    BOOL gc = gNCGC;
    if(*info->p == '(') {
        info->p++;
        skip_spaces_and_lf(info);

        if(*info->p == 'G' && *(info->p+1) == 'C') {
            info->p += 2;
            skip_spaces_and_lf(info);
        }

        if(*info->p == ')') {
            info->p++;
            skip_spaces_and_lf(info);
        }

        gc = TRUE;
    }

    if(!expression(node, FALSE, info)) {
        return FALSE;
    }

    if(*node == 0) {
        parser_err_msg(info, "Require expression for clone");
        info->err_num++;
        return TRUE;
    };

    *node = sNodeTree_create_clone(*node, gc, info);

    return TRUE;
}

BOOL parse_is_gc_heap(unsigned int* node, sParserInfo* info)
{
    *node = 0;
    if(*info->p == '(') {
        info->p++;
        skip_spaces_and_lf(info);
        
        if(!expression(node, FALSE, info)) {
            return FALSE;
        }
        
        if(*info->p == ')') {
            info->p++;
            skip_spaces_and_lf(info);
        }
    }

    if(*node == 0) {
        parser_err_msg(info, "Require expression for is_gc_heap");
        info->err_num++;
        return TRUE;
    };

    *node = sNodeTree_create_is_gc_heap(*node, info);

    return TRUE;
}

BOOL parse_typedef(unsigned int* node, sParserInfo* info)
{
    char buf[VAR_NAME_MAX+1];
    
    buf[0] = '\0';

    sNodeType* node_type = NULL;
    if(!parse_type(&node_type, info, buf, TRUE, FALSE, NULL, FALSE)) {
        return FALSE;
    }

    char asm_fname[VAR_NAME_MAX];
    if(!parse_attribute(info, asm_fname)) {
        return FALSE;
    }

    sNodeType* node_type2 = clone_node_type(node_type);

    int num_nodes = 0;
    unsigned int nodes[NODES_MAX];
    memset(nodes, 0, sizeof(unsigned int)*NODES_MAX);

    if(buf[0] == '\0') {
        while(1) {
            if(!parse_variable_name(buf, VAR_NAME_MAX, info, node_type2, FALSE, FALSE))
            {
                return FALSE;
            }

            if(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_typedef(buf, node_type2, info);
                nodes[num_nodes++] = *node;

                if(num_nodes >= NODES_MAX) {
                    fprintf(stderr, "overflow define variable max");
                    return FALSE;
                }
            }
            else {
                *node = sNodeTree_create_typedef(buf, node_type2, info);
                nodes[num_nodes++] = *node;

                if(num_nodes >= NODES_MAX) {
                    fprintf(stderr, "overflow define variable max");
                    return FALSE;
                }
                break;
            }
        }
    }
    else {
        *node = sNodeTree_create_typedef(buf, node_type2, info);
        nodes[num_nodes++] = *node;

        if(num_nodes >= NODES_MAX) {
            fprintf(stderr, "overflow define variable max");
            return FALSE;
        }
    }

    *node = sNodeTree_create_nodes(nodes, num_nodes, info);

    if(!parse_typedef_attribute(info))
    {
        return FALSE;
    };

    return TRUE;
}

BOOL parse_switch(unsigned int* node, sParserInfo* info)
{
    expect_next_character_with_one_forward("(", info);

    /// expression1 ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, FALSE, info)) {
        return FALSE;
    }

    if(expression_node == 0) {
        parser_err_msg(info, "require expression for \"switch\"");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(")", info);
    expect_next_character_with_one_forward("{", info);

    int size_switch_expression = 16;
    int num_switch_expression = 0;
    unsigned int* switch_expression = (unsigned int*)xcalloc(1, sizeof(unsigned int)*size_switch_expression);
    info->switch_nest++;

    info->first_case = TRUE;
    info->case_after_return = FALSE;

    while(1) {
        if(*info->p == '}') {
            info->p++;
            skip_spaces_and_lf(info);
            info->switch_nest--;
            break;
        }
        else {
            int sline = info->sline;

            if(!expression(switch_expression + num_switch_expression, TRUE, info)) 
            {
                return FALSE;
            }

            if(gNodes[switch_expression[num_switch_expression]].mNodeType == kNodeTypeReturn) 
            {
                info->case_after_return = TRUE;
            }
            else if(gNodes[switch_expression[num_switch_expression]].mNodeType == kNodeTypeCase) 
            {
            }
            else {
                info->case_after_return = FALSE;
            }

            unsigned int node = switch_expression[num_switch_expression];
            
            gNodes[node].mLine = sline;

            if(gNodes[node].mNodeType == kNodeTypeCase) {
                gNodes[node].uValue.sCase.mFirstCase = info->first_case;
                info->first_case = FALSE;
            }
            else {
                info->first_case = TRUE;
            }

            num_switch_expression++;

            if(num_switch_expression >= size_switch_expression) 
            {
                size_switch_expression *= 2;
                switch_expression = xrealloc(switch_expression, sizeof(unsigned int)*size_switch_expression);
            }

            if(*info->p == ';') {
                info->p++;
                skip_spaces_and_lf(info);
            }
        }
    };

    *node = sNodeTree_switch_expression(expression_node, num_switch_expression, MANAGED switch_expression, info);

    return TRUE;
}

BOOL parse_case(unsigned int* node, sParserInfo* info)
{
    BOOL in_case = info->in_case;
    info->in_case = TRUE;

    /// expression1 ///
    unsigned int expression_node = 0;
    if(!expression(&expression_node, FALSE, info)) {
        info->in_case = in_case;
        return FALSE;
    }

    info->in_case = in_case;

    if(expression_node == 0) {
        parser_err_msg(info, "require expression for \"case\"");
        info->err_num++;
        return TRUE;
    }

    expect_next_character_with_one_forward(":", info);

    char* p_before = info->p;
    int sline_before = info->sline;

    char buf[VAR_NAME_MAX+1];
    if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE))
    {
        return FALSE;
    }

    BOOL last_case = strcmp(buf, "case") != 0;

    info->p = p_before;
    info->sline = sline_before;

    *node = sNodeTree_case_expression(expression_node, last_case, info->case_after_return, info);

    return TRUE;
}

BOOL parse_default(unsigned int* node, sParserInfo* info)
{
    expect_next_character_with_one_forward(":", info);

    char* p_before = info->p;
    int sline_before = info->sline;

    char buf[VAR_NAME_MAX+1];
    if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE))
    {
        return FALSE;
    }

    BOOL last_case = strcmp(buf, "case") != 0;

    info->p = p_before;
    info->sline = sline_before;

    *node = sNodeTree_case_expression(0, last_case, info->case_after_return, info);

    return TRUE;
}

BOOL parse_label(unsigned int* node, char* name, sParserInfo* info)
{
    expect_next_character_with_one_forward(":", info);

    *node = sNodeTree_label_expression(name, info);

    return TRUE;
}

BOOL parse_goto(unsigned int* node, sParserInfo* info)
{
    char buf[VAR_NAME_MAX+1];
    if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE))
    {
        return FALSE;
    };

    *node = sNodeTree_goto_expression(buf, info);

    return TRUE;
}

BOOL get_hex_number(unsigned int* node, sParserInfo* info)
{
    int buf_size = 128;
    char buf[128+1];
    char* p = buf;

    *p++ = '0';
    *p++ = 'x';

    while((*info->p >= '0' && *info->p <= '9') || (*info->p >= 'a' && *info->p <= 'f') || (*info->p >= 'A' && *info->p <= 'F') || *info->p == '_') 
    {
        if(*info->p == '_') {
            info->p++;
        }
        else {
            *p++ = *info->p;
            info->p++;
        }

        if(p - buf >= buf_size-1) {
            parser_err_msg(info, "overflow node of number");
            return FALSE;
        }
    };
    *p = 0;
    skip_spaces_and_lf(info);

    unsigned clint64 value = strtoll(buf, NULL, 0);

    if(*info->p == 'u' || *info->p == 'U')
    {
        info->p++;
        skip_spaces_and_lf(info);

        if(*info->p == 'L' || *info->p == 'l')
        {
            info->p++;
            skip_spaces_and_lf(info);

            if(*info->p == 'L' || *info->p == 'l')
            {
                info->p++;
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_ulong_value(value, info);
            }
            else {
                *node = sNodeTree_create_ulong_value(value, info);
            }
        }
        else {
            *node = sNodeTree_create_uint_value(value, info);
        }
    }
    else if(*info->p == 'L' || *info->p == 'l') {
        info->p++;
        skip_spaces_and_lf(info);

        if(*info->p == 'L' || *info->p == 'l')
        {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_long_value(value, info);
        }
        else if(*info->p == 'U' || *info->p == 'u')
        {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_ulong_value(value, info);
        }
        else {
            *node = sNodeTree_create_long_value(value, info);
        }
    }
    else {
        *node = sNodeTree_create_int_value(value, info);
    }

    return TRUE;
}

BOOL get_oct_number(unsigned int* node, sParserInfo* info)
{
    int buf_size = 128;
    char buf[128+1];
    char* p = buf;

    *p++ = '0';

    while((*info->p >= '0' && *info->p <= '7') || *info->p == '_') {
        if(*info->p == '_') {
            info->p++;
        }
        else {
            *p++ = *info->p++;
        }

        if(p - buf >= buf_size-1) {
            parser_err_msg(info, "overflow node of number");
            return FALSE;
        }
    };

    *p = 0;
    skip_spaces_and_lf(info);

    unsigned clint64 value = strtoul(buf, NULL, 0);

    if(*info->p == 'u' || *info->p == 'U')
    {
        info->p++;
        skip_spaces_and_lf(info);

        if(*info->p == 'L' || *info->p == 'l')
        {
            info->p++;
            skip_spaces_and_lf(info);

            if(*info->p == 'L' || *info->p == 'l')
            {
                info->p++;
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_ulong_value(value, info);
            }
            else {
                *node = sNodeTree_create_ulong_value(value, info);
            }
        }
        else {
            *node = sNodeTree_create_uint_value(value, info);
        }
    }
    else if(*info->p == 'L' || *info->p == 'l') {
        info->p++;
        skip_spaces_and_lf(info);

        if(*info->p == 'L' || *info->p == 'l')
        {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_long_value(value, info);
        }
        else if(*info->p == 'U' || *info->p == 'u')
        {
            info->p++;
            skip_spaces_and_lf(info);

            *node = sNodeTree_create_ulong_value(value, info);
        }
        else {
            *node = sNodeTree_create_long_value(value, info);
        }
    }
    else {
        *node = sNodeTree_create_int_value(value, info);
    }

    return TRUE;
}

BOOL parse_impl(unsigned int* node, sParserInfo* info)
{
    char struct_name[VAR_NAME_MAX];

    char buf[VAR_NAME_MAX];
    if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    xstrncpy(struct_name, buf, VAR_NAME_MAX);

    while(*info->p == '*') {
        info->p++;
        xstrncat(struct_name, "*", VAR_NAME_MAX);
    }

    xstrncpy(info->impl_struct_name, struct_name, VAR_NAME_MAX);

    info->mNumGenerics = 0;

    if(*info->p == '<') {
        info->p++;
        skip_spaces_and_lf(info);

        int num_generics = 0;

        while(TRUE) {
            char buf[VAR_NAME_MAX];
            if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
                return FALSE;
            }

            info->mGenericsTypeNames[num_generics] = strdup(buf);
            num_generics++;

            if(num_generics >= GENERICS_TYPES_MAX)
            {
                parser_err_msg(info, "overflow generics types");
                return FALSE;
            }

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

        info->mNumGenerics = num_generics;
    }

    expect_next_character_with_one_forward("{", info);

    if(!expression(node, TRUE, info)) {
        return FALSE;
    }

    return TRUE;
}

void parse_impl_end(sParserInfo* info)
{
    strcpy(info->impl_struct_name, "");
    info->mNumGenerics = 0;
}

BOOL parse_new(unsigned int* node, sParserInfo* info)
{
    sNodeType* node_type = NULL;

    BOOL gc = gNCGC;

    if(*info->p == '(') {
        info->p++;
        skip_spaces_and_lf(info);

        if(*info->p == 'G' && *(info->p+1) == 'C') {
            info->p+=2;
            skip_spaces_and_lf(info);
        }

        if(*info->p == ')') {
            info->p++;
            skip_spaces_and_lf(info);
        }

        gc = TRUE;
    }

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
        }

        *node = sNodeTree_create_object(node_type, object_num, 0, NULL, info->sname, info->sline, gc, info);
    }
    else {
        parser_err_msg(info, "Invalid type name");
        info->err_num++;
    }

    return TRUE;
}

BOOL parse_var(unsigned int* node, sParserInfo* info, BOOL readonly)
{
    char buf[VAR_NAME_MAX];

    if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE)) {
        return FALSE;
    }

    if(*info->p == ':') {
        info->p++;
        skip_spaces_and_lf(info);
    }

    sNodeType* node_type;
    if(*info->p != '=') {
        if(!parse_type(&node_type, info, NULL, FALSE, FALSE, NULL, FALSE)) {
            return FALSE;
        }

        if(node_type->mClass == NULL) {
            *node = 0;
            return TRUE;
        }
        if(node_type) {
            check_already_added_variable(info->lv_table, buf, info);
            if(!add_variable_to_table(info->lv_table, buf, node_type, readonly, NULL, -1, info->mBlockLevel == 0, node_type->mConstant))
            {
                fprintf(stderr, "overflow variable table\n");
                exit(2);
            }
        }
    }
    else {
        node_type = NULL;
        check_already_added_variable(info->lv_table, buf, info);
        if(!add_variable_to_table(info->lv_table, buf, node_type, readonly, NULL, -1, info->mBlockLevel == 0, FALSE))
        {
            fprintf(stderr, "overflow variable table\n");
            exit(2);
        }
    }

    /// assign the value to a variable ///
    if(*info->p == '=' && *(info->p+1) != '=') {
        info->p++;
        skip_spaces_and_lf(info);

        unsigned int right_node = 0;

        BOOL no_comma_operator = info->no_comma_operator;
        info->no_comma_operator = TRUE;

        if(!expression(&right_node, FALSE, info)) {
            return FALSE;
        }

        info->no_comma_operator = no_comma_operator;

        if(right_node == 0) {
            parser_err_msg(info, "Require right value for =");
            info->err_num++;

            *node = 0;
        }
        else {
            BOOL global = info->mBlockLevel == 0;
            *node = sNodeTree_create_store_variable(buf, right_node, TRUE, global, info);
        }
    }
    else {
        char msg[1024];
        snprintf(msg, 1024, "%s should be initialized", buf);
        parser_err_msg(info, msg);
        info->err_num++;

        *node = 0;
    }

    return TRUE;
}

BOOL parse_inherit(unsigned int* node, sParserInfo* info) 
{
    if(*info->p == '(') {
        unsigned int params[PARAMS_MAX];
        int num_params = 0;

        if(!parse_funcation_call_params(&num_params, params, info)) 
        {
            return FALSE;
        }

        char* fun_name = "inherit";

        *node = sNodeTree_create_function_call(fun_name, params, num_params, FALSE, TRUE, 0, info);
    }

    return TRUE;
}

BOOL parse_come(unsigned int* node, sParserInfo* info)
{
    char buf[VAR_NAME_MAX+1];
    if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE))
    {
        return FALSE;
    }

    if(strcmp(buf, "join") == 0) {
        *node = sNodeTree_create_join(info);
    }
    else if(strcmp(buf, "select") == 0) {
        if(!parse_select(node, info)) {
            return FALSE;
        }
    }
    else if(strcmp(buf, "pselect") == 0) {
        if(!parse_pselect(node, info)) {
            return FALSE;
        }
    }
    else {
        char* fun_name = buf;

        unsigned int params[PARAMS_MAX];
        int num_params = 0;

        if(!parse_funcation_call_params(&num_params, params, info)) 
        {
            return FALSE;
        }

        *node = sNodeTree_create_come_function_call(fun_name, params, num_params, info);
    }
    
    return TRUE;
}



BOOL parse_macro(unsigned int* node, sParserInfo* info)
{
    char buf[VAR_NAME_MAX+1];
    if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE))
    {
        return FALSE;
    }

    char* p = info->p + 1;

    if(!skip_block(info)) {
        return FALSE;
    }

    sBuf body;
    sBuf_init(&body);

    sBuf_append(&body, p, info->p-p-3);

    append_macro(buf, body.mBuf);

    free(body.mBuf);

    *node = sNodeTree_create_null(info);

    skip_spaces_and_lf(info);

    return TRUE;
}

BOOL parse_defer(unsigned int* node, sParserInfo* info)
{
    unsigned int node2 = 0;
    if(!expression(&node2, TRUE, info)) {
        return FALSE;
    }

    if(node2 == 0) {
        parser_err_msg(info, "require defer expression");
        info->err_num++;
    }

    *node = sNodeTree_create_defer(node2, info);

    return TRUE;
}

BOOL parse_call_macro(unsigned int* node, char* name, sParserInfo* info)
{
    char name2[VAR_NAME_MAX];
    xstrncpy(name2, name, VAR_NAME_MAX);

    char* p = info->p + 1;

    if(*info->p == '(') {
        if(!skip_paren('(', ')', info)) {
            return FALSE;
        }
    }
    else if(*info->p == '{') {
        if(!skip_paren('{', '}', info)) {
            return FALSE;
        }
    }
    else if(*info->p == '[') {
        if(!skip_paren('[', ']', info)) {
            return FALSE;
        }
    }
    else if(*info->p == '<') {
        if(!skip_paren('<', '>', info)) {
            return FALSE;
        }
    }
    else {
        parser_err_msg(info, "Require (,{,[ or <");
        info->err_num++;
        return TRUE;
    }

    sBuf params;
    sBuf_init(&params);

    sBuf_append(&params, p, info->p-p-1);

    skip_spaces_and_lf(info);

    if(!call_macro(node, name2, params.mBuf, info)) {
        return FALSE;
    }

    free(params.mBuf);

    return TRUE;
}

BOOL parse_function_pointer_result_function(unsigned int* node, sParserInfo* info)
{
    int sline = info->sline;
    char* function_head = info->p;

    sNodeType* node_type = NULL;
    if(!parse_type(&node_type, info, NULL, FALSE, FALSE, NULL, TRUE))
    {
        return FALSE;
    }

    sNodeType* result_type = create_node_type_with_class_name("lambda");

    result_type->mResultType = clone_node_type(node_type);

    /// method generics ///
    info->mNumMethodGenerics = 0;

    BOOL operator_fun = FALSE;

    expect_next_character_with_one_forward("(", info);
    expect_next_character_with_one_forward("*", info);

    char fun_name[VAR_NAME_MAX+1];
    if(!parse_word(fun_name, VAR_NAME_MAX, info, FALSE, FALSE))
    {
        return FALSE;
    }

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

    /// params ///
    sParserParam params2[PARAMS_MAX];
    memset(params2, 0, sizeof(sParserParam)*PARAMS_MAX);

    expect_next_character_with_one_forward(")", info);
    expect_next_character_with_one_forward("(", info);

    /// parse_params ///
    int num_params2 = 0;
    BOOL var_arg2 = FALSE;
    if(!parse_params(params2, &num_params2, info, 0, &var_arg2))
    {
        return FALSE;
    }

    result_type->mNumParams = num_params2;

    int i;
    for(i=0; i<num_params2; i++) {
        result_type->mParamTypes[i] = clone_node_type(params2[i].mType);
    }

    char* struct_name = NULL;

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

