#include <neo-c2.h>
#include <neo-c2-pcre.h>

int main()
{
    auto word = string("ABC");
    list<int>*% li = new list<int>.initialize();

    li.push_back(1);
    
    if(li.length() > 0) {
        int i = li.item(0, null);

        char header_name[512];

        snprintf(header_name, 512, "%d", i);

        auto candidates = new list<string>.initialize();
        
        buffer*% command_result = new buffer.initialize();
        
        if(true) {
            auto candidates3 = new list<string>.initialize();
            list<string>*% candidates2 = string("AAA\nBBB\nCCC").split_char('\n');

            char xxx[512];
            strncpy(xxx, "XXX", 512);
            
            candidates2.each {
                char fun_name[512];

                snprintf(fun_name, 512, "%s %s %s", *parent.word, it, parent.xxx);

                (*parent.candidates).push_back(string(it));

                puts(fun_name);
            }
        }

    }

    return 0;
}
