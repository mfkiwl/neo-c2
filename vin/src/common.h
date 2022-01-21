#include "../config.h"
#include <neo-c2.h>

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>


/// main.c ///
int xgetmaxx();
int xgetmaxy();

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

    tuple3<int,int,int>* returnPoint;
    list<tuple3<int, int, int>*>* returnPointStack;

    /// layer 5 ///
    list<list<wstring>*>* undoText;
    list<int>* undoScroll;
    list<int>* undoCursorX;
    list<int>* undoCursorY;
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
    vector<int>* inputedKeys;
    vector<int>* savedInputedKeys;
    bool autoInput;
    int digitInput;
    int autoInputIndex;
    bool pressedDot;

    map<int, vector<vector<int>*>*>* macro;
    int recordingMacroKey;
    vector<vector<int>*>* recordingMacro;
    vector<vector<int>*>* runningMacro;
    int runningMacroIndex1;
    int runningMacroIndex2;

    /// layer 16 ///
    map<wchar_t, tuple3<int,int, int>*>* mark;

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

struct Vi;

struct Vi 
{
    /// layer 1 ///
    list<ViWin*>* wins;
    ViWin* activeWin;

    /// layer 2 ///
    vector<void (*lambda)(Vi*, int)>* events;
    bool appEnd;

    /// layer 3 ///
    int mode;

    /// layer 6 ///
    int toggleWin;

    /// layer 7 ///
    list<wstring>* yank;
    list<wstring>* fileYank;
    int yankKind;

    /// layer 9 ///
    wchar_t searchString[128];
    bool searchReverse;
    bool regexSearch;
};

extern Vi* gVi;

/// Vi ///
Vi* Vi::initialize(Vi* self) version 1;

void Vi::init_curses(Vi* self);
int Vi::main_loop(Vi* self) version 1;

/// ViWin ///
ViWin* ViWin::initialize(ViWin* self, int y, int x, int width, int height, Vi* vi) version 1;

void ViWin::view(ViWin* self, Vi* nvi) version 1;
void ViWin::input(ViWin* self, Vi* nvi) version 1;
bool ViWin::equals(ViWin* left, ViWin* right);

///////////////////////////////////////////////////////////////////////////////
// 02base.h
///////////////////////////////////////////////////////////////////////////////

/// VinWin ///
ViWin* ViWin::initialize(ViWin* self, int y, int x, int width, int height, Vi* vi) version 2;

void ViWin::textsView(ViWin* self, Vi* nvi);
void ViWin::statusBarView(ViWin* self, Vi* nvi) version 2;
void ViWin::view(ViWin* self, Vi* nvi) version 2;
void ViWin::input(ViWin* self, Vi* nvi) version 2;
int ViWin::getKey(ViWin* self, bool head) version 2;
void ViWin::modifyOverCursorYValue(ViWin* self);
void ViWin::modifyUnderCursorYValue(ViWin* self);
void ViWin::modifyOverCursorXValue(ViWin* self);
void ViWin::modifyOverCursorXValue2(ViWin* self);
void ViWin::modifyUnderCursorXValue(ViWin* self);

void ViWin::forward(ViWin* self) version 2;
void ViWin::backward(ViWin* self) version 2;
void ViWin::prevLine(ViWin* self);
void ViWin::nextLine(ViWin* self);
void ViWin::halfScrollUp(ViWin* self);
void ViWin::halfScrollDown(ViWin* self);
void ViWin::moveAtHead(ViWin* self);
void ViWin::moveAtTail(ViWin* self);

void ViWin::moveTop(ViWin* self);
void ViWin::keyG(ViWin* self,Vi* nvi);
void ViWin::moveBottom(ViWin* self);

void ViWin::centeringCursor(ViWin* self);

void ViWin::saveReturnPoint(ViWin* self);

void ViWin::restoreVisualMode(ViWin* self, Vi* nvi) version 2;

void ViWin::joinLines2(ViWin* self) version 2;

void ViWin::openFile(ViWin* self, char* file_name, int line_num) version 2;
void ViWin::saveInputedKeyOnTheMovingCursor(ViWin* self) version 2;

// vi ///
Vi* Vi::initialize(Vi* self) version 2;

int Vi::main_loop(Vi* self) version 2;

void Vi::openFile(Vi* self, char* file_name, int line_num) version 2;
void Vi::view(Vi* self);
void Vi::clearView(Vi* self);
void Vi::exitFromApp(Vi* self) version 2;
void Vi::enterSearchMode(Vi* self, bool regex_search, bool search_reverse) version 2;
void Vi::repositionWindows(Vi* self) version 2;

///////////////////////////////////////////////////////////////////////////////
// 03insert_mode.h
///////////////////////////////////////////////////////////////////////////////
void ViWin::view(ViWin* self, Vi* nvi) version 3;
void ViWin::insertText(ViWin* self, wstring key);
void ViWin::enterNewLine(ViWin* self);
void ViWin::enterNewLine2(ViWin* self);
void ViWin::input(ViWin* self, Vi* nvi) version 3;
void ViWin::backSpace(ViWin* self);
void ViWin::backIndent(ViWin* self);
void ViWin::blinkBraceFoward(ViWin* self, wchar_t head, wchar_t tail, Vi* nvi);
void ViWin::blinkBraceEnd(ViWin* self, wchar_t head, wchar_t tail, Vi* nvi);

void ViWin::pushUndo(ViWin* self) version 3;
void ViWin::writedFlagOn(ViWin* self) version 3;
void ViWin::completion(ViWin* self, Vi* nvi) version 3;
void ViWin::completion_neo_c2(ViWin* self, Vi* nvi) version 3;
void ViWin::clearInputedKey(ViWin* self) version 3;
void ViWin::saveInputedKey(ViWin* self) version 3;

void ViWin::backwardWord(ViWin* self) version 3; // implement after

Vi* Vi::initialize(Vi* self) version 3;

void Vi::enterInsertMode(Vi* self) version 3;
void Vi::enterInsertMode2(Vi* self) version 3;
void Vi::exitFromInsertMode(Vi* self) version 3;
int Vi::main_loop(Vi* self) version 3;

///////////////////////////////////////////////////////////////////////////////
/// 4word.h
///////////////////////////////////////////////////////////////////////////////
void ViWin::forwardWord(ViWin* self);
void ViWin::backwardWord(ViWin* self) version 4;

Vi* Vi::initialize(Vi* self) version 4;

///////////////////////////////////////////////////////////////////////////////
/// 5word.h
///////////////////////////////////////////////////////////////////////////////
ViWin* ViWin::initialize(ViWin* self, int y, int x, int width, int height, Vi* vi) version 5;

void ViWin::pushUndo(ViWin* self) version 5;

void ViWin::undo(ViWin* self);
void ViWin::redo(ViWin* self);

Vi* Vi::initialize(Vi* self) version 5;

void Vi::enterInsertMode(Vi* self) version 5;

///////////////////////////////////////////////////////////////////////////////
/// 6file.h
///////////////////////////////////////////////////////////////////////////////
ViWin* ViWin::initialize(ViWin* self, int y, int x, int width, int height, Vi* vi) version 6;

void ViWin::statusBarView(ViWin* self, Vi* nvi) version 6;
void ViWin::openFile(ViWin* self, char* file_name, int line_num) version 6;
void ViWin::writeFile(ViWin* self);
void ViWin::writedFlagOn(ViWin* self) version 6;
bool ViWin::saveDotToFile(ViWin* self, Vi* nvi) version 6;

Vi* Vi::initialize(Vi* self) version 6;

void Vi::saveLastOpenFile(Vi* self, char* file_name);
string Vi::readLastOpenFile(Vi* self);
void Vi::repositionWindows(Vi* self) version 6;
void Vi::openFile(Vi* self, char* file_name, int line_num) version 6;
void Vi::openNewFile(Vi* self, char* file_name);
void Vi::closeActiveWin(Vi* self);

void Vi::exitFromApp(Vi* self) version 6;

///////////////////////////////////////////////////////////////////////////////
/// 7yank.h
///////////////////////////////////////////////////////////////////////////////
bool ViWin::saveYankToFile(ViWin* self, Vi* nvi);
bool ViWin::loadYankFromFile(ViWin* self, Vi* nvi);
bool ViWin::loadFileYankFromFile(ViWin* self, Vi* nvi);
bool ViWin::saveFileYankToFile(ViWin* self, Vi* nvi);

enum { kYankKindLine, kYankKindNoLine };

Vi* Vi::initialize(Vi* self) version 7;

///////////////////////////////////////////////////////////////////////////////
/// 8visual.h
///////////////////////////////////////////////////////////////////////////////
enum { kYankKindLine, kYankKindNoLine };
enum eMode { kVisualMode = kInsertMode + 1 };

ViWin* ViWin::initialize(ViWin* self, int y, int x, int width, int height, Vi* vi) version 8;

void ViWin::visualModeView(ViWin* self, Vi* nvi);
void ViWin::view(ViWin* self, Vi* nvi) version 8;
void ViWin::inputVisualMode(ViWin* self, Vi* nvi);
void ViWin::input(ViWin* self, Vi* nvi) version 8;
void ViWin::restoreVisualMode(ViWin* self, Vi* nvi) version 8;
void ViWin::makeInputedKeyGVIndent(ViWin* self, Vi* nvi) version 8;
void ViWin::makeInputedKeyGVDeIndent(ViWin* self, Vi* nvi) version 8;
void ViWin::gotoBraceEnd(ViWin* self, Vi* nvi) version 8;

Vi* Vi::initialize(Vi* self) version 8;
void Vi::enterVisualMode(Vi* self);
void Vi::reenterVisualMode(Vi* self);
void Vi::exitFromVisualMode(Vi* self);

///////////////////////////////////////////////////////////////////////////////
/// 9visual.h
///////////////////////////////////////////////////////////////////////////////
enum eMode { kSearchMode = kVisualMode + 1 };

void Vi::saveSearchString(Vi* self, char* file_name);
void ViWin::readSearchString(Vi* self, char* file_name);

void ViWin::searchModeView(ViWin* self, Vi* nvi);
void ViWin::view(ViWin* self, Vi* nvi) version 9;

void ViWin::inputSearchlMode(ViWin* self, Vi* nvi);
void ViWin::input(ViWin* self, Vi* nvi) version 9;

Vi* Vi::initialize(Vi* self) version 9;

void Vi::enterSearchMode(Vi* self, bool regex_search, bool search_reverse) version 9;
void Vi::exitFromSearchMode(Vi* self);

enum eRepeatForwardNextCharacter {
    kRFNCNone, kRFNC1, kRFNC2
};

///////////////////////////////////////////////////////////////////////////////
/// 10edit.h
///////////////////////////////////////////////////////////////////////////////
ViWin* ViWin::initialize(ViWin* self, int y, int x, int width, int height, Vi* vi) version 10;
void ViWin::deleteOneLine(ViWin* self, Vi* nvi) version 10;
void ViWin::joinLines2(ViWin* self) version 10;
void ViWin::deleteUntilTail(ViWin* self);

Vi* Vi::initialize(Vi* self) version 10;

///////////////////////////////////////////////////////////////////////////////
/// 11move.h
///////////////////////////////////////////////////////////////////////////////
void ViWin::gotoBraceEnd(ViWin* self, Vi* nvi) version 11;

Vi* Vi::initialize(Vi* self) version 11;

///////////////////////////////////////////////////////////////////////////////
/// 12command.h
///////////////////////////////////////////////////////////////////////////////
enum eMode { kCommandMode = kSearchMode + 1 };

void ViWin::view(ViWin* self, Vi* nvi) version 12;
void ViWin::input(ViWin* self, Vi* nvi) version 12;

void Vi::enterComandMode(Vi* nvi);
void Vi::exitFromComandMode(Vi* self);
Vi* Vi::initialize(Vi* self) version 12;

///////////////////////////////////////////////////////////////////////////////
/// 13completion.h
///////////////////////////////////////////////////////////////////////////////
void ViWin::completion(ViWin* self, Vi* nvi) version 13;
wstring? ViWin::selector2(ViWin* self, list<wstring>* lines);

///////////////////////////////////////////////////////////////////////////////
/// 14dot.h
///////////////////////////////////////////////////////////////////////////////
ViWin* ViWin::initialize(ViWin* self, int y, int x, int width, int height, Vi* vi) version 14;

bool ViWin::saveDotToFile(ViWin* self, Vi* nvi) version 14;
bool ViWin::loadDotFromFile(ViWin* self, Vi* nvi);

int ViWin::getKey(ViWin* self, bool head) version 14;
void ViWin::clearInputedKey(ViWin* self) version 14;
void ViWin::saveInputedKey(ViWin* self) version 14;
void ViWin::makeInputedKeyGVIndent(ViWin* self, Vi* nvi) version 14;
void ViWin::makeInputedKeyGVDeIndent(ViWin* self, Vi* nvi) version 14;
void ViWin::saveInputedKeyOnTheMovingCursor(ViWin* self) version 14;

Vi* Vi::initialize(Vi* self) version 14;

///////////////////////////////////////////////////////////////////////////////
/// 16mark.h
///////////////////////////////////////////////////////////////////////////////
ViWin* ViWin::initialize(ViWin* self, int y, int x, int width, int height, Vi* vi) version 16;

Vi* Vi::initialize(Vi* self) version 16;

///////////////////////////////////////////////////////////////////////////////
/// 17hvisual.h
///////////////////////////////////////////////////////////////////////////////
enum eMode { kHorizonVisualMode = kCommandMode + 1 };

ViWin* ViWin::initialize(ViWin* self, int y, int x, int width, int height, Vi* vi) version 17;
void ViWin::view(ViWin* self, Vi* nvi) version 17;
void ViWin::input(ViWin* self, Vi* nvi) version 17;

Vi* Vi::initialize(Vi* self) version 17;

///////////////////////////////////////////////////////////////////////////////
/// 18vvisual.h
///////////////////////////////////////////////////////////////////////////////
enum eMode { kVerticalVisualMode = kHorizonVisualMode +1 };

ViWin* ViWin::initialize(ViWin* self, int y, int x, int width, int height, Vi* vi) version 18;

void ViWin::view(ViWin* self, Vi* nvi) version 18;
void ViWin::input(ViWin* self, Vi* nvi) version 18;

Vi* Vi::initialize(Vi* self) version 18;

enum eMode { kRewriteMode = kVerticalVisualMode + 1 };

///////////////////////////////////////////////////////////////////////////////
/// 19rewrite_mode.h
///////////////////////////////////////////////////////////////////////////////
void ViWin::view(ViWin* self, Vi* nvi) version 19;
void ViWin::input(ViWin* self, Vi* nvi) version 19;

Vi* Vi::initialize(Vi* self) version 19;
int Vi::main_loop(Vi* self) version 19;


///////////////////////////////////////////////////////////////////////////////
/// 20completion_neo_c2.h
///////////////////////////////////////////////////////////////////////////////
void ViWin::completion_neo_c2(ViWin* self, Vi* nvi) version 20;
