#include "common.h"
#include <ctype.h>

void parser_init()
{
}

void parser_final()
{
}

int parse_cmp(char* p, char* str)
{
    int len = strlen(str);

    int i;
    for(i=0; i<len; i++) {
        if(*p > *str) {
            return 1;
        }
        else if(*p < *str) {
            return -1;
        }

        p++;
        str++;
    }

    if((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') || *p == '_')
    {
        return 1;
    }

    return 0;
}

void parser_err_msg(sParserInfo* info, char* msg)
{
    static int output_num = 0;

    if(output_num < PARSER_ERR_MSG_MAX && !info->no_output_err_msg) {
        puts(msg);
        fprintf(stderr, "%s:%d: %s\n", info->sname, info->sline, msg);
    }

    output_num++;
}

void skip_spaces_and_lf(sParserInfo* info)
{
    while(TRUE) {
        if(*info->p == ' ' || *info->p == '\t') {
            info->p++;
        }
        else if(*info->p == '\n') {
            info->p++;
            info->sline++;
        }
        else {
            break;
        }
    }
}

void skip_spaces(sParserInfo* info)
{
    while(*info->p == ' ' || *info->p == '\t') {
        info->p++;
    }
}

BOOL parse_word(char* buf, int buf_size, sParserInfo* info, BOOL print_out_err_msg, BOOL no_skip_lf)
{
    while(*info->p == '#') {
        if(!parse_sharp(info)) {
            return FALSE;
        }
    }

    buf[0] = 0;

    char* p2 = buf;

    if(xisalpha(*info->p) || *info->p == '_') {
        while(xisalnum(*info->p) || *info->p == '_' || *info->p == '$') {
            if(p2 - buf < buf_size-1) {
                *p2++ = *info->p;
                info->p++;
            }
            else {
                parser_err_msg(info, "length of word is too long");
                return FALSE;
            }
        }
    };

    *p2 = 0;
    if(no_skip_lf) {
        skip_spaces(info);
    }
    else {
        skip_spaces_and_lf(info);
    }

    if(*info->p == 0 && buf[0] == 0) {
        if(print_out_err_msg) {
            parser_err_msg(info, "require word(alphabet or number). this is the end of source");
        }
        return FALSE;
    }

    if(buf[0] == 0) {
        if(print_out_err_msg) {
            char buf[1024];
            snprintf(buf, 1024, "require word(alphabet or _ or number). this is (%c)", *info->p);
            parser_err_msg(info, buf);
            info->err_num++;
        }

        if(*info->p == '\n') info->sline++;

        info->p++;
    }

    while(*info->p == '#') {
        if(!parse_sharp(info)) {
            return FALSE;
        }
    }


    return TRUE;
}

void expect_next_character_with_one_forward(char* characters, sParserInfo* info)
{
    skip_spaces_and_lf(info);

    while(*info->p == '#') {
        (void)parse_sharp(info);
    }

    BOOL found = FALSE;
    char* p2 = characters;
    while(*p2) {
        if(*info->p == *p2) {
            found = TRUE;
        }
        p2++;
    }

    if(found) {
        info->p++;
        skip_spaces_and_lf(info);
    }
    else {
        char buf[1024];
        snprintf(buf, 1024, "expected that next character is (%s), but it is %c(%d)", characters, *info->p, *info->p);
        parser_err_msg(info, buf);
        info->err_num++;
        info->p++;
        skip_spaces_and_lf(info);

        int f = 0;
        int a = 1;
        int x = a/f;
    }

    while(*info->p == '#') {
        (void)parse_sharp(info);
    }
}

static BOOL skip_paren(char head_char, char tail_char, sParserInfo* info)
{
    if(*info->p == head_char) {
        info->p++;

        BOOL dquort = FALSE;
        BOOL squort = FALSE;
        int sline = 0;
        int nest = 0;
        while(1) {
            if(dquort) {
                if(*info->p == '\\') {
                    info->p++;
                    if(*info->p == '\0') {
                        fprintf(stderr, "%s %d: unexpected the source end. close single quote or double quote.", info->sname, sline);
                        return FALSE;
                    }
                    info->p++;
                }
                else if(*info->p == '"') {
                    info->p++;
                    dquort = !dquort;
                }
                else {
                    info->p++;

                    if(*info->p == '\0') {
                        fprintf(stderr, "%s %d: unexpected the source end. close single quote or double quote.", info->sname, sline);
                        return FALSE;
                    }
                }
            }
            else if(squort) {
                if(*info->p == '\\') {
                    info->p++;
                    if(*info->p == '\0') {
                        fprintf(stderr, "%s %d: unexpected the source end. close single quote or double quote.", info->sname, sline);
                        return FALSE;
                    }
                    info->p++;
                }
                else if(*info->p == '\'') {
                    info->p++;
                    squort = !squort;
                }
                else {
                    info->p++;

                    if(*info->p == '\0') {
                        fprintf(stderr, "%s %d: unexpected the source end. close single quote or double quote.", info->sname, sline);
                        return FALSE;
                    }
                }
            }
            else if(*info->p == '\'') {
                sline = info->sline;
                info->p++;
                squort = !squort;
            }
            else if(*info->p == '"') {
                sline = info->sline;
                info->p++;
                dquort = !dquort;
            }
            else if(*info->p == head_char) {
                info->p++;

                nest++;
            }
            else if(*info->p == tail_char) {
                info->p++;

                if(nest == 0) {
                    skip_spaces_and_lf(info);
                    break;
                }

                nest--;
            }
            else if(*info->p == '\0') {
                char msg[1024];
                snprintf(msg, 1024, "The block requires %c character for closing block", tail_char);
                parser_err_msg(info, msg);
                info->err_num++;
                return TRUE;
            }
            else if(*info->p == '\n') {
                info->p++;
                info->sline++;
            }
            else {
                info->p++;
            }
        }
    }

    return TRUE;
}

static BOOL get_number(BOOL minus, unsigned int* node, sParserInfo* info)
{
    const int buf_size = 128;
    char buf[128+1];
    char* p2 = buf;

    if(minus) {
        *p2 = '-';
        p2++;
    }

    if(xisdigit(*info->p)) {
        while(xisdigit(*info->p) || *info->p == '_') {
            if(*info->p ==  '_') {
                info->p++;
            }
            else {
                *p2++ = *info->p;
                info->p++;
            }

            if(p2 - buf >= buf_size) {
                parser_err_msg(info, "overflow node of number");
                return FALSE;
            }
        };
        *p2 = 0;
        skip_spaces_and_lf(info);

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

                    *node = sNodeTree_create_ulong_value(atoll(buf), info);
                }
                else {
                    *node = sNodeTree_create_ulong_value(atoll(buf), info);
                }
            }
            else {
                *node = sNodeTree_create_uint_value(atoi(buf), info);
            }
        }
        else if(*info->p == 'L' || *info->p == 'l') {
            info->p++;
            skip_spaces_and_lf(info);

            if(*info->p == 'L' || *info->p == 'l')
            {
                info->p++;
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_long_value(atoll(buf), info);
            }
            else if(*info->p == 'U' || *info->p == 'u')
            {
                info->p++;
                skip_spaces_and_lf(info);

                *node = sNodeTree_create_ulong_value(atoll(buf), info);
            }
            else {
                *node = sNodeTree_create_long_value(atoll(buf), info);
            }
        }
        else {
            *node = sNodeTree_create_int_value(atoi(buf), info);
        }
    }
    else {
        parser_err_msg(info, "require digits after + or -");
        info->err_num++;

        *node = 0;
    }

    return TRUE;
}

static void create_anonymous_name(char* name, int name_size)
{
    static int n = 0;
    snprintf(name, name_size, "come_anon%d", n++);
}

static BOOL parse_type(sNodeType** result_type, sParserInfo* info, char* func_pointer_name, BOOL definition_typedef, BOOL definition_struct);

static BOOL parse_attribute(sParserInfo* info, char* asm_fname)
{
    asm_fname[0] = '\0';

    while(TRUE) {
        if(parse_cmp(info->p, "__attribute_pure__") == 0) {
            info->p += 18;
            skip_spaces_and_lf(info);
        }
        else if(parse_cmp(info->p, "__wur") == 0) {
            info->p += 5;
            skip_spaces_and_lf(info);
        }
        else if(parse_cmp(info->p, "__noreturn") == 0) {
            info->p += 10;
            skip_spaces_and_lf(info);
        }
        else if(parse_cmp(info->p, "__attribute__") == 0) {
            info->p += 13;
            skip_spaces_and_lf(info);

            int brace_num = 0;
            while(*info->p) {
                if(*info->p == '(') {
                    info->p++;
                    brace_num++;
                }
                else if(*info->p == ')') {
                    info->p++;
                    brace_num--;

                    if(brace_num == 0) {
                        break;
                    }
                }
                else {
                    info->p++;
                }
            }

            skip_spaces_and_lf(info);
        }
        else if(parse_cmp(info->p, "__asm__") == 0) {
            info->p += 7;
            skip_spaces_and_lf(info);

            int len = 0;
            asm_fname[len] = '\0';

            BOOL in_dquort = FALSE;
            int brace_num = 0;
            while(*info->p) {
                if(*info->p == '"') {
                    info->p++;

                    in_dquort = !in_dquort;
                }
                else if(in_dquort) {
                    asm_fname[len++] = *info->p++;
                    asm_fname[len] = '\0';
                }
                else if(*info->p == '(') {
                    info->p++;
                    brace_num++;
                }
                else if(*info->p == ')') {
                    info->p++;
                    brace_num--;

                    if(brace_num == 0) {
                        break;
                    }
                }
                else {
                    info->p++;
                }
            }

            skip_spaces_and_lf(info);
        }
#ifdef __DARWIN__
        else if(parse_cmp(info->p, "__asm") == 0) {
            info->p += 5;
            skip_spaces_and_lf(info);
            int len = 0;
            asm_fname[len] = '\0';

            if(*info->p == '(') {
                info->p++;
                skip_spaces_and_lf(info);
            }

            BOOL in_dquort = FALSE;
            BOOL first_underbar = TRUE;
            while(*info->p) {
                if(*info->p == '"') {
                    info->p++;

                    in_dquort = !in_dquort;
                }
                else if(in_dquort) {
                    if(first_underbar) {
                        info->p++;
                        first_underbar = FALSE;
                    }
                    else {
                        asm_fname[len++] = *info->p++;
                        asm_fname[len] = '\0';
                    }
                }
                else if(*info->p == ')') {
                    info->p++;
                    skip_spaces_and_lf(info);
                    break;
                }
                else {
                    info->p++;
                }
            }
        }
#else
        else if(parse_cmp(info->p, "__asm") == 0) {
            info->p += 5;
            skip_spaces_and_lf(info);

            int brace_num = 0;
            while(*info->p) {
                if(*info->p == '(') {
                    info->p++;
                    brace_num++;
                }
                else if(*info->p == ')') {
                    info->p++;
                    brace_num--;

                    if(brace_num == 0) {
                        break;
                    }
                }
                else {
                    info->p++;
                }
            }

            skip_spaces_and_lf(info);
        }
#endif
        else {
            break;
        }
    }

    return TRUE;
}

static BOOL parse_typedef_attribute(sParserInfo* info)
{
    while(TRUE) {
        if(parse_cmp(info->p, "__attribute__") == 0) {
            info->p += 13;
            skip_spaces_and_lf(info);

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
        }
        else {
            break;
        }
    }

    return TRUE;
}

static BOOL parse_variable_name(char* buf, int buf_size, sParserInfo* info, sNodeType* node_type, BOOL array_size_is_dynamic, BOOL param_in_function)
{
    if(*info->p == '#') {
        if(!parse_sharp(info)) {
            return FALSE;
        }
    }

    if(*info->p == '*') {
        int num_pointers = 0;
        while(*info->p == '*') {
            info->p++;
            skip_spaces_and_lf(info);
            num_pointers++;
        }

        node_type->mPointerNum = num_pointers;
    }

    if(*info->p == '[') {
        buf[0] = '\0';
    }
    else if(*info->p == ':' && info->in_struct) {
        buf[0] = '\0';
    }
    else {
        if(!parse_word(buf, buf_size, info, TRUE, FALSE)) {
            return FALSE;
        }

        if(*info->p == ':' && *(info->p+1) == ':') {
            info->p+=2;
            skip_spaces_and_lf(info);

            char buf2[VAR_NAME_MAX];

            if(!parse_word(buf2, VAR_NAME_MAX, info, TRUE, FALSE)) {
                return FALSE;
            }

            strncat(buf, "_", buf_size);
            strncat(buf, buf2, buf_size);
        }

        if(strcmp(buf, "const") == 0) {
            if(!parse_word(buf, buf_size, info, TRUE, FALSE)) {
                return FALSE;
            }
        }
    }

    if(*info->p == '[') {
        info->p++;
        skip_spaces_and_lf(info);

        if(*info->p == ']') {
            info->p++;
            skip_spaces_and_lf(info);

            node_type->mPointerNum++;
            node_type->mArrayDimentionNum = 0;
        }
        else {
            unsigned int array_size_node = 0;

            if(!expression(&array_size_node, FALSE, info)) {
                return FALSE;
            }

            int array_size = 0;
            if(!get_const_value_from_node(&array_size, array_size_node, info))
            {
                if(array_size_is_dynamic && info->mBlockLevel > 0) {
                    node_type->mDynamicArrayNum = array_size_node;
                    expect_next_character_with_one_forward("]", info);

                    return TRUE;
                }
                else {
                    parser_err_msg(info, "Require Consta Value for array size");
                    info->err_num++;
                    return TRUE;
                }
            }

            if(param_in_function) {
                expect_next_character_with_one_forward("]", info);

                node_type->mPointerNum++;
            }
            else {
                expect_next_character_with_one_forward("]", info);

                node_type->mArrayDimentionNum = 1;
                node_type->mArrayNum[0] = array_size;

                while(*info->p == '[') {
                    info->p++;
                    skip_spaces_and_lf(info);

                    unsigned int array_size_node = 0;

                    if(!expression(&array_size_node, FALSE, info)) {
                        return FALSE;
                    }

                    int array_size = 0;
                    if(!get_const_value_from_node(&array_size, array_size_node, info))
                    {
                        parser_err_msg(info, "Require Consta Value for array size");
                        info->err_num++;
                        return TRUE;
                    }

                    node_type->mArrayNum[node_type->mArrayDimentionNum] = array_size;
                    node_type->mArrayDimentionNum++;

                    if(node_type->mArrayDimentionNum >= ARRAY_DIMENTION_MAX) 
                    {
                        parser_err_msg(info, "overflow array dimetion number");
                        return FALSE;
                    }

                    expect_next_character_with_one_forward("]", info);
                }
            }
        }
    }

    if(*info->p == ':' && info->in_struct) {
        info->p++;
        skip_spaces_and_lf(info);

        int n = 0;
        while(xisdigit(*info->p)) {
            n = n * 10 + *info->p - '0';
            info->p++;
        }
        skip_spaces_and_lf(info);

        node_type->mSizeNum = n;
    }

    char asm_fname[VAR_NAME_MAX];
    if(!parse_attribute(info, asm_fname)) {
        return FALSE;
    }

    return TRUE;
}

BOOL parse_annotation(sParserInfo* info)
{
    if(*info->p == '`') {
        info->p++;
        skip_spaces_and_lf(info);

        if(xisalpha(*info->p)) {
            info->p++;
            while(xisalnum(*info->p) || *info->p == '_') {
                info->p++;
            }
            skip_spaces_and_lf(info);
        }
    }

    return TRUE;
}

BOOL parse_sharp(sParserInfo* info)
{
    skip_spaces_and_lf(info);

    if(!parse_annotation(info)) {
        return FALSE;
    }

    if(*info->p == '#') {
        info->p++;
        skip_spaces_and_lf(info);

        if(xisdigit(*info->p)) {
            int line = 0;
            char fname[PATH_MAX];

            while(xisdigit(*info->p)) {
                line = line * 10 + (*info->p - '0');
                info->p++;
            }
            skip_spaces_and_lf(info);

            if(*info->p == '"') {
                info->p++;

                char* p = fname;

                while(*info->p != '"') {
                    *p++ = *info->p++;
                };
                *p = '\0';

                while(*info->p != '\n') {
                    info->p++;
                }
                info->p++;
            }

            info->sline = line;
            xstrncpy(info->sname, fname, PATH_MAX);
            info->change_sline = TRUE;

            skip_spaces_and_lf(info);
        }
        else {
            while(TRUE) {
                if(*info->p == '\n') {
                    info->p++;
                    break;
                }
                else if(*info->p == '\0') {
                    break;
                }
                else {
                    info->p++;
                }
            }
        }

        skip_spaces_and_lf(info);
    }

    return TRUE;
}

static BOOL parse_struct(unsigned int* node, char* struct_name, int size_struct_name, BOOL anonymous, BOOL* terminated, BOOL definition_struct, sParserInfo* info) 
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
            struct_class = alloc_struct(struct_name, anonymous);


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
        struct_class = alloc_struct(struct_name, anonymous);
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
        if(!parse_type(&field, info, buf, FALSE, TRUE)) {
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

static BOOL parse_union(unsigned int* node, char* union_name, int size_union_name, BOOL* terminated, BOOL definition_struct, sParserInfo* info) 
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
        if(!parse_type(&field, info, buf, FALSE, TRUE)) {
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

static BOOL parse_params(sParserParam* params, int* num_params, sParserInfo* info, int character_type, BOOL* var_arg);

static void create_lambda_name(char* lambda_name, size_t size_lambda_name, char* module_name)
{
    static int num_lambda_name = 0;
    xstrncpy(lambda_name, "lambda", size_lambda_name);

    char buf[128];
    snprintf(buf, 128, "%d", num_lambda_name++);

    xstrncat(lambda_name, buf, size_lambda_name);
}

static BOOL parse_lambda(unsigned int* node, sNodeType* result_type, sParserInfo* info)
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
    expect_next_character_with_one_forward("{", info);
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

    BOOL single_expression = FALSE;
    if(*info->p == '{') {
        info->p++;
    }
    else {
        single_expression = TRUE;
    }

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

    if(gNCType) {
        if(*info->p != '\0') {
            expect_next_character_with_one_forward("}", info);
        }
    }
    else {
        expect_next_character_with_one_forward("}", info);
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

static BOOL parse_enum(unsigned int* node, char* name, int name_size, BOOL* terminated, sParserInfo* info) 
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

        if(*info->p == '}') {
            info->p++;
            skip_spaces_and_lf(info);
            break;
        }

        element_values[num_element] = value;
        element_names[num_element] = strdup(var_name);

        if(num_element >= ENUM_ELEMENT_MAX) {
            fprintf(stderr, "overflow enum element number\n");
            exit(2);
        }

        num_element++;

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

static BOOL is_type_name(char* buf, sParserInfo* info)
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

    return klass || node_type || generics_type_name || method_type_name || strcmp(buf, "const") == 0 || strcmp(buf, "static") == 0|| (strcmp(buf, "struct") == 0 && *info->p == '{') || (strcmp(buf, "struct") == 0) || (strcmp(buf, "union") == 0) || (strcmp(buf, "union") == 0 && *info->p == '{') || (strcmp(buf, "unsigned") == 0) || (strcmp(buf, "signed") == 0) || (strcmp(buf, "__signed") == 0) ||(strcmp(buf, "short") == 0) || (strcmp(buf, "long") == 0) || (strcmp(buf, "signed") == 0) || (strcmp(buf, "register") == 0) || (strcmp(buf, "volatile") == 0) || strcmp(buf, "enum") == 0 || strcmp(buf, "__signed__") == 0 || (strcmp(buf, "__extension__") == 0 && *info->p != '(') || (strcmp(buf, "__uniq__") == 0)|| strcmp(buf, "typeof") == 0|| strcmp(buf, "_Noreturn") == 0 || strcmp(buf, "_Alignas") == 0 || strcmp(buf, "override") == 0;
}

static BOOL is_premitive_type(char* buf, sParserInfo* info)
{
    sCLClass* klass = get_class(buf);

    if(klass == NULL) {
        return FALSE;
    }

    return klass->mFlags & CLASS_FLAGS_PRIMITIVE;
}


static BOOL parse_type(sNodeType** result_type, sParserInfo* info, char* func_pointer_name, BOOL definition_typedef, BOOL definition_struct)
{
    if(func_pointer_name) {
        func_pointer_name[0] = '\0';
    }

    BOOL uniq = FALSE;

    if(parse_cmp(info->p, "__extension__") == 0)
    {
        info->p += 13;
        skip_spaces_and_lf(info);
    }
    if(parse_cmp(info->p, "__uniq__") == 0)
    {
        uniq = TRUE;
        info->p += 8;
        skip_spaces_and_lf(info);
    }
    if(parse_cmp(info->p, "_Noreturn") == 0)
    {
        info->p += 9;
        skip_spaces_and_lf(info);
    }
    if(parse_cmp(info->p, "_Alignas") == 0)
    {
        info->p += 8;
        skip_spaces_and_lf(info);

        expect_next_character_with_one_forward("(", info);
        while(xisdigit(*info->p)) {
            info->p++;
            skip_spaces_and_lf(info);
        }
        expect_next_character_with_one_forward(")", info);
    }


    char type_name[VAR_NAME_MAX];

    *result_type = NULL;

    BOOL heap = FALSE;
    BOOL nullable = FALSE;
    BOOL constant = FALSE;
    BOOL unsigned_ = FALSE;
    BOOL long_ = FALSE;
    BOOL short_ = FALSE;
    BOOL long_long = FALSE;
    BOOL register_ = FALSE;
    BOOL volatile_ = FALSE;
    BOOL static_ = FALSE;
    BOOL signed_ = FALSE;
    BOOL no_heap = FALSE;
    BOOL managed_ = FALSE;
    BOOL override_ = 0;
    BOOL channel = FALSE;
    int pointer_num = 0;

    while(TRUE) {
        char* p_before = info->p;
        int sline_before = info->sline;

        if(!parse_word(type_name, VAR_NAME_MAX, info, FALSE, FALSE)) 
        {
            return FALSE;
        }

        if(strcmp(type_name, "const") == 0) {
            constant = TRUE;
        }
        else if(strcmp(type_name, "unsigned") == 0) {
            unsigned_ = TRUE;
        }
        else if(strcmp(type_name, "signed") == 0 || strcmp(type_name, "__signed__") == 0 || strcmp(type_name, "__signed") == 0) {
            unsigned_ = FALSE;
            signed_ = TRUE;
        }
        else if(strcmp(type_name, "register") == 0) {
            register_ = TRUE;
        }
        else if(strcmp(type_name, "volatile") == 0) {
            volatile_ = TRUE;
        }
        else if(strcmp(type_name, "static") == 0) {
            static_ = TRUE;
        }
        else if(strcmp(type_name, "override") == 0) {
            override_ = TRUE;
        }
        else {
            info->p = p_before;
            info->sline = sline_before;
            break;
        }
    }

    BOOL only_signed_unsigned = FALSE;
    if(unsigned_ || signed_) {
        char* p_before = info->p;
        int sline_before = info->sline;

        char buf[VAR_NAME_MAX+1];
        if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE))
        {
            return FALSE;
        }

        if(is_premitive_type(buf, info)) {
            info->p = p_before;
            info->sline = sline_before;

            if(!parse_word(type_name, VAR_NAME_MAX, info, TRUE, FALSE)) 
            {
                return FALSE;
            }
        }
        else {
            info->p = p_before;
            info->sline = sline_before;

            only_signed_unsigned = TRUE;
        }
    }
    else {
        if(!parse_word(type_name, VAR_NAME_MAX, info, TRUE, FALSE)) 
        {
            return FALSE;
        }
    }

    if(only_signed_unsigned) {
        *result_type = create_node_type_with_class_name("int");
    }
    else {
        if(strcmp(type_name, "long") == 0) {
            if(parse_cmp(info->p, "unsigned") == 0)
            {
                long_ = TRUE;
                unsigned_ = TRUE;

                if(!parse_word(type_name, VAR_NAME_MAX, info, TRUE, FALSE)) 
                {
                    return FALSE;
                }

                if(!parse_word(type_name, VAR_NAME_MAX, info, TRUE, FALSE)) 
                {
                    return FALSE;
                }
            }
            else if(parse_cmp(info->p, "int") == 0 || parse_cmp(info->p, "double") == 0) 
            {
                long_ = TRUE;

                if(!parse_word(type_name, VAR_NAME_MAX, info, TRUE, FALSE)) 
                {
                    return FALSE;
                }
            }
            else if(parse_cmp(info->p, "long") == 0) {
                long_ = TRUE;

                if(!parse_word(type_name, VAR_NAME_MAX, info, TRUE, FALSE)) 
                {
                    return FALSE;
                }

                if(strcmp(type_name, "long") == 0) {
                    char* p = info->p;
                    int sline = info->sline;

                    if(!parse_word(type_name, VAR_NAME_MAX, info, FALSE, FALSE)) 
                    {
                        return FALSE;
                    }

                    long_long = TRUE;

                    if(strcmp(type_name, "int") == 0)
                    {
                        long_long = TRUE;
                    }
                    else if(!is_type_name(type_name, info))
                    {
                        info->p = p;
                        info->sline = sline;

                        *result_type = create_node_type_with_class_name("int");

                        long_long = TRUE;
                    }
                    else {
                        long_long = TRUE;
                        
                        *result_type = create_node_type_with_class_name("int");

                        info->p = p;
                        info->sline = sline;
                    }
                }
            }
        }
        else if(strcmp(type_name, "short") == 0)
        {
            char* p = info->p;
            int sline = info->sline;

            if(!parse_word(type_name, VAR_NAME_MAX, info, FALSE, FALSE)) 
            {
                return FALSE;
            }

            if(strcmp(type_name, "int") == 0)
            {
                short_ = TRUE;
            }
            else if(!is_type_name(type_name, info))
            {
                info->p = p;
                info->sline = sline;

                *result_type = create_node_type_with_class_name("int");

                short_ = TRUE;
            }
            else {
                info->p = p;
                info->sline = sline;

                *result_type = create_node_type_with_class_name("int");

                short_ = TRUE;
            }
        }
        else if(strcmp(type_name, "struct") == 0)
        {
            if(xisalpha(*info->p) || *info->p == '_') {
                char struct_name[VAR_NAME_MAX];

                if(!parse_word(struct_name, VAR_NAME_MAX, info, FALSE, FALSE))
                {
                    return FALSE;
                }

                if(*info->p == '{') {
                    unsigned int node = 0;
                    BOOL anonymous = FALSE;
                    if(!parse_struct(&node, struct_name, VAR_NAME_MAX, anonymous, NULL, definition_struct, info)) {
                        return FALSE;
                    }

                    sCompileInfo cinfo;

                    memset(&cinfo, 0, sizeof(sCompileInfo));
                    cinfo.no_output = FALSE;
                    cinfo.pinfo = info;

                    if(!compile(node, &cinfo)) {
                        return FALSE;
                    }
                }
                else {
                    sCLClass* klass = get_class(struct_name);

                    if(klass == NULL) {
                        BOOL anonymous = FALSE;
                        klass = alloc_struct(struct_name, anonymous);


                        sNodeType* struct_type = create_node_type_with_class_pointer(klass);
                        BOOL undefined_struct = TRUE;
                        unsigned int node = sNodeTree_struct(struct_type, info, info->sname, info->sline, undefined_struct);

                        sCompileInfo cinfo;

                        memset(&cinfo, 0, sizeof(sCompileInfo));
                        cinfo.no_output = FALSE;
                        cinfo.pinfo = info;

                        if(!compile(node, &cinfo)) {
                            return FALSE;
                        }
                    }
                }

                xstrncpy(type_name,  struct_name, VAR_NAME_MAX);
            }
            else if(*info->p == '{') {
                char struct_name[VAR_NAME_MAX];

                create_anonymous_name(struct_name, VAR_NAME_MAX);

                unsigned int node = 0;
                BOOL anonymous = TRUE;
                if(!parse_struct(&node, struct_name, VAR_NAME_MAX, anonymous, NULL, definition_struct, info)) {
                    return FALSE;
                }

                sCompileInfo cinfo;

                memset(&cinfo, 0, sizeof(sCompileInfo));
                cinfo.no_output = FALSE;
                cinfo.pinfo = info;

                if(!compile(node, &cinfo)) {
                    return FALSE;
                }

                xstrncpy(type_name, struct_name, VAR_NAME_MAX);
            }
            else {
                parser_err_msg(info, "invalid struct\n");
                return FALSE;
            }
        }
        else if(strcmp(type_name, "union") == 0) {
            if(xisalpha(*info->p) || *info->p == '_') {
                char union_name[VAR_NAME_MAX];

                if(!parse_word(union_name, VAR_NAME_MAX, info, FALSE, FALSE))
                {
                    return FALSE;
                }

                if(*info->p == '{') {
                    unsigned int node = 0;
                    BOOL anonymous = FALSE;
                    if(!parse_union(&node, union_name, VAR_NAME_MAX, NULL, definition_struct, info)) {
                        return FALSE;
                    }

                    sCompileInfo cinfo;

                    memset(&cinfo, 0, sizeof(sCompileInfo));
                    cinfo.no_output = FALSE;
                    cinfo.pinfo = info;

                    if(!compile(node, &cinfo)) {
                        return FALSE;
                    }
                }
                else {
                    sCLClass* klass = get_class(union_name);

                    if(klass == NULL) {
                        return FALSE;
                    }
                }

                xstrncpy(type_name,  union_name, VAR_NAME_MAX);
            }
            else if(*info->p == '{') {
                char union_name[VAR_NAME_MAX];

                create_anonymous_name(union_name, VAR_NAME_MAX);

                unsigned int node = 0;
                BOOL anonymous = TRUE;
                if(!parse_union(&node, union_name, VAR_NAME_MAX, NULL, definition_struct, info)) {
                    return FALSE;
                }

                sCompileInfo cinfo;

                memset(&cinfo, 0, sizeof(sCompileInfo));
                cinfo.no_output = FALSE;
                cinfo.pinfo = info;

                if(!compile(node, &cinfo)) {
                    return FALSE;
                }

                xstrncpy(type_name, union_name, VAR_NAME_MAX);
            }
            else {
                parser_err_msg(info, "invalid union\n");
                return FALSE;
            }
        }
        else if(strcmp(type_name, "enum") == 0) 
        {
            if(xisalpha(*info->p) || *info->p == '_') {
                char enum_name[VAR_NAME_MAX];

                if(!parse_word(enum_name, VAR_NAME_MAX, info, FALSE, FALSE))
                {
                    return FALSE;
                }

                if(*info->p == '{') {
                    unsigned int node = 0;
                    if(!parse_enum(&node, enum_name, VAR_NAME_MAX, NULL, info)) {
                        return FALSE;
                    }

/*
                    sCompileInfo cinfo;

                    memset(&cinfo, 0, sizeof(sCompileInfo));
                    cinfo.no_output = FALSE;
                    cinfo.pinfo = info;

                    if(!compile(node, &cinfo)) {
                        return FALSE;
                    }
*/
                }
            }
            else if(*info->p == '{') {
                char enum_name[VAR_NAME_MAX];

                create_anonymous_name(enum_name, VAR_NAME_MAX);

                unsigned int node = 0;
                if(!parse_enum(&node, enum_name, VAR_NAME_MAX, NULL, info)) {
                    return FALSE;
                }

/*
                sCompileInfo cinfo;

                memset(&cinfo, 0, sizeof(sCompileInfo));
                cinfo.no_output = FALSE;
                cinfo.pinfo = info;

                if(!compile(node, &cinfo)) {
                    return FALSE;
                }
*/
            }
            else {
                parser_err_msg(info, "invalid enum\n");
                return FALSE;
            }

            *result_type = create_node_type_with_class_name("int");
        }

        int i;
        for(i=0; i<info->mNumGenerics; i++) {
            if(strcmp(type_name, info->mGenericsTypeNames[i]) == 0)
            {
                char buf[VAR_NAME_MAX+1];
                snprintf(buf, VAR_NAME_MAX, "generics%d", i);

                *result_type = create_node_type_with_class_name(buf);
            }
        }

        if(*result_type == NULL) {
#ifdef __DARWIN__
            if(strcmp(type_name, "va_list") == 0) {
                *result_type = create_node_type_with_class_name(type_name);
            }
            else {
                *result_type = get_typedef(type_name);
            }
#else
            *result_type = get_typedef(type_name);
#endif

            if(*result_type != NULL) {
                xstrncpy((*result_type)->mOriginalTypeName, type_name, VAR_NAME_MAX);

                if(strcmp(CLASS_NAME((*result_type)->mClass), "long") == 0)
                {
                    long_long = TRUE;
                }

                BOOL remove_heap_mark = FALSE;
                if(*info->p == '&') {
                    info->p++;
                    skip_spaces_and_lf(info);
                    remove_heap_mark = TRUE;
                }

                heap = (*result_type)->mHeap;
                channel = (*result_type)->mChannel;
                nullable = (*result_type)->mNullable;
                constant = (*result_type)->mConstant;
                unsigned_ = (*result_type)->mUnsigned;
                register_ = (*result_type)->mRegister;
                volatile_ = (*result_type)->mVolatile;
                //static_ = (*result_type)->mStatic;
                no_heap = (*result_type)->mNoHeap;
                pointer_num = (*result_type)->mPointerNum;

                if(remove_heap_mark) {
                   heap = FALSE; 
                }

                xstrncpy((*result_type)->mTypeName, type_name, VAR_NAME_MAX);
            }
        }

        if(*result_type == NULL) {
            sCLClass* klass = get_class(type_name);

            if(klass) {
                *result_type = create_node_type_with_class_name(type_name);
            }
        }
    }

    if(strcmp(type_name, "typeof") == 0 && *info->p == '(')
    {
        info->p++;
        skip_spaces_and_lf(info);

        unsigned int node = 0;
        if(!expression(&node, TRUE, info)) {
            return FALSE;
        };

        *result_type = create_node_type_with_class_name("TYPEOF");

        expect_next_character_with_one_forward(")", info);

        (*result_type)->mTypeOfExpression = node;
    }

    if(*result_type == NULL || (*result_type)->mClass == NULL) {
        *result_type = create_node_type_with_class_name("int");
    }

#if defined(__ISH__) || defined(__32BIT_CPU__)
    if(!long_long && type_identify_with_class_name((*result_type), "long"))
    {
        *result_type = create_node_type_with_class_name("int");
    }
#endif

    if(long_long && type_identify_with_class_name((*result_type), "int"))
    {
        *result_type = create_node_type_with_class_name("long");
    }

    if(long_ && type_identify_with_class_name((*result_type), "int"))
    {
        if(sizeof(long int) == 4) {
            *result_type = create_node_type_with_class_name("int");
        }
        else {
            *result_type = create_node_type_with_class_name("long");
        }
    }

    if((long_ || long_long ) && type_identify_with_class_name((*result_type), "double"))
    {
        *result_type = create_node_type_with_class_name("long_double");
    }

    if(short_ && type_identify_with_class_name((*result_type), "int"))
    {
        *result_type = create_node_type_with_class_name("short");
    }

    if(definition_typedef && func_pointer_name) {
        if(xisalpha(*info->p) || *info->p == '_' || *info->p == '*' || *info->p == '%' || *info->p == '(') 
        {
            char* p_before = info->p;
            int sline_before = info->sline;

            while(1) {
                if(*info->p == '*') {
                    info->p++;
                    skip_spaces_and_lf(info);
                    (*result_type)->mPointerNum++;
                }
                else if(*info->p == '%') {
                    info->p++;
                    skip_spaces_and_lf(info);
                    (*result_type)->mHeap = TRUE;
                }
                else {
                    break;
                }
            }

            if(*info->p == '(') {
                info->p++;
                skip_spaces_and_lf(info);
            }

            if(*info->p == '^') {
                info->p++;
                skip_spaces_and_lf(info);
            }

            if(parse_cmp(info->p, "_Nullable") == 0) {
                char buf[VAR_NAME_MAX];
                if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE))
                {
                    return FALSE;
                }
            }
            if(parse_cmp(info->p, "_Nonnull") == 0) {
                char buf[VAR_NAME_MAX];
                if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE))
                {
                    return FALSE;
                }
            }

            if(*info->p == ')') {
                xstrncpy(func_pointer_name, "fun", VAR_NAME_MAX);
            }
            else {
                if(!parse_word(func_pointer_name, VAR_NAME_MAX, info, FALSE, FALSE))
                {
                    return FALSE;
                }
            }

            if(*info->p == ')') {
                info->p++;
                skip_spaces_and_lf(info);
            }

            if(*info->p == '(') {
                sNodeType* node_type = clone_node_type(*result_type);

                *result_type = create_node_type_with_class_name("lambda");
                (*result_type)->mResultType = node_type;

                if(*info->p == '(') {
                    info->p++;
                    skip_spaces_and_lf(info);

                    if(parse_cmp(info->p, "void") == 0) {
                        char* p_before = info->p;
                        int sline_before = info->sline;

                        char buf[VAR_NAME_MAX];
                        if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE))
                        {
                            return FALSE;
                        }

                        if(*info->p == ')') {
                        }
                        else {
                            info->p = p_before;
                            info->sline = sline_before;
                        }
                    }

                    if(*info->p == ')') {
                        info->p++;
                        skip_spaces_and_lf(info);
                    }
                    else {
                        while(1) {
                            sNodeType* node_type = NULL;
                            if(!parse_type(&node_type, info, NULL,  FALSE, FALSE)) {
                                return FALSE;
                            }

                            (*result_type)->mParamTypes[(*result_type)->mNumParams] = node_type;

                            (*result_type)->mNumParams++;

                            if((*result_type)->mNumParams >= PARAMS_MAX) {
                                parser_err_msg(info, "oveflow type params");
                                return FALSE;
                            }

                            if(xisalpha(*info->p) || *info->p == '_') {
                                char buf[VAR_NAME_MAX];

                                (void)parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE);
                            }

                            if(*info->p == ')') {
                                info->p++;
                                skip_spaces_and_lf(info);
                                break;
                            }
                            else if(*info->p == ',') {
                                info->p++;
                                skip_spaces_and_lf(info);

                                if(*info->p == '.' && *(info->p+1) == '.' && *(info->p+2) == '.') {
                                    info->p += 3;
                                    skip_spaces_and_lf(info);

                                    expect_next_character_with_one_forward(")", info);

                                    (*result_type)->mVarArgs = TRUE;
                                    break;
                                }
                            }
                            else {
                                char msg[1024];
                                snprintf(msg, 1024, "invalid character in lambda type name(%c) aaa", *info->p);
                                parser_err_msg(info, msg);
                                break;
                            }
                        }
                    }
                }
            }
            else {
                info->p = p_before;
                info->sline = sline_before;
                func_pointer_name[0] = '\0';
            }
        }
    }
    else {
        char* p = info->p;
        int sline = info->sline;

        if(*info->p == '(') {
            info->p++;
            skip_spaces_and_lf(info);

            if(*info->p == '*') {
                info->p++;
                skip_spaces_and_lf(info);

                if(*info->p == ')') {
                    info->p++;
                    skip_spaces_and_lf(info);

                    if(*info->p == '(') {
                        sNodeType* node_type = clone_node_type(*result_type);

                        *result_type = create_node_type_with_class_name("lambda");
                        (*result_type)->mResultType = node_type;
                        pointer_num++;

                        if(*info->p == '(') {
                            info->p++;
                            skip_spaces_and_lf(info);

                            if(parse_cmp(info->p, "void") == 0) {
                                char* p_before = info->p;
                                int sline_before = info->sline;

                                char buf[VAR_NAME_MAX];
                                if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE))
                                {
                                    return FALSE;
                                }

                                if(*info->p == ')') {
                                }
                                else {
                                    info->p = p_before;
                                    info->sline = sline_before;
                                }
                            }

                            if(*info->p == ')') {
                                info->p++;
                                skip_spaces_and_lf(info);
                            }
                            else {
                                while(1) {
                                    sNodeType* node_type = NULL;
                                    if(!parse_type(&node_type, info, NULL, FALSE, FALSE)) {
                                        return FALSE;
                                    }

                                    (*result_type)->mParamTypes[(*result_type)->mNumParams] = node_type;

                                    (*result_type)->mNumParams++;

                                    if((*result_type)->mNumParams >= PARAMS_MAX) {
                                        parser_err_msg(info, "oveflow type params");
                                        return FALSE;
                                    }

                                    if(xisalpha(*info->p) || *info->p == '_') {
                                        char buf[VAR_NAME_MAX];

                                        (void)parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE);
                                    }

                                    if(*info->p == ')') {
                                        info->p++;
                                        skip_spaces_and_lf(info);
                                        break;
                                    }
                                    else if(*info->p == ',') {
                                        info->p++;
                                        skip_spaces_and_lf(info);
                                    }
                                    else {
                                        char msg[1024];
                                        snprintf(msg, 1024, "invalid character in lambda type name(%c) bbb", *info->p);
                                        parser_err_msg(info, msg);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    else {
                        info->p = p;
                        info->sline = sline;
                    }
                }
                else {
                    info->p = p;
                    info->sline = sline;
                }
            }
            else {
                info->p = p;
                info->sline = sline;
            }
        }
        else {
            info->p = p;
            info->sline = sline;
        }
    }

    /// generics ///
    if(*info->p == '<' && *(info->p+1) != '<' && *(info->p+1) != '=') 
    {
        info->p++;
        skip_spaces_and_lf(info);

        int generics_num = 0;

        while(1) {
            char func_pointer_name[VAR_NAME_MAX];
            if(!parse_type(&(*result_type)->mGenericsTypes[generics_num], info, func_pointer_name, FALSE, FALSE)) {
                return FALSE;
            }

            generics_num++;

            if(generics_num >= GENERICS_TYPES_MAX) {
                parser_err_msg(info, "overflow generics parametor number");
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
                char msg[1024];
                snprintf(msg, 1024, "invalid character(%c) in generics types", *info->p);
                parser_err_msg(info, msg);
                info->err_num++;
                break;
            }
        }

        (*result_type)->mNumGenericsTypes = generics_num;
    }

    /// pointer ///
    int parser_pointer_num = 0;

    while(1) {
        char* p_before = info->p;
        int sline_before = info->sline;

        char buf[VAR_NAME_MAX];
        (void)parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE);
        if(strcmp(buf, "__restrict") == 0 || strcmp(buf, "restrict") == 0)
        {
        }
        else if(strcmp(buf, "const") == 0)
        {
        }
        else {
            info->p = p_before;
            info->sline = info->sline;
        }

        if(*info->p == '*') {
            pointer_num++;
            parser_pointer_num++;
            info->p++;
            skip_spaces_and_lf(info);
        }
        else if(*info->p == '%') {
            info->p++;
            skip_spaces_and_lf(info);

            heap = TRUE;
        }
        else if(*info->p == '@') {
            info->p++;
            skip_spaces_and_lf(info);

            channel = TRUE;
        }
        else if(*info->p == '&') {
            info->p++;
            skip_spaces_and_lf(info);

            no_heap = TRUE;
        }
        else if(*info->p == '$') {
            info->p++;
            skip_spaces_and_lf(info);

            managed_ = TRUE;
        }
        else if(*info->p == '?') {
            info->p++;
            skip_spaces_and_lf(info);

            nullable = TRUE;
        }
        else {
            break;
        }
    }

    while(TRUE) {
        char* p_before = info->p;
        int sline_before = info->sline;

        if(!parse_word(type_name, VAR_NAME_MAX, info, FALSE, FALSE)) 
        {
            return FALSE;
        }

        if(strcmp(type_name, "const") == 0) {
            constant = TRUE;
        }
        else if(strcmp(type_name, "register") == 0) {
            register_ = TRUE;
        }
        else if(strcmp(type_name, "volatile") == 0) {
            volatile_ = TRUE;
        }
        else {
            info->p = p_before;
            info->sline = sline_before;
            break;
        }
    }

    (*result_type)->mPointerNum = pointer_num;
    (*result_type)->mHeap = heap;
    (*result_type)->mChannel = channel;
    (*result_type)->mNullable = nullable;
    (*result_type)->mConstant = constant;
    (*result_type)->mUnsigned = unsigned_;
    (*result_type)->mRegister = register_;
    (*result_type)->mVolatile = volatile_;
    (*result_type)->mStatic = static_;
    (*result_type)->mOverride = override_;
    (*result_type)->mUniq = uniq;
    (*result_type)->mNoHeap = no_heap;

    if(strcmp((*result_type)->mTypeName, "") != 0)
    {
        (*result_type)->mTypePointerNum = parser_pointer_num;
    }

    if(parse_cmp(info->p, "lambda") == 0 && func_pointer_name) {
        xstrncpy(func_pointer_name, "lambda", VAR_NAME_MAX);
    }
    else if(((*info->p == '(' && *(info->p+1) == '*') || (*info->p == '(' && *(info->p+1) == '^')) && func_pointer_name) {
        info->p += 2;
        skip_spaces_and_lf(info);

        if(parse_cmp(info->p, "_Nullable") == 0) {
            char buf[VAR_NAME_MAX];
            if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE))
            {
                return FALSE;
            }
        }
        if(parse_cmp(info->p, "_Nonnull") == 0) {
            char buf[VAR_NAME_MAX];
            if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE))
            {
                return FALSE;
            }
        }
        if(parse_cmp(info->p, "volatile") == 0) {
            char buf[VAR_NAME_MAX];
            if(!parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE))
            {
                return FALSE;
            }
        }
        char* before_fun = info->p;
        int before_fun_sline = info->sline;

        if(*info->p == ')') {
            func_pointer_name[0] = '\0';
            before_fun = NULL;
        }
        else {
            if(!parse_word(func_pointer_name, VAR_NAME_MAX, info, TRUE, FALSE)) 
            {
                return FALSE;
            }
            
            if(*info->p == '(') {
                info->p++;
                skip_spaces_and_lf(info);

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
            }
            else {
                before_fun = NULL;
            }
        }

        expect_next_character_with_one_forward(")", info);

        sNodeType* node_type = clone_node_type(*result_type);

        *result_type = create_node_type_with_class_name("lambda");
        (*result_type)->mResultType = node_type;

        if(*info->p == '(') {
            info->p++;
            skip_spaces_and_lf(info);

            if(parse_cmp(info->p, "void") == 0) {
                char* p_before = info->p;
                int sline_before = info->sline;

                char buf[VAR_NAME_MAX];
                if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE))
                {
                    return FALSE;
                }

                if(*info->p == ')') {
                }
                else {
                    info->p = p_before;
                    info->sline = sline_before;
                }
            }

            if(*info->p == ')') {
                info->p++;
                skip_spaces_and_lf(info);
            }
            else {
                while(1) {
                    sNodeType* node_type = NULL;
                    char buf[VAR_NAME_MAX];
                    if(!parse_type(&node_type, info, buf, FALSE, FALSE)) {
                        return FALSE;
                    }

                    (*result_type)->mParamTypes[(*result_type)->mNumParams] = node_type;

                    (*result_type)->mNumParams++;

                    if((*result_type)->mNumParams >= PARAMS_MAX) {
                        parser_err_msg(info, "oveflow type params");
                        return FALSE;
                    }

                    if(xisalpha(*info->p) || *info->p == '_') {
                        char buf[VAR_NAME_MAX];

                        (void)parse_word(buf, VAR_NAME_MAX, info, FALSE, FALSE);
                    }

                    if(*info->p == ')') {
                        info->p++;
                        skip_spaces_and_lf(info);
                        break;
                    }
                    else if(*info->p == ',') {
                        info->p++;
                        skip_spaces_and_lf(info);
                    }
                    else {
                        char msg[1024];
                        snprintf(msg, 1024, "invalid character in lambda type name(%c) ccc", *info->p);
                        parser_err_msg(info, msg);
                        break;
                    }
                }
            }
            char asm_fname[VAR_NAME_MAX];
            if(!parse_attribute(info, asm_fname)) {
                return FALSE;
            }
        }

        if(before_fun) {
            func_pointer_name[0] = '\0';
            info->p = before_fun;
            info->sline = before_fun_sline;
        }
    }

/*
    if((*result_type)->mClass->mFlags & CLASS_FLAGS_ENUM)
    {
        (*result_type)->mClass = get_class("int");
    }
*/

    return TRUE;
}

static BOOL parse_return(unsigned int* node, sParserInfo* info)
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

static BOOL parse_variable(unsigned int* node, sNodeType* result_type, char* name, BOOL extern_, sParserInfo* info, BOOL readonly)
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

static BOOL parse_param(sParserParam* param, sParserInfo* info)
{
    if(!parse_type(&param->mType, info, param->mName, FALSE, FALSE)) {
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

static BOOL get_block_text(sBuf* buf, sParserInfo* info, BOOL append_head_currly_brace)
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
static BOOL parse_params(sParserParam* params, int* num_params, sParserInfo* info, int character_type, BOOL* var_arg)
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



static BOOL parse_generics_function(unsigned int* node, sNodeType* result_type, char* fun_name, char* struct_name, sParserInfo* info)
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

static void parse_version(int* version, sParserInfo* info)
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

static BOOL parse_inline_function(unsigned int* node, char* struct_name, sParserInfo* info)
{
    BOOL operator_fun = FALSE;

    /// method generics ///
    info->mNumMethodGenerics = 0;

    char asm_fname[VAR_NAME_MAX];
    if(!parse_attribute(info, asm_fname)) {
        return FALSE;
    }

    sNodeType* result_type = NULL;
    if(!parse_type(&result_type, info, NULL, FALSE, FALSE))
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

static BOOL parse_funcation_call_params(int* num_params, unsigned int* params, sParserInfo* info)
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

    return TRUE;
}

static BOOL parse_if(unsigned int* node, sParserInfo* info)
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


static BOOL postposition_operator(unsigned int* node, BOOL enable_assginment, sParserInfo* info)
{
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
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

                /// call methods ///
                if(*info->p == '(' || *info->p == '{') 
                {
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
            else {
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

static BOOL parse_while(unsigned int* node, sParserInfo* info)
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

static BOOL parse_do(unsigned int* node, sParserInfo* info)
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

static BOOL parse_for(unsigned int* node, sParserInfo* info)
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

static BOOL parse_delete(unsigned int* node, sParserInfo* info)
{
    unsigned int object_node;
    BOOL no_comma_operator = info->no_comma_operator;
    info->no_comma_operator = TRUE;
    if(!expression(&object_node, FALSE, info)) {
        return FALSE;
    }
    info->no_comma_operator = no_comma_operator;

    *node = sNodeTree_create_delete(object_node, info);

    return TRUE;
}

static BOOL parse_select(unsigned int* node, sParserInfo* info)
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

static BOOL parse_pselect(unsigned int* node, sParserInfo* info)
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

static BOOL parse_borrow(unsigned int* node, sParserInfo* info)
{
    unsigned int object_node;
    if(!expression(&object_node, FALSE, info)) {
        return FALSE;
    };

    *node = sNodeTree_create_borrow(object_node, info);

    return TRUE;
}

static BOOL parse_nomove(unsigned int* node, sParserInfo* info)
{
    unsigned int object_node;
    if(!expression(&object_node, FALSE, info)) {
        return FALSE;
    };

    *node = sNodeTree_create_nomove(object_node, info);

    return TRUE;
}

static BOOL parse_dummy_heap(unsigned int* node, sParserInfo* info)
{
    unsigned int object_node;
    if(!expression(&object_node, FALSE, info)) {
        return FALSE;
    };

    *node = sNodeTree_create_dummy_heap(object_node, info);

    return TRUE;
}

static BOOL parse_managed(unsigned int* node, sParserInfo* info)
{
    char buf[VAR_NAME_MAX+1];

    if(!parse_word(buf, VAR_NAME_MAX, info, TRUE, FALSE))
    {
        return FALSE;
    };

    *node = sNodeTree_create_managed(buf, info);

    return TRUE;
}

static BOOL parse_alloca(unsigned int* node, sParserInfo* info)
{
    sNodeType* node_type = NULL;

    if(!parse_type(&node_type, info, NULL, FALSE, FALSE)) {
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

static BOOL parse_sizeof(unsigned int* node, sParserInfo* info)
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
        if(!parse_type(&node_type, info, NULL, FALSE, FALSE)) {
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

static BOOL parse_alignof(unsigned int* node, sParserInfo* info)
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

        if(!parse_type(&node_type, info, NULL, FALSE, FALSE)) {
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

static BOOL parse_clone(unsigned int* node, sParserInfo* info)
{
    if(!expression(node, FALSE, info)) {
        return FALSE;
    }

    if(*node == 0) {
        parser_err_msg(info, "Require expression for clone");
        info->err_num++;
        return TRUE;
    };

    *node = sNodeTree_create_clone(*node, info);

    return TRUE;
}

static BOOL parse_typedef(unsigned int* node, sParserInfo* info)
{
    char buf[VAR_NAME_MAX+1];
    
    buf[0] = '\0';

    sNodeType* node_type = NULL;
    if(!parse_type(&node_type, info, buf, TRUE, FALSE)) {
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

static BOOL parse_switch(unsigned int* node, sParserInfo* info)
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

static BOOL parse_case(unsigned int* node, sParserInfo* info)
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

static BOOL parse_default(unsigned int* node, sParserInfo* info)
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

static BOOL parse_label(unsigned int* node, char* name, sParserInfo* info)
{
    expect_next_character_with_one_forward(":", info);

    *node = sNodeTree_label_expression(name, info);

    return TRUE;
}

static BOOL parse_goto(unsigned int* node, sParserInfo* info)
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

static BOOL parse_is_heap(unsigned int* node, sParserInfo* info)
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

        if(!parse_type(&node_type, info, NULL, FALSE, FALSE)) {
            return FALSE;
        }

        expect_next_character_with_one_forward(")", info);

        *node = sNodeTree_create_is_heap(node_type, info);
    }

    return TRUE;
}

static BOOL parse_impl(unsigned int* node, sParserInfo* info)
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

static void parse_impl_end(sParserInfo* info)
{
    strcpy(info->impl_struct_name, "");
    info->mNumGenerics = 0;
}

static BOOL parse_new(unsigned int* node, sParserInfo* info)
{
    sNodeType* node_type = NULL;

    if(!parse_type(&node_type, info, NULL, FALSE, FALSE)) {
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

        *node = sNodeTree_create_object(node_type, object_num, 0, NULL, info->sname, info->sline, info);
    }
    else {
        parser_err_msg(info, "Invalid type name");
        info->err_num++;
    }

    return TRUE;
}

static BOOL parse_var(unsigned int* node, sParserInfo* info, BOOL readonly)
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
        if(!parse_type(&node_type, info, NULL, FALSE, FALSE)) {
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

static BOOL parse_inherit(unsigned int* node, sParserInfo* info) 
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

static BOOL parse_come(unsigned int* node, sParserInfo* info)
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

static BOOL expression_node(unsigned int* node, BOOL enable_assginment, sParserInfo* info)
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
            if(!parse_type(&node_type, info, NULL, FALSE, FALSE))
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
            sNodeType* result_type = NULL;
            char name[VAR_NAME_MAX+1];
            if(!parse_type(&result_type, info, name, FALSE, FALSE))
            {
                return FALSE;
            }

            if(name[0] != '\0') {
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

            char buf_before[VAR_NAME_MAX];

            xstrncpy(buf_before, buf, VAR_NAME_MAX);

            sNodeType* result_type = NULL;
            char name[VAR_NAME_MAX+1];
            if(!parse_type(&result_type, info, name, FALSE, FALSE))
            {
                return FALSE;
            }

            if(strcmp(name, "lambda") == 0) {
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
            else if(*info->p == '(') {
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

// from left to right order
static BOOL expression_mult_div(unsigned int* node, sParserInfo* info)
{
    if(!expression_node(node, TRUE, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    if(gNodes[*node].mNodeType == kNodeTypeIf || gNodes[*node].mNodeType == kNodeTypeSwitch || gNodes[*node].mNodeType == kNodeTypeFor || gNodes[*node].mNodeType == kNodeTypeWhile || gNodes[*node].mNodeType == kNodeTypeDoWhile) {
        return TRUE;
    }


    while(*info->p) {
        if(*info->p == '*' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_node(&right, TRUE, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator *");
                info->err_num++;
            };

            *node = sNodeTree_create_mult(*node, right, 0, info);
        }
        else if(*info->p == '/' && *(info->p+1) != '=' && *(info->p+1) != '*') 
        {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_node(&right, TRUE, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator /");
                info->err_num++;
            };

            *node = sNodeTree_create_div(*node, right, 0, info);
        }
        else if(*info->p == '%' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_node(&right, TRUE, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator ^");
                info->err_num++;
            };

            *node = sNodeTree_create_mod(*node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_add_sub(unsigned int* node, sParserInfo* info)
{
    if(!expression_mult_div(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '+' && *(info->p+1) != '=' && *(info->p+1) != '+') 
        {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_mult_div(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator +");
                info->err_num++;
            };

            *node = sNodeTree_create_add(*node, right, 0, info);
        }
        else if(*info->p == '-' && *(info->p+1) != '=' && *(info->p+1) != '-' && *(info->p+1) != '>') 
        {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_mult_div(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator -");
                info->err_num++;
            };

            *node = sNodeTree_create_sub(*node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_shift(unsigned int* node, sParserInfo* info)
{
    if(!expression_add_sub(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '<' && *(info->p+1) == '<' && *(info->p+2) != '=') {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_add_sub(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator <<");
                info->err_num++;
            };

            *node = sNodeTree_create_left_shift(*node, right, 0, info);
        }
        else if(*info->p == '>' && *(info->p+1) == '>' && *(info->p+2) != '=') {
            info->p+=2;
            skip_spaces_and_lf(info);
            
            unsigned int right = 0;
            if(!expression_add_sub(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator >>");
                info->err_num++;
            };

            *node = sNodeTree_create_right_shift(*node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_comparison(unsigned int* node, sParserInfo* info)
{
    if(!expression_shift(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '>' && *(info->p+1) == '=') {
            info->p += 2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_shift(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for >= operator");
                info->err_num++;
            };

            *node = sNodeTree_create_gteq(*node, right, 0, info);
        }
        else if(*info->p == '<' && *(info->p+1) == '=') {
            info->p += 2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_shift(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for <= operator");
                info->err_num++;
            };

            *node = sNodeTree_create_leeq(*node, right, 0, info);
        }
        else if(*info->p == '>' && *(info->p+1) != '>') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_shift(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for > operator");
                info->err_num++;
            };

            *node = sNodeTree_create_gt(*node, right, 0, info);
        }
        else if(*info->p == '<' && *(info->p+1) != '<') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_shift(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for < operator");
                info->err_num++;
            };

            *node = sNodeTree_create_le(*node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_equal(unsigned int* node, sParserInfo* info)
{
    if(!expression_comparison(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '=' && *(info->p+1) == '=') {
            info->p += 2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_equal(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for == operator");
                info->err_num++;
            };

            *node = sNodeTree_create_equals(*node, right, 0, info);
        }
        else if(*info->p == '!' && *(info->p+1) == '=') {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_equal(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for != operator");
                info->err_num++;
            };

            *node = sNodeTree_create_not_equals(*node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_and(unsigned int* node, sParserInfo* info)
{
    if(!expression_equal(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '&' && *(info->p+1) != '&' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_equal(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for & operator");
                info->err_num++;
            };

            *node = sNodeTree_create_and(*node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_xor(unsigned int* node, sParserInfo* info)
{
    if(!expression_and(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '^' && *(info->p+1) != '=') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_and(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for ^ operator");
                info->err_num++;
            };

            *node = sNodeTree_create_xor(*node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

// from left to right order
static BOOL expression_or(unsigned int* node, sParserInfo* info)
{
    if(!expression_xor(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '|' && *(info->p+1) != '=' && *(info->p+1) != '|') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_xor(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for | operator");
                info->err_num++;
            };

            *node = sNodeTree_create_or(*node, right, 0, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

static BOOL expression_and_and_or_or(unsigned int* node, sParserInfo* info)
{
    if(!expression_or(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(TRUE) {
        if(*info->p == '#') {
            if(!parse_sharp(info)) {
                return FALSE;
            }
        }
        else {
            break;
        }
    }


    while(*info->p) {
        if(*info->p == '&' && *(info->p+1) == '&') {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_or(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for && operator");
                info->err_num++;
            };

            *node = sNodeTree_create_and_and(*node, right, info);
        }
        else if(*info->p == '|' && *(info->p+1) == '|') {
            info->p+=2;
            skip_spaces_and_lf(info);

            unsigned int right = 0;
            if(!expression_or(&right, info)) {
                return FALSE;
            }

            if(right == 0) {
                parser_err_msg(info, "require right value for operator ||");
                info->err_num++;
            };

            *node = sNodeTree_create_or_or(*node, right, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

static BOOL expression_comma_operator(unsigned int* node, BOOL comma, sParserInfo* info)
{
    if(!expression_and_and_or_or(node, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(comma && *info->p == ',') {
            info->p++;
            skip_spaces_and_lf(info);

            unsigned int node2 = 0;
            if(!expression_and_and_or_or(&node2, info)) {
                return FALSE;
            }

            if(node2 == 0) {
                parser_err_msg(info, "require right value for , operator");
                info->err_num++;
            };

            *node = sNodeTree_create_comma(*node, node2, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

static BOOL expression_conditional_operator(unsigned int* node, BOOL comma, sParserInfo* info)
{
    if(!expression_comma_operator(node, comma, info)) {
        return FALSE;
    }
    if(*node == 0) {
        return TRUE;
    }

    while(*info->p) {
        if(*info->p == '?') {
            info->p++;
            skip_spaces_and_lf(info);

            while(TRUE) {
                if(*info->p == '#') {
                    if(!parse_sharp(info)) {
                        return FALSE;
                    }
                }
                else {
                    break;
                }
            }

            info->in_conditional_operator = TRUE;

            unsigned int value1 = 0;
            if(!expression_comma_operator(&value1, TRUE, info)) {
                info->in_conditional_operator = FALSE;
                return FALSE;
            }

            while(TRUE) {
                if(*info->p == '#') {
                    if(!parse_sharp(info)) {
                        info->in_conditional_operator = FALSE;
                        return FALSE;
                    }
                }
                else {
                    break;
                }
            }

            if(value1 == 0) {
                parser_err_msg(info, "require right value for ? operator");
                info->err_num++;
            }

            info->in_conditional_operator = FALSE;

            expect_next_character_with_one_forward(":", info);

            unsigned int value2 = 0;
            if(!expression_comma_operator(&value2, TRUE, info)) {
                return FALSE;
            }

            while(TRUE) {
                if(*info->p == '#') {
                    if(!parse_sharp(info)) {
                        return FALSE;
                    }
                }
                else {
                    break;
                }
            }

            if(value2 == 0) {
                parser_err_msg(info, "require right value for ? operator");
                info->err_num++;
            };

            *node = sNodeTree_create_conditional(*node, value1, value2, info);
        }
        else {
            break;
        }
    }

    return TRUE;
}

BOOL expression(unsigned int* node, BOOL comma, sParserInfo* info) 
{
    while(TRUE) {
        if(parse_cmp(info->p, "__extension__") == 0)
        {
            info->p += 13;
            skip_spaces_and_lf(info);
        }
        else if(*info->p == '#') {
            if(!parse_sharp(info)) {
                return FALSE;
            }
        }
        else {
            break;
        }
    }
    char asm_fname[VAR_NAME_MAX];
    if(!parse_attribute(info, asm_fname)) {
        return FALSE;
    }
    
    if(!expression_conditional_operator(node, comma, info)) {
        return FALSE;
    }

    while(TRUE) {
        if(parse_cmp(info->p, "__extension__") == 0)
        {
            info->p += 13;
            skip_spaces_and_lf(info);
        }
        else if(*info->p == '#') {
            if(!parse_sharp(info)) {
                return FALSE;
            }
        }
        else {
            break;
        }
    }
    

    return TRUE;
}
