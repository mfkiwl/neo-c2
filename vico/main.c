#include "common.h"

bool xiswalpha(wchar_t c)
{
    bool result = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    return result;
}

bool xiswblank(wchar_t c)
{
    return c == ' ' || c == '\t';
}

bool xiswalnum(wchar_t c)
{
    return xiswalpha(c) || xiswdigit(c);
}

bool xiswdigit(wchar_t c)
{
    return (c >= '0' && c <= '9');
}

int xgetmaxx()
{
    auto ws = new winsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, ws);
    
    int result = ws.ws_col;
//Raspberry PI return -1
    if(result == -1) {
        return getmaxx(stdscr);
    }
    else {
        return result;
    }
}

int xgetmaxy()
{
    auto ws = new winsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, ws);
    
    int result = ws.ws_row;
//Raspberry PI return -1
    if(result == -1) {
        return getmaxy(stdscr);
    }
    else {
        return result;
    }
}

string xbasename(char* path)
{
    char* p = path + strlen(path);
    
    while(p >= path) {
        if(*p == '/') {
            break;
        }
        else {
            p--;
        }
    }
    
    if(p < path) {
        return string(path);
    }
    else {
        return string(p+1);  
    }
}

string xrealpath(char* path)
{
    char* result = realpath(path, null);

    string result2 = string(result);

    free(result);

    return result2;
}

wstring wstring(char* str)
{
    int len = strlen(str);

wstring a = new wchar_t[1];
// I can't understand. this requires for s309x apline linux,... hmm is it my mistake?

    wstring wstr = new wchar_t[len+1];

    int ret = mbstowcs(wstr, str, len+1);
    wstr[ret] = '\0';

    if(ret < 0) {
        wstr[0] = 0;
    }

    return wstr;
}

wstring int_substring(wchar_t* str, int head, int tail)
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

wstring int_printable(wchar_t* str)
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

string char_multiply(char* str, int n)
{
    int len = strlen(str) * n + 1;

    char*% result = new char[len];

    result[0] = '\0';

    for(int i=0; i<n; i++) {
        strcat(result, str);
    }

    return result;
}

wstring int_multiply(wchar_t* str, int n)
{
    int len = wcslen(str) * n + 1;

    wchar_t*% result = new wchar_t[len];

    result[0] = '\0';

    for(int i=0; i<n; i++) {
        wcscat(result, str);
    }

    return result;
}


int int_length(wchar_t* str)
{
    return wcslen(str);
}

wchar_t* int_delete(wchar_t* str, int head, int tail) 
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

int int_index(wchar_t* str, wchar_t* search_str, int default_value)
{
    wchar_t* head = wcsstr(str, search_str);

    if(head == null) {
        return default_value;
    }

    return head - str;
}

int int_rindex(wchar_t* str, wchar_t* search_str, int default_value)
{
    int len = wcslen(search_str);

    wchar_t* p = str + wcslen(str) - len;

    while(p >= str) {
        if(wcscmp(p, search_str) == 0) {
            return (p - str);
        }

        p--;
    }

    return default_value;
}

string int_to_string(wchar_t* wstr)
{
    int len = MB_LEN_MAX*(wcslen(wstr)+1);

    string result = new char[len];

    if(wcstombs(result, wstr, len) < 0) 
    {
        strncpy(result, "", len);
    }

    return result;
}

wstring int_reverse(whar_t* str) 
{
    int len = wcslen(str);
    wstring result = new wchar_t[len + 1];

    for(int i=0; i<len; i++) {
        result[i] = str[len-i-1];
    }

    result[len] = '\0';

    return result;
}

wstring char_to_wstring(char* str)
{
    return wstring(str);
}

regex_struct*% regex(char* str, bool ignore_case, bool multiline, bool global, bool extended, bool dotall, bool anchored, bool dollar_endonly, bool ungreedy)
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

bool char_match(char* self, regex_struct* reg, list<string>?* group_strings)
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
        if(regex_result == 1 || (group_strings == null && regex_result > 0)) 
        {
            return true;
        }
        /// group strings ///
        else if(regex_result > 1) {
            group_strings.reset();
            for(int i = 1; i<regex_result; i++) {
                auto match_string = borrow self.substring(start[i], end[i]);
                group_strings.push_back(match_string);
            }

            return true;
        }
        else
        /// no match ///
        {
            return false;
        }
    }

    return false;
}

string char_sub(char* self, regex_struct* reg, char* replace, list<string>?* group_strings)
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
        if(regex_result == 1 || (group_strings == null && regex_result > 0)) 
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
        /// group strings ///
        else if(regex_result > 1) {
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
                group_strings.reset();
            }

            for(int i = 1; i<regex_result; i++) {
                auto match_string = borrow self.substring(start[i], end[i]);
                group_strings.push_back(match_string);
            }

            if(!reg.global) {
                string str = self.substring(offset, -1);
                result.append_str(str);
                break;
            }
        }
        else
        /// no match ///
        {
            string str = self.substring(offset, -1);
            result.append_str(str);
            break;
        }
    }

    return result.to_string();
}

list<string>*% char_scan(char* self, regex_struct* reg)
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
            auto str = borrow self.substring(start[0], end[0]);
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
            auto str = borrow self.substring(start[0], end[0]);
            result.push_back(str);

            if(offset == end[0]) {
                offset++;
            }
            else {
                offset = end[0];
            }

            for(int i= 1; i<regex_result; i++) {
                auto match_string = borrow self.substring(start[i], end[i]);
                result.push_back(match_string);
            }
        }
        else
        /// no match ///
        {
            break;
        }
    }

    return result;
}

int char_index(char* str, char* search_str, int default_value)
{
    char* head = strstr(str, search_str);

    if(head == null) {
        return default_value;
    }

    return head - str;
}

int char_rindex(char* str, char* search_str, int default_value)
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

int char_index_regex(char* self, regex_struct* reg, int default_value)
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
        {
            break;
        }
    }

    return result;
}

int main(int argc, char** argv)
{
    int line_num = -1;
    char* file_names[128];
    int num_file_names = 0;
    
    for(int i=1; i<argc; i++) {
        if(argv[i][0] == '+') {
            sscanf(argv[i], "+%d", &line_num);
            line_num--;

            if(line_num < 0) {
                line_num = 0;
            }
        }
        else {
            file_names[num_file_names] = argv[i];
            num_file_names++;
            
            if(num_file_names >= 128) {
                fprintf(stderr, "overflow file names\n");
                exit(2);
            }
        }
    }

    auto vi = new Vi.initialize();
    
    if(num_file_names > 0) {
        vi.openFile(file_names[0], line_num);
    }
    else {
        vi.openFile(null, -1);
    }
    
    return vi.main_loop();
}
