#include "common.h"

static sNode*% create_while(sNode*% while_exp, buffer*% while_codes, sParserInfo* info)
{
    sNode*% result = new sNode;
    
    result.kind = kWhile;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.whileValue.while_exp = while_exp;
    result.value.whileValue.while_codes = while_codes;
    
    return result;
}

void sNode_finalize(sNode* self) version 10
{
    inherit(self);

    if(self.kind == kWhile) {
        delete self.value.whileValue.while_exp;
        delete self.value.whileValue.while_codes;
    }
}

static bool word_cmp(char* p, char* word2)
{
    bool result = strstr(p, word2) == p;
    
    char c = p[strlen(word2)];
    
    if(result && (c == '\n' || c == ' ' || c == '\t' || c == '\0' || c == ':')) {
        return true;
    }
    
    return false;
}

sNode*%? exp_node(sParserInfo* info) version 10
{
    sNode* result = null;
    
    if(word_cmp(info->p, "while")) {
        info->p += strlen("while");
        skip_spaces_until_eol(info);
        
        sNode* node = NULL;
        if(!expression(&node, info)) {
            fprintf(stderr, "%s %d: invalid while exp\n", info->fname, info->sline);
            return null;
        }
        
        sNode*% while_exp = dummy_heap node;
        
        if(*info->p == ':') {
            info->p++;
            skip_spaces_until_eol(info);
        }
        else {
            fprintf(stderr, "%s %d: require : for block\n", info->fname, info->sline);
            return null;
        }
        
        buffer*% while_codes = parse_block(info);
        
        result = borrow create_while(while_exp, while_codes, info);
    }
    
    if(result == null) {
        result = borrow inherit(info);
    }
    
    return dummy_heap result;
}


bool compile(sNode* node, buffer* codes, sParserInfo* info) version 10
{
    inherit(node, codes, info);
    
    if(node.kind == kWhile) {
        sNode* while_exp = borrow node.value.whileValue.while_exp;
        buffer* while_codes = borrow node.value.whileValue.while_codes;
        
        int head = codes.length();
        
        if(!compile(while_exp, codes, info)) {
            return false;
        }
        
        codes.append_int(OP_IF);
        
        int offset = while_codes.length();
        offset = (offset + 3) & ~3;
        
        offset /= sizeof(int);
        
        offset += 2`goto;
        
        codes.append_int(offset);
        
        codes.append(while_codes.buf, while_codes.len);
        codes.alignment();
        
        info->stack_num--;
        
        codes.append_int(OP_GOTO);
        codes.append_int(head);
    }
    
    return true;
}

