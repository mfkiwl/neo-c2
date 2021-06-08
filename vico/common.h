#include <come.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "config.h"

typedef wchar_t*% wstring;

/// wstring ///
static wstring wstring(char* str)
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

/// main.c ///
bool xiswalpha(wchar_t c);
bool xiswalnum(wchar_t c);
bool xiswdigit(wchar_t c);
bool xiswblank(wchar_t c);

int xgetmaxx();
int xgetmaxy();


// 1init.h
#define SAVE_INPUT_KEY_MAX 256

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
    list<ViWin*%>* wins;
    ViWin* activeWin;
};

extern Vi* gApp;

Vi*% Vi_initialize(Vi*% self);
void Vi_finalize(Vi* self);

void Vi_init_curses(Vi* self);
int Vi_main_loop(Vi* self);

ViWin*% ViWin_initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);
void ViWin_finalize(ViWin* self);

void ViWin_view(ViWin* self, Vi* nvi);
void ViWin_input(ViWin* self, Vi* nvi);

