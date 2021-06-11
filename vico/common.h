#include <come.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "config.h"

typedef wchar_t*% wstring;

/// wstring ///
wstring wstring(char* str);
wstring int_substring(wchar_t* str, int head, int tail);
wstring int_printable(wchar_t* str);
int int_length(wchar_t* str);

/// main.c ///
bool xiswalpha(wchar_t c);
bool xiswalnum(wchar_t c);
bool xiswdigit(wchar_t c);
bool xiswblank(wchar_t c);

int xgetmaxx();
int xgetmaxy();

///////////////////////////////////////////////////////////////////////////////
// 01init.h
///////////////////////////////////////////////////////////////////////////////
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

    /// layer 2 ///
    int cursorY;
    int cursorX;
    int scroll;
    int digitInput;

    tuple3<int,int,int>*% returnPoint;
    list<tuple3<int, int, int>*%>*% returnPointStack;
};

struct Vi 
{
    /// layer 1 ///
    list<ViWin*%>* wins;
    ViWin* activeWin;

    /// layer 2 ///
    vector<void (*lambda)(Vi*, int)>*% events;
    bool appEnd;
};

extern Vi* gApp;

/// Vi ///
Vi*% Vi_initialize(Vi*% self);
void Vi_finalize(Vi* self);

void Vi_init_curses(Vi* self);
int Vi_main_loop(Vi* self);

/// ViWin ///
ViWin*% ViWin_initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);
void ViWin_finalize(ViWin* self);

void ViWin_view(ViWin* self, Vi* nvi);
void ViWin_input(ViWin* self, Vi* nvi);
bool ViWin_equals(ViWin* left, ViWin* right);

///////////////////////////////////////////////////////////////////////////////
// 02base.h
///////////////////////////////////////////////////////////////////////////////

/// VinWin ///
override ViWin*% ViWin_initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);
override void ViWin_finalize(ViWin* self);

void ViWin_textsView(ViWin* self, Vi* nvi);
void ViWin_statusBarView(ViWin* self, Vi* nvi);
override void ViWin_view(ViWin* self, Vi* nvi);
override void ViWin_input(ViWin* self, Vi* nvi);
int ViWin_getKey(ViWin* self, bool head);
void ViWin_modifyOverCursorYValue(ViWin* self);
void ViWin_modifyUnderCursorYValue(ViWin* self);
void ViWin_modifyOverCursorXValue(ViWin* self);
void ViWin_modifyOverCursorXValue2(ViWin* self);
void ViWin_modifyUnderCursorXValue(ViWin* self);

void ViWin_forward(ViWin* self);
void ViWin_backward(ViWin* self);
void ViWin_prevLine(ViWin* self);
void ViWin_nextLine(ViWin* self);
void ViWin_halfScrollUp(ViWin* self);
void ViWin_halfScrollDown(ViWin* self);
void ViWin_moveAtHead(ViWin* self);
void ViWin_moveAtTail(ViWin* self);

void ViWin_moveTop(ViWin* self);
void ViWin_keyG(ViWin* self,Vi* nvi);
void ViWin_moveBottom(ViWin* self);

void ViWin_repositionWindows(Vi* self);
void ViWin_repositionFiler(Vi* self);
void ViWin_centeringCursor(ViWin* self);

void ViWin_saveReturnPoint(ViWin* self);

void ViWin_restoreVisualMode(ViWin* self, Vi* nvi);

void ViWin_joinLines2(ViWin* self);

void ViWin_openFile(ViWin* self, char* file_name, int line_num);
void ViWin_saveInputedKeyOnTheMovingCursor(ViWin* self);

// vi ///
override Vi*% Vi_initialize(Vi*% self);
override void Vi_finalize(Vi* self);

override int Vi_main_loop(Vi* self);

void Vi_openFile(Vi* self, char* file_name, int line_num);
void Vi_view(Vi* self);
void Vi_clearView(Vi* self);
void Vi_exitFromApp(Vi* self);
void Vi_enterSearchMode(Vi* self, bool regex_search, bool search_reverse);

