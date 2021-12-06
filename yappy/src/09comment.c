#include "common.h"

static void comment(sParserInfo* info)
{
    while(true) {
        if(*info->p == '#') {
            info->p++;
            skip_spaces_until_eol(info);
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

bool expression(sNode** node, sParserInfo* info) version 9
{
    comment(info);
    return inherit(node, info);
}
