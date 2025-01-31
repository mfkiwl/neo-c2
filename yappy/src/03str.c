#include "common.h"
#include <ctype.h>

static sNode* create_string_node(char* str, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kStringValueNode;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.stringValue = wstring(str);
    
    return result;
}

sNode*? exp_node(sParserInfo* info) version 3
{
    sNode* result = inherit(info);
    
    if(result == null) {
        if(*info->p == '"') {
            info->p++;
            
            buffer* buf = new buffer.initialize();
            
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
                    skip_spaces_until_eol(info);
                    break;
                }
                else {
                    buf.append_char(*info->p);
                    info->p++;
                }
            }
            
            result = create_string_node(buf.to_string(), info);
            
            if(*info->p == '.') {
                result = method_node(result, info);
            }
        }
        else if(*info->p == '\'') {
            info->p++;
            
            buffer* buf = new buffer.initialize();
            
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
                    skip_spaces_until_eol(info);
                    break;
                }
                else {
                    buf.append_char(*info->p);
                    info->p++;
                }
            }
            
            result = create_string_node(buf.to_string(), info);
            
            if(*info->p == '.') {
                result = method_node(result, info);
            }
        }
    }
    
    return result;
}

bool compile(sNode* node, buffer* codes, sParserInfo* info) version 3
{
    inherit(node, codes, info);
    
    if(node.kind == kStringValueNode) {
        codes.append_int(OP_STRING_VALUE);
        
        wstring str = node.value.stringValue;
        
        int len = wcslen(str);
        
        codes.append_int(len);
        codes.append((char*)str, sizeof(wchar_t)*len);
        
        info->stack_num++;
    }
    
    return true;
}

