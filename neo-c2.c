#include <neo-c2.h>

regex_struct* regex(char* str, bool ignore_case, bool multiline, bool global, bool extended, bool dotall, bool anchored, bool dollar_endonly, bool ungreedy)
{
    auto result = new regex_struct;

    const char* err;
    int erro_ofs;

    int options = PCRE_UTF8 | (ignore_case ? PCRE_CASELESS:0) | (multiline ? PCRE_MULTILINE : 0) | (extended ? PCRE_EXTENDED :0) | (dotall ? PCRE_DOTALL :0) | (dollar_endonly ? PCRE_DOLLAR_ENDONLY:0) | (ungreedy ? PCRE_UNGREEDY:0);

    strncpy(result.str, str, 128);

    result.ignore_case = ignore_case;
    result.multiline = multiline;
    result.global = global;
    result.extended = extended;
    result.dotall = dotall;
    result.anchored = anchored;
    result.dollar_endonly = dollar_endonly;
    result.ungreedy;
    result.options = options;

    result.re = pcre_compile(str, options, &err, &erro_ofs, NULL);

    if(result.re == NULL) {
        return NULL;
    }

    return result;
}

bool char::match(char* self, regex_struct* reg)
{
    int offset = 0;

    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self);

        int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }

        /// match and no group strings ///
        if(regex_result > 0)
        {
            return true;
        }
        /// no match ///
        else
        {
            return false;
        }
    }

    return false;
}

bool char::match_count(char* self, regex_struct* reg, int count)
{
    int offset = 0;

    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;
    
    int n = 0;

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self);

        int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }

        /// match and no group strings ///
        if(regex_result > 0)
        {
            n++;
            
            if(count == n) {
                return true;
            }

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }
        }
        /// no match ///
        else
        {
            return false;
        }
    }

    return false;
}

bool char::match_group_strings(char* self, regex_struct* reg, int count, list<string>?* group_strings)
{
    int offset = 0;

    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;
    
    int n = 0;

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self);

        int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }

        /// match and no group strings ///
        if(regex_result == 1 || (group_strings == null && regex_result > 0)) 
        {
            n++;
            
            if(n == count) {
                return true;
            }

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }
        }
        /// group strings ///
        else if(regex_result > 1) {
            n++;
            
            group_strings.reset();
            for(int i = 1; i<regex_result; i++) {
                auto match_string = self.substring(start[i], end[i]);
                group_strings.push_back(match_string);
            }
            
            if(n == count) {
                return true;
            }

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }
        }
        /// no match ///
        else
        {
            return false;
        }
    }

    return false;
}

int char::index(char* str, char* search_str, int default_value)
{
    char* head = strstr(str, search_str);

    if(head == null) {
        return default_value;
    }

    return head - str;
}

int char::index_count(char* str, char* search_str, int count, int default_value)
{
    int n = 0;
    int len = strlen(str);
    for(int i=0; i<len; i++) {
        int len2 = strlen(search_str);
        int j;
        for(j=0; j<len2; j++) {
            if(str[i+j] != search_str[j]) {
                break;
            }
        }
        
        if(j == len2) {
            n++;
            
            if(n == count) {
                return i;
            }
        }
    }
    
    return default_value;
}

int char::rindex(char* str, char* search_str, int default_value)
{
    int len = strlen(search_str);
    char* p = str + strlen(str) - len;

    while(p >= str) {
        if(strncmp(p, search_str, len) == 0) {
            return p - str;
        }

        p--;
    }

    return default_value;
}

int char::rindex_count(char* str, char* search_str, int count, int default_value)
{
    int len = strlen(search_str);
    char* p = str + strlen(str) - len;
    
    int n = 0;

    while(p >= str) {
        if(strncmp(p, search_str, len) == 0) {
            n++;
            if(n == count) {
                return p - str;
            }
        }

        p--;
    }

    return default_value;
}


int char::index_regex(char* self, regex_struct* reg, int default_value)
{
    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    int result = default_value;
    
    int offset = 0;

    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self);
        int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }

        /// match and no group strings ///
        if(regex_result == 1 || regex_result > 0) 
        {
            result = start[0];
            break;
        }
        /// no match ///
        else 
        {
            break;
        }
    }

    return result;
}

int char::index_regex_count(char* self, regex_struct* reg, int count, int default_value)
{
    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    int result = default_value;
    
    int offset = 0;

    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;
    
    int n = 0;

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self);
        int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }
        
        /// match and no group strings ///
        if(regex_result > 0) {
            n++;

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }
            
            if(n == count) {
                result = start[0];
                break;
            }
        }
        /// no match ///
        else {
            break;
        }
    }

    return result;
}

int char::rindex_regex(char* self, regex_struct* reg, int default_value)
{
    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;

    string self2 = self.reverse();
    
    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    int result = default_value;
    
    int offset = 0;

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self2);
        int regex_result = pcre_exec(re, 0, self2, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }

        /// match and no group strings ///
        if(regex_result == 1 || regex_result > 0) 
        {
            result = strlen(self) - end[0];
            break;
        }
        /// no match ///
        else 
        {
            break;
        }
    }

    return result;
}

int char::rindex_regex_count(char* self, regex_struct* reg, int count, int default_value)
{
    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;

    string self2 = self.reverse();
    
    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    int result = default_value;
    
    int offset = 0;
    
    int n = 0;

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self2);
        int regex_result = pcre_exec(re, 0, self2, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }
        
        /// match and no group strings ///
        if(regex_result > 0)
        {
            n++;

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }
            
            if(n == count) {
                result = strlen(self) - end[0];
                break;
            }
        }
        /// no match ///
        else 
        {
            break;
        }
    }

    return result;
}

void char::replace(char* self, int index, char c)
{
    int len = strlen(self);

    if(strcmp(self, "") == 0) {
        return;
    }
    
    if(index < 0) {
       index += len;
    }

    if(index >= len) {
        index = len-1;
    }

    if(index < 0) {
        index = 0;
    }
    
    self[index] = c;
}

string char::multiply(char* str, int n)
{
    int len = strlen(str) * n + 1;

    char* result = new char[len];

    result[0] = '\0';

    for(int i=0; i<n; i++) {
        strcat(result, str);
    }

    return result;
}

string char::sub(char* self, regex_struct* reg, char* replace)
{
    int offset = 0;

    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;

    auto result = new buffer.initialize();

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self);
        int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }

        /// match and no group strings ///
        if(regex_result == 1)
        {
            string str = self.substring(offset, start[0]);

            result.append_str(str);
            result.append_str(replace);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }

            if(!reg.global) {
                string str = self.substring(offset, -1);
                result.append_str(str);
                break;
            }
        }
        /// no match ///
        else {
            string str = self.substring(offset, -1);
            result.append_str(str);
            break;
        }
    }

    return result.to_string();
}

string char::sub_count(char* self, regex_struct* reg, char* replace, int count)
{
    int offset = 0;

    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;

    auto result = new buffer.initialize();
    
    int n = 0;

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self);
        int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }

        /// match and no group strings ///
        if(regex_result == 1)
        {
            n++;
            string str = self.substring(offset, start[0]);

            result.append_str(str);
            result.append_str(replace);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }

            if(!reg.global) {
                string str = self.substring(offset, -1);
                result.append_str(str);
                break;
            }
            if(n == count) {
                string str = self.substring(offset, -1);
                result.append_str(str);
                break;
            }
        }
        /// no match ///
        else {
            string str = self.substring(offset, -1);
            result.append_str(str);
            break;
        }
    }

    return result.to_string();
}

string char::sub_block(char* self, regex_struct* reg, void* parent, string (*block)(void* parent, string match_string, list<string>* group_strings))
{
    int offset = 0;

    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;

    auto result = new buffer.initialize();

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self);
        int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }

        /// match and no group strings ///
        if(regex_result == 1) {
            string str = self.substring(offset, start[0]);

            result.append_str(str);
            
            list<string>* group_strings = new list<string>.initialize();
            
            string match_string = self.substring(start[0], end[0]);
            
            group_strings.push_back(self.substring(start[0], end[0]));
            
            string block_result = block(parent, match_string, group_strings);
            result.append_str(block_result);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }

            if(!reg.global) {
                string str = self.substring(offset, -1);
                result.append_str(str);
                break;
            }
        }
        /// group strings ///
        else if(regex_result > 1) {
            string str = self.substring(offset, start[0]);
            result.append_str(str);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }
            
            list<string>* group_strings = new list<string>.initialize();

            for(int i = 1; i<regex_result; i++) {
                auto match_string = self.substring(start[i], end[i]);
                group_strings.push_back(match_string);
            }
            
            string match_string = self.substring(start[0], end[0]);
            
            string block_result = block(parent, match_string, group_strings);
            result.append_str(block_result);

            if(!reg.global) {
                string str = self.substring(offset, -1);
                result.append_str(str);
                break;
            }
        }
        /// no match ///
        else {
            string str = self.substring(offset, -1);
            result.append_str(str);
            break;
        }
    }
    return result.to_string();
}

string char::sub_block_count(char* self, regex_struct* reg, int count, void* parent, string (*block)(void* parent, string match_string, list<string>* group_strings))
{
    int offset = 0;

    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;

    auto result = new buffer.initialize();
    
    int n = 0;

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self);
        int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }

        /// match and no group strings ///
        if(regex_result == 1) {
            n++;
            string str = self.substring(offset, start[0]);

            result.append_str(str);
            
            list<string>* group_strings = new list<string>.initialize();
            
            group_strings.push_back(self.substring(start[0], end[0]));
            
            string match_string = self.substring(start[0], end[0]);
            
            string block_result = block(parent, match_string, group_strings);
            result.append_str(block_result);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }

            if(!reg.global) {
                string str = self.substring(offset, -1);
                result.append_str(str);
                break;
            }
            
            if(n == count) {
                string str = self.substring(offset, -1);
                result.append_str(str);
                break;
            }
        }
        /// group strings ///
        else if(regex_result > 1) {
            n ++;
            
            string str = self.substring(offset, start[0]);
            result.append_str(str);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }
            
            list<string>* group_strings = new list<string>.initialize();

            for(int i = 1; i<regex_result; i++) {
                auto match_string = self.substring(start[i], end[i]);
                group_strings.push_back(match_string);
            }
            
            string match_string = self.substring(start[0], end[0]);
            
            string block_result = block(parent, match_string, group_strings);
            result.append_str(block_result);

            if(!reg.global) {
                string str = self.substring(offset, -1);
                result.append_str(str);
                break;
            }
            
            if(n == count) {
                string str = self.substring(offset, -1);
                result.append_str(str);
                break;
            }
        }
        /// no match ///
        else {
            string str = self.substring(offset, -1);
            result.append_str(str);
            break;
        }
    }

    return result.to_string();
}

list<string>* char::scan(char* self, regex_struct* reg)
{
    auto result = new list<string>.initialize();

    int offset = 0;

    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self);
        int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }

        /// match and no group strings ///
        if(regex_result == 1)
        {
            auto str = self.substring(start[0], end[0]);
            result.push_back(str);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }
        }
        /// group strings ///
        else if(regex_result > 1) {
            auto str = self.substring(start[0], end[0]);
            result.push_back(str);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }

            for(int i= 1; i<regex_result; i++) {
                auto match_string = self.substring(start[i], end[i]);
                result.push_back(match_string);
            }
        }
        /// no match ///
        else
        {
            break;
        }
    }

    return result;
}

list<string>* char::scan_block(char* self, regex_struct* reg, void* parent, string (*block)(void* parent, string match_string, list<string>* group_strings))
{
    auto result = new list<string>.initialize();

    int offset = 0;

    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self);
        int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }

        /// match and no group strings ///
        if(regex_result == 1)
        {
            auto str = self.substring(start[0], end[0]);
            
            list<string>* group_strings = new list<string>.initialize();
            
            string str2 = block(parent, str, group_strings);
            
            result.push_back(str2);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }
        }
        /// group strings ///
        else if(regex_result > 1) {
            auto str = self.substring(start[0], end[0]);

            list<string>* group_strings = new list<string>.initialize();
            for(int i= 1; i<regex_result; i++) {
                auto match_string = self.substring(start[i], end[i]);
                group_strings.push_back(match_string);
            }
            
            string str2 = block(parent, str, group_strings);
            
            result.push_back(str2);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }
        }
        /// no match ///
        else
        {
            break;
        }
    }

    return result;
}

list<string>* char::scan_block_count(char* self, regex_struct* reg, int count, void* parent, string (*block)(void* parent, string match_string, list<string>* group_strings))
{
    auto result = new list<string>.initialize();

    int offset = 0;

    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;
    
    int n = 0;

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self);
        int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }

        /// match and no group strings ///
        if(regex_result == 1)
        {
            auto str = self.substring(start[0], end[0]);
            
            list<string>* group_strings = new list<string>.initialize();
            
            string str2 = block(parent, str, group_strings);
            
            result.push_back(str2);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }
            
            n++;
            if(n == count) {
                break;
            }
        }
        /// group strings ///
        else if(regex_result > 1) {
            auto str = self.substring(start[0], end[0]);

            list<string>* group_strings = new list<string>.initialize();
            for(int i= 1; i<regex_result; i++) {
                auto match_string = self.substring(start[i], end[i]);
                group_strings.push_back(match_string);
            }
            
            string str2 = block(parent, str, group_strings);
            
            result.push_back(str2);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }
            
            n++;
            if(n == count) {
                break;
            }
        }
        /// no match ///
        else
        {
            break;
        }
    }

    return result;
}

list<string>* char::split(char* self, regex_struct* reg)
{
    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;

    auto result = new list<string>.initialize();

    int offset = 0;

    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self);

        int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }

        /// match and no group strings ///
        if(regex_result == 1)
        {
            string str = self.substring(offset, start[0]);
            result.push_back(str);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }
        }
        /// group strings ///
        else if(regex_result > 1) {
            string str = self.substring(offset, start[0]);
            result.push_back(str);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }

            for(int i=1; i<regex_result; i++) {
                string match_str = self.substring(start[i], end[i]);
                result.push_back(match_str);
            }
        }
        /// no match ///
        else
        {
            break;
        }
    }

    if(offset < self.length()) {
        string str = self.substring(offset, -1);
        result.push_back(str);
    }

    return result;
}

list<string>* char::split_maxsplit(char* self, regex_struct* reg, int maxsplit)
{
    const char* err;
    int erro_ofs;

    int options = reg.options;
    char* str = reg.str;

    pcre* re = reg.re;

    auto result = new list<string>.initialize();

    int offset = 0;

    int ovec_max = 16;
    int start[ovec_max];
    int end[ovec_max];
    int ovec_value[ovec_max * 3];
    
    int n = 0;

    while(true) {
        int options = PCRE_NEWLINE_LF;
        int len = strlen(self);

        int regex_result = pcre_exec(re, 0, self, len, offset, options, ovec_value, ovec_max*3);

        for(int i=0; i<ovec_max; i++) {
            start[i] = ovec_value[i*2];
        }
        for(int i=0; i<ovec_max; i++) {
            end[i] = ovec_value[i*2+1];
        }

        /// match and no group strings ///
        if(regex_result == 1)
        {
            string str = self.substring(offset, start[0]);
            result.push_back(str);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }
        }
        /// group strings ///
        else if(regex_result > 1) {
            string str = self.substring(offset, start[0]);
            result.push_back(str);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }

            for(int i=1; i<regex_result; i++) {
                string match_str = self.substring(start[i], end[i]);
                result.push_back(match_str);
            }
        }
        /// no match ///
        else
        {
            break;
        }
        
        n++;
        
        if(maxsplit == n) {
            break;
        }
    }

    if(offset < self.length()) {
        string str = self.substring(offset, -1);
        result.push_back(str);
    }

    return result;
}

list<string>* char::split_char(string self, char c) 
{
    auto result = new list<string>.initialize();

    auto str = new buffer.initialize();

    for(int i=0; i<self.length(); i++) {
        if(self[i] == c) {
            result.push_back(string(str.buf));
            str = new buffer.initialize();
        }
        else {
            str.append_char(self[i]);
        }
    }
    if(str.length() != 0) {
        result.push_back(string(str.buf));
    }

    return result;
}

list<string>* char::split_str(string self, char* str) 
{
    auto result = new list<string>.initialize();

    auto buf = new buffer.initialize();

    for(int i=0; i<self.length(); i++) {
        if(strstr(self + i, str) == self + i) {
            result.push_back(string(buf.buf));
            buf = new buffer.initialize();
            i += strlen(str)-1;
        }
        else {
            buf.append_char(self[i]);
        }
    }
    if(buf.length() != 0) {
        result.push_back(string(buf.buf));
    }

    return result;
}

nregex char::to_regex(char* self) 
{
    return regex(self, false, false, false, false, false, false, false, false);
}

nregex char::to_regex_flags(char* self, bool global, bool ignore_case)
{
    return regex(self, ignore_case, false, global, false, false, false, false, false);
}

string char::printable(char* str)
{
    int len = str.length();
    string result = new char[len*2+1];

    int n = 0;
    for(int i=0; i<len; i++) {
        char c = str[i];

        if((c >= 0 && c < ' ') 
            || c == 127)
        {
            result[n++] = '^';
            result[n++] = c + 'A' - 1;
        }
        else {
            result[n++] = c;
        }
    }

    result[n] = '\0'

    return result;
}

char* char::delete(char* str, int head, int tail) 
{
    int len = strlen(str);

    if(strcmp(str, "") == 0) {
        return str;
    }
    
    if(head < 0) {
       head += len;
    }
    
    if(tail < 0) {
       tail += len + 1;
    }

    if(head < 0) {
        head = 0;
    }

    if(tail < 0) {
        return str;
    }

    if(tail >= len) {
        tail = len;
    }
    
    string sub_str = str.substring(tail, -1);

    memcpy(str + head, sub_str, sub_str.length()+1);

    return str;
}

/// wstring ///
string int::to_string(wchar_t* wstr)
{
    int len = MB_LEN_MAX*(wcslen(wstr)+1);

    string result = new char[len];

    if(wcstombs(result, wstr, len) < 0) 
    {
        strncpy(result, "", len);
    }

    return result;
}

wstring wstring(char* str)
{
    int len = strlen(str);

    wstring wstr = new wchar_t[len+1];

    int ret = mbstowcs(wstr, str, len+1);
    wstr[ret] = '\0';

    if(ret < 0) {
        wstr[0] = 0;
    }

    return wstr;
}

wstring char::to_wstring(char* str)
{
    return wstring(str);
}

wstring int::substring(wchar_t* str, int head, int tail)
{
    if(str == null) {
        return wstring("");
    }

    int len = wcslen(str);

    if(head < 0) {
        head += len;
    }
    if(tail < 0) {
        tail += len + 1;
    }

    if(head > tail) {
        return wstring("");
    }

    if(head < 0) {
        head = 0;
    }

    if(tail >= len) {
        tail = len;
    }

    if(head == tail) {
        return wstring("");
    }

    if(tail-head+1 < 1) {
        return wstring("");
    }

    wstring result = new wchar_t[tail-head+1];

    memcpy(result, str + head, sizeof(wchar_t)*(tail-head));
    result[tail-head] = '\0';

    return result;
}

int int::length(wchar_t* str)
{
    return wcslen(str);
}

wchar_t* int::delete(wchar_t* str, int head, int tail) 
{
    int len = wcslen(str);

    if(len == 0) {
        return str;
    }
    
    if(head < 0) {
       head += len;
    }
    
    if(tail < 0) {
       tail += len + 1;
    }

    if(head < 0) {
        head = 0;
    }

    if(tail < 0) {
        return str;
    }

    if(tail >= len) {
        tail = len;
    }
    
    wstring sub_str = str.substring(tail, -1);

    memcpy(str + head, sub_str, sizeof(wchar_t)*(sub_str.length()+1));

    return str;
}

int int::index(wchar_t* str, wchar_t* search_str, int default_value)
{
    wchar_t* head = wcsstr(str, search_str);

    if(head == null) {
        return default_value;
    }

    return head - str;
}

int int::rindex(wchar_t* str, wchar_t* search_str, int default_value)
{
    int len = wcslen(search_str);

    wchar_t* p = str + wcslen(str) - len;

    while(p >= str) {
        int len2 = wcslen(p);
        bool result = true;
        int i;
        for(i=0; i<len && i < len2; i++) {
            if(p[i] != search_str[i]) {
                result = false;
            }
        }
        if(result) {
            return (p - str);
        }

        p--;
    }

    return default_value;
}

wstring int::reverse(whar_t* str) 
{
    int len = wcslen(str);
    wstring result = new wchar_t[len + 1];

    for(int i=0; i<len; i++) {
        result[i] = str[len-i-1];
    }

    result[len] = '\0';

    return result;
}

wstring int::multiply(wchar_t* str, int n)
{
    int len = wcslen(str) * n + 1;

    wchar_t* result = new wchar_t[len];

    result[0] = '\0';

    for(int i=0; i<n; i++) {
        wcscat(result, str);
    }

    return result;
}

wstring int::printable(wchar_t* str)
{
    int len = str.length();
    wstring result = new wchar_t[len*2+1];

    int n = 0;
    for(int i=0; i<len; i++) {
        wchar_t c = str[i];

        if((c >= 0 && c < ' ') 
            || c == 127)
        {
            result[n++] = '^';
            result[n++] = c + 'A' - 1;
        }
        else {
            result[n++] = c;
        }
    }

    result[n] = '\0'

    return result;
}
