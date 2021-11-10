#include "common.h"

void skip_spaces(sParserInfo* info)
{
    while(*info->p == ' ' || *info->p == '\t' || (*info->p == '\n' && info->sline++)) {
        info->p++;
    }
}

void skip_spaces_until_eol(sParserInfo* info)
{
    while(*info->p == ' ' || *info->p == '\t') {
        info->p++;
    }
}

static bool read_source(char* fname, buffer* source)
{
    FILE* f = fopen(fname, "r");
    
    if(f == null) {
        fprintf(stderr, "file %s is not found\n", fname);
        return false;
    }
    
    char line[4096];

    while(fgets(line, 4096, f) != null)
    {
        line[strlen(line)-1] = '\n';
        line[strlen(line)] = '\0';
        source.append_str(line);
    }

    fclose(f);
    
    return true;
}

static bool parse(sParserInfo* info, buffer* codes, int space_num)
{
    info->space_num = space_num;
    
    list<sNode*%>*% nodes = new list<sNode*%>.initialize();
    
    while(*info->p) {
        sNode* node = null;
        if(!expression(&node, info)) {
            fprintf(stderr, "%s %d: unexpected character (%c)\n", info->fname, info->sline, *info->p);
            return false;
        }
        
        nodes.push_back(dummy_heap node);
        
        if(*info->p == ';') {
            info->p++;
            skip_spaces_until_eol(info);
        }
        
        if(*info->p == '\n') {
            while(*info->p == '\n') {
                info->sline++;
                info->p++;
            }
            
            int space_num = 0;
            while(*info->p == ' ' || *info->p == '\t') {
                info->p++;
                space_num++;
            }
            
            if(space_num < info->space_num) {
                break;
            }
            else if(space_num > info->space_num) {
                fprintf(stderr, "%s %d: Invalid indent space number\n", info->fname, info->sline);
                exit(2);
            }
        }
    }
    
    foreach(it, nodes) {
        if(!compile(it, codes, info)) {
            return false;
        }
        
        if(info->stack_num >= 0) {
            codes.append_int(OP_POP);
            codes.append_int(info->stack_num);
            info->stack_num = 0;
        }
        else {
            fprintf(stderr, "%s %d: invalid stack num\n", info->fname, info->sline);
            return false;
        }
    }
    
    return true;
}

buffer*% parse_block(sParserInfo* info)
{
    int space_num = info.space_num;
    bool in_global_context = info.in_global_context;
    info.in_global_context = false;
    
    buffer*% codes = new buffer.initialize();
    
    /// multi line ///
    if(*info->p == '\n') {
        info->p++;
        info->sline++;
        
        int space_num = 0;
        while(*info->p == ' ' || *info->p == '\t') {
            info->p++;
            space_num++;
        }
        
        parse(info, codes, space_num).expect {
            exit(1);
        }
    }
    /// one line ///
    else {
    }
    
    info.in_global_context = in_global_context;
    info.space_num = space_num;
    
    return codes;
}

int main(int argc, char** argv)
{
    char* fname = null;
    
    for(int i=0; i<argc; i++) {
        if(argv[i][0] == '-') {
        }
        else {
            fname = argv[i];
        }
    }
    
    if(fname == null) {
    }
    else {
        initialize_modules();
        
        buffer*% source = new buffer.initialize();
        
        read_source(fname, source).expect {
            exit(1);
        }
        
        buffer*% codes = new buffer.initialize();
        
        sParserInfo info;
        
        info.p = borrow source.to_string();
        info.fname = fname;
        info.sline = 1;
        info.stack_num = 0;
        info.in_global_context = true;
        info.space_num = 0;
        
        parse(&info, codes, 0`space_num).expect {
            exit(1);
        }
        
        vm(codes, null).expect {
            exit(1);
        }
        
        finalize_modules();
    }
    
    return 0;
}

