#include "common.h"
#include <ctype.h>

BOOL parse_struct(unsigned int* node, char* struct_name, int size_struct_name, BOOL anonymous, BOOL* terminated, BOOL definition_struct, sParserInfo* info) 
{
    BOOL inhibits_rehash_classes = gInhibitsRehashClasses;
    gInhibitsRehashClasses = TRUE;

    char sname[PATH_MAX];
    xstrncpy(sname, info->sname, PATH_MAX);

    int sline = info->sline;

    int num_fields = 0;
    char* field_names[STRUCT_FIELD_MAX];
    sNodeType* fields[STRUCT_FIELD_MAX];

    BOOL in_struct = info->in_struct;
    info->in_struct = TRUE;

    /// already get struct name ///
    if(strcmp(struct_name, "") == 0) {
        char buf[VAR_NAME_MAX];

        if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE)) {
            info->in_struct = in_struct;
            return FALSE;
        }

        xstrncpy(struct_name, buf, size_struct_name);
    }

    info->mNumGenerics = 0;

    /// undefined struct ///
    if(*info->p == ';') {
        if(terminated) {
            *terminated = TRUE;
            info->in_struct = in_struct;
            return TRUE;
        }

        sCLClass* struct_class = get_class(struct_name);

        if(struct_class == NULL) {
            struct_class = alloc_struct(struct_name, anonymous, TRUE);


            sNodeType* struct_type = create_node_type_with_class_pointer(struct_class);
            BOOL undefined_struct = TRUE;
            *node = sNodeTree_struct(struct_type, info, sname, sline, undefined_struct);
        }
        else {
            *node = sNodeTree_create_null(info);
        }

        xstrncpy(info->parse_struct_name, struct_name, VAR_NAME_MAX);

        info->in_struct = in_struct;
        return TRUE;
    }

    if(*info->p == '*') {
        if(terminated) {
            *terminated = FALSE;
            info->in_struct = in_struct;
            return TRUE;
        }
    }

    if(xisalpha(*info->p) || *info->p == '_') {
        if(terminated) {
            *terminated = FALSE;
            info->in_struct = in_struct;
            return TRUE;
        }
    }

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

    sCLClass* struct_class = get_class(struct_name);

    if(struct_class == NULL) {
        struct_class = alloc_struct(struct_name, anonymous, TRUE);
    }

    xstrncpy(info->parse_struct_name, struct_name, VAR_NAME_MAX);

    int n = 0;
    while(TRUE) {
        if(*info->p == '#') {
            if(!parse_sharp(info)) {
                info->in_struct = in_struct;
                return FALSE;
            }
        }
        char asm_fname[VAR_NAME_MAX];
        if(!parse_attribute(info, asm_fname)) {
            info->in_struct = in_struct;
            return FALSE;
        }

        sNodeType* field = NULL;
        char buf[VAR_NAME_MAX];
        if(!parse_type(&field, info, buf, FALSE, TRUE, NULL, FALSE)) {
            info->in_struct = in_struct;
            return FALSE;
        }

        if(!parse_attribute(info, asm_fname)) {
            info->in_struct = in_struct;
            return FALSE;
        }

        char saved_buf[VAR_NAME_MAX];
        xstrncpy(saved_buf, buf, VAR_NAME_MAX);

        sNodeType* saved_field = clone_node_type(field);

        fields[num_fields] = field;

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);

            create_anonymous_name(buf, VAR_NAME_MAX);
        }
        else if(buf[0] == '\0') {
            if(!parse_variable_name(buf, VAR_NAME_MAX, info, field, FALSE, FALSE))
            {
                info->in_struct = in_struct;
                return FALSE;
            }
        }

        if(!parse_attribute(info, asm_fname)) {
            info->in_struct = in_struct;
            return FALSE;
        }

        field_names[num_fields] = strdup(buf);

        num_fields++;

        if(num_fields >= STRUCT_FIELD_MAX) {
            parser_err_msg(info, "overflow struct field");

            int i;
            for(i=0; i<num_fields; i++) {
                free(field_names[i]);
            }
            info->in_struct = in_struct;
            return FALSE;
        }

        if(*info->p == ',') {
            while(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
                char buf2[VAR_NAME_MAX];
                xstrncpy(buf2, saved_buf, VAR_NAME_MAX);

                sNodeType* field2 = clone_node_type(saved_field);

                fields[num_fields] = field2;

                if(buf2[0] == '\0') {
                    if(!parse_variable_name(buf2, VAR_NAME_MAX, info, field2, FALSE, FALSE))
                    {
                        int i;
                        for(i=0; i<num_fields; i++) {
                            free(field_names[i]);
                        }
                        info->in_struct = in_struct;
                        return FALSE;
                    }
                }

                field_names[num_fields] = strdup(buf2);

                num_fields++;

                if(num_fields >= STRUCT_FIELD_MAX) {
                    parser_err_msg(info, "overflow struct field");
                    int i;
                    for(i=0; i<num_fields; i++) {
                        free(field_names[i]);
                    }
                    info->in_struct = in_struct;
                    return FALSE;
                }
            }
        }

        if(!parse_attribute(info, asm_fname)) {
            int i;
            for(i=0; i<num_fields; i++) {
                free(field_names[i]);
            }
            info->in_struct = in_struct;
            return FALSE;
        }

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);
        }

        if(*info->p == '}') {
            info->p++;
            skip_spaces_and_lf(info);
            break;
        }
        else if(*info->p == '#') {
            if(!parse_sharp(info)) {
                int i;
                for(i=0; i<num_fields; i++) {
                    free(field_names[i]);
                }
                info->in_struct = in_struct;
                return FALSE;
            }

            if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
        }
    }

    char asm_fname[VAR_NAME_MAX];
    if(!parse_attribute(info, asm_fname)) {
        info->in_struct = in_struct;
        return FALSE;
    }

    if(*info->p == ';') {
        if(!definition_struct) {
            info->p++;
            skip_spaces_and_lf(info);
        }

        if(terminated) {
            *terminated = TRUE;
            info->in_struct = in_struct;
            return TRUE;
        }
    }

    if(terminated == NULL) {
        add_fields_to_struct(struct_class, num_fields, field_names, fields);
    }

    int i;
    for(i=0; i<num_fields; i++) {
        free(field_names[i]);
    }

    sNodeType* struct_type = create_node_type_with_class_pointer(struct_class);

    BOOL undefined_struct = FALSE;

    *node = sNodeTree_struct(struct_type, info, sname, sline, undefined_struct);

    if(!parse_attribute(info, asm_fname)) {
        info->in_struct = in_struct;
        return FALSE;
    }

    info->mNumGenerics = 0;

    info->in_struct = in_struct;

    gInhibitsRehashClasses = inhibits_rehash_classes;

    return TRUE;
}

BOOL parse_union(unsigned int* node, char* union_name, int size_union_name, BOOL* terminated, BOOL definition_struct, sParserInfo* info) 
{
    BOOL inhibits_rehash_classes = gInhibitsRehashClasses;
    gInhibitsRehashClasses = TRUE;

    char sname[PATH_MAX];
    xstrncpy(sname, info->sname, PATH_MAX);

    int sline = info->sline;

    int num_fields = 0;
    char* field_names[STRUCT_FIELD_MAX];
    sNodeType* fields[STRUCT_FIELD_MAX];

    /// already get name ///
    if(strcmp(union_name, "") == 0) {
        char buf[VAR_NAME_MAX];

        if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE)) {
            return FALSE;
        }

        xstrncpy(union_name, buf, size_union_name);
    }

    /// undefined union ///
    if(*info->p == ';') {
        if(terminated) {
            *terminated = TRUE;
            return TRUE;
        }

        sCLClass* union_class = alloc_union(union_name, FALSE, FALSE);

        xstrncpy(info->parse_struct_name, union_name, VAR_NAME_MAX);

        sNodeType* union_type = create_node_type_with_class_pointer(union_class);
        BOOL undefined_union = TRUE;
        *node = sNodeTree_union(union_type, info, sname, sline, undefined_union);

        return TRUE;
    }

    if(*info->p == '*') {
        if(terminated) {
            *terminated = FALSE;
            info->in_struct = FALSE;
            return TRUE;
        }
    }

    if(xisalpha(*info->p) || *info->p == '_') {
        if(terminated) {
            *terminated = FALSE;
            return TRUE;
        }
    }

    expect_next_character_with_one_forward("{", info);

    sCLClass* union_class = get_class(union_name);

    if(union_class == NULL) {
        union_class = alloc_union(union_name, FALSE, FALSE);
    }

    xstrncpy(info->parse_struct_name, union_name, VAR_NAME_MAX);

    int n = 0;
    while(TRUE) {
        if(*info->p == '#') {
            if(!parse_sharp(info)) {
                return FALSE;
            }
        }
        char asm_fname[VAR_NAME_MAX];
        if(!parse_attribute(info, asm_fname)) {
            return FALSE;
        }

        sNodeType* field = NULL;
        char buf[VAR_NAME_MAX];
        if(!parse_type(&field, info, buf, FALSE, TRUE, NULL, FALSE)) {
            return FALSE;
        }

        if(!parse_attribute(info, asm_fname)) {
            return FALSE;
        }

        char saved_buf[VAR_NAME_MAX];
        xstrncpy(saved_buf, buf, VAR_NAME_MAX);

        sNodeType* saved_field = clone_node_type(field);

        fields[num_fields] = field;

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);

            create_anonymous_name(buf, VAR_NAME_MAX);
        }
        else if(buf[0] == '\0') {
            if(!parse_variable_name(buf, VAR_NAME_MAX, info, field, FALSE, FALSE))
            {
                return FALSE;
            }
        }

        if(!parse_attribute(info, asm_fname)) {
            return FALSE;
        }

        field_names[num_fields] = strdup(buf);

        num_fields++;

        if(num_fields >= STRUCT_FIELD_MAX) {
            parser_err_msg(info, "overflow struct field");

            int i;
            for(i=0; i<num_fields; i++) {
                free(field_names[i]);
            }
            return FALSE;
        }

        if(*info->p == ',') {
            while(*info->p == ',') {
                info->p++;
                skip_spaces_and_lf(info);
                char buf2[VAR_NAME_MAX];
                xstrncpy(buf2, saved_buf, VAR_NAME_MAX);

                sNodeType* field2 = clone_node_type(saved_field);

                fields[num_fields] = field2;

                if(buf2[0] == '\0') {
                    if(!parse_variable_name(buf2, VAR_NAME_MAX, info, field2, FALSE, FALSE))
                    {
                        int i;
                        for(i=0; i<num_fields; i++) {
                            free(field_names[i]);
                        }
                        return FALSE;
                    }
                }

                field_names[num_fields] = strdup(buf2);

                num_fields++;

                if(num_fields >= STRUCT_FIELD_MAX) {
                    parser_err_msg(info, "overflow struct field");
                    int i;
                    for(i=0; i<num_fields; i++) {
                        free(field_names[i]);
                    }
                    return FALSE;
                }
            }
        }

        if(!parse_attribute(info, asm_fname)) {
            int i;
            for(i=0; i<num_fields; i++) {
                free(field_names[i]);
            }
            return FALSE;
        }

        if(*info->p == ';') {
            info->p++;
            skip_spaces_and_lf(info);
        }

        if(*info->p == '}') {
            info->p++;
            skip_spaces_and_lf(info);
            break;
        }
        else if(*info->p == '#') {
            if(!parse_sharp(info)) {
                int i;
                for(i=0; i<num_fields; i++) {
                    free(field_names[i]);
                }
                return FALSE;
            }

            if(*info->p == '}') {
                info->p++;
                skip_spaces_and_lf(info);
                break;
            }
        }
    }

    char asm_fname[VAR_NAME_MAX];
    if(!parse_attribute(info, asm_fname)) {
        return FALSE;
    }

    if(*info->p == ';') {
        if(!definition_struct) {
            info->p++;
            skip_spaces_and_lf(info);
        }

        if(terminated) {
            *terminated = TRUE;
            return TRUE;
        }
    }

    if(terminated == NULL) {
        add_fields_to_union(union_class, num_fields, field_names, fields);
    }

    int i;
    for(i=0; i<num_fields; i++) {
        free(field_names[i]);
    }

    sNodeType* union_type = create_node_type_with_class_pointer(union_class);

    BOOL undefined_union = FALSE;

    *node = sNodeTree_union(union_type, info, sname, sline, undefined_union);

    if(!parse_attribute(info, asm_fname)) {
        return FALSE;
    }

    gInhibitsRehashClasses = inhibits_rehash_classes;

    return TRUE;
}

void create_lambda_name(char* lambda_name, size_t size_lambda_name, char* module_name)
{
    static int num_lambda_name = 0;
    xstrncpy(lambda_name, "lambda", size_lambda_name);

    char buf[128];
    snprintf(buf, 128, "%d", num_lambda_name++);

    xstrncat(lambda_name, buf, size_lambda_name);
}

BOOL parse_lambda(unsigned int* node, sNodeType* result_type, sParserInfo* info)
{
    int sline = info->sline;
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

    sNodeBlock* node_block = ALLOC sNodeBlock_alloc();

    sVarTable* old_table = info->lv_table;

    info->lv_table = init_block_vtable(NULL, FALSE);
    sVarTable* block_var_table = info->lv_table;

    int i;
    for(i=0; i<num_params; i++) {
        sParserParam* param = params + i;

        BOOL readonly = TRUE;
        if(!add_variable_to_table(info->lv_table, param->mName, param->mType, readonly, NULL, -1, FALSE, param->mType->mConstant))
        {
            return FALSE;
        }
    }

    expect_next_character_with_one_forward("{", info);

    BOOL single_expression = FALSE;
    if(!parse_block(node_block, FALSE, single_expression, info)) {
        sNodeBlock_free(node_block);
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

    info->lv_table = old_table;

    char fun_name[VAR_NAME_MAX];
    create_lambda_name(fun_name, VAR_NAME_MAX, info->module_name);

    BOOL lambda_ = TRUE;
    BOOL simple_lambda_param = FALSE;
    BOOL construct_fun = FALSE;
    BOOL operator_fun = FALSE;

    result_type->mStatic = TRUE;

    *node = sNodeTree_create_function(fun_name, "", params, num_params, result_type, MANAGED node_block, lambda_, block_var_table, NULL, operator_fun, construct_fun, simple_lambda_param, info, FALSE, FALSE, 0, FALSE, -1, fun_name, sline);

    return TRUE;
}

BOOL parse_enum(unsigned int* node, char* name, int name_size, BOOL* terminated, sParserInfo* info) 
{
    /// already get enum name ///
    if(strcmp(name, "") == 0) {
        char buf[VAR_NAME_MAX];

        if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE)) {
            return FALSE;
        }

        xstrncpy(name, buf, name_size);
    }

    expect_next_character_with_one_forward("{", info);

    BOOL no_comma_operator = info->no_comma_operator;
    info->no_comma_operator = TRUE;

    int num_element = 0;
    char** element_names = calloc(1, sizeof(char*)*ENUM_ELEMENT_MAX);
    int* element_values = calloc(1, sizeof(int)*ENUM_ELEMENT_MAX);
    int value = 0;

    while(TRUE) {
        char asm_fname[VAR_NAME_MAX];
        if(!parse_attribute(info, asm_fname)) {
            return FALSE;
        }

        char var_name[VAR_NAME_MAX];
        if(!parse_word(var_name, VAR_NAME_MAX, info, TRUE, FALSE)) 
        {
            return FALSE;
        }
        if(!parse_attribute(info, asm_fname)) {
            return FALSE;
        }

        if(*info->p == '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int node2;
            if(!expression(&node2, FALSE, info)) {
                return FALSE;
            }

            if(terminated == NULL) {
                if(!get_const_value_from_node(&value, node2, info)) {
                    fprintf(stderr, "%s %d: can't create const value(x)\n", info->sname, info->sline);
                    exit(1);
                }
            }
        }

        if(terminated == NULL) {
            sVar* var_ = get_variable_from_this_table_only(info->lv_table, var_name);

            if(var_ == NULL) {
                unsigned int right_node = sNodeTree_create_int_value(value, info);

                BOOL alloc_ = TRUE;
                BOOL global = info->mBlockLevel == 0;
                unsigned int node = sNodeTree_create_store_variable(var_name, right_node, alloc_, global, info);

                sNodeType* result_type = create_node_type_with_class_name("int");
                result_type->mConstant = TRUE;

                check_already_added_variable(info->lv_table, var_name, info);
                BOOL readonly = TRUE;
                if(!add_variable_to_table(info->lv_table, var_name, result_type, readonly, NULL, -1, info->mBlockLevel == 0, result_type->mConstant))
                {
                    fprintf(stderr, "overflow variable table\n");
                    exit(2);
                }

                sCompileInfo cinfo;

                memset(&cinfo, 0, sizeof(sCompileInfo));
                cinfo.no_output = FALSE;
                cinfo.pinfo = info;

                if(!compile(node, &cinfo)) {
                    return FALSE;
                }

                dec_stack_ptr(1, &cinfo);
            }
        }

        if(*info->p == ',') {
            info->p++;
            skip_spaces_and_lf(info);
        }

        element_values[num_element] = value;
        element_names[num_element] = strdup(var_name);

        if(num_element >= ENUM_ELEMENT_MAX) {
            fprintf(stderr, "overflow enum element number\n");
            exit(2);
        }

        num_element++;

        if(*info->p == '}') {
            info->p++;
            skip_spaces_and_lf(info);
            break;
        }

        value++;
    }

    if(*info->p == ';') {
        info->p++;
        skip_spaces_and_lf(info);

        if(terminated) {
            *terminated = TRUE;

            return TRUE;
        }
    }

    *node = sNodeTree_create_null(info);

    (void)alloc_enum(name, num_element, element_names, element_values);

    info->no_comma_operator = no_comma_operator;

    int k;
    for(k=0; k<num_element; k++) {
        free(element_names[k]);
    }
    free(element_names);
    free(element_values);

    return TRUE;
}

BOOL is_type_name(char* buf, sParserInfo* info)
{
    if(strcmp(buf, "") == 0) {
        return FALSE;
    }

    sCLClass* klass = get_class(buf);
    sNodeType* node_type = get_typedef(buf);

    int i;
    BOOL generics_type_name = FALSE;
    for(i=0; i<info->mNumGenerics; i++) {
        if(strcmp(buf, info->mGenericsTypeNames[i]) == 0)
        {
            generics_type_name = TRUE;
        }
    }

    BOOL method_type_name = FALSE;
    for(i=0; i<info->mNumMethodGenericsTypes; i++) {
        if(strcmp(buf, info->mMethodGenericsTypeNames[i]) == 0)
        {
            method_type_name = TRUE;
        }
    }

    return klass || node_type || generics_type_name || method_type_name || strcmp(buf, "const") == 0 || strcmp(buf, "static") == 0|| (strcmp(buf, "struct") == 0 && *info->p == '{') || (strcmp(buf, "struct") == 0) || (strcmp(buf, "union") == 0) || (strcmp(buf, "union") == 0 && *info->p == '{') || (strcmp(buf, "unsigned") == 0) || (strcmp(buf, "signed") == 0) || (strcmp(buf, "__signed") == 0) ||(strcmp(buf, "short") == 0) || (strcmp(buf, "long") == 0) || (strcmp(buf, "signed") == 0) || (strcmp(buf, "register") == 0) || (strcmp(buf, "volatile") == 0) || strcmp(buf, "enum") == 0 || strcmp(buf, "__signed__") == 0 || (strcmp(buf, "__extension__") == 0 && *info->p != '(') || (strcmp(buf, "__uniq__") == 0)|| strcmp(buf, "typeof") == 0|| strcmp(buf, "_Noreturn") == 0 || strcmp(buf, "_Alignas") == 0;
}

BOOL is_premitive_type(char* buf, sParserInfo* info)
{
    sCLClass* klass = get_class(buf);

    if(klass == NULL) {
        return FALSE;
    }

    return klass->mFlags & CLASS_FLAGS_PRIMITIVE;
}

BOOL parse_return(unsigned int* node, sParserInfo* info)
{
    *node = 0;

    if(*info->p == '(') {
        info->p++;
        skip_spaces_and_lf(info);

        if(!expression(node, TRUE, info)) {
            return FALSE;
        }

        expect_next_character_with_one_forward(")", info);
        expect_next_character_with_one_forward(";", info);
    }
    else if(*info->p != ';') {
        if(!expression(node, TRUE, info)) {
            return FALSE;
        }
    };

    *node = sNodeTree_create_return(*node, info);

    return TRUE;
}

BOOL parse_variable(unsigned int* node, sNodeType* result_type, char* name, BOOL extern_, sParserInfo* info, BOOL readonly)
{
    /// assign the value to a variable ///
    if(*info->p == '=' && *(info->p+1) != '=') {
        info->p++;
        skip_spaces_and_lf(info);

        if(result_type->mArrayDimentionNum > 0) {
            if(type_identify_with_class_name(result_type, "char") && result_type->mPointerNum == 0) {
                if(*info->p == '{') {
                    info->p++;
                    skip_spaces_and_lf(info);
                }
            }
            else {
                expect_next_character_with_one_forward("{", info);
            }

            BOOL no_comma_operator = info->no_comma_operator;
            info->no_comma_operator = TRUE;

            unsigned int initialize_array_values[INIT_ARRAY_MAX];
            int num_initialize_array_value = 0;
            memset(initialize_array_values, 0, sizeof(unsigned int)*INIT_ARRAY_MAX);

            while(TRUE) {
                unsigned int right_node = 0;

                if(!expression(&right_node, FALSE, info)) {
                    return FALSE;
                }

                if(right_node == 0) {
                    parser_err_msg(info, "Require right value for {}");
                    info->err_num++;

                    *node = 0;
                }
                else {
                    initialize_array_values[num_initialize_array_value++] = right_node;

                    if(num_initialize_array_value >= INIT_ARRAY_MAX) {
                        fprintf(stderr, "overflow array initializer number\n");
                        exit(2);
                    }
                }

                if(*info->p == ',') {
                    info->p++;
                    skip_spaces_and_lf(info);
                }
                else if(*info->p == '\0') {
                    parser_err_msg(info, "In the array initialization, the parser has arraived at the source end");
                    return FALSE;
                }
                else if(*info->p == '}') {
                    info->p++;
                    skip_spaces_and_lf(info);
                    break;
                }
                else if(type_identify_with_class_name(result_type, "char") && result_type->mPointerNum == 0) {
                    if(*info->p == '}') {
                        info->p++;
                        skip_spaces_and_lf(info);
                    }
                    break;
                }
            }

            info->no_comma_operator = no_comma_operator;

            if(info->mBlockLevel == 0) {
                *node = sNodeTree_create_define_variable(name, extern_, info->mBlockLevel == 0, info);

                *node = sNodeTree_create_array_initializer(name, num_initialize_array_value, initialize_array_values, *node, info);
            }
            else {
                unsigned int nodes[INIT_ARRAY_MAX+128];
                int num_nodes = 0;

                nodes[num_nodes++] = sNodeTree_create_define_variable(name, extern_, info->mBlockLevel == 0, info);

                unsigned int array_node = sNodeTree_create_load_variable(name, info);

                int num_dimention = result_type->mArrayDimentionNum;

                if(num_dimention == 1) {
                    if(type_identify_with_class_name(result_type, "char") && result_type->mPointerNum == 0 && num_initialize_array_value == 1 && gNodes[initialize_array_values[0]].mNodeType == kNodeTypeCString) 
                    {
                        unsigned int node = initialize_array_values[0];

                        char* str = gNodes[node].uValue.sString.mString;

                        if(strlen(str)+1 >= INIT_ARRAY_MAX) {
                            parser_err_msg(info, "invalid array initializer");
                            info->err_num++;
                            return FALSE;
                        }

                        int i;
                        for(i=0; i<strlen(str); i++) {
                            initialize_array_values[i] = sNodeTree_create_character_value(str[i], info);
                        }
                        initialize_array_values[i] = sNodeTree_create_character_value('\0', info);

                        num_initialize_array_value = strlen(str)+1;
                    }

                    int i;
                    for(i=0; i<num_initialize_array_value; i++) {
                        unsigned int index_node[ARRAY_DIMENTION_MAX];

                        index_node[0] = sNodeTree_create_int_value(i, info);
                        unsigned int right_node = initialize_array_values[i];

                        nodes[num_nodes++] = sNodeTree_create_store_element(array_node, index_node, num_dimention, right_node, info);

                        if(num_nodes >= INIT_ARRAY_MAX+128) {
                            fprintf(stderr, "overflow array initializer number\n");
                            exit(2);
                        }
                    }

                    *node = sNodeTree_create_nodes(nodes, num_nodes, info);
                }
                else if(num_dimention == 2) {
                    int i;
                    for(i=0; i<num_initialize_array_value; i++) {
                        unsigned int index_node[ARRAY_DIMENTION_MAX];

                        index_node[0] = sNodeTree_create_int_value(i/result_type->mArrayNum[1], info);
                        index_node[1] = sNodeTree_create_int_value(i%result_type->mArrayNum[1], info);

                        unsigned int right_node = initialize_array_values[i];

                        nodes[num_nodes++] = sNodeTree_create_store_element(array_node, index_node, num_dimention, right_node, info);

                        if(num_nodes >= INIT_ARRAY_MAX+128) {
                            fprintf(stderr, "overflow array initializer number\n");
                            exit(2);
                        }
                    }

                    *node = sNodeTree_create_nodes(nodes, num_nodes, info);
                }
                else if(num_dimention == 3) {
                    int i;
                    for(i=0; i<num_initialize_array_value; i++) {
                        unsigned int index_node[ARRAY_DIMENTION_MAX];

                        int n = result_type->mArrayNum[1]*result_type->mArrayNum[2];

                        index_node[0] = sNodeTree_create_int_value(i/n, info);
                        index_node[1] = sNodeTree_create_int_value((i/result_type->mArrayNum[2])%result_type->mArrayNum[1], info);
                        index_node[2] = sNodeTree_create_int_value(i%result_type->mArrayNum[2], info);

                        unsigned int right_node = initialize_array_values[i];

                        nodes[num_nodes++] = sNodeTree_create_store_element(array_node, index_node, num_dimention, right_node, info);

                        if(num_nodes >= INIT_ARRAY_MAX+128) {
                            fprintf(stderr, "overflow array initializer number\n");
                            exit(2);
                        }
                    }

                    *node = sNodeTree_create_nodes(nodes, num_nodes, info);
                }
            }
        }
        else {
            unsigned int right_node = 0;

            if(!expression(&right_node, FALSE, info)) {
                return FALSE;
            }

            if(right_node == 0) {
                parser_err_msg(info, "Require right value for =");
                info->err_num++;

                *node = 0;
            }
            else {
                BOOL global = info->mBlockLevel == 0;
                *node = sNodeTree_create_store_variable(name, right_node, TRUE, global, info);
            }
        }
    }
    else {
        if(*info->p != ',' && *info->p != ';' && isascii(*info->p)) 
        {
            char msg[1024];
            snprintf(msg, 1024, "Require right value for , or ;. This is %c", *info->p);
            parser_err_msg(info, msg);
            info->err_num++;

            *node = 0;
        }
        else {
            *node = sNodeTree_create_define_variable(name, extern_, info->mBlockLevel == 0, info);
        }
    }

    check_already_added_variable(info->lv_table, name, info);
    if(!add_variable_to_table(info->lv_table, name, result_type, readonly, NULL, -1, info->mBlockLevel == 0, result_type->mConstant))
    {
        fprintf(stderr, "overflow variable table\n");
        exit(2);
    }

    return TRUE;
}
