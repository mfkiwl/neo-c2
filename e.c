#include <stdio.h>
#include <ncurses.h>

int fileCommmmmm()
{
    int cursor = 0;
    int scrolltop = 0;
    int scroll_size = 0;
    int canceled = 0;
    bool end_of_select = false;

    /// input ///
    auto key = getch();

    switch(key) {
        case KEY_UP:
        case 'k':
        case 'P'-'A'+1:
            cursor--;
            break;

        case KEY_DOWN:
        case 'j':
        case 'N'-'A'+1:
        case (('I'-'A')+1):
            cursor++;
            break;

        case 'D'-'A'+1:
            cursor+=10;
            break;
       
        case (('U'-'A')+1):
            cursor-=10;
            break;

        case ('C'-'A')+1:
        case 'q':
        case ('['-'A')+1:
            canceled = true;
            end_of_select = true;
            break;

        case KEY_ENTER:
        case ('J'-'A')+1:
            end_of_select = true;
            break;
    }
    
    // modification 
    if(cursor < 0) {
        int scroll_size = -cursor +1;
        
        cursor = 0;
        scrolltop-=scroll_size;

        if(scrolltop < 0) {
            scrolltop = 0;
            cursor = 0;
        }
    }
    aaa;
}

int main()
{
    fileCommmmmm();

    return 0;
}

