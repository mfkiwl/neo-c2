#include "common.h"
#include <ctype.h>

static sNode*% create_string_node(char* str, sParserInfo* info)
{
    sNode*% result = new sNode;
    
    result.kind = kStringValue;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.stringValue = string(str);
    
    return result;
}

void sNode_finalize(sNode* self) version 3
{
    inherit(self);

    if(self.kind == kStringValue) {
        delete self.value.stringValue;
    }
}

sNode*%? exp_node(sParserInfo* info) version 2
{
    sNode* result = borrow inherit(info);
    
    if(result == null) {
        if(*info->p == '"') {
            info->p++;
            
            buffer*% buf = new buffer.initialize();
            
            while(true) {
                if(*info->p == '\0') {
                    fprintf(stderr, "%s %d: the source end", info->fname, info->sline);
                    return null;
                }
                else if(*info->p == '\\') {
                    buf.append_char(*info->p);
                    info->p++;
                    
                    if(*info->p == '\0') {
                        fprintf(stderr, "%s %d: the source end", info->fname, info->sline);
                        return null;
                    }
                    
                    buf.append_char(*info->p);
                    info->p++;
                }
                else if(*info->p == '"') {
                    info->p++
                    skip_spaces(info);
                    break;
                }
                else {
                    buf.append_char(*info->p);
                    info->p++;
                }
            }
            
            return create_string_node(buf.to_string(), info);
        }
        else if(*info->p == '\'') {
            info->p++;
            
            buffer*% buf = new buffer.initialize();
            
            while(true) {
                if(*info->p == '\0') {
                    fprintf(stderr, "%s %d: the source end", info->fname, info->sline);
                    return null;
                }
                else if(*info->p == '\\') {
                    buf.append_char(*info->p);
                    info->p++;
                    
                    if(*info->p == '\0') {
                        fprintf(stderr, "%s %d: the source end", info->fname, info->sline);
                        return null;
                    }
                    
                    buf.append_char(*info->p);
                    info->p++;
                }
                else if(*info->p == '\'') {
                    info->p++
                    skip_spaces(info);
                    break;
                }
                else {
                    buf.append_char(*info->p);
                    info->p++;
                }
            }
            
            return create_string_node(buf.to_string(), info);
        }
    }
    
    return dummy_heap result;
}

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 3
{
    inherit(node, codes, info);
    
    if(node.kind == kStringValue) {
        codes.append_int(OP_STRING_VALUE);
        
        codes.append_str(node.value.stringValue);
        codes.apliment();
    }
    
    return true;
}

