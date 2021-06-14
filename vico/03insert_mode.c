#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <limits.h>
#include <unistd.h>

void ViWin_insertModeView(ViWin* self, Vi* nvi)
{
    //werase(self.win);

    self.textsView(nvi);

    wattron(self.win, A_REVERSE);
    mvwprintw(self.win, self.height-1, 0, "INSERT MODE x %d y %d scroll %d", self.cursorX, self.scroll+self.cursorY, self.scroll);
    wattroff(self.win, A_REVERSE);

    //wrefresh(self.win);
}

void ViWin_view(ViWin* self, Vi* nvi) version 3
{
    if(nvi.mode == kInsertMode && self.equals(nvi.activeWin)) {
        self.insertModeView(nvi);
    }
    else {
        inherit(self, nvi);
    }
}

void ViWin_insertText(ViWin* self, wstring text) {
/*
    if(self.texts.length() == 0) {
        self.texts.push_back(clone text);
        self.cursorX += text.length();
    }
    else {
*/
FILE* f = fopen("AAA", "a");
fprintf(f, "1\n");
        var old_line = self.texts.item(self.scroll+self.cursorY, wstring(""));

fprintf(f, "2\n");
        //var new_line = wstring(xsprintf("%ls", old_line.substring(self.cursorX, -1)));
fprintf(f, "3\n");
        var new_line = borrow wstring("AAA");
        //var new_line = wstring(xsprintf("%ls%ls%ls", old_line.substring(0, self.cursorX), text, old_line.substring(self.cursorX, -1)));

        self.texts.replace(self.scroll+self.cursorY, new_line);
fprintf(f, "4\n");
        //self.cursorX += text.length();
fclose(f);
//    }
}

void ViWin_enterNewLine(ViWin* self)
{
    var old_line = self.texts.item(self.scroll+self.cursorY, wstring(""));

    int num_spaces = 0;
    for(int i=0; i<old_line.length(); i++)
    {
        if(old_line[i] == ' ') {
            num_spaces++;
        }
        else {
            break;
        }
    }

    var head_new_line = new wchar_t[num_spaces+1];

    wcsncpy(head_new_line, wstring(""), num_spaces+1);

    for(int i=0; i<num_spaces; i++) {
        wcsncat(head_new_line, wstring(" "), num_spaces+1);
    }

    var new_line1 = old_line.substring(0, self.cursorX);
    var new_line2 = wstring(xsprintf("%ls%ls", head_new_line, old_line.substring(self.cursorX, -1)));

    self.texts.replace(self.scroll+self.cursorY, new_line1);
    self.texts.insert(self.scroll+self.cursorY+1, new_line2);
    self.cursorY++;
    self.cursorX = num_spaces;

    self.modifyOverCursorYValue();
}

void ViWin_enterNewLine2(ViWin* self)
{
    var line = self.texts.item(self.scroll+self.cursorY, null);
    int num_spaces = 0;
    for(int i=0; i<line.length(); i++)
    {
        if(line[i] == ' ') {
            num_spaces++;
        }
        else {
            break;
        }
    }

    var new_line = new wchar_t[num_spaces+1];

    wcsncpy(new_line, wstring(""), num_spaces+1);

    for(int i=0; i<num_spaces; i++) {
        wcsncat(new_line, wstring(" "), num_spaces+1);
    }

    self.texts.insert(self.scroll+self.cursorY+1, new_line);
    self.cursorY++;
    self.cursorX = num_spaces;

    self.modifyOverCursorYValue();
}

void ViWin_backSpace(ViWin* self) 
{
    var line = self.texts.item(self.scroll+self.cursorY, wstring(""));

    if(line.length() > 0 && self.cursorX > 0) {
        line.delete(self.cursorX-1, self.cursorX);
        self.cursorX--;
    }
}

void ViWin_backIndent(ViWin* self) 
{
    self.pushUndo();

    var line = self.texts.item(self.scroll+self.cursorY, wstring(""));

    if(line.length() >= 4) {
        if(line.index(wstring("    "), -1) == 0) {
            for(int i=0; i<4; i++) {
                line.delete(0, 1);
                self.cursorX--;
                
                if(self.cursorX < 0) {
                    self.cursorX = 0;
                }
            }
        }
    }
}

void ViWin_blinkBraceFoward(ViWin* self, wchar_t head, wchar_t tail, Vi* nvi) 
{
}

void ViWin_blinkBraceEnd(ViWin* self, wchar_t head, wchar_t tail, Vi* nvi) 
{
}

void ViWin_inputInsertMode(ViWin* self, Vi* nvi)
{
    var key = self.getKey(false);
    
    if(key == 3 || key == 27) {
        nvi.exitFromInsertMode();
    }
    else if(key == 4) {
        self.backIndent();
    }
    else if(key == 10) {
        self.enterNewLine();
    }
    else if(key == 8 || key == 127 || key == KEY_BACKSPACE) {
        self.backSpace();
    }
    else if(key == 9) {
        var str = self.texts.item(self.scroll+self.cursorY, null).substring(0, self.cursorX);
        bool all_space = true;
        for(int i=0; i<str.length(); i++) {
            if(str[i] != ' ' && str[i] != '\t') {
                all_space = false;
            }
        }
        if(str[0] == '\0' || all_space) {
            self.insertText(wstring("    "));
        }
        else {
            self.completion(nvi);
        }
    }
    else if(key > 127) {
        var size = ((key & 0x80) >> 7) + ((key & 0x40) >> 6) + ((key & 0x20) >> 5) + ((key & 0x10) >> 4);

        char keys[MB_LEN_MAX];

        keys[0] = key;

        int i;
        for(i = 1; i<size; i++)
        {
            keys[i] = self.getKey(false);
        }
        keys[i] = '\0';

        self.insertText(wstring(keys));
    }
    else if(key == '(') {
        self.blinkBraceFoward('(', ')', nvi);
        self.insertText(wstring(xsprintf("%c", key)));
    }
    else if(key == '{') {
        self.blinkBraceFoward('{', '}', nvi);
        self.insertText(wstring(xsprintf("%c", key)));
    }
    else if(key == '[') {
        self.blinkBraceFoward('<', '>', nvi);
        self.insertText(wstring(xsprintf("%c", key)));
    }
    else if(key == ')') {
        self.blinkBraceEnd('(', ')', nvi);
        self.insertText(wstring(xsprintf("%c", key)));
    }
    else if(key == '}') {
        self.blinkBraceEnd('{', '}', nvi);
        self.insertText(wstring(xsprintf("%c", key)));
    }
    else if(key == ']') {
        self.blinkBraceEnd('[', ']', nvi);
        self.insertText(wstring(xsprintf("%c", key)));
    }
    else if(key == '>') {
        self.blinkBraceEnd('<', '>', nvi);
        self.insertText(wstring(xsprintf("%c", key)));
    }
    else if(key == 'W'-'A'+1) {
        int cursor_x = self.cursorX;
        int cursor_y = self.cursorY;
        
        self.backwardWord();
        
        if(cursor_y == self.cursorY) {
            var line = self.texts.item(self.scroll+self.cursorY, wstring(""));
            line.delete(self.cursorX, cursor_x+1);
         
            self.texts.replace(self.scroll+self.cursorY, clone line);
            self.modifyOverCursorXValue();
            self.cursorX++;
        }
        else {
            self.cursorY = cursor_y;
            var line = self.texts.item(self.scroll+self.cursorY, wstring(""));
            
            line.delete(0, cursor_x+1);
            
            self.texts.replace(self.scroll+self.cursorY, clone line);
                            
            self.cursorX = 0;
            self.cursorY = cursor_y;
        }
    }
    else if(key == 'V'-'A'+1) {
        var key2 = self.getKey(false);
        
        char str[2];
        
        str[0] = key2;
        str[1] = '\0';
        
        self.insertText(wstring(str));
    }
    else {
        char buf[128];
        snprintf(buf, 128, "%c", key);
        self.insertText(wstring(buf));
    }
}

void ViWin_input(ViWin* self, Vi* nvi) version 3
{
    if(nvi.mode == kInsertMode) {
        self.inputInsertMode(nvi);
    }
    else {
        inherit(self, nvi);
    }
}

void ViWin_pushUndo(ViWin* self) 
{
    /// implemented by the after layer
}

void ViWin_writedFlagOn(ViWin* self) 
{
    /// implemented by the after layer
}

void ViWin_completion(ViWin* self, Vi* nvi) 
{
    /// implemented by the after layer
}

void ViWin_clearInputedKey(ViWin* self) 
{
    /// implemented by the after layer
}

void ViWin_saveInputedKey(ViWin* self) 
{
    /// implemented by the after layer
}

void ViWin_backwardWord(ViWin* self) 
{
    /// implemented by the after layer
}

void Vi_enterInsertMode(Vi* self) 
{
    self.mode = kInsertMode;
    self.activeWin.writedFlagOn();
    self.activeWin.modifyOverCursorXValue();
    clear();
    self.activeWin.view(self);
    refresh();
}

void Vi_enterInsertMode2(Vi* self) 
{
    self.mode = kInsertMode;
    self.activeWin.writedFlagOn();
    self.activeWin.modifyOverCursorXValue2();
    clear();
    self.activeWin.view(self);
    refresh();
}

void Vi_exitFromInsertMode(Vi* self) 
{
    self.mode = kEditMode;
    self.activeWin.saveInputedKey();
}

Vi*% Vi_initialize(Vi*% self) version 3
{
    var result = inherit(self);

    result.mode = kEditMode;

    result.events.replace('i', lambda(Vi* self, int key) 
    {
        self.enterInsertMode();
    });
    result.events.replace('I', lambda(Vi* self, int key) 
    {
        if(self.activeWin.texts.length() != 0) {
            self.activeWin.moveAtHead();
        }
        self.enterInsertMode();
    });
    result.events.replace('a', lambda(Vi* self, int key) 
    {
        self.enterInsertMode();
        if(self.activeWin.texts.length() != 0) {
            self.activeWin.cursorX++;
        }
    });
    result.events.replace('A', lambda(Vi* self, int key) 
    {
        if(self.activeWin.texts.length() != 0) {
            self.activeWin.moveAtTail();
        }
        self.enterInsertMode();
        if(self.activeWin.texts.length() != 0) {
            self.activeWin.cursorX++;
        }
    });
    result.events.replace('o', lambda(Vi* self, int key) 
    {
        self.enterInsertMode();
        if(self.activeWin.texts.length() != 0) {
            self.activeWin.enterNewLine2();
        }
    });

    return result;
}

int Vi_main_loop(Vi* self) version 3
{
    while(!self.appEnd) {
        erase();

        foreach(it, self.wins) {
            it.view(self);
        }

        if(self.mode != kInsertMode) {
            self.activeWin.clearInputedKey();
        }
        self.activeWin.input(self);
    }

    return 0;
}

