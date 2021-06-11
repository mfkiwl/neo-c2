#include "common.h"

ViWin*% ViWin_initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi) 
{
    self.texts = borrow new list<wstring>.initialize();

    self.y = y;
    self.x = x;
    self.width = width;
    self.height = height;

    self.scroll = 0;
    self.vi = vi;

    WINDOW* win = newwin(height, width, y, x);

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
        mvwprintw(self.win, it2, 0, "%ls", it);
        it2++;
    }

    wrefresh(self.win);
}

void ViWin_input(ViWin* self, Vi* nvi) 
{
    int key = wgetch(self.win);
}

Vi*% Vi_initialize(Vi*% self) 
{
    self.init_curses();

    int maxx = xgetmaxx();
    int maxy = xgetmaxy();

    self.wins = borrow new list<ViWin*%>.initialize();

    ViWin* win = borrow new ViWin.initialize(0, 0, maxx-1, maxy, self);

    win.texts.push_back(wstring("aaa"));
    win.texts.push_back(wstring("bbb"));
    win.texts.push_back(wstring("ccc"));

    self.wins.push_back(win);

    self.activeWin = win;

    return self;
}

bool ViWin_equals(ViWin* left, ViWin* right) 
{
    return left == right;
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

    return 0;
}

void Vi_init_curses(Vi* self) 
{
    initscr();
    noecho();
    keypad(stdscr, true);
    raw();
    curs_set(0);
}
