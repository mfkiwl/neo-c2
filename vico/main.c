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
    var ws = new winsize;
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
    var ws = new winsize;
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

    var vi = new Vi.initialize();
    
/*
    if(num_file_names > 0) {
        vi.openFile(file_names[0], line_num);
    }
    else {
        vi.openFile(null, -1);
    }
*/
    
    return vi.main_loop();
}
