#include "common.h"
#include <ctype.h>

BOOL expression_node(unsigned int* node, BOOL enable_assginment, sParserInfo* info)
{
    if(!parse_sharp(info)) {
        return FALSE;
    }

    if(*info->p == '(') {
        info->p++;
        skip_spaces_and_lf(info);

        char* p_before = info->p;
        int sline_before = info->sline;

        char buf[VAR_NAME_MAX+1];
        if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE))
        {
            return FALSE;
        }

        if(is_type_name(buf, info) && !get_variable_from_table(info->lv_table, buf)) {
            info->p = p_before;
            info->sline = sline_before;

            sNodeType* node_type = NULL;
            if(!parse_type(&node_type, info, NULL, FALSE, FALSE, NULL, FALSE))
            {
                return FALSE;
            }

            expect_next_character_with_one_forward(")", info);
            if(!expression_node(node, TRUE, info)) 
            {
                return FALSE;
            }

            if(*node == 0) {
                parser_err_msg(info, "require value for cast");
                info->err_num++;
            };

            *node = sNodeTree_create_cast(node_type, *node, info);
        }
        else {
            info->p = p_before;
            info->sline = sline_before;

            if(!expression(node, TRUE, info)) {
                return FALSE;
            }
            skip_spaces_and_lf(info);

            if(*node == 0) {
                parser_err_msg(info, "require expression as ( operand");
                info->err_num++;
            }

            expect_next_character_with_one_forward(")", info);
        }
    }
    else if(*info->p == '{') {
        sNodeBlock* node_block = NULL;
        if(!parse_block_easy(ALLOC &node_block, FALSE, info))
        {
            return FALSE;
        };

        *node = sNodeTree_create_normal_block(node_block, info);
    }
    else if(*info->p == '}' && strcmp(info->impl_struct_name, "") != 0)
    {
        info->p++;
        skip_spaces_and_lf(info);

        parse_impl_end(info);

        *node = sNodeTree_create_null(info);
    }
    else if(*info->p == '*') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!expression_node(node, FALSE, info)) 
        {
            return FALSE;
        }

        if(*node == 0) {
            parser_err_msg(info, "require value for *");
            info->err_num++;
        }

        if(*info->p == '=' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int node2 = 0;
            if(!expression(&node2, FALSE, info)) 
            {
                return FALSE;
            }

            if(*node == 0) {
                parser_err_msg(info, "require value for *");
                info->err_num++;
            };

            *node = sNodeTree_create_store_value_to_address(*node, node2, info);
        }
        else {
            *node = sNodeTree_create_dereffernce(*node, info);
        }
    }
    else if(*info->p == '@') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!expression_node(node, FALSE, info)) 
        {
            return FALSE;
        }

        if(*node == 0) {
            parser_err_msg(info, "require value for *");
            info->err_num++;
        }

        if(*info->p == '=' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int node2 = 0;
            if(!expression(&node2, FALSE, info)) 
            {
                return FALSE;
            }

            if(*node == 0) {
                parser_err_msg(info, "require value for *");
                info->err_num++;
            };

            *node = sNodeTree_create_write_channel(*node, node2, info);
        }
        else {
            *node = sNodeTree_create_read_channel(*node, info);
        }
    }
    else if(*info->p == '&') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!expression_node(node, TRUE, info)) {
            return FALSE;
        }

        if(*node == 0) {
            parser_err_msg(info, "require value for &");
            info->err_num++;
        };

        *node = sNodeTree_create_reffernce(*node, info);
    }
    else if(*info->p == '!') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!expression_node(node, TRUE, info)) {
            return FALSE;
        }

        if(*node == 0) {
            parser_err_msg(info, "require value for !");
            info->err_num++;
        };

        *node = sNodeTree_create_logical_denial(*node, 0, 0, info);
    }
    else if(*info->p == '~') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!expression_node(node, TRUE, info))
        {
            return FALSE;
        }

        if(*node == 0) {
            parser_err_msg(info, "require value for operator ~");
            info->err_num++;
        };

        *node = sNodeTree_create_complement(*node, info);
    }
    else if(*info->p == '+' && *(info->p+1) == '+')
    {
        info->p+=2;
        skip_spaces_and_lf(info);

        unsigned int exp = 0;
        if(!expression_node(&exp, TRUE, info)) {
            return FALSE;
        }

        if(gNodes[exp].mNodeType == kNodeTypeLoadVariable)
        {
            char var_name[VAR_NAME_MAX];

            xstrncpy(var_name, gNodes[exp].uValue.sLoadVariable.mVarName, VAR_NAME_MAX);

            unsigned int left_node = sNodeTree_create_load_variable(var_name, info);

            unsigned int right_node = sNodeTree_create_int_value(1, info);

            *node = sNodeTree_create_add(left_node, right_node, 0, info);

            BOOL global = info->mBlockLevel == 0;
            *node = sNodeTree_create_store_variable(var_name, *node, FALSE, global, info);
        }
        else if(gNodes[exp].mNodeType == kNodeTypeLoadField)
        {
            char var_name[VAR_NAME_MAX];
            xstrncpy(var_name, gNodes[exp].uValue.sLoadField.mVarName, VAR_NAME_MAX);

            unsigned int obj_node = gNodes[exp].mLeft;

            unsigned int right_node = sNodeTree_create_int_value(1, info);

            *node = sNodeTree_create_add(exp, right_node, 0, info);

            *node = sNodeTree_create_store_field(var_name, obj_node, *node, info);
        }
        else {
            parser_err_msg(info, "Invalid node for ++(1)");
            info->err_num++;

            *node = 0;
            return TRUE;
        }
    }
    else if(*info->p == '-' && *(info->p+1) == '-')
    {
        info->p+=2;
        skip_spaces_and_lf(info);

        unsigned int exp = 0;
        if(!expression_node(&exp, TRUE, info)) {
            return FALSE;
        }

        if(gNodes[exp].mNodeType == kNodeTypeLoadVariable)
        {
            char var_name[VAR_NAME_MAX];

            xstrncpy(var_name, gNodes[exp].uValue.sLoadVariable.mVarName, VAR_NAME_MAX);

            unsigned int left_node = sNodeTree_create_load_variable(var_name, info);
            unsigned int right_node = sNodeTree_create_int_value(1, info);

            *node = sNodeTree_create_sub(left_node, right_node, 0, info);

            BOOL global = info->mBlockLevel == 0;
            *node = sNodeTree_create_store_variable(var_name, *node, FALSE, global, info);
        }
        else if(gNodes[exp].mNodeType == kNodeTypeLoadField)
        {
            char var_name[VAR_NAME_MAX];

            xstrncpy(var_name, gNodes[exp].uValue.sLoadField.mVarName, VAR_NAME_MAX);

            unsigned int obj_node = gNodes[exp].mLeft;

            unsigned int right_node = sNodeTree_create_int_value(1, info);

            *node = sNodeTree_create_sub(exp, right_node, 0, info);

            *node = sNodeTree_create_store_field(var_name, obj_node, *node, info);
        }
        else {
            char buf[256];
            snprintf(buf, 256, "Invalid node for --(2) %d %d", exp, gNodes[exp].mNodeType);
            parser_err_msg(info, buf);
            info->err_num++;

            *node = 0;
            return TRUE;
        }
    }
    else if(*info->p == '-' && !xisdigit(*(info->p+1)))
    {
        info->p++;
        skip_spaces_and_lf(info);

        unsigned int zero_node = sNodeTree_create_int_value(0, info);

        unsigned int right_node = 0;
        if(!expression_node(&right_node, FALSE, info)) {
            return FALSE;
        };

        *node = sNodeTree_create_sub(zero_node, right_node, 0, info);
    }
    /// number ///
    else if((*info->p == '-' && *(info->p+1) != '=' && *(info->p+1) != '-' && *(info->p+1) != '>') || (*info->p == '+' && *(info->p+1) != '=' && *(info->p+1) != '+')) 
    {
        if(*info->p =='+') {
            info->p++;
            skip_spaces_and_lf(info);

            if(xisdigit(*info->p)) {
                if(!get_number(FALSE, node, info)) {
                    return FALSE;
                }
            }
            else {
                if(!expression_node(node, TRUE, info)) {
                    return FALSE;
                }

                if(*node == 0) {
                    parser_err_msg(info, "require right value for -");
                    info->err_num++;
                }
            }
        }
        else if(*info->p =='-') {
            info->p++;
            skip_spaces_and_lf(info);

            if(xisdigit(*info->p)) {
                if(!get_number(TRUE, node, info)) {
                    return FALSE;
                }
            }
            else {
                if(!expression_node(node, TRUE, info)) {
                    return FALSE;
                }

                if(*node == 0) {
                    parser_err_msg(info, "require right value for -");
                    info->err_num++;
                }
            }
        }
    }
    /// hex number ///
    else if(*info->p == '0' && *(info->p+1) == 'x') {
        info->p += 2;

        if(!get_hex_number(node, info)) {
            return FALSE;
        }
    }
    /// oct number ///
    else if(*info->p == '0' && xisdigit(*(info->p+1))) {
        info->p++;

        if(!get_oct_number(node, info)) {
            return FALSE;
        }
    }
    /// number ///
    else if(xisdigit(*info->p)) {
        if(!get_number(FALSE, node, info)) {
            return FALSE;
        }
    }
    /// c string ///
    else if(*info->p == '"') 
    {
        info->p++;

        int sline = info->sline;

        sBuf value;
        sBuf_init(&value);

        while(1) {
            if(*info->p == '"') {
                info->p++;
                break;
            }
            else if(*info->p == '\\') {
                info->p++;

                switch(*info->p) {
                    case '0':
                        sBuf_append_char(&value, '\0');
                        info->p++;
                        break;

                    case 'n':
                        sBuf_append_char(&value, '\n');
                        info->p++;
                        break;

                    case 't':
                        sBuf_append_char(&value, '\t');
                        info->p++;
                        break;

                    case 'r':
                        sBuf_append_char(&value, '\r');
                        info->p++;
                        break;

                    case 'a':
                        sBuf_append_char(&value, '\a');
                        info->p++;
                        break;

                    case '\\':
                        sBuf_append_char(&value, '\\');
                        info->p++;
                        break;

                    default:
                        sBuf_append_char(&value, *info->p);
                        info->p++;
                        break;
                }
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "close \" to make c string value");
                return FALSE;
            }
            else {
                if(*info->p == '\n') info->sline++;

                sBuf_append_char(&value, *info->p);
                info->p++;
            }
        }

        skip_spaces_and_lf(info);

        *node = sNodeTree_create_c_string_value(MANAGED value.mBuf, value.mLen, sline, info);
    }
    /// chararacter ///
    else if(*info->p == '\'') {
        info->p++;

        char c;

        if(*info->p == '\\') {
            info->p++;

            switch(*info->p) {
                case 'n':
                    c = '\n';
                    info->p++;
                    break;

                case 't':
                    c = '\t';
                    info->p++;
                    break;

                case 'r':
                    c = '\r';
                    info->p++;
                    break;

                case 'a':
                    c = '\a';
                    info->p++;
                    break;

                case '\\':
                    c = '\\';
                    info->p++;
                    break;

                case '0':
                    c = '\0';
                    info->p++;
                    break;

                default:
                    c = *info->p;
                    info->p++;
                    break;
            }
        }
        else {
            c = *info->p;
            info->p++;
        }

        if(*info->p != '\'') {
            parser_err_msg(info, "close \' to make character value");
            info->err_num++;
        }
        else {
            info->p++;

            skip_spaces_and_lf(info);

            *node = sNodeTree_create_character_value(c, info);
        }
    }
    else if(xisalpha(*info->p) || *info->p == '_') {
        char* p_before = info->p;
        int sline_before = info->sline;

        char buf[VAR_NAME_MAX+1];
        if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE))
        {
            return FALSE;
        }

        BOOL define_struct = FALSE;
        BOOL define_union  = FALSE;
        BOOL define_enum = FALSE;
        BOOL static_inline = FALSE;

        if(strcmp(buf, "__extension__") == 0 && *info->p != '(') {
            if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE))
            {
                return FALSE;
            }
        }

        if(strcmp(buf, "__attribute__") == 0) {
            int brace_num = 0;
            while(*info->p == '(') {
                info->p ++;
                skip_spaces_and_lf(info);
                brace_num++;
            }

            while(*info->p != ')') {
                info->p++;
            }

            while(*info->p == ')') {
                info->p ++;
                skip_spaces_and_lf(info);
            }

            p_before = info->p;
            sline_before = info->sline;

            if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE))
            {
                return FALSE;
            }
        }

        /// forwarding parse until terminated union, struct and enum
        if(strcmp(buf, "struct") == 0) {
            char* p_before2 = info->p;
            int sline_before2 = info->sline;

            char struct_name[VAR_NAME_MAX];
            if(*info->p == '{') {
                create_anonymous_name(struct_name, VAR_NAME_MAX);

                BOOL terminated = FALSE;
                BOOL anonymous = FALSE;
                BOOL definition_struct = FALSE;
                if(!parse_struct(node, struct_name, VAR_NAME_MAX, anonymous, &terminated, definition_struct, info)) {
                    return FALSE;
                }

                if(terminated) {
                    parser_err_msg(info, "undefined variable name");
                    return FALSE;
                }
            }
            else {
                xstrncpy(struct_name, "", VAR_NAME_MAX);

                BOOL terminated = FALSE;
                BOOL anonymous = FALSE;
                BOOL definition_struct = FALSE;
                if(!parse_struct(node, struct_name, VAR_NAME_MAX, anonymous, &terminated, definition_struct, info)) {
                    return FALSE;
                }

                if(terminated) {
                    define_struct = TRUE;
                }
            }

            info->p = p_before2;
            info->sline = sline_before2;
        }
        else if(strcmp(buf, "enum") == 0) {
            char* p_before2 = info->p;
            int sline_before2 = info->sline;

            char enum_name[VAR_NAME_MAX];
            if(*info->p == '{') {
                create_anonymous_name(enum_name, VAR_NAME_MAX);

                BOOL terminated = FALSE;
                if(!parse_enum(node, enum_name, VAR_NAME_MAX, &terminated, info)) {
                    return FALSE;
                }

                if(terminated) {
                    define_enum = TRUE;
                }
            }
            else {
                xstrncpy(enum_name, "", VAR_NAME_MAX);

                BOOL terminated = FALSE;
                if(!parse_enum(node, enum_name, VAR_NAME_MAX, &terminated, info)) {
                    return FALSE;
                }

                if(terminated) {
                    define_enum = TRUE;
                }
            }

            info->p = p_before2;
            info->sline = sline_before2;
        }
        else if(strcmp(buf, "union") == 0)
        {
            char* p_before2 = info->p;
            int sline_before2 = info->sline;

            char union_name[VAR_NAME_MAX];
            if(*info->p == '{') {
                create_anonymous_name(union_name, VAR_NAME_MAX);

                BOOL terminated = FALSE;
                BOOL definition_struct = FALSE;
                if(!parse_union(node, union_name, VAR_NAME_MAX, &terminated, definition_struct, info)) {
                    return FALSE;
                }

                if(terminated) {
                    parser_err_msg(info, "undefined variable name");
                    return FALSE;
                }
            }
            else {
                xstrncpy(union_name, "", VAR_NAME_MAX);

                BOOL terminated = FALSE;
                BOOL definition_struct = FALSE;
                if(!parse_union(node, union_name, VAR_NAME_MAX, &terminated, definition_struct, info)) {
                    return FALSE;
                }

                if(terminated) {
                    define_union = TRUE;
                }
            }

            info->p = p_before2;
            info->sline = sline_before2;
        }
        else if(strcmp(buf, "static") == 0) {
            char* p_before2 = info->p;
            int sline_before2 = info->sline;

            if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE))
            {
                return FALSE;
            }

            if(strcmp(buf, "inline") == 0 || strcmp(buf, "__inline") == 0 || strcmp(buf, "__inline__") == 0 || strcmp(buf, "__DARWIN_OS_INLINE") == 0)
            {
                static_inline = TRUE;
            }
            else {
                info->p = p_before2;
                info->sline = sline_before2;
            }
        }

        if(strcmp(buf, "__extension__") == 0 && *info->p == '(') {
            if(!expression(node, FALSE, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "__PRETTY_FUNCTION__") == 0) {
            *node = sNodeTree_create_c_string_value(MANAGED xstrdup(info->fun_name), strlen(info->fun_name), info->sline, info);
        }
        else if(strcmp(buf, "return") == 0) {
            if(!parse_return(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "__stack__") == 0) {
            *node = sNodeTree_create_stack(info);
        }
        else if(strcmp(buf, "macro") == 0) {
            if(!parse_macro(node, info))
            {
                return FALSE;
            }
        }
        else if(strcmp(buf, "defer") == 0) {
            if(!parse_defer(node, info))
            {
                return FALSE;
            }
        }
        else if(strcmp(buf, "struct") == 0 && *info->p != '{' && define_struct) {
            char struct_name[VAR_NAME_MAX];

            xstrncpy(struct_name, "", VAR_NAME_MAX);

            BOOL anonymous = FALSE;
            BOOL definition_struct = FALSE;
            if(!parse_struct(node, struct_name, VAR_NAME_MAX, anonymous, NULL, definition_struct, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "union") == 0 && *info->p != '{' && define_union) {
            char union_name[VAR_NAME_MAX];

            xstrncpy(union_name, "", VAR_NAME_MAX);

            BOOL definition_struct = FALSE;
            if(!parse_union(node, union_name, VAR_NAME_MAX, NULL, definition_struct, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "enum") == 0 && define_enum) {
            char enum_name[VAR_NAME_MAX];

            if(*info->p == '{') {
                create_anonymous_name(enum_name, VAR_NAME_MAX);

                if(!parse_enum(node, enum_name, VAR_NAME_MAX, NULL, info)) {
                    return FALSE;
                }
            }
            else {
                xstrncpy(enum_name, "", VAR_NAME_MAX);

                if(!parse_enum(node, enum_name, VAR_NAME_MAX, NULL, info)) {
                    return FALSE;
                }
            }
        }
        else if(strcmp(buf, "template") == 0) {
            if(strcmp(info->impl_struct_name, "") == 0)
            {
                if(!parse_method_generics_function(node, NULL, info)) {
                    return FALSE;
                }
            }
            else {
                if(!parse_method_generics_function(node, info->impl_struct_name, info)) {
                    return FALSE;
                }
            }
        }
        else if(strcmp(buf, "case") == 0) {
            if(!parse_case(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "default") == 0) {
            if(!parse_default(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "if") == 0) {
            if(!parse_if(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "switch") == 0) {
            if(!parse_switch(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "while") == 0) {
            if(!parse_while(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "do") == 0) {
            if(!parse_do(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "for") == 0) {
            if(!parse_for(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "true") == 0) {
            *node = sNodeTree_create_true(info);
        }
        else if(strcmp(buf, "false") == 0) {
            *node = sNodeTree_create_false(info);
        }
        else if(strcmp(buf, "null") == 0) {
            *node = sNodeTree_create_null(info);
        }
        else if(strcmp(buf, "clone") == 0) {
            if(!parse_clone(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "new") == 0) {
            if(!parse_new(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "auto") == 0) {
            if(!parse_var(node, info, FALSE)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "come") == 0) {
            if(!parse_come(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "delete") == 0) {
            if(!parse_delete(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "borrow") == 0) {
            if(!parse_borrow(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "nomove") == 0) {
            if(!parse_nomove(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "dummy_heap") == 0) {
            if(!parse_dummy_heap(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "managed") == 0) {
            if(!parse_managed(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "alloca") == 0 || strcmp(buf, "__builtin_alloca") == 0) {
            if(!parse_alloca(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "sizeof") == 0 && *info->p == '(') 
        {
            if(!parse_sizeof(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "__func__") == 0) 
        {
            *node = sNodeTree_create_func_name(info);
        }
        else if(strcmp(buf, "__alignof__") == 0 && *info->p == '(') 
        {
            if(!parse_alignof(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "clone") == 0) {
            if(!parse_clone(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "isheap") == 0) {
            if(!parse_is_heap(node, info)) {
                return FALSE;
            }
        }
        else if(info->mBlockLevel == 0 && strcmp(buf, "impl") == 0) {
            if(!parse_impl(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "inherit") == 0 && *info->p == '(') {
            if(!parse_inherit(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "typedef") == 0) {
            if(!parse_typedef(node, info)) {
                return FALSE;
            }
        }
        else if(strcmp(buf, "break") == 0) {
            *node = sNodeTree_create_break_expression(info);
        }
        else if(strcmp(buf, "continue") == 0) {
            *node = sNodeTree_create_continue_expression(info);
        }
        else if(strcmp(buf, "extern") == 0) {
            char* p = info->p;
            int sline = info->sline;

            char asm_fname[VAR_NAME_MAX];
            if(!parse_attribute(info, asm_fname)) {
                return FALSE;
            }
            
            sNodeType* result_type = NULL;
            char name[VAR_NAME_MAX+1];
            BOOL function_pointer_result_function = FALSE;
            if(!parse_type(&result_type, info, name, FALSE, FALSE, &function_pointer_result_function, FALSE))
            {
                return FALSE;
            }

            if(function_pointer_result_function) {
                info->p = p;
                info->sline = sline;

                if(!parse_function_pointer_result_function(node, info)) {
                    return FALSE;
                }
            }
            else if(name[0] != '\0') {
                BOOL extern_ = TRUE;
                if(!parse_variable(node, result_type, name, extern_, info, FALSE)) 
                {
                    return FALSE;
                }
            }
            else {
                unsigned int nodes[NODES_MAX];
                memset(nodes, 0, sizeof(unsigned int)*NODES_MAX);
                int num_nodes = 0;

                while(TRUE) {
                    sNodeType* result_type2 = clone_node_type(result_type);

                    if(!parse_variable_name(name, VAR_NAME_MAX, info, result_type2, TRUE, FALSE))
                    {
                        return FALSE;
                    }

                    if(*info->p == '(') {
                        char* struct_name = NULL;
                        if(!parse_function(node, result_type2, name, struct_name, info)) {
                            return FALSE;
                        }
                    }
                    else {
                        BOOL extern_ = TRUE;
                        if(!parse_variable(node, result_type2, name, extern_, info, FALSE)) {
                            return FALSE;
                        }
                    }

                    nodes[num_nodes++] = *node;

                    if(num_nodes >= NODES_MAX) {
                        fprintf(stderr, "overflow define variable max");
                        return FALSE;
                    }

                    if(*info->p == ',') {
                        info->p++;
                        skip_spaces_and_lf(info);
                    }
                    else {
                        break;
                    }
                }

                if(num_nodes > 1) {
                    *node = sNodeTree_create_nodes(nodes, num_nodes, info);
                }
            }
        }
        else if(static_inline || strcmp(buf, "inline") == 0 || strcmp(buf, "__inline") == 0 || strcmp(buf, "__inline__") == 0|| strcmp(buf, "__DARWIN_OS_INLINE") == 0) 
        {
            if(!parse_inline_function(node, NULL, info)) 
            {
                return FALSE;
            }
        }
        else if(strcmp(buf, "goto") == 0) {
            if(!parse_goto(node, info)) {
                return FALSE;
            }
        }
        else if(*info->p == ':' && !info->in_case && !info->in_conditional_operator) {
            if(!parse_label(node, buf, info)) {
                return FALSE;
            }
        }
        else if(*info->p == '!' && (*(info->p+1) == '(' || *(info->p+1) == '{' || *(info->p+1) == '[' || *(info->p+1) == '<'))
        {
            info->p++;
            skip_spaces_and_lf(info);

            if(!parse_call_macro(node, buf, info)) {
                return FALSE;
            }
        }
        /// local variable ///
        else if(get_variable_from_table(info->lv_table, buf))
        {
            if(enable_assginment && *info->p == '=' && *(info->p+1) != '=') {
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
                    *node = sNodeTree_create_store_variable(buf, right_node, FALSE, global, info);
                }
            }
            else if(*info->p == '+' && *(info->p+1) == '+')
            {
                info->p+=2;
                skip_spaces_and_lf(info);

                char var_name[VAR_NAME_MAX];

                xstrncpy(var_name, buf, VAR_NAME_MAX);

                unsigned int left_node = sNodeTree_create_load_variable(var_name, info);

                unsigned int right_node = sNodeTree_create_int_value(1, info);

                *node = sNodeTree_create_add(left_node, right_node, 0, info);

                BOOL global = info->mBlockLevel == 0;
                unsigned int left_node2 = sNodeTree_create_store_variable(var_name, *node, FALSE, global, info);

                unsigned int right_node2 = sNodeTree_create_int_value(1, info);

                *node = sNodeTree_create_sub(left_node2, right_node2, 0, info);
            }
            else if(*info->p == '-' && *(info->p+1) == '-')
            {
                info->p+=2;
                skip_spaces_and_lf(info);

                char var_name[VAR_NAME_MAX];

                xstrncpy(var_name, buf, VAR_NAME_MAX);

                unsigned int left_node = sNodeTree_create_load_variable(var_name, info);
                sVar* var_ = get_variable_from_table(info->lv_table, var_name);

                if(var_ && var_->mReadOnly) {
                    parser_err_msg(info, "This is readonly variable.");
                    info->err_num++;

                    *node = 0;
                    return TRUE;
                }

                unsigned int right_node = sNodeTree_create_int_value(1, info);

                *node = sNodeTree_create_sub(left_node, right_node, 0, info);

                BOOL global = info->mBlockLevel == 0;
                unsigned int left_node2 = sNodeTree_create_store_variable(var_name, *node, FALSE, global, info);

                unsigned int right_node2 = sNodeTree_create_int_value(1, info);

                *node = sNodeTree_create_add(left_node2, right_node2, 0, info);
            }
            else if(*info->p == '+' && *(info->p+1) == '=')
            {
                info->p+=2;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;
                if(!expression(&right_node, FALSE, info)) {
                    return FALSE;
                }

                char var_name[VAR_NAME_MAX];

                xstrncpy(var_name, buf, VAR_NAME_MAX);

                unsigned int left_node = sNodeTree_create_load_variable(var_name, info);

                *node = sNodeTree_create_add(left_node, right_node, 0, info);

                BOOL global = info->mBlockLevel == 0;
                unsigned int left_node2 = sNodeTree_create_store_variable(var_name, *node, FALSE, global, info);

                *node = sNodeTree_create_sub(left_node2, right_node, 0, info);
            }
            else if(*info->p == '-' && *(info->p+1) == '=')
            {
                info->p+=2;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;
                if(!expression(&right_node, FALSE, info)) {
                    return FALSE;
                }

                char var_name[VAR_NAME_MAX];

                xstrncpy(var_name, buf, VAR_NAME_MAX);

                unsigned int left_node = sNodeTree_create_load_variable(var_name, info);

                *node = sNodeTree_create_sub(left_node, right_node, 0, info);

                BOOL global = info->mBlockLevel == 0;
                unsigned int left_node2 = sNodeTree_create_store_variable(var_name, *node, FALSE, global, info);

                *node = sNodeTree_create_add(left_node2, right_node, 0, info);
            }
            else if(*info->p == '*' && *(info->p+1) == '=')
            {
                info->p+=2;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;
                if(!expression(&right_node, FALSE, info)) {
                    return FALSE;
                }

                char var_name[VAR_NAME_MAX];

                xstrncpy(var_name, buf, VAR_NAME_MAX);

                unsigned int left_node = sNodeTree_create_load_variable(var_name, info);

                *node = sNodeTree_create_mult(left_node, right_node, 0, info);

                BOOL global = info->mBlockLevel == 0;
                *node = sNodeTree_create_store_variable(var_name, *node, FALSE, global, info);
            }
            else if(*info->p == '/' && *(info->p+1) == '=')
            {
                info->p+=2;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;
                if(!expression(&right_node, FALSE, info)) {
                    return FALSE;
                }

                char var_name[VAR_NAME_MAX];

                xstrncpy(var_name, buf, VAR_NAME_MAX);

                unsigned int left_node = sNodeTree_create_load_variable(var_name, info);

                *node = sNodeTree_create_div(left_node, right_node, 0, info);

                BOOL global = info->mBlockLevel == 0;
                *node = sNodeTree_create_store_variable(var_name, *node, FALSE, global, info);
            }
            else if(*info->p == '%' && *(info->p+1) == '=')
            {
                info->p+=2;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;
                if(!expression(&right_node, FALSE, info)) {
                    return FALSE;
                }

                char var_name[VAR_NAME_MAX];

                xstrncpy(var_name, buf, VAR_NAME_MAX);

                unsigned int left_node = sNodeTree_create_load_variable(var_name, info);

                *node = sNodeTree_create_mod(left_node, right_node, 0, info);

                BOOL global = info->mBlockLevel == 0;
                *node = sNodeTree_create_store_variable(var_name, *node, FALSE, global, info);
            }
            else if(*info->p == '<' && *(info->p+1) == '<' && *(info->p+2) == '=')
            {
                info->p+=3;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;
                if(!expression(&right_node, FALSE, info)) {
                    return FALSE;
                }

                char var_name[VAR_NAME_MAX];

                xstrncpy(var_name, buf, VAR_NAME_MAX);

                unsigned int left_node = sNodeTree_create_load_variable(var_name, info);

                *node = sNodeTree_create_left_shift(left_node, right_node, 0, info);

                BOOL global = info->mBlockLevel == 0;
                *node = sNodeTree_create_store_variable(var_name, *node, FALSE, global, info);
            }
            else if(*info->p == '>' && *(info->p+1) == '>' && *(info->p+2) == '=')
            {
                info->p+=3;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;
                if(!expression(&right_node, FALSE, info)) {
                    return FALSE;
                }

                char var_name[VAR_NAME_MAX];

                xstrncpy(var_name, buf, VAR_NAME_MAX);

                unsigned int left_node = sNodeTree_create_load_variable(var_name, info);

                *node = sNodeTree_create_right_shift(left_node, right_node, 0, info);

                BOOL global = info->mBlockLevel == 0;
                *node = sNodeTree_create_store_variable(var_name, *node, FALSE, global, info);
            }
            else if(*info->p == '&' && *(info->p+1) == '=')
            {
                info->p+=2;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;
                if(!expression(&right_node, FALSE, info)) {
                    return FALSE;
                }

                char var_name[VAR_NAME_MAX];

                xstrncpy(var_name, buf, VAR_NAME_MAX);

                unsigned int left_node = sNodeTree_create_load_variable(var_name, info);

                *node = sNodeTree_create_and(left_node, right_node, 0, info);

                BOOL global = info->mBlockLevel == 0;
                *node = sNodeTree_create_store_variable(var_name, *node, FALSE, global, info);
            }
            else if(*info->p == '^' && *(info->p+1) == '=')
            {
                info->p+=2;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;
                if(!expression(&right_node, FALSE, info)) {
                    return FALSE;
                }

                char var_name[VAR_NAME_MAX];

                xstrncpy(var_name, buf, VAR_NAME_MAX);

                unsigned int left_node = sNodeTree_create_load_variable(var_name, info);

                *node = sNodeTree_create_xor(left_node, right_node, 0, info);

                BOOL global = info->mBlockLevel == 0;
                *node = sNodeTree_create_store_variable(var_name, *node, FALSE, global, info);
            }
            else if(*info->p == '|' && *(info->p+1) == '=')
            {
                info->p+=2;
                skip_spaces_and_lf(info);

                unsigned int right_node = 0;
                if(!expression(&right_node, FALSE, info)) {
                    return FALSE;
                }

                char var_name[VAR_NAME_MAX];

                xstrncpy(var_name, buf, VAR_NAME_MAX);

                unsigned int left_node = sNodeTree_create_load_variable(var_name, info);

                *node = sNodeTree_create_or(left_node, right_node, 0, info);

                BOOL global = info->mBlockLevel == 0;
                *node = sNodeTree_create_store_variable(var_name, *node, FALSE, global, info);
            }
            else if(*info->p == '(')
            {
                unsigned int params[PARAMS_MAX];
                int num_params = 0;

                if(!parse_funcation_call_params(&num_params, params, info)) 
                {
                    return FALSE;
                };

                *node = sNodeTree_create_load_variable(buf, info);

                *node = sNodeTree_create_lambda_call(*node, params, num_params, info);
            }
            else {
                *node = sNodeTree_create_load_variable(buf, info);
            }
        }
        else if(is_type_name(buf, info) || strcmp(buf, "typeof") == 0) 
        {
            info->p = p_before;
            info->sline = sline_before;

            char* p = info->p;
            int sline = info->sline;

            char buf_before[VAR_NAME_MAX];

            xstrncpy(buf_before, buf, VAR_NAME_MAX);

            sNodeType* result_type = NULL;
            char name[VAR_NAME_MAX+1];
            BOOL function_pointer_result_function = FALSE;
            if(!parse_type(&result_type, info, name, FALSE, FALSE, &function_pointer_result_function, FALSE)) 
            {
                return FALSE;
            }

            if(function_pointer_result_function) {
                info->p = p;
                info->sline = sline;

                if(!parse_function_pointer_result_function(node, info)) {
                    return FALSE;
                }
            }
            else if(strcmp(name, "lambda") == 0) {
                char buf[VAR_NAME_MAX];
                (void)parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE);
                if(!parse_lambda(node, result_type, info)) {
                    return FALSE;
                }
            }
            else if(name[0] != '\0') {
                BOOL extern_ = FALSE;
                if(!parse_variable(node, result_type, name, extern_, info, FALSE)) 
                {
                    return FALSE;
                }
            }
            else if(*info->p == '(' || *info->p == '{') {
                char* fun_name = buf_before;

                unsigned int params[PARAMS_MAX];
                int num_params = 0;

                if(!parse_funcation_call_params(&num_params, params, info)) 
                {
                    return FALSE;
                }

                if(strcmp(fun_name, "va_start") == 0) {
                    num_params = 1;
                };

                *node = sNodeTree_create_function_call(fun_name, params, num_params, FALSE, FALSE, info->mFunVersion, info);
            }
            else {
                unsigned int nodes[NODES_MAX];
                memset(nodes, 0, sizeof(unsigned int)*NODES_MAX);
                int num_nodes = 0;

                while(TRUE) {
                    sNodeType* result_type2 = clone_node_type(result_type);

                    if(!parse_variable_name(name, VAR_NAME_MAX, info, result_type2, TRUE, FALSE))
                    {
                        return FALSE;
                    }

                    if(*info->p == '(') {
                        char* struct_name = NULL;
                        if(strcmp(info->impl_struct_name, "") != 0)
                        {
                            struct_name = info->impl_struct_name;
                        }

                        if(info->mNumGenerics > 0) {
                            if(!parse_generics_function(node, result_type2, name, struct_name, info)) {
                                return FALSE;
                            }
                        }
                        else {
                            if(!parse_function(node, result_type2, name, struct_name, info)) {
                                return FALSE;
                            }
                        }
                    }
                    else {
                        BOOL extern_ = FALSE;
                        if(!parse_variable(node, result_type2, name, extern_, info, FALSE)) {
                            return FALSE;
                        }
                    }

                    nodes[num_nodes++] = *node;

                    if(num_nodes >= NODES_MAX) {
                        fprintf(stderr, "overflow define variable max");
                        return FALSE;
                    }

                    if(*info->p == ',') {
                        info->p++;
                        skip_spaces_and_lf(info);
                    }
                    else {
                        break;
                    }
                }

                if(num_nodes > 1) {
                    *node = sNodeTree_create_nodes(nodes, num_nodes, info);
                }
            }
        }
        else if(*info->p == '(') {
                char* fun_name = buf;

                unsigned int params[PARAMS_MAX];
                int num_params = 0;

                if(!parse_funcation_call_params(&num_params, params, info)) 
                {
                    return FALSE;
                }

                if(strcmp(fun_name, "va_start") == 0) {
                    num_params = 1;
                };

                *node = sNodeTree_create_function_call(fun_name, params, num_params, FALSE, FALSE, info->mFunVersion, info);
        }
        else {
            *node = sNodeTree_create_load_function(buf, info, sline_before);
        }
    }
    else if(*info->p == '(') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!expression(node, TRUE, info)) {
            return FALSE;
        }
        skip_spaces_and_lf(info);

        if(*node == 0) {
            parser_err_msg(info, "require expression as ( operand");
            info->err_num++;
        }

        expect_next_character_with_one_forward(")", info);
    }
    else {
        char msg[1024];
        snprintf(msg, 1024, "invalid character (character code %d) (%c)", *info->p, *info->p);
        parser_err_msg(info, msg);

        if(*info->p == '\n') info->sline++;
        info->p++;
        skip_spaces_and_lf(info);

        info->err_num++;

        *node = 0;
    }

    /// post position expression ///
    if(!postposition_operator(node, enable_assginment, info))
    {
        return FALSE;
    }

    if(!parse_sharp(info)) {
        return FALSE;
    }

    return TRUE;
}
