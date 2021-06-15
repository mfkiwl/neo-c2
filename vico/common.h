#include <come.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits.h>
#include "config.h"

typedef wchar_t*% wstring;

/// wstring ///
wstring wstring(char* str);
wstring int_substring(wchar_t* str, int head, int tail);
wstring int_printable(wchar_t* str);
int int_length(wchar_t* str);
wchar_t* int_delete(wchar_t* str, int head, int tail);
int int_index(wchar_t* str, wchar_t* search_str, int default_value);

/// main.c ///
bool xiswalpha(wchar_t c);
bool xiswalnum(wchar_t c);
bool xiswdigit(wchar_t c);
bool xiswblank(wchar_t c);

int xgetmaxx();
int xgetmaxy();

string xbasename(char* path);
string xrealpath(char* path);

///////////////////////////////////////////////////////////////////////////////
// 01init.h
///////////////////////////////////////////////////////////////////////////////
#define SAVE_INPUT_KEY_MAX 256

enum eMode { kEditMode, kInsertMode };

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
    int id;

    /// layer 2 ///
    int cursorY;
    int cursorX;
    int scroll;
    int digitInput;

    tuple3<int,int,int>*% returnPoint;
    list<tuple3<int, int, int>*%>*% returnPointStack;

    /// layer 5 ///
    list<list<wstring>*%>%* undo;
    list<int>%* undoScroll;
    list<int>%* undoCursorX;
    list<int>%* undoCursorY;
    int undoIndex;

    /// layer 6 ///
    char fileName[PATH_MAX];
    bool writed;
};

struct Vi 
{
    /// layer 1 ///
    list<ViWin*%>* wins;
    ViWin* activeWin;

    /// layer 2 ///
    vector<void (*lambda)(Vi*, int)>*% events;
    bool appEnd;

    /// layer 3 ///
    int mode;

    /// layer 6 ///
    int toggleWin;
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
void Vi_repositionWindows(Vi* self);

///////////////////////////////////////////////////////////////////////////////
// 03insert_mode.h
///////////////////////////////////////////////////////////////////////////////
override void ViWin_view(ViWin* self, Vi* nvi);
void ViWin_insertText(ViWin* self, wstring key);
void ViWin_enterNewLine(ViWin* self);
void ViWin_enterNewLine2(ViWin* self);
override void ViWin_input(ViWin* self, Vi* nvi);
void ViWin_backSpace(ViWin* self);
void ViWin_backIndent(ViWin* self);
void ViWin_blinkBraceFoward(ViWin* self, wchar_t head, wchar_t tail, Vi* nvi);
void ViWin_blinkBraceEnd(ViWin* self, wchar_t head, wchar_t tail, Vi* nvi);

void ViWin_pushUndo(ViWin* self);
void ViWin_writedFlagOn(ViWin* self);
void ViWin_completion(ViWin* self, Vi* nvi);
void ViWin_clearInputedKey(ViWin* self);
void ViWin_saveInputedKey(ViWin* self);

void ViWin_backwardWord(ViWin* self); // implement after

override Vi*% Vi_initialize(Vi*% self);

void Vi_enterInsertMode(Vi* self);
void Vi_enterInsertMode2(Vi* self);
void Vi_exitFromInsertMode(Vi* self);
override int Vi_main_loop(Vi* self);

///////////////////////////////////////////////////////////////////////////////
/// 4word.h
///////////////////////////////////////////////////////////////////////////////
void ViWin_forwardWord(ViWin* self);
override void ViWin_backwardWord(ViWin* self);

override Vi*% Vi_initialize(Vi*% self);

///////////////////////////////////////////////////////////////////////////////
/// 5word.h
///////////////////////////////////////////////////////////////////////////////
override ViWin*% ViWin_initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);
override void ViWin_finalize(ViWin* self);

override void ViWin_pushUndo(ViWin* self);

void ViWin_undo(ViWin* self);
void ViWin_redo(ViWin* self);

override Vi*% Vi_initialize(Vi*% self);

override void Vi_enterInsertMode(Vi* self);

///////////////////////////////////////////////////////////////////////////////
/// 6file.h
///////////////////////////////////////////////////////////////////////////////
override ViWin*% ViWin_initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);
override void ViWin_statusBarView(ViWin* self, Vi* nvi);
override void ViWin_openFile(ViWin* self, char* file_name, int line_num);
void ViWin_writeFile(ViWin* self);
override void ViWin_writedFlagOn(ViWin* self);
bool ViWin_saveDotToFile(ViWin* self, Vi* nvi);

override Vi*% Vi_initialize(Vi*% self);
void Vi_saveLastOpenFile(Vi* self, char* file_name);
string Vi_readLastOpenFile(Vi* self);
override void Vi_repositionWindows(Vi* self);
override void Vi_openFile(Vi* self, char* file_name, int line_num);
void Vi_openNewFile(Vi* self, char* file_name);
void Vi_closeActiveWin(Vi* self);

override void Vi_exitFromApp(Vi* self);

