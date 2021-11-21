#include "common.h"

static sNode*% create_while(sNode*% while_exp, list<sNode*%>*% while_nodes, list<sNode*%>*%? else_nodes, sParserInfo* info)
{
    sNode*% result = new sNode;
    
    result.kind = kWhile;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.whileValue.while_exp = while_exp;
    result.value.whileValue.while_nodes = while_nodes;
    result.value.whileValue.else_nodes = else_nodes;
    
    return result;
}

static sNode*% create_continue(sParserInfo* info)
{
    sNode*% result = new sNode;
    
    result.kind = kContinue;
    
    result.fname = info->fname;
    result.sline = info->sline;
    
    return result;
}

static sNode*% create_break(sParserInfo* info)
{
    sNode*% result = new sNode;
    
    result.kind = kBreak;
    
    result.fname = info->fname;
    result.sline = info->sline;
    
    return result;
}

void sNode_finalize(sNode* self) version 10
{
    inherit(self);

    if(self.kind == kWhile) {
        delete self.value.whileValue.while_exp;
        delete self.value.whileValue.while_nodes;
        if(self.value.whileValue.else_nodes) {
            delete self.value.whileValue.else_nodes
        }
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
        
        list<sNode*%>*% while_nodes = parse_block(info);
        
        list<sNode*%>*%? else_nodes = null;
        
        if(word_cmp(info->p, "else")) {
            info->p += strlen("else");
            skip_spaces_until_eol(info);
            
            if(*info->p == ':') {
                info->p++;
                skip_spaces_until_eol(info);
            }
            else {
                fprintf(stderr, "%s %d: require : for block\n", info->fname, info->sline);
                return null;
            }
            
            else_nodes = parse_block(info);
        }
        
        result = borrow create_while(while_exp, while_nodes, else_nodes, info);
    }
    else if(word_cmp(info->p, "break")) {
        info->p += strlen("break");
        skip_spaces_until_eol(info);
        
        result = borrow create_break(info);
    }
    else if(word_cmp(info->p, "continue")) {
        info->p += strlen("continue");
        skip_spaces_until_eol(info);
        
        result = borrow create_continue(info);
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
        list<sNode*%>* while_nodes = borrow node.value.whileValue.while_nodes;
        list<sNode*%>* else_nodes = borrow node.value.whileValue.else_nodes;
        
        int head = codes.length();
        
        int head_before = info->loop_head;
        info->loop_head = head;
        
        vector<int>* breaks_before = info->breaks;
        info->breaks = borrow new vector<int>.initialize();
        
        buffer*% while_codes = compile_nodes(while_nodes, info);
        
        if(!compile(while_exp, codes, info)) {
            return false;
        }
        
        codes.append_int(OP_IF);
        
        int offset = while_codes.length();
        offset = (offset + 3) & ~3;
        
        offset /= sizeof(int);
        
        offset += 2`goto;
        
        codes.append_int(offset);
        
        int while_codes_top = codes.len;
        
        codes.append(while_codes.buf, while_codes.len);
        codes.alignment();
        
        info->stack_num--;
        
        codes.append_int(OP_GOTO);
        codes.append_int(head);
        
        if(else_nodes) {
            buffer*% else_codes = compile_nodes(else_nodes, info);
            
            codes.append(else_codes.buf, else_codes.len);
            codes.alignment();
        }
        
        for(int i=0; i<info->breaks.length(); i++) {
            int break_point = info->breaks.item(i, -1);
            
            int* p = (int*)(codes.buf + while_codes_top + break_point);
            
            *p = codes.length();
        }
        
        delete info->breaks;
        
        info->breaks = breaks_before;
        info->loop_head = head_before;
    }
    else if(node.kind == kBreak) {
        if(info->breaks == null) {
            fprintf(stderr, "%s %d: require loop for break\n", info->fname, info->sline);
            return false;
        }
        
        codes.append_int(OP_GOTO);
        
        int break_point = codes.len;
        info->breaks.push_back(break_point);
        
        codes.append_int(0);
    }
    else if(node.kind == kContinue) {
        if(info->loop_head == -1) {
            fprintf(stderr, "%s %d: require loop for continue\n", info->fname, info->sline);
            return false;
        }
        
        codes.append_int(OP_GOTO);
        codes.append_int(info->loop_head);
    }
    
    return true;
}

