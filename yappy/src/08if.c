#include "common.h"

static sNode* create_if(sNode* if_exp, buffer* if_codes, vector<sNode*>* elif_exps, vector<buffer*>* elif_blocks, buffer*? else_block, sParserInfo* info)
{
    sNode* result = new sNode;
    
    result.kind = kIf;
    
    result.fname = info->fname;
    result.sline = info->sline;
    result.value.ifValue.if_exp = if_exp;
    result.value.ifValue.if_codes = if_codes;
    result.value.ifValue.elif_exps = elif_exps;
    result.value.ifValue.elif_blocks = elif_blocks;
    result.value.ifValue.else_block = else_block;
    
    return result;
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

sNode*? exp_node(sParserInfo* info) version 8
{
    sNode* result = null;
    
    if(word_cmp(info->p, "if")) {
        info->p += strlen("if");
        skip_spaces_until_eol(info);
        
        sNode* node = NULL;
        if(!expression(&node, info)) {
            fprintf(stderr, "%s %d: invalid if exp\n", info->fname, info->sline);
            return null;
        }
        
        sNode* if_exp = node;
        
        if(*info->p == ':') {
            info->p++;
            skip_spaces_until_eol(info);
        }
        else {
            fprintf(stderr, "%s %d: require : for block\n", info->fname, info->sline);
            return null;
        }
        
        buffer* if_codes = compile_block(info);
        
        vector<sNode*>* elif_exps = new vector<sNode*>.initialize();
        vector<buffer*>* elif_blocks = new vector<buffer*>.initialize();
        
        while(word_cmp(info->p, "elif")) {
            info->p += strlen("elif");
            skip_spaces_until_eol(info);
            
            sNode* node = null;
            if(!expression(&node, info)) {
                fprintf(stderr, "%s %d: invalid if exp\n", info->fname, info->sline);
                return null;
            }
            
            elif_exps.push_back(node);
            
            if(*info->p == ':') {
                info->p++;
                skip_spaces_until_eol(info);
            }
            else {
                fprintf(stderr, "%s %d: require : for block\n", info->fname, info->sline);
                return null;
            }
            
            buffer* elif_block = compile_block(info);
            
            elif_blocks.push_back(elif_block);
        }
        
        buffer*? else_block = null;
        
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
            
            else_block = compile_block(info);
        }
        
        result = create_if(if_exp, if_codes, elif_exps, elif_blocks, else_block, info);
    }
    
    if(result == null) {
        result = inherit(info);
    }
    
    return result;
}


bool compile(sNode* node, buffer* codes, sParserInfo* info) version 8
{
    inherit(node, codes, info);
    
    if(node.kind == kIf) {
        sNode* if_exp = node.value.ifValue.if_exp;
        buffer* if_codes = node.value.ifValue.if_codes;
        vector<sNode*>* elif_exps = node.value.ifValue.elif_exps;
        vector<buffer*>* elif_blocks = node.value.ifValue.elif_blocks;
        buffer* else_block = node.value.ifValue.else_block;
        
        vector<int>* end_points = new vector<int>.initialize();
        
        if(!compile(if_exp, codes, info)) {
            return false;
        }
        
        codes.append_int(OP_IF);
        
        int offset = if_codes.length();
        offset = (offset + 3) & ~3;
        
        offset /= sizeof(int);
        
        offset += 2`goto;
        
        codes.append_int(offset);
        
        codes.append(if_codes.buf, if_codes.len);
        codes.alignment();
        
        info->stack_num--;
        
        codes.append_int(OP_GOTO);
        
        int end_point = codes.len;
        end_points.push_back(end_point);
        codes.append_int(0);
        
        for(int i= 0; i<elif_exps.length(); i++) {
            sNode* elif_exp = elif_exps.item(i, null);
            buffer* elif_block = elif_blocks.item(i, null);
            
            if(!compile(elif_exp, codes, info)) {
                return false;
            }
            
            codes.append_int(OP_IF);
            int offset = elif_block.length();
            offset = (offset + 3) & ~3;
            
            offset /= sizeof(int);
        
            offset += 2`goto;
            
            codes.append_int(offset);
            
            codes.append(elif_block.buf, elif_block.len);
            codes.alignment();
            
            info->stack_num--;
            
            codes.append_int(OP_GOTO);
            int end_point = codes.len;
            end_points.push_back(end_point);
            codes.append_int(0);
        }
        
        if(else_block) {
            codes.append(else_block.buf, else_block.len);
            codes.alignment();
        }
        
        for(int i=0; i<end_points.length(); i++) {
            int end_point = end_points.item(i, -1);
            
            int* p = (int*)(codes.buf + end_point);
            
            *p = codes.length();
        }
    }
    
    return true;
}

