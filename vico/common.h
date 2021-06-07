#include <come.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "config.h"

typedef wchar_t*% wstring;

#define SAVE_INPUT_KEY_MAX 256

// 1init.h
bool xiswalpha(wchar_t* c);
bool xiswalnum(wchar_t* c);
bool xiswdigit(wchar_t* c);
bool xiswblank(wchar_t* c);

int xgetmaxx();
int xgetmaxy();

struct ViWin 
{
    /// layer 1 ///
    WINDOW* win;
    list<wstring>* texts;
    int y;
    int x;
    int width;
    int height;
    int scroll;
    void* vi;
};

struct Vi 
{
    list<ViWin*%>*% wins;
    ViWin* activeWin;
};

ViWin*% ViWin_initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);
void ViWin_finalize(ViWin* self);

void ViWin_view(ViWin* self, Vi* nvi);
void ViWin_input(ViWin* self, Vi* nvi);

Vi*% Vi_initialize(Vi*% self);
void Vi_finalize(Vi* self);

void Vi_init_curses(Vi* self);
int Vi_main_loop(Vi* self);

extern Vi* gApp;
