#include "common.h"

extern int parse_cmp(char* p, char* str);

BOOL parse_block_easy(ALLOC sNodeBlock** node_block, BOOL extern_c_lang, sParserInfo* info)
{
    BOOL single_expression = FALSE;
    if(*info->p == '{') {
        info->p++;
    }
    else {
        single_expression = TRUE;
    }

    sVarTable* old_table = info->lv_table;

    *node_block = ALLOC sNodeBlock_alloc();

    info->lv_table = init_block_vtable(old_table, extern_c_lang);

    if(!parse_block(*node_block, extern_c_lang, single_expression, info)) {
        sNodeBlock_free(*node_block);
        return FALSE;
    }

    if(!single_expression) {
        expect_next_character_with_one_forward("}", info);
    }

    info->lv_table = old_table;

    return TRUE;
}

BOOL parse_block(sNodeBlock* node_block, BOOL extern_c_lang, BOOL single_expression, sParserInfo* info)
{
    node_block->mLVTable = info->lv_table;

    xstrncpy(node_block->mSName, info->sname, PATH_MAX);
    node_block->mSLine = info->sline;

    skip_spaces_and_lf(info);

    node_block->mExternCLang = extern_c_lang;

    if(!extern_c_lang) {
        info->mBlockLevel++;
    }

    BOOL parse_block = info->parse_block;
    info->parse_block = TRUE;

    char* source_head = info->p;
    BOOL has_result = FALSE;

    if(single_expression) {
        while(TRUE) {
            if(parse_cmp(info->p, "__extension__") == 0)
            {
                info->p += 13;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '#') {
                if(!parse_sharp(info)) {
                    info->parse_block = parse_block;
                    return FALSE;
                }
            }
            else {
                break;
            }
        }

        if(*info->p == '\0') {
            parser_err_msg(info, "require } before the source end");
            info->err_num++;

            if(!extern_c_lang) {
                info->mBlockLevel--;
            }
            info->parse_block = parse_block;
            return TRUE;
        }

        unsigned int node = 0;

        skip_spaces_and_lf(info);

        int sline = info->sline;
        char sname[PATH_MAX];
        xstrncpy(sname, info->sname, PATH_MAX);

        info->sline_top = sline;

        while(TRUE) {
            if(parse_cmp(info->p, "__extension__") == 0)
            {
                info->p += 13;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '#') {
                if(!parse_sharp(info)) {
                    info->parse_block = parse_block;
                    return FALSE;
                }
            }
            else {
                break;
            }
        }

        if(*info->p == ';') {
        }
        else {
            if(!expression(&node, TRUE, info)) {
                if(!extern_c_lang) {
                    info->mBlockLevel--;
                }
                info->parse_block = parse_block;
                return FALSE;
            }

            if(node == 0) {
                parser_err_msg(info, "require an expression");
                info->err_num++;
            }

            if(info->err_num == 0) {
                append_node_to_node_block(node_block, node);
            }

            if(info->change_sline) {
                info->change_sline = FALSE;

                gNodes[node].mLine = info->sline;
                xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);

                info->sline_top = info->sline;
            }
            else {
                gNodes[node].mLine = sline;
                xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
            }
        }

        while(TRUE) {
            if(parse_cmp(info->p, "__extension__") == 0)
            {
                info->p += 13;
                skip_spaces_and_lf(info);
            }
            else if(*info->p == '#') {
                if(!parse_sharp(info)) {
                    info->parse_block = parse_block;
                    return FALSE;
                }
            }
            else {
                break;
            }
        }

        if(*info->p == ';') 
        {
            info->p++;
            skip_spaces_and_lf(info);
            has_result = FALSE;
        }
        else if(gNodes[node].mNodeType == kNodeTypeIf || gNodes[node].mNodeType == kNodeTypeWhile || gNodes[node].mNodeType == kNodeTypeFor || gNodes[node].mNodeType == kNodeTypeSwitch) 
        {
            skip_spaces_and_lf(info);
            has_result = FALSE;
        }
        else {
            has_result = TRUE;
        }
    }
    else {
        while(1) {
            while(TRUE) {
                if(parse_cmp(info->p, "__extension__") == 0)
                {
                    info->p += 13;
                    skip_spaces_and_lf(info);
                }
                else if(*info->p == '#') {
                    if(!parse_sharp(info)) {
                        info->parse_block = parse_block;
                        return FALSE;
                    }
                }
                else {
                    break;
                }
            }

            if(*info->p == '}') {
                break;
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "require } before the source end");
                info->err_num++;

                if(!extern_c_lang) {
                    info->mBlockLevel--;
                }
                info->parse_block = parse_block;
                return TRUE;
            }

            unsigned int node = 0;

            skip_spaces_and_lf(info);

            int sline = info->sline;
            char sname[PATH_MAX];
            xstrncpy(sname, info->sname, PATH_MAX);

            info->sline_top = sline;

            while(TRUE) {
                if(parse_cmp(info->p, "__extension__") == 0)
                {
                    info->p += 13;
                    skip_spaces_and_lf(info);
                }
                else if(*info->p == '#') {
                    if(!parse_sharp(info)) {
                        info->parse_block = parse_block;
                        return FALSE;
                    }
                }
                else {
                    break;
                }
            }

            if(!expression(&node, TRUE, info)) {
                if(!extern_c_lang) {
                    info->mBlockLevel--;
                }
                info->parse_block = parse_block;
                return FALSE;
            }

            if(node == 0) {
                parser_err_msg(info, "require an expression");
                info->err_num++;
            }

            if(info->err_num == 0) {
                append_node_to_node_block(node_block, node);
            }

            while(TRUE) {
                if(parse_cmp(info->p, "__extension__") == 0)
                {
                    info->p += 13;
                    skip_spaces_and_lf(info);
                }
                else if(*info->p == '#') {
                    if(!parse_sharp(info)) {
                        info->parse_block = parse_block;
                        return FALSE;
                    }
                }
                else {
                    break;
                }
            }

            if(info->change_sline) {
                info->change_sline = FALSE;

                gNodes[node].mLine = info->sline;
                xstrncpy(gNodes[node].mSName, info->sname, PATH_MAX);

                info->sline_top = info->sline;
            }
            else {
                gNodes[node].mLine = sline;
                xstrncpy(gNodes[node].mSName, sname, PATH_MAX);
            }


            if(*info->p == ';') 
            {
                info->p++;
                skip_spaces_and_lf(info);
                has_result = FALSE;
            }
            else if(gNodes[node].mNodeType == kNodeTypeIf || gNodes[node].mNodeType == kNodeTypeWhile || gNodes[node].mNodeType == kNodeTypeFor || gNodes[node].mNodeType == kNodeTypeSwitch) 
            {
                skip_spaces_and_lf(info);
                has_result = FALSE;
            }
            else {
                has_result = TRUE;
            }

            if(*info->p == '}') {
                break;
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "require } before the source end");
                info->err_num++;
                if(!extern_c_lang) {
                    info->mBlockLevel--;
                }
                info->parse_block = parse_block;
                return TRUE;
            }
        }
    }

    char* source_end = info->p;

    sBuf_append(&(node_block)->mSource, source_head, source_end - source_head);
    sBuf_append_char(&(node_block)->mSource, '\0');

    node_block->mHasResult = has_result;

    if(!extern_c_lang || info->mBlockLevel > 0) 
    {
        node_block->mHasResult = has_result;
    }
    else {
        node_block->mHasResult = FALSE;
    }

    node_block->mInCLang = info->in_clang;

    if(!extern_c_lang) {
        info->mBlockLevel--;
    }

    info->parse_block = parse_block;

    return TRUE;
}



BOOL skip_block(sParserInfo* info)
{
    if(*info->p == '{') {
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
            else if(*info->p == '{') {
                info->p++;

                nest++;
            }
            else if(*info->p == '}') {
                info->p++;

                if(nest == 0) {
                    skip_spaces_and_lf(info);
                    break;
                }

                nest--;
            }
            else if(*info->p == '\0') {
                parser_err_msg(info, "The block requires } character for closing block");
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
    else {
        char msg[1024];
        snprintf(msg, 1024, "Require block. This is %c", *info->p);
        parser_err_msg(info, msg);
        info->err_num++;
    }

    return TRUE;
}

