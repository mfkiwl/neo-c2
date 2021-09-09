#include <limits.h>
#include <wchar.h>
#include <pcre.h>
#include <sys/ioctl.h>

typedef wchar_t*% wstring;

struct regex_struct 
{
    char str[128];
    pcre* regex;

    bool ignore_case;
    bool multiline;
    bool global;
    bool extended;
    bool dotall;
    bool anchored;
    bool dollar_endonly;
    bool ungreedy;

    int options;

    pcre* re;
};

typedef regex_struct*% nregex;

regex_struct*% regex(char* str, bool ignore_case, bool multiline, bool global, bool extended, bool dotall, bool anchored, bool dollar_endonly, bool ungreedy);
bool char::match(char* self, regex_struct* reg, list<string>?* group_strings);
int char::index(char* str, char* search_str, int default_value);
int char::rindex(char* str, char* search_str, int default_value);
int char::index_regex(char* self, regex_struct* reg, int default_value);
int char::rindex_regex(char* self, regex_struct* reg, int default_value);
void char::replace(char* self, int index, char c);
string char::multiply(char* str, int n);
string char::sub(char* self, regex_struct* reg, char* replace, list<string>?* group_strings);
list<string>*% char::scan(char* self, regex_struct* reg);
list<string>*% char::split(char* self, regex_struct* reg);
list<string>*% char::split_char(string& self, char c) ;
nregex char::to_regex(char* self) ;
string char::printable(char* str);
char* char::delete(char* str, int head, int tail) ;
string int::to_string(wchar_t* wstr);
wstring wstring(char* str);
wstring char::to_wstring(char* str);
wstring int::substring(wchar_t* str, int head, int tail);
int int::length(wchar_t* str);
wchar_t* int::delete(wchar_t* str, int head, int tail) ;
int int::index(wchar_t* str, wchar_t* search_str, int default_value);
int int::rindex(wchar_t* str, wchar_t* search_str, int default_value);
wstring int::reverse(whar_t* str) ;
wstring int::multiply(wchar_t* str, int n);
wstring int::printable(wchar_t* str);
