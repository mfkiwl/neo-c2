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

BOOL skip_paren(char head_char, char tail_char, sParserInfo* info)
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

BOOL get_number(BOOL minus, unsigned int* node, sParserInfo* info)
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
        
        char c = *(info->p+1);

        if(*info->p == '.' && xisdigit(c)) {
            *p2++ = *info->p;
            
            if(p2 - buf >= buf_size) {
                parser_err_msg(info, "overflow node of number");
                return FALSE;
            }
            
            info->p++;
            skip_spaces_and_lf(info);
            
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
            
            if(*info->p == 'f') {
                info->p++;
                skip_spaces_and_lf(info);
                
                *node = sNodeTree_create_float_value(strtof(buf, NULL), info);
            }
            else {
                *node = sNodeTree_create_double_value(strtod(buf, NULL), info);
            }
        }
        else if(*info->p == 'u' || *info->p == 'U')
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

BOOL get_regex(unsigned int* node, sParserInfo* info)
{
    int sline = info->sline;
    
    sBuf buf;
    sBuf_init(&buf);
    while(TRUE) {
        if(*info->p == '\\' && *(info->p+1) == '/') {
            info->p++;
            sBuf_append_char(&buf, *info->p);
            info->p++;
        }
        else if(*info->p == '/') {
            info->p++;
            break;
        }
        else if(*info->p == '\0') {
            int sline2 = info->sline;
            info->sline = sline;
            parser_err_msg(info, "require closing / for regex");
            info->sline = sline2;
            return FALSE;
        }
        else {
            sBuf_append_char(&buf, *info->p);
            info->p++;
        }
    }
    
    BOOL global = FALSE;
    BOOL ignore_case = FALSE;
    while(*info->p == 'g' || *info->p == 'i') {
        if(*info->p == 'g') {
            info->p++;
            global = TRUE;
        }
        else if(*info->p == 'i') {
            info->p++;
            ignore_case = TRUE;
        }
        else {
            break;
        }
    }
    
    skip_spaces_and_lf(info);
    
    *node = sNodeTree_create_regex_value(buf.mBuf, global, ignore_case, sline, info);
    
    return TRUE;
}

void create_anonymous_name(char* name, int name_size)
{
    static int n = 0;
    snprintf(name, name_size, "come_anon%d", n++);
}

BOOL parse_attribute(sParserInfo* info, char* asm_fname)
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

BOOL parse_typedef_attribute(sParserInfo* info)
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

BOOL parse_variable_name(char* buf, int buf_size, sParserInfo* info, sNodeType* node_type, BOOL array_size_is_dynamic, BOOL param_in_function)
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

        unsigned int size_num_node = 0;
        if(!expression(&size_num_node, FALSE, info)) {
            return FALSE;
        }
        int n = 0;
        if(!get_const_value_from_node(&n, size_num_node, info)) {
            return FALSE;
        }

/*
        int n = 0;
        while(xisdigit(*info->p)) {
            n = n * 10 + *info->p - '0';
            info->p++;
        }
        skip_spaces_and_lf(info);
*/

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
    if(*info->p == '`' && *(info->p+1) != '`') {
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

