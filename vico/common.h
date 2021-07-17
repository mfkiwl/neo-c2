#include <come.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits.h>
#include <wchar.h>
#include <pcre.h>
#include "config.h"

typedef wchar_t*% wstring;

struct regex_struct {
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

regex_struct*% regex(char* str, bool ignore_case, bool multiline, bool global, bool extended, bool dotall, bool anchored, bool dollar_endonly, bool ungreedy);

/// wstring ///
wstring wstring(char* str);
wstring int::substring(wchar_t* str, int head, int tail);
wstring int::printable(wchar_t* str);
int int::length(wchar_t* str);
wchar_t* int::delete(wchar_t* str, int head, int tail);
int int::index(wchar_t* str, wchar_t* search_str, int default_value);
int int::rindex(wchar_t* str, wchar_t* search_str, int default_value);
string int::to_string(wchar_t* wstr);
wstring char::to_wstring(char* str);
wstring int::reverse(whar_t* str);
bool char::match(char* self, regex_struct* reg, list<string>?* group_strings);
int char::index(char* str, char* search_str, int default_value);
int char::rindex(char* str, char* search_str, int default_value);
string char::sub(char* self, regex_struct* reg, char* replace, list<string>?* group_strings);
list<string>*% char::scan(char* self, regex_struct* reg);
string char::multiply(char* str, int n);
wstring int::multiply(wchar_t* str, int n);
int char::index_regex(char* self, regex_struct* reg, int default_value);

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

    /// layer 8 ///
    int visualModeHead;
    int visualModeHeadX;
    
    int visualModeHeadHorizonScroll;
    int visualModeHeadHorizonX;
    int visualModeHeadHorizonY;

    int visualModeHeadBefore;
    int visualModeTailCursorYBefore;
    int visualModeTailScrollBefore;

    /// layer 10 ///
    int mRepeatFowardNextCharacterKind;
    wchar_t mRepeatFowardNextCharacter;

    /// layer 12 ///
    char commandString[128];

    /// layer 14 ///
    vector<int>*% inputedKeys;
    vector<int>*% savedInputedKeys;
    bool autoInput;
    int digitInput;
    int autoInputIndex;
    bool pressedDot;

    map<int, vector<vector<int>*%>*%>*% macro;
    int recordingMacroKey;
    vector<vector<int>*%>*% recordingMacro;
    vector<vector<int>*%>*% runningMacro;
    int runningMacroIndex1;
    int runningMacroIndex2;

    /// layer 16 ///
    map<wchar_t, tuple3<int,int, int>*%>*% mark;

    /// layer 17 ///
    int visualModeHorizonHeadScroll;
    int visualModeHorizonHeadX;
    int visualModeHorizonHeadY;

    /// layer 18 ///
    int visualModeVerticalHeadX;
    int visualModeVerticalHeadY;
    int visualModeVerticalLen;
    
    int visualModeVerticalStartY;
    int visualModeVerticalStartScroll;
    int visualModeVerticalStartX;
    bool visualModeVerticalInserting;
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

    /// layer 7 ///
    list<wstring>*% yank;
    int yankKind;

    /// layer 9 ///
    wchar_t searchString[128];
    bool searchReverse;
    bool regexSearch;
};

extern Vi* gApp;

/// Vi ///
Vi*% Vi::initialize(Vi*% self);
void Vi::finalize(Vi* self);

void Vi::init_curses(Vi* self);
int Vi::main_loop(Vi* self);

/// ViWin ///
ViWin*% ViWin::initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);
void ViWin::finalize(ViWin* self);

void ViWin::view(ViWin* self, Vi* nvi);
void ViWin::input(ViWin* self, Vi* nvi);
bool ViWin::equals(ViWin* left, ViWin* right);

///////////////////////////////////////////////////////////////////////////////
// 02base.h
///////////////////////////////////////////////////////////////////////////////

/// VinWin ///
override ViWin*% ViWin::initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);
override void ViWin::finalize(ViWin* self);

void ViWin::textsView(ViWin* self, Vi* nvi);
void ViWin::statusBarView(ViWin* self, Vi* nvi);
override void ViWin::view(ViWin* self, Vi* nvi);
override void ViWin::input(ViWin* self, Vi* nvi);
int ViWin::getKey(ViWin* self, bool head);
void ViWin::modifyOverCursorYValue(ViWin* self);
void ViWin::modifyUnderCursorYValue(ViWin* self);
void ViWin::modifyOverCursorXValue(ViWin* self);
void ViWin::modifyOverCursorXValue2(ViWin* self);
void ViWin::modifyUnderCursorXValue(ViWin* self);

void ViWin::forward(ViWin* self);
void ViWin::backward(ViWin* self);
void ViWin::prevLine(ViWin* self);
void ViWin::nextLine(ViWin* self);
void ViWin::halfScrollUp(ViWin* self);
void ViWin::halfScrollDown(ViWin* self);
void ViWin::moveAtHead(ViWin* self);
void ViWin::moveAtTail(ViWin* self);

void ViWin::moveTop(ViWin* self);
void ViWin::keyG(ViWin* self,Vi* nvi);
void ViWin::moveBottom(ViWin* self);

void ViWin::repositionWindows(Vi* self);
void ViWin::centeringCursor(ViWin* self);

void ViWin::saveReturnPoint(ViWin* self);

void ViWin::restoreVisualMode(ViWin* self, Vi* nvi);

void ViWin::joinLines2(ViWin* self);

void ViWin::openFile(ViWin* self, char* file_name, int line_num);
void ViWin::saveInputedKeyOnTheMovingCursor(ViWin* self);

// vi ///
override Vi*% Vi::initialize(Vi*% self);
override void Vi::finalize(Vi* self);

override int Vi::main_loop(Vi* self);

void Vi::openFile(Vi* self, char* file_name, int line_num);
void Vi::view(Vi* self);
void Vi::clearView(Vi* self);
void Vi::exitFromApp(Vi* self);
void Vi::enterSearchMode(Vi* self, bool regex_search, bool search_reverse);
void Vi::repositionWindows(Vi* self);

///////////////////////////////////////////////////////////////////////////////
// 03insert_mode.h
///////////////////////////////////////////////////////////////////////////////
override void ViWin::view(ViWin* self, Vi* nvi);
void ViWin::insertText(ViWin* self, wstring key);
void ViWin::enterNewLine(ViWin* self);
void ViWin::enterNewLine2(ViWin* self);
override void ViWin::input(ViWin* self, Vi* nvi);
void ViWin::backSpace(ViWin* self);
void ViWin::backIndent(ViWin* self);
void ViWin::blinkBraceFoward(ViWin* self, wchar_t head, wchar_t tail, Vi* nvi);
void ViWin::blinkBraceEnd(ViWin* self, wchar_t head, wchar_t tail, Vi* nvi);

void ViWin::pushUndo(ViWin* self);
void ViWin::writedFlagOn(ViWin* self);
void ViWin::completion(ViWin* self, Vi* nvi);
void ViWin::clearInputedKey(ViWin* self);
void ViWin::saveInputedKey(ViWin* self);

void ViWin::backwardWord(ViWin* self); // implement after

override Vi*% Vi::initialize(Vi*% self);

void Vi::enterInsertMode(Vi* self);
void Vi::enterInsertMode2(Vi* self);
void Vi::exitFromInsertMode(Vi* self);
override int Vi::main_loop(Vi* self);

///////////////////////////////////////////////////////////////////////////////
/// 4word.h
///////////////////////////////////////////////////////////////////////////////
void ViWin::forwardWord(ViWin* self);
override void ViWin::backwardWord(ViWin* self);

override Vi*% Vi::initialize(Vi*% self);

///////////////////////////////////////////////////////////////////////////////
/// 5word.h
///////////////////////////////////////////////////////////////////////////////
override ViWin*% ViWin::initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);
override void ViWin::finalize(ViWin* self);

override void ViWin::pushUndo(ViWin* self);

void ViWin::undo(ViWin* self);
void ViWin::redo(ViWin* self);

override Vi*% Vi::initialize(Vi*% self);

override void Vi::enterInsertMode(Vi* self);

///////////////////////////////////////////////////////////////////////////////
/// 6file.h
///////////////////////////////////////////////////////////////////////////////
override ViWin*% ViWin::initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);

override void ViWin::statusBarView(ViWin* self, Vi* nvi);
override void ViWin::openFile(ViWin* self, char* file_name, int line_num);
void ViWin::writeFile(ViWin* self);
override void ViWin::writedFlagOn(ViWin* self);
bool ViWin::saveDotToFile(ViWin* self, Vi* nvi);

override Vi*% Vi::initialize(Vi*% self);

void Vi::saveLastOpenFile(Vi* self, char* file_name);
string Vi::readLastOpenFile(Vi* self);
override void Vi::repositionWindows(Vi* self);
override void Vi::openFile(Vi* self, char* file_name, int line_num);
void Vi::openNewFile(Vi* self, char* file_name);
void Vi::closeActiveWin(Vi* self);

override void Vi::exitFromApp(Vi* self);

///////////////////////////////////////////////////////////////////////////////
/// 7yank.h
///////////////////////////////////////////////////////////////////////////////
void ViWin::deleteOneLine(ViWin* self, Vi* nvi);
bool ViWin::saveYankToFile(ViWin* self, Vi* nvi);
bool ViWin::loadYankFromFile(ViWin* self, Vi* nvi);

enum { kYankKindLine, kYankKindNoLine };

override Vi*% Vi::initialize(Vi*% self);
override void Vi::finalize(Vi* self);

///////////////////////////////////////////////////////////////////////////////
/// 8visual.h
///////////////////////////////////////////////////////////////////////////////
enum { kYankKindLine, kYankKindNoLine };
enum eMode { kVisualMode = kInsertMode + 1 };

override ViWin*% ViWin::initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);

void ViWin::visualModeView(ViWin* self, Vi* nvi);
override void ViWin::view(ViWin* self, Vi* nvi);
void ViWin::inputVisualMode(ViWin* self, Vi* nvi);
override void ViWin::input(ViWin* self, Vi* nvi);
override void ViWin::restoreVisualMode(ViWin* self, Vi* nvi);
void ViWin::makeInputedKeyGVIndent(ViWin* self, Vi* nvi);
void ViWin::makeInputedKeyGVDeIndent(ViWin* self, Vi* nvi);
void ViWin::gotoBraceEnd(ViWin* self, Vi* nvi);

override Vi*% Vi::initialize(Vi*% self);
void Vi::enterVisualMode(Vi* self);
void Vi::reenterVisualMode(Vi* self);
void Vi::exitFromVisualMode(Vi* self);

///////////////////////////////////////////////////////////////////////////////
/// 9visual.h
///////////////////////////////////////////////////////////////////////////////
enum eMode { kSearchMode = kVisualMode + 1 };

void ViWin::saveSearchString(Vi* self, char* file_name);
void ViWin::readSearchString(Vi* self, char* file_name);

void ViWin::searchModeView(ViWin* self, Vi* nvi);
override void ViWin::view(ViWin* self, Vi* nvi);

void ViWin::inputSearchlMode(ViWin* self, Vi* nvi);
override void ViWin::input(ViWin* self, Vi* nvi);

override Vi*% Vi::initialize(Vi*% self);
override void Vi::finalize(Vi* self);

override void Vi::enterSearchMode(Vi* self, bool regex_search, bool search_reverse);
void Vi::exitFromSearchMode(Vi* self);

enum eRepeatForwardNextCharacter {
    kRFNCNone, kRFNC1, kRFNC2
};

///////////////////////////////////////////////////////////////////////////////
/// 10edit.h
///////////////////////////////////////////////////////////////////////////////
override ViWin*% ViWin::initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);
override void ViWin::deleteOneLine(ViWin* self, Vi* nvi);
override void ViWin::joinLines2(ViWin* self);
void ViWin::deleteUntilTail(ViWin* self);

override Vi*% Vi::initialize(Vi*% self);

///////////////////////////////////////////////////////////////////////////////
/// 11move.h
///////////////////////////////////////////////////////////////////////////////
override void ViWin::gotoBraceEnd(ViWin* self, Vi* nvi);

override Vi*% Vi::initialize(Vi*% self);

///////////////////////////////////////////////////////////////////////////////
/// 12command.h
///////////////////////////////////////////////////////////////////////////////
enum eMode { kCommandMode = kSearchMode + 1 };

override void ViWin::view(ViWin* self, Vi* nvi);
override void ViWin::input(ViWin* self, Vi* nvi);

void Vi::enterComandMode(Vi* nvi);
void Vi::exitFromComandMode(Vi* self);
override Vi*% Vi::initialize(Vi*% self);

///////////////////////////////////////////////////////////////////////////////
/// 13completion.h
///////////////////////////////////////////////////////////////////////////////
override void ViWin::completion(ViWin* self, Vi* nvi);

///////////////////////////////////////////////////////////////////////////////
/// 14dot.h
///////////////////////////////////////////////////////////////////////////////
override ViWin*% ViWin::initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);
override void ViWin::finalize(ViWin* self);

override bool ViWin::saveDotToFile(ViWin* self, Vi* nvi);
bool ViWin::loadDotFromFile(ViWin* self, Vi* nvi);

override int ViWin::getKey(ViWin* self, bool head);
override void ViWin::clearInputedKey(ViWin* self);
override void ViWin::saveInputedKey(ViWin* self);
override void ViWin::makeInputedKeyGVIndent(ViWin* self, Vi* nvi);
override void ViWin::makeInputedKeyGVDeIndent(ViWin* self, Vi* nvi);
override void ViWin::saveInputedKeyOnTheMovingCursor(ViWin* self);

override Vi*% Vi::initialize(Vi*% self);

///////////////////////////////////////////////////////////////////////////////
/// 16mark.h
///////////////////////////////////////////////////////////////////////////////
override ViWin*% ViWin::initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);
override void ViWin::finalize(ViWin* self);

override Vi*% Vi::initialize(Vi*% self);

///////////////////////////////////////////////////////////////////////////////
/// 17hvisual.h
///////////////////////////////////////////////////////////////////////////////
enum eMode { kHorizonVisualMode = kCommandMode + 1 };

override ViWin*% ViWin::initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);
override void ViWin::view(ViWin* self, Vi* nvi);
override void ViWin::input(ViWin* self, Vi* nvi);

override Vi*% Vi::initialize(Vi*% self);

///////////////////////////////////////////////////////////////////////////////
/// 18vvisual.h
///////////////////////////////////////////////////////////////////////////////
enum eMode { kVerticalVisualMode = kHorizonVisualMode +1 };

override ViWin*% ViWin::initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi);

override void ViWin::view(ViWin* self, Vi* nvi);
override void ViWin::input(ViWin* self, Vi* nvi);

override Vi*% Vi::initialize(Vi*% self);

enum eMode { kRewriteMode = kVerticalVisualMode + 1 };

///////////////////////////////////////////////////////////////////////////////
/// 19rewrite_mode.h
///////////////////////////////////////////////////////////////////////////////
override void ViWin::view(ViWin* self, Vi* nvi);
override void ViWin::input(ViWin* self, Vi* nvi);

override Vi*% Vi::initialize(Vi*% self);
override int Vi::main_loop(Vi* self);
