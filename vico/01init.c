#include "common.h"

/*
bool xiswalpha(wchar_t* c)
{
    bool result = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    return result;
}

bool xiswblank(wchar_t* c)
{
    return c == ' ' || c == '\t';
}

bool xiswalnum(wchar_t* c)
{
    return xiswalpha(c) || xiswdigit(c);
}

bool xiswdigit(wchar_t* c)
{
    return (c >= '0' && c <= '9');
}

int xgetmaxx(){
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

int xgetmaxy(){
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

ViWin*% initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi) {
    self.texts = borrow new list<wstring>.initialize();

    self.y = y;
    self.x = x;
    self.width = width;
    self.height = height;

    self.scroll = 0;
    self.vi = vi;

    var win = newwin(height, width, y, x);

    self.win = win;

    keypad(self.win, true);

    return self;
}

void ViWin_finalize(ViWin* self) 
{
    delete self.texts;
    delwin(self.win);
}

void ViWin_view(ViWin* self, Vi* nvi) 
{
    werase(self.win);

    int it2 = 0;
    foreach(it, self.texts) {
        mvwprintw(self.win, it2, 0, it.to_string(""));
        it2++;
    }

    wrefresh(self.win);
}

void ViWin_input(ViWin* self, Vi* nvi) 
{
    var key = wgetch(self.win);
}

Vi*% Vi_initialize(Vi* self) 
{
    self.init_curses();

    self.wins = borrow new list<ViWin*%>.initialize();

    var maxx = xgetmaxx();
    var maxy = xgetmaxy();

    var win = new ViWin.initialize(0, 0, maxx-1, maxy, self);

    win.texts.push_back(wstring("aaa"));
    win.texts.push_back(wstring("bbb"));
    win.texts.push_back(wstring("ccc"));

    self.activeWin = win;

    self.wins.push_back(win);

    return self;
}

void Vi_finalize(Vi* self) 
{
    delete self.wins;

    endwin();
}

int Vi_main_loop(Vi* self) 
{
    foreach(it, self.wins) {
        it.view(self);
    }

    self.activeWin.input(self);

    return 1;
}

void Vi_init_curses(Vi* self) 
{
    initscr();
    noecho();
    keypad(stdscr, true);
    raw();
    curs_set(0);
}
*/
