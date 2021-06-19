#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits.h>

ViWin*% ViWin_initialize(ViWin*% self, int y, int x, int width, int height, Vi* vi)  version 5
{
    var result = inherit(self, y, x, width, height, vi);

    result.visualModeHead = 0;

    result.visualModeHeadBefore = -1;
    result.visualModeTailCursorYBefore = -1;
    result.visualModeTailScrollBefore = -1;

    return result;
}

void ViWin_visualModeView(ViWin* self, Vi* nvi)
{
    int maxy = getmaxy(self.win);
    int maxx = getmaxx(self.win);

    werase(self.win);

    int it2 = 0;
    foreach(it, self.texts.sublist(self.scroll, self.scroll+maxy-1))
    {
        var line = it.substring(0, maxx-1);

        if(it2 >= (self.visualModeHead-self.scroll) 
            && it2 <= self.cursorY) 
        {
            wattron(self.win, A_REVERSE);
            mvwprintw(self.win, it2, 0, "%ls", line);
            wattroff(self.win, A_REVERSE);
        }
        else if(it2 <= 
            (self.visualModeHead-self.scroll) 
            && it2 >= self.cursorY) 
        {
            wattron(self.win, A_REVERSE);
            mvwprintw(self.win, it2, 0, "%ls", line);
            wattroff(self.win, A_REVERSE);
        }
        else {
            mvwprintw(self.win, it2, 0, "%ls", line);
        }

        it2++;
    }

    wattron(self.win, A_REVERSE);
    mvwprintw(self.win, self.height-1, 0, "VISUAL MODE x %d y %d", self.cursorX, self.cursorY);
    wattroff(self.win, A_REVERSE);

    wrefresh(self.win);
}

void ViWin_view(ViWin* self, Vi* nvi) version 4
{
    if(nvi.mode == kVisualMode && nvi.activeWin.equals(self)) {
        self.visualModeView(nvi);
    }
    else {
        inherit(self, nvi);
    }
}

void ViWin_yankOnVisualMode(ViWin* self, Vi* nvi) 
{
    int head = self.visualModeHead;
    int tail = self.scroll+self.cursorY;

    if(head >= tail) {
        int tmp = tail;
        tail = head;
        head = tmp;
    }

    nvi.yank.reset();
    foreach(it, self.texts.sublist(head, tail+1)) {
        nvi.yank.push_back(clone it);
    }
    
    nvi.yankKind = kYankKindLine;
    self.saveYankToFile(nvi);
}

void ViWin_indentVisualMode(ViWin* self, Vi* nvi) 
{
    self.pushUndo();

    int head = self.visualModeHead;
    int tail = self.scroll+self.cursorY;

    if(head >= tail) {
        int tmp = tail;
        tail = head;
        head = tmp;
    }
    
    int it2 = 0;
    foreach(it, self.texts.sublist(head, tail+1)) {
        var new_line = borrow xsprintf("%ls%ls"
                    , wstring("    ")
                    , it).to_wstring();

        self.texts.replace(it2+head, new_line);
        it2++;
    }

    self.modifyOverCursorXValue();
}

void ViWin_backIndentVisualMode(ViWin* self, Vi* nvi) 
{
    self.pushUndo();

    int head = self.visualModeHead;
    int tail = self.scroll+self.cursorY;

    if(head >= tail) {
        int tmp = tail;
        tail = head;
        head = tmp;
    }

    int it2 = 0;
    foreach(it, self.texts.sublist(head, tail+1)) {
        var new_line = borrow clone it;

        if(new_line.index(wstring("    "), -1) == 0) {
            for(int i=0; i<4; i++) {
                new_line.delete(0, 1);
            }

            self.texts.replace(it2+head, new_line);
        }

        it2++;
    }

    self.modifyOverCursorXValue();
}

void ViWin_changeCaseVisualMode(ViWin* self, Vi* nvi) 
{
    self.pushUndo();

    int head = self.visualModeHead;
    int tail = self.scroll+self.cursorY;

    if(head >= tail) {
        int tmp = tail;
        tail = head;
        head = tmp;
    }

    int it2 = 0;
    foreach(it, self.texts.sublist(head, tail+1)) {
        var new_line = borrow clone it;
        
        for(int i=0; i<new_line.length(); i++) {
            wchar_t c = new_line[i];
            
            if(c >= 'a' && c <= 'z') {
                wchar_t c2 = c - 'a' + 'A';
                new_line[i] = c2;
            }
            else if(c >= 'A' && c <= 'Z') {
                wchar_t c2 = c - 'A' + 'a';
                new_line[i] = c2;
            }
        }
        
        self.texts.replace(it2+head, new_line);

        it2++;
    }

    self.modifyOverCursorXValue();
}

void ViWin_joinVisualMode(ViWin* self, Vi* nvi) 
{
    self.pushUndo();

    int head = self.visualModeHead;
    int tail = self.scroll+self.cursorY;

    if(head >= tail) {
        int tmp = tail;
        tail = head;
        head = tmp;
    }

    int len = 0;
    foreach(it, self.texts.sublist(head, tail+1)) {
        len += wcslen(it);
        len++;
    }

    len++;

    var new_line = borrow new wchar_t[len];

    new_line[0] = 0;

    int it2 = 0;
    foreach(it, self.texts.sublist(head, tail+1)) {
        wcscat(new_line, it);

        if(it2 < tail+1-head-1) {
            wcscat(new_line, wstring(" "));
        }

        it2++;
    }

    self.texts.delete(head, tail+1);
    
    self.texts.insert(head, new_line);

    if(self.scroll+self.cursorY >= self.visualModeHead) {
        self.cursorY -= tail - head;

        self.modifyUnderCursorYValue();
    }
    
    self.modifyOverCursorYValue();
    self.modifyOverCursorXValue();

}

void ViWin_equalVisualMode(ViWin* self, Vi* nvi) 
{
    self.pushUndo();

    int head = self.visualModeHead;
    int tail = self.scroll+self.cursorY;

    if(head >= tail) {
        int tmp = tail;
        tail = head;
        head = tmp;
    }
    
    int indent = 0;
    
    foreach(it, self.texts.sublist(0, head)) {
        for(int i = 0; i<it.length(); i++) {
            wchar_t c = it[i];
            
            if(c == '{') {
                indent++;
            }
            else if(c == '}') {
                indent--;
            }
        }
    }
    
    int it2 = 0;
    foreach(it, self.texts.sublist(head, tail+1)) {
        bool brace_begin = false;
        for(int i = 0; i<it.length(); i++) {
            wchar_t c = it[i];
            
            if(c == '{') {
                brace_begin = true;
                indent++;
            }
            else if(c == '}') {
                brace_begin = false;
                indent--;
            }
        }
        
        int i;
        for(i=0; i<wcslen(it); i++) {
            if(it[i] != ' ') {
                break;
            }
        }
        var new_line = it.substring(i, -1);

        var head_str = new buffer.initialize();
        int indent2 = indent;
        if(brace_begin) {
            indent2--;
        }
        for(int i = 0; i<indent2; i++) {
            head_str.append_str("    ");
        }
        
        var new_line2 = borrow xsprintf("%ls%ls"
                    , head_str.to_string().to_wstring()
                    , new_line).to_wstring();
        
        self.texts.replace(it2+head, new_line2);

        it2++;
    }

    self.modifyOverCursorXValue();

    if(self.scroll+self.cursorY >= self.visualModeHead) {
        self.cursorY -= tail - head;

        self.modifyUnderCursorYValue();
    }
    
    self.modifyOverCursorYValue();
    self.modifyOverCursorXValue();

}

void ViWin_rewriteVisualMode(ViWin* self, Vi* nvi) 
{
    self.pushUndo();
    
    var key = self.getKey(false);

    int head = self.visualModeHead;
    int tail = self.scroll+self.cursorY;

    if(head >= tail) {
        int tmp = tail;
        tail = head;
        head = tmp;
    }
    
    int indent = 0;
    
    int it2 = 0;
    foreach(it, self.texts.sublist(head, tail+1)) {
        int len = it.length();
        
        wchar_t c = key;

        var buf = new buffer.initialize();

        for(int i=0; i<len; i++) {
            buf.append_str(xsprintf("%lc", c));
        }

        var new_line = borrow buf.to_string().to_wstring();

        self.texts.replace(it2+head, new_line);
        it2++;
    }

    self.modifyOverCursorXValue();

    if(self.scroll+self.cursorY >= self.visualModeHead) {
        self.cursorY -= tail - head;

        self.modifyUnderCursorYValue();
    }
    
    self.modifyOverCursorYValue();
    self.modifyOverCursorXValue();

}

void ViWin_deleteOnVisualMode(ViWin* self, Vi* nvi) 
{
    self.pushUndo();

    self.yankOnVisualMode(nvi);

    int head = self.visualModeHead;
    int tail = self.scroll+self.cursorY;

    if(head >= tail) {
        int tmp = tail;
        tail = head;
        head = tmp;
    }

    if(tail+1 >= self.texts.length()) {
        self.texts.delete(head, -1);
        self.texts.push_back(wstring(""));
    }
    else {
        self.texts.delete(head, tail+1);
    }

    if(self.scroll+self.cursorY >= self.visualModeHead) {
        self.cursorY -= tail - head;

        self.modifyUnderCursorYValue();
    }
    
    self.modifyOverCursorYValue();
    
}

void ViWin_makeInputedKeyGVIndent(ViWin* self, Vi* nvi) 
{
    /// implemented after layer
}

void ViWin_makeInputedKeyGVDeIndent(ViWin* self, Vi* nvi) 
{
    /// implemented after layer
}

void ViWin_inputVisualMode(ViWin* self, Vi* nvi)
{
    var key = self.getKey(false);

    switch(key) {
        case KEY_RIGHT:
        case 'l':
            self.forward();
            break;
        
        case KEY_LEFT:
        case 'h':
            self.backward();
            break;

        case KEY_DOWN:
        case 'j':
            self.nextLine();
            break;
    
        case KEY_UP:
        case 'k':
            self.prevLine();
            break;

        case '0':
            self.moveAtHead();
            break;

        case '$':
            self.moveAtTail();
            break;

        case 'C'-'A'+1:
            nvi.exitFromVisualMode();
            break;

        case 'D'-'A'+1:
            self.halfScrollDown();
            break;

        case 'U'-'A'+1:
            self.halfScrollUp();
            break;
            
        case 'G':
            self.moveBottom();
            break;

        case 'g':
            self.keyG(nvi);
            break;

        case 'y':
            self.yankOnVisualMode(nvi);
            nvi.exitFromVisualMode();
            break;

        case 'd':
            self.deleteOnVisualMode(nvi);
            nvi.exitFromVisualMode();
            break;

        case 'c': 
        case 'C': {
            self.deleteOnVisualMode(nvi);
            nvi.exitFromVisualMode();
            self.cursorX = self.visualModeHeadX;
            self.modifyOverCursorXValue();
            self.modifyUnderCursorXValue();
            nvi.enterInsertMode();
            }
            break;

        case '>':
            self.indentVisualMode(nvi);
            nvi.exitFromVisualMode();
    
            self.makeInputedKeyGVIndent(nvi);
            break;

        case '<':
            self.backIndentVisualMode(nvi);
            nvi.exitFromVisualMode();
            self.makeInputedKeyGVDeIndent(nvi);
            break;

        case '~':
            self.changeCaseVisualMode(nvi);
            nvi.exitFromVisualMode();
    
            self.makeInputedKeyGVIndent(nvi);
            break;
            
        case 'J':
            self.joinVisualMode(nvi);
            nvi.exitFromVisualMode();
            break;
            
        case '=':
            self.equalVisualMode(nvi);
            nvi.exitFromVisualMode();
            break;
            
        case '%':
            self.gotoBraceEnd(nvi);
            break;
            
        case 'r':
            self.rewriteVisualMode(nvi);
            break;

        case 27:
            nvi.exitFromVisualMode();
            break;
    }
    self.saveInputedKey();
}

void ViWin_input(ViWin* self, Vi* nvi) version 4
{
    if(nvi.mode == kVisualMode) {
        self.inputVisualMode(nvi);
    }
    else {
        inherit(self, nvi);
    }
}

void ViWin_restoreVisualMode(ViWin* self, Vi* nvi) version 2
{
    nvi.mode = kVisualMode;

    if(self.visualModeHeadBefore != -1) {
        self.visualModeHead = self.visualModeHeadBefore;
        self.cursorY = self.visualModeTailCursorYBefore;
        self.scroll = self.visualModeTailScrollBefore;
    }
}

void ViWin_gotoBraceEnd(ViWin* self, Vi* nvi) 
{
    /// implemeted after layer
}

Vi*% Vi_initialize(Vi*% self) version 8
{
    var result = inherit(self);

    result.events.replace('V', lambda(Vi* self, int key) 
    {
        self.enterVisualMode();
        self.activeWin.saveInputedKey();
    });

    return result;
}

void Vi_enterVisualMode(Vi* self) 
{
    self.mode = kVisualMode;
    self.activeWin.visualModeHead = self.activeWin.cursorY + self.activeWin.scroll;
    self.activeWin.visualModeHeadX = self.activeWin.cursorX;
}

void Vi_exitFromVisualMode(Vi* self) 
{
    self.mode = kEditMode;

    self.activeWin.visualModeHeadBefore = self.activeWin.visualModeHead;
    self.activeWin.visualModeTailCursorYBefore = self.activeWin.cursorY;
    self.activeWin.visualModeTailScrollBefore = self.activeWin.scroll;
}
