#include "common.h"
#include <ctype.h>

BOOL parse_type(sNodeType** result_type, sParserInfo* info, char* func_pointer_name, BOOL definition_typedef, BOOL definition_struct, BOOL* function_pointer_result_function, BOOL definition_function_pointer_result_function)
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
                        klass = alloc_struct(struct_name, anonymous, TRUE);


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
            for(i=0; i<info->mNumMethodGenerics; i++) {
                if(strcmp(type_name, info->mMethodGenericsTypeNames[i]) == 0)
                {
                    char buf[VAR_NAME_MAX+1];
                    snprintf(buf, VAR_NAME_MAX, "mgenerics%d", i);

                    *result_type = create_node_type_with_class_name(buf);
                }
            }
        }

        if(*result_type == NULL) {
#ifdef __DARWIN__
            if(strcmp(type_name, "va_list") == 0) {
                *result_type = create_node_type_with_class_name(type_name);
            }
            else {
                if(strcmp(type_name, "__current__") == 0) {
                    create_current_stack_frame_struct(type_name, info->lv_table);
                }

                *result_type = get_typedef(type_name);
            }
#else
            if(strcmp(type_name, "__current__") == 0) {
                create_current_stack_frame_struct(type_name, info->lv_table);
            }

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
                    if(!gNCGC) {
                        remove_heap_mark = TRUE;
                    }
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
                    if(!gNCGC) {
                        (*result_type)->mHeap = TRUE;
                    }
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

            if(*info->p == '*') {
                info->p++;
                skip_spaces_and_lf(info);
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
                            if(!parse_type(&node_type, info, NULL,  FALSE, FALSE, NULL, FALSE)) {
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
    else if(!definition_function_pointer_result_function) {
        char* p = info->p;
        int sline = info->sline;

        if(*info->p == '(') {
            info->p++;
            skip_spaces_and_lf(info);

            if(*info->p == '*') {
                info->p++;
                skip_spaces_and_lf(info);

                if(xisalpha(*info->p) || *info->p == '_' || *info->p == ')')
                {
                    if(*info->p == ')') {
                        info->p++;
                        skip_spaces_and_lf(info);

                        xstrncpy(func_pointer_name, "anon_fun", VAR_NAME_MAX);
                    }
                    else {
                        if(!parse_word(func_pointer_name, VAR_NAME_MAX, info, FALSE, FALSE))
                        {
                            return FALSE;
                        }
                    }

                    BOOL no_function_pointer_result_function = FALSE;
                    if(*info->p == ')') {
                        if(function_pointer_result_function) {
                            *function_pointer_result_function = FALSE;
                            no_function_pointer_result_function = TRUE;
                        }

                        info->p++;
                        skip_spaces_and_lf(info);
                    }

                    if(*info->p == '(') {
                        if(function_pointer_result_function && !no_function_pointer_result_function) {
                            *function_pointer_result_function = TRUE;
                            info->p = p;
                            info->sline = sline;
                            return TRUE;
                        }

                        sNodeType* node_type = clone_node_type(*result_type);

                        *result_type = create_node_type_with_class_name("lambda");
                        pointer_num++;

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
                                    char func_pointer_name2[VAR_NAME_MAX];
                                    if(!parse_type(&node_type, info, func_pointer_name2,  FALSE, FALSE, NULL, FALSE)) {
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

                                        if(*info->p == ')' && *(info->p+1) == '(') {
                                            info->p++;
                                            skip_spaces_and_lf(info);
                                        }

                                        if(*info->p == '(') {
                                            info->p++;
                                            skip_spaces_and_lf(info);

                                            sNodeType* node_type = clone_node_type(*result_type);

                                            *result_type = create_node_type_with_class_name("lambda");

                                            (*result_type)->mResultType = node_type;

                                            if(*info->p == ')') {
                                                info->p++;
                                                skip_spaces_and_lf(info);
                                            }
                                            else {
                                                while(1) {
                                                    sNodeType* node_type = NULL;
                                                    char func_pointer_name2[VAR_NAME_MAX];
                                                    if(!parse_type(&node_type, info, func_pointer_name2,  FALSE, FALSE, NULL, FALSE)) 
                                                    {
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
                        info->p = p;
                        info->sline = sline;
                        func_pointer_name[0] = '\0';
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
            if(!parse_type(&(*result_type)->mGenericsTypes[generics_num], info, func_pointer_name, FALSE, FALSE, NULL, FALSE)) {
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

            if(!gNCGC) {
                heap = TRUE;
            }
        }
        else if(*info->p == '@') {
            info->p++;
            skip_spaces_and_lf(info);

            channel = TRUE;
        }
        else if(*info->p == '&') {
            info->p++;
            skip_spaces_and_lf(info);

            if(!gNCGC) {
                no_heap = TRUE;
            }
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
                    if(!parse_type(&node_type, info, buf, FALSE, FALSE, NULL, FALSE)) {
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

    return TRUE;
}

